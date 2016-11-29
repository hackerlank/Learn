#include "BeautyAct.h"
#include "RTime.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "WonderActivityMgr.h"

bool CBeautyActMgr::CheckConds(UINT32 wConds)
{
    UINT16 wActID = GetActID(); 
    //LOG_CRI <<" wActID = " << wActID;
    if(wActID == 0)
    {
        LOG_INF <<" Activity not Active";
        return false;
    }
    UINT16 wCount = GetMaxRoleCount(wConds);
    UINT16 wRoles = GetCurRoleCount(wActID,wConds); 
    //LOG_CRI << "wMaxCount " <<wCount <<" , wCurCount = " <<wRoles;
    if(wRoles >= wCount)
        return true;
    return false;
}

void CBeautyActMgr::TakePrize(UINT64 &qwPlayerID,UINT32 wCond)
{
    UINT16 wActID = GetActID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwPlayerID);
    if(pUser == NULL)
        return;
    UINT8 byResult = GetPrizeStateForRole(qwPlayerID,wActID,wCond);
    if(byResult != 1)
    {
        pUser->SendPkg(g_WonderActivityProtS.BuildPkg_SendTakePrizeNtf(wActID,wCond,eGainResult_error));
        return; 
    }
    TVecUserItem vecUserItem;
    TVecItemConfigPtr pVecItem = GetPrize(wCond);
    if(pVecItem.size() == 0)
    {
       pUser->SendPkg(g_WonderActivityProtS.BuildPkg_SendTakePrizeNtf(wActID,wCond,eGainResult_error));
        return; 
    }
    for(auto &it : pVecItem)
    {
        SUserItem oUserItem;
        oUserItem.dwTypeID = it->dwItemID;
        oUserItem.dwCount = it->dwCount;
        vecUserItem.push_back(oUserItem);
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    /*
    auto it = _setAddItemUser.find(qwPlayerID);
    if (it != _setAddItemUser.end())
    {
        LOG_WRN << "AddItemUser twice: " << qwPlayerID << ".";
        return;
    }
    _setAddItemUser.insert(qwPlayerID);
    */
    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwPlayerID,NLogDataDefine::ItemFrom_WonderActivity,vecUserItem,
            [this, qwPlayerID,wActID,wCond](UINT8 byRet_, UINT8 byError)
            {
              //  _setAddItemUser.erase(qwPlayerID);
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwPlayerID);
                if(pUser == NULL)
                    return;
                if(byRet_ || byError)
                {
                    LOG_INF << "BagFull";
                    pUser->SendPkg(g_WonderActivityProtS.BuildPkg_SendTakePrizeNtf(wActID,wCond,eGainResult_fullBag));
                    return;
                }
                g_WonderActivityMgr.OnSuccess(qwPlayerID,wActID,wCond);
            });
}

void CBeautyActMgr::OnEnd()
{

   CWonderActivity::OnEnd();
   UINT16 wActID = GetActID();
   LOG_INF << " WonderActivity ActID = " << wActID << " OnEnd";

   //活动结束，清理现场
   TVecUINT32 wConds;
   GetConds(wConds);
   TMapID2PrizeState& _mapID2PrizeState = g_WonderActivityMgr.GetMapID2PrizeState();
   for(auto &oIt : wConds)
   {
        UINT32 dwCount = CUserMgr::GetCount(NGame2CenterComm::eActBeauty,oIt); 
        NWonderActivityProt::SWonderPrize2DB sPrize2DB;
        sPrize2DB.wActID = wActID;
        sPrize2DB.wActType = 2; //活动结束，
        sPrize2DB.wCond = oIt;
        sPrize2DB.qwRoleID = dwCount; //保留人数
        sPrize2DB.byStatus = 1;

        g_Center2DBCommC.Send_UpdatePrizeStatus(sPrize2DB,eOpAdd);
        
        SWonderPrizeKey oKey(wActID,wActID,oIt);
        auto It = _mapID2PrizeState.find(oKey);
        if(It == _mapID2PrizeState.end())
        {
            _mapID2PrizeState[oKey] = sPrize2DB;
        }
   }
}


void CBeautyActMgr::OnRetain()
{
   CWonderActivity::OnRetain();
   UINT16 wActID = GetActID();
   LOG_INF << " WonderActivity ActID = " << wActID << " Retain time End";
   g_Center2DBCommC.Send_DelActPrizeData(wActID);

}


void CBeautyActMgr::GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet)
{
    UINT32 dwMaxCount;
    TVecUINT32 vecConds;
    GetConds(vecConds);
    for(auto &It : vecConds)
    {
        dwMaxCount = GetMaxRoleCount(It);
        SRoleStatus sRoleStatus;
        sRoleStatus.dwMaxRole = dwMaxCount;
        sRoleStatus.dwCurRole = GetCurRoleCount(wActID,It);
        sRoleStatus.wCond = It;
        sRoleStatus.byStatus = GetPrizeStateForRole(qwRoleID,wActID,It);
        
        vecRet.push_back(sRoleStatus);
    }
}

// 返回1表示满足条件，返回0表示未达到条件，返回2表示已经领取
UINT8 CBeautyActMgr::GetPrizeStateForRole(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond)
{
    TMapID2PrizeState mapID2PrizeState = g_WonderActivityMgr.GetMapID2PrizeState();
    SWonderPrizeKey oKey(qwRoleID,wActID,wCond);
    auto oIt = mapID2PrizeState.find(oKey);
    if(GetState() == eWActState_Begin || GetState() == eWActState_End)
    {
        if(oIt == mapID2PrizeState.end())
        {
            if(!CheckConds(wCond))
                return 0;
            else 
                return 1;
        }
        else 
            return 2;
    }
    return 0;

}

UINT32 CBeautyActMgr::GetCurRoleCount(UINT16 wActID,UINT32 wCond)
{
    UINT32 dwCount = 0;
    const TMapID2PrizeState& mapID2PrizeState = g_WonderActivityMgr.GetMapID2PrizeState();
    if(GetState() == eWActState_Advance || GetState() == eWActState_Init)
    {
        return dwCount;

    }else if(GetState() == eWActState_End)
    {
        for(auto &oIt : mapID2PrizeState)
        {
            SWonderPrize2DB sPrize = oIt.second;
            if(sPrize.wActType  == 2 
               && sPrize.wActID == wActID 
               && sPrize.wCond  == wCond)
            {
                dwCount = static_cast<UINT32>(sPrize.qwRoleID);
                return dwCount;
            }
        }

    }
    
    dwCount = CUserMgr::GetCount(NGame2CenterComm::eActBeauty,wCond);
    return dwCount;
}
