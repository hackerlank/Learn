#include "GiftRes.h"
#include "ItemResMgr.h"

GiftRes::GiftRes(ACE_UINT32 unType)
:RewardRes(unType)
{
}

GiftRes::~GiftRes()
{

}

int GiftRes::parse_xml_node(xmlNodePtr node)
{
	RewardRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"countdown") == 0)
	{
		m_unCountDown = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	
	return 0;
}

void GiftRes::process_res_id_by_name()
{
}
