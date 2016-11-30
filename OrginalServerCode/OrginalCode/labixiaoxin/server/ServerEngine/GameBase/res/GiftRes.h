#pragma once

#include "RewardRes.h"



class GiftRes : public RewardRes
{
public:
	GiftRes(ACE_UINT32 unType);
	virtual ~GiftRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_unCountDown;
private:
	
};