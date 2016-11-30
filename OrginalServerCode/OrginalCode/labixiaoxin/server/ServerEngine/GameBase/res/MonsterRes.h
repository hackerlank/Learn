#pragma once

#include "BaseRes.h"

class MonsterRes : public BaseRes
{
public:
	MonsterRes(ACE_UINT32 unType);
	virtual ~MonsterRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	//ACE_UINT32 m_unMonsterType;
	ACE_UINT32 m_unLevel;
};