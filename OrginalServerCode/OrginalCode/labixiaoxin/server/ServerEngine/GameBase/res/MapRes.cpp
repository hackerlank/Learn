#include "MapRes.h"
#include "ItemResMgr.h"
#include "GameConfig.h"

MapRes::MapRes(ACE_UINT32 unType)
:RewardRes(unType)
{
	m_unUnlockCount = 0;
	
	ACE_OS::memset(&m_costList, 0, sizeof(CostInfoList));
}

MapRes::~MapRes()
{

}

int MapRes::parse_xml_node(xmlNodePtr node)
{
	RewardRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"level_up") == 0)
	{
		m_unLevelUp = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"launch_count") == 0)
	{
		m_unLaunchCount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"bell_coin") == 0)
	{
		m_unBellCoin = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"bell_sumcount") == 0)
	{
		m_unBellAmount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"bell_count") == 0)
	{
		m_unBellCount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"reward_gold") == 0)
	{
		//m_unBonusMoney = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		RewardRes::parse_reward_list(m_bonusReward, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"drop_special") == 0)
	{
		parse_reward_list(m_specialReward, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"subboss_rate") == 0)
	{
		//m_fSubbossRate = (float)ACE_OS::atof((char *)xmlNodeGetContent(node));
		m_fSubbossRate = GameUtils::my_atof((char *)xmlNodeGetContent(node), 3);
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"unlock") == 0)
	{
		m_unUnlockCount = parse_unlock((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"cost") == 0)
	{
		GameUtils::parse_cost_list(m_costList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"timesPerDay") == 0)
	{
		m_unTotalEnterCount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name, BAD_CAST"need_stage_unlock") == 0)
	{
		m_UnlockCases.byLimited = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name, BAD_CAST"level_limit") == 0)
	{
		m_UnlockCases.unLevel =  ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name, BAD_CAST"first_reward") == 0)
	{
		parse_reward_list(m_firstReward, (char *)xmlNodeGetContent(node));
	}
	return 0;
}

ACE_UINT32 MapRes::parse_unlock(char *str)
{
	int len = ACE_OS::strlen(str);
	int i;
	int offset = 0;
	int c = 0;
	std::map<ACE_UINT32, ACE_UINT32> &refUnlockPrefix = GAME_CONFIG_INSTANCE::instance()->m_oUnlockPrefixMapID;
	for(i = 0;i < len;i ++)
	{
		if(str[i] == ',')
		{
			m_unlockList[c] = convert_unlock_id(str, offset, i);
			c ++;
			refUnlockPrefix.insert(std::make_pair(m_unlockList[c-1], m_unResID));
			offset = i + 1;
		}
	}

	m_unlockList[c] = convert_unlock_id(str, offset, len);
	refUnlockPrefix.insert(std::make_pair(m_unlockList[c], m_unResID));
	c ++;

	return c;
}

ACE_UINT32 MapRes::convert_unlock_id(char *str, int start, int end)
{
	char tmp[128];
	int len = end - start;
	ACE_OS::memcpy(tmp, &str[start], len);
	tmp[len] = '\0';

	return GameUtils::parse_res_id(tmp);
	//return ACE_OS::strtol(tmp, NULL, 16);
	//return ACE_OS::atoi(tmp);
}

void MapRes::process_res_id_by_name()
{
}
