/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    FriendProt.h
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "FriendProt.h"

namespace NFriendProt
{

//协议类：好友相关协议
class CFriendProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：询问增加好友
	bool Send_AskAddFriend( //发送给当前协议处理的客户端
		const std::string& strRoleName, //角色名字
		UINT64 qwUserID, //帐号ID
		UINT16 wFighterID, //主将ID
		NProtoCommon::ESexType eSex, //性别
		UINT8 byLevel //等级
	);
	bool SendClt_AskAddFriend(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const std::string& strRoleName, //角色名字
		UINT64 qwUserID, //帐号ID
		UINT16 wFighterID, //主将ID
		NProtoCommon::ESexType eSex, //性别
		UINT8 byLevel //等级
	);
	std::string& BuildPkg_AskAddFriend( //只组包不发送
		const std::string& strRoleName, //角色名字
		UINT64 qwUserID, //帐号ID
		UINT16 wFighterID, //主将ID
		NProtoCommon::ESexType eSex, //性别
		UINT8 byLevel //等级
	);

	//发送：增加好友/黑名单回应
	bool Send_AddFriendAck( //发送给当前协议处理的客户端
		EFriendResult eResult, //增加好友的结果
		const std::string& strName, //名字 XXX: 如果主将改名需要修改此处
		NProtoCommon::ESexType eSex //性别
	);
	bool SendClt_AddFriendAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EFriendResult eResult, //增加好友的结果
		const std::string& strName, //名字 XXX: 如果主将改名需要修改此处
		NProtoCommon::ESexType eSex //性别
	);
	std::string& BuildPkg_AddFriendAck( //只组包不发送
		EFriendResult eResult, //增加好友的结果
		const std::string& strName, //名字 XXX: 如果主将改名需要修改此处
		NProtoCommon::ESexType eSex //性别
	);

	//发送：增加好友/黑名单回应Ex
	bool Send_AddFriendAckEx( //发送给当前协议处理的客户端
		const SFriendEntry& rFriendEntry //增加的好友
	);
	bool SendClt_AddFriendAckEx(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SFriendEntry& rFriendEntry //增加的好友
	);
	std::string& BuildPkg_AddFriendAckEx( //只组包不发送
		const SFriendEntry& rFriendEntry //增加的好友
	);

	//发送：删除好友/黑名单回应
	bool Send_RemoveFriendAck( //发送给当前协议处理的客户端
		EFriendResult eResult, //删除好友的结果
		UINT64 qwUserID //删除的好友帐号ID
	);
	bool SendClt_RemoveFriendAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EFriendResult eResult, //删除好友的结果
		UINT64 qwUserID //删除的好友帐号ID
	);
	std::string& BuildPkg_RemoveFriendAck( //只组包不发送
		EFriendResult eResult, //删除好友的结果
		UINT64 qwUserID //删除的好友帐号ID
	);

	//发送：私聊失败通知
	bool Send_WhisperFailNotify( //发送给当前协议处理的客户端
		EFriendResult eResult //私聊通知的结果，成功不通知
	);
	bool SendClt_WhisperFailNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EFriendResult eResult //私聊通知的结果，成功不通知
	);
	std::string& BuildPkg_WhisperFailNotify( //只组包不发送
		EFriendResult eResult //私聊通知的结果，成功不通知
	);

	//发送：私聊成功通知
	bool Send_WhisperSuccessNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		const std::string& strBaseInfo //聊天基本信息
	);
	bool SendClt_WhisperSuccessNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		const std::string& strBaseInfo //聊天基本信息
	);
	std::string& BuildPkg_WhisperSuccessNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		const std::string& strBaseInfo //聊天基本信息
	);

	//发送：好友信息通知
	bool Send_FriendInfoNotify( //发送给当前协议处理的客户端
		const SFriend& rFriend //好友信息
	);
	bool SendClt_FriendInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SFriend& rFriend //好友信息
	);
	std::string& BuildPkg_FriendInfoNotify( //只组包不发送
		const SFriend& rFriend //好友信息
	);

	//发送：状态通知
	bool Send_OnlineStatusNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		bool bOnlineStatus //在线状态
	);
	bool SendClt_OnlineStatusNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		bool bOnlineStatus //在线状态
	);
	std::string& BuildPkg_OnlineStatusNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		bool bOnlineStatus //在线状态
	);

	//发送：等级变化通知
	bool Send_LevelChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel //当前等级
	);
	bool SendClt_LevelChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel //当前等级
	);
	std::string& BuildPkg_LevelChangeNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel //当前等级
	);

	//发送：VIP变化通知
	bool Send_VIPChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel //当前等级
	);
	bool SendClt_VIPChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel //当前等级
	);
	std::string& BuildPkg_VIPChangeNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel //当前等级
	);

	//发送：品质变化通知
	bool Send_ColorChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byColor //当前品质
	);
	bool SendClt_ColorChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byColor //当前品质
	);
	std::string& BuildPkg_ColorChangeNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		UINT8 byColor //当前品质
	);

	//发送：QQ黄钻好友通知
	bool Send_YellowDiamondNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel, //等级
		bool bYearlyPay //是否年费黄钻
	);
	bool SendClt_YellowDiamondNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel, //等级
		bool bYearlyPay //是否年费黄钻
	);
	std::string& BuildPkg_YellowDiamondNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		UINT8 byLevel, //等级
		bool bYearlyPay //是否年费黄钻
	);

	//发送：签名改变通知
	bool Send_SignChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		const std::string& strSign //签名
	);
	bool SendClt_SignChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		const std::string& strSign //签名
	);
	std::string& BuildPkg_SignChangeNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		const std::string& strSign //签名
	);

	//发送：签名改变通知
	bool Send_MoodChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		UINT16 wMood //心情表情
	);
	bool SendClt_MoodChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		UINT16 wMood //心情表情
	);
	std::string& BuildPkg_MoodChangeNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		UINT16 wMood //心情表情
	);

	//发送：签名改变通知
	bool Send_VIPLevelChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byVIPLevel //VIP等级
	);
	bool SendClt_VIPLevelChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwUserID, //帐号ID
		UINT8 byVIPLevel //VIP等级
	);
	std::string& BuildPkg_VIPLevelChangeNotify( //只组包不发送
		UINT64 qwUserID, //帐号ID
		UINT8 byVIPLevel //VIP等级
	);

	//发送：角色查询
	bool Send_FindUserIDNameAck( //发送给当前协议处理的客户端
		EFriendResult eResult, //查询返回
		UINT64 qwUserID, //帐号ID
		const std::string& strRoleName, //主角色名
		UINT16 wHeroID, //主将ID
		UINT8 byLevel, //用户等级
		bool bOnlineStatus //在线状态
	);
	bool SendClt_FindUserIDNameAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EFriendResult eResult, //查询返回
		UINT64 qwUserID, //帐号ID
		const std::string& strRoleName, //主角色名
		UINT16 wHeroID, //主将ID
		UINT8 byLevel, //用户等级
		bool bOnlineStatus //在线状态
	);
	std::string& BuildPkg_FindUserIDNameAck( //只组包不发送
		EFriendResult eResult, //查询返回
		UINT64 qwUserID, //帐号ID
		const std::string& strRoleName, //主角色名
		UINT16 wHeroID, //主将ID
		UINT8 byLevel, //用户等级
		bool bOnlineStatus //在线状态
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：增加好友/黑名单请求
	virtual void OnRecv_AddFriendReq1(
		EFriendGroupType eGroupType, //组别
		const TVecUINT64& vecUserID, //玩家ID
		UINT8 byNeedRet //0-不需要返回消息 1-需要返回消息
	) = 0;

	//接收：增加好友/黑名单请求
	virtual void OnRecv_AddFriendReq2(
		EFriendGroupType eGroupType, //组别
		const std::string& strName, //用户名
		UINT8 byNeedRet //0-不需要返回消息 1-需要返回消息
	) = 0;

	//接收：回答增加好友
	virtual void OnRecv_AnswerAddFriend(
		bool bAgree, //是否同意
		UINT64 qwUserID //帐号ID
	) = 0;

	//接收：删除好友/黑名单
	virtual void OnRecv_RemoveFriendReq(
		const TVecUINT64& vecUserID //玩家ID
	) = 0;

	struct SMoveFriendAck : public CClientFuncAck
	{
		EFriendResult eResult; //移动好友的结果

		SMoveFriendAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：移动好友
	virtual bool OnRecv_MoveFriend(
		UINT64 qwUserID, //帐号ID
		EFriendGroupType eGroupType, //分组ID
		shared_func<SMoveFriendAck>& fnAck //返回回调函数
	) = 0;

	//接收：私聊
	virtual void OnRecv_Whisper(
		UINT64 qwUserID //帐号ID
	) = 0;

	//接收：查询玩家
	virtual void OnRecv_FindUserIDNameReq(
		UINT64 qwUserID, //帐号ID
		const std::string& strRoleName //主角色名
	) = 0;

	struct SFindReferFriendReqAck : public CClientFuncAck
	{
		TVecReferFriend vecReferFriend; //推荐好友

		SFindReferFriendReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取推荐好友
	virtual bool OnRecv_FindReferFriendReq(
		shared_func<SFindReferFriendReqAck>& fnAck //返回回调函数
	) = 0;

	//接收：取得所有好友信息
	virtual void OnRecv_GetFriendInfo(
	) = 0;

	struct SSetSignAck : public CClientFuncAck
	{
		EFriendResult eResult; //修改签名结果

		SSetSignAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：修改签名
	virtual bool OnRecv_SetSign(
		const std::string& strSign, //签名文字：最多不超过255个字符
		shared_func<SSetSignAck>& fnAck //返回回调函数
	) = 0;

	struct SSetMoodAck : public CClientFuncAck
	{
		EFriendResult eResult; //修改心情表情结果

		SSetMoodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置心情表情
	virtual bool OnRecv_SetMood(
		UINT16 wMood, //心情表情
		shared_func<SSetMoodAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 24; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_AddFriendReq1(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddFriendReq2(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AnswerAddFriend(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RemoveFriendReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MoveFriend(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Whisper(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FindUserIDNameReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FindReferFriendReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFriendInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetSign(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetMood(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CFriendProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NFriendProt
