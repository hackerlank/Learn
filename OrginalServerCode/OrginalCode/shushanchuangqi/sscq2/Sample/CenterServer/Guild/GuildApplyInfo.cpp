#include "GuildApplyInfo.h"

#include "GuildUser.h"
#include "Center2DBGuildC.h"

CGuildApplyInfo::CGuildApplyInfo(UINT64 qwGuildID, CGuildUserPtr pGuidlUser, UINT32 dwBattlePoint):
    _qwRoleID(0), _qwGuildID(qwGuildID), _wLevel(0), _dwBattlePoint(dwBattlePoint)
{
    if (pGuidlUser)
    {
        _qwRoleID       = pGuidlUser->GetID();
        _strName        = pGuidlUser->GetName();
        _wLevel         = pGuidlUser->GetLevel();
    }
}

CGuildApplyInfo::~CGuildApplyInfo()
{
}

UINT64  CGuildApplyInfo::GetRoleID() const
{
    return _qwRoleID;
}

UINT64  CGuildApplyInfo::GetGuildID() const
{
    return _qwGuildID;
}

const string& CGuildApplyInfo::GetName() const
{
    return _strName;
}

UINT16  CGuildApplyInfo::GetLevel() const
{
    return _wLevel;
}

UINT32  CGuildApplyInfo::GetBattlePoint() const
{
    return _dwBattlePoint;
}

void CGuildApplyInfo::GetAllInfo(SGuildApplyInfo& rGuildApplyInfo)
{
    rGuildApplyInfo.qwRoleID        = GetRoleID();
    rGuildApplyInfo.qwGuildID       = GetGuildID();
    rGuildApplyInfo.strName         = GetName();
    rGuildApplyInfo.wLevel          = GetLevel();
    rGuildApplyInfo.dwBattlePoint   = GetBattlePoint();
}

// 交给数据库保存
void    CGuildApplyInfo::Update2DB(CGuildApplyInfoPtr pInfo, EDataChange eChangeType)
{
    if (!pInfo)
        return;
    SGuildApplyInfo sGuildApplyInfo;
    pInfo->GetAllInfo(sGuildApplyInfo);
    string strData;
    COutArchive iar(strData);
    iar << sGuildApplyInfo;
    g_Center2DBGuildC.Send_GuildDataUpdate(pInfo->GetGuildID(), eGDTApplyInfo, eChangeType, strData);
}
