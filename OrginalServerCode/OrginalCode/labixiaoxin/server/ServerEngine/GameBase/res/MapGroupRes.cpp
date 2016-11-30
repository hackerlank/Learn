#include "MapGroupRes.h"
#include "ItemResMgr.h"

std::map<ACE_UINT32,ACE_UINT32> MapGroupRes::g_map_to_mapGroup;

MapGroupRes::MapGroupRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unRewardCount = 0;
	m_unMapCount = 0;
	m_level_require = 0;
}

MapGroupRes::~MapGroupRes()
{

}

int MapGroupRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"reward") == 0)
	{
		m_unRewardCount = RewardRes::parse_reward_group(m_rewardList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"mapid") == 0)
	{
		parse_map_list((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"number") == 0)
	{
		parse_star_number((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"level_require") == 0)
	{
		m_level_require = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}

	return 0;
}

void MapGroupRes::process_res_id_by_name()
{
}

void MapGroupRes::parse_map_list(char *str)
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];
	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		//m_mapList[c] = ACE_OS::strtol(tmp, NULL, 16);
		m_mapList[c] = GameUtils::parse_res_id(tmp);
		g_map_to_mapGroup[m_mapList[c]] = m_unResID;
		c ++;
	}

	m_unMapCount = c;
}

void MapGroupRes::parse_star_number(char *str)
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];
	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		m_unRewardStarNumber[c] = ACE_OS::atoi(tmp);
		c ++;
	}
}