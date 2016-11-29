
#include "BattleAction.h"

#include "Random.h"

#include "MachineState.h"
#include "BattleField.h"
#include "BattleDebugger.h"

#include "BattleFighter.h"

namespace NBattle
{

// 免伤率
UINT32 g_dwReduceMax = 9000;
UINT32 g_dwReduceMin = 0;
UINT32 g_dwReduceValue[] = 
{
    0,      // ID = "0"
    40,     // ID = "1"
    2500,   // ID = "2"
};

// 暴击伤害
UINT32 g_dwCriticalDmgMax = 30000;
UINT32 g_dwCriticalDmgMin = 15000;

// 伤害浮动
UINT32 g_dwDamageFloatMax = 10500;
UINT32 g_dwDamageFloatMin = 9500; 

// 命中计算
UINT32 g_dwHitMax = 10000;
UINT32 g_dwHitMin = 100;
UINT32 g_dwHitValue[]  = 
{
    0,     // ID = "0"
    20,    // ID = "1"
    500,   // ID = "2"
};

// 暴击概率
UINT32 g_dwCriticalMax = 9000;
UINT32 g_dwCriticalMin = 0;
UINT32 g_dwCriticalValue[]  = 
{
    0,      // ID = "0"
    50,     // ID = "1"
    2000,   // ID = "2"
};


// 反击概率
UINT32 g_dwCounterMax = 8500;
UINT32 g_dwCounterMin = 0;
UINT32 g_dwCounterValue[]  = 
{
    0,      // ID = "0"
    20,     // ID = "1"
    2000,   // ID = "2"
};

// 抵抗计算
UINT32 g_dwResistMax = 10000;
UINT32 g_dwResistMin = 0; 

CBattleAction::CBattleAction(CBattleField& rField, CBattleSkillEffect& rEf, 
        CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID /* = 0 */):
    _rField(rField), _cBSEffect(rEf), _pBF(pBF), _pBO(pBO), _dwBuffID(dwBuffID)
{
}

CBattleAction::~CBattleAction()
{
}

const TVecEffects& CBattleAction::GetEffectsBefore() const
{
    return _vecEffectsBefore;
}

const TVecEffects& CBattleAction::GetEffects() const
{ 
    return _vecEffects; 
}

const TVecEffects& CBattleAction::GetEffectsAfter() const
{
    return _vecEffectsAfter;
}

const TVecEffects& CBattleAction::GetEffectsBeforeFinal() const
{
    return _vecEffectsBeforeFinal;
}

const TVecEffects& CBattleAction::GetEffectsFinal() const
{ 
    return _vecEffectsFinal;
}

const TVecEffects& CBattleAction::GetEffectsAfterFinal() const
{
    return _vecEffectsAfterFinal;
}

// ===  FUNCTION  ======================================================================
//         Name:  GetExtraMS
//  Description:  获取额外的状态级
// =====================================================================================
const TVecMachineStatePtr& CBattleAction::GetExtraMS() const
{
    return _vecExtraMS;
}		// -----  end of function GetExtraMS  ----- //

// 这里要根据效果时机类型改进一下
void CBattleAction::CatEffects(CMachineState& rMS)
{
    switch (rMS.GetEffectsType())
    {
        case eETAfter:
            {
                const TVecEffects& rEf = rMS.GetBattleProgress().vEffectsBefore;
                _vecEffectsAfter.insert(_vecEffectsAfter.end(), rEf.begin(), rEf.end());
                const TVecEffects& rEf2 = rMS.GetBattleProgress().vSkillEffects;
                _vecEffectsAfter.insert(_vecEffectsAfter.end(), rEf2.begin(), rEf2.end());
                const TVecEffects& rEf3 = rMS.GetBattleProgress().vEffectsAfter;
                _vecEffectsAfter.insert(_vecEffectsAfter.end(), rEf3.begin(), rEf3.end());
            }
            break;
        case eETBefore:
            {
                const TVecEffects& rEf = rMS.GetBattleProgress().vEffectsBefore;
                _vecEffectsBefore.insert(_vecEffectsBefore.end(), rEf.begin(), rEf.end());
                const TVecEffects& rEf2 = rMS.GetBattleProgress().vSkillEffects;
                _vecEffectsBefore.insert(_vecEffectsBefore.end(), rEf2.begin(), rEf2.end());
                const TVecEffects& rEf3 = rMS.GetBattleProgress().vEffectsAfter;
                _vecEffectsBefore.insert(_vecEffectsBefore.end(), rEf3.begin(), rEf3.end());
            }
            break;
        case eETSkill:
        default:
            {
                const TVecEffects& rEf = rMS.GetBattleProgress().vEffectsBefore;
                _vecEffectsBefore.insert(_vecEffectsBefore.end(), rEf.begin(), rEf.end());
                const TVecEffects& rEf2 = rMS.GetBattleProgress().vSkillEffects;
                _vecEffects.insert(_vecEffects.end(), rEf2.begin(), rEf2.end());
                const TVecEffects& rEf3 = rMS.GetBattleProgress().vEffectsAfter;
                _vecEffectsAfter.insert(_vecEffectsAfter.end(), rEf3.begin(), rEf3.end());
            }
            break;
    }

    SBattleProgress& rProgressFinal = rMS.GetBattleProgressFinal();
    _vecEffectsBeforeFinal.insert(_vecEffectsBeforeFinal.begin(), rProgressFinal.vEffectsBefore.begin(), rProgressFinal.vEffectsBefore.end());
    _vecEffectsFinal.insert(_vecEffectsFinal.begin(), rProgressFinal.vSkillEffects.begin(), rProgressFinal.vSkillEffects.end());
    _vecEffectsAfterFinal.insert(_vecEffectsAfterFinal.begin(), rProgressFinal.vEffectsAfter.begin(), rProgressFinal.vEffectsAfter.end());

    const TVecMachineStatePtr& rvecMS = rMS.GetExtraMS();
    _vecExtraMS.insert(_vecExtraMS.end(), rvecMS.begin(), rvecMS.end());
}

// 计算是否暴击
bool CBattleAction::CalcCri(CBattleFighter* pAttacker, CBattleFighter* pDefender)
{
    if (!pAttacker || !pDefender)
        return false;

    FLOAT fModifyAntiCrit = pDefender->GetAttrFinal(EFIGHTATTR_ANTICRITCAL) * (1 + pDefender->GetAttrFinal(EFIGHTATTR_ANTICRITCAL_PER));
    CALC_DBG << "ANTICRITCAL = " << pDefender->GetAttrFinal(EFIGHTATTR_ANTICRITCAL) << ", "
        "ANTICRITCAL_PER = " << pDefender->GetAttrFinal(EFIGHTATTR_ANTICRITCAL_PER) << ", "
        "fModifyAntiCrit = " << fModifyAntiCrit << ".";

    if (fModifyAntiCrit <= 0.0001f)
        fModifyAntiCrit = 0.0001f;

    FLOAT fModifyCrit = pAttacker->GetAttrFinal(EFIGHTATTR_CRITICAL) * (1 + pAttacker->GetAttrFinal(EFIGHTATTR_CRITICAL_PER));
    CALC_DBG << "CRITICAL = " << pAttacker->GetAttrFinal(EFIGHTATTR_CRITICAL) << ", "
        "CRITICAL_PER = " << pAttacker->GetAttrFinal(EFIGHTATTR_CRITICAL_PER) << ", "
        "fModifyCrit = " << fModifyCrit << ".";

    if (fModifyCrit <= 0.0001f)
        fModifyCrit = 0.0001f;

    FLOAT fFinalCrit = fModifyCrit - fModifyAntiCrit;
    if (fFinalCrit <= 0.0001f)
        fFinalCrit = 0.0001f;

    fFinalCrit = fFinalCrit / (fFinalCrit + g_dwCriticalValue[1] * pDefender->GetLevel() + g_dwCriticalValue[2]);

    if (fFinalCrit <= 0.0001f)
        fFinalCrit = 0.0001f;
    CALC_DBG << "fFinalCrit = " << fFinalCrit << ".";

    fFinalCrit = pAttacker->GetAttrFinal(EFIGHTATTR_CRTRATE) - pDefender->GetAttrFinal(EFIGHTATTR_ANTICRTRATE) + fFinalCrit;

    if (fFinalCrit <= g_dwCriticalMin / 10000.0f)
        fFinalCrit = g_dwCriticalMin / 10000.0f;
    if (fFinalCrit > g_dwCriticalMax / 10000.0f)
        fFinalCrit = g_dwCriticalMax / 10000.0f;
    CALC_DBG << "fFinalCrit = " << fFinalCrit << ".";

#ifdef _DEBUG
    if (IsCrital100())
    {
        _rField.AddCombine(pAttacker, eCTCritical);
        return true;
    }
#endif
    if (CRandom::RandFloat(0, 1) < fFinalCrit)
    {
        _rField.AddCombine(pAttacker, eCTCritical);
        return true;
    }
    else 
        return false;
}

// 计算伤害值
UINT32 CBattleAction::CalcDmg(CBattleFighter* pAttacker, CBattleFighter* pDefender, FLOAT fFactor, CBattleSkillEffect& rEf, 
        bool bCri /* = false */, bool bCounter /* = false */)
{
    if (!pAttacker || !pDefender)
        return 0;

    FLOAT fAtk = 0;
    FLOAT fDef = 0;
    FLOAT fRdc = 0;
    FLOAT fSkillAtk = 0;
    CALC_DBG << "fFactor = " << fFactor << ".";

    if (pAttacker->IsPhyJob())
    {
        fAtk = pAttacker->GetAttrFinal(EFIGHTATTR_PHYATK) * (1 + pAttacker->GetAttrFinal(EFIGHTATTR_PHYATK_PER));
        CALC_DBG << "PHYATK = " << pAttacker->GetAttrFinal(EFIGHTATTR_PHYATK) << ", "
            "PHYATK_PER = " << pAttacker->GetAttrFinal(EFIGHTATTR_PHYATK_PER) << ", "
            "fAtk = " << fAtk << ".";

        fDef = pDefender->GetAttrFinal(EFIGHTATTR_PHYDEF) * (1 + pDefender->GetAttrFinal(EFIGHTATTR_PHYDEF_PER));
        CALC_DBG << "PHYDEF = " << pDefender->GetAttrFinal(EFIGHTATTR_PHYDEF) << ", "
            "PHYDEF = " << pDefender->GetAttrFinal(EFIGHTATTR_PHYDEF) << ", "
            "fDef = " << fDef << ".";

        fRdc = pDefender->GetAttrFinal(EFIGHTATTR_PHYRDC);
        CALC_DBG << "fRdc = " << fRdc << ".";
    }
    else if (pAttacker->IsMgcJob())
    {
        fAtk = pAttacker->GetAttrFinal(EFIGHTATTR_MGCATK) * (1 + pAttacker->GetAttrFinal(EFIGHTATTR_MGCATK_PER));
        CALC_DBG << "MGCATK = " << pAttacker->GetAttrFinal(EFIGHTATTR_MGCATK) << ", "
            "MGCATK_PER = " << pAttacker->GetAttrFinal(EFIGHTATTR_MGCATK_PER) << ", "
            "fAtk = " << fAtk << ".";

        fDef = pDefender->GetAttrFinal(EFIGHTATTR_MGCDEF) * (1 + pDefender->GetAttrFinal(EFIGHTATTR_MGCDEF_PER));
        CALC_DBG << "MGCDEF = " << pDefender->GetAttrFinal(EFIGHTATTR_MGCDEF) << ", "
            "MGCDEF = " << pDefender->GetAttrFinal(EFIGHTATTR_MGCDEF) << ", "
            "fDef = " << fDef << ".";

        fRdc = pDefender->GetAttrFinal(EFIGHTATTR_MGCRDC);
        CALC_DBG << "fRdc = " << fRdc << ".";
    }

    fSkillAtk = rEf.GetValue1() * fAtk / 10000 + rEf.GetValue2();
    CALC_DBG << "fSkillAtk = " << fSkillAtk << ", "
        "Value = " << rEf.GetValue1() << ", "
        "Value2 = " << rEf.GetValue2() << ".";

    if (bCounter)
    {
        FLOAT fCounterFactor = 1.0f + pAttacker->GetAttrFinal(EFIGHTATTR_COUTEREXTRAADD)  - pDefender->GetAttrFinal(EFIGHTATTR_COUTEREXTRARDC);
        CALC_DBG << "COUTEREXTRAADD = " << pAttacker->GetAttrFinal(EFIGHTATTR_COUTEREXTRAADD) << ", "
            "COUTEREXTRARDC = " << pDefender->GetAttrFinal(EFIGHTATTR_COUTEREXTRARDC) << ", "
            "fCounterFactor = " << fCounterFactor << ".";

        if (fCounterFactor < 1.0f)
            fCounterFactor = 1.0f;
        fSkillAtk *= fCounterFactor;
    }

    FLOAT fModifyPierce = pAttacker->GetAttrFinal(EFIGHTATTR_PIERCE) * (1 + pAttacker->GetAttrFinal(EFIGHTATTR_PIERCE_PER));
    CALC_DBG << "PIERCE = " << pAttacker->GetAttrFinal(EFIGHTATTR_PIERCE) << ", "
        "PIERCE_PER = " << pAttacker->GetAttrFinal(EFIGHTATTR_PIERCE_PER) << ", "
        "fModifyPierce = " << fModifyPierce << ".";

    if (fModifyPierce <= 0.0001f)
        fModifyPierce = 0.0001f;
    FLOAT fFinalRdc = fDef - fModifyPierce;
    if (fFinalRdc <= 0.0001f)
        fFinalRdc = 0.0001f;

    fFinalRdc = fFinalRdc / (fFinalRdc + g_dwReduceValue[1] * pAttacker->GetLevel() + g_dwReduceValue[2]) + fRdc;
    fFinalRdc = fFinalRdc + 
        pDefender->GetAttrFinal(EFIGHTATTR_BLOCKRATE) - pAttacker->GetAttrFinal(EFIGHTATTR_PIERCERATE) + 
        pDefender->GetStateValue(EBFBuffTypeRedAdd) - pDefender->GetStateValue(EBFBuffTypeRedSub);

    if (fFinalRdc <= g_dwReduceMin / 10000.0f)
        fFinalRdc = g_dwReduceMin / 10000.0f;
    if (fFinalRdc >= g_dwReduceMax / 10000.0f)
        fFinalRdc = g_dwReduceMax / 10000.0f;

    if (pDefender->GetStateValue(EBFBuffTypePierce) > 0.1f) //  破甲效果伤害减免减半
        fFinalRdc *= 0.5;
    CALC_DBG << "fFinalRdc = " << fFinalRdc << ".";

    FLOAT fDamageFactor = 1 - fFinalRdc;

    // 如果发生暴击，计算暴击伤害系数
    FLOAT fCriExtraFactor = 1.0f;
    if (bCri)
    {
        fCriExtraFactor = pAttacker->GetAttrFinal(EFIGHTATTR_CRIEXTRAADD) - pDefender->GetAttrFinal(EFIGHTATTR_CRIEXTRARDC);
        CALC_DBG << "CRIEXTRAADD = " << pAttacker->GetAttrFinal(EFIGHTATTR_CRIEXTRAADD) << ", "
            "CRIEXTRARDC = " << pDefender->GetAttrFinal(EFIGHTATTR_CRIEXTRARDC) << ", "
            "fCriExtraFactor = " << fCriExtraFactor << ".";
        if (fCriExtraFactor >= g_dwCriticalDmgMax / 10000.0f)
            fCriExtraFactor = g_dwCriticalDmgMax / 10000.0f;
        if (fCriExtraFactor < g_dwCriticalDmgMin / 10000.0f)
            fCriExtraFactor = g_dwCriticalDmgMin / 10000.0f;
    }

    FLOAT fDmg = 0;
    fDmg = fSkillAtk * fCriExtraFactor * fDamageFactor * fFactor * 
        (1 + pAttacker->GetStateValue(EBFBuffTypeActAtkAdd) + pAttacker->GetStateValue(EBFBuffTypeAtkAdd) + pAttacker->GetStateFactor(EBFBuffTypeAtkAdd) - pAttacker->GetStateValue(EBFBuffTypeAtkSub) - pDefender->GetStateValue(EBFBuffTypeBeDmgReudce) - pDefender->GetStateValue(EBFBuffTypeActDefAdd));
    CALC_DBG << "EBFBuffTypeAtkAdd = " << pAttacker->GetStateValue(EBFBuffTypeAtkAdd) << ", "
        "EBFBuffTypeAtkSub = " << pAttacker->GetStateValue(EBFBuffTypeAtkSub) << ".";

    if (fDmg < 1.0f)
        fDmg = 1.0f;
    CALC_DBG << "fDmg = " << fDmg << ".";

    fDmg *= CRandom::RandFloat(g_dwDamageFloatMin / 10000.0f, g_dwDamageFloatMax / 10000.0f);

    return static_cast<UINT32>(fDmg);
}

CCounterAction::CCounterAction(CBattleField& rField, FLOAT fFactor, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO) : 
    CBattleAction(rField, rEf, pBF, pBO), _fFactor(fFactor)
{
}

CCounterAction::~CCounterAction()
{
}

void CCounterAction::Process()
{
    ACTION_DEBUG << "CCounterAction: " << _fFactor << ".";
    if(CalcCounter(_pBF, _pBO))
    {
        CMachineState cTmpMS(_rField, eMSOnCounter, _pBF, _pBO);
        cTmpMS.Process();
        CatEffects(cTmpMS);

        UINT32 dwDmg = CalcDmg(_pBF, _pBO, _fFactor, _cBSEffect, false, true);

        string strInfo;
        if (_pBF)
            strInfo << *_pBF;
        if (_pBO)
            strInfo << *_pBO;
        BATTLE_DBG  << "Counter: " << (strInfo << _cBSEffect);

        bool bNoDamage = false;
        // 有无敌状态，不会被反击造成伤害
        if (_pBO->GetStateValue(EBFBuffTypeInvincible) >= 0.0001f)
        {
            bNoDamage = true;
            dwDmg = 0;
        }

        SEffectCounterPtr pEffect(new SEffectCounter());
        pEffect->eSubHPType = _pBF->IsPhyJob()? EBSubHPPhy:EBSubHPMgc;
        pEffect->vecFighterID.push_back(_pBF->GetIndex());
        pEffect->eHPType = EBMODIFYHP_NORMAL;
        pEffect->dwDecHP = dwDmg;
        _vecEffects.push_back(SEffectBasePtr(pEffect));

        if (!bNoDamage)
        {
            CDamageMachineState cDamageMS(_rField, _pBO, _pBF, dwDmg, false, _cBSEffect.GetOriginSkillID(), eDTCounter);
            cDamageMS.Process();
            CatEffects(cDamageMS);
        }

        CMachineState cTmpMS3(_rField, eMSOnSelfCounter, _pBF, _pBO);
        cTmpMS3.SetParam(dwDmg);
        cTmpMS3.Process();
        CatEffects(cTmpMS3);

        CMachineState cTmpMS2(_rField, eMSAftCounter, _pBF, _pBO);
        cTmpMS2.Process();
        CatEffects(cTmpMS2);
    }
}

// 计算是否反击
bool CCounterAction::CalcCounter(CBattleFighter* pBF, CBattleFighter* pBO)
{
    if (!pBF || !pBO)
        return true;
    FLOAT fModifyResist = pBO->GetAttrFinal(EFIGHTATTR_RESIST) * (1 + pBO->GetAttrFinal(EFIGHTATTR_RESIST_PER));
    if (fModifyResist <= 0.0001f)
        fModifyResist = 0.0001f;
    FLOAT fModifyCounter = pBF->GetAttrFinal(EFIGHTATTR_COUNTER) * (1 + pBF->GetAttrFinal(EFIGHTATTR_COUNTER_PER));
    if (fModifyCounter <= 0.0001f)
        fModifyCounter = 0.0001f;
    FLOAT fFinalCounter = fModifyCounter - fModifyResist;
    if (fFinalCounter <= 0.0001f)
        fFinalCounter = 0.0001f;
    fFinalCounter = fFinalCounter / (fFinalCounter + g_dwCounterValue[1] * pBF->GetLevel() + g_dwCounterValue[2]);
    if (fFinalCounter <= 0.0001f)
        fFinalCounter = 0.0001f;
    fFinalCounter = pBF->GetAttrFinal(EFIGHTATTR_COUNTERRATE) - pBO->GetAttrFinal(EFIGHTATTR_RESISTRATE) + fFinalCounter;
    if (fFinalCounter <= g_dwCounterMin / 10000.0f)
        fFinalCounter = g_dwCounterMin / 10000.0f;
    if (fFinalCounter > g_dwCounterMax / 10000.0f)
        fFinalCounter = g_dwCounterMax / 10000.0f;

#ifdef _DEBUG
    if (IsCounter100())
    {
        _rField.AddCombine(pBF, eCTCounter);
        return true;
    }
#endif
    if (CRandom::RandFloat(0, 1) < fFinalCounter)
    {
        _rField.AddCombine(pBF, eCTCounter);
        return true;
    }
    else 
        return false;
}

CDmgAction::CDmgAction(CBattleField& rField, UINT8 byMainTarget, FLOAT fFactor, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, EDamageType eDmgType) : 
    CBattleAction(rField, rEf, pBF, pBO, dwBuffID), _byMainTarget(byMainTarget), _eDmgType(eDmgType), _fFactor(fFactor), _dwFinalDamage(0)
{
}

CDmgAction::~CDmgAction()
{
}

FLOAT CDmgAction::GetParam() const
{
    return static_cast<FLOAT>(_dwFinalDamage);
}

void CDmgAction::Process()
{
    ACTION_DEBUG << "CDmgAction: " << _fFactor << ".";
    if (_eDmgType == eDTActive || _eDmgType == eDTNoPosActive) // 非Buff触发的伤害（主动技能/普通攻击/法宝）
    {
        if(CalcHit(_pBF, _pBO))
        {
            HitProcess();
            if (_eDmgType == eDTActive)
            {
                CMachineState cTmpMS2(_rField, eMSAftBeAtked, _pBO, _pBF);
                cTmpMS2.SetParam(_dwFinalDamage);
                cTmpMS2.Process();
                CatEffects(cTmpMS2);
            }
        }
        else
            EvadeProcess();


        // 被攻击者在XXX都符合的条件下增加灵气
        if (_pBO->GetHP() > 0 && _byMainTarget == 1 && CBattleSkillMgr::Instance().CanBeCounter(SKILL_ID(_cBSEffect.GetID())) &&
                CBattleSkillMgr::Instance().GetSkillType(SKILL_ID(_cBSEffect.GetID())) != eSkillPeerless)
        {
            CAuraChangeMachineState cAuraChangeMS(_rField, eMSOnAuraAdd, _pBO, DEFAULT_AURA_ADD_VALUE);
            cAuraChangeMS.Process();
            CatEffects(cAuraChangeMS);
        }
    }
    else if (_eDmgType == eDTBuff)// Buff触发的伤害技能
    {
        UINT32 dwDmg = 0;
        switch (_cBSEffect.GetType())
        {
            case EHPDmg: //生命百分比伤害
                if (_pBO->GetHPP() > _cBSEffect.GetValue2())
                    dwDmg = static_cast<UINT32>(_pBO->GetMaxHP() * _cBSEffect.GetValue1() / 10000);
                break;
            default:
                dwDmg = CalcDmg(_pBF, _pBO, _fFactor, _cBSEffect, false);
                //dwDmg = static_cast<UINT32>(_pBF->GetAttack() * _cBSEffect.GetValue1() / 10000);
                break;

        }
        CDamageMachineState cDamageMS(_rField, _pBO, _pBF, dwDmg, false, _cBSEffect.GetOriginSkillID(), _eDmgType);
        cDamageMS.Process();
        CatEffects(cDamageMS);
        _dwFinalDamage = cDamageMS.GetParam();
    }
    else if (_eDmgType == eDTBounce && _fFactor >= 1.0f) // 对面反馈的伤害
    {
        UINT32 dwDmg = static_cast<UINT32>(_fFactor * _cBSEffect.GetValue1() / 10000);
        if (dwDmg <= 0)
            dwDmg = 1;
        CDamageMachineState cDamageMS(_rField, _pBO, NULL, dwDmg, false, _cBSEffect.GetOriginSkillID(), _eDmgType);
        cDamageMS.Process();
        CatEffects(cDamageMS);
        _dwFinalDamage = cDamageMS.GetParam();
    }
}

void CDmgAction::HitProcess()
{
    CMachineState cTmpMS(_rField, eMSHit, _pBF, _pBO);
    cTmpMS.Process();
    CatEffects(cTmpMS);

    if (_byMainTarget != 1)
        _fFactor += _pBF->GetStateValue(EBFBuffTypeBronze);

    if (_pBF)
    {
        CMachineState cTmpMS2(_rField, eMSOnAtkDmg, _pBF, _pBO);
        cTmpMS2.Process();
        CatEffects(cTmpMS2);
    }

    bool bCri = CalcCri(_pBF, _pBO);
    UINT32 dwDmg = CalcDmg(_pBF, _pBO, _fFactor, _cBSEffect, bCri);

    if (bCri)
    {
        CMachineState cTmpMS2(_rField, eMSBeforeCri, _pBF, _pBO);
        cTmpMS2.Process();
        CatEffects(cTmpMS2);
    }

    CDamageMachineState cDamageMS(_rField, _pBO, _pBF, dwDmg, bCri, _cBSEffect.GetOriginSkillID(), _eDmgType);
    cDamageMS.Process();
    CatEffects(cDamageMS);
    _dwFinalDamage = cDamageMS.GetParam();

    CMachineState cTmpMS2(_rField, eMSAftHit, _pBF, _pBO);
    cTmpMS2.Process();
    CatEffects(cTmpMS2);

    if (bCri)
    {
        CMachineState cTmpMS2(_rField, eMSAftCri, _pBF, _pBO);
        cTmpMS2.SetParam(_dwFinalDamage);
        cTmpMS2.Process();
        CatEffects(cTmpMS2);

        CMachineState cTmpMS3(_rField, eMSOnSelfCrit, _pBF, _pBO);
        cTmpMS3.SetParam(_dwFinalDamage);
        cTmpMS3.Process();
        CatEffects(cTmpMS3);
    }

    CMachineState cTmpMS3(_rField, eMSBeAtk, _pBO, _pBF);
    cTmpMS3.Process();
    CatEffects(cTmpMS3);

}

void CDmgAction::EvadeProcess()
{
    CMachineState cTmpMS2(_rField, eMSEvade, _pBO, _pBF);
    cTmpMS2.Process();
    CatEffects(cTmpMS2);

    string strInfo;
    if (_pBF)
        strInfo << *_pBF;
    if (_pBO)
        strInfo << *_pBO;
    BATTLE_DBG  << "Evade: " << (strInfo << _cBSEffect);
    SEffectAddStatusPtr pEffect (new SEffectAddStatus());
    pEffect->vecFighterID.push_back(_pBO->GetIndex());
    pEffect->eStatus = EBStatusType_Evade;
    _vecEffects.push_back(SEffectBasePtr(pEffect));

    CMachineState cTmpMS(_rField, eMSAftEvade, _pBO, _pBF);
    cTmpMS.Process();
    CatEffects(cTmpMS);
}

// 计算是否命中
bool CDmgAction::CalcHit(CBattleFighter* pBF, CBattleFighter* pBO)
{
    if (!pBF || !pBO)
        return true;
    FLOAT fModifyHit = pBF->GetAttrFinal(EFIGHTATTR_HIT) * (1 + pBF->GetAttrFinal(EFIGHTATTR_HIT_PER));
    CALC_DBG << "HIT = " << pBF->GetAttrFinal(EFIGHTATTR_HIT) << ", HIT_PER = " << pBF->GetAttrFinal(EFIGHTATTR_HIT_PER) << ", fModifyHit = " << fModifyHit << ".";
    if (fModifyHit <= 0.0001f)
        fModifyHit = 0.0001f;
    FLOAT fModifyDodge = pBO->GetAttrFinal(EFIGHTATTR_DODGE) * (1 + pBO->GetAttrFinal(EFIGHTATTR_DODGE_PER));
    CALC_DBG << "DODGE = " << pBO->GetAttrFinal(EFIGHTATTR_DODGE) << ", DODGE_PER = " << pBO->GetAttrFinal(EFIGHTATTR_DODGE_PER) << ", fModifyDodge = " << fModifyDodge << ".";
    if (fModifyDodge <= 0.0001f)
        fModifyDodge = 0.0001f;
    FLOAT fFinalDodge = fModifyDodge - fModifyHit;
    if (fFinalDodge <= 0.0001f)
        fFinalDodge = 0.0001f;
    fFinalDodge = fFinalDodge / (fFinalDodge + g_dwHitValue[1] * pBF->GetLevel() + g_dwHitValue[2]);
    if (fFinalDodge <= 0.0001f)
        fFinalDodge = 0.0001f;
    CALC_DBG << "fFinalDodge = " << fFinalDodge << ".";
    FLOAT fFinalHit = pBF->GetAttrFinal(EFIGHTATTR_HITRATE) - pBO->GetAttrFinal(EFIGHTATTR_DODGERATE) - fFinalDodge;
    if (fFinalHit <= g_dwHitMin / 10000.0f)
        fFinalHit = g_dwHitMin / 10000.0f;
    if (fFinalHit > g_dwHitMax / 10000.0f)
        fFinalHit = g_dwHitMax;
    CALC_DBG << "fFinalHit = " << fFinalHit << ".";

#ifdef _DEBUG
    if (IsDodge50())
    {
        if (CRandom::RandInt(0, 1))
        {
            //_rField.AddCombine(pBO, eCTEvade);
            return false;
        }
        else
            return true;
    }
#endif

    if (CRandom::RandFloat(0, 1) < fFinalHit)
        return true;
    else 
    {
        //_rField.AddCombine(pBO, eCTEvade);
        return false;
    }
}

CTherapyAction::CTherapyAction(CBattleField& rField, FLOAT fFactor, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO) : 
    CBattleAction(rField, rEf, pBF, pBO), _fFactor(fFactor), _dwRHP(0)
{
}

CTherapyAction::~CTherapyAction()
{
}

FLOAT CTherapyAction::GetParam() const
{
    return static_cast<FLOAT>(_dwRHP);
}


void CTherapyAction::Process()
{
    ACTION_DEBUG << "CTherapyAction: " << _fFactor << ".";

    CMachineState cTmpMS(_rField, eMSOnTherapyLaunch, _pBF, _pBO);
    cTmpMS.Process();
    CatEffects(cTmpMS);

    UINT32 _dwRHP = CalcTherapy(_pBF, _pBO, _fFactor, _cBSEffect);

    CHPChangeMachineState cHPChangeMS(_rField, _pBO, _pBO, _dwRHP, false, _cBSEffect.GetOriginSkillID(), _pBF->IsPhyJob()? EBSubHPPhy:EBSubHPMgc);
    cHPChangeMS.SetParam(_dwRHP);
    cHPChangeMS.Process();
    CatEffects(cHPChangeMS);

    CMachineState cTmpMS2(_rField, eMSSelfSideTherapy, _pBF, _pBO);
    cTmpMS2.SetParam(_dwRHP);
    cTmpMS2.Process();
    CatEffects(cTmpMS2);
}

// 计算治疗值
UINT32 CTherapyAction::CalcTherapy(CBattleFighter* pBF, CBattleFighter* pBO, FLOAT fFactor, CBattleSkillEffect& rEf)
{
    if (!pBF || !pBO)
        return 0;

    FLOAT fAtk = 0;
    if (pBF->IsPhyJob())
        fAtk = pBF->GetAttr(EFIGHTATTR_PHYATK) * (1 + pBF->GetAttr(EFIGHTATTR_PHYATK_PER));
    else if (pBF->IsMgcJob())
        fAtk = pBF->GetAttr(EFIGHTATTR_MGCATK) * (1 + pBF->GetAttr(EFIGHTATTR_MGCATK_PER));

    if (pBO->GetStateValue(EBFBuffTypeBleed))
    {
        fFactor *= 0.5;
        BATTLE_DBG << "pBO Has Bleed, fFactor = " << fFactor << ".";
    }
    if (pBO->GetStateValue(EBFBuffTypeBurned))
    {
        fFactor *= 0.5;
        BATTLE_DBG << "pBO Has Burned, fFactor = " << fFactor << ".";
    }

    UINT32 dwTherapy = (rEf.GetValue1() * fAtk / 10000 + rEf.GetValue2() + rEf.GetValue3() * pBO->GetMaxHP() / 10000) * fFactor;
    if (dwTherapy <= 0)
        dwTherapy = 1;

    return dwTherapy;
}

CAddBuffAction::CAddBuffAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO) : 
    CBattleAction(rField, rEf, pBF, pBO)
{
}

CAddBuffAction::~CAddBuffAction()
{
}

// 上Buff
void CAddBuffAction::Process()
{
    ACTION_DEBUG << "CAddBuffAction.";
    if (!_pBF || !_pBO)
        return;
    if (_pBO->GetHP() <= 0)
        return;

    bool bActive = true;

    if (_pBF->GetSide() != _pBO->GetSide())
    {
        if (_pBO->GetStateValue(EBFBuffTypeInvincible) >= 0.0001f)
        {
            bActive = false;
            BATTLE_DBG << "无敌";
        }
        else
            bActive = CalcResist(_pBF, _pBO, _cBSEffect);
    }

    // 被动技能要跳文字
    if (_pBF->IsPassiveSkillID(_cBSEffect.GetID()) && !_rField.IsPet(_pBF))
    {
        SEffectTriggerExecutePtr pEffect(new SEffectTriggerExecute);
        pEffect->vecFighterID.push_back(_pBF->GetIndex());
        pEffect->dwSkillID = SKILL_ID(_cBSEffect.GetID());
        _vecEffects.push_back(SEffectBasePtr(pEffect));
    }

    if (bActive) // 没有抵抗
    {
        CBuffAddMachineState cBuffMS(_rField, 0, _pBF, _pBO, _cBSEffect.GetID());
        cBuffMS.Process();
        CatEffects(cBuffMS);
    }
    else  // 抵抗状态 
    {
        string strInfo;
        strInfo << _cBSEffect;
        BATTLE_DBG << "Buff Resist " <<  strInfo << ".";
        SEffectAddStatusPtr pEffect (new SEffectAddStatus());
        pEffect->vecFighterID.push_back(_pBO->GetIndex());
        pEffect->eStatus = EBStatusType_Resist;
        _vecEffects.push_back(SEffectBasePtr(pEffect));
    }
}

bool CAddBuffAction::CalcResist(CBattleFighter* pBF, CBattleFighter* pBO, CBattleSkillEffect& rEf)
{
    if (rEf.GetResistType() != eResistTypeControl)
        return true;
    FLOAT fRate =  10000 * (1 - pBO->GetAttr(EFIGHTATTR_ANTIEFFECT) - pBO->GetResistFactor(rEf.GetResistType()));
    fRate /= 10000;
    if (fRate > g_dwResistMax / 10000.0f)
        fRate = g_dwResistMax / 10000.0f;
    if (fRate < g_dwResistMin / 10000.0f)
        fRate = g_dwResistMin / 10000.0f;
    CALC_DBG << "Resist = " << fRate << ".";
    if (CRandom::RandFloat(0, 1) <= fRate)
        return true;
    else
        return false;
}

CBuffEffectAction::CBuffEffectAction(CBattleField& rField, 
        CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO, 
        UINT32 dwBuffID, UINT32 dwBuffIDEX, FLOAT fParam):
    CBattleAction(rField, rEf, pBF, pBO, dwBuffID), _dwBuffIDEX(dwBuffIDEX), _fParam(fParam)
{
}

CBuffEffectAction::~CBuffEffectAction()
{
}

// Buff生效
void CBuffEffectAction::Process()
{
    ACTION_DEBUG << "CBuffEffectAction: ";
    bool bRet;
    CBattleBuff rBattleBuff = _pBF->GetBuffData(_dwBuffID, bRet);
    if (!bRet)
        return;
    BATTLE_DBG << "Buff Effect" << BFTValToStr(rBattleBuff.GetGroupBuffType()) << ".";

    // 到达特殊条件触发新的效果
    if (_pBF->AddBuffCondCount(_dwBuffID, _dwBuffIDEX, _pBO))
    {
        CBuffActMachineState cBuffMS(_rField, _fParam, _pBF, _pBO, _dwBuffID, _dwBuffIDEX);
        cBuffMS.Process();
        // 必须该Buff实际触发了效果才算真正触发
        if (cBuffMS.GetBuffEffectCount())
        {
            if (_pBF->IsPassiveSkillID(_dwBuffID) && !_rField.IsPet(_pBF))
            {
                SEffectTriggerExecutePtr pEffect(new SEffectTriggerExecute);
                pEffect->vecFighterID.push_back(_pBF->GetIndex());
                pEffect->dwSkillID = SKILL_ID(_cBSEffect.GetID());
                _vecEffects.push_back(SEffectBasePtr(pEffect));
            }
        }
        CatEffects(cBuffMS);
    }
}

CBuffOutEffectAction::CBuffOutEffectAction(CBattleField& rField, 
        CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO, 
        UINT32 dwBuffID, UINT32 dwBuffIDEX, FLOAT fParam) : 
    CBattleAction(rField, rEf, pBF, pBO, dwBuffID), _dwBuffIDEX(dwBuffIDEX), _fParam(fParam) 
{
}

// Buff失效
void CBuffOutEffectAction::Process()
{
    ACTION_DEBUG << "CBuffOutEffectAction: ";
    bool bRet;
    CBattleBuff rBattleBuff = _pBF->GetBuffData(_dwBuffID, bRet);
    if (!bRet)
        return;

    // 到达特殊条件Buff消失
    if (_pBF->AddBuffOutCondCount(_dwBuffID, _dwBuffIDEX, _pBO))
    {
        BATTLE_DBG << "Buff out Effect " << BFTValToStr(rBattleBuff.GetGroupBuffType()) << ".";
        CBuffActMachineState cBuffMS(_rField, _fParam, _pBF, _pBO, _dwBuffID, _dwBuffIDEX);
        cBuffMS.Process();
        CatEffects(cBuffMS);

        // 必须该Buff实际触发了效果才算真正触发
        if (cBuffMS.GetBuffEffectCount())
        {
            if (_pBF->IsPassiveSkillID(_dwBuffID) && !_rField.IsPet(_pBF))
            {
                SEffectTriggerExecutePtr pEffect(new SEffectTriggerExecute);
                pEffect->vecFighterID.push_back(_pBF->GetIndex());
                pEffect->dwSkillID = SKILL_ID(_cBSEffect.GetID());
                _vecEffects.push_back(SEffectBasePtr(pEffect));
            }
        }

        CBuffLostMachineState cBuffMS2(_rField, eMSOnAllLostBuff, _fParam, _pBF, _pBO, _dwBuffID, 0, true);
        cBuffMS2.Process();
        CatEffects(cBuffMS2);
    }
    else
        BATTLE_DBG << "Buff out no Effect " << BFTValToStr(rBattleBuff.GetGroupBuffType()) << ".";
}

CBuffOutEffectAction::~CBuffOutEffectAction()
{
}

CBuffReleaseEffectAction::CBuffReleaseEffectAction(CBattleField& rField, 
        CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID) : 
    CBattleAction(rField, rEf, pBF, pBO, dwBuffID)
{
}

// Buff减CD
void CBuffReleaseEffectAction::Process()
{
    ACTION_DEBUG << "CBuffReleaseEffectAction: ";
    CBattleBuff cBattleBuff;
    if (!_pBF || !_pBF->GetBuffData(_dwBuffID, cBattleBuff))
        return;
#ifdef BATTLE_SKILL_BUFF_LAST
    BATTLE_DBG << "Buff Release " << BFTValToStr(cBattleBuff.GetGroupBuffType()) << ".";
#endif

    _pBF->ReleaseCD(_dwBuffID);
    if (_pBF->GetReleaseBuffID(_dwBuffID))
    {
        CBuffLostMachineState cBuffMS(_rField, eMSOnAllLostBuff, 0, _pBF, _pBO, _dwBuffID);
        cBuffMS.Process();
        CatEffects(cBuffMS);
    }
}

CBuffReleaseEffectAction::~CBuffReleaseEffectAction()
{
}

CAuraAction::CAuraAction(CBattleField& rField, FLOAT fFactor, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO) : 
    CBattleAction(rField, rEf, pBF, pBO), _fFactor(fFactor)
{
}

CAuraAction::~CAuraAction()
{
}

// 灵气变化
void CAuraAction::Process()
{
    ACTION_DEBUG << "CAuraAction: " << _fFactor << ".";
    if (!_pBO)
        return;

    EMachineState eState = eMSNone;
    if (_fFactor > 0.1f)
        eState = eMSOnAuraAdd;
    else
        eState = eMSOnAuraSub;
    CAuraChangeMachineState cAuraChangeMS(_rField, eState, _pBO, static_cast<INT32>(_fFactor));
    cAuraChangeMS.Process();
    CatEffects(cAuraChangeMS);
}

CSummonAction::CSummonAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF, UINT8 byPos) : 
    CBattleAction(rField, rEf, pBF, NULL), _byPos(byPos)
{
}

CSummonAction::~CSummonAction()
{
}

// 召唤
void CSummonAction::Process()
{
    ACTION_DEBUG << "CSummonAction: byPos = " << static_cast<UINT32>(_byPos) << ".";

    if (!_pBF)
        return;
    UINT16 wFighterID = static_cast<UINT16>(_cBSEffect.GetValue1());
    CBattleFighterPtr pFighter = _rField.GetSummonFighter(wFighterID);
    if (!pFighter)
        return;
    CBattleFighterPtr pFighterNew = dynamic_pointer_cast<CBattleFighter>(CreateBattleFighter());
    if (!pFighterNew)
        return;
    if (!pFighterNew->SummonFromAnother(pFighter, static_cast<UINT32>(_cBSEffect.GetValue2()), _pBF))
        return;
    if (!_rField.TrySummonAppear(_pBF->GetSide(), _byPos, pFighterNew, static_cast<UINT8>(_cBSEffect.GetLast())))
        return;

    SEffectSummonPtr pEffect(new SEffectSummon);
    pEffect->wFighterID     = pFighterNew->GetID();

    pEffect->vecFighterID.push_back(DEFAULT_POS);
    pEffect->bySide         = pFighterNew->GetIndex();      // XXX: 这里Index
    pEffect->byGroupID      = pFighterNew->GetGroupID();
    pEffect->byPos          = pFighterNew->GetPos();

	pEffect->dwHpMax        = pFighterNew->GetMaxHP();      //最大血量
	pEffect->dwHp           = pFighterNew->GetHP();         //当前血量
	pEffect->dwAura         = pFighterNew->GetAura();       //当前灵气
	pEffect->dwAuraMax      = pFighterNew->GetMaxAura();    //最大灵气

    _vecEffects.push_back(SEffectBasePtr(pEffect));

    string strInfo;

    if (pFighterNew)
        strInfo << *pFighterNew;
    BATTLE_DBG << "Summon " << strInfo << ", bySide = " << (UINT32) pEffect->bySide
        << ", byGroupID = " << (UINT32) pEffect->byGroupID
        << ", byPos = " << (UINT32) pEffect->byPos;

    CEnterMachineState cEnterMS(_rField, pFighterNew.get());
    cEnterMS.SetEffectsType(eETAfter);
    cEnterMS.Process();
    CatEffects(cEnterMS);
}

CDialogAction::CDialogAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CDialogAction::~CDialogAction()
{
}

// 对话
void CDialogAction::Process()
{
    ACTION_DEBUG << "CDialogAction.";

    if (!_pBF)
        return;
    SEffectDialogPtr pEffect(new SEffectDialog);
    pEffect->vecFighterID.push_back(_pBF->GetIndex());
    pEffect->dwID = static_cast<UINT32>(_cBSEffect.GetValue1());
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

CReiatsuAction::CReiatsuAction(CBattleField& rField, INT8 byReiatsu, CBattleSkillEffect& rEF, CBattleFighter* pBF):
    CBattleAction(rField, rEF, pBF, NULL), _byReiatsu(byReiatsu)
{
}

CReiatsuAction::~CReiatsuAction()
{
}

void CReiatsuAction::Process()
{
    UINT8 bySide = _pBF->GetSide();
    if (_byReiatsu > 0)
        _pBF->AddAura(_byReiatsu);
    else if (_byReiatsu < 0)
        _pBF->SubAura(-_byReiatsu);
    _rField.SetReiatsu(bySide, _pBF->GetAura());

    SEffectSycAuraPtr pEffect(new SEffectSycAura());
    pEffect->vecFighterID.push_back(_pBF->GetIndex());
    pEffect->iAura = _rField.GetReiatsu(bySide);
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

static CBattleSkillEffect s_sNullSkillEffect;

CCombineAction::CCombineAction(CBattleField& rField, UINT8 bySide, UINT32 dwSkillID, UINT8 byCombine, UINT8 byIndex):
    CBattleAction(rField, s_sNullSkillEffect, NULL, NULL), 
    _bySide(bySide), _dwSkillID(dwSkillID), _byCombine(byCombine), _byIndex(byIndex)
{
}

CCombineAction::~CCombineAction()
{
}

void CCombineAction::Process()
{
    _rField.ResetCombine(_bySide, _dwSkillID);
    SEffectSycCombinePtr pEffect(new SEffectSycCombine());
    pEffect->vecFighterID.push_back(_byIndex);
    pEffect->iCombine = _byCombine;
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

CTransformAction::CTransformAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CTransformAction::~CTransformAction()
{
}

// 变身
void CTransformAction::Process()
{
    ACTION_DEBUG << "CTransformAction.";
    if (!_pBF)
        return;
    SEffectTransformPtr pEffect(new SEffectTransform());
    pEffect->vecFighterID.push_back(_pBF->GetIndex());
    pEffect->wFeatureID  = static_cast<UINT16>(_cBSEffect.GetValue1());
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

CToggleSkillsAction::CToggleSkillsAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CToggleSkillsAction::~CToggleSkillsAction()
{
}

// 变身
void CToggleSkillsAction::Process()
{
    ACTION_DEBUG << "CToggleSkillsAction.";
    if (!_pBF)
        return;
    _pBF->TryToggleSkills(static_cast<UINT32>(_cBSEffect.GetValue1()));
}

CPartBrokenAction::CPartBrokenAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CPartBrokenAction::~CPartBrokenAction()
{
}

// 部位破坏
void CPartBrokenAction::Process()
{
    ACTION_DEBUG << "CPartBrokenAction.";
    if (!_pBF)
        return;
    SEffectPartBrokenPtr pEffect(new SEffectPartBroken());
    pEffect->vecFighterID.push_back(_pBF->GetIndex());
    pEffect->wPartID  = static_cast<UINT16>(_cBSEffect.GetValue1());
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

CClearDebuffAction::CClearDebuffAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO) : 
    CBattleAction(rField, rEf, pBF, pBO)
{
}

CClearDebuffAction::~CClearDebuffAction()
{
}

// 清除异常状态
void CClearDebuffAction::Process()
{
    ACTION_DEBUG << "CClearDebuffAction.";
    if (!_pBO)
        return;
    TVecUINT32 vecBuffID;
    if (static_cast<EResistType>(_cBSEffect.GetValue1()) >= eResistTypeMax)
        return;
    _pBO->GetDebuffCanClear(vecBuffID, static_cast<EResistType>(_cBSEffect.GetValue1()));
    for (auto it = vecBuffID.begin(); it != vecBuffID.end(); ++it)
    {
        CBuffLostMachineState cBuffMS2(_rField, eMSOnClearBuff, 0, _pBF, _pBO, *it);
        cBuffMS2.Process();
        CatEffects(cBuffMS2);
    }
}

CBuffActionAction::CBuffActionAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CBuffActionAction::~CBuffActionAction()
{
}

// 被动技能出手动作效果
void CBuffActionAction::Process()
{
    ACTION_DEBUG << "CBuffActionAction.";
    if (!_pBF)
        return;
    SEffectBuffActionPtr pEffect(new SEffectBuffAction());
    pEffect->vecFighterID.push_back(_pBF->GetIndex());
    pEffect->dwSkillID = CBattleSkillMgr::Instance().GetOriginSkillID(_cBSEffect.GetID());
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

CTriggerAction::CTriggerAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CTriggerAction::~CTriggerAction()
{
}

// 技能跳字
void CTriggerAction::Process()
{
    ACTION_DEBUG << "CTriggerAction.";
    if (!_pBF)
        return;
    SEffectTriggerExecutePtr pEffect(new SEffectTriggerExecute);
    pEffect->vecFighterID.push_back(_pBF->GetIndex());
    pEffect->dwSkillID = static_cast<UINT32>(_cBSEffect.GetValue1());
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

CNeverDeadAction::CNeverDeadAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CNeverDeadAction::~CNeverDeadAction()
{
}

// 免疫死亡
void CNeverDeadAction::Process()
{
    ACTION_DEBUG << "CNeverDeadAction.";
    if(_pBF && _pBF->GetHP() == 0)
    {
        _pBF->RegenHP(1);
        SEffectAddHPPtr pEffect (new SEffectAddHP());
        pEffect->dwSkillID = _cBSEffect.GetID();
        pEffect->vecFighterID.push_back(_pBF->GetIndex());
        pEffect->eHPType = EBMODIFYHP_NORMAL;
        pEffect->dwAddHP = 1;
        _vecEffects.push_back(SEffectBasePtr(pEffect));
    }
}

CDeadActionAction::CDeadActionAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CDeadActionAction::~CDeadActionAction()
{
}

// 死亡动画效果
void CDeadActionAction::Process()
{
    ACTION_DEBUG << "CDeadActionAction.";
    if (!_pBF)
        return;
    TVecUINT8 vecCombineIndex;
    if(_pBF->GetHP() == 0 && _rField.OnDead(_pBF, vecCombineIndex))
    {
        SEffectDiedPtr pEffect (new SEffectDied());
        pEffect->vecFighterID.push_back(_pBF->GetIndex());
        pEffect->dwSkillID = CBattleSkillMgr::Instance().GetOriginSkillID(_cBSEffect.GetID());
        _vecEffects.push_back(SEffectBasePtr(pEffect));
    }
    for(auto& rIndex : vecCombineIndex)
    {
        SEffectCombineSlotPtr pEffect (new SEffectCombineSlot());
        pEffect->vecFighterID.push_back(rIndex);
        pEffect->eType = eCSOPTLock;
        _vecEffects.push_back(SEffectBasePtr(pEffect));
    }
}

CExtendLastAction::CExtendLastAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF) : 
    CBattleAction(rField, rEf, pBF, NULL)
{
}

CExtendLastAction::~CExtendLastAction()
{
}

// Buff延长持续回合数
void CExtendLastAction::Process()
{
    ACTION_DEBUG << "CExtendLastAction.";
    if (!_pBF)
        return;
    bool bRet;
    CBattleBuff& rBattleBuff = _pBF->GetBuffData(_cBSEffect.GetValue1(), bRet);
    if (!bRet)
        return;
    rBattleBuff.AddLast();
    SEffectStateBuffLastPtr pEffect(new SEffectStateBuffLast());
    pEffect->vecFighterID.push_back(_pBF->GetIndex());
    pEffect->byLast = rBattleBuff.GetLast();
    _vecEffects.push_back(SEffectBasePtr(pEffect));
}

CNoGainAuraAction::CNoGainAuraAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO):
    CBattleAction(rField, rEf, pBF, pBO)
{
}

CNoGainAuraAction::~CNoGainAuraAction()
{
}

// 无法获得灵气
void CNoGainAuraAction::Process()
{
    ACTION_DEBUG << "CNoGainAuraAction.";
    if (!_pBO)
        return;
    _pBO->AddEffectParam(_cBSEffect.GetID(), 1);
}

CAbsorbAction::CAbsorbAction(CBattleField& rField, CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwBuffIDEX, FLOAT fParam):
    CBattleAction(rField, rEf, pBF, pBO, dwBuffID), _dwBuffIDEX(dwBuffIDEX), _fParam(fParam)
{
}

CAbsorbAction::~CAbsorbAction()
{
}

// 吸血
void CAbsorbAction::Process()
{
    ACTION_DEBUG << "CAbsorbAction.";
    if (!_pBF || !_pBO)
        return;
    BATTLE_DBG << "_dwBuffIDEX = " << _dwBuffIDEX << ",_fParam = " << _fParam << ".";
    /*
    if (_dwBuffIDEX)
    {
        bool bRet = false;
        CBattleBuff rBattleBuff = _pBO->GetBuffData(_dwBuffIDEX, bRet);
        if (bRet)
            _fParam = rBattleBuff.GetValue1() * _pBF->GetAttack() / 10000;
    }
    */

    UINT32 dwRHP = static_cast<UINT32>(_fParam * _cBSEffect.GetValue1() / 10000);
    if (dwRHP <= 0)
        dwRHP = 1;
    CHPChangeMachineState cHPChangeMS(_rField, _pBF, _pBF, dwRHP, false, _cBSEffect.GetOriginSkillID(), _pBF->IsPhyJob()? EBSubHPPhy:EBSubHPMgc);
    cHPChangeMS.Process();
    CatEffects(cHPChangeMS);
}

CReliveAction::CReliveAction(CBattleField& rField, CBattleSkillEffect& rEf, 
        CBattleFighter* pBF, CBattleFighter* pBO):
    CBattleAction(rField, rEf, pBF, pBO, 0)
{
}

CReliveAction::~CReliveAction()
{
}

// 复活
void CReliveAction::Process()
{
    ACTION_DEBUG << "CReliveAction.";
    if (!_pBF || !_pBO)
        return;
    if (!_rField.TryRelive(_pBO, _cBSEffect.GetValue1() / 10000))
        return;

    SEffectRelivePtr pEffect(new SEffectRelive);
    pEffect->wFighterID     = _pBO->GetID();

    pEffect->vecFighterID.push_back(DEFAULT_POS);
    pEffect->bySide         = _pBO->GetIndex();      // XXX: 这里Index
    pEffect->byGroupID      = _pBO->GetGroupID();
    pEffect->byPos          = _pBO->GetPos();

	pEffect->dwHpMax        = _pBO->GetMaxHP();      //最大血量
	pEffect->dwHp           = _pBO->GetHP();         //当前血量
	pEffect->dwAura         = _pBO->GetAura();       //当前灵气
	pEffect->dwAuraMax      = _pBO->GetMaxAura();    //最大灵气

    _vecEffects.push_back(SEffectBasePtr(pEffect));

    string strInfo;
    if (_pBO)
        strInfo << *_pBO;
    BATTLE_DBG << "Relive " << strInfo << ", bySide = " << (UINT32) pEffect->bySide
        << ", byGroupID = " << (UINT32) pEffect->byGroupID
        << ", byPos = " << (UINT32) pEffect->byPos;

    CEnterMachineState cEnterMS(_rField, _pBO);
    cEnterMS.SetEffectsType(eETAfter);
    cEnterMS.Process();
    CatEffects(cEnterMS);
}

CReflectAction::CReflectAction(CBattleField& rField, CBattleSkillEffect& rEf, 
        CBattleFighter* pBF, CBattleFighter* pBO, 
        UINT32 dwBuffID, UINT32 dwBuffIDEX):
    CBattleAction(rField, rEf, pBF, pBO, dwBuffID),
    _dwBuffIDEX(dwBuffIDEX), _bNeedStopMS(false)
{
}

CReflectAction::~CReflectAction()
{
}

// 反弹异常状态
void CReflectAction::Process()
{
    ACTION_DEBUG << "CReflectAction.";
    if (!_pBF || !_pBO || !_dwBuffIDEX)
        return;

    SSkillEffect* pEffect = CBattleSkillMgr::Instance().GetSkillEf(_dwBuffIDEX);
    if (!pEffect || pEffect->_eResistType != eResistTypeControl)
        return;

    CBuffAddMachineState cBuffMS(_rField, 0, _pBF, _pBO, _dwBuffIDEX);
    cBuffMS.SetExLast(1);
    cBuffMS.Process();
    CatEffects(cBuffMS);
    _pBF->SetBuffResist(_dwBuffIDEX);
}

bool CReflectAction::NeedStopMS() const
{
    return _bNeedStopMS;
}

} // namespace NBattle

