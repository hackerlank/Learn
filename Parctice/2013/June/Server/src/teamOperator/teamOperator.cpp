#include "teamOperator.h"
#include "wholeDefine.h"
#include"command_other_function_all_over.h"
#include"teamManager.h"
#include"team.h"

extern int g_msg_len;
extern Hero* pg_hero;

//请求自己是否已创建队伍
void acceptTeamState(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *heroId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	const char *teamId = pg_hero->getTeamerId();
	
	//没有队伍
	if(strlen(teamId) == 0)
	{
		sprintf(teamMsg,"37,0,%d",0);
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
			
	if(!teamManger)
	{
		cout<<"acceptTeamState teamManger is NULL:"<<endl;
		return;
	}
			
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"acceptTeamState team is NULL:"<<endl;
		return;
	}

	//下线时被人踢掉了
	if(!team->isInTeam(pg_hero->getIdentity()))
	{
		sprintf(teamMsg,"37,0,%d",0);
		send_msg(pg_hero->getFd(),teamMsg);
		pg_hero->initTeamerId();
		return;
	}
	team->formTeamMemMsg();
	send_msg(pg_hero->getFd(),team->getTeamMemMsg());
	
	//更新自己的组队状态
	pg_hero->brushTeamStation();
	
	return;	
	
	
}
	
//请求别人是否已创建队伍
void acceptOtherHeroTeamState(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *otherHeroId;
	int teamFlg = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(otherHeroId);
	
	Hero *otherHero = heroid_to_hero(otherHeroId);
	
	if(!otherHero)
	{
		return;
	}
	
	const char *teamId = otherHero->getTeamerId();
	
	//没有队伍
	if(strlen(teamId) != 0)
	{
		teamFlg = 1;		
	}
	
	sprintf(teamMsg,"37,1,%s,%d",otherHeroId,teamFlg);
	send_msg(pg_hero->getFd(),teamMsg);
	return;
	
}



//申请入队
void applyForInTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *otherHeroId;
	int teamFlg = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(otherHeroId);
	
	Hero *otherHero = heroid_to_hero(otherHeroId);
	
	//不在线
	if(!otherHero)
	{
		cout<<"applyForInTeam the otherHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;		
	}
	
	const char *teamId = otherHero->getTeamerId();
	
	//对方没有队伍
	if(strlen(teamId) == 0)
	{
		cout<<"applyForInTeam you have not team :"<<otherHero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,4");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;		
	}
	
	//被邀请人已经在队伍中
	if(strlen(pg_hero->getTeamerId()) != 0)
	{
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"applyForInTeam team is NULL:"<<endl;
		return;		
	}
	
	//队伍队员已满
	if(team->size() == Team::TEAM_NUM_SIZE)
	{
		sprintf(teamMsg,"37,0,12");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	Map_Inform *mapNow1 = otherHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"applyForInTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//对方在副本中，申请失败
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//你在副本中，申请失败
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	Hero *headerHero = heroid_to_hero(team->getHeader());
	
	//队长居然不在线，开玩笑
	if(!headerHero)
	{
		return;
	}
	

	//发给被邀请人消息
	sprintf(teamMsg,"37,2,%s,%s,2",pg_hero->getIdentity(),pg_hero->getNickName());
	send_msg(headerHero->getFd(),teamMsg);	
	return;	
}


//同意申请入队
void agreeApplyForInTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *otherHeroId;
	int responseFlg = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(responseFlg);
	MSG_CHAR_END(otherHeroId);
	
	Hero *otherHero = heroid_to_hero(otherHeroId);
	
	//申请玩家不在线
	if(!otherHero)
	{
		cout<<"agreeApplyForInTeam the otherHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;
	}
	
	//拒接
	if(responseFlg == 0)
	{
		sprintf(teamMsg,"37,2,%d,%s",0,pg_hero->getNickName());
		send_msg(otherHero->getFd(),teamMsg);
		return;
	}	
	
	const char *teamId = pg_hero->getTeamerId();
	
	//邀请人已经在队伍中
	if(strlen(otherHero->getTeamerId()) != 0)
	{
		sprintf(teamMsg,"37,2,8");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//被邀请人没有队伍
	if(strlen(teamId) == 0)
	{
		cout<<"agreeApplyForInTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;		
	}
	
	Map_Inform *mapNow1 = otherHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"agreeApplyForInTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//对方在副本中，申请失败
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//你在副本中，申请失败
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	Team *team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"aggreApplyForInTeam team is NULL:"<<endl;
		return;		
	}
	
	//队伍队员已满
	if(team->size() == Team::TEAM_NUM_SIZE)
	{
		sprintf(teamMsg,"37,0,12");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
		
	teamId = team->join(otherHero->getIdentity());
	
	if(!teamId)
	{
		return;
	}
	
	team->formTeamMemMsg();
	
	team->sendMsg(team->getTeamMemMsg());	
	
	otherHero->setTeamerId(teamId);
	
	team->initCaptureCopyId(true);
	
	return;	
}



//请求"组队"
void inviteHeroJoinTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *joinHeroId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(joinHeroId);
	
	Hero *joinHero = heroid_to_hero(joinHeroId);
	
	//被邀请人不在线
	if(!joinHero)
	{
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	const char *teamId = joinHero->getTeamerId();
	
	
	//被邀请人已经在队伍中
	if(strlen(teamId) != 0)
	{
		sprintf(teamMsg,"37,0,8");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	Map_Inform *mapNow1 = joinHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"inviteHeroJoinTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//对方在副本中，申请失败
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//你在副本中，申请失败
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	teamId = pg_hero->getTeamerId();
	if(strlen(teamId) != 0)
	{
		TeamManager* teamManger = TeamManager::getManagerInst();
		Team *team = teamManger->getTeamHandle(teamId);
		
		if(!team)
		{
			cout<<"inviteHeroJoinTeam team is NULL:"<<endl;
			return;		
		}
		
		//不是队长不许邀请
		if(!team->isHeader(pg_hero->getIdentity()))
		{
			cout<<"inviteHeroJoinTeam you are not header :"<<pg_hero->getIdentity()<<endl;
			sprintf(teamMsg,"37,0,10");
			send_msg(pg_hero->getFd(),teamMsg);	
			return;
		}
	}
	
	//发给被邀请人消息
	sprintf(teamMsg,"37,2,%s,%s,1",pg_hero->getIdentity(),pg_hero->getNickName());
	send_msg(joinHero->getFd(),teamMsg);
	return;
}
				
//请求"组队"回应
void responseInviteHeroJoinTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *inviteHeroId;
	int responseFlg;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(responseFlg);
	MSG_CHAR_END(inviteHeroId);	
	
	//邀请者
	Hero *inviteHero = heroid_to_hero(inviteHeroId);
	
	//邀请者不在线
	if(!inviteHero)
	{
		cout<<"responseInviteHeroJoinTeam the inviteHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	
	
	//拒接
	if(responseFlg == 0)
	{
		sprintf(teamMsg,"37,2,%d,%s",0,inviteHero->getNickName());
		send_msg(inviteHero->getFd(),teamMsg);
		return;
	}
	
	
	//已经在队伍中
	if(strlen(pg_hero->getTeamerId()) != 0)
	{
		sprintf(teamMsg,"37,0,5");
		send_msg(inviteHero->getFd(),teamMsg);
		return;
	}
	
	
	Map_Inform *mapNow1 = inviteHero->getMap();
	
	Map_Inform *mapNow2 = pg_hero->getMap();
	
	if(!mapNow1 || !mapNow2)
	{
		cout<<"responseInviteHeroJoinTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//对方在副本中，申请失败
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,6");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	//你在副本中，申请失败
	if(mapNow2->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	const char *teamId = inviteHero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//没有队伍
	if(strlen(teamId) == 0)
	{
		if(!teamManger)
		{
			cout<<"responseInviteHeroJoinTeam teamManger is NULL:"<<endl;
			return;
		}
		
		teamId = teamManger->captureTeamHandle(inviteHero->getIdentity());
		
		if(!teamId)
		{
			cout<<"responseInviteHeroJoinTeam teamId is NULL:"<<endl;
			return;
		}		
	}		
	
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"responseInviteHeroJoinTeam team is NULL:"<<endl;
		return;		
	}	
	
	//队伍队员已满
	if(team->size() == Team::TEAM_NUM_SIZE)
	{
		sprintf(teamMsg,"37,0,12");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	teamId = team->join(pg_hero->getIdentity());
	
	if(!teamId)
	{
		return;
	}
	
	team->formTeamMemMsg();
	
	team->sendMsg(team->getTeamMemMsg());
	
	if(strlen(inviteHero->getTeamerId()) == 0)
	{
		inviteHero->setTeamerId(teamId);
	}
	
	pg_hero->setTeamerId(teamId);	
	
	team->initCaptureCopyId(true);
	
	pg_hero->brushTeamStation();

}
					
//退出
void offTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *offHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(offHeroId);	
	

	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//没有队伍
	if(strlen(teamId) == 0)
	{
		cout<<"offTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);		
		return;
	}
	
	
	Map_Inform *mapNow1 = pg_hero->getMap();
	
	if(!mapNow1)
	{
		cout<<"offTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//您在副本中，退出失败
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	if(!teamManger)
	{
		cout<<"offTeam teamManger is NULL:"<<endl;
		return;
	}
	
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"offTeam team is NULL:"<<endl;
		return;		
	}
	
	
	if(!team->eraseMemSet(pg_hero->getIdentity()))
	{
		cout<<"offTeam fail :"<<pg_hero->getIdentity()<<endl;
		return;
	}
		
	if(team->memOnLineSize() == 0)
	{
		teamManger->recoverTeamHandle(teamId);
	}
	else
	{	
		team->formTeamMemMsg();
		team->sendMsg(team->getTeamMemMsg());
	}
	
	//退出成功
	sprintf(teamMsg,"37,0,%d,%d",0,0);
	
	send_msg(pg_hero->getFd(),teamMsg);	
	
	pg_hero->initTeamerId();
	
	team->initCaptureCopyId(true);
	
	pg_hero->brushTeamStation();
}

//解散
void disMissTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *disMissHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(disMissHeroId);
	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//没有队伍
	if(strlen(teamId) == 0)
	{
		cout<<"disMissTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);			
		return;
	}
	
	
	Map_Inform *mapNow1 = pg_hero->getMap();
	
	if(!mapNow1)
	{
		cout<<"disMissTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//您在副本中，解散失败
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	if(!teamManger)
	{
		cout<<"disMissTeam teamManger is NULL:"<<endl;
		return;
	}
	
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"disMissTeam team is NULL:"<<endl;
		return;		
	}
	
	//不是队长，没有权限
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"disMissTeam you are not header :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,10");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
		
	
	
	//解散消息
	sprintf(teamMsg,"%d,%d,%d,%d",37,0,0,2);
	
	team->disMissTeam(teamMsg);
	
	team->initCaptureCopyId(true);
	
	teamManger->recoverTeamHandle(team->getTeamId());
	
}


//转让
void transferTeamLeader(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *offerHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(offerHeroId);	
	
	Hero *offHero = heroid_to_hero(offerHeroId);
	
	//对方不在线
	if(!offHero)
	{
		cout<<"transferTeamLeader the offHero is NULL:"<<endl;
		sprintf(teamMsg,"37,0,3");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//没有队伍
	if(strlen(teamId) == 0)
	{
		cout<<"transferTeamLeader you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,9");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	if(!teamManger)
	{
		cout<<"transferTeamLeader teamManger is NULL:"<<endl;
		return;
	}
		
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"transferTeamLeader team is NULL:"<<endl;
		return;		
	}
	
	//没有权限
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"transferTeamLeader you are not header :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,10");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	//候选者不在队伍中
	if(!team->isInTeam(offerHeroId))
	{
		cout<<"transferTeamLeader offerHeroId is not in team :"<<offerHeroId<<endl;
		sprintf(teamMsg,"37,0,11");
		send_msg(pg_hero->getFd(),teamMsg);
		return;		
	}
	
	if(!team->passHeader(offerHeroId))
	{
		cout<<"transferTeamLeader fail :"<<offerHeroId<<endl;
		return;
	}
	
	team->formTeamMemMsg();
	team->sendMsg(team->getTeamMemMsg());
	
	team->initCaptureCopyId(true);
	
	pg_hero->brushTeamStation();
	
	offHero->brushTeamStation();
	
#if 0	
	//转让不需要同意
	
	//转让消息
	sprintf(teamMsg,"%d,%d",37,8,);
	
	//队长接受者
	Hero *offHero = heroid_to_hero(offerHeroId);
	
	send_msg(offHero->getFd(),teamMsg);
	
#endif
	
}


//转让回应
void transferTeamLeaderResponse(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *offerHeroId;
	int responseFlg;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(responseFlg);
	MSG_CHAR_END(offerHeroId);	
	

	
	const char *teamId = pg_hero->getTeamerId();
	
	
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//没有队伍
	if(strlen(teamId) == 0)
	{
		cout<<"transferTeamLeaderResponse you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	if(!teamManger)
	{
		cout<<"transferTeamLeaderResponse teamManger is NULL:"<<endl;
		return;
	}
		
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"transferTeamLeaderResponse team is NULL:"<<endl;
		return;		
	}
	
	if(!team->isInTeam(offerHeroId))
	{
		cout<<"transferTeamLeaderResponse offerHeroId is not in team :"<<offerHeroId<<endl;
		return;		
	}
	
	Hero *teamLeader = heroid_to_hero(team->getHeader());
	
	if(!teamLeader)
	{
		cout<<"transferTeamLeaderResponse teamLeader is NULL :"<<offerHeroId<<endl;
		return;
	}
		
	if(responseFlg == 0)
	{
		//拒绝转让
		sprintf(teamMsg,"37,8,0,%s,%s",pg_hero->getIdentity(),pg_hero->getNickName());
		send_msg(teamLeader->getFd(),teamMsg);
		return;
	}
	
	
	if(!team->passHeader(pg_hero->getIdentity()))
	{
		cout<<"transferTeamLeaderResponse fail :"<<offerHeroId<<endl;
		return;
	}
	team->formTeamMemMsg();
	team->sendMsg(team->getTeamMemMsg());
}


//踢人
void kickOutTeam(char *buffer)
{
	char teamMsg[1000] = {'\0'};
	char *kickedHeroId;
	Team *team;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(kickedHeroId);	
	
	const char *teamId = pg_hero->getTeamerId();
		
	TeamManager* teamManger = TeamManager::getManagerInst();
	
	
	//没有队伍
	if(strlen(teamId) == 0)
	{
		cout<<"kickOutTeam you have not team :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	if(!teamManger)
	{
		cout<<"kickOutTeam teamManger is NULL:"<<endl;
		return;
	}
		
	team = teamManger->getTeamHandle(teamId);
		
	if(!team)
	{
		cout<<"kickOutTeam team is NULL:"<<endl;
		return;		
	}
	
	//不是队长
	if(!team->isHeader(pg_hero->getIdentity()))
	{
		cout<<"kickOutTeam you are not header :"<<pg_hero->getIdentity()<<endl;
		sprintf(teamMsg,"37,0,10");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;
	}
	
	//对方不在队伍中
	if(!team->isInTeam(kickedHeroId))
	{
		cout<<"kickOutTeam kickedHeroId is not in team :"<<kickedHeroId<<endl;
		sprintf(teamMsg,"37,0,11");
		send_msg(pg_hero->getFd(),teamMsg);	
		return;		
	}
	
	Hero *kickedHero = heroid_to_hero(kickedHeroId);
	
#if 0
	//对方不在线(不在线也照样踢）
	if(!kickedHero)
	{
		cout<<"kickOutTeam kickedHero is NULL :"<<kickedHeroId<<endl;
		sprintf(teamMsg,"37,0,5");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
#endif	
	
	Map_Inform *mapNow1 = pg_hero->getMap();
	
	if(!mapNow1)
	{
		cout<<"kickOutTeam the mapNow is NULL:"<<endl;
		return;
	}
	
	//您在副本中，不许踢人
	if(mapNow1->getFlgCpy())
	{
		sprintf(teamMsg,"37,0,7");
		send_msg(pg_hero->getFd(),teamMsg);
		return;
	}
	
	
	if(!team->eraseMemSet(kickedHeroId))
	{
		cout<<"kickOutTeam fail :"<<kickedHeroId<<endl;
		return;
	}
	
	//被踢
	sprintf(teamMsg,"37,0,2,%s,%s",pg_hero->getIdentity(),pg_hero->getNickName());
	
	team->formTeamMemMsg();
	team->sendMsg(team->getTeamMemMsg());
	
	if(kickedHero)
	{		
		send_msg(kickedHero->getFd(),teamMsg);	
		kickedHero->initTeamerId();
	}
		
	team->initCaptureCopyId(true);
}

	
	
	
