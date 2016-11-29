#ifndef GUILD_APPLY_INFO_H
#define GUILD_APPLY_INFO_H

#include "stdafx.h"

#include "GuildProt.h"

using namespace NGuildProt;
using namespace NProtoCommon;

class CGuildApplyInfo
{
    public: 
        CGuildApplyInfo(UINT64 qwGuildID, CGuildUserPtr pGuildUser, UINT32 dwBattlePoint);
        virtual ~CGuildApplyInfo();

        UINT64  GetRoleID() const;
        UINT64  GetGuildID() const;
        const string& GetName() const;
        UINT16  GetLevel() const;
        UINT32  GetBattlePoint() const;

        void GetAllInfo(SGuildApplyInfo& rGuildApplyInfo);

        static void Update2DB(CGuildApplyInfoPtr pInfo, EDataChange eChangeType);
    private:
        UINT64      _qwRoleID;
        UINT64      _qwGuildID;
        string      _strName;
        UINT16      _wLevel;
        UINT32      _dwBattlePoint;
};
#endif // #ifndef GUILD_APPLY_INFO_H

