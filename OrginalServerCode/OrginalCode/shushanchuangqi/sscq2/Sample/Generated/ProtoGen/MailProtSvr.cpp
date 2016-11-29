/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MailProt.cpp
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MailProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMailProt
{

CMailProtSvr::THandleFunc CMailProtSvr::_HandleFuncs[] =
{
	&CMailProtSvr::_DoRecv_MailPageIDReq, //FuncID: 1
	&CMailProtSvr::_DoRecv_MailSummaryListReq, //FuncID: 2
	&CMailProtSvr::_DoRecv_MailDetailReq, //FuncID: 3
	&CMailProtSvr::_DoRecv_SendMail, //FuncID: 4
	&CMailProtSvr::_DoRecv_DeleteMail, //FuncID: 5
	&CMailProtSvr::_DoRecv_MailAttachmentGetReq, //FuncID: 6
};

bool CMailProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	INT8 byFuncID = pBuf[0];
	if(byFuncID == 0 || byFuncID > (INT8)ARRAYSIZE(_HandleFuncs))
	{
#ifdef _DEBUG
		LOG_CRI << "byFuncID is invalid: " << byFuncID;
#endif
		return false;
	}
	pBuf += sizeof(INT8);
	dwLen -= sizeof(INT8);
	if(byFuncID > 0)
	{
		--byFuncID;
		if(_HandleFuncs[static_cast<UINT8>(byFuncID)] != NULL)
			return (this->*_HandleFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);
	}
	return true;
}

//发送：页邮件ID回答
bool CMailProtSvr::Send_MailPageIDAck(
	const TVecUINT64& vecMailIDList, //页面ID列表
	UINT32 uStartIndex, //当前请求索引
	UINT32 uMailTotalNum, //邮件总数量
	EMailQueryType eQueryType //邮件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailIDList << uStartIndex << uMailTotalNum << (UINT8&)eQueryType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 19, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMailProtSvr::SendClt_MailPageIDAck(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecUINT64& vecMailIDList, //页面ID列表
	UINT32 uStartIndex, //当前请求索引
	UINT32 uMailTotalNum, //邮件总数量
	EMailQueryType eQueryType //邮件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailIDList << uStartIndex << uMailTotalNum << (UINT8&)eQueryType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 19, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMailProtSvr::BuildPkg_MailPageIDAck(
	const TVecUINT64& vecMailIDList, //页面ID列表
	UINT32 uStartIndex, //当前请求索引
	UINT32 uMailTotalNum, //邮件总数量
	EMailQueryType eQueryType //邮件类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailIDList << uStartIndex << uMailTotalNum << (UINT8&)eQueryType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 19, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：页邮件列表信息回答
bool CMailProtSvr::Send_MailSummaryListAck(
	const TVecMailList& vecMailList //邮件列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 19, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMailProtSvr::SendClt_MailSummaryListAck(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecMailList& vecMailList //邮件列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 19, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMailProtSvr::BuildPkg_MailSummaryListAck(
	const TVecMailList& vecMailList //邮件列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 19, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：页邮件列表信息回答
bool CMailProtSvr::Send_MailDetailAck(
	const SMailDetail& rMailDetail //邮件详细信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rMailDetail;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 19, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMailProtSvr::SendClt_MailDetailAck(const UINT64* pUsrID_, UINT16 wCnt_,
	const SMailDetail& rMailDetail //邮件详细信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rMailDetail;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 19, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMailProtSvr::BuildPkg_MailDetailAck(
	const SMailDetail& rMailDetail //邮件详细信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << rMailDetail;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 19, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：新邮件通知
bool CMailProtSvr::Send_NewMailNotify(
	UINT8 byIsFrameNotify //1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << byIsFrameNotify;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 19, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMailProtSvr::SendClt_NewMailNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byIsFrameNotify //1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << byIsFrameNotify;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 19, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMailProtSvr::BuildPkg_NewMailNotify(
	UINT8 byIsFrameNotify //1:需要弹框显示 0:不需要弹框显示(邮件闪烁)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << byIsFrameNotify;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 19, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：邮件发送结果
bool CMailProtSvr::Send_MailSendResult(
	EMailErrorResult eErrorResult //返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eErrorResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 19, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMailProtSvr::SendClt_MailSendResult(const UINT64* pUsrID_, UINT16 wCnt_,
	EMailErrorResult eErrorResult //返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eErrorResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 19, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMailProtSvr::BuildPkg_MailSendResult(
	EMailErrorResult eErrorResult //返回结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eErrorResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 19, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：邮件发送结果
bool CMailProtSvr::Send_MailDeleteResult(
	const TVecUINT64& vecMailIDList, //请求ID列表
	EMailErrorResult eErrorResult //返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailIDList << (UINT8&)eErrorResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 19, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMailProtSvr::SendClt_MailDeleteResult(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecUINT64& vecMailIDList, //请求ID列表
	EMailErrorResult eErrorResult //返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailIDList << (UINT8&)eErrorResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 19, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMailProtSvr::BuildPkg_MailDeleteResult(
	const TVecUINT64& vecMailIDList, //请求ID列表
	EMailErrorResult eErrorResult //返回结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecMailIDList << (UINT8&)eErrorResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 19, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：收取附件结果
bool CMailProtSvr::Send_MailAttachmentGetAck(
	UINT64 qwMailID, //邮件ID
	EMailDRawResult eReSult //提取附件结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwMailID << (UINT8&)eReSult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 19, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMailProtSvr::SendClt_MailAttachmentGetAck(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwMailID, //邮件ID
	EMailDRawResult eReSult //提取附件结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwMailID << (UINT8&)eReSult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 19, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMailProtSvr::BuildPkg_MailAttachmentGetAck(
	UINT64 qwMailID, //邮件ID
	EMailDRawResult eReSult //提取附件结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwMailID << (UINT8&)eReSult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 19, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CMailProtSvr::_DoRecv_MailPageIDReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 uStartIndex = 0;
	UINT32 uiMailNum = 0;
	EMailQueryType eQueryType = (EMailQueryType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> uStartIndex >> uiMailNum >> (UINT8&)eQueryType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 19, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_MailPageIDReq(uStartIndex, uiMailNum, eQueryType);
	return true;
}

bool CMailProtSvr::_DoRecv_MailSummaryListReq(const char* pBuf_, UINT32 dwLen_)
{
	TVecUINT64 vecMailIDList;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecMailIDList;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 19, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_MailSummaryListReq(vecMailIDList);
	return true;
}

bool CMailProtSvr::_DoRecv_MailDetailReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 uiMailID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> uiMailID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 19, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_MailDetailReq(uiMailID);
	return true;
}

bool CMailProtSvr::_DoRecv_SendMail(const char* pBuf_, UINT32 dwLen_)
{
	std::string strReceiveName;
	std::string strTitle;
	std::string strMsg;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> strReceiveName >> strTitle >> strMsg;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 19, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_SendMail(strReceiveName, strTitle, strMsg);
	return true;
}

bool CMailProtSvr::_DoRecv_DeleteMail(const char* pBuf_, UINT32 dwLen_)
{
	TVecUINT64 vecMailIDList;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecMailIDList;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 19, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_DeleteMail(vecMailIDList);
	return true;
}

bool CMailProtSvr::_DoRecv_MailAttachmentGetReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwMailID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwMailID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 19, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_MailAttachmentGetReq(qwMailID);
	return true;
}

} //namespace NMailProt
