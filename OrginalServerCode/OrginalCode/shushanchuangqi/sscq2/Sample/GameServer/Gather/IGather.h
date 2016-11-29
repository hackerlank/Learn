#pragma once
#include "BaseObj.h"
#include "MapProtS.h"
#include "GatherCFG.h" 
#include "GatherProt.h"
#include "GatherCond.h"
#include "ItemProt.h"

using namespace NGatherProt; 
using namespace NItemProt;
class CPlayer;
struct SGatherCFGEx:public SGatherCFG
{
    public:
        enum EOtherType
        {
            EOTHER_ISTASK = 1 << 0,
        };
        SGatherCFGEx();
        SGatherCFGEx(const SGatherCFG& rCfg);
        bool CheckHasOtherType(EOtherType eType);
        void ResetLua(){_bCheckLua  = false;}
        UINT8 CanGagtherFromLua(CPlayer &rPlayer);
        void  FinishGather(CPlayer &rPlayer);
    public:
        UINT32 _dwOtherType;
        vector<CGatherCondBasePtr> _vecCond;
    private:
        void DoCheckLua();
    private:
        bool _bLuaHasCanGather;
        bool _bLuaHasFinishGather;
        bool _bCheckLua;
        
};
enum EGatherType
{
    eGatherType_Chest = 6, //天赐宝箱
};
class IGather : public CBaseObj
{
    friend class CGatherMgr;
    public:
    IGather(UINT16 wGatherID, UINT32 dwInstID, SGatherCFGEx& rGatherCFG,UINT64 qwVersion);
    virtual ~IGather();

    EObjType GetObjType() const { return eObjGather; }
    UINT16 GetGatherID() { return _wGatherID; }
    UINT32 GetInstID() { return _dwInstID; }

    bool IsGatherType(EGatherType eGatherType);

    virtual bool TaskCheck(CPlayer& rPlayer) { return true; }
    virtual EGatherResult CanConsume(CPlayer& rPlayer);
    virtual void Consume(CPlayer& rPlayer);
    virtual void Disappear();
    virtual void GetGatherAppear(SGatherAppear& rGatherAppear, UINT64 qwUsrID = 0);
    virtual EGatherResult GatherFinish(CPlayer& rPlayer,std::vector<SItemGenInfo>*pvecItems,TVecResource* pvecRes);//采集结算
    virtual EGatherResult CanGater(CPlayer& rPlayer,bool bIsFinish);
    virtual UINT32 AddGather(CPlayer& rPlayer){ return GetGatherConfig()._wGatherTimer;}
    virtual UINT32 GetReserverTimer(){return 0;}
    virtual void CancelGather(CPlayer& rPlayer){}
    virtual bool CanDisappear(){return true;}
    virtual void TimerCheck(time_t Now){}
    virtual void  CancelAll(EGatherResult eResult = eGatherCancel);
    bool  CanGatherTwoPerson();
    UINT8 byIndex();
    SGatherCFGEx& GetGatherConfig();
    protected:
    UINT16 _wGatherID;
    UINT32 _dwInstID;
    UINT8 _byIndex;
    protected:
    SGatherCFGEx* _pGatherCFGEx;
    UINT64 _qwVersion;
};
