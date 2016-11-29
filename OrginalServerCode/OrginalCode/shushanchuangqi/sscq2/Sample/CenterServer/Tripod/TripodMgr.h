
#ifndef TRIPODMGR_H_
#define TRIPODMGR_H_

#include "stdafx.h"
#include "ProtoCommon.h" // fox TVecFtAttrMod
#include "StoveFireCFG.h"
#include "StoveFireLevelCFG.h"
#include "StovePropCFG.h"
#include "StoveAttrCFG.h"
#include "ItemProt.h"

using namespace NItemProt;

#define MAKE_STOVEIDKEY(I,L,R) (((I)<<16|(L)<<8)|(R))

struct SStoveFireCFGEx : public SStoveFireCFG
{
    void SetConfig(const SStoveFireCFG& rStoveFireCFG)
    {
        *(SStoveFireCFG*)this = rStoveFireCFG;
    }
    TVecItemCount _vecItemCost;
    SItemGenInfo _oItemGenInfo;
};

struct SStoveFireLevelCFGEx: public SStoveFireLevelCFG
{
    void SetConfig(const SStoveFireLevelCFG& rFireLevelCFG)
    {
        *(SStoveFireLevelCFG*)this = rFireLevelCFG;
    }
};

struct SStovePropCFGEx : public SStovePropCFG
{
    void SetConfig(const SStovePropCFG& rStoveCFG)
    {
        *(SStovePropCFG*)this = rStoveCFG;
    }
    TVecUINT16 _vecFireID;
};

struct SStoveAttrCFGEx : public SStoveAttrCFG
{
    void SetConfig(const SStoveAttrCFG& rStoveAttrCFG)
    {
        *(SStoveAttrCFG*)this = rStoveAttrCFG;
    }
};

class CTripodMgr
{
public:
    static bool Init();
    static bool LoadConfig(bool bReload = false);
    static bool ReLoadConfig(const string &);
    static SStoveFireCFGEx* GetStoveFireCfg(UINT16 wFireID);
    static SStoveFireLevelCFGEx* GetStoveFireLevelCfg(UINT8 byLvl);
    static SStovePropCFGEx* GetStovePropCfg(UINT8 byStoveID);
    static SStoveAttrCFGEx* GetStoveAttrCfg(UINT8 byStoveID, UINT8 byLvl, UINT8 byRank = 1);
    static bool IsMaxLevel(UINT8 byStoveID, UINT8 byLevel, UINT8 byRank);
    static bool TestTripodLevelUp(UINT8 byTripodID, UINT8& byLevel, UINT32& dwExp, UINT8 byRank = 1);
    static UINT32 GetFireLevelRandom();

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    static UINT64 _qwVersion;

private:
    static map<UINT16, SStoveFireCFGEx> _mapID2StoveFireCFG;
    static map<UINT8, SStoveFireLevelCFGEx> _mapID2StoveFireLevelCFG;
    static map<UINT8, SStovePropCFGEx> _mapID2StovePropCFG;
    static map<UINT32, SStoveAttrCFGEx> _mapID2StoveAttrCFG;
};

#endif // TRIPODMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

