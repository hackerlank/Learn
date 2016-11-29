#pragma once
#include "DungeonProtSvr.h"

using namespace NDungeonProt;

class CDungeonProtS : public CDungeonProtSvr
{
public:
	//接收：扫荡
	virtual bool OnRecv_Sweeping(
		UINT16 wDgnID, //副本ID
		UINT16 wCount, //次数
		UINT8 byOptions, //选项, 1位为gold，2位为key
		shared_func<SSweepingAck>& fnAck //返回回调函数
		);

	//接收：加速扫荡
	virtual bool OnRecv_SweepingSpeedUp(
		UINT8 byOptions, //0为使用礼金，1为使用金币
		shared_func<SSweepingSpeedUpAck>& fnAck //返回回调函数
		);

	//接收：取消扫荡
	virtual bool OnRecv_CancelSweeping(
		shared_func<SCancelSweepingAck>& fnAck //返回回调函数
		);

	//接收:进入单人副本
	virtual bool OnRecv_EnterPlayerDungeon(
		UINT16 wDgnID, //副本ID
		shared_func<SEnterPlayerDungeonAck>& fnAck //返回回调函数
	);

	//接收：离开单人副本
	virtual bool OnRecv_LeavePlayerDungeon(
		shared_func<SLeavePlayerDungeonAck>& fnAck //返回回调函数
	);

    //接收：客户端确认领奖
	virtual bool OnRecv_NotifyAcceptDgnAward(
		UINT64 qwDgnID, //副本唯一实例ID
		shared_func<SNotifyAcceptDgnAwardAck>& fnAck //返回回调函数
	);
    //接收：查询副本星级
	virtual bool OnRecv_GetAllDgnInfo(
		shared_func<SGetAllDgnInfoAck>& fnAck //返回回调函数
	) ;
   //接收：客户端查询扫荡信息
	virtual bool OnRecv_GetDgnSweepingInfo(
		shared_func<SGetDgnSweepingInfoAck>& fnAck //返回回调函数
	) ;
	//接收：查询副本进度和星级
    virtual void OnRecv_GetDgnProcessAndStar(
	) ;
    //接收：副本中玩家复活
	virtual void OnRecv_ReliveInDgn(
	) ;
    //接收：获取角色Team信息
	virtual void OnRecv_GetTeamInfo(
	);
	//接收：购买英雄副本次数
	virtual bool OnRecv_BuyHeroDgnTimes(
		UINT16 wDgnID, //副本ID
		shared_func<SBuyHeroDgnTimesAck>& fnAck //返回回调函数
	);
	//接收：购买历险副本次数
	virtual bool OnRecv_BuyLiXianDgnTimes(
		shared_func<SBuyLiXianDgnTimesAck>& fnAck //返回回调函数
	);
	//接收：查询副本星级领奖状态
	virtual bool OnRecv_GetDgnStarAwardInfo(
		shared_func<SGetDgnStarAwardInfoAck>& fnAck //返回回调函数
	);
	//接收：领取副本星级奖励
	virtual bool OnRecv_GetDgnStarAward(
		UINT16 wStarID, //领奖ID
		shared_func<SGetDgnStarAwardAck>& fnAck //返回回调函数
	);



    void  SystemMsgNotify(EDungeonResult result,UINT64 qwUserId =0 );
    

};
