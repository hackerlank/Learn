#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include "money_operator.h"

extern Equip_Operator equip_operator[51];
using namespace std;
/*
* 返回值：0、数据异常；1、粗炼成功；2、不可锻造型装备 3、等级已满	 
*/
int EquipOperateKaiRen(Hero *hero, Equipment *equipment)
{
	if(hero == NULL || equipment == NULL) 	
	{	
		return 0;
	}

	if(equipment->gettype() == 0||equipment->gettype() == 13)	
	{
		return 2;
	}
	
	if (equipment->getrank()==1)
	{
		return 2;
	}
		
	int level = equipment->getKaiRenLevel();		//装备当前的粗炼等级 tory_01_25 unfinished等级限制提示

	//第一，粗炼等级是否超出了装备的粗炼等级上限,失败代码：3
	if (level>=50)
	{
		cout<<"kairen error in kaiRen.cpp 34"<<endl;
		return 3;
	}
	level++;
	if (equip_operator[level].kaiRenAdd==-1)
	{	
		cout<<"outside of the control grade"<<endl;
		return 3;
	}
	//第二，玩家现有的金钱是否够此次粗炼升级
	if (useBoundGameMoney(hero,equipment->getKaiRenCost()))
	{
		equipment->kaiRenAttributeIncrease(hero,level);		
		equipment->wareEquipSetBound();
		memset(g_out_buf,0,sizeof(g_out_buf));
		equipment->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
		send_msg(hero->getFd(), g_out_buf);			
		
		if (equipment->getIsBag()==1)
		{
			hero->send_msg_att();
		}
		return 1;
	}	
	else 
	{
		return 4;
	}
}