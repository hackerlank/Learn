#ifndef TIME_FUN_H
#define TIME_FUN_H
#include <time.h>
#include <sys/time.h>

class Time
{
    private:
        //系统时间(毫秒)
        unsigned long long m_msec;
    public:
        Time(const unsigned long long msec = 0);
        unsigned long long msec() const;
        unsigned long sec();
        void now();
        void delay(const unsigned long long msec);
        bool operator < (const Time &time) const;
};

class TimeClock
{
    private:
        unsigned int m_msec;
        Time m_time;
    public:
        TimeClock(const unsigned long msec);
        bool operator () (const Time &time);
};

class TimeTv
{
    private:
        time_t m_sec;
        struct tm m_tv;
    public:
        TimeTv();
        void now();
        unsigned long elapse() const;
    public:
        inline unsigned long getSec() const
        {
            return m_sec;
        }
};



#endif
