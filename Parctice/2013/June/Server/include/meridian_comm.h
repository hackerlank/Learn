/****************************************************************
 * Filename: meridian_comm.h
 * 
 * Description: 经脉系统与客户端的通信
 *
 * Original Author : bison, 2012-7-23
 *
 ****************************************************************/
#include<string>
#include"hero.h"
using namespace std;
 
//开始修炼经脉通信
void  startMeridComm(char *buffer);
//经脉强化
void strenMeridComm(char *buffer);
//是有道具缩减修炼时间
void useGoodsMeridComm(char *buffer);
//客户端请求经脉信息
void  applyMeridInfoComm(char *buffer);
//花元宝减少经脉修炼时间
void decMeridTimeComm(char *buffer);
