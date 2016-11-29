
#include "GodMonsterProtS.h"
#include "GodMonsterProt.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
//#include "GodMonster.h"
#include "User.h"
#include "UserMgr.h"
#include "GodMonsterMgr.h"

CGodMonsterProtS g_GodMonsterProtS;

//接收：打开活动面板
bool CGodMonsterProtS::OnRecv_OnEnter(
		shared_func<SOnEnterAck>& fnAck //返回回调函数
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    g_GodMonsterMgr.Enter(*pUser,fnAck->sInfo);
    return true;
}
//接收：喂养
bool CGodMonsterProtS::OnRecv_OnFeed(
		UINT8 byType, //0: 表示喂养一次，1: 表示一键喂养
		shared_func<SOnFeedAck>& fnAck //返回回调函数
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return false;
    }
    if(byType == 0)
        fnAck->eResult = g_GodMonsterMgr.OneFeed(*pUser,1);
    else if(byType == 1)
        fnAck->eResult = g_GodMonsterMgr.AllFeed(*pUser);
    return true;
}
//接收：领奖
bool CGodMonsterProtS::OnRecv_TakePrize(
		EMonsterPrizeType ePrizeType, //奖励类型
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	)
{

    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        fnAck->eResult = EMonsterResult_Err;
        return false;
    }
    fnAck->eResult = g_GodMonsterMgr.TakePrize(*pUser,ePrizeType);
    return true;
}

//接收：购买限购礼包
bool CGodMonsterProtS::OnRecv_BuyPkg(
		UINT16 wIndex, //礼包ID
		UINT8 byCount, //数量
		shared_func<SBuyPkgAck>& fnAck //返回回调函数
	)
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        fnAck->eResult = EMonsterResult_Err;
        return false;
    }
    fnAck->eResult = g_GodMonsterMgr.Buy(*pUser,wIndex,byCount);
    return true;
}

//接收：表扬
void CGodMonsterProtS::OnRecv_OnPraise(
		UINT64 qwRoleID //玩家
	) 
{
    UINT64 ID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(ID);
    if(NULL == pUser)
    {
        return;
    }
    g_GodMonsterMgr.OnPraise(*pUser,qwRoleID);
}

//接收：督促
void CGodMonsterProtS::OnRecv_OnUrge(
		UINT64 qwRoleID //玩家
	) 
{
    UINT64 ID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(ID);
    if(NULL == pUser)
    {
        return ;
    }
    g_GodMonsterMgr.OnUrge(*pUser,qwRoleID);
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

