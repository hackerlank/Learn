#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "UDPLog.h"
#include "UserMgr.h"
#include "Game2CenterLogS.h"
#include "DCLogger.h"
using namespace NProtoCommon;

//接收：log注册记录
void CGame2CenterLogS::OnRecv_LogRegister(
	UINT64 qwUsrID, //帐号ID
	const TVecString& vecStrInfo //用户登陆平台信息
	)
{
    LOG_INF<<"LogRegister:"<<qwUsrID;
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
		pUDPLog->LogMsg_Refer(vecStrInfo);
}

//接收：log登陆
void CGame2CenterLogS::OnRecv_LogUserLogin(
	UINT64 qwUsrID, //帐号ID
//	UINT32 dwDiamond, //钻石
//	UINT32 dwGiftCoin, //礼金
	const TVecString& vecStrInfo //用户登陆平台信息
	)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;
	//pUser->SetGiftCoin(dwGiftCoin);
	//pUser->SetDiamond(dwDiamond);

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
		pUDPLog->LogMsg_Login(vecStrInfo);
    CDCLOGGER().Login(pUser);
}

//接收：log登出
void CGame2CenterLogS::OnRecv_LogPlayerLogout(
	UINT32 dwTime, //时间
	UINT64 qwUsrID //帐号ID
	)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
		pUDPLog->LogMsg_LoginOut(dwTime);
    CDCLOGGER().Logout(pUser);
}

//接收：log玩家充值
void CGame2CenterLogS::OnRecv_LogRecharge(
    UINT64 qwUsrID, //帐号ID
    const std::string& strUdp1, //udpLog参数1(平台传来的)
    const std::string& strUdp2, //udpLog参数2(平台传来的)
    UINT32 dwGold //仙石数量
)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser || !dwGold)
		return;

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
	{
	    pUDPLog->LogMsg_Pay(strUdp1, strUdp2, dwGold);
	}
}

//接收：log金钱变化
void CGame2CenterLogS::OnRecv_LogMoneyChange(
	UINT64 qwUsrID, //帐号ID
    EOpType eType, //类型
	const TVecUserMoneyChange& vecMoney//货币
	)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	for(size_t i = 0;i < vecMoney.size();i++)
	{
		const SUserMoneyChange& rMoney = vecMoney[i];
		switch(rMoney.eMoneyType)
		{
		case EMONEY_GOLD: //仙石
			{
				//pUser->ChangeDiamond(rMoney.dwValue);
				CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
				if(NULL != pUDPLog)
					pUDPLog->LogMsg_Currency(eType, rMoney.wFromTo, rMoney.dwValue);
			}
			break;
		case EMONEY_COUPON: //礼券
			{
				//pUser->ChangeGiftCoin(rMoney.dwValue);
				if(rMoney.dwValue > 0) //只记录礼金消耗记录
				{
					CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
					if(NULL != pUDPLog)
						pUDPLog->LogMsg_Currency(eType, rMoney.wFromTo, 0);
				}
			}
			break;
		default:
			break;
		}
	}
}

//接收：log道具变化
void CGame2CenterLogS::OnRecv_LogItemChange(
	UINT64 qwUsrID, //帐号ID
    EOpType eType, //类型
	const TVecUserItemChange& vecItem //道具
	)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
	{
		for(size_t i = 0;i < vecItem.size();i++)
		{
			const SUserItemChange& rItem = vecItem[i];
			pUDPLog->LogMsg_Props(eType, rItem.wItemID, rItem.dwCount, rItem.dwPrice);
		}
	}
}

//接收：log新手引导变化
void CGame2CenterLogS::OnRecv_LogGuideChange(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //引导类 load或guide
	const std::string& strStep //引导ID
	)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
		pUDPLog->LogMsg_Guide(strCategory, strStep);
}

//接收：log自定义行为变化
void CGame2CenterLogS::OnRecv_LogActiveChange(
	UINT64 qwUsrID, //帐号ID
	const std::string& strCategory, //行为分类
	const std::string& strAction, //用户行为
	UINT32 dwCount //
	)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
		pUDPLog->LogMsg_Act(strCategory, strAction, dwCount);
}

//接收：log自定义行为变化
void CGame2CenterLogS::OnRecv_LogAct(
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		const std::string& strParam3, //用户行为
		const std::string& strParam4, //用户行为
		const std::string& strParam5, //用户行为
		const std::string& strParam6, //用户行为
		UINT32 dwCount //
	)
{
	NetMgr.SetCurUsrID(qwUsrID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(NULL == pUser)
		return;

	CUDPLogPtr pUDPLog = CUDPLogMgr::GetUDPLog(*pUser);
	if(NULL != pUDPLog)
        pUDPLog->UdpLog(strCategory.c_str(), strAction.c_str(), strParam3.c_str(), strParam4.c_str(),strParam5.c_str(),strParam6.c_str(), "act", dwCount);

}

//接收：log服务器变化
void CGame2CenterLogS::OnRecv_LogServerInfo(
	UINT32 dwTime, //时间
	const std::string& strType, //记录类型
	const std::string& strSubType, //记录分类型
	UINT32 dwNum //记录数据
	)
{
	CUDPLogMgr::UdpLog( strType.c_str(), strSubType.c_str(), NumberToString(dwTime).c_str(), NumberToString(dwNum).c_str(), "", "", "ser");
}
