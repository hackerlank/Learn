#include "WingMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"

WingMgr::WingMgr()
{

}

WingMgr::~WingMgr()
{

}



void WingMgr::init(ACE_UINT32 unCount, WingItemInfo *list)
{
	ACE_OS::memcpy(m_list, list, sizeof(WingItemInfo) * MAX_WING_LIST);

	m_unCount = unCount;
}

void WingMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN,int result)
{

	MsgWingListResponse *response = (MsgWingListResponse *)public_send_buff;
//		MsgWingListResponse *response = new MsgWingListResponse();
	response->unSN = unSN;;	
	response->nResult = result;

	response->unCount = m_unCount;
	
	ACE_OS::memcpy(response->list, m_list, sizeof(WingItemInfo) * m_unCount);	
	
	int size = sizeof(MsgWingListResponse) + sizeof(WingItemInfo)*m_unCount;		// + sizeof(WingItemInfo) * MAX_WING_LIST;
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_WING_LIST_RESPONSE, (char *)response, size, targetAdr);

}



void WingMgr::update_2_db()
{
	MsgDBUpdateWingListRequest *db_request = (MsgDBUpdateWingListRequest *)public_send_buff;
	ACE_OS::memcpy(db_request->list, m_list, sizeof(WingItemInfo) * MAX_WING_LIST);

	int size = sizeof(MsgDBUpdateWingListRequest) + MAX_WING_LIST * sizeof(WingItemInfo);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_WING_LIST, (char *)db_request, size);
}