#pragma once
#include "Gather.h"
#include "Version.h"

class CGatherMgr : public CVersion
{
    public:
        static bool Init();
        static IGatherPtr CreateGather(UINT16 wGatherID);
        static SGatherCFGEx* GetGatherConfig(UINT16 wGatherID);
        static IGatherPtr CreateGather(UINT16 wGatherID,UINT8 byIndex);
        //static const SGatherCFGEx* GetGatherConfig(UINT16 wGatherID);
        static void  DestroyGather(IGather&);
        static IGatherPtr GetGatherByID(UINT32 dwInstanceID);
        static void TimerCheck(time_t tNow);
        static void ClearAllLua();
        static UINT64 GetVersion() {return _qwVersion;}
        static bool ReloadConfig(bool bReload = false);
        //释放内存
        static void Destroy();
    private:
        static map<UINT16, SGatherCFGEx> _mapID2GatherData;
        static map<UINT32, IGatherPtr> _mapID2Gather;
        static UINT32 _dwNextGatherInstID;
        static UINT64 _qwVersion;

};
