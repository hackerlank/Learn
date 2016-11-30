#include "TeamRankMgr.h"
#include "json\json.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"
#include "..\GameBase\Common\GameDefine.h"
#include "..\Base\Service\ServiceConfigMgr.h"
//#include "..\GameBase\res\ArenaConfig.h"m_characterPool
#include "..\GameBase\Common\GameUtils.h"
#include "..\GameBase\res\GameConfig.h"
#include "..\DB Server\DBHandler.h"

//char friendMsgBuff[4096];


#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


TeamRankMgr::TeamRankMgr()
{
	m_unCount = 0;

	m_pvp100Cfg = GAME_CONFIG_INSTANCE::instance()->m_pvp100Cfg;//百人斩的配置文件
	for(int m = 0; m< MAX_PVP100_STAGE_COUNT; m++){  //初始化百人斩表头
		m_pvp100List[m].unCount = 0;  //设置初始个数为0
		m_pvp100List[m].head = new Pvp100_node;
		m_pvp100List[m].head->next = NULL;
		m_pvp100List[m].cur = m_pvp100List[m].head;
	}

	ZeroVar(m_unNewPaihangbang);
	m_isGetLa = false;
	ZeroVar(m_laConfig);
}

TeamRankMgr::~TeamRankMgr()
{
	
}

void TeamRankMgr::reset()
{
	m_unCount = 0;
}

void TeamRankMgr::load_from_db()
{
	
}

void TeamRankMgr::add(PublicPlayerInfo *player)
{
	UpdateList(player);

// 	if(m_unCount >= MAX_TEAM_RANK_COUNT)
// 	{
// 		return;
// 	}
// 
// 	//update_cell(m_unCount, unCharacterID, unPoint, teamInfo);
// 	m_list[m_unCount] = player;
// 
// 	m_unCount ++;
}
// 
// void TeamRankMgr::add_pvp100(PublicPlayerInfo *player)
// {
// 	if(m_unCount >= MAX_TEAM_RANK_100_COUNT)
// 	{
// 		return;
// 	}
// 
// 	
// 	m_pvp100List[m_unCount] = player;
// 
// 	m_unCount ++;
// }

void TeamRankMgr::update_pvp100(PublicPlayerInfo *player,ACE_UINT32 unOldPoint)//更新百人斩本地信息
{
	if(get_pvp100_rank(player->pvpRankInfo.unScore) < 0){
		return ;
	}

	
}

Pvp100_node* TeamRankMgr::find_pvp100(ACE_UINT32 unId,ACE_UINT32 unOldPoint)
{
	return NULL;
	

}
int TeamRankMgr::get_pvp100_rank(ACE_UINT32 point)
{
	int c;

	for(c = 0; c < m_pvp100Cfg.unCount; c++){
		if((point >= m_pvp100Cfg.pvp100Cfg[c].points.unStart) && (point <= m_pvp100Cfg.pvp100Cfg[c].points.unEnd)){
			return c;//返回排名
		}
	}
	return -1;  //没找到，配置有问题
}

void TeamRankMgr::update(PublicPlayerInfo *player, ACE_UINT32 unOldPoint)
{

	update_pvp100(player,unOldPoint);//更新百人斩信息
	UpdateList(player);
// 	int i;
// 	int pos = -1;
// 	int own_pos = -1;
// 	int addIdx = -1;
// 	int updateIdx = -1;
// 	for(i = 0;i < m_unCount;i ++)
// 	{
// 		if(m_list[i]->characterInfo.unItemID == player->characterInfo.unItemID)
// 		{
// 			if(unOldPoint >= player->highestTeamInfo.unPoint)
// 			{
// 				return;
// 			}
// 
// 			own_pos = i;
// 		}
// 
// 		if(player->highestTeamInfo.unPoint > m_list[i]->highestTeamInfo.unPoint)
// 		{
// 			if(pos == -1)
// 			{
// 				pos = i;
// 			}
// 		}
// 	}
// 
// 	if(pos == -1)
// 	{
// 		if(own_pos != -1)
// 		{
// 			return;
// 		}
// 
// 		if(m_unCount < MAX_TEAM_RANK_COUNT)
// 		{
// 			m_unCount ++;
// 			
// 			//update_cell(m_unCount - 1, unCharacterID, unPoint, teamInfo);
// 			m_list[m_unCount - 1] = player;
// 			
// 			addIdx = m_unCount - 1;
// 		}
// 		else
// 		{
// 			return;
// 		}
// 	}
// 	else
// 	{
// 		if(own_pos != -1)
// 		{
// 			if(own_pos <= pos)
// 			{
// 				return;
// 			}
// 
// 			for(i = own_pos;i > pos;i --)
// 			{
// 				m_list[i] = m_list[i - 1];
// 			}
// 
// 			updateIdx = pos;
// 
// 			m_list[pos] = player;
// 			//update_cell(pos, unCharacterID, unPoint, teamInfo);
// 		}
// 		else
// 		{
// 			addIdx = pos;
// 
// 			for(i = m_unCount;i > pos;i --)
// 			{
// 				if(i >= MAX_TEAM_RANK_COUNT)
// 				{
// 					continue;
// 				}
// 
// 				m_list[i] = m_list[i - 1];
// 			}
// 
// 			m_list[pos] = player;
// 			//update_cell(pos, unCharacterID, unPoint, teamInfo);
// 		}
// 	}
// 
// 	if(addIdx != -1)
// 	{
// 		//add 2 db
// 	}
// 
// 	if(updateIdx != -1)
// 	{
// 		//update 2 db
// 	}

}

void TeamRankMgr::UpdateList( PublicPlayerInfo *player )
{
	ACE_ASSERT(m_unCount <= MAX_TEAM_RANK_COUNT);
	if (m_unCount == 0)
	{
		m_list[m_unCount] = player;
		m_unCount++;
		return;
	}

	if (m_unCount > MAX_TEAM_RANK_COUNT)
		m_unCount = MAX_TEAM_RANK_COUNT;
	
	if (m_list[m_unCount-1]->highestTeamInfo.unPoint <= player->highestTeamInfo.unPoint)//有更新
	{
		InsertionSort(player,m_unCount);
	}
	else if (m_unCount < MAX_TEAM_RANK_COUNT )
	{
		m_list[m_unCount] = player;
		m_unCount++;
	}
}

void TeamRankMgr::InsertionSort( PublicPlayerInfo *player,int len )
{
	bool isAdd = true;
	for (int i=0;i<len;i++)
	{
		if (m_list[i] == player)
		{
			isAdd = false;
			break;
		}
	}

	if (isAdd)
	{
		m_list[m_unCount] = player;
		if (m_unCount < MAX_TEAM_RANK_COUNT)
			m_unCount ++;
		len ++;
	}

	
	for (int j=1; j<len; j++)  
	{  
		PublicPlayerInfo * key = m_list[j];  
		int i = j-1;  
		while (i>=0 && m_list[i]->highestTeamInfo.unPoint  <  key->highestTeamInfo.unPoint)  
		{  
			m_list[i+1] = m_list[i];  
			i--;
		}  
		m_list[i+1] = key;  
	}
}

void TeamRankMgr::UpdateLAAction()
{
	ACE_UINT32 unNow = GameUtils::get_utc();//当前时间

	//注意：此处需要删除
	std::map<ACE_UINT32, LimitedActivityConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityConfigEx;
	//先删除不需要的
	std::map<ACE_UINT32, LimitedActivityConfig>::iterator it = refLAConfig.begin();//当前活动任务列表
	while(it != refLAConfig.end())
	{
		if (it->second.unEndTime < unNow)//限时活动已经结束
		{
			it = refLAConfig.erase(it);
		}
		else
			it++;
	}
}

void TeamRankMgr::DoLAAction()
{
	if (m_laConfig.unID > 0 && !m_isGetLa)
	{
		ACE_UINT32 unNow = GameUtils::get_utc();
		if(m_laConfig.unEndTime < unNow)//此活动已经完成
		{
			for(int i=0;i<m_unCount;i++)
				m_unNewPaihangbang[i] = m_list[i]->characterInfo.unItemID;
		}
	}
}

bool TeamRankMgr::DoLAActionTimeCallBack()
{
	if(m_unNewPaihangbang[0] != 0)
	{
		m_isGetLa = true;
		return true;
	}
	else if (m_laConfig.unID != 0)
	{
		DoLAAction();
	}
	else if (/*m_laConfig.unID == 0 && m_unNewPaihangbang[0] == 0 && */!m_isGetLa)//没有任务并且还没有发放奖励
	{
		UpdateLAAction();
		ACE_UINT32 unNow = GameUtils::get_utc();
		//注意：此处需要删除
		const std::map<ACE_UINT32, LimitedActivityConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityConfigEx;
		//先删除不需要的
		std::map<ACE_UINT32, LimitedActivityConfig>::const_iterator c_it = refLAConfig.begin();//当前活动任务列表
		while(c_it != refLAConfig.end())
		{
			if (c_it->second.unRelatedType == E_L_A_TYPE::LA_TYPE_9)//找到
			{
				if(c_it->second.unStartTime < unNow && c_it->second.unEndTime > unNow)//此活动活跃
				{
					ZeroVar(m_unNewPaihangbang);
					m_laConfig = c_it->second;
					return false;
				}
			}

			c_it++;
		}
		return false;
	}

	return false;
}

void TeamRankMgr::GetMailItems( std::vector<MailInfo> & ver )
{
	if (m_laConfig.unID == 0)
		return;

	MailInfo mail;
	ZeroVar(mail);

	for (int i=0;i<m_laConfig.unRelatedCount;i++)
	{
		LimitedActivityMissionConfig lamConfig = FindLAmissionItem(m_laConfig.unRelatedItems[i]);//查找limitedactivitymission.xml
		if (lamConfig.unID > 0 && lamConfig.unMissionType[0] == LA_MISSION_TYPE_1006)//找到了 活跃度1006
		{
			int min = (lamConfig.unMissionType[1]- 1)%MAX_TEAM_RANK_COUNT;
			int max = (lamConfig.unMissionType[2]- 1)%MAX_TEAM_RANK_COUNT;
			if (min > max)
				min = max;

			for(int i=min;i<=max;i++ )
			{
				if (m_unNewPaihangbang[i]!=0)
				{
					ZeroVar(mail);
					if(GetMailInfo(mail,lamConfig.stReward,m_unNewPaihangbang[i],FRIENDSHIP_MAIL_LIMITED_ZHANDOULI))
					{
						sprintf(mail.m_strBody, "%d", i+1);
						ver.push_back(mail);
					}	
				}
				else
					break;
			}
		}
	}
	
	ZeroVar(m_laConfig);
	ZeroVar(m_unNewPaihangbang);
}

LimitedActivityMissionConfig TeamRankMgr::FindLAmissionItem( ACE_UINT32 unLAMissionID )
{
	LimitedActivityMissionConfig lamConfig;
	ZeroVar(lamConfig);
	const std::map<ACE_UINT32, LimitedActivityMissionConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityMissionConfig;
	std::map<ACE_UINT32, LimitedActivityMissionConfig>::const_iterator c_it = refLAConfig.find(unLAMissionID);
	if (c_it != refLAConfig.end())
		lamConfig = c_it->second;

	return lamConfig;
}

bool TeamRankMgr::GetMailInfo( MailInfo & oMailInfo,const ConfigReward & reward,ACE_UINT32 unCharacterID,ACE_UINT32 unMailId )
{
	oMailInfo.m_dwIDinTable = unMailId;
	oMailInfo.m_dwCharacterID = unCharacterID;
	oMailInfo.m_dwTimeoutDate = GameUtils::get_utc()/* + (7 * 24 * 3600)*/;

	int n = 0;
	if (reward.unCoin > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_COIN;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unCoin;
		n++;
	}
	if (reward.unMoney > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_MONEY;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unMoney;
		n++;
	}
	if (reward.unExp > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_EXP;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unExp;
		n++;
	}
	if (reward.unPowerPoint > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_POWERPOINT;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unPowerPoint;
		n++;
	}
	if (reward.unHonour > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_HONOUR;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unHonour;
		n++;
	}
	if (reward.unRecharge > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_RECHARGE;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unRecharge;
		n++;
	}
	if (reward.unEnergy > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_ENERGY;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unEnergy;
		n++;
	}
	if (reward.unPVPEnergy > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_PVP_ENERGY;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unPVPEnergy;
		n++;
	}
	if (reward.unFriendship > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_FRIENDSHIP;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unFriendship;
		n++;
	}

	for (int i=0;i<reward.unCount && n<MAIL_ATTACHMENT_LEN;i++,n++)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = reward.list[i].unResID;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.list[i].unCount;
	}


	return n>0;
}

/*
void TeamRankMgr::update_cell(int idx, ACE_UINT32 unCharacterID, ACE_UINT32 unPoint, PlayerTeamInfo *teamInfo)
{
	m_list[idx].unCharacterID = unCharacterID;
	m_list[idx].unPoint = unPoint;
	m_list[idx].unUpdateTime = GameUtils::get_utc();
	m_list[idx].teamInfo = *teamInfo;
}
*/