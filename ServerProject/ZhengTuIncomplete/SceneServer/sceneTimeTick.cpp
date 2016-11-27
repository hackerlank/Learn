#include "sceneTimeTick.h"
#include "SceneServer.h"
#include <time.h>
#include "recordClient.h"
#include "sessionClient.h"
#include "sceneTaskManager.h"

Time SceneTimeTick::s_currentTime;

SceneTimeTick::SceneTimeTick() : Thread("TimeTick"),m_oneSec(1*1000L),m_fiveSec(5*1000L),m_tenSec(10*1000L),m_oneMin(60*1000L),m_fiveMin(5*60*1000L),m_oneQuarter(15*60*1000L),m_oneClocker(1*3600,1*3600),m_zeroClocker(24*3600,24*3600),m_fourClocker(4*3600,24*3600)
{
	m_maxFrameTime = 0;
	m_frameTime = 0;
}

SceneTimeTick::~SceneTimeTick()
{
}

void SceneTimeTick::run()
{
	DWORD step = 0;
	int maxFrameNum = 100;
	while( !isFinal() )
	{
		setRuning();
		long begin = 0,end = 0;
		struct timespec tv_begin;
		clock_gettime(CLOCK_REALTIME,&tv_begin);
		begin = tv_begin.tv_sec*1000L + tv_begin.tv_nsec/1000000L;
		
		SceneServer::getInstance().doCmd();
		SceneTaskManager::getInstance().doCmd();
		recordClient->doCmd();
		sessionClient->doCmd();
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
		SceneServer::getInstance().checkFinal();
		struct timespec tv_end;
		clock_gettime(CLOCK_REALTIME,&tv_end);
		end = tv_end.tv_sec * 1000L + tv_end.tv_nsec / 1000000L;

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
		if(m_frameTime > 300)
		{
			Global::logger->debug("服务器运行桢数过慢 当前桢:%lu ms",m_frameTime);
		}
		if(m_frameTime < 10)
		{
			Thread::msleep(10 - m_frameTime);
		}
	}
	sceneFinal();
}

void SceneTimeTick::oneSec()
{
}

void SceneTimeTick::fiveSec()
{
}

void SceneTimeTick::tenSec()
{
}

void SceneTimeTick::oneMin()
{
}

void SceneTimeTick::fiveMin()
{
}

void SceneTimeTick::oneQuarter()
{
}

void SceneTimeTick::oneHour()
{
}

void SceneTimeTick::zeroHour()
{
}

void SceneTimeTick::fourHour()
{
}

void SceneTimeTick::sceneFinal()
{
}

inline bool SceneTimeTick::isHighDelay()
{
	return m_maxFrameTime > 200;
}



