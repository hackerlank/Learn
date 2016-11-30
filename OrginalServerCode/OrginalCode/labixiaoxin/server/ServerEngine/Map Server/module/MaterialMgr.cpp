#include "MaterialMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"

MaterialMgr::MaterialMgr()
{
	
}

MaterialMgr::~MaterialMgr()
{

}

void MaterialMgr::init(ACE_UINT32 unCount, MaterialInfo *list)
{
	ACE_OS::memcpy(m_list, list, sizeof(MaterialInfo) * unCount);
	
	m_unCount = unCount;
	
}

void MaterialMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgMaterialListResponse *response = (MsgMaterialListResponse *)public_send_buff;
	response->nResult = 0;
	response->unSN = unSN;
	response->unCount = m_unCount;
	ACE_OS::memcpy(response->list, m_list, sizeof(MaterialInfo) * m_unCount);
	int size = sizeof(MsgMaterialListResponse) + sizeof(MaterialInfo) * m_unCount;
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_MATERIAL_LIST_RESPONSE, (char *)response, size, targetAdr);
}

void MaterialMgr::add(ACE_UINT32 unID, ACE_UINT32 unCount)
{
	int idx;

	idx = GameUtils::find_element(m_unCount, m_list, sizeof(MaterialInfo), unID);

	if(idx == -1)
	{
		idx = GameUtils::add_element(m_unCount, m_list, MAX_MATERIAL_COUNT, sizeof(MaterialInfo), unID);
	}

	if(idx == -1)
	{
		return;
	}

	m_list[idx].unCount += unCount;

	update_2_db();
}

bool MaterialMgr::is_enough(CostInfo &cost, int times)
{
	/*
	int i;
	int idx;

	for(i = 0;i < costList.unCount;i ++)
	{
		idx = GameUtils::find_element(m_unCount, m_list, sizeof(MaterialInfo), costList.list[i].unID);
		if(idx == -1)
		{
			return false;
		}

		if(m_list[idx].unCount < costList.list[i].cost)
		{
			return false;
		}
	}
	*/
	int idx;

	idx = GameUtils::find_element(m_unCount, m_list, sizeof(MaterialInfo), cost.unID);
	if(idx == -1)
	{
		return false;
	}

	if(m_list[idx].unCount < (cost.cost * times))
	{
		return false;
	}

	return true;
}

void MaterialMgr::do_cost(CostInfo &cost, int times, bool write_db,ACE_UINT32 count)
{
	/*
	int i;
	int idx;

	for(i = 0;i < costList.unCount;i ++)
	{
		idx = GameUtils::find_element(m_unCount, m_list, sizeof(MaterialInfo), costList.list[i].unID);
		if(idx == -1)
		{
			continue;
		}

		if(m_list[idx].unCount < costList.list[i].cost)
		{
			m_list[idx].unCount  = 0;
			continue;
		}

		m_list[idx].unCount -= costList.list[i].cost;
	}
	*/
	int idx;

	idx = GameUtils::find_element(m_unCount, m_list, sizeof(MaterialInfo), cost.unID);
	if(idx == -1)
	{
		return;
	}

	if(m_list[idx].unCount <= (cost.cost * times)/count)  //前面已经做过判断了，肯定不会走到这来，不然会有少扣材料的风险
	{
		m_list[idx].unCount  = 0;
	}
	else
	{
		m_list[idx].unCount -= (cost.cost * times)/count;
	}

	if(write_db)
	{
		update_2_db();
	}
}

void MaterialMgr::update_2_db()
{
	/*
	MsgDBUpdateEquipmentListRequest db_request;
	ACE_OS::memcpy(db_request.equipmentList, m_list, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_EQUIPMENT_LIST, (char *)&db_request, sizeof(MsgDBUpdateEquipmentListRequest));
	*/
	MsgDBUpdateMaterialListRequest *db_request = (MsgDBUpdateMaterialListRequest *)public_send_buff;

	db_request->unCount = m_unCount;
	ACE_OS::memcpy(db_request->list, m_list, sizeof(MaterialInfo) * m_unCount);

	int size = sizeof(MsgDBUpdateMaterialListRequest) + m_unCount * sizeof(MaterialInfo);

	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_MATERIAL_LIST, (char *)db_request, size);
}
