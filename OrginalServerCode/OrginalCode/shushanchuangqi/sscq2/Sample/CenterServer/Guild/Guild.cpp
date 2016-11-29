#include "Guild.h"
#include "GuildUser.h"
#include "Protocols.h"
#include "GuildProt.h"
#include "GuildApplyInfo.h"
#include "GuildUserMgr.h"
#include "GuildMgr.h"
#include "GuildBuilding.h"
#include "GuildStatue.h"
#include "User.h"
#include "UserMgr.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "ItemProt.h"
#include "GuildLog.h"
#include "SystemMail.h"
#include "SysMsgDefine.h"
#include "RankMgr.h"
#include "GodMonsterMgr.h"
#include "Center2DBGuildC.h"
#include "Parameter.h"
#include "Tokenizer.h"

using namespace NItemProt;

const UINT32 IMPEACH_GOLD = 20;

CGuild::CGuild(CGuildUserPtr pUser, const string& strName):
    _strName(strName), _qwOwnerID(0), _dwExp(0), _pOwner(pUser),
    _qwQQGroupID(0), _dwMoney(0),
    _wPlayerFighterID(0), _byQuality(0), _dwCount(0),
    _qwImpeachLauncherRoleID(0), _byImpeachLauncherQuality(0)
{
    if (pUser)
    {
        _vecMemberPtr.push_back(pUser);
        _wPlayerFighterID = pUser->GetPlayerFighterID();
        _byQuality = pUser->GetQuality();
    }
    _strOwnerName = _pOwner->GetName();
    _qwOwnerID = _pOwner->GetID();
    _qwID = GET_GUID(GUID_GUILD);
    for (UINT8 byIndex = static_cast<UINT8>(eMemberNormal); byIndex < static_cast<UINT8>(eMemberMax); ++byIndex)
    {
        EMemberRank eRank = static_cast<EMemberRank>(byIndex);
        _mapAuthority[eRank] = DEFALUT_A_AUTHORITY_TABLE[byIndex];
        _mapRankCount[eRank] = DEFAULT_RANK_COUNT_TABLE[byIndex];
    }
}

CGuild::CGuild(const SGuildBaseInfo& rGuildBaseInfo):
    _qwImpeachLauncherRoleID(0), _byImpeachLauncherQuality(0)
{
    _qwID               = rGuildBaseInfo.qwGuildID;
    _strName            = rGuildBaseInfo.strName;
    _qwOwnerID          = rGuildBaseInfo.qwOwnerID;
    _strOwnerName       = rGuildBaseInfo.strOwnerName;
    _strInfo            = rGuildBaseInfo.strInfo;
    _qwQQGroupID        = rGuildBaseInfo.qwQQGroupID;
    _dwMoney            = rGuildBaseInfo.dwMoney;
    _wPlayerFighterID   = rGuildBaseInfo.wPlayerFighterID;
    _byQuality          = rGuildBaseInfo.byQuality;
    _dwCount            = rGuildBaseInfo.dwCount;
    for (UINT8 byIndex = static_cast<UINT8>(eMemberNormal); byIndex < static_cast<UINT8>(eMemberMax); ++byIndex)
    {
        EMemberRank eRank = static_cast<EMemberRank>(byIndex);
        _mapAuthority[eRank] = DEFALUT_A_AUTHORITY_TABLE[byIndex];
        _mapRankCount[eRank] = DEFAULT_RANK_COUNT_TABLE[byIndex];
    }
   
    _strLingShan = rGuildBaseInfo.strLingShan;
    Tokenizer tk(rGuildBaseInfo.strLingShan, "|");
    for (size_t i=0; i<tk.size(); i++)
    {
        UINT8 byLingShanID = atoi(tk[i].c_str());
        _vecLingShanType.push_back(byLingShanID);
    }
}

CGuild::~CGuild()
{
    _pOwner = NULL;
}

UINT64 CGuild::GetID() const
{
    return _qwID;
}

const string CGuild::GetIDHexString() const
{
    ostringstream strTmp;
    strTmp << std::hex << _qwID;
    return strTmp.str();
}

const string& CGuild::GetName() const
{
    return _strName;
}

const string& CGuild::GetInfo() const
{
    return _strInfo;
}

UINT8 CGuild::GetLevel() const
{
    if (_pStatueOwner)
    {
        return _pStatueOwner->GetLevel();
    }
    else
        LOG_CRI << "_pStatueOwner == NULL.";
    return 0;
}

UINT16 CGuild::GetBuildingMaxLevel() const
{

    const SGuildLevelCFG* pCFG = CGuildMgr::Instance().GetLevelConfig(GetLevel());
    if (pCFG)
        return pCFG->_Tower;
    return 1;
}

UINT64 CGuild::GetOwnerID() const
{
    return _qwOwnerID;
}

const string&   CGuild::GetOwnerName()  const
{
    if (_pOwner)
        return _pOwner->GetName();
    else
        return _strOwnerName;
}

UINT16 CGuild::GetMemberCount() const
{
    return _vecMemberPtr.size();
}

UINT16 CGuild::GetMaxMemberCount() const
{
    if (_pBuildingOwner)
        return _pBuildingOwner->GetAttrValue(eBuildingOracle);
    return 74;
}

UINT16 CGuild::GetEmptyMemberCount() const
{
    return 0;
}

UINT64 CGuild::GetQQGroupID() const
{
    return _qwQQGroupID;
}

UINT32 CGuild::GetMoney() const
{
    return _dwMoney;
}

UINT32 CGuild::GetCount() const
{
    return _dwCount;
}

UINT32 CGuild::GetBattleScore() const
{
    return CGuildMgr::Instance().GetBattleScore(GetID());
}

UINT16 CGuild::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

UINT8 CGuild::GetQuality() const
{
    return _byQuality;
}

CGuildBuildingOwnerPtr CGuild::GetBuildingOwner() const
{
    return _pBuildingOwner;
}

CGuildBuildingOwnerPtr CGuild::GetBuildingOwner()
{
    return _pBuildingOwner;
}

CGuildStatueOwnerPtr CGuild::GetStatueOwner() const
{
    return _pStatueOwner;
}

CGuildStatueOwnerPtr CGuild::GetStatueOwner()
{
    return _pStatueOwner;
}

bool   CGuild::SubMoney(UINT32 dwMoney)
{
    if (_dwMoney < dwMoney)
        return false;
    _dwMoney -= dwMoney;
    SetDirty(eGDTBaseInfo);
    SaveData();
    NotifyBaseInfo();
    return true;
}

void   CGuild::AddMoney(UINT32 dwMoney)
{
    _dwMoney += dwMoney;
    SetDirty(eGDTBaseInfo);
    SaveData();
    NotifyBaseInfo();
}

void    CGuild::SetMoney(UINT32 dwMoney)
{
    _dwMoney = dwMoney;
    SetDirty(eGDTBaseInfo);
    SaveData();
    NotifyBaseInfo();
}

void CGuild::AddCount(UINT32 dwCount)
{
    _dwCount += dwCount;
    SetDirty(eGDTBaseInfo);
    SaveData();
}

void CGuild::SetCount(UINT32 dwCount)
{
    _dwCount = dwCount;
    SetDirty(eGDTBaseInfo);
    SaveData();
}

TVecUINT8 CGuild::GetLingShanType()
{
    return _vecLingShanType;
}

const string& CGuild::GetLingShan() const
{
    return _strLingShan;
}

void CGuild::SetLingShan()
{
    _strLingShan = "";
    for (size_t i=0; i<_vecLingShanType.size(); i++)
    {
        char strTmp[30];
        sprintf_s(strTmp,"%d|", _vecLingShanType[i]);
        _strLingShan = _strLingShan + string(strTmp);
    }

    SetDirty(eGDTBaseInfo);
    SaveData();
}

void CGuild::SetQuality(UINT8 byQuality)
{
    _byQuality = byQuality;
    SetDirty(eGDTBaseInfo);
    SaveData();
}

void CGuild::SetPlayerFighterID(UINT16 wPlayerFighterID)
{
    _wPlayerFighterID = wPlayerFighterID;
    SetDirty(eGDTBaseInfo);
    SaveData();
}

bool CGuild::InitUser   (CGuildUserPtr pUser)
{
    if (!pUser)
        return false;
    CGuildPtr pTmpGuild = pUser->GetGuild();
    if (pTmpGuild && pTmpGuild->GetID() == _qwID)
    {
        LOG_WRN << "_qwID = " << _qwID << ", pTmpGuild->GetID() = " << pTmpGuild->GetID() << ".";
        return false;
    }
    _vecMemberPtr.push_back(pUser);
    if (pUser->GetRank() == eMemberOwner)
    {
        _qwOwnerID = pUser->GetID();
        _strOwnerName = pUser->GetName();
        _pOwner = pUser;

    }
    return true;
}

bool CGuild::InitAuthority(const TVecGuildAuthorityInfo& rvecAuthority)
{
    for (auto it = rvecAuthority.begin(); it != rvecAuthority.end(); ++it)
    {
        _mapAuthority[(*it)->eMemberRank] = (*it)->dwAuthority;
    }
    return true;
}

bool CGuild::InitBuildings()
{
    if (!_pBuildingOwner)
    {
        CGuildBuildingOwnerPtr pTmp(new CGuildBuildingOwner(ToThisPtr(this)));
        _pBuildingOwner = pTmp;
        CGuildBuildingOwner::Update2DB(_pBuildingOwner, eOpAdd);
    }
    return true;
}

bool CGuild::InitBuildings(const TVecGuildBuildingInfo& rvecBuildings)
{
    if (!_pBuildingOwner)
    {
        CGuildBuildingOwnerPtr pTmp(new CGuildBuildingOwner(ToThisPtr(this)));
        _pBuildingOwner = pTmp;
    }
    _pBuildingOwner->InitFromDB(rvecBuildings);
    return true;
}

bool CGuild::InitStatue()
{
    if (!_pStatueOwner)
    {
        CGuildStatueOwnerPtr pTmp(new CGuildStatueOwner(ToThisPtr(this)));
        _pStatueOwner = pTmp;
        CGuildStatueOwner::Update2DB(_pStatueOwner, eOpAdd);
    }
    return true;
}

bool CGuild::InitStatue(const SGuildStatueInfo& rGuildStatueInfo)
{
    if (!_pStatueOwner)
    {
        CGuildStatueOwnerPtr pTmp(new CGuildStatueOwner(ToThisPtr(this)));
        _pStatueOwner = pTmp;
    }
    _pStatueOwner->InitFromDB(rGuildStatueInfo);
    return true;
}

bool CGuild::InitLog(const TVecGuildLogInfo& rInfo)
{
    for (auto it = rInfo.rbegin(); it != rInfo.rend(); ++it)
    {
        CGuildLogPtr pLog;
        switch ((*it)->wMsgID)
        {
            case eMsgGuildImprove:
            case eMsgGuildDemote:
            case eMsgGuildJoin:
            case eMsgGuildQuit:
            case eMsgGuildKick:
            case eMsgGuildGiveOwner:
                {
                    CGuildMemberLogPtr pNewLog(new CGuildMemberLog);
                    pNewLog->InitFromDB(**it);
                    pLog = pNewLog;
                }
                break;
            case eMsgGuildDonate:
                {
                    CGuildDonateLogPtr pNewLog(new CGuildDonateLog);
                    pNewLog->InitFromDB(**it);
                    pLog = pNewLog;
                }
                break;
            case eMsgGuildBuildingUpgrade:
                {
                    CGuildBuildingLogPtr pNewLog(new CGuildBuildingLog);
                    pNewLog->InitFromDB(**it);
                    pLog = pNewLog;
                }
                break;
            case eMsgGuildStatue:
                {
                    CGuildStatueLogPtr pNewLog(new CGuildStatueLog);
                    pNewLog->InitFromDB(**it);
                    pLog = pNewLog;
                }
                break;
            default:
                break;
        }
        if (pLog)
            _vecLogPtr.push_back(pLog);
    }
    return true;
}

bool CGuild::EditInfo   (const string& strInfo, EEditInfoResult& eResult)
{
    if (strInfo.length() >= MAX_INFO_LENGTH)
    {
        eResult = eGEditInfoTooLong;
        return false;
    }
    _strInfo = strInfo;
    SetDirty(eGDTBaseInfo);
    SaveData();

    CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(GetID());
    if (pGuildListInfo)
        pGuildListInfo->SetInfo(strInfo);

    NotifyBaseInfo();
    eResult = eGEditInfoSuccess;
    return true;
}

bool CGuild::SetMemberAuthority(EMemberRank eRank, UINT32 dwAuthority, CGuildUserPtr pUser, ESetAuthorityResult& eResult)
{
    if (pUser->GetRank() != eMemberOwner)
    {
        eResult = eGSetAuthorityNoAuthority;
        return false;
    }
    _mapAuthority[eRank] = dwAuthority;
    NotifyAuthorityInfo();
    SetDirty(eGDTAuthority);
    SaveData();
    return true;
}

/*
   bool CGuild::SetMemberRank(UINT64 qwRoleID, EMemberRank eNewRank, CGuildUserPtr pUser, EMemberOperateResult& eResult)
   {
   bool bFound = false;
   if (pUser->GetID() == qwRoleID) // 设置自己的权限
   {
   eResult = eGMOpResultSelf;
   return false;
   }
   else    // 设置他人的权限
   {
   if (pUser->GetRank() <= eNewRank)
   {
   eResult = eGMOpResultTooHigh;
   return false;
   }
   for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
   {
   if (*it && (*it)->GetID() == qwRoleID)
   {
   EMemberRank eOldRank = (*it)->GetRank();
   (*it)->SetRank(eNewRank);
   OnGuildUserRankChanged(*it, pUser, eOldRank, eNewRank);
   bFound = true;
   break;
   }
   }
   }
   return bFound;
   }
   */

bool CGuild::KickMember(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult)
{
    bool bFound = false;
    eResult = eGMOpResultFailed;
    if (!CGuildMgr::Instance().IsGuildOpEnable())
    {
        eResult = eGMOpResultGuildBattle;
        return false;
    }
    if (pUser->GetID() == qwRoleID) // 设置自己的权限
    {
        eResult = eGMOpResultSelf;
        return false;
    }
    else    // 设置他人的权限
    {
        for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
        {
            if (*it && (*it)->GetID() == qwRoleID)
            {
                bFound = true;
                CGuildUserPtr pGuildUser = *it;
                EMemberRank eRank = pGuildUser->GetRank();
                if (pUser->GetRank() <= eRank)
                {
                    eResult = eGMOpResultTooHigh;
                    return false;
                }

                if (pGuildUser->GetID() == _qwImpeachLauncherRoleID)
                {
                    eResult = eGMOpResultHaveImpeach;
                    return false;
                }
                _vecMemberPtr.erase(it);
                eResult = eGMOpResultSuccess;
                OnGuildUserQuit(pGuildUser, pUser);
                break;
            }
        }
    }
    return bFound;
}

bool CGuild::UpMemberRank(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult)
{
    eResult = eGMOpResultFailed;
    bool bFound = false;
    if (pUser->GetID() == qwRoleID) // 设置自己的权限
    {
        eResult = eGMOpResultSelf;
        return false;
    }
    else    // 设置他人的权限
    {
        for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
        {
            if (*it && (*it)->GetID() == qwRoleID)
            {
                bFound = true;
                EMemberRank eOldRank = (*it)->GetRank();
                EMemberRank eNewRank = static_cast<EMemberRank>(static_cast<UINT8>(eOldRank) + 1);
                if (pUser->GetRank() <= eNewRank)
                {
                    eResult = eGMOpResultTooHigh;
                    return false;
                }
                if (GetMemberRankCount(eNewRank) >= _mapRankCount[eNewRank])
                {
                    eResult = eGMOpResultTooMany;
                    return false;
                }

                (*it)->SetRank(eNewRank);
                OnGuildUserRankChanged(*it, pUser, eOldRank, eNewRank);
                eResult = eGMOpResultSuccess;
                NotifyUserInfo();
                break;
            }
        }
    }
    return bFound;
}

bool CGuild::DownMemberRank(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult)
{
    if (pUser->GetID() == qwRoleID) // 设置自己的权限
    {
        eResult = eGMOpResultSelf;
        return false;
    }
    else    // 设置他人的权限
    {
        for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
        {
            if (*it && (*it)->GetID() == qwRoleID)
            {
                EMemberRank eOldRank = (*it)->GetRank();
                if (eOldRank == eMemberNormal)
                {
                    eResult = eGMOpResultTooLow;
                    return false;
                }
                if (pUser->GetRank() <= eOldRank)
                {
                    eResult = eGMOpResultNoAuthority;
                    return false;
                }
                EMemberRank eNewRank = static_cast<EMemberRank>(static_cast<UINT8>(eOldRank) - 1);
                if (GetMemberRankCount(eNewRank) >= _mapRankCount[eNewRank])
                {
                    eResult = eGMOpResultTooMany;
                    return false;
                }

                (*it)->SetRank(eNewRank);
                OnGuildUserRankChanged(*it, pUser, eOldRank, eNewRank);
                eResult = eGMOpResultSuccess;
                NotifyUserInfo();
                break;
            }
        }
    }
    return true;
}

bool CGuild::FireMemberRank(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult)
{
    if (pUser->GetID() == qwRoleID) // 设置自己的权限
    {
        eResult = eGMOpResultSelf;
        return false;
    }
    else    // 设置他人的权限
    {
        for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
        {
            if (*it && (*it)->GetID() == qwRoleID)
            {
                EMemberRank eNewRank = (*it)->GetRank();
                if (eNewRank == eMemberNormal)
                {
                    eResult = eGMOpResultTooLow;
                    return false;
                }
                if (pUser->GetRank() <= eNewRank)
                {
                    eResult = eGMOpResultNoAuthority;
                    return false;
                }
                EMemberRank eOldRank = (*it)->GetRank();
                (*it)->SetRank(eMemberNormal);
                OnGuildUserRankChanged(*it, pUser, eOldRank, eMemberNormal);
                eResult = eGMOpResultSuccess;
                NotifyUserInfo();
                break;
            }
        }
    }
    return true;
}

bool CGuild::GiveOwner(UINT64 qwRoleID, CGuildUserPtr pUser, EMemberOperateResult& eResult)
{
    if (pUser->GetID() == qwRoleID) // 设置自己的权限
    {
        eResult = eGMOpResultSelf;
        return false;
    }
    else    // 设置他人的权限
    {
        for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
        {
            if (*it && (*it)->GetID() == qwRoleID)
            {
                pUser->SetRank(eMemberNormal);
                CGuildUser::Update2DB(pUser, eOpUpdate);

                _pOwner = *it;
                _wPlayerFighterID = (*it)->GetPlayerFighterID();
                _byQuality = (*it)->GetQuality();
                EMemberRank eNewRank = eMemberOwner;
                EMemberRank eOldRank = _pOwner->GetRank();
                _pOwner->SetRank(eMemberOwner);
                _qwOwnerID = _pOwner->GetID();
                _strOwnerName = _pOwner->GetName();
                CGuildUser::Update2DB(_pOwner, eOpUpdate);

                CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(GetID());
                if (pGuildListInfo)
                {
                    pGuildListInfo->SetOwnerID(qwRoleID);
                    pGuildListInfo->SetOwnerName(_pOwner->GetName());
                }

                OnGuildUserRankChanged(_pOwner, pUser, eOldRank, eNewRank);
                eResult = eGMOpResultSuccess;
                SaveData();
                NotifyUserInfo();
                NotifyBaseInfo();
                break;
            }
        }
    }

    UINT32 dwID = CCenterConfig::Instance().GetSvrID();
    g_Game2CenterGuildBattleS.SendSvr_GuildOwnerChanged(&dwID, 1, GetID(), GetOwnerName());
    return true;
}

bool CGuild::GetAllInfo(SGuildAllInfo& rAllInfo, CGuildUserPtr pGuildUser) const
{
    GetBaseInfo(rAllInfo.sBaseInfo, pGuildUser);
    GetMemberInfo(rAllInfo.vecMemberInfo);
    GetApplyInfo(rAllInfo.vecApplyInfo);
    GetAuthorityInfo(rAllInfo.vecAuthority);
    GetBuildingInfo(rAllInfo.vecBuildingInfo);
    if (pGuildUser)
        pGuildUser->GetTechInfo(rAllInfo.vecTech);
    GetStatueInfo(rAllInfo.sStatueInfo);
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (pUser)
    {
        CCenterVar& rVar = pUser->GetCenterVar();
        rAllInfo.sStatueInfo.byWorshipBit = rVar.GetVar(NVarDefine::ePlayerVarGuildWorship);
    }
    GetLogInfoWithoutType(eLogStatue, rAllInfo.vecLogInfo);
    return true;
}

bool CGuild::GetBaseInfo(SGuildBaseInfo& rBaseInfo, CGuildUserPtr pGuildUser) const
{
    rBaseInfo.qwGuildID        = GetID();
    rBaseInfo.qwOwnerID        = GetOwnerID();
    rBaseInfo.strName          = GetName();
    rBaseInfo.strInfo          = GetInfo();
    rBaseInfo.strOwnerName     = GetOwnerName();
    rBaseInfo.qwQQGroupID      = GetQQGroupID();
    rBaseInfo.dwMoney          = GetMoney();
    rBaseInfo.wUserCount       = GetMemberCount();
    rBaseInfo.wMaxUserCount    = GetMaxMemberCount();;
    rBaseInfo.wPlayerFighterID = GetPlayerFighterID();
    rBaseInfo.byQuality        = GetQuality();
    rBaseInfo.dwCount          = GetCount();
    rBaseInfo.strLingShan      = GetLingShan();
    
    if (pGuildUser)
    {
        rBaseInfo.eSelfRank = pGuildUser->GetRank();
        rBaseInfo.dwContribution = pGuildUser->GetContribution();
        rBaseInfo.dwRemainDonate = pGuildUser->GetRemainDonate();
    }
    else
    {
        rBaseInfo.eSelfRank = eMemberNormal;
        rBaseInfo.dwContribution = 0;
        rBaseInfo.dwRemainDonate = 0;
    }
    GodMonsterPtr pMonster = g_GodMonsterMgr.GetMonster(GetID());
    if(pMonster)
        rBaseInfo.dwScore = pMonster->GetScore();
    return true;
}

bool CGuild::GetMemberInfo(TVecSGuildInfoBase& rInfo) const
{
    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        if (*it)
        {
            SGuildUserInfoPtr pUserInfo(new SGuildUserInfo);
            if (pUserInfo)
            {
                (*it)->GetAllInfo(*pUserInfo);
                rInfo.push_back(pUserInfo);
            }
        }
    }
    return true;
}

bool CGuild::GetMemberInfo(TVecGuildUserInfo& rInfo) const
{
    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        if (*it)
        {
            SGuildUserInfoPtr pUserInfo(new SGuildUserInfo);
            if (pUserInfo)
            {
                (*it)->GetAllInfo(*pUserInfo);
                rInfo.push_back(pUserInfo);
            }
        }
    }
    return true;
}

bool CGuild::GetApplyInfo(TVecGuildApplyInfo& rInfo) const
{
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (*it)
        {
            SGuildApplyInfoPtr pApplyInfo (new (SGuildApplyInfo));
            pApplyInfo->qwRoleID        = (*it)->GetRoleID();
            pApplyInfo->strName         = (*it)->GetName();
            pApplyInfo->wLevel          = (*it)->GetLevel();
            pApplyInfo->dwBattlePoint   = (*it)->GetBattlePoint();
            rInfo.push_back(pApplyInfo);
        }
    }
    return true;
}

bool CGuild::GetAuthorityInfo(TVecGuildAuthorityInfo& rvecInfo) const
{
    for (auto it = _mapAuthority.begin(); it != _mapAuthority.end(); ++it)
    {
        SGuildAuthorityInfoPtr pAuthorityInfo (new SGuildAuthorityInfo);
        pAuthorityInfo->qwGuildID   = GetID();
        pAuthorityInfo->eMemberRank = it->first;
        pAuthorityInfo->dwAuthority = it->second;
        rvecInfo.push_back(pAuthorityInfo);
    }
    return true;
}

bool CGuild::GetAuthorityInfo(TVecSGuildInfoBase& rvecInfo) const
{
    for (auto it = _mapAuthority.begin(); it != _mapAuthority.end(); ++it)
    {
        SGuildAuthorityInfoPtr pAuthorityInfo (new SGuildAuthorityInfo);
        pAuthorityInfo->qwGuildID   = GetID();
        pAuthorityInfo->eMemberRank = it->first;
        pAuthorityInfo->dwAuthority = it->second;
        rvecInfo.push_back(pAuthorityInfo);
    }
    return true;
}

bool CGuild::GetBuildingInfo(TVecSGuildInfoBase& rvecInfo) const
{
    if (_pBuildingOwner)
    {
        _pBuildingOwner->GetAllInfo(rvecInfo);
        return true;
    }
    return false;
}

bool CGuild::GetBuildingInfo(TVecGuildBuildingInfo& rvecInfo) const
{
    if (_pBuildingOwner)
    {
        _pBuildingOwner->GetAllInfo(rvecInfo);
        return true;
    }
    return false;
}

bool CGuild::GetStatueInfo(SGuildStatueInfo& rInfo) const
{
    if(_pStatueOwner)
    {
        _pStatueOwner->GetAllInfo(rInfo);
        GetLogInfoWithType(eLogStatue, rInfo.vecLogInfo);
        return true;
    }
    return false;
}

bool CGuild::GetLogInfo(TVecSGuildInfoBase& rInfo) const
{
    for (auto it = _vecLogPtr.begin(); it != _vecLogPtr.end(); ++it)
    {
        if (!(*it))
            continue;
        SGuildLogInfoPtr pInfo(new SGuildLogInfo);
        (*it)->GetAllInfo(*pInfo);
        rInfo.push_back(pInfo);
    }
    return true;
}

bool CGuild::GetLogInfo(TVecGuildLogInfo& rInfo) const
{
    for (auto it = _vecLogPtr.begin(); it != _vecLogPtr.end(); ++it)
    {
        if (!(*it))
            continue;
        SGuildLogInfoPtr pInfo(new SGuildLogInfo);
        (*it)->GetAllInfo(*pInfo);
        rInfo.push_back(pInfo);
    }
    return true;
}

bool CGuild::GetLogInfoWithoutType(ELogType eType, TVecSGuildInfoBase& rvecLogInfo) const
{
    for (auto it = _vecLogPtr.begin(); it != _vecLogPtr.end(); ++it)
    {
        if ((*it) && ((*it)->GetType() != eType))
        {
            SGuildLogInfoPtr pInfo(new SGuildLogInfo);
            (*it)->GetAllInfo(*pInfo);
            rvecLogInfo.push_back(pInfo);
        }
    }
    return true;
}

bool CGuild::GetLogInfoWithoutType(ELogType eType, TVecGuildLogInfo& rvecLogInfo) const
{
    for (auto it = _vecLogPtr.begin(); it != _vecLogPtr.end(); ++it)
    {
        if ((*it) && ((*it)->GetType() != eType))
        {
            SGuildLogInfoPtr pInfo(new SGuildLogInfo);
            (*it)->GetAllInfo(*pInfo);
            rvecLogInfo.push_back(pInfo);
        }
    }
    return true;
}

bool CGuild::GetLogInfoWithType(ELogType eType, TVecGuildLogInfo& rvecLogInfo) const
{
    for (auto it = _vecLogPtr.begin(); it != _vecLogPtr.end(); ++it)
    {
        if ((*it) && ((*it)->GetType() == eType))
        {
            SGuildLogInfoPtr pInfo(new SGuildLogInfo);
            (*it)->GetAllInfo(*pInfo);
            rvecLogInfo.push_back(pInfo);
        }
    }
    return true;
}

void CGuild::AddApplyInfo(CGuildApplyInfoPtr pApplyInfo)
{
    if (pApplyInfo)
        _vecApplyInfoPtr.push_back(pApplyInfo);
}

bool CGuild::AgreeApply(UINT64 qwRoleID, CGuildUserPtr pGuildUser, EApplyResult& eResult)
{
    if (!CGuildMgr::Instance().IsGuildOpEnable())
    {
        eResult = eGApplyGuildBattle;
        return false;
    }
    if (GetMemberCount() >= GetMaxMemberCount())
    {
        eResult = eGApplyGuildFull;
        return false;
    }
    eResult = eGApplyFailed;
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (!*it)
            continue;
        if ((*it)->GetRoleID() == qwRoleID)
        {
            _vecApplyInfoPtr.erase (it);
            NotifyApplyInfo();
            CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
            if (pGuildUser)
            {
                if (pGuildUser->GetGuildID())
                {
                    if (pGuildUser->GetGuildID() == GetID())
                        eResult = eGApplyInGuild;
                    else
                        eResult = eGApplyOtherGuild;
                }
                else
                {
                    PreGuildUserEnter(pGuildUser);
                    eResult = eGApplySuccess;
                    _vecMemberPtr.push_back(pGuildUser);

                    OnGuildUserEnter(pGuildUser);

                }
            }
            else
                eResult = eGApplyFailed;
            break;
        }
    }
    if (eResult == eGApplySuccess)
    {
        //LogServer日志
        SLogOp sLog;
        sLog.eType = eOpType_Apply;
        sLog.qwGuildID = GetID();
        sLog.byParam = 0;
        CGuildMgr::Instance().WriteGuildLog(sLog);
        return true;
    }
    else
        return false;
}

bool CGuild::AgreeApplyAll(CGuildUserPtr pGuildUser, EApplyResult& eResult)
{
    if (!CGuildMgr::Instance().IsGuildOpEnable())
    {
        eResult = eGApplyGuildBattle;
        return false;
    }
    if (GetMemberCount() >= GetMaxMemberCount())
    {
        eResult = eGApplyGuildFull;
        return false;
    }
    
    eResult = eGApplyFailed;
    auto it = _vecApplyInfoPtr.begin();
    for (; it != _vecApplyInfoPtr.end(); ++it)
    {
        if (!(*it))
            continue;

        CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID((*it)->GetRoleID());
        if (pGuildUser)
        {
            if (pGuildUser->GetGuildID())
            {
                if (pGuildUser->GetGuildID() == GetID())
                    eResult = eGApplyInGuild;
                else
                    eResult = eGApplyOtherGuild;
            }
            else
            {
                PreGuildUserEnter(pGuildUser);
                eResult = eGApplySuccess;
                _vecMemberPtr.push_back(pGuildUser);
                
                OnGuildUserEnter(pGuildUser);
            }
        }
        else
            CGuildMgr::Instance().AgreeApplyForGuild((*it)->GetRoleID(), (*it));
        if (GetMemberCount() >= GetMaxMemberCount())
            break;
    }
    for (; it != _vecApplyInfoPtr.end(); ++it)
    {
        if (!(*it))
            continue;
            CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID((*it)->GetRoleID());
        if (pGuildUser)
            pGuildUser->EraseApplyInfo(GetID());
    }
    _vecApplyInfoPtr.clear();

    NotifyApplyInfo();

    if (eResult == eGApplySuccess)
        return true;
    else
        return false;

    if (eResult == eGApplySuccess)
    {
        //LogServer日志
        SLogOp sLog;
        sLog.eType = eOpType_Apply;
        sLog.qwGuildID = GetID();
        sLog.byParam = 0;
        CGuildMgr::Instance().WriteGuildLog(sLog);
        return true;
    }
    else
        return false;
}

bool CGuild::RejectApply(UINT64 qwRoleID, CGuildUserPtr pGuildUser, EApplyResult& eResult)
{
    eResult = eGApplyFailed;
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (!*it)
            continue;
        if ((*it)->GetRoleID() == qwRoleID)
        {
            _vecApplyInfoPtr.erase (it);
            CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwRoleID);
            if (pGuildUser)
            {
                if (pGuildUser->GetGuildID())
                {
                    if (pGuildUser->GetGuildID() == GetID())
                        eResult = eGApplyInGuild;
                    else
                        eResult = eGApplyOtherGuild;
                }
                else
                {
                    pGuildUser->EraseApplyInfo(GetID());
                    eResult = eGApplySuccess;
                }
                CUserPtr pUser = pGuildUser->GetOnlineUser();
                if (pUser)
                {
                    string strData = g_GuildProtS.BuildPkg_GuildApplyRejectNotify(GetID());
                    pUser->SendPkg(strData);
                }
            }
            else
                eResult = eGApplyFailed;
            NotifyApplyInfo();
            break;
        }
    }
    if (eResult == eGApplySuccess)
        return true;
    else
        return false;
}

bool CGuild::RejectApplyAll(CGuildUserPtr pGuildUser, EApplyResult& eResult)
{
    eResult = eGApplyFailed;
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (!*it)
            continue;
        CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID((*it)->GetRoleID());
        if (pGuildUser)
        {
            if (pGuildUser->GetGuildID())
            {
                if (pGuildUser->GetGuildID() == GetID())
                    eResult = eGApplyInGuild;
                else
                    eResult = eGApplyOtherGuild;
            }
            else
            {
                pGuildUser->EraseApplyInfo(GetID());
                eResult = eGApplySuccess;
            }
            CUserPtr pUser = pGuildUser->GetOnlineUser();
            if (pUser)
            {
                string strData = g_GuildProtS.BuildPkg_GuildApplyRejectNotify(GetID());
                pUser->SendPkg(strData);
            }
        }
        else
            CGuildMgr::Instance().RejectApplyForGuild((*it)->GetRoleID(), *it);
    }
    _vecApplyInfoPtr.clear();
    NotifyApplyInfo();
    if (eResult == eGApplySuccess)
        return true;
    else
        return false;
}

bool CGuild::CancelApply(UINT64 qwRoleID, EApplyResult& eResult)
{
    eResult = eGApplyFailed;
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID((*it)->GetRoleID());
        if (pGuildUser && pGuildUser->GetRoleID() == qwRoleID)
        {
            if (pGuildUser->GetGuildID())
            {
                if (pGuildUser->GetGuildID() == GetID())
                    eResult = eGApplyInGuild;
                else
                    eResult = eGApplyOtherGuild;
            }
            else
            {
                pGuildUser->EraseApplyInfo(GetID());
                eResult = eGApplySuccess;
            }
            _vecApplyInfoPtr.erase(it);
            break;
        }
    }
    NotifyApplyInfo();
    if (eResult == eGApplySuccess)
        return true;
    else
        return false;

}

bool CGuild::InviteOther(CGuildUserPtr pGuildUser, const string& strName, EApplyResult& eResult)
{
    CUserPtr pUser = CUserMgr::GetUserByName(strName);
    if (!pUser)
    {
        eResult = eGApplyNoUser;
        return false;
    }
    if (pUser->GetUserID() == pGuildUser->GetRoleID())
    {
        eResult = eGApplyNoSelf;
        return false;
    }
    if (GetMemberCount() >= GetMaxMemberCount())
    {
        eResult = eGApplyGuildFull;
        return false;
    }
    if (!pUser->IsOnline())
    {
        eResult = eGApplyNotOnline;
        return false;
    }
    if (pUser->GetLevel() < MIN_GUILD_USER_LEVEL)
    {
        eResult = eGApplyLevelLow;
        return false;
    }

    CGuildUserPtr pOtherGuildUser = pUser->GetGuildUser();
    if (pOtherGuildUser)
    {
        CGuildPtr pGuild =  pOtherGuildUser->GetGuild();
        if (pGuild)
        {
            if (pGuild == ToThisPtr(this))
                eResult = eGApplyInGuild;
            else
                eResult = eGApplyOtherGuild;
            return false;
        }
    }

    TVecINT64 vecParam;
    TVecString vecString;
    UINT32 dwSeverID = pUser->GetGameSvrID();
    vecString.push_back(pGuildUser->GetName());
    vecString.push_back(GetName());
    vecParam.push_back(GetID());
    g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID, 1, pUser->GetUserID(), eOpAdd, 4, vecParam, vecString);

    string strData = g_GuildProtS.BuildPkg_GuildInviteNotify(GetID(), GetName(), pGuildUser->GetName());
    pUser->SendPkg(strData);
    eResult = eGApplySuccess;
    return true;
}

bool CGuild::InviteReply(bool bAgree, CGuildUserPtr pGuildUser, EApplyResult& eResult)
{
    if (!CGuildMgr::Instance().IsGuildOpEnable())
    {
        eResult = eGApplyGuildBattle;
        return false;
    }
    if (GetMemberCount() >= GetMaxMemberCount())
    {
        eResult = eGApplyGuildFull;
        return false;
    }
    if (bAgree)
    {
        PreGuildUserEnter(pGuildUser);
        eResult = eGApplySuccess;
        _vecMemberPtr.push_back(pGuildUser);
        OnGuildUserEnter(pGuildUser);

    }
    return true;
}

bool CGuild::QuitGuild(CGuildUserPtr pGuildUser, EQuitResult& eResult)
{
    if (!pGuildUser)
    {
        eResult = eGQuitFailed;
        return false;
    }
    if (!CGuildMgr::Instance().IsGuildOpEnable())
    {
        eResult = eGQuitGuildBattle;
        return false;
    }
    eResult = eGQuitNoGuild;
    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        if (*it == pGuildUser)
        {
            if (pGuildUser->GetRank() == eMemberOwner) // 解散帮派
                return DisbandGuild(pGuildUser, eResult);
            else // 非帮主退出帮派（帮派不解散）
            {
                _vecMemberPtr.erase(it);
                eResult = eGQuitSuccess;
                OnGuildUserQuit(pGuildUser);
            }
            break;
        }
    }
    return true;
}

bool CGuild::DisbandGuild(CGuildUserPtr pGuildUser, EQuitResult& eResult)
{
    if (_vecMemberPtr.size () > 1)
    {
        eResult = eGQuitOwnerQuit;
        return false;
    }
    else
    {
        OnGuildUserQuit(pGuildUser);
        for (auto it2 = _vecApplyInfoPtr.begin(); it2 != _vecApplyInfoPtr.end(); ++it2)
        {
            CGuildUserPtr pGuildUser2 = CGuildUserMgr::Instance().GetUserByUserID((*it2)->GetRoleID());
            if (pGuildUser2)
                pGuildUser2->EraseApplyInfo(GetID());
        }
        CGuildMgr::Instance().DisbandGuild(ToThisPtr(this));
        eResult = eGQuitSuccess;
        CUserPtr pUser = pGuildUser->GetOnlineUser();
        TVecINT32 vecParam2;
        ostringstream strInfo2;
        strInfo2 << GetID();
        if (pUser &&(pUser->IsOnline()))
        {
            pUser->OnEvent(eEventType_GuildDismiss,vecParam2, strInfo2.str());
        }
        else
        {
            CUser::AddOffLineEvent(pGuildUser->GetID(),eEventType_GuildDismiss,vecParam2, strInfo2.str());
        }
        return true;
    }
}

bool CGuild::LaunchImpeach(CGuildUserPtr pGuildUser, EImpeachResult& eResult, function<void(UINT8 byRet)> func)
{
    if (_qwImpeachLauncherRoleID)
    {
        eResult = eGImpeachResultHasLaunched;
        return false;
    }
    if (pGuildUser->GetRank() == eMemberOwner)
    {
        eResult = eGImpeachResultSelf;
        return false;
    }
    if (!pGuildUser->HasAuthority(G_IMPEACH))
    {
        eResult = eGImpeachResultNoAuthority;
        return false;
    }
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (!pUser || !pUser->IsOnline())
    {
        eResult = eGImpeachResultFailed;
        return false;
    }
    if (pUser->GetGold() < IMPEACH_GOLD)
    {
        eResult = eGImpeachResultLackOfGold;
        return false;
    }
    UINT8 byQuality = pUser->GetQuality();
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID, 1, pUser->GetUserID(), NLogDataDefine::ItemTo_GuildDonate, static_cast<UINT8>(EMONEY_GOLD), IMPEACH_GOLD,
            [this, pGuildUser, func, byQuality](UINT8 byError, UINT8 byRet)
            { 
                if (byRet == 0)
                {
                    _qwImpeachLauncherRoleID = pGuildUser->GetRoleID();
                    _byImpeachLauncherQuality = byQuality;
                    _strImpeachLauncherName  = pGuildUser->GetName();
                    _setImpeachAgreeer.insert(pGuildUser->GetRoleID());
                    NotifyImpeachInfo();
                }
                func(byRet);
            });
    return true;
}

bool CGuild::CancelImpeach()
{
    _qwImpeachLauncherRoleID = 0;
    _byImpeachLauncherQuality = 0;
    _strImpeachLauncherName = "";
    _setImpeachAgreeer.clear();
    _setImpeachRejecter.clear();
    NotifyImpeachCancel();
    return true;
}

bool CGuild::ImpeachReply(bool bAgree, CGuildUserPtr pGuildUser, EImpeachResult& eResult)
{
    if (!_qwImpeachLauncherRoleID)
    {
        eResult = eGImpeachResultFailed;
        return false;
    }
    if (pGuildUser->GetRoleID() == _qwImpeachLauncherRoleID)
    {
        eResult = eGImpeachResultSelf;
        return false;
    }
    if (_setImpeachRejecter.find(pGuildUser->GetRoleID()) != _setImpeachRejecter.end() || 
            _setImpeachAgreeer.find(pGuildUser->GetRoleID())!= _setImpeachAgreeer.end())
    {
        eResult = eGImpeachResultHasReplyed;
        return false;
    }
    if (bAgree)
        _setImpeachAgreeer.insert(pGuildUser->GetRoleID());
    else
        _setImpeachRejecter.insert(pGuildUser->GetRoleID());
    eResult = eGImpeachResultSuccess;
    
    return true;
}

bool CGuild::Donate(CGuildUserPtr pGuildUser, UINT32 dwMoney, EDonateResult& eResult, function<void(UINT8 byRet)> func)
{
    if (!pGuildUser)
    {
        eResult = eGDResultFailed;
        return false;
    }
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (!pUser || !pUser->IsOnline())
    {
        eResult = eGDResultFailed;
        return false;
    }
    if (!_pBuildingOwner)
    {
        eResult = eGDResultFailed;
        return false;
    }

    dwMoney = dwMoney / 100 * 100; // 取100的整数倍
    if (!dwMoney)
    {
        eResult = eGDResultFailed;
        return false;
    }

    CCenterVar& rVar = pUser->GetCenterVar();
    UINT32 dwDonated = rVar.GetVar(NVarDefine::ePlayerVarGuildDonate);
    if (dwDonated + dwMoney > MAX_DONATE_EVERYDAY)
    {
        eResult = eGDResultFull;
        return false;
    }
    if (pUser->GetSilver() < dwMoney)
    {
        eResult = eGDResultLackofSilver;
        return false;
    }
    if (_pBuildingOwner->GetAttrValue(eBuildingDepot) < (dwMoney + GetMoney()))
    {
        eResult = eGDResultDepotFull;
        return false;
    }
    UINT8 byQuality = pUser->GetQuality();

    // 异步处理增减钱
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID, 1, pUser->GetUserID(), NLogDataDefine::ItemTo_GuildWorship, static_cast<UINT8>(EMONEY_SILVER), dwMoney, 
            [func, this, dwMoney, pGuildUser, &rVar, pUser, byQuality](UINT8 byError, UINT8 byRet)
            { 
                if (byRet == 0)
                {
                    rVar.AddVar(NVarDefine::ePlayerVarGuildDonate, dwMoney);
                    AddMoney(dwMoney);
                    pGuildUser->AddContribution(dwMoney / 200);
                    CGuildDonateLogPtr pLog (new CGuildDonateLog);
                    if (pLog->FormatParam(byQuality, pGuildUser->GetName(), dwMoney))
                        AddLog(pLog);
                    TVecINT32 vecParam2;
                    vecParam2.push_back(GetMoney());
                    vecParam2.push_back(dwMoney);
                    vecParam2.push_back(dwMoney / 20);
                    vecParam2.push_back(dwMoney);
                    ostringstream strInfo2;
                    strInfo2 << GetID();

                    if (pUser &&(pUser->IsOnline() ))
                    {
                        //帮派id，帮派当前资金，帮派增加资金，获得贡献数，捐献银币数
                        pUser->OnEvent(eEventType_GuildDonate,vecParam2, strInfo2.str());
                    }
                    else
                    {
                        CUser::AddOffLineEvent(pUser->GetUserID(),eEventType_GuildDonate,vecParam2, strInfo2.str());
                    }
                    //LogServer 日志
                    SLogOp sLog;
                    sLog.eType = eOpType_Donate;
                    sLog.qwGuildID = GetID();
                    sLog.byParam = 0;
                    CGuildMgr::Instance().WriteGuildLog(sLog);
                    NotifyIDInfo(eMsgGuildDonate, BuildStrVec(static_cast<UINT32>(byQuality), pGuildUser->GetName(), dwMoney));
                }
                func(byRet);
            });
    return false;
}

void CGuild::AddLog(CGuildLogPtr pLog)
{
    if (pLog)
    {
        _vecLogPtr.push_back(pLog);
        CGuildLog::Update2DB(pLog, eOpAdd, GetID());
        NotifyLogInfo();
    }
}

bool CGuild::GetImpeachNotify(CGuildUserPtr pGuildUser) const
{
    if (!pGuildUser)
        return false;
    if (!_qwImpeachLauncherRoleID)
        return false;
    if (pGuildUser->GetRank() == eMemberOwner || pGuildUser->GetRoleID() == _qwImpeachLauncherRoleID)
        return false;
    if (_setImpeachRejecter.find(pGuildUser->GetRoleID()) != _setImpeachRejecter.end() || 
            _setImpeachAgreeer.find(pGuildUser->GetRoleID())!= _setImpeachAgreeer.end())
        return false;
    LOG_DBG << "GetImpeachNotify.";
    TVecUINT64 vecUserID;
    vecUserID.push_back(pGuildUser->GetID());
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildImpeachNotify(vecUserID.data(), vecUserID.size(), GetID(), _strImpeachLauncherName, _strOwnerName);
    return true;
}

void CGuild::Broadcast(const string& strData, const TVecUINT64& vecExcpRoleID) const
{
    TSetUINT64 setRoleID;
    for (auto& rID : vecExcpRoleID)
    {
        setRoleID.insert(rID);
    }

    for (auto& pGuildUser :_vecMemberPtr)
    {
        if (!pGuildUser)
            continue;
        CUserPtr pUser = pGuildUser->GetOnlineUser();
        if (pUser && setRoleID.find(pUser->GetRoleID()) == setRoleID.end())
            pUser->SendPkg(strData);
    }
}

void CGuild::SyncGuildLevel() const
{
    UINT16 wLevel = GetLevel();
    for (auto & pGuildUser : _vecMemberPtr)
    {
        if (pGuildUser)
            g_Game2CenterCommS.BuildPkg_GuildLevelUpdated(pGuildUser->GetRoleID(), wLevel);
    }
}

void CGuild::GetAllUserID(TVecUINT64& rvecUserID) const
{
    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        if (*it)
            rvecUserID.push_back((*it)->GetRoleID());
    }
}

bool CGuild::HaveAuthority(CGuildUserPtr pGuildUser, UINT16 wAuthorityBit) const
{
    if (!pGuildUser)
        return false;
    auto it = _mapAuthority.find(pGuildUser->GetRank());
    if (it == _mapAuthority.end())
        return false;
    return  ((it->second) & wAuthorityBit) ? true: false;
}

void CGuild::StatueReward()
{
    if (!_pStatueOwner)
        return;
    UINT8 byWorshipCount = _pStatueOwner->GetWorshipCount();
    if (!byWorshipCount)
        return;
    if (byWorshipCount > GetMaxMemberCount())
        byWorshipCount = GetMaxMemberCount();

    _pStatueOwner->ResetWorshipCount();
    UINT16 wCount1 = 10000 + byWorshipCount * 1000;
    UINT16 wCount2 = 100 + byWorshipCount * 10;

    CSystemMail sysMail;
    sysMail.SetSender("系统");

    SysMailSendTxt sTitle;
    sTitle.dwstrMsgID = 49;
    sysMail.SetSubject(sTitle);


    SItemAttachmentPtr pItem(new SItemAttachment());

    SMailItemInfo stAttach;
    stAttach.wItemID = 2;
    stAttach.wCount = wCount1;
    pItem->vecItemInfo.push_back(stAttach);

    stAttach.wItemID = 29;
    stAttach.wCount = wCount2;
    pItem->vecItemInfo.push_back(stAttach);
    sysMail.SetBody(SysMailSendTxt(50, BuildStrVec(byWorshipCount, wCount1, wCount2)));

    sysMail.AddItemInfo(pItem->vecItemInfo);

    bool bFound = false;

    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        CGuildUserPtr pGuildUser = *it;
        if (!pGuildUser)
            continue;
        sysMail.AddTarget(pGuildUser->GetRoleID());
        bFound = true;
    }
    if (bFound)
        sysMail.Send();
}

// 帮派战奖励发放
void CGuild::BattleReward()
{
    CSystemMail sysMail;
    UINT32 dwRank = CGuildMgr::Instance().GetBattleRank(GetID());
    const SGuildStepAwardCFGEx* pCFG = CGuildMgr::Instance().GetBattleAward(dwRank);
    if (!pCFG)
    {
        LOG_CRI << dwRank << " No BattleReward.";
        return;
    }
    sysMail.SetSender("系统");
    sysMail.SetSubject("帮派战");
    sysMail.SetBody(SysMailSendTxt(56, BuildStrVec(dwRank)));


    SItemAttachmentPtr pItem(new SItemAttachment());
    for (auto& rItems : pCFG->vecItemCount)
    {
        SMailItemInfo stAttach;
        stAttach.wItemID = rItems.wItemID;
        stAttach.wCount = rItems.wCount;
        pItem->vecItemInfo.push_back(stAttach);
    }

    sysMail.AddItemInfo(pItem->vecItemInfo);

    bool bFound = false;
    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        CGuildUserPtr pGuildUser = *it;
        if (!pGuildUser || pGuildUser->GetBattleScore() <= 0)
            continue;
        bFound = true;
        sysMail.AddTarget(pGuildUser->GetRoleID());

        CUserPtr pUser = pGuildUser->GetOnlineUser();
        TVecINT32 vecParam2;
        vecParam2.push_back(dwRank);
        ostringstream strInfo2;
        strInfo2 << GetID();

        if (pUser && pUser->IsOnLine())
        {
            pUser->OnEvent(eEventType_GuildBattleWeekendEnd,vecParam2, strInfo2.str());
        }
        else
        {
            UINT64 qwRoleID = pGuildUser->GetID();
            CUser::AddOffLineEvent(qwRoleID, eEventType_GuildBattleWeekendEnd,vecParam2, strInfo2.str());
        }
    }
    if (bFound)
        sysMail.Send();
}

void CGuild::NotifyBaseInfo(UINT64 qwExceptRoleID /* = 0 */) const
{
    TVecSGuildInfoBase vecGuildInfoBase;

    SGuildBaseInfoPtr pGuildBaseInfo (new SGuildBaseInfo);
    GetBaseInfo(*pGuildBaseInfo, NULL);
    vecGuildInfoBase.push_back(pGuildBaseInfo);

    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        if (*it && (*it)->GetID() != qwExceptRoleID)
        {
            CUserPtr pUser = (*it)->GetOnlineUser();
            if (!pUser)
                continue;
            pGuildBaseInfo->eSelfRank = (*it)->GetRank();
            pGuildBaseInfo->dwContribution = (*it)->GetContribution();
            pGuildBaseInfo->dwRemainDonate = (*it)->GetRemainDonate();
            string strData = g_GuildProtS.BuildPkg_GuildInfoNotify(eGDTBaseInfo, vecGuildInfoBase);
            pUser->SendPkg(strData);
        }
    }
}

void CGuild::NotifyBaseInfoSelf(CGuildUserPtr pGuildUser) const
{
    if (!pGuildUser)
        return;
    TVecSGuildInfoBase vecGuildInfoBase;

    SGuildBaseInfoPtr pGuildBaseInfo (new SGuildBaseInfo);
    GetBaseInfo(*pGuildBaseInfo, pGuildUser);
    vecGuildInfoBase.push_back(pGuildBaseInfo);

    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (pUser)
    {
        string strData = g_GuildProtS.BuildPkg_GuildInfoNotify(eGDTBaseInfo, vecGuildInfoBase);
        pUser->SendPkg(strData);
    }
}

void CGuild::NotifyApplyInfo() const
{
    TVecSGuildInfoBase vecGuildInfoBase;
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        SGuildApplyInfoPtr pGuildApplyInfo (new SGuildApplyInfo);
        (*it)->GetAllInfo(*pGuildApplyInfo);
        vecGuildInfoBase.push_back(pGuildApplyInfo);
    }
    TVecUINT64 vecUserID;

    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildInfoNotify(vecUserID.data(), vecUserID.size(), eGDTApplyInfo, vecGuildInfoBase);
}

void CGuild::NotifyAuthorityInfo() const
{
    TVecSGuildInfoBase vecGuildInfoBase;
    if (!GetAuthorityInfo(vecGuildInfoBase))
        return;

    TVecUINT64 vecUserID;

    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildInfoNotify(vecUserID.data(), vecUserID.size(), eGDTAuthority, vecGuildInfoBase);
}

void CGuild::NotifyUserInfo(UINT64 qwExceptRoleID /* = 0 */) const
{
    TVecSGuildInfoBase vecGuildInfoBase;
    GetMemberInfo(vecGuildInfoBase);
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    if (qwExceptRoleID)
        vecUserID.erase(std::find(vecUserID.begin(), vecUserID.end(), qwExceptRoleID));
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildInfoNotify(vecUserID.data(), vecUserID.size(), eGDTUser, vecGuildInfoBase);
}

void CGuild::NotifyImpeachInfo() const
{
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    vecUserID.erase(std::find(vecUserID.begin(), vecUserID.end(), _qwImpeachLauncherRoleID));
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildImpeachNotify(vecUserID.data(), vecUserID.size(), GetID(), _strImpeachLauncherName, _strOwnerName);
}

void CGuild::NotifyImpeachSucceed() const
{
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildImpeachSucceedNotify(vecUserID.data(), vecUserID.size());
}

void CGuild::NotifyImpeachFailed() const
{
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
    {
        TVecINT64 vecParam;
        TVecString vecString;
        ostringstream strTmp;
        strTmp << static_cast<UINT32>(_byImpeachLauncherQuality);
        vecString.push_back(strTmp.str());
        vecString.push_back(_strImpeachLauncherName);
        strTmp.str("");
        strTmp << static_cast<UINT32>(_byQuality);
        vecString.push_back(strTmp.str());
        vecString.push_back(_pOwner->GetName());
        for (auto it = vecUserID.begin(); it != vecUserID.end(); ++it)
        {
            CUserPtr pUser = CUserMgr::GetUserByUserID(*it);
            if (pUser)
            { 
                UINT32 dwSeverID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_BubbleNotify(&dwSeverID, 1, *it, eOpAdd, 5, vecParam, vecString);
                // {color:{0}:[{1}]}对帮主{color:{2}:[{3}]}的弹劾失败
            }
        }
        g_GuildProtS.SendClt_GuildImpeachFailedNotify(vecUserID.data(), vecUserID.size());

    }
}

void CGuild::NotifyImpeachCancel() const
{
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildImpeachCancelNotify(vecUserID.data(), vecUserID.size());
}

void CGuild::NotifyBuildingInfo() const
{
    if (!_pBuildingOwner)
        return;
    TVecSGuildInfoBase vecGuildInfoBase;
    GetBuildingInfo(vecGuildInfoBase);
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildInfoNotify(vecUserID.data(), vecUserID.size(), eGDTBuilding, vecGuildInfoBase);
}

void CGuild::NotifyStatueInfo() const
{
    if (!_pStatueOwner)
        return;
    SGuildStatueInfoPtr pStatueInfo (new SGuildStatueInfo);
    GetStatueInfo(*pStatueInfo);
    TVecSGuildInfoBase vecInfo;
    vecInfo.push_back(pStatueInfo);

    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        if (*it)
        {
            CUserPtr pUser = (*it)->GetOnlineUser();
            if (!pUser)
                continue;
            CCenterVar& rVar = pUser->GetCenterVar();
            pStatueInfo->byWorshipBit = rVar.GetVar(NVarDefine::ePlayerVarGuildWorship);
            string strData = g_GuildProtS.BuildPkg_GuildInfoNotify(eGDTStatue, vecInfo);
            pUser->SendPkg(strData);
        }
    }
    /*
       TVecUINT64 vecUserID;
       GetAllUserID(vecUserID);
       if (!vecUserID.empty())
       g_GuildProtS.SendClt_GuildInfoNotify(vecUserID.data(), vecUserID.size(), eGDTStatue, vecInfo);
       */
}

void CGuild::NotifyLogInfo() const
{
    TVecSGuildInfoBase vecInfo;
    if (!GetLogInfoWithoutType(eLogStatue, vecInfo))
        return;
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
        g_GuildProtS.SendClt_GuildInfoNotify(vecUserID.data(), vecUserID.size(), eGDTLog, vecInfo);
}

void CGuild::NotifyIDInfo(UINT16 wMsgID, const TVecString& vecString) const
{
    TVecUINT64 vecUserID;
    GetAllUserID(vecUserID);
    if (!vecUserID.empty())
    {
        if (vecString.empty())
            g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), wMsgID);
        else
            g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(vecUserID.data(), vecUserID.size(), wMsgID, vecString);
    }
}

void CGuild::SetDirty(EGuildDataType eType)
{
    _mapDirty[eType] = true;
}

bool CGuild::IsDirty(EGuildDataType eType) const
{
    auto it = _mapDirty.find(eType);
    if (it != _mapDirty.end())
        return it->second;
    return true;
}

void CGuild::ClearDirty()
{
    _mapDirty.clear();
}

void CGuild::SaveData()
{
    CGuild::Update2DB(ToThisPtr(this), eOpUpdate);
}

void CGuild::Update2DB(CGuildPtr pGuild, EDataChange eChangeType, UINT64 qwGuildID /* = 0 */)
{
    if (pGuild && !qwGuildID)
        qwGuildID = pGuild->GetID();

    if ((eChangeType != eOpUpdate) || (pGuild && pGuild->IsDirty(eGDTAuthority)))
    {
        TVecGuildAuthorityInfo vecAuthority;
        if (pGuild)
            pGuild->GetAuthorityInfo(vecAuthority);
        string strData2;
        COutArchive iar2(strData2);
        iar2 << vecAuthority;
        g_Center2DBGuildC.Send_GuildDataUpdate(qwGuildID, eGDTAuthority, eChangeType, strData2);
    }

    if ((eChangeType != eOpUpdate) || (pGuild && pGuild->IsDirty(eGDTBuilding)))
    {
        TVecGuildBuildingInfo vecBuilding;
        if (pGuild)
            pGuild->GetBuildingInfo(vecBuilding);
        string strData;
        COutArchive iar(strData);
        iar << vecBuilding;
        g_Center2DBGuildC.Send_GuildDataUpdate(qwGuildID, eGDTBuilding, eChangeType, strData);
    }

    if ((eChangeType != eOpUpdate) || (pGuild && pGuild->IsDirty(eGDTStatue)))
    {
        SGuildStatueInfo sStatueInfo;
        if (pGuild)
            pGuild->GetStatueInfo(sStatueInfo);
        string strData;
        COutArchive iar(strData);
        iar << sStatueInfo;
        g_Center2DBGuildC.Send_GuildDataUpdate(qwGuildID, eGDTStatue, eChangeType, strData);
    }

    if ((eChangeType != eOpUpdate) || (pGuild && pGuild->IsDirty(eGDTBaseInfo)))
    {
        SGuildBaseInfo sBaseInfo;
        if (pGuild)
            pGuild->GetBaseInfo(sBaseInfo, NULL);
        string strData;
        COutArchive iar(strData);
        iar << sBaseInfo;
        g_Center2DBGuildC.Send_GuildDataUpdate(qwGuildID, eGDTBaseInfo, eChangeType, strData);
    }
    if (pGuild)
        pGuild->ClearDirty();
}

void CGuild::UpdateRankInfo(UINT32 dwBattleScore) const
{
    TVecRankInfo vecRankInfo;
    SGRBattleInfoPtr pInfo (new SGRBattleInfo);
    pInfo->dwValue = dwBattleScore;
    pInfo->qwGuildID = GetID();
    pInfo->strGuildName = GetName();
    pInfo->strName = GetOwnerName();
    pInfo->qwRoleID = GetOwnerID();
    pInfo->wLevel = GetLevel();
    pInfo->dwBattleScore = dwBattleScore;
    pInfo->byQuality = GetQuality();
    pInfo->wPlayerFighterID = GetPlayerFighterID();
    vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    CRankMgr::Instance().UpdateRankInfo(GetID(), eRTGuildBattle, vecRankInfo);
    
    //LogServer日志
    SLogOp sLog;
    sLog.eType = eOpType_Score;
    sLog.qwGuildID = GetID();
    sLog.byParam = 0;
    CGuildMgr::Instance().WriteGuildLog(sLog);
}

void CGuild::PreGuildUserEnter(CGuildUserPtr pGuildUser)
{
    CGuildUser::Update2DB(pGuildUser, eOpDel);
    pGuildUser->SetGuild(ToThisPtr(this));
    pGuildUser->SetRank(eMemberNormal);
    CGuildUser::Update2DB(pGuildUser, eOpAdd);
}

void CGuild::OnGuildUserEnter(CGuildUserPtr pGuildUser)
{
    SGuildAllInfo sAllInfo;
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    UINT8 byQuality = 3;
    if (pUser)
    {
        byQuality = pUser->GetQuality();
        if (GetAllInfo(sAllInfo, pGuildUser))
        {
            string strData = g_GuildProtS.BuildPkg_GuildApplyPassedNotify(sAllInfo);
            pUser->SendPkg(strData);
        }
    }
    NotifyBaseInfo(pGuildUser->GetRoleID());
    NotifyUserInfo(pGuildUser->GetRoleID());
    CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(GetID());
    CGuildMemberLogPtr pLog (new CGuildMemberLog);
    if (pLog->FormatParam(eMsgGuildJoin, byQuality, pGuildUser->GetName()))
        AddLog(pLog);
    if (pGuildListInfo)
    {
        pGuildListInfo->SetMemberCount(GetMemberCount());
        CGuildListInfo::Update2DB(pGuildListInfo, eOpUpdate);
    }
    TVecINT32 vecParam2;
    vecParam2.push_back(GetLevel());
    ostringstream strInfo2;
    strInfo2 << GetID();

    if (pUser && (pUser->IsOnline()))
    {
        pUser->OnEvent(eEventType_GuildJoining,vecParam2, strInfo2.str());
        pUser->OnEvent(eEventType_GuildLevel,vecParam2, strInfo2.str());
    }
    else
    {
        TVecUINT64 vecRoleID;
        vecRoleID.push_back(pGuildUser->GetID());
        CUser::AddOffLineEvent(pGuildUser->GetID(), eEventType_GuildJoining,vecParam2, strInfo2.str());
        CUser::AddOffLineEvent(pGuildUser->GetID(), eEventType_GuildLevel,vecParam2, strInfo2.str());
    }

}

void CGuild::OnGuildUserQuit(CGuildUserPtr pGuildUser, CGuildUserPtr pKicker /* = NULL */)
{
    bool bOwner = pGuildUser->GetRank() == eMemberOwner;
    CGuildUser::Update2DB(pGuildUser, eOpDel);
    pGuildUser->SetGuild(NULL);
    pGuildUser->SetRank(eMemberNone);
    //pGuildUser->SetContribution(0);
    CGuildUser::Update2DB(pGuildUser, eOpAdd);

    if (bOwner)     // 帮主退出，即为解散帮派, 不做其他后续处理
        return;

    UINT8 byQuality = 3;
    UINT8 byQuality2 = 3;

    CUserPtr pUser = pGuildUser->GetOnlineUser();
    TVecINT32 vecParam2;
    ostringstream strInfo2;
    strInfo2 << GetID();

    if (pUser)
        byQuality2 = pUser->GetQuality();

    if (pUser && (pUser->IsOnline()))
    {
        pUser->OnEvent(eEventType_GuildQuit,vecParam2, strInfo2.str());
    }
    else
    {
        CUser::AddOffLineEvent(pGuildUser->GetID(), eEventType_GuildQuit,vecParam2, strInfo2.str());
    }

    if (_qwImpeachLauncherRoleID == pGuildUser->GetRoleID())
        CancelImpeach();
    NotifyBaseInfo();
    NotifyUserInfo();
    CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(GetID());
    if (pGuildListInfo)
    {
        pGuildListInfo->SetMemberCount(GetMemberCount());
        CGuildListInfo::Update2DB(pGuildListInfo, eOpUpdate);
    }

    CGuildMemberLogPtr pLog (new CGuildMemberLog);
    bool bRet = false;
    if (pKicker)
    {
        CUserPtr pKickUser = pKicker->GetOnlineUser();
        if (pKickUser)
            byQuality = pKickUser->GetQuality();

        bRet = pLog->FormatParam(eMsgGuildKick, byQuality, pKicker->GetName(), byQuality2, pGuildUser->GetName());
        CUserPtr pUser = pGuildUser->GetOnlineUser();
        if (pUser)
        {
            string strData = g_GuildProtS.BuildPkg_GuildKickNotify(GetID(), GetName(), pKicker->GetName());
            pUser->SendPkg(strData);
        }
    }
    else
        bRet = pLog->FormatParam(eMsgGuildQuit, byQuality2, pGuildUser->GetName());
    if (bRet)
        AddLog(pLog);
}

void CGuild::OnGuildUserRankChanged(CGuildUserPtr pGuildUser, CGuildUserPtr pChanger, EMemberRank eOldRank, EMemberRank eNewRank)
{
    CGuildMemberLogPtr pLog (new CGuildMemberLog);
    bool bRet = false;
    UINT16 wMsgID = 0;
    UINT8 byQuality = 3;
    UINT8 byQuality2 = 3;

    CUserPtr pUser = pChanger->GetOnlineUser();
    CUserPtr pUser2 = pGuildUser->GetOnlineUser();

    if (pUser)
        byQuality = pUser->GetQuality();
    if (pUser2)
        byQuality2 = pUser2->GetQuality();

    if (eNewRank == eMemberOwner)
    {
        wMsgID = eMsgGuildGiveOwner;
        bRet = pLog->FormatParam(wMsgID, byQuality, pChanger->GetName(), byQuality2, pGuildUser->GetName());
    }
    else 
    {
        if (eOldRank <= eNewRank)
            wMsgID = eMsgGuildImprove;
        else
            wMsgID = eMsgGuildDemote;
        bRet = pLog->FormatParam(wMsgID, byQuality, pChanger->GetName(), byQuality2, pGuildUser->GetName(), eNewRank);
    }
    if (bRet)
        AddLog(pLog);
    CGuildUser::Update2DB(pGuildUser, eOpUpdate);


    TVecSGuildInfoBase vecGuildInfoBase;

    NotifyBaseInfoSelf(pGuildUser);
}

void CGuild::CheckImpeach()
{
    // 弹劾通过
    if (_setImpeachAgreeer.size() * 2 >= _vecMemberPtr.size())
    {
        for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
        {
            if ((*it) && (*it)->GetRoleID() == _qwImpeachLauncherRoleID)
            {
                if (_pOwner)
                {
                    _pOwner->SetRank(eMemberNormal);
                    CGuildUser::Update2DB(_pOwner, eOpUpdate);
                }
                CGuildMemberLogPtr pLog(new CGuildMemberLog);
                if (pLog->FormatParam(eMsgGuildImpeachSuccess, _byImpeachLauncherQuality, _strImpeachLauncherName, _byQuality, _strOwnerName))
                    AddLog(pLog);
                _pOwner = *it;
                _wPlayerFighterID = (*it)->GetPlayerFighterID();
                _byQuality = (*it)->GetQuality();
                _pOwner->SetRank(eMemberOwner);
                _qwOwnerID = _pOwner->GetID();
                _strOwnerName = _pOwner->GetName();
                CGuildUser::Update2DB(_pOwner, eOpUpdate);
                CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(GetID());
                if (pGuildListInfo)
                {
                    pGuildListInfo->SetOwnerID(_pOwner->GetID());
                    pGuildListInfo->SetOwnerName(_strOwnerName);
                    CGuildListInfo::Update2DB(pGuildListInfo, eOpUpdate);
                }

                CUserPtr pUser = _pOwner->GetOnlineUser();
                TVecINT32 vecParam2;
                ostringstream strInfo2;
                strInfo2 << GetID();

                if (pUser && (pUser->IsOnline()))
                {
                    pUser->OnEvent(eEventType_GuildAccuse,vecParam2, strInfo2.str());
                }
                else
                {
                    TVecUINT64 vecRoleID;
                    vecRoleID.push_back(_pOwner->GetID());
                    CUser::AddOffLineEvent(_pOwner->GetID(), eEventType_GuildAccuse,vecParam2, strInfo2.str());
                }
                break;
            }
        }
        SetDirty(eGDTBaseInfo);
        SaveData();
        CancelImpeach();
        NotifyImpeachSucceed();
        NotifyUserInfo();
        NotifyBaseInfo();

        UINT32 dwID = CCenterConfig::Instance().GetSvrID();
        g_Game2CenterGuildBattleS.SendSvr_GuildOwnerChanged(&dwID, 1, GetID(), GetOwnerName());
        return;
    }

    // 弹劾未通过
    if (_setImpeachRejecter.size() * 2 >= _vecMemberPtr.size())
    {
        CGuildMemberLogPtr pLog(new CGuildMemberLog);
        if (pLog->FormatParam(eMsgGuildImpeachFailed, _byImpeachLauncherQuality, _strImpeachLauncherName, _byQuality, _strOwnerName))
            AddLog(pLog);
        NotifyImpeachFailed();
        CancelImpeach();
        return;
    }
}

UINT16 CGuild::GetMemberRankCount(EMemberRank eRank) const
{
    UINT16 wCount = 0;
    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        if (*it && (*it)->GetRank() == eRank)
            ++ wCount;
    }
    return wCount;
}


/*******************************帮派兑换物品Begin**************************************/

//获取帮派兑换物品信息
void CGuild::GetGuildExchangedItemInfo(
        CGuildUserPtr pGuildUser,
        TVecUINT8& vecLingShanType,
        TVecGuildExchangedItem& vecGuildExchangedItem, 
        UINT32& dwGUildAllMemberExchangedItemNum, 
        UINT32& dwPlayerExchangedItemNum,
        EMemberRank& eMemberLastRank)
{
     vecLingShanType = _vecLingShanType;
     map<UINT32, UINT32>::iterator iter = _mapGuildExchangedItem.begin();
     for ( ; iter!=_mapGuildExchangedItem.end(); iter++)
     {
         SGuildExchangedItem sGuildExchangedItem;
         sGuildExchangedItem.qwGuildID = GetID();
         sGuildExchangedItem.dwExchangeID = iter->first;
         sGuildExchangedItem.dwCount = iter->second;
         vecGuildExchangedItem.push_back(sGuildExchangedItem);
     }

     dwGUildAllMemberExchangedItemNum = GetCount();

     CUserPtr pUser = pGuildUser->GetOnlineUser();
     if (pUser)
     {
        CCenterVar& rVar = pUser->GetCenterVar();
        dwPlayerExchangedItemNum = rVar.GetVar(NVarDefine::ePlayerVarGuildExchangedItemToday);
     }
     if (eMemberNone == pGuildUser->GetLastRank())
        eMemberLastRank = pGuildUser->GetRank();
     else
        eMemberLastRank = pGuildUser->GetLastRank();
}

//请求帮派兑换物品
void CGuild::ReqGuildExchangeItem(CGuildUserPtr pGuildUser, UINT32 dwExchangeID, UINT32 dwCount, shared_func<CGuildProtSvr::SReqGuildExchangeItemAck>& fnAck)
{
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (NULL == pUser)
    {
        fnAck(false);
        return;
    }

    //检测
    EGuildExchangeRet eRet = GuildExchangedItemCheck(pGuildUser, dwExchangeID, dwCount);
    if (eGuildExchange_Sucess != eRet)
    {
        fnAck->eResult = eRet;
        fnAck(true);
        return;
    }

    const SLingMountainShopCFG* pLingMountainShopCFG = CGuildMgr::Instance().GetGuildExchangedItemConfig(dwExchangeID);
    if(NULL == pLingMountainShopCFG)
    {
        fnAck->eResult = eGuildExchange_Failed;
        fnAck(true);
        return;
    }

    TVecUserItem vecItem;
    SUserItem sItem;
    sItem.dwTypeID = pLingMountainShopCFG->_ItemId;
    sItem.dwCount = dwCount;
    vecItem.push_back(sItem);
    
    if(!pUser->GetOpLock().AddLock(eLock_GuildExchangedItem))
    {
        fnAck(false);
        return;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    UINT64 qwUserID = pUser->GetUserID();
    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID, 1, qwUserID, NLogDataDefine::ItemFrom_GuildExchangedItem, vecItem, [this, pGuildUser, dwExchangeID, dwCount, fnAck](UINT8 byRet_, UINT8 byError)
    {
        if(NULL == pGuildUser)
        {
           fnAck(false);
           return;
        }
        else
        {
           CUserPtr pUser = pGuildUser->GetOnlineUser();
           if (NULL == pUser)
           {
               fnAck(false);
               return;
           }

           pUser->GetOpLock().UnLock(eLock_GuildExchangedItem);
        }

        if(byRet_ || byError)
        {   
            fnAck->eResult = eGuildExchange_ErrorPack;
            fnAck(true);
            return;
        }
        
        EGuildExchangeRet eRet = this->GuildExchangedItemAccount(pGuildUser, dwExchangeID, dwCount);
        if (eGuildExchange_Sucess != eRet)
        {
            fnAck->eResult = eRet;
            fnAck(true);
            return;
        }
        else
        {
            
            fnAck->eResult = eGuildExchange_Sucess;
            fnAck(true);
            return;
        }
    });
}

//帮派兑换物品结算
EGuildExchangeRet CGuild::GuildExchangedItemAccount(CGuildUserPtr pGuildUser, UINT32 dwExchangeID, UINT32 dwCount)
{
    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (NULL == pUser)
        return eGuildExchange_Failed;

    //检测
    EGuildExchangeRet eRet = GuildExchangedItemCheck(pGuildUser, dwExchangeID, dwCount);
    if (eGuildExchange_Sucess != eRet)
        return eRet;

    //结算
    const SLingMountainShopCFG* pLingMountainShopCFG = CGuildMgr::Instance().GetGuildExchangedItemConfig(dwExchangeID);
    if(NULL == pLingMountainShopCFG)
        return eGuildExchange_Failed;
    
    //UINT32 dwMoneyType = pLingMountainShopCFG->_MoneyType;
    UINT32 dwMoneyCount = pLingMountainShopCFG->_MoneyPrice;

    pGuildUser->SubContribution(dwMoneyCount*dwCount);
    SetGuildExchangedItem(dwExchangeID, dwCount);
    AddCount(dwCount);
    CCenterVar& rVar = pUser->GetCenterVar();
    UINT32 dwPlayerExchangedItemNum = rVar.GetVar(NVarDefine::ePlayerVarGuildExchangedItemToday);
    rVar.SetVar(NVarDefine::ePlayerVarGuildExchangedItemToday, (dwPlayerExchangedItemNum + dwCount));

    //玩家购买日志
    SGuildLogInfo sGuildLogInfo;
    FormatGuildExchangedItemLog(pLingMountainShopCFG->_Type, pUser->GetQuality(), pGuildUser->GetName(), dwExchangeID, dwCount, sGuildLogInfo);
    AddGuildExchangedItemLog(sGuildLogInfo);
    UpdateGuildExchangedItemLogDB(sGuildLogInfo, eOpAdd);

    //更新通知
    GuildExchangedItemNotify(dwExchangeID);
    GuildExchangedItemLogNotify(sGuildLogInfo);

    return eGuildExchange_Sucess;
}

//帮派兑换物品检测
EGuildExchangeRet CGuild::GuildExchangedItemCheck(CGuildUserPtr pGuildUser, UINT32 dwExchangeID, UINT32 dwCount)
{
    if (NULL == pGuildUser)
        return eGuildExchange_Failed;

    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (NULL == pUser)
        return eGuildExchange_Failed;

    if (0 == dwExchangeID || 0 == dwCount)
        return eGuildExchange_Failed;

    CGuildMgr::EOpDisableType eOpDisableType = CGuildMgr::Instance().GetOpDisableType();
    if (CGuildMgr::eOPDNewGuildBattle == eOpDisableType)
    {
        TVecUINT64 vecUserID;
        vecUserID.push_back(pUser->GetUserID());
        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgLingMountainShopNotBuy);
        return eGuildExchange_Failed;
    }

    const SLingMountainShopCFG* pLingMountainShopCFG = CGuildMgr::Instance().GetGuildExchangedItemConfig(dwExchangeID);
    if(NULL == pLingMountainShopCFG)
        return eGuildExchange_Failed;
    
    if (!CheckLingshanType(pLingMountainShopCFG->_Type))
        return eGuildExchange_NoLingShan;

    UINT32 dwMoneyType = pLingMountainShopCFG->_MoneyType;
    UINT32 dwMoneyCount = pLingMountainShopCFG->_MoneyPrice;
    if (EMONEY_GUILDCONTRIB != dwMoneyType || 0 == dwMoneyCount)
        return eGuildExchange_Failed;

    if (pGuildUser->GetContribution() < dwMoneyCount*dwCount)
        return eGuildExchange_MoneyLimit;
        
    //商品剩余数量为0
    if (pLingMountainShopCFG->_StoreNum > 0)
        if (GetGuildExchangedItemCount(dwExchangeID) + dwCount > pLingMountainShopCFG->_StoreNum)
            return eGuildExchange_CondLimitA;

    //帮派成员每天购买次数达到上限
    UINT32 dwTempNum = 0;
    if (pGuildUser->GetLastRank() == eMemberNone)
    {
        if (pGuildUser->GetRank() == eMemberOwner)
            dwTempNum = SParamConfig::wLingMountainLimit1;
        else if (pGuildUser->GetRank() == eMemberViceOwner)
            dwTempNum = SParamConfig::wLingMountainLimit2;
        else if (pGuildUser->GetRank() == eMemberElder)
            dwTempNum = SParamConfig::wLingMountainLimit3;
        else
            dwTempNum = SParamConfig::wLingMountainLimit4;
    }
    else
    {
        if (pGuildUser->GetLastRank() == eMemberOwner)
            dwTempNum = SParamConfig::wLingMountainLimit1;
        else if (pGuildUser->GetLastRank() == eMemberViceOwner)
            dwTempNum = SParamConfig::wLingMountainLimit2;
        else if (pGuildUser->GetLastRank() == eMemberElder)
            dwTempNum = SParamConfig::wLingMountainLimit3;
        else
            dwTempNum = SParamConfig::wLingMountainLimit4;
    }

    CCenterVar& rVar = pUser->GetCenterVar();
    UINT32 dwPlayerExchangedItemNum = rVar.GetVar(NVarDefine::ePlayerVarGuildExchangedItemToday);
    if ((dwPlayerExchangedItemNum + dwCount) > dwTempNum)
        return eGuildExchange_CondLimitB;

    //帮派所有成员每天购买次数达到上限
    const SGuildLevelCFG* pGuildLevelCFG = CGuildMgr::Instance().GetLevelConfig(GetLevel());
    if (NULL == pGuildLevelCFG)
        return eGuildExchange_Failed;
    if ((GetCount() + dwCount) > pGuildLevelCFG->_LingBuyLimit)
        return eGuildExchange_CondLimitC;
    
    return eGuildExchange_Sucess;
}

bool CGuild::CheckLingshanType(UINT8 byLingShanType)
{
    for (size_t i=0; i<_vecLingShanType.size(); i++)
    {
        if (byLingShanType == _vecLingShanType[i])
            return true;
    }

    return false;
}

//设置帮派兑换物品
void CGuild::SetGuildExchangedItem(UINT32 dwExchangeID, UINT32 dwCount)
{
    if (0 == dwCount)
        return;
    EDataChange eChangeType = eOpAdd;
    map<UINT32, UINT32>::iterator iter = _mapGuildExchangedItem.find(dwExchangeID);
    if (iter == _mapGuildExchangedItem.end())
        _mapGuildExchangedItem.insert(std::make_pair(dwExchangeID, dwCount));
    else
    {
        iter->second += dwCount;
        eChangeType= eOpUpdate;
    }

    GuildExchangedItemDB(dwExchangeID, eChangeType);
}

//获取帮派兑换物品
UINT32 CGuild::GetGuildExchangedItemCount(UINT32 dwExchangeID)
{
    map<UINT32, UINT32>::iterator iter = _mapGuildExchangedItem.find(dwExchangeID);
    if (iter == _mapGuildExchangedItem.end())
        return 0;
    else
        return iter->second;
}

//帮派兑换物品通知
void CGuild::GuildExchangedItemNotify(UINT32 dwExchangeID)
{
    TVecGuildExchangedItem vecGuildExchangedItem;
    SGuildExchangedItem sGuildExchangedItem;
    sGuildExchangedItem.qwGuildID = GetID();
    sGuildExchangedItem.dwExchangeID = dwExchangeID;
    sGuildExchangedItem.dwCount = GetGuildExchangedItemCount(dwExchangeID);
    vecGuildExchangedItem.push_back(sGuildExchangedItem);

    UINT32 dwGUildAllMemberExchangedItemNum = GetCount();

    for (auto it=_vecMemberPtr.begin(); it!=_vecMemberPtr.end(); ++it)
    {
        CUserPtr pUser = (*it)->GetOnlineUser();
        if (!pUser)
            continue;

        CCenterVar& rVar = pUser->GetCenterVar();
        UINT32 dwPlayerExchangedItemNum = rVar.GetVar(NVarDefine::ePlayerVarGuildExchangedItemToday);
        
        string strData = g_GuildProtS.BuildPkg_GuildExchangedItemNotify(vecGuildExchangedItem, dwGUildAllMemberExchangedItemNum, dwPlayerExchangedItemNum);
        pUser->SendPkg(strData);
    }
}

//帮派兑换物品DB
void CGuild::GuildExchangedItemDB(UINT32 dwExchangeID, EDataChange eChangeType)
{
    SGuildExchangedItem sGuildExchangedItem;
    sGuildExchangedItem.qwGuildID = GetID();
    sGuildExchangedItem.dwExchangeID = dwExchangeID;
    sGuildExchangedItem.dwCount = GetGuildExchangedItemCount(dwExchangeID);

    g_Center2DBGuildC.Send_UpdateGuildExchangedItem(sGuildExchangedItem, eChangeType);
}

//帮派兑换物品开始
void CGuild::GuildExchangedItemBegin(TVecUINT8 vecLingShanType)
{
    _vecLingShanType = vecLingShanType;
    SetLingShan();

    for (auto it = _vecMemberPtr.begin(); it != _vecMemberPtr.end(); ++it)
    {
        CUserPtr pUser = (*it)->GetOnlineUser();
        if (!pUser)
            continue;
        
        string strData = g_GuildProtS.BuildPkg_GuildExchangedItemBeginNotify(_vecLingShanType);
        pUser->SendPkg(strData);
    }
}

//帮派兑换物品零点数据清除
void CGuild::GuildExchangedItemZeroClean()
{
    SetCount(0);

    _mapGuildExchangedItem.clear();
    
    GuildExchangedItemDB(0, eOpDel);

    for (auto it=_vecMemberPtr.begin(); it!=_vecMemberPtr.end(); ++it)
    {
        if (*it && ((*it)->GetLastRank()>eMemberNone))
            (*it)->SetLastRank(eMemberNone);
    }
}

//帮派兑换物品数据清除
void CGuild::GuildExchangedItemClean()
{
    _vecLingShanType.clear();
    SetLingShan();

    _mapGuildExchangedItem.clear();
    
    GuildExchangedItemDB(0, eOpDel);
}

//初始化帮派兑换物品日志
bool CGuild::InitGuildExchangedItemLog(const TVecGuildLogInfo& rInfo)
{
    for (auto iter=rInfo.begin(); iter!=rInfo.end(); ++iter)
    {
        _dequeExchangedItemLog.push_back(*iter);
    }

    return true;
}

//获取帮派兑换物品日志
bool CGuild::GetGuildExchangedItemLog(TVecGuildLogInfo& rInfo)
{
    UINT8 byCount = 0;
    for (auto iter=_dequeExchangedItemLog.begin(); iter!=_dequeExchangedItemLog.end(); ++iter)
    {
        rInfo.push_back(*iter);
        byCount++;

        if (byCount >= 20)
            break;
    }

    return true;
}

//添加帮派兑换物品日志
bool CGuild::AddGuildExchangedItemLog(SGuildLogInfo& sGuildLogInfo)
{
    SGuildLogInfoPtr pGuildLogInfoPtr(new SGuildLogInfo);
    *pGuildLogInfoPtr = sGuildLogInfo;
    _dequeExchangedItemLog.push_front(pGuildLogInfoPtr);

    return true;
}

//组装帮派兑换物品日志
void CGuild::FormatGuildExchangedItemLog(UINT8 byType, UINT8 byQuality, string strName, UINT32 dwItemID, UINT32 dwItemCount, SGuildLogInfo& sGuildLogInfo)
{
    TVecString vecString;
    ostringstream strTmpA;
    ostringstream strTmpB;
    ostringstream strTmpC;
    ostringstream strTmpD;
    strTmpA << static_cast<UINT32>(byType);
    strTmpB << static_cast<UINT32>(byQuality);
    strTmpC << dwItemID;
    strTmpD << dwItemCount;
    vecString.push_back(strTmpA.str());
    vecString.push_back(strName);
    vecString.push_back(strTmpB.str());
    vecString.push_back(strTmpC.str());
    vecString.push_back(strTmpD.str());

    sGuildLogInfo.qwGuildID = GetID();
    sGuildLogInfo.wMsgID = eMsgLingMountainShopList;
    sGuildLogInfo.vecString = vecString;
    sGuildLogInfo.dwTime = time(NULL);
}

//帮派兑换物品日志通知
void CGuild::GuildExchangedItemLogNotify(const SGuildLogInfo& sGuildLogInfo)
{
    for (auto it=_vecMemberPtr.begin(); it!=_vecMemberPtr.end(); ++it)
    {
        CUserPtr pUser = (*it)->GetOnlineUser();
        if (!pUser)
            continue;

        string strData = g_GuildProtS.BuildPkg_GuildExchangeItemLogNotify(sGuildLogInfo);
        pUser->SendPkg(strData);
    }
}

//帮派兑换物品日志DB
void CGuild::UpdateGuildExchangedItemLogDB(const SGuildLogInfo& sGuildLogInfo, EDataChange eChangeType)
{
    string strData;
    COutArchive iar(strData);
    iar << sGuildLogInfo;
    g_Center2DBGuildC.Send_GuildDataUpdate(GetID(), eGDTLSSBLog, eChangeType, strData);
}

/*******************************帮派兑换物品End**************************************/

CGuildListInfo::CGuildListInfo():
    _qwID(0), _byLevel(0), 
    _qwOwnerID(0),
    _wMemberCount(0), _wMaxMemberCount(0)
{
}

CGuildListInfo::CGuildListInfo(CGuildPtr pGuild)
{
    if (pGuild)
    {
        _qwID               = pGuild->GetID();
        _strName            = pGuild->GetName();
        _strInfo            = pGuild->GetInfo();
        _byLevel            = pGuild->GetLevel();

        _qwOwnerID          = pGuild->GetOwnerID();
        _strOwnerName       = pGuild->GetOwnerName();
        _wMemberCount       = pGuild->GetMemberCount();
        _wMaxMemberCount    = pGuild->GetMaxMemberCount();
    }
}

CGuildListInfo::CGuildListInfo(const SGuildListInfo& sGuildListInfo)
{
    _qwID               = sGuildListInfo.qwGuildID;
    _strName            = sGuildListInfo.strName;
    _strInfo            = sGuildListInfo.strInfo;
    _byLevel            = sGuildListInfo.byLevel;

    _qwOwnerID          = sGuildListInfo.qwOwnerID;
    _strOwnerName       = sGuildListInfo.strOwnerName;
    _wMemberCount       = sGuildListInfo.wUserCount;
    _wMaxMemberCount    = sGuildListInfo.wMaxUserCount;
}

CGuildListInfo::~CGuildListInfo()
{
}

UINT64 CGuildListInfo::GetID() const
{
    return _qwID;
}

const string& CGuildListInfo::GetName() const
{
    return _strName;
}

const string& CGuildListInfo::GetOwnerName() const
{
    return _strOwnerName;
}

UINT8 CGuildListInfo::GetLevel() const
{
    return _byLevel;
}

UINT64 CGuildListInfo::GetOwnerID() const
{
    return _qwOwnerID;
}

UINT16 CGuildListInfo::GetMemberCount() const
{
    return _wMemberCount;
}

UINT16 CGuildListInfo::GetMaxMemberCount() const
{
    return _wMaxMemberCount;
}

const string& CGuildListInfo::GetInfo() const
{
    return _strInfo;
}

void CGuildListInfo::SetOwnerID(UINT64 qwRoleID)
{
    _qwOwnerID = qwRoleID;
    SaveData();
}

void CGuildListInfo::SetOwnerName(const string& strName)
{
    _strOwnerName = strName;
    SaveData();
}

void CGuildListInfo::SetLevel(UINT8 byLevel)
{
    _byLevel = byLevel;
    CGuildMgr::Instance().UpdateOrderListMemberCount(GetID(), GetLevel(), GetMemberCount());
    SaveData();
}

void CGuildListInfo::SetInfo(const string& strInfo)
{
    _strInfo = strInfo;
    SaveData();
}

void CGuildListInfo::SetMemberCount(UINT16 wCount)
{
    if (wCount != _wMemberCount)
    {
        _wMemberCount = wCount;
        SaveData();
    }
    CGuildMgr::Instance().UpdateOrderListMemberCount(GetID(), GetLevel(), GetMemberCount());
}

void CGuildListInfo::SetMaxMemberCount(UINT16 wCount)
{
    if (wCount != _wMaxMemberCount)
    {
        _wMaxMemberCount = wCount;
        SaveData();
    }
}

bool CGuildListInfo::GetAllInfo(SGuildListInfo& rAllInfo) const
{
    rAllInfo.qwGuildID      = GetID();
    rAllInfo.strName        = GetName();
    rAllInfo.qwOwnerID      = GetOwnerID();
    rAllInfo.strOwnerName   = GetOwnerName();
    rAllInfo.byLevel        = GetLevel();
    rAllInfo.wUserCount     = GetMemberCount();
    rAllInfo.wMaxUserCount  = GetMaxMemberCount();
    rAllInfo.strInfo        = GetInfo();
    return true;
}

void CGuildListInfo::SaveData()
{
    CGuildListInfo::Update2DB(ToThisPtr(this), eOpUpdate);
}

void CGuildListInfo::Update2DB(CGuildListInfoPtr pGuildListInfo, EDataChange eChangeType, UINT64 qwGuildID /* = 0 */)
{
    if (pGuildListInfo && !qwGuildID)
        qwGuildID = pGuildListInfo->GetID();

    string strData;
    if (pGuildListInfo)
    {
        SGuildListInfo sGuildListInfo;
        pGuildListInfo->GetAllInfo(sGuildListInfo);
        COutArchive iar(strData);
        iar << sGuildListInfo;
    }

    g_Center2DBGuildC.Send_GuildPubDataUpdate(qwGuildID, eGPDTListInfo, eChangeType, strData);
}

