/****************************************************************
 * Filename: offline_unhandle_event.h
 * 
 * Description: 玩家离线期间未处理事件
 *
 * Original Author : bison, 2012-9-25
 *
 ****************************************************************/

#include<string>
#include<string.h>
#include<time.h>
#include<math.h>
#include "mail_systerm_interface.h"
#include "hero.h"
using namespace std;

#define UNHANDLE_HERO_EXP 			1			//未处理的玩家经验
#define UNHANDLE_BOUND_GAME_MONEY	2			//未处理的玩家绑定游戏币
#define UNHANDLE_GAME_MONEY			3			//未处理的非绑定游戏币
#define UNHANDLE_BOUND_GOLD			4			//未处理的绑定元宝
#define UNHANDLE_GOLD				5			//未处理的元宝
#define UNHANDLE_GUILD_EXP			6			//未处理的帮派经验
#define UNHANDLE_HERO_GLORY			7			//未处理的玩家帮贡
#define UNHANDLE_GOODS				8			//未处理的物品
#define UNHANDLE_LONG_MSG			9			//未处理的系统长消息

#define UNHANDLE_JOIN_GUILD			10			//加帮派未处理事件
#define UNHANDLE_EXIT_GUILD			11			//退出帮派的未处理事件
#define UNHANDLE_CHANGE_GUILD_TITLE	12			//未处理的帮派职位调整


//生成离线未处理事件的记录
#define UNHANDLE_FUNC(heroId, type, data) \
	MailSystermInterface::create_mail_data(heroId, type, (int)sizeof(data), (char*)&data)

//离线玩家未处理事件之物品类型
typedef struct UnhandleGoods_S {
	int type;				//消息类型
	char id[25];			//物品id
	int num;				//物品数量
	UnhandleGoods_S(int _type, char* _id, int _num)
	{
		type = _type;
		strncpy(id, _id, strlen(_id) + 1);
		num = _num;
	}
}UnhandleGoods_T;

//离线玩家未处理事件之属性加成类型
typedef struct UnhandleAttr_S {
	int type;				//消息类型
	int num;				//属性变化值
	UnhandleAttr_S(int _type, int _num)
	{
		type = _type;
		num = _num;
	}
}UnhandleAttr_T;

//离线玩家未处理事件之长消息类型
typedef struct UnhandleMsg_S {
	int type;				//消息类型
	char msg[256];			//消息
	UnhandleMsg_S(int _type, char* _msg)
	{
		type = _type;
		strncpy(msg, _msg, strlen(_msg) + 1);
	}
}UnhandleMsg_T;

//离线玩家未处理事件之加入帮派类型
typedef struct UnhandleJoinGuild_S {
	int type;				//消息类型
	char guildName[51];			//消息
	UnhandleJoinGuild_S(int _type, char* name)
	{
		type = _type;
		strncpy(guildName, name, strlen(name) + 1);
	}
}UnhandleJoinGuild_T;


//离线玩家未处理事件之退出帮派类型
typedef struct UnhandleExitGuild_S {
	int type;				//消息类型
	UnhandleExitGuild_S(int _type)
	{
		type = _type;
	}
}UnhandleExitGuild_T;

//离线玩家未处理事件之帮派职务调整类型
typedef struct UnhandleChangeGuildTitle_S {
	int type;				//消息类型
	int num;				//属性变化值
	UnhandleChangeGuildTitle_S(int _type, int _num)
	{
		type = _type;
		num = _num;
	}
}UnhandleChangeGuildTitle_T;

//离线玩家未处理事件之加好友申请
typedef struct UnhandleFriendApply_S {
	char msg[200];			//消息
	UnhandleFriendApply_S(char* _msg)
	{
		int size = strlen(_msg) + 1;
		if(size >= 200)
			size = 199;
		strncpy(msg, _msg, size);
		msg[size]='\0';
	}
}UnhandleFriendApply_T;

//离线玩家未处理事件之删除好友
typedef struct UnhandleDelFriend_S {
	char heroId[200];			//消息	//操作好友的ID；
	UnhandleDelFriend_S(char* _msg)
	{
		int size = strlen(_msg) + 1;
		if(size >= 200)
			size = 199;
		strncpy(heroId, _msg, size);
		heroId[size]='\0';
	}
}UnhandleDelFriend_T;

//离线玩家未处理事件之增加好友
typedef struct UnhandleAddFriend_S {
	char heroId[200];				//操作好友的ID；
	FriendInfo_T myFriend;			//好友信息；
	UnhandleAddFriend_S(char* _msg,FriendInfo_T _myFriend)
	{
		int size = strlen(_msg) + 1;
		if(size >= 200)
			size = 199;
		strncpy(heroId,_msg,size);
		heroId[size]='\0';
		myFriend=_myFriend;
	}
}UnhandleAddFriend_T;

//主类型为5时,玩家属性相关的未处理事件
void deal_unhandle_attr_event(char* heroId, char* data);

//主类型为6时,玩家物品奖励的未处理事件处理
void deal_unhandle_goods_event(char* heroId, char* data);

//主类型为7时,玩家一个完整未处理事件对应的消息的处理
void deal_unhandle_msg_event(char* heroId, char* data);

//主类型为8时，玩家加入帮派的未处理事件处理
void deal_unhandle_join_guild_event(char* heroId, char* data);

//主类型为9时,玩家一个完整未处理事件好友申请
void deal_unhandle_friend_apply_event(string heroId, char* data);

//主类型为10时,玩家一个完整未处理事件好友删除
void deal_unhandle_del_friend_event(string heroId, char* data);

//主类型为11时,玩家一个完整未处理事件好友添加
void deal_unhandle_add_friend_event(string heroId, char* data);
