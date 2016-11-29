#pragma once
#include "IGather.h"
const UINT16 FoverNUM = -1;//永远存在
class CGather : public IGather, public CPoolObj<CGather>
                
{
	friend class CGatherMgr;
public:
	DEF_NEW_DELETE(CGather);
	CGather(UINT16 wGatherID, UINT32 dwInstID, SGatherCFGEx& rGatherCFG,UINT64 qwVersion);
	virtual ~CGather();

	virtual bool TaskCheck(CPlayer& rPlayer);	
	virtual EGatherResult CanConsume(CPlayer& rPlayer);
	virtual void Consume(CPlayer& rPlayer);
    virtual EGatherResult CanGater(CPlayer& rPlayer,bool bIsFinish);
    virtual UINT32 AddGather(CPlayer& rPlayer);
    virtual void CancelGather(CPlayer& rPlayer);
    virtual bool CanDisappear();
    virtual void TimerCheck(time_t Now);
    virtual UINT32 GetReserverTimer(CPlayer& rPlayer);
    virtual void GetGatherAppear(SGatherAppear& rGatherAppear,UINT64 qwUserId =0);
    virtual void  CancelAll(EGatherResult eResult = eGatherCancel);
    //发采集改变消息
    void SendGatherChangeInfo();
    //发送采集中断消息
    void SendCancelGather(CPlayer& rPlayer,EGatherResult eResult);
    //注册采集
    void SetPlayerGather(CPlayer& rPlayer);
    //清除采集
    void ClearPlayerGather(CPlayer& rPlayer);
    UINT16 GetRemCount(){return _wRemCount;}

protected:
	vector<UINT16>* _pVecTaskID;
	UINT16 _wRemCount;//剩余数量
    UINT16 _wInGathering;//正在采集中的数量
    map<UINT64,UINT32> _mapGaterPlayer;
};

