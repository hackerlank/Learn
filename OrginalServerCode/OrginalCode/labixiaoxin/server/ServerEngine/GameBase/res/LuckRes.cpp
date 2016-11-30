#include "LuckRes.h"
#include "ItemResMgr.h"

LuckRes::LuckRes(ACE_UINT32 unType)
:RewardRes(unType)
{
	//m_drop.unCount = 0;
}

LuckRes::~LuckRes()
{

}

int LuckRes::parse_xml_node(xmlNodePtr node)
{
	RewardRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"level") == 0)
	{
		m_unLevel = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}

	return 0;
}



void LuckRes::process_res_id_by_name()
{
}

