#ifndef GOODS_CONFIG_H
#define GOODS_CONFIG_H
#include<string>
using namespace std;
class Goods_Config
{
private:
	char* id;				//物品id		
	char* name;			//物品名称
	char* effect;			//物品效果
	int order; 				//排序序号
	int repeat;				//堆叠数量
	int type;				//类型
	int levelLimit;			//等级限制
	int gold;				//买入元宝价格
	int goldBound;			//买入绑定元宝价格
	int money;				//买入非绑定游戏币价格
	int moneyBound;			//买入绑定游戏币价格
	int price;				//卖出游戏币价格

	
public:
		Goods_Config(char* _id,char* _name,char* _effect,int _order,int _repeat,int _type,int _levelLimit,int _gold,int _goldBound,int _money,int _moneyBound,int _price);
		char* getId(void);           //物品id
		char* getName(void);		 //物品名称
		char* getEffect(void);        //物品效果
		int getOrder(void);	//排序序号
		int getRepeat(void);         //堆叠数量
		int	getType(void);         //类型
		int getLevelLimit(void);        //等级限制
		int getGold(void);    //买入元宝价格
		int getGoldBound(void);
		int getMoneyBound(void);
		int getMoney(void);      //卖出游戏币价格
		int getPrice(void);
};
#endif
