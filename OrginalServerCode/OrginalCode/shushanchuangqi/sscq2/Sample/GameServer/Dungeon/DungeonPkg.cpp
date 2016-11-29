#include "DungeonPkg.h"
#include "Protocols.h"  
#include "Player.h"
#include "DungeonMgr.h"
#include "Dungeon.h"
#include "UserMgr.h"
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "VarDefine.h"
#include "VIPMgr.h"
#include "GameServerLog.h"
using namespace NVarDefine;
//查询一个单人副本的相关信息
CDungeonPkg::CDungeonPkg(CPlayer& rPlayer):_rPlayer(rPlayer)
{
}
RoleDgnInfo* CDungeonPkg::GetPlayerDgnInfoByType(UINT32 dwDgnType)
{
    auto it =_mapPlayerDgnInfo.find(dwDgnType);
    RoleDgnInfo *pDgnInfo = NULL;
    if (it != _mapPlayerDgnInfo.end())
    {
        pDgnInfo =  &(it->second);
    }
    if (NULL != pDgnInfo)
    {
        /*
           if (pDgnInfo->dwAppendEndTimer > 0 && pDgnInfo->dwAppendEndTimer < time(NULL))
           {
           pDgnInfo->dwAppendEndTimer = 0;
           pDgnInfo->dwEnterTimesAppend =0;
           string strData;
           COutArchive iar(strData);
           iar << *pDgnInfo;
           g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpUpdate, strData);
           }
           */
        //TODO:
        //周期副本，清除次数,byCost清0
        return pDgnInfo;
    }
    return NULL;
}
void CDungeonPkg::UpadePlayerDgnInfoForEnter(UINT32 dwDgnType)
{
    RoleDgnInfo* pDgnInfo = GetPlayerDgnInfoByType(dwDgnType);
    if (NULL != pDgnInfo)
    {
        pDgnInfo->dwEnterTimes++;
        pDgnInfo->byCost = 1;
        pDgnInfo->dwLastEnterTimer = time(NULL);
        string strData;
        COutArchive iar(strData);
        iar << *pDgnInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpUpdate, strData);

    }
    else
    {
        RoleDgnInfo sDgnInfo;
        sDgnInfo.dwDgnType = dwDgnType;
        sDgnInfo.dwEnterTimes++;
        sDgnInfo.byCost = 1;
        sDgnInfo.dwLastEnterTimer = time(NULL);
        string strData;
        COutArchive iar(strData);
        iar << sDgnInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpAdd, strData);
        _mapPlayerDgnInfo[dwDgnType] = sDgnInfo;
    }   

}

void CDungeonPkg::UpadePlayerDgnInfoForOver(UINT32 dwDgnType)
{
    RoleDgnInfo* pDgnInfo = GetPlayerDgnInfoByType(dwDgnType);
    if(pDgnInfo == NULL)
    {
        LOG_CRI << "UpadePlayerDgnInfoForOver fails:" <<_rPlayer.GetUserID();
    }
    pDgnInfo->byCost = 0;
    string strData;
    COutArchive iar(strData);
    iar << *pDgnInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpUpdate, strData);
}


bool CDungeonPkg::PlayerCompleteDgn(UINT32 dwDgnType,UINT16 wMinTurns,bool bIsClean )
{
    const SDgnConfig* pDgnConfig =NULL;
    const SDgnInfo* pInfo =CDungeonMgr::GetDgnInfo(dwDgnType);
    if(NULL != pInfo)
    {
        pDgnConfig = &(pInfo->oDgnCfg);
    }
    if(pDgnConfig == NULL)
    {
        return false;
    }
    RoleDgnInfo* pDgnInfo = NULL;
    if(pDgnConfig->eType == eTeamDgn)
    {
        bool bCanGetAward = true;
        if(_rPlayer.GetUser().GetVars().GetVar(eTeamDgnAward) >= SParamConfig::byTeamBattleAvailablePrizeTimes)
        {
            bCanGetAward = false;;
        }
        if(pDgnConfig->_dwSweepingCoin == 0)
        {
            return false;
        }
        pDgnInfo = GetPlayerDgnInfoByType(dwDgnType);
        UINT32 dwNow = time(NULL);
        if (NULL != pDgnInfo)
        {
            pDgnInfo->dwCompleteTimes++ ;
            pDgnInfo->dwEnterTimes++ ;
            pDgnInfo->dwLastEnterTimer = dwNow;
            pDgnInfo->dwLastCompleteTimer = dwNow;
            if(bCanGetAward)
            {
                _rPlayer.GetUser().GetVars().AddVar(eTeamDgnAward,1);
            }
            UpdateTeamAward();
            string strData;
            COutArchive iar(strData);
            iar << *pDgnInfo;
            g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpUpdate, strData);
            SendDgnInfo(*pDgnInfo);
            do{
                SDgnLogPtr ptrLog(new SDgnLog());
                if(NULL == ptrLog)
                    break;
                NLogDataDefine::SDgnLog& rLog = *ptrLog;
                rLog.wDgnType = dwDgnType;
                rLog.qwUserID = _rPlayer.GetUser().GetUserID();
                rLog.eOpType = NLogDataDefine::EDgnOpType_FINISH;
                CGameServerLog::LogToDB(ptrLog);
            }while(0);
            return bCanGetAward;
        }
        else
        {
            RoleDgnInfo sDgnInfo;
            sDgnInfo.dwDgnType = dwDgnType;
            sDgnInfo.dwCompleteTimes = 1;
            sDgnInfo.dwEnterTimes = 1;
            sDgnInfo.dwLastEnterTimer = dwNow;
            sDgnInfo.dwLastCompleteTimer = dwNow;
            if(bCanGetAward)
            {
                _rPlayer.GetUser().GetVars().AddVar(eTeamDgnAward,1);
            }
            string strData;
            COutArchive iar(strData);
            iar << sDgnInfo;
            g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpAdd, strData);
            _mapPlayerDgnInfo[dwDgnType] = sDgnInfo;
            UpdateTeamAward();
            SendDgnInfo(sDgnInfo);
            return bCanGetAward;
        }
    }
    else
    {
        pDgnInfo   = GetPlayerDgnInfoByType(dwDgnType);
        if(pDgnInfo == NULL)
        {
            LOG_CRI << "PlayerCompleteDgn fails:" <<_rPlayer.GetUserID();
            return false;
        }
        LOG_DBG<<"PlayerCompleteDgn:"<<pDgnInfo->wMinTurns<<"|"<<wMinTurns;
        pDgnInfo->byCost = 0;
        pDgnInfo->dwCompleteTimes++;

        //星级
        if(pDgnInfo->wMinTurns < wMinTurns && !bIsClean)
        {
            //_rPlayer.GetUser().AddMoney(EMONEY_REIKI,byStar,NLogDataDefine::ItemFrom_EDgn);
            pDgnInfo->wMinTurns = wMinTurns;

        }
        if(Time::sameDay(pDgnInfo->dwLastCompleteTimer,time(NULL)))
        {
            pDgnInfo->dwFinishTimesToday++;
        }
        else
        {
            pDgnInfo->dwFinishTimesToday = 1;
        }
        switch (pDgnConfig->eSubType)
        {
            case eSubHero:
                {

                    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
                    if(!pCfgVip || pDgnInfo->dwFinishTimesToday > pCfgVip->_HeroDungeonFreeTimes)
                    {
                        if(pDgnInfo->dwEnterTimesAppend > 0)
                        {
                            pDgnInfo->dwEnterTimesAppend--;
                        }
                    }

                }
                break;
            case eSubLiXian:
                {
                    UINT32 dwPassTimes =  _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnPassToday);
                    dwPassTimes++;
                    _rPlayer.GetUser().GetVars().AddVar(ePlayerlixianDgnPassToday,1);
                    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
                    if(!pCfgVip || dwPassTimes > pCfgVip->_AdventureDungeonFreeTimes)
                    {
                        UINT32 dwBuyTimes = _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnBuyTimes);
                        if(dwBuyTimes > 0)
                        {
                            dwBuyTimes--;
                            _rPlayer.GetUser().GetVars().SetVar(ePlayerlixianDgnBuyTimes,dwBuyTimes);

                        }
                    }
                    SendLiXianDgn();
                }
                break;
            default:
                break;


        }
    }


    //event
    TVecINT32 vecParam;
    vecParam.push_back(pDgnConfig->_Type2);
    vecParam.push_back(1);
    _rPlayer.OnEvent(eEventType_DungeonFinishType,vecParam);

    if(pDgnInfo == NULL)
        return true;

    pDgnInfo->dwLastCompleteTimer = time(NULL);

    string strData;
    COutArchive iar(strData);
    iar << *pDgnInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpUpdate, strData);
    SendDgnInfo(*pDgnInfo);
    return true;
}
void CDungeonPkg::SendLiXianDgn()
{
    DgnLiXian sLiXian;
    GetLiXian(sLiXian);
    _rPlayer.SendPkg(g_DungeonProtS.BuildPkg_UpdateLiXian(sLiXian));
}

void CDungeonPkg::GetLiXian(DgnLiXian &sLiXian)
{
    sLiXian.dwFinishTimesToday = _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnPassToday);
    sLiXian.dwBuyTimesToday =  _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnBuyTimesToday);
    sLiXian.dwBuyTimes = _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnBuyTimes);

}
void CDungeonPkg::SendDgnInfo(const RoleDgnInfo &rDgn)
{
    DgnStar sDgnStar;
    GetDgnStarByInfo(rDgn,sDgnStar);
    _rPlayer.SendPkg(g_DungeonProtS.BuildPkg_UpdateDgnInfo(sDgnStar));

}
void CDungeonPkg::GetDgnStarByInfo(const RoleDgnInfo &rDgn,DgnStar& sDgnStar)
{
    sDgnStar.wDgnId = rDgn.dwDgnType;
    sDgnStar.byStar = rDgn.wMinTurns ;
    if(Time::sameDay(rDgn.dwLastCompleteTimer,time(NULL)))
    {
        sDgnStar.dwFinishTimesToday = rDgn.dwFinishTimesToday ;
    }
    else
    {
        sDgnStar.dwFinishTimesToday = 0;
    }
    if(Time::sameDay(rDgn.dwBuyTimer,time(NULL)))
    {
        sDgnStar.dwBuyTimesToday = rDgn.dwBuyTimesToday;
    }
    else
    {
        sDgnStar.dwBuyTimesToday = 0;
    }
    sDgnStar.dwBuyTimes = rDgn.dwEnterTimesAppend ;
    sDgnStar.dwCompleteTimes = rDgn.dwCompleteTimes;

}
//删除一个单人副本的相关信息
void CDungeonPkg::DelPlayerDgnInfo(UINT32 dwDgnType)
{
    const RoleDgnInfo* pDgnInfo = GetPlayerDgnInfoByType(dwDgnType);
    if (NULL == pDgnInfo)
    {
        LOG_CRI <<"DGN INFO NOT EXIST FOR DEL:" <<dwDgnType;
        return ;
    }
    string strData;
    COutArchive iar(strData);
    iar << *(pDgnInfo);
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn, eOpDel, strData);
    _mapPlayerDgnInfo.erase(dwDgnType);
}

ETEAMResult CDungeonPkg::CanCreateEnterTeam(UINT16 wDgnID)
{
    if(_rPlayer.IsInTeam())
        LOG_CRI <<"Team info ERR";

    const SDgnConfig* pDgnConfig =NULL;
    const SDgnInfo* pInfo =CDungeonMgr::GetDgnInfo(wDgnID);
    if(NULL != pInfo)
        pDgnConfig = &(pInfo->oDgnCfg);
    if(pDgnConfig == NULL)
        return ETeam_OtherErr ;

    //等级不够不可以创建
    if(_rPlayer.GetLevel() < pDgnConfig->byMinLev)
        return ETeam_LowLevel;

    //前置任务没有完成不可以创建
    if(!IsDgnListPassed(pDgnConfig->vecPreDgnID))
        return ETeam_PreDgn;

    // 背包格子不够不可以创建
    if(_rPlayer.GetUser().GetPack().GetEmptyCount() < pDgnConfig->_PackSize)
    {
        _rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgDgnLackPack,BuildStrVec(pDgnConfig->_PackSize)));
        return ETeam_PackFull;
    }

    return ETeam_Suc;
}

bool CDungeonPkg::IsDgnListPassed(const TVecUINT16& vecDgnID)
{
    for(auto it = vecDgnID.begin();it != vecDgnID.end();it++)
    {
        if(!IsDgnPassed(*it))
        {
            return  false;
        }
    }
    return true;
}
bool CDungeonPkg::IsDgnPassed(UINT16 wDgnID)
{
    const RoleDgnInfo *pPlayerDgnInfo = GetPlayerDgnInfoByType(wDgnID);
    if (pPlayerDgnInfo != NULL && pPlayerDgnInfo->dwCompleteTimes > 0)
    {
        return true;
    }
    return false;
}
EDungeonResult CDungeonPkg::CheckDgnTimes(UINT16 wDgnID)
{
    const SDgnConfig* pDgnConfig =NULL;
    const SDgnInfo* pInfo =CDungeonMgr::GetDgnInfo(wDgnID);
    if(NULL != pInfo)
    {
        pDgnConfig = &(pInfo->oDgnCfg);
    }
    if(pDgnConfig == NULL)
    {
        return eDungeonOtherErr;
    }

    switch (pDgnConfig->eSubType)
    {
        case eSubCommon:
            {
                return eDungeonSuccess;
            }
            break;
        case eSubHero:
            {
                UINT32 dwPassTimes = 0;
                const RoleDgnInfo *pPlayerDgnInfo = GetPlayerDgnInfoByType(wDgnID);
                if(pPlayerDgnInfo != NULL)
                {
                    if(Time::sameDay(pPlayerDgnInfo->dwLastCompleteTimer,time(NULL)))
                    {
                        dwPassTimes = pPlayerDgnInfo->dwFinishTimesToday;
                    }

                }
                SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
                if(pCfgVip && dwPassTimes < pCfgVip->_HeroDungeonFreeTimes)
                {
                    return eDungeonSuccess;
                }
                else
                {
                    if(!pPlayerDgnInfo || pPlayerDgnInfo->dwEnterTimesAppend == 0)
                    {
                        return eDungeonTimesLimitForHero;
                    }
                    else
                    {
                        return eDungeonSuccess;
                    }
                }

            }
            break;
        case eSubHistory:
            {
                const RoleDgnInfo *pPlayerDgnInfo = GetPlayerDgnInfoByType(wDgnID);
                if(pPlayerDgnInfo != NULL && pPlayerDgnInfo->dwCompleteTimes > 0)
                {
                    return eDungeonTimesLimit;

                }
                else
                {
                    return eDungeonSuccess;
                }

            }
            break;
        case eSubLiXian:
            {
                UINT32 dwPassTimes =  _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnPassToday);
                SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
                if(pCfgVip && dwPassTimes < pCfgVip->_AdventureDungeonFreeTimes)
                {
                    return eDungeonSuccess;
                }
                else
                {
                    if(_rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnBuyTimes) == 0)
                    {
                        return eDungeonTimesLimitForLiXian;

                    }
                    else
                    {
                        return  eDungeonSuccess;
                    }
                }
            }
            break;
        default:
            break;

    }
    return eDungeonOtherErr;
}

EDungeonResult CDungeonPkg::Sweeping(UINT16 wDgnID, UINT8 byOptions, UINT16 wCount, UINT32& dwSweepEndTime)
{
    // TODO
    if(wCount ==0)
    {
        return eDungeonSuccess;
    }
    // 能否扫荡判定
    EDungeonResult result = CDungeonMgr::TestCanSweeping(wDgnID,_rPlayer,wCount);
    if(result != eDungeonSuccess)
    {
        return result;
    }
    EACTION eAction = _rPlayer.GetActionManager().CanAddAction(eACTION_SWEEPING);
    if(eAction !=  eACTION_NONE)
    {
        return eDungeonBusy;
    }
    if(_rPlayer.GetGatherID() != 0)
    {
        return eDungeonBusy;
    }
    if(!_rPlayer.GetActionManager().AddSweePing(wDgnID,wCount,dwSweepEndTime))
    {
        return eDungeonOtherErr;
    }
    return eDungeonSuccess;
}

EDungeonResult CDungeonPkg::CancelSweeping()
{
    if(!_rPlayer.GetActionManager().CancelAction(eACTION_SWEEPING))
    {
        return eDungeonNotSweeping;

    }
    // TODO
    return eDungeonSuccess;
}

EDungeonResult CDungeonPkg::SweepingSpeedUp(UINT8 byOptions)
{
    UINT8 bySpeedUp = _rPlayer.GetActionManager().SpeedUpAction(eACTION_SWEEPING,byOptions);
    if(1 == bySpeedUp)
    {
        return  eDungeonNotSweeping;
    }
    else if(2 == bySpeedUp)
    {
        return eSpeedUpItemLimit;
    }

    return eDungeonSuccess;
}


void CDungeonPkg::Init(const TVecRoleDgnInfo& vecRoleDgnInfo)
{
    for (auto it = vecRoleDgnInfo.begin(); it != vecRoleDgnInfo.end();it++)
    {
        _mapPlayerDgnInfo[(*it).dwDgnType] = *it; 
    }
}

void CDungeonPkg::ReturnCost()
{
    for(auto it = _mapPlayerDgnInfo.begin(); it != _mapPlayerDgnInfo.begin();it++)
    {
        RoleDgnInfo &rDgn = it->second;
        const SDgnInfo* pDgnInfo = CDungeonMgr::GetDgnInfo(it->first);
        if(rDgn.byCost ==0 || NULL == pDgnInfo)
        {
            continue;
        }
        _rPlayer.GetUser().AddAction(pDgnInfo->oDgnCfg._SpendEnergy);
        UpadePlayerDgnInfoForOver(it->first);
        //TODO发消息，通知活力找回
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgDundgeEngeryPayback);
    }
}
void CDungeonPkg::UpdateTeamAward()
{
    TeamAwardAllRecord stRecord;
    stRecord.byAwardTimesToday = _rPlayer.GetUser().GetVars().GetVar(eTeamDgnAward);
    _rPlayer.SendPkg(g_DungeonProtS.BuildPkg_SynTeamAwardRecord(stRecord));

}
void CDungeonPkg::GetDgnInfoForAll(DgnLiXian &sLiXian,TVecDgnStar &vecStar)
{
    GetLiXian(sLiXian);
    for(auto it = _mapPlayerDgnInfo.begin();it != _mapPlayerDgnInfo.end();it++)
    {
        if(it->second.dwCompleteTimes > 0 || it->second.dwEnterTimesAppend > 0)
        {
            DgnStar sDgnStar;
            GetDgnStarByInfo(it->second,sDgnStar);
            vecStar.push_back(sDgnStar);
        }
    }
}

void CDungeonPkg::SendDgnInfoForAll()
{
    DgnLiXian sLiXian;
    TVecDgnStar vecStar;
    GetDgnInfoForAll(sLiXian,vecStar);
    _rPlayer.SendPkg(g_DungeonProtS.BuildPkg_UpdateDgnInfoForAll(sLiXian,vecStar));

}

EDungeonResult CDungeonPkg::BuyHeroDgnTimes(UINT16 wDgnID)
{
    //不是英雄副本不能买
    const SDgnConfig* pDgnConfig =NULL;
    const SDgnInfo* pInfo =CDungeonMgr::GetDgnInfo(wDgnID);
    if(NULL != pInfo)
    {
        pDgnConfig = &(pInfo->oDgnCfg);
    }
    if(pDgnConfig == NULL || pDgnConfig->eSubType != eSubHero)
    {
        return eDungeonOtherErr;
    }
    UINT32 dwBuyTimes = 0;
    RoleDgnInfo *pPlayerDgnInfo = GetPlayerDgnInfoByType(wDgnID);
    if(pPlayerDgnInfo != NULL)
    {
        if(Time::sameDay(pPlayerDgnInfo->dwBuyTimer,time(NULL)))
        {
            dwBuyTimes = pPlayerDgnInfo->dwBuyTimesToday;
        }

    }
    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
    if(!pCfgVip || dwBuyTimes >= pCfgVip->_HeroDungeonBuyTimes)
    {
        return eDungeonVipBuyHero;
    }
    dwBuyTimes++;
    UINT32  dwCost = CDungeonMgr::GetHeroDgnPrice(dwBuyTimes); 
    if(!_rPlayer.GetUser().SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_BuyHeroDgn))
    {
        return eDungeonNOGold;

    }
    if(pPlayerDgnInfo == NULL)
    {
        RoleDgnInfo sDgnInfo;
        sDgnInfo.dwDgnType = wDgnID;
        sDgnInfo.dwEnterTimesAppend++;
        sDgnInfo.dwBuyTimer = time(NULL);
        sDgnInfo.dwBuyTimesToday = dwBuyTimes;
        string strData;
        COutArchive iar(strData);
        iar << sDgnInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpAdd, strData);
        _mapPlayerDgnInfo[wDgnID] = sDgnInfo;
        SendDgnInfo(sDgnInfo);

    }
    else
    {
        RoleDgnInfo& sDgnInfo = *pPlayerDgnInfo;
        sDgnInfo.dwEnterTimesAppend++;
        sDgnInfo.dwBuyTimer = time(NULL);
        sDgnInfo.dwBuyTimesToday = dwBuyTimes;
        string strData;
        COutArchive iar(strData);
        iar << sDgnInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypePlayerDgn,eOpUpdate, strData);
        SendDgnInfo(sDgnInfo);

    }
    return eDungeonSuccess;
}
EDungeonResult    CDungeonPkg::BuyLiXianDgnTimes()
{
    UINT32 dwBuyTimes =  _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnBuyTimesToday);
    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
    if(!pCfgVip || dwBuyTimes >= pCfgVip->_AdventureDungeonBuyTimes)
    {
        return eDungeonVipBuyLiXian;
    }
    dwBuyTimes++;
    UINT32  dwCost = CDungeonMgr::GetLiXianDgnPrice(dwBuyTimes); 
    if(!_rPlayer.GetUser().SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_BuyLiXianDgn))
    {
        return eDungeonNOGold;
    }
    _rPlayer.GetUser().GetVars().AddVar(ePlayerlixianDgnBuyTimesToday,1);
    _rPlayer.GetUser().GetVars().AddVar(ePlayerlixianDgnBuyTimes,1);
    SendLiXianDgn();
    return eDungeonSuccess;
}

bool CDungeonPkg::CompleteDgnIsCost(UINT16 wDgnID)
{
    const SDgnConfig* pDgnConfig =NULL;
    const SDgnInfo* pInfo =CDungeonMgr::GetDgnInfo(wDgnID);
    if(NULL != pInfo)
    {
        pDgnConfig = &(pInfo->oDgnCfg);
    }
    if(pDgnConfig == NULL)
    {
        return false;
    }

    switch (pDgnConfig->eSubType)
    {
        case eSubHero:
            {
                UINT32 dwPassTimes = 0;
                const RoleDgnInfo *pPlayerDgnInfo = GetPlayerDgnInfoByType(wDgnID);
                if(pPlayerDgnInfo != NULL)
                {
                    if(Time::sameDay(pPlayerDgnInfo->dwLastCompleteTimer,time(NULL)))
                    {
                        dwPassTimes = pPlayerDgnInfo->dwFinishTimesToday;
                    }

                }
                SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
                if(pCfgVip && dwPassTimes < pCfgVip->_HeroDungeonFreeTimes)
                {
                    return false;
                }
                else
                {
                    return true;
                }

            }
            break;
        case eSubLiXian:
            {
                UINT32 dwPassTimes =  _rPlayer.GetUser().GetVars().GetVar(ePlayerlixianDgnPassToday);
                SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
                if(pCfgVip && dwPassTimes < pCfgVip->_AdventureDungeonFreeTimes)
                {
                    return false;
                }
                else
                {
                    return  true;
                }
            }
            break;
        default:
            break;

    }
    return false;
}


EDungeonResult  CDungeonPkg::DoStarAward(UINT16 wStarID)
{
    const StarAward *pCfg = CDungeonMgr::GetAwardByID(wStarID);
    if(pCfg == NULL)
    {
        return eDungeonOtherErr;
    }
    //星级判定
    if(_rPlayer.GetUser().GetMoney(EMONEY_REIKI) < pCfg->dwStar)
    {
        return eDungeonOtherErr;
    }
    //生成物品
    TVecItemGenInfo oVecItemGenInfo;
    for(auto it = pCfg->mapAward.begin();it != pCfg->mapAward.end();it++)
    {

        SItemGenInfo sItem;
        sItem.wItemID = it->first;
        sItem.dwCount = it->second;
        oVecItemGenInfo.push_back(sItem);

    }
    if(!_rPlayer.GetUser().GetPack().AddItem(oVecItemGenInfo,NLogDataDefine::ItemFrom_StarAward))
    {
        return eDungeonPackEmptyMin;
    }
    return eDungeonSuccess;
}
