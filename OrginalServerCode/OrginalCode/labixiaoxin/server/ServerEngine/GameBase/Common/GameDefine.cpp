#include "GameDefine.h"
#include "json/json.h"
#include <string.h>
#include "../res/ChannelRes.h"
#include "../res/ItemResMgr.h"
#include "../res/GameConfig.h"

void tagEquipmentItemInfo::ToJson( Json::Value &root )
{
	root["unLevel"] = unLevel;
	root["unStep"] = unStep;
}

void tagItemDetailInfo::ToJson( Json::Value &root )
{
	equipment.ToJson(root["equipment"]);
}

void tagItemInfo::ToJson( Json::Value &root )
{
	root["unResID"] = unResID;
	info.ToJson(root["info"]);
}

void tagItemInfoExt::ToJson( Json::Value &root )
{
	root["unCount"] = unCount;
	item.ToJson(root["item"]);
}

void tagPackageCell::ToJson( Json::Value &root )
{
	root["unIdx"] = unIdx;
	item.ToJson(root["item"]);
}

void tagPlayerInfo::ToJson( Json::Value &root )
{
	root["ID"] = unItemID;
	root["unLevel"] = unLevel;
	root["unStep"] = unStep;
	if(weapon.unResID != 0)
		weapon.ToJson(root["weapon"]);
	if(armor.unResID != 0)
		armor.ToJson(root["armor"]);
	if (belt.unResID != 0)
		belt.ToJson(root["belt"]);
	if (staff.unResID != 0)
		staff.ToJson(root["staff"]);
	root["unPlayerSkillID"] = unPlayerSkillID;
	root["unSoulCount"] = unSoulCount;
}

void tagAccountBasicInfo::ToJson( Json::Value &root )
{
	root["m_unUserID"] = m_unCharacterID;
	if(strcmp(m_email, "") == 0)
		root["m_AccountName"] = m_mac;
	else
		root["m_AccountName"] = m_email;
	root["m_PlayerName"] = m_PlayerName;
	root["m_unLevel"] = m_unLevel;
	root["m_unExp"] = m_unExp;
	root["m_unCoin"] = m_unCoin;
	root["m_unGold"] = m_unMoney;
	root["m_unLastLoginTime"] = m_unLastLoginTime;
	root["m_unCreateTime"] = m_unCreateTime;//xxj 2015/04/23 11:31:45 创建时间
	root["m_unPoint"] = m_unPoint;//xxj 2015/04/23 17:33:37 战力
	root["m_unPowerPoint"] = m_unPowerPoint;//xxj 2015/04/23 19:28:23 晶石
	root["m_unEnergy"] = m_unEnergy;//xxj 2015/04/23 19:28:32 当前体力
	for (int i=0;i<MAX_SKILL_COUNT;i++)//技能
	{
		m_skillList[i].ToJson(root["m_skillList"][i]);
	}
	//渠道
	int type = GET_ITEM_TYPE(m_unChannel);
	if (type == ITEM_RES_TYPE_CHANNEL)
	{
		ChannelRes pRes = GAME_CONFIG_INSTANCE::instance()->m_oChannelRes[m_unChannel];
		root["m_unChannel"] = pRes.m_strName;
	}
	
	//-------------------
}

void tagAccountItemInfo::ToJson( Json::Value &root )
{
	for(int i = 0; i != m_unItemsCount; i++)
	{
		root["ItemList"].append(Json::Value());
		m_itemsList[i].ToJson(root["ItemList"][i]);
	}
}

void tagAccountPlayerInfo::ToJson( Json::Value &root )
{
	for(int i = 0; i != MAX_PLAYER_SELECTED_COUNT; i++)
	{
		if(m_selectedPlayerList[i] == 0)
			continue;
		root["SelectedPlayerList"].append(m_selectedPlayerList[i]);
	}
	for(int i = 0; i != MAX_PLAYER_COUNT; i++)
	{
		if(m_playerList[i].unItemID == 0)
			continue;
		root["PlayerList"].append(Json::Value());
		m_playerList[i].ToJson(root["PlayerList"][(Json::UInt)i]);
	}
	for(int i = 0; i != MAX_PLAYER_SELECTED_COUNT; i++)
	{
		if(m_selectedPlayerSkillList[i] == 0)
			continue;
		root["SelectedSkillList"].append(m_selectedPlayerSkillList[i]);
	}
}

void tagAccountBriefInfo::ToJson( Json::Value &root )
{
	root["m_unUserID"] = m_unCharacterID;
	if(strcmp(m_email, "") == 0)
		root["m_AccountName"] = m_mac;
	else
		root["m_AccountName"] = m_email;
	root["m_PlayerName"] = m_PlayerName;
}

void tagAccountBriefInfoList::ToJson( Json::Value &root )
{
	for(int i = 0; i != m_AccountCount; i++)
	{
		root["AccountList"].append(Json::Value());
		m_oBriefInfos[i].ToJson(root["AccountList"][(Json::UInt)i]);
	}
}

void tagSkillInfo::ToJson( Json::Value &root )
{
	root["skillID"] = skillID;
	root["skillLevel"] = skillLevel;
	root["m_strName"] = m_strName;
}

void tagPlayerTeamInfo::ToJson( Json::Value &root )
{
	root["unCount"] = unCount;
	root["unPoint"] = unPoint;
	staff.ToJson(root["staff"]);
	for(int i=0;i<MAX_PLAYER_SELECTED_COUNT;i++)
	{
		playerList[i].ToJson(root["playerList"][i]);
		root["skillList"].append(skillList[i]);
		root["playerSkillList"].append(skillList[i]);
	}
}

void tagCharacterInfoExt::ToJson( Json::Value &root )
{
	root["unVipLevel"] = unVipLevel;
	pveTeam.ToJson(root["pveTeam"]);
	//pvpTeam.ToJson(root["pvpTeam"]);
}

void tagMapInstanceInfo::ToJson( Json::Value &root )
{
	root["unMapID"] = unMapID;
	root["unSpecialBossID"] = unSpecialBossID;
	root["unItemCount"] = unItemCount;
	root["nGlobalMapEventType"] = nGlobalMapEventType;
	friendInfo.ToJson(root["friendInfo"]);
}
