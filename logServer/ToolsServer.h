/************************************************************************
* @File			:	ToolsServer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __ToolsServer_H__
#define __ToolsServer_H__
#include "DFPrerequisite.h"
#include "DFBaseServer.h"



// -----------------------------------------------------------------------
// @brief �߼�������
class ToolsServer : public DF::BaseServer
{
public:
	// -----------------------------------------------------------------------
	// @brief ��������
	virtual ~ToolsServer(void);
	// -----------------------------------------------------------------------
	// @brief ��ȡ����
	static ToolsServer* instancePtr(void);
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
	ToolsServer(void);

private:
	static ToolsServer*				m_pInstance;

};

#endif
