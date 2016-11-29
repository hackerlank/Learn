#ifndef TRUMP_MGR_H
#define TRUMP_MGR_H

#include "stdafx.h"

#include "Singleton.h"
#include "TrumpIntensifyCFG.h"

const UINT16 TRUMP_UPGRADE_ITEM = 175;
const UINT16 TRUMP_EVOLVE_ITEM = 176;

struct STrumpUpgradeMaterial    // 法宝升级所需材料
{
    UINT16 wItemID;
    UINT32 dwItemCount;
    STrumpUpgradeMaterial():
        wItemID(0), dwItemCount(0)
    {
    }
};

struct STrumpEvolveMaterial     // 法宝升阶所需材料
{
    UINT16 wItemID;
    UINT32 dwItemCount;
    STrumpEvolveMaterial():
        wItemID(0), dwItemCount(0)
    {
    }
};

class CTrumpMgr : public Singleton<CTrumpMgr>
{
    public:
        bool Init();

        bool LoadConfig(const string&);
        bool Reload();

        void GetAllAttr     (TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank, bool bIsMainFighter) const;
        bool GetHaloAttr    (TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;
        bool GetExtraAttr   (TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;
        bool GetActiveAttr  (TVecFloat& rvecAttr, UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;

        UINT32  GetSkill(UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;

        bool    GetUpgradeMaterial(UINT16 wItemID, UINT16 wLevel, UINT16 wRank, STrumpUpgradeMaterial& rMaterial) const;
        bool    GetEvolveMaterial(UINT16 wItemID, UINT16 wLevel, UINT16 wRank, STrumpEvolveMaterial& rMaterial) const;
        UINT32  Upgrade (CUserPtr pUser, UINT16 wItemID, UINT16& wLevel, UINT16& wRank, UINT32& dwExp, STrumpUpgradeMaterial& rMaterial, bool bOneKey, UINT32& dwAddExp) const;
        UINT32  Evolve  (UINT16 wItemID, UINT16& wLevel, UINT16& wRank, UINT32& dwExp, STrumpEvolveMaterial& rMaterial) const;

        bool  Super (UINT16 wItemID, UINT16& wLevel, UINT16& wRank, UINT32& dwExp) const;
    private:
        bool LoadIntensifyConfig    (const string& strPath);

        bool AddAttr2FighterAttr(UINT16 wAttrID, UINT16 wLevel, UINT16 wRank, TVecFloat& rvecAttr) const;

        UINT32 GetNextLevelExp(UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;

        bool IsMaxRank      (UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;
        bool IsMaxLevel     (UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;
        bool CanEvolve      (UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;
        bool CanUpgrade     (UINT16 wItemID, UINT16 wLevel, UINT16 wRank) const;

        UINT16 GetAttrID(UINT16 wItemID) const;

        UINT32 GetEquipTrumpID(UINT16 wItemID,UINT16 wLevel)
        { return wItemID*1000 + wLevel;};

    private:
        struct SOneLevelInfo    // 法宝进阶经验值
        {
            UINT16 wAttrID;
            UINT16 wLevel;
            UINT16 wRank;
            UINT32 dwExp;
            UINT16 wItemID;
            UINT32 wItemCount;
            UINT8  bySkillLevel;
            SOneLevelInfo():
                wAttrID(0), wLevel(0), wRank(0), dwExp(0), wItemID(0), wItemCount(0), bySkillLevel(0)
            {
            }
        };

        struct SIntensifyInfo   // 法宝强化等级阶梯
        {
            UINT16 wMaxTotalLevel;
            map<UINT32, SOneLevelInfo> mapOneLevelInfo;
            SIntensifyInfo():
                wMaxTotalLevel(0)
            {
            }
        };

        CTrumpIntensifyLoader _cIntensifyLoader;

        map<UINT16, SIntensifyInfo>         _mapID2Intensify;
        map<UINT32, STrumpIntensifyCFG*>    _mapIDLevelRank2AttrInfo;

        //新法宝强化列表
        map<UINT32, STrumpIntensifyCFG*>    _mapIDLevelEquipTrump;

};

#endif // #define TRUMP_MGR_H

