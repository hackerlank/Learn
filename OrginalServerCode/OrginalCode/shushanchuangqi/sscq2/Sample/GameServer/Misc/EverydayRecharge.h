#ifndef _EVERYDAYRECHARGE__
#define _EVERYDAYRECHARGE__
#include "Protocols.h"
#include "MiscProtS.h"
struct AwardEveryDay
{
    UINT16 wLimit;
    NItemProt::TVecItemGenInfo vecItem;
    AwardEveryDay():wLimit(0)
    {
    }
};
class CUser;
class CEveryDayRechargeMgr
{
    public:
        CEveryDayRechargeMgr();
        bool Init();
        void CheckIconIsOpen(CUser &rUser,bool bZero);
        void GetAward(CUser &rUser,NMiscProt::EEveryDayReChargeAward & eResult);
        void SetDragonState(bool bOpen);
    private:
        UINT32 GetDate();
        bool CheckSystemOpen();
        const AwardEveryDay* GetAwardByDate();
    private:
        map<UINT32,AwardEveryDay> _mapDayAward;
        bool _bOpen;
        bool _bGetDragon;

};
extern CEveryDayRechargeMgr g_EveryDayRechargeMgr ;
#endif

