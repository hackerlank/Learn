/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    TeamGS.h
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "TeamGS.h"

namespace NTeamGS
{

//协议类：竞技场协议
class CTeamGSSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：房间信息更新
	bool Send_TeamInfoUpdate( //发送给当前协议处理的客户端
		const TeamInfo& stInfo //房间信息
	);
	bool SendClt_TeamInfoUpdate(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TeamInfo& stInfo //房间信息
	);
	std::string& BuildPkg_TeamInfoUpdate( //只组包不发送
		const TeamInfo& stInfo //房间信息
	);

	//发送：通告自己被踢
	bool Send_NoticeKicked( //发送给当前协议处理的客户端
		UINT16 DgnType //副本类型
	);
	bool SendClt_NoticeKicked(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 DgnType //副本类型
	);
	std::string& BuildPkg_NoticeKicked( //只组包不发送
		UINT16 DgnType //副本类型
	);

	//发送：房间列表更新
	bool Send_UpdateTeamInfoList( //发送给当前协议处理的客户端
		TeamListOP eOpType, //操作类型
		const TVecTeamInfoForList& vecInfo //修改的数据
	);
	bool SendClt_UpdateTeamInfoList(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		TeamListOP eOpType, //操作类型
		const TVecTeamInfoForList& vecInfo //修改的数据
	);
	std::string& BuildPkg_UpdateTeamInfoList( //只组包不发送
		TeamListOP eOpType, //操作类型
		const TVecTeamInfoForList& vecInfo //修改的数据
	);

	//发送：队伍解散
	bool Send_TeamDelForList( //发送给当前协议处理的客户端
		UINT32 dwTeamID //队伍ID
	);
	bool SendClt_TeamDelForList(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTeamID //队伍ID
	);
	std::string& BuildPkg_TeamDelForList( //只组包不发送
		UINT32 dwTeamID //队伍ID
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetTeamListAck : public CClientFuncAck
	{
		TVecTeamInfoForList vecReturn; //返回的房间列表

		SGetTeamListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：根据模板查询可加入房间
	virtual bool OnRecv_GetTeamList(
		UINT16 DgnType, //房间ID
		shared_func<SGetTeamListAck>& fnAck //返回回调函数
	) = 0;

	//接收：停止查询
	virtual void OnRecv_StopTeamList(
	) = 0;

	struct SCreateTeamAck : public CClientFuncAck
	{
		UINT32 dwTeamID; //房间ID
		ETEAMResult eResult; //创建房间结果

		SCreateTeamAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求创建房间
	virtual bool OnRecv_CreateTeam(
		UINT16 DgnType, //副本类型
		const TeamSetting& stSetting, //队伍设置
		shared_func<SCreateTeamAck>& fnAck //返回回调函数
	) = 0;

	struct SEnterTeamAck : public CClientFuncAck
	{
		UINT32 dwTeamID; //房间ID
		ETEAMResult eResult; //请求加入房间

		SEnterTeamAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求加入房间
	virtual bool OnRecv_EnterTeam(
		UINT32 dwTeamID, //房间ID
		UINT32 dwPassWord, //队伍密码
		shared_func<SEnterTeamAck>& fnAck //返回回调函数
	) = 0;

	struct SResetFigterAck : public CClientFuncAck
	{
		ETEAMResult eResult; //请求更换将

		SResetFigterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求更换将
	virtual bool OnRecv_ResetFigter(
		UINT64 qwNewFighter, //新将
		UINT8 byPos, //将位置
		shared_func<SResetFigterAck>& fnAck //返回回调函数
	) = 0;

	struct SChangeSelfPosAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SChangeSelfPosAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：交换自己的将位置
	virtual bool OnRecv_ChangeSelfPos(
		UINT8 byPos1, //第1个位置
		UINT8 byPos2, //第2个位置
		shared_func<SChangeSelfPosAck>& fnAck //返回回调函数
	) = 0;

	struct SChangeArrayPosAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SChangeArrayPosAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：交换列的位置
	virtual bool OnRecv_ChangeArrayPos(
		UINT8 byPos1, //第1个位置
		UINT8 byPos2, //第2个位置
		shared_func<SChangeArrayPosAck>& fnAck //返回回调函数
	) = 0;

	struct SLeaveTeamAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SLeaveTeamAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求离开房间
	virtual bool OnRecv_LeaveTeam(
		shared_func<SLeaveTeamAck>& fnAck //返回回调函数
	) = 0;

	struct SDoReadyAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SDoReadyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家已经准备好
	virtual bool OnRecv_DoReady(
		shared_func<SDoReadyAck>& fnAck //返回回调函数
	) = 0;

	struct SCancelDoReadyAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SCancelDoReadyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家取消准备好
	virtual bool OnRecv_CancelDoReady(
		shared_func<SCancelDoReadyAck>& fnAck //返回回调函数
	) = 0;

	struct SEnterDgnAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SEnterDgnAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求进入副本
	virtual bool OnRecv_EnterDgn(
		shared_func<SEnterDgnAck>& fnAck //返回回调函数
	) = 0;

	struct SKickOffPlayerAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SKickOffPlayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求踢玩家出队伍
	virtual bool OnRecv_KickOffPlayer(
		UINT64 qwRoleID, //踢的人
		shared_func<SKickOffPlayerAck>& fnAck //返回回调函数
	) = 0;

	struct SGetTeamInfoAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SGetTeamInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取队伍信息
	virtual bool OnRecv_GetTeamInfo(
		shared_func<SGetTeamInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SChangDgnTypeAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SChangDgnTypeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：换副本请求
	virtual bool OnRecv_ChangDgnType(
		UINT16 NewDgnType, //新副本类型
		shared_func<SChangDgnTypeAck>& fnAck //返回回调函数
	) = 0;

	struct SChangPetAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SChangPetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：换阵灵请求
	virtual bool OnRecv_ChangPet(
		UINT64 qwRoleID, //阵灵的主人
		shared_func<SChangPetAck>& fnAck //返回回调函数
	) = 0;

	struct SChangSettingAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SChangSettingAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：更改设置请求
	virtual bool OnRecv_ChangSetting(
		const TeamSetting& stSetting, //队伍设置
		shared_func<SChangSettingAck>& fnAck //返回回调函数
	) = 0;

	struct SChangLeaderAck : public CClientFuncAck
	{
		ETEAMResult eResult; //返回

		SChangLeaderAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：换队长
	virtual bool OnRecv_ChangLeader(
		UINT64 qwNewLeader, //新队长ID
		shared_func<SChangLeaderAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 56; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetTeamList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_StopTeamList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CreateTeam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EnterTeam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ResetFigter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChangeSelfPos(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChangeArrayPos(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeaveTeam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DoReady(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CancelDoReady(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EnterDgn(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_KickOffPlayer(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTeamInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChangDgnType(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChangPet(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChangSetting(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChangLeader(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CTeamGSSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NTeamGS
