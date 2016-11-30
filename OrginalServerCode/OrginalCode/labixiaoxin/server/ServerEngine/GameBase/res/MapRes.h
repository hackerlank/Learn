#pragma once

#include "BaseRes.h"
#include "RewardRes.h"

#define MAX_MAP_UNLOCK_COUNT 8

struct UnlockMapCases
{
	UnlockMapCases():byLimited(0),unLevel(-1)
	{}
	BYTE byLimited;
	ACE_UINT32 unLevel;
};


class MapRes : public RewardRes
{
public:
	MapRes(ACE_UINT32 unType);
	virtual ~MapRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_unLevelUp;

	ACE_UINT32 m_unBellCoin;
	ACE_UINT32 m_unBellAmount;
	ACE_UINT32 m_unLaunchCount;
	ACE_UINT32 m_unBellCount;
	
	ConfigReward m_firstReward;
	//ACE_UINT32 m_unBonusMoney;
	ConfigReward m_bonusReward;

	float m_fSubbossRate;
	
	ConfigReward m_specialReward;

	ACE_UINT32 m_unUnlockCount;
	ACE_UINT32 m_unTotalEnterCount;
	ACE_UINT32 m_unlockList[MAX_MAP_UNLOCK_COUNT];

	CostInfoList m_costList;

	UnlockMapCases m_UnlockCases;
private:
	ACE_UINT32 parse_unlock(char *str);
	ACE_UINT32 convert_unlock_id(char *str, int start, int end);
	//ACE_UINT32 m_unSepcailCount;
};