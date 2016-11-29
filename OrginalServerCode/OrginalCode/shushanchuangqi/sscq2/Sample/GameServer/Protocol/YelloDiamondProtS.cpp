
#include "YelloDiamondProtS.h"
#include "YelloDiamondMgr.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "YelloDiamondProt.h"
#include "GameNetMgr.h"

CYelloDiamondProtS g_YelloDiamondProtS;
//接收：获取黄钻礼包
bool CYelloDiamondProtS::OnRecv_GainYDBag(
		EBagType eBagType, //礼包类型
		UINT16 dLevel, //玩家等级成长礼包
		shared_func<SGainYDBagAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        fnAck->eOpResult = eOtherError;
        return false;
    }
    fnAck->eOpResult = CYelloDiamondMgr::Instance().GainYDBag(*pUser,eBagType,dLevel);

   
      return true;
}

//接收：获取黄钻礼包领取信息
bool CYelloDiamondProtS::OnRecv_GetYDBagInfo(
		shared_func<SGetYDBagInfoAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        return false;
    }
    
    CYelloDiamondMgr::Instance().GetYDInfo(*pUser,fnAck->ydInfo);
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

