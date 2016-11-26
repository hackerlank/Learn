#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"hero.h"
#include"bag.h"
#include"map_inform.h"
#include"equipment.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"command_game_fight_manage.h"
#include "wholeDefine.h"
using namespace std;
extern map<string, Hero*> heroId_to_pHero;
extern int g_msg_len;
extern Hero* pg_hero;
extern char g_out_buf[20480];

//玩家装备的各种操作命令解析,处理（4,9命令）
void equiphelp_operate(char *buff)
{
	MSG_BEGIN(buff, g_msg_len);
	MSG_INT(int type);							//锻造类型
	
	/*获取道具的操作信息*/
	if(type < 0 || type > 5) return;
	
	bool isSuccess = false;
	//type: 0,开刃 1,熔炼 2,镶嵌 3，转移
	if(type == 0)		
	{	
		MSG_CHAR_END(char* equip_id);					//装备实例ID
		cout<<"4,9,"<<type<<","<<equip_id<<endl;
		
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL)
		{
			return;
		}
		
		//ret 0：失败，数据错误；1、成功； 2、不可锻造型装备；3、等级已到上限；4、金钱不够
		int ret = EquipOperateKaiRen(pg_hero, equipment);		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 9, 9, type, ret);
		send_msg(pg_hero->getFd(), g_out_buf);
		
		if(ret == 1)	
		{
			int level=equipment->getKaiRenLevel();
			
			memset(g_out_buf,0,sizeof(g_out_buf));
			equipment->msg_kaiRen(g_out_buf,sizeof(g_out_buf));
			send_msg(pg_hero->getFd(),g_out_buf);
			
			//更新玩家第一次粗炼任务的状态
			if (pg_hero->updateHeroTaskStatus(EQUIP_CUILI_TASK_NEED_TYPE, "tw000001", 1))
			{
				pg_hero->clrTskStSomeBit(TASK_NEED_FIRST_CUILI);
			}					
			//增加武林目标判定 jolly 12.13
			pg_hero->updataSingleTarget(2,0);
			
			if (level==10)
			{				
				//增加武林目标判定 jolly 12.13
				pg_hero->updataSingleTarget(4,1);
				
			}
			
			if (level==10||level==15||level==20)
			{				
				char info[1024]={'\0'};
				snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d",7,SYSTEM_WARN,"xf004",3,1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,4,equipment->getname(),equipment->getid(),equipment->getentityid(),pg_hero->getIdentity(),3,equipment->getKaiRenLevel(),0,0,0);
				map<string, Hero*>::iterator it_hero;

				for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
				{
					if (it_hero->second!=NULL)
					{						
						send_msg(it_hero->second->getFd(),info);
					}
				}
			}
		}	
	}
	else if(type == 1)
	{
		MSG_CHAR(char* equip_id);						//装备实例ID		
		MSG_CHAR(char* goodsid);
		MSG_INT(int index);
		cout<<"4,9,"<<type<<","<<equip_id<<","<<goodsid<<","<<index<<endl;
	
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL)
		{
			return;
		}
			
		int ret = EquipOperateRongLian(pg_hero, equipment, goodsid, index);		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 9, 9, type, ret);
		send_msg(pg_hero->getFd(), g_out_buf);		
		
		if (ret==1 ||ret==4)
		{
			memset(g_out_buf,0,sizeof(g_out_buf));
			equipment->msg_rongLian(g_out_buf,sizeof(g_out_buf),pg_hero->memHero->vipDailyData.rongLianRate); 
			send_msg(pg_hero->getFd(),g_out_buf);
			
			if (ret==1)
			{
				//更新第一次熔炼任务的状态数据
				if (pg_hero->updateHeroTaskStatus(EQUIP_JINGLIAN_TASK_NEED_TYPE, "tw000003", 1))
				{
					pg_hero->clrTskStSomeBit(TASK_NEED_FIRST_JINGLIAN);
				}

				int level=equipment->getRongLianLevel();
				//熔炼到制定等级,全服广播,jolly 12.13
				if (level==10)
				{
					//增加武林目标判定 jolly 12.13
					pg_hero->updataSingleTarget(4,3);
				}
				else if (level==20||level==25||level==30||level==35||level==40||level==45||level==50)
				{
					char info[1024]={'\0'};
					snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d",7,SYSTEM_WARN,"xf028",3,1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,4,equipment->getname(),equipment->getid(),equipment->getentityid(),pg_hero->getIdentity(),3,equipment->getRongLianLevel(),0,0,0);
					map<string, Hero*>::iterator it_hero;

					for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
					{
						if (it_hero->second!=NULL)
						{						
							send_msg(it_hero->second->getFd(),info);
						}
					}
				}
				//增加武林目标判定 jolly 12.13
				pg_hero->updataSingleTarget(2,4);
				if (level==50)
				{
					//增加武林目标判定 jolly 12.13
					pg_hero->updataSingleTarget(6,6);
				}
			}
		}
	}
	else if(type == 2)	//镶嵌操作
	{
		MSG_CHAR(char* equip_id);		//装备实例ID
		MSG_CHAR(char* goodsid);		//goodsid: 宝石类型id
		MSG_INT(int index);				//index: 宝石在背包中的下标
		cout<<"4,9,"<<type<<","<<equip_id<<","<<goodsid<<","<<index<<endl;
		
		/*镶嵌装备的实例*/
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL) 
		{
			return;
		}
		
		/*镶嵌操作处理,ret = 1,镶嵌成功*/
		int ret = EquipOperateXQ(pg_hero, equipment, goodsid, index);
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 9, 9, type, ret);
		send_msg(pg_hero->getFd(), g_out_buf);		
		
		//宝石镶嵌成功，增加武林目标判定 jolly 12.13
		if(ret == 1)
		{
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%d,%d", 8, 7, type, 1);
			send_msg(pg_hero->getFd(), g_out_buf);	
		
			pg_hero->updataSingleTarget(2,8);
		
			vector<string> xq_bs = equipment->getxq_bs();	 //装备上镶嵌的宝石的集合
			if(xq_bs.size()==6)	//已镶嵌满
			{
				//增加武林目标判定 jolly 12.13
				pg_hero->updataSingleTarget(5,0);
			}
		}	
	}
	else if(type == 3)	//移植
	{
		MSG_CHAR(char* equip_id);					//原装备实例ID
		MSG_CHAR_END(char* des_equip_id);				//目标装备实例ID
		cout<<"4,9,"<<type<<","<<equip_id<<","<<des_equip_id<<endl;
	
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL)
		{
			return;
		}		
		
		Equipment* desEquipment = pg_hero->getEquip(des_equip_id);		
		if(desEquipment == NULL)
		{
			return; 
		}
		
		/*装备移植*/
		int ret = EquipOperateYiZhi(pg_hero, equipment, desEquipment); 
		
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 9, 9, type, ret);
		send_msg(pg_hero->getFd(), g_out_buf);
		
		if (ret==1)
		{
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%d,%d", 8, 7, type, 1);
			send_msg(pg_hero->getFd(), g_out_buf);
			
			if (equipment->getHoleNumber()==6)
			{
				pg_hero->updataSingleTarget(5,0);
			}
		}
	}	
	else if(type == 4)	//宝石兑换
	{
		MSG_INT(int developMode);				//兑换模式：0：非绑定，1：混合
		MSG_CHAR(char* firstGoodsid);					
		MSG_INT(int first_index);				//first: 第一颗宝石在背包内的下标值
		MSG_CHAR(char* secondGoodsid);					
		MSG_INT(int second_index);				//second:第二颗宝石在背包内的下标值
		MSG_CHAR(char* thirdGoodsid);					
		MSG_INT(int third_index);				//three: 第三颗宝石在背包内的下标值
		MSG_CHAR(char *luckGoodsid);			//防爆道具id
		MSG_INT(int index);
		cout<<"4,9,"<<type<<","<<developMode<<","<<firstGoodsid<<","<<first_index<<","<<secondGoodsid<<","<<second_index<<","<<thirdGoodsid<<","<<third_index<<","<<luckGoodsid<<","<<index<<endl;
		
		int ret = EquipOperateHeCheng(pg_hero, developMode,firstGoodsid, first_index,secondGoodsid, second_index,thirdGoodsid, third_index,luckGoodsid,index);
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%d", 9, 9, type, ret);
		send_msg(pg_hero->getFd(), g_out_buf);
		
		if (ret ==1)
		{
			if (firstGoodsid[10] - '0' == 1)
			{
				pg_hero->updataSingleTarget(3,2);
			}
			else if (firstGoodsid[10] - '0' == 2)
			{
				pg_hero->updataSingleTarget(4,2);
			}	
			else if (firstGoodsid[10] - '0' == 3)
			{
				pg_hero->updataSingleTarget(5,2);		
			}
		}
	}
	else if(type == 5)	//宝石摘除
	{
		MSG_CHAR(char* equip_id);		//装备实例ID
		MSG_CHAR(char* goodsid);		//goodsid: 宝石id
		MSG_INT(int index);
		cout<<"4,9,"<<type<<","<<equip_id<<","<<goodsid<<","<<index<<endl;
		
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL)
		{
			return;
		}
		
		isSuccess = EquipOperateZQ(pg_hero, equipment, goodsid,index);
		
		memset(g_out_buf, 0, 20480);
		if(isSuccess == false)
		{
			sprintf(g_out_buf, "%d,%d,%d,%d", 9, 9, type, FAILED);
		}
		else
		{
			// sprintf(g_out_buf, "%d,%d,%d,%d", 9, 9, type, SUCCESS);
			sprintf(g_out_buf, "%d,%d,%d,%d", 8, 7, type, SUCCESS);
		}	
		send_msg(pg_hero->getFd(), g_out_buf);	
	}
}
