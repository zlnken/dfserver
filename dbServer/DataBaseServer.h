/************************************************************************
* @File			:	DataBaseServer.h
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
class DataBaseServer : public DF::BaseServer
{
public:
	// -----------------------------------------------------------------------
	// @brief ��������
	virtual ~DataBaseServer(void);
	// -----------------------------------------------------------------------
	// @brief ��ȡ����
	static DataBaseServer* instancePtr(void);
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
	DataBaseServer(void);

private:
	static DataBaseServer*				m_pInstance;

};

#endif
