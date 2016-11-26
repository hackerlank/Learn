#ifndef MAP_ACTION_H
#define MAP_ACTION_H
#include"libev.h"
class Map_Cpy;
class Map_Src;

void MapThkCalBak(struct ev_loop *loop,ev_timer *think,int revents);

/*刷出野外boss*/
void brushMonsterActiveBoss(void);

/*重置野外boss*/
void initMonsterActiveBoss(void);

/*找到副本地图实例*/
Map_Cpy* findCpyMap(char *cpyMapId);

/*判断地图id为何种地图*/
int IsCpyMap(char *mapId);

/*找到普通地图实例*/
Map_Src* findSrcMap(char *mapId);

#endif