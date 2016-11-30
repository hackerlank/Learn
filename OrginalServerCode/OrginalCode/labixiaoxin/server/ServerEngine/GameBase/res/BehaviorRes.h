#pragma once

#include "RewardRes.h"


class BehaviorRes : public RewardRes
{
public:
	BehaviorRes(ACE_UINT32 unType);
	virtual ~BehaviorRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	CostInfoList m_cost;

};