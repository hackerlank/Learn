/*
 * Filename: instancing_communication.h
 * Description: 副本模块与客户端的通信*
 * Original Author : bison, 2012-6-18
*/
#include<string>
#include"hero.h"
#include "team.h"
#include"cpyLimit.h"
using namespace std;

void entInstancing(string heroId, string inst_typeId);

void ectypeRewardAll(char *buffer);

void ectypeRewardGoods(char *buffer);

/* 
* descirbe:队长选择挑战副本时，检测队伍的可进入状态和房间空闲状态，如果条件满足，则向队友广播挑战副本的消息（处理7.3命令）
 */
void handleTeamLeaderOperate(char *buffer);	

/* 
* descirbe:收到队长的副本挑战邀请时，队伍成员回复队长邀请（处理7.4命令）
 */
void accept_invite(char* buffer);			//接受队长的邀请挑战副本	

//send message to client  
void sendEctypeRewardMsg(string ectypeId, Hero *hero, int flag);

/*组队副本辅助函数*/
bool dealTeamEntCpyAsist(string cpyRomStr,CpyLimit *_cpyLimt,int &roomNum);

/*组队副本辅助函数*/
CpyLimit* getCpylimit(string cpyRomStr);


/*
* arg:队长实例，将要进入的塔防副本的完整类型ID（010_1）
* describe：进入塔防副本开始游戏；
*/
int enterTowerDefRoom(Hero* src_Leader, char* inst_typeId);

/*
* 函数作用：队伍退出塔防副本游戏；
*/
void exitFromTowerDefence(Hero *hero);

/*
* 函数参数；src_Leader：队长； team：队伍实例
* 返回值：true表示队友在队长身边，300像素内
* 函数作用：检测队员是否在队长周围
*/
bool isAround(Hero* src_Leader, Team* team);


void handleTeamLeaderOperateAsist(const char *heroId,const char *inst_id,int inst_level);