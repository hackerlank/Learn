#ifndef PET_OPERATOR_H
#define PET_OPERATOR_H
#include<string>
#include<time.h>
#include"pet.h"
#include"bag.h"
using namespace std;

bool petMating(Hero *hero,Pet *pet1,Pet *pet2,int index1,int index2,int num);									//宠物繁殖功能函数

void matingSon(char* goodsid,int decide_level,int decide_quality,int male_type,int generation,int luckNum);	
//返回子辈的id

int decideSonQuality(int decide_level,int decide_quality,int luckNum);				//返回子辈的宠物品质

bool levelDecidePercent(int level,int luckNum);										//根据等级查看宠物繁殖是否会升级品质

bool compareNum(int num,int percent);									//比较函数

int random(int begin,int end);											//随即begin到end的随机数

bool MatingCondition(Hero *hero,Pet *pet1,Pet *pet2);							//判断是否满足繁殖条件

void petFiveEleExp(Hero *hero,char* goodsid,int index);				//使用宠物五行经验丹

bool petLevelUp(Pet *pet,Hero *hero,int exp);				//宠物升级

bool doublePetMating(Hero *hero1,Hero *hero2,Pet *pet1,Pet *pet2);	

bool doubleMatingCondition(Hero *hero1,Hero *hero2,Pet *pet1,Pet *pet2);							//判断是否满足繁殖条件

#endif

