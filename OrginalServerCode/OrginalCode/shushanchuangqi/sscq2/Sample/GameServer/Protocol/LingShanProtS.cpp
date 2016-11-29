#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "LingShanProtS.h"
#include "ZhanQiMgr.h"
#include "GameNetMgr.h"

CLingShanProtS g_LingShanProtS;
//接收：获取状态（回StatusNotify通知）
void CLingShanProtS::OnRecv_GetStatus(
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return ;

    g_ZhanQiMgr.OnGetPlayerStatus(pPlayer);

}

//接收：活动报名
bool CLingShanProtS::OnRecv_Reg(
	shared_func<SRegAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnPlayerReg(pPlayer);
 
    return true;
}

//接收：当前棋盘状态
bool CLingShanProtS::OnRecv_GetMatchInfo(
	shared_func<SGetMatchInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnGetMatchInfo(*pPlayer,fnAck);
 
    return true;
}

//接收：获取自己的比赛信息
bool CLingShanProtS::OnRecv_GetMathSelInfo(
	shared_func<SGetMathSelInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnGetMathSelInfo(*pPlayer,fnAck);

    return true;
}

	//接收：更换模型信息
bool CLingShanProtS::OnRecv_ChangeModel(
    UINT32 dwModelID, //模型id
	shared_func<SChangeModelAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnChangeModel(*pPlayer,dwModelID,fnAck->dwModelID);

    return true;
}

//接收：移动选择
bool CLingShanProtS::OnRecv_MoveSelect(
	UINT16 wPos, //位置
	shared_func<SMoveSelectAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnPlayerMove(*pPlayer,wPos,fnAck->dwCdTime);
    return true;
}
//接收：获取活动信息
bool CLingShanProtS::OnRecv_GetActInfo(
	shared_func<SGetActInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnGetActInfo(*pPlayer,fnAck);
    return true;
}
//接收：聊天
bool CLingShanProtS::OnRecv_Chat(
    const std::string& strChatMsg, //聊天内容 
	shared_func<SChatAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnChat(*pPlayer,strChatMsg);
 
    return true;
}
//接收：获取房间信息
bool CLingShanProtS::OnRecv_GetRoomList(
	shared_func<SGetRoomListAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnGetRoomList(*pPlayer,fnAck->vecRoomInfo);
    return true;
 
}

//接收：进入参观房间
bool CLingShanProtS::OnRecv_EnterVisitRoom(
	UINT16 wRoomID, //房间id
	shared_func<SEnterVisitRoomAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnEnterVisitRoom(*pPlayer,wRoomID);
 
    return true;
}

//接收：离开参观房间
bool CLingShanProtS::OnRecv_LeaveVisitRoom(
	shared_func<SLeaveVisitRoomAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnLeaveVisitRoom(*pPlayer);
 
    return true;
}
//接收：获取动画播放信息
bool CLingShanProtS::OnRecv_GetPlayMovieInfo(
	shared_func<SGetPlayMovieInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
 
    fnAck->eRet = (ELingShanOP)g_ZhanQiMgr.OnGetPlayMovieInfo(*pPlayer,fnAck);
 
    return true;
}

