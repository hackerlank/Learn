
#ifndef RTIME_H_
#define RTIME_H_

#include "Platform.h"
#include <string>

#if defined(linux) || defined(__linux) || defined(__linux__) || \
    defined(unix) || defined(__unix) || defined(__unix__) || \
    defined(__timespec_defined) || \
    defined(__STDC__)
#define __GETTIMEOFDAY 1
#define __LOCALTIME_R localtime_r
#include <sys/time.h>
#else
#define __LOCALTIME_R localtime
#endif
#include <time.h>

#define TYEAR 2000

#define TIME_MIN    (60)
#define TIME_HOUR   (60*TIME_MIN)
#define TIME_DAY    (24*TIME_HOUR)
#define TIME_WEEK   (7*TIME_DAY)

#ifndef BUF_TFBUF_SIZE
#define BUF_TFBUF_SIZE 4096 // XXX: The size of TimeFilm._msg[]
#endif

namespace buf
{

class RTime;
typedef UINT64 timediff_t;

// XXX: if CONSTRUCTOR is empty then TimeInit must be called
void TimeInit();

class Time
{
public:
    static inline time_t Now() { return time(0); }

    static inline bool sameDay(time_t a, time_t b)
    {   
        time_t t1 = a, t2 = b;
        struct tm t_tm1, t_tm2;
        __LOCALTIME_R(&t1,&t_tm1);
        __LOCALTIME_R(&t2,&t_tm2);
        return t_tm1.tm_yday == t_tm2.tm_yday;
    }  

    static inline time_t TheMin(int c, time_t tm = Now())
    {
        return (tm + c * 60) / 60 * 60;
    }

    static inline time_t TheHour(int c, time_t tm = Now())
    {
        return (tm + c * 3600) / 3600 * 3600;
    }

    static inline time_t TheDay(int c = 0, time_t cur = Now())
    {
        struct tm t_tm;
        __LOCALTIME_R(&cur, &t_tm);
        t_tm.tm_hour = t_tm.tm_min = t_tm.tm_sec = 0;
        time_t tmp = mktime(&t_tm);
        return tmp + c * 24 * 60 * 60; 
    }

    static inline time_t TheWeek(int c = 0, time_t cur = Now())
    {   
        time_t t = cur;
        struct tm t_tm;
        __LOCALTIME_R(&t, &t_tm);
        if(t_tm.tm_wday == 0)
            t_tm.tm_wday = 7;
        t = t + (7 * c + 1 - t_tm.tm_wday) * 86400;
        return TheDay(0, t);
    }   

    static inline time_t TheMonth(int c = 0, time_t cur = Now())
    {   
        time_t t = cur;
        struct tm t_tm;
        __LOCALTIME_R(&t,&t_tm);
        t_tm.tm_mon = t_tm.tm_mon + c;
        t_tm.tm_year = t_tm.tm_year + t_tm.tm_mon / 12;
        t_tm.tm_mon = t_tm.tm_mon % 12;
        t_tm.tm_mday = 1;
        t_tm.tm_hour = 0;
        t_tm.tm_min = 0; 
        t_tm.tm_sec = 0;
        return  mktime(&t_tm);
    }

    static inline time_t TheYear(int c = 0, time_t cur = Now())
    {
        time_t t = cur;
        struct tm t_tm;
        __LOCALTIME_R(&t,&t_tm); 
        t_tm.tm_year = t_tm.tm_year + c;
        t_tm.tm_mon = 0; 
        t_tm.tm_mday = 1;
        t_tm.tm_hour = 0;
        t_tm.tm_min = 0;
        t_tm.tm_sec = 0; 
        return mktime(&t_tm);
    }

    static inline time_t MkTime(UINT32 y, UINT32 m, UINT32 d, UINT32 hh = 0, UINT32 mm = 0, UINT32 ss = 0)
    {
        struct tm t_tm;
        if (y < 1900)
            t_tm.tm_year = 0;
        else
            t_tm.tm_year = y - 1900;
        if (m % 13)
            t_tm.tm_mon = m % 13 - 1;
        else
            t_tm.tm_mon = 0;
        if (d % 32)
            t_tm.tm_mday = d % 32;
        else
            t_tm.tm_mday = 1;
        t_tm.tm_hour = hh % 24;
        if (mm % 61)
            t_tm.tm_min = mm % 61 - 1;
        else
            t_tm.tm_min = 0;
        if (ss % 61)
            t_tm.tm_sec = ss % 61 - 1;
        else
            t_tm.tm_sec = 0;

        time_t t2 = mktime(&t_tm);
        return t2;
    }

public:
    Time() : _time(0)
    {
        now();
    }

    Time(time_t time) : _time(time)
    {
        struct tm t_tm;
        setTm(__LOCALTIME_R(&_time, &t_tm));
    }

    Time(const Time& time) : _time(time._time)
    {
        struct tm t_tm;
        setTm(__LOCALTIME_R(&_time, &t_tm));
    }

    void now(void)
    {
        struct tm t_tm;
        time(&_time);
        setTm(__LOCALTIME_R(&_time, &t_tm));
    }

    inline int year(void) const
    {
        return _tm.tm_year + 1900;
    }

    inline int month(void) const
    {
        return _tm.tm_mon + 1;
    }

    inline int day(void) const
    {
        return _tm.tm_mday;
    }

    inline int wday(void) const
    {
        return _tm.tm_wday;
    }


    inline int hour(void) const
    {
        return _tm.tm_hour;
    }

    inline int min(void) const
    {
        return _tm.tm_min;
    }

    inline int sec(void) const
    {
        return _tm.tm_sec;
    }

    inline timediff_t secs(void) const
    {
        return _time;
    }

    inline bool operator>(const Time& time) const
    {
        return _time > time._time;
    }

    inline bool operator>=(const Time& time) const
    {
        return _time >= time._time;
    }

    inline bool operator<(const Time& time) const
    {
        return _time < time._time;
    }

    inline bool operator<=(const Time& time) const
    {
        return _time <= time._time;
    }

    inline bool operator==(const Time& time) const 
    {
        return _time == time._time;
    }

    inline bool operator!=(const Time& time) const
    {
        return _time != time._time;
    }

    const char* toString(void) const;
    const char* toNormal(void) const;

    const char* yyyymmdd(char sep = '/') const;
    const char* yyyymmddhhmm(char ysep = '/', char hsep = ':') const;
    const char* yyyymmddhhmmss(char ysep = '/', char hsep = ':') const;

    const char* yymmdd(char sep = '/') const;
    const char* yymmddhhmm(char ysep = '/', char hsep = ':') const;
    const char* yymmddhhmmss(char ysep = '/', char hsep = ':') const;

    const char* hhmm(char sep = ':') const;
    const char* hhmmss(char sep = ':') const;

    const char* hhmmssuu(char sep = ':') const;

private:
    inline void setTm(struct tm* tm) { _tm = *tm; }

private:
    time_t _time; // seconds
    struct tm _tm; // year,month,day...
};

class RTime
{
public:
#ifdef __GETTIMEOFDAY
    static struct timezone _zone;
#endif

    inline static timediff_t tv2msecs(struct timeval& tv)
    {
        return tv.tv_sec * 1000LL + tv.tv_usec/1000LL;
    }

    inline static timediff_t tv2usecs(struct timeval& tv)
    {
        return tv.tv_sec * 1000000LL + tv.tv_usec;
    }

    static timediff_t tick(timediff_t delay = 0, timediff_t* usecs = NULL)
    {
        struct timeval val;
#ifdef __GETTIMEOFDAY
        if (gettimeofday(&val, &_zone))
            return 0;
#elif defined(WINDOWS)
        union {
            long long ns100;
            FILETIME ft;
        } now;

        GetSystemTimeAsFileTime(&now.ft);
        val.tv_usec = (long)((now.ns100 / 10LL) % 1000000LL);
        val.tv_sec = (long)((now.ns100 - 116444736000000000LL) / 10000000LL);
#else
        // XXX:
        return 0;
#endif

        if (usecs)
            *usecs = tv2usecs(val) + delay*1000LL;

        return tv2msecs(val) + delay;
    }

public:
    RTime() : _msecs(now()) {}
    RTime(const RTime& time) : _msecs(time.msecs()), _usecs(time.usecs()) {}
    explicit RTime(timediff_t diff) : _msecs(now())
    {
        addDelay(diff);
    }

    timediff_t now(timediff_t delay = 0)
    {
        _msecs = tick(delay, &_usecs);
        return _msecs;
    }

    inline void addDelay(timediff_t diff)
    {
        _msecs += diff;
    }

    inline void delay(timediff_t diff)
    {
        _msecs += diff;
    }

    inline timediff_t secs(void) const
    {
        return _msecs / 1000L;
    }
    
    inline timediff_t msec(void) const
    {
        return _msecs % 1000L;
    }

    inline timediff_t msecs(void) const
    {
        return _msecs;
    }

    inline timediff_t usecs(void) const
    {
        return _usecs;
    }

    inline timediff_t elapse(const RTime& time) const
    {
        if (time._msecs > _msecs)
            return time._msecs - _msecs;
        return _msecs - time._msecs;
    }

    inline timediff_t elapse() const
    {
        timediff_t now = tick();
        if (now > _msecs)
            return now - _msecs;
        return _msecs - now;
    }

    inline const RTime& operator=(const RTime& time)
    {
        _msecs = time._msecs;
        return *this;
    }

    inline const RTime& operator+(const RTime& time)
    {
        _msecs += time._msecs;
        return *this;
    }

    inline const RTime& operator-(const RTime& time)
    {
        _msecs -= time._msecs;
        return *this;
    }

    inline bool operator>(const RTime& time) const
    {
        return _msecs > time.msecs();
    }

    inline bool operator>=(const RTime& time) const
    {
        return _msecs >= time.msecs();
    }

    inline bool operator<(const RTime& time) const
    {
        return _msecs < time.msecs();
    }

    inline bool operator<=(const RTime& time) const
    {
        return _msecs <= time.msecs();
    }

    inline bool operator==(const RTime& time) const
    {
        return _msecs == time.msecs();
    }

    inline bool operator!=(const RTime& time) const
    {
        return _msecs != time.msecs();
    }

private:
    timediff_t _msecs;
    timediff_t _usecs;
};

class TimeInterval
{
public:
    TimeInterval(UINT64 interval/*micro seconds*/, UINT64 delay = 0)
        : _interval(interval), _time(delay) {}

    void reset(UINT64 interval, const RTime& time)
    {
        _interval = interval;
        _time = time;
        _time.addDelay(_interval);
    }

    bool operator()(const RTime& time)
    {
        if (_time <= time)
        {
            _time = time;
            _time.addDelay(_interval);
            return true;
        }
        return false;
    }

    inline void next()
    {
        _time.now();
        _time.addDelay(_interval);
    }

private:
    UINT64 _interval;
    RTime _time;
};

class TimeFilm;
const char* TimeFilmOperatorDefault(const TimeFilm*, char* buf, size_t size);

class TimeFilm
{
public:
    typedef const char* (*TimeFilmOperator)(const TimeFilm*, char* buf, size_t size);

public:
    TimeFilm(const char* msg = NULL)
        : _begin(), _end(), _op(TimeFilmOperatorDefault)
    {
        if (msg)
            SNPRINTF(_msg, sizeof(_msg), "%s", msg);
        else
            MEMZRO(_msg, sizeof(_msg));
    }

    ~TimeFilm();

    inline void setOperator(TimeFilmOperator op) { _op = op; }

    inline const RTime& begin() const { return _begin; }
    inline const RTime& end() const { return _end; }
    inline const char* msg() const { return _msg; }

private:
    RTime _begin;
    RTime _end;
    char _msg[BUF_TFBUF_SIZE]; // XXX:
    TimeFilmOperator _op; // XXX: avoid to use virtual function
};

} // namespace buf

using namespace buf;

#endif // RTIME_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

