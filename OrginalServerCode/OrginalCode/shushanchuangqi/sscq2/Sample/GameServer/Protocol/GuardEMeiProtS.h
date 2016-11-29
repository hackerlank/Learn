
#pragma once
#include "GuardEMeiProtSvr.h"

using namespace NGuardEMeiProt;

class CGuardEMeiProtS : public CGuardEMeiProtSvr 
{
public:
    
    //接收：请求守卫峨眉信息
	virtual bool OnRecv_ReqGEMInfo(
		shared_func<SReqGEMInfoAck>& fnAck //返回回调函数
	);

    //接收：请求购买守卫峨眉进入次数
	virtual bool OnRecv_BuyGEMEntryNum(
		shared_func<SBuyGEMEntryNumAck>& fnAck //返回回调函数
	);

    //接收：请求使用Buff
	virtual bool OnRecv_ReqUseBuff(
		UINT32 dwBuffID, //BuffID
		shared_func<SReqUseBuffAck>& fnAck //返回回调函数
	);
    
    //接收：请求重置关卡
	virtual bool OnRecv_ReqResetGEM(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqResetGEMAck>& fnAck //返回回调函数
	);

    //接收：请求守卫峨眉准备战斗信息
	virtual bool OnRecv_ReqGEMPrepareBattleInfo(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqGEMPrepareBattleInfoAck>& fnAck //返回回调函数
	);
    
    //接收：请求守卫峨眉战斗
	virtual bool OnRecv_ReqGEMBattle(
		UINT16 wMissionID, //关卡ID
		UINT32 dwBuffID, //BuffID
        EGEMBattleType eGEMBattleType, //战斗类型
		shared_func<SReqGEMBattleAck>& fnAck //返回回调函数
	);

    //接收：请求获取守卫峨眉扫荡开始
	virtual bool OnRecv_ReqSweepBegin(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqSweepBeginAck>& fnAck //返回回调函数
	);
    
    //接收：请求获取守卫峨眉扫荡结束(放弃扫荡)
	virtual bool OnRecv_ReqSweepEnd(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqSweepEndAck>& fnAck //返回回调函数
	);

};

extern CGuardEMeiProtS g_GuardEMeiProtS;

