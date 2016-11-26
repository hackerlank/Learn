#include "systemMessage.h"
#include "hero.h"
#include"chat.h"
#include "team.h"
#include"boxAsist.h"
#include"team.h"
#include"teamManager.h"
static char msg_buf[20480];
static char placard_info[1024];

extern struct ev_loop *loops;

extern set<string> ban_speak;
extern map<string, Hero*> heroId_to_pHero;

void
SYSTEM_MESSAGE::systemMssage(Hero*msgSender,char* _msg,int Type)
{
	int camp=-1;
	if(NULL == msgSender)
		return;
		
	//增加禁言判断；
	set<string>::iterator iterSet = ban_speak.find(msgSender->getIdentity());
	if(iterSet != ban_speak.end())
	{
		cout<<"[XHM MSG]:in the systemMessage.cpp call the function ban_speak!"<<endl;
		return;
	}
	
	if(3==Type)
		snprintf(msg_buf,sizeof(msg_buf),"4,0,%s,%s,%d,5,%s",msgSender->getIdentity(),msgSender->getNickName(),Type+4,_msg);
	else
		snprintf(msg_buf,sizeof(msg_buf),"4,0,%s,%s,%d,0,%s",msgSender->getIdentity(),msgSender->getNickName(),Type,_msg);
	
	
	if(Type==0 && msgSender!=NULL)
	{
			send_msg(msgSender->getFd(),msg_buf);
	}
	else if(1==Type && msgSender!=NULL)	// 发送给世界；
	{
	    for(map<string,Hero*>::iterator iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
		{	
			if(iter->second->getLoadState() == true)
			{
				send_msg(iter->second->getFd(),msg_buf);
			}
		}	
	}
	else if(2==Type)	//发送给阵营；
	{
		camp=msgSender->getCamp();
		if(camp >=0 && camp <= 2)
		{
			for(map<string,Hero*>::iterator iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
			{	
				if(iter->second->getCamp()==camp)
					send_msg(iter->second->getFd(),msg_buf);
			}	
		}	
	}
	else if(3==Type && msgSender!=NULL)					//发送给帮派；
	{
		set<string> factionList;
		Guild*myGuild;
		
		myGuild=msgSender->getGuild();
		if(NULL==myGuild)
			return;
		factionList = myGuild->getMembsList();
		for(set<string>::iterator setIter=factionList.begin();setIter!=factionList.end();setIter++)
		{
			map<string,Hero*>::iterator iter=heroId_to_pHero.find(*(setIter));
			if(iter!=heroId_to_pHero.end())
			{
					send_msg(iter->second->getFd(),msg_buf);
			}
		}
	}
	else if(4==Type && msgSender!=NULL)						//发送给附近的人；
	{	
		Map_Inform *map_now;
		map_now = msgSender->getMap();    
		if(map_now == NULL)
		{
			return;
		}
		Nbox *box=map_now->getBox();
		if(box == NULL)
		{
			return;
		}
		StyObj obj(msgSender->getIdentity(),HERO_STYLE_TYPE);
		box->getStaInSrcVec(obj);
		box->sentBoxMsg(msg_buf);
	}
	else if(5==Type && msgSender!=NULL)									//发送给队伍；
	{
		const char* teamId= msgSender->getTeamerId();
		if(strlen(teamId) == 0)
		{
			return;
		}
		
		TeamManager* teamManger = TeamManager::getManagerInst();
			
		Team *team = teamManger->getTeamHandle(teamId);
		
		if(!team)
		{
			cout<<"SYSTEM_MESSAGE::systemMssage team is NULL:"<<endl;
			return;
		}
		
		team->sendMsg(msg_buf);
	}
	else
	{
		return;
	}
}

/*全区消息*/
void SYSTEM_MESSAGE::systemMssageAllEral(string& _msg,size_t level)
{
	map<string,Hero*>::iterator iter;
	
	if(heroId_to_pHero.empty() || _msg.size() < 1)
	{
		return;
	}	
	
	for(iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();++iter)
	{	
		if(iter->second->getGradeNow() >= level)
		{
			send_msg(iter->second->getFd(),const_cast<char*>(_msg.c_str()));
		}
	}
}


/**消息回调函数；*/
void
SystemActivityFinishCall(struct ev_loop *loop,ev_timer *think,int revents)
{
	if(think == NULL)
		return;
    ev_timer_stop(loop,think);
	
	systemMsg_T* myMsg = (systemMsg_T *)think->target;
	
	if(myMsg == NULL)
		return;
		
	if(myMsg->msg == NULL)
	{
		if(myMsg->system_activity_timer)
			delete myMsg->system_activity_timer;	
		delete myMsg;	
		
		return;
	}
	
	memset(placard_info,0,sizeof(placard_info));
	snprintf(placard_info,1023,"%s,%d,%d",myMsg->msg,myMsg->times,myMsg->interval_time);
	//全服发送消息；
	for(map<string, Hero*>::iterator iter=heroId_to_pHero.begin();iter!=heroId_to_pHero.end();iter++)
	{
		if(iter->second->getGradeNow() >= myMsg->level)
		{
			send_msg(iter->second->getFd(),placard_info); 	
		}
	}	
	
	if(myMsg->times <= 0)//多发送一次用于提示开始信息！
	{
		if(myMsg->system_activity_timer)
			delete myMsg->system_activity_timer;
			
		delete myMsg;
	}else{
		myMsg->times=myMsg->times-1;
		if(NULL == myMsg->system_activity_timer)//重新启动计时器
			myMsg->system_activity_timer = new ev_timer;
		
		ext_ev_timer_init(myMsg->system_activity_timer,SystemActivityFinishCall,myMsg->interval_time,0,myMsg);
		ev_timer_start(loops,myMsg->system_activity_timer); 
	}
	
}

/**
参数说明 msg发送的消息；
		 time发送次数；
		 interval_time发送的间隔时间；
返回值   void
函数作用 全区活动消息系统提示消息
*/
void SYSTEM_MESSAGE::systemActivityMsg(char *msg,int time,int interval_time,int levelLimit)
{
	if(msg == NULL || strlen(msg) > MSG_LEN || strlen(msg)==0 || time < 0 || interval_time < 0)
		return;
		
	systemMsg_T* myMsg = new systemMsg_T(msg,time,interval_time,levelLimit);
	
	if(NULL == myMsg->system_activity_timer)//启动计时器
		 myMsg->system_activity_timer = new ev_timer;
	
	ext_ev_timer_init(myMsg->system_activity_timer,SystemActivityFinishCall,2,0,myMsg);
	ev_timer_start(loops,myMsg->system_activity_timer); 
}