#include "stdafx.h"
#include "Protocols.h"
#include "MapMgr.h"
#include "UserForbidMgr.h"
#include "UserMgr.h"
#include "DungeonMgr.h"
#include "WorldBossMgr.h"
#include "GuildBattleMgr.h"
#include "ShushanBattle.h"
#include "LangHuanBlessMgr.h"
#include "GodChest.h"
#include "NewGuildBattleMgr.h"
#include "GameConfig.h"
#include "GateHandler.h"
#include "ServerID.h"
#include "AllTimers.h"
#include "GameNetMgr.h"

//接收：帐号协议代理发送请求
void CGame2DBCommC::OnRecv_UserPackageProxy(
        UINT64 qwUsrID, //帐号ID
        UINT32 dwGateID, //所在网关服务器ID
        const TVecString& vecPackage //协议包列表
        )
{
    CGateHandler* pGateHandler = NetMgr.GetGateHandler();
    for(const string& strPkg : vecPackage)
        pGateHandler->SendGate(dwGateID, &qwUsrID, 1, strPkg.c_str(), (UINT32)strPkg.size());
}

bool CGame2DBCommC::PlayerEnterMap(CPlayer& rPlayer)
{
    UINT16 wMapID = rPlayer.GetCurMapID();
    if(wMapID == CLangHuanBlessMgr::Instance().GetMapID())
    {
        if(!CLangHuanBlessMgr::Instance().IsAllowEnter(rPlayer))
        {
            wMapID = 20;
            rPlayer.SetCurMapID(wMapID);
            //rPlayer.ReturnLastNormalMap();
        }

    }
    CGameMapPtr pMap = CMapMgr::GetMap(wMapID);
    if(pMap == NULL)
    {
        LOG_CRI << "Can't find map! MapID: " << wMapID;
        return false;
    }

//    g_GodChest.UserOnline(rPlayer);

    bool bAppear = true;
    g_MapProtS.NotifyUserEnterMap(rPlayer,pMap);
    switch (pMap->GetMapInfo().eMapType)
    {
        case eMapGuildBattle: // 帮派战地图
            bAppear = CGuildBattleMgr::Instance().UserOnline(ToThisPtr(&rPlayer));
            break;
        case eMapShushanBattle: // 蜀山论剑地图
            bAppear = false;
            break;
        default:
            break;
    }
    pMap->PlayerAppear(rPlayer, bAppear);
    return true;
}

void CGame2DBCommC::OnRecv_UserLogoutNtf(
        UINT64 qwUsrID, //账号ID
        NServerCommon::ELeaveType eLeaveType //下线类型
        )
{
    LOG_DBG << "UserLogout, UsrID:" << qwUsrID << " LeaveType: " << GetDescription(eLeaveType);
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser != NULL && pUser->GetUserState() != eUserLeaveAway)
        CUserMgr::OnUserLeave(*pUser, eLeaveType);
}

void CGame2DBCommC::TimerCheck()
{
    if(Config._bIsCrossServer)
    {
        _bDBInited = true;
        _bTimerClosed = true;
        if(!NetInterface::CloseTimer(CTimerMgr::Instance().GetInitTimer()))
            LOG_CRI << "CloseTimer fails!";
    }
    if(!_bDBInited)
        Send_GetStatus([this](UINT8 byRet_ //0为成功，1为失败，2为超时
                    )
                {
                if(byRet_ == 0)
                {
                if(!_bDBInited)
                {
                _bDBInited = true;
                Config.OnDBInited();
                }

                if(!_bTimerClosed)
                {
                _bTimerClosed = true;
                if(!NetInterface::CloseTimer(CTimerMgr::Instance().GetInitTimer()))
                LOG_CRI << "CloseTimer fails!";
                }
                }
                });
#if 0
    UINT32 dwNow = time(NULL); 
    for (auto it = _mapWaitEnterMap.begin();it != _mapWaitEnterMap.end();)
    {
        bool bErase = true;
        do {
            CUserPtr pUser = CUserMgr::GetUserByUserID(it->first); 
            if(pUser == NULL)
            {
                break;
            }
            CPlayerPtr pPlayer = pUser->GetPlayer();
            if(pPlayer == NULL)
            {
                break;
            }
            if(dwNow > it->second.dwTimer + 60)
            {
                UserLoadOver(*pPlayer,2,it->second.bReEnter,it->second.eEnterType);

                break;
            }

            bErase = false;
        }while(0);
        if(bErase)
        {
            it = _mapWaitEnterMap.erase(it);
        }
        else
        {
            ++it;
        }
    }
#endif
}
bool CGame2DBCommC::EnterWorldMap(CPlayer& rPlayer)
{
    CGameMapPtr pMap = CMapMgr::GetMap(rPlayer.GetCurMapID());
    if (pMap == NULL)
    {
        return false;
    }

    rPlayer.SetMap(pMap);
    rPlayer.Relive();
    SPoint sEnterPoint(rPlayer.GetBaseInfo().fX,rPlayer.GetBaseInfo().fY);
    if((sEnterPoint.fX == 0 && sEnterPoint.fY == 0) || pMap->IsBlockPoint(sEnterPoint))
    {
        sEnterPoint.fX = pMap->GetMapInfo().oRealivePoint.fX; 
        sEnterPoint.fY = pMap->GetMapInfo().oRealivePoint.fY;
    }

    rPlayer.SetPoint(sEnterPoint); 
    rPlayer.GetDgnPkg().ReturnCost();
    return PlayerEnterMap(rPlayer);//进入世界地图
}

void GetFriendsInfo(const NRoleInfoDefine::RoleDataInfo& RoleData, NFriendProt::TVecFriendDBInfo& vecFriendsInfo)
{
    vecFriendsInfo = RoleData.vecFriendsInfo;
}
void GetVarInfoForCenter(const NRoleInfoDefine::RoleDataInfo & RoleData,NRoleInfoDefine::TVecVarsDBInfo &vecGameVars)
{
    for(auto iter = RoleData.vecGameVars.begin();iter != RoleData.vecGameVars.end();iter++)
    {
        const NRoleInfoDefine::SVarsDBInfo &rInfo = *iter;
        if(rInfo.byServerType == eHostCenter)
        {
            vecGameVars.push_back(rInfo);
        }

    }

}
void GetArenaInfo(const NRoleInfoDefine::RoleDataInfo& RoleData, NRoleInfoDefine::TVecRoleArenaInfo &vecArenaInfo)
{
    vecArenaInfo = RoleData.vecArenaInfo;
}
void CGame2DBCommC::OnRecv_UserLoginNtf(
        EEnterType eEnterType, //进入的类型
        const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
        const TVecString& vecEnterString, //平台相关参数
        UINT32 dwGateID, //网关Id
        UINT64 qwUserID, //用户Id
        const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
        ) 
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if (pUser != NULL)
    {
        pUser->SetPlatformParam(vecPlatformParam);
        pUser->SetEnterString(vecEnterString);
        UserReEnterGame(*pUser, dwGateID, eEnterType,vecPlatformParam, vecEnterString, &RoleData);
        return;
    }


    bool bEnter = false;
    do
    {
        pUser = CUserMgr::CreateUser(RoleData.qwRoleId);
        if (!pUser)
        {
            LOG_CRI << "CUserMgr::CreateUser(" << RoleData.qwRoleId << ") error.";
            break;
        }
        CPlayerPtr pPlayer = CUserMgr::CreatePlayer(RoleData.qwRoleId, pUser);
        if (pPlayer == NULL)
        {
            LOG_CRI << "CUserMgr::CreatePlayer(" << RoleData.qwRoleId << ") error.";
            break;;
        }
        pPlayer->BeginReload();
        if (!pPlayer->Init())
        {
            LOG_CRI << "CPlayer::Init(" << RoleData.qwRoleId << ") error.";
            break;
        }
        if (!pPlayer->LoadFromDB(RoleData))
        {
            LOG_CRI << "CPlayer::LoadFromDB(" << RoleData.qwRoleId << ") error.";
            break;
        }

        pUser->SetPlatformParam(vecPlatformParam);
        pUser->SetEnterString(vecEnterString);
        //通知Gate有玩家进入
        NetMgr.GetGateHandler()->OnUserLogin(qwUserID, dwGateID);
        pUser->SetSvrGroup(GetServerGroup(GetCurSvrID()));
        g_Gate2GameCommS.SendSvr_UserEnterNtf(&dwGateID, 1, qwUserID);    

        SUserEnterInfo oUserEnterInfo;
        RoleBaseInfo& rInfo = pPlayer->GetModifyBaseInfo();
        if (vecEnterString.size() >= 3)
            rInfo.szOpenId = (vecEnterString[2]);
        if (vecEnterString.size() >= 4)
            rInfo.szOpenKey = vecEnterString[3];
        UINT32 dwCenterSvrID = pUser->GetCenterSvrID(); 
        switch(eEnterType)
        {
            case eEnterLogin:
                {
                    pPlayer->GetUserCenterInfo(oUserEnterInfo);
                    pPlayer->SaveOffLineEvent(RoleData.vecEventOffLine);
                    GetFriendsInfo(RoleData, oUserEnterInfo.vecFriendsInfo);
                    GetVarInfoForCenter(RoleData,oUserEnterInfo.vecGameVars);
                    GetArenaInfo(RoleData,oUserEnterInfo.vecArenaInfo); 
                    oUserEnterInfo.vecFireInfo = RoleData.vecFireInfo;
                    oUserEnterInfo.vecPlatform = pUser->GetPlatformParam();
                    oUserEnterInfo.vecShipReport = RoleData.vecShipReport;
                    oUserEnterInfo.sShipData = RoleData.sShipData;
                    g_Game2CenterCommC.SendSvr_UserLoginNtf(&dwCenterSvrID, 1, qwUserID, oUserEnterInfo);
                }
                break;

            case eEnterJump:
            case eEnterToCross:
            case eEnterFromCross:
                g_Game2CenterCommC.SendSvr_UserJumpSvrNtf(&dwCenterSvrID, 1, qwUserID);
                break;

            default:
                break;
        }

        pUser->OnEnter();
        CPlayer& rPlayer = *(pPlayer);

        //检查玩家进入副本
        if (!EnterDgn(rPlayer))
        {
            if(!EnterWorldMap(rPlayer))
            {
                LOG_CRI << "Player EnterWorld Map fails! Active RoleID: " << rPlayer.GetRoleID();
                break ;
            }
        }
        OnLogin(rPlayer.GetUser(),eEnterType);

        pPlayer->SetPlayerState(ePlayerInGame);
        pUser->SetUserState(eUserInGame);
        pPlayer->OnEnter();
        pPlayer->InitAfterLoaded(false);
        rPlayer.UpdateBaseInfo2DB(); 
        if(eEnterType == eEnterLogin)
        {
            TVecString vecLogin;
            pUser->SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogUserLogin(qwUserID, vecLogin));
        }
        bEnter = true;

    }while(0);

    if(!bEnter)
    {
        CUserMgr::KickUserOffLine(qwUserID);
        CUserMgr::OnUserLeave(qwUserID, eLeaveKick);
        LOG_CRI << "UserEnterGame Fails! UsrID: " << qwUserID;
    }
}

bool CGame2DBCommC::EnterDgn(CPlayer& rPlayer)
{
    CDungeonPtr pDgn = NULL;
    bool bNeedReset = true; // 是否需要重置到世界地图

    // 先查看副本是否还在
    pDgn = CDungeonMgr::GetDungeon(rPlayer.GetBaseInfo().qwDgnId);
    if( pDgn && pDgn->CanEnter(rPlayer)&& pDgn->IsCanRelogin())
    {
        bNeedReset = false;
        return pDgn->PlayerReEnter(rPlayer,rPlayer.GetPoint());
    }
    //如果是出生副本
    else if(!rPlayer.GetDgnPkg().IsDgnPassed(1))
    {
        //创建副本，并丢进去
        bNeedReset = false;
        const SPoint *pPoint  = NULL ;
        SPoint sPoint(rPlayer.GetDgnfX(),rPlayer.GetDgnfY());
        if(rPlayer.GetDgnID() != 0)
        {
            pPoint = &sPoint;
        }
        return eDungeonSuccess == CDungeonMgr::PlayerEnterNewDungeon(rPlayer, 1,pPoint);
    }
    else if (CGuildBattleMgr::Instance().IsPlayerInGuildBattleField(rPlayer.GetRoleID()))
    {
        LOG_DBG << "PlayerReEnter.";
        CGameMapPtr pMap = rPlayer.GetMap();
        if (pMap)
        {
            g_MapProtS.NotifyUserEnterMap(rPlayer,pMap);
            CGuildBattleMgr::Instance().UserOnline(ToThisPtr(&rPlayer));
            pMap->PlayerReappear(rPlayer);
            return true;
        }
    }
    else if (ShushanBattle.IsPlayerInShushanBattle(rPlayer.GetRoleID()))
    {
        CGameMapPtr pMap = rPlayer.GetMap();
        if (pMap)
        {
            g_MapProtS.NotifyUserEnterMap(rPlayer,pMap);
            pMap->PlayerReappear(rPlayer);
            return true;
        }
    }

    if (bNeedReset)
    {
        UINT16 wMapID = rPlayer.GetBaseInfo().wMapID;
        SPoint oPoint(rPlayer.GetBaseInfo().fX,rPlayer.GetBaseInfo().fY);
        if(wMapID == 0)
        {
            LOG_CRI << "NO MAP";
            wMapID = 1;
        }
        rPlayer.ClearDgnInfo();
        rPlayer.SetCurMapID(wMapID);
        rPlayer.SetPoint(oPoint);
    }
    return false;   
}

void CGame2DBCommC::OnLogin(CUser& rUser, EEnterType eEnterType)
{
    if (eEnterType == eEnterLogin)
        SCRIPT.VCall("OnLogin", boost::ref(rUser));
}

//接收：账号重新进入通知
void CGame2DBCommC::OnRecv_UserReEnterNotify(
        UINT64 qwUsrID, //账号ID
        UINT32 dwGateID, //所在网关服务器ID
        const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
        const TVecString& vecEnterString //平台相关参数
        ) 
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return;
    }
    UserReEnterGame(*pUser, dwGateID, eEnterNone,vecPlatformParam, vecEnterString);
    pUser->SetPlatformParam(vecPlatformParam);
    pUser->SetEnterString(vecEnterString);
}
void CGame2DBCommC::UserReEnterGame(CUser& rUser, UINT32 dwGateID, EEnterType eEnterType,const NProtoCommon::TVecPlatformParam& vecPlatformParam, const TVecString& vecEnterString, const NRoleInfoDefine::RoleDataInfo* pRoleData /* = NULL */)
{
    UINT64 qwUsrID = rUser.GetUserID();
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_CRI << "User has no player! UserID: " << qwUsrID;
        return;
    }
    bool bEnter = false;
    do
    {
        pPlayer->BeginReload();
        NetMgr.GetGateHandler()->OnUserLogin(qwUsrID, dwGateID);
        g_Gate2GameCommS.SendSvr_UserEnterNtf(&dwGateID, 1, qwUsrID);

        //通知客户端初始化开始
        SUserEnterInfo oUserEnterInfo;
        if (vecEnterString.size() >= 3)
            oUserEnterInfo.szOpenId = vecEnterString[2];
        if (vecEnterString.size() >= 4)
            oUserEnterInfo.szOpenKey = vecEnterString[3];
        UINT32 dwCenterSvrID = rUser.GetCenterSvrID();
        if(rUser.GetUserState() == eUserReplace)
        {
            g_Game2CenterCommC.SendSvr_UserReplaceNtf(&dwCenterSvrID, 1, qwUsrID);
            RoleBaseInfo& rInfo = pPlayer->GetModifyBaseInfo();
            if (vecEnterString.size() >= 3)
                rInfo.szOpenId = (vecEnterString[2]);
            if (vecEnterString.size() >= 4)
                rInfo.szOpenKey = vecEnterString[3];
        }
        else
        {
            if(pRoleData != NULL)
            {
                const NRoleInfoDefine::RoleDataInfo& RoleData = *pRoleData;
                GetFriendsInfo(RoleData, oUserEnterInfo.vecFriendsInfo);
                GetVarInfoForCenter(RoleData,oUserEnterInfo.vecGameVars);
                GetArenaInfo(RoleData,oUserEnterInfo.vecArenaInfo); 
                oUserEnterInfo.vecFireInfo = RoleData.vecFireInfo;
                pPlayer->SetBaseInfo(pRoleData->stBaseInfo);
                pPlayer->SaveOffLineEvent(RoleData.vecEventOffLine);
                rUser.PlatformParamFromDB(RoleData.vecPlatformParam);
                oUserEnterInfo.vecShipReport = RoleData.vecShipReport;
                oUserEnterInfo.sShipData = RoleData.sShipData;
            }
            RoleBaseInfo& rInfo = pPlayer->GetModifyBaseInfo();
            if (vecEnterString.size() >= 3)
                rInfo.szOpenId = (vecEnterString[2]);
            if (vecEnterString.size() >= 4)
                rInfo.szOpenKey = vecEnterString[3];
            rUser.SetPlatformParam(vecPlatformParam);
            rUser.SetEnterString(vecEnterString);
            oUserEnterInfo.vecPlatform = rUser.GetPlatformParam();
            pPlayer->GetUserCenterInfo(oUserEnterInfo);
            g_Game2CenterCommC.SendSvr_UserLoginNtf(&dwCenterSvrID, 1, qwUsrID, oUserEnterInfo);
        }

        rUser.OnEnter();
        if(Config._bIsCrossServer)
            rUser.OnReEnterCrossSvr();

    
        TVecString vecLogin;
        if (!EnterDgn(*pPlayer))
        {

            if(!PlayerReEnterGame(*pPlayer))
            {
                LOG_CRI << "PlayerReEnterGame fails for ReEnter! Active RoleID: " << pPlayer->GetRoleID();
                break;
            }
        }
        OnLogin(rUser, eEnterType);
        rUser.SetUserState(eUserInGame);
        pPlayer->OnEnter();
        rUser.SetPlatformParam(vecPlatformParam);
        rUser.SetEnterString(vecEnterString);
        pPlayer->InitAfterLoaded(true);
        pPlayer->UpdateBaseInfo2DB(); 
        rUser.SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogUserLogin(qwUsrID, vecLogin));
        bEnter =true;
    }while(0);

    //如果在锁妖塔直接退出
     CDungeonPtr pDgn = pPlayer->GetDgn();
     if(pDgn)
     {
         EDgnType eDgnType = pDgn->GetDgnType();
         switch(eDgnType)
         {
             case eDemonTowerDgn:
                     pDgn->PlayerLeave(*pPlayer);
             default:
                 break;
         }
     }

    if(!bEnter)
    {
        LOG_INF << "CGame2DBCommC::UserReEnterGame fail: " << qwUsrID;
        CUserMgr::KickUserOffLine(qwUsrID);
        CUserMgr::OnUserLeave(qwUsrID, eLeaveKick);
        LOG_CRI << "UserEnterGame Fails! UsrID: " << qwUsrID;
    }
}

bool CGame2DBCommC::PlayerReEnterGame(CPlayer& rPlayer)
{

    switch(rPlayer.GetPlayerState())
    {
        case ePlayerLeave:
            if(!PlayerEnterMap(rPlayer))
            {
                LOG_CRI << "PlayerEnterGame fails! RoleID: " << rPlayer.GetRoleID();
                return false;
            }
            break;
        case ePlayerSwitch:
            if(!PlayerEnterSwitch(rPlayer))
            {
                LOG_CRI << "PlayerReappear fails! RoleID: " << rPlayer.GetRoleID();
                return false;
            }
            break;
        default:
            LOG_CRI << "Invalid PlayerState: " << rPlayer.GetPlayerState();
            return false;
    }
    return true;
}

bool CGame2DBCommC::SaveDataReq(CUser& rUser, ESaveType eSaveType,const TVecPlatformParam& vecPlatformParam )
{
    UINT32 dwDBSvrID = rUser.GetDBSvrID();
    return SendSvr_SaveUserDataReq(&dwDBSvrID, 1, rUser.GetUserID(),  eSaveType, vecPlatformParam , &CGame2DBCommC::OnReturn_SaveUserDataReq);
}

bool CGame2DBCommC::SaveDataReq(CPlayer& rPlayer, ESaveType eSaveType,const TVecPlatformParam& vecPlatformParam )
{
    CUserPtr pUser = rPlayer.GetUserPtr();
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find User! RoleID: " << rPlayer.GetRoleID();
        return false;
    }
    UINT32 dwDBSvrID = pUser->GetDBSvrID();
    return SendSvr_SaveUserDataReq(&dwDBSvrID, 1, rPlayer.GetUserID(),  eSaveType, vecPlatformParam, &CGame2DBCommC::OnReturn_SaveUserDataReq);
}

void CGame2DBCommC::OnReturn_SaveUserDataReq(
        UINT8 byRet_, //0为成功，1为失败，2为超时
        UINT64 qwUsrID, //(本地保存的函数参数)账号ID
        ESaveType eSaveType //(本地保存的函数参数)保存类型
        )
{
    if(byRet_ != 0)
    {
        LOG_CRI << "byRet: " << byRet_;
        if(eSaveType != eSaveOff)
        {
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
            if(pUser != NULL)
            {
                LOG_CRI << "User State: " << pUser->GetUserState();
                CUserMgr::OnUserLeave(qwUsrID, eLeaveKick);
                CUserMgr::KickUserOffLine(qwUsrID);
            }
        }
        return;
    }
    switch(eSaveType)
    {
        case eSaveJump:
        case eSaveToCross:
        case eSaveFromCross:
            CUserMgr::OnUserLeave(qwUsrID, eLeaveJump);
        default:
            break;
    }
}

bool CGame2DBCommC::PlayerEnterSwitch(CPlayer& rPlayer)
{
    CGameMapPtr pMap = rPlayer.GetMap();
    if(pMap == NULL)
    {
        LOG_CRI << "Player is not on map! RoleID: " << rPlayer.GetRoleID();
        return false;
    }
    g_MapProtS.NotifyUserEnterMap(rPlayer,pMap);
    pMap->PlayerReappear(rPlayer);
    return true;
}

//接收：离线事件通知
void CGame2DBCommC::OnRecv_NewOffEventNotice(
        UINT64 qwUsrID, //账号ID
        const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return;
    }
    pUser->GetPlayer()->DoOffLineEventNotice(sEventData);

}

//接收：新帮派战历史记录获取返回
void CGame2DBCommC::OnRecv_NewGuildBattleHistoryNotify(
        UINT32 dwCurSize, //已发送条数
        UINT32 dwTotalSize, //总条数
        const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
        )
{
    string strData;
    COutArchive ar(strData);
    ar << vecInfo;
    NNewGuildBattle::CBattleMgr::Instance().LoadFromDB(strData);
    if (dwCurSize >= dwTotalSize)
    {
        NNewGuildBattle::CBattleMgr::Instance().SetLoaded(true);
        Config.SetInited(eDBInitNewGuildBattle);
    }
}

