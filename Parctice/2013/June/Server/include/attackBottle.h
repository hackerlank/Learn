/************************************************************
	文件名：attackBottle.h
	文件作用：定义九宫格辅助功能函数
	作者：chenzhen
	创建日期：2012.12.13
************************************************************/
#ifndef ATTACK_BOTTLE_H
#define ATTACK_BOTTLE_H
#include"bottle.h"
class Hero;

/*攻击瓶罐的通信函数*/
void attactBottleCom(char *buffer);

/*攻击瓶罐函数*/
void attackBottle(Hero *attHero,char* skillId,Bottle *bottInst);

/*宠物攻击瓶罐函数*/
void petAttackBottle(char *ownerId,char *identity,Point piexPt,char *skillId,Bottle *bottInst);

#endif