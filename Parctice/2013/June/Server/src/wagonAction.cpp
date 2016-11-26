/************************************************************
	文件名：wagonAction.cpp
	文件作用：实现地图思考回调函数
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/
#include"wagonAction.h"
#include"libev.h"
#include"wagon.h"
#include"timerContainer.h"
#include"task_failed_comm.h"
#include"hero.h"
extern TimerContainer<Wagon*> *wagonTimer;
extern map<string,Wagon*> wagonInstMap;
void wagonThkCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{
	map<string,Wagon*>::iterator wagon_it;
	
	/*先暂停*/
	ev_timer_stop(loop,think);
	
	/*判断思考列表是否为空*/
	// if(wagonTimer->empty())
	// {
		// return;
	// }
	
	Wagon *timeOutWagon = NULL;	
	
	
	/*获得思考对象指针*/
	// timeOutWagon = wagonTimer->outObj();
	timeOutWagon = (Wagon *)think->target;
	
	
	/*判断思考对象指针是否为空*/
	if(timeOutWagon == NULL)
	{
		return;
	}
	
	Hero *hero = timeOutWagon->getOwner();
	if (hero != NULL)
	{
		/*hero和马车相关的数据删除掉*/
		// strncpy(hero->memHero->wagonId, "\0", 2);
		memset(hero->memHero->wagonId, 0, sizeof(hero->memHero->wagonId));
		taskFailedDeal(hero, "task00295", 1);
		taskFailedDeal(hero, "task00419", 0);
	}
		
	timeOutWagon->disperMsg();
	
	delete timeOutWagon;
	timeOutWagon = NULL;
}
	
