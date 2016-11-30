#include "EquipmentRes.h"
#include "ItemResMgr.h"

EquipmentRes::EquipmentRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_charge_value = 0;
}

EquipmentRes::~EquipmentRes()
{

}

int EquipmentRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	
	if(xmlStrcasecmp(node->name, BAD_CAST"property_value") == 0)
	{
		GameUtils::parse_property_list(m_propertyList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"improve_point") == 0)
	{
		GameUtils::parse_property_list(m_improvePropertyList, (char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name, BAD_CAST"charge_value") == 0)
	{
		m_charge_value =  ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name, BAD_CAST"level_require") == 0)
	{
		m_level_require =ACE_OS::atoi((char *)xmlNodeGetContent(node)); 
	}
	return 0;
}



void EquipmentRes::process_res_id_by_name()
{
}

