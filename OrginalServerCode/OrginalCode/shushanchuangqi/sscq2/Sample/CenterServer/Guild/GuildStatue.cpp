#include "GuildStatue.h"

#include "GuildMgr.h"
#include "Center2DBGuildC.h"
#include "GuildUser.h"
#include "GuildLog.h"
#include "User.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "VIPMgr.h"
#include "Protocols.h"

CGuildStatue::CGuildStatue():
    _byWorshipCount(0)
{
    _eLevelType = eLevelUpByExp;
}

CGuildStatue::~CGuildStatue()
{
}

bool CGuildStatue::InitFromDB(UINT16 wLevel, UINT32 dwExp, UINT8 byWorshipCount)
{
    CLevelObject::InitFromDB(dwExp, wLevel, 0);
    _byWorshipCount = byWorshipCount;
    return true;
}

UINT32 CGuildStatue::GetTableLevelExp(UINT16 wLevel) const
{
    const SGuildLevelCFG* pCFG = CGuildMgr::Instance().GetStatueConfig(wLevel);
    if (!pCFG)
        return 0;
    return pCFG->_Exp;
}

// 返回等级
UINT16 CGuildStatue::GetTableLevel(UINT32 dwExp) const
{
    const SGuildLevelCFG* pCFG = CGuildMgr::Instance().GetStatueConfigByExp(dwExp);
    if (!pCFG)
        return 0;
    return pCFG->_Level;
}

//  返回最高等级
UINT16 CGuildStatue::GetMaxLevel() const
{
    return CGuildMgr::Instance().GetStatueConfigMaxLeve();
}

void CGuildStatue::GetAllInfo(SGuildStatueInfo& rInfo) const
{
    rInfo.wLevel         = GetLevel();
    rInfo.dwExp          = GetExp();
    rInfo.byWorshipCount = _byWorshipCount;
}

UINT8 CGuildStatue::GetWorshipCount() const
{
    return _byWorshipCount;
}

void CGuildStatue::AddWorshipCount()
{
    ++_byWorshipCount;
}

void CGuildStatue::ResetWorshipCount()
{
    _byWorshipCount = 0;
}

CGuildStatueOwner::CGuildStatueOwner(CGuildPtr pGuild) : 
    _pGuild(pGuild)
{
    if (!_pStatue)
    {
        CGuildStatuePtr pStatue(new CGuildStatue);
        _pStatue = pStatue;
    }
}

CGuildStatueOwner::~CGuildStatueOwner()
{
}

// 从数据库加载
bool CGuildStatueOwner::InitFromDB(const SGuildStatueInfo& rGuildStatueInfo)
{
    CGuildStatuePtr pStatue(new CGuildStatue);
    if (!pStatue)
        return false;
    pStatue->InitFromDB(rGuildStatueInfo.wLevel, rGuildStatueInfo.dwExp, rGuildStatueInfo.byWorshipCount);
    _pStatue = pStatue;
    return true;
}

UINT64 CGuildStatueOwner::GetGuildID() const
{
    if (!_pGuild)
        return 0;
    return _pGuild->GetID();
}

UINT8 CGuildStatueOwner::GetWorshipCount() const
{
    if (_pStatue)
        return _pStatue->GetWorshipCount();
    return 0;
}

void   CGuildStatueOwner::ResetWorshipCount()
{
    if (_pStatue)
        _pStatue->ResetWorshipCount();
}


UINT16 CGuildStatueOwner::GetLevel() const
{
    if (!_pStatue)
    {
        LOG_CRI << "_pStatue == NULL.";
        return 0;
    }
    return _pStatue->GetLevel();
}

UINT16 CGuildStatueOwner::GetMaxLevel() const
{
    if (!_pStatue)
        return 0;
    return _pStatue->GetMaxLevel();
}

// 帮派神像供奉
bool CGuildStatueOwner::Worship(CGuildUserPtr pGuildUser, EWorshipType eType, EStatueResult& eResult, function<void(UINT8 byRet)>func)
{
    if (eType <= eWorshipNone)
    {
        eResult= eGSResultFailed;
        return false;
    }

    if (!_pGuild)
    {
        eResult= eGSResultFailed;
        return false;
    }
    UINT16 wOldLevel = _pStatue->GetLevel();
    if (wOldLevel >= GetMaxLevel()) // 已经最高等级
    {
        eResult= eGSResultLevelMax;
        return false;
    }

    CUserPtr pUser = pGuildUser->GetOnlineUser();
    if (!pUser)
    {
        eResult = eGSResultFailed;
        return false;
    }

    CCenterVar& rVar = pUser->GetCenterVar();
    UINT8 byWorshipBit = rVar.GetVar(NVarDefine::ePlayerVarGuildWorship);
    if (byWorshipBit & (0x01 << (static_cast<UINT8>(eType) - 1)))
    {
        eResult = eGSResultWorshiped;
        return false;
    }

    UINT32 dwExp = CGuildMgr::Instance().TestWorshipCond(pGuildUser, eType, eResult);
    if (!dwExp)
        return false;

    ELevelObjectErr eErr = _pStatue->TryLevelUp(dwExp);
    CGuildMgr::Instance().SyncGuildRankByLevel(_pGuild->GetID());
    if (eErr == eErrNoEnoughExp)
    {
        eResult= eGSResultLackofSilver;
        return false;
    }
    else if (eErr != eErrSuccess && eErr != eErrMaxLevel)
    {
        eResult= eGSResultFailed;
        return false;
    }
    
    UINT32 dwNow = Time::Now();
    UINT32 dwLastTime = pGuildUser->GetLastWorshipTime();
    if (dwLastTime && dwLastTime >= dwNow)
    {
        eResult = eGSResultTooFast;
        return false;
    }
    pGuildUser->SetLastWorshipTime(dwNow);

    eResult= eGSResultFailed;
    CGuildMgr::Instance().ProcessWorshipCond(pGuildUser, eType, eResult, func, 
            [this, pGuildUser, eType, wOldLevel, &rVar, dwExp, byWorshipBit](UINT32 dwContribution, UINT32 dwCost) mutable
            {
                if (dwContribution)
                {
                    _pStatue->AddWorshipCount();

                    UINT8 byQuality = 3;
                    CUserPtr pUser = pGuildUser->GetOnlineUser();
                    if (pUser)
                    {
                        SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
                        if(pCfgVip)
                            dwContribution += dwContribution * pCfgVip->_GuildFireGet / 100;
                        byQuality = pUser->GetQuality();
                    }
                    pGuildUser->AddContribution(dwContribution);

                    byWorshipBit = byWorshipBit | (0x01 << (static_cast<UINT8>(eType) - 1));
                    rVar.SetVar(NVarDefine::ePlayerVarGuildWorship, byWorshipBit);

                    //event
                    {
                            UINT32 ePlayerVarGuildWorshipType = NVarDefine::ePlayerVarGuildWorshipTypeBegin+eType-1;
                            rVar.AddVar(ePlayerVarGuildWorshipType,1);

                            TVecINT32 vecParam2;
                            vecParam2.push_back(eType);
                            vecParam2.push_back(rVar.GetVar(ePlayerVarGuildWorshipType));
                            if (pUser && pUser->IsOnLine())
                                pUser->OnEvent(eEventType_GuildLevel, vecParam2);
                            else
                            {
                                UINT64 qwRoleID = pGuildUser->GetID();
                                CUser::AddOffLineEvent(qwRoleID, eEventType_GuildLevel,vecParam2);
                            }
                    }


                    if (_pGuild)
                    {
                        _pGuild->SetDirty(eGDTStatue);
                        _pGuild->SaveData();
                        CGuildStatueLogPtr pLog (new CGuildStatueLog);
                        if (pLog->FormatParam(byQuality, pGuildUser->GetName(), eType, dwExp))
                            _pGuild->AddLog(pLog);

                        // 升级了
                        if (_pStatue->GetLevel() != wOldLevel)
                        {
                            OnLevelChanged();
                            TVecINT32 vecParam2;
                            vecParam2.push_back(_pStatue->GetLevel());
                            ostringstream strInfo2;
                            strInfo2 << _pGuild->GetID();
                            if (pUser && pUser->IsOnLine())
                                pUser->OnEvent(eEventType_GuildLevel, vecParam2, strInfo2.str());
                            else
                            {
                                UINT64 qwRoleID = pGuildUser->GetID();
                                CUser::AddOffLineEvent(qwRoleID, eEventType_GuildLevel,vecParam2, strInfo2.str());
                            }

                            UINT32 dwID = CCenterConfig::Instance().GetSvrID();
                            g_Game2CenterGuildBattleS.SendSvr_GuildLevelChanged(&dwID, 1, GetGuildID(), _pStatue->GetLevel());

                        }
                        // 帮派ID，供奉类型，当前供奉人数
                        TVecINT32 vecParam2;
                        vecParam2.push_back(eType);
                        vecParam2.push_back(GetWorshipCount());
                        ostringstream strInfo2;
                        strInfo2 << _pGuild->GetID();

                        TVecINT32 vecParam3;
                        vecParam3.push_back(eType);
                        vecParam3.push_back(1);

                        if (pUser && pUser->IsOnLine())
                        {
                            pUser->OnEvent(eEventType_GuildOblationSelf, vecParam3);
                            pUser->OnEvent(eEventType_GuildOblation, vecParam2, strInfo2.str());
                        }
                        else
                        {
                            UINT64 qwRoleID = pGuildUser->GetID();
                            CUser::AddOffLineEvent(qwRoleID,eEventType_GuildOblation,vecParam2, strInfo2.str());
                            CUser::AddOffLineEvent(qwRoleID,eEventType_GuildOblationSelf,vecParam3);
                        }
                    }
                    CGuildStatueOwner::Update2DB(ToThisPtr(this), eOpUpdate);
                }

            });
    return false;
}

bool CGuildStatueOwner::AddExp(UINT32 dwExp)
{
    UINT16 wOldLevel = _pStatue->GetLevel();
    _pStatue->SetExp(_pStatue->GetExp() + dwExp);
    UINT16 wNewLevel = _pStatue->GetLevel();
    if (wOldLevel != wNewLevel)
    {
        OnLevelChanged();
    }
    //测试帮派活动（DEBEG）
    CGuildMgr::Instance().SyncGuildRankByLevel(_pGuild->GetID());

    _pGuild->NotifyStatueInfo();
    _pGuild->NotifyBaseInfo();
    CGuildStatueOwner::Update2DB(ToThisPtr(this), eOpUpdate);
    _pGuild->SyncGuildLevel();

    return true;
}

void CGuildStatueOwner::OnLevelChanged()
{
    CGuildListInfoPtr pGuildListInfo = CGuildMgr::Instance().GetListInfo(_pGuild->GetID());
    if (pGuildListInfo)
    {
        pGuildListInfo->SetMaxMemberCount(_pGuild->GetMaxMemberCount());
        pGuildListInfo->SetLevel(static_cast<UINT16>(_pStatue->GetLevel()));
    }
    _pGuild->NotifyBaseInfo();
    _pGuild->NotifyStatueInfo();
    _pGuild->SyncGuildLevel();
}

bool CGuildStatueOwner::GetAllInfo(SGuildStatueInfo& rGuildStatueInfo) const
{
    if (_pStatue)
    {
        rGuildStatueInfo.qwGuildID = GetGuildID();
        rGuildStatueInfo.wLevel = _pStatue->GetLevel();
        rGuildStatueInfo.dwExp  = _pStatue->GetExp();
        rGuildStatueInfo.byWorshipCount = _pStatue->GetWorshipCount();
        rGuildStatueInfo.dwTime  = Time::Now();
        return true;
    }
    return false;
}


void CGuildStatueOwner::Update2DB(CGuildStatueOwnerPtr pStatueOwner, EDataChange eChangeType, UINT64 qwOwnerID /* = 0 */)
{
    if (!pStatueOwner && !qwOwnerID)
        return;

    if (!qwOwnerID)
        qwOwnerID = pStatueOwner->GetGuildID();

    SGuildStatueInfo sGuildStatueInfo;
    if (pStatueOwner)
        pStatueOwner->GetAllInfo(sGuildStatueInfo);
    string strData;
    COutArchive iar(strData);
    iar << sGuildStatueInfo;
    g_Center2DBGuildC.Send_GuildDataUpdate(qwOwnerID, eGDTStatue, eChangeType, strData);
}
