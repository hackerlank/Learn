#pragma once

#include "BaseRes.h"
#include <vector>

class PropsRes : public BaseRes
{
public:
	PropsRes(ACE_UINT32 unType);
	virtual ~PropsRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

private:
	void _parse_reward_preview_list(char *str);
	void _parse_reward_preview(char *str, std::pair<ACE_UINT32, ACE_UINT32> &period);
	void _parse_parameter_list(char *str);

public:
	std::vector<ACE_INT32> m_oParameters;
	std::vector<std::pair<ACE_UINT32, ACE_UINT32> > m_oRewardPreview;
};