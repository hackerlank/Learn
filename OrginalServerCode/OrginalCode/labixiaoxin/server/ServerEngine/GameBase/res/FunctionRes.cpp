#include "FunctionRes.h"
#include "ItemResMgr.h"

FunctionRes::FunctionRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_isLock = 0;
}

FunctionRes::~FunctionRes()
{

}

int FunctionRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"islocked") == 0)
	{
		m_isLock = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"launch_count") == 0)
	{
		//m_unLaunchCount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	return 0;
}

void FunctionRes::process_res_id_by_name()
{
}
