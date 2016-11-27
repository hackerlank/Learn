#ifndef TIME_TICK_H
#define TIME_TICK_H
#include "thread.h"
#include "singleton.h"
#include "timefun.h"

class TimeTick : public Thread , public Singleton<TimeTick>
{
    private:
        TimeTick();
        ~TimeTick() {};
        friend class Singleton<TimeTick>;
    public:
        static Time s_time;
        virtual void run();
    private:
        TimeClock m_secClock;
        TimeClock m_minClock;
        TimeClock m_hourClock;
        TimeClock m_halfHourClock;
};

#endif



