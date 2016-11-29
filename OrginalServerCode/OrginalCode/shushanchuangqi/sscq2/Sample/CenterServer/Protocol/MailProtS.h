
#pragma once
#include "MailProtSvr.h"

using namespace NMailProt;

class CMailProtS : public CMailProtSvr
{
public:
    //接收：邮件ID请求
    virtual void OnRecv_MailPageIDReq(
        UINT32 uStartIndex, //请求开始序号
        UINT32 uiMailNum, //请求邮件数量
        EMailQueryType eQueryType //邮件类型
        );

    //接收：页邮件列表信息请求
    virtual void OnRecv_MailSummaryListReq(
        const TVecUINT64& vecMailIDList //请求ID列表
        );

    //接收：单邮件信息请求
    virtual void OnRecv_MailDetailReq(
        UINT64 uiMailID //邮件ID
        );

    //接收：发送邮件
    virtual void OnRecv_SendMail(
        const std::string& strReceiveName, //接受者姓名
        const std::string& strTitle, //邮件标题
        const std::string& strMsg //邮件内容
        );

    //接收：删除邮件
    virtual void OnRecv_DeleteMail(
        const TVecUINT64& vecMailIDList //请求ID列表
        );

    //接收：收取附件
    virtual void OnRecv_MailAttachmentGetReq(
        UINT64 qwMailID //邮件ID
        );
public:
    // 发送系统邮件
    void SendSystemMail(const string& strReceiveName, const string& strSender, const string& strTitle, const string& strMsgInfo, const string& strAttachment);
    void SendSystemMail(const string& strReceiveName, UINT16 wSenderMsgID, UINT16 wTitleMsgID, UINT16 wMsgInfoMsgID, const vector<SMailItemInfo>& rItemInfo);
    // 保存邮件
    void SaveMail(UINT64 qwMailID, UINT64 qwReceiveID, UINT64 qwSenderID, const std::string& strSenderName, EMailType eType, const std::string& strTitle, const std::string& strMsg, const std::string& strAttachment);
    // 记录邮件附件logger
    void SaveMailAttachmentLogger(UINT64 qwMailID, UINT64 qwRoleID, UINT64 qwOPID, const string& strAttachment, bool bIsSend);
    //标记已阅读邮件
    void SignReadMail(CUser &rUser,UINT64 qwMailID);
};
