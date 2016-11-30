#pragma once

#include "BaseRes.h"



class MaterialRes : public BaseRes
{
public:
	MaterialRes(ACE_UINT32 unType);
	virtual ~MaterialRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

};