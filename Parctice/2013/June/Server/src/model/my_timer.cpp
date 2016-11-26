#include"my_timer.h"
#include <iostream>
using namespace std;

void ev_timer_init(ev_timer *timer, void (*cb)(struct ev_loop *, ev_timer *, int),
	double after, int repeat)
{
#if 0
	if (event_initialized(timer->timerEv))
	{
		//如果timerEv已经初始过,并在运行中
		if (event_pending((timer->timerEv), EV_TIMEOUT, (&timer->tv)))
		{
			//已经挂上的timer不准重复init
			// printf("[BisonWarn] you must stop the timer before reinit it!!!!!\n");
			// printf("[BisonWarn] now I help you stop the timer but I have no responsibility if this cause any problem!\n");
			ev_timer_stop(loops, timer);
			//return;
		}
	}
#endif
	if (timer->isRunning)
	{
		ev_timer_stop(loops, timer);
	}
	evutil_timerclear(&timer->tv);
	timer->tv.tv_sec = (int)after;
	timer->tv.tv_usec = (int)(1000000 *(after - floor(after)));;
	timer->timeout_cb = cb;
	if (repeat <= 0)
	{
		timer->isCycle = 0;
	} else {
		timer->isCycle = repeat;
	}
	//timer->revents = repeat;
}

void ext_ev_timer_init(ev_timer *timer, void (*cb)(struct ev_loop *, ev_timer *, int),
	double after, int repeat, void *target, char* targetId)
{
#if 0	
	if (event_initialized(timer->timerEv))
	{
		//如果timerEv已经初始过,并在运行中
		if (event_pending((timer->timerEv), EV_TIMEOUT, (&timer->tv)))
		{
			//已经挂上的timer不准重复init
			// printf("[BisonWarn] you must stop the timer before reinit it!!!!!\n");
			// printf("[BisonWarn] now I help you stop the timer but I have no responsibility if this cause any problem!\n");
			ev_timer_stop(loops, timer);
			//return;
		}
	}
#endif
	if (timer->isRunning)
	{
		ev_timer_stop(loops, timer);
	}
	evutil_timerclear(&timer->tv);
	timer->tv.tv_sec = (int)after;
	timer->tv.tv_usec = (int)(1000000 *(after - floor(after)));;
	timer->timeout_cb = cb;
	timer->isCycle = ((repeat > 0) ? repeat : 0);
	timer->target = target;
	if (targetId != NULL)
	{
		strncpy(timer->targetId, targetId, strlen(targetId) + 1);
	}
}

void ev_timer_set(ev_timer *timer, double after, int repeat)
{
#if 0	
	if (event_initialized(timer->timerEv))
	{
		//如果timerEv已经初始过,并在运行中
		if (event_pending((timer->timerEv), EV_TIMEOUT, (&timer->tv)))
		{
			//已经挂上的timer不准重复init
			// printf("[BisonWarn] you must stop the timer before reinit it!!!!!\n");
			// printf("[BisonWarn] now I help you stop the timer but I have no responsibility if this cause any problem!\n");
			ev_timer_stop(loops, timer);
			//return;
		}
	}
#endif
	if (timer->isRunning)
	{
		ev_timer_stop(loops, timer);
	}
	evutil_timerclear(&timer->tv);
	timer->tv.tv_sec = (int)after;
	timer->tv.tv_usec = (int)(1000000 *(after - floor(after)));
	timer->isCycle = ((repeat > 0) ? repeat : 0);;
}

void timerSys_cb(int fd, short event, void *arg)
{
	ev_timer *timer = (ev_timer*)arg;
	timer->isRunning = false;
	timer->timeout_cb(loops, timer, timer->isCycle);
#if 0
	if (timer->isCycle > 0)
	{
		//ev_timer_init(timer, timer->timeout_cb, timer->revents, timer->revents);
		ev_timer_start(loops, timer);
	}
#endif
}

void ev_timer_start(struct ev_loop * loop, ev_timer *timer)
{
	// cout << "timer start:" << timer->tv.tv_sec << endl;
	if (timer->isRunning)
	{
		ev_timer_stop(loops, timer);
	}
	timer->isRunning = true;
#if 0	
	if (event_initialized(timer->timerEv))
        {
                //如果timerEv已经初始过,并在运行中
                if (event_pending((timer->timerEv), EV_TIMEOUT, (&timer->tv)))
                {
                        //已经挂上的timer不准重复init
                        // printf("[BisonWarn] you must stop the timer before reinit it!!!!!\n");
                        // printf("[BisonWarn] now I help you stop the timer but I have no responsibility if this cause any problem!\n");
                        ev_timer_stop(loops, timer);
                        //return;
                }
        }
#endif

	gettimeofday(&timer->endTv, NULL);
	timer->endTv.tv_sec += timer->tv.tv_sec;
	timer->endTv.tv_usec += timer->tv.tv_usec;
	if (timer->endTv.tv_usec > 1000000)
	{
		timer->endTv.tv_sec += 1;
		timer->endTv.tv_usec -= 1000000;
	}
	
	event_assign(timer->timerEv, loops, -1, EV_TIMEOUT, timerSys_cb, (void*)timer);
	
	event_add(timer->timerEv, &timer->tv);
}

void ev_timer_stop(struct ev_loop * loop, ev_timer *timer)
{
	if (timer == NULL)
	{
		return;
	}
	timer->isRunning = false;
	if (timer->timerEv && loops)
	{
		event_del(timer->timerEv);
		
	} else {
		printf("[BisonWarning] timer end so delete timerEv, but base is already del\n");
	}
	
}

double ev_timer_remaining(struct event_base *loop, ev_timer *timer)
{
#if 0
	if (!event_pending((timer->timerEv), EV_TIMEOUT, (&timer->tv)))
	{
		return 0.0;
	}
#endif 
	if (!timer->isRunning)
	{
		// cout<<"[BisonShow] the stop timer's remaining timer is 0"<<endl;
		return 0.0;
	}
	struct timeval nowTv;
	gettimeofday(&nowTv, NULL);
	double sec = timer->endTv.tv_sec - nowTv.tv_sec;
	double usec = timer->endTv.tv_usec - nowTv.tv_usec;
	// cout<<"sec is "<<sec<<" and usec is "<<usec<<endl;
	if (usec < 0)
	{
		sec -= 1;
		usec += 1000000;
	}
	if (sec < 0)
	{
		return 0.;
	}
	double ret = sec + usec / 1000000;
	return ret;
}

bool ev_timer_is_running(struct event_base *loop, ev_timer *timer)
{
	if (timer != NULL)
	{
		return timer->isRunning;
	}
}
