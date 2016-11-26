/************************************************************
	文件名：otherThingCalBack.h
	文件作用：定义瓶罐，陷阱，以及采集物品的刷出，和消失以及攻击的控制
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#ifndef OTHER_THING_CALL_BACK_H
#define OTHER_THING_CALL_BACK_H
#include"libev.h"

/*瓶罐打碎，以及重刷控制*/
void botThkCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*陷阱回调*/
void trapThkCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*可摘取物品，消失以及重刷控制*/
void takeGoodsThkCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*陷阱消失回调函数*/
void trapDispearCalBack(struct ev_loop *loop,ev_timer *think,int revents);

/*陷阱示警回调函数*/
void trapWarnCalBack(struct ev_loop *loop,ev_timer *think,int revents);

#endif