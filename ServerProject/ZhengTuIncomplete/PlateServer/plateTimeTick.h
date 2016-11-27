#ifndef PLATE_TIME_TICK_H
#define PLATE_TIME_TICK_H

#include "base/baseTime.h"
#include "base/baseThread.h"

class PlateTimeTick : public Thread,public SingletonBase<PlateTimeTick>
{
	private:
		friend class SingletonBase<PlateTimeTick>;
		PlateTimeTick();
		~PlateTimeTick();
	public:
		static Time s_currentTime;
		void run();
		static void zeroHour();
		static void fourHour();
	private:
		bool isHighDelay();
		void oneSec();
		void fiveSec();
		void tenSec();
		void oneMin();
		void fiveMin();
		void oneQuarter();
		void oneHour();
		void zeroClocker();
		void plateFinal();
	private:
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

