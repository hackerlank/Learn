#ifndef ROBOT_TIME_TICK_H
#define ROBOT_TIME_TICK_H 
#include "thread.h"
#include "singleton.h"
#include "timefun.h"

class RobotTimeTick : public Thread , public Singleton<RobotTimeTick>
{
    private:
        RobotTimeTick();
        ~RobotTimeTick() {};
        friend class Singleton<RobotTimeTick>;
    public:
        static Time s_time;
        virtual void run();
    private:
        TimeClock m_secClock;
        TimeClock m_minClock;
        TimeClock m_hourClock;
        TimeClock m_halfHourClock;
        TimeClock m_tenSecClock;
        TimeClock m_halfSecClock;
};

#endif



