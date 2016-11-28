/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Center2DBGuild.h
//  Purpose:      CenterServer到DBServer有关帮派的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Center2DBGuild.h"

namespace NCenter2DBGuild
{

//协议类：CenterServer到DBServer有关帮派的通信协议
class CCenter2DBGuildClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帮派数据更新
	bool Send_GuildDataUpdate( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	bool SendSvr_GuildDataUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	std::string& BuildPkg_GuildDataUpdate( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);

	//发送：帮派公共信息更新
	bool Send_GuildPubDataUpdate( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildPubDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	bool SendSvr_GuildPubDataUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildPubDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);
	std::string& BuildPkg_GuildPubDataUpdate( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildPubDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	);

	//发送：获取帮派公共信息（启动预加载调用）
	bool Send_GetGuildPubInfo( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetGuildPubInfo(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetGuildPubInfo( //只组包不发送
	);

	//发送：获取所有帮派信息
	bool Send_GetAllGuildInfo( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetAllGuildInfo(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetAllGuildInfo( //只组包不发送
	);

	//发送：帮派登录（通常是涉及到有关帮派的操作需要加载登录）
	bool Send_GuildLogin( //发送给当前协议处理的服务器
		UINT64 qwGuildID //帮派ID
	);
	bool SendSvr_GuildLogin(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID //帮派ID
	);
	std::string& BuildPkg_GuildLogin( //只组包不发送
		UINT64 qwGuildID //帮派ID
	);

	//发送：玩家登录，拉取可能存在的帮派信息
	bool Send_GuildUserLogin( //发送给当前协议处理的服务器
		UINT64 qwRoleID //玩家ID
	);
	bool SendSvr_GuildUserLogin(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID //玩家ID
	);
	std::string& BuildPkg_GuildUserLogin( //只组包不发送
		UINT64 qwRoleID //玩家ID
	);

	//发送：帮派神像奖励结算
	bool Send_GuildStatueReward( //发送给当前协议处理的服务器
	);
	bool SendSvr_GuildStatueReward(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GuildStatueReward( //只组包不发送
	);

	//发送：请求所有羲和神车信息
	bool Send_GetAllGuildXihe( //发送给当前协议处理的服务器
		UINT32 dwPageSize //发送条数
	);
	bool SendSvr_GetAllGuildXihe(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize //发送条数
	);
	std::string& BuildPkg_GetAllGuildXihe( //只组包不发送
		UINT32 dwPageSize //发送条数
	);

	//发送：更新玩家羲和神车信息
	bool Send_UpdateGuildXihe( //发送给当前协议处理的服务器
		const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	bool SendSvr_UpdateGuildXihe(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	std::string& BuildPkg_UpdateGuildXihe( //只组包不发送
		const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);

	//发送：获取帮派战兑换物品
	bool Send_GetAllGuildExchangedItem( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetAllGuildExchangedItem(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetAllGuildExchangedItem( //只组包不发送
	);

	//发送：更新帮派战兑换物品信息
	bool Send_UpdateGuildExchangedItem( //发送给当前协议处理的服务器
		const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	bool SendSvr_UpdateGuildExchangedItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);
	std::string& BuildPkg_UpdateGuildExchangedItem( //只组包不发送
		const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：帮派公共信息加载返回
	virtual void OnRecv_GuildPubInfoNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
	) = 0;

	//接收：帮派
	virtual void OnRecv_AllGuildLoginNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
	) = 0;

	//接收：帮派
	virtual void OnRecv_GuildLoginNotify(
		UINT64 qwGuildID, //帮派ID
		const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
	) = 0;

	//接收：帮派用户登录返回
	virtual void OnRecv_GuildUserLoginNotify(
		UINT64 qwRoleID, //玩家ID
		const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
	) = 0;

	//接收：返回请求帮派供奉人数
	virtual void OnRecv_SendAllGuildStatueWorshipCount(
		const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
	) = 0;

	//接收：返回所有羲和神车信息
	virtual void OnRecv_SendAllGuildXihe(
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecGuildXihe& vecSendData //更新信息
	) = 0;

	//接收：所有帮派兑换物品加载返回
	virtual void OnRecv_SendAllGuildExchangedItem(
		const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 32; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GuildPubInfoNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AllGuildLoginNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildLoginNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildUserLoginNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllGuildStatueWorshipCount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllGuildXihe(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendAllGuildExchangedItem(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CCenter2DBGuildClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NCenter2DBGuild
