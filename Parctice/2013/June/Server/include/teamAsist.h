#ifndef TEAM_ASIST_H
#define TEAM_ASIST_H

#include"team.h"

//队伍回调函数
void teamBindCal(struct ev_loop *loop,ev_timer *think,int revents);

//返回-1，表示异常，0：无组队，1，队员，2，队长,teamMum:表示队伍人数
int judgeHeroTeam(const Hero * heroMem,size_t &teamMum);

#endif

