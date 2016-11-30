#include "DropCurrencyRes.h"
#include "ItemResMgr.h"

CDropCurrencyRes::CDropCurrencyRes(ACE_UINT32 unType)
:RewardRes(unType)
{
}

CDropCurrencyRes::~CDropCurrencyRes()
{

}

int CDropCurrencyRes::parse_xml_node(xmlNodePtr node)
{
	RewardRes::parse_xml_node(node);

// 	if(xmlStrcasecmp(node->name, BAD_CAST"countdown") == 0)
// 	{
// 		m_unCountDown = ACE_OS::atoi((char *)xmlNodeGetContent(node));
// 	}

	return 0;
}

void CDropCurrencyRes::process_res_id_by_name()
{
}
