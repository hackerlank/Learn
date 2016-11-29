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
#include "Loot.h"
#include "SysMsgDefine.h"
#include "GameServerLog.h"
#include "PlayerDgn.h"
void SDgnInfo::LuaInit()
{
    if(!_bLoad)
    {
        _bHasOnEnterLimit = Config.GetScript().Dungeon_HasOnEnterLimit(oDgnCfg.wDgnID);
        _bHasOnInit =Config.GetScript().Dungeon_HasOnInit(oDgnCfg.wDgnID);
        _bHasOnTimer= Config.GetScript().Dungeon_HasOnTimer(oDgnCfg.wDgnID);
        _bHasOnEnd=Config.GetScript().Dungeon_HasOnEnd(oDgnCfg.wDgnID);
        _bHasOnFinish=Config.GetScript().Dungeon_HasOnFinish(oDgnCfg.wDgnID);
        _bLoad =true;
    }
}

bool SDgnInfo::CheckScriptOnEnterLimit() const
{
    return _bHasOnEnterLimit;
}

bool SDgnInfo::CheckScriptOnInit() const 
{
    return _bHasOnInit;
}

bool SDgnInfo::CheckScriptOnTimer() const 
{
    return  _bHasOnTimer;
}

bool SDgnInfo::CheckScriptOnEnd() const 
{
    return _bHasOnEnd;
}

bool SDgnInfo::CheckScriptOnFinish() const
{
    return _bHasOnFinish;
}

bool CDungeon::Init(UINT16 wMapID)
{
    if(!LoadMap(wMapID))
    {
        LOG_CRI << "Load Dungeon Map fails! DgnID: " << GetDgnID();
        return false;
    }
    if(!OnBegin())
    {
        LOG_CRI << "OnBegin fails! DgnID: " << GetDgnID();
        return false;
    }
    if(_rDgnInfo.CheckScriptOnInit())
    {
        Config.GetScript().Dungeon_OnInit(_rDgnInfo.oDgnCfg.wDgnID,this);

    }
    SetDgnState(eDgnWaitPlayer);
    return true;
}

bool CDungeon::LoadMap(UINT16 wMapID)
{
    bool bSet = false;
    CGameMapPtr pFirstMap;
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

        pMap->SetDungeon(shared_from_this());

        if(wMapID != 0)
        {
            if(_rDgnInfo.oDgnCfg.vecMap[i] == wMapID)
            {
                _pCurMap = pMap;
                bSet = true;
            }
        }
        else if(0 == i)
        {
            //first GameMap in dungeon
            _pCurMap = pMap;
            bSet = true;
        }

        if (i == 0)
            pFirstMap = pMap;
    }
    LOG_WRN << "bSet = " << (bSet?"true":"false") << ";";
    if (!bSet)
    {
        _pCurMap = pFirstMap;
    }

    return _pCurMap.lock() != NULL;
}

CGameMapPtr CDungeon::GetMap(UINT16 wMapID)
{
    auto itf = _mapID2Map.find(wMapID);
    if(itf != _mapID2Map.end())
    {
        return itf->second;
    }
    return NULL;
}
void CDungeon::CreateMonster(UINT16 wMonsterGroup,float fX,float fY)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        SPoint point(fX,fY);
        pMap->AddMonster(wMonsterGroup,&point);
    }
}
void CDungeon::CreateMonsterIfNotExist(UINT16 wMonsterGroup,float fX,float fY)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        SPoint point(fX,fY);
        pMap->AddMonsterIfNotExist(wMonsterGroup,&point);
    }
}

void CDungeon::DestroyNpc(UINT16 wNpcId)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->DelNpcById(wNpcId);
    }

}
void CDungeon::DestroyMonster(UINT16 wMonsterGroup)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->DelMonsterByGroup(wMonsterGroup);
    }
}

void CDungeon::CreateGather(UINT16 wGatherId,float fX,float fY)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        SPoint point(fX,fY);
        pMap->AddGather(wGatherId,&point);
    }
}
void CDungeon::DestroyGather(UINT16 wGatherId)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->DelGatherByGather(wGatherId);
    }
}

bool CDungeon::CanDestroy(time_t tNow)
{
    return GetDgnState() == eDgnDel_Over;
}
bool CDungeon::CanEnter(CPlayer& rPlayer)
{
    return GetDgnState() != eDgnDel_Over;
}

bool CDungeon::PlayerEnter(CPlayer& rPlayer, const SPoint* pPoint/* = NULL*/)
{
    CGameMapPtr pCurMap = GetCurMap();
    if(pCurMap == NULL)
        return false;

    SPoint oPoint;
    if(pPoint == NULL)
    {
        oPoint.fX = pCurMap->GetMapInfo().oRealivePoint.fX;
        oPoint.fY = pCurMap->GetMapInfo().oRealivePoint.fY;
    }
    else
    {
        oPoint = *pPoint;
    }
    if(!rPlayer.JumpMap(pCurMap, oPoint))
    {
        LOG_CRI << "player jump map error";
        return false;
    }
    rPlayer.EnterDgn(this,true);
    //OnEnter(rPlayer);

    SDgnLogPtr ptrLog(new SDgnLog());
    if(NULL == ptrLog)
        return false;
    NLogDataDefine::SDgnLog& rLog = *ptrLog;

    rLog.wDgnType = GetDgnID();
    rLog.qwDgnInsID = GetDgnInstID();
    rLog.qwUserID =  rPlayer.GetUser().GetUserID();
    rLog.eOpType = NLogDataDefine::EDgnOpType_PLAYERENTER;

    CGameServerLog::LogToDB(ptrLog);
    TVecINT32 vecData;
    vecData.push_back(GetDgnID());
    rPlayer.GetEventMgr()->OnEvent(eEventType_DungeonEnter,vecData);

    return true;
}

bool CDungeon::PlayerReEnter(CPlayer& rPlayer, SPoint& rPoint)
{
    CGameMapPtr pCurMap = GetCurMap();
    if(pCurMap == NULL)
        return false;

    if(rPlayer.GetCurMapID() != pCurMap->GetMapID())
    {
        rPoint.fX = pCurMap->GetMapInfo().oRealivePoint.fX;
        rPoint.fY = pCurMap->GetMapInfo().oRealivePoint.fY;
    }
    CGameMapPtr pPlayerCurMap  = rPlayer.GetMap();
    if(pPlayerCurMap == pCurMap)
    {
        pPlayerCurMap->PlayerDisappear(rPlayer);
    }
    if(!rPlayer.JumpMap(pCurMap, rPoint))
    {
        LOG_CRI << "player jump map error";
        return false;
    }

    return true;
}

bool CDungeon::PlayerLeave(CPlayer& rPlayer)
{
    SDgnLogPtr ptrLog(new SDgnLog());
    if(NULL == ptrLog)
        return false;
    NLogDataDefine::SDgnLog& rLog = *ptrLog;

    rLog.wDgnType = GetDgnID();
    rLog.qwDgnInsID = GetDgnInstID();
    rLog.qwUserID =  rPlayer.GetUser().GetUserID();
    rLog.eOpType = NLogDataDefine::EDgnOpType_PLAYERLEAVE; 
    TVecINT32 vecData;
    vecData.push_back(GetDgnID());
    string strParam;
    GetLogString(strParam);
    rPlayer.GetEventMgr()->OnEvent(eEventType_DungeonLeave,vecData,strParam);

    CGameServerLog::LogToDB(ptrLog);
    rPlayer.CheckLastPend();    

    return rPlayer.LeaveDgn(true,_rDgnInfo.oDgnCfg.sOutConfig);
}

void CDungeon::OnTimer(time_t tNow)
{
    if(_rDgnInfo.CheckScriptOnTimer())
    {
        for (auto iter =mapTimer.begin();iter != mapTimer.end();)
        {
            if(iter->second > tNow)
            {
                Config.GetScript().Dungeon_OnTimer(_rDgnInfo.oDgnCfg.wDgnID,this,iter->first);
                iter = mapTimer.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
    UINT32 dwIntral =  tNow - _tStateTimer ;
    switch (_eDgnState)
    {
        case eDgnWaitPlayer:
            {
                if( dwIntral > eTimerWaitPlayer)
                {
                    SetDgnState(eDgnDel_Over);
                    LOG_CRI << "WaitPlayer Fails :"<<  GetDgnID();
                }

            }
            break;
        case eDgnFinish:
            {
                if(dwIntral > eTimerFinish)
                {
                    _eOverSource = eOver_Finish;
                    SetDgnState(eDgnDel_Over);

                }
            }
            break;
        default:
            break;
    }
}

void CDungeon::FailOver()
{
    if(_eDgnState != eDgnDel_Over)
        SetDgnState(eDgnDel_Over);
}

void CDungeon::OnMonsterDie(CMonster& rMonster, UINT64 qwKillRoleID /*= 0*/,UINT64 qwBattleID)
{
    // TODO
}
void CDungeon::OnGather(UINT16 wGatherID, CPlayer& rPlayer)
{
    //TODO
}

bool CDungeon::IsNoPerson()
{
    CGameMapPtr pCurMap = GetCurMap();
    if(pCurMap == NULL)
    {
        LOG_CRI << "_pCurMap is NULL";
        return true;
    }
    const TMapID2Player& mapID2Player = pCurMap->GetPlayerMap();
    return mapID2Player.empty();

}

void CDungeon::SetTimer(UINT16 wTimerId,UINT32 dwTimerIntral)
{
    mapTimer[wTimerId] = time(NULL) + dwTimerIntral;
}

void CDungeon::SetParam(UINT16 wParamId,UINT32 dwParamVal)
{
    mapParam[wParamId] = dwParamVal;
}

UINT32 CDungeon::GetParam(UINT16 wPramId)
{
    auto  iter = mapParam.find(wPramId);
    if(iter != mapParam.end())
    {
        return iter->second;
    }
    return -1;
}

void CDungeon::EndTimer(UINT16 wTimerId)
{
    mapTimer.erase(wTimerId);
}
void CDungeon::SetDgnState(EDgnState eState)
{ 
    //LOG_INF << "SetDgnState :" <<eState;
    _eDgnState = eState;
    if(_eDgnState==eDgnDel_Over && _rDgnInfo.CheckScriptOnEnd())
    {
        Config.GetScript().Dungeon_OnEnd(_rDgnInfo.oDgnCfg.wDgnID,this);

    }
    if(_eDgnState==eDgnFinish && _rDgnInfo.CheckScriptOnFinish())
    {
        Config.GetScript().Dungeon_OnFinish(_rDgnInfo.oDgnCfg.wDgnID,this);

    }

    if(_eDgnState == eDgnFinish || _eDgnState == eDgnDel_Over)
    {
        SDgnLogPtr ptrLog(new SDgnLog());
        if(NULL == ptrLog)
            return;
        NLogDataDefine::SDgnLog& rLog = *ptrLog;

        rLog.wDgnType = GetDgnID();
        rLog.qwDgnInsID = GetDgnInstID();
        rLog.qwUserID =  0;
        if(GetDgnType() == ePlayerDgn || eGatherDgn == GetDgnType())
        {
            CPlayerDgn *pDgn = dynamic_cast<CPlayerDgn*>(this);
            if(pDgn != NULL)
            {
                CPlayerPtr pPlayer = pDgn->GetPlayer();
                if(pPlayer != NULL)
                {
                    rLog.qwUserID = pPlayer->GetUser().GetUserID();
                    if(_eDgnState == eDgnFinish)
                    {
                        TVecINT32 vecData;
                        vecData.push_back(pDgn->GetDgnID());
                        string strParam;
                        pDgn->GetLogString(strParam);
                        pPlayer->GetEventMgr()->OnEvent(eEventType_DungeonFinish,vecData,strParam);

                        g_Game2CenterCommC.Send_SendWonderType(NGame2CenterComm::eActDungon,pPlayer->GetRoleID(),pDgn->GetDgnID());
                        vecData.clear();
                        vecData.push_back(1);
                        pPlayer->GetEventMgr()->OnEvent(eEventType_DungeonFinishAndAuto,vecData);

                        {
                        //    TVecINT32 vecParam;
                        //    vecParam.push_back(_rDgnInfo.oDgnCfg._Type2);
                        //    vecParam.push_back(1);
                        //    pPlayer->OnEvent(eEventType_DungeonFinishType,vecParam);
                        }
                        if(_rDgnInfo.oDgnCfg.sOutConfig.wMapId > 0 )
                        pPlayer->SaveMapPoint(_rDgnInfo.oDgnCfg.sOutConfig.wMapId,_rDgnInfo.oDgnCfg.sOutConfig.fPosX,_rDgnInfo.oDgnCfg.sOutConfig.fPosY);

                    }
                }

            }
            if(_eDgnState == eDgnDel_Over)
            {
                rLog.eOpType = NLogDataDefine::EDgnOpType_DESTROY; 
            }
            else 
            {
                rLog.eOpType = NLogDataDefine::EDgnOpType_FINISH; 

                CGameServerLog::LogToDB(ptrLog);
            }

            _tStateTimer = time(NULL);
        }
    }
}

void CDungeon::TransMap(UINT16 wMap,float fX, float fy)
{
    CGameMapPtr pPreMap = _pCurMap.lock();
    if(pPreMap == NULL)
    {
        return ;
    }
    const TMapID2Player& mapPlayer = pPreMap->GetPlayerMap();
    CGameMapPtr pMap = GetMap(wMap);
    if(pMap == NULL)
    {
        return ;
    }
    SetCurMap(pMap);
    SPoint oPoint(fX,fy);
    if(fX == 0 && fy == 0)
    {
        oPoint.fX = pMap->GetMapInfo().oRealivePoint.fX;
        oPoint.fY = pMap->GetMapInfo().oRealivePoint.fY;

    }
    for(auto itPlayer = mapPlayer.begin(); itPlayer != mapPlayer.end();)
    {
        CPlayerPtr pPlayer = itPlayer->second.lock();
        ++itPlayer;
        if(pPlayer != NULL && !pPlayer->JumpMap(pMap, oPoint,0))
        {
            LOG_CRI << "player jump map error";
        }
    }

}

//设置阻挡
void CDungeon::CreateBlockByIndex(UINT16 wIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->CreateBlockByIndex(wIndex);
    }

}
//撤销阻挡
void CDungeon::DestroyBlockByIndex(UINT16 wIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->DestroyBlockByIndex(wIndex);
    }
}

//增加区域
void CDungeon::CreateAreaByIndex(UINT16 wIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->CreateAreaByIndex(wIndex);
    }
}
//撤销区域
void CDungeon::DestroyAreaByIndex(UINT16 wIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->DestroyAreaByIndex(wIndex);
    }
}

void CDungeon::AddSwitcherByIndex(UINT8 byIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->AddSwitcherByIndex(byIndex);
    }

}

void CDungeon::SwitcherDestroyByIndex(UINT8 byIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->SwitcherDestroyByIndex(byIndex);
    }
}

void CDungeon::AddGatherByIndex(UINT8 byIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->AddGatherByIndex(byIndex);
    }
}

void CDungeon::GatherDestroyByIndex(UINT8 byIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->GatherDestroyByIndex(byIndex);
    }
}

void CDungeon::AddNpcByIndex(UINT8 byIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->AddNpcByIndex(byIndex);
    }
}

void CDungeon::NpcDestroyByIndex(UINT8 byIndex)
{
    CGameMapPtr pMap = GetCurMap();
    if(pMap)
    {
        pMap->NpcDestroyByIndex(byIndex);
    }
}


