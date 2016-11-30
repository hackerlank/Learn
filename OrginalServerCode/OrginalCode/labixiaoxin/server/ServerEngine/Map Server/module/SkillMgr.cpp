#include "SkillMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\..\GameBase\res\PlayerRes.h"
#include "..\..\GameBase\res\ExtraSkillRes.h"

SkillMgr::SkillMgr()
{
	m_unSkillCount = 0;
	m_unBookResCount = 0;
	m_unPlayerSkillCount = 0;
 	int c;
 	for(c = 0; c < MAX_PLAYER_SKILL_COUNT; c++){//初始化书本列表，数据库里面暂时没有信息，暂时存0
 		m_bookRes[c].unCount = 0;
 		m_bookRes[c].unId = 0;
 	}
}

SkillMgr::~SkillMgr()
{

}

void SkillMgr::init(ACE_UINT32 *list, ACE_UINT32 *playerSkillList,SkillBook *bookRes)
//void SkillMgr::init(ACE_UINT32 *list, ACE_UINT32 *playerSkillList)
{
	ACE_OS::memcpy(m_list, list, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);
	ACE_OS::memcpy(m_playerSkillList, playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SKILL_COUNT);
	ACE_OS::memcpy(m_bookRes, bookRes, sizeof(SkillBook) * MAX_PLAYER_SKILL_COUNT);
	m_unSkillCount = 0;
	m_unPlayerSkillCount = 0;
	m_unBookResCount = 0;

	parse();

	if(m_map->m_unLevel == 1)
	{
		ExtraSkillRes *skill_res_0 = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(GAME_CONFIG_INSTANCE::instance()->m_teamLevel[m_map->m_unLevel].extraskill_learn);
		if(NULL != skill_res_0)
		{
			m_list[m_unSkillCount++] = GAME_CONFIG_INSTANCE::instance()->m_teamLevel[m_map->m_unLevel].extraskill_learn;
			add_player_skill(GAME_CONFIG_INSTANCE::instance()->m_teamLevel[m_map->m_unLevel].extraskill_learn);
			update_2_db();
		}
	}
}

void SkillMgr::parse()
{
	m_unSkillCount = 0;
	for(int i = 0;i < MAX_SKILL_COUNT;i ++)
	{
		if(m_list[i] == 0)
		{
			break;
		}

		m_unSkillCount ++;
	}
	
	m_unPlayerSkillCount = 0;
	for(int i = 0;i < MAX_PLAYER_SKILL_COUNT;i ++)
	{
		if(m_playerSkillList[i] == 0)
		{
			break;
		}

		m_unPlayerSkillCount ++;
	}
	m_unBookResCount = 0;
	for(int i = 0;i < MAX_PLAYER_SKILL_COUNT;i ++)
	{
		if(m_bookRes[i].unId == 0)
		{
			break;
		}

	m_unBookResCount ++;
	}
}

void SkillMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgSkillListResponse response;
	response.nResult = 0;
	response.unSN = unSN;

	response.unCount = m_unSkillCount;
	ACE_OS::memcpy(response.skillList, m_list, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);

	response.unPlayerSkillCount = m_unPlayerSkillCount;
	ACE_OS::memcpy(response.playerSkillList, m_playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SKILL_COUNT);

	response.unBookResCount = m_unBookResCount;
	ACE_OS::memcpy(response.bookRes,m_bookRes,sizeof(SkillBook)*MAX_PLAYER_SKILL_COUNT);//这种能直接memcpy么，待测，结构体

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_SKILL_LIST_RESPONSE, (char *)&response, sizeof(MsgSkillListResponse), targetAdr);
}

int SkillMgr::level_up(ACE_UINT32 unSkillID, int dwLevelAdd,ACE_UINT32 & unDynamicEnergy)
{
	int i;
	int  n;
	int ret = -1;
	//-----------log 日志
	//技能升级
	LogItemInfo logInfo;
	logInfo.m_goodsID = unSkillID;//装备id
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_level_up;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_level_up);//途径(附加信息)
	m_map->SetlogUserInfo(logInfo);
	std::vector<LogItemInfo> logver;
	//-------------------------------------------

	unDynamicEnergy = 0;

	for(i = 0;i < m_unSkillCount;i ++)
	{
		//if((unSkillID / 100) == (m_list[i] / 100))
		//if(GET_ITEM_ID_INFO(unSkillID, 0, 2) == GET_ITEM_ID_INFO(m_list[i], 0, 2))
		if(GET_ITEM_MASK_ID(unSkillID, 2) == GET_ITEM_MASK_ID(m_list[i], 2))
		{
			/*
			m = unSkillID % 100;
			n = m_list[i] % 100;

			if(n < MAX_SKILL_LEVEL && m == (n + 1))
			{
				ret = 0;

				m_list[i] = unSkillID;

				MsgDBUpdateSkillListRequest db_request;
				ACE_OS::memcpy(db_request.skillList, m_list, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);

				m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_SKILL_LIST, (char *)&db_request, sizeof(MsgDBUpdateSkillListRequest));
			}
			*/
			//n = m_list[i] % 100;
			n = GET_ITEM_ID_INFO(m_list[i], 0, 2);

			if(n + dwLevelAdd <= MAX_SKILL_LEVEL )//技能需要判断
			{
				int price = 0;
				for(int lv = n; lv != n + dwLevelAdd; lv++)
					price += (int)GAME_CONFIG_INSTANCE::instance()->m_unSkillPriceList[lv - 1];

				if(m_map->m_unDynamicEnergy >= price)
				{
					bool bIsSuperSkill = false;	//是否为超人技能
					for(int j = 0; j != MAX_PLAYER_SKILL_COUNT; j++)
					{
						if(GET_ITEM_MASK_ID(m_list[i], 2) == GET_ITEM_MASK_ID(m_playerSkillList[j], 2))
						{
							if(m_map->m_unLevel < n + dwLevelAdd)
								return ERROR_MSG_PARAMETER;
							m_playerSkillList[j] += dwLevelAdd;
							bIsSuperSkill = true;
							break;
						}
					}

					if(bIsSuperSkill)
					{
						for(int j = 0; j != MAX_PLAYER_SELECTED_COUNT; j++)
						{
							if(GET_ITEM_MASK_ID(m_list[i], 2) == GET_ITEM_MASK_ID(m_map->m_playerMgr.m_playerSkillList[j], 2))
							{
								m_map->m_playerMgr.m_playerSkillList[j] += dwLevelAdd;
								m_map->m_playerMgr.update_2_db();
								break;
							}
						}
					}
					else
					{
						for(int j = 0; j != m_map->m_playerMgr.m_unPlayerCount; j++)
						{
							PlayerRes *res = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(m_map->m_playerMgr.m_list[j].unItemID);
							if(res == NULL)
								return ERROR_MSG_RES;
							if(GET_ITEM_MASK_ID(m_list[i], 2) == GET_ITEM_MASK_ID(res->m_unSkillID, 2))
							{
								int start = GetSkillStart(m_map->m_playerMgr.m_list[j].unItemID,m_map->m_playerMgr.m_list[j].unStep);
								if(/*m_map->m_playerMgr.m_list[j].unStep*/start * 10 < n + dwLevelAdd)
									return -1;
								break;
							}
						}
					}

					//log日志文件
					logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_Dynamic_Energy_lower;
					logInfo.m_op_before = m_map->m_unDynamicEnergy;
					logInfo.m_op_after = m_map->m_unDynamicEnergy - price;
					logver.push_back(logInfo);
					logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_skill_up;
					logInfo.m_op_before = m_list[i];
					logInfo.m_op_after = m_list[i] + dwLevelAdd;
					logver.push_back(logInfo);
					//-------------

					m_list[i] = m_list[i] + dwLevelAdd;
					m_map->set_basic_info(0, 0, 0, 0, 0,0,-price);
					unDynamicEnergy = price;
					ret = 0;
					update_2_db();
				}
				else
					ret = ERROR_MSG_COST;
			}

			break;
		}
	}

	if(ret == 0)
	{
		m_map->dispatch_map_event(GAME_EVENT_PVE_TEAM_UPDATE);
		m_map->m_taskMgr.RefreshTask(Event_Base_Type_EnhanceSkill,0);
		m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_EnhanceSkill,0);

		m_map->SendLogInfoItemMSG(logver);//log日志
	}

	return ret;
}

ACE_UINT32 SkillMgr::get_skill_id(ACE_UINT32 unSkillID)
{
	int i;
	for(i = 0;i < m_unSkillCount;i ++)
	{
		//if((unSkillID / 100) == (m_list[i] / 100))
		int m = GET_ITEM_MASK_ID(unSkillID, 2);
		int n = GET_ITEM_MASK_ID(m_list[i], 2);
		if(m == n)
		{
			return m_list[i];
		}
	}

	return 0;
}

bool SkillMgr::has_player_skill(ACE_UINT32 unPlayerSkillID)
{
	int i;

	for(i = 0;i < m_unPlayerSkillCount;i ++)
	{
		if(m_playerSkillList[i] == unPlayerSkillID)
		{
			return true;
		}
	}

	return false;
}

/*
int SkillMgr::get_player_skill(ACE_UINT32 unPlayerSkillID)
{
	int i;

	for(i = 0;i < m_unPlayerSkillCount;i ++)
	{
		if(m_playerSkillList[i] == unPlayerSkillID)
		{
			return i;
		}
	}

	return -1;
}
*/

void SkillMgr::add_player_skill(ACE_UINT32 unPlayerSkillID)
{
	if(m_unPlayerSkillCount >= MAX_PLAYER_SKILL_COUNT)
	{
		return;
	}

	int i,in = 0;//in==1表示在人物技能列表中需要加入图纸表m_bookres，==0表示不在m_playerSkillList


	for(i = 0;i < m_unPlayerSkillCount;i ++)
	{
		if(m_playerSkillList[i] == unPlayerSkillID)
		{
//			return;
			in = 1;
			int c,flag = 0;//0表示没在列表中找到，需要新加入列表
			for(c = 0; c < m_unBookResCount; c++){
				if(unPlayerSkillID == m_bookRes[c].unId){
					m_bookRes[c].unCount++;
					flag = 1;//列表中有
					break;
				}
			}
			if(0 == flag){//列表中没有
				m_bookRes[m_unBookResCount].unId = unPlayerSkillID;
				m_bookRes[m_unBookResCount].unCount++;//初始要设置为0
				m_unBookResCount++;
			}
			
		}
	
	}
	if(in == 0){ //技能栏里面没有该技能
		m_playerSkillList[m_unPlayerSkillCount] = unPlayerSkillID;
		m_unPlayerSkillCount ++;
	}





	/*
	if(idx == -1)
	{
		if(unPlayerSkillID == 0)
		{
			return;
		}

		if(m_unPlayerSkillCount >= MAX_PLAYER_SKILL_COUNT)
		{
			return;
		}

		m_playerSkillList[m_unPlayerSkillCount] = unPlayerSkillID;
		m_unPlayerSkillCount ++;
	}
	else
	{
		if(idx >= m_unPlayerSkillCount || idx < 0)
		{
			return;
		}

		if(unPlayerSkillID == 0)
		{
			if(idx < (m_unPlayerSkillCount - 1))
			{
				m_playerSkillList[idx] = m_playerSkillList[m_unPlayerSkillCount - 1];
			}

			m_unPlayerSkillCount --;
		}
		else
		{
			m_playerSkillList[idx] = unPlayerSkillID;
		}
	}
	*/

	update_2_db();
}


void SkillMgr::update_2_db()
{
	MsgDBUpdateSkillListRequest db_request;
	ACE_OS::memcpy(db_request.skillList, m_list, sizeof(ACE_UINT32) * MAX_SKILL_COUNT);
	ACE_OS::memcpy(db_request.playerSkillList, m_playerSkillList, sizeof(ACE_UINT32) * MAX_PLAYER_SKILL_COUNT);
	ACE_OS::memcpy(db_request.bookRes,m_bookRes,sizeof(SkillBook)*MAX_PLAYER_SKILL_COUNT);

	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_SKILL_LIST, (char *)&db_request, sizeof(MsgDBUpdateSkillListRequest));
}

void SkillMgr::handle_event( BaseEvent *e )
{
	if(ACE_OS::strcmp(e->m_name, GAME_EVENT_LEVEL_UP) == 0)
	{
		ExtraSkillRes *skill_res_0 = (ExtraSkillRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(GAME_CONFIG_INSTANCE::instance()->m_teamLevel[m_map->m_unLevel].extraskill_learn);
		if(NULL != skill_res_0)
		{
			m_list[m_unSkillCount++] = GAME_CONFIG_INSTANCE::instance()->m_teamLevel[m_map->m_unLevel].extraskill_learn;
			add_player_skill(GAME_CONFIG_INSTANCE::instance()->m_teamLevel[m_map->m_unLevel].extraskill_learn);
			update_2_db();
		}
	}
}

int SkillMgr::GetSkillStart( ACE_UINT32 id,int step )
{
	int xstart = 0x00100000;
	while(1)
	{
		PlayerRes *res = (PlayerRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(id);
		if(res == NULL)
			break;
		if (res->m_unQuality <= step)
		{
			xstart =  id & 0x00F00000;
		}
		else
			break;

		id = id + 0x00100000;
	}

	return xstart >> 20;
}
