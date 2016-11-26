#include "warehouse.h"

Warehouse::Warehouse()
{
	warehousedata.gridNum=98;
	warehousedata.expandNeedGold=1;
}

Warehouse::Warehouse(WarehouseData _warehousedata)
{
	warehousedata=_warehousedata;	
}

int Warehouse::getGridNum(void)
{
	return warehousedata.gridNum;
}

void Warehouse::setGridNum(int _gridNum)
{
	warehousedata.gridNum=_gridNum;
}

int Warehouse::getExpandNeedGold(void)
{
	return warehousedata.expandNeedGold;
}

void Warehouse::setExpandNeedGold(int _expandNeedGold)
{
	warehousedata.expandNeedGold=_expandNeedGold;
}

int Warehouse::getGoodsNum(char* goodsid)
{
	int goodsNum=0;
	for (int i=0;i<warehousedata.gridNum;i++)
	{
		if (strcmp(warehousedata.goods_inform[i].goodsid,goodsid)==0)
		{
			goodsNum+=warehousedata.goods_inform[i].number;
		}
	}
	return goodsNum;
}
int Warehouse::getGridGoodsNum(int index)
{
	return warehousedata.goods_inform[index].number;
}

bool Warehouse::saveGoodsInWarehouse(char* goodsid,int number,int index)
{
	if (strlen(goodsid)!=0)
	{
		strncpy(warehousedata.goods_inform[index].goodsid,goodsid,sizeof(warehousedata.goods_inform[index].goodsid));
	}
	else
	{
		strncpy(warehousedata.goods_inform[index].goodsid,"0",sizeof(warehousedata.goods_inform[index].goodsid));
	}
	warehousedata.goods_inform[index].number = number;
	return true;
}


bool Warehouse::saveGoodsInWarehouse(char* goodsid,int number)
{
	for (int i=0;i<warehousedata.gridNum;i++)
	{
		if (strcmp(warehousedata.goods_inform[i].goodsid,"0")==0)
		{
			if (strlen(goodsid)!=0)
			{
				strncpy(warehousedata.goods_inform[i].goodsid,goodsid,sizeof(warehousedata.goods_inform[i].goodsid));
			}
			else
			{
				strncpy(warehousedata.goods_inform[i].goodsid,"0",sizeof(warehousedata.goods_inform[i].goodsid));
			}
			warehousedata.goods_inform[i].number=number;
			return true;
		}
	}
	return false;
}

int Warehouse::fullOrEmpty(char* goodsid,int repeatNum,int number)
{
	int gridFlag=-1;
	for (int i=0;i<warehousedata.gridNum;i++)
	{
		if (strcmp(warehousedata.goods_inform[i].goodsid,"0")==0)
		{		
			if (gridFlag==-1)
			{
				return i;
			}
			else
			{
				return gridFlag;
			}
		}
		else if (strcmp(warehousedata.goods_inform[i].goodsid,goodsid)==0)
		{
			if ((warehousedata.goods_inform[i].number+number)<=repeatNum)
			{
				return i;
			}
			else if (warehousedata.goods_inform[i].number<repeatNum)
			{
				gridFlag=i;
			}
		}
	}
	return -1;
}

int Warehouse::findSaveIndex(char* goodsid,int repeatNum)
{
	int index;
	for (index=0;index<warehousedata.gridNum;index++)
	{
		if (strcmp(warehousedata.goods_inform[index].goodsid,goodsid)==0)
		{
			if (warehousedata.goods_inform[index].number<repeatNum)
			{
				return index;
			}
		}
	}
	index=getEmptyGrid();
	return index;
}

char* Warehouse::getGridGoodsid(int index)
{
	return warehousedata.goods_inform[index].goodsid;
}

int Warehouse::getEmptyGrid(void)		//调用本函数前,必须调用fullOrEmpty()函数,判断仓库是否已满
{
	int index;
	for (index=0;index<warehousedata.gridNum;index++)
	{
		if (strcmp(warehousedata.goods_inform[index].goodsid,"0")==0)
		{
			return index;
		}
	}
	return index;
}

void Warehouse::initGrid(int index)
{
	strncpy(warehousedata.goods_inform[index].goodsid,"0",sizeof(warehousedata.goods_inform[index].goodsid));
	warehousedata.goods_inform[index].number=0;
}

bool Warehouse::verify(int index,char* goodsid)
{
	if (strcmp(warehousedata.goods_inform[index].goodsid,goodsid)==0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

bool Warehouse::expand(int num)
{
	// if (warehousedata.gridNum+num>108)
	// {
		// return false;
	// }
	// else
	// {
		warehousedata.gridNum+=num;
		// warehousedata.expandNeedGold=warehousedata.expandNeedGold+10;
		return true;
	// }
}

bool Warehouse::isGridExistGoods(int index)
{
	if (warehousedata.goods_inform[index].number==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Warehouse::msg_expand_success(char* msg)
{
	if (msg==NULL)
	{
		return;
	}
	sprintf(msg,"%d,%d,%d,%d",15,WAREHOUSE_EXPAND,SUCCESS,warehousedata.gridNum);
}

void Warehouse::msg_expand_failed(char *msg)
{
	if (msg==NULL)
	{
		return;
	}
	sprintf(msg,"%d,%d,%d,%d",15,WAREHOUSE_EXPAND,FAILED,warehousedata.gridNum);
}

void Warehouse::msg_delete_goods(char *msg,int type,int index,char* goodsid)
{
	if (msg==NULL)
	{
		return;
	}
	sprintf(msg,"%d,%d,%d,%d,%d,%d,%s,%s",15,WAREHOUSE_GOODS,0,warehousedata.goods_inform[index].number,type,\
	index,goodsid,warehousedata.goods_inform[index].goodsid);
	// string msg="15";
	// msg+=intTostring(WAREHOUSE_GOODS);
	// msg+=intTostring(0);
	// msg+=intTostring(warehousedata.goods_inform[index].number);
	// msg+=intTostring(type);
	// msg+=intTostring(index);
	// msg=msg+","+goodsid;
	// msg=msg+","+warehousedata.goods_inform[index].goodsid;	
	// return msg;
}

void Warehouse::msg_expand_needGold(char *msg,int num)
{
	if (msg==NULL)
	{
		return;
	}
	// string msg="15";
	// msg+=intTostring(WAREHOUSE_EXPAND_NEED);
	// msg+=intTostring(warehousedata.expandNeedGold);
	int canExpand=num+warehousedata.gridNum;
	if (canExpand>108)
	{
		num=108-warehousedata.gridNum;
		// msg+=intTostring(4);
	}
	int useMoney=0;
	for (int i=0;i<num;i++)
	{
		useMoney=useMoney+i+warehousedata.expandNeedGold;
	}
	sprintf(msg,"%d,%d,%d,%d",15,WAREHOUSE_EXPAND_NEED,useMoney,num);
	// return msg;
}

void Warehouse::saveInStruct(void)
{
	// string test;
	// for (int i=0;i<warehousedata.gridNum;i++)
	// {
		// warehousedata.number[i]=warehousedata.goods_inform[i].number;
		// test=test+warehousedata.goods_inform[i].goodsid+";";
	// }
	// strncpy(warehousedata.goodsids,test.c_str(),test.size());
}

WarehouseData Warehouse::getMemStruct(void)
{
	return warehousedata;
}

// map<string,Equipment*> Warehouse::getEquipMap(void)
// {
	// return equip;
// }

int Warehouse::showWarehouseData(WarehouseData *obj, char *outfile)
{
	// FILE *out;
	// if((out = fopen(outfile, "w+")) == NULL){
		// fprintf(stderr, "fopen file %s error!\n", outfile);
		// exit(EXIT_FAILURE);
	// }
 	// fprintf(out, "test WarehouseData goodsids:%s\n", obj->goodsids);	
	// fprintf(out, "test WarehouseData warehousedata.gridNum:%d\n", obj->gridNum);
	// fprintf(out, "test WarehouseData warehousedata.expandNeedGold:%d\n", obj->expandNeedGold);
	// fprintf(out, "test WarehouseData number:");
	// for (int i=0;i<warehousedata.gridNum;i++)
	// {
		// fprintf(out, "%d ", obj->number[i]);
	// }

	// if(fclose(out) != 0){
		// fprintf(stderr, "fclose file error!\n");
		// exit(EXIT_FAILURE);
	// } 	
	
	// return 0;
}

void Warehouse::msg_drag_success(char *msg,int len,int index1,int index2)								//拖动成功信息返回
{
	if (msg==NULL)
	{
		return;
	}
	snprintf(msg,len,"%d,%d,%d,%d,%d,%s,%d,%d,%s,%d",15,WAREHOUSE_GOODS,2,SUCCESS,index1,getGridGoodsid(index1),getGridGoodsNum(index1),index2,getGridGoodsid(index2),getGridGoodsNum(index2));
}

void Warehouse::msg_drag_failed(char *msg)								//拖动失败信息返回
{
	if (msg==NULL)
	{
		return;
	}
	sprintf(msg,"%d,%d,%d,%d",15,WAREHOUSE_GOODS,2,FAILED);
	// string msg="15";
	// msg+=intTostring(WAREHOUSE_GOODS);
	// msg+=intTostring(2);
	// msg+=intTostring(FAILED);
	// return msg;
}

Warehouse::~Warehouse(void)
{
	// map<string,Equipment*>::iterator it;
	// if (!equip.empty())
	// {
		// for (it=equip.begin();it!=equip.end();it++)
		// {
			// it->second=NULL;
		// }
	// }	
}

Goods_Inform Warehouse::getGoods_Inform(int _index)
{
	if((_index<0)||(_index>=sizeof(warehousedata.goods_inform)))
	{
		_index = 0;
	}
	return warehousedata.goods_inform[_index];
}

void Warehouse::setMemStruct(WarehouseData _warehousedata)
{
	warehousedata=_warehousedata;
}
