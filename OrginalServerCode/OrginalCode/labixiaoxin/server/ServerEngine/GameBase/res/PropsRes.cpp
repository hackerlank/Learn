#include "PropsRes.h"

int PropsRes::parse_xml_node( xmlNodePtr node )
{
	BaseRes::parse_xml_node(node);


	if(xmlStrcasecmp(node->name, BAD_CAST"parameter") == 0)
	{
		_parse_parameter_list((char *)xmlNodeGetContent(node));
	}
	//else if(xmlStrcasecmp(node->name, BAD_CAST"reward_preview") == 0)
	//{
	//	_parse_reward_preview_list((char *)xmlNodeGetContent(node));
	//}

	return 0;
}

void PropsRes::process_res_id_by_name()
{

}

void PropsRes::_parse_reward_preview_list(char *str)
{
	int len = strlen(str);

	char tmp[64];

	int offset = 0;
	//int idx;
	unsigned int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ';');

		if(c >= m_oRewardPreview.size())
			m_oRewardPreview.resize(c + 1);
		_parse_reward_preview(tmp, m_oRewardPreview[c]);
		c ++;
	}
}

void PropsRes::_parse_reward_preview(char *str, std::pair<ACE_UINT32, ACE_UINT32> &roRewardPreview)
{
	int len = strlen(str);

	char tmp[64];

	int offset = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(c == 0)
		{
			roRewardPreview.first = ACE_OS::atoi(tmp);
		}
		else
		{
			roRewardPreview.second = ACE_OS::atoi(tmp);
		}

		c ++;
	}
}

void PropsRes::_parse_parameter_list( char *str )
{
	int len = strlen(str);

	char tmp[64];

	int offset = 0;
	//int idx;
	unsigned int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(c >= m_oParameters.size())
			m_oParameters.resize(c + 1);
		m_oParameters[c] = GameUtils::parse_res_id(tmp);
		c ++;
	}
}

PropsRes::PropsRes( ACE_UINT32 unType )
:BaseRes(unType)
{

}

PropsRes::~PropsRes()
{

}
