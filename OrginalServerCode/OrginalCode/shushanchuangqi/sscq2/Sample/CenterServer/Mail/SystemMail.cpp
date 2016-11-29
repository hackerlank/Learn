#include "stdafx.h"
#include "Network/Protocols.h"
#include "User.h"
#include "UserMgr.h"
#include "SystemMail.h"
#include "Tokenizer.h"
#include "MessageSysMailBodyCFG.h"
#include "CenterServerLog.h" 
map<UINT32,string> CSystemMail::_mapBody;

CSystemMail::CSystemMail() : pVecItems(NULL)
{
    stMail.eMailState = NMailProt::eStateNew;
    stMail.eMailType = EMAILTYPE_SYSTEM;
}

void CSystemMail::AddTarget( UINT64 qwRoleID )
{
    vecTarget.push_back(SSystemMailTargetInfo(GET_GUID(GUID_MAIL), qwRoleID));
}

void CSystemMail::SetSubject( const string& strSubject )
{
    stMail.strTitle = strSubject;
}

void CSystemMail::SetSubject(const NMailProt::SysMailSendTxt& strMsgInfo )
{
    string strTitle;
    GetSysMailBody(strMsgInfo.dwstrMsgID, strTitle);
    stMail.strTitle = strTitle;
}


void CSystemMail::SetSender(const string& strSender)
{
    stMail.strSender = strSender;
}

void CSystemMail::SetBody(const NMailProt::SysMailSendTxt& strMsgInfo )
{
    string strBody;
    SysMailSendTxtToDBString(strMsgInfo,strBody);   
    stMail.strMsg = strBody;
}

void CSystemMail::SetBody(const std::string& strBody)
{
    stMail.strMsg = strBody;
}

void CSystemMail::SysMailSendTxtToDBString(const NMailProt::SysMailSendTxt& strMsgInfo,string &strBody)
{
    char buff[255];
    sprintf(buff,"%d",strMsgInfo.dwstrMsgID);
    strBody = string(buff);
    for(auto iter = strMsgInfo.vecParam.begin();iter != strMsgInfo.vecParam.end();iter++)
    {
        strBody = strBody + ",";
        strBody = strBody + *iter;
    }
}

void CSystemMail::DBStringToShowString(const string& DBstrMsg, string &strShowBody)
{
    //分解字符串
    NMailProt::SysMailSendTxt stMsg;
    buf::Tokenizer tk(DBstrMsg, ',');
    for (size_t i = 0 ; i< tk.size();++i)
    {
        if( i == 0 )
        {
            stMsg.dwstrMsgID = atoi(tk[i].c_str());
        }
        else
        {
            stMsg.vecParam.push_back(tk[i]);
        }  
    }
    string strCFG;
    if(!GetSysMailBody(stMsg.dwstrMsgID,strCFG))
    {
        return ;
    }
    //ToDO:根据ID得到
    string::size_type pos =0;
    string strReplace("$s");
    size_t ParamPos = 0;
    while((ParamPos != stMsg.vecParam.size()) &&((pos = strCFG.find(strReplace,pos)) != string::npos))
    {
        strCFG.replace(pos,strReplace.size(),stMsg.vecParam[ParamPos]);
        pos++;
        ParamPos++;
    }
    strShowBody = strCFG;
}

void CSystemMail::AddItemInfo( const TVecMailItemInfo& vecInfo )
{
    InitItemAttach();
    CMailBox::AddVecItemInfo(*pVecItems, vecInfo);
}

void CSystemMail::AddItem(const SMailItemInfo& rInfo )
{
    InitItemAttach();
    CMailBox::AddItemInfo(*pVecItems, rInfo);
}
void CSystemMail::AddBaseItems(const NItemProt::TVecItem& vecItems)
{
    InitItemAttach();
    SItemBaseCT* pItemBaseCT = new SItemBaseCT();
    if (pItemBaseCT == NULL)
        return;
    pItemBaseCT->vecItems = vecItems;
    vecAttach.push_back(SMailBaseAttachmentPtr(pItemBaseCT));
}

UINT8 CSystemMail::TestByGet()
{
    UINT8 byGet = 0;
    for(auto iter = vecAttach.begin();iter != vecAttach.end();)
    {
        bool bErase =false;
        SMailBaseAttachmentPtr pPtrBase = *(iter);
        switch(pPtrBase->GetClassType())
        {
            case  eType_SItemAttachment:
                {
                    SItemAttachmentPtr pAttach = dynamic_pointer_cast<SItemAttachment>(pPtrBase);
                    if(pAttach == NULL)
                    {
                        break;
                    }
                    TVecMailItemInfo &rvecItemInfo = pAttach->vecItemInfo;
                    if(rvecItemInfo.empty())
                    {
                        break;
                    } 
                    byGet |= (1<<ATTACH_ITEM);
                }
                break;
            case  eType_SItemBaseCT:
                {
                    SItemBaseCTPtr pAttach = dynamic_pointer_cast<SItemBaseCT>(pPtrBase);
                    if( pAttach == NULL)
                    {
                        break;
                    }
                    NItemProt::TVecItem &rvecItemInfo = pAttach->vecItems;
                    if(rvecItemInfo.empty())
                    {
                        break;
                    }
                    //把一个实例发给多个人,不允许
                    if(vecTarget.size() > 1)
                    {

                        LOG_CRI <<"INSTANCE ITEM TO more Persons;";
                        iter = vecAttach.erase(iter);
                        bErase =true;
                        break;
                    }
                    byGet |= (1<<ATTACH_INSTANCE);
                }
                break;
            default:
                break;
        }
        if(! bErase)
        {
            ++iter;
        }
    }
    return byGet;
}

bool CSystemMail::Send(function<void(UINT8 byRet_)> onSent)
{
    stMail.dwSendTime = time(NULL);
    stMail.vecMailAttachment = vecAttach;
    stMail.byGet = TestByGet();
    SSystemMailInfo& mail = stMail;
    TVecSystemMailTargetInfo& vecMail = vecTarget;
    for (auto v = vecMail.begin(); v != vecMail.end(); ++v)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(v->qwReceiveID);
        if (pUser != NULL)
        {
            SMailDetail stDetail;
            stDetail.qwMailID = v->qwMailID;
            stDetail.eMailState = mail.eMailState;
            stDetail.dwSendTime = mail.dwSendTime;
            stDetail.byGeted = mail.byGet;
            stDetail.eMailType = EMAILTYPE_SYSTEM;
            stDetail.vecMailAttachment  = mail.vecMailAttachment;
            stDetail.strTitle = mail.strTitle;
            stDetail.strMessage = mail.strMsg;
            stDetail.strSendName = mail.strSender;
            pUser->GetMailBox().AddMailToList(stDetail);
            g_MailProtS.SendClt_NewMailNotify(&(v->qwReceiveID), 1,1);

            TVecINT64 vecParam;
            vecParam.push_back(pUser->GetMailBox().GetNewMailCount());
            TVecString vecString;
            UINT32 dwSeverID = pUser->GetGameSvrID();
            g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID,1,v->qwReceiveID, eOpAdd, 1, vecParam, vecString);
        }
        NLogDataDefine::SMailLogPtr ptrLog(new NLogDataDefine::SMailLog);
        if(NULL != ptrLog)
        {
            NLogDataDefine::SMailLog& rLog = *ptrLog;
            rLog.dwServerId= Config._wGroup;
            rLog.qwPlayerId = v->qwReceiveID;
            rLog.qwMailId = v->qwMailID;
            rLog.byType = EMAILTYPE_SYSTEM;
            rLog.strTitle = mail.strTitle;
            DBStringToShowString(mail.strMsg,rLog.strText);
            vector<std::pair<UINT32,UINT32>> vecItem;
            for(auto it = mail.vecMailAttachment.begin();it != mail.vecMailAttachment.end();it++)
            {
                SMailBaseAttachmentPtr pItemBase = *(it);
                switch (pItemBase->GetClassType())
                {
                    case eType_SItemAttachment:
                        {
                            SItemAttachmentPtr pItemAttachment = dynamic_pointer_cast<SItemAttachment>(pItemBase);
                            if(pItemAttachment)
                            {
                                for(auto iter = pItemAttachment->vecItemInfo.begin();iter != pItemAttachment->vecItemInfo.end();iter++)
                                {
                                    const SMailItemInfo &rItem = *(iter);
                                    std::pair<UINT32,UINT32> pairItem;
                                    pairItem.first = rItem.wItemID;
                                    pairItem.second = rItem.wCount;
                                    vecItem.push_back(pairItem);
                                }
                            }
                        }
                        break;
                    case eType_SItemBaseCT:
                        {
                            SItemBaseCTPtr pItemIns = dynamic_pointer_cast<SItemBaseCT>(pItemBase);
                            if(pItemIns)
                            {
                                for(auto iter = pItemIns->vecItems.begin();iter != pItemIns->vecItems.end();iter++)
                                {
                                    const NItemProt::SItemPtr pItem = *(iter);
                                    std::pair<UINT32,UINT32> pairItem;
                                    pairItem.first = pItem->sItemInfo.wItemID;
                                    pairItem.second = pItem->sItemInfo.wCount;
                                    vecItem.push_back(pairItem);
                                }
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
            if(!vecItem.empty())
            {
                stringstream ss;
                for(auto it = vecItem.begin();it != vecItem.end();++it)
                {
                    if(it != vecItem.begin())
                    {
                        ss << "|";
                    }
                    ss << (*it).first;
                    ss << ",";
                    ss << (*it).second;
                }
                rLog.strAttach  = ss.str();
            }
            rLog.dwRevTime = mail.dwSendTime;
            CCenterServerLog::LogToDB(ptrLog);
        }
    }
    return g_Center2DBCommC.Send_SaveSystemMail(vecTarget, stMail, [this,vecMail, onSent, mail](UINT8 byRet_,UINT8 byRet)
            {
            if(onSent)
            onSent(byRet_);
            });
}

void CSystemMail::InitItemAttach()
{
    if(pVecItems == NULL)
    {
        SItemAttachment* pItem = new SItemAttachment();
        vecAttach.push_back(SItemAttachmentPtr(pItem));
        pVecItems = &(pItem->vecItemInfo);
    }
}

bool CSystemMail::Init()
{
    CMessageSysMailBodyLoader oMessageSysMailBodyLoader;
    string strPath = Config._strConfigDir + "Conf/Table/MessageSysMailBody.xml";
    if(!oMessageSysMailBodyLoader.LoadData(strPath))
    {
        LOG_CRI << "oMessageSysMailBodyLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    std::vector<SMessageSysMailBodyCFG*> &rVec =oMessageSysMailBodyLoader._vecData;

    for(auto iter =rVec.begin();iter != rVec.end();iter++)
    {
        SMessageSysMailBodyCFG* pCfg = *iter;
        _mapBody[pCfg->_ID] = pCfg->_Txt;
    }
    return true;
}

bool CSystemMail::GetSysMailBody(UINT32 dwBodyId,string& strBody)
{
    auto iter = _mapBody.find(dwBodyId);
    if(iter != _mapBody.end())
    {
        strBody = iter->second;
        return true;
    }
    return false;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

