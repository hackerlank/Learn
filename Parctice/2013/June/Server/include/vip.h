#ifndef VIP_DATA
#define VIP_DATA
#include<iostream>
#include<string.h>
using namespace std;

struct VipDataInitial
{
	char id[13];	//vip id
	int lastTime;	//持续时间
	char title[13];	//头衔
	int invalid1;	//保留数据1,
	int invalid2;	//保留数据2
	int invalid3;	//保留数据3
	int invalid4;	//保留数据4
	char giftBagId[13];	//奖励礼包id
};

#endif