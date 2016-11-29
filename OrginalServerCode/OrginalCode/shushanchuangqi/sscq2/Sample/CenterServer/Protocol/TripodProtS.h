
#pragma once
#include "TripodProtSvr.h"

using namespace NTripodProt;

class CTripodProtS : public CTripodProtSvr
{
public:
	//接收：取得玩家所有九疑鼎信息
	virtual bool OnRecv_GetAllTripods(
		shared_func<SGetAllTripodsAck>& fnAck //返回回调函数
	);

	//接收：取得玩家所有九疑鼎的火种信息
	virtual bool OnRecv_GetAllFires(
		shared_func<SGetAllFiresAck>& fnAck //返回回调函数
	);

	//接收：取得其他玩家所有九疑鼎信息
	virtual bool OnRecv_GetTripodData(
		UINT64 qwRoleID, //玩家ID(九疑鼎所属者)
		shared_func<SGetTripodDataAck>& fnAck //返回回调函数
	);

	//接收：激活九疑鼎
	virtual bool OnRecv_ActiveTripod(
		UINT8 byTripodID, //九疑鼎ID
		shared_func<SActiveTripodAck>& fnAck //返回回调函数
	);

	//接收：升级九疑鼎
	virtual bool OnRecv_UpgradeTripod(
		UINT8 byTripodID, //九疑鼎ID
        UINT8 byOneKey, //是否一键
		shared_func<SUpgradeTripodAck>& fnAck //返回回调函数
	);

	//接收：九疑鼎起火(炼丹)
	virtual bool OnRecv_MakeFireTripod(
		UINT8 byTripodID, //九疑鼎ID
		UINT16 wFireID, ///火种ID
		shared_func<SMakeFireTripodAck>& fnAck //返回回调函数
	);

	//接收：清除九疑鼎起火记录
	virtual bool OnRecv_ClearFireTripod(
		UINT8 byTripodID, //九疑鼎ID
		shared_func<SClearFireTripodAck>& fnAck //返回回调函数
	);

	//接收：获取九疑鼎炼丹果实
	virtual bool OnRecv_GetTripodAward(
		UINT8 byTripodID, //九疑鼎ID
		shared_func<SGetTripodAwardAck>& fnAck //返回回调函数
	);

	//接收：加速九疑鼎炼丹(道具入鼎)
	virtual bool OnRecv_SpeedTripod(
		UINT8 byTripodID, //九疑鼎ID
		const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
		shared_func<SSpeedTripodAck>& fnAck //返回回调函数
	);

	//接收：扇火九疑鼎
	virtual bool OnRecv_AddTripodExtraSoul(
        UINT64 qwRoleID, //玩家ID(九疑鼎所属者)
		UINT8 byTripodID, //九疑鼎ID
		shared_func<SAddTripodExtraSoulAck>& fnAck //返回回调函数
	);

	//接收：散仙协助九疑鼎
	virtual bool OnRecv_FighterHelpTripod(
		UINT16 wFighterID, //自己的散仙ID
        UINT8 byPos, //协助位置
		shared_func<SFighterHelpTripodAck>& fnAck //返回回调函数
	);

	//接收：玩家协助九疑鼎
	virtual bool OnRecv_UserHelpTripod(
		UINT64 qwRoleID, //对方玩家ID
        UINT8 byPos, //协助位置
		shared_func<SUserHelpTripodAck>& fnAck //返回回调函数
	);

	//接收：踢出九疑鼎协助者
	virtual bool OnRecv_ShotOffHelpTripod(
		UINT8 byPos, //协助位置(0,1,2)
		UINT8 byType, //0散仙 1玩家
		shared_func<SShotOffHelpTripodAck>& fnAck //返回回调函数
	);

	//接收：请求玩家九疑鼎的能被扇火、协助信息
	virtual bool OnRecv_GetTripodStatus(
		const TVecUINT64& vecRoleID, //好友玩家ID列表
		shared_func<SGetTripodStatusAck>& fnAck //返回回调函数
	);

};
