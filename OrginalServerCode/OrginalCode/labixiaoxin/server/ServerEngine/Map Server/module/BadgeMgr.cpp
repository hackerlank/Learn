#include "BadgeMgr.h"
#include "..\..\GameBase\res\BadgeRes.h"
#include "..\Map.h"
#include "..\..\GameBase\res\EquipmentRes.h"
#include "..\..\GameBase\res\GameConfig.h"

CBadgeMgr::CBadgeMgr()
{
	m_scheme_badge = GAME_CONFIG_INSTANCE::instance()->m_oSchemeInfo.m_scheme_badge;
}

CBadgeMgr::~CBadgeMgr()
{

}

void CBadgeMgr::init( MsgDBBadgeList * list )
{
	m_mapBadge.clear();
	for (int i=0;i<list->m_unCount;i++)
	{
		m_mapBadge[list->m_BadgeList[i].unID] = list->m_BadgeList[i];
	}

	UpdateGaint();//更新一次加成，曾益
}

bool CBadgeMgr::TryAddBadge( ACE_UINT32 equipmentID )
{
	UpdatePlayerListMap();
	EquipmentRes *res1 = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(equipmentID);
	if(res1)
	{
		ACE_UINT32 badgeID = BadgeRes::GetBadgeID(equipmentID);
		if(badgeID > 0)//找到了此id
		{
			if (!HaveBadgeByID(badgeID))//还没有此徽章
			{
				//BadgeInfo badgeInfo(badgeID);
				BadgeRes *res = (BadgeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(badgeID);//获取掉落配置资源
				if(res)
				{
					BadgeInfo info(badgeID);
					info.m_gain = res->m_gain_value[0];//加成 增益值 初始值
					info.m_charge_value = 0;//res1->m_charge_value;//充能基础值
					m_mapBadge[badgeID] = info;
					update_2_db(badgeID);

					//更新、添加一个 加成
					if (m_playerListMap.find(res->m_need_role) != m_playerListMap.end())
					{
						for (int i=0;i<3;i++)
						{
							if (res->m_gaint_to[i] != 0)
							{
								ACE_ASSERT(res->m_gaint_ype[1] <= 1);
								m_mapGaint[res->m_gaint_to[i]][res->m_gaint_ype[0]].flag[res->m_gaint_ype[1]] += info.m_gain;
							}
							else
								break;
						}
					}


					return true;
				}
			}
		}
	}

	return false;
}

bool CBadgeMgr::HaveBadgeByID( ACE_UINT32 badgeID )
{
	std::map<ACE_UINT32,BadgeInfo>::const_iterator c_it = m_mapBadge.find(badgeID);
	if (c_it != m_mapBadge.end())
	{
		return true;
	}

	return false;
}

void CBadgeMgr::update_2_db( ACE_UINT32 badgeID )
{
	std::map<ACE_UINT32,BadgeInfo>::const_iterator c_it = m_mapBadge.find(badgeID);
	if (c_it != m_mapBadge.end())
	{
		BadgeInfo db_request = c_it->second;
		m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_BADGE_PROGRESS_RESPONSE1, (char *)&db_request, sizeof(BadgeInfo));
	}
}

void CBadgeMgr::UpdateGaint()
{
	UpdatePlayerListMap();
	m_mapGaint.clear();
	std::map<ACE_UINT32,BadgeInfo>::const_iterator c_it = m_mapBadge.begin();
	while (c_it != m_mapBadge.end())
	{
		BadgeRes *res = (BadgeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(c_it->first);//获取掉落配置资源
		if(res)
		{
			if (m_playerListMap.find(res->m_need_role) != m_playerListMap.end())
			{
				for (int i=0;i<3;i++)
				{
					if (res->m_gaint_to[i] != 0)
					{
						ACE_ASSERT(res->m_gaint_ype[1] <= 1);
						m_mapGaint[res->m_gaint_to[i]][res->m_gaint_ype[0]].flag[res->m_gaint_ype[1]] += c_it->second.m_gain;
					}
					else
						break;
				}
			}
		}
		c_it++;
	}
}

// void CBadgeMgr::UpdateGaint(const BadgeInfo & old,const BadgeInfo & _new )
// {
// 	BadgeRes *res = (BadgeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(old.unID);//获取配置资源
// 	if(res)
// 	{
// 		for (int i=0;i<3;i++)
// 		{
// 			if (res->m_gaint_to[i] != 0)
// 			{
// 				ACE_ASSERT(res->m_gaint_ype[1] <= 1);
// 				m_mapGaint[res->m_gaint_to[i]][res->m_gaint_ype[0]].flag[res->m_gaint_ype[1]] = old.m_gain;
// 				m_mapGaint[res->m_gaint_to[i]][res->m_gaint_ype[0]].flag[res->m_gaint_ype[1]] += _new.m_gain;
// 			}
// 			else
// 				break;
// 		}
// 	}
// }

void CBadgeMgr::send_Gaint_info( ACE_UINT32 unSN )
{
	std::vector<MsgGetBadgeGaintResponse::tagGetBadgeGaintInfo> ver;
	GetGaintInfo(ver);
	int len = ver.size()*sizeof(MsgGetBadgeGaintResponse::tagGetBadgeGaintInfo) + sizeof(ACE_UINT32) + sizeof(MsgBaseResponse) ;
	char * pTemp = new char[len];
	memset(pTemp,0,len);

	MsgGetBadgeGaintResponse * response = (MsgGetBadgeGaintResponse *)pTemp;
	response->unCount = ver.size();
	response->nResult = 0;
	response->unSN = unSN;
	for (int i=0;i<ver.size();i++)
	{
		response->getBadgeGaintinfo[i] = ver.at(i);
	}

	m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_DO_Get_BadgeGaint_RESPONSE, (char *)response, len);
	m_map->send_response_end(m_map->m_unUserID, unSN);

	delete [] pTemp;
}

void CBadgeMgr::GetGaintInfo( std::vector<MsgGetBadgeGaintResponse::tagGetBadgeGaintInfo> & ver )
{
	//UpdateGaint();//此处已经是最新的了，所以不需要更新
	MsgGetBadgeGaintResponse::tagGetBadgeGaintInfo temp;
	ver.clear();
	std::map<ACE_UINT32,std::map<ACE_UINT32,tagGaintFlag> >::const_iterator c_it = m_mapGaint.begin();
	while(c_it != m_mapGaint.end())
	{
		std::map<ACE_UINT32,tagGaintFlag>::const_iterator c_it1 = c_it->second.begin();
		while(c_it1 != c_it->second.end())
		{
			temp.unGaint[0] = c_it->first;
			temp.unGaint[1] = c_it1->first;
			temp.unGaint[2] = c_it1->second.flag[0];
			temp.unGaint[3] = c_it1->second.flag[1];
			ver.push_back(temp);
			c_it1++;
		}
		c_it++;
	}
}

bool CBadgeMgr::DoCharge_Add( const ItemInfo *itemInfo,ACE_UINT32 & powerPoint )
{
	ACE_ASSERT(itemInfo);
	EquipmentRes *res1 = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(itemInfo->unResID);
	if(res1)
	{
		ACE_UINT32 badgeID = BadgeRes::GetBadgeID(itemInfo->unResID);
		if(badgeID > 0)//找到了此id
		{
			const BadgeInfo * pBadgeInfo = NULL;
			std::map<ACE_UINT32,ChargeBeginInfo>::iterator it= m_chargeVer.find(badgeID);
			if (it != m_chargeVer.end())
			{
				pBadgeInfo = &(it->second.m_new);
			}
			else
				pBadgeInfo = GetBadgeByID(badgeID);

			if (pBadgeInfo)//已经有此徽章了
			{
				ChargeBeginInfo chargeInfo;
				chargeInfo.m_old = *pBadgeInfo;
				chargeInfo.m_new = *pBadgeInfo;
				BadgeRes *res = (BadgeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(badgeID);//获取掉落配置资源
				if(res)
				{
					ACE_UINT32 unSetup = itemInfo->info.equipment.unStep;
					if (unSetup > 0)
						unSetup -= 1;

					ACE_UINT32 charge_value = res1->m_charge_value*(unSetup*(unSetup + 1)/2.0f + (itemInfo->info.equipment.unLevel-1)*0.05f +1) ;
					//  装备能量值基数*{[装备阶级*(装备阶级-1)/2]+[(装备等级-1)*等级系数]+1}  等级系数：0.05

					//合金消耗1倍
					powerPoint = charge_value ;

					chargeInfo.m_new.m_charge_value += charge_value;
					ACE_UINT32 level = GetLeve(badgeID,chargeInfo.m_new.m_charge_value);
					chargeInfo.m_new.m_gain = res->m_gain_value[0] + ((level -1)*res->m_gain_value[1]);//初始值+ [ (徽章等级-1) * 成长值]
					m_chargeVer[badgeID] = chargeInfo;
					return true;
				}
			}
		}
	}

	return false;
}

bool CBadgeMgr::DoCharge_Add( ACE_UINT32 tuzhiID,ACE_UINT32 & powerPoint )
{
	EquipmentRes *res1 = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(tuzhiID);
	if(res1)
	{
		ACE_UINT32 badgeID = BadgeRes::GetBadgeID(tuzhiID);
		if(badgeID > 0)//找到了此id
		{
			const BadgeInfo * pBadgeInfo = NULL;
			std::map<ACE_UINT32,ChargeBeginInfo>::iterator it= m_chargeVer.find(badgeID);
			if (it != m_chargeVer.end())
			{
				pBadgeInfo = &(it->second.m_new);
			}
			else
				pBadgeInfo = GetBadgeByID(badgeID);

			if (pBadgeInfo)//已经有此徽章了
			{
				ChargeBeginInfo chargeInfo;
				chargeInfo.m_old = *pBadgeInfo;
				chargeInfo.m_new = *pBadgeInfo;
				BadgeRes *res = (BadgeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(badgeID);//获取掉落配置资源
				if(res)
				{
					//3星 %15 8c->0c
					//4星 %4 
					//5星 %1
					if (res1->m_unQuality >= 3 && res1->m_unQuality <= 5)
					{
						ACE_UINT32 charge_value = 0;
						switch(res1->m_unQuality)
						{
						case 3:
							{
								charge_value = res1->m_charge_value * 0.30;
							}break;
						case 4:
							{
								charge_value = res1->m_charge_value * 0.300;
							}break;
						case 5:
							{
								charge_value = res1->m_charge_value * 0.3000;
							}break;
						}

						//合金消耗1倍
						powerPoint = charge_value *1;

						chargeInfo.m_new.m_charge_value += charge_value;
						ACE_UINT32 level = GetLeve(badgeID,chargeInfo.m_new.m_charge_value);
						chargeInfo.m_new.m_gain = res->m_gain_value[0] + ((level -1)*res->m_gain_value[1]);//初始值+ [ (徽章等级-1) * 成长值]
						m_chargeVer[badgeID] = chargeInfo;
						return true;
					}
				}
			}
		}
	}

	return false;
}

BadgeInfo * CBadgeMgr::GetBadgeByID( ACE_UINT32 badgeID )
{
	std::map<ACE_UINT32,BadgeInfo>::iterator c_it = m_mapBadge.find(badgeID);
	if (c_it != m_mapBadge.end())
	{
		return &c_it->second;
	}

	return NULL;
}

ACE_UINT32 CBadgeMgr::GetLeve( ACE_UINT32 unID,ACE_UINT32 chargeNum )
{
	ACE_UINT32 level = 0;
	BadgeRes *res = (BadgeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);//获取配置资源
	if(res)
	{
		res->m_unQuality;//得到品质
		const std::map<ACE_UINT32,BadgeLevelInfo> & obadlevel = GAME_CONFIG_INSTANCE::instance()->m_oBadgelevelConfig;
		std::map<ACE_UINT32,BadgeLevelInfo>::const_iterator c_it = obadlevel.begin();
		while(c_it != obadlevel.end())
		{
			if (c_it->second.m_energy[res->m_unQuality] > chargeNum)
			{
				level = c_it->second.m_level;
				break;
			}
			c_it++;
		}

	}

	return level;
}

int CBadgeMgr::GetGaintPage( MsgGETBadgeResponse & response,ACE_UINT32 unPage,bool isClear )
{
	if (m_map->m_unLevel < m_scheme_badge)
		return ERROR_MSG_BADGE_UNLOCK;

	UpdatePlayerListMap();

	response.unMaxPage =  (m_mapBadge.size() + BADGE_MAX_PAGE -1)/BADGE_MAX_PAGE;
	if (unPage >= 1)
	{
		if (response.unMaxPage >= unPage)
		{
			response.unPage  = unPage;
			unPage--;

			std::map<ACE_UINT32, BadgeInfo>::iterator c_it = m_mapBadge.begin();
			for (int i=0;i<unPage*BADGE_MAX_PAGE;i++)
			{
				c_it++;
			}

			response.unCount = 0;
			while(c_it != m_mapBadge.end() && response.unCount<BADGE_MAX_PAGE)
			{
				if (CanUse(c_it->second.unID))
				{
					response.unBadgeInfo[response.unCount] = c_it->second;
					if (c_it->second.m_flag == 1 && isClear)//还没有被显示过
					{
						c_it->second.m_flag = 0;//设置已经被显示了
						update_2_db(c_it->second.unID);
					}

					response.unCount++;
				}

				c_it++;
			}

		}
	}

	return 0;
}

double CBadgeMgr::GetCoinGaint()
{
	double ret = 0.0;
	if (isUnlock())
	{
		std::map<ACE_UINT32,std::map<ACE_UINT32,tagGaintFlag> >::const_iterator c_it = m_mapGaint.find(1);//全体
		if(c_it != m_mapGaint.end())
		{
			std::map<ACE_UINT32,tagGaintFlag>::const_iterator c_it1= c_it->second.find(5);//贝壳收益
			if(c_it1 != c_it->second.end())
			{
				ret = c_it1->second.flag[1] *0.01;
			}
		}
	}
	return ret;
}

double CBadgeMgr::GetPowerPointGaint()
{	
	double ret = 0.0;
	if (isUnlock())
	{
		std::map<ACE_UINT32,std::map<ACE_UINT32,tagGaintFlag> >::const_iterator c_it = m_mapGaint.find(1);//全体
		if(c_it != m_mapGaint.end())
		{
			std::map<ACE_UINT32,tagGaintFlag>::const_iterator c_it1= c_it->second.find(6);//贝壳收益
			if(c_it1 != c_it->second.end())
			{
				ret = c_it1->second.flag[1] *0.01;
			}
		}
	}

	return ret;
}

void CBadgeMgr::DoCharge_Add_Begin()
{
	m_chargeVer.clear();
}

void CBadgeMgr::DoCharge_Add_After()
{
	std::map<ACE_UINT32,ChargeBeginInfo>::const_iterator c_it = m_chargeVer.begin();
	while(c_it != m_chargeVer.end())
	{
		BadgeInfo * pBadgeInfo = GetBadgeByID(c_it->second.m_new.unID);
		if (pBadgeInfo)
		{
			pBadgeInfo->m_charge_value = c_it->second.m_new.m_charge_value;
			pBadgeInfo->m_gain = c_it->second.m_new.m_gain;
			//UpdateGaint(m_chargeVer.at(i).m_old,m_chargeVer.at(i).m_new);
			update_2_db(c_it->second.m_new.unID);
		}

		c_it++;
	}

	UpdateGaint();
	m_chargeVer.clear();
}

bool CBadgeMgr::isUnlock()
{
	return m_scheme_badge <= m_map->m_unLevel;
}

void CBadgeMgr::UpdatePlayerListMap()
{
	m_playerListMap.clear();
	for (int i=0;i<m_map->m_playerMgr.m_unPlayerCount;i++)
	{
		if (m_map->m_playerMgr.m_list[i].unStep > 0)
			m_playerListMap[m_map->m_playerMgr.m_list[i].unItemID] = 1;
	}
}

bool CBadgeMgr::CanUse( ACE_UINT32 badgeID )
{
	BadgeRes *res = (BadgeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(badgeID);//获取掉落配置资源
	if(res)
	{
		if (res->m_need_role == 0)
			return true;

		if (m_playerListMap.find(res->m_need_role) != m_playerListMap.end())
		{
			return true;
		}
		else
			return false;
	}

	return false;
}

