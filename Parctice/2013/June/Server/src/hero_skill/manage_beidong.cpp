/**************************************************
文件类型：被动技能管理

文件名称：manage_beidong.cpp

文件内容：被动技能处理

创建时间：2012.5.31

authou：	Evan

******************************************************/
#include<string>
#include<iostream>
#include"user_role_manage_skill.h"
#include"hero.h"
#include"skill.h"
#include"hero_help.h"
using namespace std;
void  beidonglearn(Hero *hero,Skill *skill)
{
	//cout<<"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"<<endl;
	//cout<<"the id of hero  is :"<<hero->getLifeUpperVal()<<endl;
	//cout<<"the id of skill is :"<<skill->getid()<<endl;
	//cout<<"YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY"<<endl;
	int effect = skill->geteffect();
	switch(effect)
	{
		case 1:
				//技能提高生命上限绝对值
				hero->setLifeUpperVal(hero->getLifeUpperVal()+skill->getsmsxjdz_bd());
				hero->setLifeVal(hero->getLifeVal()+skill->getsmsxjdz_bd());		
				break;
		case 2:
			//韧性绝对值
				hero->setTenacity(hero->getTenacity()+skill->getrxjdz_bd());
				break;
		case 3:
			//闪避绝对值
				hero->setDodge(hero->getDodge()+skill->getsbjdz_bd());
				break;
		case 4:
			//暴击绝对值
				hero->setCrit(hero->getCrit()+skill->getbjjdz_bd());
				break;
		case 5:
			//命中绝对值
				hero->setHited(hero->getHited()+skill->getmzjdz_bd());
				break;
		case 6:
			//外功伤害
				hero->setOutHurt(hero->getOutHurt()+skill->getwgshbfb_bd());
				break;
		case 7:
			//外功攻击
				hero->setOutAttack(hero->getOutAttack()+skill->getwggjbfb_bd());	
				break;
		case 8:
			//内功攻击		
				hero->setInAttack( hero->getInAttack()+skill->getnggjbfb_bd());
				break;
		case 9:
			//外功防御
	
				hero->setOutDefense(hero->getOutDefense()+skill->getwgfybfb_bd());
				break;		
		case 10:
			//内功防御
				hero->setInDefense(hero->getInDefense()+skill->getngfybfb_bd());
				break;	
		
	}
}