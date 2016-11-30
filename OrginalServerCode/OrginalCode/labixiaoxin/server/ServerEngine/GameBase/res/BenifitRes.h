#pragma once

#include "BaseRes.h"

class BenifitRes : public BaseRes
{
public:
	BenifitRes(ACE_UINT32 unType);
	virtual ~BenifitRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	BenefitList m_benefitList;
	//PropertyList m_propertyList;
	//PropertyComponent m_propertyList[PROPERTY_ID_MAX];
private:
	
};