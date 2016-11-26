/****************************************************************
 * Filename: guild_asist.h
 * 
 * Description: 帮派功能补充
 *
 * Original Author : bison, 2012-8-13
 *
 ****************************************************************/
#ifndef _GUILD_ASIST_H_
#define _GUILD_ASIST_H_

#include"guild.h"
#include"hero.h"
#include "guild_club.h"	


//排名项
typedef pair<string, Guild*> GuildSortItem;

//得到副帮主ID
char* getGuildVicePresidId(char* guildName);

//得到帮主ID
char* getGuildPresidId(char* guildName);

//帮派名字得到排名；
int getGuildRankInCamp(char* guildId, int camp = 3);

//创建帮会 
int createGuild(Hero *hero, char* name, int mode, int index = 0);

//申请加入帮会
int applyJoinGuild(Hero *hero, char* guildName);

//同意单人加入帮会
int agreeOneJoinGuild(Hero *manager, char* heroId);
//同意所有申请者加入帮会
int agreeAllApply(Hero *manager, char* result);
//不同意加入帮会
bool disagreeJoinGuild(Hero *manager, int mode, char* heroId = NULL);

//玩家退出帮会
bool exitGuild(Hero *hero);
//驱逐出帮会
int driveOutGuild(Hero *manager, char* heroId);

//任命
bool appointGuildTitle(Hero *manager, char* heroId);
//免职
bool deposeGuildTitle(Hero *manager, char* heroId);
//辞职
bool resignGuildTitle(Hero *manager);
//让贤
bool demiseGuildTitle(Hero *manager, char* heroId);

//贡献度排名
void guildRank(int mode);
//查看自身帮派的福利
int viewRankGuildRewardInfo(Hero *hero, int mode, char *result);
//获取帮派福利，mode=0:领取昨日排名福利；mode = 1:领取上周排名福利
bool getGuildRankReward(Hero *hero, int mode);
//获取帮派任务奖励，index：帮派任务下标
int getGuildTaskReward(Hero *hero, char* taskId, char *result, float rewardTimes);
//获取签到奖励,mode表明签到时是否使用道具
int getGuildSignReaward(Hero *hero, int mode, int *err, char *result);
//捐游戏币
int donateMoneyToGuild(Hero *hero, int val, char *result);
//捐帮贡
int donateGloryToGuild(Hero *hero, int val, char *result);

//升级帮会
int upgradeGuild(Hero *manager);

//开启第index + 1个帮派技能
int openGuildSkill(Hero *manager, int index);
//升级第index+1个帮派技能
int upgradeGuildSkill(Hero *hero, int index);
//查看玩家对应的帮派技能信息
int viewGuildSkillInfo(Hero *hero, char *result);

//帮派总排名
void allGuildRank();
#if 0			//策划说分项排名先不要
//按帮派等级排名
void guildRankByLevel();
//按帮派当前经验排名，这项估计没多大用，除非经验不减
void guildRankByExp();
//按帮派帮贡排名
void guildRankByGlory();
//按帮派资金排名
void guildRankByMoney();
//按帮派人数排名
void guildRankByMembsNum();
#endif

//查看第page页的排名信息
int viewGuildRankInfo(int page, int camp, char *result);
//搜索某个帮派
int searchOneGuild(char* guildName, int camp, char *result);
//查看自己帮派信息
int viewMyGuildInfo(Hero *hero, char *result);
//查看某个帮派信息
int viewOneGuildInfo(char* guildName, char *result);

//更改帮会公告
int changeNotices(Hero *manager, char* newNotices, int flag = 0);
//查看帮派历史记录
int viewGuildHistory(Hero *hero, int page, char *result);
//查看帮派成员信息
int viewGuildMembsList(Hero *hero, char *result);
//查看申请成员列表
int viewGuildApplyList(Hero *hero, char *result);

//增加帮派经验
int addGuildExp(char* guildName, char* heroId, int expVal);
//增加个人帮贡
int addMyGuildGlory(char* guildName, char* heroId, int glory);

//查看帮派活动信息
int viewGuildActivity(Hero *hero, char *result);

//向申请帮派的玩家发送同意加入帮派或者被拒绝加入帮派的消息
void sendJoinGuildMsg(char* heroId, char* guildName, int guildLevel);
//解散帮派
bool disbandGuild(Hero *manager);

//由帮派名得到帮派实例
Guild *getGuildWithName(char* guildName);

//帮派Id查找帮派实例
Guild *getGuildWithId(char* guildId);

//把一个帮派ID存到memcached中的所有的帮派名列表
void saveOneGuildIdToMemc(char* guildId);
//初始化所有存在的帮派
void initAllExistGuild();

//查看一个阵营中的帮主列表
int viewAllPresidInCamp(int camp, char *result);

//查看帮主或副帮主昵称
char* viewGuildPresidNick(int flag, char* guildName);

//所有帮派名的存储
void saveAllGuildIdToMemc();

//把帮派系统信息保存到memcached
void saveGuildSystemToMemc();

void sendGuildMsg(char* guildName, char* msg);

//邀请加入帮派
int inviteJoinGuild(Hero* manager, char *heroId);

bool GM_disbandGuildByName(char* guildName);

bool GM_disbandGuildByRank(int camp, int rank);

int viewGuildGameInfo(int camp, int num, int page, char *result);

//系统请客 吃饭
void systemTreatGuild(Map_Inform *mapNow,char *typeId,char *guildId);

//判断guildName是否是老的帮派名（内部只做是否判断，guildName合法性判断请在调用之前做）
bool isOldGuildName(char* guildName);

int refreshGuildTaskForAll(Hero* hero);

void viewFreshGuildTaskInfo(Hero* hero, char* result);

bool GM_setGuildPresid(char* heroId);
#endif
