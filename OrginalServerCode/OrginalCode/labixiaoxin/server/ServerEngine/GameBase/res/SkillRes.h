#pragma once

#include "BaseRes.h"

class SkillRes : public BaseRes
{
public:
	SkillRes(ACE_UINT32 unType);
	virtual ~SkillRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();


	//PropertyList m_propertyList;
	PropertyComponent m_propertyList[PLAYER_PROPERTY_MAX];
	ACE_UINT32 m_unSkillLevel;
	ACE_UINT32 m_unDamageCount;
};