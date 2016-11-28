/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ChatProt.h
//  Purpose:      聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ChatProt.h"

namespace NChatProt
{

//协议类：聊天协议
class CChatProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：聊天信息通知
	bool Send_ChatInfoNotify( //发送给当前协议处理的客户端
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const NGlobalChatProt::SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //聊天信息
		const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
	);
	bool SendClt_ChatInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const NGlobalChatProt::SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //聊天信息
		const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
	);
	std::string& BuildPkg_ChatInfoNotify( //只组包不发送
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const NGlobalChatProt::SSenderInfo& rSenderInfo, //发送者信息
		const std::string& strInfo, //聊天信息
		const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
	);

	//发送：系统信息通知
	bool Send_SystemMsgNotify( //发送给当前协议处理的客户端
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		NGlobalChatProt::EChannelSubType eSubType //额外信息
	);
	bool SendClt_SystemMsgNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		NGlobalChatProt::EChannelSubType eSubType //额外信息
	);
	std::string& BuildPkg_SystemMsgNotify( //只组包不发送
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		NGlobalChatProt::EChannelSubType eSubType //额外信息
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

	//发送：弹窗通知
	bool Send_ElasticFrameNotify( //发送给当前协议处理的客户端
		UINT16 wMsgID //消息ID
	);
	bool SendClt_ElasticFrameNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wMsgID //消息ID
	);
	std::string& BuildPkg_ElasticFrameNotify( //只组包不发送
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

	//发送：气泡提示信息
	bool Send_BubbleNotify( //发送给当前协议处理的客户端
		const NRoleInfoDefine::TVecBubbleInfo& vecBubbleInfo //气泡列表信息
	);
	bool SendClt_BubbleNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const NRoleInfoDefine::TVecBubbleInfo& vecBubbleInfo //气泡列表信息
	);
	std::string& BuildPkg_BubbleNotify( //只组包不发送
		const NRoleInfoDefine::TVecBubbleInfo& vecBubbleInfo //气泡列表信息
	);

	//发送：气泡提示信息更新
	bool Send_BubbleUpdate( //发送给当前协议处理的客户端
		NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
		const NRoleInfoDefine::SBubbleInfo& sBubbleInfo //受影响的气泡信息
	);
	bool SendClt_BubbleUpdate(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
		const NRoleInfoDefine::SBubbleInfo& sBubbleInfo //受影响的气泡信息
	);
	std::string& BuildPkg_BubbleUpdate( //只组包不发送
		NProtoCommon::EDataChange eType, //更新类型，增加，删除，修改
		const NRoleInfoDefine::SBubbleInfo& sBubbleInfo //受影响的气泡信息
	);

	//发送：系统MsgID通知
	bool Send_SystemFormatMsgIDNotifyWithShow( //发送给当前协议处理的客户端
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr, //聊天信息参数
		const NGlobalChatProt::TVecShowInfo& vecShow //炫耀信息
	);
	bool SendClt_SystemFormatMsgIDNotifyWithShow(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr, //聊天信息参数
		const NGlobalChatProt::TVecShowInfo& vecShow //炫耀信息
	);
	std::string& BuildPkg_SystemFormatMsgIDNotifyWithShow( //只组包不发送
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr, //聊天信息参数
		const NGlobalChatProt::TVecShowInfo& vecShow //炫耀信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：聊天
	virtual void OnRecv_Chat(
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
	) = 0;

	struct SBubbleGetAck : public CClientFuncAck
	{
		NRoleInfoDefine::TVecBubbleInfo vecBubbleInfo; //气泡列表信息

		SBubbleGetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：气泡信息获取
	virtual bool OnRecv_BubbleGet(
		shared_func<SBubbleGetAck>& fnAck //返回回调函数
	) = 0;

	struct SBubbleRespondAck : public CClientFuncAck
	{
		EBubbleResult eResult; //气泡操作返回结果

		SBubbleRespondAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：气泡回应
	virtual bool OnRecv_BubbleRespond(
		UINT16 wIndex, //气泡对应位置
		const TVecINT64& vecParam, //整型变量
		const TVecString& vecString, //字符串型变量
		shared_func<SBubbleRespondAck>& fnAck //返回回调函数
	) = 0;

	//接收：邀请平台好友成功
	virtual void OnRecv_InviteSuc(
		UINT64 qwRoleID //被邀请人
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 23; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_Chat(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BubbleGet(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BubbleRespond(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InviteSuc(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CChatProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NChatProt
