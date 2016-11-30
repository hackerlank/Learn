#pragma once

#include "BaseRes.h"

class MallRes : public BaseRes
{
public:
	MallRes(ACE_UINT32 unType);
	virtual ~MallRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_unGold;
	ACE_UINT32 m_unRMB;
};