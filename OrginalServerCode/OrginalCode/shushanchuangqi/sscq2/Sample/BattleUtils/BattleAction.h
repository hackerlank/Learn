#ifndef _BATTLE_ACTION_H_
#define _BATTLE_ACTION_H_

#include "BattleTypeDef.h"

#include "BattleSkill.h"

namespace NBattle
{
class CBattleField;
class CMachineState;

class CBattleAction
{
    public:
        CBattleAction(CBattleField& rField, CBattleSkillEffect& rEF, 
                CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID = 0);
        virtual ~CBattleAction();

        virtual void Process() = 0;
        virtual bool NeedStopMS() { return false; }
        virtual FLOAT GetParam() const { return 0.0f;}

        const TVecEffects& GetEffectsBefore()   const;
        const TVecEffects& GetEffects()         const;
        const TVecEffects& GetEffectsAfter()    const;

        const TVecEffects& GetEffectsBeforeFinal()   const;
        const TVecEffects& GetEffectsFinal()         const;
        const TVecEffects& GetEffectsAfterFinal()    const;

        const TVecMachineStatePtr& GetExtraMS() const;

        void CatEffects(CMachineState& rMS);

        bool    CalcCri (CBattleFighter* pAttacker, CBattleFighter* pDefender);
        UINT32  CalcDmg (CBattleFighter* pAttacker, CBattleFighter* pDefender, FLOAT fFactor, CBattleSkillEffect& rBSEF,
                            bool bCri = false, bool bCounter = false);

    protected:
        CBattleField&       _rField;
        CBattleSkillEffect  _cBSEffect;
        CBattleFighter*     _pBF;
        CBattleFighter*     _pBO;

        TVecEffects         _vecEffectsBefore;
        TVecEffects         _vecEffects;
        TVecEffects         _vecEffectsAfter;

        TVecEffects         _vecEffectsBeforeFinal;
        TVecEffects         _vecEffectsFinal;
        TVecEffects         _vecEffectsAfterFinal;

        UINT32              _dwBuffID;
        TVecMachineStatePtr _vecExtraMS;
};

class CCounterAction : public CBattleAction
{
    public:
        CCounterAction(CBattleField& rField, FLOAT fFactor, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CCounterAction();
        
    private:
        virtual void Process();

        bool CalcCounter(CBattleFighter*, CBattleFighter*);

    private:
        FLOAT _fFactor;
};

class CDmgAction : public CBattleAction
{
    public:
        CDmgAction(CBattleField& rField, UINT8 byMainTarget, FLOAT fFactor, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, EDamageType eDmgType);
        virtual ~CDmgAction();

        virtual FLOAT GetParam() const; // 返回伤害值

    private:
        virtual void Process();
        bool CalcHit (CBattleFighter*, CBattleFighter*);
        void HitProcess();
        void EvadeProcess();

    private:
        UINT8 _byMainTarget;
        EDamageType _eDmgType;
        FLOAT _fFactor;
        UINT32 _dwFinalDamage;
};

class CTherapyAction : public CBattleAction
{
    public:
        CTherapyAction(CBattleField& rField, FLOAT fFactor, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CTherapyAction();

        virtual FLOAT GetParam() const; // 返回治疗值

    private:
        virtual void Process();
        UINT32  CalcTherapy     (CBattleFighter*, CBattleFighter*, FLOAT, CBattleSkillEffect&);

    private:
        FLOAT _fFactor;
        UINT32 _dwRHP;
};

class CAddBuffAction : public CBattleAction
{
    public:
        CAddBuffAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CAddBuffAction();

    private:
        virtual void Process();
        bool    CalcResist      (CBattleFighter*, CBattleFighter*, CBattleSkillEffect&);
};

class CBuffEffectAction : public CBattleAction
{
    public:
        CBuffEffectAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO, 
                UINT32 dwBuffID, UINT32 dwBuffIDEX, FLOAT fParam);
        virtual ~CBuffEffectAction();
        virtual void Process();
    private:
        UINT32 _dwBuffIDEX;
        FLOAT  _fParam;
};

class CBuffOutEffectAction : public CBattleAction
{
    public:
        CBuffOutEffectAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO, 
                UINT32 dwBuffID, UINT32 dwBuffIDEX, FLOAT fParam);
        virtual ~CBuffOutEffectAction();
        virtual void Process();
    private:
        UINT32 _dwBuffIDEX;
        FLOAT  _fParam;
};

class CBuffReleaseEffectAction : public CBattleAction
{
    public:
        CBuffReleaseEffectAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO, 
                UINT32 dwBuffID);
        virtual ~CBuffReleaseEffectAction();
        virtual void Process();
};

class CAuraAction : public CBattleAction
{
    public:
        CAuraAction(CBattleField& rField, FLOAT fFactor, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CAuraAction();
        virtual void Process();
    private:
        FLOAT _fFactor;
};

class CSummonAction : public CBattleAction
{
    public:
        CSummonAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, UINT8 byPos);
        virtual ~CSummonAction();
        virtual void Process();
    private:
        UINT8 _byPos;
};

class CDialogAction : public CBattleAction
{
    public:
        CDialogAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CDialogAction();
        virtual void Process();
};

class CReiatsuAction : public CBattleAction
{
    public:
        CReiatsuAction(CBattleField& rField, INT8 byReiatsu, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CReiatsuAction();
        virtual void Process();

    private:
        INT8 _byReiatsu;
};

class CCombineAction : public CBattleAction
{
    public:
        CCombineAction(CBattleField& rField, UINT8 bySide, UINT32 dwSkillID, UINT8 byCombine, UINT8 byIndex);
        virtual ~CCombineAction();
        virtual void Process();

    private:
        UINT8 _bySide;
        UINT32 _dwSkillID;
        UINT8 _byCombine;
        UINT8 _byIndex;
};

class CTransformAction : public CBattleAction
{
    public:
        CTransformAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CTransformAction(); 
        virtual void Process();
};

class CToggleSkillsAction : public CBattleAction
{
    public:
        CToggleSkillsAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CToggleSkillsAction(); 
        virtual void Process();
};

class CPartBrokenAction : public CBattleAction
{
    public:
        CPartBrokenAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CPartBrokenAction(); 
        virtual void Process();
};

class CClearDebuffAction : public CBattleAction
{
    public:
        CClearDebuffAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CClearDebuffAction(); 
        virtual void Process();
};

class CBuffActionAction : public CBattleAction
{
    public:
        CBuffActionAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CBuffActionAction(); 
        virtual void Process();
};

class CTriggerAction : public CBattleAction
{
    public:
        CTriggerAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CTriggerAction(); 
        virtual void Process();
};

class CNeverDeadAction : public CBattleAction
{
    public:
        CNeverDeadAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CNeverDeadAction(); 
        virtual void Process();
};

class CDeadActionAction : public CBattleAction
{
    public:
        CDeadActionAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CDeadActionAction(); 
        virtual void Process();
};

class CExtendLastAction : public CBattleAction
{
    public:
        CExtendLastAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF);
        virtual ~CExtendLastAction(); 
        virtual void Process();
};

class CNoGainAuraAction : public CBattleAction
{
    public:
        CNoGainAuraAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CNoGainAuraAction(); 
        virtual void Process();
};

class CAbsorbAction : public CBattleAction
{
    public:
        CAbsorbAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwBuffIDEX, FLOAT fParam);
        virtual ~CAbsorbAction(); 
        virtual void Process();
    private:
        UINT32 _dwBuffIDEX;
        FLOAT _fParam;
};

class CReliveAction : public CBattleAction
{
    public:
        CReliveAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO);
        virtual ~CReliveAction();
        virtual void Process();
};

class CReflectAction : public CBattleAction
{
    public:
        CReflectAction(CBattleField& rField, CBattleSkillEffect& rEF, CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwBuffIDEX);
        virtual ~CReflectAction();
        virtual void Process();

        virtual bool NeedStopMS() const;
    private:
        UINT32 _dwBuffIDEX;
        bool _bNeedStopMS;
};

// 免伤率
extern UINT32 g_dwReduceMax;
extern UINT32 g_dwReduceMin;
extern UINT32 g_dwReduceValue[];

// 暴击伤害
extern UINT32 g_dwCriticalDmgMax;
extern UINT32 g_dwCriticalDmgMin;

// 伤害浮动
extern UINT32 g_dwDamageFloatMax;
extern UINT32 g_dwDamageFloatMin;

// 命中计算
extern UINT32 g_dwHitMax;
extern UINT32 g_dwHitMin;
extern UINT32 g_dwHitValue[];

// 暴击概率
extern UINT32 g_dwCriticalMax;
extern UINT32 g_dwCriticalMin;
extern UINT32 g_dwCriticalValue[];

// 反击概率
extern UINT32 g_dwCounterMax;
extern UINT32 g_dwCounterMin;
extern UINT32 g_dwCounterValue[];

// 抵抗计算
extern UINT32 g_dwResistMax;
extern UINT32 g_dwResistMin;

} // namespace NBattle

#endif // _BATTLE_ACTION_H_

