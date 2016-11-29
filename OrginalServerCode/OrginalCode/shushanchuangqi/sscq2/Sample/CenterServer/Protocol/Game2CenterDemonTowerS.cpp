#include "Game2CenterDemonTowerS.h"
#include "UserMgr.h"
#include "UserInfoMgr.h"
#include "DemonTowerMgr.h"

CGame2CenterDemonTowerS g_Game2CenterDemonTowerS;

//接收：玩家进入镇妖塔                 
void CGame2CenterDemonTowerS::OnRecv_OnEnterDemonTower( 
		const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
       )
{
    g_DemonTowerMgr.OnPlayerEnter(oDemonTowerEnterPlayer);
}

//接收：玩家离开镇妖塔
void CGame2CenterDemonTowerS::OnRecv_OnLeaveDemonTower(
		UINT64 qwUserID //玩家账号
	)
{
    g_DemonTowerMgr.OnPlayerLeave(qwUserID);
}

//接收：镇妖塔过关
void CGame2CenterDemonTowerS::OnRecv_OnPassDemonTower(
		UINT64 qwUserID, //玩家账号
		UINT16 wFloorID, //过关层数
        UINT16 wMonsterColor, //怪物颜色 
        const std::string& strMonsterName //封印怪物
	)
{
    g_DemonTowerMgr.OnPlayerPass(qwUserID,wFloorID,wMonsterColor,strMonsterName);
}

//接收：击败锁妖塔怪物
void CGame2CenterDemonTowerS::OnRecv_OnKillMonster(
	const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
)
{
    g_DemonTowerMgr.OnKillMonster(oDemonTowerPassPlayer);

}

//接收：19点重置事件
void CGame2CenterDemonTowerS::OnRecv_OnPlayerReset(
		UINT64 qwUserID //玩家账号
	)
{

    //g_DemonTowerMgr.GetDemonTowerInfo(qwUserID);
}

//接收：玩家进入下一层
void CGame2CenterDemonTowerS::OnRecv_OnPlayerEnterNextFloor(
	UINT64 qwUserID //玩家账号
)
{
    g_DemonTowerMgr.onPlayerEnterNextFloor(qwUserID);
}

//接收：玩家进入请求
void CGame2CenterDemonTowerS::OnRecv_PlayerEnterFloorRequest(
		UINT64 qwUserID, //玩家账号
		UINT32 dwFloorID //层数
	)
{
    g_DemonTowerMgr.PlayerEnter(qwUserID,dwFloorID);

}

	//接收：获取玩家被攻击信息列表
bool CGame2CenterDemonTowerS::OnRecv_GetAttackedLayerInfo(
	UINT64 qwUserID, //玩家账号
	const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList, //被攻击列表
	shared_func<SGetAttackedLayerInfoAck>& fnAck //返回回调函数
)
{
    for(const NDemonTower::SDemonToweAttackedInfo& oDemonToweAttackedInfo:oAttackedList)
    {
        NDemonTower::SDemonToweAttackedInfo oTmp(oDemonToweAttackedInfo);
        oTmp.dwLayerID = g_DemonTowerMgr.GetPlayerGuardLayerID(oDemonToweAttackedInfo.qwAtkRoleID);
        fnAck->oAttackedList.push_back(oTmp);
        fnAck->qwUserID = qwUserID;
    }
    return true;

}



