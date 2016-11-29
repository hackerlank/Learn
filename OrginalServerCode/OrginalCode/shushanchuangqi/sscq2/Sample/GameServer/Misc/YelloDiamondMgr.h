
#ifndef YelloDiamondMGR_H_
#define YelloDiamondMGR_H_

#include "Singleton.h"
#include "YelloDiamondCFG.h"
#include "YelloDiamondProt.h"
#include "ItemProt.h"
#include "User.h"
#include "VarDefine.h"

using namespace NVarDefine;
using namespace NItemProt;
using namespace NYelloDiamondProt;

struct SYDCFGEx : public SYelloDiamondCFG
{
    EBagType eBagType;
    UINT8 byLevel;
    TVecItemGenInfo vecItems;
    TVecItemGenInfo vecItemEx;

    void SetConfig(const SYelloDiamondCFG& rYelloDiamondCFG)
    {
        *(SYelloDiamondCFG*)this = rYelloDiamondCFG;
    }
};
typedef shared_ptr<SYDCFGEx> SYDCFGExPtr;
typedef vector<SYDCFGExPtr> TVecCFGExPtr;
struct SYDParam
{
    EBagType eBagType;
    UINT8  byYDLevel;
    UINT16  wUserLevel;
    UINT64  qwUserID;

    SYDParam()
    {
        eBagType = EBagType_eNone;
        qwUserID = 0;
        byYDLevel = 0;
        wUserLevel = 0;
    }
};
class CYelloDiamondMgr : public Singleton<CYelloDiamondMgr>
{
public:

    typedef shared_ptr<SYDParam> SYDParamPtr;
    typedef  EOpResult (CYelloDiamondMgr::*YDFun)(SYDParamPtr pYDParam);
    typedef  map<EBagType,YDFun> TMapID2YDFun;
public:
    bool Init();
    bool LoadConfig(bool bReload = false);
    EOpResult Register();
    EOpResult GainYDBag(CUser &rUser, EBagType eBagType, UINT16 &dLevel); 
    EOpResult OnModifyYDLevel(CUser&, UINT8&);
    bool GetYDInfo(CUser&, SYDInfo&);
    UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    // 礼包处理函数
    EOpResult GainYDDayBag(SYDParamPtr);
    EOpResult GainYDNewBag(SYDParamPtr);
    EOpResult GainYDYearBag(SYDParamPtr);
    EOpResult GainYDLuxuryBag(SYDParamPtr);
    EOpResult GainYDGrowBag(SYDParamPtr);
    EOpResult GainYDHorseBag(SYDParamPtr);
    EOpResult HasGainBag(CUser&, EBagType,UINT16&);
    TMapID2YDFun _mapID2YDFun;
    TVecCFGExPtr _vecCFGExPtr;
    UINT64 _qwVersion;
};
#define YelloDiamondMgr CYelloDiamondMgr::Instance()

#endif // YelloDiamondMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

