#pragma once

#include "BaseRes.h"

class GrowingRes : public BaseRes
{
public:
	GrowingRes(ACE_UINT32 unType);
	virtual ~GrowingRes();

	int init(xmlNodePtr rootNode);

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_valueList[PLAYER_PROPERTY_MAX];

private:
	
};