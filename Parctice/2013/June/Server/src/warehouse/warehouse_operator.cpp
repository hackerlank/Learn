#include "warehouse_operator.h"

extern map<string,Goods_Config*> id_to_dj;
extern map<string,Goods_Config*> id_to_cl;

using namespace std;

//将背包中的物品放入仓库中,hero:角色实例;index:要放入仓库的物品在背包中的索引
bool sendGoodsToWareHouse(Hero *hero,int index)		//双击背包中的物品 保存到仓库中
{
	Warehouse *warehouse=hero->getWarehouse();
	if (warehouse==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if(bag==NULL)
	{
		return false;
	}
	char* identity=bag->getIdentity(index);	
	int number=bag->getGridNum(index);
	char goodsid[40]={'\0'};
	strncpy(goodsid,identity,sizeof(goodsid));
	int type=getGoodsType(identity);
	int repeatNum;
	cout<<"type is "<<type<<endl;
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (type==1)
	{
		repeatNum=1;
		strncpy(goodsid,hero->identity_to_goodsid(identity),sizeof(goodsid));
	}
	else if (type==4)
	{
		map<string,Goods_Config*>::iterator it;
		it=id_to_cl.find(identity);
		if (it==id_to_cl.end())
		{	
			cout<<"error_________________________________warehouse_opearator 25"<<endl;
			return false;
		}
		else
		{
			repeatNum=it->second->getRepeat();
		}
	}
	else
	{
		map<string,Goods_Config*>::iterator it;
		it=id_to_dj.find(identity);
		if (it==id_to_dj.end())
		{	
			cout<<"error_________________________________warehouse_opearator 39"<<endl;
			return false;
		}
		else
		{
			repeatNum=it->second->getRepeat();
		}
	}	
	cout<<"goodsis repeat number is :"<<repeatNum<<endl;
	cout<<"number is "<<number<<endl;cout<<"identity is "<<identity<<"repeatNum is "<<repeatNum<<endl;
	int saveIndex=warehouse->findSaveIndex(identity,repeatNum);
	if (saveIndex==-1)		//判断仓库是否已满
	{
		cout<<"warehouse is full in warehouse_operator 74"<<endl;
		send_msg_addgoods(hero,number,type,index,goodsid,identity);
		return false;
	}
	else
	{		
		int gridNum=warehouse->getGridGoodsNum(saveIndex);
		number+=gridNum;
		cout<<"totalNum is:"<<number<<endl;
			
		cout<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;	
		if (number<=repeatNum)
		{
			cout<<"@@@@@@@@@@@@@@@@@@@@@@"<<endl;
			warehouse->saveGoodsInWarehouse(identity,number,saveIndex);
			send_msg_ToWarehouse(g_out_buf,number,type,saveIndex,goodsid,identity);
			send_msg(hero->getFd(),g_out_buf);
			bag->initGrid(index,1);
			send_msg_useSuccess(hero,index);
			return true;
		}
		else
		{			
			cout<<"########################"<<endl;
			warehouse->saveGoodsInWarehouse(identity,repeatNum,saveIndex);
			send_msg_ToWarehouse(g_out_buf,repeatNum,type,saveIndex,goodsid,identity);
			send_msg(hero->getFd(),g_out_buf);
			number-=repeatNum;			
			cout<<"test  number is "<<number<<endl;
			saveIndex=warehouse->getEmptyGrid();
			warehouse->saveGoodsInWarehouse(identity,number,saveIndex);
			send_msg_ToWarehouse(g_out_buf,number,type,saveIndex,goodsid,identity);
			send_msg(hero->getFd(),g_out_buf);
			bag->initGrid(index,1);
			send_msg_useSuccess(hero,index);
		}		
	}
}

void send_msg_ToWarehouse(char *msg,int number,int type,int index,char* goodsid,char* identity)
{	
	if (msg==NULL||goodsid==NULL||identity==NULL)
	{
		return;
	}
	
	sprintf(msg,"%d,%d,%d,%d,%d,%d,%s,%s",15,WAREHOUSE_GOODS,1,number,type,index,goodsid,identity);
}

void warehouse_drag_goods(Hero *hero,int index_first,char* goodsid_first,int index_second,char* goodsid_second)
{
	memset(g_out_buf,0,sizeof(g_out_buf));
	Warehouse *warehouse=hero->getWarehouse();
	if (warehouse==NULL)
	{
		return;
	}
	int grid_num=warehouse->getGridNum();
	if (index_second>grid_num)
	{
		warehouse->msg_drag_failed(g_out_buf);
		cout<<"index_second>grid_num"<<endl;
	}
	else
	{
		if (warehouse->isGridExistGoods(index_second))
		{
			if (strcmp(goodsid_first,goodsid_second)==0)
			{
				int number_first=warehouse->getGridGoodsNum(index_first);
				int number_second=warehouse->getGridGoodsNum(index_second);
				int type=getGoodsType(goodsid_first);
				int repeat;
				if (type==0)
				{
					cout<<"jolly:goodstype is error warehouse_operator 108"<<endl;
				}
				else if (type==1)
				{
					repeat=1;
				}
				else if (type==4)
				{				
					map<string,Goods_Config*>::iterator cl_it;
					cl_it=id_to_cl.find(goodsid_first);
					if (cl_it==id_to_cl.end())
					{
						cout<<"jolly:According  to the goodsid can't find the goods in warehouse_operator 120"<<endl;
					}
					else
					{
						Goods_Config *goods=cl_it->second;
						repeat=goods->getRepeat();
					}
				}
				else 
				{
					map<string,Goods_Config*>::iterator dj_it;
					dj_it=id_to_dj.find(goodsid_first);
					if (dj_it==id_to_dj.end())
					{
						cout<<"jolly:According th the goodsid can't find the goods in warehouse_operator 134"<<endl;
					}
					else
					{
						Goods_Config *goods=dj_it->second;
						repeat=goods->getRepeat();
					}
				} 
				int totalNum=number_first+number_second;
				if (totalNum>repeat)
				{
					number_second=repeat;
					number_first=totalNum-repeat;
					warehouse->saveGoodsInWarehouse(goodsid_second,number_second,index_second);
					warehouse->saveGoodsInWarehouse(goodsid_first,number_first,index_first);
					warehouse->msg_drag_success(g_out_buf,sizeof(g_out_buf),index_second,index_first);
				}
				else
				{
					number_second=totalNum;				
					warehouse->saveGoodsInWarehouse(goodsid_second,number_second,index_second);
					warehouse->initGrid(index_first);
					warehouse->msg_drag_success(g_out_buf,sizeof(g_out_buf),index_second,index_first);
				}
			}
			else
			{
				int number_first=warehouse->getGridGoodsNum(index_first);
				int number_second=warehouse->getGridGoodsNum(index_second);
				warehouse->initGrid(index_first);
				warehouse->initGrid(index_second);
				warehouse->saveGoodsInWarehouse(goodsid_first,number_first,index_second);
				warehouse->saveGoodsInWarehouse(goodsid_second,number_second,index_first);
				warehouse->msg_drag_success(g_out_buf,sizeof(g_out_buf),index_second,index_first);
			}
		}
		else
		{
			// cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
			// cout<<"second is empty"<<endl;
			// cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
			int number=warehouse->getGridGoodsNum(index_first);
			warehouse->saveGoodsInWarehouse(goodsid_first,number,index_second);
			warehouse->initGrid(index_first);
			warehouse->msg_drag_success(g_out_buf,sizeof(g_out_buf),index_second,index_first);
		}
	}
	send_msg(hero->getFd(),g_out_buf);
}

void warehouse_destory_goods(Hero *hero,char* identity,int index)
{
	Warehouse *warehouse=hero->getWarehouse();
	if (warehouse==NULL)
	{
		return;
	}
	int type=getGoodsType(identity);
	char goodsid[40]={'\0'};
	strncpy(goodsid,identity,sizeof(goodsid));
	if (type==1)
	{
		// Bag *bag=pg_hero->getBag();
		strncpy(goodsid,hero->identity_to_goodsid(identity),sizeof(goodsid));
		hero->deleteEquip(identity);
	}
	warehouse->initGrid(index);
	char msg[150]={'\0'};
	warehouse->msg_delete_goods(msg,type,index,goodsid);
	send_msg(hero->getFd(),msg);
}

void warehouse_destory_goods_byNum(Hero *hero,char* identity,int num)
{
	if (hero==NULL||identity==NULL)
	{
		return;
	}
	
	Warehouse *warehouse=hero->getWarehouse();
	if (warehouse==NULL)
	{
		return;
	}
	
	char goodsid[40]={'\0'};	
	char msg[150]={'\0'};
	int type;
	int warehouseNum=warehouse->getGridNum();
	for (int i=0;i<warehouseNum;i++)
	{
		type=getGoodsType(identity);
		strncpy(goodsid,identity,sizeof(goodsid));
		if (type==1)
		{
			strncpy(goodsid,hero->identity_to_goodsid(identity),sizeof(goodsid));
			hero->deleteEquip(identity);
		}
		warehouse->initGrid(i);
		warehouse->msg_delete_goods(msg,type,i,goodsid);
		send_msg(hero->getFd(),msg);
	}
}

bool takeGoodsToBag(Hero *hero,int index)
{
	Warehouse *warehouse=hero->getWarehouse();
	if (warehouse==NULL)
	{
		return false;
	}
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}
	char* identity=warehouse->getGridGoodsid(index);
	int type=getGoodsType(identity);
	int number=warehouse->getGridGoodsNum(index);
	char goodsid[40]={'\0'};
	strncpy(goodsid,identity,sizeof(goodsid));	
	if (!bag->bagIsFull(1))		//判断背包是否已满
	{			
		cout<<"111111111111111111111"<<endl;
		if (type==1)
		{
			// cout<<"!!!!!!!!   "<<identity<<endl;
			cout<<"222222222222222"<<endl;
			strncpy(goodsid,hero->identity_to_goodsid(identity),sizeof(goodsid));
			saveBagGoods(hero,goodsid,1,1,identity,3);
		}
		else
		{	
			saveGoodsInBag(hero,identity,number);
			cout<<"3333333333333333333"<<endl;
		}
		cout<<"4444444444444444444444"<<endl;
		warehouse->initGrid(index);
		char msg[150]={'\0'};
		warehouse->msg_delete_goods(msg,type,index,goodsid);
		send_msg(hero->getFd(),msg);
		return true;		
	}
	else
	{
		msg_error(g_out_buf,44);
		send_msg(hero->getFd(),g_out_buf);
		cout<<"warehouse is full in warehouse_operator 311"<<endl;
		return false;
	}
}

void destoryAllWarehouseGoods(Hero *hero,char* goodsid)
{
	Warehouse *warehouse=hero->getWarehouse();
	if (warehouse==NULL)
	{
		return;
	}
	int gridNum=warehouse->getGridNum();
	for (int index=0;index<gridNum;index++)
	{
		char* identity=warehouse->getGridGoodsid(index);
		if (strcmp(identity,goodsid)==0)
		{
			warehouse->initGrid(index);
			int type=getGoodsType(identity);
			char msg[150]={'\0'};
			warehouse->msg_delete_goods(msg,type,index,identity);
			send_msg(hero->getFd(),msg);
		}
	}
}