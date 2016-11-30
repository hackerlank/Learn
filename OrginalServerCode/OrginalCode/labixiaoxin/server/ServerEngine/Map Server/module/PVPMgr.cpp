#include "PVPMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\Map.h"

PVPMgr::PVPMgr()
{
	m_unRestoreAmount= GAME_CONFIG_INSTANCE::instance()->m_oHonorRankConfig.amount;
	m_unRestoreInterval = GAME_CONFIG_INSTANCE::instance()->m_oHonorRankConfig.attack_times;
	m_oldHonour = -1;
	m_buy_pvp_limit = 0;
	isEnter = false;
	m_scheme_arena = GAME_CONFIG_INSTANCE::instance()->m_oSchemeInfo.m_scheme_arena;
}

void PVPMgr::init( PVPInfo & info )
{
	m_pvpInfo = info;
	//m_pvpInfo.unFreshenCount = 0;
	update();
}

void PVPMgr::update( ACE_UINT32 unCurrentTime )
{
	if (m_pvpInfo.unAttackTimes >= m_unRestoreAmount)
	{
		return ;
	}

	int t= unCurrentTime - m_pvpInfo.unLastChangeTime;
	int c = (int)(t/m_unRestoreInterval);
	if (c>0)
	{
		int m = (int)(t % m_unRestoreInterval);

		m_pvpInfo.unAttackTimes += c;

		if(m_pvpInfo.unAttackTimes >= m_unRestoreAmount)
		{
			m_pvpInfo.unAttackTimes = m_unRestoreAmount;
		}

		m_pvpInfo.unLastChangeTime = unCurrentTime - m;

		update_Info_2_db(false);
	}
}

void PVPMgr::update()
{
	update(GameUtils::get_utc());
}

void PVPMgr::update_Info_2_db(bool isToUserServer)
{

	int weakDay = GameUtils::get_week(GameUtils::get_utc());
	int dayTime = GameUtils::get_day_time(GameUtils::get_utc());
	if (dayTime > DAY_TIME_SETTLE_START && dayTime <= DAY_TIME_SETTLE_END && weakDay == 0)//23点30分 ~ 0点为结算时间
	{
		return;
	}

	MsgDBUpdatePVPInfoResquest db_request;
	db_request.info = m_pvpInfo;

	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_PVP_INFO, (char *)&db_request, sizeof(MsgDBUpdatePVPInfoResquest));

// 不必更新了后面会更新的
	if (false/*isToUserServer*/ && m_pvpInfo.nhonour >= 0 && m_oldHonour != m_pvpInfo.nhonour )//更新竞技场荣誉值
	{
		m_oldHonour = m_pvpInfo.nhonour;
		HLInfo info;
		info.m_characterID = m_map->m_unID;
		info.m_honour = m_pvpInfo.nhonour;
		update_honour(info);
	}
}

void PVPMgr::update_honour( HLInfo & info )
{
	MsgDBUpdatePVPInfoResquestEx request;
	request.info = info;

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DB_UPDATE_PVP_INFO, 
		(char *)&request, sizeof(MsgDBUpdatePVPInfoResquestEx), m_map->m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);//更新任务
}

void PVPMgr::update_pvp_Info( PVPInfoEx & info )
{
	if (info.nhonour < 0)
	{
		m_pvpInfo.unLastChangeTime = 0;
		m_pvpInfo.nhonour = GAME_CONFIG_INSTANCE::instance()->m_oHonorRankConfig.init_honor;
	}
	else if (m_pvpInfo.nhonour != info.nhonour)
	{
		m_pvpInfo.nhonour = info.nhonour;
	}

	update();

	info.unLastChangeTime = m_pvpInfo.unLastChangeTime;
	info.unAttackTimes = m_pvpInfo.unAttackTimes;
	info.unWinLost = m_pvpInfo.unWinLost;
	info.unBuyCount = m_pvpInfo.unBuyCount;
	info.unFreshenCount = m_pvpInfo.unFreshenCount;
}

void PVPMgr::EnterPVPFight( HLInfoArray & _array)
{
	m_array = _array;
}

void PVPMgr::OnDo()
{
	update();
	//更新进入
	if (m_pvpInfo.nhonour < 0)
	{
		m_pvpInfo.nhonour = GAME_CONFIG_INSTANCE::instance()->m_oHonorRankConfig.init_honor;
		m_pvpInfo.unFreshenCount = 0;
		update_Info_2_db(true);
	}
}

bool PVPMgr::DoFreashen()
{
	if (m_pvpInfo.unFreshenCount < 2)//减次数
	{
		//m_pvpInfo.unFreshenCount++;
		m_pvpInfo.unFreshenCount;
		update_Info_2_db(false);
		return true;
	}

	return false;
}

void PVPMgr::update_TimesMax( ACE_UINT32 nMax,bool is )
{
	m_buy_pvp_limit =nMax;
}

int PVPMgr::BuyTimes()
{
	update();
	if(m_pvpInfo.unBuyCount >= m_buy_pvp_limit)
		return ERROR_MSG_PVP_MAX;
	else
	{
		ACE_UINT32 money = GAME_CONFIG_INSTANCE::instance()->m_oHonorCost[m_pvpInfo.unBuyCount+1];

		CostInfoList cost;
		ZeroVar(cost);
		cost.unCount = 1;
		cost.list[0].unID = RES_CURRENCY_MONEY;//消耗金卡值
		cost.list[0].cost = money;
		if (m_map->is_cost_enough(cost, 1))
		{
			//-----------log日志
			//操作
			LogItemInfo logInfo;
			logInfo.m_goodsID = RES_CURRENCY_MONEY;
			logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_PVP_TIMES_up;//动作原因
			logInfo.SetOp_Way(_LOG_OP_WAY_PVP_TIMES_up);//途径(附加信息)
			m_map->do_cost(cost, 1,logInfo);
			m_pvpInfo.unBuyCount++;
			m_pvpInfo.unAttackTimes++;
			update_Info_2_db(false);
			return 0;
		}
		else
			return ERROR_MSG_COST;

	}
}

int PVPMgr::EnterMap()
{
	int weakDay = GameUtils::get_week(GameUtils::get_utc());
	int dayTime = GameUtils::get_day_time(GameUtils::get_utc());
	if (dayTime > DAY_TIME_SETTLE_START && dayTime <= DAY_TIME_SETTLE_END && weakDay == 0)//23点30分 ~ 0点为结算时间
	{
		return ERROR_MSG_ACCOUNTS_TIME;
	}

	update();
	if (m_pvpInfo.unAttackTimes>0)//检测成功 能进入
	{
		isEnter = true;
		m_pvpInfo.unAttackTimes --;
		update_Info_2_db(true);

		return 0;
	}
	else
		return ERROR_MSG_TIMES;
	
}

void PVPMgr::DoDayChange()
{
// 	m_pvpInfo.unAttackTimes = m_unRestoreAmount;
// 	m_pvpInfo.unLastChangeTime = GameUtils::get_utc();
 	m_pvpInfo.unBuyCount = 0;
// 	m_pvpInfo.unFreshenCount = 0;
	update_Info_2_db(false);
}

int PVPMgr::AccountsMap( FightRecordInfo & info,ACE_INT32 & score )
{
	info.score = 0;
	score = 0;
	//先找到要打的对象信息
	int index = -1;
	for(int i=0;i<m_array.uncount;i++)
	{
		if (m_array.playerinfo[i].unItemID == info.to.m_characterID)//找到了
		{
			index = i;
			break;
		}
	}

	if (index < 0){
		return ERROR_MSG_OBJ_NULL;
	}
	else{
		const HonorRankInfo & honorRankConfig = GAME_CONFIG_INSTANCE::instance()->m_oHonorRankConfig;
		if (info.isWin > 0)//胜利
		{
			//基础荣誉* [1/(1+10^[(挑战者当前积分-被挑战者当前积分)/荣誉系数])]
			score = honorRankConfig.base_honor_point*(1.0/(1+std::pow(10,((m_pvpInfo.nhonour-m_array.m_array[index].m_honour)/(float)honorRankConfig.honor_modulus))));
			info.score = score;
			m_pvpInfo.nhonour += score;
			ACE_UINT32 win = (m_pvpInfo.unWinLost & 0x0FFFF) + 1; 
			ACE_UINT32 lost = (((m_pvpInfo.unWinLost)>>16)& 0x0FFFF);
			m_pvpInfo.unWinLost = ((lost<<16) | win);
		}
		else//失败
		{
			ACE_UINT32 win = (m_pvpInfo.unWinLost & 0x0FFFF); 
			ACE_UINT32 lost = (((m_pvpInfo.unWinLost)>>16)& 0x0FFFF) + 1;
			m_pvpInfo.unWinLost = ((lost<<16) | win);
		}

		//初始化对方的基础信息
		info.to.m_characterID = m_array.playerinfo[index].unItemID;
		info.to.m_level = m_array.playerinfo[index].unLevel;
		std::memcpy(info.to.name,m_array.playerinfo[index].name,MAX_CHARACTER_LENGTH + 1);
		info.to.m_honour = m_array.m_array[index].m_honour;

		//初始化自己的基础信息
		info.from.m_characterID = m_map->m_unID;
		info.from.m_level = m_map->m_unLevel;
		std::memcpy(info.from.name,m_map->m_strName,MAX_CHARACTER_LENGTH + 1);
		info.from.m_honour = m_pvpInfo.nhonour;

		//更新到userinfo
		FightRecordInfoEx infoEx;
		infoEx.info = info;
		infoEx.isRoobt = m_array.m_array[index].isRobt;
		m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PVP_ACCOUNTS_RESPONSE, 
			(char *)&infoEx, sizeof(FightRecordInfoEx), m_map->m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
		//---------------------------------end

		//默认刷新一次
		MsgPVPEnterFightRequest request;
		request.unSN = 0;
		request.m_characterID = m_map->m_unID;
		request.isReFreash = 2;
		GetQuitList(request.quitList);
		m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PVP_ENTER_FIGHT_REQUEST, 
			(char *)&request, sizeof(MsgPVPEnterFightRequest), m_map->m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);

		m_pvpInfo.unFreshenCount = 0;
		update_Info_2_db(false);//必须放到最后更新
		return 0;
	}
}

void PVPMgr::GetQuitList( HLInfo *list )
{
	for (int i=0;i<m_array.uncount;i++)
	{
		list[i] = m_array.m_array[i];
	}
}
