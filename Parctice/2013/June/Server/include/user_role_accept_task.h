/*
		文件类型：头文件
		文件名称：user_role_accept_task.h
		文件作用：声明客户端发送给服务器玩家是否接受任务方法
		  实现者：Evan
		完成时间：2012.5.18
*/
#ifndef USER_ROLE_ACCEPT_TASK
#define USER_ROLE_ACCEPT_TASK

#define ACCEPT_TASK_ACCEPTED_FULL_ERROR		1				//已接任务已满
#define ACCEPT_TASK_NO_THIS_TASK_ERROR		2				//任务ID错误
#define ACCEPT_TASK_ALREADY_ACCEPT_ERROR	3				//在已接任务列表中
#define ACCEPT_TASK_ALREADY_FINISH_ERROR	4				//已经完成的任务
#define ACCEPT_TASK_TIMES_LIMIT_ERROR		5				//每日限制次数达到
#define	ACCEPT_TASK_LEVEL_IS_LOW_ERROR		6				//等级太低
#define	ACCEPT_TASK_LEVEL_IS_HIGH_ERROR		7				//等级太高
#define ACCEPT_TASK_NOT_JOIN_CAMP_ERROR		8				//未加入阵营
#define ACCEPT_TASK_NOT_JOIN_GUILD_ERROR	9				//未加入帮派
#define ACCEPT_TASK_NOT_THIS_CAMP_ERROR		10				//接的阵营任务不是本阵营的
#define ACCEPT_TASK_PRE_NOT_FINISH_ERROR	11				//前置任务未完成
#define ACCEPT_TASK_PRE_NOT_ACCEPT_ERROR	12				//前置任务未接错误
#define ACCEPT_TASK_BAG_IS_FULL_ERROR		13				//玩家背包已满（开始有给道具的任务）
#define ACCEPT_TASK_SERVER_CONF_ERROR		14				//服务器任务配置错误
#define ACCEPT_TASK_TOO_FAR_ERROR			15				//离NPC太远
#define ACCEPT_TASK_SAME_TYPE_ERROR			16				//已接同类型的任务
#define ACCEPT_TASK_NO_CYCLE_TASK_ERROR		17				//没有这个循环任务ID


void taskAccept(char *buffer);
void GM_accept_one_task(char *buffer);
#endif

