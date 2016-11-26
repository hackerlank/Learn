#ifndef WAREHOUSE_OPERATOR_H
#define WAREHOUSE_OPERATOR_H

#include "warehouse.h"
#include "hero.h"
#include "bag.h"

using namespace std;

bool sendGoodsToWareHouse(Hero *hero,int index);
bool takeGoodsToBag(Hero *hero,int index);
void send_msg_ToWarehouse(char *msg,int number,int type,int index,char* goodsid,char* identity);
void warehouse_drag_goods(Hero *hero,int index_first,char* goodsid_first,int index_second,char* goodsid_second);
void warehouse_destory_goods(Hero *hero,char* identity,int index);
void warehouse_destory_goods_byNum(Hero *hero,char* identity,int num);
void destoryAllWarehouseGoods(Hero *hero,char* goodsid);								//根据物品id,完全摧毁物品
#endif