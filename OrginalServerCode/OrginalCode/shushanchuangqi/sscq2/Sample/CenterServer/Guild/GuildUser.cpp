#include "GuildUser.h"
#include "User.h"
#include "Guild.h"
#include "Protocols.h"
#include "Center2DBGuildC.h"
#include "GuildApplyInfo.h"
#include "GuildTech.h"
#include "SysMsgDefine.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "RankMgr.h"
#include "UserMgr.h"
#include "Parameter.h"

#include "RTime.h"
using namespace NProtoCommon;
string GetNameByRank(EMemberRank eRank)
{
    string strRet = ""; 
    switch(eRank)
    {
        case eMemberNormal:
            strRet = "成员";
            break;
        case eMemberElite:
            strRet = "精英";
            break;
        case eMemberElder:
            strRet = "长老";
            break;
        case eMemberViceOwner:
            strRet = "副帮主";
            break;
        case eMemberOwner:
            strRet = "帮主";
            break;
        default:
            break;
    }
    return strRet;
}
////////////////////////////////
CGuildUser::CGuildUser(CUserPtr pUser): 
    _pUser(pUser), _qwRoleID(0), 
    _wLevel(0), _dwJoinTime(0), _dwLastOnlineTime(0),
    _eRank(eMemberNone), _eLastRank(eMemberNone), _dwAuthority(0),
    _dwBattlePoint(0), _dwBattleScore(0), _dwContribution(0), 
    _byVIPLevel(0), _wPlayerFighterID(0), _byQuality(0),
    _dwLastWorshipTime(0)
{
    if (pUser)
    {
        _qwRoleID         = pUser->GetUserID();
        _strName          = pUser->GetUserName();
        _wLevel           = pUser->GetLevel();
        _dwBattlePoint    = pUser->GetBattlePoint();
        _byVIPLevel       = pUser->GetVIPLevel();
        _wPlayerFighterID = pUser->GetPlayerFighterID();
        _byQuality        = pUser->GetQuality();
    }

}

CGuildUser::CGuildUser(const SDBGuildUserInfo& rUserInfo):
    _qwRoleID(rUserInfo.sBaseInfo.qwRoleID), _strName(rUserInfo.sBaseInfo.strName),
    _wLevel(rUserInfo.sBaseInfo.wLevel), _dwJoinTime(rUserInfo.sBaseInfo.dwJoinTime), _dwLastOnlineTime(rUserInfo.sBaseInfo.dwLastOnlineTime),
    _eRank(rUserInfo.sBaseInfo.eMemberRank),_eLastRank(rUserInfo.sBaseInfo.eMemberLastRank), _dwAuthority(rUserInfo.sBaseInfo.dwAuthority),
    _dwBattlePoint(0), _dwBattleScore(rUserInfo.dwBattleScore), _dwContribution(rUserInfo.sBaseInfo.dwContribution),
    _byVIPLevel(rUserInfo.sBaseInfo.byVIPLevel), _wPlayerFighterID(rUserInfo.wPlayerFighterID), _byQuality(rUserInfo.byQuality),
    _dwLastWorshipTime(0)
{
}

CGuildUser::CGuildUser(): 
    _qwRoleID(0), 
    _wLevel(0), _dwJoinTime(0), _dwLastOnlineTime(0),
    _eRank(eMemberNone), _eLastRank(eMemberNone), _dwAuthority(0),
    _dwBattlePoint(0), _dwBattleScore(0), _dwContribution(0),
    _byVIPLevel(0), _wPlayerFighterID(0), _byQuality(0),
    _dwLastWorshipTime(0)
{
}

CGuildUser::~CGuildUser()
{
}

// 初次创建的初始化
bool CGuildUser::InitFromUser(CUserPtr pUser)
{
    if (GetOnlineUser())
    {
        LOG_WRN << "InitFromUser twice.";
        return false;
    }
    _pUser = pUser;
    CUserPtr pUserSelf = GetOnlineUser();
    if (!pUserSelf)
    {
        LOG_WRN << "InitFromUser NULL.";
        return false;
    }
    _qwRoleID   = pUserSelf->GetUserID();
    _strName    = pUserSelf->GetFixdCUserName();
    _dwJoinTime = Time::Now();
    return true;
}

void    CGuildUser::InitTechInfo()
{
    if (!_pTechOwner)
    {
        CGuildTechOwnerPtr pTechOwner(new CGuildTechOwner(ToThisPtr(this)));
        _pTechOwner = pTechOwner;
    }
}

void    CGuildUser::InitTechInfo(const TVecGuildTechInfo& rInfo)
{
    if (!_pTechOwner)
    {
        CGuildTechOwnerPtr pTechOwner(new CGuildTechOwner(ToThisPtr(this)));
        _pTechOwner = pTechOwner;
    }
    _pTechOwner->InitFromDB(rInfo);
}


UINT64      CGuildUser::GetID() const
{
    return _qwRoleID;
}

UINT64      CGuildUser::GetRoleID() const
{
    return _qwRoleID;
}

const string& CGuildUser::GetName() const
{
    return _strName;
}

void CGuildUser::SetLevel(UINT16 wLevel)
{
    _wLevel = wLevel;
    if (_pGuild)
        _pGuild->NotifyUserInfo();
}

UINT16 CGuildUser::GetLevel() const
{
    return _wLevel;
}

void CGuildUser::SetOnlineUser(CUserPtr pUser)
{
    _pUser = pUser;
    UpdateTechAttr();
}

void CGuildUser::SetLastOnlineTime(UINT32 dwTime)
{
    _dwLastOnlineTime = dwTime;
    CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);
    if (_pGuild)
        _pGuild->NotifyUserInfo();
}

bool CGuildUser::IsOnline() const
{
    CUserPtr pUserSelf = GetOnlineUser();
    if (!pUserSelf)
        return false;
    return pUserSelf->IsOnline();
}

CUserPtr    CGuildUser::GetOnlineUser() const
{
    return _pUser.lock();
}

CUserPtr    CGuildUser::GetOnlineUser()
{
    return _pUser.lock();
}

void        CGuildUser::SetUser(CUserPtr pUser)
{
    _pUser = pUser;
    CUserPtr pUserSelf = GetOnlineUser();
    if (pUserSelf)
    {
        UINT32 dwSeverID = pUserSelf->GetGameSvrID();
        if (dwSeverID)
        {
            g_Game2CenterCommS.SendSvr_GuildNameUpdated(&dwSeverID, 1, GetID(), _pGuild?_pGuild->GetName():"");
            g_Game2CenterCommS.SendSvr_GuildLevelUpdated(&dwSeverID, 1, GetID(), _pGuild?_pGuild->GetLevel():0);
            LOG_CRI << "Update Guild Name: " << (_pGuild?_pGuild->GetName():"") << ".";
        }
        else
            LOG_CRI << "dwSeverID = " << dwSeverID << ".";
    }
}

UINT64  CGuildUser::GetGuildID() const
{
    if (_pGuild)
        return  _pGuild->GetID();
    else
        return 0;
}

CGuildPtr   CGuildUser::GetGuild()
{
    return _pGuild;
}

void    CGuildUser::SetGuild(CGuildPtr pGuild, bool bLoad /* = false */)
{
    _pGuild = pGuild;
    if (pGuild)
    {
        ClearApplyInfo();
        if (!bLoad)
            _dwJoinTime = Time::Now();
    }
    CUserPtr pUserSelf = GetOnlineUser();
    if (pUserSelf)
    {
        UINT32 dwSeverID = pUserSelf->GetGameSvrID();
        if (dwSeverID)
        {
            g_Game2CenterCommS.SendSvr_GuildNameUpdated(&dwSeverID, 1, GetID(), pGuild?pGuild->GetName():"");
            g_Game2CenterCommS.SendSvr_GuildLevelUpdated(&dwSeverID, 1, GetID(), pGuild?pGuild->GetLevel():0);
        }
    }
    UpdateTechAttr();
    if (Config.IsDBInited() && !bLoad)
        CRankMgr::Instance().UpdateRankGuildName(GetID(), pGuild?pGuild->GetName():"");
}

UINT32 CGuildUser::GetJoinTime() const
{
    return _dwJoinTime;
}

UINT32 CGuildUser::GetLastOnlineTime() const
{
    CUserPtr pUserSelf = GetOnlineUser();
    if (pUserSelf && pUserSelf->IsOnline())
        return 0;
    return _dwLastOnlineTime;
}

EMemberRank CGuildUser::GetRank() const
{
    return _eRank;
}

void CGuildUser::SetRank(EMemberRank eRank)
{
    if (eMemberNone == _eLastRank)
        SetLastRank(_eRank);

    _eRank = eRank;
}

void CGuildUser::SetLastRank(EMemberRank eLastRank)
{
    _eLastRank = eLastRank;
}

EMemberRank CGuildUser::GetLastRank() const
{
    return _eLastRank;
}

void CGuildUser::ResetDefaultAuthority()
{
    _dwAuthority = DEFALUT_A_AUTHORITY_TABLE[static_cast<UINT8>(_eRank)];
}

void CGuildUser::SetAuthority(UINT32 dwAuthority)
{
    _dwAuthority = dwAuthority;
}

UINT32 CGuildUser::GetBattlePoint() const
{
    return _dwBattlePoint;
}

UINT32 CGuildUser::GetContribution() const
{
    return _dwContribution;
}

void   CGuildUser::SetContribution(UINT32 dwContribution)
{
    _dwContribution = dwContribution;
    if (_pGuild)
        _pGuild->NotifyBaseInfoSelf(ToThisPtr(this));
    CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);
}

UINT32  CGuildUser::GetRemainDonate() const
{
    CUserPtr pUser = GetOnlineUser();
    if (!pUser)
        return 0;
    CCenterVar& rVar = pUser->GetCenterVar();
    UINT32 dwDonated = rVar.GetVar(NVarDefine::ePlayerVarGuildDonate);
    if (dwDonated > MAX_DONATE_EVERYDAY)
        return 0;
    return MAX_DONATE_EVERYDAY - dwDonated;
}

void CGuildUser::SetVIPLevel(UINT8 byVIPLevel)
{
    if (_byVIPLevel != byVIPLevel)
    {
        _byVIPLevel = byVIPLevel;
        CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);
        if (_pGuild)
            _pGuild->NotifyUserInfo();
    }
}

UINT8 CGuildUser::GetVIPLevel() const
{
    return _byVIPLevel;
}

void CGuildUser::SetPlayerFighterID(UINT16 wPlayerFighterID)
{
    if (_wPlayerFighterID != wPlayerFighterID)
    {
        _wPlayerFighterID = wPlayerFighterID;
        CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);
        if (_pGuild)
            _pGuild->NotifyUserInfo();
    }
}

UINT16 CGuildUser::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

void CGuildUser::SetQuality(UINT8 byQuality)
{
    if (_byQuality != byQuality)
    {
        _byQuality = byQuality;
        CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);
        if (_pGuild)
        {
            if (_pGuild->GetOwnerID() == GetID())
            {
                _pGuild->SetQuality(_byQuality);
            }
            _pGuild->NotifyUserInfo();
        }
    }
}

UINT8 CGuildUser::GetQuality() const
{
    return _byQuality;
}

bool    CGuildUser::SubContribution(UINT32 dwContribution)
{
    if (_dwContribution < dwContribution)
        return false;
    _dwContribution -= dwContribution;
    if (_pGuild)
    {
        _pGuild->NotifyBaseInfo();
        _pGuild->NotifyUserInfo();
    }
    CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);

    if (GetOnlineUser())
    {
        string str = NProtoCommon::GetDescription(EMONEY_GUILDCONTRIB);
        string strPkg = g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgUseCurrency, BuildStrVec(str,dwContribution));
        GetOnlineUser()->SendPkg(strPkg);
    }
    return true;
}

void    CGuildUser::AddContribution(UINT32 dwContribution)
{
    _dwContribution += dwContribution;
    if (_pGuild)
    {
        _pGuild->NotifyBaseInfo();
        _pGuild->NotifyUserInfo();
    }
    CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);

    if (GetOnlineUser())
    {
        string str = NProtoCommon::GetDescription(EMONEY_GUILDCONTRIB);
        string strPkg = g_GlobalChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGetCurrency, BuildStrVec(str,dwContribution));
        GetOnlineUser()->SendPkg(strPkg);
    }
}

void  CGuildUser::GetAllInfo(SGuildUserInfo& rInfo) const
{
    rInfo.qwRoleID          = GetID();
    rInfo.qwGuildID         = GetGuildID();
    rInfo.strName           = GetName();
    rInfo.wLevel            = GetLevel();
    rInfo.dwLastOnlineTime  = GetLastOnlineTime();
    rInfo.dwJoinTime        = GetJoinTime();
    rInfo.eMemberRank       = GetRank();
    rInfo.eMemberLastRank   = GetLastRank();
    rInfo.dwContribution    = GetContribution();
    rInfo.byVIPLevel        = GetVIPLevel();
    rInfo.vecPlatforms      = CUserMgr::GetPlatformParam(GetID());
}

void  CGuildUser::GetTechInfo(TVecGuildTechInfo& rvecInfo) const
{
    if (_pTechOwner)
        _pTechOwner->GetAllInfo(rvecInfo);
}

void CGuildUser::GetAllDBInfo(SDBGuildUserInfo& rInfo) const
{
    SGuildUserInfo& rBaseInfo = rInfo.sBaseInfo;
    GetAllInfo(rBaseInfo);
    if (_pTechOwner)
        _pTechOwner->GetAllInfo(rInfo.vecTechInfo);
    rInfo.dwBattleScore = _dwBattleScore;
    rInfo.wPlayerFighterID = _wPlayerFighterID;
    rInfo.byQuality = _byQuality;
}

bool  CGuildUser::HasAuthority(UINT16 dwFlag) const
{
    return AUTHORITY_TABLE[static_cast<UINT8>(_eRank)] & dwFlag;
}

UINT32  CGuildUser::GetApplyCount() const
{
    return _vecApplyInfoPtr.size();
}

CGuildApplyInfoPtr CGuildUser::GetApplyInfo(UINT64 qwGuildID)
{
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (*it && ((*it)->GetGuildID() == qwGuildID))
            return *it;
    }
    return NULL;
}

EApplyResult CGuildUser::CreateApplyInfo(UINT64 qwGuildID, 
        function<void(CGuildApplyInfoPtr pApplyInfo, EApplyResult eResult)> func)
{
    if (GetApplyCount() >= SParamConfig::wGuildApplyNumLimit)
        return eGApplyListFull;

    CUserPtr pUserSelf = GetOnlineUser();
    if (pUserSelf)
    {
        UINT32 dwServerID = pUserSelf->GetGameSvrID();
        g_Game2CenterCommS.SendSvr_GetBattlePoint(&dwServerID, 1, GetRoleID(), 
                [this, qwGuildID, func](UINT8 byError, UINT8 byRet, UINT32 dwBattlePoint)
        {
            EApplyResult eResult = eGApplySuccess;
            CGuildApplyInfoPtr pApplyInfo(new CGuildApplyInfo(qwGuildID, ToThisPtr(this), dwBattlePoint));
            if (pApplyInfo)
            {
                _vecApplyInfoPtr.push_back(pApplyInfo);
                CGuildApplyInfo::Update2DB(pApplyInfo, eOpAdd);
                LOG_WRN << "dwBattlePoint = " << dwBattlePoint << ".";
                eResult = eGApplySuccess;
            }
            else
                eResult = eGApplyFailed;
            func(pApplyInfo, eResult);

        });
        return eGApplySuccess;
    }
    else
    {

        EApplyResult eResult = eGApplySuccess;
        CGuildApplyInfoPtr pApplyInfo(new CGuildApplyInfo(qwGuildID, ToThisPtr(this), 0));
        if (pApplyInfo)
        {
            _vecApplyInfoPtr.push_back(pApplyInfo);
            CGuildApplyInfo::Update2DB(pApplyInfo, eOpAdd);
            LOG_WRN << "No dwBattlePoint = 0.";
            eResult = eGApplySuccess;
        }
        else
            eResult = eGApplyFailed;
        func(pApplyInfo, eResult);
        return eGApplySuccess;
    }
}

void  CGuildUser::EraseApplyInfo(UINT64 qwGuildID)
{
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (*it && (*it)->GetGuildID() == qwGuildID)
        {
            CGuildApplyInfo::Update2DB(*it, eOpDel);
            _vecApplyInfoPtr.erase(it);
            break;
        }
    }
}

void CGuildUser::ClearApplyInfo()
{
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (*it)
        {
            CGuildApplyInfo::Update2DB(*it, eOpDel);
        }
    }
    _vecApplyInfoPtr.clear();
}

bool CGuildUser::GetApplyGuildID(TVecUINT64& rvecGuildID) const
{
    for (auto it = _vecApplyInfoPtr.begin(); it != _vecApplyInfoPtr.end(); ++it)
    {
        if (*it)
            rvecGuildID.push_back((*it)->GetGuildID());
    }
    return true;
}


void CGuildUser::TryGetImpeach()
{
    if (_pGuild)
        _pGuild->GetImpeachNotify(ToThisPtr(this));
}

CGuildTechOwnerPtr CGuildUser::GetTechOwner()
{
    return _pTechOwner;
}

void CGuildUser::UpdateTechAttr() const
{
    CUserPtr pUserSelf = GetOnlineUser();
    if (!_pTechOwner || !pUserSelf)
        return;
    if (_pGuild)
    {
        TVecSGuildInfoBase vecInfo;
        _pTechOwner->GetAllInfo(vecInfo);
        string strData = g_GuildProtS.BuildPkg_GuildInfoNotify(eGDTTech, vecInfo);
        pUserSelf->SendPkg(strData);
    }
    {
        TVecFtAttrMod vecFtAttr;
        TVecGuildTechInfo vecTech;
        _pTechOwner->GetAllInfo(vecTech);
        _pTechOwner->GetFtAttr(vecFtAttr);
        UINT32 dwSeverID = pUserSelf->GetGameSvrID();
        if (dwSeverID)
            g_Game2CenterCommS.SendSvr_GuildTechUpdate(&dwSeverID, 1, GetID(), vecFtAttr, vecTech);
    }
}

void CGuildUser::AddBattleScore(UINT32 dwScore)
{
    _dwBattleScore += dwScore;
    CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);
}

void CGuildUser::SetBattleScore(UINT32 dwScore, bool bInit /* = false */)
{
    _dwBattleScore = dwScore;
    if (!bInit)
        CGuildUser::Update2DB(ToThisPtr(this), eOpUpdate);
}

UINT32 CGuildUser::GetBattleScore() const
{
    return _dwBattleScore;
}

UINT32 CGuildUser::GetLastWorshipTime() const
{
    return _dwLastWorshipTime;
}

void CGuildUser::SetLastWorshipTime(UINT32 dwLastWorshipTime)
{
    _dwLastWorshipTime = dwLastWorshipTime;
}

// 交给数据库保存
void    CGuildUser::Update2DB(CGuildUserPtr pUser, EDataChange eChangeType)
{
    if (!pUser)
        return;
    SDBGuildUserInfo sGuildUserInfo;
    pUser->GetAllDBInfo(sGuildUserInfo);
    string strData;
    COutArchive iar(strData);
    iar << sGuildUserInfo;
    g_Center2DBGuildC.Send_GuildDataUpdate(pUser->GetGuildID(), eGDTUser, eChangeType, strData);
}

string CGuildUser::GetRankName()
{
    return GetNameByRank(_eRank);
}
