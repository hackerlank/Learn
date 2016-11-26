/*      
函数：void beidongupgrade(Hero *hero,Skill *skill)     
作用：被动技能升级
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
#include"hero_help.h"
#include"user_role_manage_skill.h"
#include"money_operator.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
using namespace std;
void beidongupgrade(Hero *hero,Skill *skill)
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
	//if(level<(control_grade+1))
	if(level<(control_grade))
	{
		cout<<"BisonTest level is "<<level<<" control_grade is "<<control_grade<<endl;
		return;
	}
	if(money < useup_money)
	{
		num_value = 3;
		msg = msg + intTostring(num_value);
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
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
	string id = skill->getid();           		//技能Id
	
	int fjxgcs_growup_bd = skill->getfjxgcs_growup_bd();  //附加效果绝对值成长参数
	int effect = skill->geteffect();
	switch(effect){
		case 1:
				//技能提高生命上限绝对值
				skill->setsmsxjdz_bd(skill->getsmsxjdz_bd()+fjxgcs_growup_bd);
				hero->setLifeUpperVal(hero->getLifeUpperVal()+fjxgcs_growup_bd);
				hero->setLifeVal(hero->getLifeVal()+fjxgcs_growup_bd);		
				break;
		case 2:
			//韧性绝对值
				skill->setrxjdz_bd(skill->getrxjdz_bd()+fjxgcs_growup_bd);
				hero->setTenacity(hero->getTenacity()+fjxgcs_growup_bd);
				break;
		case 3:
			//闪避绝对值
				skill->setsbjdz_bd(skill->getsbjdz_bd()+fjxgcs_growup_bd);
				hero->setDodge(hero->getDodge()+fjxgcs_growup_bd);
				break;
		case 4:
			//暴击绝对值
				skill->setbjjdz_bd(skill->getbjjdz_bd()+fjxgcs_growup_bd);
				hero->setCrit(hero->getCrit()+fjxgcs_growup_bd);
				break;
		case 5:
			//命中绝对值
				skill->setmzjdz_bd(skill->getmzjdz_bd()+fjxgcs_growup_bd);	
				hero->setHited(hero->getHited()+fjxgcs_growup_bd);
				break;
		case 6:
			//外功伤害
				skill->setwgshbfb_bd(skill->getwgshbfb_bd()+fjxgcs_growup_bd);
				hero->setOutHurt(hero->getOutHurt()+fjxgcs_growup_bd);
				break;
		case 7:
			//外功攻击
				skill->setwggjbfb_bd(skill->getwggjbfb_bd()+fjxgcs_growup_bd);
				hero->setOutAttack(hero->getOutAttack()+fjxgcs_growup_bd);	
				break;
		case 8:
			//内功攻击
				skill->setnggjbfb_bd(skill->getnggjbfb_bd()+fjxgcs_growup_bd);			
				hero->setInAttack( hero->getInAttack()+fjxgcs_growup_bd);
				break;
		case 9:
			//外功防御
				skill->setwgfybfb_bd(skill->getwgfybfb_bd()+fjxgcs_growup_bd);		
				hero->setOutDefense(hero->getOutDefense()+fjxgcs_growup_bd);
				break;		
		case 10:
			//内功防御
				skill->setngfybfb_bd(skill->getngfybfb_bd()+fjxgcs_growup_bd);
				hero->setInDefense(hero->getInDefense()+fjxgcs_growup_bd);
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
	cout<<"the beidong skill upgrade:"<<msg<<endl;
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
			memcpy(memhero->skilllists.skills+i,memskill,sizeof(MemSkill));
			break;
		}
	}
	cout<<"_____________________________________________________________"<<endl;
}
