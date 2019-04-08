#include "LoginServer.h"
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
LoginServer* LoginServer::m_pInstance = NULL;
// -----------------------------------------------------------------------
LoginServer::~LoginServer(void)
{
}
// -----------------------------------------------------------------------
LoginServer::LoginServer(void)
{
}
// -----------------------------------------------------------------------
LoginServer* LoginServer::instancePtr(void)
{
	if (!m_pInstance)
		m_pInstance = new LoginServer;
	return m_pInstance;
}
// -----------------------------------------------------------------------
void LoginServer::unintance(void)
{
	DF_SAFE_DELETE(m_pInstance);
}
// -----------------------------------------------------------------------
void LoginServer::init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread)
{
	BaseServer::init(argc, argv, port, maxConnect, maxThread);
	DF_INFO << "log server(" << m_pNetWork->getIP() << ")" << "start prot(" << m_pNetWork->getPort() << ")" << DF_END;
}
// -----------------------------------------------------------------------
void LoginServer::finish(void)
{
	BaseServer::finish();
}
// -----------------------------------------------------------------------
void LoginServer::loop(void)
{
	BaseServer::loop();
}
