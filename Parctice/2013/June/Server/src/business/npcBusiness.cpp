#include"anyBusiness.h"
#include<map>
#include"hero.h"
#include <stdio.h>
#include <stdlib.h>
#include"commodity.h"
#include "money_operator.h"
extern map<string, Hero*> heroId_to_pHero;
extern int sock_fd;
extern map<int, Role*> fd_to_pRole;
extern map<string,Equip_config*>id_to_equip; 
extern map<string,Ointment *>id_to_ointment;
extern map<string,Goods_Config*> id_to_dj;				
extern map<string,Goods_Config*> id_to_cl;
extern Hero* pg_hero;
extern int g_msg_len;
extern char g_out_buf[20480];

//npc处购买物品
void npcBusinessBuy(char *buff)
{
	
	char *goodsIdChar;
	int goodsNum;//物品数量
	
	MSG_BEGIN(buff,g_msg_len);
	MSG_CHAR(goodsIdChar);
	MSG_INT(goodsNum);
	
	//初始化goodsType
	int goodsType=getGoodsType(goodsIdChar);
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	//角色是红名不能通过npc购买
	if(pg_hero->getisRedName())
	{
		msg_error(g_out_buf,107);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	//根据goodsid获取物品配置类获得价格
	int boundMoney;
	map<string,Equip_config * >::iterator equipIter;
	map<string,Goods_Config * >::iterator djIter;
	map<string,Goods_Config * >::iterator clIter;
	switch(goodsType)
	{
		//在装备容器查找物品实例
		case 1:
			equipIter =id_to_equip.find(goodsIdChar); 
			if(equipIter==id_to_equip.end())
			{			
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,1);
				// msg+="1";//错误信息 未找到该商品
				send_msg(pg_hero->getFd(),g_out_buf);
				return;
			}
			boundMoney=equipIter->second->getMoneyBound()*goodsNum ;	
			break;
		//在道具容器查找物品实例
		case 2:
			djIter = id_to_dj.find(goodsIdChar);
			if(djIter==id_to_dj.end())
			{
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,1);
				send_msg(pg_hero->getFd(),g_out_buf);
				return;
			}
			boundMoney=djIter->second->getMoneyBound()*goodsNum ;	
			break;
		//任务物品不能出售
		case 3:
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,2);
			send_msg(pg_hero->getFd(),g_out_buf);
			return;
			break;
		//在材料容器查找物品实例
		case 4:
			clIter = id_to_cl.find(goodsIdChar);
			if(clIter==id_to_cl.end())
			{
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,1);
				send_msg(pg_hero->getFd(),g_out_buf);
				return;
			}
			boundMoney=clIter->second->getMoneyBound()*goodsNum ;	
			break;
		//bison Added
		default:
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,1);
			send_msg(pg_hero->getFd(),g_out_buf);
			cout<<"BisonShow the goodsId is error! goodsId is "<<goodsIdChar<<endl;
			return;
	}		
	
	Bag *bag=pg_hero->getBag();
	if  (bag==NULL)
	{
		return;
	}
	
	if  (campareBoundGameMoney(pg_hero,boundMoney))
	{			
		//将物品存入玩家背包
		if(!saveGoodsInBag(pg_hero,goodsIdChar,goodsNum))
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,4);
			send_msg(pg_hero->getFd(),g_out_buf);
			cout<<"-----there is no this hero --------shopBusiness.cpp"<<endl;
			return;
		} 
		//判断是否完成任务 
		else 
		{
			useBoundGameMoney(pg_hero,boundMoney);
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,5);
			send_msg(pg_hero->getFd(),g_out_buf);
			if (goodsType == 1)
			{
				// if (pg_hero->getTaskState() & TASK_NEED_BUY_EQUIP)
				{
					if (pg_hero->updateHeroTaskStatus(BUY_EQUIP_TASK_NEED_TYPE, "equip", 1))
					{
						pg_hero->clrTskStSomeBit(TASK_NEED_BUY_EQUIP);
					}
				}	
				// if (pg_hero->getTaskState() & TASK_NEED_BUY_DAOJU)
				{
					if (pg_hero->updateHeroTaskStatus(BUY_DAOJU_TASK_NEED_TYPE, goodsIdChar, 1))
					{
						pg_hero->clrTskStSomeBit(TASK_NEED_BUY_DAOJU);
					}
				}
			}
			else if (goodsType == 2)
			{
				// if (pg_hero->getTaskState() & TASK_NEED_BUY_DAOJU)
				{
					if (pg_hero->updateHeroTaskStatus(BUY_DAOJU_TASK_NEED_TYPE, goodsIdChar, 1))
					{
						pg_hero->clrTskStSomeBit(TASK_NEED_BUY_DAOJU);
					}
				}
			}
		}
	}	
	else
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,7,3);
		send_msg(pg_hero->getFd(),g_out_buf);
		cout<<"use useBoundGameMoney failed  in  npcBusiness.cpp "<<boundMoney<<endl;
	}
}

void npcBusinessSell(char *buffer)
{
	int num;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(num);
	
	cout<<"14,8,"<<num;
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	if(pg_hero->getisRedName())
	{	
		msg_error(g_out_buf,64);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,23,0);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	int index[20];
	char *goodsid[20];
	int loop=0;
	
	set<int> luckGoodsIndex=bag->getLockIndex();
	set<int>::iterator it;
	for (it=luckGoodsIndex.begin();it!=luckGoodsIndex.end();++it)
	{
		cout<<"luckGoodsIndex:"<<*it<<endl;
	}
	
	for (loop=0;loop<num;loop++)
	{
		MSG_INT(index[loop]);
		MSG_CHAR(goodsid[loop]);
		cout<<","<<index[loop]<<","<<goodsid[loop];
		
		if (!bag->test(index[loop],goodsid[loop]))
		{
			cout<<endl<<"loop is :"<<loop<<endl;
			cout<<"test goods error index:"<<index[loop]<<"       goodsid:"<<goodsid[loop]<<endl;
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,23,0);
			send_msg(pg_hero->getFd(),g_out_buf);
			return;
		}
		
		if (bag->isLocking(index[loop]))
		{				
			memset(g_out_buf,0,sizeof(g_out_buf));
			msg_error(g_out_buf,146);
			send_msg(pg_hero->getFd(),g_out_buf);
			
			for (int i=0;i<loop;i++)
			{
				bag->goodsUnlockIndex(index[i]);
			}
			
			
			cout<<endl<<"loop:"<<loop<<endl;
			cout<<"goods is locking index:"<<index[loop]<<endl;
			
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,23,0);
			send_msg(pg_hero->getFd(),g_out_buf);
			return;
		}
		else
		{
			bag->goodsLockIndex(index[loop]);
		}		
	}
	cout<<endl;
	
	int totalMoney=0;
	int oneMoney=0;
	for (loop=0;loop<num;loop++)
	{		
		sellGoodsFromBag(pg_hero,index[loop],goodsid[loop],oneMoney);
		// cout<<"oneMoney is :"<<oneMoney<<endl;
		totalMoney+=oneMoney;
		bag->goodsUnlockIndex(index[loop]);
	}
	// cout<<"totalMoney is :"<<totalMoney<<endl;
	increaseBoundGameMoney(pg_hero,totalMoney);
}  

/*
* author: tory
* date: 2012.12.12
* describe: 装备修理,响应客户端14,10命令
*/
void repair(char *buff)
{
	MSG_BEGIN(buff, g_msg_len);
	MSG_INT(int repair_type);
	cout<<"@@Tory repair_type:"<<repair_type<<endl;
	
	//repair_type=0:按传入ID修理指定装备; repair_type=1:修理角色所穿的所有装备
	if(repair_type == 0)
	{
		MSG_CHAR_END(char* equip_id);
		cout<<"@@Tory equip_id:"<<equip_id<<endl;
	
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL || pg_hero->getMoney() == NULL) 
		{
			memset(g_out_buf, 0, 20480);
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,17,0);
			send_msg(pg_hero->getFd(), g_out_buf);
			return;
		} 
		
		//1、判断金钱		
		int repairCost = equipment->repairCost();
		if(useBoundGameMoney(pg_hero,repairCost) == false)
		{
			cout<<"you have not enough money in hero"<<endl;
			memset(g_out_buf, 0, 20480);
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,17,0);
			send_msg(pg_hero->getFd(), g_out_buf);
			return ;
		}
		
		//恢复装备的耐久度durability		
		equipment->repair();	
		//更新客户端装备面板数据
		memset(g_out_buf, 0, 20480);
		equipment->msg_return_equipInform(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
		
		memset(g_out_buf, 0, 20480);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,17,1);
		send_msg(pg_hero->getFd(), g_out_buf);
		return ;
		
	}else{	
		//修理身上的所有装备
		if(pg_hero->memHero == NULL)	return ;
		int i = 1;		//下标从1开始，最多12件装备
		for (i=1; i<13; i++)
		{
			if (pg_hero->memHero->wearequipdata[i].flag == 1)	//穿在身上
			{
				char* equip_id = pg_hero->memHero->wearequipdata[i].goodsid;
				if(strncmp(equip_id, "ZB", 2) != 0)		
					continue;		//装备ID错误
				
				Equipment* equipment = pg_hero->getEquip(equip_id);		
				if(equipment == NULL || pg_hero->getMoney() == NULL) 	
					continue;
		
				//1、判断金钱是否足够		
				int repairCost = equipment->repairCost();
				cout<<"@@Tory will cost:"<<repairCost<<endl;
				if(useBoundGameMoney(pg_hero,repairCost) == false)
				{
					cout<<"you have not enough money in hero"<<endl;
 					memset(g_out_buf, 0, 20480);
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,17,0);
					send_msg(pg_hero->getFd(), g_out_buf); 
					return ;	//金钱已不够，跳出循环,退出修理函数
				}		
				//恢复装备的耐久度durability		
				equipment->repair();
				
				//更新客户端装备面板数据
				memset(g_out_buf, 0, 20480);
				equipment->msg_return_equipInform(g_out_buf,sizeof(g_out_buf));
				send_msg(pg_hero->getFd(),g_out_buf);
			}
		}
		
		memset(g_out_buf, 0, 20480);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",14,17,1);
		send_msg(pg_hero->getFd(), g_out_buf);
		return ;
	
	}
	
}