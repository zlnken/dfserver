#include "ToolsServer.h"
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
ToolsServer* ToolsServer::m_pInstance = NULL;
// -----------------------------------------------------------------------
ToolsServer::~ToolsServer(void)
{
}
// -----------------------------------------------------------------------
ToolsServer::ToolsServer(void)
{
}
// -----------------------------------------------------------------------
ToolsServer* ToolsServer::instancePtr(void)
{
	if (!m_pInstance)
		m_pInstance = new ToolsServer;
	return m_pInstance;
}
// -----------------------------------------------------------------------
void ToolsServer::unintance(void)
{
	DF_SAFE_DELETE(m_pInstance);
}
// -----------------------------------------------------------------------
void ToolsServer::init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread)
{
	BaseServer::init(argc, argv, port, maxConnect, maxThread, true);
	DF_INFO << "log server("<<m_pNetWork->getIP() <<")"<<"start prot(" << m_pNetWork->getPort() << ")" << DF_END;
}
// -----------------------------------------------------------------------
void ToolsServer::finish(void)
{
	BaseServer::finish();
}
// -----------------------------------------------------------------------
void ToolsServer::loop(void)
{
	BaseServer::loop();
}
