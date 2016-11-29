#include "GuildUserMgr.h"
#include "GuildUser.h"
#include "UserMgr.h"
#include "Center2DBGuildC.h"
#include "Guild.h"

CGuildUserPtr CGuildUserMgr::CreateGuildUser(CUserPtr pUser)
{
    CGuildUserPtr pGuildUser(new CGuildUser(pUser));
    if (pGuildUser)
    {
        _mapGuildUser[pGuildUser->GetID()] = pGuildUser;
        pUser->SetGuildUser(pGuildUser);
        pGuildUser->InitTechInfo();
    }
    return pGuildUser;
}

CGuildUserPtr CGuildUserMgr::CreateGuildUser(const SDBGuildUserInfo& rUserInfo)
{
    CGuildUserPtr pGuildUser(new CGuildUser(rUserInfo));
    if (pGuildUser)
    {
        _mapGuildUser[pGuildUser->GetID()] = pGuildUser;
        CUserPtr pUser = CUserMgr::GetUserByUserID(pGuildUser->GetID());
        if (pUser)
        {
            pUser->SetGuildUser(pGuildUser);
            pGuildUser->SetOnlineUser(pUser);
        }
        _mapGuildUser[pGuildUser->GetID()] = pGuildUser;
        pGuildUser->InitTechInfo(rUserInfo.vecTechInfo);
    }
    return pGuildUser;
}

CGuildUserPtr CGuildUserMgr::GetUserByUserID(UINT64 qwRoleID)
{
    auto it = _mapGuildUser.find(qwRoleID);
    if (it == _mapGuildUser.end())
        return NULL;
    else
        return it->second;
}

void CGuildUserMgr::OnUserLogin(CUserPtr pUser)
{
    if (!pUser)
        return;
    CGuildUserPtr pGuildUser = GetUserByUserID(pUser->GetUserID());
    if (!pGuildUser)
        g_Center2DBGuildC.Send_GuildUserLogin(pUser->GetUserID());
    else
    {
        pUser->SetGuildUser(pGuildUser);
        pGuildUser->SetUser(pUser);
        pGuildUser->TryGetImpeach();
        pGuildUser->UpdateTechAttr();
    }
}

void CGuildUserMgr::GetGuildName(UINT64 qwRoleID, string& strGuildName)
{
    auto it = _mapGuildUser.find(qwRoleID);
    if (it != _mapGuildUser.end())
    {
        CGuildPtr pGuild = it->second->GetGuild();
        if (pGuild)
            strGuildName = pGuild->GetName();
        else
            strGuildName = "";
    }
    else
        strGuildName = "";
}

UINT64 CGuildUserMgr::GetGuildID(UINT64 qwRoleID)
{
    auto it = _mapGuildUser.find(qwRoleID);
    if (it != _mapGuildUser.end())
    {
        CGuildPtr pGuild = it->second->GetGuild();
        if (pGuild)
            return pGuild->GetID();
    }
    return 0;
}

bool CGuildUserMgr::IsSameGuild(UINT64 qwRoleID1, UINT64 qwRoleID2)
{
    if (!qwRoleID1 || !qwRoleID2)
        return false;
    auto it1 = _mapGuildUser.find(qwRoleID1);
    if (it1 == _mapGuildUser.end())
        return false;
    auto it2 = _mapGuildUser.find(qwRoleID2);
    if (it2 == _mapGuildUser.end())
        return false;
    CGuildPtr pGuild1 = it1->second->GetGuild();
    CGuildPtr pGuild2 = it2->second->GetGuild();
    if (!pGuild1 || !pGuild2)
        return false;
    return pGuild1->GetID() == pGuild2->GetID();
}

