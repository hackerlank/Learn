#include "HandbookMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"

HandbookMgr::HandbookMgr()
{
	
}

HandbookMgr::~HandbookMgr()
{

}

void HandbookMgr::init(ACE_UINT32 unCount, BaseItemInfo *list)
{
	ACE_OS::memcpy(m_list, list, sizeof(BaseItemInfo) * unCount);
	m_unCount = unCount;

}

void HandbookMgr::add(ACE_UINT32 unID)//有重复的就不会加入里面了
{
	GameUtils::add_element(m_unCount, m_list, MAX_HANDBOOK_COUNT, sizeof(BaseItemInfo), unID);//m_unCountlist表的长度,m_list:图鉴列表

	update_2_db();
}

void HandbookMgr::del(ACE_UINT32 unID)
{
	GameUtils::delete_element(m_unCount, m_list, sizeof(BaseItemInfo), unID);// jinpan	删除掉已经用完的物品图鉴

	update_2_db();
}



bool HandbookMgr::has_handbook(ACE_UINT32 unID)
{
	return (GameUtils::find_element(m_unCount, m_list, sizeof(BaseItemInfo), unID) != -1);
}

void HandbookMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	
	MsgHandbookListResponse *response = (MsgHandbookListResponse *)public_send_buff;
	response->nResult = 0;
	response->unSN = unSN;
	response->unCount = m_unCount;
	ACE_OS::memcpy(response->list, m_list, sizeof(BaseItemInfo) * m_unCount);
	int size = sizeof(MsgHandbookListResponse) + sizeof(BaseItemInfo) * (m_unCount - 1);
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_HANDBOOK_LIST_RESPONSE, (char *)response, size, targetAdr);
}

void HandbookMgr::update_2_db()
{
	MsgDBUpdateHandbookListRequest *db_request = (MsgDBUpdateHandbookListRequest *)public_send_buff;

	db_request->unCount = m_unCount;
	ACE_OS::memcpy(db_request->list, m_list, sizeof(BaseItemInfo) * m_unCount);
	int size = sizeof(MsgDBUpdateHandbookListRequest) + m_unCount * sizeof(BaseItemInfo);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_HANDBOOK_LIST, (char *)db_request, size);
}