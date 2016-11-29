#include "BattleSkill.h"
#include "SkillBaseCFG.h"
#include "SkillEffectCFG.h"
#include "Tokenizer.h"
#include "Random.h"
#include "BattleFighter.h"
#include "BattleArea.h"

#include "BattleDebugger.h"

namespace NBattle
{

static UINT32 g_dwInstID = 1;
const string INVALID_SKILL("无效技能");

UINT32 SSkillEffect::GetRate() const
{
#ifdef _DEBUG
    if (IsRate100())
        return 10000;
#endif
    return _wRate;
}

CBattleSkillEffect::CBattleSkillEffect():
    _dwSkillEffectID(0), _dwCD(0), _dwOriginSkillID(0),
    _fValue1(0), _fValue2(0), _fValue3(0), _pSkillEffect(NULL)
{
}

CBattleSkillEffect::CBattleSkillEffect(SSkillEffect* pSEf):
    _dwSkillEffectID(0), _dwCD(0), _dwOriginSkillID(0),
    _fValue1(0), _fValue2(0), _fValue3(0), _pSkillEffect(NULL)
{
    if(pSEf)
    {
        _dwSkillEffectID = pSEf->_dwID;
        _dwOriginSkillID = pSEf->_dwID;
        _fValue1 = pSEf->_fValue1;
        _fValue2 = pSEf->_fValue2;
        _fValue3 = pSEf->_fValue3;
        _pSkillEffect = pSEf;
    }
}

UINT32 CBattleSkillEffect::GetID() const
{
    return _dwSkillEffectID;
}

UINT32 CBattleSkillEffect::GetOriginSkillID() const
{
    return _dwOriginSkillID;
}

SSkillEffect*     CBattleSkillEffect::GetSkillEffect() const
{
    return _pSkillEffect;
}

SSkillEffect*     CBattleSkillEffect::GetSkillEffect()
{
    return _pSkillEffect;
}

const string& CBattleSkillEffect::GetName() const
{
    return _pSkillEffect->_strName;
}

ESkillEffectType CBattleSkillEffect::GetType() const
{
    return _pSkillEffect->_eSkillEffectType;
}

UINT16   CBattleSkillEffect::GetArea() const
{
    if (_pSkillEffect)
        return _pSkillEffect->_wArea;
    return 0;
}

UINT32 CBattleSkillEffect::GetRate() const
{
#ifdef _DEBUG
    if (IsRate100())
        return 10000;
#endif
    if (_pSkillEffect)
        return _pSkillEffect->_wRate;
    return 0;
}

void CBattleSkillEffect::GetNextBuffID(TVecUINT32& vecBuffID) const
{
    if (_pSkillEffect)
        vecBuffID.insert(vecBuffID.end(), _pSkillEffect->_vecBuffID. begin(), _pSkillEffect->_vecBuffID.end());
}

UINT8 CBattleSkillEffect::GetLast() const
{
    if (_pSkillEffect)
        return _pSkillEffect->_byLast;
    return 0;
}

FLOAT CBattleSkillEffect::GetValue1() const
{
    return _fValue1;
}

FLOAT CBattleSkillEffect::GetValue2() const
{
    return _fValue2;
}

FLOAT CBattleSkillEffect::GetValue3() const
{
    return _fValue3;
}

FLOAT CBattleSkillEffect::GetDefaultValue1() const
{
    if (_pSkillEffect)
        return _pSkillEffect->_fValue1;
    return 0.0f;
}

FLOAT CBattleSkillEffect::GetDefaultValue2() const
{
    if (_pSkillEffect)
        return _pSkillEffect->_fValue2;
    return 0.0f;
}

FLOAT CBattleSkillEffect::GetDefaultValue3() const
{
    if (_pSkillEffect)
        return _pSkillEffect->_fValue3;
    return 0.0f;
}

EResistType CBattleSkillEffect::GetResistType() const
{
    if (_pSkillEffect)
        return _pSkillEffect->_eResistType;
    return eResistTypeNone;
}

CBattleBuff::CBattleBuff() : 
    _dwInstID(0), _dwID(0), 
    _byEffectCondCount(0), _fCondParam(0.0f), _byOutEffectCondCount(0), _fOutCondParam(0.0f),
    _byLast(0), _pSkillEffect(NULL), _pOwner(NULL), _pGiver(NULL),
    _fValue1(0), _fValue2(0), _fValue3(0), _dwCD(0), _dwTurnCD(0)
{
}

bool CBattleBuff::Build(SSkillEffect* pSEf, CBattleFighter* pGiver, CBattleFighter* pOwner)
{
    _dwInstID       = g_dwInstID++;
    _dwID           = pSEf->_dwID;
    _byLast         = pSEf->_byLast;
    if (!pSEf)
        return false;
    _pSkillEffect   = pSEf;
    _pOwner         = pOwner;
    _pGiver         = pGiver;
    _fValue1        = pSEf->_fValue1;
    _fValue2        = pSEf->_fValue2;
    _fValue3        = pSEf->_fValue3;
    return true;
}

bool CBattleBuff::Build(const CBattleSkillEffect& pSEf, CBattleFighter* pGiver, CBattleFighter* pOwner)
{

    _dwInstID        = g_dwInstID++;
    _dwID            = pSEf.GetID();
    _dwOriginSkillID = pSEf.GetOriginSkillID();
    _pSkillEffect    = pSEf.GetSkillEffect();
    if (!_pSkillEffect)
        return false;
    _byLast = _pSkillEffect->_byLast;
    _pOwner          = pOwner;
    _pGiver          = pGiver;
    _fValue1         = pSEf.GetValue1();
    _fValue2         = pSEf.GetValue2();
    _fValue3         = pSEf.GetValue3();
    return true;
}

bool CBattleBuff::Build(UINT32 dwBuffID, CBattleFighter* pGiver, CBattleFighter* pOwner)
{
    _dwInstID       = g_dwInstID++;
    _dwID           = dwBuffID;
    _pSkillEffect   = CBattleSkillMgr::Instance().GetSkillEf(dwBuffID);
    if (!_pSkillEffect)
        return false;
    _byLast = _pSkillEffect->_byLast;
    _pOwner         = pOwner;
    _pGiver         = pGiver;
    _fValue1        = _pSkillEffect->_fValue1;
    _fValue2        = _pSkillEffect->_fValue2;
    _fValue3        = _pSkillEffect->_fValue3;
    return true;
}

void CBattleBuff::SetInstID(UINT32 dwInstID)
{
    _dwInstID = dwInstID;
}

UINT32 CBattleBuff::GetInstID() const
{
    return _dwInstID;
}

UINT32 CBattleBuff::GetID() const
{
    return _dwID;
}

UINT32 CBattleBuff::GetOriginSkillID() const
{
    return _dwOriginSkillID;
}

const string& CBattleBuff::GetName() const
{
    return _pSkillEffect->_strName;
}

EBStateBuffType CBattleBuff::GetGroupBuffType() const
{
    return _pSkillEffect->_eBuffGroup;
}

ESkillEffectType CBattleBuff::GetType() const
{
    return _pSkillEffect->_eSkillEffectType;
}

EMachineState CBattleBuff::GetEffectCond() const
{
    return _pSkillEffect->_eState;
}

TVecUINT32&   CBattleBuff::GetEffectCondValue() const
{
    return _pSkillEffect->_vecCondValue;
}

TVecUINT32&   CBattleBuff::GetOutEffectCondValue() const
{
    return _pSkillEffect->_vecOutCondValue;
}

EMachineState CBattleBuff::GetOutEffectCond() const
{
    return _pSkillEffect->_eOutState;
}

UINT8 CBattleBuff::GetEffectCondCount() const
{
    return _byEffectCondCount;
}

UINT8 CBattleBuff::GetOutEffectCondCount() const
{
    return _byOutEffectCondCount;
}

FLOAT CBattleBuff::GetCondParam() const
{
    return _fCondParam;
}

FLOAT CBattleBuff::GetOutCondParam() const
{
    return _fOutCondParam;
}

FLOAT CBattleBuff::GetCondParam(bool bOut) const
{
    return bOut?_fOutCondParam:_fCondParam;
}

UINT16 CBattleBuff::GetCondRate() const
{
    return _pSkillEffect->_wCondRate;
}

SSkillEffect* CBattleBuff::GetSkillEffect()
{
    return _pSkillEffect;
}

SSkillEffect* CBattleBuff::GetSkillEffect() const
{
    return _pSkillEffect;
}

CBattleFighter* CBattleBuff::GetOwner() const
{
    return _pOwner;
}

CBattleFighter* CBattleBuff::GetGiver() const
{
    return _pGiver;
}

void CBattleBuff::AddLast(UINT8 byLast /* = 1 */)
{
    _byLast += byLast;
}

void CBattleBuff::SetLast(UINT8 byLast)
{
    _byLast = byLast;
}

UINT8 CBattleBuff::GetLast() const
{
    return _byLast;
}

UINT8 CBattleBuff::GetDefaultLast() const
{
    if (_pSkillEffect)
        return _pSkillEffect->_byLast;
    else
        return 0;
}

FLOAT CBattleBuff::GetValue1() const
{
    return _fValue1;
}

FLOAT CBattleBuff::GetValue2() const
{
    return _fValue2;
}


FLOAT CBattleBuff::GetValue3() const
{
    return _fValue3;
}

UINT32 CBattleBuff::GetRate() const
{
#ifdef _DEBUG
    if (IsRate100())
        return 10000;
#endif
    return _pSkillEffect->_wRate;
}

FLOAT CBattleBuff::GetDefaultValue1() const
{
    return _pSkillEffect->_fValue1;
}

FLOAT CBattleBuff::GetDefaultValue2() const
{
    return _pSkillEffect->_fValue2;
}

FLOAT CBattleBuff::GetDefaultValue3() const
{
    return _pSkillEffect->_fValue3;
}

void  CBattleBuff::SetValue1(FLOAT fValue1)
{
    _fValue1 = fValue1;
}

void  CBattleBuff::SetValue2(FLOAT fValue2)
{
    _fValue2 = fValue2;
}

void  CBattleBuff::SetValue3(FLOAT fValue3)
{
    _fValue3 = fValue3;
}

void  CBattleBuff::ResetValue(FLOAT fValue1, FLOAT fValue2, FLOAT fValue3)
{
    ResetValue1(fValue1);
    ResetValue2(fValue2);
    ResetValue3(fValue3);

}

void  CBattleBuff::ResetValue1(FLOAT fValue)
{
    switch (GetType())
    {
        case EAttrSub:
            _fValue1 = -GetDefaultValue1() / 10000;  // 整数值需要转化为万份比
            break;
        case EAttrAdd:
            _fValue1 = GetDefaultValue1() / 10000; // 整数值需要转化为万份比
            break;
        case EAttr2AttrAdd: // 属性增益其他属性
        case EShield: //护盾
            _fValue1 = (fValue * GetDefaultValue1() / 10000);  // 整数值需要转化为生命值的万份比
            break;
        case EAttackAddP: // 攻击提升
        case EAttackSubP: // 攻击减少
        case EDefendAddP: // 防御提升
        case EDefendSubP: // 防御减少
        case EBronze   : // 铜人
        case EKingkong :// 金刚
        case EAssist:   //  被掩护
        case EBounceDmg: // 反伤
        case EEffectAdd: // 效果值增益
        case EEffectSub: // 效果值减益
        case EResistAdd: // 效果值增益
        case EResistSub: // 效果值减益
        case EDamageShare: // 伤害分担
            _fValue1 = GetDefaultValue1() / 10000;  // 整数值需要转化为万份比
            break;
        case EStun:   // 眩晕
        case EConfuse:// 混乱
        case EForget: // 沉默
        case EFreeze: // 冻结
        case ESealed: // 封印
        case EClone:  // 分身
        case EStoned: // 石化
        case EPierce: //破甲(伤害减免减少一半)
        case EBlock: // 格挡
        case EHide:  //影遁
        case ECongest: //蓄力
        case EResistDeBuff: // 免疫负面效果
        case EInvincible: // 无敌
            _fValue1 = GetLast(); // 数值就是持续回合数
            break;
        default:
            _fValue1 = GetDefaultValue1();
    }
}

void  CBattleBuff::ResetValue2(FLOAT fValue)
{
    switch (GetType())
    {
        default:
            _fValue2 = GetDefaultValue2();
    }
}

void  CBattleBuff::ResetValue3(FLOAT fValue)
{
    switch (GetType())
    {
        case EAttr2AttrAdd:
            _fValue3 = 0.0f;
            break;
        default:
            _fValue3 = GetDefaultValue3();
    }
}

FLOAT CBattleBuff::GetDefaultResetValue1() const
{
    FLOAT fRet = 0.0f;
    switch (GetType())
    {
        case EAttr2AttrAdd: // 属性增益其他属性
            fRet = (_pOwner->GetAttrExtra(static_cast<EFighterAttr>(GetDefaultValue3())) * GetDefaultValue1() / 10000);  // 整数值需要转化为生命值的万份比
            break;
        case EAttrSub:
            fRet = -GetDefaultValue1() / 10000; // 减益应该存负数
            break;
        case EAttrAdd:
            fRet = GetDefaultValue1() / 10000;
            break;
        case EShield: //护盾
            if (_pGiver)
                fRet = (_pGiver->GetMaxHP() * GetDefaultValue1() / 10000);  // 整数值需要转化为生命值的万份比
            break;
        case EAttackAddP: // 攻击提升
        case EAttackSubP: // 攻击减少
        case EDefendAddP: // 防御提升
        case EDefendSubP: // 防御减少
        case EBronze   : // 铜人
        case EKingkong :// 金刚
        case EAssist:   //  被掩护
        case EBounceDmg: // 反伤
        case EEffectAdd: // 效果值增益
        case EEffectSub: // 效果值减益
        case EResistAdd: // 效果值增益
        case EResistSub: // 效果值减益
        case EDamageShare: // 伤害分担
            fRet = GetDefaultValue1() / 10000;  // 整数值需要转化为生命值的万份比
            break;
        case EStun:   // 眩晕
        case EConfuse:// 混乱
        case EForget: // 沉默
        case EFreeze: // 冻结
        case ESealed: // 封印
        case EClone:  // 分身
        case EStoned: // 石化
        case EPierce: //破甲(伤害减免减少一半)
        case EBlock: // 格挡
        case EHide:  //影遁
        case ECongest: //蓄力
        case EResistDeBuff: // 免疫负面效果
            fRet = 1.0f;
            break;
        default:
            fRet = GetDefaultValue1();
    }
    return fRet;
}

void CBattleBuff::GetNextBuffID(TVecUINT32& vecBuffID) const
{
    vecBuffID.insert(vecBuffID.end(), _pSkillEffect->_vecBuffID. begin(), _pSkillEffect->_vecBuffID.end());
}

bool CBattleBuff::CanResist() const
{
    bool bRet = false;
    switch (_pSkillEffect->_eResistType)
    {
        case eResistTypeNormal:
        case eResistTypeControl:
            bRet = true;
            break;
        default:
            bRet = false;
            break;
    }
    return bRet;
}

bool CBattleBuff::CanClear(EResistType eType) const
{
    bool bRet = false;
    switch (_pSkillEffect->_eResistType)
    {
        case eResistTypeNormal:
        case eResistTypeControl:
            bRet = true;
            break;
        default:
            bRet = false;
            break;
    }
    return bRet;
}

bool CBattleBuff::CanClearControl() const
{
    return _pSkillEffect->_eResistType == eResistTypeControl;
}

EResistType CBattleBuff::GetResistType() const
{
    return _pSkillEffect->_eResistType;
}

bool  CBattleBuff::AddCondCount()
{
    if (!_pSkillEffect->_byCondCD)
        return false;
    return ++_byEffectCondCount >= _pSkillEffect->_byCondCD;
}

bool  CBattleBuff::AddOutCondCount()
{
    if (!_pSkillEffect->_byOutCD)
        return false;
    return ++_byOutEffectCondCount >= _pSkillEffect->_byOutCD;
}

void CBattleBuff::SetCondParam(FLOAT fValue)
{
    _fCondParam = fValue;
}

void CBattleBuff::SetOutCondParam(FLOAT fValue)
{
    _fOutCondParam = fValue;
}

void CBattleBuff::SetCondParam(FLOAT fValue, bool bOut)
{
    if (bOut)
        _fOutCondParam = fValue;
    else
        _fCondParam = fValue;
}

INT32 CBattleBuff::GetCD() const
{
    return _dwCD;
}

void CBattleBuff::ResetCD(bool bInit /* = false */ )
{
    if (bInit)
        _dwCD = 1;
        //_dwCD = _pSkillEffect-> _dwCD;
    else
        _dwCD = _pSkillEffect-> _dwCD + 1;
}

void CBattleBuff::ResetCondCount()
{
    _byEffectCondCount = 0;
}

void CBattleBuff::ResetOutCondCount()
{
    _byOutEffectCondCount = 0;
}

void CBattleBuff::ReleaseCD() 
{
    -- _dwCD;
}

bool CBattleBuff::IsTurnEnable() const
{
    if (_pSkillEffect->_byTurnCD)
        return _dwTurnCD < _pSkillEffect->_byTurnCD ? true : false;
    else
        return true;

}

UINT8   CBattleBuff::GetTurnCD() const
{
    return _dwTurnCD;
}

void    CBattleBuff::AddTurnCD(UINT8 byCD)
{
    _dwTurnCD += byCD;
}

void    CBattleBuff::ResetTurnCD()
{
    _dwTurnCD = 0;
}
        
bool CBattleSkillMgr::ReloadCfg(const string& strPath)
{

    _mapSkill.clear();
    _mapSkillEffect2SkillID.clear();
    _mapSkillEffect.clear();
    return LoadSkill(strPath);
}

bool CBattleSkillMgr::Init(const string& strPath)
{
    return LoadSkill(strPath);
}

bool CBattleSkillMgr::LoadSkill(const string& strPath)
{
    if (!LoadSkillCfg(strPath))
        return false;
    if (!LoadSkillEffectCfg(strPath))
        return false;
    return true;
}

bool CBattleSkillMgr::ReLoadBaseConfig(const string& strPath, const string &strFile)
{
    if("SkillBase.xml" == strFile)
        return LoadSkillCfg(strPath);
    else
        return false;
}

bool CBattleSkillMgr::ReLoadEffectConfig(const string& strPath, const string &strFile)
{
    if("SkillEffect.xml" == strFile)
        return LoadSkillEffectCfg(strPath);
    else
        return false;
}

bool CBattleSkillMgr::LoadSkillCfg(const string& strPath)
{
    CSkillBaseLoader cfg;
    string strConfig = strPath + "Conf/Table/SkillBase.xml";

    if(!cfg.LoadData(strConfig))
        return false;

    LOG_INF << "Loading SkillBase.xml Config...";
    _mapSkill.clear();
    for (auto & pData : cfg._vecData)
    {
        SSkill* pSkill = new SSkill;
        if (pSkill == NULL)
            return false;
        pSkill->_dwID = pData->_ID;
        pSkill->_strName = pData->_Name;
        pSkill->_eType = static_cast<ESkillType>(pData->_type);
        pSkill->_bCanBeCounter = pData->_canBeCounter? true:false;
        AnalysisString2VectorUINT32(pData->_probEffect, ";", pSkill->_vecProbEffectID);
        for (auto & rID : pSkill->_vecProbEffectID)
        {
            _mapSkillEffect2SkillID[rID] = pSkill->_dwID;
        }
        AnalysisString2VectorUINT32(pData->_effectid, ";", pSkill->_vecEffectID);
        for (auto & rID : pSkill->_vecEffectID)
        {
            _mapSkillEffect2SkillID[rID] = pSkill->_dwID;
        }
        pSkill->_dwSymbol = pData->_symbol;
        pSkill->_byColor = pData->_Color;
        pSkill->_byCombineCount = pData->_skillLink;
        if(!_mapSkill.insert(make_pair(pSkill->_dwID, pSkill)).second)
        {
            LOG_CRI<<"Skill ID duplicated in Skill : "<< pSkill->_dwID;
            return false;
        }
    }
    return true;
}

bool CBattleSkillMgr::LoadSkillEffectCfg(const string& strPath)
{
    CSkillEffectLoader cfg;
    string strConfig = strPath + "Conf/Table/SkillEffect.xml";

    if(!cfg.LoadData(strConfig))
        return false;

    LOG_INF << "Loading SkillEffect.xml Config...";
    _mapSkillEffect.clear();
    for (auto & pData : cfg._vecData)
    {
        SSkillEffect* pSkillEffect = new SSkillEffect;
        if (pSkillEffect == NULL)
            return false;

        pSkillEffect->_dwID = pData->_id;
        pSkillEffect->_strName = pData->_name;

        pSkillEffect->_dwCD = pData->_cd;
        pSkillEffect->_wRate = pData->_rate;

        if (pData->_cond >= eMSMax)
        {
            LOG_CRI << "_cond = " << static_cast<UINT32>(pData->_cond);
            return false;
        }
        pSkillEffect->_eState = static_cast<EMachineState>(pData->_cond);
        AnalysisString2VectorUINT32(pData->_condstr, ";", pSkillEffect->_vecCondValue);
        pSkillEffect->_byCondCD = pData->_condCD;

        pSkillEffect->_wCondRate = pData->_condRate;

        if (pData->_outCond >= eMSMax)
        {
            LOG_CRI << "_outCond = " << static_cast<UINT32>(pData->_outCond);
            return false;
        }
        pSkillEffect->_eOutState = static_cast<EMachineState>(pData->_outCond);
        AnalysisString2VectorUINT32(pData->_outCondcondstr, ";", pSkillEffect->_vecOutCondValue);
        pSkillEffect->_byOutCD = pData->_outCD;
        
        pSkillEffect->_byTurnCD = pData->_turnNumber;

        pSkillEffect->_byLast = pData->_last;
        if (pData->_gpId >= EBFBuffTypeMax)
        {
            LOG_CRI << "_gpId = " << static_cast<UINT32>(pData->_gpId);
            return false;
        }
        pSkillEffect->_eBuffGroup = static_cast<EBStateBuffType>(pData->_gpId);
        pSkillEffect->_wArea = pData->_area;
        if (pData->_type >= ESkillEffectTypeMax)
        {
            LOG_CRI << "_type = " << static_cast<UINT32>(pData->_type);
            return false;
        }
        if ((pData->_resist) >= eResistTypeMax)
        {
            LOG_CRI << "_resist = " << static_cast<UINT32>(pData->_resist);
            return false;
        }

        pSkillEffect->_eResistType = static_cast<EResistType>((pData->_resist));
        pSkillEffect->_eSkillEffectType = static_cast<ESkillEffectType>(pData->_type);

        pSkillEffect->_fValue1 = pData->_value1;
        pSkillEffect->_fValue2 = pData->_value2;
        pSkillEffect->_fValue3 = pData->_value3;

        AnalysisString2VectorUINT32(pData->_buffID, ";", pSkillEffect->_vecBuffID);

        if(!_mapSkillEffect.insert(make_pair(pSkillEffect->_dwID, pSkillEffect)).second)
        {
            LOG_CRI<<"Skill Effect ID duplicated in Skill Effect : "<< pSkillEffect->_dwID;
            return false;
        }
        for (auto& rID : pSkillEffect->_vecBuffID)
        {
            _mapSkillEffect2SkillID[SKILL_ID(rID)] = _mapSkillEffect2SkillID[SKILL_ID(pSkillEffect->_dwID)];
        }
    }
    return true;
}

bool CBattleSkillMgr::AnalysisString2VectorUINT16(string strValue, string strSep, TVecUINT16& vOut)
{
    vOut.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        vOut.push_back(::atoi(tk[i].c_str()));
    }               
    return true;
}

bool CBattleSkillMgr::AnalysisString2VectorUINT32(string strValue, string strSep, TVecUINT32& vOut)
{
    vOut.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        vOut.push_back(::atoi(tk[i].c_str()));
    }               
    return true;
}

bool CBattleSkillMgr::AnalysisString2VectorFloat(string strValue, string strSep, TVecFloat& vOut)
{
    vOut.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        vOut.push_back(::atof(tk[i].c_str()));
    }               
    return true;
}

SSkill* CBattleSkillMgr::GetSkill(UINT32 dwSkillID)
{
    return _mapSkill[dwSkillID];
}

SSkill* CBattleSkillMgr::GetOriginSkill(UINT32 dwSkillID)
{
    return _mapSkill[_mapSkillEffect2SkillID[dwSkillID]];
}

UINT32 CBattleSkillMgr::GetOriginSkillID(UINT32 dwSkillID)
{
    return SKILLID_QUALITY_LEVEL(_mapSkill[_mapSkillEffect2SkillID[SKILL_ID(dwSkillID)]]->_dwID, SKILL_QUALITY(dwSkillID), SKILL_LEVEL(dwSkillID));
}

EBStateBuffType CBattleSkillMgr::GetGroupBuffType(UINT32 dwBuffID)
{
    return _mapSkillEffect[dwBuffID]->_eBuffGroup;
}

SSkillEffect* CBattleSkillMgr::GetSkillEf(UINT32 dwEffectID)
{
    return _mapSkillEffect[dwEffectID];
}

UINT32 CBattleSkillMgr::GetSkillIDQualityLevel(UINT32 dwSkillID, UINT8 byLevel, UINT8 byColor)
{
    if (byColor == 0)
    {
        SSkill* pSkillCfg = GetSkill(dwSkillID);
        if (!pSkillCfg)
        {
            pSkillCfg = GetOriginSkill(dwSkillID);
            if (!pSkillCfg)
                return 0;
        }
        byColor = pSkillCfg->_byColor;
    }
    return SKILLID_QUALITY_LEVEL(dwSkillID, byColor, byLevel);
}

ESkillEffectType CBattleSkillMgr::GetSkillEffectType(UINT32 dwSkillID)
{
    return _mapSkillEffect[dwSkillID]->_eSkillEffectType;
}

UINT8 CBattleSkillMgr::GetCombineCount(UINT32 dwSkillID)
{
    return _mapSkill[dwSkillID]->_byCombineCount;
}

EStateSubType CBattleSkillMgr::GetStateBuffSubType(EBStateBuffType eBStateBuffType) const
{
    EStateSubType eSubType = eStateSubNoNagetive;
    switch (eBStateBuffType)
    {
        case EBFBuffTypeNone:
            eSubType = eStateSubNone;
        default:
            break;
    }
    return eSubType;

}

EStateAddType CBattleSkillMgr::GetStateBuffAddType(EBStateBuffType eBStateBuffType) const
{
    EStateAddType eAddType = eStateAddAdd;
    switch (eBStateBuffType)
    {
        case EBFBuffTypeNone:
            eAddType = eStateAddNone;
            break;
        case EBFBuffTypeStun: //眩晕
        case EBFBuffTypeConfuse: //混乱
        case EBFBuffTypeForget: //沉默
        case EBFBuffTypePierce: //破甲
        case EBFBuffTypeSealed: //封印
        case EBFBuffTypeFreeze: //冻结
        case EBFBuffTypeClone: //分身
        case EBFBuffTypeStoned: //石化
        case EBFBuffTypeBlock: //格挡
        case EBFBuffTypeHide: //影遁
        case EBFBuffTypeCongest: //蓄力
        case EBFBuffTypeSmoke: //烟幕
        case EBFBuffTypeBlind: //致盲
        case EBFBuffTypeDmgShare:
            eAddType = eStateAddReplaceNew;
            break;
        case EBFBuffTypeCover: //掩护
        case EBFBuffTypeEShock: //电击
        case EBFBuffTypeInvincible: //无敌
        case EBFBuffTypeBleed: //流血
        case EBFBuffTypeBurned: //点燃
        case EBFBuffTypePoison: //中毒
        case EBFBuffTypeDmgReduce: //伤害减少
        case EBFBuffTypeDmgAdd: //伤害提升
        case EBFBuffTypeReflect: //反弹状态
        case EBFBuffTypeHitDown: //命中降低
        case EBFBuffTypeBeDmgReudce: //伤害减免
        case EBFBuffTypeBlunt: //麻痹
        case EBFBuffTypeIceBlade: //冰刃
        case EBFBuffTypeThunderBlade: //雷刃
        case EBFBuffTypeFireBlade: //炎刃
        case EBFBuffTypeHaloRed: //光环红
        case EBFBuffTypeAtkAdd: //攻击提升
        case EBFBuffTypeAtkSub: //攻击下降
        case EBFBuffTypeRedAdd: //免伤提升
        case EBFBuffTypeRedSub: //免伤下降
        case EBFBuffTypeHaloBlue: //光环蓝
        case EBFBuffTypeAttrAdd: //属性增益
        case EBFBuffTypeAttrSub: //属性减益
            eAddType = eStateAddReplaceNew;
            break;
        case EBFBuffTypeSnowSoul: //雪魂
        case EBFBuffTypeGuard: //护卫
        case EBFBuffTypeKindKing: //仁王
        case EBFBuffTypeShield: //护盾
        case EBFBuffTypeBronze: //铜人
        case EBFBuffTypeKingkong: //金刚
        case EBFBuffTypeDrogenSting: // 龙刺
        case EBFBuffTypeActAtkAdd: //行动后攻击增加
        case EBFBuffTypeActDefAdd: //行动后防御增加
            eAddType = eStateAddAdd;
            break;
        default:
            break;
    }
    return eAddType;
}

void CBattleSkillMgr::GetAllSkillEffectWithType(UINT32 dwSkillID, ESkillEffectType eType, TSetUINT32& rsetExcpEffectID, TVecSkillEffectPtr& rvecSEf)
{
    SSkillEffect* pSEf = GetSkillEf(dwSkillID);
    if (!pSEf)
        return;
    if (pSEf->_eSkillEffectType == eType)
        rvecSEf.push_back(pSEf);
    size_t szCount = pSEf->_vecBuffID.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwEffectID = pSEf->_vecBuffID[szIndex];
        if (rsetExcpEffectID.find(dwEffectID) != rsetExcpEffectID.end())
            continue;
        rsetExcpEffectID.insert(dwEffectID);
        GetAllSkillEffectWithType(dwEffectID , eType, rsetExcpEffectID, rvecSEf);
    }
}

void CBattleSkillMgr::GetPassiveSkillEffect(UINT32 dwSkillID, TVecBattleSkillEffect& vecBattleSkillEffect)
{
    SSkill* pSkill = GetSkill(SKILL_ID(dwSkillID));
    if(!pSkill)
        return;

    UINT32 dwSkillQuality = SKILL_QUALITY(dwSkillID);
    UINT32 dwSkillLevel   = SKILL_LEVEL(dwSkillID);

    size_t szCount = pSkill->_vecEffectID.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwEffectID = SKILLID_QUALITY_LEVEL(pSkill->_vecEffectID[szIndex], dwSkillQuality, dwSkillLevel);
        SSkillEffect* pSEf = GetSkillEf(dwEffectID);
        if(!pSEf)
            continue;
        CBattleSkillEffect cBattleSkillEffect(pSEf);
        vecBattleSkillEffect.push_back(cBattleSkillEffect);
    }
}

void CBattleSkillMgr::GetSkillEffectWithProb(UINT32 dwSkillID, UINT32 dwSymbolID, TVecBattleSkillEffect& vecBattleSkillEffect, TVecUINT16& rvecProb)
{
    SSkill* pSkill = GetSkill(SKILL_ID(dwSkillID));
    if(!pSkill)
        return;

    UINT32 dwSkillQuality = SKILL_QUALITY(dwSkillID);
    UINT32 dwSkillLevel   = SKILL_LEVEL(dwSkillID);

    // 概率互斥效果
    size_t szCount = pSkill->_vecProbEffectID.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwEffectID = SKILLID_QUALITY_LEVEL(pSkill->_vecProbEffectID[szIndex], dwSkillQuality, dwSkillLevel);
        UINT16 rnd = CRandom::RandInt(0, 9999);
        SSkillEffect* pSEf = GetSkillEf(dwEffectID);
        if(!pSEf)
            continue;
        if(rnd < pSEf->GetRate())
        {
            CBattleSkillEffect cBattleSkillEffect(pSEf);
            vecBattleSkillEffect.push_back(cBattleSkillEffect);
            rvecProb.push_back(10000);
            break;
        }
        rnd -= pSEf->GetRate();
    }

    // 概率独立效果
    szCount = pSkill->_vecEffectID.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwEffectID = SKILLID_QUALITY_LEVEL(pSkill->_vecEffectID[szIndex], dwSkillQuality, dwSkillLevel);
        SSkillEffect* pSEf = GetSkillEf(dwEffectID);
        if(!pSEf)
            continue;

        UINT16 wRate = pSEf->GetRate()?pSEf->GetRate():10000;

        CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(pSEf->_wArea);
        if (pArea && pArea->GetRateType() == eAreaRateSame)
        {
            UINT16 rnd = CRandom::RandInt(0, 9999);
            if(rnd < pSEf->GetRate())
                wRate = 10000;
        }

        if (wRate)
        {
            CBattleSkillEffect cBattleSkillEffect(pSEf);
            vecBattleSkillEffect.push_back(cBattleSkillEffect);
            rvecProb.push_back(wRate);
        }
    }

    // 技能符文
    pSkill = GetSkill(SKILL_ID(dwSymbolID));
    if(!pSkill)
        return;

    dwSkillQuality = SKILL_QUALITY(dwSymbolID);
    dwSkillLevel   = SKILL_LEVEL(dwSymbolID);


    // 概率互斥效果
    szCount = pSkill->_vecProbEffectID.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwEffectID = SKILLID_QUALITY_LEVEL(pSkill->_vecProbEffectID[szIndex], dwSkillQuality, dwSkillLevel);
        UINT16 rnd = CRandom::RandInt(0, 9999);
        SSkillEffect* pSEf = GetSkillEf(dwEffectID);
        if(!pSEf)
            continue;
        if(rnd < pSEf->GetRate())
        {
            CBattleSkillEffect cBattleSkillEffect(pSEf);
            vecBattleSkillEffect.push_back(cBattleSkillEffect);
            rvecProb.push_back(10000);
            break;
        }
        rnd -= pSEf->GetRate();
    }

    // 概率独立效果
    szCount = pSkill->_vecEffectID.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwEffectID = SKILLID_QUALITY_LEVEL(pSkill->_vecEffectID[szIndex], dwSkillQuality, dwSkillLevel);
        SSkillEffect* pSEf = GetSkillEf(dwEffectID);
        if(!pSEf)
            continue;

        UINT16 wRate = pSEf->GetRate()?pSEf->GetRate():10000;

        CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(pSEf->_wArea);
        if (pArea && pArea->GetRateType() == eAreaRateSame)
        {
            UINT16 rnd = CRandom::RandInt(0, 9999);
            if(rnd < pSEf->GetRate())
                wRate = 10000;
        }

        if (wRate)
        {
            CBattleSkillEffect cBattleSkillEffect(pSEf);
            vecBattleSkillEffect.push_back(cBattleSkillEffect);
            rvecProb.push_back(wRate);
        }

    }
    return;
}

void CBattleSkillMgr::InitSkillEffectWithProb(const TVecUINT32& rvecEffectID, TVecBattleSkillEffect& rvecBattleSkillEffect, TVecUINT16& rvecProb)
{
    size_t szCount = rvecEffectID.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        UINT32 dwEffectID = rvecEffectID[szIndex];
        SSkillEffect* pSEf = GetSkillEf(dwEffectID);
        if (pSEf)
        {
            UINT16 wRate = pSEf->GetRate()?pSEf->GetRate():10000;

            CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(pSEf->_wArea);
            if (pArea && pArea->GetRateType() == eAreaRateSame)
            {
                UINT16 rnd = CRandom::RandInt(0, 9999);
                if(rnd < pSEf->GetRate())
                    wRate = 10000;
                else
                    wRate = 0;
            }

            BATTLE_DBG << pSEf->_strName << ": " << wRate << ".";

            if (wRate)
            {
                CBattleSkillEffect cBattleSkillEffect(pSEf);
                rvecBattleSkillEffect.push_back(cBattleSkillEffect);
                rvecProb.push_back(wRate);
            }
        }
    }
}

UINT32 CBattleSkillMgr::GetSymbolSkillID(UINT32 dwSkillID)
{
    SSkill* pSkill = GetSkill(dwSkillID);
    if(!pSkill)
        return  0;
    return pSkill->_dwSymbol;
}

const string& CBattleSkillMgr::GetSkillName(UINT32 dwSkillID)
{
    SSkill* pSkill = GetSkill(SKILL_ID(dwSkillID));
    if(pSkill)
        return pSkill->_strName;
    return INVALID_SKILL;
}

bool CBattleSkillMgr::CanBeCounter(UINT32 dwSkillID)
{
    SSkill* pSkill = GetSkill(dwSkillID);
    if (pSkill)
        return pSkill->_bCanBeCounter;
    else
        return false;
}

ESkillType CBattleSkillMgr::GetSkillType(UINT32 dwSkillID)
{
    SSkill* pSkill = GetSkill(dwSkillID);
    if (pSkill)
        return pSkill->_eType;
    else
        return eSkillNone;

}

// 获取该技能以及后续所有技能可能召唤的人物ID
void CBattleSkillMgr::GetAllSummonFighterID(UINT32 dwSkillID, TSetUINT16& rsetFighterID)
{
    SSkill* pSkill = GetSkill(SKILL_ID(dwSkillID));
    if(!pSkill)
        return;

    UINT32 dwSkillQuality = SKILL_QUALITY(dwSkillID);
    UINT32 dwSkillLevel = SKILL_LEVEL(dwSkillID);

    TSetUINT32 setInitedEffect;
    TVecSkillEffectPtr vecSEf;

    // 概率互斥效果
    for (auto & rID : pSkill->_vecProbEffectID)
    {
        UINT32 dwEffectID = SKILLID_QUALITY_LEVEL(rID, dwSkillQuality, dwSkillLevel);
        if (setInitedEffect.find(dwEffectID) != setInitedEffect.end())
            continue;
        setInitedEffect.insert(dwEffectID);
        
        GetAllSkillEffectWithType(dwEffectID, ESummon, setInitedEffect, vecSEf);
    }

    // 概率独立效果
    for (auto & rID : pSkill->_vecEffectID)
    {
        UINT32 dwEffectID = SKILLID_QUALITY_LEVEL(rID, dwSkillQuality, dwSkillLevel);
        if (setInitedEffect.find(dwEffectID) != setInitedEffect.end())
            continue;
        setInitedEffect.insert(dwEffectID);

        GetAllSkillEffectWithType(dwEffectID, ESummon, setInitedEffect, vecSEf);
    }

    for (auto & pSkillEffect : vecSEf)
    {
        rsetFighterID.insert(static_cast<UINT16>(pSkillEffect->_fValue1));
    }
    return;
}

} // namespace NBattle

