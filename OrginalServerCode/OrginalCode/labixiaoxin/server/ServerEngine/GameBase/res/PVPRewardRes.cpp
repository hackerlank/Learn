#include "PVPRewardRes.h"
#include "ItemResMgr.h"

PVPRewardRes::PVPRewardRes(ACE_UINT32 unType)
:RewardRes(unType)
{
}

PVPRewardRes::~PVPRewardRes()
{

}

int PVPRewardRes::parse_xml_node(xmlNodePtr node)
{
	RewardRes::parse_xml_node(node);
	
	return 0;
}

void PVPRewardRes::process_res_id_by_name()
{
}
