#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"hero.h"
#include"equipment.h"
using namespace std;
extern char g_out_buf[20480];
bool EquipOperateZQ(Hero *hero, Equipment *equipment, char* goodsid,int index)
{		
	if (hero==NULL||equipment==NULL)
	{
		return 0;
	}

	if(strlen(goodsid) != 12)	
	{
		return false;
	}
	
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		cout<<"jolly:bag is null in zhaiqu.cpp 27"<<endl;
		return false;
	}
	
	int num = equipment->getBsNumByTy(goodsid);
	cout<<"num:"<<num<<endl;
	if(num!=1)	//表示数据异常
	{
		cout<<"same jewel is error:"<<num<<endl;
		return 0; 
	}
	
	if (!bag->bagIsFull(1))
	{
		if (equipment->testDiamon(index,goodsid))
		{
			if (saveGoodsInBag(hero,goodsid,1)) //将摘取后的宝石放到背包内
			{
				equipment->delBsNumByTy(goodsid);
				
				equipment->diamonOff(hero,index);
				//如果是穿在身上的装备进行了镶嵌，需同时修改人物属性,装备是否穿在身上 0:在背包内；1:在身上
				if(equipment->getIsBag() == 1)
				{
					hero->send_msg_att();	//更新客户端的人物属性面板
				}				
				
				memset(g_out_buf,0,sizeof(g_out_buf));
				equipment->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
				send_msg(hero->getFd(), g_out_buf);	
			
				if (goodsid[10] - '0' == 3)
				{
					equipment->zhaiQuFourDiamon();
				}
				
				return true;
			}
			else 
			{
				cout<<"jolly:savegoodsinbag in zhaiqu.cpp 48"<<endl;
				return false;
			}
		}
		else
		{
			cout<<"jolly: testDiamon error in zhaiqu.cpp 55"<<endl;
			return false;
		}		
	}
	else
	{
		cout<<"jolly:bag is full in zhaiqu.cpp 59"<<endl;
		return false;
	}
}