#include"monster_other_action_function.h"
#include"map_inform.h"
#include"monsterBase.h"
#include"monsterPassivity.h"
#include"monsterBoss.h"
#include"monsterPatrol.h"
#include"game_fight_assist.h"
#include"data_structure_struct.h"
#include"command_other_function_all_over.h"
#include"command_return_define_data.h"
#include"command_other_function_user_manage.h"
#include"libev.h"
#include"timerContainer.h"
#include"monsterStatuary.h"
extern map<string,Map_Inform*>mapId_connect_map;
extern struct ev_loop *loops;
extern TimerContainer<MonsterBase*> *monThkContain;
void monThkCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{	
	LveCtnManger monLveMge;
	MonsterBase *mon = NULL;
	Map_Inform *map_now;
	ev_timer_stop(loop,think);
	
	mon = (MonsterBase *)think->target;
	if(mon == NULL)
	{
		return;
	}
	
	map_now = mon->getMap();
	if(map_now == NULL)
	{
		return;
	}
	
	monLveMge = mon->getLveMag();
	
	/*怪物死亡发送消失命令和数据重置*/
	if(!mon->getLifeStation())
	{
		mon->sendOutMsg();
		
		/*活动boss不在复活*/
		if(strcmp(mon->getType(),"ActiveBossMon") == 0)
		{			
			return;
		}
		
		/*副本复活，或者场景复活*/
		else if(monLveMge.isAliveAgin() || !map_now->getFlgCpy())
		{
			if(mon->getOwnerAttriType() == 3)
			{
				cout<<"monThkCalBak(struct ev_loop *loop,ev_timer *think,int revents) there:"<<mon->getIdentity()<<endl;
			}
			
			ext_ev_timer_init(think,monReLifeCalBak,monLveMge.durTme,0, mon);
			ev_timer_start(loop,think);
			return;
		}
		
		/*那些活够了得召唤怪*/
		else if(mon->getIsCallType())
		{
			mon->initMonsterALL();
		}
		
	}	
	else
	{	
		/*雕像怪物就不思考了*/
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{			
			return;
		}
		
		mon->response();
		ext_ev_timer_init(think,monThkCalBak,MONSTER_THINK_TIME,0, mon);
		ev_timer_start(loop,think);
	}
}


/*怪物复活*/
void monReLifeCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{	
	MonsterBase *mon;
	Map_Inform *map_now;
	LveCtnManger monLveMge;
	
	ev_timer_stop(loop,think);
	
	mon = (MonsterBase *)think->target;
	if(mon == NULL)
	{
		return;
	}
	
	map_now = mon->getMap();
	if(map_now == NULL)
	{
		return;
	}
	
	monLveMge = mon->getLveMag();	
		
	/*活动boss不在复活*/
	if(strcmp(mon->getType(),"ActiveBossMon") == 0)
	{			
		return;
	}
		
	/*副本复活，或者场景复活*/
	else if(monLveMge.isAliveAgin() || !map_now->getFlgCpy())
	{
		
		if(mon->getOwnerAttriType() == 3)
		{
			cout<<"monReLifeCalBak(struct ev_loop *loop,ev_timer *think,int revents) begin:"<<mon->getIdentity()<<endl;
			cout<<"getBshMsg:"<<mon->getBshMsg()<<endl;
			cout<<"monReLifeCalBak(struct ev_loop *loop,ev_timer *think,int revents) end:"<<mon->getIdentity()<<endl;
		}
	
		mon->initMonsterBaseAsist();					
		
		//任务怪就不在复活
		if(mon->getOwnerAttriType() == 3 || mon->getOwnerAttriType() == 4)
		{
			if(mon->getOwnerAttriType() == 3)
			{
				cout<<"monReLifeCalBak(struct ev_loop *loop,ev_timer *think,int revents) return:"<<mon->getIdentity()<<endl;
			}
			
			return;
		}
		
		
		/*非副本场景且召唤怪*/
		if(!map_now->getFlgCpy())
		{
			if(mon->getIsCallType())
			{
				return;
			}
		}
		else
		{
			/*副本没活够的召唤怪*/
			if(mon->getIsCallType())
			{
				mon->setIsCalled(true);
			}
		}
		
		
		
		/*雕像怪物初始化复活数据*/
		if(strcmp(mon->getType(),"MonStatuary") == 0)
		{			
			((MonsterStatuary*)mon)->setStatuaryAttrit();
		}
		
		mon->reLife();
	}
}



/*怪物回血*/
void monRecoverBooldCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{	
	MonsterBase *mon;
	
	ev_timer_stop(loop,think);
	
	mon = (MonsterBase *)think->target;
	
	if(!mon->getIsBloodTmeOpenFlg())
	{
		return;
	}
	else
	{
		/*一次回满*/
		mon->setLifeVal(mon->getLifeUpperVal());		
		mon->brushMon();
		
		if(mon->getOwnerAttriType() == 3)
		{
			cout<<"monRecoverBooldCalBak(struct ev_loop *loop,ev_timer *think,int revents) begin:"<<mon->getIdentity()<<endl;
			cout<<"getBshMsg:"<<mon->getBshMsg()<<endl;
			cout<<"monRecoverBooldCalBak(struct ev_loop *loop,ev_timer *think,int revents) end:"<<mon->getIdentity()<<endl;
		}
		
		mon->setIsBloodTmeOpenFlg(false);
	}
}


/*任务怪物回调函数*/
void monTaskCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{	
	MonsterBase *mon;
	
	ev_timer_stop(loop,think);
	
	mon = (MonsterBase *)think->target;
	
	if(mon == NULL)
	{
		return;
	}
	
	mon->taskMonCalBack();
}


/*怪物cd回调函数*/
void monCdCalBal(struct ev_loop *loop,ev_timer *think,int revents)
{	
	MonsterBase *mon;
	
	ev_timer_stop(loop,think);
	
	mon = (MonsterBase *)think->target;
	
	if(mon == NULL)
	{
		return;
	}
	
	mon->setIsCdCool(true);
}
