#ifndef OINTMENT_
#define OINTMENT_
#include <string>
#include <string.h>

#include "my_timer.h"
//数组长度宏定义头文件
#include "wholeDefine.h"

using namespace::std; 

/* ointmentType 药品作用类型 ：按影响角色属性不同分类
0 血药			1 蓝药			2 生命上限值
3 魔法上限值	4 命中			5 暴击
6 闪避			7 韧性			8 外功攻击
9 内功攻击		10 外功防御		11 内功防御     
12 血包			13 蓝包 
***********************************************/
class Ointment
{
	public:		
		Ointment(string _id,string _name,int _cd,int _sellPriceBoundGold,int _ointmentType,			
		int _sellPriceNoBoundGold,int _sellPriceBoundMoney,int _sellPriceNoBoundMoney,
		int _levelLimits,int _pileUp,int _type,int _value,int level,int _factor);
		string getId(void);						//药品类型ID											
		string getIdentity(void);
		string getName(void);			             
		int getCd(void);  						//公共cd														              			
		int getSellPriceBoundGold(void)	;		//npc处售出价格	绑定元宝				
		int getSellPriceNoBoundGold(void);	 	//npc处售出价格	非绑定元宝
		int getSellPriceBoundMoney(void);		//npc处售出价格	绑定游戏币
		int getSellPriceNoBoundMoney(void);		//npc处售出价格	非绑定游戏币
		int getLevelLimits(void)	;			//等级限制							
		int getPileUp(void);					//堆叠上限	
		int getType(void);
		int getOintmentType(void);
		int getValue(void);
		int getLevel(void);						//获取药品等级
		int getFactor(void);
	private:
		string id;						//类型ID													
		string name;	
		int cd;
		int sellPriceBoundGold	;		//npc处售出价格	绑定元宝				
		int sellPriceNoBoundGold;	 	//npc处售出价格	非绑定元宝
		int sellPriceBoundMoney;		//npc处售出价格	绑定游戏币
		int sellPriceNoBoundMoney;		//npc处售出价格	非绑定游戏币
		int levelLimits	;				//等级限制							
		int pileUp;						//堆叠上限	
		int type;						//0 药瓶 ，1 药包，2 buff药
		int ointmentType;				//药品类型 ：按影响角色属性不同分类
		int value;						//药品影响角色属性数值
		int level;
		int factor;
};

//单个buff药品数据，用于存储
typedef struct BuffDrugData_T
{
	char		type_id[IDL];		//药品类型ID
	int			effect_type;		//buff药作用类型
	int			level;				//药品等级
	int			effect_value;		//buff药作用量
	int 		remain_time;		//剩余时间	
}BuffDrugData;
#endif
