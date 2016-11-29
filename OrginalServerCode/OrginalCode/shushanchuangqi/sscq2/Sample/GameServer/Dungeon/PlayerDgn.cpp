#include "PlayerDgn.h"
#include "Player.h"
#include "User.h"
#include "DungeonMgr.h"
#include "GameServerLog.h"
#include "Protocols.h" 
#include "Map.h"
#include <sstream>
#include "FighterManager.h"
#include "Trump.h"
#include "Monster.h"
///////////////////////////////////////////////////////////////
CPlayerDgn::~CPlayerDgn()
{
    LOG_CRI << "delete CPlayerDgn()";
}
bool CPlayerDgn::CanEnter(CPlayer& rPlayer)
{
    return CDungeon::CanEnter(rPlayer);
}
void CPlayerDgn::OnTimer(time_t tNow)
{
    UpdateDgnProcess(_InsProcess.TimerCheck(tNow),_InsStar.TimerCheck(tNow));
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer != NULL)
    {
        if(_eDgnState == eDgnRuning && pPlayer->GetUser().GetOffLineTime() > eTimerLeave)
        {
            _eOverSource = eOver_SysTem;
            SetDgnState(eDgnDel_Over);
        }
    }
    CDungeon::OnTimer(tNow);
}

void CPlayerDgn::FailOver()
{
    _eOverSource = eOver_Logic;
    CDungeon::FailOver();
}
void CPlayerDgn::ClearDungeon()
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer != NULL)
    {
        CDungeon::PlayerLeave(*pPlayer);
        _pPlayer.reset();
    }
}

bool CPlayerDgn::PlayerReEnter(CPlayer& rPlayer, SPoint& rPoint)
{
    if(!CDungeon::PlayerReEnter(rPlayer, rPoint))
        return false;
    _pPlayer = ToThisPtr(rPlayer);
    PlayerRelive();
    return true;
}

bool CPlayerDgn::PlayerEnter(CPlayer& rPlayer, const SPoint* pPoint /*= NULL*/)
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer == NULL)
        return false;
    if(pPlayer->GetRoleID() != rPlayer.GetRoleID())
        return false;
    if(!CDungeon::PlayerEnter(rPlayer, pPoint))
        return false;
    SetDgnState(eDgnRuning);
    pPlayer->GetUser().GetTaskPkg().OnAction(*pPlayer,eProcessAction_sCopy,1);
    //发送副本进度
    _InsProcess.InitByID(_rDgnInfo.oDgnCfg.vecProcess);
    _InsStar.InitByID(_rDgnInfo.oDgnCfg.vecStar);
    //UpdateDgnProcess();
    return true;
}

bool CPlayerDgn::PlayerLeave(CPlayer& rPlayer)
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer == NULL)
        return false;
    if(pPlayer->GetRoleID() != rPlayer.GetRoleID())
        return false;
    if(!CDungeon::PlayerLeave(rPlayer))
        return false;
    _eOverSource = eOver_Leave;
    SetDgnState(eDgnDel_Over);
    _pPlayer.reset();

    return true;
}

void CPlayerDgn::SetDgnState(EDgnState eState)
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
                        pPlayer->GetDgnPkg().PlayerCompleteDgn(_rDgnInfo.oDgnCfg.wDgnID,_InsStar.GetSucNum());//记录玩家完成副本
                        //pPlayer->GetActivityPkg().CheckActivityPoint(EPOINTTYPE_PASS_DGN);
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
                if(_eOverSource == eOver_Leave ||_eOverSource == eOver_Logic)//副本失败
                {               
                    CPlayerPtr pPlayer = _pPlayer.lock();
                    if(NULL != pPlayer)
                    {
                        pPlayer->GetDgnPkg().UpadePlayerDgnInfoForOver(_rDgnInfo.oDgnCfg.wDgnID);//副本结束
                    }
                    else//发消息到DB，让其更改存档
                    {
                        LOG_CRI << "Can NoT Find Player For Fisnish Player DGN";
                    }
                }
            }
            break;
        case eDgnRuning://进入副本
            {
                CPlayerPtr pPlayer = _pPlayer.lock();
                if(NULL != pPlayer)
                {
                    pPlayer->GetDgnPkg().UpadePlayerDgnInfoForEnter(_rDgnInfo.oDgnCfg.wDgnID);//记录玩家进入副本
                }

            }
            break;
        default :
            break;
    }
    CDungeon::SetDgnState(eState);
}
void CPlayerDgn::OnGather(UINT16 wGatherID, CPlayer& rPlayer)
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer == NULL)
        return ;
    if(pPlayer->GetRoleID() != rPlayer.GetRoleID())
        return ;
    UpdateDgnProcess( _InsProcess.GatherFinish(wGatherID),_InsStar.GatherFinish(wGatherID));
}

void  CPlayerDgn::OnMonsterDie(CMonster& rMonster, UINT64 qwKillRoleID,UINT64 qwBattleID )
{ 
    UINT16 wMonsterGroupID = rMonster.GetGroupID();
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer == NULL)
        return ;
    if(GetDgnType() == ePlayerDgn)
    {
        for(auto it = _vecAttackOrder.begin();it != _vecAttackOrder.end();it++)
        {
            if(wMonsterGroupID == *it)
            {
                _vecAttackOrder.erase(it);
                break;
            }
        }
    }
    UpdateDgnProcess(_InsProcess.KillMonster(wMonsterGroupID),_InsStar.KillMonster(wMonsterGroupID));

}
void CPlayerDgn::DoFinish(UINT64 qwBattleID)
{
    if(_eDgnState == eDgnFinish)
    {
        return;
    }
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer != NULL)
    {
        TVecItemGenInfo vecItems;
        TVecResource vecResource;
        CDungeonMgr::AwardToPlayer(_rDgnInfo,_InsStar.GetSucNum(),*pPlayer,true,&vecItems,&vecResource);
        pPlayer->SendPkg(g_DungeonProtS.BuildPkg_NotifyDgnAward(_qwInstID, _rDgnInfo.oDgnCfg.wDgnID,qwBattleID,_InsStar.GetSucNum(),vecItems,vecResource));
        pPlayer->PendDrop(vecItems,vecResource,PendDgn);
       /*
        UINT8 byStar = _InsStar.GetSucNum();
        TVecINT32 vecParam;
        vecParam.push_back(GetDgnID());
        vecParam.push_back(byStar);
        pPlayer->OnEvent(eEventType_DungeonStar,vecParam);
        */
        pPlayer->PendParam(PendDgn,GetDgnID(),_InsStar.GetSucNum());


    }
    SetDgnState(eDgnFinish);
}

void CPlayerDgn::FinishDgn(CPlayer &rPlayer)
{
    DoFinish();
}
void CPlayerDgn::AddAttackTurns(UINT16 wTurns)
{
    UpdateDgnProcess(_InsProcess.AddTurns(wTurns),_InsStar.AddTurns(wTurns));

}
void CPlayerDgn::ArriveArea(UINT16 wAreaId)
{
    UpdateDgnProcess(_InsProcess.ArriveArea(wAreaId),_InsStar.ArriveArea(wAreaId));

}
void CPlayerDgn::FightWithMonster(UINT16 wGroupId)
{
    UpdateDgnProcess(_InsProcess.ArriveArea(wGroupId),_InsStar.ArriveArea(wGroupId));

}

CPlayerDgn::CPlayerDgn(const SDgnInfo& rDgnInfo, UINT64 qwInstID, const CPlayerPtr& pPlayer) : CDungeon(rDgnInfo, qwInstID), 
    _pPlayer(pPlayer)
{
    _vecAttackOrder = rDgnInfo.oDgnCfg.vecAttackOrder; 
}

bool CPlayerDgn::CanAttackMonster(UINT16 wMonsterGroup)
{
    //功能屏蔽
    return true;

    if(GetDgnType() != ePlayerDgn)
    {
        return true;
    }
    if( _rDgnInfo.oDgnCfg.wDgnID == 1)
    {
        return true;
    }
    if(_vecAttackOrder.empty())
    {
        return false;
    }
    return wMonsterGroup == _vecAttackOrder[0];

}

void  CPlayerDgn:: PlayerKillAll(CPlayer& rPlayer)
{

    vector<UINT16> vecOrder(_vecAttackOrder);
    for(auto it = vecOrder.begin();it != vecOrder.end();it++)
    {
        //OnMonsterDie(*it,rPlayer.GetRoleID(),0);
    }

}

EDungeonResult  CPlayerDgn::AcceptDgnAward(CPlayer& rPlayer)
{
    //如果不是在
    if(_eDgnState != eDgnFinish)
    {
        return eDungeonNotFinish ;
    }
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer == NULL)
        return eDungeonOtherErr ;
    if(pPlayer->GetRoleID() != rPlayer.GetRoleID())
        return eDungeonOtherErr ;
    _eOverSource = eOver_Finish; 
    SetDgnState(eDgnDel_Over);
    return eDungeonSuccess;
}
bool CPlayerDgn::OnBegin()
{
    //TODO:初始化
    return CDungeon::OnBegin();
}

void CPlayerDgn::OnEnd()
{
    //TODO:副本销毁做的事情
    CDungeon::OnEnd();
}
void CPlayerDgn::GetDgnProcessFromClient(CPlayer& rPlayer)
{
    if(_eDgnState == eDgnFinish)
    {
        AcceptDgnAward(rPlayer);
    }
    else if(_eDgnState != eDgnDel_Over)
    {
        UpdateDgnProcess();
    }
}
void CPlayerDgn::UpdateDgnProcess(bool bUpdateProcess,bool bUpdateStar)
{   
    if(bUpdateStar)
    {
        CPlayerPtr pPlayer = _pPlayer.lock();
        if(pPlayer != NULL)
        {
            TVecMulCond vecProcess;
            _InsStar.GetStream(vecProcess);
            pPlayer->SendPkg(g_DungeonProtS.BuildPkg_NotifyDgnStar(_rDgnInfo.oDgnCfg.wDgnID,vecProcess));
        }

    }

    if(bUpdateProcess)
    {
        CPlayerPtr pPlayer = _pPlayer.lock();
        if(pPlayer != NULL)
        {
            TVecMulCond vecProcess;
            _InsProcess.GetStream(vecProcess);
            pPlayer->SendPkg(g_DungeonProtS.BuildPkg_NotifyDgnProcess(_rDgnInfo.oDgnCfg.wDgnID,vecProcess));

        } 

        //如果成功，结算
        if(_InsProcess.IsAllSuc())
        {
            DoFinish();
            return;
        }
        else if(_InsProcess.IsOneFail())
        {
            FailOver();
            return ;
        }
    }

}

void CPlayerDgn::PlayerRelive()
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(pPlayer != NULL)
    {
        if(pPlayer->IsDead())
        {
            pPlayer->Relive();
            CGameMapPtr pCurMap = pPlayer->GetMap();
            if(pCurMap != NULL)
            {
                SPoint oPoint(pCurMap->GetMapInfo().oRealivePoint.fX,pCurMap->GetMapInfo().oRealivePoint.fY);
                LOG_CRI << "Player to Origin";
                pPlayer->JumpMap(pCurMap,oPoint,0);
            }
        }
    }
}

void CPlayerDgn::OnPlayerDie(CCreature& rKiller,CPlayer& rPlayer)
{
    rPlayer.OnDie(rKiller);
    //回d到出生点

}
void CPlayerDgn::GetLogString(string &strMsg)
{
    CPlayerPtr pPlayer = _pPlayer.lock();
    if(!pPlayer)
        return ;
    stringstream ss;
    //参数：（副本id;副本星级;战斗力;出战散仙id,出战散仙id...）
    ss << _rDgnInfo.oDgnCfg.wDgnID;
    ss << ";";
    //星级
    ss <<(int)_InsStar.GetSucNum();
    ss << ";";
    //战斗力
    ss << pPlayer->GetBattlePoint();

    ss << ";";

   CFormation& rFormation = pPlayer->GetFighterManager()->GetFormation();
    {
        TVecLineup vecLineup;
        rFormation.GetLineup(vecLineup);
        for (size_t i = 0; i < vecLineup.size(); ++i)
        {
            if (!vecLineup[i].pFighter)
                continue;
            ss << vecLineup[i].pFighter->GetFighterID();

            if(i != vecLineup.size()-1)
            {
                ss << ",";
            }
        }
    }

    strMsg = ss.str();
}

