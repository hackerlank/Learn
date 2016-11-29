#include "stdafx.h"
#include "DemonTowerMgr.h"
#include "User.h"
#include "Player.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "CommonDef.h"
#include "Tokenizer.h"
#include "Game2CenterDemonTowerC.h"
#include "Skill.h"
#include "DemonTowerDgn.h"
#include "DungeonMgr.h"
#include "Map.h"
#include "DemonTowerSvrS.h"
#include "Battle.h"
#include "Monster.h"
#include "MonsterMgr.h"
#include "HeroFighter.h"
#include "AutoStoreMgr.h"
#include "GUIDMgr.h"
CDemonTowerMgr g_DemonTowerMgr;

extern void GetItemFromString(TVecItemGenInfo& vecItem, const string strItem);

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
        LOG_CRI << "CDemonTowerLoader.LoadData fails! Path: " << strPath;
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
                
            if(pDemonTowerCFG->_Hp)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULHP;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Hp;
               pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
           }

           if(pDemonTowerCFG->_Atk)
           {
               MoneyInfo oMoneyInfo;
               oMoneyInfo.dwMoneyType =  EMONEY_SOULATTACK;
               oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Atk;
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

           //额外奖励
           GetItemFromString(pDemonTowerCFGExPtr->vecExtraPrize,pDemonTowerCFGExPtr->_ExtraPrize);

       }
    }

    string strSpacePath = Config._strConfigDir + "Conf/Table/SoulSpace.xml";
    CSoulSpaceLoader oSpaceLoader;
    if(!oSpaceLoader.LoadData(strSpacePath))
    {
        LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i = 0; i < oSpaceLoader._vecData.size(); ++i)
    {

        const SSoulSpaceCFG* pCFG = oSpaceLoader._vecData[i];
        SSoulSpaceCFGExPtr pSoulSpaceEx(new SSoulSpaceCFGEx(pCFG));
        
        Tokenizer tk(pCFG->_Attrib, "|"); // XXX: AttrID[[,AttrValue]|AttrID[[,AttrValue]...]
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT32 dwAttribID = atoi(yatk[0].c_str());
            if (dwAttribID)
            {
                UINT32 dwAttribValue = 0;
                if (yatk.size() > 1)
                    dwAttribValue = atoi(yatk[1].c_str());
                VECATTR_ADD(pSoulSpaceEx->_vecAttr,dwAttribID,dwAttribValue);
            }
        }
 

        
        UINT32 dwSpaceID = SKILLANDLEVEL(pCFG->_TypeID,pCFG->_Level);
        
        _mapSoulSpaceCFGEx.insert(make_pair(dwSpaceID,pSoulSpaceEx));
    }
    return true;
}

bool CDemonTowerMgr::ReLoadConfig(const string &strFile)
{

    _dwAttackCD =  ATTCK_CD;
    _dwPrizeCD  = PRIZE_CD;
    _dwMinPrizeTimeSpan = MIN_PRIZE_TIMESPAN;
    if(!_dwAttackCD || !_dwPrizeCD)
    {
         LOG_CRI << "CDemonTowerMgr::Init Error CD == 0 ";
        return false;
    }

    string strPath;
    if("DemonTower.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/DemonTower.xml";
        CDemonTowerLoader oLoader;
        if(!oLoader.LoadData(strPath))
        {
            LOG_CRI << "CDemonTowerLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        
        _vecSDemonTowerCFGExPtr.clear();
        for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
        {
           const SDemonTowerCFG* pDemonTowerCFG = oLoader._vecData[i];
           if(pDemonTowerCFG)
           {
               SDemonTowerCFGExPtr pDemonTowerCFGExPtr(new SDemonTowerCFGEx(pDemonTowerCFG));
               _vecSDemonTowerCFGExPtr.push_back(pDemonTowerCFGExPtr);
                    
                if(pDemonTowerCFG->_Hp)
               {
                   MoneyInfo oMoneyInfo;
                   oMoneyInfo.dwMoneyType =  EMONEY_SOULHP;
                   oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Hp;
                   pDemonTowerCFGExPtr->vecPrize.push_back(oMoneyInfo);
               }

               if(pDemonTowerCFG->_Atk)
               {
                   MoneyInfo oMoneyInfo;
                   oMoneyInfo.dwMoneyType =  EMONEY_SOULATTACK;
                   oMoneyInfo.dwMoneyValue = pDemonTowerCFG->_Atk;
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


           }
        }
    }else if("SoulSpace.xml" == strFile)
    {
        string strSpacePath = Config._strConfigDir + "Conf/Table/SoulSpace.xml";
        CSoulSpaceLoader oSpaceLoader;
        if(!oSpaceLoader.LoadData(strSpacePath))
        {
            LOG_CRI << "oItemLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i = 0; i < oSpaceLoader._vecData.size(); ++i)
        {

            const SSoulSpaceCFG* pCFG = oSpaceLoader._vecData[i];
            SSoulSpaceCFGExPtr pSoulSpaceEx(new SSoulSpaceCFGEx(pCFG));
            
            Tokenizer tk(pCFG->_Attrib, "|"); // XXX: AttrID[[,AttrValue]|AttrID[[,AttrValue]...]
            for (size_t i = 0; i < tk.size(); ++i)
            {
                Tokenizer yatk(tk[i], ",");
                UINT32 dwAttribID = atoi(yatk[0].c_str());
                if (dwAttribID)
                {
                    UINT32 dwAttribValue = 0;
                    if (yatk.size() > 1)
                        dwAttribValue = atoi(yatk[1].c_str());
                    VECATTR_ADD(pSoulSpaceEx->_vecAttr,dwAttribID,dwAttribValue);
                }
            }
     

            
            UINT32 dwSpaceID = SKILLANDLEVEL(pCFG->_TypeID,pCFG->_Level);
            
            _mapSoulSpaceCFGEx.insert(make_pair(dwSpaceID,pSoulSpaceEx));
        }
    }
    return true;
}

//进入锁妖塔
UINT32 CDemonTowerMgr::PlayerEnter(CPlayer& rPlayer, UINT32 dwFloorID)
{
    
    EDungeonResult eResult;
    CDemonTowerDgnPtr pDemonTowerDgn = CDungeonMgr::CreateDemonTowerDgn(5001,rPlayer,eResult);
    if(pDemonTowerDgn)
    {
        bool bRet = pDemonTowerDgn->PlayerEnterFloor(rPlayer,dwFloorID);
        if(bRet)
        {
            //fnAck->dwRet = 0;
            return 0;
        }

    }
    else
    {
        ESystemMsgID eMsgID = eMsgOtherErr;
        switch(eResult)
        {
            case eDungeonLowLevel:
                {
                    eMsgID = eMsgDungeonLowLevel;
                }
                break;
            case eDungeonTypeNotExist:
                {
                    eMsgID = eMsgDungeonTypeNotExist;
                }
                break;
            case eDungeonInDgn:
                {
                    eMsgID = eMsgDungeonInDgn;
                }
                break;
            case eDungeonOtherErr:
                {

                }
                break;
            default:
                {
                }
                break;

        }
        UINT64 qwUserID = rPlayer.GetUserID();
        g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUserID,1,eMsgID);
    }


    return -1;

}

//离开锁妖塔
UINT32  CDemonTowerMgr::PlayerLeave(CPlayer& rPlayer)
{
     UINT64 qwUsrID = rPlayer.GetUserID();
     CGameMapPtr pMap = rPlayer.GetMap();
     if(NULL == pMap)
     {
        g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerErrorMap);

         return 1;
     }

     CDungeonPtr pDungeon = pMap->GetDungeon();
     if(NULL == pDungeon)
     {
         g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerNotInDgn);
         return 2;
     }
             
     if(pDungeon->GetDgnType() != eDemonTowerDgn)
     {
         g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerNotInDgn);
         return 3;
     }

     CDemonTowerDgnPtr pDemonTowerDgn = dynamic_pointer_cast<CDemonTowerDgn>(pDungeon);
     if(pDemonTowerDgn)
     {
        if(!pDemonTowerDgn->PlayerLeave(rPlayer))
        {
            g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID,1,eMsgDemonTowerLeaveFail);
        }
     }

    return 0;
}

//封印怪物
UINT32  CDemonTowerMgr::AttackMonster(CPlayer& rPlayer, UINT32 dwFloorID)
{
    if(dwFloorID > rPlayer.GetTopDemonFloorID() + 1)
    {
        return eDemonTower_NotPass;
    }
  
   SDemonTowerCFGExPtr pDemonTowerCFGExPtr = GetDemonTowerCFG(dwFloorID);
   if(NULL == pDemonTowerCFGExPtr)
   {
       return eDemonTower_Invalid_CFG;
   }

   UINT32 dwEnemyID = pDemonTowerCFGExPtr->_MonsterGroupID;

   TVecBattleFighterPtr vecBattleFighter;
   rPlayer.GetBattleFighterList(vecBattleFighter);


   vector<TVecBattleFighterPtr> vecBattleFighter2;
   UINT64 qwTmpInstID =  1;
   qwTmpInstID = CMonster::GetBattleFighterListByGroupID(vecBattleFighter2,dwEnemyID,qwTmpInstID,vecBattleFighter);
   if (!qwTmpInstID || vecBattleFighter2.empty())
       return eDemonTower_Invalid_CFG;

   IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
   pBS->PutFighters(0, rPlayer.GetMainFighter()->GetInstID(), rPlayer.GetLevel(), vecBattleFighter, rPlayer.GetRoleID());
   pBS->PutFighters(1, qwTmpInstID, CMonsterMgr::GetMonsterLevel(dwEnemyID), vecBattleFighter2[0], 1);

   IBattleFighterPtr pFighter = CMonster::GetSceneFighter(dwEnemyID);
   if (!pFighter)
       pFighter = rPlayer.GetSceneFighter();
   pBS->PutScene(pFighter);
   pBS->Start(EBTMonster);

   std::string strReport;
   pBS->GetReport(strReport);
    UINT64 qwBattleID = pBS->GetBattleID();
   
    rPlayer.SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strReport,rPlayer.GetRoleID(), rPlayer.GetMainFighter()->GetID()));

   if(pBS->GetFinalWinner() == EBResultAttackWin)
   {
        SDemonTowerPassPlayer oDemonTowerPassPlayer;
        oDemonTowerPassPlayer.qwUserID = rPlayer.GetUserID();
        oDemonTowerPassPlayer.dwCurFloorID =  dwFloorID;
        oDemonTowerPassPlayer.dwPower = rPlayer.GetBattlePoint();
        oDemonTowerPassPlayer.wTurns = pBS->GetRounds(); 
        oDemonTowerPassPlayer.qwReportID = qwBattleID;
        rPlayer.SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_OnKillMonster(oDemonTowerPassPlayer));
   }

   return 0;

}

//镇守
UINT32  CDemonTowerMgr::Guard(CPlayer& rPlayer,UINT32 dwFloorID,UINT32 dwPos)
{

    return 0;
}

//抢夺镇守位置
UINT32  CDemonTowerMgr::AtkPlayer(CPlayer& rPlayer,UINT32 dwFloorID,UINT32 dwPos)
{
    return 0;

}

void  CDemonTowerMgr::PlayerEnterNextFloor(CPlayer& rPlayer)
{
    //rPlayer.SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_OnPlayerEnterNextFloor(rPlayer.GetUserID()));    
    rPlayer.GetWalker().Abort();
    UINT32 dwCurFloorID = rPlayer.GetDemonTowerFloorID();
    rPlayer.SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_PlayerEnterFloorRequest(rPlayer.GetUserID(),dwCurFloorID+1));

}

//下一层
void   CDemonTowerMgr::PlayerEnterLowFloor(CPlayer& rPlayer)
{
    UINT32 dwCurFloorID = rPlayer.GetDemonTowerFloorID();
    if(dwCurFloorID<=1)
        return;
    rPlayer.GetWalker().Abort();
    rPlayer.SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_PlayerEnterFloorRequest(rPlayer.GetUserID(),dwCurFloorID-1));
}



//领取每日过关奖励
UINT32 CDemonTowerMgr::TakeSealPrize(CPlayer& rPlayer)
{
    UINT32 dwFloorID = rPlayer.GetPrizeDemonFloorID();
    if(!dwFloorID)
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerEmptyPrize)); 
        return eDemonTower_Empty_Prize;
    }
    
    SDemonTowerCFGExPtr pDemonTowerCFGEx = GetDemonTowerCFG(dwFloorID);

    if(!pDemonTowerCFGEx)
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerErrorCFG));
        return eDemonTower_Invalid_CFG;
    }

    rPlayer.SetPrizeDemonFloorID(0);
    //UINT32 dwMoneyValue = pDemonTowerCFGEx->_DayPrize;
    CUser& rUser = rPlayer.GetUser();
    for(MoneyInfo& rMoneyInfo:pDemonTowerCFGEx->vecDayPrize)
    {
        rUser.AddMoney((EMoneyType)rMoneyInfo.dwMoneyType,rMoneyInfo.dwMoneyValue,NLogDataDefine::ItemFrom_DemonTowerSeal);
    }

    //已领取通知
    rPlayer.SendPkg(g_DemonTowerSvrS.BuildPkg_DayPrizeResetNotify(0));

    TVecINT32 vecParam;
    vecParam.push_back(1);
    rPlayer.OnEvent(eEventType_DemonTowerGetPrize,vecParam);

    return 0;
}
    
UINT32  CDemonTowerMgr::TakePassPrize(CPlayer& rPlayer,UINT32 dwFloorID)
{
    
    SDemonTowerCFGExPtr pDemonTowerCFGEx = GetDemonTowerCFG(dwFloorID);

    if(!pDemonTowerCFGEx)
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerErrorCFG));
        return eDemonTower_Invalid_CFG;
    }

    //UINT32 dwMoneyValue = pDemonTowerCFGEx->vecPassPrize;
    CUser& rUser = rPlayer.GetUser();

    for(MoneyInfo& rMoneyInfo:pDemonTowerCFGEx->vecPassPrize)
    {
        rUser.AddMoney((EMoneyType)rMoneyInfo.dwMoneyType,rMoneyInfo.dwMoneyValue,NLogDataDefine::ItemFrom_DemonTowerPass);
    }

    return 0;

}

UINT32 GetLayerPrizeTag(CPlayer& rPlayer,UINT32 dwFloorID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_DemonTower_LayerPrize,dwFloorID);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<rPlayer.GetRoleID();
    return 0;
}

void SetLayerPrizeTag(CPlayer& rPlayer,UINT32 dwFloorID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_DemonTower_LayerPrize,dwFloorID,1);
    }
}



//每层奖励
UINT32  CDemonTowerMgr::TakeLayerPrize(CPlayer& rPlayer,UINT32 dwFloorID,UINT32& dwCurPrizeFloorID)
{
    /*UINT32 dwMintLayerID = rPlayer.GetLayerPrizeDemonFloorID();
    dwCurPrizeFloorID = dwMintLayerID;
    if(dwFloorID <= dwMintLayerID)
    {
        rPlayer.SendSysMsg(eMsgBattleArrayTakePrized);
        return eDemonTower_Empty_Prize;
    }
    */

    UINT32 dwTag = GetLayerPrizeTag(rPlayer,dwFloorID);
    if(dwTag)
    {
        rPlayer.SendSysMsg(eMsgBattleArrayTakePrized);
        return eDemonTower_Empty_Prize;
    }

    if(dwFloorID > rPlayer.GetTopDemonFloorID() )
    {
        rPlayer.SendSysMsg(eMsgDemonTowerLowFloor);
        return eDemonTower_NotPass;
    }

    SDemonTowerCFGExPtr pDemonTowerCFGEx = GetDemonTowerCFG(dwFloorID);

    if(!pDemonTowerCFGEx)
    {
        rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDemonTowerErrorCFG));
        return eDemonTower_Invalid_CFG;
    }

    //UINT32 dwMoneyValue = pDemonTowerCFGEx->vecPassPrize;
    CUser& rUser = rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
    if(!rPack.CanAddItem(pDemonTowerCFGEx->vecExtraPrize))
    {
        rPlayer.SendSysMsg(eMsgPackFullErr);
        return eDemonTower_Invalid_CFG;
    }

    if(!rPack.AddItem(pDemonTowerCFGEx->vecExtraPrize,NLogDataDefine::ItemFrom_DemonTowerPass))
    {

        LOG_CRI<<"TakeLayerPrize ERROR!!!";
    }

    rPlayer.SetLayerPrizeDemonFloorID(dwFloorID);

    dwCurPrizeFloorID = dwFloorID; 

    SetLayerPrizeTag(rPlayer,dwFloorID);
    return 0;
}

//已经领奖层数`
void CDemonTowerMgr::OnGetLayerPrized(CPlayer& rPlayer,TVecUINT32& vecFloorID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        TVecAutoStoreDBInfo vecAutoStoreDBInfo;
        pAutoStoreMgr->GetListByType(eAutoStore_DemonTower_LayerPrize,vecAutoStoreDBInfo);

        for(size_t i = 0; i < vecAutoStoreDBInfo.size(); i++)
        {
            vecFloorID.push_back(vecAutoStoreDBInfo[i].dwClassID);
        }
    }
}


//领取过每日镇守奖励
UINT32  CDemonTowerMgr::TakePassDayPrize(CPlayer& rPlayer)
{

    return 0;
}
    


//领取镇守奖励
UINT32  CDemonTowerMgr::TakeGuardFailPrize(CPlayer& rPlayer)
{
    
    return 0;

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

SSoulSpaceCFGExPtr CDemonTowerMgr::GetSoulSpaceCFG(UINT32 dwSpaceID)
{
    auto itr = _mapSoulSpaceCFGEx.find(dwSpaceID);
    if(itr != _mapSoulSpaceCFGEx.end())
    {
        return itr->second;
    }

    return NULL;

}




