#ifndef CAMP_WAR_MANAGEMENT_H
#define CAMP_WAR_MANAGEMENT_H


#include <map>
#include <string>
#include <vector>
#include <sys/time.h>

#include "chiefCampWar.h"
#include "leaderCampWar.h"
#include "ordinaryCampWar.h"
#include "camp_res_war.h"

#define ROOM_OF_CHIEF_CAMP_WAR 1
#define ROOM_OF_LEADEER_CAMP_WAR 3
#define ROOM_OF_ORDINARY_CAMP_WAR 5
#define ROOM_OF_CAMP_RES_WAR		8
#define ROOM_NUM_BEFORE_CAMP_RES_WAR (ROOM_OF_CHIEF_CAMP_WAR + ROOM_OF_LEADEER_CAMP_WAR + ROOM_OF_ORDINARY_CAMP_WAR)


#define LOW_GUILD_LEVEL 1
#define LOW_GUILD_COUNTS 5
#define MAX_BROADCAST_LEN 512//最大阵营消息；
#define LOW_ENTER_CAMP_WAR_LEVEL 30	//最低等级；
#define ORD_CAMP_WAR_TITLE_COUNTS 3

#define MAX_GUILD_NAME 252//最大报名252个；
#define MAX_GUILD_NAME_LEN 30//最大帮派名字长度；

#define HeroId_Rank(a,b) ( map<string,int>::value_type( (a),(b)) )

class Hero;
class Map_Src;

/**
	统领争夺战数据结构；
*/
typedef struct LeaderCampInfo_S{	

	char leaderName[HERO_MAME_LEN];//统领的帮主名字；
	char leaderHeroId[HERO_ID_LEN+1];//统领的帮主Id；
	
	char viceLeaderName[HERO_MAME_LEN];//副统领名字；
	char viceLeaderHeroId[HERO_ID_LEN+1];//副统领的Id;
	
	char leaderBroadcast[MAX_BROADCAST_LEN];//阵营公告；
	char leaderCampWarFactionName[HERO_MAME_LEN];//统领的帮派名字；
	
	// LeaderCampInfo_S(){
		// memset(leaderName,0,HERO_MAME_LEN);//统领的帮主名字；
		// memcpy(leaderName,"-1",strlen("-1"));
		// memset(leaderHeroId,0,HERO_ID_LEN+1);//统领的帮主Id；
		// memcpy(leaderHeroId,"-1",strlen("-1"));
	
		// memset(viceLeaderName,0,HERO_MAME_LEN);//副统领名字；
		// memcpy(viceLeaderName,"-1",strlen("-1"));
		// memset(viceLeaderHeroId,0,HERO_ID_LEN+1);//副统领的Id;
		// memcpy(viceLeaderHeroId,"-1",strlen("-1"));
		
		// memset(leaderBroadcast,0,MAX_BROADCAST_LEN);//阵营公告；
		// memcpy(leaderBroadcast,"-1",strlen("-1"));
		// memset(leaderCampWarFactionName,0,HERO_ID_LEN+1);//统领的帮派id；
		// memcpy(leaderCampWarFactionName,"-1",strlen("-1"));		
	// }
	
}LeaderCampInfo_T;


/**
	盟主争夺战数据结构；
*/
typedef struct ChieferCampInfo_S{	

	char chiefer[HERO_MAME_LEN];//武林盟主名字；
	char chieferId[HERO_ID_LEN+1];//武林盟主ID；
	char chiefCampWarName[HERO_MAME_LEN];//盟主的帮派名字；	
}ChieferCampInfo_T;


/**
	阵营信息；
*/
typedef struct CampInfo_S{	

	ChieferCampInfo_T chieferCampInfo;//盟主信息；
	LeaderCampInfo_T leaderCampInfo[ROOM_OF_LEADEER_CAMP_WAR];//统领阵营信息；
	char ordWarWinnerHeroId[ORD_CAMP_WAR_TITLE_COUNTS][HERO_ID_LEN+1];//武神，武圣，武尊角色ID；
}CampInfo_T;

typedef struct Leader_Apply_Info_S{	
	char mizong_app_guildName[MAX_GUILD_NAME][MAX_GUILD_NAME_LEN];//密宗申请列表；
	char xiejiao_app_guildName[MAX_GUILD_NAME][MAX_GUILD_NAME_LEN];	//邪教申请列表；
	char youxia_app_guildName[MAX_GUILD_NAME][MAX_GUILD_NAME_LEN];//游侠申请列表；
	char mizong_guildName[MAX_GUILD_NAME_LEN];//当前参加密宗门派；
	char xiejiao_guildName[MAX_GUILD_NAME_LEN];//当前参加邪教门派；
	char youxia_guildName[MAX_GUILD_NAME_LEN];//当前参加游侠门派；
	
	void init()
	{
		memset(mizong_app_guildName,0,sizeof(mizong_app_guildName));
		memset(xiejiao_app_guildName,0,sizeof(xiejiao_app_guildName));
		memset(youxia_app_guildName,0,sizeof(youxia_app_guildName));
		memset(mizong_guildName,0,sizeof(mizong_guildName));
		memset(xiejiao_guildName,0,sizeof(xiejiao_guildName));
		memset(youxia_guildName,0,sizeof(youxia_guildName));
	}
}Leader_Apply_Info_T;

class campWarManagement{

public:
	/**
		构造函数；
	*/
	campWarManagement();
	
	
	/**
		析构函数；
	*/
	~campWarManagement();
	

	/*******************************************************************
	****************************普通阵营战接口**************************
	********************************************************************/
	
	/**
		argument void
		  return bool 初始化成功 true;
					  失败 false;
		function 初始化所有的普通阵营战数据；
	*/
	bool initOrdinaryCampWar(void);			
	
	
	/**
		argument  void
		  return  bool true 成功；
				       false 失败；
		function  普通阵营战结束处理；
	*/
	bool finishOrdinaryCampWar(void);

	
	/**
	argument  _startTime 普通阵营战开始时间；
	  return  bool true 触发成功；
			  false 触发失败，正在进行普通阵营战，不能再触发；
	 function 开启普通阵营战；
	*/	
	bool startOrdinaryCampWar(time_t _startTime);				
	
	
	/**
	argument: string heroId,英雄Id；
			  int index,房间号；
	 return:int	-1:该英雄id不存在；
				-2:表示阵营战已饱和，达到最大允许人数；
				-3:表示插入insert失败；
				-4:英雄实例的阵营不属于系统三个阵营之内；
				-5:英雄ID等级小于30级；
				-6:表示该阵营战人数已满或者未激活；
				-7:阵营战偏移量选择房间数不在系统默认范围内或者参数heroId为空；
				-8:地图信息找不到；
				-9:删除时，在此次阵营战中，在其阵营队列中找不到；
			   -10:表示加入的时间不在活动的时间；
				 0:表示加入成功；	
	 function: 添加heroId到相应的普通阵营战；		 
	*/
	int add2OrdinaryCampWar(string heroId,int index); 
	

	/**
	argument:	heroId,英雄Id；
				int    index,房间号；
				int    _droppedFlg,是否是阵营战中下线（0不是，1是）；
	return:  	int -1:没有加入阵营；
				-2:没有加入到普通阵营战；
				-3:该英雄id不存在；
				-4:英雄ID等级小于30级；	
				-5:参数退出的index不在默认的房间号内；
				-6：参数heroId为空；
				 0:表示删除表示成功；	
	 function:  退出普通阵营战处理；
	*/	
	int exitFromOrdinayCampWar(string heroId,int index,int _droppedFlg=0);
	
	
	/**
		argument void
		  return int 普通阵营战剩余的秒数；
		function 获取普通阵营战剩余时间；
	*/
	int getOrdinaryCampWarOverTime(void);	

	
	/**
		argument void
		return string 普通阵营战房间的人数字符串表示形式，中间用逗号隔开；
		function 获取普通阵营战房间状态；
	*/	
	string getOrdinaryCampWarStatus(void);	
	
	
	/**
	argument:	myHero,英雄实例；
				index，当前查看的参见阵营战的房间号；
	  return: 	string retValue(type,int,int,string)
				type:阵营战类型；
				int:金钱;
				int:声望;
				string：物品奖励ID；
				int:0无头衔，1武神，2武圣，3武尊
	 function:  查看奖励设置；		
	*/
	void  viewOrdinaryCampWarAwards(Hero* myHero,int index);	
	
	
	/**
	argument:	myHero,英雄实例；
				index，当前查看的参见阵营战的房间号；
	  return：	int -1 实例英雄指针为空
					-2 不属于系统默认阵营类型；
					-3 在此房间没有找到英雄战斗痕迹；
					-4 给背包装东西失败；
					-5 读取参加过的阵营房间号错误，不在系统默认范围；
					 0 表示成功；
	function:   领取奖励；
	*/
	int receiveOrdinaryCampWarAwards(Hero* myHero,int index); 	

	
	/**
	argument:	Hero* myHero角色英雄；
	return：  	int 0是掉线进入，数据恢复成功；
					1不是掉线进入；
	function:   掉线重新进入处理；
	*/	
	int droppedEnt(Hero* myHero);
	
	
	
	/*****************************************************************
	****************************统领战接口****************************
	******************************************************************/
	/**
	argument:	void
	  return：  bool true 开启成功；
					false 开启失败；
	function:   开启PK模式；
	*/
	bool startLeaderCampWarPK();
	
	
	/**
	argument:	void
	  return：  bool true 初始化成功；
					false 初始化失败；
	function:   初始化统领争夺战数据；
	*/
	bool initLeaderCampWar(void);	
	
	
	/**
	argument:	string _factionName当前完成胜利的帮派名字
				int index当前完成作战的下标；
	  return：  bool true 完成设置结果成功；
					 false 完成设置结果失败；
	function:   结束统领争夺战，保存结果数据；
	*/
	bool finishLeaderCampWar(string _factionName,int _index);
	
	
	/**
	argument hero 英雄实例指针；
	return int -1：实例指针为空；
			   -2：表示实例指针对应对象的帮派名字不是当前作战的帮派名字；
			   -3：表示insert失败，已经参加过，不能参加；
			   -4: 表示阵营类型不是系统默认类型；
			   -5: 表示找不到地图；
			   -6: 表示时间不是最站时间；
			    0：表示成功；		
	function 加入统领争夺战；
	*/
	int add2LeaderCampWar(string heroId);
	
	
	/**
	argument:	heroId,英雄Id；
	return: 	int -1:heroId不存在；
					-2:帮派名字不是系统正在作战的帮派；
					-3:在阵营统领战中找不到英雄ID；
					-4：找不到阵营；
					 0:删除成功；	
	 function:  退出统领阵营战处理；
	*/	
	int exitFromLeaderCampWar(string heroId);	
	
	
	/**
	    argument index当前的阵营下标
		  return int 阵营战剩余的秒数；
		function 获取阵营战剩余时间；
	*/
	int getLeaderCampWarOverTime(int _index);	
	
	
	/**
		argument void
		return string 阵营战房间的人数字符串表示形式，中间用逗号隔开；
		function 获取阵营战房间状态；
	*/	
	string getLeaderCampWarStatus(void);
	
	
	/**
	argument  _startTime 阵营战开始时间；
	  return  bool true 触发成功；
			  false 触发失败，正在进行阵营战，不能再触发；
	 function 开启阵营战；
	*/	
	bool startLeaderCampWar(time_t _startTime);					//开启统领阵营战；
	
	
	/**
	argument:	myHero,英雄实例；
	return:  	
				消息内型
				string retValue(type,int,int,int,int,int)
				type:阵营战类型；
				int:帮派经验;
				int:个人金钱;
				int:帮派贡献;
				int:声望;				
				int:0无头衔，1统领
	 function:  查看奖励设置；		
	*/
	void viewLeaderCampWarAwards(Hero* myHero);				//查看奖励设置；
	
	
	/**
	argument:	myHero,英雄实例；
	  return：  int -1 实例英雄指针为空
					-2 不是当前作战帮派；
					-3 在此房间没有找到英雄战斗痕迹；
					-4 在此房间没有排名；
					-5 阵营类型错误；
					0 表示成功；
		function:  领取奖励；
	*/
	int receiveLeaderCampWarAwards(Hero* myHero); 				//领取奖励；
	
	
	/**
	argument:	pg_hero,英雄实例；
	  return：  int 1 位置1复活
					2 位置2复活
					0 位置0复活
	function:  获取统领战中，复活点的位置；
	*/	
	int getRevivalPt(Hero* pg_hero);
	
	
	/**
		argument void
		return time_t 当前和平剩余时间。
	*/
	time_t LeaderCampWarPeaceTime(); 								//和平剩余时间
	
	
	/*****************************************************************
	********************统领战申请报名接口****************************
	******************************************************************/
	/**
	argument:	void
	  return：  bool true 完成设置结果成功；
					false 完成设置结果失败；
	function:   结束统领争夺战报名，帅选保存结果数据；
	*/
	bool finishApplyLeaderCampWar(void);
	
	
	/**
	argument:	heroId,英雄实例Id；
	  return：  -1,英雄id错误
				-2,未加入帮派；
				-3，不是帮主或者副帮主
				-4，帮派等级没有在3级以上
				-5，帮派人数没有在15人以上
				-6，已经报过名；
				-7,不在指定时间报名；
	 function:  申请统领战报名；
	*/
	int  applyLeaderCampWar(string heroId);
	
	
	/**
	argument:	void
	  return：  bool true 开启成功；
					false 开启失败；
	function:  开启统领阵营战报名；
	*/
	bool startApplyLeaderCampWar(time_t _startTime);			//开启统领阵营战报名；

	
    /************************************************************************
	********************盟主战用到的接口*************************************
	*************************************************************************/
	/**
	argument:	void
	  return：  bool true 开启成功；
					false 开启失败；
	function:   开启PK模式；
	*/
	bool startChiefCampWarPK();
	
	
	/**
	argument:	factionName 赢家名字；
	  return：  bool true 完成设置结果成功；
					false 完成设置结果失败；
	function:   结束盟主夺战，保存结果数据；
	*/
	bool finishChiefCampWar(string&factionName);
	
	/**
	argument hero 英雄id;
	return int -1 hero为空；
			 -2 帮派名字不是当前盟主战的帮派；
			 -3 insert失败，已经参加过比赛；
			 -4 阵营类型不是系统默认三种类型；
			 -5 找不到地图的实例指针；
			  0 加入成功；
	function：参加加入盟主争夺战；
	*/
	int add2ChiefCampWar(string heroId);
	

	/**
	argument:	heroId,英雄Id；
	return: 	int -1 hero为空；
					-2 帮派名字不是当前盟主战的帮派；
					-3 找不到要删除掉的角色ID；
					-4：找不到阵营；
					 0:删除成功；	
	 function:  退出盟主阵营战处理；
	*/	
	int exitFromChiefCampWar(string heroId);
	
	
	/**
	    argument void
		  return int 阵营战剩余的秒数；
		function 获取阵营战剩余时间；
	*/	
	int getChiefCampWarOverTime(void);	
	
	
	/**
		argument void
		return string 阵营战房间的人数字符串表示形式，中间用逗号隔开；
		function 获取阵营战房间状态；
	*/	
	string getChiefCampWarStatus(void);
	
	
	/**
	argument:	void
	  return：  bool true 开启成功；
					false 开启失败；
	function:  开启盟主阵营战；
	*/	
	bool startChiefCampWar(time_t _startTime);					//开启盟主阵营战；	
	
	
	/**
	argument:	myHero,英雄实例；
	return:  	
				消息内容：
				string retValue(type,int,int,int,int,int)
				type:阵营战类型；
				int:帮派经验;
				int:个人金钱;
				int:帮派贡献;
				int:声望;				
				int:0无头衔，1盟主
	 function:  查看奖励设置；		
	*/	
	void  viewChiefCampWarAwards(Hero* myHero);				//查看奖励设置；
	
	
	/**
	argument:	myHero,英雄实例；
	  return：  int -1 实例英雄指针为空
					-2 不是当前作战帮派；
					-3 在此房间没有找到英雄战斗痕迹；
					-4 在此房间没有排名；
					-5 阵营类型错误；
					0 表示成功；
		function:  领取奖励；
	*/	
	int receiveChiefCampWarAwards(Hero* myHero); 				//领取奖励；
	
		
	/**
		argument void
		return time_t 当前和平剩余时间。
	*/
	time_t ChiefCampWarPeaceTime(); 								//和平剩余时间
	
	
	/*******************************************************************************
	 *********************************阵营资源战************************************
	 *******************************************************************************/
	
	/**
	 * function 初始化阵营资源战数据；
	 * argument void
	 * return	bool true:初始化成功;
	  				 false:失败;
	 */
	bool initCampResWar(void);			
	
	
	/**
	 * function 阵营资源战结束处理；
	 * argument void
	 * return	bool true 成功；
	 				false 失败；
	 */
	bool finishCampResWar(void);

	
	/**
	 * function 开启阵营资源战；
	 * argument  _startTime 阵营资源战开始时间；
	 * return  bool true 触发成功；
					false 触发失败，正在进行阵营资源战，不能再触发；
	 *
	 */	
	bool startCampResWar(time_t _startTime);				
	
	
	/**
	 * function: 将角色加到阵营资源战；	
	 * argument: Hero* hero,申请参加阵营资源战的角色；
	  			 int index,房间号；
	 * return:int	-1:该英雄id不存在；
				-2:表示阵营战已饱和，达到最大允许人数；
				-3:表示插入insert失败；
				-4:英雄实例的阵营不属于系统三个阵营之内；
				-5:英雄ID等级小于30级；
				-6:表示该阵营战人数已满或者未激活；
				-7:阵营战偏移量选择房间数不在系统默认范围内或者参数heroId为空；
				-8:地图信息找不到；
				-9:删除时，在此次阵营战中，在其阵营队列中找不到；
			   -10:表示加入的时间不在活动的时间；
				 0:表示加入成功；		 
	*/
	int entCampResWar(Hero* hero, int index); 
	

	/**
	argument:	Hero*	hero要离开房间的英雄；
				int    index,房间号；
				int    _droppedFlg,是否是阵营战中下线（0不是，1是）；
	return:  	int -1:没有加入阵营；
				-2:没有加入到普通阵营战；
				-3:该英雄id不存在；
				-4:英雄ID等级小于30级；	
				-5:参数退出的index不在默认的房间号内；
				-6：参数heroId为空；
				 0:表示删除表示成功；	
	 function:  退出普通阵营战处理；
	*/	
	int exitCampResWar(Hero* hero);
	
	int campResWarCollect(Hero* hero);
	
	int campResWarKill(Hero *atker, Hero* atked);
	
	//阵营资源战复活
	int campResWarRevival(Hero* hero);
	
	//设置在阵营资源战时间
	void setInCampResWarTime(bool flag);
	
	int viewHeroResNum(Hero* hero, char* heroId);
	
	int getCampResWarReward(Hero* hero);
	/**
		argument void
		  return int 普通阵营战剩余的秒数；
		function 获取普通阵营战剩余时间；
	*/
	int getCampResWarOverTime(void);	
	
		
	/**
	 * function:	获取阵营资源战房间数据	
	 * argument:	result:返回消息字符串
	 * return:		0:返回成功；非0：失败原因
	 */
	int getCampResWarStatus(Hero* hero, char *result);
	
	
	
	/**
	argument:	myHero,英雄实例；
				index，当前查看的参见阵营战的房间号；
	  return: 	string retValue(type,int,int,string)
				type:阵营战类型；
				int:金钱;
				int:声望;
				string：物品奖励ID；
				int:0无头衔，1武神，2武圣，3武尊
	 function:  查看奖励设置；		
	*/
	void  viewCampResWarAwards(Hero* myHero,int index);	
	
	
	/**
	argument:	myHero,英雄实例；
				index，当前查看的参见阵营战的房间号；
	  return：	int -1 实例英雄指针为空
					-2 不属于系统默认阵营类型；
					-3 在此房间没有找到英雄战斗痕迹；
					-4 给背包装东西失败；
					-5 读取参加过的阵营房间号错误，不在系统默认范围；
					 0 表示成功；
	function:   领取奖励；
	*/
	int receiveCampResWarAwards(Hero* myHero,int index); 	

	
	
	
	/*****************************************************************
	**********************管理公共接口********************************
	******************************************************************/
	/**
	argument void；
	  return void；
	function 从缓存获取数据；
	*/
	void gainInfoFromMem(void);
	
	/**
	argument void；
	  return void；
	function 存数据到缓存；
	*/	
	void setInfo2Mem(void);
	
	/**
	argument void；
	  return void；
	function 存报名数据到缓存；
	*/		
	void setAppInfo2Mem(void);
	
	/**
	argument  void；
	 return	 void；
	function 显示当前阵营数据
	*/
	void showCampInfo(void);
	
	
	/**
	argument myHero 英雄实例；
	return int -1:表示找不到英雄实例；
			 -2:表示该英雄的阵营阵营类型错误；
			 -3:表示该英雄的阵营阵营战类型错误；
	*/
	int addKillsInCampWar(Hero *myHero);
	
	
	/**
	argument myHero 英雄实例；
	return int -1:表示找不到英雄实例；
			 -2:表示该英雄的阵营阵营类型错误；
			 -3:表示该英雄的阵营阵营战类型错误；
			 -4 帮派名字不是当前盟主战的帮派；
			 >0 死亡次数；
	*/
	int addDeathInCampWar(Hero  *myHero);
	
	
	/**
	argument _index 阵营下标；
	return char* 信息列表；
	*/	
	char* get_apply_camp_war_info(int _index);
	
	/**
	argument：_OrdinaryCampWarLastTime 		普通阵营战持续时间；
			  _leaderCampWarLastTime		统领争夺战持续时间；
			  _ApplyLeaderCampWarLastTime	统领战报名持续时间；
			  _ChiefCampWarLastTime			盟主争夺战持续时间；
			  _peaceTime					阵营战和平模式时间(普通阵营战没有和平时间)；
	 return:  void
	*/
	void initCampWarInfo(time_t _OrdinaryCampWarLastTime,time_t _leaderCampWarLastTime,\
									time_t _ApplyLeaderCampWarLastTime,time_t _ChiefCampWarLastTime,time_t _LpeaceTime,time_t _CpeaceTime);
	
	
	/**
	argument：Hero* myHero 英雄实例指针；
	return:   int   -1: myHero==NULL,对象指针为空;
					-2:	英雄实例的阵营不属于系统三个阵营之内；
					0：在阵营tribes（正派）里面。
					1：在阵营religion（邪派）里面。
					2：在阵营ranger（游侠）里面。
	*/
	int findCampType(Hero* myhero);
	
	
	
	/**
	argument myHero 英雄实例指针；
	return int -1:表示找不到返回地图实例指针；
				-2:表示实例指针和地图指针为空；
				0：表示成功切换；
	*/
	int exitCampWarSence(Hero* myHero);
	
	
	/**
	argument myHero 英雄实例指针；
	return int -1:表示找不到返回地图实例指针；
			   -2:表示实例指针和地图指针为空；
			    0：表示成功切换；
	*/
	int enterCampWarSence(Hero* myHero,Map_Inform *mapDest);
	
	
	/**
	return int 武林盟主所在的帮派的阵营类型 
	 for 史哲轩--->福利需要接口；
	*/
	int getCheifFactionName(void);
	
	
	/**
	argument _index 英雄实例所在的阵营；
	return string 该阵营的统领所在的帮派的名字；
 	 for 史哲轩--->福利需要接口； 
	*/
	string getLeaderFactionName(int _index);
	
	/**
		统领报名战剩余时间；
	*/
	int CampWarApplyLastTime();
	
	/**
		更新统领信息；
	*/	
	bool updateLeaderInfo(Hero* myHero);
	
	
	/*********************************************************************
	**********************阵营信息****************************************
	**********************************************************************/
	/**
	argument: void
	  return: void
	function: 将统领和副统领数据更新到campInfo变量里面；
	*/
	void setCampInfo();							//设置阵营信息；
	
	
	/**
	argument: myHero 查看阵营信息的实例指针；
	  return: char* 阵营类型信息；
	*/
	char* viewCampInfo(Hero* myHero);			//查看阵营信息；
	
	
	/**
	argument: myHero 查看阵营信息的实例指针；
	  return: char* 所在阵营的帮派列表信息；
	*/	
	char*  viewCampFactionInfo(Hero* myHero);
	
	/**
		argument：myHero 设置公告的英雄实例，要求是当前阵营的统领；
				  broadcastCampInfo 公告内容；
		  return: int 1 实例指针为空；
					2 不是统领，不能设置；
					0 设置成功；
	*/
	int setCampBroadcast(Hero* myHero,char* broadcastCampInfo);
	
	
	/**
	*	argument：myHero 设置副统领的英雄实例，要求是当前阵营的统领；
				  _viceLeaderName 被设置成副统领的角色名；
		  return: int 1 实例指针为空；
			      2 统领没有找到阵营；
				  0 设置成功；
	*/
	int setViceLeaderName(Hero* myHero,string viceLeaderName,string _viceLeaderId);
	
	
	/**
		argument：myHero 撤销副统领的英雄实例，要求是当前阵营的统领；
				  _viceLeaderName 被撤销副统领的角色名；
		  return: int 1 实例指针为空；
			      2 统领没有找到阵营；
				  0 设置成功；
	*/	
	int cancelViceLeaderName(Hero* myHero,string viceLeaderName,string _viceLeaderId);
	

	/**
		argument：Hero* myHero
		  return: 是武神，不是武神；
	*/			
	bool isFukatsu(Hero* myHero);	
	
	/**
		argument：Hero* myHero
		  return: 是武圣，不是武圣；
	*/			
	bool isTakefu(Hero* myHero);	
	
	/**
		argument：Hero* myHero
		  return: 是武尊，不是武尊；
	*/			
	bool isTakeru(Hero* myHero);	
	
	/**
		argument：_camp 当前查询的角色阵营；
		  return: 是该阵营统领，不是该阵营统领；
	*/		
	bool isCampLeader(Hero* myHero,int _camp);
	
	
	/**
		argument：Hero* myHero
		  return: 是武林盟主，不是武林盟主；
	*/			
	bool isCampChief(Hero* myHero);
	
	
	/**
		argument Hero* myHero
		  return: void
	*/
	void initCampTitle(Hero* myHero);
	
private:	
/*普通阵营战数据*/	
	map<string,int>OrdinaryCampWarRank;//普通阵营战排名；
	OrdinaryCampWar OrdCampWar[ROOM_OF_ORDINARY_CAMP_WAR];//阵营欢乐斗，一共ROOM_OF_ORDINARY_CAMP_WAR房间;
	map<string,CampData_T> droppedHeroInfo;//普通阵营战中角色下线容器；
	
	time_t OrdinaryCampWarEndTime;//普通阵营战结束时间；
	time_t OrdinaryCampWarLastTime;	//普通阵营战持续时间；
	time_t OrdinaryCampWarStartTime;//普通阵营战开始时间；
	
/*阵营资源战数据*/	
	map<string,int>campResWarRank;//阵营资源战排名；
	CampResWar campResWarGroup[ROOM_OF_ORDINARY_CAMP_WAR];//阵营资源战，一共ROOM_OF_ORDINARY_CAMP_WAR房间;
	// map<string,CampData_T> droppedHeroInfo;//阵营资源战中角色下线容器；
	
	bool isInCampResWarTime;					//是否在活动时间
	time_t campResWarEndTime;				//阵营资源战结束时间；
	time_t campResWarLastTime;				//阵营资源战持续时间；
	time_t campResWarStartTime;				//阵营资源战开始时间；
		
/*统领战数据*/
	LeaderCampWar leaderCampWar[ROOM_OF_LEADEER_CAMP_WAR];

	time_t Lpeace_time;//作战开始和平时间；aceTime;
	time_t Lpeace_time_start;
	time_t Lpeace_time_end;		
	time_t LeaderCampWarLastTime;
	
	time_t ApplyLeaderCampWarEndTime;
	time_t ApplyLeaderCampWarLastTime;
	time_t ApplyLeaderCampWarStartTime;


/*盟主战数据*/
	ChiefCampWar chiefCampWar;
	time_t ChiefCampWarEndTime;//盟主阵营战结束时间；
	time_t ChiefCampWarLastTime;
	time_t ChiefCampWarStartTime;//盟主阵营战开始时间
	
	time_t Cpeace_time;//作战开始和平时间；aceTime;
	time_t Cpeace_time_start;
	time_t Cpeace_time_end;		


/*公共数据*/
	string campWarManagementId;	
	vector<Map_Src *>mapInfoVector;
	
	CampInfo_T currCampInfo;//当前阵营信息；															
	string campInfo;//阵营信息；
	string campInfoKey;//阵营数据键值；
	
	Leader_Apply_Info_T leaderCampWar_app_info;//统领战报名数据结构；
	int		app_guild_size[ROOM_OF_LEADEER_CAMP_WAR];
	string app_info_key;
};

#endif