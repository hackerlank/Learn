#include "MonsterRes.h"
#include "ItemResMgr.h"

MonsterRes::MonsterRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	//m_unMonsterType = 0;
}

MonsterRes::~MonsterRes()
{

}

int MonsterRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"level") == 0)
	{
		m_unLevel = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}

	return 0;
}



void MonsterRes::process_res_id_by_name()
{
}

