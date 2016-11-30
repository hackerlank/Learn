#include "BadgeRes.h"

std::map<ACE_UINT32,ACE_UINT32> BadgeRes::m_equipmentMap;

BadgeRes::BadgeRes( ACE_UINT32 unType )
:BaseRes(unType)
{
	m_equip_id = 0;//对应的装备ID
	ZeroVar(m_gaint_to);//"加成目标（16进制）1.全体2.队长characterID.指定角色（最多3人，逗号分割）"
	ZeroVar(m_gaint_ype);
	ZeroVar(m_gain_value);
	m_need_role =0;
}

BadgeRes::~BadgeRes()
{

}

int BadgeRes::parse_xml_node( xmlNodePtr node )
{
	BaseRes::parse_xml_node(node);


	if(xmlStrcasecmp(node->name, BAD_CAST"equip_id") == 0)
	{
		m_equip_id = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
		m_equipmentMap[m_equip_id] = m_unResID;
	}
	else if (xmlStrcasecmp(node->name,BAD_CAST("gaint_to")) == 0)
	{
		Parse_res_info(m_gaint_to,(char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name,BAD_CAST("gaint_ype")) == 0)
	{
		Parse_info(m_gaint_ype,(char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name,BAD_CAST("gain_value")) == 0)
	{
		Parse_infoEx(m_gain_value,(char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name,BAD_CAST("need_role")) == 0)
	{
		m_need_role = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}

	return 0;
}

int BadgeRes::Parse_info( ACE_UINT32 * des, char *str )
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	for(int i = 0;i < 2;i ++)
	{
		if(offset == -1)
		{
			break;
		}
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		des[i] = ACE_OS::atoi(tmp);
	}

	return 0;
}

int BadgeRes::Parse_infoEx( float * des, char *str )
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	for(int i = 0;i < 2;i ++)
	{
		if(offset == -1)
		{
			break;
		}
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		des[i] = ACE_OS::atof(tmp);
	}

	return 0;
}

ACE_UINT32 BadgeRes::GetBadgeID( ACE_UINT32 equipmentid )
{
	std::map<ACE_UINT32,ACE_UINT32>::const_iterator c_it = m_equipmentMap.find(equipmentid);
	if (c_it != m_equipmentMap.end())
	{
		return c_it->second;
	}

	return 0;
}

int BadgeRes::Parse_res_info( ACE_UINT32 * des, char *str )
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	int i=0;
	while(!(offset == -1))
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		des[i] = GameUtils::parse_res_id(tmp);;
		i++;
	}

	return 0;
}



