/************************************************************************
* @File			:	DFDateTime.h
* @Author		:	Sword
* @DateTime		:	2013.12.9 
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFDateTime_H__
#define __DFDateTime_H__

#include "DFPrerequisite.h"

namespace DF{
	//------------------------------------------------------------------------
	// @brief 时间
	class DFExport DateTime
	{

	public:
		//------------------------------------------------------------------------
		// @brief 构造函数
		DateTime(void);
		//------------------------------------------------------------------------
		// @brief 获取单例
		static DateTime* instancePtr(void);
		//------------------------------------------------------------------------
		// @brief 移除单例
		static void uninstance(void);
		//------------------------------------------------------------------------
		// @brief 刷新
		void refresh(void);
		//------------------------------------------------------------------------
		// @brief 获取年
		unsigned int year(void)const{ return m_uYear; }
		//------------------------------------------------------------------------
		// @brief 获取月
		unsigned int month(void)const{ return m_uMonth; }
		//------------------------------------------------------------------------
		// @brief 获取天
		unsigned int day(void)const{ return m_uDay; }
		//------------------------------------------------------------------------
		// @brief 获取小时
		unsigned int hour(void)const{ return m_uHour; }
		//------------------------------------------------------------------------
		// @brief 获取分钟
		unsigned int minute(void)const{ return m_uMinute; }
		//------------------------------------------------------------------------
		// @brief 获取秒
		unsigned int second(void)const{ return m_uSecond; }
		//------------------------------------------------------------------------
		// @brief 获取开机到现在(毫秒级别)
		unsigned int milliseSecond(void)const{ return m_uCPUCLock % 1000; }
		//------------------------------------------------------------------------
		// @brief 获取开机到现在(毫秒级别)
		uint64 milliseSecnods(void)const{ return m_uCPUCLock; }
		//------------------------------------------------------------------------
		// @brief 获取1970-现在总共有几天
		unsigned int days(void)const{ return (m_uUnixTime + m_uTimeZoneSecond) / 86400; }
		//------------------------------------------------------------------------
		// @brief 获取1970-现在总共有几个星期
		unsigned int weeks(void)const{ return (days() + 3) / 7; }
		//------------------------------------------------------------------------
		// @brief 获取1970-现在总共有几个月
		unsigned int months(void)const{ return (m_uYear - 1970) * 12 + m_uMonth - 1; }
		//------------------------------------------------------------------------
		// @brief 获取一年中的第几天
		unsigned int yearDay(void)const{ return m_uYearDay; }
		//------------------------------------------------------------------------
		// @brief 获取一年中的第几个月
		unsigned int monthDay(void)const{ return m_uMonthDay; }
		//------------------------------------------------------------------------
		// @brief 获取一年中的第几个星期
		unsigned int weekDay(void)const{ return m_uWeekDay; }
		//------------------------------------------------------------------------
		// @brief 1970年到现在用过多少秒
		unsigned int seconds(void)const{ return m_uUnixTime; }
		//------------------------------------------------------------------------
		// @brief 获取系统时间
		unsigned int getUnixTime(void)const{ return m_uUnixTime; }

		unsigned int timeZoneSeconds() { return m_uTimeZoneSecond; }
		//------------------------------------------------------------------------
		// @brief 设置系统时间
		void setUnixTime(unsigned int uUnixTime);
		//------------------------------------------------------------------------
		// @brief 加速时间
		void setTimeSpeed(unsigned int uTimeSpeed);

	private:
		//------------------------------------------------------------------------
		// @brief 组合时间
		void casheTime(void);
		void casheClock(void);


	private:
		static DateTime*	m_pInstance;

		uint64				m_uCPUCLock;
		uint64				m_uCumulation;

		unsigned int		m_uUnixTime;
		unsigned int		m_uTimeSpeed;
		unsigned int		m_uTimeZoneSecond;


		unsigned int		m_uYear;
		unsigned int		m_uMonth;
		unsigned int		m_uDay;
		unsigned int		m_uHour;
		unsigned int		m_uMinute;
		unsigned int		m_uSecond;

		unsigned int		m_uWeek;

		unsigned int		m_uYearDay;
		unsigned int		m_uMonthDay;
		unsigned int		m_uWeekDay;
		
		bool				m_bIsCumulatino;

	};
}

#endif
