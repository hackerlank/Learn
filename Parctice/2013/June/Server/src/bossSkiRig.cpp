/************************************************************
	文件名：bossSkiThk.cpp
	文件作用：实现Boss延时性技能：定身技能思考函数
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#include"bossSkiThk.h"
#include"rigidity.h"
#include"cpyAsist.h"
#include"unEnemy.h"
#include"timerContainer.h"
extern struct ev_loop *loops;

/*怪物延时性技能回调函数*/
void monSkiCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{	
	Rigidity *rig;
	
	ev_timer_stop(loop,think);
	rig = (Rigidity *)think->target;
	
	if(rig == NULL)
	{
		return;
	}
	if(!(rig->response()))
	{
		return;
	}	
	ext_ev_timer_init(think,monSkiCalBak,rig->getLastTme(),0,rig);
	ev_timer_start(loop,think);	
}


/*怪物延时性技能回调函数*/
void monSkiUnEnemyCalBack(struct ev_loop *loop,ev_timer *think,int revents)
{	
	UnEnemy *unEnemy;
	
	ev_timer_stop(loop,think);
	
	unEnemy = (UnEnemy *)think->target;
	
	if(unEnemy == NULL)
	{
		return;
	}
	
	unEnemy->recoverUnEnemySki();
}


/*怪物cd和播放时间回调函数*/
void monCdCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{	
	SkillBase *sklBase;
	double lenseconds;
	ev_timer_stop(loop,think);
	
	sklBase = (SkillBase *)think->target;
	
	if(sklBase == NULL)
	{
		return;
	}
	sklBase->setIsOverTme(true);
}




