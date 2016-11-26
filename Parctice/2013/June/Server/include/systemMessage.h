#ifndef SYSTEM_MESSAGE_H
#define SYSTEM_MESSAGE_H

#define MSG_LEN 2000
#define systemSendMssage SYSTEM_MESSAGE::systemMssage
#define sendActivityMsg  SYSTEM_MESSAGE::systemActivityMsg

#include "my_timer.h"

class Hero;

//活动消息体结构
typedef struct systemMsg_S{
	char msg[MSG_LEN];
	int	times;
	int interval_time;
	int level;          //消息发送等级权限
	ev_timer *system_activity_timer;//安全时间定时器；
	void init(){
		memset(msg,0,MSG_LEN);
		times=0;
	}
	systemMsg_S(char*_msg,int time,int _interval_time,int _level = 1){
		memcpy(msg,_msg,MSG_LEN);
		times=time;	
		interval_time=_interval_time;
		system_activity_timer =NULL;
		level = _level;
	}
}systemMsg_T;

/**
	Type	0：系统；
			1：世界
			2: 阵营
			3：帮派、
			4：附近
			5：队伍
*/
class SYSTEM_MESSAGE{
public:
static void systemMssage(Hero*myHero,char* msg,int Type);

/**
	全区消息
*/
static void systemMssageAllEral(string& _msg,size_t level = 1);

/**
	全区活动提示消息
*/
static void systemActivityMsg(char *msg,int time,int _interval_time,int levelLimit = 1);

};

#endif /* LOGGER_H */