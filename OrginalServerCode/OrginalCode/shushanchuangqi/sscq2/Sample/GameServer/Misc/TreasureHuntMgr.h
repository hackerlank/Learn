
#ifndef TREASUREHUNTMGR_H_
#define TREASUREHUNTMGR_H_

#include "Singleton.h"
#include "SearchBuffCFG.h"
#include "SearchMapCFG.h"

using namespace NProtoCommon;

class CTreasureHuntMgr : public Singleton<CTreasureHuntMgr>
{
public:
    bool Init();
    bool LoadConfig(const string &);

    static SSearchBuffCFG* GetSearchBuffCFG(UINT8 byBuffID);
    static SSearchMapCFG* GetSearchMapCFG(UINT8 byMapID);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    static UINT64 _qwVersion;

private:
    static map<UINT8, SSearchBuffCFG> _mapID2SearchBuffCFG;
    static map<UINT8, SSearchMapCFG> _mapID2SearchMapCFG;
};

#endif // TREASUREHUNTMgr_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

