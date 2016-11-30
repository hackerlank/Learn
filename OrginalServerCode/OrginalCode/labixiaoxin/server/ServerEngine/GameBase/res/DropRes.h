#pragma once

#include "BaseRes.h"

class DropRes : public BaseRes
{
public:
	DropRes(ACE_UINT32 unType);
	virtual ~DropRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	DropGroup m_dropGroup;

	//ACE_UINT32 m_unDropType;
	float m_fRate;

private:
	int m_step;
};