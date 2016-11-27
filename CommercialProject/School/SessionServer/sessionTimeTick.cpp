#include "sessionTimeTick.h"
#include "SessionServer.h"
#include <time.h>
#include "recordClient.h"
#include "sessionTaskManager.h"

Time SessionTimeTick::s_currentTime;

SessionTimeTick::SessionTimeTick() : Thread("SessionTimeTick"),m_oneSec(1*1000L),m_fiveSec(5*1000L),m_tenSec(10*1000L),m_oneMin(60*1000L),m_fiveMin(5*60*1000L),m_oneQuarter(15*60*1000L),m_oneClocker(1*3600,1*3600),m_zeroClocker(24*3600,24*3600),m_fourClocker(4*3600,24*3600)
{
	m_maxFrameTime = 0;
	m_frameTime = 0;
}

SessionTimeTick::~SessionTimeTick()
{
}

void SessionTimeTick::run()
{
	DWORD step = 0;
	SDWORD maxFrameNum = 100;
	while(!isFinal())
	{
		setRuning();
		s_currentTime.now();
		struct timespec tv_begin;
		clock_gettime( CLOCK_REALTIME,&tv_begin );
		QWORD begin = tv_begin.tv_sec*1000L + tv_begin.tv_nsec/1000000L;
		
		recordClient->doCmd();
		SessionServer::getInstance().doCmd();
		SessionTaskManager::getInstance().doCmd();

		if(m_oneSec(s_currentTime))
		{
			oneSec();
			if(m_fiveSec(s_currentTime))
			{
				fiveSec();
			}
			else if(m_tenSec(s_currentTime))
			{
				tenSec();
			}
			else if(m_oneMin(s_currentTime))
			{
				oneMin();
			}
			else if(m_fiveMin(s_currentTime))
			{
				fiveMin();
			}
			else if(m_oneQuarter(s_currentTime))
			{
				oneQuarter();
			}
			else if(m_oneClocker(s_currentTime))
			{
				oneHour();
			}
			else if(m_zeroClocker(s_currentTime))
			{
				zeroHour();
			}
			else if(m_fourClocker(s_currentTime))
			{
				fourHour();
			}
		}
		++step;
		struct timespec tv_end;
		clock_gettime(CLOCK_REALTIME,&tv_end);
		QWORD end = tv_end.tv_sec*1000L + tv_end.tv_nsec /1000000L;
		m_frameTime = end - begin;
		if(maxFrameNum)
		{
			maxFrameNum -= 1;
			if(m_frameTime > m_maxFrameTime)
			{
				m_maxFrameTime = m_frameTime;
			}
		}
		else
		{
			maxFrameNum = 100;
			m_maxFrameTime = 0;
		}
		LogInfoCheckConditionOnly(m_frameTime <= 300,"会话服务器运行桢数过慢%lums",m_frameTime );
		if(m_frameTime < 10)
		{
			Thread::msleep(10 - m_frameTime);
		}
	}
	sessionFinal();
}

void SessionTimeTick::oneSec()
{
}

void SessionTimeTick::fiveSec()
{
}

void SessionTimeTick::tenSec()
{
}

void SessionTimeTick::oneMin()
{
}

void SessionTimeTick::fiveMin()
{
}

void SessionTimeTick::oneQuarter()
{
}

void SessionTimeTick::oneHour()
{
}

void SessionTimeTick::zeroHour()
{
}

void SessionTimeTick::fourHour()
{
}

void SessionTimeTick::sessionFinal()
{
}

bool SessionTimeTick::isHighDelay()
{
	return m_maxFrameTime > 200;
}




