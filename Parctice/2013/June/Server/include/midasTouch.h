#ifndef MIDASTOUCH_H
#define MIDASTOUCH_H
#include <iostream>
#include <string>
#include "hero.h"

class MidasTouch
{
	private:
		MidasTouchData midastouchdata;	
	public:
		MidasTouch(void);
		MidasTouch(MidasTouchData _midastouchdata);
		void normalRefresh(char *msg,int len,Hero *hero = NULL);
		void luckyRefresh(char *msg,int flag,int len,Hero *hero = NULL);
		void reLoadMidasTouch(int freshNumber,int reNumber);
		void msg_midasTouchInform(char *msg,int len);
		void judgeReward(Hero *hero = NULL);
		void receiveReward(void);
		int getRefreshNum(void);
		void setRefreshNum(int _refreshNum);
		int getLuckyRefreshNum(void);
		void setLuckyRefreshNum(int _luckyRefreshNum);
		int getLuckyRefreshMoney(void);
		void setLuckyRefreshMoney(int _luckyRefreshMoney);
		MidasTouchData getMemStruct(void);
		int getMoney(void);
		void setMoney(int _money);
		int getPopularity(void);
		void setPopularity(int _popularity);
		int getFlag(void);
		void setFlag(int _flag);
		void decideValue(int index,int randomNum);
		bool isMax(void);
};
#endif