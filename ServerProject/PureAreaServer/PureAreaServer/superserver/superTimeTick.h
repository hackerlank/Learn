#ifndef SUPER_TIME_TICK_H
#define SUPER_TIME_TICK_H
#include "thread.h"
#include "singleton.h"
#include "timefun.h"

class SuperTimeTick : public Thread , public Singleton<SuperTimeTick>
{
    private:
        SuperTimeTick();
        ~SuperTimeTick() {};
        friend class Singleton<SuperTimeTick>;
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



