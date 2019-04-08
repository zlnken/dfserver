/************************************************************************
* @File			:	DFProcess.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFProcess_H__
#define __DFProcess_H__
#include "DFPrerequisite.h"


namespace DF{

	struct DFExport ConnectParam
	{
		ConnectParam()
		{
			uSendBlockSize = Config::SEND_BLOCK_SIZE;
			uSendBlockNum = Config::SEND_BLOCK_NUM;
			uRecvBlockSize = Config::RECV_BLOCK_SIZE;
			uRecvBlockNum = Config::RECV_BLOCK_SIZE;
		}
		unsigned short		uSendBlockSize;
		unsigned short		uSendBlockNum;
		unsigned short		uRecvBlockSize;
		unsigned short		uRecvBlockNum;
	};

	// -----------------------------------------------------------------------
	// @brief 进程
	class DFExport Process 
	{
	public:		
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~Process(void);
		// -----------------------------------------------------------------------
		// @brief 析构函数
		Process(void);
		// -----------------------------------------------------------------------
		// @brief 获取单例
		static Process* instancePtr(void);
		// -----------------------------------------------------------------------
		// @brief 释放单例
		static void uninstance(void);
		// -----------------------------------------------------------------------
		// @brief 初始化
		void init(int argc, char *argv[]);
		// -----------------------------------------------------------------------
		// @brief 构建进程KEY
		std::string	makeProcessKey(const std::string& sType, unsigned short uID);
		// -----------------------------------------------------------------------
		// @brief 获取进程类型
		const std::string& getProcessType(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取进程ID
		unsigned short getProcessID(void)const;
		// -----------------------------------------------------------------------
		// @brief TGW换行符数量
		unsigned short getLFCount(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取发送块大小
		unsigned short getSendBlockSize(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取发送块数量
		unsigned short getSendBlockNum(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取收取块大小
		unsigned short getRecvBlockSize(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取收取块数量
		unsigned short getRecvBlockNum(void)const;

	private:
		// -----------------------------------------------------------------------
		//系统检测
		void sysCheck();													

	private:
		static Process*				m_pInstance;
		std::string					m_sProcessType;													//进程类型
		unsigned short				m_uProcessID;													//进程ID
		unsigned short				m_uTGW_LF_Count;												//TGW换行符数量
		ConnectParam				m_DefualConnectParam;											//默认连接参数
	
	};
}

#endif