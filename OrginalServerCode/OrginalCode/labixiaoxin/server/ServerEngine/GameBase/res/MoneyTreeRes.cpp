#include "MoneyTreeRes.h"
#include "ItemResMgr.h"
#include "RewardRes.h"

MoneyTreeRes::MoneyTreeRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unRewardCount = 0;
}

MoneyTreeRes::~MoneyTreeRes()
{

}

int MoneyTreeRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"reward") == 0)
	{
		m_unRewardCount = RewardRes::parse_reward_group(m_rewardList, (char *)xmlNodeGetContent(node));
		if(m_unRewardCount > 0)
		{
			for(int i = m_unRewardCount; i < REWARD_LIST_LEN; i++)
			{
				m_rewardList[i] = m_rewardList[i - 1];
			}
		}
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"xp") == 0)
	{
		m_unExp = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	
	return 0;
}

void MoneyTreeRes::process_res_id_by_name()
{
}
