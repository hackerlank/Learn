/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    RoleEnterGameProt.h
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "RoleEnterGameProt.h"

namespace NRoleEnterGameProt
{

//协议类：角色信息相关操作协议
class CRoleEnterGameProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：请求进入游戏应答
	bool Send_EnterGameAck( //发送给当前协议处理的客户端
		EEnterResult eEnterResult, //登陆结果
		UINT32 dwNowTimer //目前服务器的时间
	);
	bool SendClt_EnterGameAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EEnterResult eEnterResult, //登陆结果
		UINT32 dwNowTimer //目前服务器的时间
	);
	std::string& BuildPkg_EnterGameAck( //只组包不发送
		EEnterResult eEnterResult, //登陆结果
		UINT32 dwNowTimer //目前服务器的时间
	);

	//发送：创建角色应答
	bool Send_CreateRoleAck( //发送给当前协议处理的客户端
		ECreateRoleResult eCreateRoleResult //创建结果
	);
	bool SendClt_CreateRoleAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ECreateRoleResult eCreateRoleResult //创建结果
	);
	std::string& BuildPkg_CreateRoleAck( //只组包不发送
		ECreateRoleResult eCreateRoleResult //创建结果
	);

	//发送：玩家请求推荐名字返回
	bool Send_PlayerRamdomNameAck( //发送给当前协议处理的客户端
		const std::string& strName //空表示没有得到
	);
	bool SendClt_PlayerRamdomNameAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const std::string& strName //空表示没有得到
	);
	std::string& BuildPkg_PlayerRamdomNameAck( //只组包不发送
		const std::string& strName //空表示没有得到
	);

	//发送：角色查询返回
	bool Send_GetUserInfoAck( //发送给当前协议处理的客户端
		const RoleEnterGameData& stRoleEnterInfo //进入信息
	);
	bool SendClt_GetUserInfoAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const RoleEnterGameData& stRoleEnterInfo //进入信息
	);
	std::string& BuildPkg_GetUserInfoAck( //只组包不发送
		const RoleEnterGameData& stRoleEnterInfo //进入信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：请求进入游戏
	virtual void OnRecv_EnterGameReq(
		const SEnterParam& stEnterParam //信息
	) = 0;

	//接收：创建角色请求
	virtual void OnRecv_CreateRoleReq(
		const SCreateRoleInfo& stCreateInfo //创角信息
	) = 0;

	//接收：玩家请求推荐名字
	virtual void OnRecv_PlayerRamdomNameReq(
		UINT8 byIsMale //非0表示男性
	) = 0;

	//接收：角色信息查询
	virtual void OnRecv_GetUserInfo(
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 3; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_EnterGameReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CreateRoleReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PlayerRamdomNameReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetUserInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CRoleEnterGameProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NRoleEnterGameProt
