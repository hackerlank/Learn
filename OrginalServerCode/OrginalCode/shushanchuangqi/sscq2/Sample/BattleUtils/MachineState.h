#ifndef MACHINE_STATE_H
#define MACHINE_STATE_H

#include "BattleTypeDef.h"
#include "BattleField.h"

namespace NBattle
{

class CBattleField;
class CBattleSkillEffect;

class CMachineState
{
    public:

        CMachineState(CBattleField& rField, EMachineState eMS, CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID = 0);

        CMachineState(CBattleField& rField, CBattleFighter* pBF, const TVecBattleActionPtr& rvecAction, 
                UINT32 dwSkillID, const TVecUINT8& rvecTargetID, const TVecBattleTargetPos& rvecTargetPos);

        virtual ~CMachineState();

        virtual void Process();

        SBattleProgress&            GetBattleProgress();
        const SBattleProgress&      GetBattleProgress() const;
        SBattleProgress&            GetBattleProgressFinal();
        const SBattleProgress&      GetBattleProgressFinal() const;
        const TVecBattleProgress&   GetExtraProgressBefore() const;
        const TVecBattleProgress&   GetExtraProgressAfter() const;

        void CatEffects(CMachineState& rMS);
        void CatEffects(CBattleAction* pAction);

        TVecEffects& GetEffectsVec(EEffectType eType);
 
        EEffectType GetEffectsType() const;
        void SetEffectsType(EEffectType eType);

        TVecMachineStatePtr& GetExtraMS();
        const TVecMachineStatePtr& GetExtraMS() const;

        // 返回各个不同状态机的特殊值
        virtual FLOAT GetParam() const; 

        // 设置各个不同状态机的特殊值
        virtual void SetParam(FLOAT fParam);

    private:

        EMSCheckType GetStateType() const;

        void GetProcessTargets (TVecBattleFighterPtr& rvecTargets, TVecBattleFighterPtr& rvecResponders);
        void GetOneStateAction(CBattleFighter* pBF, CBattleFighter* pBO);
        
    protected:
        void ProcessAction();

        // CBattleAction 的触发方式
        enum EBBAType
        {
            eBBANone               = 0,
            eBBABuffEffect            ,    //  Buff生效
            eBBAActiveSkill           ,    //  主动技能
            eBBANoPosActiveSkill      ,    //  非主动释放的技能
            eBBAEnter                 ,    //  入场时
            eBBABuffOutEffect         ,    //  Buff失效
            eBBABuffRelease           ,    //  Buff减CD
            eBBABuffAct               ,    //  Buff带出新的效果
            eBBAMax
        };

        bool BuildSkillAction(ESkillLaunchType eType, CBattleSkillEffect& rEf, 
                CBattleFighter* pBF, CBattleFighter* pBO, 
                UINT16 wProb, TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID);

        UINT32 BuildBuffAction(CBattleSkillEffect& rEf, 
                CBattleFighter* pBF, CBattleFighter* pBO, 
                EBBAType eType, UINT32 dwBuffID, UINT32 dwBuffIDEX, 
                UINT16 wProb, TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID);

        UINT32 BuildBuffActAction(CBattleSkillEffect& rEf, 
                CBattleFighter* pBF, CBattleFighter* pBO, 
                UINT32 dwBuffID, UINT32 dwBuffIDEX, 
                UINT16 wProb, TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID);

        CBattleAction* GetBattleAction(UINT8 byMainTarget, FLOAT fParam, CBattleSkillEffect& rEf, 
                CBattleFighter* pBF, CBattleFighter* pBO, bool& rHited,
                EBBAType eType, UINT32 dwBuffID, UINT32 dwBuffIDEX, UINT8 byPos);

        void SetCasterID(UINT8 byID, UINT8 byIndex = 0);

    protected:
        CBattleField&       _rField;                    // 这个状态机用到的战斗场地

        EMachineState       _eState;                    // 状态机当前状态
        EMachineState       _eNextState;                // 状态机下一个状态

        CBattleFighter*     _pBF;
        CBattleFighter*     _pBO;

        TVecBattleActionPtr _vecAction;                 // 技能效果产生的各种行为

        SBattleProgress     _sProgress;                 // 生成的协议数据

        TVecBattleProgress  _vecExtraProgressBefore;    // 额外触发的动作
        TVecBattleProgress  _vecExtraProgressAfter;     // 额外触发的动作

        SBattleProgress     _sProgressFinal;            // 额外触发的动作

        EEffectType         _eEffectType;

        UINT32              _dwBuffID;

        TVecMachineStatePtr _vecExtraMS;

        FLOAT               _fParam;                    // 状态机额外参数
};

class CDeadMachineState : public CMachineState
{
    public:
        CDeadMachineState(CBattleField& rField, CBattleFighter* pBF, bool bIsSummonTimeOut = false);
        virtual ~CDeadMachineState();
        virtual void Process();
    private:
        bool _bIsSummonTimeOut;     // 是否是召唤物持续时间到达所产生的老死
};

class CEnterMachineState : public CMachineState
{
    public:
        CEnterMachineState(CBattleField& rField, CBattleFighter* pFighter = NULL);
        virtual ~CEnterMachineState();
        virtual void Process();
};

class CMainMachineState : public CMachineState
{
    public:
        CMainMachineState(CBattleField& rField, bool bEndRound);
        virtual ~CMainMachineState();
        virtual void Process();

        bool IsRoundEnd() const;
        UINT8 GetActiveSide() const;

    private:
        void Start();
        void BeforeAct();
        void ActiveAct();
        void AfterAct();
        void ReleaseSummonTime();

        void SyncCombineCount();

    private:
        bool    _bRounedEnd;
        UINT8   _byActiveSide;
};

class CDamageMachineState : public CMachineState
{
    public:
        CDamageMachineState(CBattleField& rField, CBattleFighter* pBF, CBattleFighter* pBO, 
                UINT32 dwDamage, bool bCri, UINT32 dwSkillID, EDamageType eDTType);
        virtual ~CDamageMachineState();
        virtual void Process();

        // 返回实际造成的伤害值(包括护盾和扣血)
        virtual FLOAT GetParam() const;

    private:
        // 计算伤害增减益因数
        FLOAT CalcDamageFactor(CBattleFighter* pBF, CBattleFighter* pBO, bool& rBlocked);

    private:
        UINT32          _dwDamdge;      // 实际的伤害(和护盾的伤害互斥)
        UINT32          _dwShieldDmg;   // 对护盾造成的伤害
        bool            _bCri;          // 是否暴击
        UINT32          _dwSkillID;     // 造成该伤害的原始技能ID(和SkillBase的ID等价)
        EDamageType     _eDTType;       // 伤害触发的类型
};

class CHPChangeMachineState : public CMachineState
{
    public:
        CHPChangeMachineState(CBattleField& rField, CBattleFighter* pBF, CBattleFighter* pBO, 
                INT32 dwHPChange, bool bCri, UINT32 dwSkillID, EBSubHPType eSubHPType, bool bHideShow = false);
        virtual ~CHPChangeMachineState();
        virtual void Process();

    private:
        INT32       _dwHPChange;    // 生命值变化的数值
        bool        _bCri;          // 是否暴击
        UINT32      _dwSkillID;     // 造成该伤害的原始技能ID(和SkillBase的ID等价)
        EBSubHPType _eSubType;      // 扣血伤害类型（物理/法术）
        bool        _bHideShow;     // 是否客户端不显示（通常为其他效果会把这个扣血显示出来）
};

class CAttackMachineState   : public CMachineState
{
    public:
        CAttackMachineState(CBattleField& rField, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CAttackMachineState();
        virtual void Process();

    private:
        void BeforeAtk();
        void SkillAttack();
        void AfterAtk();

    private:
        ESkillLaunchType _eLaunchType;
        CBattleFighter* _pCounter;
};

class CBuffAddMachineState     : public CMachineState
{
    public:
        CBuffAddMachineState(CBattleField& rField, FLOAT fParam,
                CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID);
        virtual ~CBuffAddMachineState();
        virtual void Process();

        void SetExLast(UINT8 byExLast);

    private:
        UINT8   _byExLast;          // 增加Buff的时候额外的回合数
};

class CBuffLostMachineState     : public CMachineState
{
    public:
        CBuffLostMachineState(CBattleField& rField, EMachineState eState, FLOAT fParam,
                CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwBuffIDEX = 0);
        CBuffLostMachineState(CBattleField& rField, EMachineState eState, FLOAT fParam,
                CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwFakeBuffKey, bool bOutCond);
        virtual ~CBuffLostMachineState();
        virtual void Process();

    private:
        UINT32  _dwFakeBuffKey;     // 只是为了引起触发条件临时加的
        bool    _bOutCond;
        UINT32  _dwBuffIDEX;        // 吸血效果取的时候用的
        bool    _bClear;            // 是否是强制清除Buff
};

class CBuffActMachineState     : public CMachineState
{
    public:
        CBuffActMachineState(CBattleField& rField, FLOAT fParam,
                CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwBuffIDEX = 0);
        virtual ~CBuffActMachineState();
        virtual void Process();
        UINT32 GetBuffEffectCount() const;

        void SetExLast(UINT8 byExLast);

    private:
        UINT32  _dwBuffEffectCount;
        UINT32  _dwBuffIDEX;        // 吸血效果取的时候用的
};

class CAuraChangeMachineState   : public CMachineState
{
    public:
        CAuraChangeMachineState(CBattleField& rField, EMachineState eState, CBattleFighter* pBF, INT32 dwAura);
        virtual ~CAuraChangeMachineState();
        virtual void Process();
    private:
        INT32 _dwAura;
};

class CReiatsuChangeMachineState    : public CMachineState
{
    public:
        CReiatsuChangeMachineState(CBattleField& rField, EMachineState eState, UINT8 bySide);
        virtual ~CReiatsuChangeMachineState();
        virtual void Process();

        bool IsLaunched() const;
    private:
        void TryLaunchBeautySkill();
        bool _bLaunched;
};

class CCombineChangeMachineState    : public CMachineState
{
    public:
        CCombineChangeMachineState(CBattleField& rField, EMachineState eState, UINT8 bySide);
        virtual ~CCombineChangeMachineState();
        virtual void Process();

        bool IsLaunched() const;
    private:
        void TryLaunchCombineSkill();
        void ClearDeBuff(CBattleFighter* pFighter);

    private:
        UINT8   _bySide;
        bool    _bLaunched;
        UINT8   _byIndex;
};

class CBuffSkillMachineState    : public CMachineState
{
    public:
        CBuffSkillMachineState(CBattleField& rField, 
                CBattleFighter* pBF, CBattleFighter* pBO, 
                UINT32 dwBuffID, UINT32 dwBuffIDEX);
        virtual ~CBuffSkillMachineState();
        virtual void Process();

    private:
        UINT32 _dwBuffIDEX;
};

} // namespace NBattle

#endif // MACHINE_STATE_H

