#ifndef RIDE_H
#define RIDE_H
#include <iostream>
#include <map>
#include <vector>
#include "hero.h"
#include "data_structure_struct.h"
#include "ride_config.h"
using namespace std;

class Ride
{
private:
	RideData ridedata;
public:
	Ride(void);
	Ride(RideData rideData);
		
	void createRide(Ride_Config *ride_config,char *id);										//使用坐骑
		
	RideData getMemStruct(void);															//取出结构体
	
	int getExpNow(void);
	int getExpMax(void);
	char *getEquipmentIdentity(int index);
	int getCost(void);	
	char* getPhotoId(void);
	int getMove(void);
	int getFinalGrid(void);
	int getFinalSkillStage(void);
	int getQuality(void);
	char *getIdentity(void);
	char *getNickName(void);
	int getLevel(void);
	int getHp(void);
	int getMp(void);
	int getOutAttVal(void);
	int getInAttVal(void);
	int getInDefVal(void);
	int getOutDefVal(void);
	int getHit(void);
	int getCrit(void);
	int getDodge(void);
	int getTenacity(void);
	
	int getRefreshMoney(int number);														//返回刷新最终技能消耗的钱
	
	void gainExp(Hero *hero,int exp,int flag);												//获得经验,只有出战坐骑才能获得经验
	void equalAtt(Ride_Config *ride_config);
	void minusAtt(Ride_Config *ride_config);
	void decreaseAtt(Hero *hero);															//去掉坐骑给人物加的属性
	void increaseAtt(Hero *hero);															//加上坐骑给人物加的属性	
	bool ifFull(void);																		//判断人物是否有坐骑了 有坐骑返回true 没有返回false
	bool judgeEquipWear(int index);															//判断坐骑是否穿了装备 穿了返回true 没有返回false
	void wearEquip(Equipment *equipment,int index);											//坐骑穿装备,改变坐骑数据
	void takeOffEquip(Equipment *equipment,int index);										//坐骑脱装备,改变坐骑数据
	bool evolutionIncrease(int number,Hero *hero);											//坐骑获得进阶点,可以进阶返回true,不能进阶返回false
	void initCost(void);																	//初始化坐骑进阶花费元宝
	void evolutionIncreaseCost(void);														//坐骑进阶使用元宝累增
	void refreshSkill(vector<int> flag,Hero *hero);											//洗炼技能
	void learnFinalSkill(void);																//刚到7阶学习最终技能
	void openOneSkillGrid(void);															//开启最终技能的孔
	void finalSkillEffect(void);															//最终技能触发效果
	void finalSkilldisapear(void);															//最终技能消失效果
	int countPower(void);																	//算坐骑战力
	
	void ride_msg_return(char *msg,int len,Hero *hero);										//使用坐骑返回坐骑详细信息
	void ride_wear_equip(char *msg,int len,int index,char *identity,char *id);				//坐骑穿装备返回
	void ride_takeoff_equip(char *msg,int len,int index,char *identity,char *id);			//坐骑脱装备返回
	void ride_evolution_return(char *msg,int len,int number);								//坐骑进阶信息返回
	void ride_finalSkill_return(char *msg,int len);											//坐骑洗炼技能,信息返回
};

#endif