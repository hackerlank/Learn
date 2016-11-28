/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    SittingProt.h
//  Purpose:      打坐协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "SittingProt.h"

namespace NSittingProt
{

//协议类：打坐协议
class CSittingProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家打坐结算
	bool Send_CancelSittingOffLine( //发送给当前协议处理的客户端
		UINT8 byType, //0,表示单修，1表示双修
		const NItemProt::TVecResource& vecRes, //获得的资源
		UINT32 dwSittingTimer //开始时间
	);
	bool SendClt_CancelSittingOffLine(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byType, //0,表示单修，1表示双修
		const NItemProt::TVecResource& vecRes, //获得的资源
		UINT32 dwSittingTimer //开始时间
	);
	std::string& BuildPkg_CancelSittingOffLine( //只组包不发送
		UINT8 byType, //0,表示单修，1表示双修
		const NItemProt::TVecResource& vecRes, //获得的资源
		UINT32 dwSittingTimer //开始时间
	);

	//发送：打坐状态变化
	bool Send_UpdateSitting( //发送给当前协议处理的客户端
		UINT8 byState, //0,表示结束打坐，1 ，开始打坐
		const NMapProt::TVecPlayerAppear& vecOtherApear, //空表示单修，非空表示双修
		UINT32 dwSittingTimer //开始时间
	);
	bool SendClt_UpdateSitting(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byState, //0,表示结束打坐，1 ，开始打坐
		const NMapProt::TVecPlayerAppear& vecOtherApear, //空表示单修，非空表示双修
		UINT32 dwSittingTimer //开始时间
	);
	std::string& BuildPkg_UpdateSitting( //只组包不发送
		UINT8 byState, //0,表示结束打坐，1 ，开始打坐
		const NMapProt::TVecPlayerAppear& vecOtherApear, //空表示单修，非空表示双修
		UINT32 dwSittingTimer //开始时间
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SDoSittingTogetherAck : public CClientFuncAck
	{
		ESittingResult eResult; //请求结果

		SDoSittingTogetherAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求双修
	virtual bool OnRecv_DoSittingTogether(
		UINT64 qwOtherID, //对方ID,0表示单修，非0表示双修
		shared_func<SDoSittingTogetherAck>& fnAck //返回回调函数
	) = 0;

	//接收：请求取消修炼
	virtual void OnRecv_CancelSitting(
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 55; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_DoSittingTogether(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CancelSitting(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CSittingProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NSittingProt
