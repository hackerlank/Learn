#include "stdafx.h"
#include "User.h"
#include "UserMgr.h"
#include "Archive.h"
#include "MailProtS.h"
#include "Protocols.h"
#include "VarDefine.h"
#include "SysMsgDefine.h"
#include "CenterServerLog.h"
struct SMailInfo
{
    UINT64 qwSenderID;
    UINT64 qwReceiverID;
    string strSender;
    string strReceiver;
    string strTitle;
    string strMsg;
    string strAttachment;
};

//接收：邮件ID请求
void CMailProtS::OnRecv_MailPageIDReq(
        UINT32 uStartIndex, //请求开始序号
        UINT32 uiMailNum, //请求邮件数量
        EMailQueryType eQueryType //邮件类型
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;

    if (uiMailNum > 40)
        return;

    CMailBox& rMailBox = pUser->GetMailBox();
    if(!rMailBox.IsLoadData())
    {
        return ;
    }
    TVecUINT64 vecMailIDs;
    rMailBox.GetMailPageID(uStartIndex, uiMailNum, eQueryType, vecMailIDs);
    Send_MailPageIDAck(vecMailIDs, uStartIndex, rMailBox.GetMailCount(eQueryType),eQueryType);
}

//接收：页邮件列表信息请求
void CMailProtS::OnRecv_MailSummaryListReq(
        const TVecUINT64& vecMailIDList //请求ID列表
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;
    if(!pUser->GetMailBox().IsLoadData())
    {
        return ;
    }
    TVecMailList vecMailSummary;
    pUser->GetMailBox().GetMailSummaryList(vecMailIDList, vecMailSummary);
    Send_MailSummaryListAck(vecMailSummary);
}
void CMailProtS::SignReadMail(CUser &rUser,UINT64 qwMailID)
{
        if(!rUser.GetMailBox().SetMailDetail(qwMailID, eStateReaded))
        {
            return ;
        }

        TVecINT32 vecData;
        vecData.push_back(1);
        rUser.OnEvent(eEventType_MailReading,vecData);
}

//接收：单邮件信息请求
void CMailProtS::OnRecv_MailDetailReq(
        UINT64 uiMailID //邮件ID
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;
    if(!pUser->GetMailBox().IsLoadData())
    {
        return ;
    }
    SMailDetail stDetail;
    if (pUser->GetMailBox().GetMailDetail(uiMailID, stDetail) == true)
    {
        SignReadMail(*pUser,uiMailID);
        Send_MailDetailAck(stDetail);
    }
}

//接收：发送邮件
void CMailProtS::OnRecv_SendMail(
        const std::string& strReceiveName, //接受者姓名
        const std::string& strTitle, //邮件标题
        const std::string& strMsg //邮件内容
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;
    if(!pUser->GetMailBox().IsLoadData())
    {
        return ;
    }
    // check self
    if (pUser->GetUserName() == strReceiveName)
    {
        Send_MailSendResult(EMail_SendFail);
        return;
    }

    // check mail msg length
    if (strMsg.size() > 80 * 3)
    {
        Send_MailSendResult(EMail_SendFail);
        return;
    }

#if 0
    // check mail send lv need
    if (pUser->GetLevel() < CUserMgr::Instance().GetMailSendNeedLv())
    {
        Send2Client_MailSendResult(pUser->GetRoleID(), EMail_SendFail);
        return;
    }
    // check mail send status
    TVecGameAtomicOp vecGameOps;
    SGameOpVarInc* pVarInc = new SGameOpVarInc;
    if (pVarInc == NULL)
        return;
    pVarInc->eVarID = EVAR_MAIL_SEND;
    pVarInc->eBits = EVARBITS_DWORD;
    pVarInc->dwValue = 1;
    pVarInc->dwLimit = CUserMgr::Instance().GetMaxSendCountPerHour();
    vecGameOps.push_back(TPtrSGameOpVar(pVarInc));

    // run atomic
    g_GameCommonC.Send2Server_ProcGameAtomicOp(pUser->GetGSID(), pUser->GetRoleID(), 0, vecGameOps, [qwRoleID, strReceiveName, strTitle, strMsg](EErrCode eErrCode){
            if (eErrCode != EERR_OK)
            {
            Send2Client_MailSendResult(qwRoleID, EMail_OverMaxCount);
            return;
            }

            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if (pUser != NULL)
            pUser->GetMailBox().SendNormalMail(qwRoleID, strReceiveName, strTitle, strMsg);
            });
#endif
    pUser->GetMailBox().SendNormalMail(qwRoleID, strReceiveName, strTitle, strMsg);

}

//接收：删除邮件
void CMailProtS::OnRecv_DeleteMail(
        const TVecUINT64& vecMailIDList //请求ID列表
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;
    if(!pUser->GetMailBox().IsLoadData())
    {
        return ;
    }
    pUser->GetMailBox().RemoveMailFromList(vecMailIDList);
}

//接收：收取附件
void CMailProtS::OnRecv_MailAttachmentGetReq(
        UINT64 qwMailID //邮件ID
        )
{
    UINT64 qwRoleID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;
    if(!pUser->GetMailBox().IsLoadData())
    {
        return ;
    }
    pUser->GetMailBox().GetMailAttachment(qwMailID);
}

// 发送系统邮件
void CMailProtS::SendSystemMail(const string& strReceiveName, const string& strSender, const string& strTitle, const string& strMsgInfo, const string& strAttachment)
{
    shared_ptr<SMailInfo> pMailInfo(new SMailInfo());
    pMailInfo->qwSenderID = 0;
    pMailInfo->qwReceiverID = 0;
    pMailInfo->strSender = strSender;
    pMailInfo->strReceiver = strReceiveName;
    pMailInfo->strTitle = strTitle;
    pMailInfo->strMsg = strMsgInfo;
    pMailInfo->strAttachment = strAttachment;
#if 0 
    g_Center2DBCommC.Send_GetRoleIDFromName(0, strReceiveName, [pMailInfo](UINT8 byRet, UINT64 qwReceiveID){
            shared_ptr<SMailInfo> pInfo = pMailInfo;
            if(byRet != 0 || qwReceiveID == 0)
            {
            Send2Client_MailSendResult(pInfo->qwSenderID, EMail_SendFail);
            return;
            }
            pMailInfo->qwReceiverID = qwReceiveID;

            SaveMail(gGUIDGET(GUID_G::GUID_MAIL), pInfo->qwReceiverID, pInfo->qwSenderID, pInfo->strSender, EMAILTYPE_SYSTEM, pInfo->strTitle, pInfo->strMsg, pInfo->strAttachment);
            });
#endif
}

void CMailProtS::SendSystemMail(const string& strReceiveName, UINT16 wSenderMsgID, UINT16 wTitleMsgID, UINT16 wMsgInfoMsgID, const vector<SMailItemInfo>& rItemInfo)
{
#if 0
    // get msg
    const string& strSender = CUserMgr::Instance().GetGameMsgByID(wSenderMsgID);
    const string& strTitle = CUserMgr::Instance().GetGameMsgByID(wTitleMsgID);
    const string& strMsgInfo = CUserMgr::Instance().GetGameMsgByID(wMsgInfoMsgID);

    // combine item
    TVecMailAttachment vecMailAttachment;

    SItemAttachment* pItem = new SItemAttachment();
    if (pItem == NULL)
        return;

    pItem->vecItemInfo = rItemInfo;

    vecMailAttachment.push_back(TPtrSMailBaseAttachment(pItem));

    string strAttachment;
    CDBOutArchive oar(strAttachment);
    oar << vecMailAttachment;

    // create mail info
    shared_ptr<SMailInfo> pMailInfo(new SMailInfo());
    pMailInfo->qwSenderID = 0;
    pMailInfo->qwReceiverID = 0;
    pMailInfo->strSender = strSender;
    pMailInfo->strReceiver = strReceiveName;
    pMailInfo->strTitle = strTitle;
    pMailInfo->strMsg = strMsgInfo;
    pMailInfo->strAttachment = strAttachment;
    // send mail
    g_Center2DBCommC.Send_GetRoleIDFromName(0, strReceiveName, [pMailInfo](UINT8 byRet, UINT64 qwReceiveID){
            shared_ptr<SMailInfo> pInfo = pMailInfo;
            if(byRet != 0 || qwReceiveID == 0)
            {
            Send2Client_MailSendResult(pInfo->qwSenderID, EMail_SendFail);
            return;
            }
            pMailInfo->qwReceiverID = qwReceiveID;
            pInfo->qwReceiverID = qwReceiveID;

            SaveMail(gGUIDGET(GUID_G::GUID_MAIL), pInfo->qwReceiverID, pInfo->qwSenderID, pInfo->strSender, EMAILTYPE_SYSTEM, pInfo->strTitle, pInfo->strMsg, pInfo->strAttachment);
            });
#endif    
}
#if 0
void CMailProtS::SendSystemMail(const string& strReceiveName, UINT16 wSenderMsgID, UINT16 wTitleMsgID, UINT16 wMsgInfoMsgID, const vector<SMailItemInfo>& rItemInfo)
{
    // get msg
    const string& strSender = CUserMgr::Instance().GetGameMsgByID(wSenderMsgID);
    const string& strTitle = CUserMgr::Instance().GetGameMsgByID(wTitleMsgID);
    const string& strMsgInfo = CUserMgr::Instance().GetGameMsgByID(wMsgInfoMsgID);

    // combine item
    TVecMailAttachment vecMailAttachment;

    SItemBaseCT* pItemBaseCT = new SItemBaseCT();
    if (pItemBaseCT == NULL)
        return;

    pItemBaseCT->vecItems = rItemInfo;

    vecMailAttachment.push_back(TPtrSMailBaseAttachment(pItemBaseCT));

    string strAttachment;
    CDBOutArchive oar(strAttachment);
    oar << vecMailAttachment;

    // create mail info
    shared_ptr<SMailInfo> pMailInfo(new SMailInfo());
    pMailInfo->qwSenderID = 0;
    pMailInfo->qwReceiverID = 0;
    pMailInfo->strSender = strSender;
    pMailInfo->strReceiver = strReceiveName;
    pMailInfo->strTitle = strTitle;
    pMailInfo->strMsg = strMsgInfo;
    pMailInfo->strAttachment = strAttachment;

    // send mail
    g_Center2DBCommC.Send_GetRoleIDFromName(0, strReceiveName, [pMailInfo](UINT8 byRet, UINT64 qwReceiveID){
            shared_ptr<SMailInfo> pInfo = pMailInfo;
            if(byRet != 0 || qwReceiveID == 0)
            {
            Send2Client_MailSendResult(pInfo->qwSenderID, EMail_SendFail);
            return;
            }
            pMailInfo->qwReceiverID = qwReceiveID;
            pInfo->qwReceiverID = qwReceiveID;

            SaveMail(gGUIDGET(GUID_G::GUID_MAIL), pInfo->qwReceiverID, pInfo->qwSenderID, pInfo->strSender, EMAILTYPE_SYSTEM, pInfo->strTitle, pInfo->strMsg, pInfo->strAttachment);
            });
}
#endif
// 保存邮件
void CMailProtS::SaveMail(UINT64 qwMailID, UINT64 qwReceiveID, UINT64 qwSenderID, const std::string& strSenderName, EMailType eType, const std::string& strTitle, const std::string& strMsg, const std::string& strAttachment)
{
    EMailType eMailType = eType;
    UINT32 dwSendTime = time(NULL);//TimeUtil::Now();
    g_Center2DBCommC.Send_SaveMail(qwMailID, qwReceiveID, qwSenderID, strSenderName, eMailType, eStateNew, dwSendTime, strTitle, strMsg/*, strAttachment*/,
            [this,qwMailID, qwReceiveID, qwSenderID, strSenderName, eMailType, dwSendTime, strTitle, strMsg, strAttachment](UINT8 byRet, INT8 byRet_){
            CUserPtr pSender = CUserMgr::GetUserByUserID(qwSenderID);
            if(pSender != NULL)
            {
            pSender->GetMailBox().SetDrawLock(false);
            }
            if (byRet_ == 1)
            {
            pSender->SendSysMsg(eMsgMailMax);
            }
            if (byRet != 0)
            return;

            if (byRet_ != 0)
            return;

            // logger
            this->SaveMailAttachmentLogger(qwMailID, qwReceiveID, 0,  strAttachment, true);

            if (pSender != NULL)
            {
                this->SendClt_MailSendResult(&qwSenderID,1, EMail_SendOk);
                time_t now = Time::Now();
                Time t(now);
                pSender->GetCenterVar().AddVar(NVarDefine::ePlayerVarSendMail,1,t.min());
            }
            NLogDataDefine::SMailLogPtr ptrLog(new NLogDataDefine::SMailLog);
            if(NULL != ptrLog)
            {
            NLogDataDefine::SMailLog& rLog = *ptrLog;
            rLog.dwServerId= Config._wGroup;
            rLog.qwPlayerId = qwReceiveID;
            rLog.qwMailId = qwMailID; 
            rLog.byType = EMAILTYPE_NORMAL; 
            rLog.strTitle = strTitle;
            rLog.strText = strMsg;
            rLog.dwRevTime = dwSendTime;
            CCenterServerLog::LogToDB(ptrLog);
            }

            CUserPtr pReceiver = CUserMgr::GetUserByUserID(qwReceiveID);
            if (pReceiver == NULL)
                return;

            SMailDetail stMailDetail;
            stMailDetail.qwMailID = qwMailID;
            stMailDetail.eMailType = eMailType;
            stMailDetail.vecMailAttachment.clear();
            stMailDetail.eMailState = eStateNew;
            stMailDetail.dwSendTime = dwSendTime;
            stMailDetail.strTitle = strTitle;
            stMailDetail.strSendName = strSenderName;
            stMailDetail.strMessage = strMsg;
            //stMailDetail.strAttachment = strAttachment;
            pReceiver->GetMailBox().AddMailToList(stMailDetail);

            this->SendClt_NewMailNotify(&qwReceiveID,1, 1);
            TVecINT64 vecParam;
            vecParam.push_back(pReceiver->GetMailBox().GetNewMailCount());
            TVecString vecString;
            UINT32 dwSeverID = pReceiver->GetGameSvrID();
            g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID,1,qwReceiveID, eOpAdd, 1, vecParam, vecString);
            });
}

// 记录邮件附件logger
void CMailProtS::SaveMailAttachmentLogger(UINT64 qwMailID, UINT64 qwRoleID, UINT64 qwOPID, const string& strAttachment, bool bIsSend)
{
#if 0
    TVecMailAttachment vecMailAttachment;
    CDBInArchive iar(strAttachment);
    iar >> vecMailAttachment;

    // check size
    if (vecMailAttachment.size() == 0)
        return;

    // get now time
    UINT32 dwNow = TimeUtil::Now();

    for (auto v = vecMailAttachment.begin(); v != vecMailAttachment.end(); ++v)
    {
        if ((*v)->GetClassType() == eType_SItemAttachment)
        {
            SItemAttachment* pItem = dynamic_cast<SItemAttachment*>((*v).get());
            if (pItem != NULL)
            {
                for (auto o = pItem->vecItemInfo.begin(); o != pItem->vecItemInfo.end(); ++o)
                {
                    if (bIsSend)
                    {
                        assert(o->qwOPID != 0 && qwRoleID != 0);
                        g_LoggerProtocolC.Send2Server_LogMailAttChange(0, o->qwOPID, dwNow, qwRoleID, qwMailID, o->id, o->count);
                    }
                    else
                    {
                        assert(qwOPID != 0 && qwRoleID != 0);
                        g_LoggerProtocolC.Send2Server_LogMailAttChange(0, qwOPID, dwNow, qwRoleID, qwMailID, o->id, -o->count);
                    }
                }
            }
        }
    }
#endif
}
