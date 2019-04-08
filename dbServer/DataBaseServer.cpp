#include "DataBaseServer.h"
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
DataBaseServer* DataBaseServer::m_pInstance = NULL;
// -----------------------------------------------------------------------
DataBaseServer::~DataBaseServer(void)
{
}
// -----------------------------------------------------------------------
DataBaseServer::DataBaseServer(void)
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
	BaseServer::init(argc, argv, port, maxConnect, maxThread, true);
	DF_INFO << "log server(" << m_pNetWork->getIP() << ")" << "start prot(" << m_pNetWork->getPort() << ")" << DF_END;
}
// -----------------------------------------------------------------------
void DataBaseServer::finish(void)
{
	BaseServer::finish();
}
// -----------------------------------------------------------------------
void DataBaseServer::loop(void)
{
	BaseServer::loop();
}
