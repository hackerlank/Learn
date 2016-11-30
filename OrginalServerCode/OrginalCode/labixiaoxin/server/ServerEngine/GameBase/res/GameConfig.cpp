#include "GameConfig.h"

#include "ItemResMgr.h"
#include "MapRes.h"
#include "RewardRes.h"
#include "PlayerRes.h"
//#include "MapResMgr.h"
//#include "QuestResMgr.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

ACE_INT32 GameConfig::g_maxSetup = 0;


GameConfig::GameConfig()
{
	m_maxLevel = 0;
	m_defaultName[0] = '\0';
	m_unInitPlayerCount = 0;
	m_unInitBenefitCount = 0;

	m_unGetLuckCost = 30;
	m_unGetMoreLuckCost = 300;

	m_unRebornCost = 6;
	m_unRenameCost = 10;
	m_unRefreshDoubleDropVersion = 0;

	ACE_OS::memset(m_loginBonusList, 0, sizeof(ACE_UINT32) * MAX_LOGIN_BONUS_COUNT);
	ACE_OS::memset(&m_firstRechargeReward, 0, sizeof(ConfigReward));
	ACE_OS::memset(m_teamLevel, 0, sizeof(TeamLevel) * (MAX_TEAM_LEVEL + 1));
	ACE_OS::memset(m_roleStepInfo, 0, sizeof(RoleStepInfo) * (MAX_ROLE_STEP + 1));
	ACE_OS::memset(m_vecFormulaInfo, 0, sizeof(FormulaInfo) * 3);
	m_oHLmin = 0x0FFFFFFF;
	m_oHLmax = 0;
	
}

GameConfig::~GameConfig()
{
	
}

int GameConfig::load_all_config()
{
	if(this->load_config(CONFIG_TYPE_MALL, "config/mall.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_LOOT_REPLACE, "config/replace.xml") == -1)
	{
		return -1;
	}

	if(this->load_config(CONFIG_TYPE_GAME_CONFIG, "config/game_config.xml") == -1)
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_SECRET_CONFIG, "config/secret_config.xml") == -1)
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_PVP100,"config/pvp_100.xml")== -1)
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_TEAM_LEVEL, "config/teamlevel.xml") == -1)
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_GRADE, "config/grade.xml") == -1)
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_SIGN_UP, "config/signup.xml") == -1)
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_GIFT_BAG_CODE, "config/giftCode.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_DOUBLE_DROP, "config/bonusmap.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_TASK, "config/mainmission.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_ACTIVE_MISSION, "config/activemission.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_ACTIVE_PRIZE, "config/activeprize.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_EQUIP_STEP, "config/equipstep.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_ROBOT_PLAYER, "config/RobotChars.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_ROBOT_TEAM, "config/RobotTeams.xml") == -1)
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_LIMITED_ACTIVITY,"config/limitedactivity.xml") == -1)//限时活动时间表
	{
		return -1;
	}
	if(this->load_config(CONFIG_TYPE_LIMITED_MISSION_ACTIVITY,"config/limitedactivitymission.xml") == -1)//限时活动任务表
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_GOLDEN_TOUCH_PROFIT, "config/goldentouchprofit.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_GOLDEN_TOUCH_COST, "config/goldentouchcost.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_BUY_ENERGY_COST,"config/buyenergycost.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_CHANNEL, "config/channel.xml") == -1)
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_BADGELEVEL, "config/badgelevel.xml") == -1)//徽章能量升级
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_HONORLEVEL, "config/honorlevel.xml") == -1)//pvp每日排名
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_HONORRANK, "config/honorrank.xml") == -1)//pvp赛季排名
	{
		return -1;
	}
	if (this->load_config(CONFIG_TYPE_HONORCOST, "config/honorcost.xml") == -1)//pvp消耗
	{
		return -1;
	}

	return 0;
}

int GameConfig::deal_config(int config_id, xmlNodePtr rootNode)
{
	switch(config_id)
	{
	case CONFIG_TYPE_MALL:
		break;
	case CONFIG_TYPE_LOOT_REPLACE:
		parse_loot_replace_config(rootNode);
		break;
	case CONFIG_TYPE_GAME_CONFIG:
		parse_game_config(rootNode);
		break;
	case CONFIG_TYPE_SECRET_CONFIG:
		parse_secret_config(rootNode);
		break;
	case CONFIG_TYPE_PVP100:
		parse_pvp100_config(rootNode);
		break;
	case CONFIG_TYPE_TEAM_LEVEL:
		parse_team_level_config(rootNode);
		break;
	case CONFIG_TYPE_GRADE:
		parse_grade_config(rootNode);
		break;
	case CONFIG_TYPE_SIGN_UP:
		parse_sign_up_config(rootNode);
		break;
	case CONFIG_TYPE_GIFT_BAG_CODE:
		parse_gift_bag_code_config(rootNode);
		break;
	case CONFIG_TYPE_DOUBLE_DROP:
		{
			parse_double_drop_config(rootNode);
		}break;
	case CONFIG_TYPE_TASK:
		{
			parse_task_config(rootNode);
		}break;
	case CONFIG_TYPE_ACTIVE_MISSION:
		{
			parse_active_mission(rootNode);
		}break;
	case CONFIG_TYPE_ACTIVE_PRIZE:
		{
			parse_active_prize(rootNode);
		}break;
	case CONFIG_TYPE_EQUIP_STEP:
		{
			parse_equip_step(rootNode);
		}break;
	case CONFIG_TYPE_ROBOT_PLAYER:
		{
			parse_robot_player(rootNode);
		}break;
	case CONFIG_TYPE_ROBOT_TEAM:
		{
			parse_robot_team(rootNode);
		}break;
	case CONFIG_TYPE_LIMITED_ACTIVITY://限时活动时间表
		{
			Parse_limited_activity(rootNode);
		}break;
	case CONFIG_TYPE_LIMITED_MISSION_ACTIVITY://限时活动任务表
		{
			Parse_limited_mission_activity(rootNode);
		}break;
	case CONFIG_TYPE_GOLDEN_TOUCH_PROFIT:
		{
			Parse_golden_touch_profit(rootNode);
		}break;
	case CONFIG_TYPE_GOLDEN_TOUCH_COST:
		{
			Parse_golden_touch_cost(rootNode);
		}break;
	case CONFIG_TYPE_BUY_ENERGY_COST:
		{
			Parse_BuyEnergy_cost(rootNode);
		}break;
	case CONFIG_TYPE_CHANNEL:
		{
			Parse_channel(rootNode);
		}
		break;
	case CONFIG_TYPE_BADGELEVEL:
		{
			Parse_badgeLevel(rootNode);
		}break;
	case CONFIG_TYPE_HONORLEVEL://pvp 每日排名
		{
			parse_honor_level(rootNode);
		}break;
	case CONFIG_TYPE_HONORRANK://pvp 赛季排名
		{
			parse_honor_rank(rootNode);
		}break;
	case CONFIG_TYPE_HONORCOST:
		{
			parse_honor_cost(rootNode);
		}break;
	}

	return 0;
}

void GameConfig::parse_loot_replace_config(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"replace") == 0)
		{
			parse_loot_replace(childNode);
		}

		childNode = childNode->next;
	}
}

void GameConfig::parse_loot_replace(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	//ACE_UINT32 unID = 0;
	//DropGroup *group = NULL;

	while(childNode != NULL)
	{
		/*
		if(xmlStrcasecmp(childNode->name, BAD_CAST"replace_id") == 0)
		{
			//unID = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			unID = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);
		}
		*/
		if(xmlStrcasecmp(childNode->name, BAD_CAST"drop_list") == 0)
		{
			/*
			group = new DropGroup();

			if(group != NULL)
			{
				GameUtils::parse_drop_group(*group, (char *)xmlNodeGetContent(childNode), true);
			}
			*/
			RewardRes::parse_reward_list(m_lootReplaceReward, (char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}

}

void GameConfig::parse_game_config(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	ACE_OS::memset(m_InitPlayerList, 0, sizeof(ACE_UINT32) * MAX_PLAYER_COUNT);
	ACE_OS::memset(m_InitEquipmentList, 0, sizeof(ACE_UINT32) * MAX_EQUIPMENT_COUNT);

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"player_list") == 0)
		{
			//m_unResID = generate_id(ACE_OS::atoi((char *)xmlNodeGetContent(childNode)));
			//parse_init_player_list(childNode);
			m_unInitPlayerCount = parse_init_id_list(childNode, m_InitPlayerList);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"init_select_player") == 0)
		{
			//m_unResID = generate_id(ACE_OS::atoi((char *)xmlNodeGetContent(childNode)));
			//parse_init_player_list(childNode);
			m_unInitSelectPlayerCount = parse_init_id_list(childNode, m_InitSelectPlayerList);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"equipment_list") == 0)
		{
			//parse_init_equipment_list(childNode);
			parse_init_id_list(childNode, m_InitEquipmentList);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"energy") == 0)
		{
			this->parse_energy(childNode, true);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"pvp_energy") == 0)
		{
			this->parse_energy(childNode, false);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"coin") == 0)
		{
			m_unInitCoin = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"default_name") == 0)
		{
			ACE_OS::memcpy(m_defaultName, (char *)xmlNodeGetContent(childNode), MAX_CHARACTER_LENGTH);
			m_defaultName[MAX_CHARACTER_LENGTH] = '\0';
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"career_list") == 0)
		{
			parse_career_list(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"skill_price") == 0)
		{
			parse_skill_price_list(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"friend") == 0)
		{
			this->parse_expand_info(childNode, m_friendExpandInfo);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"package") == 0)
		{
			this->parse_expand_info(childNode, m_packageExpandInfo);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"unlock_mapid") == 0)
		{
			//m_unInitUnlockMapID = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);
			m_unInitUnlockMapID = GameUtils::parse_res_id((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"benefit_list") == 0)
		{
			//parse_init_benefit_list(childNode);
			m_unInitBenefitCount = parse_init_id_list(childNode, m_InitBenefitList);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"reward_gold") == 0)
		{
			parse_get_luck_cost(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"reward_login") == 0)
		{
			parse_login_bonus(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"first_reward") == 0)
		{
			get_luck_fix_reward(0, childNode);
			//GameUtils::parse_re
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"second_reward") == 0)
		{
			get_luck_fix_reward(1, childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"revive_hero") == 0)
		{
			m_unRebornCost = get_cost(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"rename_cost") == 0)
		{
			m_unRenameCost = get_cost(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"player_maxLv") == 0)  //added by jinpan for level limit
		{
			m_unMaxLv = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}

		else if(xmlStrcasecmp(childNode->name, BAD_CAST"version_number") == 0)
		{
			m_unCurrentVersion = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"first_recharge_reward") == 0)
		{
			//m_unCurrentVersion = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			RewardRes::parse_reward_list(m_firstRechargeReward, (char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"shopoff") == 0)
		{
			//m_unCurrentVersion = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			m_fSecretOff = (float)ACE_OS::atof((char *)xmlNodeGetContent(childNode));
		}
		else if (xmlStrcasecmp(childNode->name, BAD_CAST"bonus_stage_refresh_sec") == 0)
		{
			m_unRefreshDoubleDropSecs = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if (xmlStrcasecmp(childNode->name, BAD_CAST"friendship_get_friend") == 0)
		{
			m_unAddFriendshipFriend = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if (xmlStrcasecmp(childNode->name, BAD_CAST"friendship_return_friend") == 0)
		{
			m_unReturnFriendshipFriend = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if (xmlStrcasecmp(childNode->name, BAD_CAST"friendship_get_stranger") == 0)
		{
			m_unAddFriendshipStranger = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if (xmlStrcasecmp(childNode->name, BAD_CAST"friendship_return_stranger") == 0)
		{
			m_unReturnFriendshipStranger = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if (xmlStrcasecmp(childNode->name,BAD_CAST"formula_player") == 0)//xxj 2015/04/22  16:43:51 1：角色升级
		{
			Parse_Formula_config((char *)xmlNodeGetContent(childNode),0);
		}
		else if (xmlStrcasecmp(childNode->name,BAD_CAST"formula_equipment") == 0)//xxj 2015/04/22  16:43:51 装备升级
		{
			Parse_Formula_config((char *)xmlNodeGetContent(childNode),1);
		}
		else if (xmlStrcasecmp(childNode->name,BAD_CAST"formula_energy") == 0)//xxj 2015/04/22  16:43:51 升级恢复体力
		{
			Parse_Formula_config((char *)xmlNodeGetContent(childNode),2);
		}
		else if (xmlStrcasecmp(childNode->name,BAD_CAST"formula_multenergy") == 0)//xxj 2015/04/22  16:43:51 多倍体力公式
		{
			Parse_Formula_config((char *)xmlNodeGetContent(childNode),3);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"honor_rank") == 0)
		{
			parse_gameconfig_honor_rank(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"button_unlock") == 0)
		{
			parse_gameconfig_button_unlock(childNode);
		}

		childNode = childNode->next;
	}
}

void GameConfig::parse_login_gold(char *str)
{
	int c = 0;

	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		m_loginBonusList[c] = GameUtils::parse_res_id(tmp);

		c ++;
	}
}

void GameConfig::parse_login_bonus(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"gold") == 0)
		{
			parse_login_gold((char *)xmlNodeGetContent(childNode));
			//m_unGetLuckCost = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}
}

void GameConfig::parse_get_luck_cost(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"times1") == 0)
		{
			m_unGetLuckCost = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"times10") == 0)
		{
			m_unGetMoreLuckCost = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}
}

ACE_UINT32 GameConfig::parse_init_id_list(xmlNodePtr rootNode, ACE_UINT32 *dest)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;
	int c = 0;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"id") == 0)
		{
			//m_InitPlayerList[c] = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			//dest[c] = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);
			dest[c] = GameUtils::parse_res_id((char *)xmlNodeGetContent(childNode));

			c ++;
		}

		childNode = childNode->next;
	}

	//m_unInitPlayerCount = c;
	return c;
}

/*
void GameConfig::parse_init_player_list(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;
	int c = 0;
	m_unInitPlayerCount = 0;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"id") == 0)
		{
			//m_InitPlayerList[c] = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			m_InitPlayerList[c] = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);

			c ++;
		}

		childNode = childNode->next;
	}

	m_unInitPlayerCount = c;
}

void GameConfig::parse_init_benefit_list(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;
	int c = 0;
	m_unInitBenefitCount = 0;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"id") == 0)
		{
			//m_InitPlayerList[c] = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			m_InitBenefitList[c] = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);

			c ++;
		}

		childNode = childNode->next;
	}

	m_unInitBenefitCount = c;
}

void GameConfig::parse_init_equipment_list(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;
	int c = 0;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"id") == 0)
		{
			//m_InitEquipmentList[c] = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			m_InitEquipmentList[c] = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);

			c ++;
		}

		childNode = childNode->next;
	}
}
*/

void GameConfig::parse_career_list(xmlNodePtr rootNode)
{
	int c = 0;

	xmlNodePtr childNode;
	xmlNodePtr subNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"career") == 0)
		{
			subNode = childNode->xmlChildrenNode;


			while(subNode != NULL)
			{
				if(xmlStrcasecmp(subNode->name, BAD_CAST"character_id") == 0)
				{
					//m_careerList[c].unCharacterID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
					//m_careerList[c].unCharacterID = ACE_OS::strtol((char *)xmlNodeGetContent(subNode), NULL, 16);
					m_careerList[c].unCharacterID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				}
				else if(xmlStrcasecmp(subNode->name, BAD_CAST"equipment_type") == 0)
				{
					//m_careerList[c].unEquipmentTypeID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
					//m_careerList[c].unEquipmentTypeID = ACE_OS::strtol((char *)xmlNodeGetContent(subNode), NULL, 16);
					m_careerList[c].unEquipmentTypeID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				}
				else if(xmlStrcasecmp(subNode->name, BAD_CAST"skill_type") == 0)
				{
					//m_careerList[c].unSkillTypeID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
					//m_careerList[c].unSkillTypeID = ACE_OS::strtol((char *)xmlNodeGetContent(subNode), NULL, 16);
					m_careerList[c].unSkillTypeID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				}
				else if(xmlStrcasecmp(subNode->name, BAD_CAST"unlock_id") == 0)
				{
					//m_careerList[c].unSkillTypeID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
					//m_careerList[c].unRequiredPlayerID = ACE_OS::strtol((char *)xmlNodeGetContent(subNode), NULL, 16);
					m_careerList[c].unRequiredPlayerID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				}

				subNode = subNode->next;
			}

			c ++;
		}

		childNode = childNode->next;
	}

}

void GameConfig::parse_skill_price_list(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;
	xmlNodePtr subNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"skill") == 0)
		{
			subNode = childNode->xmlChildrenNode;

			int idx = -1;
			int price = 0;
			while(subNode != NULL)
			{
				if(xmlStrcasecmp(subNode->name, BAD_CAST"level") == 0)
				{
					idx = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
					idx = idx - 1;
				}
				else if(xmlStrcasecmp(subNode->name, BAD_CAST"price") == 0)
				{
					price = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
				}

				subNode = subNode->next;
			}

			if(idx != -1)
			{
				m_unSkillPriceList[idx] = price;
			}
		}

		childNode = childNode->next;
	}
}

ACE_UINT32 GameConfig::get_main_character_id_by_equipment(ACE_UINT32 unEquipmentID)
{
	ACE_UINT32 ret = 0;

	//ACE_UINT32 t = unEquipmentID / 10000;
	ACE_UINT32 t = GET_ITEM_ID_INFO(unEquipmentID, 3, 3);

	for(int i = 0;i < MAX_MAIN_CHARACTER_ID;i ++)
	{
		if(m_careerList[i].unEquipmentTypeID == t)
		{
			ret = m_careerList[i].unCharacterID;
			break;
		}
	}

	return ret;
}

ACE_UINT32 GameConfig::get_required_player_id_by_equipment(ACE_UINT32 unEquipmentID)
{
	ACE_UINT32 ret = 0;

	//ACE_UINT32 t = unEquipmentID / 10000;
	ACE_UINT32 t = GET_ITEM_ID_INFO(unEquipmentID, 3, 3);

	for(int i = 0;i < MAX_MAIN_CHARACTER_ID;i ++)
	{
		if(m_careerList[i].unEquipmentTypeID == t)
		{
			ret = m_careerList[i].unRequiredPlayerID;
			break;
		}
	}

	return ret;
}

void GameConfig::parse_energy(xmlNodePtr rootNode, bool flag)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"max") == 0)
		{
			if(flag)
			{
				m_unMaxEnergy = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			}
			else
			{
				m_unMaxPVPEnergy = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			}
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"restore") == 0)
		{
			if(flag)
			{
				m_unEnergyRestoreInterval = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			}
			else
			{
				m_unPVPEnergyRestoreInterval = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			}
			
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"gold") == 0)
		{
			if(flag)
			{
				m_unRestoreEnergyGold = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			}
			else
			{
				m_unPVPRestoreEnergyGold = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			}
			
		}

		childNode = childNode->next;
	}
}

void GameConfig::parse_expand_info(xmlNodePtr rootNode, PackageExpandInfo &info)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"min") == 0)
		{
			info.unMin = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"max") == 0)
		{
			info.unMax = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"count_up") == 0)
		{
			info.unCountPerTime = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"gold") == 0)
		{
			info.unGold = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}
}

void GameConfig::get_luck_fix_reward(int idx, xmlNodePtr rootNode)
{
	//ACE_UINT32 unRet;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"drop_id") == 0)
		{
			//unRet = ACE_OS::strtol((char *)xmlNodeGetContent(childNode), NULL, 16);
			RewardRes::parse_reward_list(m_luckFixRewardList[idx], (char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}

	//return unRet;
}

ACE_UINT32 GameConfig::get_cost(xmlNodePtr rootNode)
{
	ACE_UINT32 unRet = 0;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"gold") == 0)
		{
			unRet = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}

	return unRet;
}

void GameConfig::parse_secret_config(xmlNodePtr rootNode)  //added by jinpan
{
	ACE_UINT32 unRet = 0;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;
	int c = 0;
	while(childNode != NULL){

		if(xmlStrcasecmp(childNode->name, BAD_CAST"cell_price") == 0)		//开格子价钱
		{
			GameUtils::parse_secret_item(m_secretCfg.cellPrice, (char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"special_amount") == 0)  //个数需要特别处理的物品
		{
			GameUtils::parse_secret_item(m_secretCfg.specialAmount, (char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"refresh_rmb") == 0) //元宝刷新
		{
			GameUtils::parse_secret_item(&m_secretCfg.moenyRefresh, (char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"refresh_item") == 0)  //道具刷新
		{
			GameUtils::parse_secret_item(&m_secretCfg.itemRefresh, (char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"refresh_sec") == 0)
		{
			m_secretCfg.unRefreshSec = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
			printf("--------%d", m_secretCfg.unRefreshSec);
		}

		if(xmlStrcasecmp(childNode->name, BAD_CAST"higher_refresh_rmb") == 0)  //高级金币刷新
		{
			GameUtils::parse_secret_item(&m_secretCfg.higher_moenyRefresh, (char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"higher_refresh_rmbadd") == 0)  //高级金币刷新,每次价格增加值
		{
			m_secretCfg.unHigher_moneyRefresh_increase = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"higher_refresh_rmbmax") == 0)  //高级金币刷新，价格最大值
		{
			m_secretCfg.unHigher_moneyRefresh_increaseUpperBound = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"higher_refresh_item") == 0)  //高级道具刷新
		{
			GameUtils::parse_secret_item(&m_secretCfg.higher_itemRefresh, (char *)xmlNodeGetContent(childNode));
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"max_cell") == 0)  //最多格子数
		{
			m_secretCfg.unMaxCell = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		
	
		if(xmlStrcasecmp(childNode->name, BAD_CAST"secret") == 0){
			xmlNodePtr childrenNode = childNode->children;
			while(childrenNode != NULL){
				if(xmlStrcasecmp(childrenNode->name, BAD_CAST"cell") == 0)
				{
					m_secretCfg.secretCfg[c].unCell = ACE_OS::atoi((char *)xmlNodeGetContent(childrenNode));
				}
				if(xmlStrcasecmp(childrenNode->name, BAD_CAST"certain_list") == 0)
				{
					m_secretCfg.secretCfg[c].unCertainCount = GameUtils::parse_secret_list(m_secretCfg.secretCfg[c].certainList, (char *)xmlNodeGetContent(childrenNode));
					if(m_secretCfg.secretCfg[c].unCell == 0){
							m_secretCfg.secretCfg[c].unCertainCount = 0; //0个格子表示低级刷新，不保底出 jinpan
					}

				}
				
				if(xmlStrcasecmp(childrenNode->name, BAD_CAST"other_items") == 0)
				{					
					m_secretCfg.secretCfg[c].unOtherCount = GameUtils::parse_secret_list(m_secretCfg.secretCfg[c].unOtherItems, (char *)xmlNodeGetContent(childrenNode));

				}
				
				childrenNode = childrenNode->next;
			}
			c++;

		}

		

		childNode = childNode->next;



	}
	m_secretCfg.unCount = c;


}


void GameConfig::parse_pvp100_config(xmlNodePtr rootNode)  //处理百人斩配置  jinpan
{
	ACE_UINT32 unRet = 0;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;




	int c = 0;
	while(childNode != NULL){
		xmlNodePtr subNode = childNode->children;
		while(subNode != NULL){
			if(xmlStrcasecmp(subNode->name, BAD_CAST"stage") == 0)		//这轮pvp需要斩杀的人数
			{
				m_pvp100Cfg.pvp100Cfg[c].unStage = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			if(xmlStrcasecmp(subNode->name, BAD_CAST"pvp_count") == 0)		//这轮pvp需要斩杀的人数
			{
				m_pvp100Cfg.pvp100Cfg[c].unCount = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			if(xmlStrcasecmp(subNode->name, BAD_CAST"points") == 0)		//这轮pvp需要斩杀的人数
			{
				GameUtils::parse_pvp_item(&m_pvp100Cfg.pvp100Cfg[c].points ,(char *)xmlNodeGetContent(subNode));
			}
			if(xmlStrcasecmp(subNode->name, BAD_CAST"reward") == 0)		//当前所在等级的额外
			{
				GameUtils::parse_cost_list(m_pvp100Cfg.pvp100Cfg[c].reward,(char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		
		childNode = childNode->next;
		c++;


	}
	m_pvp100Cfg.unCount = c;
}

void GameConfig::parse_team_level_config( xmlNodePtr rootNode )
{
	ACE_UINT32 unRet = 0;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;
	ACE_UINT32 _level = 0;

	while(childNode != NULL){
		int level = 0;
		xmlNodePtr subNode = childNode->children;
		while(subNode != NULL){
			if(xmlStrcasecmp(subNode->name, BAD_CAST"level") == 0)		
			{
				level = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
				if (level > _level)
					_level = level;

				m_teamLevel[level].level = level;
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"levelup_exp") == 0)		
			{
				m_teamLevel[level].levelup_exp = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"extraskill_slots") == 0)		
			{
				m_teamLevel[level].extraskill_slots = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"extraskill_learn") == 0)		
			{
				m_teamLevel[level].extraskill_learn =  GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"player_levelmax") == 0)		
			{
				m_teamLevel[level].player_levelmax = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"equip_levelmax") == 0)		
			{
				m_teamLevel[level].equip_levelmax = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}

		childNode = childNode->next;
	}

	m_maxLevel = _level;
}

void GameConfig::parse_grade_config( xmlNodePtr rootNode )
{
	ACE_UINT32 unRet = 0;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;


	while(childNode != NULL){
		int level = 0;
		xmlNodePtr subNode = childNode->children;
		while(subNode != NULL){
			if(xmlStrcasecmp(subNode->name, BAD_CAST"gradelevel") == 0)		
			{
				level = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
				m_roleStepInfo[level].step = level;
				if (g_maxSetup < level)
				{
					g_maxSetup = level;
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"upgradecost") == 0)		
			{
				m_roleStepInfo[level].upgrade_cost = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if (xmlStrcasecmp(subNode->name, BAD_CAST"role_lv_require") == 0)
			{
				m_roleStepInfo[level].role_lv_require = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;

			if (level >= MAX_ROLE_STEP) 
			{
				printf("parse_grade_config error , out off len\n");
				break;	
			}
		}

		childNode = childNode->next;
	}
}

void GameConfig::parse_sign_up_config( xmlNodePtr rootNode )
{
	ACE_UINT32 unRet = 0;
	xmlNodePtr childNode;
	m_oSignUpGift.clear();
	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL){
		int dwYear = 0, dwMonth = 0, dwDay = 0;
		SignUpGift oSignUpGift;
		xmlNodePtr subNode = childNode->children;
		while(subNode != NULL){
			if(xmlStrcasecmp(subNode->name, BAD_CAST"Year") == 0)		
			{
				dwYear = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Month") == 0)		
			{
				dwMonth = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Day") == 0)		
			{
				dwDay = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"VIPCheck") == 0)		
			{
				oSignUpGift.m_dwVipCheck = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"ItemID") == 0)		
			{
				int offset = 0;
				char* str = (char *)xmlNodeGetContent(subNode);
				int len = ACE_OS::strlen(str);
				if(len > 2)
				{
					char tmp[64];

					for(int i = 0;i < 2;i ++)
					{
						offset = GameUtils::value_token(str, offset, len, tmp, ',');

						if(i == 0)
						{
							//info.unID = ACE_OS::strtol(tmp, NULL, 16);
							oSignUpGift.m_dwRewardID = GameUtils::parse_res_id(tmp);
						}
						else
						{
							oSignUpGift.m_dwRewardCount = ACE_OS::atoi(tmp);
						}
					}
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"ItemIDVip") == 0)		
			{
				int offset = 0;
				char* str = (char *)xmlNodeGetContent(subNode);
				int len = ACE_OS::strlen(str);
				if(len > 2)
				{
					char tmp[64];

					for(int i = 0;i < 2;i ++)
					{
						offset = GameUtils::value_token(str, offset, len, tmp, ',');

						if(i == 0)
						{
							//info.unID = ACE_OS::strtol(tmp, NULL, 16);
							oSignUpGift.m_dwVipRewardID = GameUtils::parse_res_id(tmp);
						}
						else
						{
							oSignUpGift.m_dwVipRewardCount = ACE_OS::atoi(tmp);
						}
					}
				}
			}
			subNode = subNode->next;
		}

		oSignUpGift.m_dwDate = dwDay + dwMonth * 100 + dwYear * 10000;
		//m_oSignUpGift.insert(std::pair<int, SignUpGift>(oSignUpGift.m_dwDate,oSignUpGift));
		m_oSignUpGift[oSignUpGift.m_dwDate] = oSignUpGift;

		childNode = childNode->next;
	}
}

void GameConfig::parse_gift_bag_code_config(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	GiftBagCodeReward oReward;
	ACE_UINT32 unGiftBagCodeType = 0;
	ConfigReward *pReward = NULL;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"GiftTypeID") == 0)
			{
				unGiftBagCodeType = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"GiftID") == 0)		
			{
				oReward.unGiftBagID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"DeadLine") == 0)		
			{
				oReward.tExpiredTime = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		m_oGiftBagCodeReward.insert(std::make_pair(unGiftBagCodeType, oReward));

		childNode = childNode->next;
	}
}

void GameConfig::parse_double_drop_config(xmlNodePtr rootNode)
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	std::map<UINT32, ACE_Byte> conMap;
	ACE_UINT32 unRawMapID = 0;
	ACE_Byte unDoubleType = 0;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		conMap.clear();
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"GoldDouble") == 0)
			{
				GameUtils::parse_double_drop(conMap, (char *)xmlNodeGetContent(subNode), 0);
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"DropDouble") == 0)		
			{
				GameUtils::parse_double_drop(conMap, (char *)xmlNodeGetContent(subNode), 1);
			}
			subNode = subNode->next;
		}
		m_vecDoubleDropMap.push_back(conMap);
		childNode = childNode->next;
	}
}

void GameConfig::parse_task_config(xmlNodePtr rootNode)
{
	ACE_UINT32 unTaskID = 0;
	TaskConfig stConfig;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		unTaskID = 0;
		memset(&stConfig, 0, sizeof(TaskConfig));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"ID") == 0)
			{
				stConfig.unID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"LvLimit") == 0)
			{
				stConfig.unLevelCase = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"PreMissionID") == 0)
			{
				stConfig.unPremiseTaskCase = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"NextMissionID") == 0)
			{
				stConfig.unNextTaskID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"MissionType") == 0)
			{
				sscanf((char *)xmlNodeGetContent(subNode), "%d,%x,%d", &stConfig.unActiveEventType, &stConfig.unAttachID, &stConfig.unCompleteCount);
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"PrizeItem") == 0)		
			{
				RewardRes::parse_reward_list(stConfig.stReward, (char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		m_oTaskConfig.insert(std::make_pair(stConfig.unID, stConfig));
		m_oTaskTypeConfig.insert(std::make_pair(stConfig.unActiveEventType, stConfig));
		childNode = childNode->next;
	}
}

void GameConfig::parse_active_mission(xmlNodePtr rootNode)
{
	ACE_UINT32 unTaskID = 0;
	ActivenessInfo stConfig;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		unTaskID = 0;
		memset(&stConfig, 0, sizeof(ActivenessInfo));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"ID") == 0)
			{
				unTaskID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			//else if(xmlStrcasecmp(subNode->name, BAD_CAST"LvLimit") == 0)
			//{
			//	stConfig.unLevelCase = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			//}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"MissionType") == 0)
			{
				sscanf((char *)xmlNodeGetContent(subNode), "%d,%d,%d", &stConfig.unActiveEventType, &stConfig.unAttachID, &stConfig.unCompleteCount);
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"ActiveScore") == 0)
			{
				stConfig.unActivenessPoints = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if (xmlStrcasecmp(subNode->name, BAD_CAST("Reward")) == 0)
			{
				RewardRes::parse_reward_list(stConfig.stReward, (char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		m_oActivenessList.insert(std::make_pair(unTaskID, stConfig));
		childNode = childNode->next;
	}
}

void GameConfig::parse_active_prize(xmlNodePtr rootNode)
{
	ACE_UINT32 unActiveScore = 0;
	ConfigReward stConfig;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		unActiveScore = 0;
		memset(&stConfig, 0, sizeof(ConfigReward));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"ActiveScore") == 0)
			{
				unActiveScore = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"PrizeItem") == 0)
			{
				RewardRes::parse_reward_list(stConfig, (char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		m_oActivenessReward.insert(std::make_pair(unActiveScore, stConfig));
		childNode = childNode->next;
	}
}

void GameConfig::parse_equip_step(xmlNodePtr rootNode)
{
	EquipStepConfig stConfig;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		memset(&stConfig, 0, sizeof(EquipStepConfig));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"equipstep") == 0)
			{
				stConfig.unEquipStep = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"max_level_bonus") == 0)
			{
				stConfig.unMaxLevelBonus = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"attribute_rate") == 0)
			{
				stConfig.fAttributeRate = ACE_OS::atof((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		m_oEquipStepConfig.push_back(stConfig);
		childNode = childNode->next;
	}
}

void GameConfig::parse_robot_player(xmlNodePtr rootNode)
{
	ACE_UINT32 unID = 0;
	PlayerInfo stPlayer;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		unID = 0;
		memset(&stPlayer, 0, sizeof(PlayerInfo));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"CharID") == 0)
			{
				unID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Grade") == 0)
			{
				stPlayer.unStep = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if (xmlStrcasecmp(subNode->name, BAD_CAST"RealCharID") == 0)
			{
				stPlayer.unItemID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"EquipID1") == 0)
			{
				stPlayer.weapon.unResID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				stPlayer.weapon.info.equipment.unStep = 1;
				stPlayer.weapon.info.equipment.unLevel = 1;
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"EquipID2") == 0)
			{
				stPlayer.armor.unResID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				stPlayer.armor.info.equipment.unStep = 1;
				stPlayer.armor.info.equipment.unLevel = 1;
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"EquipID4") == 0)
			{
				stPlayer.belt.unResID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				stPlayer.belt.info.equipment.unStep = 1;
				stPlayer.belt.info.equipment.unLevel = 1;
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"EquipID3") == 0)
			{
				stPlayer.staff.unResID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
				stPlayer.staff.info.equipment.unStep = 1;
				stPlayer.staff.info.equipment.unLevel = 1;
			}
			subNode = subNode->next;
		}
		m_oRobotPlayer.insert(std::make_pair(unID, stPlayer));
		childNode = childNode->next;
	}
}

void GameConfig::parse_robot_team(xmlNodePtr rootNode)
{
	std::map<ACE_UINT32, PlayerInfo>::iterator itMap;
	PublicPlayerInfo *pGamer;
	std::vector<PublicPlayerInfo *> conInfoVec;
	std::vector<ACE_UINT32> conSeedVec;
	std::map<ACE_UINT32, std::pair<std::vector<UINT32>, std::vector<PublicPlayerInfo *> > >::iterator itPairMap;
	xmlNodePtr childNode;

	ACE_Byte byReadFlag = 0;
	ACE_UINT32 unPreLevel = 0, unEquipLevel = 0;
	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		byReadFlag = 0;
		unEquipLevel = 0;
		xmlNodePtr subNode = childNode->children;
		pGamer = new PublicPlayerInfo;
		ZeroVar(*pGamer);
		if (pGamer == NULL)
		{
			return;
		}
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"ID") == 0)
			{
				pGamer->characterInfo.unItemID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Level") == 0)
			{
				pGamer->characterInfo.unLevel = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if (xmlStrcasecmp(subNode->name, BAD_CAST"EquipLevel") == 0)
			{
				unEquipLevel = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"LeaderID") == 0)
			{
				if ((itMap = m_oRobotPlayer.find(ACE_OS::atoi((char *)xmlNodeGetContent(subNode)))) != m_oRobotPlayer.end())
				{
					memcpy(&pGamer->characterInfo.pveTeam.playerList[0], &itMap->second, sizeof(PlayerInfo));
					byReadFlag |= 0x1;
				}
				else
				{
					//Error log
					return;
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Member1ID") == 0)
			{
				if ((itMap = m_oRobotPlayer.find(ACE_OS::atoi((char *)xmlNodeGetContent(subNode)))) != m_oRobotPlayer.end())
				{
					memcpy(&pGamer->characterInfo.pveTeam.playerList[1], &itMap->second, sizeof(PlayerInfo));
					byReadFlag |= 0x1<<1;
				}
				else
				{
					//Error log
					//return;
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Member2ID") == 0)
			{
				if ((itMap = m_oRobotPlayer.find(ACE_OS::atoi((char *)xmlNodeGetContent(subNode)))) != m_oRobotPlayer.end())
				{
					memcpy(&pGamer->characterInfo.pveTeam.playerList[2], &itMap->second, sizeof(PlayerInfo));
					byReadFlag |= 0x1<<2;
				}
				else
				{
					//Error log
					//return;
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Member3ID") == 0)
			{
				if ((itMap = m_oRobotPlayer.find(ACE_OS::atoi((char *)xmlNodeGetContent(subNode)))) != m_oRobotPlayer.end())
				{
					memcpy(&pGamer->characterInfo.pveTeam.playerList[3], &itMap->second, sizeof(PlayerInfo));
					byReadFlag |= 0x1<<3;
				}
				else
				{
					//Error log
					//return;
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Member4ID") == 0)
			{
				if ((itMap = m_oRobotPlayer.find(ACE_OS::atoi((char *)xmlNodeGetContent(subNode)))) != m_oRobotPlayer.end())
				{
					memcpy(&pGamer->characterInfo.pveTeam.playerList[4], &itMap->second, sizeof(PlayerInfo));
					byReadFlag |= 0x1<<4;
				}
				else
				{
					//Error log
					//return;
				}
			}
			else if (xmlStrcasecmp(subNode->name, BAD_CAST"TeamName") == 0)
			{
				ACE_OS::strcpy(pGamer->characterInfo.name, (char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
// 		if (byReadFlag != 0x1F)
// 		{
// 			return;
// 		}
		if (unPreLevel != pGamer->characterInfo.unLevel)
		{
			itPairMap = m_oLevelRobotTeam.find(pGamer->characterInfo.unLevel);
			if (itPairMap == m_oLevelRobotTeam.end())
			{
				conSeedVec.clear();
				conSeedVec.reserve(conInfoVec.size());
				for (int i=0;i<conInfoVec.size();++i)
				{
					conSeedVec.push_back(i);
				}

				m_oLevelRobotTeam.insert(std::make_pair(unPreLevel, std::make_pair(conSeedVec, conInfoVec)));
				conInfoVec.clear();
			}
			else
			{
				int iBegin=itPairMap->second.first.size();
				for (int i=0;i<conInfoVec.size();++i)
				{
					itPairMap->second.first.push_back(iBegin+i);
				}
				itPairMap->second.second.insert(itPairMap->second.second.end(), conInfoVec.begin(), conInfoVec.end());
			}
			unPreLevel = pGamer->characterInfo.unLevel;
		}
		conInfoVec.push_back(pGamer);
		for (int i=0;i<5;++i)
		{
			pGamer->characterInfo.pveTeam.playerList[i].unLevel = pGamer->characterInfo.unLevel;
			PlayerRes *res = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(pGamer->characterInfo.pveTeam.playerList[i].unItemID);

			if(res == NULL)
			{
				return;
			}
			pGamer->characterInfo.pveTeam.playerSkillList[i] = res->m_unSkillID + pGamer->characterInfo.unLevel - 1;
			pGamer->characterInfo.pveTeam.skillList[i] = res->m_unSkillID + pGamer->characterInfo.unLevel - 1;
			pGamer->characterInfo.pveTeam.playerList[i].weapon.info.equipment.unLevel = unEquipLevel;
			pGamer->characterInfo.pveTeam.playerList[i].armor.info.equipment.unLevel = unEquipLevel;
			pGamer->characterInfo.pveTeam.playerList[i].belt.info.equipment.unLevel = unEquipLevel;
			pGamer->characterInfo.pveTeam.playerList[i].staff.info.equipment.unLevel = unEquipLevel;
		}
		m_oRobotTeam.insert(std::make_pair(pGamer->characterInfo.unItemID,pGamer));
		childNode = childNode->next;
	}
	conSeedVec.clear();
	conSeedVec.reserve(conInfoVec.size());
	for (int i=0;i<conInfoVec.size();++i)
	{
		conSeedVec.push_back(i);
	}

	m_oLevelRobotTeam.insert(std::make_pair(pGamer->characterInfo.unLevel, std::make_pair(conSeedVec, conInfoVec)));
}

void GameConfig::Parse_Formula_config(char *str,int n)
{
	int c = 0;
	int offset = 0;
	int len = ACE_OS::strlen(str);
	//char tmp[64];

	FormulaInfo dest;
	Parse_Formula_info(dest, str);
	m_vecFormulaInfo[n] = dest;
}

void GameConfig::Parse_Formula_info( FormulaInfo &dest, char *str )
{
	int offset = 0;
	int len = ACE_OS::strlen(str);
	char tmp[64];

	int unCount = 1;
	for(int i = 0;i < 3;i ++)
	{
		if(offset == -1)
			break;

		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(i == 0)
			dest.paramA = ACE_OS::atof(tmp);
		else if (i == 1)
		{
			dest.paramB = ACE_OS::atof(tmp);
			if (dest.paramB <= 0.000001f && dest.paramB >= -0.000001f)//除数不能为0
				dest.paramB =1.0f;
		}
		else
			dest.paramC = ACE_OS::atof(tmp);
	}
}

void GameConfig::Parse_limited_activity( xmlNodePtr rootNode )
{
	m_olimitedActivityConfig.clear();
	m_olimitedActivityTypeList.clear();
	LimitedActivityConfig laConfig;
	ZeroVar(laConfig);
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		memset(&laConfig, 0, sizeof(LimitedActivityConfig));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"id") == 0)
			{
				laConfig.unID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"start_time") == 0)//开始时间
			{
				laConfig.unStartTime = GameUtils::Get_Detail_from_str((char *)xmlNodeGetContent(subNode));//ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"end_time") == 0)
			{
				laConfig.unEndTime = GameUtils::Get_Detail_from_str((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"week_circle") == 0)
			{
				char * str = (char *)xmlNodeGetContent(subNode);

				int len = strlen(str);
				char tmp[64];
				int offset = 0;
				int idx;
				laConfig.unWeekCircle= 0;
				while(offset != -1)
				{
					offset = GameUtils::value_token(str, offset, len, tmp, ',');
					idx= ACE_OS::atoi(tmp);
					laConfig.unWeekCircle = laConfig.unWeekCircle | (1 << idx);
				}	

			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"last_time") == 0)
			{
				char * str = (char *)xmlNodeGetContent(subNode);

				int len = strlen(str);
				char tmp[64];
				int offset = 0;

				offset = GameUtils::value_token(str, offset, len, tmp, ',');
				laConfig.unDayTimeStart = GameUtils::Get_Time_from_str(tmp);

				offset = GameUtils::value_token(str, offset, len, tmp, ',');
				laConfig.unDayTimeEnd = GameUtils::Get_Time_from_str(tmp);
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"related_id") == 0)		
			{
				char * str = (char *)xmlNodeGetContent(subNode);
				int len = strlen(str);
				char tmp[64];
				int offset = 0;
				//int idx;
				offset = GameUtils::value_token(str, offset, len, tmp, ',');
				laConfig.unRelatedType = ACE_OS::atoi(tmp);

				laConfig.unRelatedCount = 0;
				while(offset != -1)
				{
					offset = GameUtils::value_token(str, offset, len, tmp, ',');
					laConfig.unRelatedItems[laConfig.unRelatedCount] = GameUtils::parse_res_id(tmp);
					laConfig.unRelatedCount ++;
					if (laConfig.unRelatedCount >= MAX_RelatedT_ITEMS)
						break;
				}
			}
			else if (xmlStrcasecmp(subNode->name, BAD_CAST"close_time") == 0)
			{
				laConfig.unCloseTime = GameUtils::Get_Detail_from_str((char *)xmlNodeGetContent(subNode));
			}

			subNode = subNode->next;
		}
		m_olimitedActivityConfig.insert(std::make_pair(laConfig.unID, laConfig));

		if(laConfig.unRelatedType == E_L_A_TYPE::LA_TYPE_9)
		{
			ACE_UINT32 now = GameUtils::get_utc();//获取当前时间
			if (laConfig.unEndTime > now)//限时活动还没有结束
				m_olimitedActivityConfigEx.insert(std::make_pair(laConfig.unID,laConfig));
		}
		//m_olimitedActivityTypeList[laConfig.unRelatedType].push_back(laConfig.unID);
		childNode = childNode->next;
	}
}

void GameConfig::Parse_limited_mission_activity( xmlNodePtr rootNode )
{
	LimitedActivityMissionConfig laConfig;
	ZeroVar(laConfig);
	xmlNodePtr childNode;
	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		memset(&laConfig, 0, sizeof(LimitedActivityConfig));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"Id") == 0)
			{
				laConfig.unID = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"LvLimit") == 0)//解锁等级
			{
				laConfig.unLvLimit = GameUtils::Get_Detail_from_str((char *)xmlNodeGetContent(subNode));//ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"PreMissionID") == 0)
			{
				char * str = (char *)xmlNodeGetContent(subNode);
				int len = strlen(str);
				char tmp[64];
				int offset = 0;
				int idx = 0;
				while(offset != -1 && idx <MAX_PreMission_COUNT)
				{
					offset = GameUtils::value_token(str, offset, len, tmp, ',');
					laConfig.unPreMissionID[idx] = ACE_OS::atoi(tmp);
					idx ++;
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"MissionType") == 0)
			{
				char * str = (char *)xmlNodeGetContent(subNode);

				int len = strlen(str);
				char tmp[64];
				int offset = 0;

				int idx = 0;
				while(offset != -1 && idx <3)
				{
					offset = GameUtils::value_token(str, offset, len, tmp, ',');
					if(idx == 1)
						laConfig.unMissionType[idx] = GameUtils::parse_res_id(tmp);
					else
						laConfig.unMissionType[idx] = ACE_OS::atoi(tmp);
					idx ++;
				}
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"PrizeItem") == 0)		
			{
				RewardRes::parse_reward_list(laConfig.stReward, (char *)xmlNodeGetContent(subNode));
// 				char * str = (char *)xmlNodeGetContent(subNode);
// 
// 				int len = strlen(str),len1=0;
// 				char tmp[64],tmp1[64];
// 				int offset = 0,offset1=0;
// 
// 				int idx = 0;
// 				while(offset != -1 && idx <MAX_MissionPrize_COUNT)
// 				{
// 					offset = GameUtils::value_token(str, offset, len, tmp, ';');
// 
// 					offset1 =0;
// 					len1 = strlen(tmp);
// 					offset1 = GameUtils::value_token(tmp, offset1, len1, tmp1, ',');
// 					laConfig.unPrizeItems[idx].unID = ACE_OS::atoi(tmp1);
// 					offset1 = GameUtils::value_token(tmp, offset1, len1, tmp1, ',');
// 					laConfig.unPrizeItems[idx].unCount = ACE_OS::atoi(tmp1);
// 
// 					idx ++;
// 				}
			}

			subNode = subNode->next;
		}
		m_olimitedActivityMissionConfig.insert(std::make_pair(laConfig.unID, laConfig));
		childNode = childNode->next;
	}
}

void GameConfig::Parse_golden_touch_profit(xmlNodePtr rootNode)
{
	ACE_UINT32 unTeamLv = 0;
	GoldenTouchProfit stConfig;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		unTeamLv = 0;
		memset(&stConfig, 0, sizeof(GoldenTouchProfit));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"teamlevel") == 0)
			{
				unTeamLv = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"baseprofit") == 0)
			{
				stConfig.unBaseProfit = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"countprofit") == 0)
			{
				stConfig.unCountProfit = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		m_oGoldenTouchProfit.insert(std::make_pair(unTeamLv, stConfig));
		childNode = childNode->next;
	}
}

void GameConfig::Parse_golden_touch_cost(xmlNodePtr rootNode)
{
	ACE_UINT32 unCount = 0;
	GoldenTouchCost stConfig;
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		unCount = 0;
		memset(&stConfig, 0, sizeof(GoldenTouchCost));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"touchcount") == 0)
			{
				unCount = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"touchcost") == 0)
			{
				stConfig.unTouchCost = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Critical") == 0)
			{
				stConfig.unCriticalOdds = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}
		m_oGoldenTouchCost.insert(std::make_pair(unCount, stConfig));
		childNode = childNode->next;
	}
}

void GameConfig::Parse_BuyEnergy_cost( xmlNodePtr rootNode )
{
	ACE_UINT32 unCount = 0;
	GoldenTouchCost stConfig;
	xmlNodePtr childNode;

	BuyEnergyCost cost;
	childNode = rootNode->xmlChildrenNode;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;
		unCount = 0;
		memset(&stConfig, 0, sizeof(GoldenTouchCost));
		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"Buy_Count") == 0)
			{
				cost.buy_count = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"cost") == 0)
			{
				cost.cost = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"Energy_Recover") == 0)
			{
				cost.Energy_Recover = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}

		m_oBuyEnergyCost.AddOne(cost);
		childNode = childNode->next;
	}
}

void GameConfig::Parse_channel( xmlNodePtr rootNode )
{
	m_oChannelRes.clear();
	ChannelRes channelRes;
	xmlNodePtr childNode = rootNode->xmlChildrenNode;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;

		ZeroVar(channelRes);

		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"name") == 0)
			{
				ACE_OS::strncpy(channelRes.m_strName, (char *)xmlNodeGetContent(subNode), MAX_ITEM_NAME);
				channelRes.m_strName[MAX_ITEM_NAME] = '\0';
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"channel_id") == 0)
			{
				channelRes.m_channelID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}

		m_oChannelRes[channelRes.m_channelID] = channelRes;
		childNode = childNode->next;
	}
}

void GameConfig::Parse_badgeLevel( xmlNodePtr rootNode )
{
	m_oBadgelevelConfig.clear();
	BadgeLevelInfo badgeLevelinfo;
	xmlNodePtr childNode = rootNode->xmlChildrenNode;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;

		ZeroVar(badgeLevelinfo);

		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"level") == 0)
			{
				badgeLevelinfo.m_level = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"start1_energy") == 0)
			{
				badgeLevelinfo.m_energy[0] = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"start2_energy") == 0)
			{
				badgeLevelinfo.m_energy[1] = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"start3_energy") == 0)
			{
				badgeLevelinfo.m_energy[2] = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"start4_energy") == 0)
			{
				badgeLevelinfo.m_energy[3] = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"start5_energy") == 0)
			{
				badgeLevelinfo.m_energy[4] = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}

			subNode = subNode->next;
		}

		m_oBadgelevelConfig[badgeLevelinfo.m_level] = badgeLevelinfo;
		childNode = childNode->next;
	}
}

void GameConfig::parse_gameconfig_honor_rank( xmlNodePtr rootNode )
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"attack_times") == 0)
		{
			m_oHonorRankConfig.attack_times = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"amount") == 0)
		{
			m_oHonorRankConfig.amount = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"base_honor_point") == 0)
		{
			m_oHonorRankConfig.base_honor_point = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"init_honor") == 0)
		{
			m_oHonorRankConfig.init_honor = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"honor_modulus") == 0)
		{
			m_oHonorRankConfig.honor_modulus = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}
}

void GameConfig::parse_honor_level( xmlNodePtr rootNode )
{
	m_oHonorLevel.clear();
	HonorLevel honorLevelinfo;
	xmlNodePtr childNode = rootNode->xmlChildrenNode;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;

		ZeroVar(honorLevelinfo);

		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"level") == 0)
			{
				honorLevelinfo.unLevel = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"levelup_honor") == 0)
			{
				honorLevelinfo.unlevelupHonor = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"day_reward") == 0)
			{
				honorLevelinfo.undayReward = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			}
// 			else if(xmlStrcasecmp(subNode->name, BAD_CAST"season_reward") == 0)
// 			{
// 				honorLevelinfo.unseasonReward = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
// 			}

			subNode = subNode->next;
		}

		m_oHonorLevel[honorLevelinfo.unLevel] = honorLevelinfo;
		if (honorLevelinfo.unLevel < m_oHLmin)
			m_oHLmin = honorLevelinfo.unLevel;
		if (honorLevelinfo.unLevel > m_oHLmax)
			m_oHLmax = honorLevelinfo.unLevel;
		childNode = childNode->next;
	}
}

void GameConfig::parse_honor_rank( xmlNodePtr rootNode )
{
	m_oHonorRank.clear();
	HonorRank honorRankinfo;
	xmlNodePtr childNode = rootNode->xmlChildrenNode;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;

		ZeroVar(honorRankinfo);

		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"rankid") == 0)
			{
				honorRankinfo.rankid = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"rank_limited") == 0)
			{
				honorRankinfo.unrank_limited = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"season_reward") == 0)
			{
				honorRankinfo.season_reward = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			}
			// 			else if(xmlStrcasecmp(subNode->name, BAD_CAST"season_reward") == 0)
			// 			{
			// 				honorLevelinfo.unseasonReward = GameUtils::parse_res_id((char *)xmlNodeGetContent(subNode));
			// 			}

			subNode = subNode->next;
		}

		m_oHonorRank[honorRankinfo.rankid] = honorRankinfo;
		childNode = childNode->next;
	}
}

void GameConfig::parse_honor_cost( xmlNodePtr rootNode )
{
	m_oHonorCost.clear();
	xmlNodePtr childNode = rootNode->xmlChildrenNode;
	while(childNode != NULL)
	{
		xmlNodePtr subNode = childNode->children;

		ACE_UINT32 buycount=0;
		ACE_UINT32 buycost = 0;

		while(subNode != NULL)
		{
			if (xmlStrcasecmp(subNode->name, BAD_CAST"buycount") == 0)
			{
				buycount = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			else if(xmlStrcasecmp(subNode->name, BAD_CAST"buycost") == 0)
			{
				buycost = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			}
			subNode = subNode->next;
		}

		m_oHonorCost[buycount] = buycost;
		childNode = childNode->next;
	}
}

void GameConfig::parse_gameconfig_button_unlock( xmlNodePtr rootNode )
{
	xmlNodePtr childNode;

	childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"scheme_arena") == 0)//竞技场解锁等级
		{
			m_oSchemeInfo.m_scheme_arena = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"scheme_badge") == 0)//徽章解锁
		{
			m_oSchemeInfo.m_scheme_badge = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}

		childNode = childNode->next;
	}
}
