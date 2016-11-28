/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    InviteGS.h
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "InviteGS.h"

namespace NInviteGS
{

//协议类：邀请好友相关协议
class CInviteGSSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：被邀请好友信息更新
	bool Send_UpdateInvitedFriend( //发送给当前协议处理的客户端
		const SInvitedFriend& oInvitedFriend //查询返回
	);
	bool SendClt_UpdateInvitedFriend(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SInvitedFriend& oInvitedFriend //查询返回
	);
	std::string& BuildPkg_UpdateInvitedFriend( //只组包不发送
		const SInvitedFriend& oInvitedFriend //查询返回
	);

	//发送：被邀请任务信息更新
	bool Send_UpdateInvitedTask( //发送给当前协议处理的客户端
		const SInvitedTask& oInvitedTask //被邀请任务信息
	);
	bool SendClt_UpdateInvitedTask(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SInvitedTask& oInvitedTask //被邀请任务信息
	);
	std::string& BuildPkg_UpdateInvitedTask( //只组包不发送
		const SInvitedTask& oInvitedTask //被邀请任务信息
	);

	//发送：每日邀请好友数量
	bool Send_UpdateDayInvitedFriends( //发送给当前协议处理的客户端
		UINT32 dwInviteCnt //邀请数量
	);
	bool SendClt_UpdateDayInvitedFriends(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwInviteCnt //邀请数量
	);
	std::string& BuildPkg_UpdateDayInvitedFriends( //只组包不发送
		UINT32 dwInviteCnt //邀请数量
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetInvitedFriendListAck : public CClientFuncAck
	{
		TVecInvitedFriend vecInvitedFriend; //被邀请好友列表

		SGetInvitedFriendListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取被邀请好友列表
	virtual bool OnRecv_GetInvitedFriendList(
		shared_func<SGetInvitedFriendListAck>& fnAck //返回回调函数
	) = 0;

	struct SGetInvitedTaskListAck : public CClientFuncAck
	{
		TVecInvitedTask vecInvitedTask; //邀请任务状态信息

		SGetInvitedTaskListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：邀请任务列表
	virtual bool OnRecv_GetInvitedTaskList(
		shared_func<SGetInvitedTaskListAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDayInvitedFriendsAck : public CClientFuncAck
	{
		UINT32 dwInviteCnt; //邀请数量

		SGetDayInvitedFriendsAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：每日邀请好友数量
	virtual bool OnRecv_GetDayInvitedFriends(
		shared_func<SGetDayInvitedFriendsAck>& fnAck //返回回调函数
	) = 0;

	struct STakeTaskPrizeAck : public CClientFuncAck
	{
		EInviteResult eRet; //结果

		STakeTaskPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取奖励
	virtual bool OnRecv_TakeTaskPrize(
		UINT32 dwPrizeID, //领奖任务ID
		shared_func<STakeTaskPrizeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 134; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetInvitedFriendList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetInvitedTaskList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDayInvitedFriends(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeTaskPrize(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CInviteGSSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NInviteGS
