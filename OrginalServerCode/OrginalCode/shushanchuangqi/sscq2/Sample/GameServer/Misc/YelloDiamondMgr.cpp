#include "stdafx.h"
#include "Protocols.h"
#include "YelloDiamondMgr.h"
#include "Version.h"
#include "Tokenizer.h"
#include "UserMgr.h"
#include "User.h"
#include "Player.h"
#define REGISTER_YDFUN(type,name,fun) \
if(type > EBagType_eMax) \
{ \
    return eOtherError; \
}  \
if(!_mapID2YDFun.insert(make_pair(type,&name::fun)).second) \
{ \
    return eOtherError; \
} \

UINT32 GetValue(UINT8 byIndex)
{
    UINT32 dwRet = 1;
    for(UINT8 i=1; i<byIndex; ++i)
    {
           dwRet = dwRet * 2;
    }
    return dwRet;
}

UINT8 GetPos(UINT16 dwBit)
{
    UINT8 byCount = 0;
    if(dwBit == 0)
        return byCount;
    while(dwBit)
    {
        ++ byCount;
        dwBit = dwBit >> 1;
        
    }
    LOG_CRI << " byCount = "<< byCount ; 
    return byCount;
}

const UINT16 dlvlLength = 10;
bool CYelloDiamondMgr::Init()
{
    _qwVersion = VERSION_INIT;
    Register();
    return LoadConfig();
}

bool CYelloDiamondMgr::LoadConfig(bool bReload)
{
    
    string strPath = Config._strConfigDir + "Conf/Table/YelloDiamond.xml";
    CYelloDiamondLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oYelloDiamond.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oLoader._vecData.size(); ++i)
    {
        SYelloDiamondCFG* pCFG = oLoader._vecData[i];
        SYDCFGExPtr pCFGExPtr(new SYDCFGEx);
        pCFGExPtr->eBagType = static_cast<EBagType>(pCFG->_BagType);
        pCFGExPtr->byLevel = pCFG->_Level;
        pCFGExPtr->SetConfig(*pCFG);

        Tokenizer tk(pCFG->_Pack, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer tk2(tk[j],",");
            UINT32 dwItemID = atoi(tk2[0].c_str());
            UINT32 dwCount = atoi(tk2[1].c_str());
            if (!dwItemID)
                continue;
            SItemGenInfo stItemGen;
            stItemGen.wItemID = dwItemID;
            stItemGen.dwCount = dwCount;
            stItemGen.eBindType = eBindGet;
            pCFGExPtr->vecItems.push_back(stItemGen);
        }
        if(pCFGExPtr->eBagType == EBagType_eGrowBag)
        {
            Tokenizer tk(pCFG->_PackEx, "|");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                Tokenizer tk2(tk[j],",");
                UINT32 dwItemID = atoi(tk2[0].c_str());
                UINT32 dwCount = atoi(tk2[1].c_str());
                if (!dwItemID)
                continue;
                SItemGenInfo stItemGen;
                stItemGen.wItemID = dwItemID;
                stItemGen.dwCount = dwCount;
                stItemGen.eBindType = eBindGet;
                pCFGExPtr->vecItemEx.push_back(stItemGen);
            }
        }
       _vecCFGExPtr.push_back(pCFGExPtr);
    } 
    
    return true;
}

EOpResult CYelloDiamondMgr::Register()
{
    REGISTER_YDFUN(EBagType_eDayBag,CYelloDiamondMgr,GainYDDayBag);
    REGISTER_YDFUN(EBagType_eYearBag,CYelloDiamondMgr,GainYDYearBag);
    REGISTER_YDFUN(EBagType_eLuxuryBag,CYelloDiamondMgr,GainYDLuxuryBag);
    REGISTER_YDFUN(EBagType_eGrowBag,CYelloDiamondMgr,GainYDGrowBag);
    REGISTER_YDFUN(EBagType_eNewBag,CYelloDiamondMgr,GainYDNewBag);
    REGISTER_YDFUN(EBagType_eHorseBag,CYelloDiamondMgr,GainYDHorseBag);
    return eSuccess;
}



EOpResult CYelloDiamondMgr::HasGainBag(CUser &rUser,EBagType eBagType,UINT16 &dwLevel)
{
    EOpResult bRet = eAreadyGain;
    const SPlatformParam& stPlatformParam = rUser.GetCurrentPlatformParam();
    switch(eBagType)
    {
        case EBagType_eDayBag:
            {
                if(!rUser.GetVars().GetVar(ePlayerYDDayBag))
                {
                    bRet = eSuccess;
                }
            }
            break;
        case EBagType_eYearBag:
            {
                if(stPlatformParam.byQQPtType == eQQPtTypeYellow && !rUser.IsYealyPlatform())
                {
                    bRet = eNotYear;
                    break;
                }
                if(!rUser.GetVars().GetVar(ePlayerYDYearBag))
                {
                    bRet = eSuccess;
                }
            }
            break;
        case EBagType_eLuxuryBag:
            {
                if(stPlatformParam.byQQPtType == eQQPtTypeYellow && !rUser.IsSuperPlatform())
                {
                    bRet = eNotLuxury;
                    break;
                }
                if(!rUser.GetVars().GetVar(ePlayerYDLuxuryBag))
                {
                    bRet = eSuccess;
                }
            }
            break;
        case EBagType_eNewBag:
            {
                if(!rUser.GetVars().GetVar(ePlayerYDNewBag))
                {
                    bRet = eSuccess;
                }
            }
            break;
        case EBagType_eHorseBag:
            {
                if(!rUser.GetVars().GetVar(ePlayerYDHorseBag))
                {
                    bRet = eSuccess;
                }
            }
            break;
        case EBagType_eGrowBag:
            {
                UINT8 byNowLevel = rUser.GetLevel();
                UINT16 dwGetBit =  rUser.GetVars().GetVar(ePlayerYDGrowBag);
                UINT8 byIndex = dwLevel /10;
                if(dwLevel % 10 != 0)
                    return eOtherError;
                bool bGain = dwGetBit & GetValue(byIndex);
                if(bGain)
                {
                    bRet = eAreadyGain;
                    break;
                }
                if(byNowLevel < dwLevel)
                {
                    bRet = eShortLevel;
                    break;
                }else
                {
                    bRet = eSuccess;
                    break;
                }
            }
            break;
        default:
            break;
       }
  return bRet;
}
EOpResult CYelloDiamondMgr::GainYDBag(CUser &rUser, EBagType eBagType, UINT16 &dLevel)
{
    EOpResult eResult = HasGainBag(rUser,eBagType,dLevel);
    if(eResult != eSuccess)
    {
        return eResult;
    }
   auto it = _mapID2YDFun.find(eBagType);
   if(it != _mapID2YDFun.end())
   {
       SYDParamPtr pYDParam(new SYDParam);
       pYDParam->eBagType = eBagType;
       pYDParam->wUserLevel = dLevel;
       pYDParam->qwUserID = rUser.GetUserID();
       YDFun pFun = it->second;
       if(pFun)
           return (this->*pFun)(pYDParam);
   }
   return eOtherError;
}

EOpResult CYelloDiamondMgr::OnModifyYDLevel(CUser &rUser,UINT8 &rLevel)
{
    rUser.SetYelloDiamondLevel(rLevel);
    return eSuccess;   
}
EOpResult CYelloDiamondMgr::GainYDDayBag(SYDParamPtr pParam)
{
    EBagType eBagType = pParam->eBagType;
    SYDCFGExPtr pCFGExPtr = NULL;
    auto it = _vecCFGExPtr.begin();
    for(; it!=_vecCFGExPtr.end(); ++it)
    {
        if(eBagType == (*it)->eBagType && pParam->wUserLevel == (*it)->byLevel)
          {
              pCFGExPtr = *it;
              break;
          }
    }
    if(!pCFGExPtr)
        return eOtherError;
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(pParam->qwUserID);
    CPack &rPack = pUser->GetPack();
    std::vector<SItemGenInfo> vecItems = pCFGExPtr->vecItems;
    if(!vecItems.empty())
    {
        if(!rPack.CanAddItem(vecItems))
        {
            return eBagFull;
        }
        else
        {
            rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_YelloDiamondAward);
        }
    }
    pUser->GetVars().SetVar(ePlayerYDDayBag,1);

    if(pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pCFGExPtr->_ID);
        pUser->GetPlayer()->OnEvent(eEventType_YellowDiamondGift,vecParam);
    }

    return eSuccess;
}
EOpResult CYelloDiamondMgr::GainYDNewBag(SYDParamPtr pParam)
{
    EBagType eBagType = pParam->eBagType;
    SYDCFGExPtr pCFGExPtr = NULL;
    auto it = _vecCFGExPtr.begin();
    for(; it!=_vecCFGExPtr.end(); ++it)
    {
        if(eBagType == (*it)->eBagType)
          {
              pCFGExPtr = *it;
              break;
          }
    }
    if(!pCFGExPtr)
        return eOtherError;
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(pParam->qwUserID);
    CPack &rPack = pUser->GetPack();
    std::vector<SItemGenInfo> vecItems = pCFGExPtr->vecItems;
    if(!vecItems.empty())
    {
        if(!rPack.CanAddItem(vecItems))
        {
            return eBagFull;
        }
        else
        {
            rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_YelloDiamondAward);
        }
    }
    pUser->GetVars().SetVar(ePlayerYDNewBag,1);
    
    if(pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pCFGExPtr->_ID);
        pUser->GetPlayer()->OnEvent(eEventType_YellowDiamondGift,vecParam);
    }


    return eSuccess;
}
EOpResult CYelloDiamondMgr::GainYDYearBag(SYDParamPtr pParam)
{
    EBagType eBagType = pParam->eBagType;
    SYDCFGExPtr pCFGExPtr = NULL;
    auto it = _vecCFGExPtr.begin();
    for(; it!=_vecCFGExPtr.end(); ++it)
    {
      LOG_CRI << " Type = " << (*it)->eBagType <<" ||| Level" <<  (*it)->byLevel;
        if(eBagType == (*it)->eBagType)
          {
              pCFGExPtr = *it;
              break;
          }
    }
    if(!pCFGExPtr)
        return eOtherError;
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(pParam->qwUserID);
    CPack &rPack = pUser->GetPack();
    std::vector<SItemGenInfo> vecItems = pCFGExPtr->vecItems;
    if(!vecItems.empty())
    {
        if(!rPack.CanAddItem(vecItems))
        {
            return eBagFull;
        }
        else
        {
            rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_YelloDiamondAward);
        }
    }
    pUser->GetVars().SetVar(ePlayerYDYearBag,1);
    
    if(pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pCFGExPtr->_ID);
        pUser->GetPlayer()->OnEvent(eEventType_YellowDiamondGift,vecParam);
    }


    return eSuccess;
}
EOpResult CYelloDiamondMgr::GainYDLuxuryBag(SYDParamPtr pParam)
{
    EBagType eBagType = pParam->eBagType;
    SYDCFGExPtr pCFGExPtr = NULL;
    auto it = _vecCFGExPtr.begin();
    for(; it!=_vecCFGExPtr.end(); ++it)
    {
        if(eBagType == (*it)->eBagType)
          {
              pCFGExPtr = *it;
              break;
          }
    }
    if(!pCFGExPtr)
        return eOtherError;
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(pParam->qwUserID);
    CPack &rPack = pUser->GetPack();
    std::vector<SItemGenInfo> vecItems = pCFGExPtr->vecItems;
    if(!vecItems.empty())
    {
        if(!rPack.CanAddItem(vecItems))
        {
            return eBagFull;
        }
        else
        {
            rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_YelloDiamondAward);
        }
    }
    pUser->GetVars().SetVar(ePlayerYDLuxuryBag,1);
    
    if(pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pCFGExPtr->_ID);
        pUser->GetPlayer()->OnEvent(eEventType_YellowDiamondGift,vecParam);
    }


    return eSuccess;
 
}

EOpResult CYelloDiamondMgr::GainYDGrowBag(SYDParamPtr pParam)
{
    EBagType eBagType = pParam->eBagType;
    SYDCFGExPtr pCFGExPtr = NULL;
    UINT32 dwLv = pParam->wUserLevel;
    if(dwLv % 10 != 0)
        return eOtherError;
    UINT8 byPos = dwLv/10;
    auto it = _vecCFGExPtr.begin();
    for(; it!=_vecCFGExPtr.end(); ++it)
    {
        if(eBagType == (*it)->eBagType && dwLv == (*it)->byLevel)
          {
              pCFGExPtr = *it;
              break;
          }
    }
    if(!pCFGExPtr)
        return eOtherError;
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(pParam->qwUserID);
    CPack &rPack = pUser->GetPack();
    std::vector<SItemGenInfo> vecItems = pCFGExPtr->vecItems;
    if(!vecItems.empty())
    {
        if(!rPack.CanAddItem(vecItems))
        {
            return eBagFull;
        }
        else
        {
            rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_YelloDiamondAward);
        }
    }
    const SPlatformParam& st = pUser->GetCurrentPlatformParam();
    if(st.byQQPtType == eQQPtTypeYellow && st.byQQPtLv > 0)
    {

        std::vector<SItemGenInfo> vecItemEx = pCFGExPtr->vecItemEx;
        if(!rPack.CanAddItem(vecItemEx))
        {
            return eBagFull;
        }
        else
        {
            rPack.AddItem(vecItemEx, NLogDataDefine::ItemFrom_YelloDiamondAward);
        }
    }
    UINT16 wOldBit = pUser->GetVars().GetVar(ePlayerYDGrowBag);
    wOldBit = wOldBit | GetValue(byPos);
    pUser->GetVars().SetVar(ePlayerYDGrowBag,wOldBit);
    if(pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pCFGExPtr->_ID);
        pUser->GetPlayer()->OnEvent(eEventType_YellowDiamondGift,vecParam);
    }


    return eSuccess;
}
EOpResult CYelloDiamondMgr::GainYDHorseBag(SYDParamPtr pParam)
{
    EBagType eBagType = pParam->eBagType;
    SYDCFGExPtr pCFGExPtr = NULL;
    auto it = _vecCFGExPtr.begin();
    for(; it!=_vecCFGExPtr.end(); ++it)
    {
        if(eBagType == (*it)->eBagType)
          {
              pCFGExPtr = *it;
              break;
          }
    }
    if(!pCFGExPtr)
        return eOtherError;

    CUserPtr pUser = CUserMgr::GetUserByUserID(pParam->qwUserID);
    CPack &rPack = pUser->GetPack();
    std::vector<SItemGenInfo> vecItems = pCFGExPtr->vecItems;
    if(!vecItems.empty())
    {
        if(!rPack.CanAddItem(vecItems))
        {
            return eBagFull;
        }
        else
        {
            rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_YelloDiamondAward);
        }
    }
    pUser->GetVars().SetVar(ePlayerYDHorseBag,1);
    if(pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pCFGExPtr->_ID);
        pUser->GetPlayer()->OnEvent(eEventType_YellowDiamondGift,vecParam);
    }
    return eSuccess;
}

bool CYelloDiamondMgr::GetYDInfo(CUser& rUser, SYDInfo& sYDInfo)
{
   sYDInfo.bGainDayBag =  rUser.GetVars().GetVar(ePlayerYDDayBag);
   sYDInfo.bGainYearBag =  rUser.GetVars().GetVar(ePlayerYDYearBag);
   sYDInfo.bGainLuxuryBag =  rUser.GetVars().GetVar(ePlayerYDLuxuryBag);
   sYDInfo.bGainNewBag =  rUser.GetVars().GetVar(ePlayerYDNewBag);
   sYDInfo.bGainHorseBag =  rUser.GetVars().GetVar(ePlayerYDHorseBag);
   sYDInfo.dGrowBag =  rUser.GetVars().GetVar(ePlayerYDGrowBag);
   return true;
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

