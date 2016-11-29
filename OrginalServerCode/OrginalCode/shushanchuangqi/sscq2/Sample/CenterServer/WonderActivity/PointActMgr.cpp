#include "PointActMgr.h"
#include "RTime.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "WonderActivityMgr.h"

#include "RankMgr.h"

void CPointActMgr::OnEnd()
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
            UINT32 dwCount = CRankMgr::Instance().GetCount(oIt); 
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

void CPointActMgr::OnRetain()
{
    CWonderActivity::OnRetain();
    _setRank.clear();
    UINT16 wActID = GetActID();
    LOG_INF << " WonderActivity ActID = " << wActID << " Retain time End";
    g_Center2DBCommC.Send_DelActPrizeData(wActID);

}

void CPointActMgr::TakePrize(UINT64 &qwPlayerID,UINT32 wCond)
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
    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,qwPlayerID,NLogDataDefine::ItemFrom_WonderActivity,vecUserItem,[qwPlayerID,wActID,wCond](UINT8 byRet_, UINT8 byError)
                                {
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

bool CPointActMgr::CheckConds(UINT32 wCond)
{
    UINT16 wActID = GetActID();
    if(wActID == 0)
    {
        LOG_INF <<" Activity not Active";
        return false;
    }
    UINT16 wCount = GetMaxRoleCount(wCond);
    UINT32 dwCount = GetCurRoleCount(wActID,wCond);
    if(dwCount >= wCount)
        return true;
    return false;
}

void CPointActMgr::GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet)
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

UINT8 CPointActMgr::GetPrizeStateForRole(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond)
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

UINT32 CPointActMgr::GetCurRoleCount(UINT16 wActID,UINT32 wCond)
{
    UINT32 dwCount = 0;
    TMapID2PrizeState mapID2PrizeState = g_WonderActivityMgr.GetMapID2PrizeState();
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
    
    dwCount = CRankMgr::Instance().GetCount(wCond);
    return dwCount;
}

