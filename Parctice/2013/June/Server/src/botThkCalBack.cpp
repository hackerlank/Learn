#include"bottle.h"
#include"trap.h"
#include"takeGoods.h"
#include"otherThingCalBack.h"
extern struct ev_loop *loops;

/*瓶罐打碎，以及重刷控制*/
void botThkCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Bottle *bot;
	
	ev_timer_stop(loop,think);	
	
	bot = (Bottle *)think->target;
	
	if(bot == NULL)
	{
		return;
	}	
	
	if(bot->dieOutFlg())
	{
		bot->disperMsg();
		
		/*有一些是打碎后就刷出来*/
		if(bot->getBrushStyle() == 0)
		{
			ext_ev_timer_init(think,botThkCalBack,2,0, bot);
			ev_timer_start(loop,think);
		}
		
		/*副本里面的则就是打碎不在刷出*/
		else
		{
			return;
		}
	}
	
	else if(bot->aliveFlg())
	{
		bot->brushMsg(); 	
	}
}



/*陷阱回调*/
void trapThkCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Trap *trap;
	
	ev_timer_stop(loop,think);	
	
	trap = (Trap *)think->target;
	
	if(trap == NULL)
	{
		return;
	}	
	
	/*如果有预警*/
	if(trap->warning())
	{
		return;
	}
	
	
	/*攻击后便消失*/
	if(trap->calBack())
	{		
		ext_ev_timer_init(think,trapDispearCalBack,2,0,trap);

		ev_timer_start(loops,think);
		
		return;
	}	
	
	ext_ev_timer_init(think,trapThkCalBack,trap->getCdTme(),0,trap);

	ev_timer_start(loops,think);
	
}


/*陷阱消失回调函数*/
void trapDispearCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Trap *trap;
	
	ev_timer_stop(loop,think);	
	
	trap = (Trap *)think->target;
	
	if(trap == NULL)
	{
		return;
	}	
	
	/*消失*/
	if(trap->getIsDispear())
	{
		trap->disperMsg();		
		return;
	}
}



/*可摘取物品，消失以及重刷控制*/
void takeGoodsThkCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	TakeGoods *takeGoods;
	
	ev_timer_stop(loop,think);	
	
	takeGoods = (TakeGoods *)think->target;
	
	/*资源战里面的资源，则不需要再次刷出*/
	if(takeGoods == NULL || takeGoods->getIsCampSource())
	{
		return;
	}
		
	/*消失了，在刷出来*/
	if(!takeGoods->getBruOut())
	{
		takeGoods->brushMsg();	
	}
	
	else
	{
		/*会动的*/
		if(takeGoods->getIsMove())
		{
			takeGoods->calBack();
		
			ext_ev_timer_init(think,takeGoodsThkCalBack,4,0, takeGoods);

			ev_timer_start(loop,think);
		}		
	}	
	
}

/*陷阱示警回调函数*/
void trapWarnCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{		
	Trap *trap;
	
	ev_timer_stop(loop,think);	
	
	trap = (Trap *)think->target;
	
	
	if(trap == NULL)
	{
		return;
	}	
	
	/*攻击后便消失*/
	if(trap->calBack())
	{		
		trap->initTimerDispear();
		
		return;
	}		
	
	trap->initTimer();
}

