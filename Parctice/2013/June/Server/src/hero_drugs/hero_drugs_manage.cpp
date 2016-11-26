/*
* Description：管理游戏中所有药品使用和下线药品保存
* Author: Tory
* Date	: 2012.10.27 
*/

#include "hero_drugs_manage.h"
#include "ointment.h"
#include "my_time.h"
#include"command_other_function_all_over.h"
#include "useGoods.h"

extern struct ev_loop *loops;
extern map<string, Ointment *>id_to_ointment;
extern map<string, Hero*> heroId_to_pHero;
extern char g_out_buf[20480];
extern Hero *pg_hero;

bool drug_use_interface(Hero *hero, char* type_id, int index) //药品使用接口
{
    map<string, Ointment *>::iterator iter = id_to_ointment.find(type_id);
    if (iter == id_to_ointment.end()) 
    {
        cout << "there is no this type drug" << endl;
        return false;
    }	
    Ointment *ointment = iter->second;
	
	int effect_type = ointment->getOintmentType();		//药品作用效果
    int cur_time = MY_TV_SEC; 	//当前时间	
	int resultUse = 0;
	int value=ointment->getValue();

	/* 一次性作用药品使用 */
	if(ointment->getType() == 0) 		
    {	
		//等级判断
		if (hero->getLevel() < ointment->getLevelLimits())
		{
			string msg;
			string msg_head = "3";									//
			msg += msg_head + intTostring(USE_DRUG_RETURN);			//1,2        
			msg += intTostring(0);									//3 使用一般药品等级不够，错误代码为：0
			send_msg(hero->getFd(), msg);
			return false;
		}

		int beforeTime=0;
		if (effect_type==0)
		{
			beforeTime=hero->bloodBottle;
		}
		else if (effect_type==1)
		{
			beforeTime=hero->magicBottle;
		}
		else 
		{
			return false;
		}
		
		if(cur_time - beforeTime < ointment->getCd())//已使用过，需检测冷却时间
		{
			return false;		
		}	
		
		//所有使用药品的条件已满足，检查背包中药品的数量并减少背包中药品的数量
		if(useBagGoods(hero,type_id,index,1))		
		{
			return false;
		}
		
		if (effect_type==0)
		{
			hero->bloodBottle=cur_time;
			if (hero->memHero->basicHeroData.lifeVal+value > hero->memHero->basicHeroData.lifeUpperVal)
			{
				hero->setLifeVal(hero->memHero->basicHeroData.lifeUpperVal);
			}
			else 	
			{
				hero->setLifeVal(hero->memHero->basicHeroData.lifeVal+value);
			}
		}
		else 
		{
			hero->magicBottle=cur_time;
			if (hero->memHero->basicHeroData.magicVal+value > hero->memHero->basicHeroData.magicUpperVal) 
			{
				hero->setMagicVal(hero->memHero->basicHeroData.magicUpperVal);
			}	
            else 
			{
				hero->setMagicVal(hero->memHero->basicHeroData.magicVal+value);
			}				
		}
		
		//生成消息用于客户端表现
		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%s,%d,%d,%d,%d", 3, 5, 1, hero->getIdentity(), hero->getLifeVal(), hero->getLifeUpperVal(),\
												hero->getMagicVal(), hero->getMagicUpperVal());	
						
		send_msg(hero->getFd(), g_out_buf);
		
		return true;
    }	
    else if (ointment->getType() == 1)		//持续恢复人物属性药,需考虑使用等级和堆叠上限，同时更新剩余量
	{
		memset(g_out_buf,0,sizeof(g_out_buf));
		if (hero->getLevel() < ointment->getLevelLimits())
		{
			msg_error(g_out_buf,18);
			send_msg(hero->getFd(), g_out_buf);
			return false;
		} 
		int factor=ointment->getFactor();
		int ointmentType=ointment->getOintmentType();
		if (ointmentType==12)
		{
			if (hero->memHero->bloodBagdata.value==0)
			{
				if(useBagGoods(hero,type_id,index,1))		
				{
					cout<<"@@Tory the number of drug isn't enough"<<endl;
					return false;
				} 
				else
				{
					cout<<"hero->memHero->bloodBagdata.value:"<<hero->memHero->bloodBagdata.value<<endl;
					if (hero->memHero->bloodBagdata.value==0)
					{
						hero->memHero->bloodBagdata.lastTime=myTime.tv_sec;
					}
					hero->memHero->bloodBagdata.value=ointment->getValue();
					hero->memHero->bloodBagdata.cd=ointment->getCd();
					hero->memHero->bloodBagRecoverValue=factor;
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",3,17,hero->memHero->bloodBagdata.value,hero->memHero->magicBagdata.value);
				}
			}
			else
			{
				msg_error(g_out_buf,61);
			}						
		}		
		else if (ointmentType==13)
		{
			if (hero->memHero->magicBagdata.value==0)
			{
				if(useBagGoods(hero,type_id,index,1))		
				{
					cout<<"@@Tory the number of drug isn't enough"<<endl;
					return false;
				} 
				else
				{
					if (hero->memHero->magicBagdata.value==0)
					{
						hero->memHero->magicBagdata.lastTime=myTime.tv_sec;
					}
					hero->memHero->magicBagdata.value=ointment->getValue();
					hero->memHero->magicBagdata.cd=ointment->getCd();
					hero->memHero->magicBagRecoverValue=factor;
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",3,17,hero->memHero->bloodBagdata.value,hero->memHero->magicBagdata.value);
				}
			}
			else
			{
				msg_error(g_out_buf,62);
			}			
		}		
		send_msg(hero->getFd(),g_out_buf);
		return true;
	}
	else if (ointment->getType() == 2)					//使用buff药
	{	
		effect_type=effect_type-2;
 		//等级判断
 		if (hero->getLevel() < ointment->getLevelLimits())
		{
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%d", 3, 19, 2);	//使用药品等级不够，错误代码为：2
		
			cout<<"@@Tory buff drug msg:"<<g_out_buf<<endl;
			send_msg(hero->getFd(), g_out_buf);
			return false;
		}  
	
		//isInvalid为false时，表示此类buff药正在使用当中
		if (hero->memHero->allBuffDrug[effect_type].level!=0)
		{
			if(ointment->getLevel() <= hero->memHero->allBuffDrug[effect_type].level)	//低等级覆盖高等级药，则使用失败，需返回给客户端失败标识
			{							
				memset(g_out_buf, 0, 20480);
				sprintf(g_out_buf, "%d,%d,%d", 3, 19, 0);	//小等级buff不能覆盖高等级buff，错误代码为：0
				send_msg(hero->getFd(), g_out_buf);
				return false;
			}			
			//移除buff药的作用效果						
			resultUse = attribute_decrease(hero, effect_type); 	
		}
		
 		//所有使用药品的条件已满足，检查背包中药品的数量并减少背包中药品的数量
		if(useBagGoods(hero,type_id,index,1))		
		{
			cout<<"@@Tory the number of drug isn't enough"<<endl;
			return false;
		} 
		
		strncpy(hero->memHero->allBuffDrug[effect_type].type_id, ointment->getId().c_str(),IDL);	
		hero->memHero->allBuffDrug[effect_type].level = ointment->getLevel();
		hero->memHero->allBuffDrug[effect_type].effect_value = ointment->getValue();
		hero->memHero->allBuffDrug[effect_type].remain_time = ointment->getCd();	//buff药仅需获取剩余时间
		//按buff药作用效果更改角色属性
		resultUse = attribute_increase(hero, effect_type); 	

		memset(g_out_buf, 0, 20480);
		sprintf(g_out_buf, "%d,%d,%d,%s,%d,%d,%d,%d", 3, 19, 1, hero->getIdentity(), effect_type+2, hero->memHero->allBuffDrug[effect_type].level, hero->memHero->allBuffDrug[effect_type].remain_time, resultUse);
		send_msg(hero->getFd(), g_out_buf);
		
		hero->send_msg_att();			//更新客户端的人物属性面板
		return true;
	}	
}

/*
* Author：Tory	
* Date:2012.11.12
* Description：添加buff药的作用效果，增加角色的属性点
*/
int attribute_increase(Hero* hero,int effect_type)
{
	if(hero == NULL)	
	{
		return 0;
	}
	
	MemHero* memHero = hero->memHero;
	if(memHero == NULL)
	{
		return 0;
	}
	
	switch(effect_type)
	{
		case 0:// 生命上限值
			return hero->getLifeUpperVal();
			break;
		case 1:// 魔法上限值
			return hero->getMagicUpperVal();
			break;
		case 2://命中
			return hero->getHited();
			break;
		case 3://暴击
			return hero->getCrit();
			break;
		case 4://闪避
			return hero->getDodge();
			break;
		case 5://韧性
			return hero->getTenacity();
			break;
		case 6://外功攻击
			return hero->getOutAttack();
			break;
		case 7://内功攻击
			return hero->getInAttack();
			break;
		case 8://外功防御
			return hero->getOutDefense();
			break;			
		case 9://内功防御
			return hero->getInDefense();
			break;
		default:
			break;
	}
}

/*
* Author：Tory	
* Date:2012.11.12
* modify: jolly 2013.3.26
* Description：移除buff药的作用效果，恢复角色的正常属性
*/
int attribute_decrease(Hero* hero,int effect_type)
{
	if(hero == NULL)	
	{
		return 0;
	}
	
	MemHero* memHero = hero->memHero;
	if(memHero == NULL)
	{
		return 0;
	}
	
	switch(effect_type)
	{
		case 0:// 生命上限值
			initBuffDrugData(effect_type,hero);
			if(hero->getLifeVal() > hero->getLifeUpperVal())//如果血量上限恢复到正常后，当前血量值>血量上限，则置为当前上限
				hero->setLifeVal(hero->getLifeUpperVal());
			return hero->getLifeUpperVal();
			break;
		case 1:// 魔法上限值
			initBuffDrugData(effect_type,hero);
			if(hero->getMagicVal() > hero->getMagicUpperVal())//如果魔法上限恢复到正常后，当前魔法值>魔法上限，则置为当前上限
				hero->setMagicVal(hero->getMagicUpperVal());
			return hero->getMagicUpperVal();
			break;
		case 2://命中			
			initBuffDrugData(effect_type,hero);
			return hero->getHited();
			break;
		case 3://暴击
			initBuffDrugData(effect_type,hero);
			return hero->getCrit();
			break;
		case 4://闪避
			initBuffDrugData(effect_type,hero);
			return hero->getDodge();
			break;
		case 5://韧性
			initBuffDrugData(effect_type,hero);
			return hero->getTenacity();
			break;
		case 6://外功攻击
			initBuffDrugData(effect_type,hero);
			return hero->getOutAttack();
			break;
		case 7://内功攻击
			initBuffDrugData(effect_type,hero);
			return hero->getInAttack();
			break;
		case 8://外功防御
			initBuffDrugData(effect_type,hero);
			return hero->getOutDefense();
			break;			
		case 9://内功防御
			initBuffDrugData(effect_type,hero);
			return hero->getInDefense();
			break;
		default:
			break;
	}
}

void bloodAndMagicBagAgain(char *buffer)
{	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",3,17,pg_hero->memHero->bloodBagdata.value,pg_hero->memHero->magicBagdata.value); //do not send identity any more by benliao 2012.11.29
	send_msg(pg_hero->getFd(),g_out_buf);
	if (pg_hero->memHero->expTimesCount>0)
	{
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d,%d,%d",3,19,1,pg_hero->getIdentity(),22,pg_hero->memHero->expTimes,pg_hero->memHero->expTimesCount,pg_hero->memHero->expTimes);
	send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void continueUseBuffDrug(Hero* hero)
{
	if(hero == NULL)
	{
		return;
	}
	
	// cout<<"1111111111111111111111111111111111111111111111"<<endl;
	// cout<<"2222222222222222222222222222222222222222222222"<<endl;
	// cout<<"3333333333333333333333333333333333333333333333"<<endl;
	// cout<<"4444444444444444444444444444444444444444444444"<<endl;
	
	int offlineTime = hero->memHero->offlineTime;//下线时间
    int cur_time = MY_TV_SEC; 	//当前时间	
	for(int i=0; i<10; i++)
	{
		// cout<<"hero->memHero->allBuffDrug[i].level:"<<hero->memHero->allBuffDrug[i].level<<endl;
		if (hero->memHero->allBuffDrug[i].level!=0)
		{
			int time_pass = cur_time - offlineTime;	
			if(hero->memHero->allBuffDrug[i].remain_time < time_pass)
			{
				initBuffDrugData(i,hero);
			}
			else
			{
				hero->memHero->allBuffDrug[i].remain_time -= time_pass;	//减去下线经过的时间

				memset(g_out_buf,0,sizeof(g_out_buf));
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d,%d,%d",3,19,1,hero->getIdentity(),i+2,hero->memHero->allBuffDrug[i].level, hero->memHero->allBuffDrug[i].remain_time, 0);
				send_msg(hero->getFd(), g_out_buf);		
			}
		}	
	}	
}

void initBuffDrugData(int index,Hero *hero)
{
	if (hero==NULL)
	{
		return;
	}
	if (index<0||index>9)
	{
		return;
	}
	memset(hero->memHero->allBuffDrug[index].type_id,0,sizeof(hero->memHero->allBuffDrug[index].type_id));
	hero->memHero->allBuffDrug[index].level=0;
	hero->memHero->allBuffDrug[index].effect_value=0;
	hero->memHero->allBuffDrug[index].remain_time=0;
}