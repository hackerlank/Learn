#include "MachineState.h"

#include "Random.h"

#include "BattleAction.h"
#include "BattleSkill.h"
#include "BattleField.h"
#include "BattleFighter.h"
#include "BattleDebugger.h"
#include "BattleArea.h"

namespace NBattle
{

CMachineState::CMachineState(CBattleField& rField, EMachineState eMS, 
        CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID /* = 0 */) : 
    _rField(rField), _eState(eMS), _eNextState(eMSNone), _pBF(pBF), _pBO(pBO), _eEffectType(eETNone), 
    _dwBuffID(dwBuffID), _fParam(0.0f)
{
}

CMachineState::CMachineState(CBattleField& rField, CBattleFighter* pBF, const TVecBattleActionPtr& rvecAction,
        UINT32 dwSkillID, const TVecUINT8& rvecTargetID, const TVecBattleTargetPos& rvecTargetPos):
    _rField(rField), _eState(eMSNone), _eNextState(eMSNone), _pBF(pBF), _pBO(NULL), _vecAction(rvecAction), 
    _eEffectType(eETNone), _fParam(0.0f)
{
    if (_pBF)
        SetCasterID(pBF->GetPos());
    _sProgress.dwSkillID = dwSkillID;
    _sProgress.vTargetID = rvecTargetID;
    _sProgress.vTargetPos = rvecTargetPos;
}

CMachineState::~CMachineState()
{
}

void CMachineState::Process()
{
    TVecBattleFighterPtr vecTargets;
    TVecBattleFighterPtr vecResponders;
    GetProcessTargets(vecTargets, vecResponders);
    auto it = vecResponders.begin();
    size_t szCount = vecTargets.size();
    for (size_t szIndex = 0; szIndex < szCount; ++ szIndex)
    {
        CBattleFighter* pFighter = vecTargets[szIndex];
        CBattleFighter* pResponder;
        if (it == vecResponders.end())
            pResponder = NULL;
        else
            pResponder = *(it++);
        GetOneStateAction(pFighter, pResponder);
    }

    ProcessAction();
}

SBattleProgress& CMachineState::GetBattleProgress() 
{ 
    return _sProgress; 
}

const SBattleProgress& CMachineState::GetBattleProgress() const 
{ 
    return _sProgress; 
}

SBattleProgress& CMachineState::GetBattleProgressFinal() 
{ 
    return _sProgressFinal; 
}

const SBattleProgress& CMachineState::GetBattleProgressFinal() const 
{ 
    return _sProgressFinal; 
}

const TVecBattleProgress& CMachineState::GetExtraProgressBefore() const
{
    return _vecExtraProgressBefore;
}

const TVecBattleProgress& CMachineState::GetExtraProgressAfter() const
{
    return _vecExtraProgressAfter;
}

void CMachineState::CatEffects(CMachineState& rMS)
{
    // ==================
    // 效果列表
    const TVecEffects& vEf = rMS.GetBattleProgress().vEffectsBefore;
    TVecEffects& rvecEffects    = GetEffectsVec(eETBefore);
    rvecEffects.insert(rvecEffects.end(), vEf.begin(), vEf.end());

    const TVecEffects& vEf2 = rMS.GetBattleProgress().vSkillEffects;
    TVecEffects& rvecEffects2   = GetEffectsVec(eETSkill);
    rvecEffects2.insert(rvecEffects2.end(), vEf2.begin(), vEf2.end());

    const TVecEffects& vEf3 = rMS.GetBattleProgress().vEffectsAfter;
    TVecEffects& rvecEffects3   = GetEffectsVec(eETAfter);
    rvecEffects3.insert(rvecEffects3.end(), vEf3.begin(), vEf3.end());

    // 效果列表
    // ==================

    // 目标列表
    const TVecUINT8& vTargetID = rMS.GetBattleProgress().vTargetID;
    _sProgress.vTargetID.insert(_sProgress.vTargetID.end(), vTargetID.begin(), vTargetID.end());

    const TVecUINT8& vTargetIDEx = rMS.GetBattleProgress().vTargetIDEx;
    _sProgress.vTargetIDEx.insert(_sProgress.vTargetIDEx.end(), vTargetIDEx.begin(), vTargetIDEx.end());

    // ==================
    // 动作列表
    const TVecBattleProgress& rvecExtraProgress = rMS.GetExtraProgressBefore();
    _vecExtraProgressBefore.insert(_vecExtraProgressBefore.end(), rvecExtraProgress.begin(), rvecExtraProgress.end());

    const TVecBattleProgress& rvecExtraProgress2 = rMS.GetExtraProgressAfter();
    _vecExtraProgressAfter.insert(_vecExtraProgressAfter.end(), rvecExtraProgress2.begin(), rvecExtraProgress2.end());
    // 动作列表
    // ==================
    
    //_sProgressFinal.vTargetID.insert(_sProgressFinal.vTargetID.end(), rMS.vTargetID.begin(), rMS.vTargetID.end());
    //_sProgressFinal.vTargetIDEx.insert(_sProgressFinal.vTargetIDEx.end(), rMS.vTargetIDEx.begin(), rMS.vTargetIDEx.end());

    const TVecEffects& vEf0 = rMS._sProgressFinal.vEffectsBefore;
    _sProgressFinal.vEffectsBefore.insert(_sProgressFinal.vEffectsBefore.end(), vEf0.begin(), vEf0.end());

    const TVecEffects& vEf02 = rMS._sProgressFinal.vSkillEffects;
    _sProgressFinal.vSkillEffects.insert(_sProgressFinal.vSkillEffects.end(), vEf02.begin(), vEf02.end());

    const TVecEffects& vEf03 = rMS._sProgressFinal.vEffectsAfter;
    _sProgressFinal.vEffectsAfter.insert(_sProgressFinal.vEffectsAfter.end(), vEf03.begin(), vEf03.end());

    const TVecMachineStatePtr& rvecMS = rMS.GetExtraMS();
    _vecExtraMS.insert(_vecExtraMS.end(), rvecMS.begin(), rvecMS.end());
}

void CMachineState::CatEffects(CBattleAction* pAction)
{
    if (!pAction)
        return;

    const TVecEffects& rvecTmp  = pAction->GetEffectsBefore();
    TVecEffects& rvecEffects    = GetEffectsVec(eETBefore);
    rvecEffects.insert(rvecEffects.end(), rvecTmp.begin(), rvecTmp.end());

    const TVecEffects& rvecTmp2 = pAction->GetEffects();
    TVecEffects& rvecEffects2   = GetEffectsVec(eETSkill);
    rvecEffects2.insert(rvecEffects2.end(), rvecTmp2.begin(), rvecTmp2.end());

    const TVecEffects& rvecTmp3 = pAction->GetEffectsAfter();
    TVecEffects& rvecEffects3   = GetEffectsVec(eETAfter);
    rvecEffects3.insert(rvecEffects3.end(), rvecTmp3.begin(), rvecTmp3.end());

    const TVecEffects& rvecTmp0  = pAction->GetEffectsBeforeFinal();
    const TVecEffects& rvecTmp02 = pAction->GetEffectsFinal();
    const TVecEffects& rvecTmp03 = pAction->GetEffectsAfterFinal();

    _sProgressFinal.vEffectsBefore.insert(_sProgressFinal.vEffectsBefore.end(), rvecTmp0.begin(), rvecTmp0.end());
    _sProgressFinal.vSkillEffects.insert(_sProgressFinal.vSkillEffects.end(), rvecTmp02.begin(), rvecTmp02.end());
    _sProgressFinal.vEffectsAfter.insert(_sProgressFinal.vEffectsAfter.end(), rvecTmp03.begin(), rvecTmp03.end());

    const TVecMachineStatePtr& rvecMS = pAction->GetExtraMS();
    _vecExtraMS.insert(_vecExtraMS.end(), rvecMS.begin(), rvecMS.end());
}

TVecEffects& CMachineState::GetEffectsVec(EEffectType eType)
{
    switch(GetEffectsType())
    {
        case eETBefore:
            return _sProgress.vEffectsBefore;
        case eETAfter:
            return _sProgress.vEffectsAfter;
        case eETSkill:
            return _sProgress.vSkillEffects;
        default:
            break;
    }
    switch(eType)
    {
        case eETBefore:
            return _sProgress.vEffectsBefore;
        case eETAfter:
            return _sProgress.vEffectsAfter;
        case eETSkill:
            return _sProgress.vSkillEffects;
        default:
            break;
    }
    return _sProgress.vSkillEffects;
}

// ===  FUNCTION  ======================================================================
//         Name:  GetStateType
//  Description:  获取该状态需要触发技能的人的范围
// =====================================================================================
EMSCheckType CMachineState::GetStateType() const
{
    EMSCheckType eMSCheckType;
    switch (_eState)
    {
        case eMSSummonTimeOut:
            eMSCheckType = eMSCTNone;
            break;
        case eMSEnter:
        case eMSOnEnter:
            if (_pBF)
                eMSCheckType = eMSCTSelf;
            else
                eMSCheckType = eMSCTOther;
            break;
        case eMSOnAllBuffGet:
        case eMSOnAllLostBuff:
        case eMSOnRoundStart:
        case eMSAftRound:
        case eMSOnKilled:
            eMSCheckType = eMSCTOther;
            break;
        case eMSSelfSideDamaged:    // 我方有单位受伤
        case eMSSelfSideDead:       // 我方有单位死亡
        case eMSSelfSideTherapy:    // 我方受到治疗效果
        case eMSOnSelfSideBuffGet:
        case eMSOnSelfPeerless:
        case eMSOnSelfCrit:
        case eMSOnSelfCounter:
            eMSCheckType = eMSCTSelfSide;      // 自己一方所有人引发的状态
            break;
        case eMSOnOtherSideBuffAct:
        case eMSOnOtherBounceDmg:
        case eMSOnOtherBeDmged://      敌方受到伤害
            eMSCheckType = eMSCTOtherSide;
            break;
        default:
            eMSCheckType = eMSCTSelf;
    }
    return eMSCheckType;
}		// -----  end of function GetStateType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetProcessTargets
//  Description:  获取触发范围对应的触发者
// =====================================================================================
void CMachineState::GetProcessTargets (TVecBattleFighterPtr& rvecTargets, TVecBattleFighterPtr& rvecResponders)
{
    EMSCheckType eType = GetStateType();
    switch(eType)
    {
        case eMSCTSelf:
            if (_pBF && _pBF->HasStateBuff(_eState))
            {
                rvecTargets.push_back(_pBF);
                rvecResponders.push_back(_pBO);
            }
            break;
        case eMSCTOther:
            {
                size_t szOldSize = rvecTargets.size();

                CBattleFighter* pScene = _rField.GetScene();
                if (pScene && pScene->HasStateBuff(_eState))
                    rvecTargets.push_back(pScene);
                _rField.GetAllAliveBattleFighterWithMS(rvecTargets, _eState);

                CBattleFighter* pPet = _rField.GetPet(0);
                if (pPet && pPet->HasStateBuff(_eState))
                    rvecTargets.push_back(pPet);
                pPet = _rField.GetPet(1);
                if (pPet && pPet->HasStateBuff(_eState))
                    rvecTargets.push_back(pPet);

                size_t szAddCount = rvecTargets.size() - szOldSize;
                while(szAddCount --)
                {
                    rvecResponders.push_back(_pBF);
                }
            }
            break;
        case eMSCTSelfSide:      // 自己一方所有人引发的状态
            if (_pBF)
            {
                UINT8 bySide = _pBF->GetSide();
                size_t szOldSize = rvecTargets.size();

                _rField.GetAllAliveBattleFighterWithMS(rvecTargets, bySide, _eState);

                CBattleFighter* pPet = _rField.GetPet(bySide);
                if (pPet && pPet->HasStateBuff(_eState))
                    rvecTargets.push_back(pPet);

                size_t szAddCount = rvecTargets.size() - szOldSize;
                while(szAddCount --)
                {
                    rvecResponders.push_back(_pBF);
                }
            }
            break;
        case eMSCTOtherSide:     // 对面一方所有人引发的状态
            if (_pBF)
            {
                UINT8 bySide = 1 - _pBF->GetSide();
                size_t szOldSize = rvecTargets.size();

                _rField.GetAllAliveBattleFighterWithMS(rvecTargets, bySide, _eState);

                CBattleFighter* pPet = _rField.GetPet(bySide);
                if (pPet && pPet->HasStateBuff(_eState))
                    rvecTargets.push_back(pPet);
                size_t szAddCount = rvecTargets.size() - szOldSize;
                while(szAddCount --)
                {
                    rvecResponders.push_back(_pBF);
                }
            }
            break;
        default:
            break;
    }
}		// -----  end of function GetProcessTargets  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetOneStateAction
//  Description:  自身在该状态下触发的行动
// =====================================================================================
void CMachineState::GetOneStateAction(CBattleFighter* pBF, CBattleFighter* pBO)
{
    if(!pBF)
        return;

    const TVecUINT32& vecBuffs = pBF->GetCondBuffID(_eState);
    TVecAttacker vecAttacker;
    TVecFieldPos vecPos;
    UINT16 wAreaID = 0;
    size_t szCount = vecBuffs.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwBuffID = vecBuffs[szIndex];
        CBattleBuff cBattleBuff;
        if(pBF->GetBuffWithState(dwBuffID, cBattleBuff))
        {
            CBattleSkillEffect cBattleSkillEffect(cBattleBuff.GetSkillEffect());
            BuildBuffAction(cBattleSkillEffect, pBF, pBO, eBBABuffEffect, dwBuffID, 0, cBattleBuff.GetRate(), vecAttacker, vecPos, wAreaID);
        }
    }

    const TVecUINT32& vecOutBuffs = pBF->GetOutCondBuffID(_eState);
    szCount = vecOutBuffs.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwBuffID = vecOutBuffs[szIndex];
        CBattleBuff cBattleBuff;
        if(pBF->GetBuff(dwBuffID, cBattleBuff))
        {
            CBattleSkillEffect cBattleSkillEffect(cBattleBuff.GetSkillEffect());
            if (_eState == eMSRelease)
                BuildBuffAction(cBattleSkillEffect, pBF, pBO, eBBABuffRelease, dwBuffID, 0, 10000, vecAttacker, vecPos, wAreaID);
            else
                BuildBuffAction(cBattleSkillEffect, pBF, pBO, eBBABuffOutEffect, dwBuffID, 0 ,cBattleBuff.GetRate(), vecAttacker, vecPos, wAreaID);
        }
    }
}		// -----  end of function GetOneStateAction  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ProcessAction
//  Description:  执行行动效果
// =====================================================================================
void CMachineState::ProcessAction()
{
    size_t szCount = _vecAction.size();
    for(size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        CBattleAction* pAction = _vecAction[szIndex];
        pAction->Process();
        CatEffects(pAction);
        if (pAction->NeedStopMS())
            _eNextState = eMSNone;
        FLOAT fParam = pAction->GetParam();
        if (fParam >= 0.01f || fParam <= -0.01f)
            _fParam = fParam;
        delete pAction;
    }
    _vecAction.clear();
    _eState = _eNextState;;
    _eNextState = eMSNone;
}		// -----  end of function ProcessAction  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetEffectsType
//  Description:  返回效果所需要放入的类型（Before/Skill/After）
// =====================================================================================
EEffectType CMachineState::GetEffectsType() const
{
    return _eEffectType;
}		// -----  end of function GetEffectsType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetEffectsType
//  Description:  设置效果的时间段类型
// =====================================================================================
void CMachineState::SetEffectsType(EEffectType eType)
{
    _eEffectType = eType;
}		// -----  end of function SetEffectsType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetExtraMS
//  Description:  获取额外的状态级
// =====================================================================================
TVecMachineStatePtr& CMachineState::GetExtraMS()
{
    return _vecExtraMS;
}		// -----  end of function GetExtraMS  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetExtraMS
//  Description:  获取额外的状态级
// =====================================================================================
const TVecMachineStatePtr& CMachineState::GetExtraMS() const
{
    return _vecExtraMS;
}		// -----  end of function GetExtraMS  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetParam
//  Description:  设置各个不同状态机的特殊值
// =====================================================================================
void CMachineState::SetParam (FLOAT fParam)
{
    _fParam = fParam;
}		// -----  end of function SetParam  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BuildSkillAction
//  Description:  根据释放的技能效果生成对应的行为动作
// =====================================================================================
bool CMachineState::BuildSkillAction(ESkillLaunchType eType, CBattleSkillEffect& rEf, 
        CBattleFighter* pBF, CBattleFighter* pBO, 
        UINT16 wProb, TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID)
{
    // 是否是释放的技能的第一个效果(后续效果可能不需要再增加涉及到目标的位置)
    bool bFirst = false;    
    if (!rAreaID || rEf.GetArea() != rAreaID)
        bFirst = true;

    TVecUINT8&              rvecTargetID    = _sProgress.vTargetID;
    TVecUINT8&              rvecTargetIDEx  = _sProgress.vTargetIDEx;
    TVecBattleTargetPos&    rvecTargetPos   = _sProgress.vTargetPos;

    if(pBO && eType != eSkillPassiveActive)     // 强制指定为某个特定目标(如混乱的攻击)
    {
        rvecAttacker.clear();
        SAttacker sAttacker;
        sAttacker._pBO          = pBO;
        sAttacker._fFactor      = 1.0f;
        sAttacker._byMainTarget = 1;
        rvecAttacker.push_back(sAttacker);

        rvecPos.clear();
        rAreaID = 0;
    }
    else
        _rField.GetTargetList(pBF, pBO, rEf.GetArea(), rvecAttacker, rvecPos, rAreaID);

    // 主动技能没有主目标，直接不执行该主动技能
    if (rvecAttacker.empty() && rvecPos.empty()) 
        return false;

    EBBAType eBAType = eBBAActiveSkill;
    if (eType >= eSkillPassiveBegin && eType < eSkillPassiveEnd)
        eBAType = eBBANoPosActiveSkill;
    // 有目标单位的效果
    for (auto& rAttacker : rvecAttacker)
    {
        UINT16 wRand = CRandom::RandInt(0, 9999);
        if(wRand >= wProb)
            continue;

        bool bHited;    // 参数接口需要
        CBattleAction* pAction = GetBattleAction(rAttacker._byMainTarget, rAttacker._fFactor, rEf, 
                pBF, rAttacker._pBO, bHited, eBAType, 0, 0, rAttacker._pBO->GetPos());
        if (pAction)
        {
            _vecAction.push_back(pAction);
            if (eType == eSkillPassiveActive )
                rvecTargetID.push_back(rAttacker._pBO->GetIndex());
            else if ( bHited 
                     && (eType != eSkillPassiveCombine || bFirst) //  连携技能只要第一个人的目标选择ID就好了
                    )
            {
                if (rAttacker._byMainTarget)    //  属于技能效果范围主目标
                    rvecTargetID.push_back(rAttacker._pBO->GetIndex());
                else //  属于技能效果范围波及目标
                    rvecTargetIDEx.push_back(rAttacker._pBO->GetIndex());
            }
        }
    }

    // 没有目标单位，仅坐标上的效果
    for (auto& rPos : rvecPos)
    {
        bool bHited;    // 参数接口需要
        CBattleAction* pAction = GetBattleAction(rPos.bMainTarget, rPos.fFactor, rEf, 
                pBF, NULL, bHited, eBAType, 0, 0, rPos.byPos);
        if (pAction)
            _vecAction.push_back(pAction);
        rvecTargetPos.push_back(SBattleTargetPos(rPos.byGroupID, rPos.byPos));
    }

    return true;
}		// -----  end of function BuildSkillAction  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BuildBuffAction
//  Description:  根据Buff触发的技能效果生成对应的行为动作
// =====================================================================================
UINT32 CMachineState::BuildBuffAction(CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO, 
        EBBAType eType, UINT32 dwBuffID, UINT32 dwBuffIDEX, UINT16 wProb,
        TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID)
{
    TVecBattleActionPtr vecAction;

    bool bHited;    // 参数接口需要
    CBattleAction* pAction = GetBattleAction(1, GetParam(), rEf, pBF, pBO, bHited, eType, dwBuffID, dwBuffIDEX, DEFAULT_POS);
    if (pAction)
        vecAction.push_back(pAction);
    _vecAction.insert(_vecAction.end(), vecAction.begin(), vecAction.end());
    return vecAction.size();
}		// -----  end of function BuildBuffAction  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BuildBuffActAction
//  Description:  根据Buff触发的技能效果生成对应的行为动作
// =====================================================================================
UINT32 CMachineState::BuildBuffActAction(CBattleSkillEffect& rEf, CBattleFighter* pBF, CBattleFighter* pBO, 
        UINT32 dwBuffID, UINT32 dwBuffIDEX, UINT16 wProb,
        TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID)
{
    TVecBattleActionPtr vecAction;

    TVecUINT8 vecTargetID;
    TVecBattleTargetPos vecTargetPos;

    _rField.GetTargetList(pBF, pBO, rEf.GetArea(), rvecAttacker, rvecPos, rAreaID);

    // 有目标单位的效果
    size_t szCount = rvecAttacker.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        // 效果对应的范围每个都要独立计算概率
        const SAttacker& rAttacker = rvecAttacker[szIndex];
        UINT16 wRand = CRandom::RandInt(0, 9999);
        if(wRand >= wProb)
            continue;

        bool bHited = false; // 是否打中目标
        CBattleAction* pAction = GetBattleAction(rAttacker._byMainTarget, rAttacker._fFactor, rEf, 
                pBF, rAttacker._pBO, bHited, eBBABuffAct, 
                dwBuffID, dwBuffIDEX, rAttacker._pBO->GetPos());
        if (pAction)
        {
            vecAction.push_back(pAction);
            if (rAttacker._byMainTarget && bHited)
                vecTargetID.push_back(rAttacker._pBO->GetIndex());
        }
    }

    // 没有目标单位，仅坐标上的效果
    szCount = rvecPos.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        const SFieldPos& rPos = rvecPos[szIndex];
        bool bHited;    // 参数接口需要
        CBattleAction* pAction = GetBattleAction(rPos.bMainTarget?1:0, rPos.fFactor, rEf, 
                pBF, NULL, bHited, eBBABuffAct, 
                dwBuffID, dwBuffIDEX, rPos.byPos);
        if (pAction)
            vecAction.push_back(pAction);
        vecTargetPos.push_back(SBattleTargetPos(rPos.byGroupID, rPos.byPos));
    }

    // XXX: 场景技能放在当前行动回合之后
    if (pBF && pBF->GetPos() == SCENE_POS)
    {
        CMachineState cMS(_rField, pBF, vecAction, rEf.GetID(), vecTargetID, vecTargetPos);
        cMS.ProcessAction();
        _vecExtraProgressBefore.push_back(cMS.GetBattleProgress());
    }
    else if (pBF && 
            (pBF->GetPos() == BEAUTY_POS || pBF->GetPos() == BEAUTY_POS + 1))
    {
        CMachineState cMS(_rField, pBF, vecAction, rEf.GetID(), vecTargetID, vecTargetPos);
        cMS.SetEffectsType(eETAfter);
        cMS.ProcessAction();

        {
            const TVecEffects& vEf = cMS.GetBattleProgress().vEffectsBefore;
            TVecEffects& rvecEffects = _sProgressFinal.vEffectsAfter;
            rvecEffects.insert(rvecEffects.end(), vEf.begin(), vEf.end());

            const TVecEffects& vEf2 = cMS.GetBattleProgress().vSkillEffects;
            rvecEffects.insert(rvecEffects.end(), vEf2.begin(), vEf2.end());

            const TVecEffects& vEf3 = cMS.GetBattleProgress().vEffectsAfter;
            rvecEffects.insert(rvecEffects.end(), vEf3.begin(), vEf3.end());
        }
        {
            const TVecEffects& vEf = cMS.GetBattleProgressFinal().vEffectsBefore;
            TVecEffects& rvecEffects = _sProgressFinal.vEffectsAfter;
            rvecEffects.insert(rvecEffects.end(), vEf.begin(), vEf.end());

            const TVecEffects& vEf2 = cMS.GetBattleProgressFinal().vSkillEffects;
            rvecEffects.insert(rvecEffects.end(), vEf2.begin(), vEf2.end());

            const TVecEffects& vEf3 = cMS.GetBattleProgressFinal().vEffectsAfter;
            rvecEffects.insert(rvecEffects.end(), vEf3.begin(), vEf3.end());
        }
    }
    else
        _vecAction.insert(_vecAction.end(), vecAction.begin(), vecAction.end());
    return vecAction.size();
}		// -----  end of function BuildBuffActAction  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleAction
//  Description:  各种技能特效引发的动作效果
// =====================================================================================
CBattleAction* CMachineState::GetBattleAction(UINT8 byMainTarget, FLOAT fParam, CBattleSkillEffect& rEf, 
        CBattleFighter* pBF, CBattleFighter* pBO, bool& rHited,
        EBBAType eType, UINT32 dwBuffID, UINT32 dwBuffIDEX, UINT8 byPos)
{
    CBattleAction* pAction = NULL;
    rHited = false;

    if (eType == eBBABuffRelease)
    {
        pAction = (new CBuffReleaseEffectAction(_rField, rEf, pBF, pBO, dwBuffID));
        return pAction;
    }

    string strInfo;
    if (pBF)
        strInfo << *pBF;
    if (pBO)
        strInfo << *pBO;
    BATTLE_DBG << (strInfo << rEf);
    switch(rEf.GetType())
    {
        case EPhyDmg: //物理伤害
        case EMgcDmg: //法术伤害
        case ETrueDmg: // 真实伤害
        case EHPDmg: //生命百分比伤害
            if (pBO)
            {
                EDamageType eDmgType = eDTNone;
                switch (eType)
                {
                    case eBBAActiveSkill:   // 主动技能造成的伤害
                        rHited = true;
                        eDmgType = eDTActive;
                        break;
                    case eBBANoPosActiveSkill: //  非主动释放的技能
                        rHited = true;
                        eDmgType = eDTNoPosActive;
                        break;
                    case eBBABuffAct:  // 身上Buff带出的伤害
                        {
                            CBattleBuff cBuff;
                            if(pBF->GetBuff(_dwBuffID, cBuff))
                                pBF = cBuff.GetGiver();
                            eDmgType = eDTBuff;
                        }
                        break;
                    default:
                        break;
                }
                pAction = (new CDmgAction(_rField, byMainTarget, fParam, rEf, pBF, pBO, dwBuffID, eDmgType));
            }
            break;
        case EBounceDmg: // 反伤
            if (GetParam() >= 1.0f && pBO)
                pAction = (new CDmgAction(_rField, byMainTarget, GetParam(), rEf, pBF, pBO, dwBuffID, eDTBounce));
            break;
        case EAbsorb:
            pAction = (new CAbsorbAction(_rField, rEf, pBF, pBO, dwBuffID, dwBuffIDEX, GetParam()));
            break;
        case ETherapy: //回复
            if (pBO)
            {
                pAction = (new CTherapyAction(_rField, fParam, rEf, pBF, pBO));
                // 主动技能需要受击特效
                if (eType == eBBAActiveSkill || eType == eBBANoPosActiveSkill)
                    rHited = true;
            }
            break; 
        case EAuraSub: //减少灵气
            fParam = -rEf.GetValue1();
            if (pBO)
                pAction = (new CAuraAction(_rField, fParam, rEf, pBF, pBO));
            break;
        case EAuraAdd: //增加灵气
            fParam = rEf.GetValue1();
            if (pBO)
                pAction = (new CAuraAction(_rField, fParam, rEf, pBF, pBO));
            break;
        case ESummon: // 在召唤
            if (pBF && pBF->GetPos() == byPos)
                byPos = DEFAULT_POS;
            pAction = (new CSummonAction(_rField, rEf, pBF, byPos));
            break;
        case EDialog:  // 对话技能
            pAction = (new CDialogAction(_rField, rEf, pBF));
            break;
        case ETransForm: // 变身
            pAction = (new CTransformAction(_rField, rEf, pBF));
            break;
        case EToggleSkills: // 切换技能
            pAction = (new CToggleSkillsAction(_rField, rEf, pBF));
            break;
        case EPartBroken: // 部位破坏
            pAction = (new CPartBrokenAction(_rField, rEf, pBF));
            break;
        case EClearDebuff: // 清除Buff
            pAction =  (new CClearDebuffAction(_rField, rEf, pBF, pBO));
            break;
        case EBuffAction: // 被动技能出手
        case EBuffAction2: // 被动技能出手
            pAction = (new CBuffActionAction(_rField, rEf, pBF));
            break;
        case ESkillTrigger: // 技能跳文字
            pAction = (new CTriggerAction(_rField, rEf, pBF));
            break;
        case EDeadAction:   // 死亡
            pAction = (new CDeadActionAction(_rField, rEf, pBF));
            break;
        case ENeverDead:    // 无法死亡
            pAction = (new CNeverDeadAction(_rField, rEf, pBF));
            break;
        case ENoGainAura:   //  无法获得灵气
            pAction = (new CNoGainAuraAction(_rField, rEf, pBF, pBO));
            break;
        case ERevival: // 复活
            pAction = (new CReliveAction(_rField, rEf, pBF, pBO));
            break;
        case EReflect: // 反弹状态
            pAction = (new CReflectAction(_rField, rEf, pBF, pBO, dwBuffID, dwBuffIDEX));
            break;
        default:
            if (eType == eBBABuffEffect)
                pAction = (new CBuffEffectAction(_rField, rEf, pBF, pBO, dwBuffID, _dwBuffID, GetParam()));
            else if (eType == eBBABuffOutEffect)
                pAction = (new CBuffOutEffectAction(_rField, rEf, pBF, pBO, dwBuffID, _dwBuffID, GetParam()));
            else
                pAction = (new CAddBuffAction(_rField, rEf, pBF, pBO));
            break;
    }

    return pAction;
}		// -----  end of function GetBattleAction  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetParam
//  Description:  返回各个不同状态机的特殊值
// =====================================================================================
FLOAT CMachineState::GetParam() const
{
    return _fParam;
}		// -----  end of function GetParam  ----- //

void  CMachineState::SetCasterID(UINT8 byID, UINT8 byIndex /* = 0 */)
{
    if (_sProgress.vecCasterIndex.size() < static_cast<size_t>(byIndex + 1))
        _sProgress.vecCasterIndex.resize(byIndex + 1);
    _sProgress.vecCasterIndex[byIndex] = byID;
}

CDeadMachineState::CDeadMachineState(CBattleField& rField, CBattleFighter* pBF, bool bIsSummonTimeOut /* = false */) : 
    CMachineState(rField, eMSBeforeDead, pBF, NULL), _bIsSummonTimeOut(bIsSummonTimeOut)
{
}

CDeadMachineState::~CDeadMachineState()
{
}

void CDeadMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        switch (_eState)
        {
            case eMSBeforeDead:
                _eNextState = eMSOnDead;
                break;
            case eMSOnDead:
                if (!_bIsSummonTimeOut && _pBF->GetHP() > 0) // 已经不死了
                {
                    bEnd = true;
                    break;
                }
                _eNextState = eMSOnKilled;
                break;
            case eMSOnKilled:
                _eNextState = eMSSelfSideDead;
                break;
            case eMSSelfSideDead:
                {
                    TVecBattleFighterPtr vecFighter;
                    _rField.GetSideAliveTargets(_pBF->GetSide(), vecFighter);
                    if (vecFighter.empty())
                        _eNextState = eMSSelfSideDeadAll;
                    else
                        _eNextState = eMSAftDead;
                }
                break;
            case eMSSelfSideDeadAll:
                _eNextState = eMSAftDead;
                break;
            case eMSAftDead:
                {
                    TVecUINT8 vecCombineIndex;
                    if((_pBF->GetHP() == 0 || _bIsSummonTimeOut) && _rField.OnDead(_pBF, vecCombineIndex))
                    {
                        TSetUINT32 setBuffID;
                        _pBF->GetAllBuffID(setBuffID);

                        // 清除身上的Buff
                        for (auto& dwBuffID : setBuffID)
                        {
                            CBuffLostMachineState cBuffMS(_rField, eMSOnAllLostBuff, GetParam(), _pBF, _pBO, dwBuffID);
                            cBuffMS.Process();
                            CatEffects(cBuffMS);
                        }

                        // 协议中加入死亡效果通知客户端
                        SEffectDiedPtr pEffect (new SEffectDied());
                        pEffect->vecFighterID.push_back(_pBF->GetIndex());
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                    }

                    // 关闭相关连携技能的连携槽
                    for(auto& rIndex : vecCombineIndex)
                    {
                        SEffectCombineSlotPtr pEffect (new SEffectCombineSlot());
                        pEffect->vecFighterID.push_back(rIndex);
                        pEffect->eType = eCSOPTLock;
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                    }
                }
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CDeadMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

CEnterMachineState::CEnterMachineState(CBattleField& rField, CBattleFighter* pFighter /* = NULL */):
    CMachineState(rField, eMSEnter, pFighter, NULL)
{
}

CEnterMachineState::~CEnterMachineState()
{
}

void CEnterMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        STATE_DEBUG << "CEnterMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        switch(_eState)
        {
            case eMSEnter:
                {
                    TVecBattleFighterPtr vecBattleFighterPtr;
                    if (!_pBF)
                        _rField.GetAllAliveBattleFighter(vecBattleFighterPtr);
                    else
                        vecBattleFighterPtr.push_back(_pBF);

                    // 加载入场Buff
                    for (auto & pBattleFighter : vecBattleFighterPtr)
                    {
                        TSetUINT32 setBuffID;
                        pBattleFighter->GetAllBuffID(setBuffID);
                        for (auto& rID : setBuffID)
                        {
                            CBattleBuff cBattleBuff;
                            if(pBattleFighter->GetBuff(rID, cBattleBuff))
                            {
                                SEffectStateBuffAddPtr pEffect(new SEffectStateBuffAdd());
                                pEffect->vecFighterID.push_back(pBattleFighter->GetIndex());
                                pEffect->dwBuffKey      = cBattleBuff.GetInstID();
                                pEffect->eStateBuffType = cBattleBuff.GetGroupBuffType();
                                pEffect->dwSkillID      = cBattleBuff.GetID();
                                pEffect->byLast         = cBattleBuff.GetLast();
                                pEffect->dwValue        = static_cast<INT32>(cBattleBuff.GetValue1());
                                _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                            }
                        }
                    }

                    // 没有人出手
                    SetCasterID(DEFAULT_POS);
                    _eNextState = eMSOnEnter;
                }
                break;
            case eMSOnEnter:
                SetCasterID(DEFAULT_POS);
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        CMachineState::Process();
    }
}

CMainMachineState::CMainMachineState(CBattleField& rField, bool bEndRound) : 
    CMachineState(rField, eMSStart, NULL, NULL), _bRounedEnd(bEndRound), _byActiveSide(0)
{
    if (_bRounedEnd)
        _eState = eMSOnRoundStart;
}

CMainMachineState::~CMainMachineState()
{
}

void CMainMachineState::Process()
{
    bool bEnd = false;
    SetEffectsType(eETBefore);
    while(!bEnd)
    {
        STATE_DEBUG << "CMainMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        switch(_eState)
        {
            case eMSOnRoundStart:
                _eNextState = eMSBeforeRound;
                break;
            case eMSBeforeRound:
                _eNextState = eMSStart;
                break;
            case eMSStart:
                Start();
                break;
            case eMSBeforeAct:
                BeforeAct();
                break;
            case eMSOnAct:
                SetEffectsType(eETSkill);
                ActiveAct();
                break;
            case eMSAfterAct:
                SetEffectsType(eETAfter);
                AfterAct();
                break;
            case eMSRelease:
                if (_pBF)
                {
                    _pBF->ClearEffectParam();
                    _pBF->ResetTurnCD();
                }
                if (_pBF && _pBF->GetSummonLast())
                    _eNextState = eMSSummonTimeOut;
                else
                {
                    if (_bRounedEnd)
                        _eNextState = eMSAftRound;
                    else
                        bEnd = true;
                }
                break;
            case eMSSummonTimeOut:
                {
                    ReleaseSummonTime();
                    if (_bRounedEnd)
                        _eNextState = eMSAftRound;
                    else
                        bEnd = true;
                }
                break;
            case eMSAftRound:
                bEnd = true;
                break;
            default:
                bEnd = true;
                break;
        }
        CMachineState::Process();
    }
    STATE_DEBUG << "CMainMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
}

bool CMainMachineState::IsRoundEnd() const
{
    return _bRounedEnd;
}

UINT8 CMainMachineState::GetActiveSide() const
{
    return _byActiveSide;
}

void CMainMachineState::Start()
{
    _rField.DumpListInfo();

    CBattleFighter* pBF = _rField.PopCurrentFighter(_bRounedEnd);
    if(!pBF)
    {
        _eNextState = eMSRelease;
        return;
    }
    _byActiveSide = pBF->GetSide();

    SetCasterID(pBF->GetIndex());
    _rField.PushFighterToNext(pBF);
    _eNextState = eMSBeforeAct;
    _pBF = pBF;

    _rField.DumpListInfo();
}

void CMainMachineState::BeforeAct()
{
    if (_pBF->HaveState(EBFBuffTypeFreeze))
    {
        UINT8 byRet = CRandom::RandInt(0, 1);
        if(byRet) // 无法行动
        {
            _eNextState = eMSAfterAct;
            return;
        }
        else // 可以行动，冰块碎裂
        {
            TSetUINT32 setBuffID;
            if (_pBF->GetStateBuffID(EBFBuffTypeFreeze, setBuffID))
            {
                for (auto & rID : setBuffID)
                {
                    CBattleBuff cBattleBuff;
                    if(_pBF->GetBuff(rID, cBattleBuff))
                    {
                        CBattleSkillEffect ef(cBattleBuff.GetSkillEffect());
                        CBuffLostMachineState cBuffMS2(_rField, eMSOnAllLostBuff, GetParam(), _pBF, NULL, rID);
                        cBuffMS2.SetEffectsType(eETBefore);
                        cBuffMS2.Process();
                        CatEffects(cBuffMS2);
                    }
                }
            }
        }
    }
    if (_pBF->HaveState(EBFBuffTypeStun))
        _eNextState = eMSAfterAct;
    else
        _eNextState = eMSOnAct;
}

void CMainMachineState::ActiveAct() 
{
    CAttackMachineState attackMs(_rField, _pBF, _pBO);
    attackMs.Process();

    CatEffects(attackMs);

    _sProgress.dwSkillID = attackMs.GetBattleProgress().dwSkillID;
    _eNextState = eMSAfterAct;
}

void CMainMachineState::AfterAct()
{
    SyncCombineCount();
    _eNextState = eMSRelease;
}

void CMainMachineState::ReleaseSummonTime()
{
    UINT8 bySumonLast = _pBF->GetSummonLast();
    if (bySumonLast)
    {
        _pBF->SetSummonLast(--bySumonLast);
        if (!bySumonLast)
        {
            CDeadMachineState cBuffMS(_rField, _pBF, true);
            cBuffMS.Process();
            CatEffects(cBuffMS);
        }
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  SyncCombineCount
//  Description:  同步连携点(用于触发连携点增加的情况后，统一时段更新连携点)
// =====================================================================================
void CMainMachineState::SyncCombineCount()
{
    UINT8 bySide            = _byActiveSide;
    UINT8 byIndex           = 0;
    UINT8 byNewCombineCount = 0;

    // 行动方连携点
    TVecUINT8 vecCombineType;
    while(_rField.GetNewCombineCount(bySide, byIndex, byNewCombineCount, vecCombineType))
    {
        SEffectSycCombinePtr pEffect(new SEffectSycCombine());
        pEffect->vecFighterID.push_back(byIndex);
        pEffect->iCombine = byNewCombineCount;
        pEffect->vecSycType = vecCombineType;
        _sProgress.vEffectsAfter.push_back(SEffectBasePtr(pEffect));
    }

    // 非行动方连携点
    bySide = 1 - bySide;
    vecCombineType.clear();
    while(_rField.GetNewCombineCount(bySide, byIndex, byNewCombineCount, vecCombineType))
    {
        SEffectSycCombinePtr pEffect(new SEffectSycCombine());
        pEffect->vecFighterID.push_back(byIndex);
        pEffect->iCombine = byNewCombineCount;
        pEffect->vecSycType = vecCombineType;
        _sProgress.vEffectsAfter.push_back(SEffectBasePtr(pEffect));
    }
}		// -----  end of function SyncCombineCount  ----- //

CDamageMachineState::CDamageMachineState(CBattleField& rField, CBattleFighter* pBF, CBattleFighter* pBO, 
        UINT32 dwDamage, bool bCri, UINT32 dwSkillID, EDamageType eDTType) : 
    CMachineState(rField, eMSBeforeDmg, pBF, pBO), _dwDamdge(dwDamage), _dwShieldDmg(0), _bCri(bCri), _dwSkillID(dwSkillID), _eDTType(eDTType)
{
}

CDamageMachineState::~CDamageMachineState()
{
}

void CDamageMachineState::Process()
{
    STATE_DEBUG << "CDamageMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
    bool bEnd = false;
    bool bBlocked = false;;
    while(!bEnd)
    {
        switch (_eState)
        {
            case eMSBeforeDmg: // 受到伤害前
                // 无敌
                if (_pBF->GetStateValue(EBFBuffTypeInvincible) >= 0.0001f)
                {
#ifdef BATTLE_HP_CHANGE
                    BATTLE_DBG << "无敌";
#endif
                    bEnd = true;
                }
                else
                {
                    // 只有不是反伤的才有伤害减免
                    if (_eDTType != eDTBounce)  
                    {
                        FLOAT fFinalParam = CalcDamageFactor(_pBF, _pBO, bBlocked);

                        _dwDamdge = static_cast<UINT32>(static_cast<FLOAT>(_dwDamdge) * fFinalParam);
#ifdef BATTLE_HP_CHANGE
                        BATTLE_DBG << "_dwDamdge = " << _dwDamdge << ", fFinalParam = " << fFinalParam << ".";
#endif
                        // 虽然算完了实际伤害，But还要分一部分伤害给有分担伤害BUff的人
                        if (!_dwDamdge)
                            _dwDamdge = 1;

                        // 分担伤害只有一次
                        if (_eDTType != eDTShare)
                        {
                            FLOAT fShareFactor = 0.0f;
                            fShareFactor = _pBF->GetStateValue(EBFBuffTypeDmgShare);
                            // 有人可以帮忙分担伤害
                            if (fShareFactor >= 0.0001f)
                            {
                                UINT32 dwShareDmg = static_cast<UINT32>(_dwDamdge * fShareFactor);
                                if (dwShareDmg > _dwDamdge)
                                    dwShareDmg = _dwDamdge;
                                _dwDamdge -= dwShareDmg;

                                // 需要分担伤害
                                if (dwShareDmg > 0)
                                {
                                    TSetUINT32 setBuffID;

                                    // 寻找分担伤害的对应BUFF
                                    if (_pBF->GetStateBuffID(EBFBuffTypeDmgShare, setBuffID) && !setBuffID.empty())
                                    {
                                        dwShareDmg = dwShareDmg / setBuffID.size();
                                        if (!dwShareDmg)
                                            dwShareDmg = 1;

                                        // 遍历所有分担伤害的Buff的ID，来逐一寻找对应的人来分担伤害
                                        for (auto& rID : setBuffID)
                                        {
                                            SSkillEffect* pSkillEffect = CBattleSkillMgr::Instance().GetSkillEf(rID);
                                            if (!pSkillEffect)
                                                continue;

                                            CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(pSkillEffect->_wArea);
                                            if (!pArea || pArea->GetFighterID().empty())
                                                continue;

                                            TVecBattleFighterPtr vecFighters;
                                            _rField.GetIDTargets(_pBF->GetSide(), vecFighters, pArea->GetFighterID());

                                            // 遍历分担伤害的所有人员
                                            for(auto& pFighter : vecFighters)
                                            {
                                                if (pFighter != _pBF) // 自己不会分担自己的伤害
                                                {
                                                    CDamageMachineState cDamageMS(_rField, pFighter, _pBO, dwShareDmg, _bCri, _dwSkillID, eDTShare);
                                                    cDamageMS.Process();
                                                    CatEffects(cDamageMS);
                                                }
                                            }
                                        }
                                    }
                                    else
                                        _dwDamdge += dwShareDmg;
                                }
                            }
                        }
                        if (!_dwDamdge)
                            _dwDamdge = 1;
                    }
                    _eNextState = eMSBeDmged;
                }
                break;

            case eMSBeDmged:  // 受到伤害时
                {
                    TVecUINT32 vecBuffKey;
                    _dwShieldDmg = _pBF->MakeShieldDmg(_dwDamdge, vecBuffKey);
                    // 护盾吸收一部分伤害
                    if (_dwShieldDmg)
                    {
#ifdef BATTLE_HP_CHANGE
                        BATTLE_DBG << "ShieldDamage: " << _dwShieldDmg << ", now shield: " << (UINT32)_pBF->GetStateValue(EBFBuffTypeShield) << ".";
#endif
                        SEffectShieldAbsorbPtr pEffect(new SEffectShieldAbsorb());
                        pEffect->vecFighterID.push_back(_pBF->GetIndex());
                        pEffect->eType = EBSheildAbsorbDamage;
                        pEffect->dwHP = _dwShieldDmg;
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                    }
                    for (auto& rKey : vecBuffKey)
                    {
                        SEffectStateBuffDecPtr pEffect(new SEffectStateBuffDec());
                        pEffect->vecFighterID.push_back(_pBF->GetIndex());
                        pEffect->dwBuffKey = rKey;
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                    }

                    // 实际对生命造成的伤害
                    if (_dwDamdge > 0)
                    {
                        EBSubHPType eSubHPType = _pBO ?
                            (_pBO->IsPhyJob()?EBSubHPPhy:EBSubHPMgc) : (_pBF->IsPhyJob()?EBSubHPPhy:EBSubHPMgc);
                        if (_eDTType == eDTBounce)
                            eSubHPType = _pBF->IsPhyJob()?EBSubHPPhy:EBSubHPMgc;
                        INT32 dwHPChange = -_dwDamdge;
                        CHPChangeMachineState hpChangeMs(_rField, _pBF, _pBO, dwHPChange, _bCri, _dwSkillID, eSubHPType, (_eDTType == eDTCounter)?true:false);
                        hpChangeMs.Process();
                        CatEffects(hpChangeMs);
                    }

                    _eNextState = eMSSelfSideDamaged;
                }
                break;
            case eMSSelfSideDamaged:
                _eNextState = eMSOnOtherBeDmged;
                break;
            case eMSOnOtherBeDmged:
                _eNextState = eMSAftDmg;
                break;
            case eMSAftDmg:     // 受伤害结束
                if (bBlocked )
                {
                    CMachineState cTmpMS(_rField, eMSAftBlocked, _pBF, _pBO);
                    cTmpMS.Process();
                    CatEffects(cTmpMS);
                }
                if (_eDTType == eDTBounce)  
                {
                    CMachineState cTmpMS(_rField, eMSOnOtherBounceDmg, _pBF, _pBO);
                    cTmpMS.Process();
                    CatEffects(cTmpMS);
                }
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        CMachineState::Process();
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  GetParam
//  Description:  返回主动技能造成的实际伤害值
// =====================================================================================
FLOAT CDamageMachineState::GetParam() const
{
    return _dwDamdge + _dwShieldDmg;
}		// -----  end of function GetParam  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CalcDamageFactor
//  Description:  计算伤害增减益因数
// =====================================================================================
FLOAT CDamageMachineState::CalcDamageFactor(CBattleFighter* pBF, CBattleFighter* pBO, bool &rBlocked)
{
    rBlocked = false;
    FLOAT fFinalParam = 1.0f;
    if (!pBF)
        return fFinalParam;
    
    // 是否产生了格挡
    if (pBF->GetStateValue(EBFBuffTypeBlock) > 0.1f && CRandom::RandInt(0, 1))
    {
        string strInfo;
        if (pBF)
            strInfo << *pBF;
        if (pBO)
            strInfo << *pBO;
        BATTLE_DBG  << "Block: " << strInfo;
        SEffectAddStatusPtr pEffect (new SEffectAddStatus());
        pEffect->vecFighterID.push_back(pBF->GetIndex());
        pEffect->eStatus = EBStatusType_Block;
        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));

        fFinalParam -= 0.5f;
#ifdef BATTLE_HP_CHANGE
        BATTLE_DBG << "Damage Blocked, fFinalParam = " << fFinalParam << ".";
#endif
        rBlocked = true;


        _rField.AddCombine(pBF, eCTBlock);

        TSetUINT32 setBuffID;
        if (pBF->GetStateBuffID(EBFBuffTypeBlock, setBuffID))
        {
            for (auto & rID : setBuffID)
            {
                CBattleBuff cBattleBuff;
                if(pBF->GetBuff(rID, cBattleBuff))
                {
                    CBattleSkillEffect ef(cBattleBuff.GetSkillEffect());
                    CBuffActMachineState cBuffMS2(_rField, GetParam(), pBF, NULL, rID);
                    cBuffMS2.SetEffectsType(eETBefore);
                    cBuffMS2.Process();
                    CatEffects(cBuffMS2);
                }
            }
        }
    }

    // 石化效果
    FLOAT fStonedFactor = pBF->GetStateValue(EBFBuffTypeStoned) / 10000;
    if (fStonedFactor >= 0.0001f && CRandom::RandInt(0, 1))
    {
        TSetUINT32 setBuffID;
        if (pBF->GetStateBuffID(EBFBuffTypeStoned, setBuffID))
        {
            for (auto & rID : setBuffID)
            {
                CBattleBuff cBattleBuff;
                if(pBF->GetBuff(rID, cBattleBuff))
                {
                    CBattleSkillEffect ef(cBattleBuff.GetSkillEffect());
                    CBuffActMachineState cBuffMS2(_rField, GetParam(), pBF, NULL, rID);
                    cBuffMS2.SetEffectsType(eETBefore);
                    cBuffMS2.Process();
                    CatEffects(cBuffMS2);
                }
            }
        }
        fFinalParam += 0.5f;
#ifdef BATTLE_HP_CHANGE
        BATTLE_DBG << "Damage Stoned, fFinalParam = " << fFinalParam << ".";
#endif
    }

    // 分身效果
    FLOAT fCloneFactor = pBF->GetStateValue(EBFBuffTypeClone) / 10000;
    if (fCloneFactor >= 0.0001f)
    {
        fFinalParam -= fCloneFactor;
#ifdef BATTLE_HP_CHANGE
        BATTLE_DBG << "Damage Clone, fFinalParam = " << fFinalParam << ".";
#endif
    }

    // 掩护效果引起的光环蓝
    FLOAT fHeloBlue = pBF->GetStateValue(EBFBuffTypeHaloBlue);
    if (fHeloBlue >= 0.0001f)
    {
        fFinalParam -= fHeloBlue;
#ifdef BATTLE_HP_CHANGE
        BATTLE_DBG << "Damage HaloBlue, fFinalParam = " << fFinalParam << ".";
#endif
    }

    // 光环红造成的伤害提升
    if (pBO)
    {
        FLOAT fHeloRed = pBO->GetStateValue(EBFBuffTypeHaloRed) / 10000;
        if (fHeloRed >= 0.0001f)
        {
            fFinalParam += fHeloRed;
#ifdef BATTLE_HP_CHANGE
            BATTLE_DBG << "Damage HaloRed, fFinalParam = " << fFinalParam << ".";
#endif
        }
    }

    // 减伤因子算完了，然后开始算实际扣血值
    if (fFinalParam < 0.0001f)
        fFinalParam = 0.0f;
    return fFinalParam;
}		// -----  end of function CalcDamageFactor  ----- //

CHPChangeMachineState::CHPChangeMachineState(CBattleField& rField, CBattleFighter* pBF, CBattleFighter* pBO, 
        INT32 dwHPChange, bool bCri, UINT32 dwSkillID, EBSubHPType eSubHPType, bool bHideShow /* = false */):
    CMachineState(rField, eMSNone, pBF, pBO), 
    _dwHPChange(dwHPChange), _bCri(bCri), _dwSkillID(dwSkillID), _eSubType(eSubHPType), _bHideShow(bHideShow)
{
    if (_dwHPChange > 0)
        _eState = eMSOnHPAdd;
    else if (_dwHPChange < 0)
        _eState = eMSOnHPSub;
}

CHPChangeMachineState::~CHPChangeMachineState()
{
}

void CHPChangeMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        switch (_eState)
        {
            case eMSOnHPAdd:
                {
                    _pBF->RegenHP(_dwHPChange);

                    if (!_bHideShow)
                    {
                        SEffectAddHPPtr pEffect (new SEffectAddHP());
                        pEffect->dwSkillID = _dwSkillID;
                        pEffect->vecFighterID.push_back(_pBF->GetIndex());
                        pEffect->eHPType = _bCri ? EBMODIFYHP_CRITICAL : EBMODIFYHP_NORMAL;
                        pEffect->dwAddHP = _dwHPChange;
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                    }

#ifdef BATTLE_HP_CHANGE
                    string strInfo;
                    if (_pBF)
                        strInfo << *_pBF;
                    BATTLE_DBG << strInfo << ", " << "HP: " << _dwHPChange << ", now HP: " << _pBF->GetHP();
#endif
                }
                _eNextState = eMSOnHPHigh;
                break;
            case eMSOnHPSub:
                {
                    UINT32 dwDamage = -_dwHPChange;
                    _pBF->MakeDmg(dwDamage);

                    if (!_bHideShow)
                    {
                        SEffectDecHPPtr pEffect(new SEffectDecHP());
                        pEffect->vecFighterID.push_back(_pBF->GetIndex());
                        pEffect->eSubHPType = _eSubType;
                        pEffect->eHPType =  _bCri? EBMODIFYHP_CRITICAL : EBMODIFYHP_NORMAL;
                        pEffect->dwSkillID = _dwSkillID;
                        pEffect->dwDecHP = dwDamage;
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                    }

#ifdef BATTLE_HP_CHANGE
                    string strInfo;
                    if (_pBF)
                        strInfo << *_pBF;
                    BATTLE_DBG << strInfo << ", " << "HP: -" << dwDamage << ", now HP: " << _pBF->GetHP();
#endif
                }
                _eNextState = eMSOnHPLow;
                break;
            case eMSOnHPHigh:
            case eMSOnHPLow:
                _eNextState = eMSOnHPChanged;
                break;
            case eMSOnHPChanged:
                if (_pBF->GetHP() <= 0)
                {
                    CDeadMachineState cDeadMS(_rField, _pBF);
                    cDeadMS.Process();
                    CatEffects(cDeadMS);
                }
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CHPChangeMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

CAttackMachineState::CAttackMachineState(CBattleField& rField, CBattleFighter* pBF, CBattleFighter* pBO) : 
    CMachineState(rField, eMSBeforeAtk, pBF, pBO), _pCounter(NULL)
{
}

CAttackMachineState::~CAttackMachineState()
{
}

void CAttackMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        switch(_eState)
        {
            case eMSBeforeAtk:
                BeforeAtk();
                break;
            case eMSSkillAtk:
                SkillAttack();
                break;
            case eMSOnSelfPeerless:
                _eNextState = eMSAfterAtk;
                break;
            case eMSAfterAtk:
                AfterAtk();
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CAttackMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

void CAttackMachineState::BeforeAtk()
{
    _eNextState = eMSSkillAtk;
}

void CAttackMachineState::SkillAttack()
{
    if (_pBF->GetHP() <= 0)
    {
        _eNextState = eMSAfterAtk;
        return;
    }

    bool bForceNormal       = false; // 是否技能攻击无效，强制为普通攻击（沉默，混乱）
    bool bSelfSideAttack    = false; // 是否共计自己人(混乱状态概率触发)
    bool bNoPeerless        = false; // 是否无法发动无双

    CBattleFighter* pTarget = NULL;

    if(_pBF->HaveState(EBFBuffTypeForget)) // 沉默状态必然只能普通攻击
        bForceNormal = true;

    if (_pBF->HaveState(EBFBuffTypeBlunt) && CRandom::RandInt(0, 1)) // 麻痹50%概率无法释放技能
        bForceNormal = true;

    if (_pBF->HaveState(EBFBuffTypeSealed))
        bNoPeerless = true;

    if (_pBF->HaveState(EBFBuffTypeConfuse)) // 混乱状态可能攻击自己人
    {
        if(CRandom::RandInt(0, 1)) // 混乱攻击自己人
        {
            bSelfSideAttack = true;
            TVecBattleFighterPtr vecExcpFgtOut;
            vecExcpFgtOut.push_back(_pBF);
            pTarget = _rField.GetRandomTarget(_pBF->GetSide(), vecExcpFgtOut);
            if (!pTarget)
                bSelfSideAttack = false; // 没有其他自己人，只能攻击对面
            else
                bForceNormal = true;
        }
    }

    TVecBattleSkillEffect vecBattleSkillEffect;
    _eLaunchType = eSkillLaunchNone;
    TVecUINT16 vecProb;
    UINT32 dwSkillID = _pBF->LaunchActiveSkill(vecBattleSkillEffect, bForceNormal, bNoPeerless, _eLaunchType, vecProb);

    bool bActived = false;
    auto it = vecProb.begin();
    TVecAttacker vecAttacker;
    TVecFieldPos vecPos;
    UINT16 wAreaID = 0;
    for(auto& rEF : vecBattleSkillEffect)
    {
        UINT16 wProb = 0;
        if (it != vecProb.end())
            wProb = *(it++);
        bActived = BuildSkillAction(_eLaunchType, rEF, _pBF, pTarget, wProb, vecAttacker, vecPos, wAreaID)? true:bActived;
    }

    // 由于种种原因，主动技能没有发动出来
    if (!bActived)
    {
        _eLaunchType = eSkillLaunchNone;
        dwSkillID = 0;
    }

    // 正常释放技能，切换到下一个技能
    if (_eLaunchType == eSkillActiveSkill || (_eLaunchType == eSkillActiveNormal && !bForceNormal))
        _pBF->ReadyForNextSkill();

    _sProgress.dwSkillID = dwSkillID;


    if (!pTarget)
        pTarget = _rField.GetPossibleTarget(_pBF, IsTargetCanBeAttacked);
    if (!bSelfSideAttack && CBattleSkillMgr::Instance().CanBeCounter(SKILL_ID(dwSkillID)))
        _pCounter =  pTarget;

    if (_eLaunchType == eSkillActivePeerless)
        _eNextState = eMSOnSelfPeerless;
    else
        _eNextState = eMSAfterAtk;
}

void CAttackMachineState::AfterAtk()
{
    FLOAT fAura = 0.0f;
    INT8  byReiatsu = 0;
    switch (_eLaunchType)
    {
        case eSkillActiveNormal:
            {
                fAura = DEFAULT_AURA_ADD_VALUE;
                byReiatsu = DEFAULT_NORMAL_ATTACK_REIATSU;
                CMachineState cTmpMS(_rField, eMSAftNormaleAtk, _pBF, _pBO);
                cTmpMS.Process();
                CatEffects(cTmpMS);

            }
            break;
        case eSkillActiveSkill:
            {
                fAura = DEFAULT_AURA_ADD_VALUE;
                byReiatsu = DEFAULT_SKILL_ATTACK_REIATSU;
                CMachineState cTmpMS(_rField, eMSAftActSkill, _pBF, _pBO);
                cTmpMS.Process();
                CatEffects(cTmpMS);
            }
            break;
        case eSkillActivePeerless:
            {
                fAura = DEFAULT_AURA_SUB_VALUE;
                byReiatsu = DEFAULT_PEERLESS_ATTACK_REIATSU;
                CMachineState cTmpMS(_rField, eMSAftPeerless, _pBF, _pBO);
                cTmpMS.Process();
                CatEffects(cTmpMS);
                _rField.AddCombine(_pBF, eCTPeerless, 3);
            }
            break;
        default:
            break;
    }

    if (_pBF->IsAuraGainDisabel() && fAura > 0.1f) // 灵气值无法增加
        ;
    else if (fAura > 0.1f || fAura < -0.1f) // 灵气值有变化
    {
        CBattleSkillEffect sBSEf;
        CBattleAction* pAction = (new CAuraAction(_rField, fAura, sBSEf, _pBF, _pBF));
        _vecAction.push_back(pAction);
    }
    
    // 增加阵灵灵压
    if (byReiatsu)
    {
        CBattleFighter* pBeauty = _rField.GetBeauty(_pBF->GetSide());
        if (pBeauty)
        {
            CBattleSkillEffect sBSEf;
            CBattleAction* pAction = (new CReiatsuAction(_rField, byReiatsu, sBSEf, pBeauty));
            _vecAction.push_back(pAction);
        }
    }
    // 加入尝试反击行为
    if(_pCounter && _pCounter->CanCounter() && _pBF->GetHP() > 0)
    {
        TVecBattleSkillEffect vecBattleSkillEffect;
        TVecUINT16 vecProb;
        _pCounter->LaunchNormalAttack(vecBattleSkillEffect, vecProb);
        if (!vecBattleSkillEffect.empty())
        {
            for(auto& rEF : vecBattleSkillEffect)
            {
                CBattleAction* pAction = (new CCounterAction(_rField, 1.0f, rEF, _pCounter, _pBF));
                _vecAction.push_back(pAction);
            }
        }
    }
}

CBuffAddMachineState::CBuffAddMachineState(CBattleField& rField, FLOAT fParam,
        CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID) :
    CMachineState(rField, eMSOnBuffSet, pBF, pBO, dwBuffID), 
    _byExLast(0)
{
    _fParam = fParam;
}

CBuffAddMachineState::~CBuffAddMachineState()
{
}

void CBuffAddMachineState::SetExLast(UINT8 byExLast)
{
    _byExLast = byExLast;
}

void CBuffAddMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        switch(_eState)
        {
            case eMSOnBuffSet:// 造成指定buff时触发
                _eNextState = eMSState;
                break;
            case eMSState: 
                {
                    CBattleFighter* pTmp = _pBO;
                    _pBO = _pBF;
                    _pBF = pTmp;
                    _eNextState = eMSOnBuffGet;
                }
                break;
            case eMSOnBuffGet:// 获得指定buff时触发
                {
                    if (_pBF->GetBuffResist() == _dwBuffID)
                    {
                        bEnd = true;
                        _pBF->SetBuffResist(0);
                        _eNextState = eMSNone;
                        break;
                    }
                    CBattleBuff cBattleBuff;
                    if (cBattleBuff.Build(_dwBuffID, _pBO, _pBF))
                    {
                        if (_pBO == _pBF && cBattleBuff.GetLast() && cBattleBuff.GetLast() != INFINIT_CD)
                            ++_byExLast;
                        cBattleBuff.AddLast(_byExLast);
                        if (_pBF->GetStateValue(EBFBuffTypeSmoke) > 0.1f) // 烟幕可以防止上异常状态
                        {
                            if (cBattleBuff.CanResist())
                            {
                                SEffectAddStatusPtr pEffect (new SEffectAddStatus());
                                pEffect->vecFighterID.push_back(_pBF->GetIndex());
                                pEffect->eStatus = EBStatusType_Immu;
                                bEnd = true;
                                break;
                            }
                        }
                        UINT32 dwBuffKey = 0;
                        if (_pBF->CheckAddBattleBuff(cBattleBuff, dwBuffKey)) // 先检查能否加上Buff
                        {
                            if (dwBuffKey)
                            {
                                BATTLE_DBG << "Conflicit BuffKey = " << dwBuffKey << ".";
                                CBuffLostMachineState cBuffMS2(_rField, eMSOnAllLostBuff, GetParam(), _pBF, _pBO, _dwBuffID, dwBuffKey, false);
                                cBuffMS2.Process();
                                CatEffects(cBuffMS2);
                            }

                            // 上Buff成功
                            if (_pBF->AddBattleBuff(cBattleBuff))
                            {
                                SEffectStateBuffAddPtr pEffect(new SEffectStateBuffAdd());
                                pEffect->vecFighterID.push_back(_pBF->GetIndex());
                                pEffect->dwBuffKey = cBattleBuff.GetInstID();
                                pEffect->eStateBuffType = cBattleBuff.GetGroupBuffType();
                                pEffect->dwSkillID =  cBattleBuff.GetID();
                                pEffect->dwBaseSkillID = SKILL_ID(CBattleSkillMgr::Instance().GetOriginSkillID(cBattleBuff.GetID()));
                                pEffect->byLast = cBattleBuff.GetLast() - _byExLast;
                                pEffect->dwValue = static_cast<INT32>(cBattleBuff.GetValue1());
                                _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                                string strInfo;
                                if (_pBO)
                                    strInfo << *_pBO;
                                if (_pBF)
                                    strInfo << *_pBF;
                                BATTLE_DBG << "Buff Get: " << (strInfo << cBattleBuff) << ", conflicit BuffKey = " << dwBuffKey << ".";

                                // 上流血状态会清除护盾
                                if (cBattleBuff.GetGroupBuffType() == EBFBuffTypeBleed)
                                {
                                    TSetUINT32 setBuffID; _pBF->GetStateBuffID( EBFBuffTypeShield, setBuffID); 
                                    for (auto & rID : setBuffID)
                                    {
                                        CBattleBuff cBattleBuff;
                                        if(_pBF->GetBuff(rID, cBattleBuff))
                                        {
                                            CBattleSkillEffect ef(cBattleBuff.GetSkillEffect());
                                            CBuffLostMachineState cBuffMS2(_rField, eMSOnAllLostBuff, GetParam(), _pBF, NULL, rID);
                                            cBuffMS2.SetEffectsType(eETBefore);
                                            cBuffMS2.Process();
                                            CatEffects(cBuffMS2);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                string strInfo;
                                if (_pBO)
                                    strInfo << *_pBO;
                                if (_pBF)
                                    strInfo << *_pBF;
                                BATTLE_DBG << "Buff Get failed: " << (strInfo << cBattleBuff);
                            }
                        }
                    }
                    else
                        LOG_CRI << "Build BattleBuff failed.(" << _dwBuffID << ")";
                }
                _eNextState = eMSOnSelfSideBuffGet;
                break;
            case eMSOnSelfSideBuffGet:
                _eNextState = eMSOnAllBuffGet;
                break;
            case eMSOnAllBuffGet:
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CBuffAddMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

CBuffLostMachineState::CBuffLostMachineState(CBattleField& rField, EMachineState eState, FLOAT fParam,
        CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwBuffIDEX /* = 0 */) :
    CMachineState(rField, eState, pBF, pBO, dwBuffID), 
    _dwFakeBuffKey(0), _bOutCond(false), _dwBuffIDEX(dwBuffIDEX),
    _bClear(false)
{
    _fParam = fParam;
}

CBuffLostMachineState::CBuffLostMachineState(CBattleField& rField, EMachineState eState, FLOAT fParam,
        CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwFakeBuffKey, bool bOutCond) :
    CMachineState(rField, eState, pBF, pBO, dwBuffID), 
    _dwFakeBuffKey(dwFakeBuffKey), _bOutCond(bOutCond), _dwBuffIDEX(0),
    _bClear(false)
{
    _fParam = fParam;
}

CBuffLostMachineState::~CBuffLostMachineState()
{
}

void CBuffLostMachineState::Process()
{

    bool bEnd = false;
    while(!bEnd)
    {
        switch(_eState)
        {
            case eMSOnClearBuff:
                _bClear = true;
                _eNextState = eMSOnAllLostBuff;
                break;
            case eMSOnAllLostBuff:
                if (_bClear)
                {
                    CBattleFighter* pTmp = _pBO;
                    _pBO = _pBF;
                    _pBF = pTmp;
                }
                _eNextState = eMSOnLostBuff;
                break;
            case eMSOnLostBuff:// 失去指定buff时触发
                {
                    if (_dwFakeBuffKey) // 只是为了触发其他技能，实际不移除buff
                    {
                        SEffectStateBuffDecPtr pEffect(new SEffectStateBuffDec());
                        pEffect->vecFighterID.push_back(_pBF->GetIndex());
                        pEffect->dwBuffKey = _dwFakeBuffKey;
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                        string strInfo;
                        if (_pBO)
                            strInfo << *_pBO;
                        if (_pBF)
                            strInfo << *_pBF;
                        BATTLE_DBG << "Fake Buff Lost: " << strInfo  << _dwBuffID << ", " << _dwFakeBuffKey << ".";
                    }
                    else
                    {
                        CBattleBuff cBattleBuff;
                        if(_pBF->GetBuff(_dwBuffID, cBattleBuff))
                        {
                            if (!_bOutCond)
                            {
                                SEffectStateBuffDecPtr pEffect(new SEffectStateBuffDec());
                                pEffect->vecFighterID.push_back(_pBF->GetIndex());
                                pEffect->dwBuffKey = cBattleBuff.GetInstID();
                                _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                                _pBF->RemoveBattleBuff(_dwBuffID);
                                string strInfo;
                                if (_pBO)
                                    strInfo << *_pBO;
                                if (_pBF)
                                    strInfo << *_pBF;
                                BATTLE_DBG << "Buff Lost: " << (strInfo << cBattleBuff);
                            }
                            else
                            {
                                UINT32 dwRet = _pBF->ReduceBattleBuff(_dwBuffID);
                                if (dwRet)
                                {
                                    SEffectStateBuffEffectPtr pEffect(new SEffectStateBuffEffect());
                                    pEffect->vecFighterID.push_back(_pBF->GetIndex());
                                    pEffect->dwBuffKey = cBattleBuff.GetInstID();
                                    _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                                    string strInfo;
                                    if (_pBO)
                                        strInfo << *_pBO;
                                    if (_pBF)
                                        strInfo << *_pBF;
                                    BATTLE_DBG << "Buff Reduce: " << (strInfo << cBattleBuff);
                                }
                                else
                                {
                                    SEffectStateBuffDecPtr pEffect(new SEffectStateBuffDec());
                                    pEffect->vecFighterID.push_back(_pBF->GetIndex());
                                    pEffect->dwBuffKey = cBattleBuff.GetInstID();
                                    _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                                    string strInfo;
                                    if (_pBO)
                                        strInfo << *_pBO;
                                    if (_pBF)
                                        strInfo << *_pBF;
                                    BATTLE_DBG << "Reduce Buff Lost: " << (strInfo << cBattleBuff);
                                }
                            }
                        }
                    }
                }
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CBuffLostMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

CBuffActMachineState::CBuffActMachineState(CBattleField& rField, FLOAT fParam,
        CBattleFighter* pBF, CBattleFighter* pBO, UINT32 dwBuffID, UINT32 dwBuffIDEX /* = 0 */) :
    CMachineState(rField, eMSOnBuffAct, pBF, pBO, dwBuffID), 
    _dwBuffEffectCount(0), _dwBuffIDEX(dwBuffIDEX)
{
    _fParam = fParam;
}

CBuffActMachineState::~CBuffActMachineState()
{
}

UINT32 CBuffActMachineState::GetBuffEffectCount() const
{
    return _dwBuffEffectCount;
}

void CBuffActMachineState::Process()
{

    bool bEnd = false;
    while(!bEnd)
    {
        switch(_eState)
        {
            case eMSOnBuffAct:// 指定buff触发时触发
                {
                    CBattleBuff cBattleBuff;
                    if(_pBF->GetBuff(_dwBuffID, cBattleBuff))
                    {
                        SEffectStateBuffEffectPtr pEffect(new SEffectStateBuffEffect());
                        pEffect->vecFighterID.push_back(_pBF->GetIndex());
                        pEffect->dwBuffKey = cBattleBuff.GetInstID();
                        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
                        string strInfo;
                        if (_pBO)
                            strInfo << *_pBO;
                        if (_pBF)
                            strInfo << *_pBF;
                        BATTLE_DBG << "Buff Act: " << (strInfo << cBattleBuff);
                    }

                    // 阵灵技能变为单独一个出手
                    if (_pBF->GetPos() == PET_POS || _pBF->GetPos() == PET_POS + 1)
                    {
                        CMachineState* pMS = new CBuffSkillMachineState(_rField, _pBF, _pBO, _dwBuffID, _dwBuffIDEX);
                        _vecExtraMS.push_back(pMS);
                    }
                    else if (cBattleBuff.GetEffectCond() == eMSOnRoundStart || cBattleBuff.GetEffectCond() == eMSEnter)
                    {
                        CMachineState* pMS = new CBuffSkillMachineState(_rField, _pBF, _pBO, _dwBuffID, _dwBuffIDEX);
                        _vecExtraMS.push_back(pMS);
                    }
                    else
                    {
                        TVecUINT32 vecEffectID;
                        cBattleBuff.GetNextBuffID(vecEffectID);
                        TVecBattleSkillEffect vecBattleSkillEffect;
                        TVecUINT16 vecProb;
                        CBattleSkillMgr::Instance().InitSkillEffectWithProb(vecEffectID, vecBattleSkillEffect, vecProb);
                        UINT32 dwActionAct = 0;
                        auto it = vecProb.begin();
                        TVecAttacker vecAttacker;
                        TVecFieldPos vecPos;
                        UINT16 wAreaID = 0;
                        for (auto& rEF : vecBattleSkillEffect)
                        {
                            UINT16 wProb = 10000;
                            if (it != vecProb.end())
                                wProb = *(it++);
                            dwActionAct += BuildBuffActAction(rEF, _pBF, _pBO, _dwBuffID, _dwBuffIDEX, wProb, vecAttacker, vecPos, wAreaID);
                        }
                        _dwBuffEffectCount = dwActionAct;
                    }
                }
                _eNextState = eMSOnOtherSideBuffAct;
                break;
            case eMSOnOtherSideBuffAct:
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CBuffActMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

CAuraChangeMachineState::CAuraChangeMachineState(CBattleField& rField, EMachineState eState, CBattleFighter* pBF, INT32 dwAura) :
    CMachineState(rField, eState, pBF, NULL), _dwAura(dwAura)
{
}

CAuraChangeMachineState::~CAuraChangeMachineState()
{
}

void CAuraChangeMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        switch(_eState)
        {
            case eMSOnAuraAdd:
                {
                    _pBF->AddAura(_dwAura);
                    SEffectSycAuraPtr pEffect(new SEffectSycAura());
                    pEffect->vecFighterID.push_back(_pBF->GetIndex());
                    pEffect->iAura = _pBF->GetAura();
                    _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
#ifdef BATTLE_AURA_CHANGE
                    string strInfo;
                    if (_pBF)
                        strInfo << *_pBF;
                    BATTLE_DBG << strInfo << " AuraAdd: " << _dwAura << ", now arua = " << _pBF->GetAura() << ".";
#endif
                }
                bEnd = true;
                break;
            case eMSOnAuraSub:
                {
                    if (_dwAura < 0)
                        _dwAura = -_dwAura;
                    _pBF->SubAura(_dwAura);
                    SEffectSycAuraPtr pEffect(new SEffectSycAura());
                    pEffect->vecFighterID.push_back(_pBF->GetIndex());
                    pEffect->iAura = _pBF->GetAura();
                    _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
#ifdef BATTLE_AURA_CHANGE
                    string strInfo;
                    if (_pBF)
                        strInfo << *_pBF;
                    BATTLE_DBG << strInfo << " AuraSub: " << _dwAura << ", now arua = " << _pBF->GetAura() << ".";
#endif
                }
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CAuraChangeMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

CReiatsuChangeMachineState::CReiatsuChangeMachineState(CBattleField& rField, EMachineState eState, UINT8 bySide) :
    CMachineState(rField, eState, NULL, NULL), _bLaunched(false)
{
    _pBF = _rField.GetBeauty(bySide);
    if (_pBF)
        SetCasterID(_pBF->GetIndex());
}

CReiatsuChangeMachineState::~CReiatsuChangeMachineState()
{
}

void CReiatsuChangeMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        switch(_eState)
        {
            case eMSOnReiatsuAdd:
                TryLaunchBeautySkill();
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CReiatsuChangeMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

bool CReiatsuChangeMachineState::IsLaunched() const
{
    return _bLaunched;
}

void CReiatsuChangeMachineState::TryLaunchBeautySkill()
{
    if (!_pBF)
        return;
    TVecBattleSkillEffect vecBattleSkillEffect;
    TVecUINT16 vecProb;
    UINT32 dwSkillID = _pBF->LaunchBeautySkill(vecBattleSkillEffect, vecProb);

    auto it = vecProb.begin();
    TVecAttacker vecAttacker;
    TVecFieldPos vecPos;
    UINT16 wAreaID = 0;

    for(auto& rEF : vecBattleSkillEffect)
    {
        UINT16 wProb = 0;
        if (it != vecProb.end())
            wProb = *(it++);
        BuildSkillAction(eSkillPassiveBeauty, rEF, _pBF, NULL, wProb, vecAttacker, vecPos, wAreaID);
    }

    _sProgress.dwSkillID = dwSkillID;

    // 释放阵灵技能成功，减少灵压
    if (dwSkillID)
    {
        _bLaunched = true;
        INT8 byReiatsu = -100;
        CBattleSkillEffect sBSEf;
        CBattleAction* pAction = (new CReiatsuAction(_rField, byReiatsu, sBSEf, _pBF));
        _vecAction.push_back(pAction);
    }
}

CCombineChangeMachineState::CCombineChangeMachineState(CBattleField& rField, EMachineState eState, UINT8 bySide) :
    CMachineState(rField, eState, NULL, NULL), _bySide(bySide), _bLaunched(false), _byIndex(DEFAULT_POS)
{
}

CCombineChangeMachineState::~CCombineChangeMachineState()
{
}

void CCombineChangeMachineState::Process()
{
    bool bEnd = false;
    while(!bEnd)
    {
        switch(_eState)
        {
            case eMSOnCombineAdd:       // 连携点数到达指定值触发
            case eMSBeforeCombineSkill: // 连携技能发动前
            case eMSOnCombineSkill:     // 连携技能发动
            case eMSAfterCombineSkill:  // 连携技能发动
                TryLaunchCombineSkill();
                _eNextState = eMSAfterCombineAdd;
                break;
            case eMSAfterCombineAdd:    // 连携技能触发后
                if (_bLaunched && _sProgress.dwSkillID && _byIndex != DEFAULT_POS)
                {
                    CBattleSkillEffect sBSEf;
                    CBattleAction* pAction = (new CCombineAction(_rField, _bySide, _sProgress.dwSkillID, 0, _byIndex));
                    if (pAction)
                        _vecAction.push_back(pAction);
                }
                bEnd = true;
                break;
            default:
                bEnd = true;
        }
        STATE_DEBUG << "CCombineChangeMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
        CMachineState::Process();
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  IsLaunched
//  Description:  获取是否触发连携技能
// =====================================================================================
bool CCombineChangeMachineState::IsLaunched() const
{
    return _bLaunched;
}		// -----  end of function IsLaunched  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  TryLaunchCombineSkill
//  Description:  尝试发动连携技能
// =====================================================================================
void CCombineChangeMachineState::TryLaunchCombineSkill()
{
    UINT8 byTeamID = 0;
    UINT32 dwSkillID = _rField.GetCombineSkill(_bySide, _byIndex, byTeamID);

    _sProgress.dwSkillID = dwSkillID;


    // 释放组合技能成功，减少连携点数
    if (dwSkillID)
    {
#ifdef BATTLE_SKILL_COMBINE
        ostringstream strInfo;
        strInfo << CBattleSkillMgr::Instance().GetSkillName(dwSkillID) << ".";
        BATTLE_DBG << "Launch CombineSkill: " << strInfo.str();
#endif

        TVecBattleSkillEffect vecBattleSkillEffect;
        TVecUINT16 vecProb;
        CBattleSkillMgr::Instance().GetSkillEffectWithProb(dwSkillID, 0, vecBattleSkillEffect, vecProb);

        TSetUINT16 setFighterID;

        if (_rField.GetCombineSkillFighterID(_bySide, _byIndex, setFighterID))
        {
            UINT8 byIndex = 0;
            TVecBattleFighterPtr vecFighter;
            for (auto & rID : setFighterID)
            {
                CBattleFighter* pFighter = _rField.GetFighterByID(_bySide, byTeamID, rID);
                if (pFighter)
                {
                    SetCasterID(pFighter->GetIndex(), byIndex ++);
                    vecFighter.push_back(pFighter);

                    // 首先需要清除自己身上的异常Buff
                    ClearDeBuff(pFighter);
                }
            }

            TVecAttacker vecAttacker;
            TVecFieldPos vecPos;
            UINT16 wAreaID = 0;

            auto it = vecProb.begin();
            for(auto& rEf : vecBattleSkillEffect)
            {
                UINT16 wProb = 0;
                if (it != vecProb.end())
                    wProb = *(it++);

                for (auto & pFighter: vecFighter)
                {
                    _pBF = pFighter;
                    BuildSkillAction(eSkillPassiveCombine, rEf, _pBF, NULL, wProb, vecAttacker, vecPos, wAreaID);
                }
            }
            _bLaunched = true;
        }
    }
}		// -----  end of function TryLaunchCombineSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearDeBuff
//  Description:  清除异常状态Buff
// =====================================================================================
void CCombineChangeMachineState::ClearDeBuff (CBattleFighter* pFighter)
{
    if (!pFighter)
        return;
    TVecUINT32 vecBuffID;
    pFighter->GetDebuffCanClear(vecBuffID, eResistTypeControl);
    for (auto& rBuffID : vecBuffID)
    {
        CBuffLostMachineState cBuffMS2(_rField, eMSOnClearBuff, 0, pFighter, pFighter, rBuffID);
        cBuffMS2.Process();
        CatEffects(cBuffMS2);
    }
}		// -----  end of function ClearDeBuff  ----- //

CBuffSkillMachineState::CBuffSkillMachineState(CBattleField& rField, 
        CBattleFighter* pBF, CBattleFighter* pBO, 
        UINT32 dwBuffID, UINT32 dwBuffIDEX):
    CMachineState(rField, eMSNone, pBF, pBO, dwBuffID), 
    _dwBuffIDEX(dwBuffIDEX)
{
    if (_pBF)
        SetCasterID(pBF->GetIndex());
    _sProgress.dwSkillID = dwBuffID;
}

CBuffSkillMachineState::~CBuffSkillMachineState()
{
}

void CBuffSkillMachineState::Process()
{
    CBattleBuff cBattleBuff;
    if(_pBF->GetBuff(_dwBuffID, cBattleBuff))
    {
        SEffectStateBuffEffectPtr pEffect(new SEffectStateBuffEffect());
        pEffect->vecFighterID.push_back(_pBF->GetIndex());
        pEffect->dwBuffKey = cBattleBuff.GetInstID();
        _sProgress.vSkillEffects.push_back(SEffectBasePtr(pEffect));
        string strInfo;
        if (_pBO)
            strInfo << *_pBO;
        if (_pBF)
            strInfo << *_pBF;
        BATTLE_DBG << "Buff Act: " << (strInfo << cBattleBuff);
        TVecUINT32 vecEffectID;
        cBattleBuff.GetNextBuffID(vecEffectID);
        TVecBattleSkillEffect vecBattleSkillEffect;
        TVecUINT16 vecProb;
        CBattleSkillMgr::Instance().InitSkillEffectWithProb(vecEffectID, vecBattleSkillEffect, vecProb);
        UINT32 dwActionAct = 0;
        auto it = vecProb.begin();
        TVecAttacker vecAttacker;
        TVecFieldPos vecPos;
        UINT16 wAreaID = 0;
        for (auto& rEF : vecBattleSkillEffect)
        {
            UINT16 wProb = 10000;
            if (it != vecProb.end())
                wProb = *(it++);
            dwActionAct += BuildSkillAction(eSkillPassiveActive, rEF, _pBF, _pBO, wProb, vecAttacker, vecPos, wAreaID);
        }
    }
    STATE_DEBUG << "CBuffSkillMachineState: " << MSValToStr(_eState) << ", next: " << MSValToStr(_eNextState) << ".";
    ProcessAction();
}

} // namespace NBattle
