#include "DropRes.h"
#include "ItemResMgr.h"
#include "..\Common\GlobalLootMgr.h"

DropRes::DropRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_dropGroup.unCount = 0;
	//m_unDropType = DROP_LOCAL_TYPE;
	m_fRate = 0.0f;
	m_step = 0;
}

DropRes::~DropRes()
{

}

int DropRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"drop_list") == 0)
	{
		//parse_drop_list((char *)xmlNodeGetContent(node));
		GameUtils::parse_drop_group(m_dropGroup, (char *)xmlNodeGetContent(node), true);
		m_step ++;
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"rate") == 0)
	{
		//m_fRate = (float)ACE_OS::atof((char *)xmlNodeGetContent(node));
		m_fRate = GameUtils::my_atof((char *)xmlNodeGetContent(node), 3);

		/*
		if(m_fRate > 0.0f)
		{
			m_unDropType = DROP_GLOBAL_TYPE;
		}
		else
		{
			m_unDropType = DROP_LOCAL_TYPE;
		}
		*/
		m_step ++;
	}

	if(m_step >= 2)
	{
		this->m_dropGroup.unGlobalDropID = GLOBAL_LOOT_MGR_INSTANCE::instance()->create_global_drop(m_fRate, m_dropGroup.unGlobalCount, m_dropGroup.globalList);
	}

	return 0;
}



void DropRes::process_res_id_by_name()
{
}
