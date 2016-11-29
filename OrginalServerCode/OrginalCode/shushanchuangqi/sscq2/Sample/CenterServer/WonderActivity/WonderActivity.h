#ifndef WONDERACTIVITY_H__ 
#define WONDERACTIVITY_H__
#include "stdafx.h"
#include "ActivityOperatingCFG.h"
#include "ActivityOperatingConfigCFG.h"
#include "WonderActivityProt.h"
#include "ActivityIDProt.h"

using namespace NActivityIDProt;
using namespace NWonderActivityProt;

struct SActID2Cond
{
    SActID2Cond()
    {
        wActID = 0;
        dwCond = 0;
    }
    UINT16 wActID;
    UINT32 dwCond;
};

struct SWActTime
{
    UINT16 wYear;
    UINT8  byMonth;
    UINT8  byDay;
    UINT8  byHour;
    UINT8  byMin;
    SWActTime()
    {
        wYear   = 0;
        byMonth = 0;
        byDay   = 0;
        byHour  = 0;
        byMin   = 0;
    }
};
UINT32 GetDayTime(const SWActTime&);
typedef shared_ptr<SItemConfig> SItemConfigPtr;
typedef std::vector<SItemConfigPtr> TVecItemConfigPtr; 
struct SWActPrizeCFG {
    UINT32 wHigh;
    UINT16 wLow;
    TVecItemConfigPtr vecItem;
    SWActPrizeCFG()
    {
        wHigh = 0;
        wLow  = 0;
    }
};

typedef shared_ptr<SWActPrizeCFG> SWActPrizeCFGPtr;
typedef std::vector<SWActPrizeCFGPtr> TVecPrizeCFGPtr;

struct SWActConfigCFG : public SActivityOperatingConfigCFG
{
    UINT16 wConfigID;
    UINT16 wType;
    UINT16 wMailID;
    UINT16 wMailContentID;
    TVecPrizeCFGPtr vecWActPrizePtr;

    void CopyFrom(SActivityOperatingConfigCFG &rActivityConfigCFG)
    {
        *((SActivityOperatingConfigCFG*)this) = rActivityConfigCFG;
    }

};
typedef shared_ptr<SWActConfigCFG> SWActConfigCFGPtr;

struct SWActCFGEx : public SActivityOperatingCFG 
{
    UINT16 wID;
    UINT16 wCfgID;
    UINT16 wType;
    UINT16 wOpenAct;
    SWActTime sAdvanceTime;
    SWActTime sBeginTime;
    SWActTime sEndTime;
    SWActTime sRetainTime;
    SWActCFGEx()
    {
        wID = 0;
        wCfgID = wType = wOpenAct = 0;
    }
    void CopyFrom(SActivityOperatingCFG &rActivityCFG)
    {
        *((SActivityOperatingCFG*)this) = rActivityCFG;
    }

};
typedef shared_ptr<SWActCFGEx> SWActCFGExPtr;
struct SWonderPrizeKey
{
    SWonderPrizeKey(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond)
        : qwRoleID(qwRoleID),wActID(wActID),wCond(wCond) {}

    UINT64  qwRoleID;
    UINT16  wActID;
    UINT32  wCond;

    bool operator < (const SWonderPrizeKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        if(wCond != sk.wCond)
            return wCond < sk.wCond;
        return wActID < sk.wActID;
    }
};
typedef std::map<SWonderPrizeKey,SWonderPrize2DB> TMapID2PrizeState;

class CWonderActivity
{
    public:
        CWonderActivity(UINT16 wActType);
        virtual ~CWonderActivity(){};
        
        UINT16           GetActID() { return _wActID; };
        void             SetActID(UINT16 wActID) { _wActID = wActID; }
        bool             OnInit();
        string           GetActName();

        UINT16           GetActType() { return _wActType; }
        void             SetActType(UINT16 wActType){ _wActType = wActType; }
        bool             OnMail();

        SWActCFGExPtr    GetCFG();
        EWActState       GetState() { return _eActState; }
        void             SetState(EWActState eActState){ _eActState = eActState ;}
        void             UpdateState();
        virtual void            GMOpen(SWActTime& sAdv,SWActTime sBegin,SWActTime sEnd,SWActTime sRetain);
        UINT32                  GetMaxRoleCount(UINT32 wCond);
        TVecItemConfigPtr       GetPrize(UINT32 wConds);
        void                    GetConds(TVecUINT32& vecConds);
        
        //活动状态
        virtual void     OnAdvance();
        virtual void     OnBegin();
        virtual void     OnEnd();
        virtual void     OnRetain();
        virtual void     OnReAdvance();
        virtual void     OnReBegin();
        virtual void     OnReRetain();
        virtual void     OpenIcon(bool bNotify) { };

        virtual void     GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet){ }
        virtual bool     SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID){ return true; }
        virtual void     TakePrize(UINT64 &qwPlayerID,UINT32 wCond){ }
        virtual void     GetStateByRoleID(UINT64 qwRoleID,UINT16,TVecWonderPrize2DB& sResult){ }
        virtual bool     GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer){ return true; }
        virtual bool     CheckConds(UINT32 dwCond){ return true; }
        virtual void     SpecialProcess();

    protected:
        UINT16 _wActID;
        UINT32 _dwAdvanceTime;
        UINT32 _dwBeginTime;
        UINT32 _dwEndTime;
        UINT32 _dwRetainTime;
        UINT16 _wActType;
        UINT16 _wCfgID;
        EWActState _eActState;
        SWActCFGExPtr _pWActEx;
};
typedef shared_ptr<CWonderActivity> CWonderActivityPtr;

//活动开启动作操作
class CWonderActivityEvent
{
 public:
    CWonderActivityEvent(UINT16 wActID,UINT16 wActType):
        _wActID(wActID),
        _wActType(wActType)
    {


    };
    ~CWonderActivityEvent(){};
    void OnInit();
    bool IsOpenDay();
    bool IsInitTime(time_t tNow);
    void GMOpen();
    void CheckStatus();
    SWActCFGExPtr GetCFG();
    UINT16 GetActID(){ return _wActID; }

 public:
    UINT16 _wActID;
    UINT16 _wActType;
};
typedef shared_ptr<CWonderActivityEvent> CWonderActivityEventPtr;

#endif
 
