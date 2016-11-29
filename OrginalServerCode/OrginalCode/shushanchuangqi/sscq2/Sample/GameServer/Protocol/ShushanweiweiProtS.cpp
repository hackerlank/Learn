
#include "ShushanweiweiProtS.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "ShushanweiweiProt.h"
#include "Shushanweiwei.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "GameNetMgr.h"

CShushanweiweiProtS g_ShushanweiweiProtS;
//接收：获取礼包
bool CShushanweiweiProtS::OnRecv_TakePrize(
		EPkgType eType, //活动类型
		UINT16 wIndex, //领奖类型：0表示个人奖励，1..16 表示领取全服第几个奖励
		const std::string& strCDK, //CDK
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        fnAck->eRet = ePackError;
        return false;
    }
    fnAck->eRetType = eType;
    fnAck->wRetIndex = wIndex;
    CShushanweiweiPtr pShushanweiwei = NULL;
    pShushanweiwei = pPlayer->GetShushanweiwei();
    if(pShushanweiwei)
        fnAck->eRet = pShushanweiwei->TakePrize(*pUser,eType,wIndex,strCDK);
    return true;
}
	//接收：获得玩家奖励信息
void CShushanweiweiProtS::OnRecv_GetPrizeInfo(
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        return ;
    }
    CShushanweiweiPtr pShushanweiwei = NULL;
    TVecPrizeInfo vecPrizeInfo;
    pShushanweiwei = pPlayer->GetShushanweiwei();
    if(pShushanweiwei)
        pShushanweiwei->SyncPrizeInfo(*pUser,vecPrizeInfo);
    
}

//接收：收听微博
bool CShushanweiweiProtS::OnRecv_ListenWeibo(
		shared_func<SListenWeiboAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
    {
        fnAck->eRet = ePackError;
        return false;
    }
    CShushanweiweiPtr pShushanweiwei = NULL;
    pShushanweiwei = pPlayer->GetShushanweiwei();
    if(pShushanweiwei)
        pShushanweiwei->SetListenWeibo(*pUser);
    fnAck->eRet = ePackSuccess;
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

