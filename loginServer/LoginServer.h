/************************************************************************
* @File			:	LoginServer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __LoginServer_H__
#define __LoginServer_H__
#include "DFPrerequisite.h"
#include "DFBaseServer.h"

// -----------------------------------------------------------------------
// @brief �߼�������
class LoginServer : public DF::BaseServer
{
public:
	// -----------------------------------------------------------------------
	// @brief ��������
	virtual ~LoginServer(void);
	// -----------------------------------------------------------------------
	// @brief ��ȡ����
	static LoginServer* instancePtr(void);
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
	LoginServer(void);

private:
	static LoginServer*				m_pInstance;

};

#endif
