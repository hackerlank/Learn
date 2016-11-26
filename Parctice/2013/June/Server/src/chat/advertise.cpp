/*
		文件类型：实现文件
		文件名称：chat.cpp
		文件作用：实现（0系统、1世界、2阵营、3帮派、4附近、5队伍）的消息发送；
		修改人：  xhm
		修改时间：2012.7.12 13:56
*/
#include"chat.h"
#include "team.h"
#include "systemMessage.h"
#include"teamManager.h"
#include"GM.h"

static char msg_buf[20480];

extern int sock_fd;
extern Hero* pg_hero;
extern int g_msg_len;
extern set<string> ban_speak;
extern set<string> heroid_to_gm;
extern string GM_verify_password;
extern map<string, Hero*> heroId_to_pHero;
extern set<string> innerIPSet;
extern map<int, Message_Receive>   message_queue;
extern char server_name[10];


void advertise(char *buffers)
{	
	int numGoods=0;						//当前聊天框发送物品数目,有疑问RTX xhm；
	map<string,Hero*>::iterator iter;
	MSG_BEGIN(buffers,g_msg_len)
	MSG_CHAR(char* hero_id);
	MSG_CHAR(char* msg_obj);
	MSG_CHAR(char* counts);	
	memset(g_out_buf, 0, 20480);
	//增加禁言判断；
	set<string>::iterator iterSet = ban_speak.find(hero_id);	
	if(iterSet != ban_speak.end())
	{
		cout<<"[XHM MSG]:in the advertise.cpp Call the Function ban_speak,advertise Error!"<<endl;
		char msg_er[20]={'\0'};
		msg_error(msg_er,22);		
		send_msg(sock_fd,msg_er);
	
		sprintf(msg_buf,"4,21,5");	//禁言列表。
		send_msg(sock_fd,msg_buf);		
			
		return;
	}
	
	sprintf(msg_buf,"4,0,%s,%s,%s,%s",hero_id,pg_hero->getNickName(),msg_obj,counts);
	
	numGoods=atoi(counts);
	char* temp;
	int len=strlen(msg_buf);
	for(int row = 0; row < numGoods;row++)
	{
		MSG_CHAR(temp);	
		sprintf(msg_buf+len,",%s",temp);	
		len=strlen(msg_buf);		
	}
	MSG_CHAR_END(char* msg_info);
	cout<<"msg_info:"<<msg_info<<endl;
	sprintf(msg_buf+len,",%s",msg_info);	
	cout<<"msg_buf:"<<msg_buf<<endl;
	
	/**
	  发送数据给客户端；
	*/
	Map_Inform *map_now;
	map_now = pg_hero->getMap();            
	Nbox *box=map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);
	box->getStaInSrcVec(obj);	
	
	if (strcmp(msg_info,GM_verify_password.c_str())==0)
	{
		map<int, Message_Receive>::iterator it_msg;
		it_msg = message_queue.find(sock_fd);
		if (it_msg == message_queue.end())
		{
			cout<<"The user havn't connected with server when loginUser!!!!!!!!!!!!!!"<<endl;
			return;
		}
		char *userIP = it_msg->second.ip_str;
		cout<<"[XHM MSG]:Someone apply for GM permission,and he's heroID is "<<hero_id<<endl;
		set<string>::iterator it_ip;
		for (it_ip = innerIPSet.begin(); it_ip != innerIPSet.end(); it_ip++)
		{
			if (strncmp(userIP, (*it_ip).c_str(), (*it_ip).size()) == 0)
			{
				char GM_msg[100]={0};
				set<string>::iterator it;
				it=heroid_to_gm.find(hero_id);
				if (it==heroid_to_gm.end())
				{					
					heroid_to_gm.insert(hero_id);
					snprintf(GM_msg,sizeof(GM_msg),"%d,%d",16,2,1);
					send_msg(pg_hero->getFd(),GM_msg);
					systemSendMssage(pg_hero, (char*)("You are becoming a GameMaster now!"), 0);
				}
				else
				{
					heroid_to_gm.erase(it);					
					snprintf(GM_msg,sizeof(GM_msg),"%d,%d",16,2,0);
					send_msg(pg_hero->getFd(),GM_msg);
					systemSendMssage(pg_hero, (char*)("You are losing GameMaster rights now!"), 0);
				}
				cout<<"[XHM MSG]:Current GM counts: "<<heroid_to_gm.size()<<endl;
			}
			
		}	
		return;
	}
	
	int camp=-1;
	Guild*myGuild;	
	set<string> factionList;
	vector<string> teamMenber;
	char account_msg[1024]={0};
	
	switch(msg_obj[0])
	{

	case '0':		// 发送给系统；
		if(pg_hero!=NULL)
			send_msg(sock_fd,msg_buf);
		break;
		
	case '1':		// 发送给世界
	
		if (isWorldFreeTalk(pg_hero->getIdentity()))
		{
			for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
			{	
				send_msg(iter->second->getFd(),msg_buf);	
			}
			/*记录世界说话的流水账 jolly 2.20 start*/
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",13,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),msg_buf);
			write_log(account_msg);	
			/*记录世界说话的流水账 jolly 2.20 end*/
		}
		else
		{
			if (pg_hero->memHero->vipDailyData.callTimes>0)
			{
				for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
				{	
					send_msg(iter->second->getFd(),msg_buf);	
				}
				/*记录世界说话的流水账 jolly 2.20 start*/
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",13,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),msg_buf);
				write_log(account_msg);	
				/*记录世界说话的流水账 jolly 2.20 end*/
				pg_hero->memHero->vipDailyData.callTimes--;
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",7,7,pg_hero->memHero->vipDailyData.callTimes);
				send_msg(pg_hero->getFd(),g_out_buf);
			}
			else if (pg_hero->memHero->vipDailyData.callTimes==-1)
			{
				for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
				{	
					send_msg(iter->second->getFd(),msg_buf);	
				}
				/*记录世界说话的流水账 jolly 2.20 start*/
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s",13,0,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),msg_buf);
				write_log(account_msg);	
				/*记录世界说话的流水账 jolly 2.20 end*/
			}
			else
			{
				msg_error(g_out_buf,140);
				send_msg(pg_hero->getFd(),g_out_buf);
			}
		}		
		break;	
		
	case '2':		//发送给阵营；
		camp= pg_hero->getCamp();
		if(camp >= 0 && camp <= 2)
		{
			for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
			{	
				if(iter->second->getCamp()==camp)
					send_msg(iter->second->getFd(),msg_buf);
			}	
		}else{
			sprintf(msg_buf,"4,21,2");	//没有加入阵营，不能再阵营频道说话。
			send_msg(sock_fd,msg_buf);
		}
		break;
			
	case '3':	//发送给帮派；
		myGuild=pg_hero->getGuild();
		
		if(NULL==myGuild)
		{
			sprintf(msg_buf,"4,21,3");	//没有加入帮派，不能再帮派频道说话。
			send_msg(sock_fd,msg_buf);
			return;
		}
		factionList = myGuild->getMembsList();
		for(set<string>::iterator setIter=factionList.begin();setIter!=factionList.end();setIter++)
		{
			iter=heroId_to_pHero.find(*(setIter));
			if(iter!=heroId_to_pHero.end())
			{
				send_msg(iter->second->getFd(),msg_buf);
			}
		}
		break;
			
	case '4':										//发送给附近的人；
		box->sentBoxMsg(msg_buf);
		break;
		
	case '5':										//发送给队伍；
	{
		const char *teamId = pg_hero->getTeamerId();
		if(strlen(teamId) == 0)
		{
			sprintf(msg_buf,"4,21,4");	//没有加入队伍，不能再队伍频道说话。
			send_msg(sock_fd,msg_buf);	
			return;
		}
		
		TeamManager* teamManger = TeamManager::getManagerInst();
			
		Team *team = teamManger->getTeamHandle(teamId);
		
		if(!team)
		{
			cout<<"advertise team is NULL:"<<endl;
			return;
		}
		
		team->sendMsg(msg_buf);
		break;
	}
	  
	case '6':
		if( useBagGoods(pg_hero,"b_cl_109_100",1)==0 || useBagGoods(pg_hero,"f_cl_109_100",1)==0 )
		{		
			for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
			{	
				send_msg(iter->second->getFd(),msg_buf);	
			}				
		}
		else
		{
			sprintf(msg_buf,"4,21,1");	//没有号角，不能再世界频道说话。
			send_msg(sock_fd,msg_buf);
		}
		break;
	  
	case '7':
		if( useBagGoods(pg_hero,"b_cl_140_100",1)==0 || useBagGoods(pg_hero,"f_cl_140_100",1)==0 )
		{		
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d,%s,%s",4,25,1,1,msg_info,pg_hero->getNickName());
			for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
			{	
				send_msg(iter->second->getFd(),g_out_buf);	
			}				
		}
		else
		{
			msg_error(g_out_buf,134);
			send_msg(pg_hero->getFd(),g_out_buf);
		}
		break;
		
	//摆摊聊天	
	case '8':
		if(pg_hero->getGradeNow() >= 33)
		{
			for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
			{	
				send_msg(iter->second->getFd(),msg_buf);	
			}				
		}
		else
		{
			sprintf(msg_buf,"4,21,8");	//等级不够
			send_msg(pg_hero->getFd(),g_out_buf);
		}
		break;
		
    default:										//其他默认为不发送数据；
		{
			sprintf(msg_buf,"4,21,6");	//频道类型选择错误。
			send_msg(sock_fd,msg_buf);
			break;	
		}
	}	
}
