
#ifndef GUARDEMEIMGR_H_
#define GUARDEMEIMGR_H_

#include "Singleton.h"
#include "GuardEMeiCFG.h"
#include "GuardEMeiLevelCFG.h"
#include "EffectCFG.h"


using namespace NProtoCommon;

class CGuardEMeiMgr : public Singleton<CGuardEMeiMgr>
{
public:
    bool Init();
    bool LoadConfig(const string &);

    static SGuardEMeiCFG * GetGuardEMeiCFG(UINT16 wMissionID);
    static SGuardEMeiLevelCFG * GetGuardEMeiLevelCFG(UINT16 wMissionID, UINT16 wProgress);
    static SEffectCFG * GetEffectCFG(UINT16 wEffectID);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    static UINT64 _qwVersion;

private:
    static std::map<UINT16, SGuardEMeiCFG> _mapID2GuardEMeiCFG;
    static std::map<UINT16, std::map<UINT16, SGuardEMeiLevelCFG>> _mapID2GuardEMeiLevelCFG;
    static std::map<UINT16, SEffectCFG> _mapID2EffectCFG;
};

#endif // GUARDEMEIMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

