#ifndef GUILDCLUB_H
#define GUILDCLUB_H

#include<iostream>
#include"my_timer.h"
#include"guild.h"
#include"guild_club_assist.h"
#include"map_inform.h"
#include"command_other_function_all_over.h"

typedef struct GuildFeastConf_S
{
	char id[IDL + 1];			//宴席类型ID
	int cost;					//宴席花费元宝数
	int lastTime;				//宴席持续时间
	int contb;					//请宴者对帮派贡献度
	int hostMoney;				//请宴者获得金钱值
	int hostGlory;				//请宴者获得帮贡值
	int hostReputation;			//请宴者获得声望值
	int joinMoney;				//赴宴者获得金钱值
	int joinGlory;				//赴宴者获得帮贡值
	int joinReputation;			//赴宴者获得声望值
	GuildFeastConf_S(char* _id, int cst, int last, int ctb, int hm, int hg, int hr, int jm, int jg, int jr)
	{
		strncpy(id, _id, sizeof(id));
		cost = cst;
		lastTime = last;
		contb = ctb;
		hostMoney = hm;
		hostGlory = hg;
		hostReputation = hr;
		joinMoney = jm;
		joinGlory = jg;
		joinReputation = jr;
	}
}GuildFeastConf_T;
class Map_Inform;
class Guild;
class GuildClub
{
	private:
		char identity[50];
		char invitePerson[IDL + 1];							//邀请者
		set<string> invitedPerson;							//已经赴宴的玩家列表													
		ev_timer feastTimer;		
		char typeId[IDL + 1];			//宴席类型ID				
		int beginTime;				//开始时间
		int totalTime;					//总时间
		Map_Inform *mapNow;
		//宴席奖励
		int joinMoney;				//赴宴者获得金钱值
		int joinGlory;				//赴宴者获得帮贡值
		int joinReputation;			//赴宴者获得声望值
	public:
		// GuildClub(char* guildId, char* guildName, Map_Src *clubMap);
		GuildClub(void);
		// int enter(Hero *hero);
		// int exit(Hero *hero);
		
		void setIdentity(char *_identity);
		char *getIdentity(void);
		
		Map_Inform *getMap(void);
		void setMap(Map_Inform *_mapNow);
		//请客
		void treat(Hero *hero, char* typeId,Guild *guild,char *_identity);
		//赴宴
		void joinDinner(Hero *hero,Guild *guild);
		//盛宴结束
		void end_feast(void);
		//盛宴是否开始
		bool feastStart(void);
		//返回剩余时间
		int getRemainTime(void);
		//返回看盛宴的玩家
		char *getInvitePerson(void);
		//判断是不是这个盛宴
		bool isThisDish(char *_identity);
		//判断是否可以试用盛宴
		bool canEatDish(Hero *hero);
		//系统请客
		void sysTreat(Map_Inform *_mapNow,char* _typeId,Guild *guild);
		
		~GuildClub(void);
};
#endif