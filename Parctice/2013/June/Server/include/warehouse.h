#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <string>
#include <map>
#include "hero.h"
#include "equipment.h"
#include "data_structure_struct.h"
#include "command_return_define_data.h"

using namespace std;

class Equipment;
class Warehouse
{
private:
	// Goods_Inform goods_inform[108];								//物品信息结构体	
	WarehouseData warehousedata;								//用于保存memcached的结构体
	map<string,Equipment*> equip;								//通过memcached初始化时,暂存装备实例的容器,在转存到背包下,改容器删除
	
public:
	Warehouse();												//构造函数
	Warehouse(WarehouseData _warehousedata);					//通过memcached的构造函数
	~Warehouse(void);
	int getGridNum(void);										//取仓库格子数量
	void setGridNum(int _gridNum);								//设置仓库格子数量
	int getExpandNeedGold(void);								//取本次拓展所需要的元宝数量
	void setExpandNeedGold(int _expandNeedGold);				//设置下一次拓展所需要的元宝数量
	char* getGridGoodsid(int index);							//取得该索引下的物品id
	int getGoodsNum(char* goodsid);							//取得该物品的所有数量
	int getGridGoodsNum(int index);								//取得该索引下的物品数量
	bool saveGoodsInWarehouse(char*  goodsid,int number,int index);//根据物品的id和数量,存放的仓库的指定格子内
	bool saveGoodsInWarehouse(char*  goodsid,int number);		//根据物品的id和数量,存放到仓库的第一个为空的格子内
	int fullOrEmpty(char*  goodsid,int repeatNum,int number);				//根据物品的id和存储上限,判断仓库是否已经满
	int findSaveIndex(char*  goodsid,int repeatNum);			//根据物品的id和存储上限,查找物品可以存放的索引
	int getEmptyGrid(void);										//取得第一个空的格子
	void initGrid(int index);									//初始化该索引的格子
	bool verify(int index,char*  goodsid);						//验证改索引下放的物品 是否相同
	bool expand(int num);										//拓展num数量的格子
	bool isGridExistGoods(int index);							//判断该格子下是否存在物品
	void msg_expand_success(char *msg);							//返回拓展成功的消息
	void msg_expand_failed(char *msg);								//返回拓展失败的消息
	void msg_delete_goods(char *msg,int type,int index,char*  goodsid);	//返回删除物品的消息
	void msg_expand_needGold(char *msg,int num);							//返回拓展仓库所需要的元宝的消息
	void msg_drag_success(char *msg,int len,int index1,int index2);								//拖动成功信息返回
	void msg_drag_failed(char *msg);								//拖动失败信息返回
	void saveInStruct(void);									//保存memcached结构体
	WarehouseData getMemStruct(void);							//返回要存在memcached的结构体
	// map<string,Equipment*> getEquipMap(void);					//取出存放装备的临时容器
	int showWarehouseData(WarehouseData *obj, char *outfile);
	Goods_Inform getGoods_Inform(int _index);	
	void setMemStruct(WarehouseData _warehousedata);
};
#endif
