#ifndef DAYACTIVITYMGR_H__
#define DAYACTIVITYMGR_H__

#include "stdafx.h"
#include "DayActivity.h"
#include "ItemProt.h"

using namespace NItemProt;


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

        void Destroy();

        bool GetTypeTime(NDayActProt::EActType eType, TSetUINT32& rsetDayTime);

        UINT8 GetForceOpenDay(NDayActProt::EActType eType);

    private:
        bool CheckConflictType(UINT32 dwActType);

        bool LoadTimerInfo(STimerInfo& oTimerInfo,string& strText);

        TMapDayActExPtr _mapDayActExPtr;

        TMapDayActEventPtr _mapDayActEventPtr; //配置表对应的实例

        TMapDayActivity _mapDayActivity; //实现类型对应的实例
        
        UINT32 _bInitCheck;
};
extern CDayActivityMgr g_DayActivityMgr;
#endif
