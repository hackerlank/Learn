/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterLog.h
//  Purpose:      GameServer到CenterServer的数据中心log协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterLog.h"

namespace NGame2CenterLog
{

//协议类：GameServer到CenterServer的数据中心log协议
class CGame2CenterLogSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：log注册记录
	virtual void OnRecv_LogRegister(
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	) = 0;

	//接收：log登陆
	virtual void OnRecv_LogUserLogin(
		UINT64 qwUsrID, //帐号ID
		const TVecString& vecStrInfo //用户登陆平台信息
	) = 0;

	//接收：log登出
	virtual void OnRecv_LogPlayerLogout(
		UINT32 dwTime, //时间
		UINT64 qwUsrID //帐号ID
	) = 0;

	//接收：log玩家充值
	virtual void OnRecv_LogRecharge(
		UINT64 qwUsrID, //帐号ID
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		UINT32 dwGold //仙石数量
	) = 0;

	//接收：log金钱变化
	virtual void OnRecv_LogMoneyChange(
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserMoneyChange& vecMoney //货币
	) = 0;

	//接收：log道具变化
	virtual void OnRecv_LogItemChange(
		UINT64 qwUsrID, //帐号ID
		EOpType eType, //类型
		const TVecUserItemChange& vecItem //道具
	) = 0;

	//接收：log新手引导变化
	virtual void OnRecv_LogGuideChange(
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //引导类 load或guide
		const std::string& strStep //引导ID
	) = 0;

	//接收：log自定义行为变化
	virtual void OnRecv_LogActiveChange(
		UINT64 qwUsrID, //帐号ID
		const std::string& strCategory, //行为分类
		const std::string& strAction, //用户行为
		UINT32 dwCount //
	) = 0;

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
	) = 0;

	//接收：log服务器变化
	virtual void OnRecv_LogServerInfo(
		UINT32 dwTime, //时间
		const std::string& strType, //记录类型
		const std::string& strSubType, //记录分类型
		UINT32 dwNum //记录数据
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 61; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_LogRegister(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogUserLogin(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogPlayerLogout(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogRecharge(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogMoneyChange(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogItemChange(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogGuideChange(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogActiveChange(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogAct(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LogServerInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGame2CenterLogSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterLog
