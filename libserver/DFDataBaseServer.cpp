#include "DFDataBaseServer.h"
#include "DFNetWork.h"
#include "DFProcess.h"
#include "DFDateTime.h"
#include "DFIO.h"
#include "DFMessageBase.h"
#include "DFPackMessage.h"
#include "DFUnpackMessage.h"
#include "DFTrigger.h"
#include "DFManager.h"
#include "DFGlobalIDAlloc.h"
#include "DFNetConnect.h"
#include "DFDataBaseMySQL.h"
namespace DF{
	// -----------------------------------------------------------------------
	DataBaseServer*	DataBaseServer::m_pInstance = NULL;
	// -----------------------------------------------------------------------
	DataBaseServer::~DataBaseServer(void)
	{
	}
	// -----------------------------------------------------------------------
	DataBaseServer::DataBaseServer(void) :
	m_pDBSql(NULL)
	{

	}
	// -----------------------------------------------------------------------
	DataBaseServer* DataBaseServer::instancePtr(void)
	{
		if (!m_pInstance)
			m_pInstance = new DataBaseServer;
		return m_pInstance;
	}
	// -----------------------------------------------------------------------
	void DataBaseServer::unintance(void)
	{
		DF_SAFE_DELETE(m_pInstance);
	}
	// -----------------------------------------------------------------------
	void DataBaseServer::init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread)
	{
		BaseServer::init(argc, argv, port, maxConnect, maxThread);
		DF_INFO << "log server(" << m_pNetWork->getIP() << ")" << "start prot(" << m_pNetWork->getPort() << ")" << DF_END;
	}
	// -----------------------------------------------------------------------
	bool DataBaseServer::initDataBase(const char* host, const char* user, const char* passwd, unsigned short port, const char* ip)
	{
		DF_ASSERT(!m_pDBSql);
		m_pDBSql = new DataBaseMySQL;
		return m_pDBSql->connect(host, user, passwd, port, ip);
	}
	// -----------------------------------------------------------------------
	bool DataBaseServer::executeSQL(const char* sql)
	{
		DF_ASSERT(m_pDBSql);
		return m_pDBSql->execute(sql, m_pPackMessage);
	}
	// -----------------------------------------------------------------------
	bool DataBaseServer::executeStmt(const char* sql, UnpackMessage* unpack)
	{
		DF_ASSERT(m_pDBSql);
		return m_pDBSql->executeStmt(sql, unpack);
	}
	// -----------------------------------------------------------------------
	void DataBaseServer::finish(void)
	{
		DF_SAFE_DELETE(m_pDBSql);
		BaseServer::finish();
	}
	// -----------------------------------------------------------------------
	void DataBaseServer::loop(void)
	{
		BaseServer::loop();
	}
	// -----------------------------------------------------------------------
	DataBaseMySQL* DataBaseServer::getDataBaseMySQL(void)const
	{
		return m_pDBSql;
	}
}