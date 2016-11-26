/************************************************************
    文件名：entCpy.cpp
    文件作用：初进副本的方法
    作者：chenzhen
    创建日期：2012.06.21
************************************************************/
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"command_other_function_all_over.h"
#include"cpyLimit.h"
#include"cpyAsist.h"

#include"command_user_role_manage.h"
//包含所有宏定义的头文件
#include"other_define_data.h"
//返回头命令的宏定义头文件
#include"command_return_define_data.h"
//用户角色管理辅助函数头文件
#include"user_role_manage_assist.h"
//所有工具函数的头文件
#include"command_other_function_all_over.h"
#include"map_inform.h"
// #include "TD_Instancing.h"
//Tory 副本管理类
#include "instancing_manage.h"
//Tory 副本交互头文件
#include "instancing_communication.h"

#include"cpyManager.h"

extern int sock_fd;
extern int g_msg_len;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<int, Role*> fd_to_pRole;
extern map<string, Hero*> heroId_to_pHero;
extern Hero* pg_hero;
extern char server_name[10];
extern CpyManger *cpyManger;
//塔防副本管理类
extern Instancing_manage *Inst_MNG;  
 			
void entCpy(char *buffer)
{
	char *hero_id,*cpyTyeId,failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	
	int cpyRank;       
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*解析id*/
	MSG_CHAR(hero_id);	
	
	//解析副本类型号
	MSG_CHAR(cpyTyeId);
	
	/*解析副本难度*/
	MSG_INT(cpyRank);		
	
	if(strlen(pg_hero->getTeamerId()) == 0)
	{
		entCpyAsist(hero_id,cpyTyeId,cpyRank);
		return;
	}
	
	else
	{
		handleTeamLeaderOperateAsist(hero_id,cpyTyeId,cpyRank);
		return;
	}
}



void entCpyAsist(const char* hero_id,const char* _cpyTyeId,int cpyRank)
{
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	map<string,CpyLimit*>::iterator cpyLimt_it;
	bool isParty = false;		
	vector<string> heroId;  
    char cpyTyeId[100] = {'\0'};
	
	if(!hero_id || !_cpyTyeId)
	{
		cout<<"entCpyAsist argument is error:"<<endl;
		return;
	}
	
	strncpy(cpyTyeId,_cpyTyeId,strlen(_cpyTyeId));
	
	heroId.push_back(hero_id);
	
	/*帮派副本*/
	if (cpyRank == 3)
	{
		isParty = true;
	}	
	strncat(cpyTyeId,"_",strlen("_"));		
	appendNum(cpyTyeId,cpyRank,1);	
	
	/*是任务副本法海不懂爱*/
	if(strcmp(cpyTyeId,"021_0") == 0)
	{
		cout<<"the cpyTyeId is  the taskCpy:"<<cpyTyeId<<endl;
		return;
	}

#if 0	
	if(strncmp(cpyTyeId,"008",3) == 0)	//判断是不是进塔防副本
	{
		int ret = Inst_MNG->apply_td_inst(pg_hero, cpyTyeId);
		return;	
	}
#endif		
	
    // 先在普通副本中进行查找,找不到则尝试进入塔防副本
    cpyLimt_it = cpyId_to_cpyLimit.find(cpyTyeId);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		return;
	}
	else
	{
		Failure_Reason* failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason));		
		failure_reason->size = 0;

		if(!initFailReson(failure_reason))
		{
			cout<<"failure_reason is NULL:"<<endl;
			return;
		}
	
		if (cpyLimt_it->second == 0) return;
	
		/*资格审查*/
		if(!cpyLimt_it->second->qualifyExam(heroId,failure_reason,false,isParty))
		{			
			dealFailRson(failure_reason,failMsg,sizeof(failMsg));
			sendFailMsg(heroId,failMsg);			
			free(failure_reason);			
			return;
		}
		cpyLimt_it->second->assignRom(heroId);
		free(failure_reason); 
	
		/*记录进入副本的流水账 jolly 12.11 start*/
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",6,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),cpyLimt_it->second->getCpyId());
		write_log(account_msg);	
		/*记录进入副本的流水账 jolly 12.11 end*/
	}
}
