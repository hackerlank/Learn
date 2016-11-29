#ifndef ACTIONSWEEPING_H__
#define ACTIONSWEEPING_H__
#include "ActionBase.h"
#include "DungeonProt.h"
struct SDgnInfo;
class CActionSweeping:public CActionBase
{
    public:
        CActionSweeping(time_t ContinueTimer,UINT32 dwTimes,CActionManager *pManager):CActionBase(eACTION_SWEEPING,ContinueTimer,dwTimes,pManager)
    {
        _wDgnId = 0;
        _wMaxCount = dwTimes;
    }
        virtual void End();//这个动作结束时作的事情
        virtual void Break();//这个动作被终止时作的事情
        virtual void TimeOut();//一个计数到达时做的事情
        virtual bool CheckSpeedUp(UINT8 byOptions);
        virtual bool IsTimeOut(time_t tNow);
        void SetDgnId(UINT16 wDgnId){_wDgnId = wDgnId;}
        UINT16 GetDgnId() {return _wDgnId;}
        void  ClearDB(CPlayer& rPlayer);
        void  SaveDB(CPlayer& rPlayer);
        NDungeonProt::TVecSweepItem& GetSweepItem() { return _vecSweepItem; }
        UINT16 GetMaxTimes() { return _wMaxCount; }
        void   SetMaxTimes(UINT16 dwMaxCount) { _wMaxCount=dwMaxCount; }
 private:
        UINT16 _wDgnId;
        UINT16 _wMaxCount;
        NDungeonProt::TVecSweepItem _vecSweepItem;
};

#endif // ACTIONSWEEPING_H__
