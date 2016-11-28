/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    CollectionProt.h
//  Purpose:      收藏协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "CollectionProt.h"

namespace NCollectionProt
{

//协议类：收藏协议
class CCollectionProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：收藏点通知
	bool Send_APNotify( //发送给当前协议处理的客户端
		UINT32 dwAP //收藏点
	);
	bool SendClt_APNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwAP //收藏点
	);
	std::string& BuildPkg_APNotify( //只组包不发送
		UINT32 dwAP //收藏点
	);

	//发送：收藏等级通知
	bool Send_CollectionLevelNotify( //发送给当前协议处理的客户端
		UINT16 wLevel //收藏等级
	);
	bool SendClt_CollectionLevelNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wLevel //收藏等级
	);
	std::string& BuildPkg_CollectionLevelNotify( //只组包不发送
		UINT16 wLevel //收藏等级
	);

	//发送：收藏等级通知
	bool Send_CollectionInfoNotify( //发送给当前协议处理的客户端
		const SCollectionInfo& oCollectionInfo //收藏信息
	);
	bool SendClt_CollectionInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SCollectionInfo& oCollectionInfo //收藏信息
	);
	std::string& BuildPkg_CollectionInfoNotify( //只组包不发送
		const SCollectionInfo& oCollectionInfo //收藏信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGeCollectionInfoAck : public CClientFuncAck
	{
		TVecCollectionInfo vecCollectionInfo; //收藏榜信息
		UINT16 wLevel; //收藏等级
		UINT32 dwAP; //收藏点

		SGeCollectionInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取收藏信息
	virtual bool OnRecv_GeCollectionInfo(
		shared_func<SGeCollectionInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 78; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GeCollectionInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CCollectionProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NCollectionProt
