#include "PlayerRes.h"
#include "ItemResMgr.h"

PlayerRes::PlayerRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	//m_propertyList.unCount = 0;
	m_unBasicPropertyID = 0;
	m_unGrowingID = 0;
	ACE_OS::memset(m_unInitEquipmentList, 0, sizeof(ACE_UINT32) * EQUIPMENT_TYPE_MAX);
}

PlayerRes::~PlayerRes()
{

}

int PlayerRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	/*
	if(xmlStrcasecmp(node->name, BAD_CAST"property_value") == 0)
	{
		GameUtils::parse_property_list(m_propertyList, (char *)xmlNodeGetContent(node));
	}
	*/
	if(xmlStrcasecmp(node->name, BAD_CAST"skillid") == 0)
	{
		//m_unSkillID = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		//m_unSkillID = ACE_OS::strtol((char *)xmlNodeGetContent(node), NULL, 16);
		m_unSkillID = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"realid") == 0)
	{
		//m_unSkillID = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		//m_unSkillID = ACE_OS::strtol((char *)xmlNodeGetContent(node), NULL, 16);
		m_unRealID = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"grade") == 0)
	{
		//m_unSkillID = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		//m_unSkillID = ACE_OS::strtol((char *)xmlNodeGetContent(node), NULL, 16);
		m_dwGrade = (int)GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"changenum") == 0)
	{
		//m_unSkillID = ACE_OS::atoi((char *)xmlNodeGetContent(node));
		//m_unSkillID = ACE_OS::strtol((char *)xmlNodeGetContent(node), NULL, 16);
		m_dwChangeNum = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"basic_id") == 0)
	{
		//m_unBasicPropertyID = ACE_OS::strtol((char *)xmlNodeGetContent(node), NULL, 16);
		m_unBasicPropertyID = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"growing_id") == 0)
	{
		//m_unGrowingID = ACE_OS::strtol((char *)xmlNodeGetContent(node), NULL, 16);
		m_unGrowingID = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"equipment_id") == 0)
	{
		parse_init_equipment_list((char *)xmlNodeGetContent(node));
	}

	return 0;
}



void PlayerRes::process_res_id_by_name()
{
}

void PlayerRes::parse_init_equipment_list(char *str)
{
	int len = strlen(str);

	char tmp[64];
	
	int offset = 0;

	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		//m_unInitEquipmentList[c] = ACE_OS::strtol(tmp, NULL, 16);
		m_unInitEquipmentList[c] = GameUtils::parse_res_id(tmp);

		c ++;
	}
}

ACE_UINT32 PlayerRes::get_init_equipment(ACE_UINT32 unType)
{
	int i;
	for(i = 0;i < EQUIPMENT_TYPE_MAX;i ++)
	{
		int equipment_type = GET_ITEM_ID_INFO(m_unInitEquipmentList[i], 5, 1);

		if(equipment_type == unType)
		{
			return m_unInitEquipmentList[i];
		}
	}

	return 0;
}

ACE_UINT32 PlayerRes::get_current_step(PlayerRes *res, ACE_UINT32 unLevel)
{
	/*
	int t = res->m_unQuality * 10 + 10;

	if(unLevel <= t)
	{
		return 1;
	}

	t = t - unLevel;

	return (2 + ((t - 1) / 10));
	*/
	int t = 20 + (res->m_unQuality - 1) * 2;
	if(unLevel <= t)
	{
		return 1;
	}
	t = unLevel - t;
	return (2 + ((t - 1) / 10));
}

ACE_UINT32 PlayerRes::get_max_level(PlayerRes *res, ACE_UINT32 unStep)
{
	/*
	int t = res->m_unQuality * 10 + 10;

	return (t + (unStep - 1) * 10);
	*/
	int t = 20 + (res->m_unQuality - 1) * 2 + (unStep - 1) * 10;
	return t;
}