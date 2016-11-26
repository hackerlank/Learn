#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"hero.h"
#include"equipment.h"
#include "money_operator.h"

extern Equip_Operator equip_operator[51];
using namespace std;
/*
完成人：jolly
完成时间：2013.5.14
operate_type:0,普通精炼；1，元宝精炼
返回值：0、数据异常，不响应；1、精练成功；2、不可锻造型装备 3、等级已满；4、幸运值不够，精练失败；5、装备品级太低 6、没有矿精
熔炼为增加装备的本身属性,带成功率,需要消耗矿晶
*/
int EquipOperateRongLian(Hero *hero,Equipment *equip,char* goodsid, int index)
{
	if(hero == NULL || equip == NULL) 	
	{
		return 0;
	}	

	Bag *bag = hero->getBag(); 
    if (bag == NULL)	
	{
		return 0;	
	}
	
	if(equip->gettype() == 0||equip->gettype() == 13)	
	{
		return 2;
	}
	
	int level = equip->getRongLianLevel();	
	if(level>=50)		
	{
		cout<<"jolly:you have ronglian Max "<<endl;
		return 3; 
	}	
	level++;

	//第二，玩家是否有充足的金钱和矿精支持此次精炼
	int grade = equip->getgrade();			//装备等级
	int rank = equip->getrank();			//装备成色
	
	//验证该背包下标索引到的是矿精ID和数目是否足够
	if (bag->test(index,goodsid))
	{
		if (useBoundGameMoney(hero,equip->getRongLianCost()))
		{			
			//第三，成功率的判断
			int randomNumber = random_number(1,1000);	
			int luckyNumber = equip->getRongLianLucky();  			//幸运值
			int successNumber=equip_operator[level].rongLianPer+luckyNumber+hero->memHero->vipDailyData.rongLianRate*10;
			
			if(randomNumber > successNumber)		//大于成功区间，精练失败
			{	
				equip->rongLianFailed();	//精炼失败,增加失败次数		
				
				if (useBagGoods(hero, goodsid, index, 1)==0)	//精练失败，将背包中的矿精用掉一颗		
				{
					equip->msg_return_equipInform(g_out_buf,sizeof(g_out_buf));
					send_msg(hero->getFd(),g_out_buf);
					return 4;
				}
				else
				{
					msg_error(g_out_buf,14);
					send_msg(hero->getFd(),g_out_buf);
				}
			}
			else	//精炼成功
			{				
				if (useBagGoods(hero, goodsid, index, 1)==0)// 将背包中的矿精用掉一颗
				{		
					equip->rongLianAttributeIncrease(hero,level);	
					equip->wareEquipSetBound();					
					memset(g_out_buf,0,sizeof(g_out_buf));
					equip->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
					send_msg(hero->getFd(), g_out_buf);
					
					
					if (equip->getIsBag()==1)
					{
						hero->send_msg_att();
					}
					
					//精炼至满级，且为橙色，的装备（武器类型还要问冯伟亮），给头衔：神器拥有者
					if(level == 50 && equip->getrank() == 5)
					{
						hero->addTitle("T016");
					}
					return 1;
				}
				else
				{
					msg_error(g_out_buf,14);
					send_msg(hero->getFd(),g_out_buf);
				}
			}	
		}
	}
	else
	{
		cout<<"goodsid error in rongLian.cpp 180"<<endl;
		return 6;
	}	
	
	return 10;
}