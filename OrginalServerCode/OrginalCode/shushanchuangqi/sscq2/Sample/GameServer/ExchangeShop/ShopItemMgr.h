
#ifndef SHOPITEMMGR_H_
#define SHOPITEMMGR_H_
#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "MallProt.h"
using namespace NProtoCommon;
using namespace NRoleInfoDefine;
using namespace NMallProt;
typedef std::map<UINT32,SBuyItemDBInfo> TMapBuyItemDBInfo;
class CPlayer;

class CShopItemMgr:public CPoolObj<CShopItemMgr> 
{

public:
    CShopItemMgr(CPlayer& rPlayer);
    ~CShopItemMgr() {}
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(const SBuyItemDBInfo& rInfo, EDataChange eDataChanige = eOpUpdate);

    //查询已购买数量
    UINT32 GetBuyItemCountByInstID(UINT32 dwInstID);

    //增加已购买数量
    void AddBuyItemCountByInstID(UINT32 dwInstID,UINT32 dwCount);

    //清理购买数量
    void ClearItemCount();

    //获取玩家已兑换列表
    void GetShopItemList(TVecBuyItemInfo& vecBuyItemInfo);
  

private:
    CPlayer&  _rPlayer;
    TMapBuyItemDBInfo _mapBuyItemDBInfo;
};

#endif // SHOPITEMMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

