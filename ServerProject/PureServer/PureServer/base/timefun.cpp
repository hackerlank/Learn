#include "timefun.h"


Time::Time(const unsigned long long msec)
{
    now();
    delay(msec);
}
    
void Time::now()
{
    unsigned long long ret = 0LL;
    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);

    ret = tv.tv_sec * 1000;
    ret += tv.tv_nsec / 1000000L;
    m_msec = ret;
}

unsigned long long Time::msec() const
{
    return m_msec;
}

unsigned long Time::sec()
{
    return m_msec / 1000;
}

void Time::delay(const unsigned long long msec)
{
    m_msec += msec;
}

bool Time::operator < (const Time &arg) const
{
    return m_msec < arg.msec();
}

TimeClock::TimeClock(const unsigned long msec) : m_msec(msec),m_time(m_msec)
{
}

bool TimeClock::operator () (const Time &time)
{
    bool ret = false;
    if(m_time < time)
    {
        m_time.delay(m_msec);
        ret = true;
    }
    return ret;
}

TimeTv::TimeTv()
{
    now();
}

void TimeTv::now()
{
    time(&m_sec);
    gmtime_r(&m_sec,&m_tv);
}

unsigned long TimeTv::elapse() const
{
    TimeTv now;
    return now.getSec() - m_sec;
}
