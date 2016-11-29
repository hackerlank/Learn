
#ifndef EXCHANGEMALLMGR_H_
#define EXCHANGEMALLMGR_H_

#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "ExchangeShopProt.h"
#include "ExchangeMallCFG.h"

using namespace NProtoCommon;
using namespace NRoleInfoDefine;
using namespace NExchangeShopProt;

struct SExchangeMallCFG;

typedef std::shared_ptr<SExchangeMallCFG> SExchangeMallCFGPtr;
typedef std::map<UINT32,SExchangeMallCFGPtr> TMapExchangeMallCFGPtr;
typedef std::map<UINT32,ExchangeInfo> TMapExchangeInfo;

class CPlayer;

class CExchangeShopMgr:public CPoolObj<CExchangeShopMgr> 
{

public:
    CExchangeShopMgr(CPlayer& rPlayer);
    ~CExchangeShopMgr() {}
    static bool ExchangeInit();
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(const ExchangeInfo& rInfo, EDataChange eDataChange = eOpUpdate);
    SExchangeMallCFGPtr GetItemByID(UINT32 dwExchangeID);

    //兑换物品
    UINT32 ExchangeItem(UINT32 dwExchangeID,UINT32 dwCount, function<void(UINT32 dwRet)> func);

    //获取玩家已兑换列表
    void GetExchangedItemList(TVecExchangeInfo& vecExchangeInfo);

private:
    UINT32 CheckExchangeCond(UINT32 dwExchangeID, UINT32 dwCount);

private:
    CPlayer&  _rPlayer;
    TMapExchangeInfo _mapExchangeInfo;
    static TMapExchangeMallCFGPtr _mapExchangeMallCFGPtr;
};

#endif // EXCHANGEMALLMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

