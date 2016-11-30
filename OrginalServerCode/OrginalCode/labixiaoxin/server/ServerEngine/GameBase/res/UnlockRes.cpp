#include "UnlockRes.h"
#include "ItemResMgr.h"

UnlockRes::UnlockRes(ACE_UINT32 unType)
:RewardRes(unType)
{
	ACE_OS::memset(&m_reward, 0, sizeof(ConfigReward));

	ACE_OS::memset(&m_require, 0, sizeof(UnlockRequireInfo));
}

UnlockRes::~UnlockRes()
{

}

int UnlockRes::parse_xml_node(xmlNodePtr node)
{
	RewardRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"unlock_require") == 0)
	{
		parse_require(m_require, (char *)xmlNodeGetContent(node));
	}
	
	return 0;
}

void UnlockRes::process_res_id_by_name()
{
}

void UnlockRes::parse_require(UnlockRequireInfo &dest, char *str)
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	for(int i = 0;i < 2;i ++)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(i == 0)
		{
			dest.unType = ACE_OS::atoi(tmp) - 1;
		}
		else
		{
			dest.unValue = ACE_OS::atoi(tmp);
		}
	}
}
