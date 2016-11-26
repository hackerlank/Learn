#ifndef MONSTER_OTHER_ACTION_FUNCTION_H
#define MONSTER_OTHER_ACTION_FUNCTION_H
#include"libev.h"
void monThkCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*测试怪物思考容器内容,测试用*/
void printMonThk(void);

/*怪物复活*/
void monReLifeCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*怪物回血*/
void monRecoverBooldCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*任务怪物回调函数*/
void monTaskCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*怪物cd回调函数*/
void monCdCalBal(struct ev_loop *loop,ev_timer *think,int revents);

#endif




	
