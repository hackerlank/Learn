#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "Shushanweiwei.h"
#include "Parameter.h"
#include "Loot.h"
#include "Player.h"
#include "ShushanweiweiProtS.h"
#include <algorithm>

const string strCDK = "SDFQW123456";
///////////////////////////
bool CShushanweiwei::Check(CUser& rUser,EPkgType eType,UINT16 wIndex,UINT32& dwLootIndex,const string& strCDK)
{
    UINT64 qwVar = 0;
    bool bRet = false;
    if(eType >= eMax)
        return false;
    CGameVar& rVar = rUser.GetVars();
    switch(eType)
    {
        case eWeibo:
            {
                if(!wIndex) //个人奖励
                {
                    qwVar = rVar.GetVar(ePlayerShushanweiwei);
                    
                    bRet =  (qwVar & (1 << 2)) ? true : false;
                    if(!bRet)
                    {
                        LOG_INF << " Not Listen";
                        return bRet;
                    }
                    
                    bRet =  (qwVar & (1 << eWeibo)) ? false : true;
                    LOG_INF << " PersonWeibo State:" << bRet;
                    dwLootIndex = SParamConfig::wAttentionWeibo;
                    break;
                }

                UINT32 dwWeiboNum = rVar.GetVar(ePlayerWeiboNum);
                UINT32 dwConfigNum = 0;
                switch(wIndex)
                {
#define CASE(dwNum,index,id)  case id: { \
                    dwNum = SParamConfig::dwAttentionWeiboN##id; \
                    index = SParamConfig::wAttentionWeibo##id; \
                    } break; 
                    CASE(dwConfigNum,dwLootIndex,1);
                    CASE(dwConfigNum,dwLootIndex,2);
                    CASE(dwConfigNum,dwLootIndex,3);
                    CASE(dwConfigNum,dwLootIndex,4);
                    CASE(dwConfigNum,dwLootIndex,5);
#undef CASE
                }
                LOG_INF << "[Weibo] CurNum:" <<dwWeiboNum<<",ConfigNum:" <<dwConfigNum * 10000;
/*
                switch(wIndex)
                {
#define CASE(index,id)  case id: { \
                    index = SParamConfig::wAttentionWeibo##id; \
                    } break; 
                    CASE(dwLootIndex,1);
                    CASE(dwLootIndex,2);
                    CASE(dwLootIndex,3);
                    CASE(dwLootIndex,4);
                    CASE(dwLootIndex,5);
#undef CASE
                }
*/
                LOG_INF << "[weibo] ConfigPrizeNo: " <<dwLootIndex;
                
                if(dwWeiboNum < dwConfigNum * 10000)
                {
                    return false;
                }
                    
                UINT64 qwTake = rVar.GetVar(ePlayerShushanweibo);
                bRet = qwTake & (1 << (wIndex - 1)) ? false : true;
            }
            break;
        case eWeixin:
            {
                if(!wIndex) //个人奖励
                {
                    
                     if(!CheckCDK(strCDK))
                     {
                        LOG_INF <<" Not Attention";
                        return false;
                     }
                    
                    qwVar = rVar.GetVar(ePlayerShushanweiwei);
                    /*
                    bRet =  (qwVar & (1 << 3)) ? true : false;
                    if(!bRet)
                    {
                        LOG_INF << " Not Watch";
                        return bRet;
                    }
                    */
                    bRet =  (qwVar & (1 << eWeixin)) ? false : true;
                    dwLootIndex = SParamConfig::wAttentionWechat;
                    LOG_INF << " PersonWeixin State:" << bRet;
                    break;
                }
                UINT32 dwWeixinNum = rVar.GetVar(ePlayerWeixinNum);
                //UINT32 dwWeixinNum = ShushanweiweiMgr.GetWeixinNum();
                UINT32 dwConfigNum = 0;
                switch(wIndex)
                {
                    
#define CASE(dwNum,index,id)  case id: { \
                    dwNum = SParamConfig::dwAttentionWechatN##id; \
                    index = SParamConfig::wAttentionWechat##id; \
                    } break; 
                    CASE(dwConfigNum,dwLootIndex,1);
                    CASE(dwConfigNum,dwLootIndex,2);
                    CASE(dwConfigNum,dwLootIndex,3);
                    CASE(dwConfigNum,dwLootIndex,4);
                    CASE(dwConfigNum,dwLootIndex,5);
#undef CASE
/*
#define CASE(index,id)  case id: { \
                    index = SParamConfig::wAttentionWechat##id; \
                    } break; 
                    CASE(dwLootIndex,1);
                    CASE(dwLootIndex,2);
                    CASE(dwLootIndex,3);
                    CASE(dwLootIndex,4);
                    CASE(dwLootIndex,5);
#undef CASE
*/
                }
                LOG_INF << "[Weixin] CurNum:" <<dwWeixinNum<<",ConfigNum:" <<dwConfigNum * 10000;
                LOG_INF << "[weixin] ConfigPrizeNo: " <<dwLootIndex;
                
                if(dwWeixinNum < dwConfigNum * 10000)
                    return false;
                    
                UINT64 qwTake = rUser.GetVars().GetVar(ePlayerShushanweixin);
                bRet = qwTake & (1 << (wIndex - 1)) ? false : true;
            }
            break;
        default:
            break;
    }
    return bRet;
}

EPkgResult CShushanweiwei::TakePrize(CUser& rUser,EPkgType eType,UINT16 wIndex,const string& strCDK)
{
    UINT32 dwRootIndex = 0;
    EPkgResult eResult = ePackError;
    if(!Check(rUser,eType,wIndex,dwRootIndex,strCDK))
    {
        LOG_INF << "qwRoleID:" <<rUser.GetRoleID() <<" TakePrize false[eType:" << eType<<" ,wIndex:" <<wIndex <<"].";
        return eResult;
    }
    if(!dwRootIndex)
    {
        LOG_INF <<" eType(" <<eType<<"),dwRootIndex(" <<dwRootIndex<<"),wIndex(" << wIndex<<").";
        return eResult;
    }
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    LOOT.Roll(dwRootIndex, vecItems,vecRes);
    for(auto it=vecRes.begin(); it!=vecRes.end(); ++it)
    {
        SItemGenInfo tepInfo;
        SResource &rRes = *it;
        tepInfo.wItemID = rRes._eRes;
        tepInfo.dwCount = rRes._dwValue;
        vecItems.push_back(tepInfo);

    }
    if(!vecItems.empty())
    {
        CPack& oPack = rUser.GetPack();
        if(!oPack.CanAddItem(vecItems))
        {
            return ePackFull;
        }
        else
        {
            oPack.AddItem(vecItems,NLogDataDefine::ItemFrom_Shushanweiwei);
            SetShushanVar(rUser,eType,wIndex);

            {
                TVecINT32 vecParam;
                vecParam.push_back(dwRootIndex);
                if(eType == eWeibo)
                {
                    CEventMgrPtr pEventMgr = rUser.GetPlayer()->GetEventMgr();
                    if(pEventMgr)
                        pEventMgr->OnEvent(eEventType_WeiBoGift,vecParam);
                }else if (eType == eWeixin)
                {
                    CEventMgrPtr pEventMgr = rUser.GetPlayer()->GetEventMgr();
                    if(pEventMgr)
                        pEventMgr->OnEvent(eEventType_WeChatGift,vecParam);
                }
            }
        }
    }
    return ePackSuccess;
}

void CShushanweiwei::SetShushanVar(CUser &rUser,EPkgType eType,UINT16 wIndex)
{
    UINT64 qwVar = 0;
    TVecPrizeInfo vecPrizeInfo;
    switch(eType)
    {
        case eWeibo:
            {
                if(!wIndex)
                {
                    qwVar = rUser.GetVars().GetVar(ePlayerShushanweiwei);
                    qwVar = qwVar | (1 << eWeibo);
                    rUser.GetVars().SetVar(ePlayerShushanweiwei,qwVar);
                    break;
                }
                qwVar = rUser.GetVars().GetVar(ePlayerShushanweibo);
                if(wIndex < 1)
                {
                    LOG_INF <<" wIndex Error.";
                    return;
                }
                qwVar = qwVar | (1 << (wIndex - 1));
                rUser.GetVars().SetVar(ePlayerShushanweibo,qwVar);
            }
            break;
        case eWeixin:
            {
                if(!wIndex)
                {
                    qwVar = rUser.GetVars().GetVar(ePlayerShushanweiwei);
                    qwVar = qwVar | (1 << eWeixin);
                    rUser.GetVars().SetVar(ePlayerShushanweiwei,qwVar);
                    break;
                }
                qwVar = rUser.GetVars().GetVar(ePlayerShushanweixin);
                if(wIndex < 1)
                {
                    LOG_INF <<" wIndex Error.";
                    return;
                }
                qwVar = qwVar | (1 << (wIndex - 1));
                rUser.GetVars().SetVar(ePlayerShushanweixin,qwVar);

            }
            break;
        default:
            break;

    }
    SyncPrizeInfo(rUser,vecPrizeInfo);
}

void CShushanweiwei::GetPrizeInfo(CUser& rUser,TVecPrizeInfo& vecPrizeInfo)
{
    SPrizeInfo sWeiboInfo;
    sWeiboInfo.eType = eWeibo;
    SetPrizeInfo(rUser,eWeibo,sWeiboInfo);
    vecPrizeInfo.push_back(sWeiboInfo);

    SPrizeInfo sWeixinInfo;
    sWeixinInfo.eType = eWeixin;
    SetPrizeInfo(rUser,eWeixin,sWeixinInfo);
    vecPrizeInfo.push_back(sWeixinInfo);
}

void CShushanweiwei::SyncPrizeInfo(CUser& rUser,TVecPrizeInfo& vecPrizeInfo)
{
    GetPrizeInfo(rUser,vecPrizeInfo);
    rUser.GetPlayer()->SendPkg(g_ShushanweiweiProtS.BuildPkg_SyncPrizeInfo(vecPrizeInfo));
}

void CShushanweiwei::SetPrizeInfo(CUser& rUser,EPkgType eType,SPrizeInfo& sInfo)
{
    UINT64 qwVar = 0;
    switch(eType)
    {
        case eWeibo:
            {
                qwVar = rUser.GetVars().GetVar(ePlayerShushanweiwei);
                sInfo.bResult = qwVar & (1 << eWeibo) ? true : false;
                sInfo.bListen = qwVar & (1 << 2) ? true : false;

                sInfo.dwCount =0; 
                sInfo.wResult = rUser.GetVars().GetVar(ePlayerShushanweibo);
            }
            break;
        case eWeixin:
            {
                qwVar = rUser.GetVars().GetVar(ePlayerShushanweiwei);
                sInfo.bResult = qwVar & (1 << eWeixin) ? true : false;
                sInfo.dwCount = 0; 
                sInfo.wResult = rUser.GetVars().GetVar(ePlayerShushanweixin);
            }
            break;
        default:
            break;
    }

}
void CShushanweiwei::SetListenWeibo(CUser& rUser)
{
    CGameVar& rVar = rUser.GetVars();
    UINT64 qwVar = rVar.GetVar(ePlayerShushanweiwei);
    qwVar = qwVar | (1 << 2);
    rUser.GetVars().SetVar(ePlayerShushanweiwei,qwVar);
}

//GM命令
void  CShushanweiwei::GMOpen(CUser& rUser,EPkgType eType,UINT32 dwCount)
{
   CGameVar& rVar = rUser.GetVars();
    switch(eType)
    {
        case eWeibo:
            {
               rVar.SetVar(ePlayerWeiboNum,dwCount);
            }
            break;
        case eWeixin:
            {
               rVar.SetVar(ePlayerWeixinNum,dwCount);
            }
            break;
        default:
            break;
    }
}
static int ToUpper(int c)
{
    return toupper(c);
}
bool CShushanweiwei::CheckCDK(string strRecvCDK)
{
    bool  bRet = false;
    if(strRecvCDK.length() == 0)
        return bRet;
    transform(strRecvCDK.begin(),strRecvCDK.end(),strRecvCDK.begin(),ToUpper);
    if(strCDK.compare(strRecvCDK) == 0)
        bRet = true;
    return bRet;
}


////////////////////////////
#if 0
bool CShushanweiweiMgr::Init()
{

    return true;
}
void CShushanweiweiMgr::Attention(UINT64 qwRoleID,UINT8 byType,UINT32 dwCount)
{
   switch(byType)
   {
        case 0:
            SetWeiboNum(dwCount);
            break;
        case 1:
            SetWeixinNum(dwCount);
            break;
        default:
            break;
   }
   bool bFlag = false;
   CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
   if(pUser)
   {
       UINT64 qwVar = pUser->GetVars().GetVar(ePlayerShushanweiwei);
       if(byType == 0)
       {
           bFlag = qwVar & (1 << 2) ? true : false;
           if(bFlag)
           {
               LOG_INF <<" Attention twice err!";
               return;
           }
           qwVar = qwVar | (1 <<2);
       }else if(byType == 1)
       {
           bFlag = qwVar & (1 << 3) ? true : false;
           if(bFlag)
           {
               LOG_INF <<" Attention twice err!";
               return;
           }
           qwVar = qwVar | (1 <<3);
       }
       pUser->GetVars().SetVar(ePlayerShushanweiwei,qwVar);
   }
}
#endif

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

