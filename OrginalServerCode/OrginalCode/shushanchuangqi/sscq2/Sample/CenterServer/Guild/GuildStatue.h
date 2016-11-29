#ifndef GUILD_STATUE_H
#define GUILD_STATUE_H

#include "stdafx.h"

#include  "LevelObject.h"
#include  "GuildProt.h"

using namespace NGuildProt;
using namespace NProtoCommon;

class CGuildStatue : public CLevelObject
{
    public:
        CGuildStatue ();
        virtual ~CGuildStatue();

        bool InitFromDB(UINT16 wLevel, UINT32 dwExp, UINT8 byWorshipCount);

        UINT8 GetAttrValue() const;

        void GetAllInfo(SGuildStatueInfo& rInfo) const;

        UINT8 GetWorshipCount() const;
        void AddWorshipCount();
        void ResetWorshipCount();

    public:
        virtual UINT32 GetTableLevelExp(UINT16 wLevel) const;
        virtual UINT16 GetTableLevel(UINT32 dwExp) const;
        virtual UINT16 GetMaxLevel() const;

        UINT8 _byWorshipCount;
};

class CGuildStatueOwner : public enable_shared_from_this<CGuildStatueOwner>
{
    public:
        CGuildStatueOwner(CGuildPtr pGuild);
        virtual ~CGuildStatueOwner();

        bool InitFromDB(const SGuildStatueInfo& rGuildStatueInfo);

        UINT16 GetLevel() const;
        UINT16 GetMaxLevel() const;

        bool   Worship(CGuildUserPtr pGuildUser, EWorshipType eType, EStatueResult& eResult, function<void(UINT8 byRet)> func);

        bool   AddExp(UINT32 dwExp);

        void   PushLog(CGuildStatueLogPtr pLog);

        UINT64 GetGuildID() const;
        UINT8  GetWorshipCount() const;
        void   ResetWorshipCount();

        bool GetAllInfo(SGuildStatueInfo& rGuildStatueInfo) const;

        void OnLevelChanged();

        static void Update2DB(CGuildStatueOwnerPtr pStatueOwner, EDataChange eChangeType, UINT64 qwOwnerID = 0);
    private:
        CGuildPtr               _pGuild;
        CGuildStatuePtr         _pStatue;    // 帮派神像

        // XXX: 还是从帮派中获取，不然时间排序麻烦的说
        //TvecGuildStatueLogPtr   _vecLogPtr;
};

#endif // #ifndef GUILD_STATUE_H

