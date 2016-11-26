#ifndef TEAM_OPERATION
#define TEAM_OPERATION
#include "team.h"
#include"hero.h"
#include"user_role_manage_assist.h"
#include"command_other_function_all_over.h"

void cTeam(char *buff);				//创建队伍

void invited(char *buff);			//邀请加入队伍请求
	
void backInvited(char *buff);		//被邀请的人，是否同意邀请，加入队伍
	
void request(char *buff);			//请求加入队伍
	
void backRequest(char *buff);		//队长是否同意该请求，使其加入队伍
	
void kick(char *buff);				//踢人请求
		
void leave(char *buff);				//退出队伍请求

void detail(char *buff);		    //发布组队信息		

void refresh(char *buff);			//刷新组队信息

void dismiss(char *buff);			//队长解散队伍

void assignment(char *buff);		//转让队长

bool deleteTeamId(string aim,string teamId);

void acceptStateBack(char *buff);	//邀请组队前，对被邀请者组队或者无组队状态返回
#endif
