#pragma once

#include "BaseRes.h"

//#define GENERATE_IMPROVE_ID(quality,resID) (1600000000 + quality + (resID / 1000000) * 100)

#define GENERATE_IMPROVE_ID(quality,resID) (0x10000000 | ((GET_ITEM_ID_INFO(resID, 5, 1) << 20) & 0x00f00000) | (quality & 0xff))

class ImproveRes : public BaseRes
{
public:
	ImproveRes(ACE_UINT32 unType);
	virtual ~ImproveRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_unPowerPoint;
	//ACE_UINT32 m_unImprovePoint;
	//PropertyList m_propertyList;
	PropertyComponent m_propertyList[PLAYER_PROPERTY_MAX];
	double m_dImproveRate;
	double m_dPowerRate;
};