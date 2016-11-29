#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "PHPProtS.h"
#include "CenterGameVar.h"
#include "SystemMail.h"
#include "Tokenizer.h"
#include "SysMsgDefine.h"
#include "VarDefine.h"
#include "RoleInfoDefine.h"
#include "ArenaManager.h"
#include "GuildMgr.h"
#include "GuildUser.h"
#include "GuildUserMgr.h"
#include "Memcached.h"
#include "PrepaidManager.h"
#include "VarDefine.h"
#include "ActivityMgr.h"
#include "WonderActivityMgr.h"

CPHPProtS g_PHPProtS;

using namespace NRoleInfoDefine;

//接收：玩家充值仙石
bool CPHPProtS::OnRecv_OnUserRecharge(
        UINT16 wServerNo, //区服ID
        const std::string& strToken, //memcach校验
        const std::string& strNo, //充值流水号
        UINT64 qwUserID, //用户ID
        UINT16 wID, //仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])或者Q点直购道具ID
        UINT32 dwValue, //充值的仙石包数量或者Q点直购道具数量
        const std::string& strUINT, //单位,默认发QQCOIN(Q点)
        const std::string& strMoney, //仙石对应的QQCOIN值
        const std::string& strParam, //用来url请求
        shared_func<SOnUserRechargeAck>& fnAck //返回回调函数
        )
{

    LOG_CRI << "CPHPProtS::OnRecv_OnUserRecharge (" <<  wServerNo <<","<< strToken <<","<< strNo<<","<<qwUserID<<","<<wID<<","<<dwValue<<","<<strUINT<<","<<strMoney<<","<<strParam<<")";
    if (0 == wServerNo)
    {
        LOG_CRI << "PHP OnUserRecharge: wServerNo is error";
        fnAck->byRet    = 9;
        fnAck->strError = "wServerNo is 0 !";
        return true;
    }
    if(0 == qwUserID)
    {
        LOG_CRI << "PHP OnUserRecharge: qwUserID is 0 ! Error";
        fnAck->byRet    = 8;
        fnAck->strError = "qwUserID is 0 !";
        return true;
    }
    if (!dwValue)
    {
        fnAck->byRet = 7;
        fnAck->strError = " wrong item id or number.";
        return true;
    }
    UINT8 byRet = 1;
    string strErr;
    CheckRechargeToken(qwUserID, strToken, wID, strParam, byRet, strErr);

    strErr = "";
    byRet = 0; // 不检查返回值，直接充值成功
    if (!strErr.length())
    {
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
        SRecharge oRecharge;
        if ((wID >= 41 && wID <= 46) || (wID >= 180 && wID <= 185))
        {
            static const UINT32 dwGolds[6] = { 10, 100, 300, 500, 1000, 3000 };    //XXX 仙石包ID对应的仙石单价
            int idx = 0;
            if (wID >= 41 && wID <= 46)
                idx = wID - 41;
            else
                idx = wID - 180;
            oRecharge.strNo    = strNo;
            oRecharge.qwRoleID = qwUserID;
            oRecharge.wGoldID  = wID;
            oRecharge.dwCount  = dwValue;
            oRecharge.dwGold   = dwValue * dwGolds[idx];
            oRecharge.byStatus = 0;
            oRecharge.dwHappenedTime = time(NULL);
            g_Center2DBCommC.Send_InsertRecharge(oRecharge);
        }

        auto itTmp = std::find(_vecUserID.begin(), _vecUserID.end(), qwUserID);
        if (itTmp == _vecUserID.end())
        {   //玩家未注册 预充值
            if (strNo.length())
            {
                if ((wID >= 41 && wID <= 46) || (wID >= 180 && wID <= 185))
                {
                    CPrepaidManager::Instance().PushRecharge(qwUserID, oRecharge.dwGold);
                }
                else
                {
                    strErr += "User no exist in game.";
                    byRet = 5;
                }
            }
            else
            {
                strErr += " serial number error.";
                byRet = 6;
            }
        }
        else
        {
            UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
            if (wID >= 41 && wID <= 46)
            {
                string strUdp = strUINT + "#" + strNo;     //XXX 与蜀山1相同
                oRecharge.byStatus = 1;
                g_Game2CenterCommS.SendSvr_AddTotalRecharge(&dwGameSvrIdx,1,oRecharge, strUdp, strMoney);
            }
            else if (wID >= 180 && wID <= 185)   //XXX 改版：仙石礼包发邮件
            {
                string strUdp = strUINT + "#" + strNo;     //XXX 与蜀山1相同
                oRecharge.byStatus = 1;
                g_Game2CenterCommS.SendSvr_AddRechargeMailItem(&dwGameSvrIdx,1,oRecharge, strUdp, strMoney);
            }
            else  //直购其他物品
            {
                TVecUserItem vecUserItem;
                SUserItem oUserItem(wID, dwValue);
                vecUserItem.push_back(oUserItem);
                g_Game2CenterCommS.SendSvr_AddQQCoinBuyItem(&dwGameSvrIdx,1,qwUserID,vecUserItem);
                /*
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                if (!pUser)
                {
                    strErr += "User no exist in game.";
                    byRet = 5;
                }
                else
                {
                    //TODO
                }
                */
            }
        }
    }

    fnAck->byRet    = byRet;
    fnAck->strError = strErr;
    return true;
}

//接收：修改玩家各种活动积分信息
bool CPHPProtS::OnRecv_ModifyActivityIntegral(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //用户ID
        EActivityType eType, //活动ID
        INT32 dwActCount, //活动积分
        shared_func<SModifyActivityIntegralAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        LOG_CRI << "PHP QueryActivityIntegral: wServerNo is 0 ! error";
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }
    if(0 == qwUserID)
    {
        LOG_CRI << "PHP QueryActivityIntegral: qwUserID is 0 ! Error";
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }
    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
    switch(eType)
    {
        case 0:
            if (dwActCount < 0)
            {
                //TODO
            }
            else
            {
                //TODO
            }
            break;
        case 1:
            break;
        default:
            fnAck->eOptResult = eOptResultFailed;
            return false;
    }
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：获取玩家信息
bool CPHPProtS::OnRecv_GetPlayerInfo(
        UINT16 wServerNo, //区服ID
        const std::string& strName, //角色名称
        UINT64 qwUserID, //用户ID
        shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
        )
{
    LOG_CRI << "OnRecv_GetPlayerInfo RecvPHPTime:" <<"qwUserID" << qwUserID << "RecvPHPTime" << time(NULL);
    if (0 == wServerNo)
    {
        LOG_CRI << "PHP GetPlayerInfo: wServerNo is error";
        LOG_CRI << "OnRecv_GetPlayerInfo ACKPHPTime_A:" << time(NULL);
        return false;
    }

    if (strName.empty() && 0==qwUserID)
    {
        LOG_CRI << "PHP GetPlayerInfo: strName and qwUserID is error";
        LOG_CRI << "OnRecv_GetPlayerInfo ACKPHPTime_B:" << time(NULL);
        return false;
    }

    if(qwUserID == 0)
    {
        string name = MakeName(wServerNo, strName);

        if(!GetIDByName(name, qwUserID))
        {
            LOG_CRI << "PHP GetPlayerInfo: GetIDByName is error";
            LOG_CRI << "OnRecv_GetPlayerInfo ACKPHPTime_C:" << time(NULL);
            return false;
        }
    }
    else
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_GetPlayerInfo(&dwGameSvrIdx, 1, qwUserID, [qwUserID, fnAck](UINT8 byRet, const NPHPProt::SPlayerInfo& sPlayerInfo)
            {
                SPlayerInfo sTempPlayerInfo;
                if (0 == byRet)
                {
                sTempPlayerInfo.qwUserID = sPlayerInfo.qwUserID;
                sTempPlayerInfo.strName = sPlayerInfo.strName;
                sTempPlayerInfo.wLevel = sPlayerInfo.wLevel;
                sTempPlayerInfo.byJob = sPlayerInfo.byJob ;
                sTempPlayerInfo.bySex = sPlayerInfo.bySex;
                sTempPlayerInfo.dwSilver = sPlayerInfo.dwSilver;
                sTempPlayerInfo.dwGold = sPlayerInfo.dwGold;
                sTempPlayerInfo.dwCoupon = sPlayerInfo.dwCoupon;
                sTempPlayerInfo.byVIPLevel = sPlayerInfo.byVIPLevel;
                sTempPlayerInfo.dwPrestige = sPlayerInfo.dwPrestige;
                sTempPlayerInfo.dwHonor = sPlayerInfo.dwHonor;
                sTempPlayerInfo.wShiMenTask = sPlayerInfo.wShiMenTask;
                sTempPlayerInfo.wYaMenTaTask = sPlayerInfo.wYaMenTaTask;
                sTempPlayerInfo.byForbExpire = sPlayerInfo.byForbExpire;
                sTempPlayerInfo.byLockExpire = sPlayerInfo.byLockExpire;
                sTempPlayerInfo.dwCreateTime = sPlayerInfo.dwCreateTime;



                CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwUserID);
                if (pGuildUser)
                {
                    sTempPlayerInfo.qwGuildID = pGuildUser->GetGuildID();
                    CGuildPtr pGuild = pGuildUser->GetGuild();
                    if (pGuild)
                        sTempPlayerInfo.strGuildName = pGuild->GetName();
                }

                CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
                if (pUser)
                {
                    sTempPlayerInfo.byForbExpire = pUser->GetForbExpireTime();
                    sTempPlayerInfo.byLockExpire = pUser->GetLockExpireTime();
                    SArenaPlayerData* sArenaPlayerData = CArenaManager::GetPlayer(qwUserID);
                    if(sArenaPlayerData)
                    {
                        sTempPlayerInfo.dwDJ = sArenaPlayerData->stBaseData.dwLadderRank;
                        sTempPlayerInfo.dwHistoryDJ = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerMinLadderRank);
                    }
                }
            }
  
            fnAck->vecPlayerInfo.push_back(sTempPlayerInfo);
            fnAck(true);
            LOG_CRI << "OnRecv_GetPlayerInfo SUCC_ACKPHPTime:" << time(NULL);
            return;
            });

    return true;
}

//接收：获取玩家背包信息
bool CPHPProtS::OnRecv_GetPlayerBagInfo(
        UINT16 wServerNo, //区服ID
        const std::string& strName, //角色名称
        UINT64 qwUserID, //用户ID
        shared_func<SGetPlayerBagInfoAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
        return false;

    if (strName.empty() && 0==qwUserID)
        return false;

    if(qwUserID == 0)
    {
        string name = MakeName(wServerNo, strName);

        if(!GetIDByName(name, qwUserID))
            return false;
    }
    else
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_GetPlayerBagInfo(&dwGameSvrIdx, 1, qwUserID, [qwUserID, fnAck](UINT8 byRet, const NPHPProt::TVecPlayerBagInfo& vecPlayerBagInfo) 
            {
            fnAck->vecPlayerBagInfo = vecPlayerBagInfo;
            fnAck(true);
            return;
            });

    return true;
}

//接收：删除物品
bool CPHPProtS::OnRecv_DelItem(
        UINT16 wServerNo, //区服ID
        const std::string& strName, //角色名称
        UINT64 qwUserID, //用户ID
        UINT8 byType, //1；背包，2：仓库
        UINT64 qwInstID, //物品唯一ID
        UINT16 wCount, //堆叠数
        shared_func<SDelItemAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strName.empty() && 0==qwUserID)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (1!=byType && 2!=byType)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (0 == qwInstID)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (0 == wCount)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if(qwUserID == 0)
    {
        string name = MakeName(wServerNo, strName);

        if(!GetIDByName(name, qwUserID))
        {
            fnAck->eOptResult = eOptResultFailed;
            return false;
        }
    }
    else
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_DelPlayerItem(&dwGameSvrIdx, 1, qwUserID, byType, qwInstID, wCount, [fnAck] (UINT8 byRet)
            {
            if (0 == byRet)
            {
            fnAck->eOptResult = eOptResultSucc;
            fnAck(true);
            return;
            }
            else
            {
            fnAck->eOptResult = eOptResultFailed;
            fnAck(false);
            return;
            }
            });
    return true;
}

//接收：获取在线人数
bool CPHPProtS::OnRecv_GetOnlineNum(
        UINT16 wServerNo, //区服ID
        shared_func<SGetOnlineNumAck>& fnAck //返回回调函数
        )
{
    UINT32 dwNum = 0;
    if (0 == wServerNo)
    {
        fnAck->dwOnlineNum = dwNum;
        return false;
    }

    for (size_t i=0; i<_vecUserID.size(); ++i)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(_vecUserID[i]);
        if (pUser)
            if (pUser->IsOnLine())
                dwNum++;
    }

    fnAck->dwOnlineNum = dwNum;
    return true;
}

//接收：封号/解封
bool CPHPProtS::OnRecv_LockOrUnlockUser(
        UINT16 wServerNo, //区服ID
        const std::string& strName, //角色名称
        UINT64 qwUserID, //用户ID
        EOptType eOptType, //后台操作类型
        UINT32 dwEndTime, //时间
        const std::string& strArgument, //理由
        shared_func<SLockOrUnlockUserAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "PHP LockOrUnlockUser: wServerNo is error";
        return false;
    }

    if (strName.empty() && 0==qwUserID)
    {
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "PHP LockOrUnlockUser: strName and qwUserID is error";
        return false;
    }   

    if (eOptLockUser!=eOptType && eOptUnlockUser!=eOptType)
    {
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "PHP LockOrUnlockUser: eOptType is error";
        return false;
    }
    else
    {
        if (eOptLockUser==eOptType && dwEndTime < time(NULL))
        {
            fnAck->eOptResult = eOptResultFailed;
            return false;
        }
    }

    if(qwUserID == 0)
    {
        string name = MakeName(wServerNo, strName);

        if(!GetIDByName(name, qwUserID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            LOG_CRI << "PHP LockOrUnlockUser: GetIDByName is error";
            return false;
        }
    }
    else
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    g_Center2DBCommC.Send_FreezePlayer(qwUserID, dwEndTime);

    //踢玩家下线
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser && eOptLockUser == eOptType)
    {
        g_Gate2CenterCommS.SendSvr_KickUserOffLine(NULL, 0, pUser->GetUserID(), eLeaveKick);
        LOG_CRI << "Palyer ID:" << qwUserID << "Kick off byFreeze";
        CUserMgr::RemoveUser(qwUserID);
    }

    fnAck->eOptResult = eOptResultSucc;
    LOG_CRI << "PHP LockOrUnlockUser: ack is succ";
    return true;
}

//接收：禁言/解禁
bool CPHPProtS::OnRecv_LockOrUnlockSpeak(
        UINT16 wServerNo, //区服ID
        const std::string& strName, //角色名称
        UINT64 qwUserID, //用户ID
        EOptType eOptType, //后台操作类型
        UINT32 dwEndTime, //时间
        const std::string& strArgument, //理由
        shared_func<SLockOrUnlockSpeakAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strName.empty() && 0==qwUserID)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }   

    if (eOptUnlockSpeak!=eOptType && eOptLockSpeak!=eOptType)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }
    else
    {
        if (eOptLockSpeak==eOptType && dwEndTime < time(NULL))
        {
            fnAck->eOptResult = eOptResultFailed;
            return true;
        }
    }

    if(qwUserID == 0)
    {
        string name = MakeName(wServerNo, strName);

        if(!GetIDByName(name, qwUserID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            return false;
        }
    }
    else
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    g_Center2DBCommC.Send_ForbitChat(qwUserID, dwEndTime);

    //禁言同步
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser)
    {
        pUser->SetForbExpireTime(dwEndTime);
    }

    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：发放物品/货币
bool CPHPProtS::OnRecv_SendItem(
        UINT16 wServerNo, //区服ID
        const std::string& strUserID, //格式：用户AID|户BID|..
        const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent, //邮件内容
        const std::string& strArgument, //理由
        shared_func<SSendItemAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "PHP SendItem: wServerNo is error";
        return false;
    }

    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty()) 
    {
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "PHP SendItem: strItem or strTitle or strContent is error";
        return false;
    }

    TVecUINT64 vecReceiveID; 
    if (!strUserID.empty())
    {
        Tokenizer tk(strUserID, "|");
        for (size_t i=0; i<tk.size(); ++i)
        {
            UINT64 qwPlayerID = atol(tk[i].c_str());
            UINT64 qwReceiveID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwPlayerID);
            vecReceiveID.push_back(qwReceiveID);
        }
    }
    else if (!strName.empty())
    {
        UINT64 qwReceiveID;
        string name = MakeName(wServerNo, strName);
        if(!GetIDByName(name, qwReceiveID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            LOG_CRI << "PHP SendItem: GetIDByName is error";
            return false;
        }
        vecReceiveID.push_back(qwReceiveID);
    }
    else
    {
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "PHP SendItem: strUserID and strName is error";
        return false;
    }

    if (!SendItemByMail(strTitle, strContent, strItem, vecReceiveID))
    {
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "PHP SendItem: SendItemByMail is error";
        return false;
    }

    fnAck->eOptResult = eOptResultSucc;
    LOG_CRI << "PHP SendItem: ack is succ";
    return true;
}
/*
   bool CPHPProtS::OnSendItem(
   UINT16 wServerNo, //区服ID
   const std::string& strUserID, //格式：用户AID|户BID|..
   const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
   const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
   const std::string& strTitle, //邮件标题
   const std::string& strContent, //邮件内容
   const std::string& strArgument //理由
   )
   {
   if (0 == wServerNo)
   {
   LOG_CRI << "PHP SendItem: wServerNo is error";
   return false;
   }

   if (strItem.empty() 
   || strTitle.empty() 
   || strContent.empty()) 
   {
   LOG_CRI << "PHP SendItem: strItem or strTitle or strContent is error";
   return false;
   }

   TVecUINT64 vecReceiveID; 
   if (!strUserID.empty())
   {
   Tokenizer tk(strUserID, "|");
   for (size_t i=0; i<tk.size(); ++i)
   {
   UINT64 qwPlayerID = atol(tk[i].c_str());
   UINT64 qwReceiveID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwPlayerID);
   vecReceiveID.push_back(qwReceiveID);
   }
   }
   else if (!strName.empty())
   {
   UINT64 qwReceiveID;
   string name = MakeName(wServerNo, strName);
   if(!GetIDByName(name, qwReceiveID))
   {
   LOG_CRI << "PHP SendItem: GetIDByName is error";
   return false;
   }
   vecReceiveID.push_back(qwReceiveID);
   }
   else
   {
   LOG_CRI << "PHP SendItem: strUserID and strName is error";
   return false;
   }

   if (!SendItemByMail(strTitle, strContent, strItem, vecReceiveID))
   {
   LOG_CRI << "PHP SendItem: SendItemByMail is error";
   return false;
   }

   LOG_CRI << "PHP SendItem: ack is succ";
   return true;
   }
   */
//接收：减少货币数量
bool CPHPProtS::OnRecv_SubMoney(
        UINT16 wServerNo, //区服ID
        const std::string& strUserID, //格式：用户AID|户BID|..
        const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        shared_func<SSubMoneyAck>& fnAck //返回回调函数
        )
{
    if (0==wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strItem.empty()) 
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUINT64 vecReceiveID; 
    if (!strUserID.empty())
    {
        Tokenizer tk(strUserID, "|");
        for (size_t i=0; i<tk.size(); ++i)
        {
            UINT64 qwPlayerID = atol(tk[i].c_str());
            UINT64 qwReceiveID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwPlayerID);
            vecReceiveID.push_back(qwReceiveID);
        }
    }
    else if (!strName.empty())
    {
        UINT64 qwReceiveID;
        string name = MakeName(wServerNo, strName);
        if(!GetIDByName(name, qwReceiveID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            return false;
        }
        vecReceiveID.push_back(qwReceiveID);
    }
    else
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUserItem vecUserItem;
    Tokenizer tk(strItem, "|");
    for (size_t i=0; i<tk.size(); ++i)
    {
        Tokenizer tk1(tk[i], ",");
        if (2 == tk1.size())
        {
            SUserItem oItem(atoi(tk1[0].c_str()), atoi(tk1[1].c_str()));
            vecUserItem.push_back(oItem);
        }
    }

    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_SubPlayerMoney(&dwGameSvrIdx, 1, vecReceiveID, vecUserItem, [fnAck] (UINT8 byRet)
            {
            if (0 == byRet)
            {
            fnAck->eOptResult = eOptResultSucc;
            fnAck(true);
            return;
            }
            else
            {
            fnAck->eOptResult = eOptResultFailed;
            fnAck(false);
            return;
            }
            });
    return true;
}

//接收：发放VIP物品
bool CPHPProtS::OnRecv_SendVIPItem(
        UINT16 wServerNo, //区服ID
        UINT8 byVIPMinLevel, //VIP最小等级
        UINT8 byVIPMaxLevel, //VIP最大等级
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent, //邮件内容
        const std::string& strArgument, //理由
        shared_func<SSendVIPItemAck>& fnAck //返回回调函数
        )
{
    if (0==wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (0==byVIPMinLevel || byVIPMaxLevel>15)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty()) 
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUINT64 vecTempUserID;
    for (size_t i=0; i<_vecUserID.size(); ++i)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(_vecUserID[i]);
        if (pUser && pUser->IsOnLine())
            if (pUser->GetVIPLevel()>=byVIPMinLevel && pUser->GetVIPLevel()<=byVIPMaxLevel)
                vecTempUserID.push_back(_vecUserID[i]);
    }

    if (!SendItemByMail(strTitle, strContent, strItem, vecTempUserID))
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：发放帮派物品
bool CPHPProtS::OnRecv_SendClanItem(
        UINT16 wServerNo, //区服ID
        UINT64 qwClanID, //帮派ID
        ESendTarget eTarget, //对象
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent, //邮件内容
        const std::string& strArgument, //理由
        shared_func<SSendClanItemAck>& fnAck //返回回调函数
        )
{
    if (0==wServerNo || 0==qwClanID)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eClanMember != eTarget && eClanBag != eTarget)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty()) 
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUINT64 vecTempUserID;
    if (eClanMember == eTarget)
    {
        CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwClanID);
        if (pGuild)
            pGuild->GetAllUserID(vecTempUserID);
    }
    else
    {
        //TODO 暂时没有帮派仓库
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (!SendItemByMail(strTitle, strContent, strItem, vecTempUserID))
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    fnAck->eOptResult = eOptResultSucc;
    return true;

}

//接收：全区发放物品
bool CPHPProtS::OnRecv_GlobalSendItem(
        UINT16 wServerNo, //区服ID
        ESendTarget eTarget, //对象
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent, //邮件内容
        const std::string& strArgument, //理由
        shared_func<SGlobalSendItemAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }
    if (eIsOnline != eTarget && eAll != eTarget)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty()) 
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUINT64 vecTempUserID;
    if (eIsOnline == eTarget)
    {
        for (size_t i=0; i<_vecUserID.size(); ++i)
        {
            CUserPtr pUser = CUserMgr::GetUserByUserID(_vecUserID[i]);
            if (pUser)
                if (pUser->IsOnLine())
                    vecTempUserID.push_back(_vecUserID[i]);
        }
    }
    else
        vecTempUserID = _vecUserID;

    if (!SendItemByMail(strTitle, strContent, strItem, vecTempUserID))
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：发送邮件
bool CPHPProtS::OnRecv_SendMail(
        UINT16 wServerNo, //区服ID
        const std::string& strUserID, //格式：用户AID|户BID|..
        const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
        const std::string& strTitle, //邮件标题
        const std::string& strContent, //邮件内容
        shared_func<SSendMailAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strTitle.empty() 
            || strContent.empty()) 
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUINT64 vecReceiveID; 
    if (!strUserID.empty())
    {
        Tokenizer tk(strUserID, "|");
        for (size_t i=0; i<tk.size(); ++i)
        {
            UINT64 qwPlayerID = atol(tk[i].c_str());
            UINT64 qwReceiveID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwPlayerID);
            vecReceiveID.push_back(qwReceiveID);
        }
    }
    else if (!strName.empty())
    {
        UINT64 qwReceiveID;
        string name = MakeName(wServerNo, strName);
        if(!GetIDByName(name, qwReceiveID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            return false;
        }
        vecReceiveID.push_back(qwReceiveID);
    }
    else
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (!SendMail(strTitle, strContent, vecReceiveID))
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    fnAck->eOptResult = eOptResultSucc;
    return true;

}

//接收：全区发送邮件
bool CPHPProtS::OnRecv_GlobalSendMail(
        UINT16 wServerNo, //区服ID
        ESendTarget eTarget, //对象
        const std::string& strTitle, //邮件标题
        const std::string& strContent, //邮件内容
        shared_func<SGlobalSendMailAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eIsOnline != eTarget && eAll != eTarget)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strTitle.empty() || strContent.empty()) 
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUINT64 vecTempUserID;
    if (eIsOnline == eTarget)
    {
        for (size_t i=0; i<_vecUserID.size(); ++i)
        {
            CUserPtr pUser = CUserMgr::GetUserByUserID(_vecUserID[i]);
            if (pUser)
                if (pUser->IsOnLine())
                    vecTempUserID.push_back(_vecUserID[i]);
        }
    }
    else
        vecTempUserID = _vecUserID;

    if (!SendMail(strTitle, strContent, vecTempUserID))
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    fnAck->eOptResult = eOptResultSucc;
    return true;

}

//接收：发送公告
bool CPHPProtS::OnRecv_GlobalSendNotice(
        UINT16 wServerNo, //区服ID
        const std::string& strContent, //系统弹窗内容
        EPlatformType ePlatformType, //平台类型
        EShowType eShowType, //显示区域
        ERollType eRollType, //是否滚动
        ESendType eSendType, //是否立即发送
        UINT32 dwBeginTime, //公告开始时间(注：如果选择立即发送，dwBeginTime为0)
        UINT32 dwEndTime, //公告结束时间(注：如果选择立即发送，dwEndTime为0)
        shared_func<SGlobalSendNoticeAck>& fnAck //返回回调函数
        )
{
    fnAck->dwNoticeID = 0;
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strContent.empty())
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eShowNone == eShowType || eShowType >= eShowEnd)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eRollNone == eRollType || eRollType >= eRollEnd)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eSendNone == eSendType || eSendType >= eSendEnd)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eIsRoll == eRollType)
    {
        if (dwBeginTime > 0 && dwEndTime > time(NULL) && eNoImmediateSend == eSendType)
        {
            SNotice sNotice;
            _MaxNoticeNum++;
            sNotice.dwNoticeID = _MaxNoticeNum; 
            sNotice.byNoticeType = eShowType;
            sNotice.strContent = strContent;
            sNotice.dwBeginTime = dwBeginTime;
            sNotice.dwEndTime = dwEndTime;
            _mapNotice.insert(std::make_pair(sNotice.dwNoticeID, sNotice));

            fnAck->dwNoticeID = sNotice.dwNoticeID;
            g_Center2DBCommC.Send_AddNotice(sNotice);
        }
        else
        {
            fnAck->eOptResult = eOptResultFailed;
            return false;
        }
    }
    else
    {
        if (eIsImmediateSend == eSendType)
        {
            TVecString vecStr;
            vecStr.push_back(strContent);

            if (eChatWindowNotice == eShowType)
                g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgPHPNoticeA, vecStr);
            else
                g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgPHPNoticeB, vecStr);
        }
    }
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：发送系统弹窗
bool CPHPProtS::OnRecv_GlobalSendSysDialog(
        UINT16 wServerNo, //区服ID
        EPlatformType ePlatformType, //平台类型
        EDialogType eDialogType, //弹窗类型
        shared_func<SGlobalSendSysDialogAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eUpdateNoticeDialog != eDialogType && eSysDialog != eDialogType)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    for (size_t i=0; i<_vecUserID.size(); ++i)
    {
        CUserPtr pUser = CUserMgr::GetUserByUserID(_vecUserID[i]);
        if (pUser)
        {
            if (pUser->IsOnLine())
            {
                pUser->SendPkg(g_GlobalChatProtS.BuildPkg_SysDialogAndNoticeUpdateNotify(eDialogType));

                //设置新的标记
                if (eUpdateNoticeDialog == eDialogType)
                    pUser->GetCenterVar().SetVar(NVarDefine::ePlayerNoticeUpdateMark, 1);
                else
                    pUser->GetCenterVar().SetVar(NVarDefine::ePlayerSysDialogMark, 1);
            }
            else
            {
                //清掉原来标记
                if (eUpdateNoticeDialog == eDialogType)
                    pUser->GetCenterVar().SetVar(NVarDefine::ePlayerNoticeUpdateMark, 0);
                else
                    pUser->GetCenterVar().SetVar(NVarDefine::ePlayerSysDialogMark, 0);
            }
        }
        else
        {
            SVarsDBInfo oVarsDBInfo;
            oVarsDBInfo.qwRoleID = _vecUserID[i];
            oVarsDBInfo.byServerType = eHostCenter;
            if (eUpdateNoticeDialog == eDialogType)
                oVarsDBInfo.wVar = NVarDefine::ePlayerNoticeUpdateMark;
            else
                oVarsDBInfo.wVar = NVarDefine::ePlayerSysDialogMark;
            oVarsDBInfo.qwValue = 0;
            oVarsDBInfo.dwExpired = 0;

            string strData;
            COutArchive iar(strData);
            iar << oVarsDBInfo;
            g_Center2DBCommC.Send_RoleDataUpdate(oVarsDBInfo.qwRoleID, eTypeVarInfo, eOpUpdate, strData);
        }
    }

    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：设置玩家等级
bool CPHPProtS::OnRecv_SetPlayerLevel(
        UINT16 wServerNo, //区服ID
        const std::string& strName, //角色名称
        UINT64 qwUserID, //用户ID
        UINT16 wLevel, //等级
        shared_func<SSetPlayerLevelAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (0 == wLevel)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strName.empty() && 0==qwUserID)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }   

    if(qwUserID == 0)
    {
        string name = MakeName(wServerNo, strName);

        if(!GetIDByName(name, qwUserID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            return false;
        }
    }
    else
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_SetPlayerLevel(&dwGameSvrIdx, 1, qwUserID, wLevel, [fnAck] (UINT8 byRet)
            {
            if (0 == byRet)
            {
            fnAck->eOptResult = eOptResultSucc;
            fnAck(true);
            return;
            }
            else
            {
            fnAck->eOptResult = eOptResultFailed;
            fnAck(false);
            return;
            }
            });
    return true;
}

//接收：设置玩家VIP等级
bool CPHPProtS::OnRecv_SetPlayerVIPLevel(
        UINT16 wServerNo, //区服ID
        const std::string& strName, //角色名称
        UINT64 qwUserID, //用户ID
        EOptType eOptType, //后台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
        UINT32 wLevelOrGrowthValue, //等级or成长值
        shared_func<SSetPlayerVIPLevelAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eOptType!=eOptSetPlayerVIPLevel && eOptType!=eOptAddGrowthValue)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (0 == wLevelOrGrowthValue)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (strName.empty() && 0==qwUserID)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }   

    if(qwUserID == 0)
    {
        string name = MakeName(wServerNo, strName);

        if(!GetIDByName(name, qwUserID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            return false;
        }
    }
    else
        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_SetPlayerVIPLevel(&dwGameSvrIdx, 1, qwUserID, eOptType, wLevelOrGrowthValue, [fnAck] (UINT8 byRet)
            {
            if (0 == byRet)
            {
            fnAck->eOptResult = eOptResultSucc;
            fnAck(true);
            return;
            }
            else
            {
            fnAck->eOptResult = eOptResultFailed;
            fnAck(false);
            return;
            }
            });
    return true;
}

//接收：日常任务管理
bool CPHPProtS::OnRecv_TaskManager(
        UINT16 wServerNo, //区服ID
        const std::string& strUserID, //格式：用户AID|户BID|..
        const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
        EPHPTaskType eTaskType, //任务类型
        shared_func<STaskManagerAck>& fnAck //返回回调函数
        )
{
    if (0 == wServerNo)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if (eTaskType!=ePHPYaMenTask && eTaskType!=ePHPShiMenTask)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    TVecUINT64 vecReceiveID; 
    if (!strUserID.empty())
    {
        Tokenizer tk(strUserID, "|");
        for (size_t i=0; i<tk.size(); ++i)
        {
            UINT64 qwPlayerID = atol(tk[i].c_str());
            UINT64 qwReceiveID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwPlayerID);
            vecReceiveID.push_back(qwReceiveID);
        }
    }
    else if (!strName.empty())
    {
        UINT64 qwReceiveID;
        string name = MakeName(wServerNo, strName);
        if(!GetIDByName(name, qwReceiveID))
        {
            fnAck->eOptResult = eOptResultFailed; 
            return false;
        }
        vecReceiveID.push_back(qwReceiveID);
    }
    else
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_SetDayTask(&dwGameSvrIdx, 1, vecReceiveID, eTaskType, [fnAck] (UINT8 byRet)
            {
            if (0 == byRet)
            {
            fnAck->eOptResult = eOptResultSucc;
            fnAck(true);
            return;
            }
            else
            {
            fnAck->eOptResult = eOptResultFailed;
            fnAck(false);
            return;
            }
            });
    return true;
}

//接收：获取活动列表信息
bool CPHPProtS::OnRecv_GetActList(
        shared_func<SGetActListAck>& fnAck //返回回调函数
        )
{
    return true;
}

//接收：开启指定活动
bool CPHPProtS::OnRecv_OpenAct(
        EActivityType eType, //活动ID
        UINT32 dwBegin, //活动开启时间
        UINT32 dwEnd, //活动结束时间
        shared_func<SOpenActAck>& fnAck //返回回调函数
        ) 
{
    if(dwEnd <= dwBegin)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    if(eType >= eActivity_Max)
    {
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    switch(eType)
    {

#if 0
#define SETBEGINTIME(var,begin) var=((var&0xFFFFFFFF00000000)|(begin))
#define SETENDTIME(var,end) var=(var|((end)<<32))
#define CASE(eType,eVar) \
        case eType: \
                    { \
                        UINT64 dwValue = g_CenterGameVar.GetVar(eVar); \
                        SETBEGINTIME(dwValue,dwBegin); \
                        UINT64 qwEnd = static_cast<UINT64>(dwEnd); \
                        SETENDTIME(dwValue,qwEnd); \
                        g_CenterGameVar.SetVar(eVar,dwValue); \
                    } \
        break;
        CASE(eActivity_WorldBoss, NVarDefine::eSystemVar_WorldBossAct)
            CASE(eActivity_LangHuanBless, NVarDefine::eSystemVar_LangHuanBlessAct)
#endif
        case eActivity_WorldBoss:
            g_CenterGameVar.SetVar(NVarDefine::eSystemVar_WorldBossActBeginTime, dwBegin);
            g_CenterGameVar.SetVar(NVarDefine::eSystemVar_WorldBossActEndTime, dwEnd);
            break;
        case eActivity_LangHuanBless:
            g_CenterGameVar.SetVar(NVarDefine::eSystemVar_LangHuanBlessActBeginTime, dwBegin);
            g_CenterGameVar.SetVar(NVarDefine::eSystemVar_LangHuanBlessActEndTime, dwEnd);
            break;
        case eActivity_DragonBall:
            {
                dwBegin = Time::TheDay(0, dwBegin);
                dwEnd   = dwBegin * 86400 * 7;
                g_CenterGameVar.SetVar(NVarDefine::eSystemVar_DragonBallActBeginTime, dwBegin);
                g_CenterGameVar.SetVar(NVarDefine::eSystemVar_DragonBallActEndTime, dwEnd);

                /*
                   UINT32 dwServerID = CCenterConfig::Instance().GetSvrID();
                   TVecUINT16 vecVars;
                   vecVars.push_back(NVarDefine::ePlayerVarDragonBall_AllCount);
                   for (size_t i=0; i< _vecUserID.size(); ++ i)
                   {
                   if (!_vecUserID[i])
                   continue;
                   g_Game2CenterCommS.SendSvr_DeleteGameVar(&dwServerID,1,_vecUserID[i], vecVars);
                   }
                   */
            }
            break;
        case eActivity_SevenConsume:
            {
                UINT32 dwLastBegin = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime);
                UINT32 dwLastEnd = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime);
                UINT32 dwNow = time(NULL);
                if (dwNow < dwLastBegin || dwNow > dwLastEnd)
                {
                    dwBegin = Time::TheDay(0, dwBegin);
                    dwEnd   = dwBegin * 86400 * 7;
                    g_CenterGameVar.SetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime, dwBegin);
                    g_CenterGameVar.SetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime, dwEnd);
                }
            }
            break;
        default:
            fnAck->eOptResult = eOptResultFailed;
            return false;
    }
    //活动中心注册
    //g_ActivityMgr.SetTime(eType,dwBegin,dwEnd);
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

bool CPHPProtS::IsActOpen(EActivityType eType)
{
    switch(eType)
    {
#if 0
#define GETBEGINTIME(qwValue,qwBegin) qwBegin=(qwValue & 0x00000000FFFFFFFF)
#define GETENDTIME(qwValue,qwEnd) qwEnd=(qwValue>>32)
        case eActivity_WorldBoss:
            {
                UINT64 qwValue = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_WorldBossAct);
                time_t tNow = time(NULL);
                UINT64 qwBegin = 0;
                UINT64 qwEnd = 0;
                GETBEGINTIME(qwValue,qwBegin);
                GETENDTIME(qwValue,qwEnd);
                LOG_CRI << "BeginTime = "<<qwBegin<<" | EndTime = " <<qwEnd;
                if(static_cast<UINT64>(tNow) > qwBegin && static_cast<UINT64>(tNow) < qwEnd)
                    return true;
            }
            break;
#endif
        case eActivity_WorldBoss:
            {
                UINT32 dwBegin = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_WorldBossActBeginTime);
                UINT32 dwEnd = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_WorldBossActEndTime);
                LOG_WRN << "BeginTime = " << dwBegin << " | EndTime = " << dwEnd;
                UINT32 dwNow = static_cast<UINT32>(time(NULL));
                if(dwNow >= dwBegin && dwNow <= dwEnd)
                    return true;
            }
            break;
        case eActivity_DragonBall:
            {
                UINT32 dwBegin = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActBeginTime);
                UINT32 dwEnd = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_DragonBallActEndTime);
                LOG_WRN << "BeginTime = " << dwBegin << " | EndTime = " << dwEnd;
                UINT32 dwNow = static_cast<UINT32>(time(NULL));
                if(dwNow >= dwBegin && dwNow <= dwEnd)
                    return true;
            }
            break;
        case eActivity_SevenConsume:
            {
                UINT32 dwBegin = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime);
                UINT32 dwEnd = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime);
                LOG_WRN << "BeginTime = " << dwBegin << " | EndTime = " << dwEnd;
                UINT32 dwNow = static_cast<UINT32>(time(NULL));
                if(dwNow >= dwBegin && dwNow <= dwEnd)
                    return true;
            }
            break;
        default:
            break;
    }
    return false;
}

//接收：开启商城限购活动
bool CPHPProtS::OnRecv_OpenDiscountActivity(
        UINT16 wServerNo, //区服ID
        UINT8 byPos, //限购位置(0,1,2表示)
		UINT8 byOptType, //操作类型(0：增加；1：删除)
        const std::string& strDisItems, //限购道具信息(itemID,原价,折扣价|...)
        UINT8 byLimitType, //类型限制(0无条件、1充值限购、2消费限购)
        UINT32 dwLimitValue, //达到的仙石数量限制(0无条件、1充值限购、2消费限购)
        UINT16 wLimitCount, //购买道具个数限制
        UINT32 dwBeginTime, //限购开始时间
        UINT32 dwEndTime, //限购结束时间
        shared_func<SOpenDiscountActivityAck>& fnAck //返回回调函数
        )
{
    if (!wServerNo || byPos > 2)
    {
        LOG_CRI << "PHP OpenDiscountActivity: wServerNo or byPos is error" << wServerNo <<","<< byPos;
        fnAck->eOptResult = eOptResultFailed;
        return false;
    }

    UINT32 dwServerID = CCenterConfig::Instance().GetSvrID();
    if (byOptType)
    {
        g_Game2CenterCommS.SendSvr_ClearMallDiscount(&dwServerID, 1, byPos);
        
        fnAck->eOptResult = eOptResultSucc;
        return true;
    }
    else
    {
        UINT32 dwNow = time(NULL);
        if(dwBeginTime > dwNow || dwEndTime < dwNow)
        {
            LOG_CRI << "PHP OpenDiscountActivity: dwBeginTime or dwEndTime is error" << dwNow <<","<< dwBeginTime << "," << dwEndTime;
            fnAck->eOptResult = eOptResultFailed;
            return false;
        }

        dwBeginTime = Time::TheDay(0, dwBeginTime);
        dwEndTime   = Time::TheDay(0, dwEndTime);
        //XXX ==>> NMallProt::TVecDiscount
        NMallProt::SDiscount oDiscount;
        oDiscount.byPos = byPos;
        oDiscount.byLimitType  = byLimitType;
        oDiscount.dwLimitValue = dwLimitValue;
        oDiscount.wLimitCount  = wLimitCount;
        oDiscount.dwBeginTime  = dwBeginTime;
        oDiscount.dwEndTime    = dwEndTime;

        Tokenizer tk(strDisItems, "|");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            Tokenizer tkItem(tk[j], ",");
            if (tkItem.size() <= 2)
                continue;
            NMallProt::SDiscountItem oDiscountItem;
            oDiscountItem.wItemID = atoi(tkItem[0].c_str());
            oDiscountItem.wOriginalPrice = atoi(tkItem[1].c_str());
            oDiscountItem.wDiscountPrice = atoi(tkItem[2].c_str());
            oDiscount.vecDisItems.push_back(oDiscountItem);
        }
        
        g_Game2CenterCommS.SendSvr_AddMallDiscount(&dwServerID,1,oDiscount);
        
        fnAck->eOptResult = eOptResultSucc;
        return true;
    }
    /*
       TVecUINT16 vecVars;
       vecVars.push_back(NVarDefine::ePlayerMallDiscountPos1);
       vecVars.push_back(NVarDefine::ePlayerMallDiscountPos2);
       vecVars.push_back(NVarDefine::ePlayerMallDiscountPos3);
       vecVars.push_back(NVarDefine::ePlayerMallDiscountRecharge);
       vecVars.push_back(NVarDefine::ePlayerMallDiscountConsume);
       for (size_t i=0; i< _vecUserID.size(); ++ i)
       {
       if (!_vecUserID[i])
       continue;
       g_Game2CenterCommS.SendSvr_DeleteGameVar(&dwServerID,1,_vecUserID[i],vecVars);
       }
       */
}

//接收：平台信息
void CPHPProtS::OnRecv_PlatformInfo(
        EPlatformType byPtType, //平台类型
        EQQPlatformType byQQPtType, //QQ平台类型
        UINT8 byQQPtLv, //QQ平台类型等级
        UINT8 byQQPtYearType, //是否年费
        UINT8 byQQPtLuxuryType, //是否豪华
        const std::string& customPar1, //广告主来源
        const std::string& customPar2, //广告次来源
        const std::string& strOpenId, //openID
        const std::string& strOpenKey //openKey
        )
{
    LOG_INF << "PHP Platform Info:" << static_cast<UINT32>(byPtType) << ", " << static_cast<UINT32>(byQQPtType) << ", "
        << byQQPtLv << "," << byQQPtYearType << "," << byQQPtLuxuryType << "," 
        << customPar1 << "," << customPar2 << "," << strOpenId << "," << strOpenKey;
    return; 
}

//接收：Test
void CPHPProtS::OnRecv_TestPHP(
        )
{    
    return;
}

//发送邮件
bool CPHPProtS::SendMail(
        const std::string& strTitle,
        const std::string& strContent, 
        TVecUINT64 vecReceiveID)
{
    if (strTitle.empty() 
            || strContent.empty() 
            || 0==vecReceiveID.size())
    {
        return false;
    }

    CSystemMail sysMail;
    sysMail.SetSender("系统");
    sysMail.SetSubject(strTitle);
    sysMail.SetBody(strContent);

    //接收人
    for (size_t i=0; i<vecReceiveID.size(); ++i)
    {
        sysMail.AddTarget(vecReceiveID[i]);
    }

    sysMail.Send();

    return true;
}

//通过邮件发放物品
bool CPHPProtS::SendItemByMail(
        const std::string& strTitle,
        const std::string& strContent, 
        const std::string& strItem, 
        TVecUINT64 vecReceiveID)
{
    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty() 
            || 0==vecReceiveID.size())
    {
        return false;
    }

    CSystemMail sysMail;
    sysMail.SetSender("系统");
    sysMail.SetSubject(strTitle);
    sysMail.SetBody(strContent);

    //发送物品
    SItemAttachmentPtr pItem(new SItemAttachment());
    Tokenizer tk(strItem, "|");
    for (size_t i=0; i<tk.size(); ++i)
    {
        SMailItemInfo stAttach;
        Tokenizer tk1(tk[i], ",");
        if (2 == tk1.size())
        {
            stAttach.wItemID = atoi(tk1[0].c_str());
            stAttach.wCount = atoi(tk1[1].c_str());
            pItem->vecItemInfo.push_back(stAttach);
        }
    }
    sysMail.AddItemInfo(pItem->vecItemInfo);

    //接收人
    for (size_t i=0; i<vecReceiveID.size(); ++i)
    {
        sysMail.AddTarget(vecReceiveID[i]);
    }

    sysMail.Send();

    return true;
}

//系统公告定时滚动检测
void CPHPProtS::TimerCheck()
{
    time_t tNow = time(NULL);

    for (auto it=_mapNotice.begin(); it!=_mapNotice.end();)
    {
        if (tNow >= it->second.dwBeginTime && tNow <= it->second.dwEndTime)
        {
            UINT8 byShowType = it->second.byNoticeType;
            TVecString vecStr;
            vecStr.push_back(it->second.strContent);

            if (eChatWindowNotice == byShowType)
                g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgPHPNoticeA, vecStr);
            else
                g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgPHPNoticeB, vecStr);
        }
        else if (tNow > it->second.dwEndTime)
        {
            it = _mapNotice.erase(it);
            g_Center2DBCommC.Send_DelNotice(it->second.dwNoticeID);

            continue;
        }

        it++;
    }
}

//加载所有玩家ID和名字
void CPHPProtS::LoadFromDB()
{
    g_Center2DBCommC.Send_GetAllUserIDAndName();

    return;
}

//接受所有玩家ID和名字
void CPHPProtS::RecvAllUserIDAndName(
        UINT32 dwTotalSize, //总条数
        const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
        )
{
    for (size_t i=0; i<vecUserIDAndName.size(); ++i)
    {
        _vecUserID.push_back(vecUserIDAndName[i].qwUserID);
        _mapUserIDAndName.insert(std::make_pair(vecUserIDAndName[i].qwUserID, vecUserIDAndName[i].strName));
        _mapUserNameAndID.insert(std::make_pair(vecUserIDAndName[i].strName, vecUserIDAndName[i].qwUserID));
    }

    if (0 == dwTotalSize)
        Config.SetInited(eDBUserIDAndName);
}

//加载所有公告
void CPHPProtS::LoadNoticeFromDB()
{
    g_Center2DBCommC.Send_GetAllNotice();

    return;
}

//接受所有公告
void CPHPProtS::RecvAllNotice(
        const NPHPProt::TVecNotice& vecNotice //公告信息
        )
{
    for (size_t i=0; i<vecNotice.size(); ++i)
    {
        if (vecNotice[i].dwNoticeID > _MaxNoticeNum)
            _MaxNoticeNum = vecNotice[i].dwNoticeID;

        _mapNotice.insert(std::make_pair(vecNotice[i].dwNoticeID, vecNotice[i]));
    }

    Config.SetInited(eDBNotice);
}

bool CPHPProtS::GetNameByID(UINT64 qwUsrID,string& strName)
{
    auto it = _mapUserIDAndName.find(qwUsrID);
    if(it == _mapUserIDAndName.end())
        return false;

    strName = it->second;
    return true;
}

bool CPHPProtS::GetIDByName(const string& strName, UINT64 &qwUsrID)
{
    auto it = _mapUserNameAndID.find(strName);
    if(it == _mapUserNameAndID.end())
        return false;

    qwUsrID = it->second;
    return true;
}

string CPHPProtS::MakeName(UINT16 wServerNo, const string& strName)
{
    //临时合服标志
    bool _bIsMerge = false;
    if (!_bIsMerge)
        return strName;

    //XXX: 如果合服，加上区号
    string strServerName;
    strServerName = strName + ".";
    char szServerGroupID[32] = {0};
    snprintf(szServerGroupID, sizeof(strServerName), "%d", wServerNo);
    strServerName += szServerGroupID;

    return strServerName;
}

/******************GM****************/
//GM发放帮派物品
bool CPHPProtS::GMSendClanItem(
        UINT64 qwClanID, //帮派ID
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent //邮件内容
        )
{
    if (0 == qwClanID)
        return false;

    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty()) 
        return false;

    TVecUINT64 vecTempUserID;
    CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwClanID);
    if (pGuild)
        pGuild->GetAllUserID(vecTempUserID);

    if (!SendItemByMail(strTitle, strContent, strItem, vecTempUserID))
        return false;

    return true;
}

//GM全区发放物品
bool CPHPProtS::GMGlobalSendItem(
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent //邮件内容
        )
{
    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty()) 
        return false;

    if (!SendItemByMail(strTitle, strContent, strItem, _vecUserID))
        return false;

    return true;
}

//GM封号/解封
bool CPHPProtS::GMLockOrUnlockUser(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //用户ID
        UINT8 byOptType, //操作类型((1:封号；2：解封)
        UINT32 dwEndTime //时间
        )
        {
        if (0 == wServerNo)
        return false;

        if (0 == qwUserID)
        return false;

        if (1!=byOptType && 2!=byOptType)
        return false;

        if (1==byOptType)
        dwEndTime = dwEndTime + time(NULL);
        else
        dwEndTime = 0;

        qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

        g_Center2DBCommC.Send_FreezePlayer(qwUserID, dwEndTime);

        //踢玩家下线
        CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
        if(pUser && 1 == byOptType)
        {
            g_Gate2CenterCommS.SendSvr_KickUserOffLine(NULL, 0, pUser->GetUserID(), eLeaveKick);
            LOG_CRI << "Palyer ID:" << qwUserID << "Kick off byFreeze";
            CUserMgr::RemoveUser(qwUserID);
        }

        return true;
        }

//GM禁言/解禁
bool CPHPProtS::GMLockOrUnlockSpeak(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //用户ID
        UINT8 byOptType, //后台操作类型
        UINT32 dwEndTime //时间
        )
{
    if (0 == wServerNo)
        return false;

    if (0==qwUserID)
        return false;

    if (1!=byOptType && 2!=byOptType)
        return false;

    if (1==byOptType)
        dwEndTime = dwEndTime + time(NULL);
    else
        dwEndTime = 0;

    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);

    g_Center2DBCommC.Send_ForbitChat(qwUserID, dwEndTime);

    //禁言同步
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser)
    {
        pUser->SetForbExpireTime(dwEndTime);
    }

    return true;
}

//GM发送公告
bool CPHPProtS::GMGlobalSendNotice(const std::string& strContent)
{
    if (strContent.empty())
        return false;

    TVecString vecStr;
    vecStr.push_back(strContent);
    g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgPHPNoticeB, vecStr);

    return true;
}

//GM发放个人物品
bool CPHPProtS::GMSendItem(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //用户ID
        const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
        const std::string& strTitle, //邮件标题
        const std::string& strContent //邮件内容
        )
{
    if (0 == wServerNo)
        return false;

    if (0 == qwUserID)
        return false;

    if (strItem.empty() 
            || strTitle.empty() 
            || strContent.empty()) 
        return false;

    TVecUINT64 vecReceiveID; 
    UINT64 qwReceiveID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
    vecReceiveID.push_back(qwReceiveID);

    if (!SendItemByMail(strTitle, strContent, strItem, vecReceiveID))
        return false;

    return true;
}

void CPHPProtS::PullWeiboNum() //定时拉微博收听人数
{

}

//接收：任务集市中任务状态查询
bool CPHPProtS::OnRecv_GetTaskState(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //玩家ID
        UINT32 dwTaskID, //任务ID
        UINT8 byStep, //步骤ID
        ETaskOpt eTaskOpt, //任务操作
        shared_func<SGetTaskStateAck>& fnAck //返回回调函数
        ) 
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    fnAck->wServerNo = wServerNo;
    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
   
    auto it = _mapUserIDAndName.find(qwUserID);
    if(it == _mapUserIDAndName.end())
    {
        LOG_INF<<" Not find qwUserID(" << qwUserID<<").";
        fnAck->eTaskState = eTaskStateNoRole;
        return true;
    }

    g_Game2CenterCommS.SendSvr_GetTaskStateForPlatfrom(&dwGameSvrIdx, 1, qwUserID, dwTaskID, byStep, eTaskOpt, [fnAck] (UINT8 byRet,NPHPProt::ETaskState eRet)
            {
            if (0 == byRet)
            {
            fnAck->eTaskState = eRet;
            LOG_INF << "eTaskState=" << eRet;
            fnAck(true);
            return;
            }
            else
            {
            fnAck->eTaskState = eRet;
            LOG_INF << "eTaskState=" << eRet;
            fnAck(false);
            return;
            }
            });

    return true;
}

//接收：同步微信微博人数
bool CPHPProtS::OnRecv_SynWeiweiPersonNum(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //玩家ID
        UINT8 byType, //任务ID
        UINT32 dwCount, //步骤ID
        shared_func<SSynWeiweiPersonNumAck>& fnAck //返回回调函数
        )
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
    LOG_CRI <<" Recv Platfrom : qwUserID=" <<qwUserID<<",byType=" <<byType<<", dwCount = " <<dwCount;
    g_Game2CenterCommS.SendSvr_SynWeiweiPersonNum(&dwGameSvrIdx, 1, qwUserID, byType,dwCount);
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：检测CDK
bool CPHPProtS::OnRecv_CheckCDK(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //玩家ID
        const std::string& strCDK, //CDK码
        shared_func<SCheckCDKAck>& fnAck //返回回调函数
        )
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
    LOG_CRI <<" Recv Platfrom : qwUserID=" <<qwUserID;
    g_Game2CenterCommS.SendSvr_CheckCDK(&dwGameSvrIdx, 1, qwUserID,strCDK);
    fnAck->eOptResult = eOptResultSucc;
    return true;
}
//接收：QQAlarm安装
bool CPHPProtS::OnRecv_SynQQAlarm(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //玩家ID
        shared_func<SSynQQAlarmAck>& fnAck //返回回调函数
        )
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
    LOG_CRI << "QQAlarm qwRoleID(" <<qwUserID<<").";
    g_Game2CenterCommS.SendSvr_SynQQAlarm(&dwGameSvrIdx, 1, qwUserID);
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

string CPHPProtS::GetUserNameByID(UINT64 qwRoleID)
{
    auto it = _mapUserIDAndName.find(qwRoleID);
    if(it != _mapUserIDAndName.end())
        return it->second;
    return "";
}
//接收：天赐宝箱活动参数修改
bool CPHPProtS::OnRecv_ModifyChest(
        const SChestInfo& sInfo, //数据
        shared_func<SModifyChestAck>& fnAck //返回回调函数
        )
{
    LOG_CRI<<"dwTime="<<sInfo.dwTime<<",Big="<<sInfo.byBig<<",Mid="<<sInfo.byMid<<",Small="<<sInfo.bySmall<<",Long="<<sInfo.byPeroid<<",MapID="<<sInfo.wMapID;
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterCommS.SendSvr_ModifyChest(&dwGameSvrIdx, 1,sInfo);
    fnAck->eOptResult = eOptResultSucc;
    return true;
}
//接收：设置汇灵盏奖励池
bool CPHPProtS::OnRecv_SetPool(
        UINT8 byType, //类型，0表示设置奖励池最大值，1表示设置奖励池现有值
        UINT32 dwValue, //数据
        shared_func<SSetPoolAck>& fnAck //返回回调函数
        )
{
    g_WonderActivityMgr.SetPoolValue(byType,dwValue);
    LOG_CRI<< " setPool:" << byType<<"," << dwValue;
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：请求玩家累计登入天数
bool CPHPProtS::OnRecv_GetLoginDays(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //玩家ID
        shared_func<SGetLoginDaysAck>& fnAck //返回回调函数
        )
{
    LOG_CRI << "OnRecv_GetLoginDays RecvPHPTime:" << "qwUserID" << qwUserID << "RecvTime" << time(NULL);
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
    auto it = _mapUserIDAndName.find(qwUserID);
    if(it == _mapUserIDAndName.end())
    {
        LOG_INF<<" Not find qwUserID(" << qwUserID<<").";
        fnAck->eOptResult = eOptResultFailed;
        LOG_CRI << "OnRecv_GetLoginDays ACKPHPTime_A:" << time(NULL);
        return true;
    }

    g_Game2CenterCommS.SendSvr_GetLoginDays(&dwGameSvrIdx, 1, qwUserID,[fnAck](UINT8 byRet_,UINT32 dwDays)
            {
            if(byRet_ != 0)
            {
            fnAck->eOptResult = eOptResultFailed;
            LOG_CRI << "OnRecv_GetLoginDays ACKPHPTime_B:" << time(NULL);
            fnAck(true);
            return;
            }
            fnAck->dwDays = dwDays;
            fnAck->eOptResult = eOptResultSucc;
            LOG_CRI << "OnRecv_GetLoginDays Succ_ACKPHPTime:" << time(NULL);
            fnAck(true);
            return;
            });
    return true;
}

//接收：发送工会聊天信息
bool CPHPProtS::OnRecv_SendQQGroupMsg(
	UINT64 qwGroupUserID, //绑定qq的玩家ID
	UINT16 wServerNo, //聊天玩家区号ID
	UINT64 qwUserID, //聊天玩家账号ID
	const std::string& strChatMsg, //聊天
	shared_func<SSendQQGroupMsgAck>& fnAck //返回回调函数
)
{

    return true;
}
//接收：删除公告
bool CPHPProtS::OnRecv_GlobalDelNotice(
        UINT16 wServerNo, //区服ID
        UINT32 dwNoticeID, //公告ID
        shared_func<SGlobalDelNoticeAck>& fnAck //返回回调函数
        )
{
    auto it = _mapNotice.find(dwNoticeID);
    if(it != _mapNotice.end())
    {
        g_Center2DBCommC.Send_DelNotice(dwNoticeID);
        _mapNotice.erase(it);
    }
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

//接收：添加称号
bool CPHPProtS::OnRecv_SendTitle(
        UINT16 wServerNo, //区服ID
        UINT64 qwUserID, //玩家ID
        UINT16 wTitleID,
        shared_func<SSendTitleAck>& fnAck //返回回调函数
        )
{
    UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
    qwUserID = CGUIDMgr::GetGUID(wServerNo, 0, GUID_ROLE, qwUserID);
    LOG_CRI << "qwRoleID(" <<qwUserID<<").";
    auto it = _mapUserIDAndName.find(qwUserID);
    if(it == _mapUserIDAndName.end())
    {
        LOG_INF<<" Not find qwUserID(" << qwUserID<<").";
        fnAck->eOptResult = eOptResultFailed;
        return true;
    }
    
    g_Game2CenterCommS.SendSvr_SyncTitle(&dwGameSvrIdx, 1, qwUserID,wTitleID);
    fnAck->eOptResult = eOptResultSucc;
    return true;
}

