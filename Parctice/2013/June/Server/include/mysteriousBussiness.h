#ifndef MYSTERIOUSBUSSINESS_H
#define MYSTERIOUSBUSSINESS_H
#include<string>
#include<vector>
#include "hero.h"
#include "mysteriousBussiness_config.h"
using namespace std;
/********************************************
*神秘商人类的结构体
*goodsid表示,此次神秘商人卖的物品id,flag代表此次玩家是否已经购买,0代表没购买,1代表已经购买,money为对应的物品的价格,beginTime为建号时间
*创建:jolly    日期:2012,10,11
*********************************************/

class MysteriousBussiness
{
private:
		MysteriousBussinessData mysteriousBussinessData;
public:
		MysteriousBussiness(void);
		MysteriousBussiness(MysteriousBussinessData _mysteriousBussinessData);
		void refreshGoods(int level);
		void msg_mysteriousGoods(char* msg);
		void msg_mysteriousRefresh(char* msg);
		void refreshIncreaseMoney(void);
		bool isTimerForRefresh(void);
		void verifyFlag(void);	
		void setFlag(int _flag);
		MysteriousBussinessData getMemStruct(void);
		bool isSameGoods(char* goodsid,int loop);
		char* getIdentiy(int _index);
		int getPrice(int _index);
		void setBuyFlag(int _flag,int _index);
		int getBuyFlag(int _index);
		void setRefreshMoney(int _refreshMoney);
		int getRefreshMoney(void);
};
#endif

