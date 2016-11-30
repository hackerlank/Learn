#include "DBHomeHandler.h"
#include "DBUserHandler.h"
#include "..\Base\Service\BaseAdapter.h"
#include "..\GameBase\Common\GameUtils.h"
#include "DBHomeMgr.h"
#include "DBService.h"
#include "..\GameBase\res\GameConfig.h"
#include "..\GameBase\res\RechargeRes.h"
#include "..\GameBase\res\ItemResMgr.h"

DBHomeHandler::DBHomeHandler(ACE_UINT32 unID, BaseAdapter *parent)
:DBHandler(unID, parent)
{
	ACE_OS::strcpy(m_strHandlerName, "home handler");

	m_bValidID = false;
	//m_unLockResCount = 0;
	m_unItemsCount = 0;
	m_unCurrentBuyEnergy = 0;
	memset(m_taskList, 0, sizeof(TaskInfo) * MAX_TOTAL_TASK_COUNT);
	ZeroVar(m_deleteFriendList);
	ACE_OS::memset(m_mapFlagList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	m_unDynamicEnergy = 0;
	ACE_OS::memset(&m_pvpOpponent, 0, sizeof(CharacterInfoExt));
	ACE_OS::memset(&m_pvpBasicInfo, 0, sizeof(PVPBasicInfo));
	ACE_OS::memset(&m_pvpRankInfo, 0, sizeof(DBPVPRankInfo));
	ZeroVar(m_itemsList);
	m_unPower = 0;
// 	m_unPVPEnergy = 0;
// 	m_unPVPEnergyRestoreTime = 0;
}

void DBHomeHandler::do_db_load(Connection *db_conn)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	m_bLoadingSuccess = true;
	m_bValidID = false;

	if(load_basic_info(db_conn) == -1)
	{
		return;
	}

	if(load_items_list(db_conn) == -1)
	{
		return;
	}

	if(load_map_list(db_conn) == -1)
	{
		return;
	}

	if(load_skill_list(db_conn) == -1)
	{
		return;
	}
	/*
	if(load_weapon_skill_list(db_conn) == -1)
	{
		return;
	}
	*/

	if(load_friend_list(db_conn) == -1)
	{
		return;
	}

	if(load_function_list(db_conn) == -1)
	{
		return;
	}

	if(load_gift_list(db_conn) == -1)
	{
		return;
	}

	if(load_player_list(db_conn) == -1)
	{
		return;
	}

	if(load_cooldown_list(db_conn) == -1)
	{
		return;
	}

	if(load_handbook_list(db_conn) == -1)
	{
		return;
	}

	if(load_materail_list(db_conn) == -1)
	{
		return;
	}

	if(load_props_list(db_conn) == -1)
	{
		return;
	}

	if(load_pvp_info(db_conn) == -1)
	{
		return;
	}

	if(load_money_tree_info(db_conn) == -1)
	{
		return;
	}
	if(load_secret_list(db_conn) == -1)
	{
		return;
	}
	if (load_wing_list(db_conn) == -1)
	{
		return;
	}
	if (load_task_list(db_conn) == -1)
	{
		return;
	}
	if (load_obtained_activeness_reward(db_conn) == -1)
	{
		return;
	}
	if (load_task_progress(db_conn) == -1)
	{
		return;
	}
	if (load_limited_activity_progress(db_conn) == -1)
	{
		return;
	}
	if(Load_ProductList(db_conn) == -1)
	{
		return;
	}
	if(Load_monthCardTime(db_conn) == -1)
	{
		return;
	}
	if(Load_Badge(db_conn) == -1)
	{
		return;
	}
	

	m_bValidID = true;
}

void DBHomeHandler::do_db_request(Connection *db_conn, MessageInfo &msgInfo)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	/*
	MessageInfo msgInfo;

	//printf("%s deal db request\n", m_strHandlerName);

	if(parseMsg(msgInfo, this->m_msg) == -1)
	{
		return;
	}
	*/

	//printf("%s deal db request\n", m_strHandlerName);

	if(!m_bValidID)
	{
		/*
		MsgDBLoadFailedResponse response;

		response.nResult = 0;
		response.unCode = 0;

		this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_LOAD_FAILED,(char*)&response, sizeof(MsgDBLoadFailedResponse), msgInfo.s_head->srcAdr, 0, false);
		*/
		return;
	}

	switch(msgInfo.m_head->unType)
	{
	case MSG_DB_UPDATE_DATABASE:
		{
			MsgDBUpdateDatabase *body = (MsgDBUpdateDatabase *)msgInfo.body;
			//DBUserHandler::init_cooldown_list();

			//insert_cooldown_list(db_conn, initCooldownList);
			insert_new_table(db_conn);
		}
		break;
	case MSG_DB_LOAD_CHARACTER_INFO:
		{
			//do_db_load(db_conn);//add by guo
			send_basic_info(msgInfo.s_head->srcAdr);
			send_items_list(msgInfo.s_head->srcAdr);
			send_player_list(msgInfo.s_head->srcAdr);
			//send_equipment_list(msgInfo.s_head->srcAdr);
			send_map_list(msgInfo.s_head->srcAdr);
			send_skill_list(msgInfo.s_head->srcAdr);
			//send_weapon_skill_list(msgInfo.s_head->srcAdr);
			send_function_list(msgInfo.s_head->srcAdr);
			send_gift_list(msgInfo.s_head->srcAdr);
			send_cooldown_list(msgInfo.s_head->srcAdr);
			send_handbook_list(msgInfo.s_head->srcAdr);
			send_material_list(msgInfo.s_head->srcAdr);
			send_props_list(msgInfo.s_head->srcAdr);
			send_pvp_info(msgInfo.s_head->srcAdr);
			send_money_tree_info(msgInfo.s_head->srcAdr);
			send_friend_list(msgInfo.s_head->srcAdr);
 			send_secret_list(msgInfo.s_head->srcAdr);
 			send_wing_list(msgInfo.s_head->srcAdr);
			send_gift_bag_code(msgInfo.s_head->srcAdr);
			send_double_drop(msgInfo.s_head->srcAdr);
			send_task_list(msgInfo.s_head->srcAdr);
			send_task_progress(msgInfo.s_head->srcAdr);
			send_obtained_activeness_reward(msgInfo.s_head->srcAdr);
			send_limited_activity_progress(msgInfo.s_head->srcAdr);//发送活动任务列表
			send_badge_progress(msgInfo.s_head->srcAdr);
		}
		break;
	case MSG_ADMIN_OP_REQUEST:
		{
			deal_admin_op(db_conn, (MsgAdminOPRequest *)msgInfo.body, msgInfo.s_head->srcAdr);
		}
		break;
	case MSG_ADMIN_OP_RECHARGE_REQUEST:
		{
			Deal_recharge_op_result(db_conn,(OrderInfo *)msgInfo.body);
		}break;
	case MSG_ADMIN_OP_BUFFER_REQUEST:
		{
			deal_admin_buffer_op((MsgAdminOPBufferRequest *)msgInfo.body, msgInfo.s_head->srcAdr);
		}break;
	case MSG_DB_UPDATE_BASIC_INFO:
		{
			update_basic_info(db_conn, (MsgDBUpdateBasicInfoRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_CHARACTER_FLAG:
		{
			update_character_flag(db_conn, (MsgDBUpdateCharacterFlagRequest*)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_CURRENT_MAP:
		{
			update_current_map(db_conn, (MsgDBUpdateCurrentMapRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_MAP_FLAG_LIST:
		{
			update_map_flag_list(db_conn, (MsgDBUpdateMapFlagListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_DOUBLE_DROP_INFO:
		{
			update_double_drop(db_conn, (MsgDBUpdateDoubleDropInfoRequest *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_TASK_LIST:
		{
			update_task_list(db_conn, (MsgDBUpdateTaskInfoRequest *)msgInfo.body);
		}break;
	case MSG_DB_INSERT_TASK_LIST:
		{
			insert_task_list(db_conn, (MsgDBUpdateTaskInfoRequest *)msgInfo.body);
		}break;
	case MSG_DB_DELETE_TASK:
		{
			delete_task(db_conn, (MsgDBDeleteTaskInfoRequest *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_TASK_PROGRESS_REQUEST:
		{
			update_task_progress(db_conn, (MsgDBTaskList *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_GOLDEN_TOUCH_REQUEST:
		{
			update_golden_touch(db_conn, (MsgDBUpdateGoldenTouchRequest *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_BUY_ENERGY_REQUEST://买体力
		{
			update_Buy_energy(db_conn, (MsgDBUpdateBuyEnergyRequest *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_LA_PROGRESS_RESPONSE://限时活动
		{
			update_LA_progress(db_conn,(MsgDBLimitedActivityList *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_LA_PROGRESS_RESPONSE1://限时活动更新一条数据
		{
			update_LA_progress(db_conn,(LimitedActivityInfo *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_BADGE_PROGRESS_RESPONSE1://徽章
		{
			update_Badge_progress(db_conn,(BadgeInfo *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_CHANGED_DATE:
		{
			update_changed_date(db_conn, (MsgDBUpdateChangedDate *)msgInfo.body);
		}break;
	case MSG_DB_INSERT_OBTAINED_ACTIVENESS_REWARD:
		{
			insert_obtained_activeness_reward(db_conn, (MsgDBInsertObtainedActivenessRewardRequest *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_PLAYER_LIST:
		{
// 			for (int i=0;i<100000;i++)
// 			{
// 				m_unID = i;
				update_player_list(db_conn, (MsgDBUpdatePlayerListRequest *)msgInfo.body);
//			}
			
		}
		break;
		/*
	case MSG_DB_UPDATE_EQUIPMENT_LIST:
		{
			update_equipment_list(db_conn, (MsgDBUpdateEquipmentListRequest *)msgInfo.body);
		}
		break;
		*/
	case MSG_DB_UPDATE_PACKAGE_CELL:
		{
			update_package_cell(db_conn, (MsgDBUpdatePackageCellRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_ADD_PACKAGE_CELL:
		{
			add_package_cell(db_conn, (MsgDBAddPackageCellRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_ENERGY:
		{
			update_energy_info(db_conn, (MsgDBUpdateEnergyRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_SKILL_LIST:
		{
			update_skill_list(db_conn, (MsgDBUpdateSkillListRequest *)msgInfo.body);
		}
		break;
	/*
	case MSG_DB_UPDATE_WEAPON_SKILL_LIST:
		{
			update_weapon_skill_list(db_conn, (MsgDBUpdateWeaponSkillListRequest *)msgInfo.body);
		}
		break;
		*/
	case MSG_DB_UPDATE_FRIEND_LIST:
		{
			update_friend_list(db_conn, (MsgDBUpdateFriendListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_DELERE_FRIEND_LIST:
		{
			update_friend_delete_list(db_conn, (DeleteFriendList *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_INVITE_LIST:
		{
			update_invite_list(db_conn, (MsgDBUpdateInviteListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_ASSIST_LIST:
		{
			update_assist_list(db_conn, (MsgDBUpdateAssistListRequest *)msgInfo.body);
		}break;
		/*
	case MSG_DB_PROPERTY_UPDATE:
		{
			update_property_list(db_conn, (MsgDBPropertyUpdateRequest *)msgInfo.body);
		}
		break;
		*/
	case MSG_DB_VIP_LEVEL_UPDATE:
		{
			update_vip_level(db_conn, (MsgDBVipLevelUpdateRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_DELETE_LAST_ITEM:
		{
			delete_last_item(db_conn, (MsgDBDeleteLastItemRequest *)msgInfo.body);
		}
		break;
	case MSG_UPDATE_NAME:
		{
			update_name(db_conn, (MsgDBUpdateNameRequest *)msgInfo.body, msgInfo.s_head->srcAdr);
		}
		break;
	case MSG_DB_UPDATE_LOGIN_INFO:
		{
			update_login_info(db_conn, (MsgDBUpdateLoginInfoRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_FUNCTION_LIST:
		{
			update_function_list(db_conn, (MsgDBUpdateFunctionListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_RECHARGE_INFO:
		{
			update_recharge_info(db_conn, (MsgDBUpdateRechargeInfoRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_VIP_GIFT_INFO:
		{
			update_Vip_Gift_info(db_conn, ( MsgDBVipGiftInfo *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_PACKAGE_MAX:
		{
			update_package_max(db_conn, (MsgDBUpdatePackageMaxRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_REBORN_INFO:
		{
			update_reborn_info(db_conn, (MsgDBUpdateRebornInfoRequest *)msgInfo.body);
		}
		break;
		/*
	case MSG_DB_UPDATE_BATTLE_INFO:
		{
			update_battle_info(db_conn, (MsgDBUpdateBattleInfoRequest *)msgInfo.body);
		}
		break;
		*/
	case MSG_UPDATE_GIFT_LIST:
		{
			update_gift_list(db_conn, (MsgDBUpdateGiftListRequest *)msgInfo.body);
		}
		break;
	case MSG_UPDATE_TUTORIAL_FLAG:
		{
			update_tutorial_flag(db_conn, (MsgDBUpdateTutorialFlagRequest *)msgInfo.body);
		}
		break;
	case MSG_UPDATE_USE_LUCK_COUNT:
		{
			update_use_luck_count(db_conn, (MsgDBUpdateUseLuckCountRequest *)msgInfo.body);
		}
		break;
		/*
	case MSG_UPDATE_IMPROVE_PROPERTY:
		{
			update_improve_property(db_conn, (MsgDBUpdateImprovePropertyRequest *)msgInfo.body);
		}
		break;
		*/
	case MSG_DB_UPDATE_COOLDOWN_LIST:
		{
			update_cooldown_list(db_conn, (MsgDBUpdateCooldownListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_HANDBOOK_LIST:
		{
			update_handbook_list(db_conn, (MsgDBUpdateHandbookListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_MATERIAL_LIST:
		{
			update_material_list(db_conn, (MsgDBUpdateMaterialListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_PROPS_LIST:
		{
			update_props_list(db_conn, (MsgDBUpdatePropsListRequest*)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_CHARACTER_SNAP_INFO:
		{
//  			for (int i=0;i<100000;i++)
//  			{
//  				m_unID = i;
				update_character_snap_info(db_conn, (MsgDBUpdateCharacterSnapInfoRequest *)msgInfo.body);
			//}
		}
		break;
	case MSG_DB_UPDATE_FRIENDSHIP:
		{
			update_friendship(db_conn, (MsgDBUpdateFriendshipRequest *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_PVP_INFO:
		{
			update_pvp_info(db_conn, (MsgDBUpdatePVPInfoResquest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_MONEY_TREE_INFO:
		{
			update_money_tree(db_conn, (MsgDBUpdateMoneyTreeInfoRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_HIGHEST_TEAM_INFO:
		{
			update_highest_team_info(db_conn, (MsgDBUpdateHighestTeamInfoRequest *)msgInfo.body);
		}
		break;

	case MSG_DB_UPDATE_SECRET_LIST:
		{
			update_secret_list(db_conn, (MsgDBUpdateSecretListRequest *)msgInfo.body);
		}
		break;
	case MSG_DB_UPDATE_WING_LIST:
		{
			update_wing_list(db_conn, (MsgDBUpdateWingListRequest *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_PLAYER_GIFT_BAG_CODE:
		{
			update_player_gift_bag_code(db_conn, (MsgDBUpdatePlayerGiftBagCodeRequest*)msgInfo.body);
		}break;
	//case MSG_DB_UPDATE_GLOBLE_GIFT_BAG_CODE:
	//	{
	//		update_globle_gift_bag_code(db_conn, (MsgDBUpdateGlobleGiftBagCodeRequest*)msgInfo.body);
	//	}break;
	/*case MSG_DB_REQUEST_GLOBLE_GIFT_BAG_CODE:
		{
			load_globle_gift_bag_code(db_conn);
			send_globle_gift_bag_code(msgInfo.s_head->srcAdr);
		}break;*/
	case MSG_DB_ORDER_REQUEST://充值订单请求
		{
			CreatOneOrder(db_conn,(MsgDBOrderRequest*)msgInfo.body);
		}break;
	case MSG_DESTROY_MSG_ACK://异常断开
		{
			MsgDestroyRequest *info = (MsgDestroyRequest *)msgInfo.body;
			this->set_destroy(true);
			//this->setObjStatus(SERVICE_OBJ_DESTROY);
			printf("db home destroy obj：[%d]\n",m_unID);
		}break;
	}
}

void DBHomeHandler::update_cache(MessageInfo &msgInfo)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

// 	if(BaseService::g_msg_count>500)//消息已经处理不过来了
// 	{
// 		ACE_UINT32 now = GameUtils::get_utc();
// 		if (BaseService::g_msg_time < now)
// 		{
// 			MsgDoDBTimeHardRequest request;
// 			ZeroVar(request);
// 
// 			sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DO_DB_SERVER_TIME_HARD, (char *)&request,
// 				sizeof(MsgDoDBTimeHardRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unID);
// 
// 			BaseService::g_msg_time = now + 2;
// 		}
// 	}

	switch(msgInfo.m_head->unType)
	{
	case MSG_DB_UPDATE_DATABASE:
		{
			//DBUserHandler::init_cooldown_list();

			//ACE_OS::memcpy(m_cooldownList, initCooldownList, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);
		}
		break;
	case MSG_DB_UPDATE_BASIC_INFO:
		{
			MsgDBUpdateBasicInfoRequest *body = (MsgDBUpdateBasicInfoRequest *)msgInfo.body;
			m_unCoin = body->unCoin;
			m_unMoney = body->unMoney;
			m_unExp = body->unExp;
			m_unLevel = body->unLevel;
			m_unPowerPoint = body->unPowerPoint;
			m_unHonour = body->unHonour;
			m_unFriendship = body->unFriendship;
			m_unDynamicEnergy = body->unDynamicEnergy;
		}
		break;
	case MSG_DB_UPDATE_CHARACTER_FLAG:
		{
			MsgDBUpdateCharacterFlagRequest *body = (MsgDBUpdateCharacterFlagRequest *)msgInfo.body;
			m_dwFlag = body->unFlag;
		}
		break;
	case MSG_DB_UPDATE_CURRENT_MAP:
		{
			MsgDBUpdateCurrentMapRequest *body = (MsgDBUpdateCurrentMapRequest *)msgInfo.body;
			m_mapInstanceInfo = body->info;
			m_mapReward = body->reward;
			m_unMapLastRewardTime = body->unLastRewardTime;
		}
		break;
	case MSG_DB_UPDATE_MAP_FLAG_LIST:
		{
			MsgDBUpdateMapFlagListRequest *body = (MsgDBUpdateMapFlagListRequest *)msgInfo.body;
			ACE_OS::memcpy(m_mapFlagList, body->flagList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
			ACE_OS::memcpy(m_mapGiftList, body->giftList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
		}
		break;
	case MSG_DB_UPDATE_PLAYER_LIST:
		{
			MsgDBUpdatePlayerListRequest *body = (MsgDBUpdatePlayerListRequest *)msgInfo.body;
			//m_unPlayerCount = body->unCount;
			//m_unMaxPlayerSelected = body->unMaxSelected;
			m_staff = body->staff;
			ACE_OS::memcpy(m_selectedPlayerList, body->selectedList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
			ACE_OS::memcpy(m_playerList, body->playerList, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
			ACE_OS::memcpy(m_selectedPlayerSkillList, body->playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
		}
		break;
		/*
	case MSG_DB_UPDATE_EQUIPMENT_LIST:
		{
			MsgDBUpdateEquipmentListRequest *body = (MsgDBUpdateEquipmentListRequest *)msgInfo.body;
			ACE_OS::memcpy(m_equipmentList, body->equipmentList, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);
		}
		break;
		*/
	case MSG_DB_UPDATE_PACKAGE_CELL:
		{
			MsgDBUpdatePackageCellRequest *body = (MsgDBUpdatePackageCellRequest *)msgInfo.body;
			int idx = body->cell.unIdx;
			m_itemsList[idx] = body->cell;
		}
		break;
	case MSG_DB_ADD_PACKAGE_CELL:
		{
			MsgDBAddPackageCellRequest *body = (MsgDBAddPackageCellRequest *)msgInfo.body;
			int idx = body->cell.unIdx;
			m_itemsList[idx] = body->cell;
			m_unItemsCount ++;
		}
		break;
	case MSG_DB_UPDATE_ENERGY:
		{
			MsgDBUpdateEnergyRequest *body = (MsgDBUpdateEnergyRequest *)msgInfo.body;
			m_unEnergy = body->unEnergy;
			m_unEnergyRestoreTime = body->unRestoreTime;
// 			m_unPVPEnergy = body->unPVPEnergy;
// 			m_unPVPEnergyRestoreTime = body->unPVPRestoreTime;
			//m_unBuyEnergyCount = body->unEnergyBuyCount;
			//m_unBuyEnergyTime = body->unEnergyBuyTime;
		}
		break;
	case MSG_DB_UPDATE_SKILL_LIST:
		{
			MsgDBUpdateSkillListRequest *body = (MsgDBUpdateSkillListRequest *)msgInfo.body;
			ACE_OS::memcpy(m_skillList, body->skillList, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);
			ACE_OS::memcpy(m_playerSkillList, body->playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SKILL_COUNT);
			ACE_OS::memcpy(m_bookRes, body->bookRes, sizeof(SkillBook) * MAX_PLAYER_SKILL_COUNT);
		}
		break;
		/*
	case MSG_DB_UPDATE_WEAPON_SKILL_LIST:
		{
			MsgDBUpdateWeaponSkillListRequest *body = (MsgDBUpdateWeaponSkillListRequest *)msgInfo.body;
			ACE_OS::memcpy(m_weaponSkillList, body->list, sizeof(WeaponSkillInfo) * MAX_WEAPON_SKILL_COUNT);
		}
		break;
		*/
	case MSG_DB_UPDATE_FRIEND_LIST:
		{
			MsgDBUpdateFriendListRequest *body = (MsgDBUpdateFriendListRequest *)msgInfo.body;
			m_unMaxFriendCount = body->unMaxFriendCount;
			ACE_OS::memcpy(m_friendList, body->friendList, sizeof(DBFriendInfo) * MAX_FRIEND_COUNT);
		}
		break;
	case MSG_DB_UPDATE_DELERE_FRIEND_LIST:
		{
			m_deleteFriendList = *((DeleteFriendList *)msgInfo.body);
		}break;
	case MSG_DB_UPDATE_INVITE_LIST:
		{
			MsgDBUpdateInviteListRequest *body = (MsgDBUpdateInviteListRequest *)msgInfo.body;
			ACE_OS::memcpy(m_inviteList, body->inviteList, sizeof(ACE_UINT32) * MAX_INVITE_COUNT);
		}
		break;
	case MSG_DB_UPDATE_ASSIST_LIST:
		{
			MsgDBUpdateAssistListRequest *body = (MsgDBUpdateAssistListRequest *)msgInfo.body;
			ACE_OS::memcpy(m_assistList, body->assistList, sizeof(AssistInfo) * MAX_ASSIST_COUNT);
		}break;
	case MSG_DB_DELETE_LAST_ITEM:
		{
			m_unItemsCount --;
		}
		break;
	case MSG_UPDATE_NAME:
		{
			//MsgDBUpdateNameRequest *body = (MsgDBUpdateNameRequest *)msgInfo.body;
			//ACE_OS::memcpy(this->m_name, body->name, MAX_CHARACTER_LENGTH);
			//this->m_name[MAX_CHARACTER_LENGTH] = '\0';
		}
		break;
	case MSG_DB_UPDATE_NAME_INTERNAL:
		{
			MsgDBUpdateNameInternalRequest *body = (MsgDBUpdateNameInternalRequest *)msgInfo.body;
			ACE_OS::memcpy(this->m_name, body->name, MAX_CHARACTER_LENGTH);
			this->m_name[MAX_CHARACTER_LENGTH] = '\0';
		}
		break;
	case MSG_DB_UPDATE_LOGIN_INFO:
		{
			MsgDBUpdateLoginInfoRequest *body = (MsgDBUpdateLoginInfoRequest *)msgInfo.body;
			this->m_unLastLoginTime = body->unLoginTime;
			this->m_unLoginBonusCount = body->unLoginBonusCount;
			this->m_unLoginCount = body->unLoginCount;
		}
		break;
	case MSG_DB_UPDATE_FUNCTION_LIST:
		{
			MsgDBUpdateFunctionListRequest *body = (MsgDBUpdateFunctionListRequest *)msgInfo.body;
			ACE_OS::memcpy(m_LockedFunctionList, body->list, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);
		}
		break;
	case MSG_DB_UPDATE_RECHARGE_INFO:
		{
			MsgDBUpdateRechargeInfoRequest *body = (MsgDBUpdateRechargeInfoRequest *)msgInfo.body;
			m_unRechargeCount = body->unRechargeCount;
			m_unRechargeAmount = body->unRechargeAmount;
		}
		break;
	case MSG_DB_UPDATE_VIP_GIFT_INFO:
		{
			MsgDBVipGiftInfo * body = (MsgDBVipGiftInfo *)msgInfo.body;
			m_vipGift = body->m_vipGift;
		}break;
	case MSG_DB_UPDATE_PACKAGE_MAX:
		{
			MsgDBUpdatePackageMaxRequest *body = (MsgDBUpdatePackageMaxRequest *)msgInfo.body;

			this->m_unPackageMax = body->unPackageMax;
		}
		break;
	case MSG_DB_UPDATE_REBORN_INFO:
		{
			MsgDBUpdateRebornInfoRequest *body = (MsgDBUpdateRebornInfoRequest *)msgInfo.body;

			m_unFreeRebornCount = body->unFreeRebornCount;
			m_unLastRebornTime = body->unLastRebornTime;
		}
		break;
		/*
	case MSG_DB_UPDATE_BATTLE_INFO:
		{
			MsgDBUpdateBattleInfoRequest *body = (MsgDBUpdateBattleInfoRequest *)msgInfo.body;

			m_battleInfo = body->battleInfo;
			m_battleSnapInfo = body->snapInfo;
		}
		break;
		*/
	case MSG_UPDATE_GIFT_LIST:
		{
			MsgDBUpdateGiftListRequest *body = (MsgDBUpdateGiftListRequest *)msgInfo.body;

			ACE_OS::memcpy(m_giftList, body->list, sizeof(GiftInfo) * MAX_GIFT_COUNT);
		}
		break;
	case MSG_UPDATE_TUTORIAL_FLAG:
		{
			MsgDBUpdateTutorialFlagRequest *body = (MsgDBUpdateTutorialFlagRequest *)msgInfo.body;

			m_unTutorialFlag = body->unTutorialFlag;
		}
		break;
	case MSG_UPDATE_USE_LUCK_COUNT:
		{
			MsgDBUpdateUseLuckCountRequest *body = (MsgDBUpdateUseLuckCountRequest *)msgInfo.body;

			m_unUseLuckCount = body->unUseLuckCount;
		}
		break;
		/*
	case MSG_UPDATE_IMPROVE_PROPERTY:
		{
			MsgDBUpdateImprovePropertyRequest *body = (MsgDBUpdateImprovePropertyRequest *)msgInfo.body;

			ACE_OS::memcpy(m_improvePropertyList, body->improvePropertyList, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
			//update_improve_property
		}
		break;
		*/
	case MSG_DB_UPDATE_COOLDOWN_LIST:
		{
			MsgDBUpdateCooldownListRequest *body = (MsgDBUpdateCooldownListRequest *)msgInfo.body;

			ACE_OS::memcpy(m_cooldownList, body->list, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);
		}
		break;
	case MSG_DB_UPDATE_HANDBOOK_LIST:
		{
			MsgDBUpdateHandbookListRequest *body = (MsgDBUpdateHandbookListRequest *)msgInfo.body;

			m_unHandbookCount = body->unCount;
			ACE_OS::memcpy(m_handbookList, body->list, sizeof(BaseItemInfo) * body->unCount);
		}
		break;
	case MSG_DB_UPDATE_MATERIAL_LIST:
		{
			MsgDBUpdateMaterialListRequest *body = (MsgDBUpdateMaterialListRequest *)msgInfo.body;

			m_unMaterialCount = body->unCount;
			ACE_OS::memcpy(m_materialList, body->list, sizeof(MaterialInfo) * body->unCount);
		}
		break;
	case MSG_DB_UPDATE_PROPS_LIST:
		{
			MsgDBUpdatePropsListRequest *body = (MsgDBUpdatePropsListRequest *)msgInfo.body;
			m_propsList.resize(body->unCount);
			if(body->unCount != 0)
				ACE_OS::memcpy(&m_propsList[0], body->list, sizeof(PropsInfo) * body->unCount);
		}
		break;
	case MSG_DB_UPDATE_PVP_INFO:
		{
			MsgDBUpdatePVPInfoResquest *body = (MsgDBUpdatePVPInfoResquest *)msgInfo.body;

			m_pvpInfo = body->info;


		}
		break;
	case MSG_DB_UPDATE_MONEY_TREE_INFO:
		{
			MsgDBUpdateMoneyTreeInfoRequest *body = (MsgDBUpdateMoneyTreeInfoRequest *)msgInfo.body;
			
			m_unMoneyTreeLevel = body->unLevel;
			m_unMoneyTreeExp = body->unExp;
		}
		break;
	case MSG_DB_UPDATE_HIGHEST_TEAM_INFO:
		{
			MsgDBUpdateHighestTeamInfoRequest *body = (MsgDBUpdateHighestTeamInfoRequest *)msgInfo.body;
			m_unHighestPoint = body->info.unPoint;
		}
		break;
	case MSG_DB_UPDATE_SECRET_LIST:  //added by jinpan for secret
		{
			MsgDBUpdateSecretListRequest *body = (MsgDBUpdateSecretListRequest *)msgInfo.body;

			m_secretMgr.m_unCellCount = body->unCellCount;
			m_secretMgr.m_refreshTimes = body->unRefreshTimes;
			m_secretMgr.m_unLastRefreshTime = body->unLastRefreshTime;
			ACE_OS::memcpy(m_secretMgr.m_list, body->list, sizeof(SecretItemInfo) * body->unCellCount);
		}
		break;
	case MSG_DB_UPDATE_WING_LIST:
		{
			MsgDBUpdateWingListRequest *body = (MsgDBUpdateWingListRequest *)msgInfo.body;
			m_wingInfo.m_count = body->unCount;
			ACE_OS::memcpy(m_wingInfo.m_list, body->list, sizeof(WingItemInfo) * MAX_WING_LIST);
		}break;
	case MSG_DB_UPDATE_PLAYER_GIFT_BAG_CODE:
		{
			MsgDBUpdatePlayerGiftBagCodeRequest *body = (MsgDBUpdatePlayerGiftBagCodeRequest *)msgInfo.body;
			m_giftBagCodeSet[m_unGiftBagCodeCount++] = body->wGiftBagCodeType;
		}break;
	case MSG_DB_UPDATE_DOUBLE_DROP_INFO:
		{
			MsgDBUpdateDoubleDropInfoRequest *body = (MsgDBUpdateDoubleDropInfoRequest *)msgInfo.body;
			m_unDoubleDropVersion = body->m_unVersion;
			ACE_OS::memcpy(m_usedDoubleDropList, body->m_usedDoubleList,sizeof(ACE_UINT32) * MAX_DOUBLE_DROP_COUNT);
		}break;
	case MSG_DB_INSERT_TASK_LIST:
	case MSG_DB_UPDATE_TASK_LIST:
		{
			MsgDBUpdateTaskInfoRequest *body = (MsgDBUpdateTaskInfoRequest *)msgInfo.body;
			int i=0;
			for(;i<m_unTaskCount;++i)
			{
				if (m_taskList[i].unTaskID == body->m_taskInfo.unTaskID)
				{
					m_taskList[i].unCurrentProgress = body->m_taskInfo.unCurrentProgress;
					m_taskList[i].byStatus = body->m_taskInfo.byStatus;
					break;
				}
			}
			if (i==m_unTaskCount && m_unTaskCount+1<MAX_TOTAL_TASK_COUNT)
			{
				m_taskList[m_unTaskCount].byStatus = body->m_taskInfo.byStatus;
				m_taskList[m_unTaskCount].unCurrentProgress = body->m_taskInfo.unCurrentProgress;
				m_taskList[m_unTaskCount].unTaskID = body->m_taskInfo.unTaskID;
				++m_unTaskCount;
			}
		}break;
	case MSG_DB_DELETE_TASK:
		{
			MsgDBDeleteTaskInfoRequest *body = (MsgDBDeleteTaskInfoRequest *)msgInfo.body;
			int i=0;
			for(;i<m_unTaskCount;++i)
			{
				if (m_taskList[i].unTaskID == body->m_unTaskID)
				{
					m_taskList[i] = m_taskList[m_unTaskCount--];
					break;
				}
			}
		}break;
	case MSG_DB_UPDATE_TASK_PROGRESS_REQUEST:
		{
			MsgDBTaskList *body = (MsgDBTaskList *)msgInfo.body;
			memset(m_taskProgressList, 0, sizeof(TaskInfo) * MAX_TOTAL_TASK_COUNT); //保险起见
			memcpy(m_taskProgressList, body->m_taskList, body->m_unCount*sizeof(TaskInfo));
		}break;
	case MSG_DB_UPDATE_GOLDEN_TOUCH_REQUEST:
		{
			MsgDBUpdateGoldenTouchRequest *body = (MsgDBUpdateGoldenTouchRequest *)msgInfo.body;
			m_unUsedGoldenTouchCount = body->m_unUsedCount;
		}break;
	case MSG_DB_UPDATE_BUY_ENERGY_REQUEST:
		{
			MsgDBUpdateBuyEnergyRequest *body = (MsgDBUpdateBuyEnergyRequest *)msgInfo.body;
			m_unCurrentBuyEnergy = body->m_unCurrentCount;
		}break;
	case MSG_DB_UPDATE_LA_PROGRESS_RESPONSE://限时活动
		{
			MsgDBLimitedActivityList *body = (MsgDBLimitedActivityList *)msgInfo.body;
			ZeroVar(m_LAlist);
			memcpy(&m_LAlist,body,sizeof(MsgDBLimitedActivityList));
			//memset(&m_LAlist,0,sizeof(MsgDBLimitedActivityList));
		}break;
	case MSG_DB_UPDATE_LA_PROGRESS_RESPONSE1://限时活动更新一条数据
		{
			LimitedActivityInfo *body = (LimitedActivityInfo *)msgInfo.body;
			bool isIn =false;
			for (int i=0;i<m_LAlist.m_unCount;i++)
			{
				if (m_LAlist.m_LAList[i].unLAID == body->unLAID)
				{
					m_LAlist.m_LAList[i] = *body;
					isIn = true;
					break;
				}
			}
			
			//没有更新，跟新
			if (!isIn && m_LAlist.m_unCount <MAX_LIMITED_ACTIVITY_COUNT )
			{
				m_LAlist.m_LAList[m_LAlist.m_unCount] = *body;
				m_LAlist.m_unCount++;
			}
		}break;
	case MSG_DB_UPDATE_BADGE_PROGRESS_RESPONSE1:
		{
			BadgeInfo * body = (BadgeInfo *)msgInfo.body;
			m_mapBadge[body->unID] = *body;
		}break;
	case MSG_DB_UPDATE_CHANGED_DATE:
		{
			MsgDBUpdateChangedDate *body = (MsgDBUpdateChangedDate *)msgInfo.body;
			m_unChangedDate = body->m_unUpdateChangedDate;
		}break;
	case MSG_DB_INSERT_OBTAINED_ACTIVENESS_REWARD:
		{
			MsgDBInsertObtainedActivenessRewardRequest *body = (MsgDBInsertObtainedActivenessRewardRequest *)msgInfo.body;
			m_ObtainedActivenessRewardList[m_unObtainedActivenessRewardCount++] = body->m_unObtainedActivenessReward;
		}break;
	case MSG_DB_UPDATE_FRIENDSHIP:
		{
			MsgDBUpdateFriendshipRequest *body = (MsgDBUpdateFriendshipRequest *)msgInfo.body;
			m_unFriendship = body->m_unFriendship;
		}break;
	}
}

int DBHomeHandler::load_basic_info(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = db_conn->prepareStatement("select user_id,name,level,exp,coin,money,last_login_time,login_bonus_count,login_count,energy,energy_restore_time,power_point,honour,recharge_count,recharge_amount,vip_level,vip_amount,package_max,tutorial_flag,use_luck_count,flag,buy_month_card_time, gift_bag_code_flag, used_double_drop, changed_date, friendship,dynamic_energy, golden_touch_count,buy_energy_num,bitfield,vip_gift,power from character_tbl where character_id=?");
	ResultSet *_db_res = NULL;
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);

	try
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception * e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_basic_info sql exception unID[%u],error:%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}

	if(_db_res == NULL)
	{
		return -1;
	}

	
	//char *p;
	int c = 0;

	//m_unPlayerCount = 0;

	if(_db_res->next())
	{
		try
		{
			m_unUserID = _db_res->getInt("user_id");
			m_unLevel = _db_res->getInt("level");
			m_unExp = _db_res->getInt("exp");
			m_unCoin = _db_res->getInt("coin");
			m_unMoney = _db_res->getInt("money");
			m_unHonour = _db_res->getInt("honour");
			m_unLastLoginTime = _db_res->getInt("last_login_time");
			m_unLoginBonusCount = _db_res->getInt("login_bonus_count");
			m_unLoginCount = _db_res->getInt("login_count");
			m_unEnergy = _db_res->getInt("energy");
			m_unEnergyRestoreTime = _db_res->getUInt("energy_restore_time");
// 			m_unPVPEnergy = _db_res->getInt("pvp_energy");
// 			m_unPVPEnergyRestoreTime = _db_res->getUInt("pvp_energy_restore_time");
			//m_unBuyEnergyTime = _db_res->getInt("buy_energy_time");
			//m_unBuyEnergyCount = _db_res->getInt("buy_energy_count");
			m_unPowerPoint = _db_res->getInt("power_point");
			m_unRechargeCount = _db_res->getInt("recharge_count");
			m_unRechargeAmount = _db_res->getInt("recharge_amount");
			m_unPackageMax = _db_res->getInt("package_max");
			m_unTutorialFlag = _db_res->getInt("tutorial_flag");
			m_unUseLuckCount = _db_res->getInt("use_luck_count");
			m_dwFlag = _db_res->getUInt("flag");
			m_dwBuyMonthCardTime = _db_res->getUInt("buy_month_card_time");
			m_vipInfo.vip_level = _db_res->getUInt("vip_level");
			m_vipInfo.vip_amount = _db_res->getUInt("vip_amount");
			m_bitField = _db_res->getUInt("bitfield");

			set_name(_db_res->getString("name"), m_name, MAX_CHARACTER_LENGTH);

			std::istream *stream = _db_res->getBlob("gift_bag_code_flag");
			m_unGiftBagCodeCount = 0;
			memset(m_giftBagCodeSet, 0, MAX_GIFT_BAG_CODE_COUNT * sizeof(WORD));
			while((m_unGiftBagCodeCount < MAX_GIFT_BAG_CODE_COUNT) && stream->read((char *)&m_giftBagCodeSet[m_unGiftBagCodeCount], sizeof(WORD)))
			{
				++m_unGiftBagCodeCount;
			}

			stream = _db_res->getBlob("vip_gift");
			m_vipGift.unCount = 0;
			while((m_vipGift.unCount < RECHARGE_MAX_PRODUCT) && stream->read((char *)&m_vipGift.list[m_vipGift.unCount], sizeof(ACE_UINT32)))
			{
				++m_vipGift.unCount;
			}

			stream = _db_res->getBlob("used_double_drop");
			m_unUsedDoubleDropCount = 0;
			memset(m_usedDoubleDropList, 0, MAX_DOUBLE_DROP_COUNT * sizeof(ACE_UINT32));
			if (stream->read((char *)&m_unDoubleDropVersion, sizeof(ACE_UINT32)))
			{
				while((m_unUsedDoubleDropCount < MAX_DOUBLE_DROP_COUNT) && stream->read((char *)&m_usedDoubleDropList[m_unUsedDoubleDropCount], sizeof(ACE_UINT32)))
				{
					++m_unUsedDoubleDropCount;
				}
			}
			m_unChangedDate = _db_res->getInt("changed_date");
			m_unFriendship = _db_res->getInt("friendship");
			m_unDynamicEnergy = _db_res->getInt("dynamic_energy");
			m_unPower = _db_res->getInt("power");
			m_unUsedGoldenTouchCount = _db_res->getInt("golden_touch_count");
			m_unCurrentBuyEnergy = _db_res->getInt("buy_energy_num");//买体力
			/*
			stream = _db_res->getBlob("player_list");
			c = 0;
			while(stream->read((char *)&m_playerList[c], sizeof(PlayerInfo)))
			{
				c ++;
			}
			m_unPlayerCount = c;
			*/
			//m_unMaxPlayerSelected = 4;

			/*
			stream = _db_res->getBlob("equipment_list");
			c = 0;
			while(stream->read((char *)&m_equipmentList[c], sizeof(PackageCell)))
			{
				c ++;
			}
			*/
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_basic_info data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}
	else
	{
		return -1;
	}

	destroy_db_res(_prep_stmt,_db_res);

	return load_Channel_info(db_conn);
}

int DBHomeHandler::load_items_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = db_conn->prepareStatement("select idx,item_id,count,info from items_tbl where character_id=? order by idx");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	ResultSet *_db_res = NULL;
	try
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_items_list sql exception unID[%u],error:%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	int idx;

	m_unItemsCount = 0;

	while(_db_res->next())
	{
		try
		{
			idx = _db_res->getInt("idx");
			m_itemsList[m_unItemsCount].unIdx = idx;
			m_itemsList[m_unItemsCount].item.item.unResID = _db_res->getInt("item_id");
			m_itemsList[m_unItemsCount].item.unCount = _db_res->getInt("count");
			stream = _db_res->getBlob("info");
			p = (char *)&m_itemsList[m_unItemsCount].item.item.info;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}

			m_unItemsCount ++;
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_items_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_map_list(Connection *db_conn)
{
	PreparedStatement * _prep_stmt = db_conn->prepareStatement("select current_map_info,current_reward,flag_list,last_reward_time,free_reborn_count,last_reborn_time,map_gift_list from map_tbl where character_id=?");
	ResultSet *_db_res = NULL;

	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try 
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_map_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;

	//ACE_OS::memset(&m_battleSnapInfo, 0, sizeof(BattleSnapInfo));
	//ACE_OS::memset(&m_battleInfo, 0, sizeof(MapBattleInfo));
	ACE_OS::memset(&m_mapInstanceInfo, 0, sizeof(MapInstanceInfo));
	ACE_OS::memset(&m_mapReward, 0, sizeof(RewardInfo));
	ACE_OS::memset(m_mapFlagList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	ACE_OS::memset(&m_mapGiftList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);


	while(_db_res->next())
	{
		try
		{
		stream = _db_res->getBlob("current_map_info");
		p = (char *)&m_mapInstanceInfo;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("current_reward");
		p = (char *)&m_mapReward;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("flag_list");
		p = (char *)m_mapFlagList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("map_gift_list");
		p = (char *)m_mapGiftList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		/*
		stream = _db_res->getBlob("snap_info");
		p = (char *)&m_battleSnapInfo;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("battle_info");
		p = (char *)&m_battleInfo;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
		*/

		m_unMapLastRewardTime = _db_res->getInt("last_reward_time");
		m_unFreeRebornCount = _db_res->getInt("free_reborn_count");
		m_unLastRebornTime = _db_res->getInt("last_reborn_time");
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_map_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_skill_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt =NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select skill_list,player_skill_list,player_skill_res from skill_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_skill_info sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;

	ACE_OS::memset(m_skillList, 0, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);
	ACE_OS::memset(m_playerSkillList, 0, sizeof(ACE_UINT32) * MAX_PLAYER_SKILL_COUNT);
	ACE_OS::memset(m_bookRes, 0, sizeof(SkillBook) * MAX_PLAYER_SKILL_COUNT);

	while(_db_res->next())
	{
		try
		{

		
		stream = _db_res->getBlob("skill_list");
		p = (char *)m_skillList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("player_skill_list");
		p = (char *)m_playerSkillList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("player_skill_res");
		p = (char *)m_bookRes;
		int count = 0;
		while(stream->read(p, sizeof(SkillBook)))
		{			
			count++;
			p = (char *)&m_bookRes[count];//注意指针读取数据的大小和类型!bug jinpan

		}
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_skill_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

/*
int DBHomeHandler::load_weapon_skill_list(Connection *db_conn)
{
	_prep_stmt = db_conn->prepareStatement("select list,improve_property from weapon_skill_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	int idx;

	while(_db_res->next())
	{
		stream = _db_res->getBlob("list");
		p = (char *)m_weaponSkillList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		ACE_OS::memset(m_improvePropertyList, 0, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
		stream = _db_res->getBlob("improve_property");
		p = (char *)m_improvePropertyList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
	}

	destroy_db_res();

	return 0;
}
*/

int DBHomeHandler::load_friend_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select max_count,invite_list,friend_list,assist_list,delete_list from friend_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_friend_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;

	m_unMaxFriendCount = 10;
	
	ACE_OS::memset(m_inviteList, 0, sizeof(ACE_UINT32) * MAX_INVITE_COUNT);
	ACE_OS::memset(m_friendList, 0, sizeof(DBFriendInfo) * MAX_FRIEND_COUNT);
	ACE_OS::memset(m_inviteList, 0, sizeof(AssistInfo) * MAX_ASSIST_COUNT);

	while(_db_res->next())
	{
		try
		{

		m_unMaxFriendCount = _db_res->getInt("max_count");

		stream = _db_res->getBlob("invite_list");
		p = (char *)m_inviteList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("friend_list");
		p = (char *)m_friendList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		ZeroVar(m_deleteFriendList);
		stream = _db_res->getBlob("delete_list");
		p = (char *)&m_deleteFriendList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}


		stream = _db_res->getBlob("assist_list");
		p = (char *)m_assistList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_friendl_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	ZeroVar(m_bs);
	for (int i=0;i<MAX_FRIEND_COUNT;i++)
	{
		if (m_friendList[i].unCharacterID > 0)
		{
			Get_BS_info(db_conn,m_bs[i],m_friendList[i].unCharacterID);
		}
		else
			break;
	}
	return 0;
}

int DBHomeHandler::load_function_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;

	_prep_stmt = db_conn->prepareStatement("select lock_list from function_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_function sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;
	
	ACE_OS::memset(m_LockedFunctionList, 0, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);

	while(_db_res->next())
	{
		try
		{

		stream = _db_res->getBlob("lock_list");
		p = (char *)m_LockedFunctionList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_function_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_gift_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;

	_prep_stmt = db_conn->prepareStatement("select gift_list from gift_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_gift_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;
	
	ACE_OS::memset(m_giftList, 0, sizeof(GiftInfo) * MAX_GIFT_COUNT);

	while(_db_res->next())
	{
		try
		{

		stream = _db_res->getBlob("gift_list");
		p = (char *)m_giftList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_gift_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_player_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select list,selected_list,staff,player_skill_list from player_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
	_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_player_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;
	
	ACE_OS::memset(m_playerList, 0, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	ACE_OS::memset(m_selectedPlayerList, 0, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memset(&m_staff, 0, sizeof(ItemInfo));
	ACE_OS::memset(m_selectedPlayerSkillList, 0, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);

	while(_db_res->next())
	{
		try
		{

			stream = _db_res->getBlob("list");
			p = (char *)m_playerList;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}

			stream = _db_res->getBlob("selected_list");
			p = (char *)m_selectedPlayerList;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}

			stream = _db_res->getBlob("staff");
			p = (char *)&m_staff;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}

			stream = _db_res->getBlob("player_skill_list");
			p = (char *)m_selectedPlayerSkillList;
			while(stream->read(p, sizeof(char)))
			{
				p ++;
			}
		}
		catch (std::exception * e)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_player_list data handle exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	m_unHighestPoint = 0;
	_prep_stmt = db_conn->prepareStatement("select point from team_rank_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	while(_db_res->next())
	{
		m_unHighestPoint = _db_res->getInt("point");
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_cooldown_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt=NULL;
	ResultSet *_db_res = NULL;

	_prep_stmt = db_conn->prepareStatement("select info from cooldown_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
	_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception * e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_cooldown_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;
	
	ACE_OS::memset(m_cooldownList, 0, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);

	while(_db_res->next())
	{
		try
		{
		stream = _db_res->getBlob("info");
		p = (char *)m_cooldownList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_cooldown_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_handbook_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;

	m_unHandbookCount = 0;
	_prep_stmt = db_conn->prepareStatement("select list from handbook_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{

		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_handbook_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;
	
	ACE_OS::memset(m_handbookList, 0, sizeof(BaseItemInfo) * MAX_HANDBOOK_COUNT);

	while(_db_res->next())
	{
		try
		{
		stream = _db_res->getBlob("list");
		p = (char *)m_handbookList;
		while(stream->read(p, sizeof(BaseItemInfo)))
		{
			m_unHandbookCount ++;
			p = (char *)&m_handbookList[m_unHandbookCount];
			
		}
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_handbook_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_materail_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res= NULL;
	m_unMaterialCount = 0;
	_prep_stmt = db_conn->prepareStatement("select list from material_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
	_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception &e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_materail_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e.what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;
	
	ACE_OS::memset(m_materialList, 0, sizeof(MaterialInfo) * MAX_MATERIAL_COUNT);

	while(_db_res->next())
	{
		try
		{

		stream = _db_res->getBlob("list");
		p = (char *)m_materialList;
		while(stream->read(p, sizeof(MaterialInfo)))
		{
			m_unMaterialCount ++;
			p = (char *)&m_materialList[m_unMaterialCount];
		}
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_material_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_pvp_info(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select honour,attack_times,last_change_time,win_lost,buy_count,freshen_count from pvp_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
	_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_pvp_info sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	ZeroVar(m_pvpInfo);

	if (_db_res->next())
	{
		m_pvpInfo.nhonour = _db_res->getInt("honour");
		m_pvpInfo.unAttackTimes = _db_res->getInt("attack_times");
		m_pvpInfo.unLastChangeTime = _db_res->getInt("last_change_time");
		m_pvpInfo.unWinLost = _db_res->getInt("win_lost");
		m_pvpInfo.unBuyCount = _db_res->getInt("buy_count");
		m_pvpInfo.unFreshenCount =_db_res->getInt("freshen_count");
	}
	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBHomeHandler::load_money_tree_info(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select level,exp from moneytree_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
	_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception *e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_money_tree_info sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	while(_db_res->next())
	{
		try
		{
		m_unMoneyTreeLevel = _db_res->getInt("level");
		m_unMoneyTreeExp = _db_res->getInt("exp");
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_money_tree_info data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

void DBHomeHandler::send_basic_info(ObjAdr &desAdr)
{
	MsgDBCharacterBasicResponse info;
	info.nResult = 0;

	ACE_OS::memcpy(info.name, m_name, MAX_CHARACTER_LENGTH + 1);
	info.unUserID = m_unUserID;
	info.unCoin = m_unCoin;
	info.unMoney = m_unMoney;
	info.unPowerPoint = m_unPowerPoint;
	info.unHonour = m_unHonour;
	info.unLevel = m_unLevel;
	info.unExp = m_unExp;
	info.unEnergy = m_unEnergy;
	info.unEnergyRestoreTime = m_unEnergyRestoreTime;
// 	info.unPVPEnergy = m_unPVPEnergy;
// 	info.unPVPEnergyRestoreTime = m_unPVPEnergyRestoreTime;
	info.unLastLoginTime = m_unLastLoginTime;
	info.unLoginBonusCount = m_unLoginBonusCount;
	info.unLoginCount = m_unLoginCount;
	
	//info.unBuyEnergyTime = m_unBuyEnergyTime;
	//info.unBuyEnergyCount = m_unBuyEnergyCount;
	info.unRechargeCount = m_unRechargeCount;
	info.unRechargeAmount = m_unRechargeAmount;
	info.unPackageMax = m_unPackageMax;
	info.unTutorialFlag = m_unTutorialFlag;
	info.unUseLuckCount = m_unUseLuckCount;
	info.unFlag = m_dwFlag;
	info.unGoldenTouchUsedTimes = m_unUsedGoldenTouchCount;
	info.unBuyMonthCardTime = m_dwBuyMonthCardTime;
	info.unChangedDate = m_unChangedDate;
	info.unFriendship = m_unFriendship;
	info.unDynamicEnergy = m_unDynamicEnergy;
	info.m_unChannel = m_unChannel;//渠道id
	info.m_unCurrentBuyEnergy = m_unCurrentBuyEnergy;
	info.m_vipInfo = m_vipInfo;
	info.m_vipGift = m_vipGift;
	info.m_bitField = m_bitField;
	info.m_Productlist = m_Productlist;
	info.m_monthTime = m_monthTime;
	info.m_power = m_unPower;

	//ACE_OS::memcpy(info.improvePropertyList, m_improvePropertyList, sizeof(PropertyComponent) * PROPERTY_ID_MAX);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_CHARACTER_BASIC,(char*)&info, sizeof(MsgDBCharacterBasicResponse), desAdr, 0, false);
}

void DBHomeHandler::send_player_list(ObjAdr &desAdr)
{
	MsgDBPlayerListResponse info;
	info.nResult = 0;

	//info.unCount = m_unPlayerCount;
	//info.unMaxSelected = m_unMaxPlayerSelected;

	ACE_OS::memcpy(info.selectedList, m_selectedPlayerList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memcpy(info.playerList, m_playerList, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	ACE_OS::memcpy(info.playerSkillList, m_selectedPlayerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	info.staff = m_staff;
	info.unHighestPoint = m_unHighestPoint;

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_PLAYER_LIST,(char*)&info, sizeof(MsgDBPlayerListResponse), desAdr, 0, false);
}

/*
void DBHomeHandler::send_equipment_list(ObjAdr &desAdr)
{
	MsgDBEquipmentListResponse info;
	info.nResult = 0;

	ACE_OS::memcpy(info.equipmentList, m_equipmentList, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_EQUIPMENT_LIST,(char*)&info, sizeof(MsgDBEquipmentListResponse), desAdr, 0, false);
}
*/

void DBHomeHandler::send_items_list(ObjAdr &desAdr)
{
	//char send_buff[1024];
	int size;
	MsgDBItemsListResponse *info = (MsgDBItemsListResponse *)db_send_buff;
	info->unCount = 0;
	info->nResult = 0;

	//PackageCell *pCell;
	int c = 0;
	int i;

// 	for(i = 0; i < m_unItemsCount; i++)
// 	{
// 		info->list[c] = m_itemsList[i];
// 
// 		c ++;
// 
// 		/*
// 		if(c == 50)
// 		{
// 			info->unCount = c;
// 			size = sizeof(MsgDBItemsListResponse) + c * sizeof(PackageCell);
// 			this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_ITEMS_LIST,(char *)info, size, desAdr, 0, false);
// 
// 			c = 0;
// 		}
// 		*/
// 	}
	memcpy(&info->list[0],&m_itemsList[0],m_unItemsCount*sizeof(PackageCell));

	info->unCount = m_unItemsCount;
	size = sizeof(MsgDBItemsListResponse) + m_unItemsCount * sizeof(PackageCell);
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_ITEMS_LIST,(char *)info, size, desAdr, 0, false);
}

void DBHomeHandler::send_map_list(ObjAdr &desAdr)
{
	MsgDBMapListResponse response;

	response.nResult = 0;
	response.instanceInfo = m_mapInstanceInfo;
	response.reward = m_mapReward;
	ACE_OS::memcpy(response.flagList, m_mapFlagList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	response.unFreeRebornCount = m_unFreeRebornCount;
	response.unLastRewardTime = m_unMapLastRewardTime;
	response.unLastRebornTime = m_unLastRebornTime;
	ACE_OS::memcpy(response.giftList, m_mapGiftList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	//response.snapInfo = m_battleSnapInfo;
	//response.battleInfo = m_battleInfo;

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_MAP_LIST,(char*)&response, sizeof(MsgDBMapListResponse), desAdr, 0, false);
}

void DBHomeHandler::send_skill_list(ObjAdr &desAdr)
{
	MsgDBSkillListResponse response;

	response.nResult = 0;
	ACE_OS::memcpy(response.skillList, m_skillList, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);
	ACE_OS::memcpy(response.playerSkillList, m_playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SKILL_COUNT);
	ACE_OS::memcpy(response.bookRes,m_bookRes,sizeof(SkillBook)*MAX_PLAYER_SKILL_COUNT);
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_SKILL_LIST,(char*)&response, sizeof(MsgDBSkillListResponse), desAdr, 0, false);
}

/*
void DBHomeHandler::send_weapon_skill_list(ObjAdr &desAdr)
{
	MsgDBWeaponSkillListResponse response;

	response.nResult = 0;
	ACE_OS::memcpy(response.list, m_weaponSkillList, sizeof(WeaponSkillInfo) * MAX_WEAPON_SKILL_COUNT);
	ACE_OS::memcpy(response.improvePropertyList, m_improvePropertyList, sizeof(PropertyComponent) * PROPERTY_ID_MAX);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_WEAPON_SKILL_LIST,(char*)&response, sizeof(MsgDBWeaponSkillListResponse), desAdr, 0, false);
}
*/

void DBHomeHandler::send_friend_list(ObjAdr &desAdr)
{
	MsgDBFriendListResponse response;

	response.nResult = 0;
	response.unMaxFriendCount = m_unMaxFriendCount;
	ACE_OS::memcpy(response.inviteList, m_inviteList, sizeof(ACE_UINT32) * MAX_INVITE_COUNT);
	ACE_OS::memcpy(response.friendList, m_friendList, sizeof(DBFriendInfo) * MAX_FRIEND_COUNT);
	ACE_OS::memcpy(response.assistList, m_assistList, sizeof(AssistInfo) * MAX_ASSIST_COUNT);
	ACE_OS::memcpy(response.m_bs, m_bs, sizeof(BadgeShuxingS) * MAX_FRIEND_COUNT);
	ACE_OS::memcpy(&response.deleteFriendList,&m_deleteFriendList,sizeof(DeleteFriendList));

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_FRIEND_LIST,(char*)&response, sizeof(MsgDBFriendListResponse), desAdr, 0, false);
}

void DBHomeHandler::send_function_list(ObjAdr &desAdr)
{
	MsgDBFunctionListResponse response;

	response.nResult = 0;
	ACE_OS::memcpy(response.list, m_LockedFunctionList, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_FUNCTION_LIST,(char*)&response, sizeof(MsgDBFunctionListResponse), desAdr, 0, false);
}

void DBHomeHandler::send_gift_list(ObjAdr &desAdr)
{
	MsgDBGiftListResponse response;

	response.nResult = 0;
	ACE_OS::memcpy(response.list, m_giftList, sizeof(GiftInfo) * MAX_GIFT_COUNT);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_GIFT_LIST,(char*)&response, sizeof(MsgDBGiftListResponse), desAdr, 0, false);
}

void DBHomeHandler::send_cooldown_list(ObjAdr &desAdr)
{
	MsgDBCooldownListResponse response;

	response.nResult = 0;
	ACE_OS::memcpy(response.list, m_cooldownList, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_COUNT_LIMIT_LIST,(char*)&response, sizeof(MsgDBCooldownListResponse), desAdr, 0, false);
}

void DBHomeHandler::send_handbook_list(ObjAdr &desAdr)
{
	MsgDBHandbookListResponse *response = (MsgDBHandbookListResponse *)db_send_buff;

	response->nResult = 0;
	response->unCount = m_unHandbookCount;
	ACE_OS::memcpy(response->list, m_handbookList, sizeof(BaseItemInfo) * m_unHandbookCount);
	int size = sizeof(BaseItemInfo) * m_unHandbookCount + sizeof(MsgDBHandbookListResponse);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_HANDBOOK_LIST,(char*)response, size, desAdr, 0, false);
}

void DBHomeHandler::send_material_list(ObjAdr &desAdr)
{
	MsgDBMaterialListResponse *response = (MsgDBMaterialListResponse *)db_send_buff;

	response->nResult = 0;
	response->unCount = m_unMaterialCount;
	ACE_OS::memcpy(response->list, m_materialList, sizeof(MaterialInfo) * m_unMaterialCount);
	int size = sizeof(MaterialInfo) * m_unMaterialCount + sizeof(MsgDBMaterialListResponse);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_MATERIAL_LIST,(char*)response, size, desAdr, 0, false);
}

void DBHomeHandler::send_pvp_info(ObjAdr &desAdr)
{
	MsgDBPVPInfoResponse response;

	response.nResult = 0;
	response.info = m_pvpInfo;

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_PVP_INFO,(char*)&response, sizeof(MsgDBPVPInfoResponse), desAdr, 0, false);
}

void DBHomeHandler::send_money_tree_info(ObjAdr &desAdr)
{
	MsgDBMoneyTreeInfoResponse response;
	response.nResult = 0;
	response.unLevel = m_unMoneyTreeLevel;
	response.unExp = m_unMoneyTreeExp;

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_MONEY_TREE_INFO,(char*)&response, sizeof(MsgDBMoneyTreeInfoResponse), desAdr, 0, false);
}

void DBHomeHandler::update_basic_info(Connection *db_conn, MsgDBUpdateBasicInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set coin=?,money=?,exp=?,level=?,power_point=?,honour=?,friendship=?,dynamic_energy=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unCoin);
	_prep_stmt->setInt(2, info->unMoney);
	_prep_stmt->setInt(3, info->unExp);
	_prep_stmt->setInt(4, info->unLevel);
	_prep_stmt->setInt(5, info->unPowerPoint);
	_prep_stmt->setInt(6, info->unHonour);
	_prep_stmt->setInt(7, info->unFriendship);
	_prep_stmt->setInt(8, info->unDynamicEnergy);
	_prep_stmt->setInt(9, m_unID);

	try
	{
	_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_basic_info sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::deal_admin_op( Connection *db_conn, MsgAdminOPRequest *request, ObjAdr &targetAdr )
{
	switch(request->unOpType)
	{
	//change by xxj 2015/04/22  12: 05:59
	//用户可能不在线，所以可能封号不成功 调整到DBUserHandler中处理
	/*
	case ADMIN_OP_TYPE_DISABLE_ACCOUNT:
		{
			MsgDBUpdateCharacterFlagRequest rq;
			rq.unFlag |= 0x1;
			update_character_flag(db_conn, &rq);
		}
		break;
	case ADMIN_OP_TYPE_ENABLE_ACCOUNT:
		{
			MsgDBUpdateCharacterFlagRequest rq;
			rq.unFlag &= ~0x1;
			update_character_flag(db_conn, &rq);
		}
		break;
	*/
	default:
		break;
	}
}

void DBHomeHandler::deal_admin_buffer_op(MsgAdminOPBufferRequest *pRequest, ObjAdr &strAdr)
{
	switch(pRequest->unOpType)
	{
// 	case ADMIN_OP_TYPE_STATISTICS://统计
// 		{
// 			AdminStatistics oStatistics;
// 			if (pRequest->unParamCount < 1)
// 			{
// 				printf("error occurs in ADMIN_OP_TYPE_STATISTICS");
// 				return;
// 			}
// 			oStatistics.unStatisticsType = pRequest->paramList[0];
// 			ACE_OS::memcpy(oStatistics.strDate, pRequest->strBuffer, pRequest->unBufferLen); //不会超长的
// 			pRequest->strBuffer[pRequest->unBufferLen] = '\0';
// 			DBHomeMgr *adapter = (DBHomeMgr *)DBService::instance()->getAdapter(ADAPTER_DB_HOME_MGR);
// 			int iData = -1;
// 			if (adapter != NULL)
// 				iData = adapter->LoadStatistics(oStatistics.unStatisticsType, oStatistics.strDate,pRequest->paramList);
// 
// 			tagMsgDBGetStatisticsResponse response;
// 			response.unData = iData;
// 			response.unType = oStatistics.unStatisticsType;
// 			this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_GET_DATA_STATISTICS, (char *)&response, sizeof(MsgDBAdminStatisticsResponse), strAdr);
// 		}break;
	default:
		break;
	}
}

void DBHomeHandler::update_current_map(Connection *db_conn, MsgDBUpdateCurrentMapRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update map_tbl set current_map_info=?,current_reward=?,last_reward_time=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)&info->info, sizeof(MapInstanceInfo));
	std::istream is(&data);

	DBDataBuf data1((char *)&info->reward, sizeof(RewardInfo));
	std::istream is1(&data1);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setBlob(2, &is1);
	_prep_stmt->setInt(3, info->unLastRewardTime);
	_prep_stmt->setInt(4, m_unID);

	try
	{
	_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_current_map sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_map_flag_list(Connection *db_conn, MsgDBUpdateMapFlagListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update map_tbl set flag_list=?,map_gift_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->flagList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	std::istream is(&data);

	DBDataBuf data1((char *)info->giftList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	std::istream is1(&data1);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setBlob(2, &is1);
	_prep_stmt->setInt(3, m_unID);

	try
	{
	_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_map_flag_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_double_drop(Connection *db_conn, MsgDBUpdateDoubleDropInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set used_double_drop=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info, sizeof(MsgDBUpdateDoubleDropInfoRequest));
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	try
	{
	_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_double_drop sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_task_list(Connection *db_conn, MsgDBUpdateTaskInfoRequest *info)
{
	PreparedStatement *_prep_stmt= NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update task_tbl set task_status=?, progress=? where character_id=? and task_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->m_taskInfo.byStatus);
	_prep_stmt->setInt(2, info->m_taskInfo.unCurrentProgress);
	_prep_stmt->setInt(3, m_unID);
	_prep_stmt->setInt(4, info->m_taskInfo.unTaskID);

	try
	{
	_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_task_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::insert_task_list(Connection *db_conn, MsgDBUpdateTaskInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "insert into task_tbl(character_id, task_id, task_status, progress) values(%d, %d, %d, %d) on duplicate key update task_status=1, progress=0",
		m_unID, info->m_taskInfo.unTaskID, info->m_taskInfo.byStatus, info->m_taskInfo.unCurrentProgress);
	_prep_stmt = db_conn->prepareStatement(tmp_sql);
	if(_prep_stmt == NULL)
	{
		return;
	}

	/*_prep_stmt->setInt(1, m_unID);
	_prep_stmt->setInt(2, info->m_taskInfo.unTaskID);
	_prep_stmt->setInt(3, info->m_taskInfo.byStatus);
	_prep_stmt->setInt(4, info->m_taskInfo.unCurrentProgress);*/
	try
	{

	_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler insert_task_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::delete_task(Connection *db_conn, MsgDBDeleteTaskInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "delete from task_tbl where character_id=%d and task_id=%d",m_unID, info->m_unTaskID);
	_prep_stmt = db_conn->prepareStatement(tmp_sql);
	if(_prep_stmt == NULL)
	{
		return;
	}
	try
	{
	_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler delete task exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_task_progress(Connection *db_conn, MsgDBTaskList *info)
{
	//_prep_stmt = db_conn->prepareStatement("insert into task_progress_tbl(character_id, task_progress) values(?, ?) on duplicate key update task_progress = ? ");
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("replace into task_progress_tbl(character_id, task_progress) values(?, ?)");
	if(_prep_stmt == NULL)
	{
		return;
	}
	DBDataBuf data((char *)info->m_taskList, sizeof(TaskInfo) * info->m_unCount);
	std::istream is(&data);

	_prep_stmt->setInt(1, m_unID);
	_prep_stmt->setBlob(2, &is);
	//_prep_stmt->setBlob(3, &is);

	try
	{
		_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_task_progress exception unID[%u],%s",__FILE__, __LINE__, m_unID,e->what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_golden_touch(Connection *db_conn, MsgDBUpdateGoldenTouchRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	char tmp_sql[1024];
	ACE_OS::sprintf(tmp_sql, "update character_tbl set golden_touch_count=%d where character_id=%d",info->m_unUsedCount, m_unID);
	_prep_stmt = db_conn->prepareStatement(tmp_sql);
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}


void DBHomeHandler::update_Buy_energy( Connection *db_conn, MsgDBUpdateBuyEnergyRequest *info )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	char tmp_sql[1024];
	ACE_OS::sprintf(tmp_sql, "update character_tbl set buy_energy_num=%d where character_id=%d",info->m_unCurrentCount, m_unID);
	_prep_stmt = db_conn->prepareStatement(tmp_sql);
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}


void DBHomeHandler::update_changed_date(Connection *db_conn, MsgDBUpdateChangedDate *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "update character_tbl set changed_date=%d where character_id=%d",info->m_unUpdateChangedDate,	m_unID);
	_prep_stmt = db_conn->prepareStatement(tmp_sql);
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::insert_obtained_activeness_reward(Connection *db_conn, MsgDBInsertObtainedActivenessRewardRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	char tmp_sql[1024];

	ACE_OS::sprintf(tmp_sql, "insert into activeness_reward_tbl(character_id, activeness_point, obtain_date) values(%d, %d, CURRENT_DATE())",m_unID,info->m_unObtainedActivenessReward);
	_prep_stmt = db_conn->prepareStatement(tmp_sql);
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_player_list(Connection *db_conn, MsgDBUpdatePlayerListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update player_tbl set list=?,selected_list=?,staff=?,player_skill_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->playerList, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	std::istream is(&data);

	DBDataBuf data1((char *)info->selectedList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	std::istream is1(&data1);

	DBDataBuf data2((char *)&info->staff, sizeof(ItemInfo));
	std::istream is2(&data2);

	DBDataBuf data3((char *)&info->playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	std::istream is3(&data3);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setBlob(2, &is1);
	_prep_stmt->setBlob(3, &is2);
	_prep_stmt->setBlob(4, &is3);
	_prep_stmt->setInt(5, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

/*
void DBHomeHandler::update_equipment_list(Connection *db_conn, MsgDBUpdateEquipmentListRequest *info)
{
	_prep_stmt = db_conn->prepareStatement("update character_tbl set equipment_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->equipmentList, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res();
}
*/


void DBHomeHandler::update_package_cell(Connection *db_conn, MsgDBUpdatePackageCellRequest *info)
{
	//删除老的
	{
		PreparedStatement *_prep_stmt = NULL;
		ResultSet *_db_res = NULL;
		_prep_stmt = db_conn->prepareStatement("delete from items_tbl where character_id=? and idx=?");
		if(_prep_stmt == NULL)
		{
			return;
		}

		_prep_stmt->setInt(1, m_unID);
		_prep_stmt->setInt(2, info->cell.unOldIndex);

		_prep_stmt->executeUpdate();
		destroy_db_res(_prep_stmt,_db_res);
	}

	//更新新的
	{
		PreparedStatement *_prep_stmt = NULL;
		ResultSet *_db_res = NULL;
		//_prep_stmt = db_conn->prepareStatement("update items_tbl set item_id=?,count=?,info=? where character_id=? and idx=?");
		_prep_stmt = db_conn->prepareStatement("replace into items_tbl(item_id,count,info,character_id,idx) values(?,?,?,?,?)");
		if(_prep_stmt == NULL)
		{
			return;
		}

		DBDataBuf data((char *)&info->cell.item.item.info, sizeof(ItemDetailInfo));
		std::istream is(&data);

		_prep_stmt->setInt(1, info->cell.item.item.unResID);
		_prep_stmt->setInt(2, info->cell.item.unCount);
		_prep_stmt->setBlob(3, &is);
		_prep_stmt->setInt(4, m_unID);
		_prep_stmt->setInt(5, info->cell.unIdx);

		_prep_stmt->executeUpdate();
		destroy_db_res(_prep_stmt,_db_res);
	}
}

void DBHomeHandler::add_package_cell(Connection *db_conn, MsgDBAddPackageCellRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("replace into items_tbl(character_id,idx,item_id,count,info) values(?,?,?,?,?)");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)&info->cell.item.item.info, sizeof(ItemDetailInfo));
	std::istream is(&data);

	_prep_stmt->setInt(1, m_unID);
	_prep_stmt->setInt(2, info->cell.unIdx);
	_prep_stmt->setInt(3, info->cell.item.item.unResID);
	_prep_stmt->setInt(4, info->cell.item.unCount);
	_prep_stmt->setBlob(5, &is);
	
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_energy_info(Connection *db_conn, MsgDBUpdateEnergyRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set energy=?,energy_restore_time=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unEnergy);
	_prep_stmt->setInt(2, info->unRestoreTime);
	//_prep_stmt->setInt(3, info->unPVPEnergy);
	//_prep_stmt->setInt(4, info->unPVPRestoreTime);
	_prep_stmt->setInt(3, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_skill_list(Connection *db_conn, MsgDBUpdateSkillListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update skill_tbl set skill_list=?,player_skill_list=?,player_skill_res=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->skillList, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);
	std::istream is(&data);

	DBDataBuf data1((char *)info->playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SKILL_COUNT);
	std::istream is1(&data1);

	DBDataBuf data2((char *)info->bookRes, sizeof(SkillBook) * MAX_PLAYER_SKILL_COUNT);
	std::istream is2(&data2);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setBlob(2, &is1);
	_prep_stmt->setBlob(3, &is2);
	_prep_stmt->setInt(4, m_unID);
	//_prep_stmt->setInt(3, m_unID);
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

/*
void DBHomeHandler::update_weapon_skill_list(Connection *db_conn, MsgDBUpdateWeaponSkillListRequest *info)
{
	_prep_stmt = db_conn->prepareStatement("update weapon_skill_tbl set list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(WeaponSkillInfo) * MAX_WEAPON_SKILL_COUNT);
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res();
}
*/

void DBHomeHandler::update_friend_list(Connection *db_conn, MsgDBUpdateFriendListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update friend_tbl set max_count=?,friend_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->friendList, sizeof(DBFriendInfo) * MAX_FRIEND_COUNT);
	std::istream is(&data);

	_prep_stmt->setInt(1, info->unMaxFriendCount);
	_prep_stmt->setBlob(2, &is);
	_prep_stmt->setInt(3, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_invite_list(Connection *db_conn, MsgDBUpdateInviteListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update friend_tbl set invite_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->inviteList, sizeof(ACE_UINT32) * MAX_INVITE_COUNT);
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_assist_list(Connection *db_conn, MsgDBUpdateAssistListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update friend_tbl set assist_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->assistList, sizeof(AssistInfo) * MAX_ASSIST_COUNT);
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

/*
void DBHomeHandler::update_property_list(Connection *db_conn, MsgDBPropertyUpdateRequest *info)
{
	_prep_stmt = db_conn->prepareStatement("update character_tbl set property=?,skill_id=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->propertyList, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, info->unSkillID);
	_prep_stmt->setInt(3, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res();
}
*/

void DBHomeHandler::update_vip_level(Connection *db_conn, MsgDBVipLevelUpdateRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set vip_level=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}
	_prep_stmt->setInt(1, info->unVipLevel);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::delete_last_item(Connection *db_conn, MsgDBDeleteLastItemRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("delete from items_tbl where character_id=? and idx=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, m_unID);
	_prep_stmt->setInt(2, info->unIdx);
	
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_name(Connection *db_conn, MsgDBUpdateNameRequest *info, ObjAdr &desAdr)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set name=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setString(1, info->name);
	_prep_stmt->setInt(2, m_unID);

	int update_ret = 0;
	try
	{
		_prep_stmt->executeUpdate();
	}
	catch(SQLException &e)
	{
		update_ret = -1;
	}

	destroy_db_res(_prep_stmt,_db_res);

	MsgDBUpdateNameResponse response;
	response.unSN = info->unSN;
	ACE_OS::memcpy(response.name, info->name, MAX_CHARACTER_LENGTH);
	response.name[MAX_CHARACTER_LENGTH] = '\0';
	response.nResult = 1;
	response.unSig = info->unSig;
	if(update_ret == 0)
	{
		response.nResult = 0;

		MsgDBUpdateNameInternalRequest request;
		ACE_OS::memcpy(request.name, info->name, MAX_CHARACTER_LENGTH);
		request.name[MAX_CHARACTER_LENGTH] = '\0';

		this->send_local_msg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_UPDATE_NAME_INTERNAL, (char *)&request, sizeof(MsgDBUpdateNameInternalRequest), m_ParentAdapter->m_unID, m_unID);
	}

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_UPDATE_NAME,(char*)&response, sizeof(MsgDBUpdateNameResponse), desAdr, 0, false);
}

void DBHomeHandler::update_login_info(Connection *db_conn, MsgDBUpdateLoginInfoRequest *info)
{
	//last_login_time,login_bonus_count,login_count
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set last_login_time=?,login_bonus_count=?,login_count=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unLoginTime);
	_prep_stmt->setInt(2, info->unLoginBonusCount);
	_prep_stmt->setInt(3, info->unLoginCount);
	_prep_stmt->setInt(4, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_function_list(Connection *db_conn, MsgDBUpdateFunctionListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update function_tbl set lock_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_recharge_info(Connection *db_conn, MsgDBUpdateRechargeInfoRequest *info)
{
	PreparedStatement *_prep_stmt= NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set recharge_count=?,recharge_amount=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unRechargeCount);
	_prep_stmt->setInt(2, info->unRechargeAmount);
	_prep_stmt->setInt(3, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_package_max(Connection *db_conn, MsgDBUpdatePackageMaxRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set package_max=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unPackageMax);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_reborn_info(Connection *db_conn, MsgDBUpdateRebornInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update map_tbl set free_reborn_count=?,last_reborn_time=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unFreeRebornCount);
	_prep_stmt->setInt(2, info->unLastRebornTime);
	_prep_stmt->setInt(3, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_gift_list(Connection *db_conn, MsgDBUpdateGiftListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update gift_tbl set gift_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(GiftInfo) * MAX_GIFT_COUNT);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);

	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_tutorial_flag(Connection *db_conn, MsgDBUpdateTutorialFlagRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set tutorial_flag=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unTutorialFlag);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_use_luck_count(Connection *db_conn, MsgDBUpdateUseLuckCountRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set use_luck_count=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unUseLuckCount);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

/*
void DBHomeHandler::update_improve_property(Connection *db_conn, MsgDBUpdateImprovePropertyRequest *info)
{
	_prep_stmt = db_conn->prepareStatement("update weapon_skill_tbl set improve_property=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->improvePropertyList, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);

	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res();
}
*/

void DBHomeHandler::update_cooldown_list(Connection *db_conn, MsgDBUpdateCooldownListRequest *info)
{
	PreparedStatement *_prep_stmt=NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update cooldown_tbl set info=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);

	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::insert_cooldown_list(Connection *db_conn, CooldownInstanceInfo *list)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("insert into cooldown_tbl(character_id,info) values(?,?)");

	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)list, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);
	std::istream is(&data);

	_prep_stmt->setInt(1, m_unID);
	_prep_stmt->setBlob(2, &is);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}


void DBHomeHandler::insert_new_table(Connection *db_conn)
{
	/*
	_prep_stmt = db_conn->prepareStatement("insert into handbook_tbl(character_id) values(?)");

	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, m_unID);
	_prep_stmt->executeUpdate();
	destroy_db_res();

	_prep_stmt = db_conn->prepareStatement("insert into material_tbl(character_id) values(?)");

	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, m_unID);
	_prep_stmt->executeUpdate();
	destroy_db_res();
	*/
}


void DBHomeHandler::update_handbook_list(Connection *db_conn, MsgDBUpdateHandbookListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update handbook_tbl set list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(BaseItemInfo) * info->unCount);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);

	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_material_list(Connection *db_conn, MsgDBUpdateMaterialListRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update material_tbl set list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(MaterialInfo) * info->unCount);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);

	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_character_snap_info(Connection *db_conn, MsgDBUpdateCharacterSnapInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tmp_tbl set team_info=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)&info->teamInfo, sizeof(PlayerTeamInfo));
	std::istream is(&data);
// 	DBDataBuf data1((char *)&info->pvpTeamInfo, sizeof(PlayerTeamInfo));
// 	std::istream is1(&data1);
	_prep_stmt->setBlob(1, &is);
	//_prep_stmt->setBlob(2, &is1);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_friendship(Connection *db_conn, MsgDBUpdateFriendshipRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set friendship=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->m_unFriendship);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_pvp_info(Connection *db_conn, MsgDBUpdatePVPInfoResquest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	//_prep_stmt = db_conn->prepareStatement("update pvp_tbl set honour=?,attack_times=?,last_change_time=?,win_lost=?,buy_count=?,freshen_count=? where character_id=?");
	_prep_stmt = db_conn->prepareStatement("update pvp_tbl set attack_times=?,last_change_time=?,buy_count=?,freshen_count=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	//_prep_stmt->setInt(1, info->info.nhonour);
	_prep_stmt->setUInt(1, info->info.unAttackTimes);
	_prep_stmt->setInt(2, info->info.unLastChangeTime);
	//_prep_stmt->setUInt(4, info->info.unWinLost);//不能在这里更新
	_prep_stmt->setUInt(3, info->info.unBuyCount);
	_prep_stmt->setUInt(4, info->info.unFreshenCount);
	_prep_stmt->setUInt(5, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	/*
	_prep_stmt = db_conn->prepareStatement("update character_tmp_tbl set rank=?,pvp_season=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->rankInfo.unRank);
	_prep_stmt->setInt(2, info->rankInfo.unSeasonID);
	_prep_stmt->setInt(3, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res();
	*/
}

void DBHomeHandler::update_money_tree(Connection *db_conn, MsgDBUpdateMoneyTreeInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update moneytree_tbl set level=?,exp=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unLevel);
	_prep_stmt->setInt(2, info->unExp);
	_prep_stmt->setInt(3, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_highest_team_info(Connection *db_conn, MsgDBUpdateHighestTeamInfoRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res=NULL;

	if (info->unType == 1)//更新战斗力
	{
		_prep_stmt = db_conn->prepareStatement("UPDATE character_tbl SET power = ? WHERE character_id =?");

		if(_prep_stmt == NULL)
		{
			return;
		}

		_prep_stmt->setInt(1, info->info.unPoint);
		_prep_stmt->setInt(2, m_unID);
		_prep_stmt->executeUpdate();
		destroy_db_res(_prep_stmt,_db_res);
	}
	else
	{
		_prep_stmt = db_conn->prepareStatement("replace into team_rank_tbl(point,team_info,update_time,character_id) values(?,?,?,?)");

		if(_prep_stmt == NULL)
		{
			return;
		}

		DBDataBuf data((char *)&info->info, sizeof(PlayerTeamInfo));
		std::istream is(&data);

		_prep_stmt->setInt(1, info->info.unPoint);
		_prep_stmt->setBlob(2, &is);
		_prep_stmt->setInt(3, GameUtils::get_utc());
		_prep_stmt->setInt(4, m_unID);
		_db_res = _prep_stmt->executeQuery();
		destroy_db_res(_prep_stmt,_db_res);
	}
}

void DBHomeHandler::send_secret_list(ObjAdr &desAdr)
{
	//MsgDBSecretListResponse *response = (MsgDBSecretListResponse *)db_send_buff;//瞎搞..
	MsgDBSecretListResponse response;
	response.nResult = 0;
	
//	ACE_OS::memcpy(response.list, m_secretMgr.m_list, sizeof(SecretItemInfo) * m_secretMgr.m_unCellCount);   //刚建账号没有刷新，list米面没数据但是大小乘以了3，把后面的count和times覆盖了这句必须在后面那几句的前面
	ACE_OS::memcpy(response.list, m_secretMgr.m_list, sizeof(SecretItemInfo) * MAX_SECRET_LIST);   //刚建账号没有刷新，list米面没数据但是大小乘以了3，把后面的count和times覆盖了这句必须在后面那几句的前面
	response.unCellCount = m_secretMgr.m_unCellCount;
	response.unRefreshTimes = m_secretMgr.m_refreshTimes;
	response.unLastRefreshTime = m_secretMgr.m_unLastRefreshTime;
	
	
//	int size = sizeof(SecretItemInfo) * (m_secretMgr.m_unCellCount) + sizeof(MsgDBSecretListResponse);//这是从1开始的
	//int size = sizeof(SecretItemInfo) * MAX_SECRET_LIST + sizeof(MsgDBSecretListResponse);//change by xxj 2015/06/06  17: 56:11 这一句有问题故改由下一句来执行
	int size = sizeof(MsgDBSecretListResponse);//这是从1开始的
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_SECRET_LIST,(char*)&response, size, desAdr, 0, false);
}


int DBHomeHandler::load_secret_list(Connection *db_conn)  //added by jinpan for secret
{	
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select list,cell_count,refresh_times,last_refresh from secret_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

//	bool insertFlag = true;
	if(!_db_res->next())
	{
		//当角色第一次进入时，新建神秘商店信息
		PreparedStatement *tmp_prep_stmt = db_conn->prepareStatement("insert into secret_tbl(character_id, cell_count) values(?, ?)");
		if(tmp_prep_stmt == NULL)
		{
			return -1;
		}
		tmp_prep_stmt->setInt(1, m_unID);
		tmp_prep_stmt->setInt(2, GAME_CONFIG_INSTANCE::instance()->m_secretCfg.unMaxCell);
		tmp_prep_stmt->executeUpdate(); //??这个该选用什么 jinpan
		//-------------------------------------
		//add by xxj 2015/05/14 14:46:23 (检查到可能有内存泄漏)
		tmp_prep_stmt->close();
		delete tmp_prep_stmt;
		tmp_prep_stmt = NULL;
		//Set init value;
		m_secretMgr.m_unCellCount = GAME_CONFIG_INSTANCE::instance()->m_secretCfg.unMaxCell; 
		m_secretMgr.m_refreshTimes = 0;
		m_secretMgr.m_unLastRefreshTime = 0;
		//---------------------------------------------------
	}else {
		std::istream *stream;
		char *p;
		//int idx;

		ACE_OS::memset(m_secretMgr.m_list, 0, sizeof(SecretItemInfo) * MAX_SECRET_LIST);
		
		stream = _db_res->getBlob("list");
		p = (char *)m_secretMgr.m_list;
		int count = 0;
		while(stream->read(p, sizeof(SecretItemInfo)))
		{			
			count++;
			p = (char *)&m_secretMgr.m_list[count];//注意指针读取数据的大小和类型!bug jinpan
			
		}

		m_secretMgr.m_unCellCount = _db_res->getInt("cell_count");  //这段应该放在后面...
		m_secretMgr.m_refreshTimes = _db_res->getInt("refresh_times");
		m_secretMgr.m_unLastRefreshTime = _db_res->getInt("last_refresh");
	}
	destroy_db_res(_prep_stmt,_db_res);
	return 0;
}     

void DBHomeHandler::update_secret_list(Connection *db_conn, MsgDBUpdateSecretListRequest *info)
{
	PreparedStatement *_prep_stmt=NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update secret_tbl set list=?,cell_count = ?,refresh_times = ?,last_refresh = ? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(SecretItemInfo) * info->unCellCount);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, info->unCellCount);
	_prep_stmt->setInt(3, info->unRefreshTimes);
	_prep_stmt->setInt(4, info->unLastRefreshTime);
	_prep_stmt->setInt(5, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

int DBHomeHandler::load_wing_list(Connection *db_conn){
	PreparedStatement *_prep_stmt=NULL;
	ResultSet *_db_res= NULL; 
	_prep_stmt = db_conn->prepareStatement("select list from wing_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}
	m_wingInfo.m_count = 0;
	//	bool insertFlag = true;
	if(!_db_res->next())
	{
		//没数据创建数据
		PreparedStatement *tmp_prep_stmt = db_conn->prepareStatement("insert into wing_tbl(character_id) values(?)");
		if(tmp_prep_stmt == NULL)
		{
			return -1;
		}
		tmp_prep_stmt->setInt(1, m_unID);
		tmp_prep_stmt->executeUpdate();
		//-------------------------------------
		//add by xxj 2015/05/14 14:46:23 (检查到可能有内存泄漏)
		tmp_prep_stmt->close();
		delete tmp_prep_stmt;
		tmp_prep_stmt = NULL;
		//----------------------------------------------

	}else {
		std::istream *stream;
		char *p;
		//int idx;

		ACE_OS::memset(m_wingInfo.m_list, 0, sizeof(WingItemInfo) * MAX_WING_LIST);

		stream = _db_res->getBlob("list");
		p = (char *)m_wingInfo.m_list;
		int count = 0;
		while(stream->read(p, sizeof(WingItemInfo)))
		{			
			count++;
			p = (char *)&m_wingInfo.m_list[count];

		}
		m_wingInfo.m_count = count;

		//WingInfo.m_unCellCount = _db_res->getInt("cell_count");
		//WingInfo.m_refreshTimes = _db_res->getInt("refresh_times");
		//WingInfo.m_unLastRefreshTime = _db_res->getInt("last_refresh");
	}
	destroy_db_res(_prep_stmt,_db_res);
	return 0;

}

void DBHomeHandler::send_wing_list(ObjAdr &desAdr)
{
	MsgDBWingListResponse response;
	response.nResult = 0;

	//	ACE_OS::memcpy(response.list, m_secretMgr.m_list, sizeof(SecretItemInfo) * m_secretMgr.m_unCellCount);
	ACE_OS::memcpy(response.list, m_wingInfo.m_list, sizeof(WingItemInfo) * MAX_WING_LIST);
	response.unCount = m_wingInfo.m_count;
	//response.unCellCount = m_secretMgr.m_unCellCount;
	//response.unRefreshTimes = m_secretMgr.m_refreshTimes;
	//response.unLastRefreshTime = m_secretMgr.m_unLastRefreshTime;


	int size = sizeof(MsgDBWingListResponse);		//sizeof(WingItemInfo) * MAX_WING_LIST
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_WING_LIST,(char*)&response, size, desAdr, 0, false);
}
void DBHomeHandler::update_wing_list(Connection *db_conn, MsgDBUpdateWingListRequest *info)
{
	PreparedStatement *_prep_stmt= NULL;
	ResultSet *_db_res =NULL;
	_prep_stmt = db_conn->prepareStatement("update secret_tbl set list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(WingItemInfo) * MAX_WING_LIST);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::send_gift_bag_code(ObjAdr &desAdr)
{
	MsgDBPlayerGiftBagCodeResponse response;
	response.nResult = 0;

	ACE_OS::memcpy(response.m_giftBagCodeSet, m_giftBagCodeSet, sizeof(WORD) * MAX_GIFT_BAG_CODE_COUNT);
	response.m_dwGiftBagCodeNum = m_unGiftBagCodeCount;

	int size = sizeof(MsgDBPlayerGiftBagCodeResponse);		//sizeof(WingItemInfo) * MAX_WING_LIST
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_PLAYER_GIFT_BAG_CODE,(char*)&response, size, desAdr, 0, false);
}

void DBHomeHandler::update_player_gift_bag_code(Connection *db_conn, MsgDBUpdatePlayerGiftBagCodeRequest *info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("call update_gift_bag_code_flag(?, ?);");
	if (_prep_stmt == NULL)
	{
		return;
	}
	DBDataBuf data((char *)&info->wGiftBagCodeType, sizeof(WORD));
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);
	//_prep_stmt->setBlob(2, &is1);
	_prep_stmt->setInt(2, m_unID);
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::send_double_drop(ObjAdr &desAdr)
{
	MsgDBDoubleDropInfoResponse response;
	response.nResult = 0;
	response.m_unVersion = m_unDoubleDropVersion;
	response.m_unCount = m_unUsedDoubleDropCount;
	ACE_OS::memcpy(response.m_usedDoubleList, m_usedDoubleDropList, sizeof(ACE_UINT32) * MAX_DOUBLE_DROP_COUNT);
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_DOUBLE_DROP_INFO, (char *)&response, sizeof(MsgDBDoubleDropInfoResponse), desAdr, 0, false);
}

int DBHomeHandler::load_task_list(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select task_id, progress, task_status from task_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}
	m_unTaskCount = 0;
	memset(m_taskList, 0, sizeof(TaskInfo) * MAX_TOTAL_TASK_COUNT);
	while (_db_res->next() && m_unTaskCount < MAX_TOTAL_TASK_COUNT)
	{
		m_taskList[m_unTaskCount].unTaskID = _db_res->getInt("task_id");
		m_taskList[m_unTaskCount].unCurrentProgress = _db_res->getInt("progress");
		m_taskList[m_unTaskCount].byStatus = _db_res->getInt("task_status");

		++m_unTaskCount;
	}

	destroy_db_res(_prep_stmt,_db_res);
	return 0;
}

void DBHomeHandler::send_task_list(ObjAdr &desAdr)
{
	MsgDBTaskList response;
	response.m_unCount = m_unTaskCount;
	ACE_OS::memcpy(response.m_taskList, m_taskList, sizeof(TaskInfo) * MAX_TOTAL_TASK_COUNT);
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_TASK_LIST, (char *)&response, sizeof(MsgDBTaskList), desAdr, 0, false);
}

int DBHomeHandler::load_obtained_activeness_reward(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select activeness_point from activeness_reward_tbl where character_id=? and obtain_date=CURRENT_DATE()");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}
	m_unObtainedActivenessRewardCount = 0;
	memset(m_ObtainedActivenessRewardList, 0, sizeof(UINT32) * MAX_ACTIVENESS_COUNT);
	while (_db_res->next() && m_unObtainedActivenessRewardCount < MAX_ACTIVENESS_COUNT)
	{
		m_ObtainedActivenessRewardList[m_unObtainedActivenessRewardCount++] = _db_res->getInt("activeness_point");
	}

	destroy_db_res(_prep_stmt,_db_res);
	return 0;
}

void DBHomeHandler::send_obtained_activeness_reward(ObjAdr &desAdr)
{
	MsgDBObtainedActivenessRewardList response;
	response.m_unCount = m_unObtainedActivenessRewardCount;
	ACE_OS::memcpy(response.m_ObtainedList, m_ObtainedActivenessRewardList, sizeof(UINT32) * MAX_ACTIVENESS_COUNT);
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_OBTAINED_ACTIVENESS_REWARD_LIST, (char *)&response, sizeof(MsgDBObtainedActivenessRewardList), desAdr, 0, false);
}

int DBHomeHandler::load_task_progress(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select task_progress from task_progress_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}
	memset(m_taskProgressList, 0, MAX_TOTAL_TASK_COUNT * sizeof(TaskInfo));
	if (_db_res->next())
	{
		std::istream *stream = _db_res->getBlob("task_progress");
		int iCount = 0;
		while((iCount < MAX_TOTAL_TASK_COUNT) && stream->read((char *)&m_taskProgressList[iCount], sizeof(TaskInfo)))
		{
			++iCount;
		}

		//m_unObtainedActivenessRewardCount = iCount;
	}

	destroy_db_res(_prep_stmt,_db_res);
	return 0;
}

void DBHomeHandler::send_task_progress(ObjAdr &desAdr)
{
	MsgDBTaskList response;
	response.m_unCount = MAX_TOTAL_TASK_COUNT;//m_unObtainedActivenessRewardCount;现在这个没必要了
	ACE_OS::memcpy(response.m_taskList, m_taskProgressList, sizeof(TaskInfo) * MAX_TOTAL_TASK_COUNT);
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_UPDATE_TASK_PROGRESS_RESPONSE, (char *)&response, sizeof(MsgDBTaskList), desAdr, 0, false);
}


/*void DBHomeHandler::send_globle_gift_bag_code(ObjAdr &desAdr)
{
	MsgDBGlobleGiftBagCodeResponse response;
	response.nResult = 0;
	ACE_OS::memcpy(response.m_oCodeItemList, m_globleGiftBagCodeList, sizeof(GiftBagCodeDBItem) * MAX_GLOBLE_GIFT_BAG_CODE_COUNT);
	
	int size = sizeof(MsgDBGlobleGiftBagCodeResponse);
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_GLOBLE_GIFT_BAG_CODE,(char*)&response, size, desAdr, 0, false);
}

void DBHomeHandler::update_globle_gift_bag_code(Connection *db_conn, MsgDBUpdateGlobleGiftBagCodeRequest *info)
{
	_prep_stmt = db_conn->prepareStatement("update gift_bag_code_tbl set used=? where gift_bag_code=?;");
	if (_prep_stmt == NULL)
	{
		return;
	}
	_prep_stmt->setInt(1, info->m_oCodeItem.m_byUsed);
	_prep_stmt->setString(2, sql::SQLString(info->m_oCodeItem.m_strGiftBagCode));
	_prep_stmt->executeUpdate();
	destroy_db_res();
}

int DBHomeHandler::load_globle_gift_bag_code(Connection *db_conn)
{
	_prep_stmt = db_conn->prepareStatement("select gift_bag_code, gift_bag_type, code_type, used from gift_bag_code_tbl;");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}
	m_unGiftBagCodeCount = 0;
	while(_db_res->next() && m_unGlobleGiftBagCodeCount < MAX_GLOBLE_GIFT_BAG_CODE_COUNT)
	{
		set_name(_db_res->getString("gift_bag_code"), m_globleGiftBagCodeList[m_unGlobleGiftBagCodeCount].m_strGiftBagCode, MAX_GIFT_BAG_CODE_LENGTH+1);
		//m_globleGiftBagCodeList[m_unGlobleGiftBagCodeCount].m_unExpiredTime = _db_res->getUInt("UNIX_TIMESTAMP(expired_time)");
		m_globleGiftBagCodeList[m_unGlobleGiftBagCodeCount].m_unGiftBagType = _db_res->getUInt("gift_bag_type");
		m_globleGiftBagCodeList[m_unGlobleGiftBagCodeCount].m_unCodeType = _db_res->getUInt("code_type");
		m_globleGiftBagCodeList[m_unGlobleGiftBagCodeCount].m_byUsed = _db_res->getInt("used");

		++m_unGlobleGiftBagCodeCount;
	}

	destroy_db_res();
	return 0;
}*/

void DBHomeHandler::update_character_flag( Connection *db_conn, MsgDBUpdateCharacterFlagRequest *info )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set flag=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unFlag);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

int DBHomeHandler::load_Channel_info( Connection *db_conn )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select channel_id from user_tbl where user_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}

	_prep_stmt->setInt(1, m_unUserID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	if (_db_res->next())
	{
		m_unChannel = _db_res->getInt("channel_id");//渠道id
	}

	destroy_db_res(_prep_stmt,_db_res);
	return 0;
}

int DBHomeHandler::load_limited_activity_progress( Connection *db_conn )
{
	Delete_limited_activity_progress(db_conn);//先删除

	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("SELECT limited_id,closetime,progress,dealtime,linktype,related_list from limit_activity_tbl where character_id=?;");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}
	ZeroVar(m_LAlist);
	//memset(m_LAlist, 0, MAX_LIMITED_ACTIVITY_COUNT * sizeof(MsgDBLimitedActivityList));
	//limited_id,closetime,progress,related_list
	int iCount = 0;
	while (_db_res->next() && iCount < MAX_LIMITED_ACTIVITY_COUNT)
	{
		//m_LAlist.m_LAList[iCount].unCharacterID = m_unID;
		m_LAlist.m_LAList[iCount].unLAID = _db_res->getInt("limited_id");
		m_LAlist.m_LAList[iCount].unCloseTime = _db_res->getInt("closetime");
		m_LAlist.m_LAList[iCount].unProgress = _db_res->getInt("progress");
		m_LAlist.m_LAList[iCount].unDealTime = _db_res->getInt("dealtime");
		m_LAlist.m_LAList[iCount].unLinkType = _db_res->getInt("linktype");
		std::istream *stream = _db_res->getBlob("related_list");//已领取列表

		int count = 0;
		while((count<MAX_RelatedT_ITEMS) && 
			stream->read((char *)&m_LAlist.m_LAList[iCount].unRelatedItems[count], sizeof(ACE_UINT32)))
		{
			count ++;
		}
		m_LAlist.m_LAList[iCount].unRelatedCount = count;
		iCount++;
	}
	m_LAlist.m_unCount = iCount;

	destroy_db_res(_prep_stmt,_db_res);
	return 0;
}


int DBHomeHandler::Delete_limited_activity_progress( Connection *db_conn )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("DELETE FROM limit_activity_tbl WHERE closetime < ?;");
	if(_prep_stmt == NULL)
	{
		return -1;
	}

	_prep_stmt->setInt(1,GameUtils::get_utc());//用于删除现在之前的老数据
	_prep_stmt->executeUpdate();

	destroy_db_res(_prep_stmt,_db_res);
	return 0;
}


void DBHomeHandler::send_limited_activity_progress( ObjAdr &desAdr )
{
	MsgDBLimitedActivityList response;
	std::memcpy(&response,&m_LAlist,sizeof(MsgDBLimitedActivityList));
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_UPDATE_LA_PROGRESS_RESPONSE,
		(char *)&response, sizeof(MsgDBLimitedActivityList), desAdr, 0, false);
}

void DBHomeHandler::update_LA_progress( Connection *db_conn, MsgDBLimitedActivityList *info )
{
	for (int i=0;i<info->m_unCount;i++)
	{
		update_LA_progress(db_conn,&info->m_LAList[i]);
	}
}

void DBHomeHandler::update_LA_progress( Connection *db_conn, LimitedActivityInfo *info )
{
	//_prep_stmt = db_conn->prepareStatement("insert into task_progress_tbl(character_id, task_progress) values(?, ?) on duplicate key update task_progress = ? ");
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("replace into limit_activity_tbl(character_id,limited_id,closetime,progress,dealtime,linktype,related_list) values(?,?,?,?,?,?,?)");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->unRelatedItems, sizeof(ACE_UINT32) * info->unRelatedCount);
	std::istream is(&data);

	_prep_stmt->setInt(1, m_unID);//用户id
	_prep_stmt->setInt(2,info->unLAID);//限时活动id
	_prep_stmt->setInt(3,info->unCloseTime);//关闭时间
	_prep_stmt->setInt(4,info->unProgress);//进度
	_prep_stmt->setInt(5,info->unDealTime);//最近处理时间
	_prep_stmt->setInt(6,info->unLinkType);
	_prep_stmt->setBlob(7, &is);
	//_prep_stmt->setBlob(3, &is);

	try
	{
		_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_LA_progress exception unID[%u]",__FILE__, __LINE__, m_unID);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::Deal_recharge_op_result( Connection *db_conn, OrderInfo *request )
{
	m_unMoney += request->unMoney;//更新钱
	m_unRechargeCount += 1;
	m_unRechargeAmount += request->unRenminbi;
	m_bitField = request->unbitfield;
}

void DBHomeHandler::CreatOneOrder( Connection *db_conn,MsgDBOrderRequest * request )
{
	MsgDBOrderResponse response;
	ZeroVar(response);
	GetNewOrderID(response.orderID);
	response.nResult = -1;
	response.unSN = request->unSN;
	response.unSig = request->unSig;

	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	//插入数据库
	_prep_stmt = db_conn->prepareStatement("insert into recharge_tbl(order_id,character_id,product_id,product_count,creat_time, state) values(?,?,?,?,?,?)");
	if(_prep_stmt != NULL)
	{

		_prep_stmt->setString(1, response.orderID);//订单号
		_prep_stmt->setInt(2,m_unID);//用户id
		_prep_stmt->setInt(3,request->product_id);//商品id
		_prep_stmt->setInt(4,request->product_count);//商品数量
		_prep_stmt->setInt(5,GameUtils::get_utc());//创建时间
		_prep_stmt->setInt(6,RECHARGE_STATE_FALSE);//状态
		//_prep_stmt->setBlob(3, &is);
		try
		{
			_prep_stmt->executeUpdate();
			response.nResult = 0;
			response.m_unID = m_unID;
		}
		catch (std::exception *e)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler CreatOneOrder exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);
	
	sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DB_ORDER_RESPONSE, (char *)&response, sizeof(MsgDBOrderResponse), OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unID);
	
	
	//by test 模拟订单完成请求
// 	MsgDBAdminRechargeRequest rechargeRequest;
// 	ZeroVar(rechargeRequest);
// 	memcpy(rechargeRequest.orderID,response.orderID,RECHARGE_ORDERID_LEN);
// 	rechargeRequest.unProductId = request->product_id;
// 	rechargeRequest.unProductCount = request->product_count;
// 	rechargeRequest.unPayStats =1;
// 	rechargeRequest.unCharacterID = m_unID;
// 	RechargeRes * res = (RechargeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(request->product_id);
// 	if (res)
// 	{
// 		rechargeRequest.unRenminbi = res->m_unPrice;
// 		rechargeRequest.deal_time[0] = '1';
// 		rechargeRequest.strChannel[0]='2';
// 	}
// 	sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_ADMINCOMMAND_RECHARGE_INFO_REQUEST, (char *)&rechargeRequest, sizeof(MsgDBAdminRechargeRequest), OBJ_ID_NONE, ADAPTER_DB_USER_MGR, m_unID);
	//------------------------end
	
}

void DBHomeHandler::GetNewOrderID( char * orderid )
{
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); // The GetLocalTime function retrieves the current local date and time
	sprintf(orderid, "%04d%04d%02d%02d%02d%02d%02d%03d%09d",ServiceConfigMgr::zone,sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond,sys.wMilliseconds,m_unID);
}

int DBHomeHandler::Load_ProductList( Connection *db_conn )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	int iReturn = -1;
	ZeroVar(m_Productlist);
	_prep_stmt = db_conn->prepareStatement("select product from product_tbl where character_id=?");
	if(_prep_stmt != NULL)
	{
		_prep_stmt->setInt(1, m_unID);
		_db_res = _prep_stmt->executeQuery();

		if(_db_res != NULL && _db_res->next())
		{
			std::istream *stream;
			stream = _db_res->getBlob("product");
			stream->read((char *)&m_Productlist, sizeof(ProductList));
		}
		iReturn = 0;
	}
	destroy_db_res(_prep_stmt,_db_res);
	return iReturn;
}

int DBHomeHandler::Load_monthCardTime( Connection *db_conn )
{
	m_monthTime = 0;
	int iReturn = -1;
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select end_time from month_card_tbl where character_id=?");
	if(_prep_stmt != NULL)
	{
		_prep_stmt->setInt(1, m_unID);
		_db_res = _prep_stmt->executeQuery();

		if(_db_res != NULL && _db_res->next())
		{
			m_monthTime = _db_res->getInt("end_time");//已经有月卡开启了 不需要更新 否则需要更新
		}
		iReturn = 0;
	}
	destroy_db_res(_prep_stmt,_db_res);

	return iReturn;
}

void DBHomeHandler::update_Vip_Gift_info( Connection *db_conn, MsgDBVipGiftInfo *info )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set vip_gift=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->m_vipGift.list, sizeof(ACE_UINT32)*info->m_vipGift.unCount);
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	try
	{
		_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_Vip_Gift_info sql exception unID[%u]",__FILE__, __LINE__, m_unID);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::update_friend_delete_list( Connection *db_conn, DeleteFriendList *info )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update friend_tbl set delete_list=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info, sizeof(DeleteFriendList));
	std::istream is(&data);

	_prep_stmt->setBlob(1, &is);
	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

int DBHomeHandler::Load_Badge( Connection * db_conn )
{
	m_mapBadge.clear();
	int iReturn = -1;
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select info from badge_tbl where character_id=?");
	if(_prep_stmt != NULL)
	{
		_prep_stmt->setInt(1, m_unID);
		_db_res = _prep_stmt->executeQuery();
		if (_db_res)
		{
			while(_db_res->next())
			{
				std::istream *stream = _db_res->getBlob("info");
				BadgeInfo badinfo;
				stream->read((char *)&badinfo, sizeof(BadgeInfo));
				m_mapBadge[badinfo.unID] = badinfo;
			}
		}

		iReturn = 0;
	}
	destroy_db_res(_prep_stmt,_db_res);

	return iReturn;
}

void DBHomeHandler::send_badge_progress( ObjAdr &desAdr )
{
	int n = m_mapBadge.size()*sizeof(BadgeInfo) + sizeof(ACE_UINT32);
	char * p = new char[n];
	memset(p,0,n);


	MsgDBBadgeList * response = (MsgDBBadgeList *)p;
	response->m_unCount = 0;
	std::map<ACE_UINT32, BadgeInfo>::const_iterator c_it = m_mapBadge.begin();
	while(c_it != m_mapBadge.end())
	{
		response->m_BadgeList[response->m_unCount] = c_it->second;
		response->m_unCount ++;
		c_it++;
	}

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_UPDATE_BADGE_PROGRESS_RESPONSE,(char *)response,n, desAdr, 0, false);
	delete []p;
}

void DBHomeHandler::update_Badge_progress( Connection *db_conn, BadgeInfo *info )
{
	//_prep_stmt = db_conn->prepareStatement("insert into task_progress_tbl(character_id, task_progress) values(?, ?) on duplicate key update task_progress = ? ");
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("replace into badge_tbl(character_id,badge_id,info) values(?,?,?)");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info, sizeof(BadgeInfo));
	std::istream is(&data);

	_prep_stmt->setInt(1, m_unID);//用户id
	_prep_stmt->setInt(2,info->unID);//徽章id
	_prep_stmt->setBlob(3, &is);
	//_prep_stmt->setBlob(3, &is);

	try
	{
		_prep_stmt->executeUpdate();
	}
	catch (std::exception *e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler update_Badge_progress exception unID[%u]",__FILE__, __LINE__, m_unID);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::send_props_list( ObjAdr &desAdr )
{
	MsgDBPropsListResponse *response = (MsgDBPropsListResponse *)db_send_buff;

	response->nResult = 0;
	response->unCount = m_propsList.size();
	if(m_propsList.size() != 0)
		ACE_OS::memcpy(response->list, &m_propsList[0], sizeof(PropsInfo) * response->unCount);
	int size = sizeof(PropsInfo) * response->unCount + sizeof(MsgDBPropsListResponse);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_PROPS_LIST,(char*)response, size, desAdr, 0, false);
}

int DBHomeHandler::load_props_list( Connection *db_conn )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res= NULL;
	m_propsList.resize(0);
	_prep_stmt = db_conn->prepareStatement("select list from props_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, m_unID);
	try
	{
		_db_res = _prep_stmt->executeQuery();
	}
	catch (std::exception &e)
	{
		_db_res = NULL;
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_props_list sql exception unID[%u],%s",__FILE__, __LINE__, m_unID,e.what());
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;
	while(_db_res->next())
	{
		try
		{
			m_propsList.clear();
			stream = _db_res->getBlob("list");
			PropsInfo temp;
			ZeroVar(temp);
			p = (char *)&temp;
			while(stream->read(p, sizeof(PropsInfo)))
			{
				m_propsList.push_back(temp);
				ZeroVar(temp);
			}
		}
		catch (...)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:DBHomeHandler load_props_list data handle exception unID[%u]",__FILE__, __LINE__, m_unID);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

void DBHomeHandler::update_props_list( Connection *db_conn, MsgDBUpdatePropsListRequest *info )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("replace into props_tbl(list,character_id) values(?,?)");
	if(_prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)info->list, sizeof(PropsInfo) * info->unCount);
	std::istream is(&data);
	_prep_stmt->setBlob(1, &is);

	_prep_stmt->setInt(2, m_unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

void DBHomeHandler::Get_BS_info( Connection *db_conn, BadgeShuxingS& infos,ACE_UINT32 unCharacterID )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("SELECT info FROM badge_info_tbl WHERE character_id = ?");
	if(_prep_stmt == NULL)
	{
		printf("Get_BS_info failed2!\n");
		return ;
	}
	_prep_stmt->setInt(1,unCharacterID);
	_db_res = _prep_stmt->executeQuery();

	if(_db_res->next())
	{
		std::istream *stream = _db_res->getBlob("info");
		char *p = (char *)&infos;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
	}
	destroy_db_res(_prep_stmt,_db_res);
}
