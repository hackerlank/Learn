#ifndef LOGIN_TIME_TICK_H
#define LOGIN_TIME_TICK_H
#include "thread.h"
#include "singleton.h"
#include "timefun.h"

class LoginTimeTick : public Thread , public Singleton<LoginTimeTick>
{
    private:
        LoginTimeTick();
        ~LoginTimeTick() {};
        friend class Singleton<LoginTimeTick>;
        void testHttp(const std::string userName);
    public:
        static Time s_time;
        virtual void run();
    private:
        TimeClock m_secClock;
        TimeClock m_minClock;
        TimeClock m_hourClock;
        TimeClock m_halfHourClock;
        TimeClock m_heartClock;
};

#endif



