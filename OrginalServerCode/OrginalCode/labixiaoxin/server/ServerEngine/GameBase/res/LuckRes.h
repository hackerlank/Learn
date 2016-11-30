#pragma once

#include "BaseRes.h"
#include "RewardRes.h"

class LuckRes : public RewardRes
{
public:
	LuckRes(ACE_UINT32 unType);
	virtual ~LuckRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	//DropGroup m_drop;
	ACE_UINT32 m_unLevel;
};