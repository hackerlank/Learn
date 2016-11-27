#ifndef SESSION_TIME_TICK_H 
#define SESSION_TIME_TICK_H 

#include "base/baseTime.h"
#include "base/baseThread.h"

class SessionTimeTick : public Thread,public SingletonBase<SessionTimeTick>
{
	private:
		friend class SingletonBase<SessionTimeTick>;
		SessionTimeTick();
		~SessionTimeTick();
	public:
		static Time s_currentTime;
		void run();
		static void zeroHour();
		static void fourHour();
		bool isHighDelay();
	private:
		void oneSec();
		void fiveSec();
		void tenSec();
		void oneMin();
		void fiveMin();
		void oneQuarter();
		void oneHour();
		void zeroClocker();
		void sessionFinal();

		Timer m_oneSec;
		Timer m_fiveSec;
		Timer m_tenSec;

		Timer m_oneMin;
		Timer m_fiveMin;
		Timer m_oneQuarter;

		Clocker  m_oneClocker;
		Clocker  m_zeroClocker;
		Clocker  m_fourClocker;

		QWORD m_maxFrameTime;
		QWORD m_frameTime;
};

#endif

