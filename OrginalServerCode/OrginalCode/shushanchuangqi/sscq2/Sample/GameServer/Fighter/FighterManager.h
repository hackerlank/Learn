
#ifndef FIGHTERMANAGER_H_
#define FIGHTERMANAGER_H_

#include "Fighter.h"
#include "FighterProt.h"
#include "FighterSlots.h"
#include "FormationPet.h"
#include "FighterMgr.h"
#include "BattlePoint.h"
#include "HeroFighterCombinationSlots.h"
#include "BoostOwner.h"
#include "FashionSlots.h"
#include "TrumpSlots.h"
#include "CittaSlots.h"
#include "FightFormation.h"
#include "Formation.h"
#include "Draw.h"


using namespace NFighterProt;
using namespace NFightFormation;

class CUser;

enum ECombEquipToType   //XXX 连携技能在各功能中的装备类型
{
    eCombEquipToLineUp      = 1,
    eCombEquipToEMei        = 2,
    eCombEquipToTeam        = 3,
    eCombEquipToZhanQi      = 4, //秘境寻宝
};

class CFighterManager : public CBoostOwner
{
public:
    CFighterManager(CUser& rUser);
    virtual ~CFighterManager();

    CUserPtr GetUserPtr();

    bool InitDefaultFashion();
    CFighterPtr GetMainFighter() const { return _oFighterSlots.GetMainFighter(); }
    CFighter * GetpMainFighter() {return GetMainFighter().get();}

    CFighterPtr GetFighterByInstID(UINT64 qwFighterID) { return _oFighterSlots.GetFighterByInstID(qwFighterID); } 
    CFighter * GetpFighterByInstID(UINT64 qwFighterID) { return GetFighterByInstID(qwFighterID).get();}

    CFighterPtr GetFighterByID(UINT16 wFighterID) { return _oFighterSlots.GetFighterByID(wFighterID); }
    CFighter* GetpFighterByID(UINT16 wFighterID) { return GetFighterByID(wFighterID).get(); }

    bool HasFighter(UINT16 wFighterID) { return _oFighterSlots.HasFighter(wFighterID); }
    bool HasRecruitFighter(UINT16 wFighterID) { return _oFighterSlots.HasRecruitFighter(wFighterID); }

    UINT16 GetHeroNum();
    CFighterSlots& GetFighterSlots() { return _oFighterSlots; }
    CFormationPet& GetFormationPet() { return _oFormationPet; }
    CHeroFighterCombinationSlots& GetHeroFighterCombinationSlots() { return _oHeroCombinationSlots; }
 
    //LogServer日志
    void WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID);

    // 招募相关
    void NotifyFighterInfo(const CFighterPtr& pFighter);
    void RecruitNotify(CFighterPtr& pFighter, bool bNew);
    ERecruitResult Recruit(UINT16 wFighterID);
    bool GetFighterForce(UINT16 wFighterID);

    /*****散仙组合相关*****/
    void ResetCombinationSkill(const TVecUINT16& rvecFighterID, ECombEquipToType eType, bool bInBattle = true);
    void ResetCombinationSkill();
    void EquipToCombinationSkillAfterLoadDB();
    //激活散仙组合
    ECombinationResult ActiveCombination(UINT8 byGroupID);
    //升级散仙组合
    ECombinationResult UpgradeCombination(UINT8 byGroupID, bool bOneKey, SFighterCombination& oCombinationInfo);
    //装备散仙组合技能(连携技)
    ECombinationResult EquipToCombinationSkill(UINT8 byGroupID, UINT8 byType, TVecUINT16& rvecFighterID);
    UINT32 GetCombinationSkill(ECombEquipToType eType);
    void SetCombinationSkill(ECombEquipToType eType, UINT32 dwSkillID);

    UINT64 GetBattleFighters(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType=EBTINVALID);
    
    //散仙购买
    EFighterBuyResult FighterBuy(UINT16 wFighterID);
    
    //获取战斗信息
    std::string  GetInfoLog();

    IBattleFighterPtr GetPetFighter(const TVecFloat& vecAttr);
    bool GetAllFighters(TVecFighterPtr& rvecFighters);
    bool GetTeamFighters(TVecFighterPtr& rvecFighters);
    void SetTeamFighters(const TVecUINT16& rvecFighterID, const TVecUINT8& rvecPos);
    UINT32 GetFightersCurrHP();
    UINT32 GetFightersMaxHP();
    UINT32 GetFightersMaxHP2();
    void RegenAllHP();  //恢复满血
    bool RecoverFighters(TVecBattleFighterPtr& vecBattleFighter);
    void AddFightersCurrHP(UINT32 dwHP);
    void AddFightersCurrHPPer(float fFactor);

    void ToStream(TVecFighterSpecInfo& vecFighters);
    bool AddFighterFromDB(CFighterPtr& pFighter);
    void Update2DB();
    void LoadSceneFromDB();

    // 玩家属性相关
    void SetDirty(EAttrGroupType eType) ;
    void SetDirty(EAttrGroupType eType, const TVecFloat& vecAttr) ;
    bool IsDirty(EAttrGroupType eType) const   ;

    TVecFloat GetAllAttr() const;
    TVecFloat GetGroupAttr(EAttrGroupType eType) const;

    bool RebuildGroupAttr() const;

    void FighterInitLevelAttr();
    void AddExp(UINT64 qwExp, bool bNotify = true);
    void AddToLevel(UINT16 wLevel);
    void GetRecruitedFigterIDList(TVecUINT16& vecFighterID);

    bool FindHeroFighterSkillAndTrump(UINT32 skillOrTrumpID);
    //获取增加到主将的属性
    void GetPlayerAddAttr(TVecFloat&  vecAttr);

    //获得增加到所有单位的属性
    void GetHeroAndPlayerAddAttr(TVecFloat&  vecAttr);
    void GetHeroAndPlayerAddAttrWithoutBuffer(TVecFloat&  vecAttr);

    //获取增加到散仙的属性
    void GetHeroAddAttr(TVecFloat&  vecAttr);

    UINT32 GetBattlePoint();
    UINT32 GetHeroFighterBattlePoint(UINT16 wFighterID);
    UINT32 CalcHeroFighterBattlePoint();
    UINT32 GetBeautyBattlePoint();
    UINT32 GetTrumpBattlePoint();
    UINT32 GetTrumpAttrBattlePoint();
    UINT32 GetTrumpSkillBattlePoint();
    UINT32 GetHorseBattlePoint();
    UINT32 GetDujieBattlePoint();
    UINT32 GetXinfaBattlePoint();
    UINT32 GetGuildBattlePoint();
    UINT32 GetBufferBattlePoint();

    void   UpdateHeroFighterRankInfo();

    void   FormationBoost(UINT32 dwMode);
    void   RobotFormationBoost(UINT32 dwMode);
    void   FormationSuper();
    void   HeroFighterBoost(UINT32 dwMode);
    void   HeroFighterSuper();

    void SetBattleType(EBattleType eBattleType) { _eBattleType = eBattleType; }
    EBattleType GetBattleType(){ return _eBattleType ; }

    void GetDefaultFightFormation(FightFormationInfo& rFightFormationInfo);

    virtual void SuperBoostObjects();

    CFashionSlots&  GetFashionSlots();
    const CFashionSlots&  GetFashionSlots() const;
    CTrumpSlots&    GetTrumpSlots();
    const CTrumpSlots&    GetTrumpSlots() const;
    CCittaSlots&    GetCittaSlots();
    const CCittaSlots&    GetCittaSlots() const;

    CDraw& GetDraw();

    CFormation&  GetFormation() { return _oFormation; }

    void OnFighterColorChange(UINT8 byNewcolor);

    CEquipTrumpPtr GetEquipTrumpByInstID(UINT64  qwInstID);

    //获取一定条件的法宝数量
    UINT32 GetEquipTrumpCount(UINT8 byMinQuality,UINT8 byMinInsifyLevel);

    //获取一定条件的宝石数量
    UINT32 GetStoneCount(UINT8 byMinLevel);

private:
    bool RebuildGroupAttr(EAttrGroupType eType) const;

private:
    CUser&                          _rUser;
    CFighterSlots                   _oFighterSlots; //所有见过面的将 [0] 是主将
    CFormationPet                   _oFormationPet; // 阵灵 XXX: 阵灵与队伍是互斥的
    CFormation                      _oFormation;    //阵型
    CHeroFighterCombinationSlots    _oHeroCombinationSlots;  //散仙组合

    mutable map<EAttrGroupType, bool>       _mapAttrGroupDirty; // 不同功能是否需要更新新的属性
    mutable map<EAttrGroupType, TVecFloat>  _mapAttrGroup;      // 不同功能对应的属性加成

    mutable map<EAttrGroupType, TVecFloat>  _mapAttrGroupCache; // 不同功能对应的属性加成(从Center来的临时存)

    EBattleType _eBattleType;

    CCittaSlots             _oCittas;       // 心法栏
    CTrumpSlots             _oTrumps;       // 法宝栏
    CFashionSlots           _oFashions;     // 时装栏

    CDraw                   _oDraw;         // 求签数据

    UINT32 _dwCombineSkillIDTeam;       // 散仙组队上装备的连携技能ID
    UINT32 _dwCombineSkillIDLineUp;     // 散仙阵型上装备的连携技能ID
    UINT32 _dwCombineSkillIDEMei;       // 守卫峨眉上装备的连携技能ID

};

#endif // FIGHTERMANAGER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

