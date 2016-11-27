#ifndef TIME_TICK_H
#define TIME_TICK_H

#include "base/baseTime.h"
#include "base/baseThread.h"

class SceneTimeTick : public Thread,public SingletonBase<SceneTimeTick>
{
	private:
		friend class SingletonBase<SceneTimeTick>;
		SceneTimeTick();
		~SceneTimeTick();
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
		void sceneFinal();

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
		QWORD  m_frameTime;
};

#endif

