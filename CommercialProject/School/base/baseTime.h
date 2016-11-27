#ifndef BASE_TIME_H
#define BASE_TIME_H
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "common/baseDef.h"
#include "baseFunc.h"
#include "global.h"

using namespace std;

#define ONE_SEC (1000)
#define HALF_SEC (500)
#define ONE_MIN (60000)
#define HALF_MIN (30000)
#define ONE_HOUR (3600000)
#define HALF_HOUR (1800000)
#define ONE_DAY (86400000)
#define HALF_DAY (43200000)
#define ONE_WEEK (604800000)
#define FOREVER (4294967294)
typedef struct{
WORD wYear;
WORD wMonth;
WORD wDay;
WORD wHour;
WORD wMinute;
WORD wSecond;
}SYSTEMTIME;

void TM_SYSTEMTIME( struct tm* pTM, SYSTEMTIME *pST);

bool TIME_T_SYSTEMTIME( time_t ltime,SYSTEMTIME *pST );

bool getSystemTime( SYSTEMTIME *pST );

class RTime
{
	private:
		QWORD _msecs;  //毫秒
		QWORD _now()
		{
			QWORD retval = 0LL;
			struct timeval tv;
			gettimeofday(&tv,NULL);
			retval = tv.tv_sec;
			retval *= 1000;
			retval += tv.tv_usec / 1000;
			return retval;
		}
		//延时delay毫秒
		void nowByDelay(int delay)
		{
			_msecs = _now();
			addDelay(delay);
		}
	public:
		RTime(const int delay)
		{
			nowByDelay(delay);
		}
		RTime(const RTime & _time)
		{
			_msecs = _time.msecs();
		}
		void now()
		{
			_msecs = _now();
		}
		DWORD sec() const
		{
			return _msecs / 1000;
		}
		DWORD msec() const
		{
			return _msecs % 1000;
		}
		QWORD msecs() const
		{
			return _msecs;
		}
		void setmsecs(QWORD _data)
		{
			_msecs = _data;
		}
		void addDelay(int delay)
		{
			_msecs += delay;
		}
		RTime& operator= (const RTime& rt)
		{
			_msecs = rt.msecs();
			return *this;
		}
		const RTime& operator+ (const RTime &rt)
		{
			_msecs += rt.msecs();
			return *this;
		}
		const RTime& operator- (const RTime &rt)
		{
			_msecs -= rt.msecs();
			return *this;
		}
		bool operator> (const RTime &rt)
		{
			return _msecs > rt.msecs();
		}
		bool operator >= (const RTime &rt)
		{
			return _msecs >= rt.msecs();
		}
		bool operator < (const RTime &rt)
		{
			return _msecs < rt.msecs();
		}
		bool operator <= (const RTime &rt)
		{
			return _msecs <= rt.msecs();
		}
		bool operator == (const RTime &rt)
		{
			return _msecs == rt.msecs();
		}
		QWORD elapse(const RTime &rt)
		{
			if(rt.msecs() > _msecs)
			{
				return rt.msecs() - _msecs;
			}
			return 0LL;
		}

		static void getLocalTime(struct tm &tv,time_t timeValue)
		{
			timeValue += 8 * 60 * 60;
			tv = *localtime(&timeValue);
		}

};
class Time
{
	public:
		friend class Clocker;
		static SQWORD s_myTimeZone;
		static SQWORD s_myTimeSync;
	public:
		Time()
		{
			now();
		}
		Time(const Time &time)
		{
			m_timeSpec = time.m_timeSpec;
			m_msec = time.m_msec;
			m_tmOk = false;
		}
		void now()
		{
			clock_gettime(CLOCK_REALTIME,&m_timeSpec);
			m_msec = sec()*1000L + m_timeSpec.tv_nsec/1000000L;
			m_tmOk = false;
		}
		inline QWORD sec() const
		{
			return m_timeSpec.tv_sec - s_myTimeZone - s_myTimeSync;
		}
		inline QWORD msec() const
		{
			return m_msec;
		}
		inline QWORD usec() const
		{
			return sec()*1000L + m_timeSpec.tv_nsec/1000L;
		}
		//delay为毫秒
		inline void addDelay(const QWORD delay)
		{
			QWORD secTemp = delay/1000L;
			QWORD nsecTemp = delay%1000L;
			m_timeSpec.tv_nsec += (nsecTemp*1000000L);
			secTemp += m_timeSpec.tv_nsec/1000000000L;
			m_timeSpec.tv_sec += secTemp;
			m_timeSpec.tv_nsec -= nsecTemp*1000000000L;
			m_msec = sec()*1000L + m_timeSpec.tv_nsec/1000000L;
			m_tmOk = false;
		}
		inline Time& operator= (const Time &time)
		{
			m_timeSpec = time.m_timeSpec;
			m_msec = time.m_msec;
			m_tmOk = false;
			return *this;
		}
		inline bool operator> (const Time &time) const
		{
			return m_msec > time.m_msec ? true : false;
		}
		inline bool operator>= (const Time &time) const
		{
			return m_msec >= time.m_msec ? true : false;
		}
		inline bool operator< (const Time &time) const
		{
			return m_msec < time.m_msec ? true : false;
		}
		inline bool operator<=  (const Time &time) const
		{
			return m_msec <= time.m_msec ? true : false;
		}
		inline bool operator== (const Time &time) const
		{
			return (time.m_msec == m_msec);
		}
		QWORD elapse(const Time &time) const
		{
			SWORD val = time.msec() - msec();
			return val < 0 ? 0L : val;
		}
		static void getLocalTime(struct tm &tmVal,time_t timeVal)
		{
			time_t timeValue = timeVal - s_myTimeSync - s_myTimeZone;
			gmtime_r(&timeValue,&tmVal);
		}
		WORD getMDays(const WORD dayDiff)
		{
			if(dayDiff == 0)
			{
				return getMDays();
			}
			time_t timeVal = m_timeSpec.tv_sec + dayDiff *(ONE_DAY/1000);
			struct tm tmVal;
			getLocalTime(tmVal,timeVal);
			return tmVal.tm_mday;
		}
		void checkTmOk()
		{
			if(!m_tmOk) 
			{ 
				getLocalTime(s_tm,m_timeSpec.tv_sec);
				m_tmOk = true;
			}
		}
		void format(char *buffer,size_t bufferlen,const char *format = "%c/$M/%d$Y")
		{
			checkTmOk();
			strftime(buffer,bufferlen,format,&s_tm);
		}
		QWORD getSeconds()
		{
			checkTmOk();
			return s_tm.tm_sec;
		}
		DWORD getMinutes()
		{
			checkTmOk();
			return s_tm.tm_min;
		}
		DWORD getHours()
		{
			checkTmOk();
			return s_tm.tm_hour;
		}
		DWORD getMDays()
		{
			checkTmOk();
			return s_tm.tm_mday;
		}
		DWORD getMonths()
		{
			checkTmOk();
			return s_tm.tm_mon;
		}
		DWORD getYears()
		{
			checkTmOk();
			return s_tm.tm_year;
		}
		DWORD getWDays()
		{
			checkTmOk();
			return s_tm.tm_wday;
		}
		DWORD getYDays()
		{
			checkTmOk();
			return s_tm.tm_yday;
		}
		static const std::string& getLocalTZ();
		static void save_timezone(std::string &tzstr);
		static void restore_timezone(const std::string &tzstr);
		static void setTimeSync(const QWORD sync = 0);
	public:
		struct timespec m_timeSpec;
		QWORD m_msec;
		bool m_tmOk;
		struct tm s_tm;
};

class Timer
{
	public:
		Timer() : m_milliSec(0),m_timer() {}
		explicit Timer(const QWORD milSec,bool first=false,const QWORD delay=0) : m_milliSec(milSec),m_timer()
		{
			if(!first)
			{
				m_timer.addDelay(m_milliSec+ delay);
			}
		}
		explicit Timer(const QWORD milSec,bool first,Time &ctv) : m_milliSec(milSec),m_timer(ctv)
		{
			if(!first)
			{
				m_timer.addDelay(m_milliSec);
			}
		}
		void reset(const QWORD milSec,const Time &cur)
		{
			m_milliSec = milSec;
			m_timer = cur;
			m_timer.addDelay(m_milliSec);
		}
		void current(const Time &cur)
		{
			m_timer = cur;
		}
		void next(const Time &cur,const QWORD delay)
		{
			m_timer = cur;
			m_timer.addDelay(delay);
		}
		void next(const Time &cur)
		{
			m_timer = cur;
			m_timer.addDelay(m_milliSec);
		}
		inline DWORD leftSec(const Time &cur)
		{
			return (m_timer.sec() > cur.sec()) ? (m_timer.sec() - cur.sec()) : 0;
		}
		inline QWORD leftMsec(const Time &cur)
		{
			return (m_timer.m_msec > cur.m_msec) ? (m_timer.m_msec- cur.m_msec) : 0;
		}
		inline bool operator() (const Time &cur)
		{
			CheckConditonReturn(m_timer.m_msec<=cur.m_msec,false);
			addDelay(cur);
			return true;
		}
		inline bool empty()
		{
			return m_milliSec == 0 ? true : false;
		}
		QWORD getTimeMesc()
		{
			return m_timer.msec();
		}
	private:
		//毫秒数
		QWORD m_milliSec;
		Time m_timer;
	private:
		inline void addDelay(const Time &cur)
		{
			m_timer = cur;
			m_timer.addDelay(m_milliSec);
		}
};

		

class Clocker
{
	public:
		explicit Clocker(const SQWORD how_long,const SQWORD interval):_long(how_long),_interval(interval)
		{
			my_timesync = Time::s_myTimeSync;
			assert(_long + _interval);
			delay();
		}
		explicit Clocker(const SQWORD how_long,const SQWORD interval,Time &ctv):_long(how_long),_interval(interval),_clock(ctv)
		{
			my_timesync = Time::s_myTimeSync;
			assert(_long + _interval);
			assert(_interval >= _long);
			delay();
		}
		void next (const Time &cur)
		{
			_clock = cur;
			delay();
		}
		inline QWORD leftSec(const Time &cur)
		{
			SQWORD val = _clock.sec() - cur.sec();
			if(val < 0L)
			{
				return 0L;
			}
			return val;
		}
		inline bool operator() (const Time &cur)
		{
			if(_clock.m_timeSpec.tv_sec + Time::s_myTimeSync - my_timesync > cur.m_timeSpec.tv_sec)
			{
				return false;
			}
			else
			{
				my_timesync = Time::s_myTimeSync;
				_clock = cur;
				delay();
				return true;
			}
		}
	private:
		void delay()
		{
			QWORD escape = _clock.sec() % _interval;
			if(escape < _long)
			{
				_clock.addDelay((_long - escape) * 1000);
			}
			else if(escape > _long)
			{
				_clock.addDelay((_interval + _long - escape) * 1000);
			}
			else
			{
				_clock.addDelay(_interval * 1000);
			}
		}
		const QWORD _long;
		const QWORD _interval;
		SQWORD my_timesync;
		Time _clock;
};
#if 0
//时间
class Timer
{
	public:
		Timer(const float how_long,const int delay = 0):_long((int)(how_long * 1000)),_timer(delay*1000)
		{
		}
		Timer(const float how_long,const RTime& cur):_long((int)(how_long * 1000)),_timer(cur)
		{
			_timer.addDelay(_long);
		}
		void next(const RTime &cur)
		{
			_timer = cur;
			_timer.addDelay(_long);
		}
		//如果当前时间小于或者等于_timer则延时_long
		bool operator() (const RTime &cur)
		{
			if(_timer <= cur)
			{
				_timer = cur;
				_timer.addDelay(_long);
				return true;
			}
			return false;
		}
	private:
		int _long;
		RTime _timer;
};

#endif

#endif














