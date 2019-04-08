#include "DFDataBaseMySQL.h"
#include "DFIO.h"
#include "DFDateTime.h"
#include "DFPackMessage.h"
#include "DFMessageBase.h"
#include "DFUnpackMessage.h"
#include <mysql.h>
namespace DF{
	// -----------------------------------------------------------------------
	static MYSQL						myCont;
	static MYSQL_RES*					result;
	static MYSQL_ROW					sql_row;
	static MYSQL_FIELD*					fd;
	static MYSQL_STMT*					stmt = NULL;
	static std::vector<MYSQL_BIND>		binds;

	// -----------------------------------------------------------------------
	DataBaseMySQL::~DataBaseMySQL(void)
	{
		mysql_close(&myCont);
	}
	// -----------------------------------------------------------------------
	DataBaseMySQL::DataBaseMySQL(void):
	m_sUser(""),
	m_sPawd(""),
	m_sHost(""),
	m_sIP(""),
	m_uPort(0)
	{
	}
	// -----------------------------------------------------------------------
	bool DataBaseMySQL::connect(const char* host, const char* user, const char* passwd, unsigned short port, const char* ip)
	{
		if (NULL == mysql_init(&myCont))
		{
			DF_EXC << "can't not init Mysql" << DF_END;
			return false;
		}

		if (NULL == mysql_real_connect(&myCont, host, user, passwd, NULL, port, ip, 0))
		{
			const char* error = mysql_error(&myCont);
			DF_EXC << error << DF_END;
			return false;
		}

		mysql_query(&myCont, "SET NAMES utf8");
		mysql_query(&myCont, "ALTER TABLE `wp_posts` ENGINE = MyISAM;");
		
		m_sHost = host;
		m_sUser = user;
		m_sPawd = passwd;
		m_uPort = port;
		return true;
	}
	// -----------------------------------------------------------------------
	bool DataBaseMySQL::execute(const char* sql, PackMessage* pPackMsg)
	{
		int res = mysql_query(&myCont, sql);
		if (res)
		{
			const char* error = mysql_error(&myCont);
			DF_EXC << error << DF_END;
			return false;
		}

		MYSQL_RES* result = mysql_store_result(&myCont);
		if (!result)
		{
			return true;
		}
			
		
		MYSQL_ROW sql_row;
		MYSQL_FIELD* fd;
		std::vector<MYSQL_FIELD*> fdlist;
		while (fd = mysql_fetch_field(result))
		{
			fdlist.push_back(fd);
		}

		size_t checkMaxCol = fdlist.size();
		if (checkMaxCol > Config::MAX_UINT16)
		{
			DF_EXC << "execute sql can't not pack message by maxCol(" << checkMaxCol << ")" << DF_END;
			return false;
		}

		my_ulonglong checkMaxRow = mysql_num_rows(result);
		if (checkMaxRow > Config::MAX_UINT16)
		{
			DF_EXC << "execute sql can't not pack message by maxRow(" << checkMaxRow << ")" << DF_END;
			return false;
		}

		if (!pPackMsg)
		{
			DF_EXC << "execute sql pPackMsg is NULL" << DF_END;
			return false;
		}

		unsigned short maxCol = static_cast<unsigned short>(checkMaxCol);
		unsigned short maxRow = static_cast<unsigned short>(checkMaxRow);
		pPackMsg->packDict(maxRow);

		unsigned short row = 0;
		for (unsigned short r = 0; r < maxRow; ++r)
		{
			pPackMsg->packInt(r+1);

			sql_row = mysql_fetch_row(result);
			pPackMsg->packDict(maxCol);

			for (unsigned short c = 0; c < maxCol; ++c)
			{
				pPackMsg->packInt(c+1);
				fd = fdlist[c];
				char* val = sql_row[c];
				if (MYSQL_TYPE_SHORT == fd->type || MYSQL_TYPE_LONG == fd->type || MYSQL_TYPE_TINY == fd->type || MYSQL_TYPE_LONGLONG == fd->type)
				{ 
					pPackMsg->packValue(atof(val));
				}
				else if (MYSQL_TYPE_FLOAT == fd->type || MYSQL_TYPE_DOUBLE == fd->type || MYSQL_TYPE_DECIMAL == fd->type)
				{
					pPackMsg->packValue(atof(val));
				}
				else if (MYSQL_TYPE_STRING == fd->type || MYSQL_TYPE_VAR_STRING == fd->type)
				{	
					pPackMsg->packString(val);
				}
				else if (MYSQL_TYPE_BLOB == fd->type)
				{
					if (0 == fd->max_length)
						pPackMsg->packInt8(Config::NONE_FLAG);
					else
						pPackMsg->packBytes((void*)val, fd->max_length);
				}
				else if (MYSQL_TYPE_NULL == fd->type)	
				{
					pPackMsg->packInt8(Config::NONE_FLAG);
				}
				else if (MYSQL_TYPE_BIT == fd->type)
				{
					int b = atoi(val);
					pPackMsg->packInt8( b > 0 ? Config::TRUE_FLAG : Config::FALSE_FLAG);
				}
				else
				{
					DF_EXC << "execute sql can't not pack message by SqlType(" << fd->flags << ")" << DF_END;
					return false;
				}
			}
			++row;
		}
		mysql_free_result(result);
		
		return true;
	}
	// -----------------------------------------------------------------------
	bool DataBaseMySQL::executeStmt(const char* sql, UnpackMessage* unpack)
	{
		binds.clear();
		stmt = mysql_stmt_init(&myCont);
		int res = mysql_stmt_prepare(stmt, sql, static_cast<unsigned long>(strlen(sql)));
		if (res)
		{
			const char* error = mysql_error(&myCont);
			binds.clear();
			//mysql_stmt_free_result(stmt);
			mysql_stmt_close(stmt);
			DF_EXC << error << DF_END;
			return false;
		}

		unsigned int count = 0;
		char t = unpack->unpackInt8();
		if (t != Config::SMALL_DICT_FLAG && t != Config::BIG_DICT_FLAG)
			return false;

		if (t == Config::SMALL_DICT_FLAG)
			count = unpack->unpackUint8();
		else if (t == Config::BIG_DICT_FLAG)
			count = unpack->unpackUint16();



		for (unsigned int i = 0; i < count; ++i)
		{
			double ikey = unpack->unpackValue();
			
			char* pUnpackFence = (char*)unpack->getUnpackFence();
			unsigned short uSurplusSize = unpack->getSurplusSize();
			
			t = unpack->unpackInt8();
			if (Config::SIGNED_INT8_FLAG == t)
			{
				pushData(MYSQL_TYPE_TINY, static_cast<const char*>(unpack->unpackStream(1)));
			}
			else if (Config::SIGNED_INT16_FLAG == t)
			{
				pushData(MYSQL_TYPE_SHORT, static_cast<const char*>(unpack->unpackStream(2)));
			}
			else if (Config::SIGNED_INT32_FLAG == t)
			{
				pushData(MYSQL_TYPE_LONG, static_cast<const char*>(unpack->unpackStream(4)));
			}
			else if (Config::FLOAT_FLAG == t)
			{
				pushData(MYSQL_TYPE_FLOAT, static_cast<const char*>(unpack->unpackStream(4)));
			}
			else if (Config::DOUBLE_FLAG == t)
			{
				pushData(MYSQL_TYPE_DOUBLE, static_cast<const char*>(unpack->unpackStream(8)));
			}
			else if (Config::SMALL_STRING_FLAG == t)
			{
				unsigned char uSize = unpack->unpackUint8();
				void* data = unpack->unpackStream(static_cast<unsigned short>(uSize));
				pushString((const char*)data);
			}
			else if (Config::BIG_STRING_FLAG == t)
			{
				unsigned short uSize = unpack->unpackUint16();
				void* data = unpack->unpackStream(static_cast<unsigned short>(uSize));
				pushString((const char*)data);
			}
			else if (Config::FALSE_FLAG == t || Config::TRUE_FLAG == t || Config::NONE_FLAG == t)
			{
				pushData(MYSQL_TYPE_TINY, static_cast<const char*>(pUnpackFence));
			}
			else if (Config::SMALL_DICT_FLAG == t || Config::BIG_DICT_FLAG == t)
			{
				pushBlob(pUnpackFence, uSurplusSize);
				unpack->reset(pUnpackFence, uSurplusSize);
			}
			else
			{
				DF_EXC << "can not support sql type" << DF_END;
				return false;
			}
		}
		return executeStmt();
	}
	// -----------------------------------------------------------------------
	bool DataBaseMySQL::initStmt(const char* sql)
	{
		if (stmt)
		{
			DF_EXC << "initStmt stmt not NULL memory is Leak" << DF_END;
			mysql_stmt_free_result(stmt);
			return false;
		}

		stmt = mysql_stmt_init(&myCont);
		int res = mysql_stmt_prepare(stmt, sql, static_cast<unsigned long>(strlen(sql)));
		if (res)
		{
			binds.clear();
			mysql_stmt_free_result(stmt);
			const char* error = mysql_error(&myCont);
			DF_EXC << error << DF_END;
			return false;
		}

		return true;
	}
	// -----------------------------------------------------------------------
	void DataBaseMySQL::pushString(const char* val)
	{
		MYSQL_BIND bind;
		memset(&bind, 0, sizeof(MYSQL_BIND));
		size_t len = strlen(val) + 1;
		//char* data = new char[len];
		//memcpy(data, val, len);

		if (len > Config::MAX_UINT8)
		{
			bind.buffer_type = MYSQL_TYPE_VAR_STRING;
			bind.buffer = (void*)(val);
			bind.buffer_length = static_cast<unsigned long>(len);
			bind.is_null = 0;
		}
		else
		{
			bind.buffer_type = MYSQL_TYPE_STRING;
			bind.buffer = (void*)(val);
			bind.buffer_length = static_cast<unsigned long>(len);
			bind.is_null = 0;
		}
		binds.push_back(bind);
	}
	// -----------------------------------------------------------------------
	void DataBaseMySQL::pushBlob(const char* val, unsigned int len)
	{
		//char* data = new char[len];
		//memcpy(data, val, len);
		MYSQL_BIND bind;
		memset(&bind, 0, sizeof(MYSQL_BIND));
		bind.buffer_type = MYSQL_TYPE_BLOB;
		bind.buffer = (void*)(val);
		bind.buffer_length = len;
		bind.is_null = 0;
		binds.push_back(bind);
	}
	// -----------------------------------------------------------------------
	void DataBaseMySQL::pushData(int type, const char* val, unsigned int len)
	{
		MYSQL_BIND bind;
		char* data = new char[len];
		//memcpy(data, val, len);
		//memset(&bind, 0, sizeof(MYSQL_BIND));
		bind.buffer_type = static_cast<enum_field_types>(type);
		bind.buffer = (void*)(val);
		bind.buffer_length = len;
		bind.is_null = 0;
		binds.push_back(bind);
	}

	// -----------------------------------------------------------------------
	bool DataBaseMySQL::executeStmt(void)
	{
		int ret = mysql_stmt_bind_param(stmt, &(binds[0]));
		if (ret)
		{
			mysql_stmt_close(stmt);
			binds.clear();
			const char* error = mysql_error(&myCont);
			DF_EXC << error << DF_END;
			return false;
		}

		ret = mysql_stmt_execute(stmt);
		if (ret)
		{
			//mysql_stmt_free_result(stmt);
			mysql_stmt_close(stmt);
			binds.clear();
			const char* error = mysql_error(&myCont);
			DF_EXC << error << DF_END;
			return false;
		}

		//prepare_meta_result = mysql_stmt_result_metadata(stmt);
		//column_count = mysql_num_fields(prepare_meta_result);

		//mysql_stmt_result_metadata(stmt);
		//mysql_stmt_free_result(stmt);
		binds.clear();
		mysql_stmt_close(stmt);
		return true;
	}


	// -----------------------------------------------------------------------
	const char* DataBaseMySQL::getUser(void)const
	{
		return m_sUser.c_str();
	}
	// -----------------------------------------------------------------------
	const char* DataBaseMySQL::getPassword(void)const
	{
		return m_sPawd.c_str();
	}
	// -----------------------------------------------------------------------
	const char* DataBaseMySQL::getHost(void)const
	{
		return m_sHost.c_str();
	}
	// -----------------------------------------------------------------------
	const char* DataBaseMySQL::getIP(void)const
	{
		return m_sIP.c_str();
	}
	// -----------------------------------------------------------------------
	unsigned short DataBaseMySQL::getPort(void)const
	{
		return m_uPort;
	}


}