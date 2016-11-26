/*      
函数：void buffupgrade(Hero *hero,Skill *skill)     
作用：buff技能升级
返回值：void
完成人：Evan
完成时间：2012.6.15
*/
#include<map>
#include<string>
#include<iostream>
#include"hero.h"
#include"skill.h"
#include"skill_struct.h"
#include"user_role_manage_skill.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include "money_operator.h"
using namespace std;
void buffupgrade(Hero *hero,Skill *skill)
{
	string msg = "3";
	msg = msg + intTostring(HERO_SKILL_UPGRADE);
	int num_value;
	map<string,Skill*> skill_list;
	skill_list = hero->getSkill_list();
	
	int skill_grade = skill->getskill_grade();
	skill_grade = skill_grade + 1;

	int control_grade = skill->getcontrol_grade();		
	if(skill_grade == 2)
	{
		control_grade += 2;
	}
	int useup_money = skill->getuseup_money();
	unsigned int useup_exp = skill->getuseup_exp();
	
	int level =hero->getLevel();
	int money = hero->getMoney()->money_getBoundGameMoney();
	unsigned int expNow = hero->getExpNow();	
	if(level<(control_grade+1))
	{cout<<"the grade is not"<<endl;
		return;
	}
	// cout<<"the money of hero:"<<money<<endl;
	// cout<<"the money of skill:"<<useup_money<<endl;
	if(money < useup_money)
	{
		num_value = 3;
		msg = msg + intTostring(num_value);
		send_msg(hero->getFd(),const_cast<char *>(msg.c_str()));
		return ;
	}	
	if(expNow < useup_exp)
	{
		num_value = 2;
		msg = msg + intTostring(num_value);
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
		return ;
	}
	useBoundGameMoney(hero,useup_money);		//从背包内删除游戏币
	hero->setExpNow(expNow-useup_exp, 1);	
	
	control_grade = control_grade+2;
	
	if(control_grade == 4)
	{
		useup_money = skillneedmoney(level,skill_grade,control_grade -1);
	}
	else
	{
		useup_money = skillneedmoney(level,skill_grade,control_grade);
	}
	
	// useup_money = skillneedmoney(level,skill_grade,control_grade);
	useup_exp = skillneedexp(control_grade);
	skill->setcontrol_grade(control_grade);
	skill->setuseup_money(useup_money);
	skill->setuseup_exp(useup_exp);
	skill->setskill_grade(skill_grade);
	
	string id = skill->getid();           					//技能Id
	/*
	int genuine = skill->getgenuine(); 						//真气
	int cxsjcz_buff = skill->getcxsjcz_buff();				//持续时间初值
	int cxsjcz_growup_buff = skill->getcxsjcz_growup_buff();//持续时间增长参数
	
	int smxh_buff = skill->getsmxh_buff();					//生命值消耗
	int zjngshbfb_buff = skill->getzjngshbfb_buff();		//内功伤害
	int zjwgshbfb_buff = skill->getzjwgshbfb_buff();		//外功伤害
	int	consumer_growth = skill->getconsumer_growth();		//技能消耗成长参数
	int xg_growup_buff = skill->getxg_growup_buff();	    //技能效果成长
	
	int zjsmsx_buff = skill->getzjsmsx_buff();    		    //buff增加生命上限
	
	int cd_time = skill->getcd_time();						//技能CD
	int cd_growup_buff = skill->getcd_growup_buff();        //技能cd成长参数
	*/
	int effect = skill->geteffect();
	switch(effect)
	{
		case 1:			
			skill->setgenuine(skill->getgenuine() + 190);    //真气成长
			skill->setcxsjcz_buff(skill->getcxsjcz_buff() + skill->getcxsjcz_growup_buff()); //持续时间初值成长
			break;
		case 2:			
			skill->setsmxh_buff(skill->getsmxh_buff() + skill->getconsumer_growth());         //生命值消耗成长			
			skill->setzjngshbfb_buff(skill->getzjngshbfb_buff() + skill->getxg_growup_buff());//内功伤害成长			
			skill->setzjwgshbfb_buff(skill->getzjwgshbfb_buff() + skill->getxg_growup_buff());//外功伤害成长
			break;
		case 3:		
			skill->setgenuine(skill->getgenuine() + 510);	//真气成长
			skill->setcxsjcz_buff(skill->getcxsjcz_buff() + skill->getcxsjcz_growup_buff()); //持续时间初值成长
			break;
		case 4:
			skill->setgenuine(skill->getgenuine() + 319);	//真气成长
			skill->setzjsmsx_buff(skill->getzjsmsx_buff() + skill->getxg_growup_buff());//buff增加生命上限成长
			break;
		case 5:
			skill->setgenuine(skill->getgenuine() + 151);	//真气成长
			skill->setcd_time(skill->getcd_time() - skill->getcd_growup_buff());//技能cd成长
			break;
	}
	
	skill_list[id] = skill;
	hero->setSkill_list(skill_list);
	num_value = 1;			//技能升级成功
	msg = msg + intTostring(num_value);
	msg = msg + "," + id;
	msg = msg + intTostring(skill_grade);
	msg = msg + intTostring(control_grade);
	msg = msg + intTostring(skill->getgenuine());//evan add 2012.9.26
	msg = msg + intTostring(useup_money);
	msg = msg + intTostring(useup_exp);//evan add 2012.10.13
	send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
	cout<<"the buff skill upgrade:"<<msg<<endl;
	skill->newmem();
	MemSkill *memskill = skill->getmemskill();
	MemHero *memhero = hero->memHero;
	int num = memhero->skilllists.size;
	for(int i=0;i<num;i++)
	{
		
		string id2 = memhero->skilllists.skills[i].id;
		cout<<"have id:"<<id2<<endl;
		if(id==id2)
		{
			memcpy(memhero->skilllists.skills+i, memskill, sizeof(MemSkill));
			break;
		}
	}
	cout<<"_____________________________________________________________"<<endl;
}
