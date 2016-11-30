#include "BehaviorRes.h"
#include "ItemResMgr.h"

BehaviorRes::BehaviorRes(ACE_UINT32 unType)
:RewardRes(unType)
{
	ACE_OS::memset(&m_cost, 0, sizeof(CostInfoList));
}

BehaviorRes::~BehaviorRes()
{

}

int BehaviorRes::parse_xml_node(xmlNodePtr node)
{
	RewardRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"cost") == 0)
	{
		//m_limitInfo.unCountLimit = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		GameUtils::parse_cost_list(m_cost, (char *)xmlNodeGetContent(node));
	}
	
	return 0;
}


void BehaviorRes::process_res_id_by_name()
{
}

