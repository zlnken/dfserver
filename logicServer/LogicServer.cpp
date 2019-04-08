#include "LogicServer.h"
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
// -----------------------------------------------------------------------
LogicServer* LogicServer::m_pInstance = NULL;
// -----------------------------------------------------------------------
LogicServer::~LogicServer(void)
{
}
// -----------------------------------------------------------------------
LogicServer::LogicServer(void)
{
}
// -----------------------------------------------------------------------
LogicServer* LogicServer::instancePtr(void)
{
	if (!m_pInstance)
		m_pInstance = new LogicServer;
	return m_pInstance;
}
// -----------------------------------------------------------------------
void LogicServer::unintance(void)
{
	DF_SAFE_DELETE(m_pInstance);
}
// -----------------------------------------------------------------------
void LogicServer::init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread)
{
	BaseServer::init(argc, argv, port, maxConnect, maxThread);
	DF_INFO << "log server(" << m_pNetWork->getIP() << ")" << "start prot(" << m_pNetWork->getPort() << ")" << DF_END;
}
// -----------------------------------------------------------------------
void LogicServer::finish(void)
{
	BaseServer::finish();
}
// -----------------------------------------------------------------------
void LogicServer::loop(void)
{
	BaseServer::loop();
}
