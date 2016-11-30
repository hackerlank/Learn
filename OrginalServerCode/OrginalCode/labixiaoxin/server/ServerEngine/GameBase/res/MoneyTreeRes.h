#pragma once

#include "RewardRes.h"

#define REWARD_LIST_LEN 32

class MoneyTreeRes : public BaseRes
{
public:
	MoneyTreeRes(ACE_UINT32 unType);
	virtual ~MoneyTreeRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_unRewardCount;
	ConfigReward m_rewardList[REWARD_LIST_LEN];
	ACE_UINT32 m_unExp;
	//ACE_UINT32 m_unCountDown;
private:
	
};