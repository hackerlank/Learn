/***********************************************
*	金钱类:Money
*	制作:jolly
*	日期:2012.7.10
*	功能:提供增加金钱和使用金钱的方法的接口
***********************************************/
#ifndef MONEY_H
#define MONEY_H
#include <iostream>
#include <string>
#include "data_structure_struct.h"
#include "hero.h"
#include "command_return_define_data.h"
using namespace std;

class Hero;
class Money
{
private:	

	moneyData money_data;	
	
public:
	
	Money(void);
	Money(moneyData _moneydata);
	void load(moneyData _moneydata);
	void money_increaseBoundGold(long _boundGold);	//增加绑定元宝	
	long money_getBoundGold(void);		//获得玩家身上绑定元宝数量	
	void money_setBoundGold(long _boundGold);	//设置玩家身上绑定元宝数量
	void money_useBoundGold(long _boundGold);	//使用绑定元宝数量
	
	void money_increaseGold(long _gold);	//增加元宝	
	long money_getGold(void);		//获得玩家身上元宝数量	
	void money_setGold(long _gold);	//设置玩家身上元宝数量
	void money_useGold(long _gold);	//使用元宝数量
	
	void money_increaseBoundGameMoney(long _boundGameMoney);	//增加绑定游戏币	
	long money_getBoundGameMoney(void);		//获得玩家身上绑定游戏币数量	
	void money_setBoundGameMoney(long _boundGameMoney);	//设置玩家身上绑定游戏币数量
	void money_useBoundGameMoney(long _boundGameMoney);	//使用绑定游戏币数量
	
	void money_increaseGameMoney(long _gameMoney);	//增加游戏币
	long money_getGameMoney(void);		//获得玩家身上游戏币数量	
	void money_setGameMoney(long _gameMoney);	//设置玩家身上游戏币数量
	void money_useGameMoney(long _gameMoney);	//使用游戏币数量
	
	
	bool beforeUse(long _gameMoney); 
	
	bool getMoneyFlag(void);					//取标志
	void setMoneyFlag(char *msg,int _flag);			//设置标志
	
	bool getGoldFlag(void);					//取标志
	void setGoldFlag(char *msg,int _flag);			//设置标志
	
	void saveInStruct();					//保存结构体
	
	void send_msg_money(char *msg,int len);
	
	void increase(int _flag,long _money);	
	
	int showMoneyData(moneyData *obj, char *outfile);
	
	moneyData getMemStruct(void);
	
	void setAccMoney(long _accMoney);
	void increaseAccMoney(long _accMoney);
	long getAccMoney(void);
	
	void money_inform(char *msg,int len);
};
#endif