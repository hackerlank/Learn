#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
using namespace std;
/*
	完成内容：玩家穿装备的辅助方法实现
	完成时间：2012.8.23
	完成人：Evan
*/
void wearEquip(Hero *hero,Equipment *equip)
{
	/*第一，判断玩家当前部位是否已经穿有装备*/
	// int type = equip->gettype();	
	//玩家身上相应部位穿有装备
						
	/*第二，穿上玩家申请要穿的装备*/
	equip->setBound(1);									//将装备设置为绑定状态
	
	int iswear = 1;
	equip->setisbag(iswear);							//装备是否穿在身上 0，在背包内；1，在身上 evan add 2012.8.31
	
	// hero->setWearEquip(type,equip);	//将要穿的装备添加到已穿装备集合
	// cout<<"*******the type:"<<type<<endl;
	// cout<<"size:"<<hero_equipment_map.size()<<endl;
	int type_num = 1;
	ChangeEquipToHero(hero,equip,type_num);				//改变角色属性
	/*玩家脱去的装备是否属于玩家身上套装的一部分  evan add 2012.8.31*/
	int type_n = 1;//玩家穿装备
	SuitManage(hero,equip,type_n);
	
}
/*
	完成内容：玩家身上套装的管理,type=1，玩家穿装备，type=2，玩家脱装备
	完成时间：2012.8.31
	完成人：Evan
*/
int  SuitManage(Hero *hero,Equipment *equip,int type)
{
	string suit_id = equip->getsuit_id();
	if(suit_id != "0")
	{cout<<"*****************suit start start************************************"<<endl;
		int number = 0;
		string msg = "3";
		msg = msg + intTostring(HERO_SUIT_NUMBER); 
		map<string,int> suits = hero->getsuitlist();
		cout<<"suits_size:"<<suits.size()<<endl;
		map<string,int>::iterator suits_iter;
		suits_iter = suits.find(suit_id);
		if(suits_iter == suits.end())
		{//玩家身上没有此类套装
			number = 1;
		}else{
		//玩家身上穿有此类套装
			number = suits_iter->second;
			switch(type)
			{
				case 1:
					//玩家穿装备
					number = number + 1;
					break;
				case 2:
					//玩家脱装备
					number = number - 1;
					break;
			}
		}
		suits[suit_id] = number;
		hero->setsuitlist(suits);
		msg = msg + "," + suit_id;
		msg = msg + intTostring(number);
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));  //发送给当前玩家
		cout<<"suits_size:"<<suits.size()<<endl;
		cout<<"msg:"<<msg<<endl;
		cout<<"********************suit end end*********************************"<<endl;
	}
	return 0;
}		
/*
	完成内容：更换装备导致玩家自身属性改变的方法实现，type=-1：脱装备；type=1:穿装备；
	完成时间：2012.8.23
	完成人：Evan
*/
void ChangeEquipToHero(Hero *hero,Equipment *equip,int type)
{   
	MemHero* memHero = hero->memHero;
	if(memHero == NULL)
	{
		return ;
	}

	hero->setLifeUpperVal(memHero->basicHeroData.lifeUpperVal + type*(equip->getlife()));		//生命上限值
	hero->setMagicUpperVal(memHero->basicHeroData.magicUpperVal + type*(equip->getMagic()));		//魔法上限值
	hero->setOutAttack(memHero->basicHeroData.outattack + type*(equip->getoutattack()));		//外功攻击
	hero->setInAttack(memHero->basicHeroData.inattack + type*(equip->getinattack())); 			//内功攻击
	hero->setOutDefense(memHero->basicHeroData.outdefense + type*(equip->getoutdefence()));		//外功防御
	hero->setInDefense(memHero->basicHeroData.indefense + type*(equip->getindefence()));		//内功防御
	hero->setHited(memHero->basicHeroData.hited + type*(equip->gethit()));						//命中
	hero->setCrit(memHero->basicHeroData.crit + type*(equip->getcrit()));						//暴击
	hero->setDodge(memHero->basicHeroData.dodge + type*(equip->getdodge()));					//闪避
	hero->setTenacity(memHero->basicHeroData.tenacity + type*(equip->gettenacity()));			//韧性	
}
