#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include <set>

class GiftBagCodeMgr:public BaseModule
{
public:
	GiftBagCodeMgr();
	~GiftBagCodeMgr();

	std::set<WORD> m_setClaimCode;

	void init(const WORD codeSet[], const int codeCount);
	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN,int result = 0);

	void update_2_db(const WORD wClaimCodeType);

};