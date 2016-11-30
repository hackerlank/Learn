#include "SecretMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"

SecretMgr::SecretMgr()
{
	m_unCellCount = 0;//当前拥有格子数
	m_refreshTimes = 0;
}

SecretMgr::~SecretMgr()
{

}



void SecretMgr::init(ACE_UINT32 unCellCount,ACE_UINT32 refreshTimes,ACE_UINT32 lastRefreshTime,SecretItemInfo *list)//格子次数，刷新次数，上次刷新时间，物品列表 
{
//	ACE_OS::memcpy(m_list, list, sizeof(SecretItemInfo) * unCellCount);MAX_SECRET_LIST
		ACE_OS::memcpy(m_list, list, sizeof(SecretItemInfo) * MAX_SECRET_LIST);
	m_unCellCount =  unCellCount;
	m_refreshTimes = refreshTimes;
	m_unLastRefreshTime = lastRefreshTime;

}

void SecretMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN,int result) //第一次刷新的时候发送过去前要先刷新下,resutl在其神秘商店刷新的时候要用和开格子也要用，第一次发送默认0
{    //还有就是时间到了当用户打开的时候自动刷新一次  ，还要加个当前台点开时，时间到了发送个消息过来也要返回的

	MsgSecretListResponse *response = (MsgSecretListResponse *)public_send_buff;
	ACE_UINT32 curTime = GameUtils::get_utc();//当前时间戳
	Secret tmpCfg = GAME_CONFIG_INSTANCE::instance()->m_secretCfg;
	ACE_OS::memcpy(response->list, m_list, sizeof(SecretItemInfo) * m_unCellCount);	
	response->unRefreshTimes = m_refreshTimes;
	response->unPaidRefreshPrice = m_unPaidRefreshPrice;
	int tmpTime = m_unLastRefreshTime +tmpCfg.unRefreshSec - curTime;
	response->unRemainingTime =   tmpTime > 0 ? tmpTime:0;//时间到了返回0，没到返回剩余时间
	response->unSN = unSN;
	response->unCell = m_unCellCount;	
	response->nResult = result;
	int size = sizeof(MsgSecretListResponse) + sizeof(SecretItemInfo) * m_unCellCount;
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_SECRET_LIST_RESPONSE, (char *)response, size, targetAdr);

}



void SecretMgr::update_2_db()
{
	MsgDBUpdateSecretListRequest *db_request = (MsgDBUpdateSecretListRequest *)public_send_buff;
	ACE_OS::memcpy(db_request->list, m_list, sizeof(SecretItemInfo) * m_unCellCount);
	db_request->unLastRefreshTime = m_unLastRefreshTime;
	db_request->unRefreshTimes = m_refreshTimes;
	db_request->unCellCount = m_unCellCount;
	
	int size = sizeof(MsgDBUpdateSecretListRequest) + m_unCellCount * sizeof(SecretItemInfo);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_SECRET_LIST, (char *)db_request, size);
}