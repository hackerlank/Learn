#pragma once

#include "RewardRes.h"

typedef struct tagUnlockRequireInfo
{
	ACE_UINT32 unType;
	ACE_UINT32 unValue;
}UnlockRequireInfo;

/*
typedef struct tagUnlockReward
{
	ACE_UINT32 unResID;
	ACE_UINT32 unCount;
}UnlockReward;

#define MAX_UNLOCK_REWARD_COUNT 8
*/

class UnlockRes : public RewardRes
{
public:
	UnlockRes(ACE_UINT32 unType);
	virtual ~UnlockRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	/*
	ACE_UINT32 m_unCoin;
	ACE_UINT32 m_unGold;
	ACE_UINT32 m_unPowerPoint;
	ACE_UINT32 m_unRecharge;
	*/

	UnlockRequireInfo m_require;
	//ACE_UINT32 m_unRewardCount;
	//UnlockReward m_rewardList[MAX_UNLOCK_REWARD_COUNT];
private:
	void parse_require(UnlockRequireInfo &dest, char *str);
};