#pragma once

#include "BaseRes.h"

class PlayerRes : public BaseRes
{
public:
	PlayerRes(ACE_UINT32 unType);
	virtual ~PlayerRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 get_init_equipment(ACE_UINT32 unType);

	ACE_UINT32 m_unRealID;
	ACE_UINT32 m_dwGrade;
	ACE_UINT32 m_dwChangeNum;
	ACE_UINT32 m_unBasicPropertyID;
	ACE_UINT32 m_unGrowingID;
	ACE_UINT32 m_unInitEquipmentList[EQUIPMENT_TYPE_MAX];
	//ACE_UINT32 m_unGrowthFormula;
	//PropertyList m_propertyList;
	//PropertyComponent m_propertyList[PROPERTY_ID_MAX];
	ACE_UINT32 m_unSkillID;

	static ACE_UINT32 get_current_step(PlayerRes *res, ACE_UINT32 unLevel);
	static ACE_UINT32 get_max_level(PlayerRes *res, ACE_UINT32 unStep);
private:
	void parse_init_equipment_list(char *str);
};