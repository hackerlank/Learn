#include "stdafx.h"
#include "Protocols.h"
#include "Creature.h"
#include "UserMgr.h"
#include "Player.h"
#include "MapMgr.h"
#include "NPC.h"
#include "ItemMgr.h"
#include "GameScript.h"
#include "Monster.h"
#include "Switcher.h"
#include "JumpSwitcher.h"
#include "Blocker.h"
#include "Gather.h"
#include "MapArea.h"
#include "Dungeon.h"
//接收：角色移动请求
void CMapProtS::OnRecv_PlayerMoveReq(
        UINT16 wMapID, //地图ID
        const TVecPosition& vecPosition //移动位置列表
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return;
    }
    CGameMapPtr pMap = pPlayer->GetMap();
    if(pMap == NULL)
    {
        LOG_DBG << "Player is not on map! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return;
    }
    if(pMap->IsBlockPoint(pPlayer->GetPoint()))//在阻挡点，那么放到非阻挡点
    {
        LOG_CRI<<"In Block reset!!!";
        SPoint rPoint;
        pMap->GetMovablePoint(pPlayer->GetPoint(),rPoint);
        pPlayer->SetPoint(rPoint);
        Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint(),vecPosition);
        return;

    }
    static UINT16 eWorldBossDeadBufferID = 15;

    if(pPlayer->HasBuff(eWorldBossDeadBufferID))
    {
        LOG_CRI<<"IsDead In worldboss!!!";
        Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint(),vecPosition);
        return;
    }

    if(pPlayer->IsDead())
    {
        LOG_CRI<<"player IsDead!! uid:"<<pPlayer->GetUserID();
        Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint(),vecPosition);
        return;
    }

    if(pMap->GetMapID() != wMapID)
        return;

    // TODO:
    /*
       if((pPlayer->GetRoleState() != eRoleLive && pPlayer->GetRoleState() != eRoleGhost) ||
       pPlayer->GetFightInfo().HasFight() || pPlayer->IsInDummyFight())
       {
       Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint());
       return;
       }
       */


    //最端移动间隔检查
    if(!pPlayer->GetWalker().CheckAndSetLastMoveTime())
    {
        //Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint(),vecPosition);
        return;
    }

    TVecPoint vecPoint(vecPosition.size());
    for(size_t i = 0; i < vecPosition.size(); ++i)
        vecPoint[i] = vecPosition[i];
    /*
       LOG_INF << "Tick: " << GetTickCount() << ", " << pPlayer->GetRoleID() << " move from " << pPlayer->GetPoint() << " to:";
       for(size_t i = 0, size = vecPosition.size(); i < size; ++i)
       LOG_INF << "\t\t[" << vecPosition[i].fX << ", " << vecPosition[i].fY << "]";
       */
    if(!pPlayer->GetWalker().CheckPath(vecPoint))
    {
        Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint(),vecPosition);
        return;
    }
    /*
       LOG_INF<<"This Path";
       LOG_INF<<"Cur POINT " << "fX:" <<pPlayer->GetPoint().fX <<" fY:"<<pPlayer->GetPoint().fY;
       for (auto i = 0;i != vecPoint.size();i++)
       {
       LOG_INF << "fX:" <<vecPoint[i].fX <<" fY:"<<vecPoint[i].fY;
       }
    // TODO:
    */
    //pPlayer->ClearFightFinishTime();
    // LOG_CRI << "Start walk:" << GetTickCount();
    if(!pPlayer->GetWalker().StartPath(vecPoint,PLAYER_WALK_TIME_INTERVAL))
    {
        Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint(),vecPosition);
        LOG_CRI << "move Fail for StartPath(vecPoint)";
        for (size_t i = 0;i != vecPoint.size();i++)
        {
            LOG_CRI << "fX:" <<vecPoint[i].fX <<" fX:"<<vecPoint[i].fY;
        }
        SPoint rPoint;
        pMap->GetMovablePoint(pPlayer->GetPoint(),rPoint);
        pPlayer->SetPoint(rPoint);
        Send_PlayerMoveFail(pPlayer->GetRoleID(), pPlayer->GetPoint(),vecPosition);

        return;
    }
    if(pPlayer->IsDead() && pPlayer->IsInDungeon())
    {
        return ;
    }
    pPlayer->GetActionManager().CancelAction(eACTION_SIT);
}
//接收：角色停止移动
void CMapProtS::OnRecv_PlayerStopReq(
        UINT16 wMapID, //地图ID
        const SPosition& StopPos //停止点
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return;
    }
    CGameMapPtr pMap = pPlayer->GetMap();
    if(pMap == NULL)
    {
        LOG_DBG << "Player is not on map! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return;
    }

    if(pMap->GetMapID() != wMapID)
        return;
    pPlayer->GetWalker().Abort();

}
//接收：获取玩家的外观信息
bool CMapProtS::OnRecv_GetPlayerAppear(
        UINT64 qwUserID, //目标玩家ID
        shared_func<SGetPlayerAppearAck>& fnAck //返回回调函数
        )
{

    UINT64 qwCurUserID = GetCurUsrID();

    LOG_DBG<<"onload PlayerAppear:"<<qwUserID;

    CUserMgr::LoadUser(qwUserID,[fnAck,qwCurUserID,qwUserID](CUserPtr pOtherUser){
            if(pOtherUser == NULL)
            {
            LOG_CRI<<"Can not Find Player" << qwUserID;
            fnAck->byRet = 1;
            return ;
            }

            CUserPtr pUser = CUserMgr::GetUserByUserID(qwCurUserID);
            if (!pUser)
            {
            LOG_CRI << "Can't find User! UsrID: " << qwCurUserID;
            fnAck->byRet = 1;
            return ;
            }

            CPlayerPtr pPlayer = pOtherUser->GetPlayer();
            pPlayer->GetPlayerAppear(fnAck->rPlayerAppear);
            fnAck->byRet = 0;
            LOG_DBG<<"load PlayerAppear:"<<pOtherUser->GetUserID();
            return ;
    });
    return true;
}

//接收：请求跳地图
bool CMapProtS::OnRecv_JumpMap(
        UINT16 wMapID, //地图ID
        UINT8 byIndex, //地图序号,255表示任意地图
        shared_func<SJumpMapAck>& fnAck //返回回调函数
        ) 
{
    fnAck->wMapID = wMapID;
    fnAck->byIndex = byIndex;
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        fnAck->byRet = 1;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->byRet = 1;  
        return false;
    }
    CGameMapPtr pMap = pPlayer->GetMap();
    if(pMap == NULL)
    {
        fnAck->byRet = 1;  
        return false;

    }
    if(!pMap->GetMapInfo().IsNormal())
    {
        fnAck->byRet = 1;  
        return true;
    }
    bool bTransSame = (pMap->GetMapID() == wMapID);
    UINT8 bySelfIndex =CMapMgr::GetMapIndex(pMap);
    if(bTransSame && byIndex == bySelfIndex)
    {
        fnAck->byRet = 1;  
        return true;

    }
    SMapInfoPtr pDestMapInfo = CMapMgr::GetMapInfo(wMapID);
    if(pDestMapInfo == NULL || !pDestMapInfo->IsNormal())
    {
        fnAck->byRet = 1;  
        return true;
    }

    if(pPlayer->GetLevel() < pDestMapInfo->wLeastlevel)
    {
        fnAck->byRet = 1;  
        return true;
    }
    if(!bTransSame)
    {
        SPoint oPoint(pDestMapInfo->oRealivePoint.fX,pDestMapInfo->oRealivePoint.fY);
        pPlayer->JumpMap(wMapID, oPoint);
    }
    else
    {
        CGameMapPtr pDestMap = CMapMgr::GetMap(wMapID,byIndex);
        if(NULL == pDestMap|| pDestMap == pMap || pDestMap->IsFull())
        {
            fnAck->byRet = 1;  
            return true;
        }
        pPlayer->JumpMap(pDestMap,pPlayer->GetPoint()); 
    }
    pPlayer->GetActionManager().CancelAction(eACTION_SIT);
    return true;

}
//接收：请求地图负载
bool CMapProtS::OnRecv_GetMapOverLoad(
        UINT16 wMapID, //地图ID
        shared_func<SGetMapOverLoadAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    fnAck->wMapID = wMapID;
    CMapMgr::GetMapLoad(wMapID,fnAck->vecLoad);
    return true;

}




////////////////////////////////////////////////////////////////////////
void CMapProtS::NotifyPlayerAppear(TVecUINT64& rVecUsrID, CPlayer& rPlayer, bool bBorn)
{
    if(rVecUsrID.empty())
        return;
    SPlayerAppear appear;
    rPlayer.GetPlayerAppear(appear);
    SendClt_PlayerAppear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rPlayer.GetRoleID(), appear, rPlayer.GetPoint(), rPlayer.GetDir(), rPlayer.GetAppearState(), bBorn);
}

void CMapProtS::NotifyCreatureDisappear(TVecUINT64& rVecUsrID, CCreature& rCreature, bool bFade)
{
    if(rVecUsrID.empty())
        return;
    SendClt_CreatureDisappear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rCreature.GetCreatureID(), bFade);
}

void CMapProtS::NotifySurroundAppear(CPlayer& rPlayer, set<CBaseObjPtr>& rSetObj)
{
    if(!rPlayer.IsOnActiveMap())
        return;
    UINT64 qwUsrID = rPlayer.GetUserID();
    for(auto it = rSetObj.begin(); it != rSetObj.end(); ++it)
    {
        CBaseObj& rBaseObj = **it;
        switch(rBaseObj.GetObjType())
        {
            case eObjPlayer:
                {
                    CPlayer& rOtherPlayer = (CPlayer&)rBaseObj;
                    if(rPlayer.GetUserID() == rOtherPlayer.GetUserID())
                    {
                        SPlayerAppear appear;
                        rOtherPlayer.GetPlayerAppear(appear);
                        SendClt_NotifyAppear(&qwUsrID, 1, rOtherPlayer.GetRoleID(), appear, rOtherPlayer.GetPoint(), rOtherPlayer.GetDir(), rOtherPlayer.GetAppearState());
                    }
                    else
                    {
                        SPlayerAppear appear;
                        rOtherPlayer.GetPlayerAppear(appear);
                        SendClt_PlayerAppear(&qwUsrID, 1, rOtherPlayer.GetRoleID(), appear, rOtherPlayer.GetPoint(), rOtherPlayer.GetDir(), rOtherPlayer.GetAppearState(), false);
                    }
                    NotifyCreatureMove(rPlayer, rOtherPlayer);
                }
                break;
            case eObjNpc:
                {
                    CNpc& rNpc = (CNpc&)rBaseObj;
                    SNpcAppear oNpcAppear;
                    rNpc.GetNpcAppear(oNpcAppear);
                    SendClt_NpcAppear(&qwUsrID, 1, rNpc.GetCreatureID(), oNpcAppear, rNpc.GetPoint(), rNpc.GetDir(), false);
                }
                break;

            case eObjMonster:
                {
                    CMonster& rMonster = (CMonster&)rBaseObj;
                    SMonsterAppear oMonsterAppear;
                    rMonster.GetMonsterAppear(oMonsterAppear);
                    SendClt_MonsterAppear(&qwUsrID, 1, rMonster.GetCreatureID(), oMonsterAppear, rMonster.GetPoint(), rMonster.GetDir(), rMonster.GetAppearState(), false);
                    NotifyCreatureMove(rPlayer, rMonster);
                }
                break;
            case eObjSwitcher:
                {
                    CSwitcher& rSwitcher = (CSwitcher&)rBaseObj;
                    SSwitcherAppear oSwitcherAppear;
                    rSwitcher.GetSwitcherAppear(oSwitcherAppear);
                    SendClt_SwitcherAppear(&qwUsrID, 1, rSwitcher.GetInstID(), oSwitcherAppear, rSwitcher.GetPoint(), rSwitcher.GetDir(), false);
                }
                break;
            case eObjBlocker:
                {
                    CBlocker& rBlocker = (CBlocker&)rBaseObj;
                    SBlockerAppear oBlockerAppear;
                    rBlocker.GetBlockerAppear(oBlockerAppear);
                    SendClt_BlockerAppear(&qwUsrID, 1, rBlocker.GetInstID(), oBlockerAppear, rBlocker.GetPoint(), rBlocker.GetDir(), false);
                }
                break;
            case eObjGather:
                {
                    IGather& rGather = (IGather&)rBaseObj;
                    SGatherAppear oGatherAppear;
                    rGather.GetGatherAppear(oGatherAppear, qwUsrID);
                    SendClt_GatherAppear(&qwUsrID, 1, rGather.GetInstID(), oGatherAppear, rGather.GetPoint(), rGather.GetDir(), false);
                }
                break;
            case eObjArea:
                {
                    CMapArea& rMapArea = (CMapArea&)rBaseObj;
                    SAreaAppear oMapAreaAppear;
                    rMapArea.GetAreaAppear(oMapAreaAppear);
                    SendClt_AreaAppear(&qwUsrID, 1, rMapArea.GetInstID(), oMapAreaAppear, rMapArea.GetPoint());


                }
                break;
            default:
                LOG_CRI << "Unknown Object Type: " << rBaseObj.GetObjType();
        }
    }
}

void CMapProtS::NotifySurroundDisappear(CPlayer& rPlayer, set<CBaseObjPtr>& rSetObj)
{
    if(!rPlayer.IsOnActiveMap())
        return;
    UINT64 qwUsrID = rPlayer.GetUserID();
    for(auto it = rSetObj.begin(); it != rSetObj.end(); ++it)
    {
        CBaseObj& rBaseObj = **it;
        switch(rBaseObj.GetObjType())
        {
            case eObjPlayer:
            case eObjMonster:
            case eObjNpc:
                {
                    CCreature& rCreature = (CCreature&)rBaseObj;
                    SendClt_CreatureDisappear(&qwUsrID, 1, rCreature.GetCreatureID(), false);
                }
                break;
            case eObjSwitcher:
                {
                    CJumpSwitcher& rJumpSwitcher = (CJumpSwitcher&)rBaseObj;
                    SendClt_SwitcherDisappear(&qwUsrID, 1, rJumpSwitcher.GetInstID());
                }
                break;
            case eObjBlocker:
                {
                    CBlocker& rBlocker = (CBlocker&)rBaseObj;
                    SendClt_BlockerDisappear(&qwUsrID, 1, rBlocker.GetInstID());
                }
                break;
            case eObjGather:
                {
                    IGather& rGather = (IGather&)rBaseObj;
                    SendClt_GatherDisappear(&qwUsrID, 1, rGather.GetInstID(), false);
                }
                break;
            case eObjArea:
                {
                    CMapArea& rMapArea = (CMapArea&)rBaseObj;
                    SendClt_AreaDisappear(&qwUsrID, 1, rMapArea.GetInstID());
                }
                break;

            default:
                LOG_CRI << "Unknown Object Type: " << rBaseObj.GetObjType();
        }
    }
}

void CMapProtS::NotifyCreatureMove(CPlayer& rPlayer, CCreature& rCreature)
{
    CWalker& rWalker = rCreature.GetWalker();
    if(rWalker.GetState() == eWalkMove)
    {
        ::TVecPoint vecPathPoint;
        rWalker.GetCurPath(vecPathPoint);
        UINT64 qwUsrID = rPlayer.GetUserID();
        SendClt_NotifyCreatureMove(&qwUsrID, 1, rCreature.GetCreatureID(), SPoint::ToProtVecPoint(vecPathPoint));
    }
}

void CMapProtS::NotifyUserEnterMap(CPlayer& rPlayer,CGameMapPtr pMap)
{
    if(pMap == NULL)
    {
        LOG_CRI << "NO Map Enter";
        return ;
    }
    UINT16 wMapID = pMap->GetMapID();;
    UINT64 qwRoleID = rPlayer.GetRoleID();
    SPoint& rPoint = rPlayer.GetPoint();
    UINT64 qwDgnId = 0;
    UINT16 wDgnType = 0;
    CDungeonPtr  pDgn = pMap->GetDungeon();
    if( pDgn)
    {
        qwDgnId = pDgn->GetDgnInstID();
        wDgnType = pDgn->GetDgnID();
    }
    rPlayer.SendPkg(g_RoleEventProtS.BuildPkg_ChangeMapNotify(wMapID,qwDgnId,wDgnType));
    if(wMapID == 0)
        LOG_CRI << "Map Is Zero";
    else
        LOG_DBG << "Map ID = " << wMapID << ".";
    rPlayer.SendPkg(g_MapProtS.BuildPkg_UserEnterMapNtf(wMapID, qwRoleID,CMapMgr::GetMapIndex(pMap),CMapMgr::GetMapSize(wMapID), rPoint,rPlayer.GetDir()));
}

void CMapProtS::NotifyNpcAppear(TVecUINT64& rVecUsrID, CNpc& rNpc, bool bBorn)
{
    if(rVecUsrID.empty())
        return;
    SNpcAppear appear;
    rNpc.GetNpcAppear(appear);
    SendClt_NpcAppear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rNpc.GetCreatureID(), appear, rNpc.GetPoint(), rNpc.GetDir(), bBorn);
}
void CMapProtS::NotifyMonsterAppear(TVecUINT64& rVecUsrID, CMonster& rMonster, bool bBorn)
{
    if(rVecUsrID.empty())
        return;
    SMonsterAppear oAppear;
    rMonster.GetMonsterAppear(oAppear);
    SendClt_MonsterAppear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rMonster.GetCreatureID(), oAppear, rMonster.GetPoint(), rMonster.GetDir(), rMonster.GetAppearState(), bBorn);
    //TO DO:LogCreatureAppear(rVecUsrID, rMonster);
}

void CMapProtS::NotifySwitcherAppear(TVecUINT64& rVecUsrID, CSwitcher& rSwitcher, bool bBorn)
{
    if(rVecUsrID.empty())
        return;
    SSwitcherAppear oAppear;
    rSwitcher.GetSwitcherAppear(oAppear);
    SendClt_SwitcherAppear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rSwitcher.GetInstID(), oAppear, rSwitcher.GetPoint(), rSwitcher.GetDir(), bBorn);
}

void CMapProtS::NotifySwitcherDisappear(TVecUINT64& rVecUsrID, CSwitcher& rSwitcher, bool bFade)
{
    if(rVecUsrID.empty())
        return;
    SendClt_SwitcherDisappear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rSwitcher.GetInstID());
}


void CMapProtS::NotifyBlockerAppear(TVecUINT64& rVecUsrID, CBlocker& rBlocker, bool bBorn)
{
    if(rVecUsrID.empty())
        return;
    SBlockerAppear oAppear;
    rBlocker.GetBlockerAppear(oAppear);
    SendClt_BlockerAppear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rBlocker.GetInstID(), oAppear, rBlocker.GetPoint(), rBlocker.GetDir(), bBorn);
}

void CMapProtS::NotifyBlockerDisappear(TVecUINT64& rVecUsrID, CBlocker& rBlocker, bool bFade)
{
    if(rVecUsrID.empty())
        return;
    SendClt_BlockerDisappear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rBlocker.GetInstID());
}
void CMapProtS::NotifyGatherAppear(TVecUINT64& rVecUsrID, IGather& rGather, bool bBorn)
{
    if(rVecUsrID.empty())
        return;
    SGatherAppear oAppear;
    rGather.GetGatherAppear(oAppear);
    SendClt_GatherAppear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rGather.GetInstID(), oAppear, rGather.GetPoint(), rGather.GetDir(), bBorn);
}

void CMapProtS::NotifyGatherDisappear(TVecUINT64& rVecUsrID, IGather& rGather, bool bFade)
{
    if(rVecUsrID.empty())
        return;
    SendClt_GatherDisappear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rGather.GetInstID(), bFade);
}

void  CMapProtS::NotifyGatherChange(TVecUINT64& rVecUsrID, IGather& rGather)
{
    if(rVecUsrID.empty())
        return;
    SGatherAppear oAppear;
    rGather.GetGatherAppear(oAppear);
    SendClt_GatherChange(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rGather.GetInstID(), oAppear);

}
void  CMapProtS::NotifyMonsterChange(TVecUINT64& rVecUsrID, CMonster& rMonster)
{
    if(rVecUsrID.empty())
        return;
    SMonsterAppear oAppear;
    rMonster.GetMonsterAppear(oAppear);
    SendClt_MonsterChange(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rMonster.GetCreatureID(), oAppear);

}

void CMapProtS::NotifyAreaAppear(TVecUINT64& rVecUsrID, CMapArea& rMapArea)
{
    if(rVecUsrID.empty())
        return;
    SAreaAppear oAppear;
    rMapArea.GetAreaAppear(oAppear);
    SendClt_AreaAppear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rMapArea.GetInstID(), oAppear, rMapArea.GetPoint());

}

void CMapProtS::NotifyAreaDisappear(TVecUINT64& rVecUsrID, CMapArea& rMapArea)
{
    if(rVecUsrID.empty())
        return;
    SendClt_AreaDisappear(&rVecUsrID[0], (UINT16)rVecUsrID.size(), rMapArea.GetInstID());

}

