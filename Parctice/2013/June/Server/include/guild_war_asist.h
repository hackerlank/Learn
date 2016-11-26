/****************************************************************
 * Filename: guild_war_asist.h
 * 
 * Description: 帮战房间辅助类
 *
 * Original Author : bison, 2012-8-28
 *
 ****************************************************************/
#ifndef _GUILD_WAR_ASIST_H_
#define _GUILD_WAR_ASIST_H_

#include"guild_war_room.h"
#include<list>

#define MAX_GUILD_WAR_ROOM_NUM			50				//最大帮战房间数

class GuildWarAsist
{
private:
	map<string, GuildWarRoom*>	allGuildWarRooms;
	vector<GuildWarRoom*> idleGuildWarRooms;				//所有帮派战房间
	bool isInGuildWarTime;									//是否在帮战时间
	
public:
	//帮战房间的初始化
	GuildWarAsist();

	//帮主占领帮战房间主帮位置
	int hostHoldGuildWarRoom(Hero *manager, int mode, char* password = NULL);
	//帮主占领帮战房间客帮位置
	int guestHoldGuildWarRoom(Hero *manager, char* roomId, char* password = NULL);
	//帮众进入帮战房间
	int JoinGuildWar(Hero *hero, char* roomId);
	//帮派战伤害统计
	int hurtCount(Hero *hero, int value);
	//杀人数统计
	int killCount(Hero *hero);
	//查看帮战房间状态
	int viewRoomState(Hero *hero, char* result);
	//召唤加入
	void callJoinWar(Hero *hero);
	//房主准备
	int managerPrepare(Hero *hero);
	//帮派战退出
	void exitGuildWar(Hero *hero, bool offlineFlag);
	//释放一个房间资源
	void freeOneRoom(GuildWarRoom *room);
	//设置是否在帮战时间
	void setIsInGuildWarTime(bool start);
	//查看是否在帮派战房间中
	bool getIsInGuildWarTime();
	//查看玩家所在帮派战房间的状态
	int getOneRoomState(Hero* hero);
	//帮战复活
	int guildWarRevival(Hero* hero);
	//是否可以采集大旗
	int isHeroPickFlagOk(Hero *hero, int type);
	//停止采旗
	int stopPickFlag(Hero *hero, int type);
	//采旗结束
	int finishPickFlag(Hero *hero, int type);
};

#endif