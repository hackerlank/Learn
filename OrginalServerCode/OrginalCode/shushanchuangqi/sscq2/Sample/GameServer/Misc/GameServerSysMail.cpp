#include "GameServerSysMail.h"
#include "ItemMgr.h"
#include "Protocols.h"
#include "MessageSysMailBodyCFG.h"

map<UINT32,string> GameServerSysMail::_mapMailMsg;
void GameServerSysMail::SendSysMail(const string &strSender,const string& strTitle,const NMailProt::SysMailSendTxt& stBody,const TVecUINT64& vecTargets,std::vector<SItemGenInfo> * pvecGen /*= NULL*/,std::vector<CItemPtr>* pInsTance /*= NULL*/ )
{
#if 0
    if(strSender.empty())
    {
        LOG_CRI << "SYsMail Need Sender";
        return ;
    }
#endif
    if(strTitle.empty())
    {
        LOG_CRI << "SYsMail Need NeedTitle";  
        return ;
    }
    if(vecTargets.empty())
    {
        LOG_CRI << "SYsMail Need NeedTargets";
    }
    string strBody;
    if(!GetMailMsgbyId(stBody.dwstrMsgID,strBody))
    {
        LOG_CRI << "SYsMail empty Body";
        return ;
    }
    NMailProt::TVecMailAttachment vecAttach;
    if(pvecGen != NULL && !pvecGen->empty())
    {
        NMailProt::SItemAttachmentPtr ItemPtr(new NMailProt::SItemAttachment());
        for(auto iter = pvecGen->begin(); iter != pvecGen->end(); iter++)
        {
            SItemGenInfo *pGenInfo = &(*(iter));
            bool bHasSame = false;
            for (size_t i = 0; i < ItemPtr->vecItemInfo.size(); ++ i)
            {
                if (pGenInfo->wItemID == ItemPtr->vecItemInfo[i].wItemID)
                {
                    bHasSame = true;
                    ItemPtr->vecItemInfo[i].wCount += pGenInfo->dwCount;
                    break;
                }
            }
            if (!bHasSame)
            {
                NMailProt::SMailItemInfo stAttach;
                stAttach.wItemID = pGenInfo->wItemID;
                stAttach.eItemQuelity = static_cast<NItemProt::EItemQuality>(pGenInfo->byQuality);
                stAttach.eBindType = pGenInfo->eBindType;
                stAttach.wCount = pGenInfo->dwCount;
                ItemPtr->vecItemInfo.push_back(stAttach);
            }
        }
        vecAttach.push_back(ItemPtr);
    }
    if(pInsTance !=NULL && !pInsTance->empty())
    {
        NMailProt::SItemBaseCTPtr InsItemPtr(new NMailProt::SItemBaseCT());
        for(auto iter = pInsTance->begin(); iter != pInsTance->end();iter++)
        {
            CItemPtr ItemPtr = *iter;
            if(ItemPtr == NULL)
                continue;
            else if(ItemPtr->IsCittaItem())
            {
                SCittaPtr pSItemPtr(new SCitta());
                ItemPtr->ToStream(*pSItemPtr);
                InsItemPtr->vecItems.push_back(pSItemPtr);
            }
            else if(ItemPtr->IsFashionItem())
            {
                SFashionPtr pSItemPtr(new SFashion());
                ItemPtr->ToStream(*pSItemPtr);
                InsItemPtr->vecItems.push_back(pSItemPtr);

            }
            else if (ItemPtr->IsTrumpItem())
            {
                STrumpPtr pSItemPtr(new STrump());
                ItemPtr->ToStream(*pSItemPtr);
                InsItemPtr->vecItems.push_back(pSItemPtr);

            }
            else if (ItemPtr->IsEquipTrumpItem())
            {
                SEquipTrumpPtr pSItemPtr(new SEquipTrump());
                ItemPtr->ToStream(*pSItemPtr);
                InsItemPtr->vecItems.push_back(pSItemPtr);
            }
            else
            {
                SItemPtr pSItemPtr(new SItem());
                ItemPtr->ToStream(*pSItemPtr);
                InsItemPtr->vecItems.push_back(pSItemPtr);
            }
        }
        vecAttach.push_back(InsItemPtr);
    }
    g_Game2CenterCommC.Send_SendMail(strSender,strTitle,stBody,vecAttach,vecTargets);
}

bool GameServerSysMail::Init()
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
        _mapMailMsg[pCfg->_ID] = pCfg->_Txt;
    }
    return true;
}

bool GameServerSysMail::GetMailMsgbyId(UINT32 dwMsgId,string& strMsg)
{
    auto iter = _mapMailMsg.find(dwMsgId);
    if(iter == _mapMailMsg.end())
    {
        return false ;
    }
    strMsg = iter->second;
    return true;
}

void  GameServerSysMail::SendSysMail(UINT32 dwSendId,UINT32 dwTitleId,const NMailProt::SysMailSendTxt& stBody, const TVecUINT64 &vecTargets,std::vector<SItemGenInfo> * pvecGen /*= NULL*/,std::vector<CItemPtr>* pInsTance /*= NULL*/ )
{
    string strSender;
    string strTitle;
    GetMailMsgbyId(dwSendId,strSender);
    GetMailMsgbyId(dwTitleId,strTitle);
    SendSysMail(strSender,strTitle,stBody,vecTargets,pvecGen,pInsTance);
}


