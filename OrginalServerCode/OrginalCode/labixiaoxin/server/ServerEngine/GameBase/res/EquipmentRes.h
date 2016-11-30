#pragma once

#include "BaseRes.h"

class EquipmentRes : public BaseRes
{
public:
	EquipmentRes(ACE_UINT32 unType);
	virtual ~EquipmentRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	
	//ACE_UINT32 m_unPrice;

	//PropertyList m_propertyList;
	//PropertyList m_improvePropertyList;
	PropertyComponent m_propertyList[PLAYER_PROPERTY_MAX];
	PropertyComponent m_improvePropertyList[PLAYER_PROPERTY_MAX];
	ACE_UINT32 m_charge_value;//充能值
	ACE_UINT32 m_level_require;//最小使用等级
};