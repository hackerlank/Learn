#include "PlayerMgr.h"
#include "..\Map.h"
#include "BroadcastMgr.h"

#include "..\..\GameBase\Logger\LoggerClient.h"
#include <math.h>
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\res\PieceRoleRes.h"
#include "..\..\GameBase\res\ExtraSkillRes.h"
#include "..\..\GameBase\res\EquipmentRes.h"

PlayerMgr::PlayerMgr()
{
	ACE_OS::memset(&m_teamInfo, 0, sizeof(PlayerTeamInfo));
	m_teamProperty.init(&m_teamInfo);
	m_unHighestPoint = 0;
}

PlayerMgr::~PlayerMgr()
{

}


void PlayerMgr::handle_event(BaseEvent *e)
{
	update_pve_team();
}

int PlayerMgr::level_up_equipment(ACE_UINT32 unPlayerID, ACE_UINT32 unEquipmentID, int dwLevelAdd)
{
	int ret = -1;

	ItemInfo *item = NULL;

	/*if(unPlayerID == TANG_MONK_ID)
	{
	item = &m_staff;
	}
	else*/ //屏蔽超人
	{
		item = get_equipment(unPlayerID, unEquipmentID);
	}

	if(item == NULL)
	{
		return ERROR_MSG_OBJ_NULL;
	}

	ret = m_map->level_up_item(LEVEL_UP_TYPE_EQUIPMENT, item, dwLevelAdd);

	if(ret == 0)
	{
		update_2_db();
		//m_map->dispatch_map_event(GAME_EVENT_PVE_TEAM_UPDATE);
		m_map->dispatch_map_event(GAME_EVENT_PLAYER_INFO_UPDATE);
	}

	return ret;
}

int PlayerMgr::level_up_player(ACE_UINT32 unPlayerID, int dwLevelAdd)
{
	PlayerInfo *info = get_player_by_id(unPlayerID);
	if(info == NULL)
	{
		return ERROR_MSG_RES;
	}

	TeamLevel &oTeamLevel = GAME_CONFIG_INSTANCE::instance()->m_teamLevel[m_map->m_unLevel];

	if(info->unLevel + dwLevelAdd > oTeamLevel.player_levelmax)
	{
		return ERROR_MSG_MAX;
	}

	PlayerRes *res = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unPlayerID);

	if(res == NULL)
	{
		return ERROR_MSG_RES;
	}

	//int maxLevel = PlayerRes::get_max_level(res, info->unStep);

	//if(info->unLevel >= maxLevel)
	//{
	//	return -1;
	//}

	//int price = (info->unLevel * 3) * (info->unLevel * 3) + 100;


	//int price = lv * lv * lv * 10 + 50;
	FormulaInfo formula = GAME_CONFIG_INSTANCE::instance()->m_vecFormulaInfo[0];//xxj 2015/04/22  17:11:35 公式
	int price = 0;
	for(int lv = info->unLevel; lv != info->unLevel + dwLevelAdd; lv++)
	{
		//price += 2 * (int)(((float)50) * pow((float)lv, (float)(1 + lv / 56.0)));
		price += (int)formula.paramC + (int)(((float)formula.paramA) * pow((float)lv, (float)(1 + lv / formula.paramB)));
	}

	//编号【7】角色升级折扣，折扣率
	ACE_UINT32 count = 100;
	if (m_map->m_LAMgr.DoLATypeLeveUP(LA_TYPE_7,count))
	{
		price = price*count*0.01;//立即折扣
	}
	//----------------------------------end

	if(m_map->m_unCoin < price)
	{
		return ERROR_MSG_COST;
	}
	//-----------log 日志
	//伙伴升级
	LogItemInfo logInfo;
	logInfo.m_goodsID = unPlayerID;//装备id
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_level_up;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_level_up);//途径(附加信息)
	m_map->SetlogUserInfo(logInfo);
	std::vector<LogItemInfo> logver;
	//log日志文件
	logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_coin_lower;
	logInfo.m_op_before = m_map->m_unCoin;
	logInfo.m_op_after = m_map->m_unCoin - price;
	logver.push_back(logInfo);
	logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_player_up;
	logInfo.m_op_before = info->unLevel;
	logInfo.m_op_after = info->unLevel + dwLevelAdd;
	logver.push_back(logInfo);
	//-------------------------------------------

	m_map->set_basic_info(-price, 0, 0, 0, 0,0,0);
	info->unLevel += dwLevelAdd;

	// 	//---gm 后台
	// 	GMInfo gminfo;
	// 	ZeroVar(gminfo);
	// 	gminfo.unType = ADMIN_OP_GM_STEP_PLAYER;
	// 	gminfo.unGoodID = unPlayerID;
	// 	gminfo.unLevel = info->unLevel;
	// 	m_map->AddGmMsg(gminfo);
	// 	//----------------------------------------------

	LOGGER_CLIENT_INSTANCE::instance()->log("[ID=0x%08x]level up player,ID=0x%08x,step=%d", m_map->m_unID, info->unItemID, info->unLevel);

	update_2_db();

	m_map->dispatch_map_event(GAME_EVENT_PLAYER_INFO_UPDATE);

	m_map->m_taskMgr.RefreshTask(Event_Base_Type_LevelUp, 0);
	m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_LevelUp, 0);

	m_map->m_taskMgr.RefreshTask(Event_Base_Type_ReachSpecificLevel, info->unLevel);
	m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_ReachSpecificLevel, info->unLevel);

	m_map->SendLogInfoItemMSG(logver);//log日志
	return 0;
}

int PlayerMgr::step_up_player(ACE_UINT32 unPlayerID)
{
	PlayerInfo *info = get_player_by_id(unPlayerID);
	if(info == NULL)
	{
		return ERROR_MSG_RES;
	}

	if(info->unStep >= GAME_CONFIG_INSTANCE::instance()->g_maxSetup)
		return ERROR_MSG_MAX;

	RoleStepInfo &t = GAME_CONFIG_INSTANCE::instance()->m_roleStepInfo[info->unStep];
	if (info->unLevel < t.role_lv_require)//阶数依赖于等级
		return ERROR_MSG_LEVEL;

	int cost = t.upgrade_cost;

	if(info->unSoulCount < cost)
	{
		return ERROR_MSG_COST;
	}

	info->unSoulCount -= cost;
	info->unStep ++;

	//---gm 后台
	GMInfo gminfo;
	ZeroVar(gminfo);
	gminfo.unType = ADMIN_OP_GM_STEP_PLAYER;
	gminfo.unGoodID = unPlayerID;
	gminfo.unLevel = info->unStep;
	m_map->AddGmMsg(gminfo);
	//----------------------------------------------

	m_map->m_taskMgr.RefreshTask(Event_Base_Type_ReachSpecificStar, info->unStep);
	m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_ReachSpecificStar, info->unStep);

	LOGGER_CLIENT_INSTANCE::instance()->log("[ID=0x%08x]step up player ID = 0x%08x, step = %d, soulcount = %d", m_map->m_unID, unPlayerID, info->unStep, info->unSoulCount);

	BROADCAST_MGR_INSTANCE::instance()->add_message(m_map->m_strName, BROADCAST_MESSAGE_TYPE_STEP_UP, info->unItemID, info->unStep);

	update_2_db();

	m_map->dispatch_map_event(GAME_EVENT_PLAYER_INFO_UPDATE);

	return 0;
}

ItemInfo *PlayerMgr::get_equipment(ACE_UINT32 unPlayerID, ACE_UINT32 unEquipmentID)
{
	/*if(unPlayerID == TANG_MONK_ID)
	{
	return &m_staff;
	}*/ //屏蔽超人

	PlayerInfo *info = get_player_by_id(unPlayerID);
	if(info == NULL)
	{
		return NULL;
	}

	return get_equipment(info, unEquipmentID);
}

ItemInfo *PlayerMgr::get_equipment(PlayerInfo *info, ACE_UINT32 unEquipmentID)
{
	int equipment_type = GET_ITEM_ID_INFO(unEquipmentID, 5, 1);

	ItemInfo *ret = NULL;
	switch (equipment_type)
	{
	case EQUIPMENT_TYPE_WEAPON:
		{
			ret = &info->weapon;
		}break;
	case EQUIPMENT_TYPE_ARMOR:
		{
			ret = &info->armor;
		}break;
	case EQUIPMENT_TYPE_BELT:
		{
			ret = &info->belt;
		}break;
	case EQUIPMENT_TYPE_STAFF:
		{
			ret = &info->staff;
		}break;
	default:
		break;
	}

	return ret;
}

void PlayerMgr::update_pve_team()
{
	 ACE_UINT32 unPoint = m_teamInfo.unPoint;
	ACE_OS::memset(&m_teamInfo, 0, sizeof(PlayerTeamInfo));
	m_teamInfo.staff = m_staff;
	m_teamInfo.unPoint = unPoint;

	int i;
	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(m_selectedList[i] == 0)
		{
			break;
		}

		PlayerInfo *tmp = get_player_by_id(m_selectedList[i]);

		if(tmp == NULL)
		{
			break;
		}

		PlayerRes *res = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(m_selectedList[i]);
		if(res == NULL)
		{
			break;
		}

		m_teamInfo.playerList[i] = *tmp;
		m_teamInfo.skillList[i] = m_map->m_skillMgr.get_skill_id(res->m_unSkillID);
		//m_teamInfo.playerList[i].unPlayerSkillID = m_playerSkillList[i];
		m_teamInfo.playerList[i].unPlayerSkillID = 0;
		m_teamInfo.playerSkillList[i] = m_playerSkillList[i];
	}


	//update 2 character_tmp_tbl

	m_teamProperty.build_property();

	MsgCharacterInfoUpdateRequest request;
	request.unCharacterID = m_map->m_unID;
	request.unType = 0;	//pve
	request.teamInfo = m_teamInfo;
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_CHARACTER_INFO_UPDATE_REQUEST, (char *)&request, sizeof(MsgCharacterInfoUpdateRequest), m_map->m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);

	m_map->update_snap_info_2_db();

	if(m_teamInfo.unPoint > m_unHighestPoint)
	{
		m_unHighestPoint = m_teamInfo.unPoint;
		highest_team_info_2_db(0);
	}
}


/*
void PlayerMgr::sort(int count, PlayerInfo *list)
{
int i, j;
ACE_UINT32 tmp_min;
int idx;
PlayerInfo tmp;
for(i = 0;i < count;i ++)
{
idx = i;
tmp_min = list[i].unItemID;
for(j = i + 1;j < count;j ++)
{
if(list[j].unItemID < tmp_min)
{
tmp_min = list[j].unItemID;
idx = j;
}
}

if(idx != i)
{
tmp = list[idx];
list[idx] = list[i];
list[i] = tmp;
}
}
}
*/

void PlayerMgr::init(PlayerInfo *list, ACE_UINT32 *selectedList, ItemInfo *staff, ACE_UINT32 *selectPlayerSkillList, ACE_UINT32 unHighestPoint)
{
	ACE_OS::memcpy(m_list, list, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	ACE_OS::memcpy(m_selectedList, selectedList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memcpy(m_playerSkillList, selectPlayerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);

	m_staff = *staff;

	m_unHighestPoint = unHighestPoint;

	m_unPlayerCount = 0;
	ACE_UINT32 realPlayerCount = 0;
	ACE_UINT32 _list[MAX_PLAYER_COUNT];
	ACE_OS::memcpy(_list, _list, sizeof(ACE_UINT32) * MAX_PLAYER_COUNT);


	int i;
	for(i = 0;i < MAX_PLAYER_COUNT;i ++)
	{
		if(m_list[i].unItemID == 0)
		{
			break;
		}

		if (m_list[i].unLevel > 0)
		{
			_list[realPlayerCount] = m_list[i].unItemID;
			realPlayerCount ++;
		}

		m_unPlayerCount ++;
	}

	int max = GAME_CONFIG_INSTANCE::instance()->g_maxSetup;
	for(int i=0;i<m_unPlayerCount;i++)
	{
		if (m_list[i].unStep > max)
		{
			m_list[i].unStep = max;
		}
	}

	m_unMaxSelected= 0;
	for (int i=0;i<MAX_PLAYER_SELECTED_COUNT;i++)
	{
		if (m_selectedList[i]!=0)
		{
			m_unMaxSelected++;
		}
		else
			break;
	}

	if (m_unMaxSelected < MAX_PLAYER_SELECTED_COUNT)
	{
		if (realPlayerCount > m_unMaxSelected)//添加遗漏的到上战列表
		{
			ACE_UINT32 tempID = 0;
			for (int i=0;i<realPlayerCount;i++)
			{
				tempID = _list[i];
				for (int j=0;j<m_unMaxSelected;j++)
				{
					if (_list[i] == m_selectedList[j])//已经上阵
					{
						tempID = 0;
						break;
					}
				}

				if (tempID != 0)
				{
					m_selectedList[m_unMaxSelected] = tempID;
					m_unMaxSelected ++;

					if (m_unMaxSelected >= MAX_PLAYER_SELECTED_COUNT)
					{
						break;
					}
				}
			}

			update_2_db();//从新更新
		}
	}
}

int PlayerMgr::update_player(ACE_UINT32 *list, ACE_UINT32 *playerSkillList)
{
	int i, j;

	int idx;
	ACE_UINT32 tmp_list[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 tmp_skill_list[MAX_PLAYER_SELECTED_COUNT];

	ACE_OS::memset(tmp_list, 0,  sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memset(tmp_skill_list, 0,  sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);

	for(i = 0;i < m_unMaxSelected;i ++)
	{
		for(j = 0;j < i;j ++)
		{
			if(tmp_list[j] == list[i])
			{
				return ERROR_MSG_PARAMETER;
			}
		}

		idx = GameUtils::find_element(m_unPlayerCount, m_list, sizeof(PlayerInfo), list[i]);

		if(idx == -1)
		{
			return ERROR_MSG_RES;
		}

		tmp_list[i] = list[i];
	}

	if(!set_player_skill(tmp_skill_list, playerSkillList))
	{
		return ERROR_MSG_PARAMETER;
	}

	ACE_OS::memcpy(m_selectedList, tmp_list, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memcpy(m_playerSkillList, tmp_skill_list, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	/*
	PlayerInfo tmp_list[MAX_PLAYER_SELECTED_COUNT];

	for(i = 0;i < unCount;i ++)
	{
	tmp_list[i].unItemID = list[i];
	tmp_list[i].unSelected = 1;
	tmp_list[i].unLevel = 1;
	}

	GameUtils::sort(unCount, tmp_list, sizeof(PlayerInfo));

	int c = 0;
	int offset = unCount;

	for(i = 0;i < m_unPlayerCount;i ++)
	{
	if(c < unCount && m_list[i].unItemID == tmp_list[c].unItemID)
	{
	m_list[i].unSelected = 1;
	c ++;
	}
	else
	{
	m_list[i].unSelected = 0;
	}
	}

	if(c != unCount)
	{
	return -1;
	}
	*/


	//ACE_OS::memcpy(m_list, tmp_list, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);

	update_2_db();


	//m_map->dispatch_map_event(GAME_EVENT_LOOT_IGNORE_UPDATE);


	//update 2 db


	return 0;
}

PlayerInfo *PlayerMgr::get_player_by_id(ACE_UINT32 unID)
{
	//int i;

	int idx = GameUtils::find_element(m_unPlayerCount, m_list, sizeof(PlayerInfo), unID);

	if(idx == -1)
	{
		return NULL;
	}

	return &m_list[idx];
}

/*
int PlayerMgr::select_player(int newIdx, int oldIdx)
{
if(newIdx < 0 || newIdx >= m_unPlayerCount || oldIdx < 0 || oldIdx >= m_unPlayerCount)
{
return -1;
}

if(newIdx == oldIdx)
{
return -1;
}

if(m_list[newIdx].unSelected == 1 || m_list[oldIdx].unSelected == 0)
{
return -1;
}

m_list[newIdx].unSelected = 1;
m_list[oldIdx].unSelected = 0;

return 0;
}
*/

void PlayerMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgPlayerInfoResponse response;
	response.nResult = 0;
	response.unSN = unSN;

	response.staff = m_staff;
	response.unCount = m_unPlayerCount;
	//response.unMaxSelected = this->m_unMaxSelected;
	ACE_OS::memcpy(response.selectedList, m_selectedList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memcpy(response.playerList, m_list, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	ACE_OS::memcpy(response.playerSkillList, m_playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);

	response.unHighestPoint = m_unHighestPoint;

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PLAYER_INFO_RESPONSE, (char *)&response, sizeof(MsgPlayerInfoResponse), targetAdr);
}

void PlayerMgr::update_2_db()
{
	MsgDBUpdatePlayerListRequest db_request;
	//db_request.unCount = m_unPlayerCount;
	//db_request.unMaxSelected = m_unMaxSelected;
	db_request.staff = m_staff;
	ACE_OS::memcpy(db_request.selectedList, m_selectedList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memcpy(db_request.playerList, m_list, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	ACE_OS::memcpy(db_request.playerSkillList, m_playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_PLAYER_LIST, (char *)&db_request, sizeof(MsgDBUpdatePlayerListRequest));

	m_map->dispatch_map_event(GAME_EVENT_PVE_TEAM_UPDATE);
}

void PlayerMgr::highest_team_info_2_db(ACE_UINT32 unType)
{
	/*
	#define MSG_DB_UPDATE_HIGHEST_TEAM_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0033)

	typedef struct tagMsgDBUpdateHighestTeamInfoRequest
	{
	PlayerTeamInfo info;
	}MsgDBUpdateHighestTeamInfoRequest;
	*/
	MsgDBUpdateHighestTeamInfoRequest db_request;
	db_request.info = m_teamInfo;
	db_request.unType = unType;

	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_HIGHEST_TEAM_INFO, (char *)&db_request, sizeof(MsgDBUpdateHighestTeamInfoRequest));
}

int PlayerMgr::exchange_equipment(ACE_UINT32 unPlayerID, int packageIdx)
{
	PackageCell *cell = m_map->m_packageMgr.get_cell(packageIdx);

	if(cell == NULL)
	{
		return ERROR_MSG_OBJ_NULL;
	}

	int equipment_type = GET_ITEM_ID_INFO(cell->item.item.unResID, 5, 1);
	ItemInfo oldItem;

	ItemInfo *pItem = NULL;
	if (equipment_type > EQUIPMENT_TYPE_MAX || equipment_type < EQUIPMENT_TYPE_WEAPON)
		return -4;

	//if(equipment_type == EQUIPMENT_TYPE_STAFF)
	//{
	//	//oldInfo = m_staff;
	//	//m_staff = cell->item.item;
	//	pItem = &m_staff;
	//}
	//else
	//{
	PlayerInfo *player = this->get_player_by_id(unPlayerID);
	if(player == NULL)
	{
		return ERROR_MSG_OBJ_NULL;
	}

	EquipmentRes * res = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(cell->item.item.unResID);
	if (!res)
		return ERROR_MSG_RES;
	if (res->m_level_require > player->unLevel)//穿装备，关联角色等级
		return ERROR_MSG_LEVEL;

	switch (equipment_type)
	{
	case EQUIPMENT_TYPE_WEAPON:
		{
			PlayerRes *playerRes = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(player->unItemID);

			if(playerRes != NULL)
			{
				ACE_UINT32 unTmpID = playerRes->get_init_equipment(equipment_type);		

				if(unTmpID != 0)
				{
					if(GET_ITEM_ID_INFO(unTmpID, 3, 1) == GET_ITEM_ID_INFO(cell->item.item.unResID, 3, 1))
					{
						pItem = &player->weapon;	
					}
				}
			}
		}break;
	case EQUIPMENT_TYPE_ARMOR:
		{
			pItem = &player->armor;
		}break;
	case EQUIPMENT_TYPE_BELT:
		{
			pItem = &player->belt;
		}break;
	case EQUIPMENT_TYPE_STAFF:
		{
			pItem = &player->staff;
		}break;
	default:
		{

		}break;
	}
	//}
	if(pItem == NULL)
	{
		return ERROR_MSG_PARAMETER;
	}

	oldItem = *pItem;
	*pItem = cell->item.item;


	if(oldItem.unResID == 0)
	{
		PackageCell tmp_cell;
		m_map->m_packageMgr.delete_item(packageIdx, tmp_cell);
	}
	else
	{
		cell->item.item = oldItem;
		//cell->unIdx = packageIdx;
		m_map->m_packageMgr.update_cell(packageIdx);
	}

	LOGGER_CLIENT_INSTANCE::instance()->log("[ID=0x%08x]select equipment packageIdx = %d, itemID = 0x%08x, oldItemID = 0x%08x", m_map->m_unID, packageIdx, pItem->unResID, oldItem.unResID);

	update_2_db();

	m_map->dispatch_map_event(GAME_EVENT_PLAYER_INFO_UPDATE);

	return 0;
}

int PlayerMgr::exchange_equipment( ACE_UINT32 unPlayerID1, ACE_UINT32 unPlayerID2, int equipment_type )
{
	ItemInfo *pItem1 = NULL;
	ItemInfo *pItem2 = NULL;

	PlayerInfo *player1 = this->get_player_by_id(unPlayerID1);
	if(player1 == NULL)
	{
		return -1;
	}

	PlayerInfo *player2 = this->get_player_by_id(unPlayerID2);
	if(player2 == NULL)
	{
		return -1;
	}

	switch (equipment_type)
	{
	case EQUIPMENT_TYPE_WEAPON:
		{
			PlayerRes *playerRes1 = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(player1->unItemID);
			ACE_UINT32 unTmpID1;
			if(playerRes1 != NULL)
			{
				unTmpID1 = playerRes1->get_init_equipment(EQUIPMENT_TYPE_WEAPON);
			}

			PlayerRes *playerRes2 = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(player2->unItemID);
			ACE_UINT32 unTmpID2;
			if(playerRes2 != NULL)
			{
				unTmpID2 = playerRes2->get_init_equipment(EQUIPMENT_TYPE_WEAPON);
			}

			if(unTmpID1 != 0 && unTmpID2 != 0)
			{
				if(GET_ITEM_ID_INFO(unTmpID1, 3, 1) == GET_ITEM_ID_INFO(unTmpID2, 3, 1))
				{
					pItem1 = &player1->weapon;
					pItem2 = &player2->weapon;
				}
			}
		}break;
	case EQUIPMENT_TYPE_ARMOR:
		{
			pItem1 = &player1->armor;
			pItem2 = &player2->armor;
		}break;
	case EQUIPMENT_TYPE_BELT:
		{
			pItem1 = &player1->belt;
			pItem2 = &player2->belt;
		}break;
	case EQUIPMENT_TYPE_STAFF:
		{
			pItem1 = &player1->staff;
			pItem2 = &player2->staff;
		}break;
	default:
		break;
	}

	if(pItem1 == NULL || pItem2 == NULL)
	{
		return -1;
	}

	ItemInfo oldItem = *pItem1;
	*pItem1 = *pItem2;
	*pItem2 = oldItem;

	update_2_db();

	m_map->dispatch_map_event(GAME_EVENT_PLAYER_INFO_UPDATE);

	return 0;
}

/*
int PlayerMgr::exchange_player_skill(ACE_UINT32 unIndex, ACE_UINT32 unSkillID)
{

if(!m_map->m_skillMgr.has_player_skill(unSkillID))
{
return -1;
}

if(!can_player_skill_equip(m_playerSkillList, unIndex, unSkillID))
{
return -1;
}

m_playerSkillList[unIndex] = unSkillID;

update_2_db();

return 0;
}
*/

/*
bool PlayerMgr::can_player_skill_equip(ACE_UINT32 *list, int idx, ACE_UINT32 unNewID)
{
int i;

if(idx < 0 || idx >= MAX_PLAYER_SELECTED_COUNT)
{
return false;
}

ExtraSkillRes *res = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unNewID);
if(res == NULL)
{
return false;
}

ExtraSkillRes *tmp_res;

int c = 0;

for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
{
if(idx == i)
{
continue;
}

if(list[i] == unNewID)
{
return false;
}

tmp_res = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);

if(tmp_res == NULL)
{
return false;
}

if(tmp_res->m_unSkillType == res->m_unSkillType)
{
c ++;
}
//if(m_playerSkillList[i]->)
}

if(c > 1)
{
return false;
}
return true;
}
*/

bool PlayerMgr::set_player_skill(ACE_UINT32 *dest, ACE_UINT32 *list)
{
	int i, j;
	//int idx;

	int nRet = 0;

	ACE_OS::memset(dest, 0, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		ExtraSkillRes *skill_res_0 = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);

		if(m_map->m_skillMgr.has_player_skill(list[i]) && skill_res_0 != NULL)
		{
			ExtraSkillRes *skill_res_1;
			int c = 0;

			for(j = 0;j < i;j ++)
			{
				if(dest[j] == list[i])
				{
					break;
				}

				skill_res_1 = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(dest[j]);

				if(skill_res_1 != NULL && skill_res_1->m_unSkillType == skill_res_0->m_unSkillType)
				{
					c ++;
				}
			}

			if(j < i || c > 1)
			{
				return false;
			}

			dest[i] = list[i];
		}
		else
		{
			dest[i] = 0;
		}
	}

	return true;
}

int PlayerMgr::add_player(ACE_UINT32 unItemID, ACE_UINT32 unNum,LogItemInfo & logInfo)
{
	PlayerRes *playerRes = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unItemID);
	if(playerRes == NULL)
	{
		return -1;
	}

	int idx = GameUtils::find_element(m_unPlayerCount, m_list, sizeof(PlayerInfo), playerRes->m_unRealID);

	if(idx != -1)//已经有这个元素了（可能是碎片，或者真人）
	{
		if (m_list[idx].unStep == 0 && playerRes->m_dwGrade > 0) //原来是碎片，现在出真人
		{
			PlayerRes *temp = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res( playerRes->m_unRealID);
			if(temp == NULL)
			{
				return -1;
			}
			PlayerInfo *info = &m_list[idx];
			info->unStep = playerRes->m_dwGrade;

			if (add_really_player(temp, info) < 0)
			{
				return -1;
			}

			//-----log日志
			//真人
			logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_player_add;
			logInfo.m_goodsID = unItemID;
			logInfo.m_op_after = unNum;
			//---------------------------------
		}
		else
		{
			m_list[idx].unSoulCount += unNum * playerRes->m_dwChangeNum;//加入碎片
			//-----log日志
			//碎片
			logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_player_chip_add;
			logInfo.m_goodsID = unItemID;
			logInfo.m_op_after = unNum;
			//---------------------------------
		}
	}
	else
	{
		PlayerRes *temp = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res( playerRes->m_unRealID);
		if(temp == NULL)
		{
			return -1;
		}
		int idx = GameUtils::add_element(m_unPlayerCount, m_list, MAX_PLAYER_COUNT, sizeof(PlayerInfo),  playerRes->m_unRealID);

		if(idx == -1)
		{
			return -1;
		}

		PlayerInfo *info = &m_list[idx];
		info->unStep = playerRes->m_dwGrade;
		if (playerRes->m_dwGrade > 0)
		{
			if (add_really_player(temp, info) < 0)
			{
				return -1;
			}
			//-----log日志
			//真人
			logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_player_add;
			logInfo.m_goodsID = unItemID;
			logInfo.m_op_after = unNum;
			//---------------------------------
		}
		else
		{
			info->unSoulCount += unNum * playerRes->m_dwChangeNum;//加入碎片 真人个数*每个真人多少碎片
			//-----log日志
			//碎片
			logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_player_chip_add;
			logInfo.m_goodsID = unItemID;
			logInfo.m_op_after = unNum;
			//---------------------------------
		}
	}

	update_2_db();

	BROADCAST_MGR_INSTANCE::instance()->add_message(m_map->m_strName, BROADCAST_MESSAGE_TYPE_GET_PLAYER, unItemID, 0);

	return 0;
}

//初始化真人信息
int PlayerMgr::add_really_player(PlayerRes *temp,PlayerInfo *info)
{
	info->unLevel = 1;

	info->weapon.unResID = temp->get_init_equipment(EQUIPMENT_TYPE_WEAPON);
	if(info->weapon.unResID != 0)
	{
		info->weapon.info.equipment.unLevel = 1;
		info->weapon.info.equipment.unStep = 1;
		m_map->m_badgeMgr.TryAddBadge(info->weapon.unResID);
	}

	info->armor.unResID = temp->get_init_equipment(EQUIPMENT_TYPE_ARMOR);
	if(info->armor.unResID != 0)
	{
		info->armor.info.equipment.unLevel = 1;
		info->armor.info.equipment.unStep = 1;
		m_map->m_badgeMgr.TryAddBadge(info->armor.unResID);
	}

	info->belt.unResID = temp->get_init_equipment(EQUIPMENT_TYPE_BELT);
	if (info->belt.unResID != 0)
	{
		info->belt.info.equipment.unLevel = 1;
		info->belt.info.equipment.unStep = 1;
		m_map->m_badgeMgr.TryAddBadge(info->belt.unResID);
	}

	info->staff.unResID = temp->get_init_equipment(EQUIPMENT_TYPE_STAFF);
	if (info->staff.unResID != 0)
	{
		info->staff.info.equipment.unLevel = 1;
		info->staff.info.equipment.unStep = 1;
		m_map->m_badgeMgr.TryAddBadge(info->staff.unResID);
	}

	if(m_unMaxSelected < MAX_PLAYER_SELECTED_COUNT)
	{
		//info->unSelected = 1;
		m_selectedList[m_unMaxSelected] = temp->m_unRealID;
		m_unMaxSelected ++;
		//m_map->dispatch_map_event(GAME_EVENT_PVE_TEAM_UPDATE);
		//m_map->dispatch_map_event(GAME_EVENT_LOOT_IGNORE_UPDATE);
	}
	return 0;
}

int PlayerMgr::get_selected_list(PlayerInfo *list)
{
	//int c = 0;
	PlayerInfo *info;
	for(int i = 0;i < m_unMaxSelected;i ++)
	{
		info = get_player_by_id(m_selectedList[i]);

		if(info == NULL)
		{
			return 0;
		}
		list[i] = *info;
		/*
		if(m_list[i].unSelected == 1)
		{
		list[c] = m_list[i];
		c ++;
		}
		*/
	}

	return m_unMaxSelected;
}

int PlayerMgr::PieceToPlayer( ACE_UINT32 unItemID,/*CostInfoList & cost,*/ACE_UINT32 & playerID)
{
	PieceRoleRes * piceRes = (PieceRoleRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unItemID);
	if (piceRes == NULL)
	{
		return ERROR_MSG_RES;
	}

	playerID = piceRes->m_character_id;
	PlayerRes *playerRes = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(piceRes->m_character_id);
	if(playerRes == NULL)
	{
		return ERROR_MSG_RES;
	}
	CostInfoList cost = piceRes->m_cost;


	int idx = GameUtils::find_element(m_unPlayerCount, m_list, sizeof(PlayerInfo), playerRes->m_unRealID);
	if (idx < 0)
	{
		return ERROR_MSG_PARAMETER;
	}

	PlayerInfo *info = &m_list[idx];
	if(info == NULL)
	{
		return ERROR_MSG_PARAMETER;
	}

	if(info->unSoulCount < piceRes->m_use_amount)
	{
		return ERROR_MSG_COST;
	}

	//减掉碎片
	info->unSoulCount -=  piceRes->m_use_amount;

	if(!m_map->is_cost_enough(cost, 1))//是否足够扣
	{
		return ERROR_MSG_COST;
	}

	if(idx != -1)//已经有这个元素了（可能是碎片，或者真人）
	{
		if (m_list[idx].unStep == 0 && playerRes->m_dwGrade > 0) //原来是碎片，现在出真人
		{
			PlayerRes *temp = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res( playerRes->m_unRealID);
			if(temp == NULL)
			{
				return ERROR_MSG_RES;
			}
			PlayerInfo *info = &m_list[idx];
			info->unStep = playerRes->m_dwGrade;

			if (add_really_player(temp, info) < 0)
			{
				return -1;
			}
		}
		else
		{
			return ERROR_MSG_PARAMETER;
		}
	}
	else
	{
		PlayerRes *temp = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res( playerRes->m_unRealID);
		if(temp == NULL)
		{
			return ERROR_MSG_RES;
		}

		int idx = GameUtils::add_element(m_unPlayerCount, m_list, MAX_PLAYER_COUNT, sizeof(PlayerInfo),  playerRes->m_unRealID);
		if(idx == -1)
		{
			return ERROR_MSG_PARAMETER;
		}

		PlayerInfo *info = &m_list[idx];
		info->unStep = playerRes->m_dwGrade;
		if (playerRes->m_dwGrade > 0)
		{
			if (add_really_player(temp, info) < 0)
			{
				return -1;
			}
		}
		else
		{
			return ERROR_MSG_PARAMETER;
		}
	}

	LogItemInfo logInfo;
	//-----log日志
	//真人
	m_map->SetlogUserInfo(logInfo);
	logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_player_add;
	logInfo.m_goodsID = unItemID;
	logInfo.m_op_after = 1;
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_piece_role;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_piece_role);
	//---------------------------------
	std::vector<LogItemInfo> logver;
	logver.push_back(logInfo);
	m_map->SendLogInfoItemMSG(logver);//log日志
	logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_DEFALT;
	logInfo.m_goodsID = unItemID;
	logInfo.m_op_after = 0;
	m_map->do_cost(cost, 1,logInfo);//消耗

	update_2_db();
	//BROADCAST_MGR_INSTANCE::instance()->add_message(m_map->m_strName, BROADCAST_MESSAGE_TYPE_GET_PLAYER, unItemID, 0);

	return 0;
}

//int PlayerMgr::levelup_extra_skill( ACE_UINT32 unExtralSkillID )
//{
//	ExtraSkillRes *skill_res_0 = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unExtralSkillID);
//
//	if(skill_res_0 == NULL)
//		return -1;
//
//	ExtraSkillRes *skill_res_1 = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unExtralSkillID + 1);
//
//	if(skill_res_1 == NULL)
//		return -1;
//
//	for(int i = 0; i < MAX_PLAYER_SELECTED_COUNT; i++)
//	{
//		if(m_playerSkillList[i] == 0)
//			return -1;
//		if(m_playerSkillList[i] == unExtralSkillID)
//		{
//			m_playerSkillList[i] = unExtralSkillID + 1;
//			break;
//		}
//	}
//
//	update_2_db();
//	return 0;
//}
