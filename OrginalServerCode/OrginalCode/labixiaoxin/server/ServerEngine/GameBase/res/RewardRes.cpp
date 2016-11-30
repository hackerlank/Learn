#include "RewardRes.h"
#include "ItemResMgr.h"

RewardRes::RewardRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	ACE_OS::memset(&m_reward, 0, sizeof(ConfigReward));
}

RewardRes::~RewardRes()
{

}

int RewardRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"reward") == 0)
	{
		parse_reward_list(m_reward, (char *)xmlNodeGetContent(node));
	}
	return 0;
}

void RewardRes::process_res_id_by_name()
{
}

int RewardRes::parse_reward_group(ConfigReward rewardList[], char *str)
{
	int len = ACE_OS::strlen(str);
	int start, end;

	char tmp[1024];

	int i;
	int c;
	int ret = 0;
	for(i = 0;i < len;i ++)
	{
		if(str[i] == '{')
		{
			start = i;
		}
		else if(str[i] == '}')
		{
			end = i;

			c = end - (start + 1);
			ACE_OS::strncpy(tmp, &str[start + 1], c);
			tmp[c] = '\0';
			
			parse_reward_list(rewardList[ret], tmp);
			ret ++;
		}
	}

	return ret;
}

void RewardRes::parse_reward_list(ConfigReward &reward, char *str)
{
	int c = 0;

	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	ACE_OS::memset(&reward, 0, sizeof(ConfigReward));

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ';');
		if(parse_reward(reward.list[c], tmp) == 0)
		{
			if(reward.list[c].unResID == RES_CURRENCY_COIN)
			{
				reward.unCoin = reward.list[c].unCount;
			}
			else if(reward.list[c].unResID == RES_CURRENCY_MONEY)
			{
				reward.unMoney = reward.list[c].unCount;
			}
			else if(reward.list[c].unResID == RES_CURRENCY_ENERGY)
			{
				reward.unEnergy = reward.list[c].unCount;
			}
			else if(reward.list[c].unResID == RES_CURRENCY_POWERPOINT)
			{
				reward.unPowerPoint = reward.list[c].unCount;
			}
			else if(reward.list[c].unResID == RES_CURRENCY_EXP)
			{
				reward.unExp = reward.list[c].unCount;
			}
			else if(reward.list[c].unResID == RES_CURRENCY_RECHARGE)
			{
				reward.unRecharge = reward.list[c].unCount;
			}
			else if(reward.list[c].unResID == RES_CURRENCY_HONOUR)
			{
				reward.unHonour = reward.list[c].unCount;
			}
			else if(reward.list[c].unResID == RES_CURRENCY_PVP_ENERGY)
			{
				reward.unPVPEnergy = reward.list[c].unCount;
			}
			else if (reward.list[c].unResID == RES_CURRENCY_FRIENDSHIP)
			{
				reward.unFriendship = reward.list[c].unCount;
			}
			else if (reward.list[c].unResID == RES_CURRENCY_DYNAMIC_ENERGY)
			{
				reward.unDynamicEnergy = reward.list[c].unCount;
			}
			else
			{
				c ++;
			}
		}
	}

	reward.unCount = c;
	//return c;
}

int RewardRes::parse_reward(ConfigRewardInfo &dest, char *str)
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
			//dest.unResID = ACE_OS::atoi(tmp);
			//dest.unResID = ACE_OS::strtol(tmp, NULL, 16);
			dest.unResID = GameUtils::parse_res_id(tmp);
		}
		else
		{
			dest.unCount = ACE_OS::atoi(tmp);
		}
	}

	return 0;
}