#pragma once

#include "BaseRes.h"

class StageRes : public BaseRes
{
public:
	StageRes(ACE_UINT32 unType);
	virtual ~StageRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	int m_neffectValue;
	float m_fDamagePercent;
	//PropertyList m_propertyList;
	PropertyComponent m_propertyList[PLAYER_PROPERTY_MAX];
};