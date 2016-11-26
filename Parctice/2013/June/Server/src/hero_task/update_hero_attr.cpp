/***********************************************************
 * 文件名：update_hero_attr.cpp
 * 文件描述：更新英雄属性，同时向客户端发送hero的新变动属性
 * 时间：2012.6.6 by bison
 ***********************************************************/

#include<iostream>
#include "hero.h"
#include"command_other_function_all_over.h"

using namespace std;

/**
 * hero_add_exp - 英雄增加经验
 * @hero: 要增加经验的英雄指针
 * @_exp: 增加的经验值
 * description: 对英雄的当前经验进行增加，如果没有升级向客户端发送经验变化，
 * 如果升级了，则向客户端发送全部变化信息
 */
void hero_add_exp(Hero *hero, unsigned _exp)
{
	string msgHead = "1";
	unsigned oldLevel = hero->getLevel();
	unsigned newLevel;
	string incExpMsg;
	
	incExpMsg = incExpMsg + msgHead + intTostring(ADDEXPRETURN);
	
	hero->setExpNow(_exp);
	newLevel = hero->getLevel();
	if (newLevel == oldLevel)
	{
		incExpMsg  = incExpMsg + intTostring(newLevel) + intTostring(hero->getExpNow());
		send_msg(hero->getFd(), const_cast<char *>(incExpMsg.c_str()));
		cout<<"Send no level up msg"<<endl;
		cout<<incExpMsg<<endl;
		
	} else {
		incExpMsg += intTostring(newLevel);
		incExpMsg += intTostring(hero->getExpForGrow());
		incExpMsg += intTostring(hero->getExpNow());
		incExpMsg += intTostring(hero->getLifeUpperVal());
		incExpMsg += intTostring(hero->getLifeVal());
		incExpMsg += intTostring(hero->getMagicUpperVal());
		incExpMsg += intTostring(hero->getMagicVal());
		incExpMsg += intTostring(hero->getOutAttack());
		incExpMsg += intTostring(hero->getInAttack());
		incExpMsg += intTostring(hero->getOutDefense());
		incExpMsg += intTostring(hero->getInDefense());
		send_msg(hero->getFd(), const_cast<char *>(incExpMsg.c_str()));
		cout<<"Send level up msg"<<endl;
		cout<<incExpMsg<<endl;
	}
	
}

