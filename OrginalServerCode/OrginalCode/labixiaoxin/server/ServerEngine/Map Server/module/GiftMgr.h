#pragma once

#include "ace\ace.h"
#include "BaseModule.h"


class GiftMgr : public BaseModule
{
public:
	GiftMgr();
	~GiftMgr();

	void init(GiftInfo *list);
	virtual void update(ACE_UINT32 unCurrentTime);
	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	ACE_UINT32 m_unGiftCount;
	GiftInfo m_giftList[MAX_GIFT_COUNT];

	int add_gift(ACE_UINT32 unID);
	int use_gift(int idx, RewardInfo &reward);

private:
	void update_2_db();
};