#include "FormulaRes.h"
#include "ItemResMgr.h"

FormulaRes::FormulaRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unRecipeRequired = 0;
}

FormulaRes::~FormulaRes()
{

}

int FormulaRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"cost") == 0)
	{
		GameUtils::parse_cost_list(m_costList, (char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"recipe_require") == 0)
	{
		m_unRecipeRequired = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	
	return 0;
}

void FormulaRes::process_res_id_by_name()
{
}
