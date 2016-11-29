#ifndef DAYACTIVITYMGR_H__
#define DAYACTIVITYMGR_H__

#include "stdafx.h"
#include "DayActivity.h"
#include "FoundationCFG.h"
#include "ItemProt.h"

using namespace NItemProt;

//centerserver 删掉gameserver代码
/*
//蜀山基金
struct SFoundationCFGEx : public SFoundationCFG
{
    void SetConfig(const SFoundationCFG& rFoundationCFG)
    {
        *(SFoundationCFG*)this = rFoundationCFG;
    }

    map<UINT8, SItemGenInfo> _mapItemGen;
    map<UINT8, UINT8> _mapID2Level;     //成长基金用
};
*/
typedef std::vector<SDayActExPtr>  TVecDayActExPtr;
typedef std::map<UINT32,SDayActExPtr> TMapDayActExPtr;

typedef std::map<UINT16,CDayActivity*> TMapDayActivity;
typedef std::map<UINT32,CDayActEventPtr> TMapDayActEventPtr;

class CDayActivityMgr
{
    public:
        CDayActivityMgr(){ _bInitCheck = false; };
        bool Init();

        void OnMinuteCheck(time_t tNow);
        
        void TimerCheck(time_t tNow);

        void OpenActivity(UINT32 dwActID);

        SDayActExPtr GetDayActEx(UINT32 dwActID);

        CDayActEventPtr GetDayActEvent(UINT32 dwActID);

        CDayActivity* GetDayActivity(UINT32 dwActType);

        void GetActInfo(TVecActInfo& vecActInfo);
        //SFoundationCFGEx* GetFoundationCFG(UINT8 byType);

        void Destroy();

    private:
        //TVecDayActExPtr _vecDayActExPtr;
        TMapDayActExPtr _mapDayActExPtr;
        //配置表对应的实例
        TMapDayActEventPtr _mapDayActEventPtr;
        //实现类型对应的实例
        TMapDayActivity _mapDayActivity;
        
        UINT32 _bInitCheck;

        //map<UINT8,SFoundationCFGEx> _mapID2FoundationCFG;
};
extern CDayActivityMgr g_DayActivityMgr;
#endif
