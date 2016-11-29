
#ifndef TRIPODMGR_H_
#define TRIPODMGR_H_

#include "stdafx.h"
#include "StoveAttrCFG.h"

class CUser;

#define MAKE_STOVEIDKEY(I,L,R) (((I)<<16|(L)<<8)|(R))

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
    static SStoveAttrCFGEx* GetStoveAttrCfg(UINT8 byStoveID, UINT8 byLvl, UINT8 byRank = 1);
    static bool AddTripodAttr(UINT8 byStoveID, UINT8 byLvl, UINT8 byRank, TVecFloat& rvecAttr);
    static bool IsMaxLevel(UINT8 byStoveID, UINT8 byLevel, UINT8 byRank);
    static bool UpgradeTripod(UINT8 byStoveID, UINT8& byLevel, UINT8 byRank, UINT32& dwExp, bool bOneKey, CUserPtr pUser);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    static UINT64 _qwVersion;

private:
    static map<UINT32, SStoveAttrCFGEx> _mapID2StoveAttrCFG;
};

#endif // TRIPODMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

