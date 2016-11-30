#include "SecretCfg.h"

CSecretCfg::CSecretCfg(ACE_UINT32 unType)
{
}

CSecretCfg::~CSecretCfg(void)
{
}



int CSecretCfg::parse_xml_node(xmlNodePtr node)
{
	

	 if(xmlStrcasecmp(node->name, BAD_CAST"secret_type") == 0)
	{
		m_unType = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	 }
	 if(xmlStrcasecmp(node->name, BAD_CAST"item_id") == 0)
	 {
		 m_unItemId = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	 }
	 if(xmlStrcasecmp(node->name, BAD_CAST"amount") == 0)
	 {
		 m_unCount = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	 }

	return 0;
}

void CSecretCfg::process_res_id_by_name()
{
}