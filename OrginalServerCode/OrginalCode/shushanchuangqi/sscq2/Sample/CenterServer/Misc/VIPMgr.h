
#ifndef VIPMGR_H_
#define VIPMGR_H_

#include "Singleton.h"
#include "VIPLevelCFG.h"

using namespace NProtoCommon;

struct SVIPLevelCFGEx : public SVIPLevelCFG
{
    void SetConfig(const SVIPLevelCFG& rVIPLevelCFG)
    {
        *(SVIPLevelCFG*)this = rVIPLevelCFG;
    }
};

class CVIPMgr : public Singleton<CVIPMgr>
{
public:
    bool Init();
    bool ReLoadConfig(const string &);

    static SVIPLevelCFGEx* GetVIPLevelCfg(UINT8 bylvl);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    static UINT64 _qwVersion;

private:
    static map<UINT8, SVIPLevelCFGEx> _mapID2VIPLevelCFG;
};

#define VIPMgr CVIPMgr::Instance()

#endif // VIPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

