#ifndef _TIMESPRICEMGR_H__
#define _TIMESPRICEMGR_H_
#include "TimesPriceCFG.h"
#include <map>
class TimesPriceManager
{
    public:
        bool  Init();
        const STimesPriceCFG* GetConfigByTimes(UINT32 dwTimes);
        UINT32 GetCount();
    private:
        std::map<UINT32,STimesPriceCFG> _mapTimesPriceCFG;
};
extern TimesPriceManager g_TimesPriceManager;
#endif // _TIMESPRICEMANAGER_H__



