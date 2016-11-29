
#include "stdafx.h"
#include "Protocols.h"
#include "RTime.h"
#include "MapMgr.h"
#include "Random.h"
#include "Player.h"
#include "User.h"
#include <algorithm>
#include "DayActProt.h"
#include "SysMsgDefine.h"
#include "Tokenizer.h"
#include "GameServerSysMail.h" 
#include "LangHuanBlessMgr.h"
#include "Parameter.h"
#include "UserMgr.h"
#include "LangHuanBlessProt.h"
#include "LangHuanBlessProtS.h"
#include "UserMgr.h"

#define SETLOGINTIME(var,begin) var=((var&0xFFFFFFFF00000000)|(begin))
#define SETLEAVETIME(var,end) var=((var&0x00000000FFFFFFFF)|(end<<32))
#define GETLOGINTIME(qwValue,qwBegin) qwBegin=(qwValue & 0x00000000FFFFFFFF)
#define GETLEAVETIME(qwValue,qwEnd) qwEnd=(qwValue>>32)

using namespace NDayActProt;
using namespace NLangHuanBlessProt;

const UINT32 GAME_PlAYER_COUNT = 100;
/*
UINT32 GetTime(time_t tTime)
{
    time_t tNow = time(NULL);
    struct tm *pTm = localtime(tTime);
    struct tm *pNowTm = localtime(tNow);
    tm oTm = *pNowTm;
    oTm.tm_hour = pTm->tm_hour;
	oTm.tm_min = pTm->tm_min;
    oTm.tm_sec = pTm->tm_sec;

    return mktime(&oTm);
}
*/
CLangHuanBlessMgr::CLangHuanBlessMgr()
    :CDayActivity(eActTypeLangHuanBless)
{
    _dwAskTaoismValue = 0;
    _dwTalkTaoismValue = 0;
    _dwWanderValue = 0;
    _bLog = true;
    _byState = eLHBState_none;
}

CLangHuanBlessMgr::~CLangHuanBlessMgr()
{}

bool CLangHuanBlessMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/LanghuanfudiSkill.xml";
    CLanghuanfudiSkillLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
    {
        SLanghuanfudiSkillCFG* pCFG = oLoader._vecData[i];
        if(pCFG)
        {
            SLHBSkillCFGExPtr pCFGEx(new SLHBSkillCFGEx);
            pCFGEx->dwID = pCFG->_ID;
            pCFGEx->dDistance = pCFG->_Distance;
            pCFGEx->dSkillCD = pCFG->_CoolDown;
            pCFGEx->dwMapID = pCFG->_MapId;
            pCFGEx->dwUseTimes = pCFG->_UseTimes;
            pCFGEx->CopyFrom(*pCFG);
                    
            _mapID2LHBSkillPtr.insert(make_pair(pCFGEx->dwID,pCFGEx));
        }

    }
    string strPath1 = Config._strConfigDir + "Conf/Table/LanghuanfudiAward.xml";
    CLanghuanfudiAwardLoader aLoader;
    if(!aLoader.LoadData(strPath1))
    {
        LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i  = 0; i < aLoader._vecData.size(); ++i)
    {
        SLanghuanfudiAwardCFG* pCFG = aLoader._vecData[i];
        if(pCFG)
        {
            SLHBAwardCFGExPtr pCFGEx(new SLHBAwardCFGEx);
            pCFGEx->byLevel = pCFG->_Level;
            pCFGEx->dBasicXiuwei = pCFG->_SitBasicXiuwei;
            pCFGEx->dExp = pCFG->_SitBasicExp;
            pCFGEx->dSkillXiuwei = pCFG->_SkillXiuwei;

            pCFGEx->CopyFrom(*pCFG);
                    
            _mapID2AwardPtr.insert(make_pair(pCFGEx->byLevel,pCFGEx));
        }

    }
     if(!_mapID2LHBSkillPtr.empty())
     {
         auto it = _mapID2LHBSkillPtr.begin();
         _dwMapId = (it->second)->dwMapID;
     }
     _dwBuffId = 12;
     return true;
}

bool CLangHuanBlessMgr::ReLoadConfig(const string &strFile)
{
    if("LanghuanfudiSkill.xml" == strFile)
    {
        string strPath = Config._strConfigDir + "Conf/Table/LanghuanfudiSkill.xml";
        CLanghuanfudiSkillLoader oLoader;
        if(!oLoader.LoadData(strPath))
        {
            LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
        {
            SLanghuanfudiSkillCFG* pCFG = oLoader._vecData[i];
            if(pCFG)
            {
                SLHBSkillCFGExPtr pCFGEx(new SLHBSkillCFGEx);
                pCFGEx->dwID = pCFG->_ID;
                pCFGEx->dDistance = pCFG->_Distance;
                pCFGEx->dSkillCD = pCFG->_CoolDown;
                pCFGEx->dwMapID = pCFG->_MapId;
                pCFGEx->dwUseTimes = pCFG->_UseTimes;
                pCFGEx->CopyFrom(*pCFG);
                        
                _mapID2LHBSkillPtr.insert(make_pair(pCFGEx->dwID,pCFGEx));
            }

        }
        if(!_mapID2LHBSkillPtr.empty())
        {
            auto it = _mapID2LHBSkillPtr.begin();
            _dwMapId = (it->second)->dwMapID;
        }

    }else if("LanghuanfudiAward.xml" == strFile)
    {
        string strPath1 = Config._strConfigDir + "Conf/Table/LanghuanfudiAward.xml";
        CLanghuanfudiAwardLoader aLoader;
        if(!aLoader.LoadData(strPath1))
        {
            LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath1;
            return false;
        }

        for(size_t i  = 0; i < aLoader._vecData.size(); ++i)
        {
            SLanghuanfudiAwardCFG* pCFG = aLoader._vecData[i];
            if(pCFG)
            {
                SLHBAwardCFGExPtr pCFGEx(new SLHBAwardCFGEx);
                pCFGEx->byLevel = pCFG->_Level;
                pCFGEx->dBasicXiuwei = pCFG->_SitBasicXiuwei;
                pCFGEx->dSkillXiuwei = pCFG->_SkillXiuwei;
                pCFGEx->dExp = pCFG->_SitBasicExp;
                LOG_CRI << " InitFromCFG dwExp = " << pCFGEx->dExp;
                pCFGEx->CopyFrom(*pCFG);
                        
                _mapID2AwardPtr.insert(make_pair(pCFGEx->byLevel,pCFGEx));
            }

        }
    }
     _dwBuffId = 12;
     return true;
}

bool CLangHuanBlessMgr::InitSkillInfo(TVecLHBSkillPtr &rVecLHBSkillPtr,UINT32 dwScore)
{
   if(_mapID2LHBSkillPtr.empty())
   {
       return false;
   }
   if(_mapID2LHBSkillPtr.size() >= eLHBSkillType_max)
   {
       LOG_CRI << " LHBskill config error size >= eLHBSkillType_max" ;
       return false;
   }
   auto rIt = _mapID2LHBSkillPtr.begin();
   for(; rIt!=_mapID2LHBSkillPtr.end() ; ++rIt)
   {
       SLHBSkillPtr pSkill(new SLHBSkill);
       pSkill->eSkillType = static_cast<ELHBSkillType> (rIt->second->dwID);
       pSkill->dwCount = rIt->second->dwUseTimes;
       pSkill->dwScore = dwScore;
       rVecLHBSkillPtr.push_back(pSkill);
   }
   return true;

}

ELHBResult CLangHuanBlessMgr::OnUseSkill(CPlayer &rPlayer,UINT64 qwPlayerID,ELHBSkillType eSkillType)
{
    ELHBResult eResult = eLHBResult_success;
    switch(eSkillType)
    {
        case eLHBSkillType_eAskTaoism:
            {
                auto it = _mapID2LHBSkillPtr.find(static_cast<UINT32>(eLHBSkillType_eAskTaoism));
                if(it != _mapID2LHBSkillPtr.end())
                   eResult = PlayerAskTaoism(rPlayer,it->second);
                break;
            }
        case eLHBSkillType_eTalkTaoism:
            {
                auto it = _mapID2LHBSkillPtr.find(static_cast<UINT32>(eLHBSkillType_eTalkTaoism));
                if(it != _mapID2LHBSkillPtr.end())
                   eResult = PlayerTalkTaoism(rPlayer,qwPlayerID,it->second);
                break;

            }
        case eLHBSkillType_eWander:
            {
                auto it = _mapID2LHBSkillPtr.find(static_cast<UINT32>(eLHBSkillType_eWander));
                if(it != _mapID2LHBSkillPtr.end())
                   eResult = PlayerWander(rPlayer,qwPlayerID,it->second);
                break;

            }
        default:
            break;
    }
    {
        TVecINT32 vecParam;
        INT32 dwEvent = eSkillType;
        vecParam.push_back(dwEvent);
        CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_HolyLandJoin,vecParam);
    }
    return eResult;
}
ELHBResult CLangHuanBlessMgr::CanEnterMap(CPlayer &rPlayer)
{
     CUserPtr pUser = rPlayer.GetUserPtr();
     if(pUser == NULL)
          return eLHBResult_otherError;
    UINT32 dwLastLeaveTime = static_cast<UINT32>(pUser->GetVars().GetVar(ePlayerLeaveLHB));
    UINT32 dwNowTime = static_cast<UINT32>(time(NULL));
    if(rPlayer.GetLevel() < 30)
    {
        return eLHBResult_lowLevel;
    }
    
    if(time(NULL) < _dwReadyTime)
    {
        g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgHuoDongNotOpen);
        return eLHBResult_notBegin;
    }
    if(time(NULL) > _dwEndTime)
    {
        g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgHuoDongClosed);
          return  eLHBResult_end;
    }
   
   if((dwNowTime - dwLastLeaveTime) <  5*60)
   {
       return eLHBResult_wait5min;
   }
    
    return eLHBResult_success;
}

bool CLangHuanBlessMgr::CalcOffLinePlayer(CPlayer& rPlayer)
{
    CUserPtr pUser = rPlayer.GetUserPtr();
    if(!pUser)
    {
        LOG_INF << " pUser NULL.";
        return false;
    }
    UINT64 qwCalcTime =  pUser->GetVars().GetVar(ePlayerLHBLoginTime);
    LOG_INF << "LHB qwCalcTime(" << qwCalcTime << ").";
    UINT64 qwEndTime = 0;
    UINT64 qwLoginTime = 0;
    UINT32 dwTime = 0;
    if(qwCalcTime)
    {
        GETLEAVETIME(qwCalcTime,qwEndTime);
        GETLOGINTIME(qwCalcTime,qwLoginTime);
        LOG_INF << " LHB qwLoginTime(" << qwLoginTime << ")|qwEndTime(" << qwEndTime << ")| _dwEndTime(" << _dwEndTime<<")." ;
        if(qwLoginTime < qwEndTime)
        {
             UINT32 dwNow = static_cast<UINT32>(time(NULL));
             UINT32 dwEndTimeTmp = static_cast<UINT32>(qwEndTime);
             LOG_CRI <<"LHB: dwNow = " <<dwNow<<" ,qwLoginTime = " <<qwLoginTime <<",dwEndTimeTmp =" << dwEndTimeTmp;
             if(dwEndTimeTmp == _dwEndTime)
                 dwTime = static_cast<UINT32>(time(NULL) - qwLoginTime);
             else if(IsReBegin() &&  dwNow > qwLoginTime && dwNow < dwEndTimeTmp)
                 dwTime = static_cast<UINT32>(time(NULL) - qwLoginTime);
             else
                 dwTime = static_cast<UINT32>(qwEndTime - qwLoginTime);
             UINT32 dwXiuwei = GetXiuweiForOffLine(rPlayer,dwTime);
             UINT32 dwExp = GetExpForOffLine(rPlayer,dwTime);
             pUser->AddMoney(EMONEY_PEXP,dwXiuwei,NLogDataDefine::ItemFrom_LangHuanBless);
             rPlayer.AddExp(dwExp);
             LOG_CRI << " qwRoleID = " << rPlayer.GetUserID() << " Get xiuwei = " << dwXiuwei << " | Exp = " << dwExp;
             rPlayer.SendPkg(g_LangHuanBlessProtS.BuildPkg_PrizeNotify(dwXiuwei,dwExp));
        }
    }
    pUser->GetVars().SetVar(ePlayerLHBLoginTime,0);

    return true;
}

UINT16 CLangHuanBlessMgr::GetOffValue(CPlayer &rPlayer,UINT8 byIndex /* 0 修为，1 经验*/)
{
    UINT8 byLevel = rPlayer.GetLevel();
    UINT64 qwRoleID = rPlayer.GetUserID();
    if(!byLevel || !qwRoleID)
    {
        return 0;
    }
    auto it = _mapID2AwardPtr.find(byLevel);
    if(it == _mapID2AwardPtr.end())
    {
        return 0;
    }
    if(byIndex)
         return it->second->dExp;
    else
         return it->second->dBasicXiuwei;

}

UINT32 CLangHuanBlessMgr::GetXiuweiForOffLine(CPlayer& rPlayer,UINT32 dwTime)
{
    UINT32 rScore = 0;
    /*
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return rScore;
    }
    */ 
    UINT16 wXiuwei = GetOffValue(rPlayer,0);
    rScore += dwTime / 5 * wXiuwei;
    return rScore;
}

UINT32 CLangHuanBlessMgr::GetExpForOffLine(CPlayer& rPlayer,UINT32 dwTime)
{
    UINT32 rScore = 0;
    /*
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return rScore;
    }
    */ 
    UINT16 wExp = GetOffValue(rPlayer,1);
    rScore += dwTime / 5 * wExp;
    return rScore;
}
//进入地图
ELHBResult CLangHuanBlessMgr::OnEnterMap(CPlayer& rPlayer)
{
    
    CGameMapPtr pMap = NULL;
    for(auto it=_deqMapGroup.begin(); it!=_deqMapGroup.end(); ++it)
    {
       if(NULL == *it)
       {
           _deqMapGroup.pop_front();
           continue;
       }
       UINT32 dwCount =  (*it)->GetPlayerCount();
       LOG_INF << " LHB Map PlayerCount = " <<dwCount;
       if(GAME_PlAYER_COUNT >= dwCount)
       {
           pMap = *it;
           break;
       }
    }
    if(!pMap)
    {
          pMap = CMapMgr::CreateMap(_dwMapId);
          if(!pMap)
          {
              LOG_INF << " LangHuanBless pMap NULL.";
              return eLHBResult_CMapError;
          }
        _deqMapGroup.push_front(pMap);
    }
   
    UINT8 byLevel = rPlayer.GetLevel();
    UINT32 dwXiuwei;
    UINT32 dwExp;
    UINT16 dSkillXiuwei;
    auto it = _mapID2AwardPtr.find(byLevel);
    if(it == _mapID2AwardPtr.end())
    {
        return eLHBResult_otherError;
    }
    dwXiuwei = static_cast<UINT32>((it->second)->dBasicXiuwei);
    dwExp = static_cast<UINT32>((it->second)->dExp);
    LOG_CRI << " dwExp = " <<dwExp;
    dSkillXiuwei = (it->second)->dSkillXiuwei;
    time_t rNow = time(NULL);
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        SLHBPlayerInfoPtr pLHBPlayerPtr(new SLHBPlayerInfo);
        pLHBPlayerPtr->qwUserID = rPlayer.GetUserID();
        pLHBPlayerPtr->qwRoleID = rPlayer.GetRoleID();
        pLHBPlayerPtr->strName = rPlayer.GetName();
        pLHBPlayerPtr->dwLevel = rPlayer.GetLevel();
        pLHBPlayerPtr->ePlayerSex = rPlayer.GetSex();
        pLHBPlayerPtr->dwEnrollTime = rNow; 
        pLHBPlayerPtr->dwLastLeaveActTime = rNow;
        pLHBPlayerPtr->rMapInstPtr = pMap;
        pLHBPlayerPtr->dwScore = dwXiuwei;
        pLHBPlayerPtr->dwBasicExp = dwExp;
        pLHBPlayerPtr->dwSkillXiuwei = dSkillXiuwei;
       if(!InitSkillInfo(pLHBPlayerPtr->vecLHBSkillPtr,dSkillXiuwei))
       {
           return eLHBResult_otherError;
       }
       _mapID2LHBPlayerPtr.insert(make_pair(rPlayer.GetUserID(),pLHBPlayerPtr));
    }
  
    /*
    if(!CalcOffLinePlayer(rPlayer))
    {
        LOG_INF <<"calc offline player error";    
    }
    */

    CUserPtr pUser = rPlayer.GetUserPtr();
    if(!pUser)
    {
        LOG_INF << " pUser NULL.";
        return eLHBResult_otherError;
    }
    
    if(pMap)
   { 
        SPoint rDestPoint(pMap->GetMapInfo().oRealivePoint.fX,pMap->GetMapInfo().oRealivePoint.fY);
        rPlayer.JumpMap(pMap,rDestPoint);

        //事件
        {
            TVecINT32 vecParam;
            INT32 dwEvent = 1;
            vecParam.push_back(dwEvent);
            CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
            if(pEventMgr)
            pEventMgr->OnEvent(eEventType_HolyLandJoin,vecParam);
        }
   }
    time_t tNow = time(NULL);
    UINT64 qwCalcTime = 0;
    SETLOGINTIME(qwCalcTime,tNow); 
    UINT64 qwEndTimeTmp = static_cast<UINT64>(_dwEndTime);
    SETLEAVETIME(qwCalcTime,qwEndTimeTmp);
    LOG_INF << "tNow(" <<tNow<<") | qwEndTimeTmp(" <<qwEndTimeTmp<<")|qwCalcTime(" << qwCalcTime<<").";
    pUser->GetVars().SetVar(ePlayerLHBLoginTime,qwCalcTime);

   if(rPlayer.HasBuff(21))
       rPlayer.RemoveBuff(21);
   LOG_INF << "RoleID[" << rPlayer.GetUserID()<<"] Enter LangHuanBless Suc!"; 
   return eLHBResult_success;
}

//离开地图
ELHBResult CLangHuanBlessMgr::OnLeaveMap(CPlayer& rPlayer)

{
    time_t tBugTime = time(NULL);
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        LOG_INF <<"qwRoleID = "<<rPlayer.GetUserID()<<"Not Find | dwLeaveTime = " << tBugTime;
        return eLHBResult_otherError;
    }
    if(NULL == rIt->second)
    {
        LOG_INF << " rIt->second Not Find ! qwRoleID = " <<rPlayer.GetUserID() << " | dwLeavetime = " <<tBugTime;
        return eLHBResult_otherError;
    }

    UINT32 dwXiuwei = GetScore(rPlayer);
    UINT32 dwExp = GetExp(rPlayer);
    rIt->second->dwTotalXiuwei += dwXiuwei;
    rIt->second->dwTotalExp += dwExp;
    
    // 设置玩家的修为值
    rPlayer.GetUser().AddMoney(EMONEY_PEXP,dwXiuwei,NLogDataDefine::ItemFrom_LangHuanBless);
    rPlayer.AddExp(dwExp);
    LOG_CRI << " qwRoleID = " << rPlayer.GetUserID() << " Get xiuwei = " << dwXiuwei << " | Exp = " << dwExp;
    
    rPlayer.SendPkg(g_LangHuanBlessProtS.BuildPkg_PrizeNotify(dwXiuwei,dwExp));
    
    //事件
    {
        TVecINT32 vecParam;
        INT32 dwEvent = static_cast<INT32>(time_t(NULL));
        vecParam.push_back(dwEvent);
        CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_HolyLandQuit,vecParam);
    }
    
    if(time(NULL) < _dwEndTime)
    {
        if(!rPlayer.HasBuff(21))
            rPlayer.AddBuff(21); //逃跑离开buff
    }

    rPlayer.ReturnLastNormalMap();
    auto oIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(oIt != _mapID2LHBPlayerPtr.end())
    {
        _mapID2LHBPlayerPtr.erase(oIt);
        LOG_INF <<" qwRoleID = " <<rPlayer.GetUserID()<< " erase Suc.";
    }
    else
    {
        LOG_INF <<" qwRoleID = " <<rPlayer.GetUserID()<< " Not Find";
    }
    CUser& rUser = rPlayer.GetUser();
    time_t tNow = time(NULL);
    rUser.GetVars().SetVar(ePlayerLeaveLHB,tNow);
    rUser.GetVars().SetVar(ePlayerLHBLoginTime,0);
    LOG_INF << "RoleID[ "<<rPlayer.GetUserID() << "] Leave LangHuanBless Suc! Set LeveaVar = " << tNow << "| LeaveTime = "<< tNow;
    return eLHBResult_success;
}

bool CLangHuanBlessMgr::GetTotalInfo(CPlayer& rPlayer,SLHBTotalInfo& rTotalInfo)
{
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return false;
    }
    rTotalInfo.byState = _byState;
    rTotalInfo.dwTime = rIt->second->dwPeriodTime;
    rTotalInfo.dwXiuwei = rIt->second->dwTotalXiuwei;
    rTotalInfo.dwExp = rIt->second->dwTotalExp;
    if(eLHBResult_success != GetSkillInfo(rPlayer,rTotalInfo.vecLHBSkillInfo))
    {
          return false;
    }
    return true;
}

UINT32 CLangHuanBlessMgr::GetSustainTime(CPlayer &rPlayer)
{
    UINT32 dwTime = 0;
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return dwTime;
    }
    return rIt->second->dwPeriodTime;
}

UINT32 CLangHuanBlessMgr::GetExp(CPlayer &rPlayer)
{
    UINT32 rScore = 0;
    UINT32 rBeginCalcTime = 0;
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return rScore;
    }
    rBeginCalcTime = (rIt->second)->dwLastLeaveActTime > _dwBeginTime ?  (rIt->second)->dwLastLeaveActTime : _dwBeginTime;

    if(time(NULL) < rBeginCalcTime)
        return rScore;
    else
    {
        time_t tNow = time(NULL);
        if(tNow > _dwEndTime)
            tNow = _dwEndTime;
        if(tNow <= rBeginCalcTime)
        {
            return rScore;
        }
        rScore += (tNow - rBeginCalcTime) / 5 * (rIt->second)->dwBasicExp;
    }
    return rScore;
}

UINT32 CLangHuanBlessMgr::GetScore(CPlayer &rPlayer)
{
    UINT32 rScore = 0;
    UINT32 rBeginCalcTime = 0;
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    UINT32 dwScore = 0;
    if(rIt == _mapID2LHBPlayerPtr.end())
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return rScore;
    }
    rBeginCalcTime = (rIt->second)->dwLastLeaveActTime > _dwBeginTime ?  (rIt->second)->dwLastLeaveActTime : _dwBeginTime;
    dwScore = (rIt->second)->dwSkillXiuwei;
    LOG_CRI << " dwScore = " << dwScore;
    if(time(NULL) < rBeginCalcTime)
        return rScore;
    else
    {
        time_t tNow = time(NULL);
        if(tNow > _dwEndTime)
            tNow = _dwEndTime;
        if(tNow <= rBeginCalcTime)
        {
            return rScore;
        }
        rScore += (tNow - rBeginCalcTime) / 5 * (rIt->second)->dwScore;
    }
   
    //结算技能修为
    {
        CUser& rUser = rPlayer.GetUser();
        UINT32 dwAskCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill1)); 
        UINT32 dwTalkCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill2)); 
        UINT32 dwWanderCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill3)); 
        auto sIt = (rIt->second)->vecLHBSkillPtr.begin();
        auto eIt = (rIt->second)->vecLHBSkillPtr.end();
        for(; sIt!=eIt ; ++sIt)
        {
            ELHBSkillType eType = (*sIt)->eSkillType;
            switch(eType)
            {
                case eLHBSkillType_eAskTaoism:
                    {
                             rScore += (dwAskCount* dwScore);
                        break;
                    }
                case eLHBSkillType_eTalkTaoism:
                    {
                             rScore += (dwTalkCount * dwScore);
                        break;
                    }
                case eLHBSkillType_eWander:
                    {
                             rScore += (dwWanderCount * dwScore);
                        break;
                    }
                default:
                    break;
            }
            LOG_CRI << " Skill calc xiuwei = " << rScore ;

        }
    }
    return rScore;
}

//获取玩家技能的使用次数
ELHBResult  CLangHuanBlessMgr::GetSkillInfo(CPlayer &rPlayer,TVecLHBSkillInfo& vecSkill)
{
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end() )
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return eLHBResult_otherError;
    }
    CUser& rUser = rPlayer.GetUser();
    UINT32 dwCount = 0;
    if((rIt->second)->vecLHBSkillPtr.size() != 1)
    {
        for(auto it=(rIt->second)->vecLHBSkillPtr.begin(); it!=(rIt->second)->vecLHBSkillPtr.end(); ++it)
        {
           ELHBSkillType  eSkillType =  (*it)->eSkillType;
            if(eSkillType != eLHBSkillType_eNone)
            {
               switch(eSkillType)
               {
                    case eLHBSkillType_eAskTaoism:
                    {
                        dwCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill1));
                    }
                    break;
                    case eLHBSkillType_eTalkTaoism:
                    {
                        dwCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill2));
                    }
                    break;
                    case eLHBSkillType_eWander:
                    {
                        dwCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill3));
                    }
                    break;
                default:
                    break;
               }

                SLHBSkillInfo sSkill;
                sSkill.eLHBSkillType = eSkillType;
                sSkill.byTimes = static_cast<UINT8>(dwCount);
                sSkill.wScore = 0;
                LOG_CRI <<"wScore : " <<sSkill.wScore;
                sSkill.byCD = 10;
                vecSkill.push_back(sSkill);
            }
        }
    }
   return eLHBResult_success; 
}

ELHBResult CLangHuanBlessMgr::UseSkill(CPlayer &rPlayer, ELHBSkillType eSkillType)
{
    auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
    if(rIt == _mapID2LHBPlayerPtr.end() )
    {
        LOG_CRI<<"Player [" <<rPlayer.GetName()<<"] not In Activity";
        return eLHBResult_otherError;
    }
    UINT32 dwScore = 0;
    auto sIt = (rIt->second)->vecLHBSkillPtr.begin();
    auto eIt = (rIt->second)->vecLHBSkillPtr.end();
    for(; sIt!=eIt ; ++sIt)
    {
        dwScore = (*sIt)->dwScore;
    }

    CUser& rUser = rPlayer.GetUser();
    switch(eSkillType)
        {
            case eLHBSkillType_eAskTaoism:
                {
                    UINT64 qwAskCount =  rUser.GetVars().GetVar(ePlayerLHBSkill1);
                    rUser.GetVars().SetVar(ePlayerLHBSkill1,qwAskCount + 1);
                }
                break;
            case eLHBSkillType_eTalkTaoism:
                {
                    UINT64 qwTalkCount =  rUser.GetVars().GetVar(ePlayerLHBSkill2);
                    rUser.GetVars().SetVar(ePlayerLHBSkill2,qwTalkCount + 1);
                }
                break;
            case eLHBSkillType_eWander:
                {
                    UINT64 qwWanderCount =  rUser.GetVars().GetVar(ePlayerLHBSkill3);
                    rUser.GetVars().SetVar(ePlayerLHBSkill3,qwWanderCount + 1);

                }
                break;
            default:
                break;
         }
    string strPkg;
    strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLangHuanBlessSkillXiuWei, BuildStrVec(dwScore));
    rPlayer.SendPkg(strPkg);

    rPlayer.AddBuff(_dwBuffId);
    return eLHBResult_success;
}

ELHBResult CLangHuanBlessMgr::CanUseSkill(CPlayer &rPlayer, ELHBSkillType eSkillType,UINT16 &rSkillCD, UINT32 &rUseTimes)
{
   ELHBResult rRet = eLHBResult_success;
   if(time(NULL) > _dwEndTime)
       return eLHBResult_otherError;

   if(rSkillCD == 0 && rUseTimes == 0)
       return rRet;
   UINT32 dwCount = 0;
   UINT32 dwLastUseTime = 0;
   auto rIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());
   if(rIt != _mapID2LHBPlayerPtr.end())
   {
       CUser& rUser = rPlayer.GetUser();
       UINT32 dwMaxCount = 0;
       auto sIt = rIt->second->vecLHBSkillPtr.begin();
       for(; sIt!=rIt->second->vecLHBSkillPtr.end() ; ++sIt)
       { 
           if(eSkillType == (*sIt)->eSkillType)
           {
                dwLastUseTime = (*sIt)->dwLastUseTime;
                dwMaxCount = (*sIt)->dwCount;
           }
       }
       switch(eSkillType)
       {
                case eLHBSkillType_eAskTaoism:
                {
                    dwCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill1));
                }
                break;
                case eLHBSkillType_eTalkTaoism:
                {
                    dwCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill2));
                }
                break;
                case eLHBSkillType_eWander:
                {
                    dwCount = static_cast<UINT32>(rUser.GetVars().GetVar(ePlayerLHBSkill3));
                }
                break;
            default:
                break;
         }
         if(dwCount > dwMaxCount)
         {
            rRet = eLHBResult_empty;
         }
         UINT32 dwNowTime = static_cast<UINT32>(time(NULL));
         if(dwNowTime > dwLastUseTime)
         {  
             if(rSkillCD > (dwNowTime - dwLastUseTime))
                 rRet = eLHBResult_inCD;
         }   
     }else 
        rRet = eLHBResult_otherError;
  return rRet;
} 

bool  CLangHuanBlessMgr::GetUserPtrByPlayerID(UINT64 &qwPlayerId,CUserPtr &pUser)
{
    for(auto aIt = _mapID2LHBPlayerPtr.begin(); aIt!=_mapID2LHBPlayerPtr.end(); ++aIt)
    {
        if(qwPlayerId == (aIt->second)->qwRoleID)
        {
            pUser = CUserMgr::GetUserByUserID(aIt->first);
            return true;
        }
    }
    return false;
}
// 论道
ELHBResult CLangHuanBlessMgr::PlayerTalkTaoism(CPlayer &rPlayer,UINT64 &qwPlayerId,SLHBSkillCFGExPtr pSkillEx)
{
    
    ELHBResult eResult = eLHBResult_success;
    auto aIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());

    if(aIt == _mapID2LHBPlayerPtr.end())
        return eLHBResult_otherError;
    CUserPtr pUser;
    if(!GetUserPtrByPlayerID(qwPlayerId,pUser))
    {
        LOG_CRI<<" LangHuanBlessMgr:: PlayerTalkTaoism : GetUserPtrByPlayerID failed";
        return eLHBResult_otherError;
    }
    
    CPlayerPtr pPlayer;
    if(!pUser)
    {
        LOG_CRI << " pUser NULL " ;
        return eLHBResult_otherError;
    }
    if(!(pPlayer = pUser->GetPlayer()))
    {
        LOG_CRI<<"LangHuanBless:: PlayerTalkTaoism : pPlayer NULL ";
        return eLHBResult_otherError;
    }
    if(rPlayer.HasBuff(_dwBuffId) || pPlayer->HasBuff(_dwBuffId))
       return eLHBResult_hasBuff;
    
    if(eLHBResult_success != (eResult = CanUseSkill(rPlayer,eLHBSkillType_eTalkTaoism,pSkillEx->dSkillCD,pSkillEx->dwUseTimes)))
        return eResult;
        
    pPlayer->SendPkg(g_LangHuanBlessProtS.BuildPkg_SkillInfo(
                     rPlayer.GetRoleID(),pPlayer->GetRoleID(),eLHBSkillType_eTalkTaoism));
    rPlayer.SendPkg(g_LangHuanBlessProtS.BuildPkg_SkillInfo(
                    rPlayer.GetRoleID(),pPlayer->GetRoleID(),eLHBSkillType_eTalkTaoism));
    eResult =  UseSkill(rPlayer,eLHBSkillType_eTalkTaoism);
    return eResult;
}

// 开小差
ELHBResult CLangHuanBlessMgr::PlayerWander(CPlayer &rPlayer,UINT64 &qwPlayerId,SLHBSkillCFGExPtr pSkillEx)
{
    ELHBResult eResult = eLHBResult_success;
    auto aIt = _mapID2LHBPlayerPtr.find(rPlayer.GetUserID());

    if(aIt == _mapID2LHBPlayerPtr.end())
        return eLHBResult_otherError;
    CUserPtr pUser;
    if(!GetUserPtrByPlayerID(qwPlayerId,pUser))
    {
        LOG_CRI<<" LangHuanBlessMgr:: PlayerWander : GetUserPtrByPlayerID failed";
        return eLHBResult_otherError;
    }
    
    CPlayerPtr pPlayer;
    if(!pUser)
    {
        LOG_CRI << " pUser NULL " ;
        return eLHBResult_otherError;
    }
    if(!(pPlayer = pUser->GetPlayer()))
    {
        LOG_CRI<<"LangHuanBless:: PlayerWander : pPlayer NULL ";
        return eLHBResult_otherError;
    }
    if(rPlayer.HasBuff(_dwBuffId) || pPlayer->HasBuff(_dwBuffId))
       return eLHBResult_hasBuff;
    
    if(eLHBResult_success != (eResult = CanUseSkill(rPlayer,eLHBSkillType_eWander,pSkillEx->dSkillCD,pSkillEx->dwUseTimes)))
        return eResult;
        
    pPlayer->SendPkg(g_LangHuanBlessProtS.BuildPkg_SkillInfo(rPlayer.GetRoleID(),pPlayer->GetRoleID(),eLHBSkillType_eWander));
    rPlayer.SendPkg(g_LangHuanBlessProtS.BuildPkg_SkillInfo(rPlayer.GetRoleID(),pPlayer->GetRoleID(),eLHBSkillType_eWander));
    eResult =  UseSkill(rPlayer,eLHBSkillType_eWander);
    return eResult;

}

// 问道
ELHBResult CLangHuanBlessMgr::PlayerAskTaoism(CPlayer &rPlayer,SLHBSkillCFGExPtr pSkillEx)
{
    ELHBResult eResult = eLHBResult_success;
    if(rPlayer.HasBuff(_dwBuffId))
       return eLHBResult_hasBuff;
    
    if(eLHBResult_success != (eResult = CanUseSkill(rPlayer,eLHBSkillType_eAskTaoism,pSkillEx->dSkillCD,pSkillEx->dwUseTimes)))
        return eResult;
   
    return UseSkill(rPlayer,eLHBSkillType_eAskTaoism);     
}

//T 玩家
void CLangHuanBlessMgr::KickAllPlayer()
{
    if(pMap)
    {
       const TMapID2Player& mapPlayer = pMap->GetPlayerMap();
       for(auto itr = mapPlayer.begin(); itr != mapPlayer.end();)
       {
           CPlayerPtr pPlayer = itr->second.lock();
           ++itr;
           if(pPlayer)
           {
              LOG_INF << "qwRoleID = " << pPlayer->GetRoleID()<< " Info get in Map."; 
              ELHBResult eResult = OnLeaveMap(*pPlayer);
              if(eResult == eLHBResult_success)
              {
                  LOG_INF << "qwRoleID = " <<pPlayer->GetRoleID()<<" Kick Suc.";
              }
              else
              {
                 LOG_INF << "qwRoleID = " <<pPlayer->GetRoleID()<<" Kick Error.";
              }

           }
        }
    }
}

void CLangHuanBlessMgr::KickPlayers()
{
    UINT64 qwRoleID = 0;
    UINT16 wMapID = 0;
    for(auto it=_mapID2LHBPlayerPtr.begin(); it!=_mapID2LHBPlayerPtr.end();)
    {
        auto oIt = it;
        it++;
        qwRoleID = oIt->first;
        if(oIt->second == NULL)
        {
            LOG_INF << " PlayerInfo error";
            continue;
        }
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser == NULL)
        {
            LOG_INF << "pUser Null. qwRoleID = " <<qwRoleID;
            continue;
        }
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if(pPlayer == NULL)
        {
            LOG_INF << " pPlayer Null. qwRoleID = " << qwRoleID;
            continue;
        }
        wMapID = pPlayer->GetCurMapID();
        if(wMapID != 3002)
        {
            LOG_INF << " pPlayer Not in LangHuanBless Map. qwRoleID = "<< qwRoleID;
            continue ;
        }
        ELHBResult eResult = OnLeaveMap(*pPlayer);
        if(eResult == eLHBResult_success)
        {
           pUser->GetVars().SetVar(ePlayerLHBLoginTime,0);
           LOG_INF << "qwRoleID = " <<qwRoleID<<" Kick Suc.";
        }
        else
        {
           LOG_INF << "qwRoleID = " <<qwRoleID<<" Kick Error.";
        }
    }
}

/////////////////////////
bool CLangHuanBlessMgr::OnAlarm()
{
    bool bRet = CDayActivity::OnAlarm();
    if(!bRet)
    {
        return false;
    }
    
    ClearEvent();      

    /* 
    pMap = CMapMgr::GetMap(_dwMapId);
    if(!pMap)
    {
        LOG_INF << " LangHuanBless dwMapId Error!";
        return false;
    }
    */

    AddEvent(eLangHuanBlessEnrollEvent,_dwReadyTime,10);
    UINT32 dwAttackCd = 40*60;
    AddPeriodEvent(eLangHuanBlessStartEvent,_dwBeginTime,1,dwAttackCd);
    _byState = eLHBState_alarm ; 
    
    return true;
}

void CLangHuanBlessMgr::OnReady()
{
    if(_bLog)
        LOG_INF<<"CLangHuanBlessMgr::OnReady";
    CDayActivity::OnReady();
   

    //g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLangHuanBlessEnroll);
    
    //清理数据
    for(auto it=_mapID2LHBPlayerPtr.begin(); it!=_mapID2LHBPlayerPtr.end(); ++it)
    {
        (it->second)->vecLHBSkillPtr.clear();
    }
   
    _mapID2LHBPlayerPtr.clear();
    _deqMapGroup.clear(); 
    _byState = eLHBState_ready;
}

void CLangHuanBlessMgr::OnBegin()
{
    if(_bLog)
        LOG_INF<<"CLangHuanBlessMgr::OnBegin";
    CDayActivity::OnBegin();
    g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLangHuanBlessBegin);
    _byState = eLHBState_begin;
    g_LangHuanBlessProtS.SendClt_BeginNotify(NULL,0,_dwBeginTime); 
    LOG_CRI << "LanghuanBless Begin time sended ";

}
#if 0
void  CLangHuanBlessMgr::SendPrize()
{
   for(auto it=_mapID2LHBPlayerPtr.begin(); it!=_mapID2LHBPlayerPtr.end(); ++it)
   {
       if(NULL != (it->second))
       {
            CUserPtr pUser;
            UINT64 qwPlayerId = it->second->qwUserID;
            if(!GetUserPtrByPlayerID(qwPlayerId,pUser))
            {
                LOG_CRI<<" LangHuanBlessMgr:: PlayerTalkTaoism : GetUserPtrByPlayerID failed";
                continue;
            }
            CPlayerPtr pPlayer;
            if(!pUser)
            {
                LOG_CRI << " pUser NULL " ;
                continue;
            }
            if(!(pPlayer = pUser->GetPlayer()))
            {
                LOG_CRI<<"LangHuanBless:: PlayerTalkTaoism : pPlayer NULL ";
                continue;
            }
            pPlayer->SendPkg(g_LangHuanBlessProtS.BuildPkg_PrizeNotify(it->second->dwTotalXiuwei,it->second->dwTotalExp));
            LOG_CRI << " pPlayer sendPkg( " <<it->second->dwTotalXiuwei<<" , " << it->second->dwTotalExp<<")"; 
       }
   }
}
#endif
void CLangHuanBlessMgr::OnEnd()
{
   if(_bLog)
       LOG_INF<<"CLangHuanBlessMgr::OnEnd";

   CDayActivity::OnEnd();
   g_ChatProtS.SendClt_SystemMsgIDNotify(NULL,0,eMsgLangHuanBlessEnd);

   ClearEvent(eLangHuanBlessStartEvent);
   AddEvent(eLangHuanBlessEvent_KickPlayer,time(NULL));
   //_dwEndTime = time(NULL);
   _byState = eLHBState_end;

}

void CLangHuanBlessMgr::OnReBegin()
{
    LOG_INF << "GameServer ReBegin...";
    OnAlarm();
    LOG_INF << " LHB ReBegin Suc.";
} 
void CLangHuanBlessMgr::OnEvent(SActEventData& oSActEventData)
{
    if(_bLog)
        LOG_INF<<"CWorldBossMgr::OnEvent: "<<oSActEventData.dwEventID;

    switch(oSActEventData.dwEventID)
    {
        case eLangHuanBlessEnrollEvent:
            {
                LOG_INF<<"BOSS TIP: "<<oSActEventData.dwParam;
                g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgLangHuanBlessEnroll,BuildStrVec(oSActEventData.dwParam));
            }
            break;
        case eLangHuanBlessStartEvent:
            {}
            break;
        case eLangHuanBlessEvent_KickPlayer:
            {
                KickPlayers();
            }
            break;
        default:
            {
            }
            break;
    }

}

bool CLangHuanBlessMgr::GMOpen()
{
    if(_bLog)
        LOG_INF<<"CLangHuanBlessMgr::GMOpen";
   
   time_t tNow = time(NULL);
   _dwAlarmTime = tNow;
   _dwReadyTime = tNow;
   _dwBeginTime = tNow;  //30s
   _dwEndTime   = tNow + 10*60; //3minute

   ClearEvent();

   SetStatus(eDayActivityStatusAlarm);
   AddEvent(eLangHuanBlessEnrollEvent,_dwReadyTime,10);
   
   UINT32 dwAttackCd = 40 * 60;
   AddPeriodEvent(eLangHuanBlessStartEvent,_dwBeginTime,1,dwAttackCd);
   return true;
}

bool CLangHuanBlessMgr::OpenActivity(UINT32 dwBegin,UINT32 dwEnd)
{
    if(_bLog)
        LOG_INF<<"CLangHuanBlessMgr::OpenActivity";
   
   _dwAlarmTime = dwBegin;
   _dwReadyTime = dwBegin;
   _dwBeginTime = dwBegin;  
   _dwEndTime   = dwEnd; 

   ClearEvent();

   SetStatus(eDayActivityStatusAlarm);
   AddEvent(eLangHuanBlessEnrollEvent,_dwReadyTime,10);
   
   UINT32 dwAttackCd = dwEnd - dwBegin;
   AddPeriodEvent(eLangHuanBlessStartEvent,_dwBeginTime,1,dwAttackCd);
   return true;
}

bool CLangHuanBlessMgr::IsAllowEnter(CPlayer &rPlayer)
{
    bool bOpen = false;
    if(CheckActTime()) //检测是否在活动期间
    {
       LOG_INF << " LHB Activity is openning.";
       bOpen = true;  
    }
    UINT64 qwNow = static_cast<UINT64>(time(NULL));
    CUserPtr pUser = rPlayer.GetUserPtr();
    if(!pUser)
    {
        LOG_INF << " pUser NULL.";
        return false;
    }
    UINT64 qwCalcTime =  pUser->GetVars().GetVar(ePlayerLHBLoginTime);
    LOG_INF << "LHB qwCalcTime(" << qwCalcTime << ").";
    UINT64 qwLoginTime  = 0;
    UINT64 qwEndTime = 0;
    GETLOGINTIME(qwCalcTime,qwLoginTime);
    GETLEAVETIME(qwCalcTime,qwEndTime);
    if(qwLoginTime == 0 || qwEndTime == 0)
    {
        LOG_INF << " qwLoginTime || qwEndTime is 0 [Error].";
        return false;
    }
    LOG_INF << " NowTime="<<qwNow << "|qwLoginTime=" <<qwLoginTime << "|qwEndTime=" <<qwEndTime;
    
    if(qwEndTime > qwNow && qwNow > qwLoginTime)
    {
        LOG_INF << "LHB qwNow - qwLoginTime = " << qwNow - qwLoginTime;
        if(IsReBegin())
        {
            if(!CalcOffLinePlayer(rPlayer))
            {
                LOG_INF << " LHB Calc Error!";
            }
            return false;
        }
    }
    
    if(qwEndTime < qwNow && qwNow > qwLoginTime && qwEndTime > qwLoginTime)
    {
        LOG_INF << "LHB qwNow - qwLoginTime = " << qwNow - qwLoginTime;
        if(!CalcOffLinePlayer(rPlayer))
        {
            LOG_INF << " LHB Calc Error!";
        }
        return false ;
    }
    
    return bOpen;
}

bool CLangHuanBlessMgr::CheckActTime()
{
   time_t tNow = time(NULL);
   if(tNow > _dwReadyTime && tNow < _dwEndTime)
       return true;
   return false;
}
UINT16  CLangHuanBlessMgr::GetMapID()
{
    UINT16 wMapId = static_cast<UINT16>(_dwMapId);
    return wMapId;
}
bool CLangHuanBlessMgr::IsReBegin()
{
    return _mapID2LHBPlayerPtr.size() == 0 ? true : false;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

