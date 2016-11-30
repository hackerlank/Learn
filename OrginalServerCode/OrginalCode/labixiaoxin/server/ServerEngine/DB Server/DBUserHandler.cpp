#include "DBUserHandler.h"
#include "..\GameBase\res\GameConfig.h"
#include "..\GameBase\res\MonsterRes.h"
#include "..\GameBase\res\ItemResMgr.h"
#include "..\GameBase\res\FunctionRes.h"
//#include "..\GameBase\res\MapResMgr.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
//#include "..\GameBase\res\QuestResMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"
#include "..\GameBase\res\ResInitMgr.h"
#include "..\GameBase\res\PlayerRes.h"
#include "..\GameBase\res\BasicPropertyRes.h"
#include "..\GameBase\res\GrowingRes.h"
#include "..\GameBase\res\EquipmentRes.h"
#include "..\GameBase\res\SkillRes.h"
#include "..\GameBase\res\ExtraSkillRes.h"
#include "..\GameBase\res\BehaviorRes.h"
#include "..\GameBase\res\RechargeRes.h"

ACE_UINT32 DBUserHandler::m_unUserInfoServerID = 0;

static bool isInitMapFlagList = false;
static MapFlagInfo initMapFlagList[MAX_MAP_COUNT];
static bool isInitSkillList = false;
static ACE_UINT32 initSkillList[MAX_SKILL_COUNT];
static bool isInitWeaponSkillList = false;
//static WeaponSkillInfo initWeaponSkillList[MAX_WEAPON_SKILL_COUNT];
static bool isInitFunctionList = false;
static ACE_UINT32 initFunctionList[MAX_FUNCTION_COUNT];

//static bool isInitCooldownList = false;
//CooldownInstanceInfo initCooldownList[MAX_COOLDOWN_INFO];

typedef struct tagCombatUnit
{
	ACE_UINT32 unUnitID;
	int original_property[PLAYER_PROPERTY_MAX];
	//int real_property[PLAYER_PROPERTY_MAX];
	//int property_range[PLAYER_PROPERTY_MAX][2];
	ACE_UINT32 unSkillID;
	ACE_UINT32 unPlayerSkillID;
}CombatUnit;


DBUserHandler::DBUserHandler(ACE_UINT32 unID, BaseAdapter *parent)
:DBHandler(unID, parent)
{
	ACE_OS::strcpy(m_strHandlerName, "user handler");

	if(m_unUserInfoServerID == 0)
	{
		m_unUserInfoServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Test User Info Server");
	}

	m_bDirty = true;
}

void DBUserHandler::do_db_load(Connection *db_conn)
{
	m_bLoadingSuccess = false;

	load_character_id(db_conn);

	m_bLoadingSuccess = true;
	m_bDirty = false;
}

void DBUserHandler::do_db_request(Connection *db_conn, MessageInfo &msgInfo)
{
	/*printf("%s deal db request[0x%08x]\n", m_strHandlerName, msgInfo.m_head->unType);*/
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	switch(msgInfo.m_head->unType)
	{
// 	case MSG_DB_LOG_INFO_REQUEST://日志请求 写入
// 		{
// 			MsgDBLogInfoRequest *request = (MsgDBLogInfoRequest*)msgInfo.body;
// 			DB_LOG_MGR_INSTANCE::instance()->write_db_log(request->logInfoItem,request->unCount);
// 		}
// 		break;
	case MSG_DB_ADMINCOMMAND_LOG_INFO_REQUEST://日志admin请求 查询
		{
			// 方法1
			MsgDBAdminLogInfoRequest * request = (MsgDBAdminLogInfoRequest *)msgInfo.body;
			request->m_srcAdr = msgInfo.s_head->srcAdr;

			//DB_LOG_MGR_INSTANCE::instance()->write_admin_db_log(request);
			//方法2
			// 			MsgDBAdminLogInfoResponse response;
			// 			if (DB_LOG_MGR_INSTANCE::instance()->ReadLogItems((MsgDBAdminLogInfoRequest *)msgInfo.body,response))
			// 			{
			// 				sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_ADMINCOMMAND_LOG_INFO_RESPONSE,(char*)&response, sizeof(MsgDBAdminLogInfoResponse), msgInfo.s_head->srcAdr, 0, false);
			// 			}
		}
		break;
	case MSG_DB_ADMINCOMMAND_RECHARGE_INFO_REQUEST://充值请求
		{
			MsgDBAdminRechargeRequest * request = (MsgDBAdminRechargeRequest *)msgInfo.body;
			MsgDBAdminRechargeResponse resbonse;
			ZeroVar(resbonse);
			memcpy(resbonse.orderID,request->orderID,RECHARGE_ORDERID_LEN);
			resbonse.unErrorflag = Recharge_request(db_conn,request,resbonse);
			sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_ADMINCOMMAND_RECHARGE_INFO_RESPONSE,(char*)&resbonse, sizeof(MsgDBAdminRechargeResponse), msgInfo.s_head->srcAdr, 0, false);
		}break;
	case MSG_DB_GET_ACCOUNT_INFO:
		{
			MsgDBGetAccountInfoRequest *request = (MsgDBGetAccountInfoRequest*)msgInfo.body;
			MsgDBAccountInfoResponse oAccountInfo;
			memset(&oAccountInfo,0,sizeof(MsgDBAccountInfoResponse));
			if(request->dwFindType == FIND_TYPE_BY_ACCOUNT_NAME || request->dwFindType == FIND_TYPE_BY_PLAYER_NAME)
			{
				oAccountInfo.nResult = load_basic_info(db_conn, request->dwFindType, request->name, oAccountInfo.m_oBasicInfos);
				if(oAccountInfo.nResult == 0)
				{
					oAccountInfo.nResult = load_items_list(db_conn, oAccountInfo.m_oBasicInfos.m_unCharacterID, oAccountInfo.m_oItemInfos);
					if(oAccountInfo.nResult == 0)
					{
						oAccountInfo.nResult = load_player_list(db_conn, oAccountInfo.m_oBasicInfos.m_unCharacterID, oAccountInfo.m_oPlayerInfos);
						//xxj 2015/04/23 16:37:00 
						if (oAccountInfo.nResult == 0)
						{
							//加载战力信息
							oAccountInfo.nResult = load_Point_info(db_conn, oAccountInfo.m_oBasicInfos.m_unCharacterID, oAccountInfo.m_oBasicInfos);
							if(oAccountInfo.nResult == 0)//加载技能信息
							{
								oAccountInfo.nResult = load_Skill_list(db_conn, oAccountInfo.m_oBasicInfos.m_unCharacterID, oAccountInfo.m_oBasicInfos);
							}
						}
						//---------------------------------------
					}
				}
				send_account_info(oAccountInfo, msgInfo.s_head->srcAdr);
			}
		}
		break;
	case MSG_DB_QUERY_ACCOUNT_LIST:
		{
			MsgDBQueryAccountListRequest *request = (MsgDBQueryAccountListRequest*)msgInfo.body;
			MsgDBQueryAccountListResponse oAccountList;
			if(request->dwFindType == FIND_TYPE_BY_ACCOUNT_NAME || request->dwFindType == FIND_TYPE_BY_PLAYER_NAME)
			{
				oAccountList.nResult = load_account_list(db_conn, request->dwFindType, request->name, oAccountList.m_oAccountList);
				sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_QUERY_ACCOUNT_LIST,(char*)&oAccountList, sizeof(MsgDBQueryAccountListResponse), msgInfo.s_head->srcAdr, 0, false);
			}
		}
		break;
	case MSG_ADMIN_OP_REQUEST:
		{
			deal_admin_op(db_conn, (MsgAdminOPRequest *)msgInfo.body, msgInfo.s_head->srcAdr);
		}
		break;
	case MSG_DB_QUERY_CHARACTER_INFO:
		{
			if(m_bDirty)
			{
				load_character_id(db_conn);
				m_bDirty = false;
			}

			send_character_list(msgInfo.s_head->srcAdr);
			m_bDirty = true;
		}
		break;
		/*
		case MSG_CHARACTER_NAME_UPDATE_REQUEST:
		{
		MsgCharacterNameUpdateRequest *body = (MsgCharacterNameUpdateRequest *)msgInfo.body;

		}
		break;
		*/
	case MSG_DB_CREATE_CHARACTER:
		{
			MsgDBCreateCharacterRequest *body = (MsgDBCreateCharacterRequest *)msgInfo.body;

			MsgDBCreateCharacterResponse info;

			info.nResult = create_character(db_conn, body->unCharacterID, body->name, body->unPlayerID);
			info.unCharacterID = body->unCharacterID;

			ACE_OS::memcpy(info.name, body->name, MAX_CHARACTER_LENGTH + 1);

#if 0 //add by guo
			MsgCharacterLevelUpdateRequest tmpInfo;
			tmpInfo.unCharacterID = m_unID;
			tmpInfo.unLevel = 1;
			this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_CHARACTER_LEVEL_UPDATE_REQUEST,(char *)&tmpInfo, sizeof(MsgCharacterLevelUpdateRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
#endif

			this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_CREATE_CHARACTER,(char *)&info, sizeof(MsgDBCreateCharacterResponse), msgInfo.s_head->srcAdr, 0, false);
		}
		break;
	case MSG_Update_Bitfield:
		{
			MsgDoBitFieldRequest * body = (MsgDoBitFieldRequest *)msgInfo.body;
			Bitfield bit = body->bitfield;
			UpdateBitfield(db_conn,body->unCharactID,bit);
			if (!(bit.monthCard & 0x1))
			{
				DoUpdateMonthCard(db_conn,body->unCharactID,0);//更新月卡数据
			}
		}break;

	case MSG_DESTROY_MSG_ACK:
		{
			this->set_destroy(true);
			//this->setObjStatus(SERVICE_OBJ_DESTROY);
			printf("db userHandler destroy obj：[%d]\n",m_unID);
		}break;

	default:
		break;
	}
}

void DBUserHandler::send_character_list(ObjAdr &adr)
{
	MsgDBQueryCharacterInfoResponse info;
	info.nResult = 0;
	ACE_OS::memcpy(info.list, m_CharacterList, sizeof(CharacterInfo) * MAX_PLAYER_PER_ACCOUNT);

	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_QUERY_CHARACTER_INFO,(char *)&info, sizeof(MsgDBQueryCharacterInfoResponse), adr, 0, false);
}

void DBUserHandler::update_cache(MessageInfo &msgInfo)
{
	switch(msgInfo.m_head->unType)
	{
	case MSG_DB_CREATE_CHARACTER:
		break;
	}
}

void DBUserHandler::load_character_id(Connection *db_conn)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select character_id,level,name,flag from character_tbl where user_id=? order by character_id");
	if(_prep_stmt == NULL)
	{
		return;
	}
	_prep_stmt->setInt(1, m_unID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return;
	}
	int c = 0;
	while(_db_res->next())
	{
		ACE_UINT32 unFlag = _db_res->getUInt("flag");
		m_CharacterList[c].unItemID = _db_res->getInt("character_id");
		m_CharacterList[c].unLevel = _db_res->getInt("level");
		if((unFlag & 0x1) != 0)
			m_CharacterList[c].unLevel = (ACE_UINT32)(-(int)m_CharacterList[c].unLevel);
		this->set_name(_db_res->getString("name"), m_CharacterList[c].name, MAX_CHARACTER_LENGTH);

		c ++;

		if(c >= MAX_PLAYER_PER_ACCOUNT)
		{
			break;
		}
	}

	destroy_db_res(_prep_stmt,_db_res);
}

int DBUserHandler::create_character(Connection *db_conn, ACE_UINT32 unID, char *name, ACE_UINT32 unPlayerID)
{
	/*
	_prep_stmt = db_conn->prepareStatement("insert into character_tbl(user_id,food,coin,money,exp,level,sex,last_login_time,login_bonus_count,character_name,create_time,time_data,energy_data) values(?,?,?,?,?,?,?,?,?,?,?,?,?)");
	if(_prep_stmt == NULL)
	{
	return;
	}

	EnergyInfo energyList[ENERGY_MAX];

	for(int i = 0;i < ENERGY_MAX;i ++)
	{
	energyList[i].unEnergy = 99999;
	energyList[i].unRestoreTime = 0;
	}

	DBDataBuf data((char *)energyList, sizeof(EnergyInfo) * ENERGY_MAX);
	std::istream is(&data);

	_prep_stmt->setInt(1, m_unID);
	_prep_stmt->setInt(2, GAME_CONFIG_INSTANCE::instance()->m_unInitFood);
	_prep_stmt->setInt(3, GAME_CONFIG_INSTANCE::instance()->m_unInitCoin);
	_prep_stmt->setInt(4, GAME_CONFIG_INSTANCE::instance()->m_unInitMoney);
	_prep_stmt->setInt(5, DEFAULT_CHARACTER_EXP);
	_prep_stmt->setInt(6, 0);
	_prep_stmt->setInt(7, 1);
	_prep_stmt->setUInt(8, 0);
	_prep_stmt->setInt(9, 0);
	_prep_stmt->setString(10, "init_name");
	_prep_stmt->setUInt(11, 0);
	_prep_stmt->setBlob(12, NULL);
	_prep_stmt->setBlob(13, &is);

	_prep_stmt->executeUpdate();
	destroy_db_res();
	*/

	int i;
	int idx = -1;

	for(i = 0;i < MAX_PLAYER_PER_ACCOUNT;i ++)
	{
		if(m_CharacterList[i].unItemID == unID)
		{
			idx = i;
			break;
		}
	}
	if(idx == -1)
	{
		return -1;
	}

	if(m_CharacterList[idx].unLevel != 0)
	{
		return 0;
	}

	for(i = 0;i < GAME_CONFIG_INSTANCE::instance()->m_unInitSelectPlayerCount;i ++)
	{
		if(unPlayerID == GAME_CONFIG_INSTANCE::instance()->m_InitSelectPlayerList[i])
		{
			break;
		}
	}

	if(i >= GAME_CONFIG_INSTANCE::instance()->m_unInitSelectPlayerCount)
	{
		return -1;
	}

	PlayerInfo tmp_player_list[MAX_PLAYER_COUNT];
	ACE_UINT32 player_selected_list[MAX_PLAYER_SELECTED_COUNT];

	ACE_OS::memset(player_selected_list, 0, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memset(tmp_player_list, 0, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);

	PlayerRes *tmpPlayerRes;

	for(i = 0;i < (GAME_CONFIG_INSTANCE::instance()->m_unInitPlayerCount + 1);i ++)
	{
		if(i == 0)
		{
			tmp_player_list[i].unItemID = unPlayerID;
		}
		else
		{
			tmp_player_list[i].unItemID = GAME_CONFIG_INSTANCE::instance()->m_InitPlayerList[i - 1];
		}


		tmp_player_list[i].unLevel = 1;
		tmp_player_list[i].unStep = 1;
		tmp_player_list[i].unSoulCount = 0;
		tmp_player_list[i].unPlayerSkillID = 0;

		tmpPlayerRes = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(tmp_player_list[i].unItemID);

		if(tmpPlayerRes == NULL)
		{
			return -1;
		}

		tmp_player_list[i].weapon.unResID = tmpPlayerRes->get_init_equipment(EQUIPMENT_TYPE_WEAPON);

		if(tmp_player_list[i].weapon.unResID != 0)
		{
			tmp_player_list[i].weapon.info.equipment.unLevel = 1;
			tmp_player_list[i].weapon.info.equipment.unStep = 1;
		}


		player_selected_list[i] = tmp_player_list[i].unItemID;
	}

	GameUtils::sort(GAME_CONFIG_INSTANCE::instance()->m_unInitPlayerCount + 1, tmp_player_list, sizeof(PlayerInfo));

	//DBDataBuf data((char *)&tmp_player_list, sizeof(PlayerInfo) * GAME_CONFIG_INSTANCE::instance()->m_unInitPlayerCount);
	DBDataBuf data((char *)&tmp_player_list, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	std::istream is(&data);

	/*
	PackageCell tmp_equipment_list[MAX_EQUIPMENT_COUNT];

	for(i = 0;i < MAX_EQUIPMENT_COUNT;i ++)
	{
	tmp_equipment_list[i].unIdx = i;
	tmp_equipment_list[i].item.item.unResID = GAME_CONFIG_INSTANCE::instance()->m_InitEquipmentList[i];
	tmp_equipment_list[i].item.unCount = 1;
	tmp_equipment_list[i].item.item.info.equipment.unLevel = 1;
	tmp_equipment_list[i].item.item.info.equipment.unStep = 1;
	}

	DBDataBuf data1((char *)&tmp_equipment_list, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);
	std::istream is1(&data1);
	*/

	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res  = NULL;

	_prep_stmt = db_conn->prepareStatement("update character_tbl set level=1,coin=?,power_point=0,honour=0,last_login_time=0,energy_restore_time=0,pvp_energy_restore_time=0,exp=0,name=?,package_max=?,recharge_count=0,recharge_amount=0,tutorial_flag=0,use_luck_count=0 where character_id=?");
	_prep_stmt->setInt(1, GAME_CONFIG_INSTANCE::instance()->m_unInitCoin);
	//_prep_stmt->setBlob(2, &is1);
	_prep_stmt->setString(2, name);
	_prep_stmt->setUInt(3, GAME_CONFIG_INSTANCE::instance()->m_packageExpandInfo.unMin);
	_prep_stmt->setUInt(4, unID);

	//int update_ret = _prep_stmt->executeUpdate();
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

	if(update_ret == -1)
	{
		return 1;
	}

	m_CharacterList[idx].unLevel = 1;

	//add map list
	init_map_flag_list();

	MapInstanceInfo tmp_instance;
	RewardInfo tmp_reward;
	//BattleSnapInfo tmp_snap_info;
	//MapBattleInfo tmp_battle_info;

	ACE_OS::memset(&tmp_instance, 0, sizeof(MapInstanceInfo));
	ACE_OS::memset(&tmp_reward, 0, sizeof(RewardInfo));
	//ACE_OS::memset(&tmp_snap_info, 0, sizeof(BattleSnapInfo));
	//ACE_OS::memset(&tmp_battle_info, 0, sizeof(MapBattleInfo));

	DBDataBuf data2((char *)&tmp_instance, sizeof(MapInstanceInfo));
	std::istream is2(&data2);

	DBDataBuf data3((char *)&tmp_reward, sizeof(RewardInfo));
	std::istream is3(&data3);

	DBDataBuf data4((char *)initMapFlagList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	std::istream is4(&data4);

	/*
	DBDataBuf data8((char *)&tmp_snap_info, sizeof(BattleSnapInfo));
	std::istream is8(&data8);

	DBDataBuf data9((char *)&tmp_battle_info, sizeof(MapBattleInfo));
	std::istream is9(&data9);
	*/

	//_prep_stmt = db_conn->prepareStatement("insert into map_tbl(character_id,current_map_info,current_reward,flag_list,last_reward_time,free_reborn_count,last_reborn_time) values(?,?,?,?,0,0,0)");
	// 	for (int i=0;i<100000;i++)
	// 	{
	// 		unID = i;
	_prep_stmt = db_conn->prepareStatement("insert into map_tbl(character_id,current_map_info,current_reward,last_reward_time,free_reborn_count,last_reborn_time) values(?,?,?,0,0,0)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->setBlob(2, &is2);
	_prep_stmt->setBlob(3, &is3);
	//_prep_stmt->setBlob(4, &is4);
	//_prep_stmt->setBlob(5, &is8);
	//_prep_stmt->setBlob(6, &is9);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
	//}
	// 	_prep_stmt = db_conn->prepareStatement("insert into map_tbl(character_id,current_map_info,current_reward,last_reward_time,free_reborn_count,last_reborn_time) values(?,?,?,0,0,0)");
	// 	_prep_stmt->setInt(1, unID);
	// 	_prep_stmt->setBlob(2, &is2);
	// 	_prep_stmt->setBlob(3, &is3);
	// 	//_prep_stmt->setBlob(4, &is4);
	// 	//_prep_stmt->setBlob(5, &is8);
	// 	//_prep_stmt->setBlob(6, &is9);
	// 
	// 	_prep_stmt->executeUpdate();
	//destroy_db_res();

	init_skill_list();

	DBDataBuf data5((char *)initSkillList, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);
	std::istream is5(&data5);

	_prep_stmt = db_conn->prepareStatement("insert into skill_tbl(character_id,skill_list) values(?,?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->setBlob(2, &is5);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	/*
	init_weapon_skill_list();

	DBDataBuf data6((char *)initWeaponSkillList, sizeof(WeaponSkillInfo) * MAX_WEAPON_SKILL_COUNT);
	std::istream is6(&data6);

	PropertyComponent tmp_improve_property[PROPERTY_ID_MAX];
	ACE_OS::memset(tmp_improve_property, 0, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
	DBDataBuf data11((char *)tmp_improve_property, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
	std::istream is11(&data11);

	_prep_stmt = db_conn->prepareStatement("insert into weapon_skill_tbl(character_id,list,improve_property) values(?,?,?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->setBlob(2, &is6);
	_prep_stmt->setBlob(3, &is11);

	_prep_stmt->executeUpdate();
	destroy_db_res();

	*/

	_prep_stmt = db_conn->prepareStatement("insert into friend_tbl(character_id,max_count) values(?,?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->setInt(2, 10);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	init_function_list();

	DBDataBuf data7((char *)initFunctionList, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);
	std::istream is7(&data7);

	_prep_stmt = db_conn->prepareStatement("insert into function_tbl(character_id,lock_list) values(?,?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->setBlob(2, &is7);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);


	GiftInfo tmp_gift_list[MAX_GIFT_COUNT];

	ACE_OS::memset(tmp_gift_list, 0, sizeof(GiftInfo) * MAX_GIFT_COUNT);

	DBDataBuf data10((char *)tmp_gift_list, sizeof(GiftInfo) * MAX_GIFT_COUNT);
	std::istream is10(&data10);

	_prep_stmt = db_conn->prepareStatement("insert into gift_tbl(character_id,gift_list) values(?,?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->setBlob(2, &is10);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	DBDataBuf data12((char *)player_selected_list, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	std::istream is12(&data12);

	ItemInfo staffInfo;
	ACE_OS::memset(&staffInfo, 0, sizeof(ItemInfo));

	tmpPlayerRes = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(TANG_MONK_ID);

	staffInfo.unResID = 0;//tmpPlayerRes->get_init_equipment(EQUIPMENT_TYPE_STAFF);

	if(staffInfo.unResID != 0)
	{
		staffInfo.info.equipment.unLevel = 1;
		staffInfo.info.equipment.unStep = 1;
	}

	DBDataBuf data14((char *)&staffInfo, sizeof(ItemInfo));
	std::istream is14(&data14);

	_prep_stmt = db_conn->prepareStatement("insert into player_tbl(character_id,list,selected_list,staff) values(?,?,?,?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->setBlob(2, &is);
	_prep_stmt->setBlob(3, &is12);
	_prep_stmt->setBlob(4, &is14);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	//init_cooldown_list();

	/*
	ResInitInfo *initInfo = RES_INIT_MGR_INSTANCE::instance()->get_inited_res(RES_INIT_COOLDOWN);
	DBDataBuf data13((char *)initInfo->data, initInfo->size);
	std::istream is13(&data13);
	*/

	_prep_stmt = db_conn->prepareStatement("insert into cooldown_tbl(character_id) values(?)");
	_prep_stmt->setInt(1, unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	_prep_stmt = db_conn->prepareStatement("insert into handbook_tbl(character_id) values(?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	_prep_stmt = db_conn->prepareStatement("insert into material_tbl(character_id) values(?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	_prep_stmt = db_conn->prepareStatement("insert into moneytree_tbl(character_id,level,exp) values(?,1,0)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	_prep_stmt = db_conn->prepareStatement("insert into pvp_tbl(character_id) values(?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	_prep_stmt = db_conn->prepareStatement("insert into character_tmp_tbl(character_id) values(?)");
	_prep_stmt->setInt(1, unID);
	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);

	return 0;

}

void DBUserHandler::init_map_flag_list()
{
	if(isInitMapFlagList)
	{
		return;
	}

	isInitMapFlagList = true;

	ACE_OS::memset(initMapFlagList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);

	ACE_UINT32 list[MAX_MAP_COUNT];
	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_MAP, 0, 0, 0, list, 1);

	for(int i = 0;i < c;i ++)
	{
		initMapFlagList[i].unMapID = list[i];
		initMapFlagList[i].unFlag = 0;
		initMapFlagList[i].unFlag2 = 0;

		//if(initMapFlagList[i].unMapID == GAME_CONFIG_INSTANCE::instance()->m_unInitUnlockMapID)
		if(initMapFlagList[i].unMapID == GET_ITEM_MASK_ID(GAME_CONFIG_INSTANCE::instance()->m_unInitUnlockMapID, 1))
		{
			//set unlock flag
			//initMapFlagList[i].unFlag = SET_MAP_UNLOCK(initMapFlagList[i].unFlag,1,1);
			initMapFlagList[i].unFlag = GameUtils::set_map_unlock_flag(initMapFlagList[i].unFlag,1,1);
		}
	}
}

void DBUserHandler::init_skill_list()
{
	if(isInitSkillList)
	{
		return;
	}

	isInitSkillList = true;

	ACE_OS::memset(initSkillList, 0, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);

	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_SKILL, 0, 0, 0, initSkillList, 2);
	for(int i = 0;i < c;i ++)
	{
		initSkillList[i] += 1;
	}
}

/*
void DBUserHandler::init_cooldown_list()
{
if(isInitCooldownList)
{
return;
}

isInitCooldownList = true;

ACE_OS::memset(initCooldownList, 0, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);

ACE_UINT32 list[320];

int j;
int type;
int count = 0;
for(j = 0;j < 2;j ++)
{
if(j == 0)
{
type = ITEM_RES_TYPE_MAP;
}
else
{
type = ITEM_RES_TYPE_BEHAVIOR;
}

int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(type, 0, 0, 0, list, 0);
for(int i = 0;i < c;i ++)
{
//initCooldownList[idx].unItemID = ;
BaseRes *res = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);

if(res == NULL)
{
continue;
}

if(res->m_cdInfo.unCD == 0)
{
continue;
}

int t = count;
int k = 0;

for(k = 0;k < count;k ++)
{
if(list[i] < initCooldownList[k].unItemID)
{
break;
}
}

for(int m = count;m > k;m --)
{
initCooldownList[m].unItemID = initCooldownList[m - 1].unItemID;
}

initCooldownList[k].unItemID = list[i];

count ++;
}
}



}
*/

/*
void DBUserHandler::init_weapon_skill_list()
{
if(isInitWeaponSkillList)
{
return;
}

isInitWeaponSkillList = true;

ACE_OS::memset(initWeaponSkillList, 0, sizeof(WeaponSkillInfo) * MAX_WEAPON_SKILL_COUNT);

ACE_UINT32 list[MAX_WEAPON_SKILL_COUNT];
int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_EQUIPMENT, 0, 0, 0, list, 0);
for(int i = 0;i < c;i ++)
{
initWeaponSkillList[i].unItemID = list[i];

int j;

for(j = 0;j < MAX_EQUIPMENT_COUNT;j ++)
{
if(list[i] == GAME_CONFIG_INSTANCE::instance()->m_InitEquipmentList[j])
{
break;
}
}

if(j >= MAX_EQUIPMENT_COUNT)
{
initWeaponSkillList[i].unLevel = 0;
}
else
{
initWeaponSkillList[i].unLevel = 1;
}
}
}
*/

void DBUserHandler::init_function_list()
{
	if(isInitFunctionList)
	{
		return;
	}

	isInitFunctionList = true;

	ACE_OS::memset(initFunctionList, 0, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);

	ACE_UINT32 list[MAX_FUNCTION_COUNT];
	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_FUNCTION, 0, 0, 0, list, 0);

	FunctionRes *res;
	int j = 0;

	for(int i = 0;i < c;i ++)
	{
		res = (FunctionRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);

		if(res == NULL || res->m_isLock == 0)
		{
			continue;
		}

		initFunctionList[j] = list[i];

		j ++;
	}
}

void DBUserHandler::deal_admin_op( Connection *db_conn, MsgAdminOPRequest *request, ObjAdr &targetAdr )
{
	//xxj 2015/04/22  12:15:49 
	switch(request->unOpType)
	{
		//case ADMIN_OP_TYPE_ADD_COIN:
		//	{
		//		AccountBasicInfos oAccountInfo;
		//		if(0 == load_basic_info(db_conn, request->unCharacterID, oAccountInfo))
		//		{
		//			oAccountInfo.m_unCoin += request->paramList[0];
		//			update_basic_info(db_conn, oAccountInfo);
		//		}
		//	}
		//	break;
		//case ADMIN_OP_TYPE_ADD_MONEY:
		//	{
		//		AccountBasicInfos oAccountInfo;
		//		if(0 == load_basic_info(db_conn, request->unCharacterID, oAccountInfo))
		//		{
		//			oAccountInfo.m_unMoney += request->paramList[0];
		//			update_basic_info(db_conn, oAccountInfo);
		//		}
		//	}
		//	break;
		//case ADMIN_OP_TYPE_ADD_PLAYER:
		//	{
		//		AccountPlayerInfos oAccountPlayerInfos;
		//		if(0 == load_player_list(db_conn, request->unCharacterID, oAccountPlayerInfos))
		//		{
		//			
		//		}
		//	}
		//	break;
		//case ADMIN_OP_TYPE_ADD_EQUIPMENT:
		//	{
		//		AccountItemInfos oAccountItemInfos;
		//		if(0 == load_items_list(db_conn, request->unCharacterID, oAccountItemInfos))
		//		{
		//		}
		//	}
		//	break;
	case ADMIN_OP_TYPE_DISABLE_ACCOUNT://封停
		{
			MsgDBUpdateCharacterFlagRequest rq;
			rq.unFlag = request->paramList[0];
			update_character_flag(db_conn, &rq,request->unCharacterID);
			if (request->unCharacterID > 0)//发送断开消息
			{
				MsgDestroyRequest info;
				info.unErrorCode = 1;
				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DESTROY_MSG_ACK, (char *)&info, sizeof(MsgDestroyRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, request->unCharacterID );//退出
			}
		}
		break;
	case ADMIN_OP_TYPE_ENABLE_ACCOUNT://解封
		{
			MsgDBUpdateCharacterFlagRequest rq;
			rq.unFlag = 0;
			update_character_flag(db_conn, &rq,request->unCharacterID);
		}
		break;
	default:
		break;
	}
}

void DBUserHandler::update_basic_info(Connection *db_conn, AccountBasicInfos &info)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set coin=?,money=?,exp=?,level=?,power_point=?,honour=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info.m_unCoin);
	_prep_stmt->setInt(2, info.m_unMoney);
	_prep_stmt->setInt(3, info.m_unExp);
	_prep_stmt->setInt(4, info.m_unLevel);
	_prep_stmt->setInt(5, info.m_unPowerPoint);
	_prep_stmt->setInt(6, info.m_unHonour);
	_prep_stmt->setInt(7, info.m_unCharacterID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

int DBUserHandler::load_basic_info(Connection *db_conn, int type, const std::string& rstrName, AccountBasicInfos& roAccountBasicInfo)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL; 
	if(type == FIND_TYPE_BY_ACCOUNT_NAME)
	{
		bool bFindAt = false;
		for(int i = 0; i != rstrName.length(); i++)
		{
			if(rstrName[i] == '@')
			{
				bFindAt = true;
				break;
			}
		}

		//添加时间 create_time
		if(bFindAt)
			_prep_stmt = db_conn->prepareStatement("select name,mac,email,level,exp,coin,money,last_login_time,login_bonus_count,login_count,energy,energy_restore_time,power_point,honour,recharge_count,recharge_amount,package_max,tutorial_flag,use_luck_count,character_id,create_time,user_tbl.channel_id FROM character_tbl INNER JOIN user_tbl ON character_tbl.user_id = user_tbl.user_id where email = ?");
		else
			_prep_stmt = db_conn->prepareStatement("select name,mac,email,level,exp,coin,money,last_login_time,login_bonus_count,login_count,energy,energy_restore_time,power_point,honour,recharge_count,recharge_amount,package_max,tutorial_flag,use_luck_count,character_id,create_time,user_tbl.channel_id FROM character_tbl INNER JOIN user_tbl ON character_tbl.user_id = user_tbl.user_id where mac = ?");
	}
	else
	{
		_prep_stmt = db_conn->prepareStatement("select name,mac,email,level,exp,coin,money,last_login_time,login_bonus_count,login_count,power_point,honour,recharge_count,recharge_amount,package_max,tutorial_flag,use_luck_count,character_id,create_time,user_tbl.channel_id FROM character_tbl INNER JOIN user_tbl ON character_tbl.user_id = user_tbl.user_id where name = ?");
	}
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setString(1, rstrName.c_str());
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	//std::istream *stream;
	//char *p;
	int c = 0;

	//m_unPlayerCount = 0;

	if(_db_res->next())
	{
		roAccountBasicInfo.m_unCharacterID = _db_res->getInt("character_id");
		roAccountBasicInfo.m_unLevel = _db_res->getInt("level");
		roAccountBasicInfo.m_unExp = _db_res->getInt("exp");
		roAccountBasicInfo.m_unCoin = _db_res->getInt("coin");
		roAccountBasicInfo.m_unMoney = _db_res->getInt("money");
		roAccountBasicInfo.m_unHonour = _db_res->getInt("honour");
		roAccountBasicInfo.m_unLastLoginTime = _db_res->getInt("last_login_time");
		roAccountBasicInfo.m_unLoginBonusCount = _db_res->getInt("login_bonus_count");
		roAccountBasicInfo.m_unLoginCount = _db_res->getInt("login_count");
		roAccountBasicInfo.m_unEnergy = _db_res->getInt("energy");
		roAccountBasicInfo.m_unEnergyRestoreTime = _db_res->getUInt("energy_restore_time");
// 		roAccountBasicInfo.m_unPVPEnergy = _db_res->getInt("pvp_energy");
// 		roAccountBasicInfo.m_unPVPEnergyRestoreTime = _db_res->getUInt("pvp_energy_restore_time");
		//m_unBuyEnergyTime = _db_res->getInt("buy_energy_time");
		//m_unBuyEnergyCount = _db_res->getInt("buy_energy_count");
		roAccountBasicInfo.m_unPowerPoint = _db_res->getInt("power_point");//晶石
		roAccountBasicInfo.m_unRechargeCount = _db_res->getInt("recharge_count");
		roAccountBasicInfo.m_unRechargeAmount = _db_res->getInt("recharge_amount");
		roAccountBasicInfo.m_unPackageMax = _db_res->getInt("package_max");
		roAccountBasicInfo.m_unTutorialFlag = _db_res->getInt("tutorial_flag");
		roAccountBasicInfo.m_unUseLuckCount = _db_res->getInt("use_luck_count");
		roAccountBasicInfo.m_unCreateTime = _db_res->getInt("create_time");//xxj 2015/04/23  11:30:26 创建时间
		roAccountBasicInfo.m_unChannel = _db_res->getInt("channel_id");//渠道

		set_name(_db_res->getString("name"), roAccountBasicInfo.m_PlayerName, MAX_CHARACTER_LENGTH);
		set_name(_db_res->getString("mac"), roAccountBasicInfo.m_mac, MAX_ACCOUNT_LENGTH);
		set_name(_db_res->getString("email"), roAccountBasicInfo.m_email, MAX_EMAIL_LENGTH);


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
	else
	{
		return -1;
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBUserHandler::load_basic_info( Connection *db_conn, int dwCharchterID, AccountBasicInfos& roAccountBasicInfo )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select name,level,exp,coin,money,last_login_time,login_bonus_count,login_count,energy,energy_restore_time,power_point,honour,recharge_count,recharge_amount,package_max,tutorial_flag,use_luck_count,character_id FROM character_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, dwCharchterID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	//std::istream *stream;
	//char *p;
	int c = 0;

	//m_unPlayerCount = 0;

	if(_db_res->next())
	{
		roAccountBasicInfo.m_unCharacterID = _db_res->getInt("character_id");
		roAccountBasicInfo.m_unLevel = _db_res->getInt("level");
		roAccountBasicInfo.m_unExp = _db_res->getInt("exp");
		roAccountBasicInfo.m_unCoin = _db_res->getInt("coin");
		roAccountBasicInfo.m_unMoney = _db_res->getInt("money");
		roAccountBasicInfo.m_unHonour = _db_res->getInt("honour");
		roAccountBasicInfo.m_unLastLoginTime = _db_res->getInt("last_login_time");
		roAccountBasicInfo.m_unLoginBonusCount = _db_res->getInt("login_bonus_count");
		roAccountBasicInfo.m_unLoginCount = _db_res->getInt("login_count");
		roAccountBasicInfo.m_unEnergy = _db_res->getInt("energy");
		roAccountBasicInfo.m_unEnergyRestoreTime = _db_res->getUInt("energy_restore_time");
// 		roAccountBasicInfo.m_unPVPEnergy = _db_res->getInt("pvp_energy");
// 		roAccountBasicInfo.m_unPVPEnergyRestoreTime = _db_res->getUInt("pvp_energy_restore_time");
		//m_unBuyEnergyTime = _db_res->getInt("buy_energy_time");
		//m_unBuyEnergyCount = _db_res->getInt("buy_energy_count");
		roAccountBasicInfo.m_unPowerPoint = _db_res->getInt("power_point");
		roAccountBasicInfo.m_unRechargeCount = _db_res->getInt("recharge_count");
		roAccountBasicInfo.m_unRechargeAmount = _db_res->getInt("recharge_amount");
		roAccountBasicInfo.m_unPackageMax = _db_res->getInt("package_max");
		roAccountBasicInfo.m_unTutorialFlag = _db_res->getInt("tutorial_flag");
		roAccountBasicInfo.m_unUseLuckCount = _db_res->getInt("use_luck_count");
		set_name(_db_res->getString("name"), roAccountBasicInfo.m_PlayerName, MAX_CHARACTER_LENGTH);

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
	else
	{
		return -1;
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBUserHandler::load_items_list( Connection *db_conn, int dwCharchterID, AccountItemInfos& roAccountItemInfos )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select idx,item_id,count,info from items_tbl where character_id=? order by idx");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, dwCharchterID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	int idx;

	roAccountItemInfos.m_unItemsCount = 0;

	while(_db_res->next())
	{
		idx = _db_res->getInt("idx");
		roAccountItemInfos.m_itemsList[idx].unIdx = idx;
		roAccountItemInfos.m_itemsList[idx].item.item.unResID = _db_res->getInt("item_id");
		roAccountItemInfos.m_itemsList[idx].item.unCount = _db_res->getInt("count");
		stream = _db_res->getBlob("info");
		p = (char *)&roAccountItemInfos.m_itemsList[idx].item.item.info;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		roAccountItemInfos.m_unItemsCount ++;
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

int DBUserHandler::load_player_list( Connection *db_conn, int dwCharchterID, AccountPlayerInfos& roAccountPlayerInfos )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select list,selected_list,staff,player_skill_list from player_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, dwCharchterID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;

	ACE_OS::memset(roAccountPlayerInfos.m_playerList, 0, sizeof(PlayerInfo) * MAX_PLAYER_COUNT);
	ACE_OS::memset(roAccountPlayerInfos.m_selectedPlayerList, 0, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);
	ACE_OS::memset(&roAccountPlayerInfos.m_staff, 0, sizeof(ItemInfo));
	ACE_OS::memset(roAccountPlayerInfos.m_selectedPlayerSkillList, 0, sizeof(ACE_UINT32) * MAX_PLAYER_SELECTED_COUNT);

	while(_db_res->next())
	{
		stream = _db_res->getBlob("list");
		p = (char *)roAccountPlayerInfos.m_playerList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("selected_list");
		p = (char *)roAccountPlayerInfos.m_selectedPlayerList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("staff");
		p = (char *)&roAccountPlayerInfos.m_staff;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}

		stream = _db_res->getBlob("player_skill_list");
		p = (char *)roAccountPlayerInfos.m_selectedPlayerSkillList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

void DBUserHandler::send_account_info( MsgDBAccountInfoResponse &info, ObjAdr &desAdr )
{
	sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_GET_ACCOUNT_INFO,(char*)&info, sizeof(MsgDBAccountInfoResponse), desAdr, 0, false);
}

int DBUserHandler::load_account_list( Connection *db_conn, int type, const std::string& rstrName, AccountBriefInfoList& roAccountList )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	if(type == FIND_TYPE_BY_ACCOUNT_NAME)
	{
		_prep_stmt = db_conn->prepareStatement(("select name,mac,email,character_id FROM character_tbl INNER JOIN user_tbl ON character_tbl.user_id = user_tbl.user_id where email like '%" + rstrName + "%'").c_str());

	}
	else
	{
		_prep_stmt = db_conn->prepareStatement(("select name,mac,email,character_id FROM character_tbl INNER JOIN user_tbl ON character_tbl.user_id = user_tbl.user_id where name like '%" + rstrName + "%'").c_str());
	}
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	//std::istream *stream;
	//char *p;
	int c = 0;

	//m_unPlayerCount = 0;

	ACE_OS::memset(&roAccountList.m_oBriefInfos, 0, sizeof(AccountBriefInfo) * MAX_ACCOUNT_BRIEF_INFO_LEN);

	for(roAccountList.m_AccountCount = 0; _db_res->next() && roAccountList.m_AccountCount < MAX_CHARACTER_LENGTH; roAccountList.m_AccountCount++)
	{
		roAccountList.m_oBriefInfos[roAccountList.m_AccountCount].m_unCharacterID = _db_res->getInt("character_id");
		set_name(_db_res->getString("name"), roAccountList.m_oBriefInfos[roAccountList.m_AccountCount].m_PlayerName, MAX_CHARACTER_LENGTH);
		set_name(_db_res->getString("mac"), roAccountList.m_oBriefInfos[roAccountList.m_AccountCount].m_mac, MAX_ACCOUNT_LENGTH);
		set_name(_db_res->getString("email"), roAccountList.m_oBriefInfos[roAccountList.m_AccountCount].m_email, MAX_EMAIL_LENGTH);
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

void DBUserHandler::update_character_flag( Connection *db_conn, MsgDBUpdateCharacterFlagRequest *info ,ACE_UINT32 unID)
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set account_flag=? where character_id=?");
	if(_prep_stmt == NULL)
	{
		return;
	}

	_prep_stmt->setInt(1, info->unFlag);
	_prep_stmt->setInt(2, unID);

	_prep_stmt->executeUpdate();
	destroy_db_res(_prep_stmt,_db_res);
}

//xxj 2015/04/23 17:22:21 加载战力信息
int DBUserHandler::load_Point_info( Connection *db_conn, int dwCharchterID, AccountBasicInfos& roAccountBasicInfo )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select team_info from character_tmp_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, dwCharchterID);
	_db_res = _prep_stmt->executeQuery();
	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	if(_db_res != NULL)
	{
		if(_db_res->next())
		{
			CharacterInfoExt info;
			stream = _db_res->getBlob("team_info");
			stream->read((char *)&info.pveTeam, sizeof(PlayerTeamInfo));
			//			pvp没有用到
			// 			stream = _db_res->getBlob("pvp_team_info");
			// 			stream->read((char *)&info.pvpTeam, sizeof(PlayerTeamInfo));
			build_property(&info.pveTeam);
			roAccountBasicInfo.m_unPoint = info.pveTeam.unPoint;//得到数据
		}
	}

	destroy_db_res(_prep_stmt,_db_res);

	return 0;
}

void DBUserHandler::build_property( PlayerTeamInfo * pteamInfo )
{
	int i, j;

	PropertyComponent allList[PLAYER_PROPERTY_MAX];
	PropertyComponent singleList[PLAYER_PROPERTY_MAX];

	ACE_OS::memset(allList, 0, sizeof(PropertyComponent) * PLAYER_PROPERTY_MAX);

	CombatUnit unitList[MAX_PLAYER_SELECTED_COUNT];
	ACE_OS::memset(unitList, 0, sizeof(CombatUnit) * MAX_PLAYER_SELECTED_COUNT);

	int c = 0;
	pteamInfo->unCount = 0;
	pteamInfo->unPoint = 0;

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(pteamInfo->playerList[i].unItemID == 0)
		{
			break;
		}

		//build property

		ACE_OS::memset(singleList, 0, sizeof(PropertyComponent) * PLAYER_PROPERTY_MAX);

		add_player_property(singleList, &pteamInfo->playerList[i]);

		unitList[i].unUnitID = pteamInfo->playerList[i].unItemID;
		unitList[i].unSkillID = pteamInfo->skillList[i];
		//m_unitList[i].unPlayerSkillID = m_teamInfo->playerList[i].unPlayerSkillID;
		unitList[i].unPlayerSkillID = pteamInfo->playerSkillList[i];

		for(j = 0;j < PLAYER_PROPERTY_MAX;j ++)
		{
			unitList[i].original_property[j] = (int)((allList[j].unValue + singleList[j].unValue) * (1000 + allList[j].unScale + singleList[j].unScale) / 1000);
		}

		int s = GET_ITEM_ID_INFO(unitList[i].unSkillID, 0, 2);
		//int tmp_point = ((10 + s) * m_unitList[i].original_property[PLAYER_PROPERTY_ATTACK] + 5 * m_unitList[i].original_property[PLAYER_PROPERTY_HP] + 4 * m_unitList[i].original_property[PLAYER_PROPERTY_DEFENSE] + 3 * m_unitList[i].original_property[PLAYER_PROPERTY_CRITICAL]) / 10;
		int tmp_point = (unitList[i].original_property[PLAYER_PROPERTY_ATTACK] * 5 + s * 30 * (1 + s * 7 / 60) +
			unitList[i].original_property[PLAYER_PROPERTY_HP] * 4 + unitList[i].original_property[PLAYER_PROPERTY_DEFENSE] * 3 +
			unitList[i].original_property[PLAYER_PROPERTY_CRITICAL] * 3) / 10;

		pteamInfo->unPoint += tmp_point;

		c ++;
	}

	pteamInfo->unCount = c;
}

void DBUserHandler::add_player_property( PropertyComponent *componentList, PlayerInfo *player )
{
	PlayerRes * playerRes = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(player->unItemID);

	if(playerRes == NULL)
	{
		return;
	}

	BasicPropertyRes *basicRes = (BasicPropertyRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(playerRes->m_unBasicPropertyID);
	GrowingRes *growingRes = (GrowingRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(playerRes->m_unGrowingID);

	if(basicRes == NULL || growingRes == NULL)
	{
		return;
	}

	add_equipment_property(componentList, &player->weapon);
	add_equipment_property(componentList, &player->armor);
	add_equipment_property(componentList, &player->belt);
	add_equipment_property(componentList, &player->staff);

	int i;
	for(i = 0;i < PLAYER_PROPERTY_MAX;i ++)
	{
		componentList[i].unValue += (basicRes->m_valueList[i] + growingRes->m_valueList[i] * (player->unLevel - 1));
	}
}

void DBUserHandler::add_equipment_property( PropertyComponent *componentList, ItemInfo *equipment )
{	
	EquipmentRes *res = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(equipment->unResID);

	if(res == NULL)
	{
		return;
	}

	int i;

	for(i = 0;i < PLAYER_PROPERTY_MAX;i ++)
	{
		componentList[i].unValue += (res->m_propertyList[i].unValue + res->m_improvePropertyList[i].unValue * (equipment->info.equipment.unLevel - 1));
		componentList[i].unScale += (res->m_propertyList[i].unScale + res->m_improvePropertyList[i].unScale * (equipment->info.equipment.unLevel - 1));
	}

}

int DBUserHandler::load_Skill_list( Connection *db_conn, int dwCharchterID, AccountBasicInfos& roAccountPlayerInfos )
{
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select skill_list from skill_tbl where character_id=?");
	if(_prep_stmt == NULL)
	{
		return -1;
	}
	_prep_stmt->setInt(1, dwCharchterID);
	_db_res = _prep_stmt->executeQuery();

	if(_db_res == NULL)
	{
		return -1;
	}

	std::istream *stream;
	char *p;
	//int idx;

	ACE_UINT32 skillList[MAX_SKILL_COUNT];
	ACE_OS::memset(skillList, 0, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);

	while(_db_res->next())
	{
		stream = _db_res->getBlob("skill_list");
		p = (char *)skillList;
		while(stream->read(p, sizeof(char)))
		{
			p ++;
		}
	}

	//得到详细结果
	for (int i=0;i<MAX_SKILL_COUNT;i++)
	{
		if (skillList[i]>0)
		{
			int type = GET_ITEM_TYPE(skillList[i]);
			switch(type)
			{
			case ITEM_RES_TYPE_SKILL:
				{
					SkillRes * pSkillRes = (SkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(skillList[i]);
					if (pSkillRes)
					{
						roAccountPlayerInfos.m_skillList[i].skillID = skillList[i];
						roAccountPlayerInfos.m_skillList[i].skillLevel = pSkillRes->m_unSkillLevel;
						memcpy(roAccountPlayerInfos.m_skillList[i].m_strName,pSkillRes->m_strName,MAX_ITEM_NAME);
					}
				}
				break;
			case ITEM_RES_TYPE_EXTRA_SKILL://附加技能表中查找
				{
					ExtraSkillRes * pExtraSkillRes = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(skillList[i]);
					if(pExtraSkillRes)
					{
						roAccountPlayerInfos.m_skillList[i].skillID = skillList[i];
						roAccountPlayerInfos.m_skillList[i].skillLevel = pExtraSkillRes->m_unSkillLevel;
						memcpy(roAccountPlayerInfos.m_skillList[i].m_strName,pExtraSkillRes->m_strName,MAX_ITEM_NAME);
					}
				}
				break;
			default:
				break;
			}
		}
		else
			break;
	}

	//---------------------------


	destroy_db_res(_prep_stmt,_db_res);

	return 0;


}

void DBUserHandler::SendAdminLogItem( const MsgDBAdminLogInfoResponse & response ,const ObjAdr & _srcAdr)
{
	ObjAdr srcAdr = _srcAdr;
	sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_ADMINCOMMAND_LOG_INFO_RESPONSE,(char*)&response, sizeof(MsgDBAdminLogInfoResponse), srcAdr, 0, false);
}

int DBUserHandler::Recharge_request( Connection *db_conn, const MsgDBAdminRechargeRequest * request,MsgDBAdminRechargeResponse & response )
{
	OrderInfo orderinfo;//订单信息
	memcpy(orderinfo.orderID,request->orderID,RECHARGE_ORDERID_LEN);

	int iReturn = GetOrderInfo(db_conn,orderinfo);
	RechargeRes * res = NULL;

	if (iReturn >= 0)//初步成功
	{
		//商品id检测
		if(orderinfo.unProductId != request->unProductId)//商品id不一致
			iReturn =RECHARGE_ORDER_ProductId_ERROR;
		else if (orderinfo.unProductCount != request->unProductCount)
			iReturn = RECHARGE_ORDER_ProductCount_ERROR;
		else
		{
			res = (RechargeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(orderinfo.unProductId);
			if(!res)
				iReturn = RECHARGE_ORDER_Product_NOT_EXIST;
			else if (res->m_unPrice > request->unRenminbi)//实际金额不对
				iReturn = RECHARGE_ORDER_Renminbi_ERROR;
		}
	}

	if (iReturn >= 0)//初步成功
	{
		if (orderinfo.unCharacterID == request->unCharacterID && request->unPayStats == 1)//充值成功
		{
			ACE_ASSERT(res != NULL);
			orderinfo.unProductCount = request->unProductCount;//商品数量
			orderinfo.unMoney = res->m_reward.unMoney + res->m_gift_card;//金币直接更新，其它稍后更新
			orderinfo.unFlagEx = res->m_gift_card;
			orderinfo.unProductId = request->unProductId;
			orderinfo.state = RECHARGE_STATE_FLAG;
			orderinfo.unRenminbi = request->unRenminbi;
			
			//发送充值附件
			ConfigReward reward = res->m_reward;
			reward.unMoney = 0;//金币直接更新，其它稍后更新
			MailInfo oMailInfo;
			ZeroVar(oMailInfo);
			if (GetMailInfo(oMailInfo,reward,orderinfo.unCharacterID,FRIENDSHIP_MAIL_LIMITED_ACTIVITE))
				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_USER_INFO_ADD_MAIL, (char *)&oMailInfo, sizeof(MailInfo), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);//添加邮件
			//-------------------------end

			//添加邮件消息
			Bitfield bitfield;
			bool isFirst = false;
			if (DoRechargeAction(db_conn,orderinfo,res->m_unSubType,bitfield))//是首充
			{
				isFirst = true;
				orderinfo.unMoney *= 2;//首充翻倍
			}
			orderinfo.unbitfield = bitfield.GetValue();
			//--------------------------end


			//--------加入数据库
			PreparedStatement *_prep_stmt = NULL;
			ResultSet *_db_res = NULL;
			_prep_stmt = db_conn->prepareStatement("update recharge_tbl set deal_time=?,money=?,rmb=?,channel_id=?,state=? where order_id=?");
			if(_prep_stmt == NULL)
				return RECHARGE_ORDER_ERROR;

			_prep_stmt->setString(1,request->deal_time);
			_prep_stmt->setInt(2,orderinfo.unMoney);
			_prep_stmt->setInt(3,orderinfo.unRenminbi);
			_prep_stmt->setString(4,request->strChannel);
			_prep_stmt->setInt(5,orderinfo.state);
			_prep_stmt->setString(6,orderinfo.orderID);
			_prep_stmt->executeUpdate();
			destroy_db_res(_prep_stmt,_db_res);
			//-----------------------end

			//立即更新到在线用户身上
			sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_RECHARGE_REQUEST, (char *)&orderinfo, sizeof(OrderInfo), OBJ_ID_NONE, ADAPTER_DB_HOME_MGR, orderinfo.unCharacterID);
			sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_RECHARGE_REQUEST, (char *)&orderinfo, sizeof(OrderInfo), OBJ_ID_NONE, ADAPTER_MAP_MGR, orderinfo.unCharacterID);
			sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ADMIN_OP_RECHARGE_REQUEST, (char *)&orderinfo, sizeof(OrderInfo), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);

			//更新钱到数据库里面
			_prep_stmt = db_conn->prepareStatement("update character_tbl set money=money + ?,recharge_count = recharge_count+1,recharge_amount = recharge_amount + ? where character_id=?");
			if(_prep_stmt == NULL)
				return RECHARGE_ORDER_ERROR;

			_prep_stmt->setInt(1,orderinfo.unMoney);
			_prep_stmt->setInt(2,orderinfo.unRenminbi);
			_prep_stmt->setInt(3,orderinfo.unCharacterID);
			_prep_stmt->executeUpdate();
			destroy_db_res(_prep_stmt,_db_res);
			//--------------------------------------end

			//写入日志
			//--------------------注册
			LogItemInfo info;
			info.m_unUserID = GetUserID(db_conn,orderinfo.unCharacterID);
			info.m_charactID = orderinfo.unCharacterID;
			info.m_goodsID = orderinfo.unProductId;
			if(isFirst)//是否是首充
			{
				info.m_op_action = enum_LOG_ACTION::LOG_ACTION_FIRST_RECHARGE;
				info.SetOp_Way(orderinfo.orderID);
			}
			else
			{
				info.m_op_action = enum_LOG_ACTION::LOG_ACTION_RECHARGE;
				info.SetOp_Way(orderinfo.orderID);
			}
			info.m_unType = LOG_TYPE_RECHARGE;
			info.m_op_after = orderinfo.unRenminbi;
			info.m_op_time = GameUtils::get_utc();
			DBUserHandler::SendLogInfoItemMSG(info,orderinfo.unCharacterID,this);
			//------------------------------end
			//---------------------------end
		}
		else if(request->unPayStats != 1)
			iReturn = RECHARGE_ORDER_PayState_ERROR;
		else
			iReturn = RECHARGE_ORDER_USER_ID_ERROR;
	}

	return iReturn;
}

int DBUserHandler::GetOrderInfo( Connection *db_conn, OrderInfo & info )
{
	char zone[5];
	zone[4] = '\0';
	memcpy(zone,info.orderID,4);
	int nZone = atoi(zone);
	if(nZone != ServiceConfigMgr::zone)//检查分区号
		return RECHARGE_ORDER_ZONE_ERROR;

	int ireturn = RECHARGE_ORDER_NOT_EXIST;

	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res= NULL;
	_prep_stmt = db_conn->prepareStatement("select character_id,creat_time,state,product_id,product_count from recharge_tbl where order_id=?");
	if(_prep_stmt == NULL)
	{
		return RECHARGE_ORDER_ERROR;
	}
	_prep_stmt->setString(1, info.orderID);
	_db_res = _prep_stmt->executeQuery();

	if(_db_res != NULL)
	{
		if(_db_res->next())
		{
			info.unCharacterID = _db_res->getInt("character_id");
			info.creat_time = _db_res->getInt("creat_time");
			info.state = _db_res->getInt("state");
			info.unProductId = _db_res->getInt("product_id");//商品id
			info.unProductCount = _db_res->getInt("product_count");//商品数量

			if (info.state != RECHARGE_STATE_FALSE)
				ireturn = RECHARGE_ORDER_COMPLETED;
			else
				ireturn = RECHARGE_ORDER_SUCCESS;
		}
		else
		{
			ireturn = RECHARGE_ORDER_NOT_EXIST;
		}
	}
	else
	{
		return RECHARGE_ORDER_ERROR;
	}

	destroy_db_res(_prep_stmt,_db_res);

	return ireturn;
}

bool DBUserHandler::DoRechargeAction( Connection *db_conn,const OrderInfo & info,ACE_UINT32 type,Bitfield & bitfield )
{
	GetBitfield(db_conn,info.unCharacterID,bitfield);
	bool isUpdate = false;
	bool isFirst = false;
	if (type == RechargeRes_type_monthcard)//月卡
	{
		if (DoCheckMonthCard(db_conn,info))
		{
			isUpdate = true;
			bitfield.monthCard = 1;
			ACE_UINT32 _time = GameUtils::Get_current_day_0_0();
			_time += 24*60*60 -1 + 30*(24*60*60);//当天23点59分59秒 后继30天
			DoUpdateMonthCard(db_conn,info.unCharacterID,_time);//更新月卡数据
			send_month_card(info.unCharacterID);//首先发送一封
		}
	}

	if (!isUpdate)//有月卡就不记录首充值
	{
		isFirst = DoRechargeMail(db_conn,info,bitfield);//首充邮件
		isUpdate = (isUpdate || isFirst);
	}


	if (isUpdate)
		UpdateBitfield(db_conn,info.unCharacterID,bitfield);

	return isFirst;
}

bool DBUserHandler::DoRechargeMail( Connection *db_conn,const OrderInfo & info,Bitfield & bitfield )
{
	if (!(bitfield.firstRecharge & 0x1))//没有领取
	{
		MailInfo oMailInfo;
		ZeroVar(oMailInfo);
		if (GetMailInfo(oMailInfo,info.unCharacterID,FIRST_RECHARGE_REWARD_ID))
		{
			//添加邮件
			sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_USER_INFO_ADD_MAIL, (char *)&oMailInfo, sizeof(MailInfo), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
			//--------------------------------------
			bitfield.firstRecharge = 0x1;//首充标记

			return true;
		}
	}

	return false;
}

bool DBUserHandler::GetBitfield( Connection *db_conn,ACE_UINT32 unCharacterID,Bitfield & bitfield )
{
	bool iReturn = false;
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select bitfield from character_tbl where character_id=?");
	if(_prep_stmt != NULL)
	{
		_prep_stmt->setInt(1, unCharacterID);
		_db_res = _prep_stmt->executeQuery();

		if(_db_res != NULL && _db_res->next())
		{
			bitfield = _db_res->getInt("bitfield");
			iReturn = true;
		}
	}
	destroy_db_res(_prep_stmt,_db_res);

	return iReturn;
}

bool DBUserHandler::UpdateBitfield( Connection *db_conn,ACE_UINT32 unCharacterID,const Bitfield & bitfield )
{
	//更新到数据库里面
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("update character_tbl set bitfield = ? where character_id=?");
	if(_prep_stmt)
	{
		_prep_stmt->setInt(1,bitfield.GetValue());
		_prep_stmt->setInt(2,unCharacterID);
		_prep_stmt->executeUpdate();
	}
	destroy_db_res(_prep_stmt,_db_res);
	//--------------------------------------end
	return true;
}

bool DBUserHandler::DoCheckMonthCard( Connection *db_conn,const OrderInfo & info )
{
	bool iReturn = true;
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("select end_time from month_card_tbl where character_id=?");
	if(_prep_stmt != NULL)
	{
		_prep_stmt->setInt(1, info.unCharacterID);
		_db_res = _prep_stmt->executeQuery();

		if(_db_res != NULL && _db_res->next())
		{
			ACE_UINT32 end_time = _db_res->getInt("end_time");
			if (end_time >= GameUtils::get_utc())//已经有月卡开启了 不需要更新 否则需要更新
				iReturn  = false;
		}
	}
	destroy_db_res(_prep_stmt,_db_res);

	return iReturn;
}

bool DBUserHandler::DoUpdateMonthCard( Connection *db_conn,ACE_UINT32 unCharacterID,ACE_UINT32 _time )
{
	//更新到数据库里面
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("replace into month_card_tbl(end_time , character_id) values(?, ?)");
	if(_prep_stmt)
	{
		_prep_stmt->setInt(1,_time);
		_prep_stmt->setInt(2,unCharacterID);
		_prep_stmt->executeUpdate();
	}
	destroy_db_res(_prep_stmt,_db_res);
	//--------------------------------------end
	return true;
}

bool DBUserHandler::GetMailInfo( MailInfo & oMailInfo,ACE_UINT32 unCharacterID,ACE_UINT32 unid )
{
	BehaviorRes *res = (BehaviorRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unid);//开始首充奖励
	if (res)
	{
		oMailInfo.m_dwIDinTable = FRIENDSHIP_MAIL_FIRST_RECHARGE;
		oMailInfo.m_dwCharacterID = unCharacterID;
		oMailInfo.m_dwTimeoutDate = GameUtils::get_utc()/* + (7 * 24 * 3600)*/;

		int n = 0;
		if (res->m_reward.unCoin > 0)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_COIN;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unCoin;
			n++;
		}
		if (res->m_reward.unMoney > 0)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_MONEY;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unMoney;
			n++;
		}
		if (res->m_reward.unExp > 0)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_EXP;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unExp;
			n++;
		}
		if (res->m_reward.unPowerPoint > 0)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_POWERPOINT;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unPowerPoint;
			n++;
		}
		if (res->m_reward.unHonour > 0)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_HONOUR;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unHonour;
			n++;
		}
		if (res->m_reward.unRecharge > 0 && n<MAIL_ATTACHMENT_LEN)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_RECHARGE;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unRecharge;
			n++;
		}
		if (res->m_reward.unEnergy > 0 && n<MAIL_ATTACHMENT_LEN)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_ENERGY;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unEnergy;
			n++;
		}
		if (res->m_reward.unPVPEnergy > 0 && n<MAIL_ATTACHMENT_LEN)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_PVP_ENERGY;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unPVPEnergy;
			n++;
		}
		if (res->m_reward.unFriendship > 0 && n<MAIL_ATTACHMENT_LEN)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_FRIENDSHIP;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.unFriendship;
			n++;
		}
		for (int i=0;i<res->m_reward.unCount && n<MAIL_ATTACHMENT_LEN;i++,n++)
		{
			oMailInfo.m_aMailAttachment[n].m_dwItemID = res->m_reward.list[i].unResID;
			oMailInfo.m_aMailAttachment[n].m_dwItemCount = res->m_reward.list[i].unCount;
		}
		return true;
	}

	return false;
}

bool DBUserHandler::GetMailInfo( MailInfo & oMailInfo,ConfigReward & reward,ACE_UINT32 unCharacterID,ACE_UINT32 unMailId )
{

	oMailInfo.m_dwIDinTable = unMailId;
	oMailInfo.m_dwCharacterID = unCharacterID;
	oMailInfo.m_dwTimeoutDate = GameUtils::get_utc()/* + (7 * 24 * 3600)*/;

	int n = 0;
	if (reward.unCoin > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_COIN;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unCoin;
		n++;
	}
	if (reward.unMoney > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_MONEY;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unMoney;
		n++;
	}
	if (reward.unExp > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_EXP;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unExp;
		n++;
	}
	if (reward.unPowerPoint > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_POWERPOINT;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unPowerPoint;
		n++;
	}
	if (reward.unHonour > 0)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_HONOUR;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unHonour;
		n++;
	}
	if (reward.unRecharge > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_RECHARGE;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unRecharge;
		n++;
	}
	if (reward.unEnergy > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_ENERGY;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unEnergy;
		n++;
	}
	if (reward.unPVPEnergy > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_PVP_ENERGY;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unPVPEnergy;
		n++;
	}
	if (reward.unFriendship > 0 && n<MAIL_ATTACHMENT_LEN)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = RES_CURRENCY_FRIENDSHIP;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.unFriendship;
		n++;
	}

	for (int i=0;i<reward.unCount && n<MAIL_ATTACHMENT_LEN;i++,n++)
	{
		oMailInfo.m_aMailAttachment[n].m_dwItemID = reward.list[i].unResID;
		oMailInfo.m_aMailAttachment[n].m_dwItemCount = reward.list[i].unCount;
	}


	return n>0;
}

void DBUserHandler::send_month_card( ACE_UINT32 unCharacterID )
{
	MsgSendMonthCardRequest db_request;
	db_request.m_dwCharacterID = unCharacterID;
	db_request.m_unTime = GameUtils::get_utc();

	this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_SEND_MONTH_CARD, (char *)&db_request, 
		sizeof(db_request), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
}

void DBUserHandler::SendLogInfoItemMSG( LogItemInfo & ver,ACE_UINT32 unUserID,DBHandler * handle)
{
	MsgDBLogInfoRequest request;
	ZeroVar(request);
	request.unCount = 1;
	request.logInfoItem[0] = ver;
	handle->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DB_LOG_INFO_REQUEST, (char *)&request, 
		sizeof(MsgDBLogInfoRequest), DBUserHandler::m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
	//DB_LOG_MGR_INSTANCE::instance()->write_db_log(request.logInfoItem,request.unCount);
	// 	//发送日志信息
	// 	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, MSG_DB_LOG_INFO_REQUEST, (char *)&request, sizeof(MsgDBLogInfoRequest),
	// 	OBJ_ID_NONE, ADAPTER_DB_USER_MGR, unUserID);
}

ACE_UINT32 DBUserHandler::GetUserID( Connection *db_conn,ACE_UINT32 characterID )
{
	ACE_UINT32 user_id = 0;
	//更新到数据库里面
	PreparedStatement *_prep_stmt = NULL;
	ResultSet *_db_res = NULL;
	_prep_stmt = db_conn->prepareStatement("SELECT user_id FROM character_tbl WHERE character_id = ?");
	if(_prep_stmt)
	{
		_prep_stmt->setInt(1,characterID);
		_db_res = _prep_stmt->executeQuery();
		
		if(_db_res != NULL)
		{
			if(_db_res->next())
			{
				user_id = _db_res->getInt("user_id");
			}
		}

	}
	destroy_db_res(_prep_stmt,_db_res);
	//--------------------------------------end
	return user_id;
}

// int DBUserHandler::Get_Announcement_info( Connection *db_conn,MsgDBAdminAnnouncementRequest *response,MsgAnnouncementRequest * request)
// {
// 	response->m_unOpType = request->unTypeID;
// 
// 	_prep_stmt = db_conn->prepareStatement("select type, info from gm_tbl where type = ?");
// 	if(_prep_stmt == NULL)
// 	{
// 		return -1;
// 	}
// 	_prep_stmt->setInt(1, response->m_unOpType);
// 	_db_res = _prep_stmt->executeQuery();
// 
// 	if(_db_res == NULL)
// 	{
// 		return -1;
// 	}
// 
// 	if(_db_res->next())
// 	{
// 		SQLString str = _db_res->getString();
// 		char * dest = response->m_strBuffer;
// 		const char *t = str.c_str();
// 		if(t == NULL)
// 		{
// 			response->m_strBuffer[0] = '\0';
// 		}
// 		else
// 		{
// 			ACE_OS::strncpy( response->m_strBuffer, t, MAX_ADMIN_OP_BUFFER_ANNOUNCEMENT_LENGTH);
// 			response->m_strBuffer[MAX_ADMIN_OP_BUFFER_ANNOUNCEMENT_LENGTH] = '\0';
// 		}
// 	}
// 
// 	destroy_db_res();
// 	return 0;
// }
