#include "DropMaterialRes.h"
#include "ItemResMgr.h"

CDropMaterialRes::CDropMaterialRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unCount = 0;
	ACE_OS::memset(&m_list, 0, sizeof(ConfigRewardInfo)*MAX_CONFIG_REWARD_COUNT);
}

CDropMaterialRes::~CDropMaterialRes()
{

}

int CDropMaterialRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"reward") == 0)
	{
		parse_reward((char *)xmlNodeGetContent(node));
	}
	return 0;
}

void CDropMaterialRes::process_res_id_by_name()
{
}

void CDropMaterialRes::parse_reward(char *str )
{
	int c = 0;

	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ';');
		if(Parse_info(m_list[c], tmp) == 0)
		{
			c++;
		}
	}

	m_unCount = c;
}

int CDropMaterialRes::Parse_info( ConfigRewardInfo &dest, char *str )
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	dest.unCount = 1;

	for(int i = 0;i < 2;i ++)
	{
		if(offset == -1)
		{
			break;
		}
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(i == 0)
		{
			dest.unResID = GameUtils::parse_res_id(tmp);
		}
		else
		{
			dest.unCount = ACE_OS::atoi(tmp);
		}
	}

	return 0;
}
