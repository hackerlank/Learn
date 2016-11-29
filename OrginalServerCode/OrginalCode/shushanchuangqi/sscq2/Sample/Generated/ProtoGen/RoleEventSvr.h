/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    RoleEvent.h
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "RoleEvent.h"

namespace NRoleEvent
{

//协议类：玩家在GameServer的消息处理
class CRoleEventSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：散仙信息通知列表
	bool Send_FighterInfoNotify( //发送给当前协议处理的客户端
		const TVecFighterSpecInfo& vecFighters //散仙信息
	);
	bool SendClt_FighterInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecFighterSpecInfo& vecFighters //散仙信息
	);
	std::string& BuildPkg_FighterInfoNotify( //只组包不发送
		const TVecFighterSpecInfo& vecFighters //散仙信息
	);

	//发送：增加的AppearIcon通知
	bool Send_AddAppearIconNotify( //发送给当前协议处理的客户端
		const TVecUINT16& vecAppearIcon //增加的Icon列表
	);
	bool SendClt_AddAppearIconNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecUINT16& vecAppearIcon //增加的Icon列表
	);
	std::string& BuildPkg_AddAppearIconNotify( //只组包不发送
		const TVecUINT16& vecAppearIcon //增加的Icon列表
	);

	//发送：玩家Buff变化通知
	bool Send_BuffNotify( //发送给当前协议处理的客户端
		NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
		const NProtoCommon::TVecBuffInfo& vecBuffInfo //玩家Buff信息
	);
	bool SendClt_BuffNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
		const NProtoCommon::TVecBuffInfo& vecBuffInfo //玩家Buff信息
	);
	std::string& BuildPkg_BuffNotify( //只组包不发送
		NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
		const NProtoCommon::TVecBuffInfo& vecBuffInfo //玩家Buff信息
	);

	//发送：准备切地图
	bool Send_ChangeMapNotify( //发送给当前协议处理的客户端
		UINT16 wMapId, //地图id，客户端准备资源
		UINT64 qwDgnId, //副本实例，非单人副本为0
		UINT16 wDgnType //副本模板，单人副本为0
	);
	bool SendClt_ChangeMapNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wMapId, //地图id，客户端准备资源
		UINT64 qwDgnId, //副本实例，非单人副本为0
		UINT16 wDgnType //副本模板，单人副本为0
	);
	std::string& BuildPkg_ChangeMapNotify( //只组包不发送
		UINT16 wMapId, //地图id，客户端准备资源
		UINT64 qwDgnId, //副本实例，非单人副本为0
		UINT16 wDgnType //副本模板，单人副本为0
	);

	//发送：暴击通知
	bool Send_CritNotify( //发送给当前协议处理的客户端
		ECritType eCritType, //暴击类型
		ECritMultiple eCritMultiple //暴击倍数
	);
	bool SendClt_CritNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ECritType eCritType, //暴击类型
		ECritMultiple eCritMultiple //暴击倍数
	);
	std::string& BuildPkg_CritNotify( //只组包不发送
		ECritType eCritType, //暴击类型
		ECritMultiple eCritMultiple //暴击倍数
	);

	//发送：删除AppearIcon通知
	bool Send_DelAppearIconNotify( //发送给当前协议处理的客户端
		UINT16 wIconID //删除的IconApear
	);
	bool SendClt_DelAppearIconNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wIconID //删除的IconApear
	);
	std::string& BuildPkg_DelAppearIconNotify( //只组包不发送
		UINT16 wIconID //删除的IconApear
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetRoleSpecInfoAck : public CClientFuncAck
	{
		SRoleStream stRoleStream; //角色信息

		SGetRoleSpecInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取角色面板信息
	virtual bool OnRecv_GetRoleSpecInfo(
		shared_func<SGetRoleSpecInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetFightersAck : public CClientFuncAck
	{
		TVecFighterSpecInfo vecFighters; //散仙信息

		SGetFightersAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：取得散仙列表
	virtual bool OnRecv_GetFighters(
		shared_func<SGetFightersAck>& fnAck //返回回调函数
	) = 0;

	struct SStoreGuideAck : public CClientFuncAck
	{
		bool bResult; //结果

		SStoreGuideAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：存储新手引导信息
	virtual bool OnRecv_StoreGuide(
		const std::string& strGuide, //引导步骤信息
		shared_func<SStoreGuideAck>& fnAck //返回回调函数
	) = 0;

	struct SGetRoleBuffInfoAck : public CClientFuncAck
	{
		NProtoCommon::TVecBuffInfo vecBuffInfo; //玩家Buff信息

		SGetRoleBuffInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取角色Buff信息
	virtual bool OnRecv_GetRoleBuffInfo(
		shared_func<SGetRoleBuffInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 11; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetRoleSpecInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFighters(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_StoreGuide(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRoleBuffInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CRoleEventSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NRoleEvent
