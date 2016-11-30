#pragma once

#include "BaseRes.h"



class FormulaRes : public BaseRes
{
public:
	FormulaRes(ACE_UINT32 unType);
	virtual ~FormulaRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	CostInfoList m_costList;
	ACE_UINT32 m_unRecipeRequired;
};