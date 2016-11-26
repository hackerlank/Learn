/************************************************************
	文件名：boxAsist.cpp
	文件作用：定义九宫格辅助功能函数
	作者：chenzhen
	创建日期：2012.11.15
************************************************************/
#include"boxAsist.h"
#include"map_inform.h"
#include"hero.h"
#include"command_other_function_all_over.h"
#include"move_asist.h"

#include"statuaryHero.h"

extern map<string,StatuaryHero*> statuaryTypeToStatuaryHero;
extern map<string,Equipment*> dropEquipMent;
extern map<int, Role*> fd_to_pRole;

/*判断放入九宫格的类型是否正确*/
bool isStyObjTpe(int _type)
{
	if(_type < HERO_STYLE_TYPE || _type > STATUARY_STYLE_TYPE)
	{
		return false;
	}
	return true;
}


/*封装的消息发送函数，以九宫格发送*/
void SendMsgClass::sentBoxMsg(set<string> &nbox_id_set,char *msg,char *heroId)
{
    set<string>::iterator sty_it;
	Hero *hero;
	
    /*如果九宫格为空，或者消息为空，则返回*/
    if(nbox_id_set.empty() || msg == NULL || strlen(msg) == 0)
    {
        return;
    }
	
	
    /*遍历九宫格*/
    for(sty_it = nbox_id_set.begin(); sty_it != nbox_id_set.end(); sty_it++)
    {
		hero = heroid_to_hero(*sty_it);
		if(hero == NULL)
		{
			continue;
		}
		// if(!hero->getWalkingFlg()) 
		// {
			// continue;
		// }
		if(heroId != NULL && strcmp(hero->getIdentity(),heroId) == 0) 
		{
			continue;
		}
		
        send_msg(hero->getFd(),msg); 
	}
}

/*全地图发送消息*/
void SendMsgClass::sendMapMsg(Map_Inform *map_now,char *msg,int fd)
{
	set<int> fdSet;
	set<int>::iterator fd_it;
	/*如果地图为空，或者消息为空，则返回*/
	if(map_now == NULL || msg == NULL || strlen(msg) == 0)
	{
		return;
	}
	
	fdSet = map_now->getHeroFd();	
	
	/*如果地图没人，则返回*/
	if(fdSet.empty())
	{
		return;
	}
	
	/*如果是玩家信息，则过滤掉自身*/
	if(fd != -1)
	{
		fdSet.erase(fd);
	}
	
	/*消息发送*/
	for(fd_it = fdSet.begin();fd_it != fdSet.end();fd_it++)
	{
		cout<<"@@Tory my_infor to others:"<<msg<<endl;
		send_msg(*fd_it,msg);
	}
}


/*
* author:tory
* describe: 将整张地图的角色信息发送给指定的fd
*/
void SendMsgClass::sendMapMsg(Map_Inform *map_now, int fd)
{
	set<int>::iterator fd_it;
	/*如果地图为空，或者消息为空，则返回*/
	if(map_now == NULL || fd == -1)	return;
	set<int> fdSet;
	fdSet = map_now->getHeroFd();	
	
	/*如果地图没人，则返回*/
	if(fdSet.empty())	return;
	
	/*如果是玩家信息，则过滤掉自身*/
	fdSet.erase(fd);
	
	/*将其他角色的信息发送给自己*/
	for(fd_it = fdSet.begin(); fd_it != fdSet.end(); fd_it++)
	{
		map<int, Role*> ::iterator iterRole=fd_to_pRole.find(*fd_it);
        if(iterRole == fd_to_pRole.end())
			continue;
		Hero* otherHero = iterRole->second->getActive_hero();
		string othersMsg = CreateMessage::come_into_view(otherHero);
		cout<<"@@Tory others infor for me: "<<othersMsg<<endl;
		send_msg(fd, othersMsg);
	}
}

/*封装的消息发送函数，以九宫格发送,为相互看见的,主要用在玩家的消息发送*/
void SendMsgClass::sentBoxViewMsg(OneScreen &nbox_id_set,\
					char *msg,Map_Inform *map_now,Hero *myHero,int style)
{
	set<string>::iterator sty_it;	
	map<string,Equipment*>::iterator equip_it;
	map<string,StatuaryHero*>::iterator statuary_it;
	TakeGoods* seeTakeGoods;
	MonsterBase *seeMon;
	Bottle* seeBottle;
	Wagon *seeWgon;
	Trap* seeTrap;
	Pick* seePick;
	Pet* seePet;
	Hero *hero;   
	Equipment *seeEquip;
	StatuaryHero* seeStatuary;
    char *heroId;
   
    
     
	// cout<<"view chage sence  begin heroId:"<<myHero->getIdentity()<<endl;
	
    /*如果不是角色或者地图为空，后者消息为空，则返回*/
    if(map_now == NULL || myHero == NULL || msg == NULL || strlen(msg) == 0)
    {
		return;
    } 
	
	heroId = myHero->getIdentity();

    /*遍历九宫格*/
	set<string> *temp;
	string logStr;
	for (int i = 0; i < 10; i++)
	{
		
		switch(i) {
			case 0:
				temp = &nbox_id_set.heroSet;
                                break;
			case 1:
				temp = &nbox_id_set.monsterSet;
				break;
			case 2:
				temp = &nbox_id_set.petSet;
				break;
			case 3:
				temp = &nbox_id_set.wagonSet;
				break;
			case 4:
				temp = &nbox_id_set.bottleSet;
				break;
			case 5:
				temp = &nbox_id_set.takeSet;
				break;
			case 6:
				temp = &nbox_id_set.pickSet;
				break;
			case 7:
				temp = &nbox_id_set.dropEqpSet;
				break;
			case 8:
				temp = &nbox_id_set.trapSet;
				break;
			case 9:
				temp = &nbox_id_set.statuarySet;
				break;	
			default:
				break;
		}

		if (temp->empty())
		{
			continue;
		}
		
		for(sty_it = temp->begin(); sty_it != temp->end(); ++sty_it)
		{
			if (i == HERO_STYLE_TYPE)
			{
				hero = heroid_to_hero(*sty_it);
				if(hero == NULL)
				{
					continue;
				}
				// if(!hero->getWalkingFlg()) 
				// {
					// continue;
				// }
				if(heroId != NULL && (*sty_it) == heroId)
				{
					continue;
				}
					
				send_msg(hero->getFd(),msg); 
				viewStyleHero(myHero,hero,style);
				view_other_hero_move(myHero, hero);
			} else if (i == MONSTER_STYLE_TYPE)
			{
			
				seeMon = map_now->getMonsterObj(const_cast<char*>((*sty_it).c_str()));
				viewStyleMon(myHero,seeMon,style);
				view_mon_move(myHero, seeMon);
				
			}
			else if (PET_STYLE_TYPE == i)
			{
				seePet = id_to_getActivePet(const_cast<char*>((*sty_it).c_str()));
				viewStylePet(myHero,seePet,style);
			}
			else if(WAGON_STYLE_TYPE == i)
			{
				cout<<"view Wagon begin:"<<endl;
				seeWgon = getInstWgon(*sty_it);
				viewStyleWagon(myHero,seeWgon,style);
				cout<<"view Wagon end:"<<endl;
			}
			else if(BOTTLE_STYLE_TYPE == i)
			{
				seeBottle = map_now->getBotInst(const_cast<char*>((*sty_it).c_str()));
				viewStyleBottle(myHero,seeBottle,style);
				
			}
			else if(TAKEGOODS_STYLE_TYPE == i)
			{				
				seeTakeGoods = map_now->getTakeObj(const_cast<char*>((*sty_it).c_str()));
				viewStyleTakeGoods(myHero,seeTakeGoods,style);
			}
			else if(PICK_STYLE_TYPE == i)
			{
				seePick = map_now->getDropPickInst(const_cast<char *>((*sty_it).c_str()));
				// seePick = id_to_getPick(*sty_it);
				viewStylePick(myHero,seePick,style);
			}
			else if(TRAP_STYLE_TYPE == i)
			{
				seeTrap = map_now->getTrapInst(const_cast<char*>((*sty_it).c_str()));
				viewStyleTrap(myHero,seeTrap,style);
			}
			else if (DROP_EQUIP_STYLE_TYPE == i)
			{			
				equip_it = dropEquipMent.find(*sty_it);
				if(equip_it != dropEquipMent.end())
				{
					seeEquip = equip_it->second;
					viewStyleEquip(myHero,seeEquip, style);
				}
			
			}
			else if (STATUARY_STYLE_TYPE == i)
			{		
				cout<<"SendMsgClass::sentBoxViewMsg statuary begin:"<<endl;
				statuary_it = statuaryTypeToStatuaryHero.find(*sty_it);
				if(statuary_it != statuaryTypeToStatuaryHero.end())
				{
					seeStatuary = statuary_it->second;
					viewStyleStatuary(myHero,seeStatuary, style);
				}
				cout<<"SendMsgClass::sentBoxViewMsg statuary end:"<<endl;
			
			}
		}
	}
	
	// cout<<"view chage sence  end heroId:"<<myHero->getIdentity()<<endl;
}
		
       
      
