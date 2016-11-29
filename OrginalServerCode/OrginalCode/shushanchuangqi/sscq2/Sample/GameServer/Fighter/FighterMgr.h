
#ifndef FIGHTERMGR_H_
#define FIGHTERMGR_H_
#include <memory>
#include <algorithm>
#include "ProtoCommon.h" // XXX: for TVecFtAttrMod
#include "FormationProt.h" // XXX: for EBeastSoulType
#include "Fighter.h"
#include "FighterPropCFG.h"
#include "FighterCuiTiCFG.h"
#include "FormationCFG.h"
#include "PetCFG.h"
#include "PetLevelCFG.h"
#include "ItemMgr.h"
#include "FighterLvAttrCFG.h"
#include "FighterStarCFG.h"
#include "FighterStarGrowthCFG.h"
#include "DujieTemplateCFG.h"
#include "XinfaCFG.h"
#include "XinfaEffectCFG.h"
#include "StarPageCFG.h"
#include "StarSoulCFG.h"
#include "GameServerLog.h"
#include "FighterCombinationCFG.h"
#include "FighterCombinationEffectCFG.h"

using namespace NProtoCommon;
using namespace NFormationProt;

#define HEROCUITI_KEY(S, F) (((S)<<16)|(F))
#define FIGHTERSTAR_KEY(I, S) (((I)<<16)|(S))
#define HEROCOMBINATION_KEY(I, S) (((I)<<16)|(S))

struct SFighterPropCFGEx : public SFighterPropCFG
{
    SFighterPropCFGEx() : _bIsTaskFighter(false) {}
    void SetConfig(const SFighterPropCFG& rFighterPropCFG)
    {
        _bIsTaskFighter = false;
        *(SFighterPropCFG*)this = rFighterPropCFG;
    }

    TVecUINT32 _vecSkillID;
    vector<TVecUINT32> _vecSkillIDEx;
    TVecUINT32 _vecNormalAttackEx;
    TVecUINT16 _vecBuffID;
    TVecUINT32 _vecPeerless;
    TVecUINT32 _vecPassive;
    TVecUINT16 _vecXinFaID;
    bool _bIsTaskFighter;
};

struct SFormationCFGEx : public SFormationCFG
{
    void SetConfig(const SFormationCFG& rFormationCFG)
    {
        *(SFormationCFG*)this = rFormationCFG;
    }

    bool IsValidPos(UINT8 byPos)
    {
        auto itr = find(vecPos.begin(),vecPos.end(),byPos);
        return itr != vecPos.end();
    }

    //TVecFtAttrMod vecAttr; // 解锁属性加成
    TVecUINT8 vecPos; // 开放的位置
};

struct SPetCFGEx : public SPetCFG
{
    void SetConfig(const SPetCFG& rPetCFG)
    {
        *(SPetCFG*)this = rPetCFG;
    }

    //TVecFtAttrMod vecAttr; // 解锁属性加成
};

struct SDujieTemplateCFGEx : public SDujieTemplateCFG
{
    void SetConfig(const SDujieTemplateCFG& rDujieCFG)
    {
        *(SDujieTemplateCFG*)this = rDujieCFG;
    }
    TVecUINT8 _vecActiveUnlock;
    TVecUINT8 _vecPassiveUnlock;
    TVecFloat _vecAddAttr;
};

struct SBeastSoulLevelConfig : public SStarSoulCFG
{
    void SetConfig(const SStarSoulCFG& rCFG)
    {
        *(SStarSoulCFG*)this = rCFG;
    }
};

struct SBeastSoulItemAward
{
	UINT16 wItemID; //道具ID
	UINT32 dwCount; //道具个数
	SBeastSoulItemAward():
        wItemID(0), dwCount(0)
    {
    }
	SBeastSoulItemAward(UINT16 wItemID, UINT32 dwCount):
        wItemID(wItemID), dwCount(dwCount)
    {
    }
};
typedef std::vector<SBeastSoulItemAward> TVecBeastSoulItemCount;

struct SBeastSoulRankConfig : public SStarPageCFG
{
    SBeastSoulRankConfig():
        _byMaxLevel(0)
    {
    }
    void SetConfig(const SStarPageCFG& rCFG)
    {
        *(SStarPageCFG*)this = rCFG;
    }

    vector<SBeastSoulLevelConfig*> _vecLevelConfig;
    TVecBeastSoulItemCount _vecAward;    // 全部激活后的奖励
    UINT8 _byMaxLevel;
};

struct SBeastSoulCFG
{
    vector<SBeastSoulRankConfig*> _vecRankConfig;
    UINT8 _byMaxRank;
    SBeastSoulCFG():
        _byMaxRank(0)
    {
    }
};

struct SFighterCombinationCFGEx : public SFighterCombinationCFG
{
    void SetConfig(const SFighterCombinationCFG& rFighterCombinationCFG)
    {
        *(SFighterCombinationCFG*)this = rFighterCombinationCFG;
    }
    TVecUINT16 _vecFighterID;
};

struct SFighterCombinationEffectCFGEx : public SFighterCombinationEffectCFG
{
    void SetConfig(const SFighterCombinationEffectCFG& rFighterCombinationEffectCFG)
    {
        *(SFighterCombinationEffectCFG*)this = rFighterCombinationEffectCFG;
    }
};

class CFighterMgr
{
public:
    static bool Init();
    static bool LoadConfig(bool bReload = false);
    static bool ReLoadConfig(const string &);
    static UINT16 GetDefaultFighterID(UINT8 byJob, ESexType eSex);
    static const string GetFighterName(UINT16 wFighterID);
    static CFighterPtr Create(UINT16 wFighterID, bool bGenGUID = true, const CUserPtr& pUser = NULL);
    static CFighterPtr Create(const SFighterDBInfo& rFighterDBInfo, const CUserPtr& pUser = NULL);
    static bool IsMainFighter(SFighterPropCFG& rFighterPropCFG);
    static bool IsHeroFighter(SFighterPropCFG& rFighterPropCFG);
    static bool IsMonsterFighter(SFighterPropCFG& rFighterPropCFG);
    static bool IsWorldBossFighter(SFighterPropCFG& rFighterPropCFG);
    static bool IsMonsterOrWorldBossFighter(SFighterPropCFG& rFighterPropCFG);

    // XXX: Pet
    static SPetLevelCFG* GetPetLevelCfg(UINT16 wPetID, UINT8 byPetLevel);

    static SFighterPropCFGEx* GetFighterPropCfg(UINT16 wFighterID);
    static SFighterLvAttrCFG* GetFighterLvAttrCfg(UINT16 wFighterID);
    static SFighterCuiTiCFG* GetFighterCuiTiCfg(UINT8 byType, UINT8 byLevel);
    static SFormationCFGEx* GetFormationCfg(UINT16 wFormationID);
    static SPetCFGEx* GetPetCfg(UINT16 wPetID);
    static SFighterStarCFG* GetFighterStarCfg(UINT8 byInclination, UINT8 byStar);
    static SFighterStarGrowthCFG* GetFighterStarGrowthCfg(UINT8 byStar);
    static SDujieTemplateCFGEx* GetDujieCFG(UINT8 byTemplateID, UINT8 byLevel);
    static bool IsDujieMaxLevel(UINT8 byTemplateID, UINT8 byLevel);
    static UINT8 GetDujieLvlByExp(UINT8 byTemplateID, UINT32 dwExp);
    static UINT8 GetDujieMaxLevel(UINT8 byTemplateID);
    static const SXinfaCFG* GetXinFaCfg(UINT16 wXinFaID);
    static const SXinfaEffectCFG* GetXinFaLevelCfg(UINT16 wXinFaID, UINT8 byXinFaLevel);

    static const SBeastSoulLevelConfig* GetBeastSoulLevelCFG(EBeastSoulType eType, UINT8 byRank, UINT8 byLevel);
    static const SBeastSoulRankConfig* GetBeastSoulRankCFG(EBeastSoulType eType, UINT8 byRank);
    static SFighterCombinationCFGEx* GetFighterCombinationCFG(UINT8 byGroupID);
    static SFighterCombinationEffectCFGEx* GetFighterCombinationEffectCFG(UINT8 byGroupID, UINT8 byGroupLvl);
    static bool IsMaxCombinationLevel(UINT8 byGroupID, UINT8 byGroupLevel);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新

    static IBattleFighterPtr CreateFromID(UINT16 wFighterID);

private:
    static bool LoadDujieTemplate(bool bReload, string strPath);

private:
    static UINT64 _qwVersion;

private:
    static map<UINT16, SFighterPropCFGEx> _mapID2FighterPropCFG;
    static map<UINT32, SFighterCuiTiCFG> _mapTypeLevel2CuiTiCFG;
    static map<UINT16, SFormationCFGEx> _mapID2FormationCFG;
    static map<UINT16, SPetCFGEx> _mapID2PetCFG;
    //宠物
    static map<UINT16, std::map<UINT8, SPetLevelCFG>> _mapID2PetLevelCFG;
    /*static map<UINT16, SPetLevelCFG> _mapID2PetLevelCFG; // XXX: 宠物升级配置
    static vector<SPetLevelCFG> _vecPetLevel2Exp;*/
    //主将天赋
    static map<UINT16, SFighterLvAttrCFG> _mapID2FighterLvAttrCFG;
    static map<UINT32, SFighterStarCFG> _mapIDnStar2AttrStar;
    static map<UINT32, SFighterStarGrowthCFG> _mapStar2Growth;
    static map<UINT8, vector<SDujieTemplateCFGEx*>> _mapID2DujieCFG;
    //心法
    static map<UINT16, SXinfaCFG> _mapID2XinFaCFG; //学习心法配置
    static map<UINT16, std::map<UINT8, SXinfaEffectCFG>> _mapID2XinFaLevelCFG; //心法升级配置
    static map<EBeastSoulType, SBeastSoulCFG> _mapType2BeastSoulCFG;
    //散仙组合
    static map<UINT8, SFighterCombinationCFGEx> _mapID2FighterCombinationCFG;
    static map<UINT32, SFighterCombinationEffectCFGEx> _mapID2FighterCombinationEffectCFG;
    static map<UINT32, UINT8> _mapCombSkillID2GroupID;
};

#endif // FIGHTERMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

