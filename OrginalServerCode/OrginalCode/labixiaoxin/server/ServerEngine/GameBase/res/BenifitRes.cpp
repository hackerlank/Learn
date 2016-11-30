#include "BenifitRes.h"
#include "ItemResMgr.h"

BenifitRes::BenifitRes(ACE_UINT32 unType)
:BaseRes(unType)
{

}

BenifitRes::~BenifitRes()
{

}

int BenifitRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"property_value") == 0)
	{
		//m_unLevelUp = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		GameUtils::parse_benefit_list(m_benefitList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"duration") == 0)
	{
		//m_unLaunchCount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	
	return 0;
}


void BenifitRes::process_res_id_by_name()
{
}
