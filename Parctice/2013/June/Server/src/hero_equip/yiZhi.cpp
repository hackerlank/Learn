#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"hero.h"
#include "money_operator.h"
#include"equipment.h"
using namespace std;
extern Equip_Operator equip_operator[51];
/*
返回值：0、数据异常；1、转移成功；2、不可锻造型装备 3、原装备粗炼等级太低 4、不是同一部位的装备
*/
int EquipOperateYiZhi(Hero *hero,Equipment *equipment, Equipment *desEquipment)
{
	if(hero == NULL || equipment == NULL || desEquipment == NULL)
	{
		return 0;
	}
	
	if(equipment->gettype() != desEquipment->gettype())
	{
		cout<<"equip type not suit in yizhi.cpp 28"<<endl;
		return 2;
	}
	
	if (equipment->gettype() ==0||equipment->gettype() ==13)
	{
		cout<<"equip type is 0 or 13 error in yizhi.cpp 34"<<endl;
		return 4;
	}
	
	if (desEquipment->getgrade()-10>equipment->getgrade())
	{
		cout<<"equip zhuanyi level expand too large in yizhi.cpp 36"<<endl;
		return 3;
	}
	
	if (useGold(hero,200))
	{
		int rongLianLevel=equipment->getRongLianLevel();
		int kaiRenLevel=equipment->getKaiRenLevel();
		int rank=equipment->getrank();
		int desRank=desEquipment->getrank();
		int tempRank=desRank-rank;
		if (tempRank<0)
		{
			tempRank=1;
		}
		else
		{
			tempRank+=1;
		}
		
		int finalRongLianLevel=rongLianLevel-tempRank*5;
		int finalKaiRenLevel=kaiRenLevel-tempRank*2;
		int desRongLianLevel=desEquipment->getRongLianLevel();
		int desKaiRenLevel=desEquipment->getKaiRenLevel();
		
		if (finalRongLianLevel<desRongLianLevel)
		{
			finalRongLianLevel=desRongLianLevel;
		}
		if (finalKaiRenLevel<desKaiRenLevel)
		{
			finalKaiRenLevel=desKaiRenLevel;
		}
		
		//源装备熔炼等级和开刃等级都降为0
		equipment->initRongLian(hero);
		equipment->initKaiRen(hero);	
		
		memset(g_out_buf,0,sizeof(g_out_buf));
		equipment->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
		send_msg(hero->getFd(), g_out_buf);		
		
		if (equipment->getIsBag()==1)
		{		
			hero->send_msg_att();
		}
		
		for (int i=desEquipment->getRongLianLevel()+1;i<=finalRongLianLevel;i++)
		{
			desEquipment->rongLianAttributeIncrease(hero,i);
		}
		
		for (int j=desEquipment->getKaiRenLevel()+1;j<=finalKaiRenLevel;j++)
		{
			desEquipment->kaiRenAttributeIncrease(hero,j);
		}
		
		desEquipment->wareEquipSetBound();	
		memset(g_out_buf,0,sizeof(g_out_buf));
		desEquipment->msg_return_equipInform(g_out_buf, sizeof(g_out_buf));
		send_msg(hero->getFd(), g_out_buf);		
		
		if (desEquipment->getIsBag()==1)
		{		
			hero->send_msg_att();
		}
	
		return 1;
	}	
	
	return 10;
}

void msg_yiZhi(Hero* hero, Equipment *src_quipment, Equipment *des_equipment)
{
    if (src_quipment == NULL || des_equipment == NULL) 
	{
		return;
	}
	
	EquipmentData* desEquipmentdata=des_equipment->getEquipmentData();
	if (desEquipmentdata==NULL)
	{
		return;
	}
	
	if(src_quipment->gettype() != des_equipment->gettype())
	{
		cout<<"equip type not suit in yizhi.cpp 28"<<endl;
		return;
	}
	
	if (src_quipment->gettype() ==0||src_quipment->gettype() ==13)
	{
		cout<<"equip type is 0 or 13 error in yizhi.cpp 34"<<endl;
		return;
	}
	
	if (des_equipment->getgrade()-10>src_quipment->getgrade())
	{
		cout<<"equip zhuanyi level expand too large in yizhi.cpp 36"<<endl;
		return;
	}	
		
    memset(g_out_buf, 0, sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",8,7,3,src_quipment->getBaseLife(),src_quipment->getBaseMagic(),src_quipment->getBaseOutAttack(),src_quipment->getBaseInAttack(),src_quipment->getBaseOutDefense(), src_quipment->getBaseInDefense(),src_quipment->getBaseHit(),src_quipment->getBaseCrit(),src_quipment->getBaseDodge(),src_quipment->getBaseTenacity());
			
	int rongLianLevel=src_quipment->getRongLianLevel();
	int kaiRenLevel=src_quipment->getKaiRenLevel();
	int rank=src_quipment->getrank();
	int desRank=des_equipment->getrank();
	int tempRank=desRank-rank;
	if (tempRank<0)
	{
		tempRank=1;
	}
	else
	{
		tempRank+=1;
	}
	
	int finalRongLianLevel=rongLianLevel-tempRank*5;
	int finalKaiRenLevel=kaiRenLevel-tempRank*2;
	int desRongLianLevel=des_equipment->getRongLianLevel();
	int desKaiRenLevel=des_equipment->getKaiRenLevel();
	
	if (finalRongLianLevel<desRongLianLevel)
	{
		finalRongLianLevel=desRongLianLevel;
	}
	if (finalKaiRenLevel<desKaiRenLevel)
	{
		finalKaiRenLevel=desKaiRenLevel;
	}
	
	float increasePer;

	increasePer=(float)equip_operator[finalRongLianLevel].rongLianAdd/1000.0;
	
	int lifeIncrease=des_equipment->getBaseLife()*increasePer;
	if (lifeIncrease>0&&lifeIncrease<finalRongLianLevel)
	{
		lifeIncrease=finalRongLianLevel;
	}
	int magicIncrease=des_equipment->getBaseMagic()*increasePer;
	if (magicIncrease>0&&magicIncrease<finalRongLianLevel)
	{
		magicIncrease=finalRongLianLevel;
	}
	int outAttackIncrease=des_equipment->getBaseOutAttack()*increasePer;
	if (outAttackIncrease>0&&outAttackIncrease<finalRongLianLevel)
	{
		outAttackIncrease=finalRongLianLevel;
	}
	int inAttackIncrease=des_equipment->getBaseInAttack()*increasePer;
	if (inAttackIncrease>0&&inAttackIncrease<finalRongLianLevel)
	{
		inAttackIncrease=finalRongLianLevel;
	}
	int outDefenseIncrease=des_equipment->getBaseOutDefense()*increasePer;
	if (outDefenseIncrease>0&&outDefenseIncrease<finalRongLianLevel)
	{
		outDefenseIncrease=finalRongLianLevel;
	}
	int inDefenseIncrease=des_equipment->getBaseInDefense()*increasePer;
	if (inDefenseIncrease>0&&inDefenseIncrease<finalRongLianLevel)
	{
		inDefenseIncrease=finalRongLianLevel;
	}

	increasePer=(float)equip_operator[finalKaiRenLevel].kaiRenAdd/1000.0;
	int hitIncrease=des_equipment->getBaseHit()*increasePer;
	if (hitIncrease>0&&hitIncrease<finalKaiRenLevel)
	{
		hitIncrease=finalKaiRenLevel;
	}
	int critIncrease=des_equipment->getBaseCrit()*increasePer;
	if (critIncrease>0&&critIncrease<finalKaiRenLevel)
	{
		critIncrease=finalKaiRenLevel;
	}
	int dodgeIncrease=des_equipment->getBaseDodge()*increasePer;
	if (dodgeIncrease>0&&dodgeIncrease<finalKaiRenLevel)
	{
		dodgeIncrease=finalKaiRenLevel;
	}
	int	tenacityIncrease=des_equipment->getBaseTenacity()*increasePer;	
	if (tenacityIncrease>0&&tenacityIncrease<finalKaiRenLevel)
	{
		tenacityIncrease=finalKaiRenLevel;
	}

	snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf), ",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", des_equipment->getlife()+lifeIncrease, des_equipment->getMagic()+magicIncrease, des_equipment->getoutattack()+outAttackIncrease, des_equipment->getinattack()+inAttackIncrease, des_equipment->getoutdefence()+outDefenseIncrease,des_equipment->getindefence()+inDefenseIncrease,des_equipment->gethit()+hitIncrease,des_equipment->getcrit()+critIncrease,des_equipment->getdodge()+dodgeIncrease,des_equipment->gettenacity()+tenacityIncrease);
    send_msg(hero->getFd(), g_out_buf);
}