#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"hero.h"
#include"equipment.h"
#include "money_operator.h"

extern HeChengConfig g_heChengConfig;			//宝石合成配置数据

using namespace std;

int EquipOperateHeCheng(Hero *hero, int developMode,char* firstGoodsid, int first_index,char* secondGoodsid, int second_index,char* thirdGoodsid, int third_index,char *luckGoodsid,int index)
{	
	Bag *bag = hero->getBag(); 
    if (bag == NULL)
	{
		return 0;
	}
	
	if (!bag->test(first_index,firstGoodsid))
	{
		cout<<"firstGoods test error in heCheng.cpp 24"<<endl;
		return 5;
	}
	if (!bag->test(second_index,secondGoodsid))
	{
		cout<<"secondGoodsid test error in heCheng.cpp 29"<<endl;
		return 5;
	}
	if (!bag->test(third_index,thirdGoodsid))
	{
		cout<<"thirdGoodsid test error in heCheng.cpp 34"<<endl;
		return 5;
	}
	if (strcmp(luckGoodsid,"0")!=0)
	{	
		if (!bag->test(index,luckGoodsid))
		{
			cout<<"luckGoodsid test error in heCheng.cpp 39"<<endl;
			return 5;
		}	
	}
	
	if (strncmp(firstGoodsid+1,secondGoodsid+1,11)!=0)
	{
		cout<<"firstGoodsid and secondGoodsid are not suit in heCheng.cpp 40"<<endl;
		return 3;
	}
	if (strncmp(secondGoodsid+1,thirdGoodsid+1,11)!=0)
	{
		cout<<"secondGoodsid and thirdGoodsid are not suit in heCheng.cpp 45"<<endl;
		return 3;
	}
	if (strncmp(firstGoodsid+1,thirdGoodsid+1,11)!=0)
	{
		cout<<"firstGoodsid and thirdGoodsid are not suit in heCheng.cpp 50"<<endl;
		return 3;
	}
	
	if (developMode==0)
	{
		if (strncmp(firstGoodsid,"f",1)!=0)
		{
			cout<<"developMode is 0,but firstGoodsid error firstGoodsid:"<<firstGoodsid<<endl;
			return 4;
		}
		if (strncmp(secondGoodsid,"f",1)!=0)
		{
			cout<<"developMode is 0,but secondGoodsid error secondGoodsid:"<<secondGoodsid<<endl;
			return 4;
		}
		if (strncmp(thirdGoodsid,"f",1)!=0)
		{
			cout<<"developMode is 0,but thirdGoodsid error thirdGoodsid:"<<thirdGoodsid<<endl;
			return 4;
		}
	}
	else if (developMode==2)
	{
		if (strncmp(firstGoodsid,"b",1)!=0)
		{
			cout<<"developMode is 2,but firstGoodsid error firstGoodsid:"<<firstGoodsid<<endl;
			return 4;
		}
		if (strncmp(secondGoodsid,"b",1)!=0)
		{
			cout<<"developMode is 2,but secondGoodsid error secondGoodsid:"<<secondGoodsid<<endl;
			return 4;
		}
		if (strncmp(thirdGoodsid,"b",1)!=0)
		{
			cout<<"developMode is 2,but thirdGoodsid error thirdGoodsid:"<<thirdGoodsid<<endl;
			return 4;
		}
	}
	
	//宝石等级为最大了 不能合成
	if (firstGoodsid[10] - '0' == 3)
	{
		cout<<"firstGoodsid level is Max in heCheng.cpp 93"<<endl;
		return 2;		
	}
	if (secondGoodsid[10] - '0' == 3)
	{
		cout<<"secondGoodsid level is Max in heCheng.cpp 93"<<endl;
		return 2;		
	}
	if (thirdGoodsid[10] - '0' == 3)
	{
		cout<<"thirdGoodsid level is Max in heCheng.cpp 93"<<endl;
		return 2;		
	}
	
	int need_money = 0;	//金钱消耗
	int rate = 0;		//成功率*100
	if (firstGoodsid[10] - '0' == 0)
    {
		need_money = g_heChengConfig.cost[0];           
		rate = g_heChengConfig.rate[0];
    } 
	else if (firstGoodsid[10] - '0' == 1)
    {
        need_money = g_heChengConfig.cost[1];           
		rate = g_heChengConfig.rate[1];
    } 
	else if (firstGoodsid[10] - '0' == 2)
    {		
        need_money = g_heChengConfig.cost[2];           
		rate = g_heChengConfig.rate[2];
    }

	if (bag->bagIsFull(1))
	{
		return 10;
	}
	
	//f_cl_142_100
	//1、判断金钱是否足够
	if (useBoundGameMoney(hero,need_money))
	{	
		// 2、成功率的判定
		int randomNumber= random_number(1,100);			//获取1~100之间的一个随机数
		cout<<"randomNumber:"<<randomNumber<<endl;
		cout<<"rate:"<<rate<<endl;
		if(randomNumber >= rate)				//大于成功区间，宝石合成失败
		{				
			if (strcmp(luckGoodsid,"0")!=0)
			{
				useBagGoods(hero, luckGoodsid, index, 1);  
			}
			else
			{
				useBagGoods(hero, firstGoodsid, first_index, 1); 
			}
			return 6;
		}
		else
		{
			if (useBagGoods(hero, firstGoodsid, first_index, 1)==0)
			{
				if (useBagGoods(hero, secondGoodsid, second_index, 1)==0)
				{
					if (useBagGoods(hero, thirdGoodsid, third_index, 1)==0)
					{
						firstGoodsid[10]=firstGoodsid[10]+1;
						if (developMode==0)
						{
							firstGoodsid[0]='f';
						}
						else if (developMode==1)
						{
							if (strncmp(firstGoodsid,"f",1)==0&&strncmp(secondGoodsid,"f",1)==0&&strncmp(thirdGoodsid,"f",1)==0)
							{
								firstGoodsid[0]='f';
							}
							else
							{
								firstGoodsid[0]='b';
							}
						}
						else
						{
							firstGoodsid[0]='b';
						}
						
						saveGoodsInBag(hero, firstGoodsid, 1);
					}					
				}
				else
				{
					saveGoodsInBag(hero,firstGoodsid,first_index,1);
				}
			}
			else
			{
				saveGoodsInBag(hero,firstGoodsid,first_index,1);
			}
		}
		
		if (strcmp(luckGoodsid,"0")!=0)
		{
			useBagGoods(hero, luckGoodsid, index, 1);  
		}
		
		return 1;
	}
	
	return 10;
}
