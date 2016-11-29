
#pragma once
#include "CommonDef.h"
#include "ProtoCommon.h"
#include "DayActivity.h"
using namespace NProtoCommon;
using namespace NProtoCommon;
class CPlayer;
struct SEnergyPriceCFG;
typedef shared_ptr<SEnergyPriceCFG> SEnergyPriceCFGPtr;
typedef std::vector<SEnergyPriceCFGPtr> TVecEnergyPriceCFGPtr;

class CEnergyActivity : public Singleton<CEnergyActivity>,public CDayActivity
{
public:
    CEnergyActivity():CDayActivity(eActTypeEnergy)
    {
    }
    virtual void OnEvent(SActEventData& oSActEventData) {}; 

    //是否是活动期间
    bool IsInProcess()
    {
        return GetStatus() == eDayActivityStatusProcess;
    }

    //是否已领奖
    bool IsHasTakedPrize(UINT32 dwLastTime)
    {
        if(dwLastTime >= _dwBeginTime && dwLastTime<= _dwEndTime)
        {
            return true;
        }
        return false;
    }

    virtual void OnReBegin()
    {
        //重新启动活动
        CDayActivity::OnAlarm();
    }
};

class CEnergyMgr 
{
    enum
    {
        eEnergy_BufferID = 4,
    };

public:
    CEnergyMgr(CPlayer& rPlayer);
    static bool CEnergyMgr_Init();

    //初始化
    void OnLoad();

    //购买行动力
    UINT32 BuyAction();

    //活动购买行动力次数
    UINT32 GetBuyActionCount();
    
    //获取购买价格 
    UINT32 GetBuyPrice();

    //刷新体力buffer,增加体力
    void TimerCheck(UINT32 dwNow);

    void AddAction(UINT32 dwAddAction,bool bCheckLimit=true);

    bool CanSubAction(UINT32 dwAddAction);

    bool SubAction(UINT32 dwAddAction,bool bNotify=true);

    void NotifyActionBuffer();

    void OnFirstLogin();

    void SetTakeFlag(UINT32 dwFlag);
    UINT32 GetTakeFlag();

    void OnTakeActionBuff();

private:
    static TVecEnergyPriceCFGPtr _vecEnergyPriceCFGPtr;
    CPlayer&  _rPlayer;
};


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

