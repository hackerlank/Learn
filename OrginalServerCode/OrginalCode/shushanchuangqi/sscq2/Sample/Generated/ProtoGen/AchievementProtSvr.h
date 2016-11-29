/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    AchievementProt.h
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "AchievementProt.h"

namespace NAchievementProt
{

//协议类：成就相关协议
class CAchievementProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：成就点通知
	bool Send_APNotify( //发送给当前协议处理的客户端
		UINT32 dwAP //成就点
	);
	bool SendClt_APNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwAP //成就点
	);
	std::string& BuildPkg_APNotify( //只组包不发送
		UINT32 dwAP //成就点
	);

	//发送：成就等级通知
	bool Send_AchievementLevelNotify( //发送给当前协议处理的客户端
		UINT16 wLevel //成就等级
	);
	bool SendClt_AchievementLevelNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wLevel //成就等级
	);
	std::string& BuildPkg_AchievementLevelNotify( //只组包不发送
		UINT16 wLevel //成就等级
	);

	//发送：成就等级通知
	bool Send_AchievementInfoNotify( //发送给当前协议处理的客户端
		const SAchievementInfo& oAchievementInfo //成就信息
	);
	bool SendClt_AchievementInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SAchievementInfo& oAchievementInfo //成就信息
	);
	std::string& BuildPkg_AchievementInfoNotify( //只组包不发送
		const SAchievementInfo& oAchievementInfo //成就信息
	);

	//发送：成就分享通知
	bool Send_AchievementShareNotify( //发送给当前协议处理的客户端
		const SAchievementShare& oAchievementShare //成就分享信息
	);
	bool SendClt_AchievementShareNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SAchievementShare& oAchievementShare //成就分享信息
	);
	std::string& BuildPkg_AchievementShareNotify( //只组包不发送
		const SAchievementShare& oAchievementShare //成就分享信息
	);

	//发送：零点通知
	bool Send_MidnightNotify( //发送给当前协议处理的客户端
	);
	bool SendClt_MidnightNotify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_MidnightNotify( //只组包不发送
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGeAchievementInfoAck : public CClientFuncAck
	{
		TVecAchievementInfo vecAchievementInfo; //成就榜信息
		UINT16 wLevel; //成就等级
		UINT32 dwAP; //成就点

		SGeAchievementInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取成就信息
	virtual bool OnRecv_GeAchievementInfo(
		shared_func<SGeAchievementInfoAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeAck : public CClientFuncAck
	{
		EAchievementRet eRet; //结果

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取成就奖励
	virtual bool OnRecv_TakePrize(
		UINT16 wAchievementID, //成就ID
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SGeAchievementShareListAck : public CClientFuncAck
	{
		TVecAchievementShare vecAchievementShare; //成就分享信息

		SGeAchievementShareListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取成就分享信息
	virtual bool OnRecv_GeAchievementShareList(
		shared_func<SGeAchievementShareListAck>& fnAck //返回回调函数
	) = 0;

	struct STakeSharePrizeAck : public CClientFuncAck
	{
		EAchievementRet eRet; //结果

		STakeSharePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取成就分享奖励
	virtual bool OnRecv_TakeSharePrize(
		UINT16 wAchievementID, //成就ID
		shared_func<STakeSharePrizeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 75; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GeAchievementInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GeAchievementShareList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeSharePrize(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CAchievementProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NAchievementProt
