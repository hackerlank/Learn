#ifndef BAG_OPERATOR_H
#define BAG_OPERATOR_H
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <set>
#include <vector>
#include "droplist_configuration.h"
#include "monster_configuration.h"
#include "monsterBase.h"
#include "hero.h"
#include "ointment.h"
#include "pick.h"
#include "map_inform.h"
#include "nbox.h"
#include "task.h"
#include "user_role_manage_equip.h"
#include "bag.h"
#include "warehouse_operator.h"

void mulityUse(char *buffer);
void testGoods(char *buffer);
void bagArrang(char *buffer);
void bag_operator(char *buffer);
void destoryGoods(char *buffer);
void getEquipInform(char *buffer);
void bagFlagSet(char *buffer);
bool expand(Hero *hero,int num);
void expandReturn(char *buffer);
void useExpTimesReturn(char *buffer);
void bag_useAllGoods(char *buffer);
void setGoodsUnBound(char *buffer);
int getGemType(char* goodsid);
int getGemEffect(char* goodsid);
int goodsReturnInt(char* goodsid,int index);			//取得物品的效果,goodsid为物品id,index为想取得的第几位数据,从0开始
int goodsReturnInt(Goods_Config *goods,int index);		//取得物品的效果,goods为物品实例,index为想取得的第几位数据,从0开始
void goodsReturnVector(Goods_Config *goods,vector<string> &effects);	//取得物品的效果,返回所有的effect
int getGoodsType(char* goodsid);
void testPet(char *buffer);
void testMoney(char *buffer);
void modifyCamp(Hero *hero);
void testHeroExp(char *buffer);
void useAllGoods(Hero *hero,char* identity);
bool useRandomGoods(Hero *hero,char* goodsid,int index);
void useRewardBagWithMoney(Hero *hero,char* goodsid,int index);
void useMoneyBox(Hero *hero,char *goodsid,Point pt);
void taskGoodsSpecialPosUse(Hero *hero, char* goodsId, int index);								//到指定地点使用的任务道具的使用
void heroExpDrug(Hero *hero,char* goodsid,int index,int number);
void petExpDrug(Hero *hero,char* goodsid,int index,int number);
void useRandomEquip(Hero *hero,char* goodsid,int index);
void useEquipBag(Hero *hero,char* goodsid,int index);
void useExpTimes(Hero *hero,char *goodsid,int index);										//人物使用双倍经验或者三倍经验的数据	
void useRewardBag(Hero *hero,char* goodsid,int index);
void useChunjieBag(Hero *hero,char* goodsid,int index);
void usePopularity(Hero *hero,char* goodsid,int index,int number);
void useDecreaseCrime(Hero *hero,char* goodsid,int index,int number);
void useRideExp(Hero *hero,char* goodsid,int index,int number);
bool usePetAgg(Hero *hero,char* goodsid,int index);											//使用宠物蛋
void useMoneyBag(Hero *hero,char* goodsid,int index,int number);											//使用钱袋
bool saveGoodsInBag(Hero *hero,char* goodsid,int num,int accountFlag=0);										//将物品保存入背包	
bool splitGoods(Hero *hero,int index,int num);													//背包拆分功能
void destoryBagGoods(Hero *hero,int index,char* identity);										//摧毁物品
bool sellGoodsFromBag(Hero *hero,int index,char* id,int &money);											//卖物品
bool saveBagGoods(Hero *hero,char* goodsid,int type,int num,char* identity,int accountFlag);					//保存物品方法
bool saveBagGoods(Hero *hero,char* goodsid,int type,int num,char* identity,int index,int accountFlag);		//保存物品方法
void destoryAllBagGoods(Hero *hero,char* identity);											//摧毁背包中所有的该物品
int useBagGoods(Hero *hero,char* goodsid,int number);											//通过goodsid使用物品
int useBagGoods(Hero *hero,const char* goodsid,int index,int num,bool sendFlag=true);									//使用背包中的物品,删除物品
bool useGoodsBoth(Hero *hero,char *goodsid,int number);											//使用物品,包括背包中的和仓库中的
bool takeOffEquipToBag(Hero *hero,int index,Equipment* equipment);								//脱装备,拖到背包中
bool takeOffEquipToBag(Hero *hero,Equipment* equipment);										//脱装备,不需要给出全部中的索引
Equipment* getEquipFromBag(Hero *hero,int _index);												//取装备实例
bool tradeSuccessInsert(Hero *hero,vector<Trade_Goods> goods);									//交易成功,向背包中插入物品
void send_msg_addgoods(Hero *hero,int num,int type,int index,char* goodsid,char* identity);	//发送物品放入背包的信息	
void send_msg_saveError(Hero *hero);															//物品保存失败发送信息
void send_msg_useSuccess(Hero *hero,int index);													//使用物品成功,发送信息
int getTime();

/*使用道具刷怪*/
void useToolBruMon(Hero *hero,char* goodsid,int index);
//试用坐骑
void useRideAgg(Hero *hero,char *goodsid,int index);
//将装备实例保存到背包中
bool saveEquipIntoBag(Hero *hero,Equipment *equip);
//使用礼包
bool useGiftBag(Hero *hero,char *goodsid,int index);
#endif