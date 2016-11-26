/***********************************************
*	金钱类使用方法:Money_operator
*	制作:jolly
*	日期:2012.12.17
*	功能:提供增加金钱和使用金钱的方法
***********************************************/
#ifndef MONEY_OPERATOR_H
#define MONEY_OPERATOR_H
#include <iostream>
#include <string>
#include "data_structure_struct.h"
#include "hero.h"
#include "money.h"
#include "command_return_define_data.h"
using namespace std;

bool increaseBoundGold(Hero *hero,long _boundGold);	//增加绑定元宝	
bool useBoundGold(Hero *hero,long _boundGold);	//使用绑定元宝数量
bool campareBoundGold(Hero *hero,long _boundGold);		//判断绑定元宝是否够用

bool increaseGold(Hero *hero,long _gold);	//增加元宝	
bool useGold(Hero *hero,long _gold);	//使用元宝数量
bool campareGold(Hero *hero,long _gold);		//判定元宝是否够用

bool increaseBoundGameMoney(Hero *hero,long _boundGameMoney);	//增加绑定游戏币	
bool useBoundGameMoney(Hero *hero,long _boundGameMoney);	//使用绑定游戏币数量
bool campareBoundGameMoney(Hero *hero,long _boundGameMoney);		//判断绑定游戏币是否够用

bool increaseGameMoney(Hero *hero,long _gameMoney);	//增加游戏币
bool useGameMoney(Hero *hero,long _gameMoney);	//使用游戏币数量
bool campareGameMoney(Hero *hero,long _gameMoney);		//判断游戏币是否够用

bool increaseAccMoney(Hero *hero,long accMoney);		//充值
#endif