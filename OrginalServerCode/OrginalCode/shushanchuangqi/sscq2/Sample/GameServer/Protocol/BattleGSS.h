#ifndef _BATTLE_GSS_H_
#define _BATTLE_GSS_H_
#include "BattleGSSvr.h"
using namespace NBattleGS;

class CBattleGSS : public CBattleGSSvr
{
public:
	//接收：请求战斗
	virtual void OnRecv_BattleReq(
		UINT64 qwDefenseID //防守ID
	);

	//接收：请求战报
	virtual void OnRecv_BattleReportReq(
		UINT64 qwReportID, //请求战报ID
		UINT64 qwMasterID //视角角色ID
	);
    virtual void OnRecv_FinishBattleReport(
		UINT64 qwReportID //请求战报ID
	);

};


#endif // _BATTLE_GSS_H_
