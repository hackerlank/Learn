#include "warehouse_communicate.h"
#include "money_operator.h"
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
void warehouse_drag(char* buffer)
{	
	int index_first;
	
	int index_second;
		
	char* goodsid_first;
	
	char* goodsid_second;
	
	int num;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index_first);
	MSG_INT(index_second);
	MSG_CHAR(goodsid_first);
	MSG_CHAR_END(goodsid_second);
	
	cout<<"15,3,"<<index_first<<","<<goodsid_first<<","<<index_second<<","<<goodsid_second<<endl;

	Warehouse *warehouse=pg_hero->getWarehouse();		
	if (warehouse==NULL)
	{
		return;
	}
	int gridNum=warehouse->getGridNum();
	if (index_first<0||index_first>gridNum)
	{
		return;
	}
	if (index_second<0||index_second>gridNum)
	{
		return;
	}	
	
	if (warehouse->verify(index_first,goodsid_first)&&warehouse->verify(index_second,goodsid_second))
	{
		warehouse_drag_goods(pg_hero,index_first,goodsid_first,index_second,goodsid_second);
	}
	else
	{
		char msg[20]={'\0'};
		warehouse->msg_drag_failed(msg);
		send_msg(pg_hero->getFd(),msg);
		cout<<"verify error"<<endl;
	}
}

void warehouse_expand(char* buffer)
{
	int flag;
	
	int num;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(flag);
	MSG_INT(num);
	
	if (num<0)
	{
		num=0;
	}
	
	Warehouse *warehouse=pg_hero->getWarehouse();		
	if (warehouse==NULL)
	{
		return;
	}
	char msg[100]={'\0'};
	if (flag==1)
	{
		warehouse->msg_expand_needGold(msg,num);
		send_msg(pg_hero->getFd(),msg);
	}	
	else if(flag==2)
	{
		int gridNum=warehouse->getGridNum();
		if (gridNum>=98)
		{
			cout<<"jolly:warehouse num is too big in warehouse_communicate 82"<<endl;
		}
		else
		{
			if ((num+gridNum)>98)
			{
				num=98-gridNum;
			}
			int needGold=warehouse->getExpandNeedGold();
			int useMoney=0;
			int initMoney;
			for (int i=0;i<num;i++)
			{
				useMoney=useMoney+needGold+i;
			}
			if (useBoundGold(pg_hero,useMoney))
			{
				warehouse->expand(num);
				warehouse->msg_expand_success(msg);
				send_msg(pg_hero->getFd(),msg);
				needGold+=num;
				warehouse->setExpandNeedGold(needGold);
			}
			else
			{
				cout<<"jolly:gold is not enough to expand warehouse_communicate 102"<<endl;
			}
		}
	}
	else
	{
		cout<<"jolly:command is error in warehouse_communicate.cpp 90"<<endl;
	}		
}

void warehouse_destory(char* buffer)
{		
	char *goodsid;
	
	int index;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_CHAR(goodsid);
	MSG_INT(index);
	
	Warehouse *warehouse=pg_hero->getWarehouse();		
	if (warehouse==NULL)
	{
		return;
	}
	int gridNum=warehouse->getGridNum();
	if (index<0||index>gridNum)
	{
		return;
	}
		
	if (warehouse->verify(index,goodsid))
	{
		warehouse_destory_goods(pg_hero,goodsid,index);		
	}		
}

void warehouse_saveGoods(char* buffer)
{	
	int index;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);
	
	cout<<"15,2,"<<index<<endl;
	
	Bag *bag=pg_hero->getBag();	
	if (bag==NULL)
	{
		cout<<"jolly:bag is null warehouse_communicate 158"<<endl;
		return;
	}
	int gridNum=bag->getBagNum();
	if (index<0||index>gridNum)
	{
		return;
	}
	
	sendGoodsToWareHouse(pg_hero,index);
}

void warehouse_takeGoods(char* buffer)
{
	int index;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(index);
	
	cout<<"15,3,"<<index<<endl;	
	
	Warehouse *warehouse=pg_hero->getWarehouse();	
	if (warehouse==NULL)
	{
		return;
	}
	int gridNum=warehouse->getGridNum();
	if (index<0||index>gridNum)
	{
		return;
	}
	
	takeGoodsToBag(pg_hero,index);
}

void warehouse_reduction(char* buffer)
{
	char msg[11000]={'\0'};
	pg_hero->msg_warehouse(msg);
	send_msg(pg_hero->getFd(),msg);
}

void warehouseArrange(char* buffer)
{
	int n;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(n);
	
	cout<<"15,6,"<<n<<endl;	
	Warehouse *warehouse=pg_hero->getWarehouse();
	if (warehouse==NULL)
	{
		return;
	}
	WarehouseData warehousedata;
	warehousedata.gridNum=warehouse->getGridNum();
	warehousedata.expandNeedGold=warehouse->getExpandNeedGold();
	int index;
	char test[109]={'\0'};
	memset(test,'0',108);
	int indexArr[108];
	for (int i=0;i<n;i++)				//检查客户端传来的索引是否正确
	{
		MSG_INT(index);
		// cout<<index<<endl;
		if (index>=0||index<98)			//下标越界判断
		{				
			if (test[index]=='0')			//判断发来的索引有没有重复的
			{
				test[index]='1';
				indexArr[i]=index;			//记录索引列表
			}	
			else							//有重复的索引,返回
			{
				return;
			}
		}
		else								//下标越界,返回
		{
			return;
		}
	}
	for (int i=0;i<n;i++)
	{
		warehousedata.goods_inform[i]=warehouse->getGoods_Inform(indexArr[i]);
	}		
	warehouse->setMemStruct(warehousedata);
	char msg[20]={'\0'};
	sprintf(msg,"%d,%d,%d",15,4,1);
	send_msg(pg_hero->getFd(),msg);	
}