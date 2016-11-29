/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GlobalChatProt.h
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GlobalChatProt.h"

namespace NGlobalChatProt
{

//协议类：全局聊天协议
class CGlobalChatProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：聊天信息通知
	bool Send_ChatInfoNotify( //发送给当前协议处理的客户端
		EChannelType eChannelType, //通道类型
		const SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //聊天信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
	);
	bool SendClt_ChatInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EChannelType eChannelType, //通道类型
		const SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //聊天信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
	);
	std::string& BuildPkg_ChatInfoNotify( //只组包不发送
		EChannelType eChannelType, //通道类型
		const SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //聊天信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
	);

	//发送：私聊错误通知
	bool Send_WhisperErrorNotify( //发送给当前协议处理的客户端
		EWhisperErrorType eErrType, //错误类型
		UINT64 qwUsrID //帐号ID
	);
	bool SendClt_WhisperErrorNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EWhisperErrorType eErrType, //错误类型
		UINT64 qwUsrID //帐号ID
	);
	std::string& BuildPkg_WhisperErrorNotify( //只组包不发送
		EWhisperErrorType eErrType, //错误类型
		UINT64 qwUsrID //帐号ID
	);

	//发送：私聊信息通知
	bool Send_WhisperInfoNotify( //发送给当前协议处理的客户端
		const SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //私聊信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
	);
	bool SendClt_WhisperInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //私聊信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
	);
	std::string& BuildPkg_WhisperInfoNotify( //只组包不发送
		const SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //私聊信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
	);

	//发送：系统信息通知
	bool Send_SystemMsgNotify( //发送给当前协议处理的客户端
		EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		EChannelSubType eSubType //额外信息
	);
	bool SendClt_SystemMsgNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		EChannelSubType eSubType //额外信息
	);
	std::string& BuildPkg_SystemMsgNotify( //只组包不发送
		EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		EChannelSubType eSubType //额外信息
	);

	//发送：系统MsgID通知
	bool Send_SystemMsgIDNotify( //发送给当前协议处理的客户端
		UINT16 wMsgID //消息ID
	);
	bool SendClt_SystemMsgIDNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wMsgID //消息ID
	);
	std::string& BuildPkg_SystemMsgIDNotify( //只组包不发送
		UINT16 wMsgID //消息ID
	);

	//发送：系统MsgID通知
	bool Send_SystemFormatMsgIDNotify( //发送给当前协议处理的客户端
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);
	bool SendClt_SystemFormatMsgIDNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);
	std::string& BuildPkg_SystemFormatMsgIDNotify( //只组包不发送
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);

	//发送：系统弹窗和公告更新通知
	bool Send_SysDialogAndNoticeUpdateNotify( //发送给当前协议处理的客户端
		UINT8 byNotifyType //通知类型1:系统弹窗通知；2、公告更新通知
	);
	bool SendClt_SysDialogAndNoticeUpdateNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byNotifyType //通知类型1:系统弹窗通知；2、公告更新通知
	);
	std::string& BuildPkg_SysDialogAndNoticeUpdateNotify( //只组包不发送
		UINT8 byNotifyType //通知类型1:系统弹窗通知；2、公告更新通知
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：聊天
	virtual void OnRecv_Chat(
		EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
	) = 0;

	struct SWhisperAck : public CClientFuncAck
	{
		UINT16 wMsgID; //返回错误码（0为没有错误）

		SWhisperAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：私聊
	virtual bool OnRecv_Whisper(
		UINT64 qwUsrID, //帐号ID
		const std::string& strInfo, //聊天信息
		const TVecShowInfo& vecShowInfo, //炫耀物品信息
		shared_func<SWhisperAck>& fnAck //返回回调函数
	) = 0;

	struct SGetShowInfoAck : public CClientFuncAck
	{
		SSenderInfo rSenderInfo; //发送者信息
		std::string strShowInfo; //展示信息序列化

		SGetShowInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取炫耀信息
	virtual bool OnRecv_GetShowInfo(
		UINT64 qwInstID, //唯一ID
		shared_func<SGetShowInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SReqWhisperInfoAck : public CClientFuncAck
	{
		SWhisperInfo whisperInfo; //获取私聊对方信息返回

		SReqWhisperInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求私聊信息
	virtual bool OnRecv_ReqWhisperInfo(
		const std::string& strReceiveName, //玩家名字
		shared_func<SReqWhisperInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 28; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_Chat(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Whisper(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetShowInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqWhisperInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGlobalChatProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGlobalChatProt
