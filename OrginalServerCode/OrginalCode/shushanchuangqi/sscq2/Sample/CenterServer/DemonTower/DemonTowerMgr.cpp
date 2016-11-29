#include "stdafx.h"
#include "DemonTowerMgr.h"
#include "User.h"
#include "UserMgr.h"
#include "Game2CenterDemonTowerS.h"
#include "DemonTowerSvrS.h"
#include "SysMsgDefine.h"
#include "DemonTower.h"
#include "Parameter.h"
#include "EventCenter.h"
#include "LogDataDefine.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "CenterDataMgr.h"
using namespace NEventCenter;
CDemonTowerMgr g_DemonTowerMgr;

void AddVecMoney(TVecMoneyInfo& vecMoneyInfo,const MoneyInfo& rMoneyInfo)
{
    bool bAdd = true;
    for(MoneyInfo& tmpMoneyInfo:vecMoneyInfo)
    {
        if(tmpMoneyInfo.dwMoneyType == rMoneyInfo.dwMoneyType)
        {
            bAdd = false;
            tmpMoneyInfo.dwMoneyValue += rMoneyInfo.dwMoneyValue; 
        }
    }
    if(bAdd)
        vecMoneyInfo.push_back(rMoneyInfo);
}

//vecMoneyInfo = vecMoneyInfo + vecAddMoneyInfo
void AddVecMoney(TVecMoneyInfo& vecMoneyInfo,const TVecMoneyInfo& vecAddMoneyInfo)
{
    for(const MoneyInfo& tmpMoneyInfo:vecAddMoneyInfo)
    {
        AddVecMoney(vecMoneyInfo,tmpMoneyInfo);
    }
}


CDemonTowerMgr::CDemonTowerMgr()
{
    _bOpenLog = true;
    _dwResetTime = 0;
    _dwReduceAttrTime = 0;
    _dwLastSubSpeedTime = 0;
}


//锁妖塔
CDemonTowerMgr::~CDemonTowerMgr()
{
}


bool CDemonTowerMgr::Init()
{
    
    _dwAttackCD =  ATTCK_CD;
    _dwPrizeCD  = PRIZE_CD;
    _dwMinPrizeTimeSpan = MIN_PRIZE_TIMESPAN;
    if(!_dwAttackCD || !_dwPrizeCD)
    {
        LOG_CRI << "CDemonTowerMgr::Init Error CD == 0 ";
        return false;
    }

    string strPath = Config._strConfigDir + "Conf/Table/DemonTower.xml";
    CDemonTowerLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
        return false;
    }


    SDemonTowerCFGExPtr pLowDemonTowerCFGEx; //上一层配置
    for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
    {
       const SDemonTowerCFG* pDemonTowerCFG = oLoader._vecData[i];
       if(pDemonTowerCFG)
       {
           SDemonTowerCFGExPtr pDemonTowerCFGExPtr(new SDemonTowerCFGEx(pDemonTowerCFG));
           _vecSDemonTowerCFGExPtr.push_back(pDemonTowerCFGExPtr);

                
           if(pDemonTowerCFG->_Atk)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULATTACK;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Atk;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

            if(pDemonTowerCFG->_Hp)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULHP;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Hp;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

           if(pDemonTowerCFG->_Craze)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULCRITICAL;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Craze;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

           if(pDemonTowerCFG->_Pierce)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULCOUNTER;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Pierce;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

           if(pDemonTowerCFG->_Agilty)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULSPEED;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Agilty;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

           if(pDemonTowerCFG->_Def)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULDEFENCE;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Def;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

           if(pDemonTowerCFG->_Destory)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULHIT;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Destory;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }


           if(pDemonTowerCFG->_Tenacity)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULDODGE;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Tenacity;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

           //day prize
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType = pDemonTowerCFG->_DayPrizeType;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_DayPrize;
               pDemonTowerCFGExPtr->vecDayPrize.push_back(oMoneyInfo);
           }

           //计算累计奖励
           if(pLowDemonTowerCFGEx)
           {
               AddVecMoney(pDemonTowerCFGExPtr->vecDayPrize,pLowDemonTowerCFGEx->vecDayPrize);
           }
            
           //save下次用
           pLowDemonTowerCFGEx = pDemonTowerCFGExPtr;

           //pass prize
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType = pDemonTowerCFG->_PassPrizeType;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_PassPrize;
               pDemonTowerCFGExPtr->vecPassPrize.push_back(oMoneyInfo);
           }

        SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(i+1);
        if(NULL == pDemonTowerFloorInfo)
        {
            return false;
        }
        else
        {
            pDemonTowerFloorInfo->dwFloorID = i+1;
            pDemonTowerFloorInfo->dwMaxPos = pDemonTowerCFG->_PositoinCount?pDemonTowerCFG->_PositoinCount:1;
            if(pDemonTowerFloorInfo->dwMaxPos >= MAX_POSITON)
            {
                pDemonTowerFloorInfo->dwMaxPos = MAX_POSITON-1;
            }
            pDemonTowerFloorInfo->bCanAtk = pDemonTowerCFG->_IsCanFighter?true:false;
        }


       }
    }



    return true;
}

//从开始计时到现在多少天
UINT32 GetPassDay(UINT32 dwTime)
{
    return dwTime/3600/24;
}

UINT32 GetDayTime(UINT32 dwHour)
{
   time_t tNow = time(NULL);
    struct tm *pTm = localtime(&tNow);
	tm oTm = *pTm;
	oTm.tm_hour = dwHour;
	oTm.tm_min = 0;
    oTm.tm_sec = 0;
    return mktime(&oTm);
}

void CDemonTowerMgr::TimerCheck(UINT64 qwTick)
{
    //未加载数据
    if(0 == _dwResetTime)
    {
        return;
    }

    //19点更新
    if( (time(NULL) > GetDayTime(19)) && (_dwResetTime < GetDayTime(19)))
    {
        OnReset();

        _dwResetTime = time(NULL);
    }
    

    UINT32 dwReduceCD = 5; //10分钟

    if(_dwReduceAttrTime<time(NULL))
    {
        if( 0 == _dwLastSubSpeedTime)
        {
            _dwLastSubSpeedTime = time(NULL);
        }
        for(UINT32 i = 1; i < MAX_FLOORID; ++i)
        {

            SDemonTowerFloorInfo& rDemonTowerFloor = _arFloorInfo[i];
            for(UINT32 j=0; j<MAX_POSITON; ++j)
            {
                GuardInfo& rGuardInfo = rDemonTowerFloor.arGuardInfo[j];
                UINT64 qwUserID = rGuardInfo.qwUserID;
                if(0 == qwUserID)
                {
                    continue;
                }

                DemonTowerUserPtr pDemonTowerUser=GetTowerUserInfoByUserId(qwUserID);
                if(NULL == pDemonTowerUser)
                {
                    //取消镇守信息
                    rGuardInfo.qwUserID = 0;
                    LOG_CRI<<"null pDemonTowerUser:"<<qwUserID;
                    continue;
                }

                OnReduceAttr(pDemonTowerUser,rGuardInfo);
                UINT32 dwRet = OnGainPrize(pDemonTowerUser,rGuardInfo);
                if(dwRet == eGainPrize_RESET)
                {
                    //OnResetPlayer(pDemonTowerUser);
                }

                //扣除加速时间
                /*
                if(pDemonTowerUser->dwGuardGatherSpeedEndTimer)
                {
                    UINT32 dwSpanTime = _dwLastSubSpeedTime - time(NULL);
                    if(pDemonTowerUser->dwGuardGatherSpeedEndTimer > dwSpanTime )
                    {
                        pDemonTowerUser->dwGuardGatherSpeedEndTimer -= dwSpanTime;
                    }
                    else
                    {
                        pDemonTowerUser->dwGuardGatherSpeedEndTimer = 0;

                    }

                    g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);

                }
                */

                //GuardInfoChangeNotify(i,pDemonTowerUser->dwGuardPos,qwUserID,rGuardInfo);

            }

        }
        _dwReduceAttrTime = time(NULL)+dwReduceCD;

    }

}

void CDemonTowerMgr::LoadFromDB()
{
  g_Center2DBCommC.Send_GetDemonTowerInfo(	[] (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NDemonTowerGS::TVecDemonTowerPlayer& vecDemonTowerPlayer //(返回值)镇妖塔玩家信息
	)
          {
            if(0 == byRet_)
                g_DemonTowerMgr.OnLoad(vecDemonTowerPlayer);
          }
); 
}

void CDemonTowerMgr::OnLoad(const TVecDemonTowerPlayer& vecDemonTowerUser)
{
    //UINT32 dwTodays = GetPassDay(time(NULL));


    for(auto itr = vecDemonTowerUser.begin(); itr != vecDemonTowerUser.end(); itr++)
    {
        DemonTowerUserPtr pInfo(new SDemonTowerPlayer(*itr));
        _mapDemonTowerUserPtr.insert(make_pair(pInfo->qwUserID,pInfo));
        if(0 != pInfo->dwGuardStartTime && pInfo->dwGuardStartTime<GetDayTime(19))
        {
            _dwResetTime = pInfo->dwGuardStartTime;
        }

          if(pInfo->dwGuardFloorID && pInfo->dwGuardPos)
          {
             SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(pInfo->dwGuardFloorID);
            if(pDemonTowerFloorInfo)
            {
                if( pInfo->dwGuardPos < MAX_POSITON)
                {
                       GuardInfo& rGardInfo  =  pDemonTowerFloorInfo->arGuardInfo[pInfo->dwGuardPos];
                       rGardInfo.qwUserID    = pInfo->qwUserID;
                       rGardInfo.qwRoleID    = pInfo->qwRoleID;
                       rGardInfo.dwGuardPos  = pInfo->dwGuardPos;
                       rGardInfo.dwLastFightCD = 0;
                       FullPlayerInfo(pInfo,pDemonTowerFloorInfo->arGuardInfo[pInfo->dwGuardPos].oDemonFloorPlayer);
                }
            }
          }


    }

    if(0 == _dwResetTime)
    {
        _dwResetTime = time(NULL);
    }
}

void ParseData(SDemonTowerKillMonster& rKillMonster,const SCenterData& oCenterData)
{
    rKillMonster.strName = oCenterData.strParam;
    rKillMonster.dwBattlePoint = oCenterData.dwParam2;
    rKillMonster.dwRounds = oCenterData.dwParam3;
    rKillMonster.qwReportID = oCenterData.qwParam;
    rKillMonster.qwUserID = oCenterData.qwParam4;

    URoleInfo uRoleInfo;
    uRoleInfo.dwRole = oCenterData.dwParam1;

    rKillMonster.byColor =uRoleInfo.sRole.byColor;  
    rKillMonster.bySex   =uRoleInfo.sRole.bySex;    
    rKillMonster.byCareer=uRoleInfo.sRole.byCareer; 
    rKillMonster.byLevel =uRoleInfo.sRole.byLevel;  
}
void CDemonTowerMgr::OnLoad_MinTurns(const SCenterData& oCenterData)
{
    UINT32 dwFloorID = oCenterData.qwInstID;
    if(dwFloorID>= MAX_FLOORID)
    {
        LOG_CRI<<"ERROR floorID:"<<dwFloorID;
        return;
    }

    SDemonTowerKillMonster oKillMonster;
    ParseData(oKillMonster,oCenterData);
    LOG_INF<<"OnLoad_MinTurns:"<<dwFloorID<<"|"<<oCenterData.qwInstID2<<"|"<<oCenterData.qwParam;
    _arMinRound[dwFloorID].push_back(oKillMonster);
}

void CDemonTowerMgr::OnLoad_MinBattlePoint(const SCenterData& oCenterData)
{
    UINT32 dwFloorID = oCenterData.qwInstID;
    if(dwFloorID>= MAX_FLOORID)
    {
        LOG_CRI<<"ERROR floorID:"<<dwFloorID;
        return;
    }

    SDemonTowerKillMonster oKillMonster;
    ParseData(oKillMonster,oCenterData);
    _arMinBattlePoint[dwFloorID].push_back(oKillMonster);

}

void CDemonTowerMgr::Update2DB(ECenterData eCenterData,UINT32 dwFloorID,UINT32 dwNo,SDemonTowerKillMonster& rSDemonTowerKillMonster,bool bDelete /*= false*/)
{
    URoleInfo uRoleInfo;
    uRoleInfo.sRole.byColor = rSDemonTowerKillMonster.byColor;
    uRoleInfo.sRole.bySex   = rSDemonTowerKillMonster.bySex;
    uRoleInfo.sRole.byCareer= rSDemonTowerKillMonster.byCareer;
    uRoleInfo.sRole.byLevel = rSDemonTowerKillMonster.byLevel;
 
    SCenterData oCenterData;
    oCenterData.wType = eCenterData;
    oCenterData.qwInstID = dwFloorID;
    oCenterData.qwInstID2 = dwNo;
    oCenterData.strParam = rSDemonTowerKillMonster.strName; 
    oCenterData.dwParam1 = uRoleInfo.dwRole;
    oCenterData.dwParam2 = rSDemonTowerKillMonster.dwBattlePoint;
    oCenterData.dwParam3 = rSDemonTowerKillMonster.dwRounds;
    oCenterData.qwParam  = rSDemonTowerKillMonster.qwReportID;
    oCenterData.qwParam4 = rSDemonTowerKillMonster.qwUserID;
    g_CenterDataMgr.Update2DB(oCenterData,bDelete);
}


bool CDemonTowerMgr::GetDemonTowerInfo(UINT64 qwUserID,SDemonTowerPlayer& rSDemonTowerPlayer)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
        return false;
    }

    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(!pDemonTowerUser)
    {
        return false;
    }

    rSDemonTowerPlayer = *pDemonTowerUser;

    //pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_DemonTowerPlayerNotify(*pDemonTowerUser));
    
    return true;

}

//进入锁妖塔
UINT32 CDemonTowerMgr::PlayerEnter(UINT64 qwUserID, UINT32 dwFloorID)
{
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser || 0 == dwFloorID)
    {
         return eDemonTower_Invalid_UserID;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterDemonTowerS.SendSvr_EnterDemonTower(&dwServerID,1,qwUserID,dwFloorID);
    
    if(_bOpenLog)
    {
        LOG_INF<<"PlayerEnter request qwUserID:"<<qwUserID<<" dwFloorID:"<<dwFloorID;
    }

    return 0;

}


UINT32 CDemonTowerMgr::onPlayerEnterNextFloor(UINT32 qwUserID)
{

    DemonTowerUserPtr pDemonTowerUserPtr = GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUserPtr)
    {
        return -1;
    }

    UINT32 dwNextFloorID = pDemonTowerUserPtr->dwFloorID + 1;

    return  PlayerEnter(qwUserID,dwNextFloorID);
}

UINT32 CDemonTowerMgr::OnPlayerEnter(const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer)
{
  SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(oDemonTowerEnterPlayer.dwFloorID);
  if(NULL == pDemonTowerFloorInfo)
  {
      return eDemonTower_Invalid_FloorID;
  }
    
  if(_bOpenLog)
  {
     LOG_INF<<"OnPlayerEnter  qwUserID:"<<oDemonTowerEnterPlayer.qwUserID<<" dwFloorID:"<<oDemonTowerEnterPlayer.dwFloorID;
  }


  CUserPtr pUser = CUserMgr::GetUserByUserID(oDemonTowerEnterPlayer.qwUserID);
  if(!pUser)
  {
      return eDemonTower_Invalid_UserID;
  }
  TVecGuardInfo  vecGuardInfo;
  for(UINT16 i = 1; i <= pDemonTowerFloorInfo->dwMaxPos; i++)
  {
      //注意默认拷贝函数不能带字符串
      vecGuardInfo.push_back(pDemonTowerFloorInfo->arGuardInfo[i]);
      if(_bOpenLog)
      {
          LOG_INF<<"FloorInfo dwFloorID:"<<oDemonTowerEnterPlayer.dwFloorID<<"GuardPos:"<<i<<" qwUserID:"<<pDemonTowerFloorInfo->arGuardInfo[i].qwUserID;
      }
  }

  pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_GuardInfoNotify(oDemonTowerEnterPlayer.dwFloorID,vecGuardInfo));
  pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_EnterDemonTowerNotify(oDemonTowerEnterPlayer.dwFloorID));
  auto itr = _mapDemonTowerUserPtr.find(oDemonTowerEnterPlayer.qwUserID);
  if(itr == _mapDemonTowerUserPtr.end())
  {
     /////////////////////
     DemonTowerUserPtr pInfo(new SDemonTowerPlayer);
     pInfo->qwUserID = oDemonTowerEnterPlayer.qwUserID;
     pInfo->qwRoleID = oDemonTowerEnterPlayer.qwRoleID;
     pInfo->strRoleName = pUser->GetRoleName();
     pInfo->bySex = pUser->GetSex();
     pInfo->byLevel = pUser->GetLevel();
     pInfo->dwFloorID = oDemonTowerEnterPlayer.dwFloorID;
     pInfo->dwPower = oDemonTowerEnterPlayer.dwPower;
     pInfo->byColor = pUser->GetColor();
     _mapDemonTowerUserPtr.insert(make_pair(pInfo->qwUserID,pInfo));
  }
  else
  {
      itr->second->dwFloorID =oDemonTowerEnterPlayer.dwFloorID;
      //更新一下等级
      itr->second->byLevel = pUser->GetLevel(); 
      itr->second->dwPower = oDemonTowerEnterPlayer.dwPower;
  }

  return 0;

}

//离开锁妖塔
UINT32  CDemonTowerMgr::PlayerLeave(UINT64 qwUserID)
{
    if(_bOpenLog)
    {
        LOG_INF<<"DemonTowerMgr::PlayerLeave qwUserID:"<<qwUserID;
    }

    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
         return eDemonTower_Invalid_UserID;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
   
    auto itr = _mapDemonTowerUserPtr.find(qwUserID);
    if(itr != _mapDemonTowerUserPtr.end())
    {
        itr->second->dwFloorID = 0;
    }
    g_Game2CenterDemonTowerS.SendSvr_LeaveDemonTower(&dwServerID,1,qwUserID);
    return 0;
}


void   CDemonTowerMgr::OnPlayerLeave(UINT64 qwUserID)
{
    //暂时没有需要处理的

    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(pDemonTowerUser)
    {
        if(!pDemonTowerUser->vecDaySoulPrize.empty())
        {
            TakePassDayPrize(qwUserID);

        }

        if(!pDemonTowerUser->vecFailSoulPrize.empty())
        {
            TakeGuardFailPrize(qwUserID);
        }
    }
    else
    {
        LOG_CRI<<"OnPlayerLeave ERROR:"<<qwUserID;
    }

}

void CDemonTowerMgr::OnPlayerPass(UINT64 qwUserID,UINT16 wFloorID,UINT16 wMonsterColor, const std::string& strMonsterName)
{
   if(_bOpenLog)
   {
       LOG_INF<<"CDemonTowerMgr::OnPlayerPass qwUserID:"<<qwUserID<<"wFloorID:"<<wFloorID;
   }

   CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
   if(!pUser)
   {
       return;
   } 
   pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_PassDemonTowerNotify(wFloorID));

   /*
   SDemonTowerCFGExPtr pDemonTowerCFGExPtr = GetDemonTowerCFG(wFloorID);
   if(pDemonTowerCFGExPtr)
   {

   }
   */

   if(g_CenterGameVar.GetVar(NVarDefine::eSystemVarDemonTowerMaxTop) < wFloorID)
   {
       g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgTowerFirstCross, BuildStrVec(pUser->GetColor(),pUser->GetRoleName(),wFloorID,wMonsterColor,strMonsterName));
       g_CenterGameVar.SetVar(NVarDefine::eSystemVarDemonTowerMaxTop, wFloorID);
   }

   if(0 == (wFloorID%10))
        g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgTowerPass, BuildStrVec(pUser->GetColor(),pUser->GetRoleName(),wFloorID));

}

void FullUserInfo(SDemonTowerKillMonster& rMinRound,CUser& rUser)
{
    rMinRound.qwUserID = rUser.GetUserID();
    rMinRound.strName = rUser.GetRoleName();
    rMinRound.byColor = rUser.GetColor();
    rMinRound.bySex   = rUser.GetSex();
    rMinRound.byCareer = rUser.GetCareer();
    rMinRound.byLevel  = rUser.GetLevel();
}

//交换数据信息
void SwapInfo(SDemonTowerKillMonster& rOld, SDemonTowerKillMonster& rNew)
{
    SDemonTowerKillMonster oTemp = rNew;
    rNew = rOld;
    rOld = oTemp;
}

bool CDemonTowerMgr::IsNeedUpdate(TVecDemonTowerKillMonster& vecKillMonster,SDemonTowerKillMonster& rKillMonster,UINT16 wFloorID,ECenterData eCenterData)
{
    bool bFind = false;
    for(size_t i=0;i < vecKillMonster.size(); )
    {
        SDemonTowerKillMonster& rTmp = vecKillMonster[i];

        if(!bFind)
        {
        if(rTmp.qwUserID == rKillMonster.qwUserID)
        {
            if(eCenterData == eCenterDate_DemonTower_MinRonds)
            {
                if(rTmp.dwRounds<= rKillMonster.dwRounds)
                    return false;
            }
            else if(eCenterData == eCenterDate_DemonTower_MinBattlePoint)
            {
                if(rTmp.dwBattlePoint <= rKillMonster.dwBattlePoint)
                {
                    return false;
                }

            }
            else
            {
                return false;
            }
            bFind = true;
            vecKillMonster.erase(vecKillMonster.begin()+i);
            continue;
        }
        }
        else
        {
            Update2DB(eCenterData,wFloorID,i,rTmp);
        }

        i++;

    }

    return true;
}

//击败锁妖塔怪物
void CDemonTowerMgr::OnKillMonster(const SDemonTowerPassPlayer& oDemonTowerPassPlayer)
{
   CUserPtr pUser = CUserMgr::GetUserByUserID(oDemonTowerPassPlayer.qwUserID);
   if(!pUser)
   {
       LOG_DBG<<"eDemonTower_Invalid_UserID";
       return;
   }

   if(oDemonTowerPassPlayer.dwCurFloorID > MAX_FLOORID)
       return;

   UINT16 wFloorID = oDemonTowerPassPlayer.dwCurFloorID;
   TVecDemonTowerKillMonster& rVecMinRound = _arMinRound[wFloorID];

   SDemonTowerKillMonster oPassPlayer;
   oPassPlayer.dwRounds = oDemonTowerPassPlayer.wTurns;
   oPassPlayer.dwBattlePoint = oDemonTowerPassPlayer.dwPower;
   oPassPlayer.qwReportID = oDemonTowerPassPlayer.qwReportID;
   FullUserInfo(oPassPlayer,*pUser);

   SDemonTowerKillMonster oMinRoundInsert = oPassPlayer;
   
   bool bRetMinRound = IsNeedUpdate(rVecMinRound,oPassPlayer,wFloorID,eCenterDate_DemonTower_MinRonds);

   if(bRetMinRound)
   {
        for(size_t i=0;i < rVecMinRound.size(); i++)
        {
            SDemonTowerKillMonster& rMinRound = rVecMinRound[i];
            if(rMinRound.dwRounds < oPassPlayer.dwRounds)
           continue;
            SwapInfo(rMinRound,oMinRoundInsert);
            Update2DB(eCenterDate_DemonTower_MinRonds,wFloorID,i,rMinRound);
        }

        if(rVecMinRound.size() < MIN_TOP_SIZE)
        {
            rVecMinRound.push_back(oMinRoundInsert);
            Update2DB(eCenterDate_DemonTower_MinRonds,wFloorID,rVecMinRound.size()-1,oMinRoundInsert);
        }
   }

   TVecDemonTowerKillMonster& rVecMinBattlePoint = _arMinBattlePoint[wFloorID];
   SDemonTowerKillMonster oMinBattlePointInsert = oPassPlayer;
   bool bBattlePoint = IsNeedUpdate(rVecMinBattlePoint,oPassPlayer,wFloorID,eCenterDate_DemonTower_MinBattlePoint);
   if(bBattlePoint)
   {
      for(size_t i=0; i < rVecMinBattlePoint.size(); i++)
      {
          SDemonTowerKillMonster& rMinBattlePoint = rVecMinBattlePoint[i];
          if(rMinBattlePoint.dwBattlePoint < oMinBattlePointInsert.dwBattlePoint)
              continue;
          SwapInfo(rMinBattlePoint,oMinBattlePointInsert); 
          Update2DB(eCenterDate_DemonTower_MinBattlePoint,wFloorID,i,rMinBattlePoint);
      }
     
      if(rVecMinBattlePoint.size()<MIN_TOP_SIZE)
        {
            rVecMinBattlePoint.push_back(oMinBattlePointInsert);
            Update2DB(eCenterDate_DemonTower_MinBattlePoint,wFloorID,rVecMinBattlePoint.size()-1,oMinBattlePointInsert); 
        }
   }

   pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_PassInfoNotify(wFloorID,rVecMinRound,rVecMinBattlePoint));

}

/*
void FullPassInfo(const TVecDemonTowerKillMonster& rVecKillMonste,TVecDemonTowerKillMonster& vecPassPlayer)
{
    for(size_t i=0; i< rVecKillMonste.size(); i++)
    {
        const SDemonTowerKillMonster& rKillMonster = rVecKillMonste[i];
        PassPlayer oPassPlayer;
        oPassPlayer.qwUserID = rKillMonster.qwUserID;
        oPassPlayer.strName  = rKillMonster.strName;
        oPassPlayer.byColor  = rKillMonster.byColor;
        oPassPlayer.dwRounds  = rKillMonster.dwRounds;
        oPassPlayer.dwBattlePoint = rKillMonster.dwBattlePoint;
        oPassPlayer.qwReportID = rKillMonster.qwReportID;
        vecPassPlayer.push_back(oPassPlayer);
    }
}
*/
//获取过关信息
void CDemonTowerMgr::OnGetPassInfo(UINT16 wFloorID,TVecDemonTowerKillMonster& vecMinRound,TVecDemonTowerKillMonster& vecMinBattlePoint)
{
    if(wFloorID >= MAX_FLOORID)
    {
        LOG_CRI<<"Error floorID:"<<wFloorID;
        return;
    }
    TVecDemonTowerKillMonster& rvecMinRound       = _arMinRound[wFloorID]; 
    //FullPassInfo(rvecMinRound,vecMinRound);
    vecMinRound = rvecMinRound;
    TVecDemonTowerKillMonster& rvecMinBattlePoint = _arMinBattlePoint[wFloorID];
    //FullPassInfo(rvecMinBattlePoint,vecMinBattlePoint);
    vecMinBattlePoint = rvecMinBattlePoint;

}
 
//镇守
UINT32  CDemonTowerMgr::Guard(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos)
{
   if(_bOpenLog)
   {
       LOG_INF<<"CDemonTowerMgr::Guard  qwUserID:"<<qwUserID<<" dwFloorID:"<<dwFloorID<<" dwPos:"<<dwPos;
   }
   CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
   if(!pUser)
   {
       LOG_DBG<<"eDemonTower_Invalid_UserID";
       return eDemonTower_Invalid_UserID;
   }
   
   DemonTowerUserPtr pAtkPlayer= GetTowerUserInfoByUserId(qwUserID);
    if(!pAtkPlayer)
    {
        pUser->SendSysMsg(eMsgDemonTowerNotInTower);
        LOG_DBG<<"eDemonTower_NotInTower";
       return eDemonTower_NotInTower;
    }

    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_GetUserUINTProp(&dwServerID,1,qwUserID,ePropTopDemonFloorID,[qwUserID,dwFloorID,dwPos](UINT8 byRet_, //0为成功，1为失败，2为超时
		                                                                                       UINT32 dwValue, //(返回值)属性值
		                                                                                       UINT8 byError //(返回值)0 成功, 其他错误
                                                                                                )
            {
                if(byRet_ || byError)
                {
                    LOG_DBG<<"SendSvr_GetUserUINTProp Error";
                    return;

                }
                            

                UINT32 dwTopFloorID = dwValue;


                if(dwFloorID > dwTopFloorID)
                {
                    LOG_DBG<<"Error dwTopFloorID"<<dwTopFloorID<<" dwFloorID"<<dwFloorID;
                    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                    if(!pUser)
                    {
                        return;
                    }
    //return eDemonTower_NotPass;
                    pUser->SendSysMsg(eMsgDemonTowerLowFloor);
                    return;
                }
                
                g_DemonTowerMgr.OnGuard(qwUserID,dwFloorID,dwPos);
    
                });
    return 0;
}

UINT32  CDemonTowerMgr::OnGuard(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos)
{
   CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
   if(!pUser)
    {
        LOG_DBG<<"eDemonTower_NotInTower";
        return eDemonTower_NotInTower;
    }

   auto itr = _mapDemonTowerUserPtr.find(qwUserID);
   if(itr == _mapDemonTowerUserPtr.end())
   {
      pUser->SendSysMsg(eMsgDemonTowerNotInTower);
      LOG_DBG<<"eDemonTower_NotInTower";
      return eDemonTower_NotInTower;
   }
   

   SDemonTowerCFGExPtr pDemonTowerCFGExPtr = GetDemonTowerCFG(dwFloorID);    
   if(!pDemonTowerCFGExPtr)
   {

      pUser->SendSysMsg(eMsgDemonTowerErrorCFG);
      LOG_DBG<<"eDemonTower_Invalid_CFG";
      return eDemonTower_Invalid_CFG;
   }
   SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(dwFloorID);
   if(!pDemonTowerFloorInfo)
 
   {
       pUser->SendSysMsg(eMsgDemonTowerErrorFloor);
       LOG_DBG<<"eDemonTower_Invalid_FloorID";
       return eDemonTower_Invalid_FloorID;
   }
 
   if( !dwPos || dwPos > pDemonTowerCFGExPtr->_PositoinCount)
   {
       pUser->SendSysMsg(eMsgDemonTowerErrorPos);
       LOG_DBG<<"eDemonTower_Invalid_Positoin "<<dwPos<<" maxpos "<<pDemonTowerCFGExPtr->_PositoinCount;
       return eDemonTower_Invalid_Positoin;
   }
 
   if(pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID)
   {
       pUser->SendSysMsg(eMsgDemonTowerNotEmptyPos);
       LOG_DBG<<"eDemonTower_Not_Empty_Positoin";
       return eDemonTower_Not_Empty_Positoin;
   }

   if(0 != itr->second->dwGuardFloorID)
   {
        //pUser->SendSysMsg(eMsgDemonTowerHasGuardPos);
        //return eDemonTower_Invalid_FloorID;
        AbandonGuard(qwUserID);
   }


   //没有进入该层
 
   if(itr->second->dwFloorID != dwFloorID)
   {
       pUser->SendSysMsg(eMsgDemonTowerNotInCurFloor);
       LOG_DBG<<"eDemonTower_Invalid_FloorID";
       return eDemonTower_Invalid_FloorID;
   }
 
   //开始镇守
   pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID = qwUserID;
   pDemonTowerFloorInfo->arGuardInfo[dwPos].qwRoleID = itr->second->qwRoleID;   
   pDemonTowerFloorInfo->arGuardInfo[dwPos].dwGuardPos = dwPos;
   itr->second->dwGuardFloorID = dwFloorID;
   itr->second->dwGuardPos = dwPos;

   OnGuardInit(itr->second); //save db
   FullPlayerInfo(itr->second,pDemonTowerFloorInfo->arGuardInfo[dwPos].oDemonFloorPlayer);
  
   GuardInfoChangeNotify(dwFloorID,dwPos,qwUserID,pDemonTowerFloorInfo->arGuardInfo[dwPos]);

   //g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*(itr->second));
   PlayerInfoNotify(itr->second,false);

   //pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_GuardSucessNotify(dwFloorID,dwPos));
   
   if(_bOpenLog)
   {
       LOG_INF<<"CDemonTowerMgr::OnGuard  qwUserID:"<<qwUserID<<" dwFloorID:"<<dwFloorID<<" dwPos:"<<dwPos;
       LOG_INF<<"dwFloorID:"<<pDemonTowerFloorInfo->dwFloorID;
       for(UINT32 i=1; i <pDemonTowerFloorInfo->dwMaxPos; i++)
       {
           if(pDemonTowerFloorInfo->arGuardInfo[i].qwUserID)
           {
               LOG_INF<<"qwUserID:"<<pDemonTowerFloorInfo->arGuardInfo[i].qwUserID<<" dwPos:"<<i;
           }
       }
   }

    return 0;

}

//每天重置
void CDemonTowerMgr::OnReset()
{
    for(auto itr =  _mapDemonTowerUserPtr.begin(); itr != _mapDemonTowerUserPtr.end(); ++itr)
    {
        if(itr->second->dwGuardFloorID)
        {
            OnResetPlayer(itr->second);
        }
    }
}

void CDemonTowerMgr::OnResetPlayer(DemonTowerUserPtr& pGuardPlayer)
{
    if(_bOpenLog)
    {
        LOG_INF<<"OnResetPlayer: qwUserID:"<<pGuardPlayer->qwUserID<<"dwGuardPos:"<<pGuardPlayer->dwGuardPos<<"dwGuardStartTime:"<<pGuardPlayer->dwGuardStartTime;
    }

    float bRatePrize = 1.0;

    CalGuildPrize(pGuardPlayer,pGuardPlayer->vecDaySoulPrize,bRatePrize);
    
    //日志使用
    pGuardPlayer->dwTotalTime  = pGuardPlayer->dwGuardEndTime - pGuardPlayer->dwGuardStartTime;

    
    UINT32 dwGuardFloorID = pGuardPlayer->dwGuardFloorID;
    UINT32 dwGuardPos = pGuardPlayer->dwGuardPos;

    bool bOffline = true;
    CUserPtr pUser = CUserMgr::GetUserByUserID(pGuardPlayer->qwUserID);
    if(pUser&&pUser->IsOnline())
    {
        g_DemonTowerSvrS.SendClt_DemonTowerResetNotify(&pGuardPlayer->qwUserID,1,dwGuardFloorID,dwGuardPos,pGuardPlayer->vecDaySoulPrize);
        TakePassDayPrize(pGuardPlayer->qwUserID);
        bOffline = false;
    }

    UINT64 qwUserID = pGuardPlayer->qwUserID;

    if(pGuardPlayer->dwGuardPos < MAX_POSITON )
    {
         SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(dwGuardFloorID);
        if(NULL == pDemonTowerFloorInfo)
        {
            LOG_CRI<<"Error Reset NULL == pDemonTowerFloorInfo  dwGuardFloorID:"<<dwGuardFloorID;
            return;
        }

        GuardInfo& rGuardInfo = pDemonTowerFloorInfo->arGuardInfo[dwGuardPos];
        if(rGuardInfo.qwUserID != qwUserID)
        {
            LOG_CRI<<"Error Reset: "<<qwUserID<<"->"<<rGuardInfo.qwUserID;
        }
        {
            rGuardInfo.qwUserID = 0;
            rGuardInfo.qwRoleID = 0;
            rGuardInfo.dwLastFightCD = 0;
            SDemonFloorPlayer oDemonFloorPlayer;
            oDemonFloorPlayer.dwFloorID = dwGuardFloorID;
            rGuardInfo.oDemonFloorPlayer = oDemonFloorPlayer;

        }

        GuardInfoChangeNotify(dwGuardFloorID,dwGuardPos,0,rGuardInfo); 
    }
    else
    {
         LOG_CRI<<"Error Reset pos"<<dwGuardPos<<"UserID:"<<qwUserID;
    }

    OnGuardEnd(pGuardPlayer);
    PlayerInfoNotify(pGuardPlayer,true);
    if(bOffline)
    {
        pGuardPlayer->dwGuardPos = eDemonTower_Prize_Day;
    }


 }

UINT32 CDemonTowerMgr::AbandonGuard(UINT64 qwUserID,bool bReset)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {

        return eDemonTower_Invalid_UserID;
    }
    
    DemonTowerUserPtr pGuardPlayer= GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pGuardPlayer)
    {
        pUser->SendSysMsg(eMsgDemonTowerNotInTower);
        return eDemonTower_NotInTower;
    }

    //已经放弃过了
   if(0 == pGuardPlayer->dwGuardFloorID)
    {
        //pUser->SendSysMsg(eMsgDemonTowerHasGuardPos);
        return eDemonTower_Invalid_FloorID;
    }

    SDemonTowerCFGExPtr pDemonTowerCFGExPtr = GetDemonTowerCFG(pGuardPlayer->dwGuardFloorID);    
    if(!pDemonTowerCFGExPtr)
    {

      pUser->SendSysMsg(eMsgDemonTowerErrorCFG);
      return eDemonTower_Invalid_CFG;
    }
   
    SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(pGuardPlayer->dwGuardFloorID);
    if(!pDemonTowerFloorInfo)
    {
       pUser->SendSysMsg(eMsgDemonTowerErrorFloor);
       return eDemonTower_Invalid_FloorID;
    }

    float bRatePrize = SParamConfig::wDemonTowerAbandonPrizeRate/MAX_RATE;
    if(bReset)
    {
        bRatePrize = 1.0;
 
    }

    TVecMoneyInfo  VecMoneyInfo;
    TVecUserItem vecUserItem;
    
    if(bReset)
    {
        CalGuildPrize(pGuardPlayer,pGuardPlayer->vecDaySoulPrize,bRatePrize);
    }
    else
    {
        CalGuildPrize(pGuardPlayer,VecMoneyInfo,bRatePrize);

        for(size_t i = 0; i < VecMoneyInfo.size(); ++i)
        {
            SUserItem oUserItem;
            oUserItem.dwTypeID = VecMoneyInfo[i].dwMoneyType;
            oUserItem.dwCount = VecMoneyInfo[i].dwMoneyValue;
            vecUserItem.push_back(oUserItem);

        }
    }


    UINT32 dwChangePos = pGuardPlayer->dwGuardPos;
    UINT32 dwFloorID   = pGuardPlayer->dwGuardFloorID;

    if(_bOpenLog)
    {
       LOG_INF<<"CDemonTowerMgr::AbandonGuard  qwUserID:"<<qwUserID<<" dwFloorID"<<pGuardPlayer->dwGuardFloorID<<" dwGuardPos:"<<pGuardPlayer->dwGuardPos;

    }

    if(pGuardPlayer->dwGuardPos < MAX_POSITON )
    {
        GuardInfo& rGuardInfo = pDemonTowerFloorInfo->arGuardInfo[pGuardPlayer->dwGuardPos];
        if(rGuardInfo.qwUserID != qwUserID)
        {
            LOG_CRI<<"Error AbandonGuard "<<qwUserID<<"->"<<rGuardInfo.qwUserID;
        }
        {
            rGuardInfo.qwUserID = 0;
            rGuardInfo.qwRoleID = 0;
            //rGuardInfo.dwGuardPos = 0;
            rGuardInfo.dwLastFightCD = 0;
            SDemonFloorPlayer oDemonFloorPlayer;
            oDemonFloorPlayer.dwFloorID = dwFloorID;
            rGuardInfo.oDemonFloorPlayer = oDemonFloorPlayer;

        }
    }
    else
    {
         LOG_CRI<<"Error AbandonGuard pos"<<pGuardPlayer->dwGuardPos<<"UserID:"<<qwUserID;
    }

    //

    OnGuardEnd(pGuardPlayer);
    GuardInfo oGuardInfo;
    GuardInfoChangeNotify(dwFloorID,dwChangePos,0,oGuardInfo);
    PlayerInfoNotify(pGuardPlayer,true);
    //GuardInfoNotify(pDemonTowerFloorInfo);
    //19点重置发奖励通知
    if(bReset)
    {
            
        return 0;
    }

    //主动放弃直接发奖励
    UINT32 dwServerID = pUser->GetGameSvrID();

    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemFrom_DemonTower,vecUserItem,[qwUserID](UINT8 byRet_, UINT8 byError)
                                {
                                    
                                    if(byRet_ || byError)
                                    {   
                                        return;
                                    }   
                                     
                                });



    return 0;


}

//抢夺镇守位置
UINT32  CDemonTowerMgr::AtkPlayer(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos)
{

   if(_bOpenLog)
   {
       LOG_INF<<"CDemonTowerMgr::AtkPlayer  qwUserID:"<<qwUserID<<" dwFloorID:"<<dwFloorID<<" dwPos:"<<dwPos;
   }

   //1是主镇守位
   if(dwPos != 1)
   {
       return Guard(qwUserID,dwFloorID,dwPos);
   }

   CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
   if(!pUser)
    {
      LOG_DBG<<"eDemonTower_Invalid_UserID";
      return eDemonTower_Invalid_UserID;
    }
    

   //放弃镇守
    if(0 == dwFloorID)
    {

       return AbandonGuard(qwUserID);

    }

    UINT32 dwServerID = pUser->GetGameSvrID();
    
    g_Game2CenterCommS.SendSvr_GetUserUINTProp(&dwServerID,1,qwUserID,ePropTopDemonFloorID,[qwUserID,dwFloorID,dwPos](UINT8 byRet_, //0为成功，1为失败，2为超时
		                                                                                       UINT32 dwValue, //(返回值)属性值
		                                                                                       UINT8 byError //(返回值)0 成功, 其他错误
                                                                                                )
            {
                if(byRet_ || byError)
                {
                    return;

                }

                UINT32 dwTopFloorID = dwValue;


                 if(dwFloorID > dwTopFloorID)
                 {
                        LOG_DBG<<"Error atk floor dwFloorID"<<dwFloorID <<"dwTopFloorID"<<dwTopFloorID;
                       CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                      if(!pUser)
                      {
                       return;
                      }
                      pUser->SendSysMsg(eMsgDemonTowerLowFloor);
                      return;
                  }

                  g_DemonTowerMgr.OnAtkPlayer(qwUserID,dwFloorID,dwPos);
             });

    return 0;
}


UINT32  CDemonTowerMgr::OnAtkPlayer(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        LOG_DBG<<"eDemonTower_Error";
        return eDemonTower_Error;
    }

    DemonTowerUserPtr pAtkPlayer= GetTowerUserInfoByUserId(qwUserID);
    if(!pAtkPlayer)
    {
        pUser->SendSysMsg(eMsgDemonTowerNotInTower);
        LOG_DBG<<"eDemonTower_NotInTower";
        return eDemonTower_NotInTower;
    }

   
 
    SDemonTowerCFGExPtr pDemonTowerCFGExPtr = GetDemonTowerCFG(dwFloorID);    
    if(!pDemonTowerCFGExPtr)
    {
        pUser->SendSysMsg(eMsgDemonTowerErrorCFG);
        LOG_DBG<<"eDemonTower_Invalid_CFG";
        return eDemonTower_Invalid_CFG;
    }
    
    SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(dwFloorID);
    if(!pDemonTowerFloorInfo)
   
    {
        pUser->SendSysMsg(eMsgDemonTowerErrorFloor);
        LOG_DBG<<"eDemonTower_Invalid_FloorID";
        return eDemonTower_Invalid_FloorID;
    }
   
    if( !dwPos || dwPos > pDemonTowerCFGExPtr->_PositoinCount )
    {
        pUser->SendSysMsg(eMsgDemonTowerErrorPos);
        LOG_DBG<<"eDemonTower_Invalid_Positoin";
        return eDemonTower_Invalid_Positoin;
    }
   
    if(!pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID)
    {
       return Guard(qwUserID,dwFloorID,dwPos);
    }

   //攻击cd检查
    if(pAtkPlayer->dwGuardNextAttackTime>time(NULL))
    {

        //pUser->SendSysMsg(eMsgDemonTowerVSPlayerCD);
        UINT32 dwTime = pAtkPlayer->dwGuardNextAttackTime-time(NULL);
        pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgDemonTowerVSPlayerCD,BuildStrVec(dwTime)));
        return eDemonTower_NotInTower;
    }
  
    if(qwUserID == pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID)
    {
        pUser->SendSysMsg(eMsgDemonTowerErrorPos);
        LOG_DBG<<"eDemonTower_Invalid_Positoin";
        return eDemonTower_Invalid_Positoin;
    }
    
    if(0 != pAtkPlayer->dwGuardFloorID)
    {
        //pUser->SendSysMsg(eMsgDemonTowerHasGuardPos);
        //LOG_DBG<<"eDemonTower_Invalid_FloorID";
        //return eDemonTower_Invalid_FloorID;
        AbandonGuard(qwUserID);
    }

  
    //没有进入该层
   
    if(pAtkPlayer->dwFloorID != dwFloorID)
    {
       pUser->SendSysMsg(eMsgDemonTowerNotInCurFloor); 
       LOG_DBG<<"eDemonTower_Invalid_FloorID";
       return eDemonTower_Invalid_FloorID;
   
    }
   
    if(pDemonTowerFloorInfo->arGuardInfo[dwPos].dwLastFightCD > time(NULL) )
    {
        pUser->SendSysMsg(eMsgDemonTowerFightCD);
        LOG_DBG<<"eDemonTower_FightCD";
        return eDemonTower_FightCD;
    }

    UINT64 qwRoleID  = pAtkPlayer->qwRoleID;
    UINT64 qwDefRoleID = pDemonTowerFloorInfo->arGuardInfo[dwPos].qwRoleID;
    UINT64 qwDefUserID = pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID;
 
    DemonTowerUserPtr pDefPlayer= GetTowerUserInfoByUserId(qwDefUserID);
    if(NULL == pDefPlayer)
    {
        return eDemonTower_Invalid_Positoin;
    }
   
    //5s战斗cd 防止多人攻击一个位置
    pDemonTowerFloorInfo->arGuardInfo[dwPos].dwLastFightCD = time(NULL) + 5;


    UINT32 dwBufferID =0;
    UINT32 dwSkillID = 0;
    UINT32 dwBufferCnt = 0;
    if(pDefPlayer->dwGuardReduceRate < 100)
    {
        dwBufferID = 18;
        dwSkillID = 4200;
        dwBufferCnt = 100 - pDefPlayer->dwGuardReduceRate;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_FigtherToOther(&dwServerID, 1, qwRoleID,qwDefRoleID,0, NBattleGS::EBDemonTower,dwBufferID,dwSkillID,dwBufferCnt,[qwUserID,qwRoleID,qwDefRoleID,qwDefUserID,dwFloorID,dwPos,dwServerID](
                UINT8 byRet_,UINT8 byRet,UINT8 bySuc, UINT64 qwBattleID,UINT32 dwSelfFighterPower, UINT8 bySelfQuality, UINT32 dwOtherFighterPower, UINT8 byOtherQuality, UINT32 dwTurns)
            {
                if(byRet_ != 0)
                 {
                    LOG_DBG<<"GameServer Error";
                    return;
                }

                //战斗1次
                {
                    //TVecINT32 vecParam;
                    //vecParam.push_back(1);
                    //g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID, 1,qwUserID,eEventType_DemonTowerBattle,vecParam,"",true);
                    //g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID, 1,qwDefUserID,eEventType_DemonTowerBattle,vecParam,"",true);
                }

                if(0 != byRet)
                {
                    LOG_DBG<<"SendSvr_FigtherToOther fail";
                    return;
                }
                if(bySuc)
                {
                    //抢夺成功
                    g_DemonTowerMgr.OnChangePos(qwUserID,dwFloorID,dwPos);
                    DemonTowerUserPtr pAtkPlayer= g_DemonTowerMgr.GetTowerUserInfoByUserId(qwUserID);
                    if(pAtkPlayer)
                    {
                         //pDefPlayer->dwGuardFloorID = 0;
                         UINT32 dwSendServerID = dwServerID;
                          CUserPtr pUser = CUserMgr::GetUserByUserID(qwDefRoleID);
                          if(pUser)
                          {
                              dwSendServerID = pUser->GetGameSvrID();
                          }

                          NDemonTower::SDemonToweAttackedInfo oAttedInfo;
                          oAttedInfo.qwAtkRoleID=pAtkPlayer->qwRoleID;
                          oAttedInfo.strRoleName = pAtkPlayer->strRoleName;
                          oAttedInfo.byLevel = pAtkPlayer->byLevel;
                          oAttedInfo.dwLayerID = dwFloorID;

                        g_Game2CenterDemonTowerS.SendSvr_Attacked(&dwSendServerID,1,qwDefRoleID,oAttedInfo);

                    }
                    
              
                }
                else
                {
                   

                }

                
                SDemonTowerFloorInfo* pDemonTowerFloorInfo = g_DemonTowerMgr.GetFloorInfo(dwFloorID);
                if(pDemonTowerFloorInfo && dwPos < MAX_POSITON )
   
                {
                    pDemonTowerFloorInfo->arGuardInfo[dwPos].dwLastFightCD = 0;
                }
            });

   
    pAtkPlayer->dwGuardNextAttackTime = time(NULL) + SParamConfig::wDemonTowerAtkPlayerCD;

    pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_DemonTowerAtkCDNotify(pAtkPlayer->dwGuardNextAttackTime));
    g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pAtkPlayer);

    {
        TVecINT32 vecParam;
        vecParam.push_back(1);
        pUser->OnEvent(eEventType_DemonTowerRob,vecParam);
    }

       return 0;

}
//镇守位改变
UINT32 CDemonTowerMgr::OnChangePos(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos)
{
    
    if(_bOpenLog)
    {
       LOG_INF<<"CDemonTowerMgr::OnChangePos  qwUserID:"<<qwUserID<<" dwFloorID:"<<dwFloorID<<" dwPos:"<<dwPos;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        LOG_DBG<<"eDemonTower_Error";
        return eDemonTower_Error;
    }

  
    DemonTowerUserPtr pAtkPlayer= GetTowerUserInfoByUserId(qwUserID);
    if(!pAtkPlayer)
    {
       pUser->SendSysMsg(eMsgDemonTowerNotInTower);
       LOG_DBG<<"eDemonTower_Error";
       return eDemonTower_NotInTower;
    }
   
    SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(dwFloorID);
    if(!pDemonTowerFloorInfo)
   
    {
        pUser->SendSysMsg(eMsgDemonTowerErrorFloor);
        LOG_DBG<<"eDemonTower_Invalid_FloorID";
        return eDemonTower_Invalid_FloorID;
    }
    
    SDemonTowerCFGExPtr pDemonTowerCFGExPtr = GetDemonTowerCFG(dwFloorID);    
    if(!pDemonTowerCFGExPtr)
    {
        pUser->SendSysMsg(eMsgDemonTowerErrorCFG);
        LOG_DBG<<"eDemonTower_Invalid_CFG dwFloorID "<<dwFloorID;
        return eDemonTower_Invalid_CFG;
    }
   
     //开始镇守
     //处理战败玩家
     UINT64 qwDefUserID = pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID;
     DemonTowerUserPtr pDemonTowerUser= GetTowerUserInfoByUserId(qwDefUserID);
     if(pDemonTowerUser)
     {
            UINT32 dwTimeSpan = pDemonTowerUser->dwGuardStartTime < time(NULL)?time(NULL)-pDemonTowerUser->dwGuardStartTime:0;

            float fRateFail = SParamConfig::wDemonTowerFailPrizeRate/MAX_RATE;
            //计算战败奖励
            CalGuildPrize(pDemonTowerUser,pDemonTowerUser->vecFailSoulPrize,fRateFail);

            CUserPtr pDefUser = CUserMgr::GetUserByUserID(qwDefUserID);
            //notify
            bool bOffline = true;
            if(pDefUser&& pDefUser->IsOnline())
            {
                g_DemonTowerSvrS.SendClt_DemonTowerBeAttackNotify(&pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID,1,
                    dwFloorID,dwPos,qwUserID,pAtkPlayer->strRoleName,pDemonTowerUser->vecFailSoulPrize);
                TakeGuardFailPrize(qwDefUserID);
                bOffline = false;
                
            }
            else
            {
                TVecINT64 vecParam;
                TVecString vecString;
 
                UINT32 dwServerID = pUser->GetGameSvrID();  
                vecString.push_back(pAtkPlayer->strRoleName);
                g_Game2CenterCommS.SendSvr_BubbleNotify(&dwServerID, 1, qwDefUserID, eOpAdd, 9, vecParam, vecString);
            }
           
            TVecMoneyInfo vecWinMoneyInfo;
            //抢夺者获得1份1奖励
            if(dwTimeSpan > SParamConfig::wDemonTowerWinPrizeMinTime)
            {
                float fRateWin = SParamConfig::wDemonTowerWinPrizeRate/MAX_RATE;
                CalGuildPrize(pDemonTowerUser,vecWinMoneyInfo,fRateWin);
                TVecUserItem vecUserItem;
                for(size_t i = 0; i <  vecWinMoneyInfo.size(); ++i) 
                {
                    SUserItem oUserItem;
                    oUserItem.dwTypeID = vecWinMoneyInfo[i].dwMoneyType;
                    oUserItem.dwCount  = vecWinMoneyInfo[i].dwMoneyValue;
                    vecUserItem.push_back(oUserItem);
                }
                UINT32 dwServerID = pUser->GetGameSvrID(); 
                g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemFrom_DemonTower,vecUserItem,[qwUserID](UINT8 byRet_, UINT8 byError)
                                            {
                                                
                                                if(byRet_ || byError)
                                                {   
                                                    LOG_CRI<<"additem fail";
                                                    return;
                                                }   
                                                 
                                            });
             }

              //胜利1次
               {
                    TVecINT32 vecParam;
                    for(size_t i=0;i<vecWinMoneyInfo.size(); i++)
                    {
                        vecParam.push_back(vecWinMoneyInfo[i].dwMoneyType);
                        vecParam.push_back(vecWinMoneyInfo[i].dwMoneyValue);
                    }
                    UINT32 dwServerID = pUser->GetGameSvrID();
                    g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID,1,qwUserID,eEventType_DemonTowerRobSuccess,vecParam,"",true);
               }

            //失败玩家数据清理
            OnGuardEnd(pDemonTowerUser);
            PlayerInfoNotify(pDemonTowerUser,true);
            if(bOffline)
            {
                //保存失败消息
                pDemonTowerUser->dwGuardPos = eDemonTower_Prize_Fail;
            }
            g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgDemonTowerRober, 
                   BuildStrVec(pUser->GetColor(),pUser->GetRoleName(),pDemonTowerUser->byColor,pDemonTowerUser->strRoleName,dwFloorID));

     }
    
     //开始镇守
     pDemonTowerFloorInfo->arGuardInfo[dwPos].qwUserID = qwUserID;
     pDemonTowerFloorInfo->arGuardInfo[dwPos].qwRoleID = pAtkPlayer->qwRoleID;   
     pDemonTowerFloorInfo->arGuardInfo[dwPos].dwGuardPos = dwPos;
 
     pAtkPlayer->dwGuardFloorID = dwFloorID;
     pAtkPlayer->dwGuardPos = dwPos;

     OnGuardInit(pAtkPlayer); //save db
     FullPlayerInfo(pAtkPlayer,pDemonTowerFloorInfo->arGuardInfo[dwPos].oDemonFloorPlayer);
     //g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pAtkPlayer);

     //下面两协议不要颠倒（客户端需求）
     pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_GuardSucessNotify(dwFloorID,dwPos));
     GuardInfoChangeNotify(dwFloorID,dwPos,qwUserID,pDemonTowerFloorInfo->arGuardInfo[dwPos]);
     PlayerInfoNotify(pAtkPlayer,false);

     return 0;
}

//领取每日过关奖励
UINT32 CDemonTowerMgr::TakeSealPrize(UINT64 qwUserID)
{
    /*
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
      return eDemonTower_Invalid_UserID;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
 
    g_Game2CenterCommS.SendSvr_GetUserUINTProp(&dwServerID,1,qwUserID,ePropPrizeDemonFloorID,[qwUserID](UINT8 byRet_, //0为成功，1为失败，2为超时
		                                                                                       UINT32 dwValue, //(返回值)属性值
		                                                                                       UINT8 byError //(返回值)0 成功, 其他错误
                                                                                                )
            {
                if(!byRet_ || !byError)
                {
                    return;

                }



                UINT32 dwFloorID = dwValue;
                if(!dwFloorID)
                {
                    //return eDemonTower_Empty_Prize;
                    return;
                }
                
                SDemonTowerCFGExPtr pDemonTowerCFGEx = g_DemonTowerMgr.GetDemonTowerCFG(dwFloorID);
            
                if(pDemonTowerCFGEx)
                {
                    //return eDemonTower_Invalid_CFG;
                    return;
                }

                UINT32 dwMoneyValue = pDemonTowerCFGEx->_DayPrize;
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                if(!pUser)
                {
                  return eDemonTower_Invalid_UserID;
                }
                UINT32 dwServerID = pUser->GetGameSvrID();
       

                g_Game2CenterCommS.SendSvr_SetUserUINTProp(&dwServerID,1,qwUserID,ePropPrizeDemonFloorID,0,[qwUserID,dwMoneyValue](UINT8 byRet_, UINT8 byError)
                        {
                            if(!byRet_ || !byError)
                            {
                                return;
                            }

                            TVecUserItem vecUserItem;
                            SUserItem oUserItem;
                            oUserItem.dwTypeID = EMONEY_DEMONSOUL;
                            oUserItem.dwCount = dwMoneyValue;
                            CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                            if(!pUser)
                            {
                                return eDemonTower_Invalid_UserID;
                            }
                            UINT32 dwServerID = pUser->GetGameSvrID();
                            g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemFrom_DemonTower,vecUserItem,[](UINT8 byRet_, UINT8 byError)
                                {
                                    
                                    if(!byRet_ || !byError)
                                    {   
                                        return;
                                    }   
                                });
                        
                        });
            });
*/
    return -1;
}
    
//领取过每日镇守奖励
UINT32  CDemonTowerMgr::TakePassDayPrize(UINT64 qwUserID)
{
    
    if(_bOpenLog)
    {
        LOG_INF<<"CDemonTowerMgr::TakePassDayPrize  qwUserID:"<<qwUserID;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
        LOG_DBG<<"eDemonTower_Invalid_UserID";
        return eDemonTower_Invalid_UserID;
    }

    UINT32 dwServerID = pUser->GetGameSvrID();
 
    DemonTowerUserPtr pDemonTowerUser= GetTowerUserInfoByUserId(qwUserID);
    if(!pDemonTowerUser)
    {
        pUser->SendSysMsg(eMsgDemonTowerEmptyPrize);
        LOG_DBG<<"eDemonTower_Empty_Prize";
        return eDemonTower_Empty_Prize;
    }
    
    if(pDemonTowerUser->vecDaySoulPrize.empty())
    {
        pUser->SendSysMsg(eMsgDemonTowerEmptyPrize);
        LOG_DBG<<"eDemonTower_Empty_Prize";
        return eDemonTower_Empty_Prize;
    }




   
    TVecUserItem vecUserItem;

    for(size_t i = 0; i < pDemonTowerUser->vecDaySoulPrize.size(); ++i)
    {
        SUserItem oUserItem;
        oUserItem.dwTypeID = pDemonTowerUser->vecDaySoulPrize[i].dwMoneyType;
        oUserItem.dwCount = pDemonTowerUser->vecDaySoulPrize[i].dwMoneyValue;
        vecUserItem.push_back(oUserItem);

    }

    pDemonTowerUser->vecDaySoulPrize.clear();
    //g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);
    PlayerInfoNotify(pDemonTowerUser,true,true);

    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemFrom_DemonTower,vecUserItem,[qwUserID](UINT8 byRet_, UINT8 byError)
                                {
                                    
                                    if(byRet_ || byError)
                                    {   
                                        return;
                                    }   
                                     
                                });
    return 0;
}
    


//领取镇守奖励
UINT32  CDemonTowerMgr::TakeGuardFailPrize(UINT64 qwUserID)
{

    if(_bOpenLog)
    {
       LOG_INF<<"CDemonTowerMgr::TakeGuardFailPrize  qwUserID:"<<qwUserID;
    }
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
        LOG_DBG<<"eDemonTower_Invalid_UserID";
        return eDemonTower_Invalid_UserID;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    
    DemonTowerUserPtr pDemonTowerUser= GetTowerUserInfoByUserId(qwUserID);
    if(!pDemonTowerUser)
    {
        pUser->SendSysMsg(eMsgDemonTowerEmptyPrize);
        LOG_DBG<<"eDemonTower_Empty_Prize";
        return eDemonTower_Empty_Prize;
    }
    
    if(pDemonTowerUser->vecFailSoulPrize.empty())
    {
        pUser->SendSysMsg(eMsgDemonTowerEmptyPrize);
        LOG_DBG<<"eDemonTower_Empty_Prize";
        return eDemonTower_Empty_Prize;
    }

     TVecUserItem vecUserItem;
                           
    for(size_t i = 0; i < pDemonTowerUser->vecFailSoulPrize.size(); ++i)
    {
        SUserItem oUserItem;
        oUserItem.dwTypeID = pDemonTowerUser->vecFailSoulPrize[i].dwMoneyType;
        oUserItem.dwCount = pDemonTowerUser->vecFailSoulPrize[i].dwMoneyValue;
        vecUserItem.push_back(oUserItem);
    }
    pDemonTowerUser->vecFailSoulPrize.clear();

    //g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);
    PlayerInfoNotify(pDemonTowerUser,true,true);

    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemFrom_DemonTower,vecUserItem,[qwUserID](UINT8 byRet_, UINT8 byError)
                                {
                                    
                                    if(byRet_ || byError)
                                    {   
                                        return;
                                    }   
                                     
                                    //DemonTowerUserPtr pDemonTowerUser= GetTowerUserInfoByRoleiId(qwUserID);
                                    //if(pDemonTowerUser)
                                     {
                                       // pDemonTowerUser->vecFailSoulPrize.clear();
                                        
                                     }

                                });
    return 0;
}

//会清理掉原先的奖励数据
void CDemonTowerMgr::CalGuildPrize(DemonTowerUserPtr& pDemonTowerUser, TVecMoneyInfo& VecMoneyInfo,float fRate)
{
    if(0 == pDemonTowerUser->dwGuardStartTime)
    {
        return;
    }

    //warning
    VecMoneyInfo.clear();
    
    if(pDemonTowerUser)
    {
       for(size_t i = 0; i <  pDemonTowerUser->vecGatherSoulPrize.size(); ++i)
        {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType  = pDemonTowerUser->vecGatherSoulPrize[i].dwMoneyType;
               oMoneyInfo.dwMoneyValue = pDemonTowerUser->vecGatherSoulPrize[i].dwMoneyValue*fRate;
               VecMoneyInfo.push_back(oMoneyInfo);
        }
   
    }
}
//获取镇守榜
void CDemonTowerMgr::GetTopList(UINT16 wPage,UINT16 wPageItemCount,SDemonFloorPage& oDemonFloorPage)
{
    LOG_INF<<"CDemonTowerMgr::GetTopList:"<<wPage;
    oDemonFloorPage.wMaxPage = MAX_FLOORID/wPageItemCount;

    UINT16 wCurPage = wPage;
    if(wCurPage > oDemonFloorPage.wMaxPage)
    {
        wCurPage = oDemonFloorPage.wMaxPage;
    }

    if(0 == wPage)
    {
        //玩家打到的最高层
        UINT16 wTopFloorID = GetTopGuardFloorID();
        if(wTopFloorID == MAX_FLOORID-1)
        {
            wCurPage = 1;
        }
        else
        {
            wCurPage = (MAX_FLOORID-1-wTopFloorID-1)/wPageItemCount + 1;
        }
    }
  
    UINT16 wMinNO;
    UINT16 wMaxNO;
    //if(wPage)
    {

        oDemonFloorPage.wCurPage = wCurPage;
        wMaxNO = (MAX_FLOORID-1) - ((wCurPage-1)*wPageItemCount+1) + 1;
        wMinNO = (MAX_FLOORID-1) - (wCurPage*wPageItemCount) + 1;
        for(UINT16 i = wMaxNO; i >= wMinNO; --i)
        {
            SDemonFloorPlayer oDemonFloorPlayer;
            //填充层（客户端用）
            oDemonFloorPlayer.dwFloorID = i;
            SDemonTowerFloorInfo& rDemonTowerFloorInfo = _arFloorInfo[i];
            GuardInfo& rGuardInfo = rDemonTowerFloorInfo.arGuardInfo[1];
            if(rGuardInfo.qwUserID)
            {

                DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(rGuardInfo.qwUserID);
                if(pDemonTowerUser)
                {
                    FullPlayerInfo(pDemonTowerUser,oDemonFloorPlayer);
                }

            }
            oDemonFloorPage.vecDemonFloorPlayer.push_back(oDemonFloorPlayer);
        }
    }
}


void  CDemonTowerMgr::GuardInfoChangeNotify(UINT32 dwFloorID,UINT32 dwPos,UINT64 qwUserID,GuardInfo& oGuardInfo)
{
    for(auto itr = _mapDemonTowerUserPtr.begin(); itr != _mapDemonTowerUserPtr.end(); itr++ )
    {
        DemonTowerUserPtr pDemonTowerUser = itr->second;
        if(pDemonTowerUser &&  pDemonTowerUser->dwFloorID)
        {
            if(pDemonTowerUser->qwUserID)
            {

                 CUserPtr pUser = CUserMgr::GetUserByUserID(pDemonTowerUser->qwUserID);
                 if(pUser)                                            
                 {                                                     
                     LOG_DBG<<"GuardInfoChangeNotify userId:"<<pUser->GetUserID()<<" dwFloorID:"<<dwFloorID<<dwPos<<" dwPos"<<qwUserID;
                     pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_GuardInfoChangeNotify(dwFloorID,dwPos,qwUserID,oGuardInfo));
                 }
            }
        }

    }


}

void  CDemonTowerMgr::GuardInfoNotify(const SDemonTowerFloorInfo* pDemonTowerFloorInfo)
{
    if(NULL == pDemonTowerFloorInfo)
    {
        return;
    }

    if(0 == pDemonTowerFloorInfo->dwFloorID)
    {
        return;
    }

    TVecGuardInfo vecGuardInfo;
    for(UINT32 i = 1; (i < MAX_POSITON) && (i <= pDemonTowerFloorInfo->dwMaxPos); i++)
    {
        vecGuardInfo.push_back(pDemonTowerFloorInfo->arGuardInfo[i]);
    }

    for(auto itr = _mapDemonTowerUserPtr.begin(); itr != _mapDemonTowerUserPtr.end(); itr++ )
    {
        DemonTowerUserPtr pDemonTowerUser = itr->second;
        if(pDemonTowerUser &&  pDemonTowerUser->dwFloorID)
        {
            if(pDemonTowerUser->qwUserID)
            {

                 CUserPtr pUser = CUserMgr::GetUserByUserID(pDemonTowerUser->qwUserID);
                 if(pUser)                                            
                 {                                                     
                     pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_GuardInfoNotify(pDemonTowerFloorInfo->dwFloorID,vecGuardInfo));
                 }
            }
        }

    }

}

void  CDemonTowerMgr::SendPkgToFloor(UINT32 dwFloorID,const string& strPkg)
{
    
    for(auto itr = _mapDemonTowerUserPtr.begin(); itr != _mapDemonTowerUserPtr.end(); itr++ )
    {
        DemonTowerUserPtr pDemonTowerUser = itr->second;
        if(pDemonTowerUser &&  pDemonTowerUser->dwFloorID && (pDemonTowerUser->dwFloorID ==dwFloorID))
        {
            if(pDemonTowerUser->qwUserID)
            {

                 CUserPtr pUser = CUserMgr::GetUserByUserID(pDemonTowerUser->qwUserID);
                 if(pUser)                                            
                 {                                                     
                     pUser->SendPkg(strPkg);
                 }
            }
        }

    }


}

//群发层消息
void  CDemonTowerMgr::SendPkg(const string& strPkg)
{
    for(auto itr = _mapDemonTowerUserPtr.begin(); itr != _mapDemonTowerUserPtr.end(); itr++ )
    {
        DemonTowerUserPtr pDemonTowerUser = itr->second;
        if(pDemonTowerUser &&  pDemonTowerUser->dwFloorID )
        {
            if(pDemonTowerUser->qwUserID)
            {
                 CUserPtr pUser = CUserMgr::GetUserByUserID(pDemonTowerUser->qwUserID);
                 if(pUser)                                            
                 {                                                     
                     pUser->SendPkg(strPkg);
                 }
            }
        }

    }

}


void  CDemonTowerMgr::PlayerInfoNotify(DemonTowerUserPtr pDemonTowerUser,bool bToSelfOnly,bool bSaveToDB /*= true*/)
{
    if(NULL == pDemonTowerUser)
    {
        return;
    }

    if(bSaveToDB)
    {
        g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);
    }

    //LOG_INF<<"PlayerInfoNotify:UID:"<<pDemonTowerUser->qwUserID<<"dwGuardFloor"<<pDemonTowerUser->dwGuardFloorID;

    if(bToSelfOnly)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(pDemonTowerUser->qwUserID);
        if(pUser)
        {
            pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_DemonTowerPlayerNotify(*pDemonTowerUser));
        }
        return;
    }

    UINT32 dwFloorID = pDemonTowerUser->dwFloorID;
    if(0 == dwFloorID) //仅通知玩家本人即可
    {
        return;
    }

    SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(dwFloorID);
    if(NULL == pDemonTowerFloorInfo)
    {
        LOG_CRI<<"Error dwFloorID: "<<dwFloorID<<"uid:"<<pDemonTowerUser->qwUserID;
        return;
    }

    //SendPkg(g_DemonTowerSvrS.BuildPkg_DemonTowerPlayerNotify(*pDemonTowerUser));
    SendPkgToFloor(dwFloorID,g_DemonTowerSvrS.BuildPkg_DemonTowerPlayerNotify(*pDemonTowerUser));


}

void  CDemonTowerMgr::GetGuardInfo(UINT32 dwFloorID,TVecGuardInfo& vecGuardInfo)
{
    SDemonTowerFloorInfo* pDemonTowerFloorInfo = GetFloorInfo(dwFloorID);
    if(NULL == pDemonTowerFloorInfo)
    {
        LOG_CRI<<"Error dwFloorID: "<<dwFloorID;
        return;
    }

    if(_bOpenLog)
    {
        LOG_INF<<"GetGuardInfo dwFloorID:"<<dwFloorID;
    }

    for(UINT32 i = 1; (i < MAX_POSITON) && (i <= pDemonTowerFloorInfo->dwMaxPos); i++)
    {
        vecGuardInfo.push_back(pDemonTowerFloorInfo->arGuardInfo[i]);
        if(_bOpenLog)
        {
            LOG_INF<<"FloorInfo GuardPos: "<<i<<" qwUserID:"<<pDemonTowerFloorInfo->arGuardInfo[i].qwUserID;
        }

    }

}

//恢复
void CDemonTowerMgr::Restore(UINT64 qwUserID,UINT32 dwItemCount)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
        LOG_DBG<<"eDemonTower_Invalid_UserID"<<qwUserID;
        return;
    }

    UINT32 dwServerID = pUser->GetGameSvrID();

    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUser)
    {
        LOG_DBG<<"Restore NULL == pDemonTowerUser userid:"<<qwUserID;
        pUser->SendSysMsg(eMsgDemonTowerUserIDError); 
        return;
    }

    if(pDemonTowerUser->dwBuyTime>time(NULL))
    {
        LOG_DBG<<"BuycdTime";
        pUser->SendSysMsg(eMsgDemonTowerOpCD);
        return;
    }

    if(0 == dwItemCount)
    {
        LOG_DBG<<"0 == dwItemCount";
        return;
    }


    if(pDemonTowerUser->dwGuardReduceRate >= SParamConfig::wDemonTowerAddHealthMax)
    {
        LOG_DBG<<"is full Rate";
        pUser->SendSysMsg(eMsgDemonTowerMaxReduceReate);
        return;
    }

    pDemonTowerUser->dwBuyTime = time(NULL) + 10;

    UINT32 dwCount = pDemonTowerUser->dwGuardReduceRate>dwItemCount?dwItemCount:pDemonTowerUser->dwGuardReduceRate;
    UINT32 dwItemID = SParamConfig::wDemonTowerRestoreItemID;

    TVecUserItem vecUserItem;
    SUserItem oItem(dwItemID,dwCount);
    vecUserItem.push_back(oItem);

    g_Game2CenterCommS.SendSvr_UserSubItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemTo_DemonTower,vecUserItem,[qwUserID,dwCount](UINT8 byRet_, UINT8 byError)
                                {
                                    
                                    if(byRet_ || byError)
                                    {   
                                        //LOG_CRI<<"Sub item Error!!";
                                        CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                                        if(pUser)
                                        {
                                            pUser->SendSysMsg(eMsgDemonTowerHealthItemError);
                                        }
                                        g_DemonTowerMgr.OnResetBuyTime(qwUserID);
                                        return;
                                    }   
                                     
                                    g_DemonTowerMgr.OnRestore(qwUserID,dwCount);
                                });
}

void CDemonTowerMgr::OnResetBuyTime(UINT64 qwUserID)
{
    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUser)
    {
        LOG_DBG<<"Restore NULL == pDemonTowerUser userid:"<<qwUserID;
        return;
    }

    pDemonTowerUser->dwBuyTime = 0;

}

void CDemonTowerMgr::OnRestore(UINT64 qwUserID,UINT32 dwItemCount)
{
    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUser)
    {
        LOG_DBG<<"Restore NULL == pDemonTowerUser userid:"<<qwUserID;
        return;
    }

    pDemonTowerUser->dwGuardReduceRate += dwItemCount*SParamConfig::wDemonTowerAdddHealth;
    if(pDemonTowerUser->dwGuardReduceRate >= SParamConfig::wDemonTowerAddHealthMax)
    {
        pDemonTowerUser->dwGuardReduceRate = SParamConfig::wDemonTowerAddHealthMax;
    }

    pDemonTowerUser->dwBuyTime = 0;

    PlayerInfoNotify(pDemonTowerUser,false);
    //CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    //if(pUser)
        //pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_DemonTowerPlayerNotify(*pDemonTowerUser));
    

}

UINT32 GetTimePoint(UINT8 byHour,UINT8 byMinute=0,UINT8 bySec=0)
{
    time_t tNow = time(NULL);
    struct tm *pTm = localtime(&tNow);
	tm oTm = *pTm;
	oTm.tm_hour = byHour;
	oTm.tm_min = byMinute;
    oTm.tm_sec = bySec;

    return mktime(&oTm);
}


//增加聚魂速度
void CDemonTowerMgr::AddSpeed(UINT64 qwUserID,UINT32 dwItemCount)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
        LOG_DBG<<"eDemonTower_Invalid_UserID"<<qwUserID;
        return;
    }

    UINT32 dwServerID = pUser->GetGameSvrID();

    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUser)
    {
        LOG_DBG<<"Restore NULL == pDemonTowerUser useroid:"<<qwUserID;
        pUser->SendSysMsg(eMsgDemonTowerUserIDError);
        return;
    }

    if(pDemonTowerUser->dwBuyTime>time(NULL))
    {
        LOG_DBG<<"BuycdTime";
        pUser->SendSysMsg(eMsgDemonTowerOpCD);
        return;
    }

    if(0 == dwItemCount)
    {
        LOG_DBG<<"0 == dwItemCount";
        return;
    }


    //UINT32 dwLastPoint = GetTimePoint(18);
    //if(time(NULL)>dwLastPoint)
    //{
      //  dwLastPoint += 24*3600;
    //}

    UINT32 dwPerTime = SParamConfig::dwDemonTowerAddSpeedTime; //6小时


    //UINT32 dwTotalLastTime = dwLastPoint-time(NULL);
    //加速不计算时间一直起作用
    
    UINT32 dwAddTime = dwItemCount*dwPerTime;
    UINT32 dwCount = dwItemCount;
    UINT32 dwItemID = SParamConfig::wDemonTowerAddSpeedItemID;

    UINT32 dwLastTime = pDemonTowerUser->dwGuardGatherSpeedEndTimer + SParamConfig::dwDemonTowerAddSpeedTime;
    if(dwLastTime > SParamConfig::dwDemonTowerAddSpeedTimeMax)
    {
        pUser->SendSysMsg(eMsgDemonTowerMaxSpeedTime);
        return;
    }

    pDemonTowerUser->dwBuyTime = time(NULL) + 10;

    TVecUserItem vecUserItem;
    SUserItem oItem(dwItemID,dwCount);
    vecUserItem.push_back(oItem);

    g_Game2CenterCommS.SendSvr_UserSubItem(&dwServerID,1,qwUserID,NLogDataDefine::ItemTo_DemonTower,vecUserItem,[qwUserID,dwCount,dwAddTime](UINT8 byRet_, UINT8 byError)
                                {
                                    
                                    if(byRet_ || byError)
                                    {   
                                        //LOG_CRI<<"Sub item Error!!";
                                        CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                                        if(pUser)                                            
                                        {                                                    
                                            pUser->SendSysMsg(eMsgDemonTowerSpeedItemError);
                                        }                                                    
                                        g_DemonTowerMgr.OnResetBuyTime(qwUserID);
                                        return;
                                    }   
                                     
                                    g_DemonTowerMgr.OnAddSpeed(qwUserID,dwCount,dwAddTime);
                                });


}

void CDemonTowerMgr::OnAddSpeed(UINT64 qwUserID,UINT32 dwItemCount,UINT32 dwAddTime)
{
    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUser)
    {
        LOG_DBG<<"Restore NULL == pDemonTowerUser userid:"<<qwUserID;
        return;
    }

    
    pDemonTowerUser->dwGuardGatherSpeedEndTimer += dwAddTime;
    
    pDemonTowerUser->dwGuardGatherSpeed = SParamConfig::wDemonTowerSpeedRate;

    pDemonTowerUser->dwBuyTime = 0;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser)
        pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_DemonTowerPlayerNotify(*pDemonTowerUser));

    PlayerInfoNotify(pDemonTowerUser,true);

}

UINT16 CDemonTowerMgr::GetTopGuardFloorID()
{
    UINT16 wFloorID = 1;
    for(UINT16 i = MAX_FLOORID-1; i > 0; --i)
    {
        SDemonTowerFloorInfo& rDemonTowerFloorInfo = _arFloorInfo[i];
        GuardInfo& rGuardInfo = rDemonTowerFloorInfo.arGuardInfo[1];
        if(rGuardInfo.qwUserID)
        {
            wFloorID = i;
            break;
        }
    }

    return wFloorID;
}
SDemonTowerCFGExPtr CDemonTowerMgr::GetDemonTowerCFG(UINT32 dwFloorID)
{
    UINT32 dwVecFloorID = dwFloorID-1;
    if(_vecSDemonTowerCFGExPtr.size() > dwVecFloorID)
    {
        return _vecSDemonTowerCFGExPtr[dwVecFloorID];
    }

    return NULL;
}

SDemonTowerFloorInfo* CDemonTowerMgr::GetFloorInfo(UINT32 dwFloorID)
{
    if(dwFloorID < 1 || dwFloorID >= MAX_FLOORID )
    {
        return NULL;
    }

    return &_arFloorInfo[dwFloorID]; 

}

DemonTowerUserPtr CDemonTowerMgr::GetTowerUserInfoByUserId(UINT64 qwUserID)
{
    auto itr = _mapDemonTowerUserPtr.find(qwUserID);
    if(itr != _mapDemonTowerUserPtr.end())
    {
        return itr->second;
    }

    return NULL;

}

UINT32 CDemonTowerMgr::GetPlayerGuardLayerID(UINT64 qwUserID)
{
    DemonTowerUserPtr pUser = GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pUser)
    {
        return 0;
    }

    return pUser->dwGuardFloorID;
}

//减弱属性
void CDemonTowerMgr::OnReduceAttr(DemonTowerUserPtr pDemonTowerUser,GuardInfo& rGuardInfo)
{
    
    if(NULL == pDemonTowerUser)
    {
        return;
    }

    //error
    if(pDemonTowerUser->dwGuardNextReduceRateTime < pDemonTowerUser->dwGuardStartTime)
    {
        pDemonTowerUser->dwGuardNextReduceRateTime = pDemonTowerUser->dwGuardStartTime;
    }

    //dbchange
    if(0 == pDemonTowerUser->dwGuardNextReduceRateTime)
    {
        pDemonTowerUser->dwGuardNextReduceRateTime = time(NULL) + SParamConfig::wDemonTowerHealthCD;
    }

    if(0 == SParamConfig::wDemonTowerPrizeCD)
    {
        LOG_CRI<<"0 == SParamConfig::wDemonTowerPrizeCD";
        return;
    }


    while( pDemonTowerUser->dwGuardNextReduceRateTime<time(NULL) && (pDemonTowerUser->dwGuardNextReduceRateTime <=  pDemonTowerUser->dwGuardEndTime))
    {
      
        pDemonTowerUser->dwGuardNextReduceRateTime +=  SParamConfig::wDemonTowerHealthCD;

        if(pDemonTowerUser->dwGuardReduceRate <= 1)
        {
            continue;
        }
       
        pDemonTowerUser->dwGuardReduceRate -= 1;


        if(pDemonTowerUser->dwGuardReduceRate < 1)
        {
            pDemonTowerUser->dwGuardReduceRate = 1;
            break;
        }
        
        if(_bOpenLog)
        {
            LOG_INF<<"OnReduceAttr UID:"<<pDemonTowerUser->qwUserID<<" dwGuardReduceRate:"<<pDemonTowerUser->dwGuardReduceRate;
        }

    }

    rGuardInfo.oDemonFloorPlayer.dwGuardReduceRate = pDemonTowerUser->dwGuardReduceRate;
    
    PlayerInfoNotify(pDemonTowerUser,false);

    return;
    

}

//产生奖励
UINT32 CDemonTowerMgr::OnGainPrize(DemonTowerUserPtr pDemonTowerUser,GuardInfo& rGuardInfo)
{
    
    if(NULL == pDemonTowerUser)
    {
        return eGainPrize_Error;
    }

    //发奖结束
    if(pDemonTowerUser->dwGuardNextPrizeTime>pDemonTowerUser->dwGuardEndTime)
    {
        return eGainPrize_RESET;
    }

    if(0 == SParamConfig::wDemonTowerPrizeCD)
    {
        SParamConfig::wDemonTowerPrizeCD = 600;
        LOG_CRI<<"0 == SParamConfig::wDemonTowerPrizeCD";
    }
        //add prize
        
    SDemonTowerCFGExPtr pDemonTowerCFGExPtr = GetDemonTowerCFG(pDemonTowerUser->dwGuardFloorID); 
    if(NULL == pDemonTowerCFGExPtr)
    {
        LOG_CRI<<"pDemonTowerCFGExPtr empty dwFloorID:"<<pDemonTowerUser->dwFloorID;
        return eGainPrize_Error;
    }

    if(0 == pDemonTowerUser->dwGuardNextPrizeTime)
    {
        pDemonTowerUser->dwGuardNextPrizeTime = time(NULL) + SParamConfig::wDemonTowerPrizeCD;
    }

    UINT32 dwWhileCnt = 0;

    while(pDemonTowerUser->dwGuardNextPrizeTime <= time(NULL)&& pDemonTowerUser->dwGuardNextPrizeTime<pDemonTowerUser->dwGuardEndTime)
    {
        dwWhileCnt++;
        if(dwWhileCnt > 144)
        {
            PlayerInfoNotify(pDemonTowerUser,true);
            return eGainPrize_RESET;
        }

        float fRate = 1.0;
        if(pDemonTowerUser->dwGuardGatherSpeedEndTimer)
        {
            fRate += SParamConfig::wDemonTowerSpeedRate/10000.0;
        }

        

        UINT32 dwCount = 1;
        
        for(size_t i = 0; i <  pDemonTowerCFGExPtr->vecPrize.size(); ++i)
        {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType  = pDemonTowerCFGExPtr->vecPrize[i].dwMoneyType;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFGExPtr->vecPrize[i].dwMoneyValue*dwCount*fRate;
               //VecMoneyInfo.push_back(oMoneyInfo);
               AddVecMoney(pDemonTowerUser->vecGatherSoulPrize,oMoneyInfo);
               if(_bOpenLog)
               {
                   LOG_INF<<"add one prize uid:"<<pDemonTowerUser->qwUserID<<" "<<oMoneyInfo.dwMoneyType<<"|"<<oMoneyInfo.dwMoneyValue<<" rate:"<<fRate;
               }
        }

        if(_bOpenLog)
        {
            for(MoneyInfo& rMoneyInfo:pDemonTowerUser->vecGatherSoulPrize)
            {
                LOG_INF<<"Total Prize moneytype:"<<rMoneyInfo.dwMoneyType<<" dwMoneyValue:"<<rMoneyInfo.dwMoneyValue;
            }
        }

        pDemonTowerUser->dwGuardNextPrizeTime += SParamConfig::wDemonTowerPrizeCD;

        //扣加速时间
       if(pDemonTowerUser->dwGuardGatherSpeedEndTimer> SParamConfig::wDemonTowerPrizeCD)
       {
           pDemonTowerUser->dwGuardGatherSpeedEndTimer -= SParamConfig::wDemonTowerPrizeCD;
       }
       else
       {
           pDemonTowerUser->dwGuardGatherSpeedEndTimer = 0;
       }


       if(pDemonTowerUser->dwGuardNextPrizeTime>time(NULL))
       {
            break;
       }


    }

    CalGuildPrize(pDemonTowerUser,rGuardInfo.oDemonFloorPlayer.vecSoulPrize,1.0);

    PlayerInfoNotify(pDemonTowerUser,false);

    return eGainPrize_SUCESS;
}

void CDemonTowerMgr::GMSet()
{
    SParamConfig::wDemonTowerPrizeCD = 60;
    SParamConfig::wDemonTowerAtkPlayerCD = 30;
    SParamConfig::wDemonTowerAtkMonsterCD = 5;
    SParamConfig::dwDemonTowerAddSpeedTime = 60;
}
//初始化
void CDemonTowerMgr::OnGuardInit(DemonTowerUserPtr pDemonTowerUser)
{
    if(NULL == pDemonTowerUser)
    {
        return;
    }

   pDemonTowerUser->dwGuardStartTime = time(NULL);
   //pDemonTowerUser->dwGuardNextAttackTime = time(NULL) + SParam::wDemonTowerAtkPlayerCD;
   pDemonTowerUser->dwGuardNextReduceRateTime = time(NULL) + SParamConfig::wDemonTowerPrizeCD;
   pDemonTowerUser->dwGuardNextPrizeTime = time(NULL) + SParamConfig::wDemonTowerPrizeCD;
   
   if(pDemonTowerUser->dwGuardReduceRate<100)
        pDemonTowerUser->dwGuardReduceRate = 100;

   UINT32 dwEndTime = GetDayTime(19);
   if(dwEndTime <time(NULL))
   {
       dwEndTime += 24*3600;
   }
   pDemonTowerUser->dwGuardEndTime = dwEndTime; 

   g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);

}

void CDemonTowerMgr::OnGuardEnd(DemonTowerUserPtr pDemonTowerUser)
{

    if(NULL == pDemonTowerUser)
    {
        return;
    }
    //镇守成功日志
    {
        
        //
        UINT32 dwTotalTime = 0;
        if(pDemonTowerUser->dwGuardEndTime>time(NULL))
        {
            dwTotalTime  = time(NULL) - pDemonTowerUser->dwGuardStartTime;
        }

        else
        {
            dwTotalTime = pDemonTowerUser->dwGuardEndTime - pDemonTowerUser->dwGuardStartTime; 
        }

        CUserPtr pUser = CUserMgr::GetUserByUserID(pDemonTowerUser->qwUserID);
        TVecINT32 vecParam;
        vecParam.push_back(dwTotalTime);
        for(size_t i=0; i <pDemonTowerUser->vecGatherSoulPrize.size(); i++)
        {
            vecParam.push_back(pDemonTowerUser->vecGatherSoulPrize[i].dwMoneyType);
            vecParam.push_back(pDemonTowerUser->vecGatherSoulPrize[i].dwMoneyValue);
        }

        if(pUser&&pUser->IsOnline())
        {
            pUser->OnEvent(eEventType_DemonTowerDefendSuccess,vecParam);
        }
        else
        {
            CUser::AddOffLineEvent(pDemonTowerUser->qwUserID,eEventType_DemonTowerDefendSuccess,vecParam);
        }

    }

    //save

    pDemonTowerUser->dwFailFloorID = pDemonTowerUser->dwGuardFloorID;
    pDemonTowerUser->dwFailPos     = pDemonTowerUser->dwGuardPos;

    pDemonTowerUser->dwGuardStartTime = 0;
    //pDemonTowerUser->dwGuardNextAttackTime = 0;
    pDemonTowerUser->dwGuardNextReduceRateTime = 0;
    pDemonTowerUser->dwGuardNextPrizeTime = 0;
    pDemonTowerUser->dwGuardEndTime = 0; 
    pDemonTowerUser->dwGuardFloorID   = 0;
    pDemonTowerUser->dwGuardPos       = 0;
    if(pDemonTowerUser->dwGuardReduceRate<100)
        pDemonTowerUser->dwGuardReduceRate = 100;
    pDemonTowerUser->vecGatherSoulPrize.clear();

      
    g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);
}
 

void CDemonTowerMgr::FullPlayerInfo(DemonTowerUserPtr pDemonTowerUser,SDemonFloorPlayer& oDemonFloorPlayer)
{
    oDemonFloorPlayer.dwFloorID = pDemonTowerUser->dwGuardFloorID;
    oDemonFloorPlayer.qwUserID  = pDemonTowerUser->qwUserID;
    oDemonFloorPlayer.strRoleName = pDemonTowerUser->strRoleName;
    oDemonFloorPlayer.bySex       = pDemonTowerUser->bySex;
    oDemonFloorPlayer.byLevel = pDemonTowerUser->byLevel;
    oDemonFloorPlayer.dwPower = pDemonTowerUser->dwPower;
    oDemonFloorPlayer.dwGuardStartTime = pDemonTowerUser->dwGuardStartTime;
    oDemonFloorPlayer.dwGuardReduceRate = pDemonTowerUser->dwGuardReduceRate;
    CalGuildPrize(pDemonTowerUser,oDemonFloorPlayer.vecSoulPrize,1.0);
}

UINT8 CDemonTowerMgr::GetPlayerInfo(UINT64 qwUserID,SDemonFloorPlayer& oDemonFloorPlayer)
{
    DemonTowerUserPtr pDemonTowerUser=GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUser)
    {
        return 1;
    }
    FullPlayerInfo(pDemonTowerUser,oDemonFloorPlayer);
    return 0;
}

UINT8 CDemonTowerMgr::OnClearFightCd(UINT64 qwUserID,shared_func<CDemonTowerGSSvr::SClearFightCdAck>& fnAck)
{
    DemonTowerUserPtr pDemonTowerUser=GetTowerUserInfoByUserId(qwUserID);
    if(NULL == pDemonTowerUser)
    {
        return eDemonTower_NotInTower;
    }
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(!pUser)
    {
         return eDemonTower_Invalid_UserID;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();

    //不需要购买cd
    if( pDemonTowerUser->dwGuardNextAttackTime < time(NULL))
    {
        return 0;
    }
    
    if(pDemonTowerUser->dwBuyTime>time(NULL))
    {
        LOG_DBG<<"BuycdTime";
        pUser->SendSysMsg(eMsgDemonTowerOpCD);
        return eDemonTower_Error;
    }

    pDemonTowerUser->dwBuyTime = time(NULL) + 2;

    //TVecUserItem vecUserItem;
    //SUserItem oItem(EMONEY_GOLD,SParamConfig::wDemonTowerCleanCD2);
    //vecUserItem.push_back(oItem);

    g_Game2CenterCommS.SendSvr_SubGoldOrCoupon(&dwServerID,1,qwUserID,NLogDataDefine::ItemTo_DemonTower,SParamConfig::wDemonTowerCleanCD2,[pDemonTowerUser,fnAck,qwUserID](UINT8 byRet_, UINT8 byError)
                                {
                                    pDemonTowerUser->dwBuyTime = 0;
                                    
                                    if(byRet_ )
                                    {   
                                        fnAck->bRet = eDemonTower_Error;
                                        return;
                                    }   

                                    if(byError)
                                    {
                                        fnAck->bRet = eDemonTower_LackMoney;
                                        return;
                                    }
                                    
                                    pDemonTowerUser->dwGuardNextAttackTime = 0;
                                    //pUser->SendPkg(g_DemonTowerSvrS.BuildPkg_DemonTowerAtkCDNotify(0));

                                    fnAck->bRet = 0;
                                    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                                    if(pUser)
                                        pUser->SendSysMsg(eMsgDemonTowerClean);

                                    TVecINT32 vecParam;
                                    vecParam.push_back(1);
                                    pUser->OnEvent(eEventType_DemonTowerClearPVPCD,vecParam);
                                    fnAck(true);
                                });

    return 0;
}

//重新加载表格
bool CDemonTowerMgr::ReloadTable()
{
    //TODO:
    return true;
}

void CDemonTowerMgr::RemoveUser(UINT64 qwUserID)
{
    auto itr = _mapDemonTowerUserPtr.find(qwUserID);
    if(itr != _mapDemonTowerUserPtr.end())
    {

        g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Delete,*(itr->second));
        _mapDemonTowerUserPtr.erase(itr);
    }


}

//上线
void CDemonTowerMgr::OnLogin(CUser& rUser)
{
    UINT64 qwUserID = rUser.GetUserID();
    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(pDemonTowerUser)
    {
        if(pDemonTowerUser->byColor != rUser.GetColor())
        {
            pDemonTowerUser->byColor = rUser.GetColor();
            g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser); 
        }

        if(pDemonTowerUser->dwGuardFloorID)
        {
            return;
        }

        if(eDemonTower_Prize_Fail == pDemonTowerUser->dwGuardPos)
        {
           g_DemonTowerSvrS.SendClt_PrizeNotify(&qwUserID,1,eDemonTower_Prize_Fail,pDemonTowerUser->dwFailFloorID,pDemonTowerUser->dwFailPos,pDemonTowerUser->vecFailSoulPrize);
           pDemonTowerUser->dwGuardPos = 0;
           TakeGuardFailPrize(qwUserID);
           g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);
           
        }

        if(eDemonTower_Prize_Day == pDemonTowerUser->dwGuardPos)
        {
            g_DemonTowerSvrS.SendClt_PrizeNotify(&qwUserID,1,eDemonTower_Prize_Day,pDemonTowerUser->dwFailFloorID,pDemonTowerUser->dwFailPos,pDemonTowerUser->vecDaySoulPrize);
            pDemonTowerUser->dwGuardPos = 0;
            TakePassDayPrize(qwUserID);
            g_Center2DBCommC.Send_UpateDemonTowerInfo(eDemonTowerDB_Update,*pDemonTowerUser);

        }


    }

}


//下线
void CDemonTowerMgr::OnOffLine(UINT64 qwUserID)
{
    LOG_DBG<<"CDemonTowerMgr OnOffLine:"<<qwUserID;
    DemonTowerUserPtr pDemonTowerUser = GetTowerUserInfoByUserId(qwUserID);
    if(pDemonTowerUser)
    {
        pDemonTowerUser->dwFloorID = 0;

        if(pDemonTowerUser->dwGuardFloorID)
        {
            return;
        }

        if(!pDemonTowerUser->vecFailSoulPrize.empty() || !pDemonTowerUser->vecDaySoulPrize.empty()) 
        {
            return;
        }

        if(pDemonTowerUser->dwGuardNextAttackTime>time(NULL))
        {
            return;
        }

        if(pDemonTowerUser->dwGuardPos)
        {
            return;
        }

        RemoveUser(qwUserID);

    }


}


