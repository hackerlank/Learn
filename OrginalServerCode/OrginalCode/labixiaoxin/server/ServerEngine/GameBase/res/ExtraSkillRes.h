#pragma once

#include "BaseRes.h"

class ExtraSkillRes : public BaseRes
{
public:
	ExtraSkillRes(ACE_UINT32 unType);
	virtual ~ExtraSkillRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();


	//PropertyList m_propertyList;
	//PropertyComponent m_propertyList[PLAYER_PROPERTY_MAX];
	ACE_UINT32 m_unSkillLevel;
	//ACE_UINT32 m_unDamageCount;
	ACE_UINT32 m_unSkillType;
	ACE_UINT32 m_unSkillValueType;
	ACE_UINT32 m_unValue;

	ACE_UINT32 m_unEnergyCost;

private:
	void parse_skill_param(char *str);
};