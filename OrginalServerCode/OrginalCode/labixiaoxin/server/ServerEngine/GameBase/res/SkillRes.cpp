#include "SkillRes.h"
#include "ItemResMgr.h"

SkillRes::SkillRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unDamageCount = 1;
	m_unSkillLevel = 0;
}

SkillRes::~SkillRes()
{

}

int SkillRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"skill_level") == 0)
	{
		m_unSkillLevel = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"property_value") == 0)
	{
		GameUtils::parse_property_list(m_propertyList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"damage_count") == 0)
	{
		m_unDamageCount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"name") == 0)//xxj 2015/04/23 20:57:11  º”»Î√˚◊÷
	{
		ACE_OS::strncpy(m_strName, (char *)xmlNodeGetContent(node), MAX_ITEM_NAME);
		m_strName[MAX_ITEM_NAME] = '\0';
	}

	return 0;
}



void SkillRes::process_res_id_by_name()
{
}

