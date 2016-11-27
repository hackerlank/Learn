#ifndef RECORD_TIME_TICK_H
#define RECORD_TIME_TICK_H
#include "thread.h"
#include "singleton.h"
#include "timefun.h"

class RecordTimeTick : public Thread , public Singleton<RecordTimeTick>
{
    private:
        RecordTimeTick();
        ~RecordTimeTick() {};
        friend class Singleton<RecordTimeTick>;
    public:
        static Time s_time;
        virtual void run();
    private:
        TimeClock m_secClock;
        TimeClock m_minClock;
        TimeClock m_hourClock;
        TimeClock m_halfHourClock;
        TimeClock m_tenSecClock;
};

#endif



