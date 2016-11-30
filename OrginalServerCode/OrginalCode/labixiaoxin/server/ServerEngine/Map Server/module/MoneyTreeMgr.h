#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\GameBase\res\MoneyTreeRes.h"

class MoneyTreeMgr : public BaseModule
{
public:
	MoneyTreeMgr();
	~MoneyTreeMgr();

	void init(ACE_UINT32 unLevel, ACE_UINT32 unExp);
	virtual void update(ACE_UINT32 unCurrentTime);
	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	void watering();
	void get_reward(RewardInfo &reward);

	ACE_UINT32 m_unLevel;
	ACE_UINT32 m_unExp;
private:
	void update_2_db();

	MoneyTreeRes *get_res(ACE_UINT32 unLevel);
};