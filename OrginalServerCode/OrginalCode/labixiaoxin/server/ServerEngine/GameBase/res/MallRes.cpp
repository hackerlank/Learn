#include "MallRes.h"
#include "ItemResMgr.h"

MallRes::MallRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unGold = 0;
}

MallRes::~MallRes()
{

}

int MallRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"gold") == 0)
	{
		m_unGold = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"rmb") == 0)
	{
		m_unRMB = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}

	return 0;
}



void MallRes::process_res_id_by_name()
{
}

