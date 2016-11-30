#include "ExtraSkillRes.h"
#include "ItemResMgr.h"

ExtraSkillRes::ExtraSkillRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unSkillLevel = 0;
}

ExtraSkillRes::~ExtraSkillRes()
{

}

int ExtraSkillRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"cost") == 0)
	{
		m_unEnergyCost = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"level") == 0)
	{
		m_unSkillLevel = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"property_value") == 0)
	{
		parse_skill_param((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"name") == 0)//xxj 2015/04/23 20:57:11  º”»À√˚◊÷
	{
		ACE_OS::strncpy(m_strName, (char *)xmlNodeGetContent(node), MAX_ITEM_NAME);
		m_strName[MAX_ITEM_NAME] = '\0';
	}


	return 0;
}



void ExtraSkillRes::process_res_id_by_name()
{

}

void ExtraSkillRes::parse_skill_param(char *str)
{
	int len = strlen(str);

	char tmp[64];
	
	int offset = 0;

	int step = 0;
	int c = 0;
	float v = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp);

		if(step == 0)
		{
			m_unSkillType = ACE_OS::atoi(tmp);
		}
		else if(step == 1)
		{
			//propertyList.list[c].unType = ACE_OS::atoi(tmp);
			m_unSkillValueType = ACE_OS::atoi(tmp);
		}
		else if(step == 2)
		{
			//propertyList.list[c].fValue = (float)ACE_OS::atof(tmp);

			//propertyList.list[c].fValue = GameUtils::my_atof(tmp, 3);
			/*
			v = GameUtils::my_atof(tmp, 3);

			if(m_unSkillValueType == 1)
			{
				m_unValue = (ACE_UINT32)(v * 100);
			}
			else if(m_unSkillValueType == 2)
			{
				m_unValue = (ACE_UINT32)v;
			}
			*/
			m_unValue = ACE_OS::atoi(tmp);
		}

		step = (step + 1) % 3;
	}
}