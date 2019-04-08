/************************************************************************
* @File			:	DFLuaTable.h
* @Author		:	Sword
* @DateTime		:	2015.3.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFLuaTable_H__
#define __DFLuaTable_H__

#include "DFPrerequisite.h"
#include "DFLuaStack.h"

namespace DF{

	class DFExport LuaTable : public LuaStack
	{
	public:
		LuaTable(int iTop);
		LuaTable(void);

		void setTableTop(int top);

		void setValue(int index, bool val);
		void setValue(int index, int val);
		void setValue(int index, unsigned int val);
		void setValue(int index, float val);
		void setValue(int index, const std::string& val);
		void setValue(int index, void* pObj, std::string& type);

		void setValue(const std::string& key, bool val);
		void setValue(const std::string& key, int val);
		void setValue(const std::string& key, unsigned int val);
		void setValue(const std::string& key, float val);
		void setValue(const std::string& key, const std::string& val);
		void setValue(const std::string& key, void* pObj, const std::string& type);


		bool getBoolean(int idx)const;
		int getInt(int idx)const;
		unsigned int getUint(int idx)const;
		float getFloat(int idx)const;
		std::string getString(int idx)const;
		LuaFunction* getFunction(int idx)const;
		LuaTable* getLuaTable(int idx)const;
		void* getObject(int idx)const;

		bool getBoolean(const std::string& key)const;
		int getInt(const std::string& key)const;
		unsigned int getUint(const std::string& key)const;
		float getFloat(const std::string& key)const;
		std::string getString(const std::string& key)const;
		LuaFunction* getFunction(const std::string& key)const;
		LuaTable* getLuaTable(const std::string& key)const;
		void* getObject(const std::string& key)const;

		void begin(void);
		bool hasNext(void)const;
		void next(void);

		int getNextIntKey(void)const;
		std::string getNextStringKey(void)const;
		bool getNextBoolean(void)const;
		int getNextInt(void)const;
		unsigned int getNextUint(void)const;
		float getNextFloat(void)const;
		std::string getNextString(void)const;

		LuaFunction* getNextFunction(void)const;
		LuaTable* getNextLuaTable(void)const;
		void* getNextObject(void)const;
		
		bool remove(int key);
		bool remove(const std::string& key);

		int getTop(void)const;
		int getSize(void)const;

		//void dumpString(std::string& dumps, const std::string& d);

	protected:
		int				m_iTableTop;

	};
}

#endif