#ifndef GUILD_BUILDING_H
#define GUILD_BUILDING_H

#include "stdafx.h"

#include  "LevelObject.h"
#include  "GuildProt.h"

using namespace NGuildProt;
using namespace NProtoCommon;

const UINT32 MAX_CONTRIBUTION = 9999999;

typedef map<EBuildingType, CGuildBuildingPtr> TMapGuildBuildingPtr;

class CGuildBuilding : public CLevelObject
{
    public:
        CGuildBuilding ();
        virtual ~CGuildBuilding();

        bool InitFromDB(EBuildingType eType, UINT16 wLevel);

        EBuildingType GetType() const;
        void SetType(EBuildingType eType);
        UINT32 GetAttrValue() const;

        void GetAllInfo(SGuildBuildingInfo& rInfo) const;

    public:
        virtual UINT32 GetTableLevelExp(UINT16 wLevel) const;
        virtual UINT16 GetTableLevel(UINT32 dwExp) const;
        virtual UINT16 GetMaxLevel() const;

    private:
        EBuildingType           _eType;    // 建筑类型
};

class CGuildBuildingOwner : public enable_shared_from_this<CGuildBuildingOwner>
{
    public:
        CGuildBuildingOwner(CGuildPtr pGuild);
        virtual ~CGuildBuildingOwner();

        bool InitFromDB(const TVecGuildBuildingInfo& rvecBuildings);

        UINT16 GetLevel(EBuildingType  eType) const;
        UINT16 GetMaxLevel(EBuildingType  eType) const;

        UINT32 GetAttrValue(EBuildingType eType) const;

        bool   UpgradeBuilding(EBuildingType eType, EBuildingResult& eResult);

        UINT64 GetGuildID() const;

        void GetAllInfo(TVecSGuildInfoBase& rvecInfo) const;
        void GetAllInfo(TVecGuildBuildingInfo& rvecInfo) const;

        void NotifyInfo() const;

        static void Update2DB(CGuildBuildingOwnerPtr pBuildingOwner, EDataChange eChangeType, UINT64 qwOwnerID = 0);
    private:
        CGuildPtr            _pGuild;
        TMapGuildBuildingPtr _mapGuildBuildingPtr;
};

#endif // #ifndef GUILD_BUILDING_H

