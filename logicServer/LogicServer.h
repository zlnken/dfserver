/************************************************************************
* @File			:	LogicServer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __LogicServer_H__
#define __LogicServer_H__
#include "DFPrerequisite.h"
#include "DFBaseServer.h"



// -----------------------------------------------------------------------
// @brief �߼�������
class LogicServer : public DF::BaseServer
{
public:
	// -----------------------------------------------------------------------
	// @brief ��������
	virtual ~LogicServer(void);
	// -----------------------------------------------------------------------
	// @brief ��ȡ����
	static LogicServer* instancePtr(void);
	// -----------------------------------------------------------------------
	// @brief �Ƴ�����
	static void unintance(void);
	// -----------------------------------------------------------------------
	// @brief ��ʼ��
	void init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread);
	// -----------------------------------------------------------------------
	// @brief ����
	void loop(void);
	// -----------------------------------------------------------------------
	// @brief ����
	void finish(void);

private:
	// -----------------------------------------------------------------------
	// @brief ���캯��
	LogicServer(void);

private:
	static LogicServer*				m_pInstance;

};

#endif
