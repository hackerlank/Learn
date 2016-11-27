#ifndef GATE_WAY_TIME_TICK_H
#define GATE_WAY_TIME_TICK_H
#include "thread.h"
#include "singleton.h"
#include "timefun.h"

class GatewayTimeTick : public Thread , public Singleton<GatewayTimeTick>
{
    private:
        GatewayTimeTick();
        ~GatewayTimeTick() {};
        friend class Singleton<GatewayTimeTick>;
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



