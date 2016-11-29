#include "ActionBase.h" 
#include "ActionSweeping.h"
#include "DungeonMgr.h"
#include "ExclusionCFG.h"
#include "SysMsgDefine.h"
#include "Player.h"
#include "Protocols.h"
#include "Map.h"
#include "VarDefine.h"
#include "ExpMgr.h"
#include "VIPMgr.h"
#include "UserMgr.h" 
#include "Parameter.h"
#include "RoleInfoDefine.h"
#include "Bubble.h"
using namespace NRoleInfoDefine;
using namespace NVarDefine;
map<EACTION,map<EACTION,EACTION_RELATION> > CActionManager::_mapActionConfig; 

void CActionBase::End()
{
}

void CActionBase::Break()
{
    _bIsWork = false;
}

CActionBase::~CActionBase()
{
}

void CActionBase::TimeOut()
{
    if(_dwTimes == 0)
    {
        return ;
    }
    if(_dwTimes != static_cast<UINT32>(E_TimerEndLess))
        _dwTimes--;
    if(_dwTimes == 0)
    {
        End();
    }
    else
    {
        _LastEndTimer = _LastEndTimer + _ContinueTimer;
    }
}

bool CActionBase::IsTimeOut(time_t tNow)
{
   if(_LastEndTimer < tNow)
   {
       return true;
   }

   if(_dwSpeedTime)
   {
       UINT32 lastTime = _LastEndTimer - tNow;

       if(lastTime < _dwSpeedTime)
       {
           _dwSpeedTime  -= lastTime;
           _LastEndTimer -= lastTime;
           //LOG_INF<<"add speed time:"<<lastTime;
           return true;
       }
       else //加速时间耗尽
       {
           //LOG_INF<<"add speed time LACK:"<<_dwSpeedTime;
           _LastEndTimer -= _dwSpeedTime;
           _dwSpeedTime = 0;
       }
   }

   return false;

}

CActionManager::~CActionManager()
{
    for (auto iter =_mapAction.begin() ;iter != _mapAction.end();iter++)
    {
        if(iter->second != NULL)
        {
            delete iter->second;
            iter->second =NULL;
        }
    }
    _mapAction.clear();
}
time_t CActionBase::ReserverTime()
{
    if(_dwTimes == 0)
    {
        return 0;
    }

    UINT32 dwEndTime = (_dwTimes-1)*_ContinueTimer +  _LastEndTimer;

    if(dwEndTime < time(NULL))
    {
        return 0;
    }

    return dwEndTime - time(NULL);
}

void CActionManager::TimerCheck(time_t now)
{
    if(!_bLoaded)
    {
        return;
    }

    for (auto iter =_mapAction.begin() ;iter != _mapAction.end();)
    {
        if(iter->second == NULL || !iter->second->IsWork()||iter->second->IsOver())
        {
            if(iter->second != NULL)
            {
                delete iter->second;
                iter->second =NULL;
            }
            ClearAction(iter->first);
            iter = _mapAction.erase(iter);
            continue;
        }
        else if(iter->second->IsTimeOut(now))
        {
            iter->second->TimeOut();
        }

        ++iter;
    }

}

UINT8 CActionManager::SpeedUpAction(EACTION eAction,UINT8 byOptions)
{
    CActionBase * pAction = GetActionByType(eAction);
    if(pAction == NULL || !pAction->IsWork() || pAction->IsOver())
    {
        return 1;
    }
    do
    {
        const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(GetPlayer().GetUser().GetVIPLevel());
        if(pCfgVip == NULL)
            return 0;

        if (!pCfgVip->_SaoDangFree) //VIP免费
            if(!pAction->CheckSpeedUp(byOptions))
                return 2;

        pAction->TimeOut();

    }while(!pAction->IsOver() && pAction->IsWork());
    return 0;
}

void CActionManager::OnVIPChange()
{
    if(GetPlayer().GetUser().GetVIPLevel()>SParamConfig::byAutoFightNoCDRequiredVipLevel)
    {
        CActionBase * pAction = GetActionByType(eACTION_SWEEPING);
        if(pAction == NULL || !pAction->IsWork() || pAction->IsOver())
        {
            return;
        }

        do
        {
          pAction->TimeOut();

        }while(!pAction->IsOver() && pAction->IsWork());

    }

}

CActionBase * CActionManager::CreateAction(EACTION eAction,time_t ContinueTimer,UINT32 dwTimes)
{
    CActionBase * pAction = GetActionByType(eAction);
    if(pAction != NULL)
    {
        return NULL;
    }

    switch (eAction)
    {
        case  eACTION_SWEEPING:
            {
                if(/*ContinueTimer == 0 ||*/ dwTimes ==0)
                {
                    return NULL;
                }
                pAction = new CActionSweeping(ContinueTimer,dwTimes,this); 
            }
            break;
            /*
               case  eACTION_SIT:
               {
               pAction = new CActionSitting(this); 
               }
               break;
               */
        default:
            break;
            return NULL;
    }
    if(NULL != pAction)
    {
        _mapAction[eAction] = pAction;
        AddAction(eAction);
    }
    return pAction;
}


CActionBase * CActionManager::GetActionByType(EACTION eAction)
{
    auto  iter =_mapAction.find(eAction);
    if(iter == _mapAction.end())
    {
        return NULL;
    }
    return iter->second;

}

bool CActionManager::CancelAction( EACTION eAction)
{
    if(eAction == eACTION_SWEEPING)
    {
        CActionBase * pAction = GetActionByType(eAction);
        if(pAction && pAction->IsWork())
        {
            pAction->Break();//主动终止，可发消息
            return true;
        }
    }
    else if(eAction ==  eACTION_SIT)
    {
        if(!HasAction(eACTION_SIT))
        {
            return true;
        }
        //发送消息，打坐中止
        //结算
        UINT32 dwTimer =  _rPlayer.GetUser().GetVars().GetVar(NVarDefine::ePlayerVarSittingTime);
        NMapProt::TVecPlayerAppear vecAppear;
        GetPlayer().SendPkg(g_SittingProtS.BuildPkg_UpdateSitting(0,vecAppear,dwTimer));
        //LOG_INF<<GetPlayer().GetRoleID() << "结束修行 ";
        UINT64 qwRoleID = GetPlayer().GetSitToGatherPlayer();
        ClearAction(eACTION_SIT);
        if(dwTimer != 0)
        {
          //  LOG_INF<<"修行结算";
            TVecResource vecRes;
            CalSittingAward(vecRes,time(NULL)-dwTimer,qwRoleID != 0);
            CStore::AddResource(_rPlayer.GetUser(),vecRes,NLogDataDefine::ItemFrom_Siting);
            GetPlayer().SendPkg(g_SittingProtS.BuildPkg_CancelSittingOffLine(qwRoleID ==0? 0 : 1,vecRes,dwTimer));

            TVecINT32 vecParam;
            vecParam.push_back(time(NULL)-dwTimer);
            GetPlayer().OnEvent(eEventType_SitDownTime,vecParam);
        }
        else
        {
           // LOG_INF <<"Sit Begin is ZERO";
        }
        _rPlayer.GetUser().GetVars().SetVar(NVarDefine::ePlayerVarSittingTime,0);
        CGameMapPtr pMap = GetPlayer().GetMap();
        if(pMap)
            pMap->AppearToSurround( GetPlayer());
        //如果双修玩家在线，改为单修

        if(qwRoleID ==0)
        {
            return true;
        }
        GetPlayer().SetSitToGatherPlayer(0,false);
        CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pOtherUser)
        {
            pOtherUser->GetPlayer()->SetSitToGatherPlayer(0,true);
        }
        return true;
    }
    return false;
}
bool  CActionManager::AddSweePing(UINT16 wDgnID,UINT16 wCount,UINT32& dwSweepEndTime)
{
    const SDgnInfo* pDgnInfo = CDungeonMgr::GetDgnInfo(wDgnID);
    if(NULL == pDgnInfo)
    {

        return false;
    }

    UINT32 dwSweepingTime = 0;

    if(_rPlayer.GetUser().GetVIPLevel()>=SParamConfig::byAutoFightNoCDRequiredVipLevel)
    {
        dwSweepingTime = 0;
    }
    else
    {
        dwSweepingTime = pDgnInfo->oDgnCfg._dwSweepingTime;
    }

    CActionBase *pAction =  CreateAction(eACTION_SWEEPING,dwSweepingTime,wCount);
    if(pAction == NULL)
    {
        return false;
    }
    CActionSweeping *pSweep =static_cast<CActionSweeping *>(pAction);
    if(pSweep ==NULL)
    {
        return false;
    }
    pSweep->SetDgnId(wDgnID);
    dwSweepEndTime = dwSweepingTime * wCount;
    pSweep->SaveDB(_rPlayer);
    //LOG_INF<<"AddSweePing wDgnID:"<<wDgnID<<" dwSweepingTime:"<<dwSweepingTime<<" wCount"<<wCount;
    return true;
}

UINT32 CActionManager::GetReserverTimerByType(EACTION eAction)
{
    CActionBase * pAction = GetActionByType(eAction);
    if(pAction != NULL && !pAction->IsOver() && pAction->IsWork())
    {
        return pAction->ReserverTime();
    }
    return 0;
}
void CActionManager::GetSweePingInfo(SGetSweepInfo& oGetSweepInfo)
{
    CActionBase * pAction = GetActionByType(eACTION_SWEEPING);
    if(pAction != NULL && !pAction->IsOver() && pAction->IsWork())
    {
        CActionSweeping *pSweep =static_cast<CActionSweeping *>(pAction);
        if(pSweep ==NULL)
        {
            return ;
        }
        oGetSweepInfo.wDgnId = pSweep->GetDgnId();
        if(_rPlayer.GetUser().GetVIPLevel()>=SParamConfig::byAutoFightNoCDRequiredVipLevel)
        {
            oGetSweepInfo.dwReserverTimer= 0;
        }
        else
        {
            oGetSweepInfo.dwReserverTimer = pSweep->ReserverTime();
        }
        oGetSweepInfo.wCount =  pSweep->GetTimes();
        oGetSweepInfo.wMaxCount = pSweep->GetMaxTimes();
        oGetSweepInfo.vecSweepItem = pSweep->GetSweepItem();
        //LOG_INF<<"GetSweePingInfo: dwReserverTime:"<<oGetSweepInfo.dwReserverTimer;
    }

    SetLoadedOk();
}

void   CActionManager::AddAction(EACTION eAction)//登记一个动作
{
    setAction  setBreak;
    do
    {
        if(_setAction.empty())
        {
            break;
        }
        for(auto it = _setAction.begin();it != _setAction.end();it++)
        {
            auto iter =_mapActionConfig.find(*it);
            if(iter== _mapActionConfig.end())
            {
                continue;
            }
            auto pos = iter->second.find(eAction);
            if(pos == iter->second.end())
            {
                continue;
            }
            if(pos->second == E_BREAK)
            {
                setBreak.insert(*it);
            }
        }
    }while(0);
    BreakAction(setBreak);
    _setAction.insert(eAction);
}
void   CActionManager::ClearAction(EACTION eAction)//清除一个动作
{
    _setAction.erase(eAction);
}

EACTION CActionManager::CanAddAction(EACTION eAction,bool bNeedNotice)//判定可否加入一个动作
{
    if(_setAction.empty())
    {
        return eACTION_NONE;
    }
    for(auto it = _setAction.begin();it != _setAction.end();it++)
    {
        auto iter =_mapActionConfig.find(*it);
        if(iter== _mapActionConfig.end())
        {
            continue;
        }
        auto pos = iter->second.find(eAction);
        if(pos == iter->second.end())
        {
            continue;
        }
        if(pos->second == E_MUTEX)
        {
            if(bNeedNotice)
            {
                NoticeActionErrMsg(*it);
            }
            return *it;
        }
    }
    return eACTION_NONE;
}

bool CActionManager::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/Exclusion.xml";
    CExclusionLoader oLoader;
    oLoader.LoadData(strPath);
    for(size_t it = 0;it != oLoader._vecData.size();it++)
    {
        SExclusionCFG* pCfg = oLoader._vecData[it];
        if(pCfg->_Level <=  eACTION_NONE || pCfg->_Level >= eACTION_MAX)
        {
            return false;
        }
        EACTION eEACTION = eACTION_NONE;
        EACTION_RELATION  eRelation = E_MUTEX;
#define INSERTMAP(ACTION,NUMBER) \
        if(pCfg->_##NUMBER < E_MUTEX || pCfg->_##NUMBER > E_BREAK) \
        return false;                                         \
        eEACTION = ACTION;        \
        eRelation = EACTION_RELATION(pCfg->_##NUMBER);\
        _mapActionConfig[EACTION(pCfg->_Level)][eEACTION] = eRelation;

        INSERTMAP(eACTION_SWEEPING,One);
        INSERTMAP(eACTION_SIT,Two);
        INSERTMAP(eACTION_DGN,Three);
        INSERTMAP(eACTION_WORLDBOSS,Four);
        INSERTMAP(eACTION_TOWER,Five);
        INSERTMAP(eACTION_GUIDBATTLE,Six);
        INSERTMAP(eACTION_CAMPBATTLE,Seven);
        INSERTMAP(eACTION_GATHER,Eight);
    }
    return true;

}
void CActionManager::BreakAction(const setAction &setBreak)
{
    for (auto it = setBreak.begin();it != setBreak.end();it++)
    {
        EACTION eAction = *it;
        switch (eAction)
        {
            case eACTION_SIT:
                {
                    //TODO:打坐中断
                    CancelAction(eACTION_SIT);

                }
                break;
            default:
                LOG_CRI << "UNKNOWN ACTION : " << eAction;
        }
    }
}

void CActionManager::NoticeActionErrMsg(EACTION eAction)
{
    UINT16 wMsgId = 0;
    switch(eAction)
    {
        case  eACTION_SWEEPING ://扫荡
            {
                wMsgId = eMsgAutoDgnConflict;

            }
            break;
        case  eACTION_SIT://打坐
            {
                wMsgId  = eMsgSitConflict;
            }
            break;
        case  eACTION_DGN://副本
            {
                wMsgId = eMsgDgnConflict;
            }
            break;
        case  eACTION_WORLDBOSS://世界Boss
            {
                wMsgId = eMsgWorldBossConflict;
            }
            break;
        case  eACTION_TOWER://索妖塔
            {
                wMsgId = eMsgDemonTowerConflict;
            }
            break;
        case  eACTION_GUIDBATTLE://帮派战
            {
                wMsgId = eMsgGuildBattleConflict;
            }
            break;
        case  eACTION_CAMPBATTLE://阵营战
            {
                wMsgId =eMsgCampBattleConflict;
            }
            break;
        case  eACTION_GATHER://采集
            {
                wMsgId = eMsgCollectionConflict;
            }
            break;
        default:
            break;
    }
    if(wMsgId != 0)
    {            
        _rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(wMsgId));
    }

}
NSittingProt::ESittingResult CActionManager::DoSitting(UINT64 qwRoleId)
{
    if(_rPlayer.GetLevel() < SParamConfig::bySitLimitLevel)
    {
       return  eLevelLow;
    }

    //如果在修行，那么不处理
    if(CanAddAction(eACTION_SIT) !=  eACTION_NONE)
    {
        return  eSittingSucceed;
    }
    //如果不在主城，那么不处理
    CGameMapPtr pMap = _rPlayer.GetMap();
    if(pMap == NULL || !pMap->GetMapInfo().IsNormal())
    {
        return eNotInCity;
    }
    //单修可以开始
    if(qwRoleId == 0 )
    {
        AddAction(eACTION_SIT);
        NMapProt::TVecPlayerAppear vecAppear;
        UINT32 dwNow = time(NULL);
        _rPlayer.GetUser().GetVars().SetVar(NVarDefine::ePlayerVarSittingTime,dwNow);
        GetPlayer().SendPkg(g_SittingProtS.BuildPkg_UpdateSitting(1,vecAppear,dwNow));
        pMap->AppearToSurround(GetPlayer());
        //LOG_INF <<_rPlayer.GetRoleID() << " 开始单修";
    }
    else
    {
        //如和人双修
        CPlayerPtr pOtherPlayer = pMap->GetPlayer(qwRoleId);
        if(pOtherPlayer == NULL)
        {
            return eSittingTogether;
        }
        if(pOtherPlayer->GetSex() == _rPlayer.GetSex())
        {
            return eSittingTogether;
        }
        if(!pOtherPlayer->GetActionManager().HasAction(eACTION_SIT))
        {
            return eSittingTogether;
        }
        if(pOtherPlayer->GetSitToGatherPlayer() != 0)
        {
            return eSittingTogether;
        }
        AddAction(eACTION_SIT);  
        float fDiffX = pOtherPlayer->GetPoint().fX -_rPlayer.GetPoint().fX;
        float fDiffY = pOtherPlayer->GetPoint().fY -_rPlayer.GetPoint().fY;
        _rPlayer.SetDir(atan2f(fDiffY,fDiffX));
        pOtherPlayer->SetDir(atan2f(fDiffY*(-1),fDiffX*(-1)));
        pOtherPlayer->SetSitToGatherPlayer(_rPlayer.GetRoleID(),true);
        _rPlayer.SetSitToGatherPlayer(qwRoleId,true);
    }
    return eSittingSucceed;
}
bool  CActionManager::HasAction(EACTION eAction)
{
    return  _setAction.find(eAction) != _setAction.end();
}
void CActionManager::CalSittingAward(TVecResource& vecRes,UINT32 dwTimer,bool bDouble)
{
    UINT32 dwTimes = dwTimer / SParamConfig::wSitGivenFrequent; 
    float fCityAdd =0;
    float fVip = 0;
    float fDouble = 0;
    float fBaseExp = 0;
    float fBasePExp = 0;
    //获得Base
    SExpCFGPtr pCfg = CExpMgr::GetExpCfg(_rPlayer.GetLevel());
    if(pCfg == NULL)
    {
        LOG_CRI<< "Can not find Exp";
        return ;
    }
    EMoneyType eType = EMONEY_NONE;
    if(pCfg->_SitBasicResourceType == EMONEY_NONE || pCfg->_SitBasicResourceType >= EMONEY_END)
    {
        LOG_CRI << "ERR ResourceType";
        return ;
    }
    eType = static_cast<EMoneyType>(pCfg->_SitBasicResourceType);
    fBaseExp  = pCfg->_SitBasicExp;
    fBasePExp = pCfg->_SitBasicResourceValue;
    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());    
    if(pCfgVip == NULL)
    {
        LOG_CRI << "Can not Find Vip";
        return ;
    }

    fVip = pCfgVip->_SitAddition;
    if(bDouble)
    {
        fDouble = SParamConfig::wSitDoubleSitC;
    }
    if(dwTimes > pCfgVip->_SitTimeMax*3600 / SParamConfig::wSitGivenFrequent)
    {
        dwTimes = pCfgVip->_SitTimeMax*3600 / SParamConfig::wSitGivenFrequent;
    }
    CGameMapPtr pMap = _rPlayer.GetMap();
    if(pMap != NULL && pMap->GetMapInfo().IsWorldCity())
    {
        fCityAdd = SParamConfig::wSitWorldTownC;
    }
    float fAdd = fVip+fCityAdd+fDouble;
    float exp = fBaseExp*(100+fAdd)/100*dwTimes;
    float pExp = fBasePExp*(100+fAdd)/100*dwTimes;
    if(exp != 0)
    {
        SResource sRes;
        sRes._eRes = EMONEY_EXP;
        sRes._dwValue = exp;
        vecRes.push_back(sRes);
        TVecINT64 vecParam;
        UINT32 dwBubleTimer = dwTimer < pCfgVip->_SitTimeMax*3600 ? dwTimer : pCfgVip->_SitTimeMax*3600;
        vecParam.push_back(dwBubleTimer);
        vecParam.push_back(exp);
        _rPlayer.GetUser().GetBubbleOwner()->CreateBubble(BubbleType_Sit,vecParam);
    }
    if(pExp != 0)
    {
        SResource sRes;
        sRes._eRes = eType;
        sRes._dwValue = pExp;
        vecRes.push_back(sRes);
    }

}

bool CActionManager::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    if(rRoleDataInfo.vecSweepInfo.size())
    {
        const SSweepInfo& rSweepInfo  = rRoleDataInfo.vecSweepInfo[0];
        
        const SDgnInfo* pDgnInfo = CDungeonMgr::GetDgnInfo(rSweepInfo.wCurDgnID);
        if(NULL == pDgnInfo)
        {
            return false;
        }
        CActionBase *pAction =  CreateAction(eACTION_SWEEPING,pDgnInfo->oDgnCfg._dwSweepingTime,rSweepInfo.wCurCount);
        if(pAction == NULL)
        {
            return false;
        }
        CActionSweeping *pSweep =static_cast<CActionSweeping *>(pAction);
        if(pSweep ==NULL)
        {
            return false;
        }
        pSweep->SetDgnId(rSweepInfo.wCurDgnID);

        //UINT32 dwReserverTime = time(NULL) > rSweepInfo.dwSaveTime? time(NULL)-rSweepInfo.dwSaveTime:0;

        pAction->SetEndTime(rSweepInfo.dwSaveTime + pDgnInfo->oDgnCfg._dwSweepingTime);
        pSweep->SetMaxTimes(rSweepInfo.wCount);

        _bInitSweep = true;


        /*
        if(_rPlayer.GetLastOfflineTime()<time(NULL))
        {
            pAction->AddSpeedTime(dwReserverTime);
        }
        else
        {
            LOG_CRI<<"warning server datetime changed!!!";
        }
        pSweep->ClearDB(_rPlayer);
        */

    }

    return true;
}

