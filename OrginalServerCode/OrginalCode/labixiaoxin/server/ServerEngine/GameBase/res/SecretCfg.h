#pragma once
#include "BaseRes.h"

class CSecretCfg 
{
public:
	ACE_UINT32 m_unType;	
	ACE_UINT32 m_unItemId;
	ACE_UINT32 m_unCount;
	CSecretCfg(ACE_UINT32 unType);
	~CSecretCfg();

	ACE_UINT32 m_unCell;
	ACE_UINT32 m_HighList[80];
	ACE_UINT32 m_unHighCount;

	ACE_UINT32 m_LowList[80];
	ACE_UINT32 m_unLowCount;

	ACE_UINT32 m_CertainList[80];

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();
};
