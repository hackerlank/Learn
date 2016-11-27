#include "baseTime.h"
#include "baseLock.h"
void TM_SYSTEMTIME( struct tm* pTM,SYSTEMTIME *pST )
{
	memset( pST,0,sizeof(SYSTEMTIME) );
	pST->wYear   = pTM->tm_year + 1900;
	pST->wMonth  = pTM->tm_mon + 1;
	pST->wDay    = pTM->tm_mday;
	pST->wHour   = pTM->tm_hour;
	pST->wMinute = pTM->tm_min;
	pST->wSecond = pTM->tm_sec;
}

bool TIME_T_SYSTEMTIME( time_t ltime,SYSTEMTIME *pST )
{
	struct tm *now;
	now = localtime(&ltime);
	if(NULL == now) return false;
	TM_SYSTEMTIME(now,pST);
	return true;
}

bool getSystemTime( SYSTEMTIME *pST )
{
	time_t ltime;
	time(&ltime);
	return  TIME_T_SYSTEMTIME(ltime,pST);
}
long Time::s_myTimeZone = 0L;
long Time::s_myTimeSync = 0L;
const std::string& Time::getLocalTZ()
{
	static std::string stime;
	static bool init = false;
	if(!init)
	{
		std::ostringstream oss;
		tzset();
		s_myTimeZone = s_myTimeZone ? s_myTimeZone : timezone;
		oss << tzname[0] << timezone/3600;
		stime = oss.str().c_str();
		init = true;
	}
	return stime;
}
static Mutex tz_lock;
void Time::save_timezone(std::string &tzstr)
{
	tz_lock.lock();
	std::string ss = Time::getLocalTZ();
	std::ostringstream so;
	so << "TZ=" << ss;
	tzstr = so.str().c_str();
}

void Time::restore_timezone(const std::string &tzstr)
{
	static char tmp_tzstr[256 + 1];
	bzero(tmp_tzstr,sizeof(tmp_tzstr));
	strncpy(tmp_tzstr,tzstr.c_str(),sizeof(tmp_tzstr));
	putenv(tmp_tzstr);
	tzset();
	tz_lock.unlock();
}
void Time::setTimeSync(const QWORD sync)
{
	s_myTimeSync = sync;
}
