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

#include "instancing_manage.h"
//副本管理类的全局配置
extern int sock_fd;

extern map<string,CpyLimit*> cpyId_to_cpyLimit;

extern map<int, Role*> fd_to_pRole;

extern map<string, Hero*> heroId_to_pHero;

extern Instancing_manage *Inst_MNG;

/*使用道具进副本*/
void enterCpyByTool(char *buffer)
{
	//not implimented
}
