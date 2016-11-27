#ifndef SCENE_TIME_TICK_H
#define SCENE_TIME_TICK_H
#include "thread.h"
#include "singleton.h"
#include "timefun.h"

class SceneTimeTick : public Thread , public Singleton<SceneTimeTick>
{
    private:
        SceneTimeTick();
        ~SceneTimeTick() {};
        friend class Singleton<SceneTimeTick>;
    public:
        static Time s_time;
        virtual void run();
    private:
        TimeClock m_secClock;
        TimeClock m_minClock;
        TimeClock m_hourClock;
        TimeClock m_halfHourClock;
        TimeClock m_tenSecClock;
        TimeClock m_heartClock;;
};

#endif



