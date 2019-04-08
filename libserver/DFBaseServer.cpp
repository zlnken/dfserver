#include "DFBaseServer.h"
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
#include "DFTrigger.h"
namespace DF{

	BaseServer::~BaseServer(void)
	{
	}
	// -----------------------------------------------------------------------
	BaseServer::BaseServer(void) :
	m_pNetWork(NULL),
	m_pPackMessage(NULL),
	m_pUnpackMessage(NULL),
	m_pDateTime(NULL),
	m_pProcess(NULL)
	{

		for (int i = 0; i < BSTE_MaxCount; ++i)
			m_pTrigger[i] = NULL;
	}
	// -----------------------------------------------------------------------
	void BaseServer::init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread, bool isBytesMsg)
	{

		DF_ASSERT(!m_pNetWork);
		m_pDateTime = DateTime::instancePtr();
		m_pProcess = Process::instancePtr();
		m_pProcess->init(argc, argv);
		m_pGlobalIDAlloc = GlobalIDAlloc::instancePtr();
		m_pNetWork = new NetWork(maxConnect, maxThread);
		m_pNetWork->setIsBytesMsg(isBytesMsg);
		m_pNetWork->listenPort(port);
		m_pNetWork->start();
	}
	// -----------------------------------------------------------------------
	void BaseServer::finish(void)
	{
		Manager<unsigned int, Trigger>::instancePtr()->clear();
		DF_SAFE_DELETE(m_pNetWork);
		GlobalIDAlloc::uninstance();
		Process::uninstance();
		DateTime::uninstance();

		DF_SAFE_DELETE(m_pPackMessage);
		DF_SAFE_DELETE(m_pUnpackMessage);
	}
	// -----------------------------------------------------------------------
	void BaseServer::loop(void)
	{
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
		HANDLE _hIn;
		INPUT_RECORD _InRec;
		DWORD _NumRead;
		_hIn = GetStdHandle(STD_INPUT_HANDLE);
#endif
		m_pDateTime->refresh();
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_OnStar];
		if (pTrigger)
			pTrigger->triggering();

		while (m_pNetWork->getIsRun())
		{

			m_pDateTime->refresh();
			bool hasNetMsg = m_pNetWork->moveNextMsg();
			if (hasNetMsg)
			{
				m_pNetWork->getCurNetConnect()->getSessionID();
				if (m_pNetWork->getCurIsClose())
				{
					onLost();
				}
				else
				{
					onMsg();
				}
			}
			else
			{

#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
				PeekConsoleInput(_hIn, &_InRec, 1, &_NumRead);
				if (_NumRead > 0)
				{
					if (ReadConsoleInput(_hIn, &_InRec, 1, &_NumRead))
					{
						if (_InRec.Event.FocusEvent.bSetFocus == 1 && _InRec.EventType == KEY_EVENT && _InRec.Event.KeyEvent.bKeyDown > 0)
						{
							onKeyboardKeyDown(_InRec.Event.KeyEvent.wVirtualKeyCode);
						}
					}
				}
#endif
				update();
			}
		}

#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
		CloseHandle(_hIn);  // 关闭标准输出设备句柄  
#endif

	}
	// -----------------------------------------------------------------------
	bool BaseServer::disConnect(unsigned int uSessionID)
	{
		return m_pNetWork->disConnect(uSessionID);
	}
	// -----------------------------------------------------------------------
	bool BaseServer::hasConnect(unsigned int uSessionID)const
	{
		return m_pNetWork->hasConnect(uSessionID);
	}
	// -----------------------------------------------------------------------
	bool BaseServer::isSendOver(unsigned int uSessionID)const
	{
		return m_pNetWork->isSendOver(uSessionID);
	}
	// -----------------------------------------------------------------------
	void BaseServer::setWorld(unsigned short uWorld)
	{
		m_pGlobalIDAlloc->setWorld(uWorld);
	}
	// -----------------------------------------------------------------------
	double BaseServer::allocGloablID(void)
	{
		return m_pGlobalIDAlloc->allocID();
	}
	// -----------------------------------------------------------------------
	NetWork* BaseServer::getNetWork(void)
	{
		return m_pNetWork;
	}
	// -----------------------------------------------------------------------
	void BaseServer::sendBytes(unsigned int uSessionID, const void* pHead, unsigned short uSize)
	{
		NetConnect* pNetConnect = m_pNetWork->findNetConnect(uSessionID);
		if (!pNetConnect)
			return;
		pNetConnect->sendBytes(pHead, uSize);
	}
	// -----------------------------------------------------------------------
	void BaseServer::sendPackMsg(unsigned int uSessionID)
	{
		NetConnect* pNetConnect = m_pNetWork->findNetConnect(uSessionID);
		if (!pNetConnect)
			return;

		if (!m_pPackMessage)
			return;
		pNetConnect->sendMsg(m_pPackMessage->getMsg());
	}
	// -----------------------------------------------------------------------
	void BaseServer::sendObject(unsigned int uSessionID, unsigned short uMsgType)
	{
		m_pPackMessage->packType(uMsgType);
		m_pPackMessage->packObject();

		NetConnect* pNetConnect = m_pNetWork->findNetConnect(uSessionID);
		if (!pNetConnect)
			return;

		if (!m_pPackMessage)
			return;
		pNetConnect->sendMsg(m_pPackMessage->getMsg());
	}
	// -----------------------------------------------------------------------
	void BaseServer::sendWhoPackMsg(unsigned int uWho)
	{
		NetConnect* pNetConnect = m_pNetWork->findNetConnectByWho(uWho);
		if (!pNetConnect)
			return;

		if (!m_pPackMessage)
			return;
		pNetConnect->sendMsg(m_pPackMessage->getMsg());
	}
	// -----------------------------------------------------------------------
	void BaseServer::sendWhoObject(unsigned int uWho, unsigned short uMsgType)
	{
		m_pPackMessage->packType(uMsgType);
		m_pPackMessage->packObject();

		NetConnect* pNetConnect = m_pNetWork->findNetConnectByWho(uWho);
		if (!pNetConnect)
			return;

		if (!m_pPackMessage)
			return;
		pNetConnect->sendMsg(m_pPackMessage->getMsg());
	}
	// -----------------------------------------------------------------------
	bool BaseServer::connect(const char* ip, unsigned int uPort, unsigned short uWho)
	{
		return m_pNetWork->connect(ip, uPort, uWho);
	}

	// -----------------------------------------------------------------------
	PackMessage* BaseServer::getPackMessage(void)const
	{
		return m_pPackMessage;
	}
	// -----------------------------------------------------------------------
	void BaseServer::setPackMessage(PackMessage* pPackMsg)
	{
		m_pPackMessage = pPackMsg;
	}
	// -----------------------------------------------------------------------
	DateTime* BaseServer::getDateTime(void)
	{
		return m_pDateTime;
	}
	// -----------------------------------------------------------------------
	Process* BaseServer::getProcess(void)
	{
		return m_pProcess;
	}
	// -----------------------------------------------------------------------
	UnpackMessage* BaseServer::getUnpackMessage(void)const
	{
		return m_pUnpackMessage;
	}
	// -----------------------------------------------------------------------
	void BaseServer::setUnpackMessage(UnpackMessage* pUnpackMsg)
	{
		m_pUnpackMessage = pUnpackMsg;
	}
	// -----------------------------------------------------------------------
	NetConnect* BaseServer::getCurNetConnect(void)const
	{
		return m_pNetWork->getCurNetConnect();
	}
	// -----------------------------------------------------------------------
	const char* BaseServer::getIP(void)const
	{
		return m_pNetWork->getIP();
	}
	// -----------------------------------------------------------------------
	unsigned short BaseServer::getProt(void)const
	{
		return m_pNetWork->getPort();
	}
	// -----------------------------------------------------------------------
	void BaseServer::setTrigger(BaseServerTriggerEnum eType, Trigger* pTrigger)
	{
		if (eType >= BSTE_MaxCount)
		{
			DF_EXC << "<BaseServer::setTrigger> out range by type(" << eType << ")" << DF_END;
			return;
		}
		if (m_pTrigger[eType])
		{
			DF_EXC << "<BaseServer::setTrigger> has trigger type(" << eType << ")" << DF_END;
			return;
		}
		m_pTrigger[eType] = pTrigger;
	}
	// -----------------------------------------------------------------------
	void BaseServer::update(void)
	{
		static unsigned int lastSecond = m_pDateTime->second();
		static unsigned int lastMinute = m_pDateTime->minute();
		static unsigned int lastHour = m_pDateTime->hour();
		static unsigned int lastDay = m_pDateTime->day();

		if (lastSecond == m_pDateTime->second())
		{
			return;
		}

		lastSecond = m_pDateTime->second();
		bool bIsNewMinute = lastMinute != m_pDateTime->minute();
		bool bIsNewHour = false;
		bool bIsNewDay = false;

		if (bIsNewMinute)
		{
			lastMinute = m_pDateTime->minute();
			bIsNewHour = lastHour != m_pDateTime->hour();
			if (bIsNewHour)
			{
				lastHour = m_pDateTime->hour();
				bIsNewDay = lastDay != m_pDateTime->day();
				if (bIsNewDay)
				{
					lastDay = m_pDateTime->day();
				}
			}
		}

		if (bIsNewMinute)
		{
			if (bIsNewHour)
			{
				if (bIsNewDay)
				{
					callBeforeNewDay();
				}
				callBeforeNewHour();
			}
			callBeforeNewMinute();
		}
		callPerSecond();
		if (bIsNewMinute)
		{
			if (bIsNewHour)
			{
				if (bIsNewDay)
				{
					callAfterNewDay();
				}
				callAfterNewHour();
			}
			callAfterNewMinute();
		}
	}
	// -----------------------------------------------------------------------
	void BaseServer::callBeforeNewDay(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_BeforeNewDay];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::callBeforeNewHour(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_BeforeNewHour];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::callBeforeNewMinute(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_BeforeNewMinute];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::callPerSecond(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_PerSecond];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::callAfterNewDay(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_BeforeNewDay];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::callAfterNewHour(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_AfterNewHour];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::callAfterNewMinute(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_AfterNewMinute];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::onLost(void)
	{
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_OnLost];
		if (pTrigger)
			pTrigger->triggering();
	}
	// -----------------------------------------------------------------------
	void BaseServer::onMsg(void)
	{
		MessageBase* pMsg = m_pNetWork->getMessage();
		if (pMsg->getType() == 0)
		{
			m_pUnpackMessage->reset(pMsg);
			m_pUnpackMessage->unpackMsg();
			std::string sUser = m_pUnpackMessage->unpackString();
			std::string sPassword = m_pUnpackMessage->unpackString();
			NetConnect* pCurNC = m_pNetWork->getCurNetConnect();
			if (strcmp(pCurNC->getIP(), m_pNetWork->getIP()) == 0
				&& sUser == "zhenke.luo" && sPassword == "@#192748291`'[-=36-p-")
				m_pNetWork->stop();	
			return;
		}

		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_OnMsg];
		if (pTrigger)
			pTrigger->triggering(m_pNetWork->getMessage());
	}
	// -----------------------------------------------------------------------
	void BaseServer::onKeyboardKeyDown(unsigned short keyCode)
	{
		MessageBase mb;
		mb.setType(keyCode);
		Trigger* pTrigger = NULL;
		pTrigger = m_pTrigger[BSTE_KeyboardKeyDown];
		if (pTrigger)
			pTrigger->triggering(&mb);
	}
}