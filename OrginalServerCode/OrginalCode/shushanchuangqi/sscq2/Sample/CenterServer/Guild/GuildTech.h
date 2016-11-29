#ifndef GUILD_TECG_H
#define GUILD_TECG_H

#include "stdafx.h"

#include "LevelObject.h"
#include "GuildProt.h"
#include "ProtoCommon.h"

using namespace NGuildProt;
using namespace NProtoCommon;
using namespace NProtoCommon;

typedef map<ETechType, CGuildTechPtr> TMapGuildTechPtr;

class CGuildTech : public CLevelObject
{
    public:
        CGuildTech (ETechType eType);
        virtual ~CGuildTech();

        bool InitFromDB(ETechType eType, UINT16 wLevel);

        ETechType GetType() const;
        UINT32 GetAttrValue() const;

        void GetAllInfo(SGuildTechInfo& rInfo) const;

        bool GetFtAttr(TVecFtAttrMod& vecFtAttr) const;

        UINT16 GetUserLevel() const;

    public:
        virtual UINT32 GetTableLevelExp(UINT16 wLevel) const;
        virtual UINT16 GetTableLevel(UINT32 dwExp) const;
        virtual UINT16 GetMaxLevel() const;

    private:
        ETechType           _eType;    // 建筑类型
};

class CGuildTechOwner : public enable_shared_from_this<CGuildTechOwner>
{
    public:
        CGuildTechOwner(CGuildUserPtr pGuildUser);
        virtual ~CGuildTechOwner();

        bool InitFromDB(const TVecGuildTechInfo& rvecTechs);

        UINT16 GetLevel(ETechType  eType) const;
        UINT16 GetMaxLevel(ETechType  eType) const;

        bool   UpgradeTech(ETechType eType, ETechResult& eResult);

        UINT64 GetGuildID() const;

        void GetAllInfo(TVecSGuildInfoBase& rvecInfo) const;
        void GetAllInfo(TVecGuildTechInfo& rvecInfo) const;

        bool GetFtAttr(TVecFtAttrMod& vecFtAttr) const;

        static void Update2DB(CGuildTechOwnerPtr pTechOwner, EDataChange eChangeType, UINT64 qwOwnerID = 0);
    private:
        CGuildUserPtr    _pGuildUser;
        TMapGuildTechPtr _mapGuildTechPtr;
};

#endif // #define GUILD_TECG_H
