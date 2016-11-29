#ifndef GUILD_USER_MGR_H
#define GUILD_USER_MGR_H

#include "stdafx.h"
#include <Singleton.h>

#include "GuildProt.h"

using namespace NGuildProt;

class CGuildUserMgr : public Singleton<CGuildUserMgr>
{
    public:
        CGuildUserPtr CreateGuildUser(CUserPtr pUser);
        CGuildUserPtr CreateGuildUser(const SDBGuildUserInfo& rUserInfo);
        CGuildUserPtr GetUserByUserID(UINT64 qwRoleID);
        void OnUserLogin(CUserPtr pUser);

        void GetGuildName(UINT64 qwRoleID, string& strGuildName);
        UINT64 GetGuildID(UINT64 qwRoleID);
        bool IsSameGuild(UINT64 qwRoleID1, UINT64 qwRoleID2);

    private:
        map<UINT64, CGuildUserPtr> _mapGuildUser;
};
#endif //#ifndef GUILD_USER_MGR_H
