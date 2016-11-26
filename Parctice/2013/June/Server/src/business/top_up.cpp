/*
	Author: Tory
	Date:	2012.1024
	Description:账户交互系统，角色申请从账户中提取刀币并将其转换成元宝
*/
#include "hero.h"
#include"wholeDefine.h"
#include "account_communication.h"
#include "money_operator.h"
#include "recharge_reward.h"
#include "system_activity_reward_assist.h"
#include "libev.h"

#define MAX_MSG_SIZE 200
#define USER_ANME_SIZE 50
#define RECHARGE_MSG_LEN 256
using namespace std;

extern int rechargeSrvFd; 

extern int g_msg_len;
extern Hero* pg_hero;

extern  Role *pg_role;

extern int sock_fd;

extern char server_name[10];

extern map<int, Role*> fd_to_pRole;

extern map<string, Hero*> heroId_to_pHero;

extern Recharge_reward *recharge_reward_asist;

static unsigned char recharge_msg[RECHARGE_MSG_LEN];

static char recharge_log[RECHARGE_MSG_LEN+MAX_MSG_SIZE];

static ev_timer *recharge_server_timer;
extern struct ev_loop *loops;
char keepalive_info[512];

void top_up(char* buffer)		
{
	int number;	//元宝数量；
	char msg_body[MAX_MSG_SIZE]={0}; 
	unsigned char msg_info[MAX_MSG_SIZE]={0};
	char msg_number[USER_ANME_SIZE]={0};
 	char account_id[USER_ANME_SIZE]={0};   

	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(number);//获取刀币数目；
	
	if(pg_role == NULL || pg_hero == NULL)
	{
		sprintf(recharge_log,"%d,%d,%s,%d,pg_hero||pg_role==NULL,pg_hero||pg_role==NULL,pg_hero||pg_role==NULL,%d,-1",10,0,server_name,(int)myTime.tv_sec,number);
		write_log(recharge_log);//写日志服务器；
		return;
	}

	if(number <= 0)
    {
		sprintf(msg_body,"14,10,3,%d,10,%s",number,pg_role->getUserName());
		send_msg(sock_fd,msg_body);

		//充值数目小于等于零退出；
		sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,1",10,0,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number);
		write_log(recharge_log);//写日志服务器；	
		
		cout<<"[XHM Warning]---(top_up.cpp):(top_up)::The Recharge number Error（less than zero）,we just return."<<endl;
        return;
    }
	
	sprintf(account_id,"LJ%s",pg_role->getUserName());		//生成账户名字；
	// cout<<"[XHM MSG] The account_id:"<<account_id<<" Ready to buy Gold ,size:"<<number<<endl;
	
	if(strlen(account_id)<=2)
	{
		sprintf(msg_body,"14,10,4,%d,10,%s",number,account_id+2);
		send_msg(sock_fd,msg_body);
		
		sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,2",10,0,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number);
		write_log(recharge_log);//写日志服务器；		
		
		cout<<"[XHM Warning] (top_up.cpp)strlen(account_id) == 0,we just return."<<endl;
		return ;
	}
	
	int size = 0, totalLen = 0;
	size = strlen(account_id);
	msg_info[0] = size;	
	memcpy(msg_info + 1, account_id, size);
	totalLen += size + 1;
	
	sprintf(msg_number, "%d", number);
	size = strlen(msg_number);
	msg_info[totalLen] = size;
	memcpy(msg_info + totalLen + 1, msg_number, size);
	totalLen += size + 1;
	
	size = strlen(pg_hero->getIdentity());
	msg_info[totalLen] = size;
	memcpy(msg_info + totalLen + 1, pg_hero->getIdentity(), size);
	totalLen += size + 1;

	size = strlen(pg_hero->getNickName());
	msg_info[totalLen] = size;
	memcpy(msg_info + totalLen + 1, pg_hero->getNickName(), size);
	totalLen += size + 1;

	size = strlen(server_name);
	msg_info[totalLen] = size;
	memcpy(msg_info + totalLen + 1, server_name, size);
	totalLen += size + 1;	
	
	
	
	memset(recharge_msg,0,sizeof(recharge_msg));
	recharge_msg[0]=255;//消息头的生成；
	recharge_msg[1]=216;	
	recharge_msg[2]=1;
	recharge_msg[3]=1;	
	// size=strlen((char*)msg_info);
	size=htonl(totalLen);//转换网络字节序；
	memcpy(recharge_msg+4,(char*)&size,4);
	
	/** size=0;//测试写入的大小对不对；
	 memcpy((char*)&size,recharge_msg+4,4);
	 cout<<"size:"<<size<<endl;*/
	// memcpy(recharge_msg+8,msg_info,strlen((char*)msg_info));
	memcpy(recharge_msg+8,msg_info,totalLen);


	// int ret = write(rechargeSrvFd, recharge_msg, 8 + strlen((char*)msg_info));
	int ret = write(rechargeSrvFd, recharge_msg, 8 + totalLen);
		
	sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,%d",10,9,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number,ret);
	write_log(recharge_log);//写日志服务器；

	if (ret == -1)
	{
		sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,%d",10,10,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number,ret);
		write_log(recharge_log);//写日志服务器；
		
		con_recharge_server();
		// ret = write(rechargeSrvFd, recharge_msg, 8 + strlen((char*)msg_info));
		ret = write(rechargeSrvFd, recharge_msg, 8 + totalLen);
		if (ret == -1)
		{
			sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,%d",10,11,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number,ret);
			write_log(recharge_log);//写日志服务器；
		
			sprintf(msg_body,"14,10,2,%d,10,%s",number,account_id+2);
			send_msg(pg_hero->getFd(),msg_body);		
			return;
		}else{
			sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,%d",10,12,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number,ret);
			write_log(recharge_log);//写日志服务器；		
		
		}
	}
	
#if 0	
	if(rechargeSrvFd == -1)//充值服务器宕机，重连接；
	{
		if(!con_recharge_server())
		{
			//充值服务器宕机，重新链接失败；
			cout<<"[XHM TEST] recharge_server is not working,To con_recharge_server ERROR!"<<endl;
		}else{
			cout<<"[XHM TEST] To con_recharge_server SUCCESS!"<<endl;
		}
	}

	
	int ret = write(rechargeSrvFd, recharge_msg, 8 + strlen((char*)msg_info));//将消息发送到充值服务器
	if(ret != strlen((char*)msg_info)+8)
	{
		cout<<"[XHM Warning] (top_up.cpp) write ERROR,we just return."<<endl;
		if(ret == -1)
		{
			if(rechargeSrvFd == -1)//充值服务器宕机，重连接；
			{
				if(!con_recharge_server())
				{
					//充值服务器宕机，重新链接失败；
					cout<<"[XHM TEST] recharge_server is not working,To con_recharge_server ERROR!"<<endl;
				}else{
					ret = write(rechargeSrvFd, recharge_msg, 8 + strlen((char*)msg_info));//将消息发送到充值服务器
					if(ret == strlen((char*)msg_info)+8)
					{
						cout<<"[XHM TEST] To con_recharge_server SUCCESS!"<<endl;
						
						sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,0",10,0,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number);
						write_log(recharge_log);//写日志服务器；
						
						return;
					}
				}
			}
		}
		sprintf(msg_body,"14,10,2,%d,10,%s",number,account_id+2);
		send_msg(pg_hero->getFd(),msg_body);	

		sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,3",10,0,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number);
		write_log(recharge_log);//写日志服务器；	
		
		return;
	}
#endif
	
	sprintf(recharge_log,"%d,%d,%s,%d,LJ%s,%s,%s,%d,0",10,0,server_name,(int)myTime.tv_sec,pg_role->getUserName(),pg_hero->getIdentity(),pg_hero->getNickName(),number);
	write_log(recharge_log);//写日志服务器；	
	return; 
}

void
recharge_srv_msg(char* buffer)
{
	MSG_BEGIN(buffer, g_msg_len);				//获取刀币数目；
	MSG_CHAR(char *flag);
	// printf("in the recharge_srv_msg flg:%d\n",*flag);	
	MSG_INT(int use_size);
	printf("in the recharge_srv_msg use_size:%d\n",use_size);		
	MSG_INT(int to_use_size);
	printf("in the recharge_srv_msg to_use_size:%d\n",to_use_size);		
	MSG_CHAR(char *hero_id);
	printf("in the recharge_srv_msg hero_id:%s\n",hero_id);		
	MSG_CHAR_END(char * acc_id);
	printf("in the recharge_srv_msg acc_id:%s\n",acc_id);	
	
	printf("the server Name:%s\n",server_name);		
	
	if (rechargeSrvFd!=sock_fd)
	{
		cout<<"rechargeSrvFd!=sock_fd"<<endl;
		return;
	}
	
	int recharge_flag=0;
	char msg_body[MAX_MSG_SIZE]={0}; 
	
	map<string, Hero*>::iterator iter=heroId_to_pHero.find(hero_id);
	if(iter == heroId_to_pHero.end())
	{
		//写到邮件
		// char title_email[128]={0};//TODO 奖励邮件提示信息，这些可以从配置文件上来；
		// char nickname_send[32]={0};
		// char content_email[256]={0};	

		// snprintf(nickname_send,32,"游戏官网");
		// snprintf(title_email,128,"购买元宝提示");	
		// snprintf(content_email,256,"武举人官网通知您：您在%d年%d月%d日到%d日购买%d元宝时\:成功购买元宝数目:%d\:！",\
			// consume_reward_time_conf.year,consume_reward_time_conf.month,consume_reward_time_conf.start_day,consume_reward_time_conf.end_day);
	
		// Mail_Txt mail(nickname_send, title_email, content_email);//构建收件箱中的邮件数据
		// mail.isRead = 1;//收件箱内未读
	
		// char* uuid = cid();
		// strcpy(mail.mail_id,uuid);//生成邮件的Id
		// free(uuid);	
		
		sprintf(recharge_log,"%d,%d,%s,%d,%s,%s,%s,%d,%d,%d,%d",10,1,server_name,(int)myTime.tv_sec,acc_id,hero_id,"找不到实例",to_use_size,use_size,flag[0],1);
		write_log(recharge_log);//写日志服务器；	
		
		return;
	}
	Hero* myHero=iter->second;	
	
	if(use_size <= 0)//充值不成功处理；							
	{
		sprintf(msg_body,"14,10,0,%d,10,%s",to_use_size-use_size,acc_id+2);
		send_msg(myHero->getFd(),msg_body);
		
		sprintf(recharge_log,"%d,%d,%s,%d,%s,%s,%s,%d,%d,%d,%d",10,1,server_name,(int)myTime.tv_sec,acc_id,hero_id,myHero->getNickName(),to_use_size,use_size,flag[0],2);
		write_log(recharge_log);//写日志服务器；	
		
		return;
	}else if(use_size == to_use_size){//充值成功，充值数据等于use_size,但是余额不足处理；
		recharge_flag=1;
	}
	
	if(myHero->getMoney() != NULL)					
	{
		cout<<"[XHM MSG] The system will increaseGold size:"<<use_size<<endl;		
		increaseGold(myHero,use_size);
		
		sprintf(recharge_log,"%d,%d,%s,%d,%s,%s,%s,%d,%d,%d,%d",10,1,server_name,(int)myTime.tv_sec,acc_id,hero_id,myHero->getNickName(),to_use_size,use_size,flag[0],0);
		write_log(recharge_log);//写日志服务器；
		
	}else{//如果实例下的金钱实例指针为零，写到邮件；
	
	
		sprintf(recharge_log,"%d,%d,%s,%d,%s,%s,%s,%d,%d,%d,%d",10,1,server_name,(int)myTime.tv_sec,acc_id,hero_id,myHero->getNickName(),to_use_size,use_size,flag[0],3);
		write_log(recharge_log);//写日志服务器；
		
		return;
	}

	if(!recharge_flag){//如果当前账户的刀币不足而且本次充值元宝没有完全成功；
		sprintf(msg_body,"14,10,0,%d,10,%s",to_use_size-use_size,acc_id+2);	
	}
	else{
		sprintf(msg_body,"14,10,1,%d,10",use_size);
	}	
	
	send_msg(myHero->getFd(),msg_body);
	
	increaseAccMoney(myHero,use_size);
	//充值奖励；
	if(recharge_reward_asist != NULL)
	{
		if(!isNowRechargeReward(time(NULL)))		
		{
			myHero->memHero->cum_recharge_awards=0;
			cout<<"[XHM MSG] !isNowRechargeReward"<<endl;
		}else{
			
			myHero->memHero->cum_recharge_awards+=use_size;
			int succ = recharge_reward_asist->add_to_reward_team(myHero->getIdentity(),myHero->memHero->cum_recharge_awards);
			if(succ==1)
			{
				myHero->memHero->cum_recharge_awards=0;
				myHero->memHero->recharge_time=time(NULL);
				cout<<"[XHM MSG]:recharge_reward_asist->add_to_reward_team ERROR<top_up.cpp> "<<msg_body<<endl;	
			}else{
				cout<<"[XHM MSG] recharge_reward_asist->add_to_reward_team Right!"<<endl;			
			}
		}
	}else{
		cout<<"[XHM MSG] recharge_reward_asist == NULL!"<<endl;		
	}	
};

/**消息回调函数；*/
static void
csd_keepalive_FinishCall(struct ev_loop *loop,ev_timer *think,int revents)
{
	if(think == NULL)
		return;
    ev_timer_stop(loop,think);
	
	//发送数据；
	int ret = write(rechargeSrvFd, keepalive_info, 10);
	// sprintf(recharge_log,"%d,%d,%s,%d,keepalive_info",10,13,server_name,(int)myTime.tv_sec);
	// write_log(recharge_log);//写日志服务器；	
	
	if(NULL == recharge_server_timer)//重新启动计时器
		recharge_server_timer = new ev_timer;
		
	ext_ev_timer_init(recharge_server_timer,csd_keepalive_FinishCall,30,0);
	ev_timer_start(loops,recharge_server_timer); 
}

void csd_keepalive()
{
	int totalLen=2;
	keepalive_info[0]=255;//消息头的生成；
	keepalive_info[1]=216;	
	keepalive_info[2]=0;
	keepalive_info[3]=0;	
	int size=htonl(totalLen);//转换网络字节序；
	memcpy(keepalive_info+4,(char*)&size,4);
	keepalive_info[8]=1;
	keepalive_info[9]=1;	
	

	if(NULL == recharge_server_timer)//启动计时器
		 recharge_server_timer = new ev_timer;
	
	ev_timer_init(recharge_server_timer,csd_keepalive_FinishCall,2,0);
	ev_timer_start(loops,recharge_server_timer); 
}