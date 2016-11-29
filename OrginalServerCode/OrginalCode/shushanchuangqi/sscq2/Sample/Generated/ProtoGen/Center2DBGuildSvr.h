/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Center2DBGuild.h
//  Purpose:      CenterServer到DBServer有关帮派的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Center2DBGuild.h"

namespace NCenter2DBGuild
{

//协议类：CenterServer到DBServer有关帮派的通信协议
class CCenter2DBGuildSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帮派公共信息加载返回
	bool Send_GuildPubInfoNotify( //发送给当前协议处理的服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
	);
	bool SendSvr_GuildPubInfoNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
	);
	std::string& BuildPkg_GuildPubInfoNotify( //只组包不发送
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecPubGuildAllInfo& vecPubGuildAllInfo //更新信息
	);

	//发送：帮派
	bool Send_AllGuildLoginNotify( //发送给当前协议处理的服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
	);
	bool SendSvr_AllGuildLoginNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
	);
	std::string& BuildPkg_AllGuildLoginNotify( //只组包不发送
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecDBGuildAllInfo& vecData //帮派具体数据
	);

	//发送：帮派
	bool Send_GuildLoginNotify( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
	);
	bool SendSvr_GuildLoginNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
	);
	std::string& BuildPkg_GuildLoginNotify( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		const NGuildProt::SDBGuildAllInfo& sData //帮派具体数据
	);

	//发送：帮派用户登录返回
	bool Send_GuildUserLoginNotify( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
	);
	bool SendSvr_GuildUserLoginNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
	);
	std::string& BuildPkg_GuildUserLoginNotify( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		const NGuildProt::TVecDBGuildUserInfo& vecGuildUserInfo //用户信息，数量为0表示完全没有在或者加入过帮派
	);

	//发送：返回请求帮派供奉人数
	bool Send_SendAllGuildStatueWorshipCount( //发送给当前协议处理的服务器
		const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
	);
	bool SendSvr_SendAllGuildStatueWorshipCount(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
	);
	std::string& BuildPkg_SendAllGuildStatueWorshipCount( //只组包不发送
		const TVecGSWorshipInfo& vecGSWorshiInfo //供奉人数信息
	);

	//发送：返回所有羲和神车信息
	bool Send_SendAllGuildXihe( //发送给当前协议处理的服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecGuildXihe& vecSendData //更新信息
	);
	bool SendSvr_SendAllGuildXihe(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecGuildXihe& vecSendData //更新信息
	);
	std::string& BuildPkg_SendAllGuildXihe( //只组包不发送
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NGuildProt::TVecGuildXihe& vecSendData //更新信息
	);

	//发送：所有帮派兑换物品加载返回
	bool Send_SendAllGuildExchangedItem( //发送给当前协议处理的服务器
		const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
	);
	bool SendSvr_SendAllGuildExchangedItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
	);
	std::string& BuildPkg_SendAllGuildExchangedItem( //只组包不发送
		const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem //派兑换物品信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：帮派数据更新
	virtual void OnRecv_GuildDataUpdate(
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	) = 0;

	//接收：帮派公共信息更新
	virtual void OnRecv_GuildPubDataUpdate(
		UINT64 qwGuildID, //帮派ID
		NGuildProt::EGuildPubDataType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	) = 0;

	//接收：获取帮派公共信息（启动预加载调用）
	virtual void OnRecv_GetGuildPubInfo(
	) = 0;

	//接收：获取所有帮派信息
	virtual void OnRecv_GetAllGuildInfo(
	) = 0;

	//接收：帮派登录（通常是涉及到有关帮派的操作需要加载登录）
	virtual void OnRecv_GuildLogin(
		UINT64 qwGuildID //帮派ID
	) = 0;

	//接收：玩家登录，拉取可能存在的帮派信息
	virtual void OnRecv_GuildUserLogin(
		UINT64 qwRoleID //玩家ID
	) = 0;

	//接收：帮派神像奖励结算
	virtual void OnRecv_GuildStatueReward(
	) = 0;

	//接收：请求所有羲和神车信息
	virtual void OnRecv_GetAllGuildXihe(
		UINT32 dwPageSize //发送条数
	) = 0;

	//接收：更新玩家羲和神车信息
	virtual void OnRecv_UpdateGuildXihe(
		const NGuildProt::SGuildXihe& oGuildXihe, //玩家羲和神车的数据
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	) = 0;

	//接收：获取帮派战兑换物品
	virtual void OnRecv_GetAllGuildExchangedItem(
	) = 0;

	//接收：更新帮派战兑换物品信息
	virtual void OnRecv_UpdateGuildExchangedItem(
		const NGuildProt::SGuildExchangedItem& sGuildExchangedItem, //帮派战兑换物品信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 32; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GuildDataUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildPubDataUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildPubInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllGuildInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildLogin(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildUserLogin(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildStatueReward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllGuildXihe(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateGuildXihe(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllGuildExchangedItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateGuildExchangedItem(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CCenter2DBGuildSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NCenter2DBGuild
