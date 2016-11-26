#ifndef _ACCOUNT_COMMUNICATION__
#define _ACCOUNT_COMMUNICATION__
/*
	角色与玩家账户的数据交互
	Author:Tory
	Date:2012/10/24
*/
#include <iostream>

using namespace std;

void top_up(char* );		//从账户中提取刀币转换成元宝
void recharge_srv_msg(char *);
void csd_keepalive();
#endif