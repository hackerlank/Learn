/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    BattleGS.h
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "BattleGS.h"

namespace NBattleGS
{

//协议类：战斗通信协议
class CBattleGSSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：战斗请求结果
	bool Send_BattleAck( //发送给当前协议处理的客户端
		EBattleReqResult eResult //返回结果
	);
	bool SendClt_BattleAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EBattleReqResult eResult //返回结果
	);
	std::string& BuildPkg_BattleAck( //只组包不发送
		EBattleReqResult eResult //返回结果
	);

	//发送：请求战报结果
	bool Send_BattleReportAck( //发送给当前协议处理的客户端
		EReportReqResult eResult //战报请求结果
	);
	bool SendClt_BattleReportAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EReportReqResult eResult //战报请求结果
	);
	std::string& BuildPkg_BattleReportAck( //只组包不发送
		EReportReqResult eResult //战报请求结果
	);

	//发送：战报
	bool Send_BattleReportData( //发送给当前协议处理的客户端
		const std::string& strBattleReport, //战报
		UINT64 qwMasterID, //视角角色ID
		UINT16 wFighterID //主将ID
	);
	bool SendClt_BattleReportData(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const std::string& strBattleReport, //战报
		UINT64 qwMasterID, //视角角色ID
		UINT16 wFighterID //主将ID
	);
	std::string& BuildPkg_BattleReportData( //只组包不发送
		const std::string& strBattleReport, //战报
		UINT64 qwMasterID, //视角角色ID
		UINT16 wFighterID //主将ID
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：请求战斗
	virtual void OnRecv_BattleReq(
		UINT64 qwDefenseID //防守ID
	) = 0;

	//接收：请求战报
	virtual void OnRecv_BattleReportReq(
		UINT64 qwReportID, //请求战报ID
		UINT64 qwMasterID //视角角色ID
	) = 0;

	//接收：战报阅读完成
	virtual void OnRecv_FinishBattleReport(
		UINT64 qwReportID //请求战报ID
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 21; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_BattleReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BattleReportReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FinishBattleReport(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CBattleGSSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NBattleGS
