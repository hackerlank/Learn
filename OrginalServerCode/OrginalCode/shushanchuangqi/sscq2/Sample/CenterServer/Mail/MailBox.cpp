#include "stdafx.h"
#include "MailBox.h"
#include "UserMgr.h"
#include "User.h"
//#include "OPIDMgr.h"
//#include "Utility/GUID.h"
#include "Network/Protocols.h"
#include "SystemMail.h" 
#include "VarDefine.h"
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "CenterServerLog.h"
UINT32 CMailBox::GetMailCount(EMailQueryType eQueryType) const
{

    UINT32 dwCount = 0;
    for (auto v = _vecMail.rbegin() ; v != _vecMail.rend(); ++v)
    {
        bool bFind = false;
        switch(eQueryType)
        {
            case eQueryNew:
                {
                    bFind = (eStateNew == v->eMailState);
                }
                break;
            case eQueryReaded:
                {
                    bFind = (eStateReaded == v->eMailState);
                }
                break;
            case eQueryTotal:
                {
                    bFind = true;
                }
                break;
            case eQueryPerson:
                {
                    bFind = (EMAILTYPE_NORMAL == v->eMailType);
                }
                break;
            case eQuerysysTem:
                {
                    bFind = (EMAILTYPE_SYSTEM == v->eMailType);
                }
                break;
            case eQueryAttch:
                {
                    bFind = ((v->byGeted > 0) && (v->byGeted != ATTACH_MAX ) );

                }
                break;
            default:
                break;
        }
        if (!bFind)
        {
            continue;
        }
        dwCount++;
    }

    return dwCount;
}

void CMailBox::AddItemInfo( vector<SMailItemInfo> &vecResults,const SMailItemInfo &rItem )
{
    bool notFound = true;
    for(auto p=vecResults.begin(),e=vecResults.end(); p!=e; ++p)
    {
        if(p->qwInstID != rItem.qwInstID)
        {
            continue;
        }
        if(p->wItemID != rItem.wItemID)
        {
            continue;
        }
        if(p->qwOPID != rItem.qwOPID)
        {
            continue;
        }
        if(p->eBindType != rItem.eBindType)
        {
            continue;
        }
        if(p->byExpired != rItem.byExpired)
        {
            continue;
        }
        if(p->dwExpireTime != rItem.dwExpireTime)
        {
            continue;
        }
        notFound = false;
        p->wCount += rItem.wCount;
    }
    if(notFound)
    {
        vecResults.push_back(rItem);
    }
}

void CMailBox::AddVecItemInfo(vector<SMailItemInfo> &vecResults,const vector<SMailItemInfo> &SourceItems)
{
    for(auto iter = SourceItems.begin();iter != SourceItems.end();iter++)
    {
        AddItemInfo(vecResults,*iter);
    }
}

CMailBox::CMailBox(CUser& rUser) : _rOwnerUser(rUser), _qwCheckCount(0)
{
    _vecMail.clear();
    _vecInvalidMailIDs.clear();
    SetLoadData(false);
    SetDrawLock(false);
}

CMailBox::~CMailBox()
{

}

//加载邮件列表 
void CMailBox::LoadMailList()
{
    if(IsLoadData())
    {
        return ;
    }
    UINT64 qwRoleID = _rOwnerUser.GetUserID();
    g_Center2DBCommC.Send_GetAllMailList(_rOwnerUser.GetUserID(), 0/*TimeUtil::Now() - MAIL_SEVEN_DAYS*/, 
            [qwRoleID, this](UINT8 byRet_, const TVecMailDetail& vecMails)
            {
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if (pUser == NULL)
            return;
            pUser->GetMailBox().SetLoadData(true);
            // get now time
            UINT32 dwNow = time(NULL);// TimeUtil::Now();

            // collect valid mail
            for (auto v = vecMails.begin(); v != vecMails.end(); ++v)
            {
            if (IsMailOverTime(dwNow, *v) == true)
            {
            MailDelData stDelData;
            stDelData.qwMailID = v->qwMailID;
            stDelData.byGet = v->byGeted;
            _vecInvalidMailIDs.push_back(stDelData);
            continue;
            }
            AddMailToList(*v);
            SortMail();
            }


    // check new mail
    UINT32 dwNewCount = 0;
    for (auto v = vecMails.begin(); v != vecMails.end(); ++v)
    {
        if (v->eMailState == eStateNew)
            ++dwNewCount;
    }
    if (dwNewCount > 0)
    {
        UINT64 qwUserID = _rOwnerUser.GetUserID();
        g_MailProtS.SendClt_NewMailNotify(&qwUserID,1, 0);

        TVecINT64 vecParam;
        TVecString vecString;
        vecParam.push_back(dwNewCount);
        UINT32 dwSeverID = _rOwnerUser.GetGameSvrID();
        g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID, 1, qwUserID, eOpAdd, 1, vecParam, vecString);
    }
            });
}

//分页获取邮件
void CMailBox::GetMailPageID(UINT32 dwStartIndex, UINT32 dwReqNum, EMailQueryType eQueryType, TVecUINT64& vecMailIDs)
{
    if (dwStartIndex >= _vecMail.size())
        return;

    UINT32 dwCount = 0;
    UINT32 dwPreCount =0;
    for (auto v = _vecMail.rbegin() ; v != _vecMail.rend(); ++v)
    {
        bool bFind = false;
        switch(eQueryType)
        {
            case eQueryNew:
                {
                    bFind = (eStateNew == v->eMailState);
                }
                break;
            case eQueryReaded:
                {
                    bFind = (eStateReaded == v->eMailState);
                }
                break;
            case eQueryTotal:
                {
                    bFind = true;
                }
                break;
            case eQueryPerson:
                {
                    bFind = (EMAILTYPE_NORMAL == v->eMailType);
                }
                break;
            case eQuerysysTem:
                {
                    bFind = (EMAILTYPE_SYSTEM == v->eMailType);
                }
                break;
            case eQueryAttch:
                {
                    bFind = ((v->byGeted > 0) && (v->byGeted != ATTACH_MAX ) );

                }
                break;
            default:
                {
                }
                break;
        }
        if (!bFind)
        {
            continue;
        }
        dwPreCount++;
        if(dwPreCount > dwStartIndex)
        {
            if (dwCount++ >= dwReqNum)
                break;
        }
        else 
        {
            continue;
        }

        vecMailIDs.push_back(v->qwMailID);
    }
}

//  获得邮件列表
void CMailBox::GetMailSummaryList(const TVecUINT64& vecMailIDs, TVecMailList& vecMailSummary)
{
    for (auto v = _vecMail.rbegin(); v != _vecMail.rend(); ++v)
    {
        auto p = find(vecMailIDs.begin(), vecMailIDs.end(), v->qwMailID);
        if (p == vecMailIDs.end())
            continue;

        SMailSummary stSummary;

        stSummary.uMailID = v->qwMailID;
        stSummary.eMailType = v->eMailType;
        stSummary.eMailState = v->eMailState;
        stSummary.uSendTime = v->dwSendTime;
        /*
           if (v->vecMailAttachment.empty() == true)
           stSummary.byHasAttachment = 0;
           else
           stSummary.byHasAttachment = !v->byGeted;
           */
        stSummary.byHasAttachment = ((v->byGeted > 0) && (v->byGeted < ATTACH_MAX));
        stSummary.strTitle = v->strTitle;
        stSummary.strSendName = v->strSendName;

        vecMailSummary.push_back(stSummary);
    }
}

//获得邮件详细信息
bool CMailBox::GetMailDetail(UINT64 qwMailID, SMailDetail& rMailDetail)
{
    for (auto v = _vecMail.begin(); v != _vecMail.end(); ++v)
    {
        if (v->qwMailID == qwMailID)
        {
            rMailDetail = *v;

            // CInArchive iar(rMailDetail.strAttachment);
            //iar >> rMailDetail.vecMailAttachment;

            return true;
        }
    }

    return false;
}

// 邮件是否过期
bool CMailBox::IsMailOverTime(UINT32 dwNow, const SMailDetail& rDetail)
{

    UINT32 dwOverTime = dwNow - MAIL_THIRTY_DAYS;
    if ((rDetail.byGeted == 0 || rDetail.byGeted == ATTACH_MAX) && dwOverTime > rDetail.dwSendTime)
        return true;
    return false;
}

//设置邮件状态
bool CMailBox::SetMailDetail(UINT64 qwMailID, EMailState eMailState)
{
    for (auto v = _vecMail.begin(); v != _vecMail.end(); ++v)
    {
        if (v->qwMailID == qwMailID)
        {
            // update mail status
            if (v->eMailState != eMailState)
            {
                g_Center2DBCommC.Send_UpdateMailStatus(v->qwMailID, eMailState,[qwMailID](UINT8 byRet_,UINT8 byRet){
                        if(byRet_ != 0 ||byRet != 0)
                        {
                        LOG_CRI << "CMailBox::SetMailDetail :" << qwMailID <<"DB Return False!";
                        }
                        });
                v->eMailState = eMailState;
            }
            return true;
        }
    }

    return false;
}

// 添加一份邮件
bool CMailBox::AddMailToList(const SMailDetail& rMailDetail)
{
    // check duplicate mail
    for (auto v = _vecMail.begin(); v != _vecMail.end(); ++v)
    {
        if (v->qwMailID == rMailDetail.qwMailID)
            return false;
    }
    if(rMailDetail.eMailType ==  EMAILTYPE_SYSTEM)
    {
        SMailDetail tepMailDetail(rMailDetail);
        CSystemMail::DBStringToShowString(tepMailDetail.strMessage,tepMailDetail.strMessage);
        _vecMail.push_back(tepMailDetail);
    }
    else
    {
        _vecMail.push_back(rMailDetail);
    }
    return true;
}

// 删除邮件
void CMailBox::RemoveMailFromList(const TVecUINT64& vecSourceMailIDs)
{
    // get valid id
    if(IsDrawLock())
    { 
        return;
    }
    TVecMailDelData  vecValidDatas;
    TVecUINT64 vecValidIDs;
    for (auto v = vecSourceMailIDs.begin(); v != vecSourceMailIDs.end(); ++v)
    {
        SMailDetail  stMail;
        if (GetMailDetail(*v, stMail) == false)
            continue;

        if (stMail.byGeted > 0 && stMail.byGeted != ATTACH_MAX)
            continue;
        MailDelData stDelData;
        stDelData.qwMailID = stMail.qwMailID;
        stDelData.byGet = stMail.byGeted;
        vecValidDatas.push_back(stDelData);
        vecValidIDs.push_back(stMail.qwMailID);
    }
    SetDrawLock(true);
    // delete mail
    UINT64 qwRoleID = _rOwnerUser.GetUserID();
    g_Center2DBCommC.Send_DeleteMail( qwRoleID,vecValidDatas, [this, qwRoleID,vecValidIDs](UINT8 byRet_, INT8 byRet){
            SetDrawLock(false);
            if(byRet != 0 || byRet != 0)
            {
            g_MailProtS.SendClt_MailDeleteResult(&qwRoleID,1, vecValidIDs, EMail_DeleteFail);
            return;
            }

            if (vecValidIDs.size() == 0)
            {
            g_MailProtS.SendClt_MailDeleteResult(&qwRoleID,1, vecValidIDs, EMail_DeleteFail);
            return;
            }
            for(auto it = vecValidIDs.begin();it != vecValidIDs.end();it++)
            {
            NLogDataDefine::SMailLogPtr ptrLog(new NLogDataDefine::SMailLog);
            if(ptrLog != NULL)
            {
            NLogDataDefine::SMailLog &rLog = *ptrLog;
            rLog.dwServerId= Config._wGroup;
            rLog.qwPlayerId = _rOwnerUser.GetUserID();
            rLog.qwMailId  = *it;
            rLog.byState = 2;
            rLog.dwDelTime = time(NULL);
            CCenterServerLog::LogToDB(ptrLog);
            }
            }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;

    for (auto v = _vecMail.begin(); v != _vecMail.end();)
    {
        auto p = find(vecValidIDs.begin(), vecValidIDs.end(), v->qwMailID);
        if (p == vecValidIDs.end())
        {
            ++v;
            continue;
        }

        v = _vecMail.erase(v);
    }
    g_MailProtS.SendClt_MailDeleteResult(&qwRoleID,1, vecValidIDs, EMail_DeleteOk);
    });
}

// 获取邮件附件
void CMailBox::GetMailAttachment(UINT64 qwMailID)
{
    if (_vecMail.empty() == true)
        return;

    SMailDetail* pDetail = NULL;
    for (auto v = _vecMail.begin(); v != _vecMail.end(); ++v)
    {
        if (v->qwMailID == qwMailID)
        {
            pDetail = &(*v);
            break;
        }
    }
    if (pDetail == NULL)
        return;
    if (pDetail->qwMailID == 0)
        return;
    TVecMailAttachment &vecMailAttachment = pDetail->vecMailAttachment;
    if (pDetail->byGeted == 0 || pDetail->byGeted == ATTACH_MAX)
        return;
    if(IsDrawLock())
    {
        PushWaitDraw(qwMailID);
        return ;
    }
    //提取锁定
    SetDrawLock(true);
    //向GameServer询问，可否提取
    UINT32 ServerId =_rOwnerUser.GetGameSvrID();
    UINT64 qwUserID = _rOwnerUser.GetUserID();
    UINT8 byGet = pDetail->byGeted;
    g_Game2CenterCommS.SendSvr_CheckMailAttch(&ServerId,1,qwUserID,qwMailID,vecMailAttachment,
            [vecMailAttachment,qwMailID,byGet,this](UINT8 byRet_,UINT8 byCan)
            {
            if(byRet_ != 0 || byCan != 0)
            {
            // TODO:返回，包裹放不下
            UINT64 qwUserID = _rOwnerUser.GetUserID();
            g_MailProtS.SendClt_MailAttachmentGetAck(&qwUserID,1,qwMailID,PACK_FULL);
            _setWaitDraw.clear();
            SetDrawLock(false);
            return;
            }
            MailDelData delData;
            delData.qwMailID = qwMailID;
            delData.byGet = byGet;
            g_Center2DBCommC.Send_DelMailAttach(delData,
                [vecMailAttachment,qwMailID,this](UINT8 byRet_,INT8 byRet)
                {
                if(byRet_ != 0 || byRet != 0)
                {
                // 返回，包裹放不下
                UINT64 qwUserID = _rOwnerUser.GetUserID();
                g_MailProtS.SendClt_MailAttachmentGetAck(&qwUserID,1,qwMailID,PACK_FULL);
                _setWaitDraw.clear();
                SetDrawLock(false);  
                return ;
                }
                SMailDetail* pDetail = NULL;
                for (auto v = _vecMail.begin(); v != _vecMail.end(); ++v)
                {
                if (v->qwMailID == qwMailID)
                { 
                pDetail = &(*v);
                break;
                }
                }
                //向GameSver发送附件
                UINT32 ServerId =_rOwnerUser.GetGameSvrID();
                g_Game2CenterCommS.SendSvr_SendMailAttch(&ServerId,1,_rOwnerUser.GetUserID(),qwMailID,vecMailAttachment);
                //改变当前服务器的状态
                if( pDetail != NULL)
                {
                    pDetail->byGeted = ATTACH_MAX;
                    pDetail->vecMailAttachment.clear();
                    g_MailProtS.SignReadMail(_rOwnerUser,qwMailID);
                }
                TVecINT32 vecData;
                vecData.push_back(1);
                _rOwnerUser.OnEvent(eEventType_MailReceiving,vecData);
                //返回，成功
                UINT64 qwUserID = _rOwnerUser.GetUserID();
                g_MailProtS.SendClt_MailAttachmentGetAck(&qwUserID,1,qwMailID,DRAW_SUC);
                NLogDataDefine::SMailLogPtr ptrLog(new NLogDataDefine::SMailLog);
                if(ptrLog != NULL)
                {
                    NLogDataDefine::SMailLog &rLog = *ptrLog;
                    rLog.dwServerId= Config._wGroup;
                    rLog.qwPlayerId = _rOwnerUser.GetUserID();
                    rLog.qwMailId  = qwMailID;
                    rLog.byState = 1;
                    rLog.dwRevTime = time(NULL);
                    CCenterServerLog::LogToDB(ptrLog);
                }
                _setWaitDraw.erase(qwMailID);
                SetDrawLock(false);

                });
            });
}

//发送普通邮件
void CMailBox::SendNormalMail(UINT64 qwRoleID, const std::string& strReceiveName, const std::string& strTitle, const std::string& strMsg)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser == NULL)
        return;

    // collect mail info
    shared_ptr<SMailDetail> pMailInfo(new SMailDetail());
    pMailInfo->qwMailID = 0;
    pMailInfo->eMailState = eStateNew;
    pMailInfo->dwSendTime = 0;
    pMailInfo->byGeted = 1;
    pMailInfo->eMailType = EMAILTYPE_NORMAL;
    pMailInfo->vecMailAttachment.clear();
    pMailInfo->strTitle = strTitle;
    pMailInfo->strSendName = pUser->GetUserName();
    pMailInfo->strMessage = strMsg;
    //pMailInfo->strAttachment.clear();
    if(pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarSendMail) >= SParamConfig::byMailHourLimit)
    {
        pUser->SendSysMsg(eMsgMailLimit);
        return ;
    }
    if(IsDrawLock())
    {
        return ;
    }
    SetDrawLock(true);
    UINT64 qwSenderID = pUser->GetUserID();
    g_Center2DBCommC.Send_GetUserIDFromName( strReceiveName, [this,pMailInfo, qwSenderID](UINT8 byRet, UINT64 qwReceiveID){
            if(byRet != 0 || qwReceiveID == 0)
            {
            g_MailProtS.SendClt_MailSendResult(&qwSenderID,1, EMail_SendFail);
            SetDrawLock(false);
            return;
            }
            g_MailProtS.SaveMail(GET_GUID(GUID_MAIL), qwReceiveID, qwSenderID, pMailInfo->strSendName, EMAILTYPE_NORMAL, pMailInfo->strTitle, pMailInfo->strMessage, "");
            });
}

//时间检测
void CMailBox::TimerCheck()
{
    if (GetTickCount64() - _qwCheckCount > MAIL_REFRESH_TIME || GetTickCount64() < _qwCheckCount)
    {
        UINT32 dwCurTime = time(NULL);//TimeUtil::Now();
        for (auto v = _vecMail.begin(); v != _vecMail.end();)
        {
            if (IsMailOverTime(dwCurTime, *v) == true)
            {
                MailDelData stDelData;
                stDelData.qwMailID = v->qwMailID;
                stDelData.byGet = v->byGeted;
                _vecInvalidMailIDs.push_back(stDelData);
                v = _vecMail.erase(v);
                continue;;
            }

            ++v;
        }

        // set overtime mail
        if (_vecInvalidMailIDs.empty() == false)
        {
            UINT64 qwRoleID = _rOwnerUser.GetUserID();
            g_Center2DBCommC.Send_DeleteMail(qwRoleID,_vecInvalidMailIDs, [qwRoleID](UINT8 byRet_, INT8 byDBRet){
                    if (byRet_ != 0 || byDBRet != 0)
                    return;
                    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
                    if (pUser != NULL)
                    {
                    TVecUINT64 vecDel;
                    for(auto it = pUser->GetMailBox()._vecInvalidMailIDs.begin();it != pUser->GetMailBox()._vecInvalidMailIDs.end();it++)
                    {
                    vecDel.push_back((*it).qwMailID);
                    }
                    for(auto it = vecDel.begin();it != vecDel.end();it++)
                    {
                    NLogDataDefine::SMailLogPtr ptrLog(new NLogDataDefine::SMailLog);
                    if(ptrLog != NULL)
                    {
                    NLogDataDefine::SMailLog& rLog = *ptrLog;
                    rLog.dwServerId= Config._wGroup;
                    rLog.qwPlayerId = qwRoleID;
                    rLog.qwMailId  = *it;
                    rLog.byState = 3;
                    rLog.dwDelTime = time(NULL);
                    CCenterServerLog::LogToDB(ptrLog);
                    }
                    }
            g_MailProtS.SendClt_MailDeleteResult(&qwRoleID,1,vecDel, EMail_DeleteFail);
            pUser->GetMailBox()._vecInvalidMailIDs.clear();
                    }
            return;

            });
        }

        _qwCheckCount = GetTickCount64();
    } 
}

UINT32 CMailBox::GetNewMailCount() const
{
    UINT32 dwNewCount = 0;
    for (auto v = _vecMail.begin(); v != _vecMail.end(); ++v)
    {
        if (v->eMailState == eStateNew)
            ++dwNewCount;
    }
    return dwNewCount;

}

void CMailBox::SetDrawLock(bool bLock)
{
    _bDrawLock = bLock;
    if(!bLock)
    {
        if(!_setWaitDraw.empty())
        {
            //do提取邮件,可能加锁
            UINT64 qwMailId = *(_setWaitDraw.begin());
            _setWaitDraw.erase(_setWaitDraw.begin());
            GetMailAttachment(qwMailId);
        }
    }

}

void CMailBox::PushWaitDraw(UINT64 qwMailId)
{
    _setWaitDraw.insert(qwMailId);
}

bool compare(const SMailDetail &rMailA,const SMailDetail &rMailB)
{
  return rMailA.dwSendTime < rMailB.dwSendTime;
}

void CMailBox::SortMail()
{
    sort(_vecMail.begin(),_vecMail.end(),compare);
}
