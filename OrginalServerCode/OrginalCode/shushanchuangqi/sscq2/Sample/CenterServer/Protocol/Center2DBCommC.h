#pragma once
#include "Center2DBCommClt.h"

using namespace NCenter2DBComm;

class CCenter2DBCommC : public CCenter2DBCommClt
{
public:
	///////////////////////////////////////////////////////////////////////////////
	void TimerCheck();
	bool IsDBInited() const { return _bDBInited; }
	CCenter2DBCommC() : _bDBInited(false), _bTimerClosed(false) { }

    //接收：返回所有玩家ID和名字
	virtual void OnRecv_SendAllUserIDAndName(
		UINT32 dwTotalSize, //总条数
		const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
	);
    
    //接收：返回所有公告
	virtual void OnRecv_SendAllNotice(
		const NPHPProt::TVecNotice& vecNotice //公告内容
	);

    //接收：返回请求斗剑信息
	virtual void OnRecv_SendAllArena(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
	);

    //接收：返回请求排行榜数据
    virtual void OnRecv_RankInitNotify(
            UINT32 dwCurSize, //已发送条数
            UINT32 dwTotalSize, //总条数
            const NRankProt::TVecRankInfo& vecRankInfo //更新信息
            );

	//接收：返回请求崇拜数据
	virtual void OnRecv_AdoreInitNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
	);

    //接收：返回所有九疑鼎信息
    virtual void OnRecv_SendAllTripod(
            UINT32 dwPageSize, //已发送条数
            UINT32 dwTotalSize, //总条数
            const NTripodProt::TVecTripodData& vecSendData //更新信息
    );

	//接收：返回所有九疑鼎的协助信息
	virtual void OnRecv_SendAllTripodHelper(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodHelp& vecSendData //更新信息
	);

	//接收：返回所有九疑鼎的动态信息
	virtual void OnRecv_SendAllTripodLog(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodLog& vecSendData //更新信息
	);

    //接收：平台参数加载返回
	virtual void OnRecv_PlatformParamInfoNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecUINT64& vecRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
	);
   //接收：返回查询结果
	virtual void OnRecv_SendResult2Cent(
		const SBaseCond& sCond, //查询条件
		const SBaseResult& sResult //查询结果
	);
	//接收：返回请求金船信息
	virtual void OnRecv_SendAllShip(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NShipProt::TVecPlayerShip& vecSendDate //更新信息
	) ;
   //接收：返回机器人天梯排行信息
	virtual void OnRecv_SendAllRobot(
		const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
	) ;


private:
	bool _bDBInited;
	bool _bTimerClosed;
};
