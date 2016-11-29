
#include "CoinProtS.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "CoinProt.h"
#include "Protocols.h"
#include "SysMsgDefine.h"

CCoinProtS g_CoinProtS;
//接收：获取礼包
bool CCoinProtS::OnRecv_GetCoinPacket(
		NProtoCommon::EMoneyType eType, //礼包类型
		UINT32 dwMoney, //数量
		shared_func<SGetCoinPacketAck>& fnAck //返回回调函数
	)
{
    /*
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        fnAck->eResult = eCoinError;
        return false;
    }
    string str = NProtoCommon::GetDescription(eType);
    pUser->SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGetCurrency, BuildStrVec(str,dwMoney)));
    */
    fnAck->eResult = eCoinSuccess;
    return true;
}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

