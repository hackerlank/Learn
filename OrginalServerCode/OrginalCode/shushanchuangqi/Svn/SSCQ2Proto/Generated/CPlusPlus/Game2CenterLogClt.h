/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterLog.h
//  Purpose:      GameServer到CenterServer的数据中心log协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterLog.h"

namespace NGame2CenterLog
{

//协议类：GameServer到CenterServer的数据中心log协议
class CGame2CenterLogClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：log注册记录
	bool Send_LogRegister( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	);
	bool SendSvr_LogRegister(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	);
	std::string& BuildPkg_LogRegister( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	);

	//发送：log登陆
	bool Send_LogUserLogin( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	);
	bool SendSvr_LogUserLogin(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	);
	std::string& BuildPkg_LogUserLogin( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	);

	//发送：log登出
	bool Send_LogPlayerLogout( //发送给当前协议处理的服务器
		UINT32 dwTime, //时间
		UINT64 qwUsrID //帐号ID
	);
	bool SendSvr_LogPlayerLogout(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwTime, //时间
		UINT64 qwUsrID //帐号ID
	);
	std::string& BuildPkg_LogPlayerLogout( //只组包不发送
		UINT32 dwTime, //时间
		UINT64 qwUsrID //帐号ID
	);

	//发送：log玩家充值
	bool Send_LogRecharge( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		UINT32 dwGold //仙石数量
	);
	bool SendSvr_LogRecharge(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		UINT32 dwGold //仙石数量
	);
	std::string& BuildPkg_LogRecharge( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		UINT32 dwGold //仙石数量
	);

	//发送：log金钱变化
	bool Send_LogMoneyChange( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserMoneyChange& vecMoney //货币
	);
	bool SendSvr_LogMoneyChange(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserMoneyChange& vecMoney //货币
	);
	std::string& BuildPkg_LogMoneyChange( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserMoneyChange& vecMoney //货币
	);

	//发送：log道具变化
	bool Send_LogItemChange( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserItemChange& vecItem //道具
	);
	bool SendSvr_LogItemChange(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserItemChange& vecItem //道具
	);
	std::string& BuildPkg_LogItemChange( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserItemChange& vecItem //道具
	);

	//发送：log新手引导变化
	bool Send_LogGuideChange( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //引导类 load或guide
		const std::string& strStep //引导ID
	);
	bool SendSvr_LogGuideChange(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //引导类 load或guide
		const std::string& strStep //引导ID
	);
	std::string& BuildPkg_LogGuideChange( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //引导类 load或guide
		const std::string& strStep //引导ID
	);

	//发送：log自定义行为变化
	bool Send_LogActiveChange( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		UINT32 dwCount //
	);
	bool SendSvr_LogActiveChange(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		UINT32 dwCount //
	);
	std::string& BuildPkg_LogActiveChange( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		UINT32 dwCount //
	);

	//发送：log自定义行为变化
	bool Send_LogAct( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		const std::string& strParam3, //用户行为
		const std::string& strParam4, //用户行为
		const std::string& strParam5, //用户行为
		const std::string& strParam6, //用户行为
		UINT32 dwCount //
	);
	bool SendSvr_LogAct(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		const std::string& strParam3, //用户行为
		const std::string& strParam4, //用户行为
		const std::string& strParam5, //用户行为
		const std::string& strParam6, //用户行为
		UINT32 dwCount //
	);
	std::string& BuildPkg_LogAct( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		const std::string& strParam3, //用户行为
		const std::string& strParam4, //用户行为
		const std::string& strParam5, //用户行为
		const std::string& strParam6, //用户行为
		UINT32 dwCount //
	);

	//发送：log服务器变化
	bool Send_LogServerInfo( //发送给当前协议处理的服务器
		UINT32 dwTime, //时间
		const std::string& strType, //记录类型
		const std::string& strSubType, //记录分类型
		UINT32 dwNum //记录数据
	);
	bool SendSvr_LogServerInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwTime, //时间
		const std::string& strType, //记录类型
		const std::string& strSubType, //记录分类型
		UINT32 dwNum //记录数据
	);
	std::string& BuildPkg_LogServerInfo( //只组包不发送
		UINT32 dwTime, //时间
		const std::string& strType, //记录类型
		const std::string& strSubType, //记录分类型
		UINT32 dwNum //记录数据
	);

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 61; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:

private:
	typedef bool (CGame2CenterLogClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterLog
