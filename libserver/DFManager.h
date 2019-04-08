/************************************************************************
* @File			:	DFManager.h
* @Author		:	Sword
* @DateTime		:	2013.12.9 
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFManager_H__
#define __DFManager_H__

#include "DFPrerequisite.h"

namespace DF{
	// -----------------------------------------------------------------------
	// @brief 管理模板可以省去很多代码用来偷懒
	template<typename KeyType, typename ValueType>
	class DFExport Manager
	{
	public:

		typedef typename boost::unordered_map<KeyType, ValueType*> TypeMap;	
		typedef typename TypeMap::iterator TypeMapIt;
		typedef typename TypeMap::const_iterator TypeMapCIt;

	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~Manager(void)
		{
			
		}

		// -----------------------------------------------------------------------
		// @brief 获取单例
		static Manager<KeyType, ValueType>* instancePtr(void)
		{
			static Manager<KeyType, ValueType> m_Instance;
			return &m_Instance;
		}

		// -----------------------------------------------------------------------
		// @brief 获取单例
		static Manager<KeyType, ValueType>& instance(void)
		{
			static Manager<KeyType, ValueType> m_Instance;
			return m_Instance;
		}

		// -----------------------------------------------------------------------
		// @brief 移除单例
		static void uninstance(void)
		{

		}
		// -----------------------------------------------------------------------
		// @brief 清空容器
		void clear(bool bDestory = true)
		{
			if(!bDestory)
			{
				m_TypeMap.clear();
				return;
			}

			TypeMapIt it = m_TypeMap.begin();
			while(it != m_TypeMap.end())
			{
				DF_SAFE_DELETE(it->second);
				++it;
			}
			m_TypeMap.clear();
		}

		// -----------------------------------------------------------------------
		// @brief 往后添加一个模板实例
		// @param[key] 钥匙
		// @param[pObject] 实例
		void push(const KeyType& key, ValueType* pObject)
		{
			if(pObject)
			{
				m_TypeMap[key] = pObject;
			}
		}
		// -----------------------------------------------------------------------
		// @brief 查找后,添加一个模板实例
		// @param[key] 钥匙
		// @param[pObject] 实例
		bool append(const KeyType& key, ValueType* pObject)
		{
			if(0 == pObject)
			{
				return false;
			}

			ValueType* pFind = find(key);
			if(pFind)
			{
				return false;
			}

			push(key, pObject);
			return true;
		}
		// -----------------------------------------------------------------------
		// @brief 查找
		// @param[key] 钥匙
		ValueType* find(const KeyType& key)const
		{
			TypeMapCIt it = m_TypeMap.find(key);
			if(it != m_TypeMap.end())
			{
				return it->second;
			}
			return 0;
		}
		// -----------------------------------------------------------------------
		// @brief 移除
		// @param[key] 钥匙
		bool remove(const KeyType& key)
		{
			TypeMapIt it = m_TypeMap.find(key);
			if(it != m_TypeMap.end())
			{
				DF_SAFE_DELETE(it->second);
				m_TypeMap.erase(it);
				return true;
			}
			return false;
		}
		// -----------------------------------------------------------------------
		// @brief 移除
		// @param[pValue] 实例
		bool remove(const ValueType* pValue)
		{
			TypeMapIt it = m_TypeMap.begin();
			while (it != m_TypeMap.end())
			{
				if (it->second == pValue)
				{
					DF_SAFE_DELETE(it->second);
					m_TypeMap.erase(it);
					return true;
				}
				++it;
			}
			return false;
		}
		// -----------------------------------------------------------------------
		// @brief 重置
		// @param[key] 钥匙
		// @param[pValue] 实例
		bool reset(const KeyType& key, ValueType* pValue)
		{
			TypeMapIt it = m_TypeMap.find(key);
			if (it == m_TypeMap.end())
				return false;
			m_TypeMap.erase(it);
			m_TypeMap[key] = pValue;
			return true;
		}
		// -----------------------------------------------------------------------
		void begin(void)
		{
			m_pIt = m_TypeMap.begin();
		}

		// -----------------------------------------------------------------------
		ValueType* get(void)const
		{
			if( m_pIt != m_TypeMap.end() )
			{
				return m_pIt->second;
			}
			return 0;
		}
		// -----------------------------------------------------------------------
		void next(void)
		{
			++m_pIt;
		}

		// -----------------------------------------------------------------------
		bool hasNext(void)const
		{
			return (m_pIt != m_TypeMap.end());
		}

	protected:
		// -----------------------------------------------------------------------
		Manager(void)
		{
			m_TypeMap.clear();
			m_pIt = m_TypeMap.begin();
		}

	protected:
		TypeMap					m_TypeMap;
		TypeMapIt				m_pIt;
	};


#define DF_MANAGER_FIND(varKey, varType) \
	varType* varType::sfind(const varKey& id){ return Manager<varType>::instancePtr()->find(id);}

#define DF_MANAGER_REMOVE(varKey, varType) \
	bool varType::sfind(const varKey& id){ return Manager<varType>::instancePtr()->remove(id);}


}
#endif