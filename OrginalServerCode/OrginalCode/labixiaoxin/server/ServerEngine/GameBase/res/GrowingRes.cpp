#include "GrowingRes.h"
#include "ItemResMgr.h"

GrowingRes::GrowingRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	ACE_OS::memset(m_valueList, 0, sizeof(ACE_UINT32) * PLAYER_PROPERTY_MAX);
}

GrowingRes::~GrowingRes()
{

}

int GrowingRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"attribute") == 0)
	{
		GameUtils::parse_property_value_list(m_valueList, (char *)xmlNodeGetContent(node));
	}
	
	return 0;
}

void GrowingRes::process_res_id_by_name()
{
}