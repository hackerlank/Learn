#include "PropsMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"

PropsMgr::PropsMgr()
{
	
}

PropsMgr::~PropsMgr()
{

}

void PropsMgr::init(ACE_UINT32 unCount, PropsInfo *list)
{
	m_list.assign(list, list + unCount);
}

void PropsMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgPropsListResponse *response = (MsgPropsListResponse *)public_send_buff;
	response->nResult = 0;
	response->unSN = unSN;
	response->unCount = m_list.size();
	if(m_list.size() != 0)
		ACE_OS::memcpy(response->list, &m_list[0], sizeof(PropsInfo) * m_list.size());
	int size = sizeof(MsgPropsListResponse) + sizeof(PropsInfo) * m_list.size();
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_PROPS_LIST_RESPONSE, (char *)response, size, targetAdr);
}

void PropsMgr::add(ACE_UINT32 unID, ACE_UINT32 unCount)
{
	int idx = -1;

	if(m_list.size() != 0)
		idx = GameUtils::find_element(m_list.size(), &m_list[0], sizeof(PropsInfo), unID);

	if(idx == -1)
	{
		m_list.push_back(PropsInfo());
		ACE_UINT32 dwCount = m_list.size() - 1;
		idx = GameUtils::add_element(dwCount, &m_list[0], m_list.size(), sizeof(PropsInfo), unID);
	}

	if(idx == -1)
	{
		return;
	}

	m_list[idx].unCount += unCount;

	update_2_db();
}

bool PropsMgr::is_enough(CostInfo &cost, int times)
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
	int idx = -1;

	if(m_list.size() != 0)
		idx = GameUtils::find_element(m_list.size(), &m_list[0], sizeof(PropsInfo), cost.unID);
	if(idx == -1)
	{
		return false;
	}

	if((int)m_list[idx].unCount < (cost.cost * times))
	{
		return false;
	}

	return true;
}

void PropsMgr::do_cost(CostInfo &cost, int times, bool write_db,ACE_UINT32 count)
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
	int idx = -1;

	if(m_list.size() != 0)
		idx = GameUtils::find_element(m_list.size(), &m_list[0], sizeof(PropsInfo), cost.unID);
	if(idx == -1)
	{
		return;
	}

	if(m_list[idx].unCount <= (cost.cost * times)/count)  //前面已经做过判断了，肯定不会走到这来.
	{
		m_list.erase(m_list.begin() + idx);
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

void PropsMgr::update_2_db()
{
	/*
	MsgDBUpdateEquipmentListRequest db_request;
	ACE_OS::memcpy(db_request.equipmentList, m_list, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_EQUIPMENT_LIST, (char *)&db_request, sizeof(MsgDBUpdateEquipmentListRequest));
	*/
	MsgDBUpdatePropsListRequest *db_request = (MsgDBUpdatePropsListRequest *)public_send_buff;

	db_request->unCount = m_list.size();
	if(m_list.size() != 0)
		ACE_OS::memcpy(db_request->list, &m_list[0], sizeof(PropsInfo) * db_request->unCount);

	int size = sizeof(MsgDBUpdatePropsListRequest) + db_request->unCount * sizeof(PropsInfo);

	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_PROPS_LIST, (char *)db_request, size);
}

const PropsInfo* PropsMgr::GetPropsInfo( int idx )
{
	if(idx >= m_list.size())
		return NULL;
	if(m_list[idx].unCount == 0)
		return NULL;
	return &m_list[idx];
}

const PropsInfo* PropsMgr::GetPropsInfoByID( int id )
{
	for(int i = 0; i != m_list.size(); i++)
	{
		if(m_list[i].unItemID == id)
			return GetPropsInfo(i);
	}

	return NULL;
}
