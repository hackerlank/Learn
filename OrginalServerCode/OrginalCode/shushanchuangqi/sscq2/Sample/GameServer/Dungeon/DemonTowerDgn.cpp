#include "stdafx.h"
#include "Dungeon.h"
#include "DungeonMgr.h"
#include "Map.h"
#include "MapMgr.h"
#include "Player.h"
#include "Random.h"
#include "Protocols.h"
#include "User.h"
#include "NPC.h"
#include "NPCMgr.h"
#include "GameServerSysMail.h"
#include "SysMsgDefine.h"
#include "GameServerLog.h"
#include "DemonTowerDgn.h"
#include "DemonTowerMgr.h"
#include "Game2CenterDemonTowerC.h"
#include "DemonTowerSvrS.h"
#include "MonsterMgr.h"
///////////////////////////////////////////////////////////////
CDemonTowerDgn::CDemonTowerDgn(const SDgnInfo& rDgnInfo, UINT64 qwInstID, const CPlayerPtr& pPlayer) : CDungeon(rDgnInfo, qwInstID), 
    _pPlayer(pPlayer),_wTotalTurns(0),_dwGatherID(0),_dwCurFloorID(0)
{
    _vecAttackOrder = rDgnInfo.oDgnCfg.vecAttackOrder; 
}

CDemonTowerDgn::~CDemonTowerDgn()
{
}
bool CDemonTowerDgn::CanEnter(CPlayer& rPlayer)
{
    return CDungeon::CanEnter(rPlayer);
}
void CDemonTowerDgn::TimerCheck(UINT64 qwTick)
{
    //CDungeon::TimerCheck(qwTick);
    CGameMapPtr pCurMap = GetCurMap();
    if(pCurMap == NULL)
    {
        LOG_CRI << "_pCurMap is NULL";
        return;
    }
}

void CDemonTowerDgn::FailOver()
{
    CDungeon::FailOver();
}
void CDemonTowerDgn::ClearDungeon()
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer != NULL)
    {
        if(PlayerLeave(*pPlayer))
            _pPlayer.reset();
    }
}

bool CDemonTowerDgn::PlayerReEnter(CPlayer& rPlayer, SPoint& rPoint)
{
    if(!CDungeon::PlayerReEnter(rPlayer, rPoint))
        return false;

    _pPlayer = ToThisPtr(rPlayer);
    return true;
}

bool CDemonTowerDgn::PlayerEnter(CPlayer& rPlayer, SPoint* pPoint /*= NULL*/)
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer == NULL)
        return false;
    if(pPlayer->GetRoleID() != rPlayer.GetRoleID())
        return false;
    if(!CDungeon::PlayerEnter(rPlayer, pPoint))
        return false;
    SetDgnState(eDgnRuning);
    return true;
}

bool CDemonTowerDgn::PlayerLeave(CPlayer& rPlayer)
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer == NULL)
        return false;
    if(pPlayer->GetRoleID() != rPlayer.GetRoleID())
        return false;
    if(!CDungeon::PlayerLeave(rPlayer))
        return false;
    SetDgnState(eDgnDel_Over);
    _pPlayer.reset();

    rPlayer.SetDemonTowerFloorID(0); 
    rPlayer.SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_OnLeaveDemonTower(rPlayer.GetUserID()));

    return true;
}


void CDemonTowerDgn::SetDgnState(EDgnState eState)
{
    if(eState == _eDgnState)
    {
        return ;
    }
    switch (eState)
    {
        case eDgnFinish:
            {
                if(_eDgnState == eDgnRuning)//完成副本
                {
                    CPlayerPtr pPlayer = _pPlayer.lock();
                    if(NULL != pPlayer)
                    {
                    }
                    else
                    {
                        LOG_CRI << "Can NoT Find Player For Fisnish Player DGN";
                    }

                }

            }
            break;
        case eDgnDel_Over:
            {
                if(_eDgnState == eDgnRuning)//副本失败
                {               
                    CPlayerPtr pPlayer = _pPlayer.lock();
                    if(NULL != pPlayer)
                    {
                    }
                    else//发消息到DB，让其更改存档
                    {
                        LOG_CRI << "Can NoT Find Player For Fisnish Player DGN";
                    }
                }
                else if(_eDgnState == eDgnFinish)//奖励发送
                {
                    // DoAward();
                } 
            }
            break;
        case eDgnRuning://进入副本
            {
                CPlayerPtr pPlayer = _pPlayer.lock();
                if(NULL != pPlayer)
                {
                }

            }
            break;
        default :
            break;
    }
    CDungeon::SetDgnState(eState);
}
void  CDemonTowerDgn::OnMonsterDie(CMonster& rMonster, UINT64 qwKillRoleID,UINT64 qwBattleID )
{
    CPlayerPtr pPlayer = GetPlayer(); 
    if(pPlayer)
    {
        
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
         {
             TVecINT32 vecParam;
             vecParam.push_back(1);
             pEventMgr->OnEvent(eEventType_DemonTowerBattle,vecParam);
         }

        //过关
        if((pPlayer->GetTopDemonFloorID() +1) == _dwCurFloorID)
        {

            pPlayer->SetTopDemonFloorID(_dwCurFloorID);
            SFighterPropCFG& rFighterPropCFG = rMonster.GetFighterPropCfg();
            pPlayer->SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_OnPassDemonTower(pPlayer->GetUserID(),_dwCurFloorID,rFighterPropCFG._Color,rMonster.GetName()));
            g_DemonTowerMgr.TakePassPrize(*pPlayer,_dwCurFloorID);
            pPlayer->SendPkg(g_DemonTowerSvrS.BuildPkg_FloorPassNotify(_dwCurFloorID));

            SDemonTowerCFGExPtr pCfg = g_DemonTowerMgr.GetDemonTowerCFG(_dwCurFloorID);
            if(pCfg&&pCfg->_PrizeBox)
            {
                CreateGather(pCfg->_PrizeBox,15,20);
                _dwGatherID = pCfg->_PrizeBox;
                //采集物标志
                pPlayer->SetDemonFloorGather();
            }
            else
            {
                CGameMapPtr pMap = _pCurMap.lock();
                if(pMap)
                {
                    if(_dwCurFloorID != 100) 
                        pMap->AddSwitcherByIndex(1);
                }
            }


            CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
            if(pEventMgr)
            {
                TVecINT32 vecParam;
                vecParam.push_back(_dwCurFloorID);
                pEventMgr->OnEvent(eEventType_DemonTowerHighestChanging,vecParam);

            }
        }

        SDemonTowerPassPlayer oDemonTowerPassPlayer;
        oDemonTowerPassPlayer.qwUserID = pPlayer->GetUserID();
        oDemonTowerPassPlayer.dwCurFloorID =  _dwCurFloorID;
        oDemonTowerPassPlayer.dwPower = pPlayer->GetBattlePoint();
        oDemonTowerPassPlayer.wTurns = GetBattleRouds(); 
        oDemonTowerPassPlayer.qwReportID = qwBattleID;
        pPlayer->SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_OnKillMonster(oDemonTowerPassPlayer));
    }
}


const UINT32 DEMONTOWER_DEATH = 19;

void CDemonTowerDgn::OnPlayerDie(CCreature& rKiller,CPlayer& rPlayer)
{
    CPlayerPtr pPlayer = GetPlayer();
    if(pPlayer)
    {
        pPlayer->AddBuff(DEMONTOWER_DEATH);
        
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
         {
             TVecINT32 vecParam;
             vecParam.push_back(1);
             pEventMgr->OnEvent(eEventType_DemonTowerBattle,vecParam);
         }

    }
}
void CDemonTowerDgn::AddAttackTurns(UINT16 wTurns)
{
    _wTotalTurns += wTurns;
}


bool CDemonTowerDgn::CanAttackMonster(UINT16 wMonsterGroup)
{
    CPlayerPtr pPlayer = GetPlayer();
    if(pPlayer)
    {
       if(pPlayer->HasBuff(DEMONTOWER_DEATH))
        {
            SDBBuffInfo oDBBuffInfo;
            pPlayer->GetDBBuffData(DEMONTOWER_DEATH,oDBBuffInfo);
            pPlayer->SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgDemonTowerVSMonsterCD,BuildStrVec(oDBBuffInfo.dwBuffTime)));
            //CUser& rUser = pPlayer->GetUser();
            //rUser.SendSysMsg(eMsgDemonTowerVSMonsterCD,BuildStrVec(oDBBuffInfo.dwBuffTime));
            return false;
        }
    }

    return true;
}

bool CDemonTowerDgn::OnBegin()
{
    //TODO:初始化
    return CDungeon::OnBegin();
}

void CDemonTowerDgn::OnEnd()
{
    //TODO:副本销毁做的事情
    CDungeon::OnEnd();
}


bool CDemonTowerDgn::LoadMap()
{
    for(size_t i = 0; i < _rDgnInfo.oDgnCfg.vecMap.size(); ++i)
    {
        CGameMapPtr pMap = CMapMgr::CreateMap(_rDgnInfo.oDgnCfg.vecMap[i]);
        if(pMap == NULL)
        {
            LOG_CRI << "Load Dgn Map error";
            return false;
        }
        if(!_mapID2Map.insert(std::make_pair(pMap->GetMapID(), pMap)).second)
        {
            LOG_CRI << "Insert Dgn Map error";
            return false;
        }
    
        //地图层数
        // pMap->SetParam(eMapParamDemonFloorID,i+1);

        //_vecFloorMap.push_back(pMap);

        pMap->SetDungeon(shared_from_this());
        if(0 == i)
        {
            //first GameMap in dungeon
            _pCurMap = pMap;
        }
    }

    return true;
}

bool CDemonTowerDgn::PlayerEnterFloor(CPlayer& rPlayer,UINT32 dwFloorID)
{
    if((rPlayer.GetTopDemonFloorID() + 1) < dwFloorID)
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerLowFloor));
        return false;
    }

    /*
    if((rPlayer.GetTopDemonFloorID() + 1) ==  dwFloorID && rPlayer.IsSpawGather())
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerLowFloor));
        return false;
    }
    */


    //CGameMapPtr pMap = GetFloorMapByID(dwFloorID);
    //if(!pMap)
    //{
    //    return false;
    //}

    // _pCurMap = pMap;
    CGameMapPtr pMap = _pCurMap.lock();
    if(NULL == pMap)
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerErrorMap));
        return false;
    }
    
    pMap->ClearAllMonsters();
    pMap->ClearAllSwitchers();
    //pMap->ClearAllGathers();

    if(_dwGatherID)
        DestroyGather(_dwGatherID);

    if(dwFloorID == rPlayer.GetTopDemonFloorID() + 1)
    {
        SDemonTowerCFGExPtr pDemonTowerCFGEx = g_DemonTowerMgr.GetDemonTowerCFG(dwFloorID);
        if(!pDemonTowerCFGEx)
        {
            rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerErrorCFG));
            return false;
        }
        
        SPoint point(17.0,18.0);

        bool bAddRet = pMap->AddMonster(pDemonTowerCFGEx->_MonsterGroupID,&point);
        if(!bAddRet)
        {
            rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerErrorAddMonster));
            return false;
        }
    }
    else
    {
        if((dwFloorID == rPlayer.GetTopDemonFloorID()) && rPlayer.IsSpawGather())
        {
                SDemonTowerCFGExPtr pCfg = g_DemonTowerMgr.GetDemonTowerCFG(dwFloorID);
                if(pCfg&&pCfg->_PrizeBox)
                {
                    CreateGather(pCfg->_PrizeBox,15,20);
                    _dwGatherID = pCfg->_PrizeBox;
                }
                else
                {
                    if(dwFloorID != 100)
                        pMap->AddSwitcherByIndex(1);
                }
        }
        else
        {
            if(dwFloorID != 100)
                pMap->AddSwitcherByIndex(1);
        }

    }

    if(dwFloorID != 1)
        pMap->AddSwitcherByIndex(2);


    bool bRet = PlayerEnter(rPlayer,NULL);
    if(bRet)
    {
       const RoleBaseInfo rRoleBaseInfo = rPlayer.GetBaseInfo();
       _dwCurFloorID = dwFloorID;
       SDemonTowerEnterPlayer oDemonTowerEnterPlayer;
       oDemonTowerEnterPlayer.qwUserID  = rPlayer.GetUserID();
       oDemonTowerEnterPlayer.qwRoleID  = rPlayer.GetRoleID();
       oDemonTowerEnterPlayer.strName = rPlayer.GetName();
       oDemonTowerEnterPlayer.dwFloorID =  dwFloorID;
       oDemonTowerEnterPlayer.bySex     =  rPlayer.GetSex();
       oDemonTowerEnterPlayer.byLevel   =  rPlayer.GetLevel();
       oDemonTowerEnterPlayer.dwCareer  = rRoleBaseInfo.eCareer;
       oDemonTowerEnterPlayer.dwPower   = rPlayer.GetBattlePoint();
       rPlayer.SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_OnEnterDemonTower(oDemonTowerEnterPlayer));
       rPlayer.SetDemonTowerFloorID(dwFloorID);
    }
    else
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerFailEnterDgn));
    }
    return bRet;
}

CGameMapPtr CDemonTowerDgn::GetFloorMapByID(UINT32 dwFloorID)
{
    if(dwFloorID < 1 || dwFloorID > _vecFloorMap.size())
    {
        return NULL;
    }

    //return _vecFloorMap[dwFloorID-1];
    return _pCurMap.lock();

}

  //-qf- 2014/05/28
//是否可以跳转地图
bool CDemonTowerDgn::IsCanJumpMap( CPlayer* pPlayer,CGameMapPtr& pCurMap,CGameMapPtr& pDestMap) 
{ 
    return true; 
}

//玩家离开副本事件
void CDemonTowerDgn::OnBeforeLeaveDgn( CPlayer* pPlayer) 
{
    
}

//进入副本
void CDemonTowerDgn::OnEnterDgn(CPlayer* pPlayer)
{

}

//进入地图之后事件（在进入副本函数之后调用）
void CDemonTowerDgn::OnEnterMap(CPlayer* pPlayer,CGameMapPtr& pCurMap) 
{

}
   
//采集一个物品
void CDemonTowerDgn::OnGather(UINT16 wGatherID, CPlayer& rPlayer)
{
    rPlayer.OnDemonFloorGathered();
    CGameMapPtr pMap = _pCurMap.lock();
    if(pMap)
    {
         if(_dwCurFloorID != 100) 
            pMap->AddSwitcherByIndex(1);
    }

}
 
