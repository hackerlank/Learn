#include "StageRes.h"
#include "ItemResMgr.h"

StageRes::StageRes(ACE_UINT32 unType)
:BaseRes(unType)
{
}

StageRes::~StageRes()
{

}

int StageRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"effect_target") == 0)
	{
		m_neffectValue = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"effect_value") == 0)
	{
		GameUtils::parse_property_list(m_propertyList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"damage_value") == 0)
	{
		//m_fDamagePercent = (float)ACE_OS::atof((char *)xmlNodeGetContent(node));
		m_fDamagePercent = GameUtils::my_atof((char *)xmlNodeGetContent(node), 3);
	}

	return 0;
}

void StageRes::process_res_id_by_name()
{
}
