/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DBProt.h
//  Purpose:      数据库查询协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "DBProt.h"

namespace NDBProt
{

//协议类：数据库查询协议
class CDBProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：无结果集的返回
	bool Send_ResultRet( //发送给当前协议处理的服务器
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		UINT32 dwAffectRow //影响的行数
	);
	bool SendSvr_ResultRet(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		UINT32 dwAffectRow //影响的行数
	);
	std::string& BuildPkg_ResultRet( //只组包不发送
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		UINT32 dwAffectRow //影响的行数
	);

	//发送：有结果集的返回
	bool Send_ResultDataRet( //发送给当前协议处理的服务器
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		const TVecTable& vecTable, //返回的结果表集
		UINT8 byCount //结果表数量
	);
	bool SendSvr_ResultDataRet(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		const TVecTable& vecTable, //返回的结果表集
		UINT8 byCount //结果表数量
	);
	std::string& BuildPkg_ResultDataRet( //只组包不发送
		UINT32 dwTransID, //事务的ID
		INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
		const TVecTable& vecTable, //返回的结果表集
		UINT8 byCount //结果表数量
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：查询请求
	virtual void OnRecv_QueryReq(
		UINT32 dwTransID, //事务的ID
		EQueryType eQueryType, //查询类型
		const SQuery& query //查询
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 9; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_QueryReq(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CDBProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NDBProt
