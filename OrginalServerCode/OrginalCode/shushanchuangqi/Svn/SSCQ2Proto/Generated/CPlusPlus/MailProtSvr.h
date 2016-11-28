/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MailProt.h
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "MailProt.h"

namespace NMailProt
{

//协议类：邮件CenterServer通讯协议
class CMailProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：页邮件ID回答
	bool Send_MailPageIDAck( //发送给当前协议处理的客户端
		const TVecUINT64& vecMailIDList, //页面ID列表
		UINT32 uStartIndex, //当前请求索引
		UINT32 uMailTotalNum, //邮件总数量
		EMailQueryType eQueryType //邮件类型
	);
	bool SendClt_MailPageIDAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecUINT64& vecMailIDList, //页面ID列表
		UINT32 uStartIndex, //当前请求索引
		UINT32 uMailTotalNum, //邮件总数量
		EMailQueryType eQueryType //邮件类型
	);
	std::string& BuildPkg_MailPageIDAck( //只组包不发送
		const TVecUINT64& vecMailIDList, //页面ID列表
		UINT32 uStartIndex, //当前请求索引
		UINT32 uMailTotalNum, //邮件总数量
		EMailQueryType eQueryType //邮件类型
	);

	//发送：页邮件列表信息回答
	bool Send_MailSummaryListAck( //发送给当前协议处理的客户端
		const TVecMailList& vecMailList //邮件列表
	);
	bool SendClt_MailSummaryListAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecMailList& vecMailList //邮件列表
	);
	std::string& BuildPkg_MailSummaryListAck( //只组包不发送
		const TVecMailList& vecMailList //邮件列表
	);

	//发送：页邮件列表信息回答
	bool Send_MailDetailAck( //发送给当前协议处理的客户端
		const SMailDetail& rMailDetail //邮件详细信息
	);
	bool SendClt_MailDetailAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SMailDetail& rMailDetail //邮件详细信息
	);
	std::string& BuildPkg_MailDetailAck( //只组包不发送
		const SMailDetail& rMailDetail //邮件详细信息
	);

	//发送：新邮件通知
	bool Send_NewMailNotify( //发送给当前协议处理的客户端
		UINT8 byIsFrameNotify //1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
	);
	bool SendClt_NewMailNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byIsFrameNotify //1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
	);
	std::string& BuildPkg_NewMailNotify( //只组包不发送
		UINT8 byIsFrameNotify //1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
	);

	//发送：邮件发送结果
	bool Send_MailSendResult( //发送给当前协议处理的客户端
		EMailErrorResult eErrorResult //返回结果
	);
	bool SendClt_MailSendResult(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EMailErrorResult eErrorResult //返回结果
	);
	std::string& BuildPkg_MailSendResult( //只组包不发送
		EMailErrorResult eErrorResult //返回结果
	);

	//发送：邮件发送结果
	bool Send_MailDeleteResult( //发送给当前协议处理的客户端
		const TVecUINT64& vecMailIDList, //请求ID列表
		EMailErrorResult eErrorResult //返回结果
	);
	bool SendClt_MailDeleteResult(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecUINT64& vecMailIDList, //请求ID列表
		EMailErrorResult eErrorResult //返回结果
	);
	std::string& BuildPkg_MailDeleteResult( //只组包不发送
		const TVecUINT64& vecMailIDList, //请求ID列表
		EMailErrorResult eErrorResult //返回结果
	);

	//发送：收取附件结果
	bool Send_MailAttachmentGetAck( //发送给当前协议处理的客户端
		UINT64 qwMailID, //邮件ID
		EMailDRawResult eReSult //提取附件结果
	);
	bool SendClt_MailAttachmentGetAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwMailID, //邮件ID
		EMailDRawResult eReSult //提取附件结果
	);
	std::string& BuildPkg_MailAttachmentGetAck( //只组包不发送
		UINT64 qwMailID, //邮件ID
		EMailDRawResult eReSult //提取附件结果
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：邮件ID请求
	virtual void OnRecv_MailPageIDReq(
		UINT32 uStartIndex, //请求开始序号
		UINT32 uiMailNum, //请求邮件数量
		EMailQueryType eQueryType //邮件类型
	) = 0;

	//接收：页邮件列表信息请求
	virtual void OnRecv_MailSummaryListReq(
		const TVecUINT64& vecMailIDList //请求ID列表
	) = 0;

	//接收：单邮件信息请求
	virtual void OnRecv_MailDetailReq(
		UINT64 uiMailID //邮件ID
	) = 0;

	//接收：发送邮件
	virtual void OnRecv_SendMail(
		const std::string& strReceiveName, //接受者姓名
		const std::string& strTitle, //邮件标题
		const std::string& strMsg //邮件内容
	) = 0;

	//接收：删除邮件
	virtual void OnRecv_DeleteMail(
		const TVecUINT64& vecMailIDList //请求ID列表
	) = 0;

	//接收：收取附件
	virtual void OnRecv_MailAttachmentGetReq(
		UINT64 qwMailID //邮件ID
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 19; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_MailPageIDReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MailSummaryListReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MailDetailReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DeleteMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MailAttachmentGetReq(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CMailProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NMailProt
