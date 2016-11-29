
#include "stdafx.h"
#include "Friend.h"
#include "User.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "RoleInfoDefine.h" // for eTypeFriendInfo
#include "ProtoCommon.h"
#include "Parameter.h"
#include "VIPMgr.h"
#include "EventCenter.h"
using namespace NRoleInfoDefine;
using namespace NProtoCommon;

static void SystemMessageNotify(CUser& rUser, EFriendResult eRes)
{
    ESystemMsgID eMsgID = eMsgOtherErr;

    switch(eRes)
    {
        case eFriendSuccess: //成功
            eMsgID = eMsgSuccess;
            break;
        case eFriendDuplicateErr: //已经存在
            eMsgID = eMsgFriendExistErr;
            break;
        case eFriendOnBlackList: //已在黑名单中
            eMsgID = eMsgFriendExistBlack;
            break;
        case eFriendOnTarBlackList: //已在对方黑名单中
            eMsgID = eMsgFriendExistTarBlack;
            break;
        case eFriendOtherDuplicateErr: //已存在于目标的好友列表
            eMsgID = eMsgFriendExist2Err;
            break;
        case eFriendMaxNumErr: //好友达到上限
            eMsgID = eMsgFriendNumLimitErr;
            break;
        case eFriendOtherMaxNumErr: //对方好友达到上限
            eMsgID = eMsgFriendNumLimit2Err;
            break;
        case eFriendOfflineErr: //目标不在线
            eMsgID = eMsgTargetNotExistOrOfflineErr;
            break;
        case eFriendRefuseErr: //对方拒绝
            eMsgID = eMsgFriendRefuseErr;
            break;
        case eFriendNotExistErr: //目标不存在
            eMsgID = eMsgTargetNotExistErr;
            break;
        case eFriendGroupIDErr: //分组ID错误
            eMsgID = eMsgFriendGroupIDErr;
            break;
        case eFriendOtherErr: //其他错误
        default:
            break;
    }

    rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify((UINT16)eMsgID));
}

    CFriend::CFriend(CUser& rUser)
    : _rUser(rUser)
      , _bInitialized(false)
{}

void CFriend::Init(const TVecFriendDBInfo& rVecFriends)
{
    if (_bInitialized)
        return;
    _bInitialized = true;

    size_t szFriends = rVecFriends.size();
    if(!szFriends)
        return;

    // clean up
    _mapUserID2FriendEntry.clear();

    for(size_t i = 0; i < szFriends; ++i)
    {
        SFriendEntryPtr pFriendEntry(new SFriendEntry);
        if(!pFriendEntry)
        {
            LOG_CRI << "CFriend::Init Alloc Failed!";
            continue;
        }

        pFriendEntry->qwUserID = rVecFriends[i].qwUserID;
        pFriendEntry->eGroupType = (EFriendGroupType)rVecFriends[i].byGroup;
        pFriendEntry->strName = rVecFriends[i].strName;
        pFriendEntry->wFighterID = rVecFriends[i].wFighterID;
        pFriendEntry->byLevel = rVecFriends[i].byLevel;
        pFriendEntry->byColor = rVecFriends[i].byColor;
        pFriendEntry->bOnlineStatus = false;

        pFriendEntry->byVIPLevel = rVecFriends[i].byVIPLevel;
        pFriendEntry->vecPlatforms = CUserMgr::GetPlatformParam(rVecFriends[i].qwUserID);
        _mapUserID2FriendEntry[pFriendEntry->qwUserID] = pFriendEntry;
        SyncLatestVIPLevel(rVecFriends[i].qwUserID, pFriendEntry);
    }
}

void CFriend::ChangeSign(const std::string& strSign)
{
    UserChangeNotify(g_FriendProtS.BuildPkg_SignChangeNotify(_rUser.GetUserID(), strSign));
}

void CFriend::ChangeMood(UINT16 wMood)
{
    UserChangeNotify(g_FriendProtS.BuildPkg_MoodChangeNotify(_rUser.GetUserID(), wMood));
}

void CFriend::ChangeVIPLevel(UINT64 qwRoleID, UINT8 byVIPLevel)
{
   for(auto& rPair: _mapUserID2FriendEntry)
    {
        if(rPair.first == qwRoleID && rPair.second)
        {
            SFriendEntryPtr pFriendEntry = rPair.second;
            pFriendEntry->byVIPLevel = byVIPLevel;
            Update2DB(_rUser.GetUserID(), *pFriendEntry, eOpUpdate);
            string strPkg = g_FriendProtS.BuildPkg_VIPLevelChangeNotify(qwRoleID, byVIPLevel);
            _rUser.SendPkg(strPkg);
        }
    }
}

void CFriend::ChangeVIPLevel(UINT8 byVIPLevel)
{
    SyncUserVIPLevel(byVIPLevel);
}

void CFriend::ChangeColor(UINT64 qwRoleID, UINT8 byColor)
{
   for(auto& rPair: _mapUserID2FriendEntry)
    {
        if(rPair.first == qwRoleID && rPair.second)
        {
            SFriendEntryPtr pFriendEntry = rPair.second;
            pFriendEntry->byColor = byColor;
            Update2DB(_rUser.GetUserID(), *pFriendEntry, eOpUpdate);
            string strPkg = g_FriendProtS.BuildPkg_ColorChangeNotify(qwRoleID, byColor);
            _rUser.SendPkg(strPkg);
        }
    }

}
void CFriend::ChangeColor(UINT8 byColor)
{
    for(auto itr = _mapUserID2FriendEntry.begin(); itr != _mapUserID2FriendEntry.end(); ++itr)
    {
        if(NULL == itr->second || itr->second->eGroupType == eBlackFriend)
            continue;

        CUserPtr pUser = CUserMgr::GetUserByUserID(itr->first);
        if(pUser)
        {
            CFriend& rFriend = pUser->GetFriend();
            rFriend.ChangeColor(_rUser.GetRoleID(), byColor);
        }
    }

}


void CFriend::SyncLatestVIPLevel(UINT64 qwRoleID, SFriendEntryPtr pFriendEntry)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (pUser && pUser->GetVIPLevel() != pFriendEntry->byVIPLevel)
    {
        pFriendEntry->byVIPLevel = pUser->GetVIPLevel();
        Update2DB(_rUser.GetUserID(), *pFriendEntry, eOpUpdate);
    }

}

void CFriend::AddFriend(UINT64 qwUserID, UINT8 byNeedRet)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    AddFriend(pUser);
}

void CFriend::AddFriend(const std::string& strName, UINT8 byNeedRet)
{
    CUserPtr pUser = CUserMgr::GetUserByName(strName);
    AddFriend(pUser);
}

void CFriend::AddFriend(CUserPtr pUser, UINT8 byNeedRet)
{
    string strName;
   ESexType eSex =  ESEX_ALL;
    EFriendResult eRes = eFriendSuccess;
    do
    {
        //check Friend Num 
        /*if(!CheckAddFriendNum())
          {
          eRes = eFriendMaxNumErr;
          break;
          }*/

        // check is initialize
        if(!_bInitialized)
        {
            eRes = eFriendOtherErr;
            break;
        }

        // check exist
        if(!pUser)
        {
            eRes = eFriendOfflineErr;
            break;
        }
        UINT64 qwUserID = pUser->GetUserID();

        // 如果B已经是我的好友则不能加为好友
        auto itr = _mapUserID2FriendEntry.find(qwUserID);
        if(itr != _mapUserID2FriendEntry.end())
        {
            if(itr->second->eGroupType == eBlackFriend)
                eRes = eFriendOnBlackList;
            else
                eRes = eFriendDuplicateErr;

            break;
        }

        // A在B的黑名单中则不可以把B加为好友
        CFriend& rBFriend = pUser->GetFriend();
        TMapFriendEntry& mapUserID2FriendEntryB = rBFriend.GetFriendEntryMap();
        auto itrB = mapUserID2FriendEntryB.find(_rUser.GetUserID());
        if (itrB != mapUserID2FriendEntryB.end() && itrB->second->eGroupType == eBlackFriend)
        {
            eRes = eFriendOnTarBlackList;
            break;
        }

        // exec
        pUser->SendPkg(g_FriendProtS.BuildPkg_AskAddFriend(_rUser.GetRoleName(), _rUser.GetUserID(), _rUser.GetFighterID(), _rUser.GetSex(), _rUser.GetLevel()));
        _rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemMsgIDNotify(eMsgFriendInvited));
        UINT32 dwSeverID = _rUser.GetGameSvrID();
        TVecINT64 vecParam;
        TVecString vecString;
        g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID, 1, pUser->GetUserID(), eOpAdd, 2, vecParam, vecString);
        return;

    } while(false);

    // exec
    if (byNeedRet == 1)
        SystemMessageNotify(_rUser, eRes);
    _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eRes,strName,eSex));
}

void CFriend::AnswerAddFriend(bool bAgree, UINT64 qwUserID)
{
    if(!bAgree)
    {
        CUserPtr pUserA = CUserMgr::GetUserByUserID(qwUserID);
        if(!pUserA)
            return;

        SystemMessageNotify(_rUser, eFriendSuccess);
        _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendSuccess,pUserA->GetRoleName(),(ESexType)pUserA->GetSex()));
        // notify A refused by B
        SystemMessageNotify(*pUserA, eFriendRefuseErr);
        pUserA->SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendRefuseErr,_rUser.GetRoleName(),(ESexType)_rUser.GetSex()));
        TVecINT64 vecParam;
        TVecString vecString;
        vecString.push_back(_rUser.GetRoleName());
        UINT32 dwSeverID = pUserA->GetGameSvrID();
        g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID, 1, qwUserID, eOpAdd, 8, vecParam, vecString);
        return;
    }
    else
    {
        if(!_bInitialized)
        {
            // notify not initialized
            SystemMessageNotify(_rUser, eFriendOtherErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOtherErr,string(),ESEX_MAX));
            return;
        }

        CUserPtr pUserA = CUserMgr::GetUserByUserID(qwUserID);
        if(!pUserA)
        {
            // notify B that A is offline
            SystemMessageNotify(_rUser, eFriendOfflineErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOfflineErr,string(),ESEX_MAX));
            return;
        }

        // 如果B的好友到了上限则加好友失败
        const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(_rUser.GetVIPLevel());
        if(pCfgVip == NULL)
            return;

        //if((_mapUserID2FriendEntry.size() + pCfgVip->_FriendNum) >= SParamConfig::byFriendMax)
        if(GetFriendNum() >= SParamConfig::byFriendMax + pCfgVip->_FriendNum)
        {
            // notify B that B reach the max num of friend
            SystemMessageNotify(_rUser, eFriendMaxNumErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendMaxNumErr,string(),ESEX_MAX));
            // notify A that B reach the max num of friend
            SystemMessageNotify(*pUserA, eFriendOtherMaxNumErr);
            pUserA->SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOtherMaxNumErr,string(),ESEX_MAX));
            return;
        }

#if 0
        // 如果A在B的好友列表里则加好友失败
        auto itr = _mapUserID2FriendEntry.find(qwUserID);
        if(itr != _mapUserID2FriendEntry.end())
        {
            // notify B that B's friend duplicate
            SystemMessageNotify(_rUser, eFriendDuplicateErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendDuplicateErr));
            // notify A that B's friend duplicate
            SystemMessageNotify(*pUserA, eFriendOtherDuplicateErr);
            pUserA->SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOtherDuplicateErr));
            return;
        }
#else
        // 如果A在B的好友列表里可继续
        bool bAlreadyBs = false;
        auto itr = _mapUserID2FriendEntry.find(qwUserID);
        if(itr != _mapUserID2FriendEntry.end())
            bAlreadyBs = true;
#endif

        // A的好友达到上限则加好友失败
        const SVIPLevelCFGEx* pCfgVipA = VIPMgr.GetVIPLevelCfg(pUserA->GetVIPLevel());
        if(pCfgVipA == NULL)
            return;

        CFriend& rFriendA = pUserA->GetFriend();
        TMapFriendEntry& mapUserID2FriendEntryA = rFriendA.GetFriendEntryMap();
        //if(mapUserID2FriendEntryA.size() >= SParamConfig::byFriendMax)
        if(rFriendA.GetFriendNum() >= SParamConfig::byFriendMax + pCfgVipA->_FriendNum)
        {
            // notify B that A reach the max num of friend
            SystemMessageNotify(_rUser, eFriendOtherMaxNumErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOtherMaxNumErr,string(),ESEX_MAX));
            // notify A that A reach the max num of friend
            SystemMessageNotify(*pUserA, eFriendMaxNumErr);
            pUserA->SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendMaxNumErr,string(),ESEX_MAX));
            return;
        }

#if 0
        // A duplicate
        itr = mapUserID2FriendEntryA.find(_rUser.GetUserID());
        if(itr != mapUserID2FriendEntryA.end())
        {
            // notify B that A's friend duplicate
            SystemMessageNotify(_rUser, eFriendOtherDuplicateErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOtherDuplicateErr));
            // notify A that A's friend duplicate
            SystemMessageNotify(*pUserA, eFriendDuplicateErr);
            pUserA->SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendDuplicateErr));
            return;
        }
#else
        // 如果B在A的好友列表里则继续
        bool bAlreadyAs = false;
        itr = mapUserID2FriendEntryA.find(_rUser.GetUserID());
        if(itr != mapUserID2FriendEntryA.end())
            bAlreadyAs = true;
#endif

        SFriendEntryPtr pFriendEntryA(new SFriendEntry);
        if(!pFriendEntryA)
        {
            SystemMessageNotify(_rUser, eFriendOtherErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOtherErr,string(),ESEX_MAX));
            return;
        }

        SFriendEntryPtr pFriendEntryB(new SFriendEntry);
        if(!pFriendEntryB)
        {
            SystemMessageNotify(_rUser, eFriendOtherErr);
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eFriendOtherErr,string(),ESEX_MAX));
            return;
        }

        // fill data
        pFriendEntryA->bOnlineStatus = true;
        pFriendEntryA->eGroupType = eCommonFriend;
        pFriendEntryA->qwUserID = qwUserID;
        pFriendEntryA->wFighterID = pUserA->GetFighterID();
        pFriendEntryA->byLevel = pUserA->GetLevel();
        pFriendEntryA->byColor = pUserA->GetColor();
        pFriendEntryA->byVIPLevel = pUserA->GetVIPLevel();
        pFriendEntryA->strName = pUserA->GetRoleName();
        pFriendEntryA->wMood = pUserA->GetMood();
        pFriendEntryA->strSign = pUserA->GetSign();
        pFriendEntryA->eSex = pUserA->GetSex();
        pFriendEntryA->byVIPLevel = pUserA->GetVIPLevel();
        pFriendEntryA->vecPlatforms = (pUserA->GetPlatformParam());


        pFriendEntryB->bOnlineStatus = true;
        pFriendEntryB->eGroupType = eCommonFriend;
        pFriendEntryB->qwUserID = _rUser.GetUserID();
        pFriendEntryB->wFighterID = _rUser.GetFighterID();
        pFriendEntryB->byLevel = _rUser.GetLevel();
        pFriendEntryB->byColor = _rUser.GetColor();
        pFriendEntryB->byVIPLevel = _rUser.GetVIPLevel();
        pFriendEntryB->strName = _rUser.GetRoleName();
        pFriendEntryB->wMood =  _rUser.GetMood();
        pFriendEntryB->strSign = _rUser.GetSign();
        pFriendEntryB->eSex = _rUser.GetSex();
        pFriendEntryB->byVIPLevel = _rUser.GetVIPLevel();
        pFriendEntryB->vecPlatforms = (_rUser.GetPlatformParam());

        // correct
        if (!bAlreadyAs)
            mapUserID2FriendEntryA.insert(make_pair(_rUser.GetUserID(), pFriendEntryB));
        if (!bAlreadyBs)
            _mapUserID2FriendEntry.insert(make_pair(qwUserID, pFriendEntryA));

        // notify client
        if (!bAlreadyAs)
        {
            pUserA->SendPkg(g_FriendProtS.BuildPkg_AddFriendAckEx(*pFriendEntryB));
            pUserA->SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgFriendAddFriend, BuildStrVec(pFriendEntryB->strName)));
        }

        if (!bAlreadyBs)
        {
            _rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgFriendAddFriend, BuildStrVec(pFriendEntryA->strName)));
            _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAckEx(*pFriendEntryA));
        }

#if 0
        {
            UINT32 dwSvrID = pUserA->GetGameSvrID();
            if(dwSvrID != 0)
                g_MiscGS2CSS.SendSvr_AddFriendNtf(&dwSvrID, 1, qwUserID, pUserA->GetFriend().GetFriendNum());
        }

        {
            UINT32 dwSvrID = _rUser.GetGameSvrID();
            if(dwSvrID != 0)
                g_MiscGS2CSS.SendSvr_AddFriendNtf(&dwSvrID, 1, _rUser.GetUserID(), GetFriendNum());
        }
#endif

        if (!bAlreadyBs)
            Update2DB(_rUser.GetUserID(), *pFriendEntryA, eOpAdd);
        if (!bAlreadyAs)
            Update2DB(qwUserID, *pFriendEntryB, eOpAdd);

        //成功添加好友事件
        TVecINT32 vecParam;
        UINT32 dwServerID = 0;

        vecParam.push_back(pUserA->GetFriend().GetFriendNum());
        dwServerID = pUserA->GetGameSvrID();
        if(dwServerID != 0)
            g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID, 1, qwUserID, NEventCenter::eEventType_FriendAdding, vecParam, "", true);
        if(pUserA)
        {
            TVecINT64 vecParam;
            TVecString vecString;
            vecString.push_back(_rUser.GetRoleName());
            UINT32 dwSeverID = pUserA->GetGameSvrID();
            g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID, 1, qwUserID, eOpAdd, 7, vecParam, vecString);

        }
        vecParam.clear();
        vecParam.push_back(GetFriendNum());
        dwServerID = _rUser.GetGameSvrID();
        if(dwServerID != 0)
            g_Game2CenterCommS.SendSvr_OnPlayerEvent(&dwServerID, 1, _rUser.GetUserID(), NEventCenter::eEventType_FriendAdding, vecParam, "", true);
    }
}

void CFriend::RemoveFriend(UINT64 qwUserID, bool bAddBlackList /*= false*/)
{
    if(!_bInitialized)
    {
        // notify A that B not exist
        SystemMessageNotify(_rUser, eFriendOtherErr);
        _rUser.SendPkg(g_FriendProtS.BuildPkg_RemoveFriendAck(eFriendOtherErr, qwUserID));
        return;
    }

    // remove B from A's friend list
    auto itr = _mapUserID2FriendEntry.find(qwUserID);
    if(itr == _mapUserID2FriendEntry.end())
    {
        // notify A that B not exist
        SystemMessageNotify(_rUser, eFriendNotExistErr);
        _rUser.SendPkg(g_FriendProtS.BuildPkg_RemoveFriendAck(eFriendNotExistErr, qwUserID));
        return;
    }

    bool bBlackList = itr->second->eGroupType == eBlackFriend;
    if(bBlackList)
        _rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgFriendRemoveBlack, BuildStrVec(itr->second->strName)));
    else
        _rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgFriendRemoveFriend, BuildStrVec(itr->second->strName)));

    _rUser.SendPkg(g_FriendProtS.BuildPkg_RemoveFriendAck(eFriendSuccess, qwUserID));

    // XXX: 同时把A从B的好友里也删除，如果B在线的话，否则在上线时处理
    CUserPtr pUserB = CUserMgr::GetUserByUserID(qwUserID);
    if (pUserB)
    {
        CFriend& rBFriend = pUserB->GetFriend();
        TMapFriendEntry& mapUserID2FriendEntryB = rBFriend.GetFriendEntryMap();
        auto itrB = mapUserID2FriendEntryB.find(_rUser.GetUserID());
        if (itrB != mapUserID2FriendEntryB.end())
        {
            Update2DB(qwUserID, *itrB->second, eOpDel);
            mapUserID2FriendEntryB.erase(itrB);
        }
        pUserB->SendPkg(g_FriendProtS.BuildPkg_RemoveFriendAck(eFriendSuccess, _rUser.GetUserID()));
    }
    else
    {
        SFriendEntry sFriendEntry;
        sFriendEntry.qwUserID = _rUser.GetUserID();
        Update2DB(qwUserID, sFriendEntry, eOpDel);
    }

    if(bAddBlackList)
    {
        itr->second->eGroupType = eBlackFriend;
        _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAckEx(*itr->second));
        Update2DB(_rUser.GetUserID(), *itr->second, eOpUpdate);
    }
    else
    {
        Update2DB(_rUser.GetUserID(), *itr->second, eOpDel);
        _mapUserID2FriendEntry.erase(itr);
    }
}

EFriendResult CFriend::MoveFriend(UINT64 qwUserID, EFriendGroupType eGroupType)
{
    EFriendResult eRes = eFriendSuccess;

    do
    {
        // check group id
        if(eGroupNone == eGroupType || eBlackFriend == eGroupType || eGroupEnd <= eGroupType)
        {
            eRes = eFriendGroupIDErr;
            break;
        }

        // check exist?
        auto itr = _mapUserID2FriendEntry.find(qwUserID);
        if(itr == _mapUserID2FriendEntry.end())
        {
            eRes = eFriendNotExistErr;
            break;
        }

        // check group id
        SFriendEntryPtr pFriendEntryA = itr->second;
        if(pFriendEntryA->eGroupType == eGroupType || eBlackFriend == pFriendEntryA->eGroupType)
        {
            eRes = eFriendGroupIDErr;
            break;
        }

        // exec
        pFriendEntryA->eGroupType = eGroupType;

        Update2DB(_rUser.GetUserID(), *pFriendEntryA, eOpUpdate);
    } while(false);

    if(eRes != eFriendSuccess)
        SystemMessageNotify(_rUser, eRes);
    return eRes;
}

void CFriend::OnUserLogout(CUser& rUser)
{
    CFriend& rFriend = rUser.GetFriend();
    rFriend.UserChangeNotify(g_FriendProtS.BuildPkg_OnlineStatusNotify(rUser.GetUserID(), false));
}

void CFriend::OnUserLogin(CUser& rUser)
{
    CFriend& rFriend = rUser.GetFriend();
    rFriend.UserChangeNotify(g_FriendProtS.BuildPkg_OnlineStatusNotify(rUser.GetUserID(), true));
#if 0
    rFriend.UserChangeNotify(g_FriendProtS.BuildPkg_VIPChangeNotify(rUser.GetUserID(), rUser.VIPLevel(), rUser.VIPType()));
#endif
}

SFriendEntryPtr CFriend::GetFriendEntry(UINT64 qwUserID) const
{
    auto itr = _mapUserID2FriendEntry.find(qwUserID);
    if(itr != _mapUserID2FriendEntry.end())
        return itr->second;

    return NULL;
}

bool CFriend::IsFriendEntry(UINT64 qwUserID) const
{
    return _mapUserID2FriendEntry.find(qwUserID) != _mapUserID2FriendEntry.end();
}

bool CFriend::IsFriend(UINT64 qwUserID) const
{
    auto itr = _mapUserID2FriendEntry.find(qwUserID);
    if (itr == _mapUserID2FriendEntry.end())
        return false;
    return itr->second->eGroupType != eBlackFriend;
}

bool CFriend::IsBlackFriend(UINT64 qwUserID) const
{
    auto itr = _mapUserID2FriendEntry.find(qwUserID);
    if (itr == _mapUserID2FriendEntry.end())
        return false;

    if (itr->second->eGroupType != eBlackFriend)
        return false;

    return true;
}

bool CFriend::FriendInfoNotify()
{
    if(!_bInitialized)
    {
        LOG_CRI << "Friend Info has not been initialized! UsrID: " << _rUser.GetUserID();
        return false;
    }
    SFriend oFriend;
    oFriend.wMood = _rUser.GetMood();
    oFriend.strSign = _rUser.GetSign();
    TVecFriendEntry& vecFriendEntry = oFriend.vecFriendEntry;
    vecFriendEntry.reserve(_mapUserID2FriendEntry.size());
    for(auto itr = _mapUserID2FriendEntry.begin(); itr != _mapUserID2FriendEntry.end(); ++itr)
    {
        SFriendEntryPtr& pFriendEntry = itr->second;
        CUserPtr pUser = CUserMgr::GetUserByUserID(itr->second->qwUserID);
        if(NULL != pUser && pUser->GetState() == eUserInGame)
        {
            pFriendEntry->strName = pUser->GetUserName();
            pFriendEntry->wFighterID = pUser->GetFighterID();
            pFriendEntry->eSex = (ESexType)pUser->GetSex();
            pFriendEntry->byLevel = pUser->GetLevel();
            pFriendEntry->byColor = pUser->GetColor();
            pFriendEntry->byVIPLevel = pUser->GetVIPLevel();
            pFriendEntry->wMood = pUser->GetMood();
            pFriendEntry->strSign = pUser->GetSign();
            pFriendEntry->dwTotalRecharge = pUser->GetTotalRecharge();
            pFriendEntry->bOnlineStatus = true;
            pFriendEntry->byVIPLevel = pUser->GetVIPLevel();
            pFriendEntry->vecPlatforms = pUser->GetPlatformParam();
#if 0
            // TODO:
            pFriendEntry->eVIPType = pUser->VIPType();
            pFriendEntry->byYellowDiamond = pUser->YellowDiamondLevel();
            pFriendEntry->bYearlyPay = pUser->IsYearlyPay();
#endif
        }
        else
        {
            pFriendEntry->bOnlineStatus = false;
            pFriendEntry->vecPlatforms = CUserMgr::GetPlatformParam(itr->second->qwUserID);
        }

        vecFriendEntry.emplace_back(itr->second);
    }

    // notify user friend
    return _rUser.SendPkg(g_FriendProtS.BuildPkg_FriendInfoNotify(oFriend));
}

void CFriend::UserChangeNotify(const string& strMsg)
{
    for(auto itr = _mapUserID2FriendEntry.begin(); itr != _mapUserID2FriendEntry.end(); ++itr)
    {
        if(NULL == itr->second || itr->second->eGroupType == eBlackFriend)
            continue;

        CUserPtr pUser = CUserMgr::GetUserByUserID(itr->first);
        if(pUser != NULL)
            pUser->SendPkg(strMsg);
    }
}

UINT16 CFriend::GetFriendNum()
{
    UINT16 wCount = (UINT16)_mapUserID2FriendEntry.size();
    for (auto it = _mapUserID2FriendEntry.begin();it != _mapUserID2FriendEntry.end();it++)
    {
        if (eBlackFriend == it->second->eGroupType && wCount > 0)
            wCount--;
    }

    return wCount;
}

void CFriend::AddBlackList(UINT64 qwUserID)
{
    EFriendResult eRes = eFriendSuccess;
    do
    {
        // check is initialize
        if(!_bInitialized)
        {
            eRes = eFriendOtherErr;
            break;
        }

        // check duplicate
        auto itr = _mapUserID2FriendEntry.find(qwUserID);
        if(itr != _mapUserID2FriendEntry.end())
        {
            if(itr->second->eGroupType == eBlackFriend)
            {
                eRes = eFriendOnBlackList;
                break;
            }
            else
            {
                RemoveFriend(qwUserID, true);
                return;
            }
        }

        // fill data
        SFriendEntryPtr pFriendEntry(new SFriendEntry);
        if(!pFriendEntry)
        {
            eRes = eFriendOtherErr;
            break;
        }
        pFriendEntry->eGroupType = eBlackFriend;
        pFriendEntry->qwUserID = qwUserID;

        CUserPtr pDestUser = CUserMgr::GetUserByUserID(qwUserID);
        if(pDestUser)
        {
            pFriendEntry->bOnlineStatus = true;
            pFriendEntry->wFighterID = pDestUser->GetFighterID();
            pFriendEntry->byLevel = pDestUser->GetLevel();
            pFriendEntry->byColor = pDestUser->GetColor();
            pFriendEntry->byVIPLevel = pDestUser->GetVIPLevel();
            pFriendEntry->strName = pDestUser->GetUserName();
            pFriendEntry->byVIPLevel = pDestUser->GetVIPLevel();
            pFriendEntry->vecPlatforms = pDestUser->GetPlatformParam();
        }
        else
        {
            pFriendEntry->bOnlineStatus = false;
            pFriendEntry->wFighterID = 0;
            pFriendEntry->byLevel = 0;
            pFriendEntry->byColor = 0;
            pFriendEntry->strName = "";
        }
        pFriendEntry->vecPlatforms = CUserMgr::GetPlatformParam(qwUserID);
        // TODO:
        /*pFriendEntry->wFighterID = 0;
          pFriendEntry->byLevel = 0;
          pFriendEntry->strName = "";

          CUserPtr pDestUser = CUserMgr::GetUserByUserID(qwUserID);
        // correct
        if(pDestUser)
        pFriendEntry->bOnlineStatus = true;
        else
        pFriendEntry->bOnlineStatus = false;*/

        _mapUserID2FriendEntry.insert(make_pair(qwUserID, pFriendEntry));

        // notify client
        _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAckEx(*pFriendEntry));
        _rUser.SendPkg(g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgFriendAddBlack, BuildStrVec(pFriendEntry->strName)));

        Update2DB(_rUser.GetUserID(), *pFriendEntry, eOpAdd);
        return;
    } while(false);

    // exec
    SystemMessageNotify(_rUser, eRes);
    _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eRes,string(),ESEX_MAX));
}

void CFriend::AddBlackList(const std::string& strName)
{
    EFriendResult eRes = eFriendSuccess;

    do
    {
        // check is initialize
        if(!_bInitialized)
        {
            eRes = eFriendOtherErr;
            break;
        }

        // check exist
        CUserPtr pUserB = CUserMgr::GetUserByName(strName);
        if(!pUserB)
        {
            eRes = eFriendOfflineErr;
            break;
        }
        AddBlackList(pUserB->GetUserID());
        return;
    } while(false);

    // exec
    SystemMessageNotify(_rUser, eRes);
    _rUser.SendPkg(g_FriendProtS.BuildPkg_AddFriendAck(eRes,string(),ESEX_MAX));
}

void CFriend::SyncUserVIPLevel(UINT8 byVIPLevel)
{
    for(auto itr = _mapUserID2FriendEntry.begin(); itr != _mapUserID2FriendEntry.end(); ++itr)
    {
        if(NULL == itr->second || itr->second->eGroupType == eBlackFriend)
            continue;

        CUserPtr pUser = CUserMgr::GetUserByUserID(itr->first);
        if(pUser)
        {
            CFriend& rFriend = pUser->GetFriend();
            rFriend.ChangeVIPLevel(_rUser.GetRoleID(), byVIPLevel);
        }
    }
}

void CFriend::Update2DB(UINT64 qwUserID, SFriendEntry& rFriendEntry, EDataChange eDataChange)
{
    SFriendDBInfo oFriendDBInfo;

    oFriendDBInfo.byGroup = (UINT8)rFriendEntry.eGroupType;
    oFriendDBInfo.qwUserID = rFriendEntry.qwUserID;
    oFriendDBInfo.strName = rFriendEntry.strName;
    oFriendDBInfo.wFighterID = rFriendEntry.wFighterID;
    oFriendDBInfo.byLevel = rFriendEntry.byLevel;
    oFriendDBInfo.byColor = rFriendEntry.byColor;
    oFriendDBInfo.wMood = rFriendEntry.wMood;
    oFriendDBInfo.strSign = rFriendEntry.strSign;
    oFriendDBInfo.byVIPLevel = rFriendEntry.byVIPLevel;

    string strData;
    COutArchive iar(strData);
    iar << oFriendDBInfo;
    g_Center2DBCommC.Send_RoleDataUpdate(qwUserID, eTypeFriendInfo, eDataChange, strData);
}

bool CFriend::CheckAddFriendNum()
{
    const SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(_rUser.GetVIPLevel());
    if(pCfgVip == NULL)
        return false;

    if (GetFriendNum() + pCfgVip->_FriendNum >= SParamConfig::byFriendMax)
        return false;

    return true;
}
