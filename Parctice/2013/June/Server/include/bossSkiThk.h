/************************************************************
	文件名：bossSkiThk.h
	文件作用：定义Boss延时性（即有计时器）技能思考函数原型
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#ifndef BOSS_SKILL_THK_H
#define BOSS_SKILL_THK_H
#include"libev.h"

/*定身思考函数原型,天罗地网*/
void monSkiCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*无敌回调函数*/
void monSkiUnEnemyCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*怪物cd和播放时间回调函数*/
void monCdCalBak(struct ev_loop *loop,ev_timer *think,int revents);

#endif