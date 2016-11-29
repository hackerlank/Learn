#include "stdafx.h"
#include "ShopItemMgr.h"
#include "Player.h"
#include "User.h"
#include "Protocols.h"
#include "SysMsgDefine.h"

extern CMallProtS g_MallProtS; 
CShopItemMgr::CShopItemMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer)
{
    
}

bool CShopItemMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    for(size_t i = 0; i < rRoleDataInfo.vecBuyItemDBInfo.size(); ++i)
    {
       const SBuyItemDBInfo& rInfo = rRoleDataInfo.vecBuyItemDBInfo[i];
        _mapBuyItemDBInfo[rInfo.dwInstID]=rInfo;
    }
    return true;
}

void CShopItemMgr::Update2DB(const SBuyItemDBInfo& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeBuyItemLimit, eDataChange, strData);
}

UINT32 CShopItemMgr::GetBuyItemCountByInstID(UINT32 dwInstID)
{
    auto itr = _mapBuyItemDBInfo.find(dwInstID);
    if(itr == _mapBuyItemDBInfo.end())
    {
        return 0;
    }

    return itr->second.dwCount;
}

void CShopItemMgr::AddBuyItemCountByInstID(UINT32 dwInstID,UINT32 dwCount)
{
    SBuyItemDBInfo& rInfo = _mapBuyItemDBInfo[dwInstID];
    if(0 == rInfo.qwRoleID)
    {
        rInfo.qwRoleID = _rPlayer.GetRoleID();
        rInfo.dwInstID = dwInstID;
    }
    rInfo.dwCount += dwCount;

    //发送更新协议
    SBuyItemInfo rBuyItemInfo(dwInstID,rInfo.dwCount);
    _rPlayer.SendPkg(g_MallProtS.BuildPkg_BuyItemNotify(rBuyItemInfo));
    Update2DB(rInfo);
}

void CShopItemMgr::ClearItemCount()
{
    for(auto itr = _mapBuyItemDBInfo.begin(); itr != _mapBuyItemDBInfo.end(); itr++)
    {
        Update2DB(itr->second,eOpDel);
    }

    _mapBuyItemDBInfo.clear();

    //发送协议
    SBuyItemInfo rBuyItemInfo(0,0);
    _rPlayer.SendPkg(g_MallProtS.BuildPkg_BuyItemNotify(rBuyItemInfo));

}

//获取玩家已兑换列表
void CShopItemMgr::GetShopItemList(TVecBuyItemInfo& vecBuyItemInfo)
{
    for(auto itr = _mapBuyItemDBInfo.begin(); itr != _mapBuyItemDBInfo.end(); itr++)
    {
        vecBuyItemInfo.emplace_back(itr->second.dwInstID,itr->second.dwCount);
    }
}
 
