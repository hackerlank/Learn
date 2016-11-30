#include "PackageMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\res\EquipmentRes.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "BroadcastMgr.h"

PackageMgr::PackageMgr()
{
	m_unCount = 0;
	m_unPackageMax = 0;
	m_unExtraLimit = 0;
	ACE_OS::memset(m_lockList, 0, sizeof(ACE_UINT32) * MAX_ITEMS_COUNT);
	ZeroVar(m_list);
}

PackageMgr::~PackageMgr()
{

}

void PackageMgr::Init_list(ACE_UINT32 unCount, PackageCell *list)
{
	ACE_OS::memcpy(&m_list[0], list, unCount *sizeof(PackageCell));
	m_unCount = unCount;
	
	//开始校验
	for (int i=0;i<m_unCount;i++)
	{
		m_list[i].unOldIndex = m_list[i].unIdx;
		if (m_list[i].unIdx != i)
		{
			replace(i,&m_list[i]);
		}
	}
	//-----------------end
	

	DeleteOldRes();
}

PackageCell *PackageMgr::get_cell(int idx)
{
	PackageCell *cell = NULL;

	if(idx >= 0 && idx < m_unCount)
	{
		cell = &m_list[idx];
	}

	return cell;
}

int PackageMgr::replace(int idx, PackageCell *cell)
{
	if(idx < 0 || idx >= m_unCount)
	{
		return -1;
	}

	m_list[idx] = *cell;
	m_list[idx].unIdx = idx;

	update_2_db(idx);

	return 0;
}

void PackageMgr::update_cell(int idx)
{
	//m_list[idx].unOldIndex = m_list[idx].unIdx;
	update_2_db(idx);

	//徽章系统
	m_map->m_badgeMgr.TryAddBadge(m_list[idx].item.item.unResID);
	//---------------
}

int PackageMgr::delete_item(int idx, PackageCell &cell)
{
	if(idx < 0 || idx >= m_unCount)
	{
		return -1;
	}

	cell = m_list[idx];

	if(idx != (m_unCount - 1))
	{
		m_list[m_unCount - 1].unOldIndex = m_list[m_unCount - 1].unIdx;
		this->replace(idx, &m_list[m_unCount - 1]);
	}
	
	//delete last item
	delete_last_item();

	return 0;
}

void PackageMgr::delete_last_item()
{
	if(m_unCount <= 0)
	{
		return;
	}

	MsgDBDeleteLastItemRequest db_request;
	db_request.unIdx = m_unCount - 1;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_DELETE_LAST_ITEM, (char *)&db_request, sizeof(MsgDBDeleteLastItemRequest));

	m_unCount = m_unCount - 1;
}

int PackageMgr::delete_item_list(int *idxList, int nCount)
{
	int i, j;

	int t;

	for(i = 0;i < nCount;i ++)
	{
		if(idxList[i] < 0 || idxList[i] >= m_unCount)
		{
			return -1;
		}

		for(j = i + 1;j < nCount;j ++)
		{
			if(idxList[j] > idxList[i])
			{
				t = idxList[i];
				idxList[i] = idxList[j];
				idxList[j] = t;
			}
			else if(idxList[j] == idxList[i])
			{
				return -1;
			}
		}
	}

	for(i = 0;i < nCount;i ++)
	{
		if(idxList[i] != (m_unCount - 1))
		{
			m_list[m_unCount - 1].unOldIndex = m_list[m_unCount - 1].unIdx;
			this->replace(idxList[i], &m_list[m_unCount - 1]);
		}

		delete_last_item();
	}

	return 0;
}

int PackageMgr::send_info_i(ObjAdr &targetAdr, ACE_UINT32 unSN, int start_pos)
{
	//char send_buff[4096];
	int size;
	MsgPackageInfoResponse *info = (MsgPackageInfoResponse *)public_send_buff;
	info->unCount = 0;
	info->nResult = 0;
	info->unSN = unSN;

	int c = m_unCount - start_pos;

	/*
	if(c > 50)
	{
		c = 50;
	}
	*/

	int i;

	for(i = 0; i < c; i++)
	{
		info->list[i] = m_list[start_pos + i];
	}

	info->unCount = c;
	size = sizeof(MsgPackageInfoResponse) + c * sizeof(PackageCell);
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PACKAGE_INFO_RESPONSE, (char *)info, size, targetAdr);

	return c;
}

void PackageMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	/*
	char send_buff[4096];
	int size;
	MsgPackageInfoResponse *info = (MsgPackageInfoResponse *)send_buff;
	info->unCount = 0;
	info->nResult = 0;
	info->unSN = unSN;

	PackageCell *pCell;
	int c = 0;
	int i;

	for(i = 0; i < m_unCount; i++)
	{
		info->list[c] = m_list[i];

		c ++;

		if(c == 50)
		{
			info->unCount = c;
			size = sizeof(MsgPackageInfoResponse) + c * sizeof(PackageCell);
			m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PACKAGE_INFO_RESPONSE, (char *)info, size, OBJ_ID_NONE, ADAPTER_GATEWAY_MGR, unTargetID);

			c = 0;
		}
	}

	info->unCount = c;
	size = sizeof(MsgPackageInfoResponse) + c * sizeof(PackageCell);
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PACKAGE_INFO_RESPONSE, (char *)info, size, OBJ_ID_NONE, ADAPTER_GATEWAY_MGR, unTargetID);
	*/
	int offset = 0;

	int c = 0;

	while(offset < m_unCount)
	{
		c = send_info_i(targetAdr, unSN, offset);

		offset += c;
	}
}

int PackageMgr::add_item(const ItemInfo &info)
{
	if(m_unCount >= MAX_ITEMS_COUNT)
	{
		return -1;
	}

	m_list[m_unCount].item.item = info;
	m_list[m_unCount].item.unCount = 1;
	m_list[m_unCount].unIdx = m_unCount;
	m_unCount ++;



	//m_map->m_weaponSkillMgr.update_weapon_skill(info.unResID, 1);

	//update 2 db
	MsgDBAddPackageCellRequest db_request;
	db_request.cell = m_list[m_unCount - 1];
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_ADD_PACKAGE_CELL, (char *)&db_request, sizeof(MsgDBAddPackageCellRequest));

	if(GET_ITEM_TYPE(info.unResID) == ITEM_RES_TYPE_EQUIPMENT)
	{
		EquipmentRes *res = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(info.unResID);
		if(res != NULL)
		{
			if(res->m_unQuality >= 4)
			{
				BROADCAST_MGR_INSTANCE::instance()->add_message(m_map->m_strName, BROADCAST_MESSAGE_TYPE_GET_EQUIPMENT, info.unResID, 0);
			}
		}

		//徽章系统
		m_map->m_badgeMgr.TryAddBadge(info.unResID);
		//---------------
	}

	return 0;
}

void PackageMgr::update_2_db(int idx)
{
	MsgDBUpdatePackageCellRequest db_request;
	db_request.cell = m_list[idx];
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_PACKAGE_CELL, (char *)&db_request, sizeof(MsgDBUpdatePackageCellRequest));
	m_list[idx].unOldIndex = m_list[idx].unIdx;//更新到最新
}

bool PackageMgr::is_full()
{
	if(m_unCount >= /*(*/m_unPackageMax /*+ m_unExtraLimit)*/)//背包上限数量
	{
		return true;
	}
	return false;
}

int PackageMgr::expand_max_package()
{
	if(m_unPackageMax >= GAME_CONFIG_INSTANCE::instance()->m_packageExpandInfo.unMax)
	{
		return -1;
	}

	int t = (int)GAME_CONFIG_INSTANCE::instance()->m_packageExpandInfo.unGold;

	if(m_map->m_unMoney < t)
	{
		return -1;
	}

	m_map->set_basic_info(0, -t, 0, 0, 0,0,0);

	m_unPackageMax = m_unPackageMax + GAME_CONFIG_INSTANCE::instance()->m_packageExpandInfo.unCountPerTime;

	update_PackageMax(m_unPackageMax,true);

	return 0;
}

void PackageMgr::handle_event(BaseEvent *e)
{
	m_unExtraLimit = m_map->m_benefitMgr.get_benefit(BENEFIT_TYPE_PACKAGE_LIMIT, 0);
}

void PackageMgr::update_PackageMax(ACE_UINT32 packageMax,bool is)
{
	m_unPackageMax = packageMax;
	if(is)
	{
		MsgDBUpdatePackageMaxRequest db_request;
		db_request.unPackageMax = m_unPackageMax;
		m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_PACKAGE_MAX, (char *)&db_request, sizeof(MsgDBUpdatePackageMaxRequest));
	}
}

void PackageMgr::DeleteOldRes()
{
	for (int i=m_unCount-1;i>=0;i--)
	{
		EquipmentRes *res = (EquipmentRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(m_list[i].item.item.unResID);
		if(res == NULL)
		{
			PackageCell cell;
			delete_item(m_list[i].unIdx,cell);
		}
	}
}
