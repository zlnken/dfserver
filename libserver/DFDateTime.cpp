/************************************************************************
* @File			:	DFDateTime.h
* @Author		:	Sword
* @DateTime		:	2014.6.3 
* @Version		:	v0.01
* @Description	:
*
*
*
*
************************************************************************/
#include "DFDateTime.h"
#include "DFPrerequisite.h"
#include <time.h>
namespace DF{
	// -----------------------------------------------------------------------
	DateTime* DateTime::m_pInstance = NULL;
	// -----------------------------------------------------------------------
	DateTime::DateTime(void):
	m_uCPUCLock(0),
	m_uCumulation(0),
	m_uUnixTime(0),
	m_uTimeSpeed(1000),
	m_uTimeZoneSecond(0),
	m_uYear(0),
	m_uMonth(0),
	m_uDay(0),
	m_uHour(0),
	m_uMinute(0),
	m_uSecond(0),
	m_uWeek(0),
	m_uYearDay(0),
	m_uMonthDay(0),
	m_uWeekDay(0),
	m_bIsCumulatino(true)
	{
		m_uUnixTime = 0;
		casheTime();
		m_uTimeZoneSecond = m_uHour * 3600 + m_uMinute * 60 + m_uSecond;
		m_uUnixTime = static_cast<unsigned int>(time(0));
		casheClock();
		casheTime();
	}
	// -----------------------------------------------------------------------
	DateTime* DateTime::instancePtr(void)
	{
		if(0 == m_pInstance)
		{
			m_pInstance = new DateTime;
		}
		return m_pInstance;
	}

	// -----------------------------------------------------------------------
	void DateTime::uninstance(void)
	{
		DF_SAFE_DELETE(m_pInstance);
	}
	// -----------------------------------------------------------------------
	void DateTime::casheClock(void)
	{

#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
		m_uCPUCLock = static_cast<uint64>(clock());
#elif DF_TARGET_PLATFORM == DF_PLATFORM_APPLE
		clock_serv_t cclock;
		mach_timespec_t mts;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
		clock_get_time(cclock, &mts);
		mach_port_deallocate(mach_task_self(), cclock);
		m_uCPUCLock = mts.tv_sec * 1000 + mts.tv_nsec / 1000000;
#else
		struct timespec ts; 
		clock_gettime(CLOCK_MONOTONIC, &ts);
		m_uCPUCLock = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#endif
	}
	// -----------------------------------------------------------------------
	void DateTime::casheTime(void)
	{
		time_t _tt = static_cast<time_t>(m_uUnixTime);
		tm* _tm = localtime(&_tt);
		m_uYear = static_cast<unsigned int>(_tm->tm_year + 1900);
		m_uMonth = static_cast<unsigned int>(_tm->tm_mon + 1);
		m_uDay = static_cast<unsigned int>(_tm->tm_mday + 1);

		m_uMonthDay = static_cast<unsigned int>(_tm->tm_mday);

		m_uHour = static_cast<unsigned int>(_tm->tm_hour);
		m_uMinute = static_cast<unsigned int>(_tm->tm_min);
		m_uSecond = static_cast<unsigned int>(_tm->tm_sec);
		m_uWeekDay = static_cast<unsigned int>(_tm->tm_wday);
		m_uYearDay = static_cast<unsigned int>(_tm->tm_yday);
		m_uWeek = m_uYearDay / 7;
	}
	// -----------------------------------------------------------------------
	void DateTime::refresh(void)
	{
		uint64 uTmpClock = m_uCPUCLock;
		casheClock();
		if (m_uCPUCLock < uTmpClock)
		{
			//std::cout << "Time Cycle." << std::endl;
			return;
		}

		if (m_bIsCumulatino)
		{
			m_uCumulation += (m_uCPUCLock - uTmpClock);
			if (m_uCumulation > m_uTimeSpeed)
			{
				m_uUnixTime += 1;
				m_uCumulation -= m_uTimeSpeed;
				this->casheTime();
			}
		}
	}
	// -----------------------------------------------------------------------
	void DateTime::setUnixTime(unsigned int uUnixTime)
	{
		if (uUnixTime)
		{
			// 时间必须单调递增
			DF_ASSERT(uUnixTime >= m_uUnixTime);
			m_uUnixTime = uUnixTime;
			refresh();
			casheTime();
			m_bIsCumulatino = true;
		}
		else
		{
			m_bIsCumulatino = false;
		}
	}
	// -----------------------------------------------------------------------
	void DateTime::setTimeSpeed(unsigned int uTimeSpeed)
	{
		if (uTimeSpeed)
		{
			m_uTimeSpeed = uTimeSpeed;
		}
	}
}