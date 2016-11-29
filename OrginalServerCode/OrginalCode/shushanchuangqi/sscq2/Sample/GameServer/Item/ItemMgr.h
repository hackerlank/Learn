
#ifndef ITEMMGR_H_
#define ITEMMGR_H_

#include "Fashion.h"
#include "StackItem.h"
#include "BagCostCFG.h"
#include "DepotCostCFG.h"
#include "IntensifyCFG.h"
#include "ArmorUpgradeCFG.h"
#include "AttachSpiritCFG.h"
#include "AttachSpiritLevelUpCFG.h"
#include "FashionCFG.h"
#include "FashionAttrCFG.h"
#include "MallCFG.h"
#include "ChongZhiCFG.h"
#include "Version.h" // for VERSION_INIT
#include "CommonDef.h"

#define MAKE_JOBLEVELEQUIPKEY(J,L,T) (((J)<<24|(L)<<16)|(T))
#define MAKE_INTENSIFYKEY(J,L) ((J)<<8|(L))
#define MAKE_ATTACHSPIRITLEVELUPKEY(J,T) ((J)<<8|(T))
#define MAKE_ZODTRUMPUPKEY(I,L) (((I)<<8)|(L))

struct SItemAttrCFGEx : public SItemAttrCFG
{
    void SetConfig(const SItemAttrCFG& rItemAttrCFG)
    {
        *(SItemAttrCFG*)this = rItemAttrCFG;
    }

    void ResetIntoVec(TVecFloat& rvecAttr)
    {
        VECATTR_RESET(rvecAttr);
        SetIntoVec(rvecAttr);
    }

    void SetIntoVec(TVecFloat& rvecAttr)
    {
        PHYATK_ADD(rvecAttr, this);
        MGCATK_ADD(rvecAttr, this);
        PHYDEF_ADD(rvecAttr, this);
        MGCDEF_ADD(rvecAttr, this);
        PHYRDC_ADD(rvecAttr, this);
        MGCRDC_ADD(rvecAttr, this);
        MAXHP_ADD(rvecAttr, this);
        SPEED_ADD(rvecAttr, this);
        HIT_ADD(rvecAttr, this);
        HITRATE_ADD(rvecAttr, this);
        DODGE_ADD(rvecAttr, this);
        DODGERATE_ADD(rvecAttr, this);
        CRITICAL_ADD(rvecAttr, this);
        CRTRATE_ADD(rvecAttr, this);
        ANTICRITCAL_ADD(rvecAttr, this);
        ANTICRTRATE_ADD(rvecAttr, this);
        BLOCK_ADD(rvecAttr, this);
        BLOCKRATE_ADD(rvecAttr, this);
        PIERCE_ADD(rvecAttr, this);
        PIERCERATE_ADD(rvecAttr, this);
        COUNTER_ADD(rvecAttr, this);
        COUNTERRATE_ADD(rvecAttr, this);
        RESIST_ADD(rvecAttr, this);
        RESISTRATE_ADD(rvecAttr, this);
        INITAURA_ADD(rvecAttr, this);
        MAXAURA_ADD(rvecAttr, this);
        CRIEXTRAADD_ADD(rvecAttr, this);
        CRIEXTRARDC_ADD(rvecAttr, this);
        METALATK_ADD(rvecAttr, this);
        WOODATK_ADD(rvecAttr, this);
        WATERATK_ADD(rvecAttr, this);
        FIREATK_ADD(rvecAttr, this);
        EARTHATK_ADD(rvecAttr, this);
        METALDEF_ADD(rvecAttr, this);
        WOODDEF_ADD(rvecAttr, this);
        WATERDEF_ADD(rvecAttr, this);
        FIREDEF_ADD(rvecAttr, this);
        EARTHDEF_ADD(rvecAttr, this);
        PHYATK_PER_ADD(rvecAttr, this);
        MGCATK_PER_ADD(rvecAttr, this);
        PHYDEF_PER_ADD(rvecAttr, this);
        MGCDEF_PER_ADD(rvecAttr, this);
        MAXHP_PER_ADD(rvecAttr, this);
        SPEED_PER_ADD(rvecAttr, this);
        HIT_PER_ADD(rvecAttr, this);
        DODGE_PER_ADD(rvecAttr, this);
        CRITICAL_PER_ADD(rvecAttr, this);
        ANTICRITCAL_PER_ADD(rvecAttr, this);
        BLOCK_PER_ADD(rvecAttr, this);
        PIERCE_PER_ADD(rvecAttr, this);
        COUNTER_PER_ADD(rvecAttr, this);
        RESIST_PER_ADD(rvecAttr, this);
        ANTIEFFECT_ADD(rvecAttr, this);
        //COUTEREXTRAADD_ADD(rvecAttr, this);
        //COUTEREXTRARDC_ADD(rvecAttr, this);
    }

    UINT32 dwPeerless;
    std::vector<UINT32> vecPassSkills;
    std::vector<SItemCount> vecLockOne; // XXX: 解锁1号位技能所需要的物品
    std::vector<SItemCount> vecLockTwo; // XXX: 解锁2号位技能所需要的物品
};

struct SItemInfo
{
	SItemCFG oItemCfg;
    SItemAttrCFGEx* pItemAttr;          // XXX: 这个指针不允许被引用或者存储
    SItemAttrCFGEx* pItemAttrActive;    // XXX: 这个指针不允许被引用或者存储，法宝需要这条
    SItemAttrCFGEx* pItemAttrExtra;     // XXX: 这个指针不允许被引用或者存储，法宝需要这条

	bool bHasOnUseItem;
	bool bHasCanUseItem;

    TSetUINT16 setEquipConflict;      // 法宝互斥
    TSetUINT16 setEquipConflictTeam;  // 队伍法宝互斥

	SItemInfo() : pItemAttr(NULL), pItemAttrActive(NULL), pItemAttrExtra(NULL), bHasOnUseItem(false), bHasCanUseItem(false) { }
};

struct SItemTimeInfo
{
	SItemTimeCFG oTimeCfg;
	time_t tExpireTime;

	SItemTimeInfo() : tExpireTime(0) { }
};

struct SChongZhiCFGEx : public SChongZhiCFG
{
    void SetConfig(const SChongZhiCFG& rChongZhiCFG)
    {
        *(SChongZhiCFG*)this = rChongZhiCFG;
    }
    TVecItemGenInfo _vecItemAward;
};

class CItemMgr
{
public:
    static bool Init();
    static bool ReLoadConfig(const string &);
    static bool LoadConfig(bool bReLoad = false);

    static CItemPtr CreateAllTypeItem(UINT16 dwItemID, UINT16 wNum = 1, UINT8 byQuality = 0);
    static CItemPtr CreateAllTypeEmptyItem(UINT16 wItemID);
    static CItemPtr CreateItem(UINT16 wItemID, UINT16 wNum = 1, UINT8 byQuality = 0);
    static CItemPtr CreateItem(const SItem& rItemStream);
    static CItemPtr CreateEmptyItem(UINT16 wItemID, UINT16 wNum = 1);
    static CStackItemPtr CreateEmptyStackItem(UINT16 wItemID);
    static CFashionPtr CreateFashion(UINT16 wItemID, UINT8 byQuality = 0);
    static CFashionPtr CreateEmptyFashion(UINT16 wItemID);
    static CCittaPtr CreateCitta(UINT16 wItemID, UINT32 dwSignetID = 0);
    static CCittaPtr CreateEmptyCitta(UINT16 wItemID);
    static CTrumpPtr CreateTrump(UINT16 wItemID);
    static CTrumpPtr CreateEmptyTrump(UINT16 wItemID);
    static CGemstonePtr CreateGemstone(UINT16 wItemID);
    static CGemstonePtr CreateEmptyGemstone(UINT16 wItemID);
    static CEquipTrumpPtr CreateEquipTrump(UINT16 wItemID);
    static CEquipTrumpPtr CreateEmptyEquipTrump(UINT16 wItemID);

    static bool AssignItemProp(CItem& rItem, UINT8 byQuality = 0);
    static bool AssignFashionProp(CFashion& rEquip, UINT8 byQuality = 0);
    static bool AssignCittaProp(CCitta& rCitta, UINT32 dwSignetID = 0);
    static bool AssignTrumpProp(CTrump& rTrump);

    //不同容器间交换
    static bool TransferStoreItem(CStore& rFromStore, CStore& rToStore, CItem& rFromItem, INT16 wFromIndex, CItem& rToItem, INT16 wIndex);
    //不同容器间堆叠
    static bool MergeStackItem(CStore& rFromStore, CStore& rToStore, CItem& rFromItem, CItem& rToItem);

    static SItemInfo* GetItemConfig(UINT16 wItemID);
    static SItemTimeCFG* GetItemTimeConfig(UINT16 wTimeID);
    static SItemAttrCFGEx* GetItemAttrConfig(UINT16 wAttrID);
    static SBagCostCFG* GetBagCost(UINT16 wIdx);
    static SDepotCostCFG* GetDepotCost(UINT16 wIdx);
    static SIntensifyCFG* GetIntensifyConfig(UINT8 byJob, UINT8 byType, UINT8 byLevel);
    static SFashionCFG* GetFashionConfig(UINT8 byLevel);
    static SFashionAttrCFG* GetFashionAttrConfig(UINT16 wItemID, UINT8 byLevel);

    static bool AppendAttr2(UINT16 wAttrID, TVecFloat& rvecAttr);

    static UINT8 FashionExpToLevel(UINT32 dwExp);
    static UINT32 LevelToFashionExp(UINT8 byLevel);
    static bool FashionTestLevelUp(UINT8& byLevel, UINT32& dwExp);
    static UINT8 GetFashionLevelMax();

    static bool LoadMallCfg(string& strPath);
    static bool LoadChongZhiCfg(string& strPath);
    static const std::vector<SMallCFG>* GetMallCfg(UINT8 byType);
    static const SMallCFG* GetMallCFG(UINT8 byType,UINT32 dwInstID);
    static float GetGoldPrice(UINT16 wItemID);
    static SChongZhiCFGEx* GetChongZhiCfg(UINT16 wGoldID);
    static bool GetUpdateMaterial(UINT16 wItemId,map<UINT16,UINT32>  &mapMaterial);

    static TSetUINT16& GetConflictID(UINT16 wItemID);
    static TSetUINT16& GetTeamConflictID(UINT16 wItemID);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

private:
    static bool LoadItemConfig(const SItemCFG& rItemCfg, bool bReload = false);
    static UINT64 _qwVersion;

private:
    static map<UINT16, SItemInfo> _mapID2ItemInfo;
    static map<UINT16, SItemTimeInfo> _mapID2TimeInfo;
    static map<UINT16, SItemAttrCFGEx> _mapID2ItemAttrInfo;
    static map<UINT16, SBagCostCFG> _mapID2BagCostCfg;
    static map<UINT16, SDepotCostCFG> _mapID2DepotCostCfg;
    static map<UINT32, SIntensifyCFG> _mapJobLevel2IntensifyCfg;
    static vector<SFashionCFG> _vecLevel2FashionExp;
    static map<UINT16, std::vector<SFashionAttrCFG>> _mapIDLevel2FashionAttr;
    static map<UINT8, std::vector<SMallCFG>> _mapMallType2MallCfg;
    static map<UINT8, SChongZhiCFGEx> _mapID2ChongZhiCfg;
    static map<UINT16,map<UINT16,UINT32> > _mapUpgrade;
};

#endif // ITEMMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

