#include "GiftBagCodeMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\res\GameConfig.h"

GiftBagCodeMgr::GiftBagCodeMgr()
{

}

GiftBagCodeMgr::~GiftBagCodeMgr()
{

}



void GiftBagCodeMgr::init(const WORD codeSet[], const int codeCount)
{
	int iOffset = 0;
	while (iOffset < codeCount)
	{
		m_setClaimCode.insert(codeSet[iOffset++]);
	}
}

void GiftBagCodeMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN,int result) 
{
	MsgConvertGiftBagCodeResponse *response = (MsgConvertGiftBagCodeResponse *)public_send_buff;
	response->nResult = result;
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_SECRET_LIST_RESPONSE, (char *)response, sizeof(MsgConvertGiftBagCodeResponse), targetAdr);
}

void GiftBagCodeMgr::update_2_db(const WORD wClaimCodeType)
{
	MsgDBUpdatePlayerGiftBagCodeRequest db_request;
	db_request.wGiftBagCodeType = wClaimCodeType;
	int size = sizeof(MsgDBUpdatePlayerGiftBagCodeRequest);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_PLAYER_GIFT_BAG_CODE, (char *)&db_request, size);
}