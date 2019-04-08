#include "DFProcess.h"
#include "DFB4.h"
#include "DFB8.h"
#include "DFIO.h"


namespace DF{
	// -----------------------------------------------------------------------
	Process* Process::m_pInstance = NULL;
	// -----------------------------------------------------------------------
	Process::~Process(void)
	{
	}
	// -----------------------------------------------------------------------
	Process::Process(void):
	m_sProcessType(""),
	m_uProcessID(0),
	m_uTGW_LF_Count(0),
	m_DefualConnectParam()
	{
	}
	// -----------------------------------------------------------------------
	Process* Process::instancePtr(void)
	{
		if (!m_pInstance)
			m_pInstance = new Process;
		return m_pInstance;
	}
	// -----------------------------------------------------------------------
	void Process::uninstance(void)
	{
		DF_SAFE_DELETE(m_pInstance);
	}
	// -----------------------------------------------------------------------
	void Process::sysCheck(void)
	{
		//这里确保系统是小端结DF_ASSERT(sizeof(DF::B4) == 4);
		DF_ASSERT(sizeof(DF::B8) == 8);
		DF_ASSERT(sizeof(long) >= 4);
		DF::B4 b4;
		b4.uI16_0() = 1;
		DF_ASSERT(b4 == 1);
		DF::B8 b8(5, 0);
		DF_ASSERT(b8 == 5);
	}
	// -----------------------------------------------------------------------
	void Process::init(int argc, char *argv[])
	{
		sysCheck();
		if (argc > 2)
		{
			m_sProcessType = argv[1];
			m_uProcessID = atoi(argv[2]);
		}

#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS 
		// 让用户输入一个非0的进程ID
		if (m_sProcessType.empty())
		{
			m_sProcessType = "LogicServer";
			m_uProcessID = 1;
			//DF_OUT << DF::green << "input process group and id(not 0): ";
			//DF_IN >> m_sProcessType >> m_uProcessID;
		}
		// 注意清空输入缓冲flush(stdin);
#endif
	}
	// -----------------------------------------------------------------------
	std::string	Process::makeProcessKey(const std::string& sType, unsigned short uID)
	{
		std::stringstream ss;
		ss << sType << "." << uID;
		return ss.str();
	}
	// -----------------------------------------------------------------------
	const std::string& Process::getProcessType(void)const
	{
		return m_sProcessType;
	}
	// -----------------------------------------------------------------------
	unsigned short Process::getProcessID(void)const
	{
		return m_uProcessID;
	}
	// -----------------------------------------------------------------------
	unsigned short Process::getLFCount(void)const
	{
		return m_uTGW_LF_Count;
	}
	// -----------------------------------------------------------------------
	unsigned short Process::getSendBlockSize(void)const
	{
		return m_DefualConnectParam.uSendBlockSize;
	}
	// -----------------------------------------------------------------------
	unsigned short Process::getSendBlockNum(void)const
	{
		return m_DefualConnectParam.uSendBlockNum;
	}
	// -----------------------------------------------------------------------
	unsigned short Process::getRecvBlockSize(void)const
	{
		return m_DefualConnectParam.uRecvBlockSize;
	}
	// -----------------------------------------------------------------------
	unsigned short Process::getRecvBlockNum(void)const
	{
		return m_DefualConnectParam.uRecvBlockNum;
	}

}