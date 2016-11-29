
#ifndef VIPMGR_H_
#define VIPMGR_H_

#include "Singleton.h"
#include "VIPLevelCFG.h"
#include "VIPBaseCFG.h"

using namespace NProtoCommon;

struct SVIPLevelCFGEx : public SVIPLevelCFG
{
    void SetConfig(const SVIPLevelCFG& rVIPLevelCFG)
    {
        *(SVIPLevelCFG*)this = rVIPLevelCFG;
    }

    TVecItemGenInfo _vecItemDayPack;
    TVecItemGenInfo _vecItemLevelAward;
};

struct SVIPBaseCFGEx : public SVIPBaseCFG
{
    void SetConfig(const SVIPBaseCFG& rVIPBaseCFG)
    {
        *(SVIPBaseCFG*)this = rVIPBaseCFG;
    }
};


class CVIPMgr : public Singleton<CVIPMgr>
{
public:
    bool Init();
    bool LoadConfig(const string &);

    UINT8 CalcVIPLevel(UINT32);

    UINT8 GetVIPMaxLevel();

    static SVIPLevelCFGEx* GetVIPLevelCfg(UINT8 bylvl);
    static SVIPBaseCFGEx* GetVIPBaseCfg(UINT8 byTypeID);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    static UINT64 _qwVersion;

private:
    TVecUINT32 _vecRecharge;
    static map<UINT8, SVIPLevelCFGEx> _mapID2VIPLevelCFG;
    static map<UINT8, SVIPBaseCFGEx> _mapID2VIPBaseCFG;
};

#define VIPMgr CVIPMgr::Instance()

#endif // VIPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

