#include "ImproveRes.h"
#include "ItemResMgr.h"

ImproveRes::ImproveRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_dImproveRate = 0;
	m_dPowerRate = 0;
}

ImproveRes::~ImproveRes()
{

}

int ImproveRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"sub_point") == 0)
	{
		GameUtils::parse_property_list(m_propertyList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"power_point") == 0)
	{
		m_unPowerPoint = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"improve_rate") == 0)
	{
		m_dImproveRate = ACE_OS::atof((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"power_rate") == 0)
	{
		m_dPowerRate = ACE_OS::atof((char *)xmlNodeGetContent(node));
	}
	/*
	else if(xmlStrcasecmp(node->name, BAD_CAST"improve_point") == 0)
	{
		m_unImprovePoint = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	*/

	return 0;
}



void ImproveRes::process_res_id_by_name()
{
}
