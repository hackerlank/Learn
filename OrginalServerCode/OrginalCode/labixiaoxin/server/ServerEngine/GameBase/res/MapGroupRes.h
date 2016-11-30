#pragma once

#include "RewardRes.h"
#include <map>



class MapGroupRes : public BaseRes
{
public:
	static std::map<ACE_UINT32,ACE_UINT32> g_map_to_mapGroup;
public:
	MapGroupRes(ACE_UINT32 unType);
	virtual ~MapGroupRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	//ACE_UINT32 m_unCountDown;
	ACE_UINT32 m_unMapCount;
	ACE_UINT32 m_mapList[MAX_MAP_COUNT];
	ACE_UINT32 m_unRewardCount;
	ConfigReward m_rewardList[MAP_REWARD_COUNT];
	ACE_UINT32 m_unRewardStarNumber[MAP_REWARD_COUNT];
	ACE_UINT32 m_level_require;//进入等级限制
private:
	void parse_map_list(char *str);
	void parse_star_number(char *str);
};