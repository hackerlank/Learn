#include "stdafx.h"
#include "User.h"
#include "FeedBackMgr.h"
#include "Parameter.h"
#include "Loot.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "IconAppearManager.h"
#include "FighterManager.h"
#include "AutoStoreMgr.h"
#include "Random.h"
#include "FeedBackProtS.h"
CFeedBackMgr g_FeedBackMgr;

void GetItemFromString(TVecItemGenInfo& vecItem, const string strItem,const string strSep=";")
{
        Tokenizer tk(strItem, "|"); // XXX: itemID,count|ItemID,count
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], strSep.c_str());
            UINT16 wItemID = atoi(yatk[0].c_str());
            if (wItemID)
            {
                UINT32 dwCount = 0;
                if (yatk.size() > 1)
                {
                    dwCount = atoi(yatk[1].c_str());
                    SItemGenInfo oItemGenInfo;
                    oItemGenInfo.wItemID = wItemID;
                    oItemGenInfo.dwCount = dwCount;
                    vecItem.push_back(oItemGenInfo);
                }
            }
        }
}

CFeedBackMgr::CFeedBackMgr() 
{

}

const UINT32 ONEDAY = 24*3600;

bool CFeedBackMgr::FeedBackMgrInit()
{
    UINT32 dwOpenServerTime = Time::MkTime(2015, 6, 11);

    //比今天晚的开服时间按开服时间算
    if(Config._dwOpenServerTime > dwOpenServerTime)
    {
        dwOpenServerTime = Config._dwOpenServerTime;
    }

    string strFeedbackPath = Config._strConfigDir + "Conf/Table/Feedback.xml";
    CFeedbackLoader oFeedbackLoader;
    if(!oFeedbackLoader.LoadData(strFeedbackPath))
    {
        LOG_CRI << "CFeedbackLoaderLoader fails! Path: " << strFeedbackPath;
        return false;
    }

    for(size_t i  = 0; i < oFeedbackLoader._vecData.size(); ++i)
    {
        SFeedbackCFGExPtr pFeedbackCFG(new SFeedbackCFGEx);
        pFeedbackCFG->CopyFrom(*oFeedbackLoader._vecData[i]);
        GetItemFromString(pFeedbackCFG->_vecPrize,pFeedbackCFG->_Award);
        GetItemFromString(pFeedbackCFG->_vecRandomPrize,pFeedbackCFG->_Random1);

        if(pFeedbackCFG->_Type == 0)
            return false;

        if(pFeedbackCFG->_BgDay < 1)
            return false;
        if(pFeedbackCFG->_EndDay < pFeedbackCFG->_BgDay)
            return false;
        pFeedbackCFG->_dwBeginTime = dwOpenServerTime + (pFeedbackCFG->_BgDay-1)*ONEDAY;
        pFeedbackCFG->_dwEndTime   = dwOpenServerTime + pFeedbackCFG->_EndDay*ONEDAY;
        _mapFeedbackCFGExPtr[pFeedbackCFG->_Id] = pFeedbackCFG;
    }


    string strFeedbackBagPath = Config._strConfigDir + "Conf/Table/FeedbackBag.xml";
    CFeedbackBagLoader oFeedbackBagLoader;
    if(!oFeedbackBagLoader.LoadData(strFeedbackBagPath))
    {
        LOG_CRI << "CFeedbackBagLoaderLoader fails! Path: " << strFeedbackBagPath;
        return false;
    }

    for(size_t i  = 0; i < oFeedbackBagLoader._vecData.size(); ++i)
    {
        SFeedbackBagCFGExPtr pFeedbackBagCFG(new SFeedbackBagCFGEx);
        pFeedbackBagCFG->CopyFrom(*oFeedbackBagLoader._vecData[i]);
        GetItemFromString(pFeedbackBagCFG->_vecItem,pFeedbackBagCFG->_Award);
        
        if(pFeedbackBagCFG->_BgDay < 1)
            return false;
        if(pFeedbackBagCFG->_EndDay < pFeedbackBagCFG->_BgDay)
            return false;

        pFeedbackBagCFG->_dwBeginTime = dwOpenServerTime + (pFeedbackBagCFG->_BgDay-1)*ONEDAY;
        pFeedbackBagCFG->_dwEndTime   = dwOpenServerTime + pFeedbackBagCFG->_EndDay*ONEDAY;

        _mapFeedbackBagCFGExPtr[pFeedbackBagCFG->_Type] = pFeedbackBagCFG;
    }

    InitData();

    return true;
}


//初始化数据
void CFeedBackMgr::InitData()
{
    _mapActiveFeedbackCFGExPtr.clear();
    for(auto itr = _mapFeedbackCFGExPtr.begin(); itr != _mapFeedbackCFGExPtr.end(); itr++)
    {
        SFeedbackCFGExPtr pFeedbackCFGEx = itr->second;
        if(pFeedbackCFGEx)
        {
            if(pFeedbackCFGEx->_dwBeginTime < time(NULL) && time(NULL) < pFeedbackCFGEx->_dwEndTime )
            {
                _mapActiveFeedbackCFGExPtr[pFeedbackCFGEx->_Id] = pFeedbackCFGEx;
            }
        }

    }

    _mapActiveFeedbackBagCFGExPtr.clear();

    for(auto itr = _mapFeedbackBagCFGExPtr.begin(); itr != _mapFeedbackBagCFGExPtr.end(); itr++)
    {
        SFeedbackBagCFGExPtr pFeedbackBagCFGEx = itr->second;
        if(pFeedbackBagCFGEx)
        {
            if(pFeedbackBagCFGEx->_dwBeginTime<time(NULL) && time(NULL) < pFeedbackBagCFGEx->_dwEndTime)
            {
                _mapActiveFeedbackBagCFGExPtr[pFeedbackBagCFGEx->_Type] = pFeedbackBagCFGEx;
            }
        }
    }

}


void CFeedBackMgr::TimerCheck()
{

}

void CFeedBackMgr::OnMidNight()
{
    CheckUpdateTime(true);
}

void CFeedBackMgr::OnPlayerMidNight(CPlayer& rPlayer)
{
    for(auto itr = _mapActiveFeedbackBagCFGExPtr.begin(); itr != _mapActiveFeedbackBagCFGExPtr.end();itr ++)
    {
        InitPlayerData(rPlayer,itr->second->_Type);
    }
}

void CFeedBackMgr::InitPlayerData(CPlayer& rPlayer,UINT32 dwActiveType)
{
    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        return;
    }
    CFighterManagerPtr pFighterManager = rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
    {
        return;
    }


    if(pAutoStoreMgr->GetValue(eAutoStore_FeedBack_InitData,dwActiveType) != 0)
    {
        return;
    }

    bool bUpdate = false;

    for(auto itr = _mapActiveFeedbackCFGExPtr.begin(); itr != _mapActiveFeedbackCFGExPtr.end();itr++)
    {
        SFeedbackCFGExPtr pFeedbackCFGEx = itr->second;
        if(NULL == pFeedbackCFGEx)
            continue;

        if(pFeedbackCFGEx->_Type != dwActiveType)
         {
                continue;;
         }

         UINT32 dwSum = 0;
         if(pFeedbackCFGEx->_Type == eFeedBackActType_EquipTrump)
         {
             dwSum = pFighterManager->GetEquipTrumpCount(pFeedbackCFGEx->_Quality,pFeedbackCFGEx->_Term); 
             bUpdate = true;
         }
         else if(pFeedbackCFGEx->_Type == eFeedBackActType_Stone)
         {
             dwSum = pFighterManager->GetStoneCount(pFeedbackCFGEx->_Term);
             bUpdate = true;
         }
         else
         {
             LOG_CRI<<"Error Param! _Type:"<<pFeedbackCFGEx->_Type;
             continue;
         }

         pAutoStoreMgr->SetValue(eAutoStore_FeedBack_MaxTakePrize,pFeedbackCFGEx->_Id,dwSum); 
 
    }

    if(!bUpdate)
    {
        LOG_CRI<<"Cfg Error!!!";
        return;
    }

    pAutoStoreMgr->SetValue(eAutoStore_FeedBack_InitData,dwActiveType,1);

}

void CFeedBackMgr::CheckUpdateTime(bool bNotify)
{
    bool bEquipTrump = false;
    bool bStone      = false;


    InitData();

    for(auto itr = _mapActiveFeedbackBagCFGExPtr.begin(); itr != _mapActiveFeedbackBagCFGExPtr.end();)
    {
            if(itr->second->_Type == eFeedBackActType_EquipTrump)
            {
                bEquipTrump = true;
            }
            else
            {
                bStone = true;
            }

            itr++;
    }


    if(bEquipTrump)
    {
        CIconAppearMgr::Instance().OpenActionToClientForAll(113);
    }
    else
    {
        CIconAppearMgr::Instance().CloseActionToClientForAll(113);
    }

    if(bStone)
    {
        CIconAppearMgr::Instance().OpenActionToClientForAll(114);
    }
    else
    {
        CIconAppearMgr::Instance().CloseActionToClientForAll(114);
    }
}

//接收：获取回馈列表
EFeedBackRet CFeedBackMgr::OnGetFeedBackList(CPlayer& rPlayer,TVecFeedBackInfo& vecFeedBackInfo,TVecSBuyDiscountInfo& vecSBuyDiscountInfo)
{
    CFighterManagerPtr pFighterManager = rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
    {
        return eFeedBackRet_Sucess;
    }

    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        return eFeedBackRet_Sucess;
    }
    for(auto itr = _mapActiveFeedbackCFGExPtr.begin(); itr != _mapActiveFeedbackCFGExPtr.end(); itr++)
    {

        SFeedbackCFGExPtr pFeedbackCFGEx = itr->second;
        if(pFeedbackCFGEx)
        {
            SFeedBackInfo oFeedBackInfo;
            oFeedBackInfo.dwActID     = pFeedbackCFGEx->_Id;
            oFeedBackInfo.dwBeginTime = pFeedbackCFGEx->_dwBeginTime;
            oFeedBackInfo.dwEndTime   = pFeedbackCFGEx->_dwEndTime;
            oFeedBackInfo.dwTakePrizeMax = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_MaxTakePrize,pFeedbackCFGEx->_Id);
            oFeedBackInfo.dwTakePrizedCnt = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_TakPrize,oFeedBackInfo.dwActID);
            vecFeedBackInfo.push_back(oFeedBackInfo);
        }
    }

    for(auto itr = _mapActiveFeedbackBagCFGExPtr.begin(); itr != _mapActiveFeedbackBagCFGExPtr.end(); itr++)
    {

        SFeedbackBagCFGExPtr pFeedbackBagCFGEx = itr->second;
        if(pFeedbackBagCFGEx)
        {
            SBuyDiscountInfo oBuyDiscountInfo;
            oBuyDiscountInfo.eType = (EFeedBackActType)pFeedbackBagCFGEx->_Type;
            oBuyDiscountInfo.dwBuyCount = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_BuyCnt,pFeedbackBagCFGEx->_Type);
            vecSBuyDiscountInfo.push_back(oBuyDiscountInfo);
        }
    }

    return eFeedBackRet_Sucess;
}

//接收：购买折扣物品
EFeedBackRet CFeedBackMgr::OnBuyDisCountItem(CPlayer& rPlayer,UINT32 dwBuyID,UINT32 dwCount)
{
    LOG_INF<<"OnBuyDisCountItem dwBuyID:"<<dwBuyID<<" dwCount:"<<dwCount;

    if(dwBuyID != 1 && dwBuyID != 2)
    {
            LOG_CRI<<"eFeedBackRet_ParamError";
        return eFeedBackRet_ParamError;
    }

    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"eFeedBackRet_CFGError";
        return eFeedBackRet_CFGError;
    }

    if(0 == dwCount)
    {
        LOG_CRI<<"0 == dwCount";
        return eFeedBackRet_ParamError;
    }
    auto itr = _mapActiveFeedbackBagCFGExPtr.find(dwBuyID);
    if(itr == _mapActiveFeedbackBagCFGExPtr.end())
    {
        LOG_CRI<<"eFeedBackRet_TimeError";
        return eFeedBackRet_TimeError;
    }

    SFeedbackBagCFGExPtr pFeedbackBagCFGEx = itr->second;
    if(NULL == pFeedbackBagCFGEx)
    {
        LOG_CRI<<"UnkownError";
        return eFeedBackRet_CFGError;
    }

    UINT32 dwSumMoney = pFeedbackBagCFGEx->_NewCost*dwCount;

    UINT32 dwBuyCount = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_BuyCnt,pFeedbackBagCFGEx->_Type);

    UINT32 dwTotal = dwBuyCount + dwCount;
    if(dwTotal > pFeedbackBagCFGEx->_BuyNum)
    {
        return eFeedBackRet_CFGError;
    }


    CUser& rUser = rPlayer.GetUser();
    if(!rUser.CanSubMoney(EMONEY_GOLD,dwSumMoney))
    {
        LOG_CRI<<"eFeedBackRet_MoneyLimit:"<<dwSumMoney;
        return eFeedBackRet_MoneyLimit;
    }

    TVecItemGenInfo vecItem = pFeedbackBagCFGEx->_vecItem;
    for(size_t i=0; i < vecItem.size(); i++)
    {
        vecItem[i].dwCount = vecItem[i].dwCount * dwCount;
    }

    CPack& rPack = rUser.GetPack();
    if(!rPack.CanAddItem(vecItem))
    {
        rUser.SendSysMsg(eMsgETeamPackFull);
        return eFeedBackRet_PackError;
    }

    pAutoStoreMgr->SetValue(eAutoStore_FeedBack_BuyCnt,pFeedbackBagCFGEx->_Type,dwTotal);

    rUser.SubMoney(EMONEY_GOLD,dwSumMoney,NLogDataDefine::ItemTo_Feedback);

    rPack.AddItem(vecItem,NLogDataDefine::ItemFrom_Feedback);

    return eFeedBackRet_Sucess;
}

//接收：领取奖励
EFeedBackRet CFeedBackMgr::OnTakeFeedBackPrize(CPlayer& rPlayer,UINT32 dwActID)
{
    CFighterManagerPtr pFighterManager = rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
    {
        LOG_CRI<<"eFeedBackRet_CFGError";
        return eFeedBackRet_CFGError;
    }

    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        LOG_CRI<<"eFeedBackRet_CFGError";
        return eFeedBackRet_CFGError;
    }

    LOG_CRI<<"OnTakeFeedBackPrize dwActID:"<<dwActID<<" qwRoleID:"<<rPlayer.GetRoleID();
    auto itr = _mapActiveFeedbackCFGExPtr.find(dwActID);
    if(itr == _mapActiveFeedbackCFGExPtr.end())
    {
        LOG_CRI<<"eFeedBackRet_ActiveTimeError "<<dwActID;
        return eFeedBackRet_ActiveTimeError;
    }

    SFeedbackCFGExPtr pFeedbackCFGEx = itr->second;
    if(NULL == pFeedbackCFGEx)
    {
        LOG_CRI<<"eFeedBackRet_CFGError";
        return eFeedBackRet_CFGError;
    }

    UINT32 dwMaxPrize = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_MaxTakePrize,pFeedbackCFGEx->_Id);

    UINT32 dwTakePrize = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_TakPrize,dwActID);
    if(dwTakePrize >= dwMaxPrize)
    {
        LOG_CRI<<"eFeedBackRet_PrizeCntError dwTakePrize:"<<dwTakePrize<<" dwMaxPrize:"<<dwMaxPrize;
        return eFeedBackRet_PrizeCntError;
    }

    CUser& rUser = rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();

    TVecItemGenInfo vecItemPrize = pFeedbackCFGEx->_vecPrize;
    if(!pFeedbackCFGEx->_vecRandomPrize.empty())
    {
       UINT32 dwMaxCnt = pFeedbackCFGEx->_vecRandomPrize.size()-1;
       if(0 == dwMaxCnt)
       {
           vecItemPrize.push_back(pFeedbackCFGEx->_vecRandomPrize[0]);
       }
       else
       {
           UINT32 dwSelect = CRandom::RandInt(0,dwMaxCnt);
           vecItemPrize.push_back(pFeedbackCFGEx->_vecRandomPrize[dwSelect]);
       }
    }

    if(!rPack.CanAddItem(vecItemPrize))
    {
        rUser.SendSysMsg(eMsgETeamPackFull);
        return eFeedBackRet_PackError;
    }

    pAutoStoreMgr->SetValue(eAutoStore_FeedBack_TakPrize,dwActID,dwTakePrize+1);

    rPack.AddItem(vecItemPrize,NLogDataDefine::ItemFrom_Feedback);

    return eFeedBackRet_Sucess;
}

//玩家登陆
void CFeedBackMgr::OnLogin(CPlayer& rPlayer)
{
    bool bEquipTrump = false;
    bool bStone      = false;


    for(auto itr = _mapActiveFeedbackBagCFGExPtr.begin(); itr != _mapActiveFeedbackBagCFGExPtr.end();itr ++)
    {
            if(itr->second->_Type == eFeedBackActType_EquipTrump)
            {
                bEquipTrump = true;
            }
            else
            {
                bStone = true;
            }
    }

    CUser& rUser = rPlayer.GetUser();
    if(bEquipTrump)
    {
        TVecUINT16 vec;
        vec.push_back(113);
        CIconAppearMgr::Instance().OpenActionToClient(rUser,vec);
        InitPlayerData(rPlayer,eFeedBackActType_EquipTrump);
    }
    else
    {
        CIconAppearMgr::Instance().CloseActionToClient(rUser,113);
    }

    if(bStone)
    {
        TVecUINT16 vec;
        vec.push_back(114);
        CIconAppearMgr::Instance().OpenActionToClient(rUser,vec);
        InitPlayerData(rPlayer,eFeedBackActType_Stone);
    }
    else
    {
        CIconAppearMgr::Instance().CloseActionToClient(rUser,114);
    }
}

//强化
void CFeedBackMgr::OnEquipTrumpChange(CPlayer& rPlayer,UINT8 byQuality,UINT8 byMinLevel)
{
    CFighterManagerPtr pFighterManager = rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
    {
        return ;
    }

    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        return;
    }
    for(auto itr = _mapActiveFeedbackCFGExPtr.begin(); itr != _mapActiveFeedbackCFGExPtr.end(); itr++)
    {
        SFeedbackCFGExPtr pFeedbackCFGEx = itr->second;
        if(pFeedbackCFGEx)
        {
            if(pFeedbackCFGEx->_Type != eFeedBackActType_EquipTrump )
            {
                continue;
            }

            if(byQuality != pFeedbackCFGEx->_Quality)
                continue;

            if(byMinLevel != pFeedbackCFGEx->_Term)
                continue;
 
            pAutoStoreMgr->AddValue(eAutoStore_FeedBack_MaxTakePrize,pFeedbackCFGEx->_Id,1);

            SFeedBackInfo oFeedBackInfo;
            oFeedBackInfo.dwActID     = pFeedbackCFGEx->_Id;
            oFeedBackInfo.dwBeginTime = pFeedbackCFGEx->_dwBeginTime;
            oFeedBackInfo.dwEndTime   = pFeedbackCFGEx->_dwEndTime;
            oFeedBackInfo.dwTakePrizeMax =  pAutoStoreMgr->GetValue(eAutoStore_FeedBack_MaxTakePrize,pFeedbackCFGEx->_Id); 
            oFeedBackInfo.dwTakePrizedCnt = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_TakPrize,oFeedBackInfo.dwActID);
            rPlayer.SendPkg(g_FeedBackProtS.BuildPkg_FeedBackInfoNotify(oFeedBackInfo));
       }
    }

}

//合成
void CFeedBackMgr::OnStoneChange(CPlayer& rPlayer,UINT8 byMinLevel,UINT32 dwCount)
{
    CFighterManagerPtr pFighterManager = rPlayer.GetFighterManager();
    if(NULL == pFighterManager)
    {
        return;
    }

    CAutoStoreMgrPtr pAutoStoreMgr = rPlayer.GetAutoStoreMgr();
    if(NULL == pAutoStoreMgr)
    {
        return;
    }
    for(auto itr = _mapActiveFeedbackCFGExPtr.begin(); itr != _mapActiveFeedbackCFGExPtr.end(); itr++)
    {

        SFeedbackCFGExPtr pFeedbackCFGEx = itr->second;
        if(pFeedbackCFGEx)
        {
            if(pFeedbackCFGEx->_Type != eFeedBackActType_Stone)
            {
                continue;
            }

            if(byMinLevel != pFeedbackCFGEx->_Term)
                continue;

            pAutoStoreMgr->AddValue(eAutoStore_FeedBack_MaxTakePrize,pFeedbackCFGEx->_Id,dwCount);
            SFeedBackInfo oFeedBackInfo;
            oFeedBackInfo.dwActID     = pFeedbackCFGEx->_Id;
            oFeedBackInfo.dwBeginTime = pFeedbackCFGEx->_dwBeginTime;
            oFeedBackInfo.dwEndTime   = pFeedbackCFGEx->_dwEndTime;
            oFeedBackInfo.dwTakePrizeMax =  pAutoStoreMgr->GetValue(eAutoStore_FeedBack_MaxTakePrize,pFeedbackCFGEx->_Id);
            oFeedBackInfo.dwTakePrizedCnt = pAutoStoreMgr->GetValue(eAutoStore_FeedBack_TakPrize,oFeedBackInfo.dwActID);
            rPlayer.SendPkg(g_FeedBackProtS.BuildPkg_FeedBackInfoNotify(oFeedBackInfo));
       }
    }


}


void CFeedBackMgr::CloseIcon()
{
    /*
    //关闭图标
    CIconAppearMgr::Instance().CloseActionToClient();
    */
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

