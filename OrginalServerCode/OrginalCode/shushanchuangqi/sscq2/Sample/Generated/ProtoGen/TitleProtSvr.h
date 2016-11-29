/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    TitleProt.h
//  Purpose:      称号协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "TitleProt.h"

namespace NTitleProt
{

//协议类：称号协议
class CTitleProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：获得称号
	bool Send_AddTitle( //发送给当前协议处理的客户端
		const NRoleInfoDefine::STitle& stTitleInfo //称号详情
	);
	bool SendClt_AddTitle(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const NRoleInfoDefine::STitle& stTitleInfo //称号详情
	);
	std::string& BuildPkg_AddTitle( //只组包不发送
		const NRoleInfoDefine::STitle& stTitleInfo //称号详情
	);

	//发送：删除称号
	bool Send_DelTitle( //发送给当前协议处理的客户端
		UINT16 wId //称号ID
	);
	bool SendClt_DelTitle(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wId //称号ID
	);
	std::string& BuildPkg_DelTitle( //只组包不发送
		UINT16 wId //称号ID
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetAllTitleAck : public CClientFuncAck
	{
		NRoleInfoDefine::TVecTitle vecTitle; //当前所有称号

		SGetAllTitleAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：得到当前所有称号
	virtual bool OnRecv_GetAllTitle(
		shared_func<SGetAllTitleAck>& fnAck //返回回调函数
	) = 0;

	struct SEquipTitleAck : public CClientFuncAck
	{
		ETitleResult eResult; //操作结果
		UINT16 wId; //称号ID
		UINT8 byPos; //装备位置

		SEquipTitleAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：刷新称号列表
	virtual bool OnRecv_EquipTitle(
		UINT16 wId, //称号ID
		UINT8 byPos, //装备位置,0表示任意位置
		shared_func<SEquipTitleAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 54; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetAllTitle(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EquipTitle(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CTitleProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NTitleProt
