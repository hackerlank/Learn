#ifndef __INSTANCING_MANAGE__
#define __INSTANCING_MANAGE__
#include <iostream>
#include<list>
#include "hero.h"
#include "data_structure_struct.h"
#include "TD_Instancing.h"
#include"libev.h"

//describe:初始化塔防副本管理类
void initInstManage();

//describe: 副本锁定时间到期后的回调函数
void cpyOutOfLockCB(struct ev_loop *loop, ev_timer *watcher, int revents);

typedef struct failure_member
{
	int 	failure_flag;				//申请进入副本失败代号（0：等级不够，1：次数已满，2：难度等级不够,）
	char 	nickName[IDL+1];			//相应角色的昵称	
}Failure_Member;

typedef struct _Failure_Reason
{
	int				size;
	Failure_Member	member[4];
}Failure_Reason;


class Instancing_manage{
	public:
		Instancing_manage();	
		TD_Instancing* id2tdRoom(string roomId);			//查找塔防副本的实例指针		
		
		//队长申请进入塔防副本，申请成功，则向队员发送挑战副本的邀请；否则向队长返回申请副本失败的原因
		int apply_td_inst(Hero* leader, char* td_inst_id);
		
		int enableEnter(Hero *myHero, char *inst_typeId);
		
		string gain_towerDefTeam_roomId(string inst_typeId);
		
		bool enter_inst_room(Hero *heroWillEnter,string tdRoom,int _index);		//玩家进入指定副本房间	
		int	 teamEnter(Team*);
		
		bool start_instancing(TD_Instancing* tdPtr);		//开启指定副本的定时器
		bool stop_instancing(TD_Instancing* tdPtr);			//关闭指定副本的定时器
		bool start_instancing(string);	//开启指定副本的定时器
		bool stop_instancing(string);	//关闭指定副本的定时器	
		
		bool exit_inst_room(Hero *heroWillQuit, TD_Instancing*);					//退出塔防副本；
		
	public:
		map<string, TD_Instancing*> instId2totalRooms;	//塔防副本实例
		list<TD_Instancing*> idleRooms;					//塔防副本空闲房间
};
#endif