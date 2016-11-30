#include "MaterialRes.h"
#include "ItemResMgr.h"

MaterialRes::MaterialRes(ACE_UINT32 unType)
:BaseRes(unType)
{
}

MaterialRes::~MaterialRes()
{

}

int MaterialRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	
	return 0;
}

void MaterialRes::process_res_id_by_name()
{
}
