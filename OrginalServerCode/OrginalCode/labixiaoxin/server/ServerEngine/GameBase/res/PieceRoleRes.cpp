#include "PieceRoleRes.h"

PieceRoleRes::PieceRoleRes( ACE_UINT32 unType )
:BaseRes(unType)
{
	m_piece_id = 0;
	m_use_amount = 0;
	m_character_id =0;
	ZeroVar(m_cost);
}

PieceRoleRes::~PieceRoleRes()
{

}

int PieceRoleRes::parse_xml_node( xmlNodePtr node )
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"piece_id") == 0)//xxj 2015/04/23 20:57:11  加人名字
	{
		m_piece_id = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"cost") == 0)
	{
		GameUtils::parse_cost_list(m_cost, (char *)xmlNodeGetContent(node));
	}
	else if (xmlStrcasecmp(node->name, BAD_CAST"use_amount") == 0)
	{
		m_use_amount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"character_id") == 0)//xxj 2015/04/23 20:57:11  加人名字
	{
		m_character_id = GameUtils::parse_res_id((char *)xmlNodeGetContent(node));
	}
	return 0;
}
