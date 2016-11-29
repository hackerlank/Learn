#include "stdafx.h"
#include "RoleEventS.h"
#include "UserMgr.h"
#include "Player.h"
#include "MapMgr.h"
#include "Protocols.h"

////////////////////////////////////////////////////////////////////////
#if 0
void CRoleEventS::OnRecv_RoleLoadDataOver(
        UINT8 bySuc //玩家加载数据结果，0表示ok
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        return;
    }
    g_Game2DBCommC.UserLoadOverFromClient(*pPlayer,bySuc);
}
#endif
bool CRoleEventS::OnRecv_GetRoleSpecInfo(
    shared_func<SGetRoleSpecInfoAck>& fnAck //返回回调函数
)
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return false;
    }
    pUser->RoleToStream(fnAck->stRoleStream);
    return true;
}

//接收：取得散仙列表
bool CRoleEventS::OnRecv_GetFighters(
    shared_func<SGetFightersAck>& fnAck //返回回调函数
)
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return false;
    }
    pUser->GetFighters(fnAck->vecFighters);
    return true;
}

//接收：存储新手引导信息
bool CRoleEventS::OnRecv_StoreGuide(
    const std::string& strGuide, //引导步骤信息
    shared_func<SStoreGuideAck>& fnAck //返回回调函数
)
{
    fnAck->bResult = false;
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        return false;
    }

    pPlayer->SetGuide(strGuide);
    fnAck->bResult = true;
    g_Game2CenterLog.Send_LogGuideChange(pPlayer->GetUserID(),"guide",strGuide);
    TVecINT32 vecParam;
    pPlayer->OnEvent(eEventType_NewPlayerClient,vecParam,strGuide);
    return true;
}

//接收：获取角色Buff信息
bool CRoleEventS::OnRecv_GetRoleBuffInfo(
        shared_func<SGetRoleBuffInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);

    TVecUINT16      vecBuffID;

    /*
    if(pUser)
    {
        TVecUINT16      vecUserBuffID;
        TVecBuffInfo    vecUserBuffInfo;
        EBuffOpResult eResult = pUser->GetAllBuffData(vecUserBuffID, vecUserBuffInfo);
        if(eResult == eBORSuccess)
        {
            vecBuffID.insert(vecBuffID.end(), vecUserBuffID.begin(), vecUserBuffID.end());
            fnAck->vecBuffInfo.insert(fnAck->vecBuffInfo.end(), vecUserBuffInfo.begin(), vecUserBuffInfo.end());
        }
    }
    */
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer)
    {
        TVecUINT16      vecPlayerBuffID;
        TVecBuffInfo    vecPlayerBuffInfo;
        EBuffOpResult eResult = pPlayer->GetAllBuffData(vecPlayerBuffID, vecPlayerBuffInfo);
        if(eResult == eBORSuccess)
        {
            vecBuffID.insert(vecBuffID.end(), vecPlayerBuffID.begin(), vecPlayerBuffID.end());
            fnAck->vecBuffInfo.insert(fnAck->vecBuffInfo.end(), vecPlayerBuffInfo.begin(), vecPlayerBuffInfo.end());
        }
    }
    return true;
    // TODO: 散仙具体Buff信息
}

