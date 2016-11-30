#pragma once

#include "BaseRes.h"

class FunctionRes : public BaseRes
{
public:
	FunctionRes(ACE_UINT32 unType);
	virtual ~FunctionRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	ACE_UINT32 m_isLock;
private:

};