#ifndef _BATTLE_FIGHTER_H_
#define _BATTLE_FIGHTER_H_

#include "ProtoCommon.h"

#include "Battle.h"

#include "BattleTypeDef.h"
#include "BattleGS.h"
#include "BattleSkill.h"

namespace NBattle
{
using namespace NBattleGS;
using namespace NProtoCommon;

// =====================================================================================
//        Class:  CBattleFighter
//  Description:  战斗对象
// =====================================================================================
class CBattleFighter : public IBattleFighter, public enable_shared_from_this<CBattleFighter>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBattleFighter ();                             // constructor //
        virtual ~CBattleFighter();

        // ====================  ACCESSORS     ======================================= //

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //

        virtual bool InitFighter(const SBFInfo& rBFInfo);
        virtual bool InitFighterAttr(const TVecFloat& rvecFighterAttr);
        virtual bool InitFighterBattleInfo(UINT32 dwHpMax, UINT32 dwHp, UINT32 dwAura, UINT32 dwAuraMax);
        virtual bool SetFighterAttr(UINT8 byIndex, FLOAT fValue);

        // 设置战斗对象技能
        virtual bool InitFighterSkills(const TVecUINT32& rvecAllSkills, UINT32 dwNormalAttack = 0);

        virtual bool PushMoreSkills(const TVecUINT32& rvecSkills);

        virtual bool InitFighterSkillsEx(const std::vector<TVecUINT32>& rvecvecAllSkills, const TVecUINT32& vecNormalAttack);

        virtual bool InitFromInfo(const SBattleFighter& rBF, ::TVecBattleFighterPtr& rvecBattleFighterSummon);

        virtual UINT32 RegenAllHP();
        virtual void   SetPos(INT32 dwPos);
        virtual UINT16 GetID()       const;
        virtual UINT8  GetColour() const;
        virtual UINT8  GetQuality() const;
        virtual INT32  GetPos()      const;
        virtual void   SetLevel(UINT32 dwLevel);
        virtual UINT32 GetHP() const;
        virtual UINT16 GetLevel() const;

        UINT64 GetInstID() const;

        bool SummonFromAnother(CBattleFighterPtr pFighter, UINT32 dwParam, CBattleFighter* pFighterOrigin);
        bool GetSummonFighterID(TSetUINT16& rsetFighterID);
        void GetBattleFighterInfo(SBattleFighter& sBF) const;

        bool   IsPhyJob()            const;
        bool   IsMgcJob()            const;
        const  string& GetName()     const;

        UINT8  GetIndex()            const;
        UINT8  GetGroupID()          const;
        UINT8  GetField()            const;
        UINT8  GetSide()             const;
        UINT8  GetTeamID()           const;

        SFeatureBasePtr GetFeature();

        void   SetSide(UINT8 bySide);
        void   UpdateIndex();
               
        FLOAT  GetAttr(EFighterAttr eIdx) const;
        FLOAT  GetAttrExtra(EFighterAttr eIdx) const;
        FLOAT  GetAttrFinal(EFighterAttr eIdx) const;
        FLOAT  GetSpeed() const;

        FLOAT  GetAttack() const;

        void   AddAura(UINT32 dwAura);
        void   SubAura(UINT32 dwAura);
        void   SetAura(UINT32 dwAura);
        UINT32 GetAura() const;
        UINT32 GetMaxAura() const;

        UINT32 MakeDmg(UINT32 dmg);
        UINT32 MakeShieldDmg(UINT32& dmg, TVecUINT32& rvecBuffKey);
        UINT32 RegenHP(UINT32 rhp);
        void   SetHP(UINT32 dwHP);
        void   SetMaxHP(UINT32 dwMaxHP);
        UINT32 GetHPP() const;
        UINT32 GetLostHPP() const;
        UINT32 GetMaxHP() const;

        UINT32 GetBattlePoint() const;
        UINT32 GetAttrBattlePoint() const;
        UINT32 GetSkillBattlePoint() const;

        UINT32 LaunchActiveSkill(TVecBattleSkillEffect& vecEfOut, bool bForceNormal, bool bNoPeerless, ESkillLaunchType& eType, TVecUINT16& rvecProb);
        UINT32 LaunchNormalAttack(TVecBattleSkillEffect& vecEfOut, TVecUINT16& rvecProb);
        UINT32 LaunchBeautySkill(TVecBattleSkillEffect& vecEfOut, TVecUINT16& rvecProb);

        void   ReadyForNextSkill();

        bool   TryToggleSkills(UINT8 byIndex);

        bool   CanCounter() const;

        bool   CheckEffectMaxCount(UINT32 dwSkillID, FLOAT fValue) const;
        void   SetEffectParam(UINT32 dwSkillID, FLOAT fValue);
        void   AddEffectParam(UINT32 dwSkillID, FLOAT fValue);
        FLOAT  GetEffectParam(UINT32 dwSkillID) const;
        void   ClearEffectParam();
        void   ResetTurnCD();
        bool   IsAuraGainDisabel() const;

        const TVecTeamSkillInfo& GetCombineSkill(UINT8& rIndex);

        // Buff相关类型成员方法

        void         ResetBuff();

        void         ResetPassiveSkillCD();

        bool         CheckAddBattleBuff(CBattleBuff& rBuff, UINT32& rBuffKeyToRemove);
        bool         AddBattleBuff(CBattleBuff& rBuff);

        bool         RemoveBattleBuff (TSetUINT32 setBufID);
        bool         RemoveBattleBuff (UINT32 dwBuffID);
        UINT32       ReduceBattleBuff (UINT32 dwBuffID);

        bool         GetReleaseBuffID(UINT32 dwBuffID);
        void         GetReleaseBuffID(TVecUINT32& rvecBUffID);

        void         ReleaseCD(UINT32 dwBuffID);
        void         ReleaseCD();
        void         ReleaseBuff();
                     
        bool         HaveState(EBStateBuffType eBStateBuffType) const;
        FLOAT        GetStateValue (EBStateBuffType) const;
        bool         GetStateBuffID( EBStateBuffType eBStateBuffType, TSetUINT32& rsetBuffID);
                     
        bool         AddBuffCondCount(UINT32 dwBuffID, UINT32 dwBuffIDEX, CBattleFighter* pBF);
        bool         AddBuffOutCondCount(UINT32 dwBuffID, UINT32 dwBuffIDEX, CBattleFighter* pBF);
                     
        void         GetAllBuffID(TSetUINT32& rsetBuffID);
        bool         HasStateBuff(EMachineState eMachineState) const;
        TVecUINT32&  GetCondBuffID(EMachineState eMachineState);
        TVecUINT32&  GetOutCondBuffID(EMachineState eMachineState);
        bool         GetBuffWithState(UINT32 dwBuffID, CBattleBuff& rBuff);
        bool         HaveBuff(UINT32 dwBuffID) const;
        bool         GetBuff(UINT32 dwBuffID, CBattleBuff& rBuffOut);
        bool         GetBuffData(UINT32 dwBuffID, CBattleBuff& rBuffOut);
        CBattleBuff& GetBuffData(UINT32 dwBuffID, bool& bRet);

        FLOAT        GetStateFactor(EBStateBuffType eBStateBuffType) const;
        FLOAT        GetResistFactor(EResistType eType) const;

        bool         IsHide() const;
        bool         IsControled() const;

        bool         IsPassiveSkillID(UINT32 dwSkillID) const;
                     
        void         GetDebuffCanClear(TVecUINT32& rvecBuffID, EResistType eType) const;
                     
        UINT8        GetSummonLast() const;
        void         SetSummonLast(UINT8 bySumonLast);
        bool         RemoveStateValue(EBStateBuffType eBStateBuffType);

        UINT32       GetBuffResist() const;
        void         SetBuffResist(UINT32 dwBuffID);

    private:
        // ====================  METHODS       ======================================= //
         
        bool         InitNormalAttack(UINT32 dwNormalAttack);
        bool         InitActiveSkill(const TVecUINT32& rvecActiveSkill, UINT32 dwPeerless);
        bool         InitSymbolSkill(const TVecUINT32& rvecSymbolSkill);
        bool         InitPassiveSkill(const TVecUINT32& rvecPassiveSkill);

        bool         ClearPassiveSkillBuff();

        void         InitSkillInfo();
        void         ClearSkillInfo();

        bool         InitPassiveSkillBuff();
        bool         InitCombineSkill();
        bool         AddPassiveSkillBuff(const CBattleBuff& rBuff);

        void         SyncSkillsToSkillsEx();

        // 输出当前正在使用的一套技能
        void         DumpCurrentSkills() const;
        // 输出所有技能
        void         DumpAllSkills() const;

        // Buff相关类型成员方法
        bool   CheckTryAddStateValue (CBattleBuff& rBuff, UINT32& rBuffKeyToRemove);

        bool   TryAddStateValue (CBattleBuff& rBuff);
        UINT32 TrySubStateValue (CBattleBuff& rBuff, bool bReduce);

        bool   CheckAddStateValue  (CBattleBuff& rBuff, UINT32& rBuffKeyToRemove);
        bool   AddStateValue  (CBattleBuff& rBuff);
        
        bool   SubStateValue  (EBStateBuffType eBStateBuffType, FLOAT fValue, TVecUINT32& rvecBuffKey);
        UINT32 SubStateValue  (CBattleBuff& rBuff, bool bReduce);

        UINT32 ClearState     (EBStateBuffType eBStateBuffType);

        bool   AddStateFactor (CBattleBuff& rBuff);
        bool   SubStateFactor (CBattleBuff& rBuff, bool bReduce);

        bool   AddResistFactor (CBattleBuff& rBuff);
        bool   SubResistFactor (CBattleBuff& rBuff, bool bReduce);

        bool   CheckCondValue(const TVecUINT32& rvecCondValue, EMachineState eMachineState, 
                bool bOut, UINT32 dwBuffID, UINT32 dwBuffIDEX, CBattleFighter* pBF);
        void   UpdateCondValue(UINT32 dwBuffID, bool bOut);
               
        bool   CheckAddAttrBuff(CBattleBuff& rBuff, UINT32& rBuffKeyToRemove, EFighterAttr eAttrTypeSrc);
        bool   AddAttrBuff(CBattleBuff& rBuff, EFighterAttr eAttrTypeSrc);
        UINT32 SubAttrBuff(CBattleBuff& rBuff, bool bReduce);

        void   AddBuffMap(CBattleBuff& rBuff);
        void   RemoveBuffMap(CBattleBuff& rBuff);
                     

        // ====================  DATA MEMBERS  ======================================= //

        // Buff相关的类型定义
        typedef std::map<UINT32, CBattleBuff>       TMapBuff;       // <BuffID, cBuff>

        typedef std::vector<TVecUINT32>             TVecBuffCond;   // 下标为条件

        typedef std::set<EBStateBuffType>               TSetBuffType;
        typedef std::vector<FLOAT>                      TVecStateValue;
        typedef std::vector<FLOAT>                      TVecStateFactor;
        typedef std::vector<FLOAT>                      TVecResistFactor;
        typedef std::vector<TSetUINT32>                 TVecStateID;

        typedef std::map<UINT32, FLOAT>     TMapEffectParam;


        SBattleFighterInfo  _oFighterInfo;      // 协议用战斗对象信息

        UINT8 _byIndex;
        UINT8 _byGroupID;
        UINT8 _byField;
        UINT8 _bySide;

        TVecFloat  _vecAttrBase;          // 战斗基础属性
        TVecFloat  _vecAttrExtra;         // 从Buff获得的属性

        TVecUINT32 _vecPassiveSkill;               // 被动技能
        TSetUINT32 _setPassiveEffectID;            // 被动技能效果ID
        UINT32     _dwActiveSkill[MAX_SKILL_POS];  // 主动
        UINT32     _dwActiveSymbol[MAX_SKILL_POS]; // 主动（技能符文）
        UINT32     _dwPeerless;                    // 无双 
        UINT32     _dwPlSymbol;                    // 无双（技能符文）
        UINT32     _dwNormalAtk;                   // 平砍

        UINT8      _dwActiveSkillIdx;              // 当前已经使用的技能索引

        // 技能相关成员变量
        // 0号位为当前技能，后面的为可以切换的技能
        TVecUINT32         _vecNormalAttack;         // 平砍
        std::vector<TVecUINT32> _vecvecPassiveSkill; // 被动技能
        std::vector<TVecUINT32> _vecvecActiveSkill;  // 主动技能
        std::vector<TVecUINT32> _vecvecSymbol;       // 主动技能符文
        TVecUINT32         _vecPeerless;             // 无双技能

        TVecUINT32 _vecPassiveSkillEx;               // 被动技能
        TSetUINT32 _setPassiveEffectIDEx;            // 被动技能效果ID
        UINT32     _dwActiveSkillEx[MAX_SKILL_POS];  // 主动
        UINT32     _dwActiveSymbolEx[MAX_SKILL_POS]; // 主动（技能符文）
        UINT32     _dwPeerlessEx;                    // 无双 
        UINT32     _dwPlSymbolEx;                    // 无双（技能符文）
        UINT32     _dwNormalAtkEx;                   // 平砍

        TVecTeamSkillInfo _vecCombineSkill;          // 组合技能

        bool       _bCanToggleSkills;                // 是否可以切换技能

        TMapEffectParam _mapEffectParam;        // 技能效果相关保存变量 map<UINT32, FLOAT>
        UINT32     _dwBuffResist;               // 临时可以抵抗的Buff

        // Buff相关类型成员变量
        TVecStateValue    _vecStateValue;   // 玩家Buff状态的具体值
        TVecStateFactor   _vecStateFactor;  // 玩家Buff状态的修正参数
        TVecResistFactor  _vecResistFactor; // 玩家抵抗修正参数
        TVecStateID       _vecStateID;      // EBStateBuffType<TSetUINT32>
        TMapBuff          _mapBuff;         // <UINT32, CBattleBuff>

        TVecBuffCond      _vecBuffCond;     // EMachineState<TVecUINT32> 
        TVecBuffCond      _vecBuffOutCond;  // EMachineState<TVecUINT32>

        UINT8             _bySummonLast;    // 召唤物持续时间
}; // -----  end of class CBattleFighter  ----- //

} // namespace NBattle;

#endif // _BATTLE_FIGHTER_H_
