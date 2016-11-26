#ifndef DROP_EQUIP_ACTION_H
#define DROP_EQUIP_ACTION_H
#include"libev.h"
/*红名被杀掉落装备回调函数*/
void dropEquipCalBak(struct ev_loop *loop,ev_timer *think,int revents);
#endif