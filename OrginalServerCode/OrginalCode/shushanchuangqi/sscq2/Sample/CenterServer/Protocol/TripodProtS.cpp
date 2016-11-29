
#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "UserMgr.h"
#include "TripodProtS.h"
#include "TripodManager.h"
#include "SysMsgDefine.h"
#include "FireSlots.h"
#include "VarDefine.h"

//接收：取得玩家所有九凝鼎信息
bool CTripodProtS::OnRecv_GetAllTripods(
    shared_func<SGetAllTripodsAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    TripodManager.SyncAppear(qwUsrID, 
            [fnAck, pUser]()
            {
                TripodManager.GetAllTripods(pUser, fnAck->oTripodData);
                fnAck->byShanfeng  = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarTripodShanfeng);
                fnAck->byHelpTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarTripodHelp);
                fnAck(true);
            });
    return true;
}

//接收：取得玩家所有九疑鼎的火种信息
bool CTripodProtS::OnRecv_GetAllFires(
    shared_func<SGetAllFiresAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    pUser->GetFireSlots().GetAllFires(fnAck->vecFires);
    return true;
}

//接收：取得其他玩家所有九疑鼎信息
bool CTripodProtS::OnRecv_GetTripodData(
    UINT64 qwRoleID, //玩家ID(九疑鼎所属者)
    shared_func<SGetTripodDataAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser || !qwRoleID)
		return false;
    TripodManager.SyncAppear(qwUsrID, 
            [fnAck, qwRoleID]()
            {
                CTripodSlots& tripodSlots = TripodManager.GetTripodSlots(qwRoleID);
                tripodSlots.GetAllTripods(fnAck->oTripodData);
                fnAck(true);
            });

    return true;
}

//接收：激活九疑鼎
bool CTripodProtS::OnRecv_ActiveTripod(
    UINT8 byTripodID, //九疑鼎ID
    shared_func<SActiveTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    fnAck->byTripodID = byTripodID;
    fnAck->eResult = TripodManager.ActiveTripod(pUser, byTripodID, fnAck);
    return true;
}

//接收：升级九疑鼎
bool CTripodProtS::OnRecv_UpgradeTripod(
    UINT8 byTripodID, //九疑鼎ID
    UINT8 byOneKey, //是否一键
    shared_func<SUpgradeTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    fnAck->eResult = TripodManager.UpgradeTripod(pUser, byTripodID, byOneKey, fnAck);
    return true;
}

//接收：九疑鼎起火(炼丹)
bool CTripodProtS::OnRecv_MakeFireTripod(
    UINT8 byTripodID, //九疑鼎ID
    UINT16 wFireID, //火种ID
    shared_func<SMakeFireTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    fnAck->eResult = TripodManager.MakeFireTripod(pUser, byTripodID, wFireID, fnAck);
    return true;
}

//接收：清除九疑鼎起火记录
bool CTripodProtS::OnRecv_ClearFireTripod(
    UINT8 byTripodID, //九疑鼎ID
    shared_func<SClearFireTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    fnAck->byTripodID = byTripodID;
    fnAck->eResult = TripodManager.ClearFireTripod(pUser, byTripodID);
    fnAck(true);
    TripodManager.Send_UpdateTripod(pUser);
    return true;
}

//接收：获取九疑鼎炼丹果实
bool CTripodProtS::OnRecv_GetTripodAward(
    UINT8 byTripodID, //九疑鼎ID
    shared_func<SGetTripodAwardAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    fnAck->eResult = TripodManager.GetTripodAward(pUser, byTripodID, fnAck);
    return true;
}

//接收：加速九疑鼎炼丹(道具入鼎)
bool CTripodProtS::OnRecv_SpeedTripod(
    UINT8 byTripodID, //九疑鼎ID
    const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
    shared_func<SSpeedTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser || vecItems.empty())
		return false;

    fnAck->eResult = TripodManager.SpeedTripod(pUser, byTripodID, vecItems, fnAck);
    return true;
}

//接收：扇火九疑鼎
bool CTripodProtS::OnRecv_AddTripodExtraSoul(
    UINT64 qwRoleID, //玩家ID(九疑鼎所属者)
    UINT8 byTripodID, //九疑鼎ID
    shared_func<SAddTripodExtraSoulAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;
    if (qwUsrID == qwRoleID)
    {
        fnAck->eResult = eTripodFailed;
        return false;
    }

    fnAck->eResult = TripodManager.AddTripodExtraSoul(pUser, qwRoleID, byTripodID, fnAck->vecTripods);
    fnAck(true);
    TripodManager.Send_UpdateTripod(pUser);
    return true;
}

//接收：散仙协助九疑鼎
bool CTripodProtS::OnRecv_FighterHelpTripod(
    UINT16 wFighterID, //自己的散仙ID
    UINT8 byPos, //协助位置
    shared_func<SFighterHelpTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    fnAck->eResult = TripodManager.FighterHelpTripod(pUser, wFighterID, byPos, fnAck);
    return true;
}

//接收：玩家协助九疑鼎
bool CTripodProtS::OnRecv_UserHelpTripod(
    UINT64 qwRoleID, //对方玩家ID
    UINT8 byPos, //协助位置
    shared_func<SUserHelpTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser || !qwRoleID || qwUsrID == qwRoleID)
		return false;

    fnAck->eResult = TripodManager.UserHelpTripod(pUser, qwRoleID, byPos, 
            [fnAck, qwRoleID, pUser](ETripodType eResult, SPlayerHelpInfo oPlayerHelp)
            {
                fnAck->eResult = eResult;
                fnAck->oPlayerHelp = oPlayerHelp;
                if (eResult != eTripodSucc)
                    fnAck(false);
                else
                {   // 通知九疑鼎所属者
                    CUserPtr pUser2 = CUserMgr::GetUserByUserID(qwRoleID);
                    if (pUser2)
                        TripodManager.Send_UpdateTripod(pUser2);
                    if (pUser)
                        TripodManager.Send_UpdateTripod(pUser);
                }
                fnAck(true);
                TripodManager.Send_UpdateTripod(pUser);
            });
    return true;
}

//接收：踢出九疑鼎协助者
bool CTripodProtS::OnRecv_ShotOffHelpTripod(
    UINT8 byPos, //协助位置(0,1,2)
    UINT8 byType, //0散仙 1玩家
    shared_func<SShotOffHelpTripodAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
		return false;

    fnAck->byPos  = byPos;
    fnAck->byType = byType;
    fnAck->eResult = TripodManager.ShotOffHelpTripod(pUser, byPos, byType);
    fnAck(true);
    TripodManager.Send_UpdateTripod(pUser);
    return true;
}

//接收：请求玩家九疑鼎的能被扇火、协助信息
bool CTripodProtS::OnRecv_GetTripodStatus(
    const TVecUINT64& vecRoleID, //好友玩家ID列表
    shared_func<SGetTripodStatusAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser || !vecRoleID.size())
		return false;

    TripodManager.GetTripodStatus(pUser, vecRoleID, fnAck->vecStatus);
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

