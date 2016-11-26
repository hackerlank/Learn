/****************************************************************
 * Filename: guild_war_comm.h
 * 
 * Description: 帮战房间通信
 *
 * Original Author : bison, 2012-9-23
 *
 ****************************************************************/

//查看帮派战房间信息
void viewGuildWarRoomInfoComm(char *buffer);
//创建帮派战房间通信
void createGuildWarRoomComm(char *buffer);
//帮战挑战通信
void challengeGuildWarComm(char *buffer);
//召唤加入帮派战
void callJoinGuildWarComm(char *buffer);
//帮众加入帮派战
void JoinGuildWarComm(char *buffer);
//帮主准备帮派战
void prepareGuildWarComm(char *buffer);
//帮派战退出
void exitGuildWarComm(char *buffer);
//帮派战中复活
void revivalInGuildWar(char *buffer);
