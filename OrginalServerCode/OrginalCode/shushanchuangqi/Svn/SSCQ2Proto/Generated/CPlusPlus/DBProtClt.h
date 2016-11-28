/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    DBProt.h
//  Purpose:      数据库查询协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "DBProt.h"

namespace NDBProt
{

//协议类：数据库查询协议
class CDBProtClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：查询请求
	bool Send_QueryReq( //发送给当前协议处理的服务器
		UINT32 dwTransID, //事务的ID
		EQueryType eQueryType, //查询类型
		const SQuery& query //查询
	);
	bool SendSvr_QueryReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwTransID, //事务的ID
		EQueryType eQueryType, //查询类型
		const SQuery& query //查询
	);
	std::string& BuildPkg_QueryReq( //只组包不发送
		UINT32 dwTransID, //事务的ID
		EQueryType eQueryType, //查询类型
		const SQuery& query //查询
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：无结果集的返回
	virtual void OnRecv_ResultRet(
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		UINT32 dwAffectRow //影响的行数
	) = 0;

	//接收：有结果集的返回
	virtual void OnRecv_ResultDataRet(
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		const TVecTable& vecTable, //返回的结果表集
		UINT8 byCount //结果表数量
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 9; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_ResultRet(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ResultDataRet(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CDBProtClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NDBProt
