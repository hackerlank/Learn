#pragma once

#include "RewardRes.h"



class PVPRewardRes : public RewardRes
{
public:
	PVPRewardRes(ACE_UINT32 unType);
	virtual ~PVPRewardRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();
private:
	
};