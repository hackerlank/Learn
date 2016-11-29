#pragma once
#include "Game2CenterLogSvr.h"

using namespace NGame2CenterLog;
using namespace NProtoCommon;

class CGame2CenterLogS : public CGame2CenterLogSvr
{
public:
	//接收：log注册记录
	virtual void OnRecv_LogRegister(
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
		);

	//接收：log登陆
	virtual void OnRecv_LogUserLogin(
		UINT64 qwUsrID, //帐号ID
//		UINT32 dwDiamond, //钻石
//		UINT32 dwGiftCoin, //礼金
		const TVecString& vecStrInfo //用户登陆平台信息
		);

	//接收：log登出
	virtual void OnRecv_LogPlayerLogout(
		UINT32 dwTime, //时间
		UINT64 qwUsrID //帐号ID
		);

	//接收：log玩家充值
	virtual void OnRecv_LogRecharge(
		UINT64 qwUsrID, //帐号ID
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		UINT32 dwGold //仙石数量
	);

	//接收：log金钱变化
	virtual void OnRecv_LogMoneyChange(
		UINT64 qwUsrID, //帐号ID
        EOpType eType, //类型
		const TVecUserMoneyChange& vecMoney//货币
		);

	//接收：log道具变化
	virtual void OnRecv_LogItemChange(
		UINT64 qwUsrID, //帐号ID
        EOpType eType, //类型
		const TVecUserItemChange& vecItem //道具
		);

	//接收：log新手引导变化
	virtual void OnRecv_LogGuideChange(
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //引导类 load或guide
		const std::string& strStep //引导ID
		);

	//接收：log自定义行为变化
	virtual void OnRecv_LogActiveChange(
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		UINT32 dwCount //
		);
	
    //接收：log自定义行为变化
	virtual void OnRecv_LogAct(
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		const std::string& strParam3, //用户行为
		const std::string& strParam4, //用户行为
		const std::string& strParam5, //用户行为
		const std::string& strParam6, //用户行为
		UINT32 dwCount //
	);

	//接收：log服务器变化
	virtual void OnRecv_LogServerInfo(
		UINT32 dwTime, //时间
		const std::string& strType, //记录类型
		const std::string& strSubType, //记录分类型
		UINT32 dwNum //记录数据
		);
};

