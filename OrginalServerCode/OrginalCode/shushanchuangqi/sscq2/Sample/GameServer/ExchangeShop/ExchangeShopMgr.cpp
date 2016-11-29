#include "stdafx.h"
#include "stdafx.h"
#include "ExchangeShopMgr.h"
#include "Player.h"
#include "User.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "GetCondMgr.h"
#include "ItemMgr.h"
#include "ExchangeShopSvrS.h"
#include "RTime.h"

using namespace NExchangeShopProt;

TMapExchangeMallCFGPtr CExchangeShopMgr::_mapExchangeMallCFGPtr;
bool CExchangeShopMgr::ExchangeInit()
{
    string strPath = Config._strConfigDir + "Conf/Table/ExchangeMall.xml";
    CExchangeMallLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "CExchangeMallLoader fails! Path: " << strPath;
        return false;
    }

    for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
    {
        SExchangeMallCFGPtr pExchangeMallCFG(new SExchangeMallCFG);
        *pExchangeMallCFG = *oLoader._vecData[i];
        _mapExchangeMallCFGPtr[pExchangeMallCFG->_Id] = pExchangeMallCFG;
    }
 
    return true;
}

CExchangeShopMgr::CExchangeShopMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer)
{
    
}

bool CExchangeShopMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    for(size_t i = 0; i < rRoleDataInfo.vecExchangeInfo.size(); ++i)
    {
        const ExchangeInfo& rExchangeInfo = rRoleDataInfo.vecExchangeInfo[i];
        _mapExchangeInfo[rExchangeInfo.dwExchangeID]=rExchangeInfo;
    }

    return true;
}

void CExchangeShopMgr::Update2DB(const ExchangeInfo& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeExchangedItem, eDataChange, strData);
}

SExchangeMallCFGPtr CExchangeShopMgr::GetItemByID(UINT32 dwExchangeID)
{
    auto itr = CExchangeShopMgr::_mapExchangeMallCFGPtr.find(dwExchangeID);
    if(itr != CExchangeShopMgr::_mapExchangeMallCFGPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

//兑换物品
UINT32 CExchangeShopMgr::ExchangeItem(UINT32 dwExchangeID,UINT32 dwCount, function<void(UINT32 dwRet)> func)
{
    //  检查是否满足兑换条件(XXX: 帮贡不检查，直接扣的时候检查)
    UINT32 dwRet = CheckExchangeCond(dwExchangeID, dwCount);
    if (dwRet != eExchangeShop_Sucess)
        return dwRet;

    CUser& rUser = _rPlayer.GetUser(); 
    SExchangeMallCFGPtr pExchangeMallCFG = GetItemByID(dwExchangeID);
    if(NULL == pExchangeMallCFG)
    {
        rUser.SendSysMsg(eMsgExchangeShopCfgLimit);
        return eExchangeShop_CfgLimit;
    }

    // 道具ID
    SItemInfo* pItemCfg = CItemMgr::GetItemConfig(pExchangeMallCFG->_ItemId);
    if (!pItemCfg)
    {
        rUser.SendSysMsg(eMsgExchangeShopErrorItemID);
        return eExchangeShop_ErrorItemID;
    }
    TVecItemGenInfo vecItems;
    SItemGenInfo sItemGen;
    sItemGen.wItemID    = pExchangeMallCFG->_ItemId;
    sItemGen.dwCount    = pExchangeMallCFG->_ItemCount * dwCount;
    sItemGen.eBindType  = eBindGet;
    sItemGen.byQuality  = pItemCfg->oItemCfg._Quality;
    sItemGen.dwTimeID   = pItemCfg->oItemCfg._ItemTimeID;
    vecItems.push_back(sItemGen);

    // 满足实际条件
    if(pExchangeMallCFG->_AvailableCon)
    {
        if(!CGetCondMgr::Instance().ProcessCond(rUser,pExchangeMallCFG->_AvailableCon, NLogDataDefine::ItemTo_ExchangeItem))
        {   
            rUser.SendSysMsg(eMsgExchangeShopCondLimit);
            return eExchangeShop_CondLimit;
        }
    }

    EMoneyType eType = (EMoneyType)pExchangeMallCFG->_MoneyType;

    // 扣除货币
    UINT32 dwPrice = pExchangeMallCFG->_Price * dwCount;
    if (eType != EMONEY_GUILDCONTRIB) // 不是帮贡，直接扣除
    {
        if(!rUser.SubMoney(eType, dwPrice, NLogDataDefine::ItemTo_ExchangeItem))
            return eExchangeShop_MoneyLimit; // 货币不足
    }
    else // 帮贡，需要找CenterServer扣除
    {
        g_Game2CenterCommC.Send_SubGuildContribution(_rPlayer.GetUserID(), dwPrice,
                [func, dwExchangeID, dwCount, dwPrice, this](UINT8 byRet, NGuildProt::EGuildResult eResult)
                {
                    if (byRet == 0 && eResult == eGuildSuccess)
                    {
                        CUser& rUser = _rPlayer.GetUser(); 
                        SExchangeMallCFGPtr pExchangeMallCFG = GetItemByID(dwExchangeID);
                        if(NULL == pExchangeMallCFG)
                        {
                            rUser.SendSysMsg(eMsgExchangeShopCfgLimit);
                            func(eExchangeShop_CfgLimit);
                        }
                        EMoneyType eType = (EMoneyType)pExchangeMallCFG->_MoneyType;

                        SItemInfo* pItemCfg = CItemMgr::GetItemConfig(pExchangeMallCFG->_ItemId);
                        if (!pItemCfg)
                        {
                            rUser.SendSysMsg(eMsgExchangeShopErrorItemID);
                            func(eExchangeShop_ErrorItemID);
                        }

                        TVecItemGenInfo vecItems;
                        SItemGenInfo sItemGen;
                        sItemGen.wItemID    = pExchangeMallCFG->_ItemId;
                        sItemGen.dwCount    = pExchangeMallCFG->_ItemCount * dwCount;
                        sItemGen.eBindType  = eBindGet;
                        sItemGen.byQuality  = pItemCfg->oItemCfg._Quality;
                        sItemGen.dwTimeID   = pItemCfg->oItemCfg._ItemTimeID;
                        vecItems.push_back(sItemGen);

                        // 增加道具
                        if (!rUser.GetPack().AddItem(vecItems, NLogDataDefine::ItemFrom_ExchangeItem))
                            func(eExchangeShop_ErrorPack);

                        UINT32 dwTotalCount = 0; // 总兑换次数

                        //限购数据处理
                        if (pExchangeMallCFG->_StoreNum)
                        {
                            EDataChange eDataChange = eOpUpdate;
                            if (_mapExchangeInfo.find(dwExchangeID) == _mapExchangeInfo.end())
                                eDataChange = eOpAdd;
                            else
                                eDataChange = eOpUpdate;

                            ExchangeInfo& rInfo = _mapExchangeInfo[dwExchangeID];

                            rInfo.qwRoleID      =   _rPlayer.GetUserID();
                            rInfo.dwExchangeID  =   dwExchangeID;
                            rInfo.dwCount       +=  dwCount;
                            rInfo.dwFinishTime  =   Time::Now();

                            _rPlayer.SendPkg(g_ExchangeShopProtSvrS.BuildPkg_ExchangeItemUpdate(rInfo));
                            Update2DB(rInfo, eDataChange);

                            dwTotalCount = rInfo.dwCount;
                        }
                        LOG_INF << "dwExchangeID: " << dwExchangeID << ", dwCount:" << dwTotalCount << "|" << pExchangeMallCFG->_StoreNum;

                        //兑换事件
                        TVecINT32 vecParam;
                        vecParam.push_back(dwCount);
                        vecParam.push_back(dwExchangeID);
                        vecParam.push_back(dwPrice);
                        vecParam.push_back(eType);
                        vecParam.push_back(dwTotalCount); //总兑换次数
                        _rPlayer.OnEvent(eEventType_ExChangingMallBought,vecParam);

                        func(eExchangeShop_Sucess);
                    }
                    else
                        func(eExchangeShop_MoneyLimit);
                });
        return eExchangeShop_Sucess;
    }

    // 增加道具
    if (!rUser.GetPack().AddItem(vecItems, NLogDataDefine::ItemFrom_ExchangeItem))
        return eExchangeShop_ErrorPack;

    UINT32 dwTotalCount = 0; // 总兑换次数

    //限购数据处理
    if (pExchangeMallCFG->_StoreNum)
    {
        EDataChange eDataChange = eOpUpdate;
        if (_mapExchangeInfo.find(dwExchangeID) == _mapExchangeInfo.end())
            eDataChange = eOpAdd;
        else
            eDataChange = eOpUpdate;

        ExchangeInfo& rInfo = _mapExchangeInfo[dwExchangeID];

        rInfo.qwRoleID      =   _rPlayer.GetUserID();
        rInfo.dwExchangeID  =   dwExchangeID;
        rInfo.dwCount       +=  dwCount;
        rInfo.dwFinishTime  =   Time::Now();

        _rPlayer.SendPkg(g_ExchangeShopProtSvrS.BuildPkg_ExchangeItemUpdate(rInfo));
        Update2DB(rInfo, eDataChange);

        dwTotalCount = rInfo.dwCount;
    }
    LOG_INF << "dwExchangeID: " << dwExchangeID << ", dwCount:" << dwTotalCount << "|" << pExchangeMallCFG->_StoreNum;

    //兑换事件
    TVecINT32 vecParam;
    vecParam.push_back(dwCount);
    vecParam.push_back(dwExchangeID);
    vecParam.push_back(dwPrice);
    vecParam.push_back(eType);
    vecParam.push_back(dwTotalCount); //总兑换次数
    _rPlayer.OnEvent(eEventType_ExChangingMallBought,vecParam);

    return eExchangeShop_Sucess;
}

//获取玩家已兑换列表
void CExchangeShopMgr::GetExchangedItemList(TVecExchangeInfo& vecExchangeInfo)
{
    for(auto & rPair :  _mapExchangeInfo)
    {
        SExchangeMallCFGPtr pExchangeMallCFG = GetItemByID(rPair.first);
        if(NULL == pExchangeMallCFG)
            continue;

        // 可购买次数
        if(pExchangeMallCFG->_StoreNum != 0)
        {
            switch (pExchangeMallCFG->_Type)
            {
                case 7: // 帮派商城
                    if(Time::TheDay(0, rPair.second.dwFinishTime) < Time::TheDay(0, Time::Now()))
                    {
                        rPair.second.dwCount = 0;
                        rPair.second.dwFinishTime = 0;
                        Update2DB(rPair.second, eOpUpdate);
                    }
            }
        }
        vecExchangeInfo.push_back(rPair.second);
    }

}

UINT32 CExchangeShopMgr::CheckExchangeCond(UINT32 dwExchangeID, UINT32 dwCount)
{
    if(0 == dwCount)
    {
        LOG_CRI << "dwCount == 0";
        return eExchangeShop_CfgLimit;
    }
    CUser& rUser = _rPlayer.GetUser(); 
    SExchangeMallCFGPtr pExchangeMallCFG = GetItemByID(dwExchangeID);
    if(NULL == pExchangeMallCFG)
    {
        rUser.SendSysMsg(eMsgExchangeShopCfgLimit);
        return eExchangeShop_CfgLimit;
    }

    EMoneyType eType = (EMoneyType)pExchangeMallCFG->_MoneyType;

    // 不是帮贡，直接GameServer上操作
    if (eType != EMONEY_GUILDCONTRIB)
    {
        // 货币是否足够
        if(!rUser.CanSubMoney(eType, pExchangeMallCFG->_Price * dwCount))
        {
            rUser.SendSysMsg(eMsgExchangeShopMoneyLimit); // 货币不足
            return eExchangeShop_MoneyLimit;
        }
    }

    // 条件购买商品
    if(pExchangeMallCFG->_AvailableCon)
    {
        if(!CGetCondMgr::Instance().TestCond(rUser,pExchangeMallCFG->_AvailableCon))
        {
            rUser.SendSysMsg(eMsgExchangeShopCondLimit);
            return eExchangeShop_CondLimit;
        }
    }

    auto itr = _mapExchangeInfo.find(dwExchangeID);
    if(itr != _mapExchangeInfo.end())
    {
        // 可购买次数
        if(pExchangeMallCFG->_StoreNum != 0)
        {
            switch (pExchangeMallCFG->_Type)
            {
                case 7: // 帮派商城
                    if(Time::TheDay(0, itr->second.dwFinishTime) < Time::TheDay(0, Time::Now()))
                    {
                        itr->second.dwCount = 0;
                        itr->second.dwFinishTime = 0;
                        Update2DB(itr->second, eOpUpdate);
                    }
                    else
                    {
                        if((itr->second.dwCount + dwCount) > pExchangeMallCFG->_StoreNum )
                        {
                            rUser.SendSysMsg(eMsgExchangeShopCountLimit);
                            return eExchangeShop_CountLimit;
                        }
                    }
                    break;
                default:
                    if((itr->second.dwCount + dwCount) > pExchangeMallCFG->_StoreNum )
                    {
                        rUser.SendSysMsg(eMsgExchangeShopCountLimit);
                        return eExchangeShop_CountLimit;
                    }
            }
        }
    }

    // 道具ID
    SItemInfo* pItemCfg = CItemMgr::GetItemConfig(pExchangeMallCFG->_ItemId);
    if (!pItemCfg)
    {
        rUser.SendSysMsg(eMsgExchangeShopErrorItemID);
        return eExchangeShop_ErrorItemID;
    }

    TVecItemGenInfo vecItems;
    SItemGenInfo sItemGen;
    sItemGen.wItemID    = pExchangeMallCFG->_ItemId;
    sItemGen.dwCount    = pExchangeMallCFG->_ItemCount*dwCount;
    sItemGen.eBindType  = eBindGet;
    sItemGen.byQuality  = pItemCfg->oItemCfg._Quality;
    sItemGen.dwTimeID   = pItemCfg->oItemCfg._ItemTimeID;
    vecItems.push_back(sItemGen);

    // 背包空间是否足够
    if (!rUser.GetPack().CanAddItem(vecItems))
    {
        rUser.SendSysMsg(eMsgPackFullErr);
        return eExchangeShop_ErrorPack;
    }
    return eExchangeShop_Sucess;
}

