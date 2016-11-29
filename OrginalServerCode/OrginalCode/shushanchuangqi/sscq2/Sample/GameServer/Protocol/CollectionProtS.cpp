
#include "CollectionProtS.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "CollectionMgr.h"
#include "GameNetMgr.h"

CCollectionProtS g_CollectionProtS;

//接收：获取成就信息
bool CCollectionProtS::OnRecv_GeCollectionInfo(
	shared_func<SGeCollectionInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    
    CCollectionMgrPtr pCollectionMg =  pPlayer->GetCollectionMgr();
    if(pCollectionMg)
    {
        pCollectionMg->GetCollectionInfo(fnAck->vecCollectionInfo);
    }

    fnAck->wLevel = pPlayer->GetCollectionLevel();
    fnAck->dwAP   = pUser->GetMoney(EMONEY_COLLECTAP);

    return true;


}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

