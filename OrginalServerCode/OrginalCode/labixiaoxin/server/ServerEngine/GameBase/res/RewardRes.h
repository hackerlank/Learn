#pragma once

#include "BaseRes.h"


/*
typedef struct tagUnlockReward
{
	ACE_UINT32 unResID;
	ACE_UINT32 unCount;
}UnlockReward;

#define MAX_UNLOCK_REWARD_COUNT 8
*/

class RewardRes : public BaseRes
{
public:
	RewardRes(ACE_UINT32 unType);
	virtual ~RewardRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ConfigReward m_reward;

	static int parse_reward_group(ConfigReward rewardList[], char *str);
	static void parse_reward_list(ConfigReward &reward, char *str);
	static int parse_reward(ConfigRewardInfo &dest, char *str);

protected:
	//void parse_require(UnlockRequireInfo &dest, char *str);
	
};