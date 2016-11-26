#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_

#include <cstdlib>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <list>
#include <string>
#include <map>

#include <event2/util.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include<math.h>
#define ev_loop event_base



//第一次合服版
// #define MERGE_SERVER_FIRST_VERSION

//公共缓存下标
#define PUBLIC_MEMCACHED_INDEX			1

using namespace std;

extern struct event_base *loops;

struct ev_timer;
typedef void(*cbFun)(struct ev_loop *loop, struct ev_timer *timer, int revents);
void timerSys_cb(int fd, short event, void *arg);
typedef struct ev_timer
{
	struct event *timerEv;
	void *target;
	char targetId[64];
	struct timeval tv;
	cbFun timeout_cb;
	int isCycle;
	bool isRunning;
	struct timeval endTv;
	ev_timer()
	{
		//timerEv =  event_new(base, -1, EV_PERSIST, timeout_cb, (void *)base);
		target = NULL;
		memset(targetId, 0, sizeof(targetId));
		//targetId = "";
		//timerEv =  evtimer_new(loops, NULL, &timerEv);
		timerEv = event_new(loops, -1, EV_TIMEOUT, timerSys_cb, NULL);
		isRunning = false;
		//event_assign(timerEv, base, -1, EV_PERSIST, timeout_cb, (void*) timerEv);
	}
	~ev_timer()
	{
		//printf("[BisonWarn] if you delete timer please give me a signo!\n");
		if (timerEv)
		{
			// printf("[] have event_free one timer!!\n");
			event_free(timerEv);
			timerEv = NULL;
		}
		if (target != NULL)
		{
			//delete target; 这里不做释放，这个target是外面传入的话就在外面释放
			target = NULL;
		}
	
		isRunning = false;
		memset(targetId, 0, sizeof(targetId));
	}
}ev_timer;

void ev_timer_start(struct ev_loop * loop, ev_timer *timer);

void ev_timer_init(ev_timer *timer, void (*cb)(struct ev_loop *, ev_timer *, int),
	double after, int repeat);

void ext_ev_timer_init(ev_timer *timer, void (*cb)(struct ev_loop *, ev_timer *, int),
	double after, int repeat, void *target = NULL, char* targetId = NULL);

void timerSys_cb(int fd, short event, void *arg);

void ev_timer_set(ev_timer *timer, double after, int repeat);

void ev_timer_stop(struct ev_loop *loop, ev_timer *timer);

double ev_timer_remaining(struct event_base *loop, ev_timer *timer);

bool ev_timer_is_running(struct event_base *loop, ev_timer *timer);

/* return remaining time */
//float ev_timer_remaining (ev_timer *w);
#endif
