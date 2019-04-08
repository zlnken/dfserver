#include "DFNetWork.h"
#include "DFIO.h"
#include "DFDateTime.h"
#include "DFNetConnect.h"
namespace DF{
	// -----------------------------------------------------------------------
	NetWork::~NetWork(void)
	{
		stop();
		DF_SAFE_DELETE(m_pAcceptor);
		for (unsigned int uIdx = 0; uIdx < static_cast<unsigned int>(m_pNetWorkThreads.size()); ++uIdx)
		{
			DF_SAFE_DELETE(m_pNetWorkThreads.at(uIdx));
		}
		if (NULL != this->m_pAsyncSendThread)
		{
			DF_SAFE_DELETE(m_pAsyncSendThread);
		}

	}
	// -----------------------------------------------------------------------
	NetWork::NetWork(unsigned int uMaxConnect, unsigned short uThread) :
		m_sIP(""),
		m_pNetWorkThreads(),
		m_IOS(),
		m_NetConnectMap(),
		m_NetWhoConnectMap(),
		m_FreeAllocIDSet(),
		m_ConnectMutex(),
		m_uMaxConnect(uMaxConnect),
		m_uMaxThread(uThread),
		m_uAsyncSendWho(0),
		m_uPort(Config::MAX_UINT16),
		m_pAcceptor(NULL),
		m_pAsyncSendThread(NULL),
		m_pCurConnect(NULL),
		m_pCurMessage(NULL),
		m_bIsRun(false),
		m_bIsStop(true),
		m_bLastConnectClose(false),
		m_bIsBytesMsg(false)
	{
		for (unsigned short uIdx = 0; uIdx < uThread; ++uIdx)
		{
			this->m_pNetWorkThreads.push_back(NULL);
		}
	}
	// -----------------------------------------------------------------------
	bool NetWork::listenPort(unsigned int uPort)
	{
		if (NULL == m_pAcceptor)
		{
			try
			{
				boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::from_string("127.0.0.1"), uPort);
				
				m_uPort = uPort;
				
				// 获取本机ip地址
				boost::asio::ip::tcp::resolver resolver(m_IOS);
				boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
				boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
				boost::asio::ip::tcp::resolver::iterator end;
				while (iter != end)
				{
					ep = *iter++;
					m_sIP = ep.address().to_string();
					if (m_sIP.find_first_of('.') != std::string::npos)
						break;
				}
				ep = boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string(m_sIP), uPort);
				m_pAcceptor = new BoostAcceptor(m_IOS, ep, false);

			}
			catch (std::exception& e)
			{
				DF_OUT << e.what() << DF_END;
				DF_EXC << "can't listen the port(" << uPort << ")." << DF_END;
				return false;
			}
			asyncAccept();
			return true;
		}
		else
		{
			DF_OUT << "can not double listen." << DF_END;
			return false;
		}
	}
	// -----------------------------------------------------------------------
	void NetWork::start(void)
	{
		for (size_t uIdx = 0; uIdx < m_pNetWorkThreads.size(); ++uIdx)
		{
			this->m_pNetWorkThreads.at(uIdx) = new BoostThread(boost::bind(&DF::NetWork::boostAsioRun, this));
		}
		this->m_bIsRun = true;
	}
	// -----------------------------------------------------------------------
	void NetWork::stop(void)
	{
		m_bIsRun = false;
		m_bIsStop = true;
		m_uAsyncSendWho = false;

		m_ConnectMutex.lock();

		m_NetWhoConnectMap.clear();
		NetConnectMapIt it = m_NetConnectMap.begin();
		while (it != m_NetConnectMap.end())
		{
			it->second->shutdown(NetConnect::enNetConnect_LocalClose);
			++it;
		}
		m_NetConnectMap.clear();
		m_ConnectMutex.unlock();

		m_IOS.stop();
		for (size_t uIdx = 0; uIdx < m_pNetWorkThreads.size(); ++uIdx)
		{
			m_pNetWorkThreads.at(uIdx)->timed_join(boost::posix_time::seconds(5));
		}
		if (NULL != m_pAsyncSendThread)
		{
			m_pAsyncSendThread->timed_join(boost::posix_time::seconds(5));
		}
	}
	// -----------------------------------------------------------------------
	bool NetWork::connect(const char* ip, unsigned int uPort, unsigned short uWho)
	{
		if (m_NetWhoConnectMap.find(uWho) != m_NetWhoConnectMap.end())
			return false;

		if (m_NetConnectMap.size() + 1 >= m_uMaxConnect)
			return false;

		BoostResolver resolver(m_IOS);
		BoostResolver::query q(ip, boost::lexical_cast<std::string>(uPort));
		BoostResolver::iterator endpoint_iterator = resolver.resolve(q);
		NetConnect::ConnectSharedPtr pNetConnect = NetConnect::ConnectSharedPtr(new NetConnect(this));
		try
		{
			boost::asio::connect(pNetConnect->getSocket(), endpoint_iterator);
		}
		catch (std::exception& e)
		{
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
			e.what();
			DF_EXC << "can't connect the remote address. ip(" << ip << ") port(" << uPort << ")." << DF_END;
#else
			DF_EXC<<"can't connect the remote address. ip("<<ip<<") port("<<uPort<<") what("<<e.what()<<")."<<DF_END;
#endif
			pNetConnect->shutdown(NetConnect::enNetConnect_ConnectFull);
			return false;
		}

		m_ConnectMutex.lock();
		unsigned int uId = allocSessionID();
		pNetConnect->setWho(uWho);
		pNetConnect->setSessionID(uId);
		m_NetConnectMap[uId] = pNetConnect;
		m_NetWhoConnectMap[uWho] = pNetConnect;
		pNetConnect->start();
		m_ConnectMutex.unlock();
		return true;
	}
	// -----------------------------------------------------------------------
	void NetWork::asyncAccept(void)
	{
		if (NULL == m_pAcceptor)
		{
			return;
		}

		NetConnect::ConnectSharedPtr pNetConnect = NetConnect::ConnectSharedPtr(new NetConnect(this));
		m_pAcceptor->async_accept(pNetConnect->getSocket(),
			boost::bind(&NetWork::boostAsyncAccept, this, pNetConnect, boost::asio::placeholders::error));
	}
	// -----------------------------------------------------------------------
	void NetWork::boostAsioRun(void)
	{
		m_IOS.run();
		DF_OUT << "BoostAsio is Leave." << DF_END;
	}
	// -----------------------------------------------------------------------
	void NetWork::boostAsyncAccept(NetConnect::ConnectSharedPtr& pNetConnect, const boost::system::error_code& error)
	{
		if (error)
		{
			pNetConnect->shutdown(NetConnect::enNetConnect_ConnectFull);
			asyncAccept();
			return;
		}

		if (m_NetConnectMap.size() >= m_uMaxConnect)
		{
			pNetConnect->shutdown(NetConnect::enNetConnect_ConnectFull);
			DF_EXC << "too much network connect(" << m_NetConnectMap.size() << ")." << DF_END;
		}
		else
		{
			m_ConnectMutex.lock();
			unsigned int uId = allocSessionID();
			m_NetConnectMap[uId] = pNetConnect;
			pNetConnect->setSessionID(uId);
			pNetConnect->start();
			m_ConnectMutex.unlock();
		}
		asyncAccept();
	}
	// -----------------------------------------------------------------------
	unsigned int NetWork::allocSessionID(void)
	{
		if (m_FreeAllocIDSet.empty())
		{
			return static_cast<unsigned int>(m_NetConnectMap.size());
		}
		FreeAllocIDSetIt it = m_FreeAllocIDSet.begin();
		unsigned int uID = *it;
		m_FreeAllocIDSet.erase(it);
		return uID;
	}
	// -----------------------------------------------------------------------
	bool NetWork::clearConnect(unsigned int uSessionID)
	{
		bool bRet = false;
		m_ConnectMutex.lock();

		NetConnectMapIt it = m_NetConnectMap.find(uSessionID);
		if (it != m_NetConnectMap.end())
		{
			NetConnectMapIt whoIt = m_NetWhoConnectMap.find(it->second->getWho());
			if (whoIt != m_NetWhoConnectMap.end())
				m_NetWhoConnectMap.erase(whoIt);

			m_FreeAllocIDSet.insert(uSessionID);
			it->second->shutdown(NetConnect::enNetConnect_ConnectFull);
			m_NetConnectMap.erase(it);
			bRet = true;
		}
		m_ConnectMutex.unlock();
		return bRet;
	}
	// -----------------------------------------------------------------------
	bool NetWork::disConnect(unsigned int uSessionID)
	{
		NetConnectMapIt it = m_NetConnectMap.find(uSessionID);
		if (it != m_NetConnectMap.end())
		{
			it->second->shutdown(NetConnect::enNetConnect_LocalClose);
			return true;
		}
		return false;
	}
	// -----------------------------------------------------------------------
	bool NetWork::hasConnect(unsigned int uSessionID)const
	{
		NetConnectMapCIt it = m_NetConnectMap.find(uSessionID);
		if (it != m_NetConnectMap.end())
		{
			return (false == it->second->isShutdown());
		}
		return false;
	}
	// -----------------------------------------------------------------------
	bool NetWork::isSendOver(unsigned int uSessionID)const
	{
		NetConnectMapCIt it = m_NetConnectMap.find(uSessionID);
		if (it != m_NetConnectMap.end())
			return it->second->isSendOver();

		return false;
	}
	// -----------------------------------------------------------------------
	bool NetWork::getCurIsClose(void)const
	{
		return m_bLastConnectClose;
	}
	// -----------------------------------------------------------------------
	NetConnect* NetWork::getCurNetConnect(void)const
	{
		return m_pCurConnect;
	}
	// -----------------------------------------------------------------------
	bool NetWork::moveNextMsg(void)
	{
		if (m_bLastConnectClose)
			clearConnect(m_pCurConnect->getSessionID());

		m_pCurMessage = NULL;
		m_bLastConnectClose = false;

		m_ConnectMutex.lock();
		NetConnectMapIt it = m_NetConnectMap.begin();
		while (it != m_NetConnectMap.end())
		{
			m_pCurConnect = it->second.get();
			if (m_pCurConnect->isShutdown())
			{
				this->m_bLastConnectClose = true;
				break;
			}
				
			if (m_pCurConnect->readMessage(&m_pCurMessage))
				break;
			++it;
		}
		m_ConnectMutex.unlock();
		return m_bLastConnectClose || NULL != m_pCurMessage;
	}
	// -----------------------------------------------------------------------
	BoostIOService& NetWork::getISO(void)
	{
		return m_IOS;
	}
	// -----------------------------------------------------------------------
	bool NetWork::getIsRun(void)const
	{
		return m_bIsRun;
	}
	// -----------------------------------------------------------------------
	bool NetWork::getIsStop(void)const
	{
		return m_bIsStop;
	}
	// -----------------------------------------------------------------------
	MessageBase* NetWork::getMessage(void)const
	{
		return m_pCurMessage;
	}
	// -----------------------------------------------------------------------
	NetConnect* NetWork::findNetConnect(unsigned int uSessionID)
	{
		NetConnectMapIt it = m_NetConnectMap.find(uSessionID);
		if (it != m_NetConnectMap.end())
		{
			return it->second.get();
		}
		return NULL;
	}
	// -----------------------------------------------------------------------
	NetConnect* NetWork::findNetConnectByWho(unsigned short uWho)
	{
		NetConnectMapIt it = m_NetWhoConnectMap.find(uWho);
		if (it != m_NetWhoConnectMap.end())
			return it->second.get();
		return NULL;
	}
	// -----------------------------------------------------------------------
	NetWork::NetConnectMap& NetWork::getNetConnectMap(void)
	{
		return m_NetConnectMap;
	}
	// -----------------------------------------------------------------------
	unsigned short NetWork::getPort(void)const
	{
		return m_uPort;
	}
	// -----------------------------------------------------------------------
	const char* NetWork::getIP(void)const
	{
		return m_sIP.c_str();
	}
	// -----------------------------------------------------------------------
	void NetWork::setIsBytesMsg(bool isBytesMsg)
	{
		m_bIsBytesMsg = isBytesMsg;
	}
	// -----------------------------------------------------------------------
	bool NetWork::getIsBytesMsg(void)const
	{
		return m_bIsBytesMsg;
	}

}