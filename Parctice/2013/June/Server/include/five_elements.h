/****************************************************************
 * Filename: five_elements.h
 * 
 * Description: 五行
 *
 * Original Author : bison, 2012-7-10
 *
 ****************************************************************/

#ifndef _FIVE_ELEMENTS_H_
#define _FIVE_ELEMENTS_H_
#include "data_structure_struct.h"
#include <iostream>
using namespace std;

//五行成员
typedef enum{
	METAL = 1,		//金属性
	WOOD,			//木属性
	EARTH,			//土属性
	WATER,			//水属性
	FIRE,			//火属性
	NOELEM			//没有属性
}FIVE_ELEMENT_T;

typedef struct FiveElemConf_S
{
	int startLevel;
	int changeNeedGold;
	double defFactor[6][6];
	int needHeroLevel[100];
	int upgradeNeedExp[100];
	int fiveValue[100];
} FiveElemConf_T;

extern FiveElemConf_T heroFiveElemConf; 		//人物五行配置

class FiveElem
{
	private:
		int level;					//五行等级
		FIVE_ELEMENT_T element;		//五行的属性
		int expNow;					//当前累积经验
		int expForNext;				//升到下一级所需要的经验
		
	public:
		//五行的构造函数
		FiveElem(FIVE_ELEMENT_T elem = NOELEM, int level = 0);
		//memcached恢复调用构造
		FiveElem(FiveElementData fiveData);
		//更改五行属性
		bool changeElem(FIVE_ELEMENT_T elem);
		//五行升级
		bool upGrade(void);
		//获得五行等级
		int getLevel(void);
		//获得五行属性
		FIVE_ELEMENT_T getElem(void);
		//获取五行数值
		int getValue(void);
		//获得被攻击者五行抗性
		double getFactor(FIVE_ELEMENT_T hitElem);
		//获取五行伤害值
		int getHurt(double k);
		//增加五行升级进度
		bool addExp(int value);
		//当前经验
		int getExpNow();
		//升到下一级需要的经验
		int getExpForNext();
		
};

#endif	
	