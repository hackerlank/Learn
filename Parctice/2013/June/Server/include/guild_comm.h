/****************************************************************
 * Filename: guild_comm.cpp
 * 
 * Description: 帮派系统的通信
 *
 * Original Author : bison, 2012-8-15
 *
 ****************************************************************/

//创建帮派
void createGuildComm(char *buffer);
//查看帮会排行榜的某页
void viewGuildPageRankComm(char *buffer);
//搜索某个帮派
void searchOneGuildComm(char *buffer);
//申请加入帮派
void applyJoinGuildComm(char *buffer);
//查看某个帮派信息
void viewOneGuildComm(char *buffer);
//查看我的帮派信息
void viewMyGuildComm(char *buffer);
//升级帮派
void upgradeGuildComm(char *buffer);
//领取帮派排名奖励
void getGuildRankRewardComm(char *buffer);
//修改公告
void changeGuildNoticesComm(char *buffer);
//退出帮派
void exitGuildComm(char *buffer);
//查看帮派成员信息
void viewGuildMembsListComm(char *buffer);
//查看帮派申请列表
void viewGuildApplyListComm(char *buffer);
//移除帮派
void removeFromGuildComm(char *buffer);
//同意加入帮派
void agreeJoinGuildComm(char *buffer);
//拒绝加入帮派
void disagreeJoinGuildComm(char *buffer);
//同意帮派所有申请
void agreeGuildAllApplyComm(char *buffer);
//清空帮派申请列表
void clrGuildApplyListComm(char *buffer);
//查看帮派技能信息
void viewGuildSkillInfoComm(char *buffer);
//激活帮派技能
void openGuildSkillComm(char *buffer);
//升级帮派技能
void upgradeGuildSkillComm(char *buffer);
//查看帮派历史信息
void viewGuildHistoryInfoComm(char *buffer);
//查看帮派活动信息
void viewGuildActivityComm(char *buffer);
//领取帮派签到奖励
void getGuildSignRewardComm(char *buffer);
//向帮派捐献的通信
void guildDonateComm(char *buffer);
//帮派职务调整
void changeGuildTitleComm(char *buffer);
//解散帮派
void disbandGuildComm(char *buffer);
//帮派游戏时查看帮派信息
void guildGameComm(char* buffer);

void refreshGuildTaskComm(char* buffer);

void viewFreshGuildTaskInfoComm(char* buffer);