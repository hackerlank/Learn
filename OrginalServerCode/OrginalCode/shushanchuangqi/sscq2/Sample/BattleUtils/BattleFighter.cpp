#include "CommonDef.h"

#include "BattleFighter.h"
#include "BattleSkill.h"
#include "Random.h"
#include "BattleDebugger.h"

namespace NBattle
{

static CBattleBuff s_cTmpBuff;

// ===  FUNCTION  ======================================================================
//         Name:  CBattleFighter
//  Description:  构造函数
// =====================================================================================
CBattleFighter::CBattleFighter() : 
    _byIndex(0), _byGroupID(0), _byField(0), _bySide(0),
    _dwPeerless(0), _dwPlSymbol(0), _dwNormalAtk(0), _dwActiveSkillIdx(0),
    _dwBuffResist(0),
    _bySummonLast(0)
{
    memset(_dwActiveSkill,      0, sizeof(_dwActiveSkill)); // 主动
    memset(_dwActiveSymbol,     0, sizeof(_dwActiveSymbol)); // 主动技能符文
    memset(_dwActiveSkillEx,    0, sizeof(_dwActiveSkillEx)); // 主动
    memset(_dwActiveSymbolEx,   0, sizeof(_dwActiveSymbolEx)); // 主动技能符文

    VECATTR_RESET(_vecAttrBase);
    VECATTR_RESET(_vecAttrExtra);

    _vecStateValue.resize(EBFBuffTypeMax);
    _vecStateFactor.resize(EBFBuffTypeMax);
    _vecResistFactor.resize(eResistTypeMax);

    _vecStateID.resize(EBFBuffTypeMax);

    _vecBuffCond.resize(eMSMax);
    _vecBuffOutCond.resize(eMSMax);
}		// -----  end of function CBattleFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CBattleFighter
//  Description:  析构函数
// =====================================================================================
CBattleFighter::~CBattleFighter()
{
}		// -----  end of function ~CBattleFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitFighter
//  Description:  从CFighter对象上初始化CBattleFighter属性参数
// =====================================================================================
bool CBattleFighter::InitFighter(const SBFInfo& rBFInfo)
{
    _oFighterInfo.qwInstID    = rBFInfo.qwInstID; //将唯一ID
    _oFighterInfo.wFighterID  = rBFInfo.wFighterID; //将类型ID
    _oFighterInfo.iPos        = rBFInfo.dwPos; //阵型中的位置
    _oFighterInfo.byTeamID    = rBFInfo.byTeamID; // 队伍ID
	_oFighterInfo.byLevel     = rBFInfo.byLevel; //等级
    _oFighterInfo.strName     = rBFInfo.strName;
    _oFighterInfo.eSex        = rBFInfo.eSex;
    _oFighterInfo.eCareer     = rBFInfo.eJob;

    _oFighterInfo.pFeature = rBFInfo.pFeature;

#ifdef BATTLE_FIGHTER_DEBUG
    ostringstream strInfo;
    strInfo << _oFighterInfo.strName;
    switch (_oFighterInfo.eCareer)
    {
        case ECAREER_RU:
            strInfo << "（儒）";
            break;
        case ECAREER_SHI:
            strInfo << "（释）";
            break;
        case ECAREER_DAO:
            strInfo << "（道）";
            break;
        case ECAREER_MO:
            strInfo << "（墨）";
            break;
        default:
            strInfo << "（???）";
            break;
    }
    strInfo << ":";
    if (_oFighterInfo.iPos >= 0 && _oFighterInfo.iPos < MAX_POS)
        strInfo << (UINT32) _oFighterInfo.iPos % ROW_LEN << "," << (UINT32) _oFighterInfo.iPos / ROW_LEN << ".";
    else
        strInfo << "阵灵(" << _oFighterInfo.iPos << ").";
    BATTLE_DBG << strInfo.str();
#endif
    return true;
}		// -----  end of function InitFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitFighterAttr
//  Description:  初始化CBattleFighter一级属性参数
// =====================================================================================
bool CBattleFighter::InitFighterAttr(const TVecFloat& rvecFighterAttr)
{
    _oFighterInfo.oAttrVec.clear();

    for (size_t szIndex = 0; szIndex < rvecFighterAttr.size(); ++ szIndex)
    {
        if (rvecFighterAttr[szIndex] > 0.00005f
                || rvecFighterAttr[szIndex] < -0.00005f)
        {
            SFtAttrMod sAttr(EFighterAttr(szIndex), rvecFighterAttr[szIndex]);
            _oFighterInfo.oAttrVec.push_back(sAttr);
        }
    }
    _vecAttrBase = rvecFighterAttr;

#ifdef BATTLE_FIGHTER_DEBUG_ATTR
    string strAttr = GetAddAttrStr(rvecFighterAttr);
    BATTLE_DBG << strAttr;
    BATTLE_DBG << "属性战力: " << GetAttrBattlePoint();
#endif
    return true;
}		// -----  end of function InitFighterAttr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitFighterBattleInfo
//  Description:  初始化CBattleFighter身上战斗相关属性参数
// =====================================================================================
bool CBattleFighter::InitFighterBattleInfo(UINT32 dwHpMax, UINT32 dwHp, UINT32 dwAura, UINT32 dwAuraMax)
{
    _oFighterInfo.dwHpMax     = dwHpMax;
    _oFighterInfo.dwHp        = dwHp;
    _oFighterInfo.dwAura      = dwAura;
    _oFighterInfo.dwAuraMax   = dwAuraMax;
#ifdef BATTLE_FIGHTER_DEBUG_ATTR
    BATTLE_DBG << "dwHpMax: " << _oFighterInfo.dwHpMax << ", dwHp: " << _oFighterInfo.dwHp << ", dwAura: " << _oFighterInfo.dwAura << ", dwAuraMax: " << _oFighterInfo.dwAuraMax;
#endif
    return true;
}		// -----  end of function InitFighterBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetFighterAttr
//  Description:  单独设置某一属性值
// =====================================================================================
bool CBattleFighter::SetFighterAttr(UINT8 byIndex, FLOAT fValue)
{
    if (byIndex >= static_cast<UINT8>(EFIGHTATTR_MAX))
        return false;

    bool bSet = false;
    for(auto rInfo : _oFighterInfo.oAttrVec)
    {
        if (rInfo._eAttr == EFighterAttr(byIndex))
        {
            rInfo._fValue = fValue;
            bSet = true;
            break;
        }
    }

    if (!bSet)
    {
        SFtAttrMod sAttr(EFighterAttr(byIndex), fValue);
        _oFighterInfo.oAttrVec.push_back(sAttr);
    }

    VECATTR_SET(_vecAttrBase, byIndex, fValue);
    return true;
}		// -----  end of function SetFighterAttr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitFighterSkills
//  Description:  初始化技能
// =====================================================================================
bool CBattleFighter::InitFighterSkills (const TVecUINT32& rvecAllSkills, UINT32 dwNormalAttack /* = 0 */)
{
    // 平砍类型
    InitNormalAttack(dwNormalAttack);

    UINT8 byActiveSkillIndex = 0;
    for (auto& rID : rvecAllSkills)
    {
        SSkill* pSkill = CBattleSkillMgr::Instance().GetSkill(SKILL_ID(rID));
        if(!pSkill)
            continue;
        switch (pSkill->_eType)
        {
            case eSkillActive: // 主动技能
                if (byActiveSkillIndex < MAX_SKILL_POS)
                    _dwActiveSkill[byActiveSkillIndex++] = rID;
                break;
            case eSkillPassive: // 被动技能
            case eSkillTalent:  // 天赋技能
            case eSkillPet: // 阵灵技能
            case eSkillTrump: // 法宝技能
                _vecPassiveSkill.push_back(rID);
                break;
            case eSkillCombine: // 连携技能
                _vecCombineSkill.push_back(STeamSkillInfo(GetIndex(), 0, rID));
                break;
            case eSkillPeerless: // 无双技能
            case eSkillBeauty:  // 美女技能
                _dwPeerless = rID;
                break;
            default:
                break;
        }
    }
#ifdef _DEBUG
    if (IsActiveDisable())
    {
        memset (_dwActiveSkill, 0, sizeof(_dwActiveSkill));
        _dwPeerless = 0;
    }
#endif

    InitPassiveSkillBuff();

    SyncSkillsToSkillsEx();

    // 将技能信息加载进战报中
    InitSkillInfo();

    DumpCurrentSkills();

    return true;
}		// -----  end of function InitFighterSkills  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PushMoreSkills
//  Description:  额外增加技能
// =====================================================================================
bool CBattleFighter::PushMoreSkills(const TVecUINT32& rvecSkills)
{
    for (auto& rID : rvecSkills)
    {
        SSkill* pSkill = CBattleSkillMgr::Instance().GetSkill(SKILL_ID(rID));
        if(!pSkill)
            continue;
        switch (pSkill->_eType)
        {
            case eSkillActive: // 主动技能
                for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
                {
                    if (!_dwActiveSkill[byIndex])
                    {
                        _dwActiveSkill[byIndex] = rID;
                        break;
                    }
                }
                break;
            case eSkillPassive: // 被动技能
            case eSkillTalent:  // 天赋技能
            case eSkillCombine: // 连携技能
            case eSkillPet: // 阵灵技能
            case eSkillTrump: // 法宝技能
                _vecPassiveSkill.push_back(rID);
                break;
                break;
            case eSkillPeerless: // 无双技能
            case eSkillBeauty:  // 美女技能
                _dwPeerless = rID;
                break;
            case eSkillSymbol: // 技能符文 XXX: 就不处理了
            default:
                break;
        }
    }

    InitCombineSkill();

    InitPassiveSkillBuff();
    InitSkillInfo();
    return true;
}		// -----  end of function PushMoreSkills  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitFighterSkillsEx
//  Description:  初始化额外的备用技能供切换用
// =====================================================================================
bool CBattleFighter::InitFighterSkillsEx(const vector<TVecUINT32>& rvecvecAllSkills, const TVecUINT32& vecNormalAttack)
{
    for (auto & rvecAllSkills : rvecvecAllSkills)
    {
        TVecUINT32 vecActiveSkill;
        TVecUINT32 vecSymbolSkill;
        TVecUINT32 vecPassiveSkill;
        UINT32 dwPeerless = 0;
        for (auto& rID : rvecAllSkills)
        {
            SSkill* pSkill = CBattleSkillMgr::Instance().GetSkill(SKILL_ID(rID));
            if(!pSkill)
                continue;
            switch (pSkill->_eType)
            {
                case eSkillActive: // 主动技能
                    vecActiveSkill.push_back(rID);
                    break;
                case eSkillPassive: // 被动技能
                case eSkillTalent:  // 天赋技能
                case eSkillCombine: // 连携技能
                case eSkillBeauty:  // 美女技能
                case eSkillTrump: // 法宝技能
                    vecPassiveSkill.push_back(rID);
                    break;
                    break;
                case eSkillPeerless: // 无双技能
                case eSkillPet: // 阵灵技能
                    dwPeerless = rID;
                    break;
                case eSkillSymbol: // 技能符文 XXX: 就不处理了
                    vecSymbolSkill.push_back(rID);
                default:
                    break;
            }
        }

        // 主动技能
        _vecvecActiveSkill.push_back(vecActiveSkill);
        _vecPeerless.push_back(dwPeerless);

        // 技能符文
        _vecvecSymbol.push_back(vecSymbolSkill);

        // 被动技能
        _vecvecPassiveSkill.push_back(vecPassiveSkill);
    }

    // 平砍类型
    _vecNormalAttack.insert(_vecNormalAttack.end(), vecNormalAttack.begin(), vecNormalAttack.end());


    // 将技能信息加载进战报中
    InitSkillInfo();

    DumpAllSkills();
    return true;
}		// -----  end of function InitFighterSkillsEx  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SummonFromAnother
//  Description:  从某个散仙召唤出对应的召唤物（有属性百分比加成）
// =====================================================================================
bool CBattleFighter::SummonFromAnother(CBattleFighterPtr pFighter, UINT32 dwParam, CBattleFighter* pFighterOrigin)
{
    _oFighterInfo.qwInstID    = pFighter->_oFighterInfo.qwInstID; //将唯一ID
    _oFighterInfo.wFighterID  = pFighter->_oFighterInfo.wFighterID; //将类型ID
    _oFighterInfo.iPos        = pFighter->_oFighterInfo.iPos; //阵型中的位置
    _oFighterInfo.byTeamID    = pFighter->_oFighterInfo.byTeamID; // 队伍ID
	_oFighterInfo.byLevel     = pFighter->_oFighterInfo.byLevel; //等级
    _oFighterInfo.strName     = pFighter->_oFighterInfo.strName;
    _oFighterInfo.eSex        = pFighter->_oFighterInfo.eSex;
    _oFighterInfo.eCareer     = pFighter->_oFighterInfo.eCareer;

    _oFighterInfo.pFeature = pFighter->_oFighterInfo.pFeature;

    _oFighterInfo.oAttrVec = pFighter->_oFighterInfo.oAttrVec;

    TVecFtAttrMod vecAttrTmp;

    // 召唤者对召唤物的属性加成
    if (dwParam && pFighterOrigin)
    {
        for (auto & rInfoOrigin : pFighterOrigin->_oFighterInfo.oAttrVec)
        {
            // 暴击伤害，初始灵气和最大灵气值不需要加成
            if (rInfoOrigin._eAttr == EFIGHTATTR_CRIEXTRAADD
                    || rInfoOrigin._eAttr == EFIGHTATTR_INITAURA
                    || rInfoOrigin._eAttr == EFIGHTATTR_MAXAURA)
                continue;
            bool bSet = false;
            for (auto & rInfo : _oFighterInfo.oAttrVec)
            {
                if (rInfoOrigin._eAttr == rInfo._eAttr)
                {
                    rInfo._fValue += rInfoOrigin._fValue * dwParam / 10000;
                    bSet = true;
                    break;
                }
            }
            if (!bSet)
            {
                SFtAttrMod sAttr(rInfoOrigin._eAttr, rInfoOrigin._fValue * dwParam / 10000);
                vecAttrTmp.push_back(sAttr);
            }
        }
        _oFighterInfo.oAttrVec.insert(_oFighterInfo.oAttrVec.end(), vecAttrTmp.begin(), vecAttrTmp.end());
    }

    for (auto& rInfo : _oFighterInfo.oAttrVec)
    {
        VECATTR_SET(_vecAttrBase, rInfo._eAttr, rInfo._fValue);
    }

    _oFighterInfo.dwHpMax     = GetAttr(EFIGHTATTR_MAXHP);
    _oFighterInfo.dwHp        = GetAttr(EFIGHTATTR_MAXHP);
    _oFighterInfo.dwAura      = GetAttr(EFIGHTATTR_INITAURA);
    _oFighterInfo.dwAuraMax   = GetAttr(EFIGHTATTR_MAXAURA);

    _dwNormalAtk = pFighter->_dwNormalAtk;

    for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
    {
        _dwActiveSkill[byIndex] = pFighter->_dwActiveSkill[byIndex];
        _dwActiveSymbol[byIndex] = pFighter->_dwActiveSymbol[byIndex];
    }

    InitPassiveSkill(pFighter->_vecPassiveSkill);

    SyncSkillsToSkillsEx();

    InitSkillInfo();

    return true;
}		// -----  end of function SummonFromAnother  ----- //

bool CBattleFighter::GetSummonFighterID(TSetUINT16& rsetFighterID)
{
    for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
    {
        CBattleSkillMgr::Instance().GetAllSummonFighterID(_dwActiveSkill[byIndex], rsetFighterID);
        CBattleSkillMgr::Instance().GetAllSummonFighterID(_dwActiveSymbol[byIndex], rsetFighterID);
    }
    CBattleSkillMgr::Instance().GetAllSummonFighterID(_dwPeerless, rsetFighterID);
    CBattleSkillMgr::Instance().GetAllSummonFighterID(_dwPlSymbol, rsetFighterID);
    for (auto it = _vecPassiveSkill.begin(); it != _vecPassiveSkill.end(); ++it)
    {
        CBattleSkillMgr::Instance().GetAllSummonFighterID(*it, rsetFighterID);
    }
    return true;
}

UINT16 CBattleFighter::GetID() const
{
    return _oFighterInfo.wFighterID;
}

UINT8 CBattleFighter::GetColour() const
{
    return GetQuality();
}

UINT8 CBattleFighter::GetQuality() const
{
    UINT8 byQuality = 3;
    if (_oFighterInfo.pFeature)
    {
        switch(_oFighterInfo.pFeature->GetClassType())
        {
            case eType_SPlayerFeature:
                {
                    SPlayerFeaturePtr pPlayerFeature = dynamic_pointer_cast<SPlayerFeature>(_oFighterInfo.pFeature);
                    byQuality = pPlayerFeature->byQuality;
                }
                break;
            case eType_SHeroFeature:
                {
                    SHeroFeaturePtr pHeroFeature = dynamic_pointer_cast<SHeroFeature>(_oFighterInfo.pFeature);
                    byQuality = pHeroFeature->byQuality;
                }
                break;
            default:
                break;

        }
    }
    return byQuality;

}

UINT64 CBattleFighter::GetInstID() const
{
    return _oFighterInfo.qwInstID;
}

bool CBattleFighter::IsPhyJob() const
{
    bool bRet = false;
    switch(_oFighterInfo.eCareer)
    {
        case ECAREER_SHI:
        case ECAREER_MO:
            bRet = true;
        default:
            break;
    }
    return bRet;
}

bool CBattleFighter::IsMgcJob() const
{
    bool bRet = false;
    switch(_oFighterInfo.eCareer)
    {
        case ECAREER_RU:
        case ECAREER_DAO:
            bRet = true;
        default:
            break;
    }
    return bRet;
}

void CBattleFighter::GetBattleFighterInfo(SBattleFighter& sBf) const
{
    sBf.byFighterID = _byIndex;
    sBf.oFgtInfo    = _oFighterInfo;
}

// ===  FUNCTION  ======================================================================
//         Name:  InitFromInfo
//  Description:  从协议数据中反序列化出对应的战斗信息
// =====================================================================================
bool CBattleFighter::InitFromInfo(const SBattleFighter& rBF, ::TVecBattleFighterPtr& rvecBattleFighterSummon)
{

    _byIndex             = rBF.byFighterID;
    _oFighterInfo        = rBF.oFgtInfo;

    for (auto& rInfo : _oFighterInfo.oAttrVec)
    {
        VECATTR_SET(_vecAttrBase, rInfo._eAttr, rInfo._fValue);
    }


    if (GetPos() < MAX_POS) // 阵灵没有平砍
    {
        UINT32 dwNormalAttack = 0;
        auto it = _oFighterInfo.vActiveSkill.begin();
        if (it != _oFighterInfo.vActiveSkill.end())
        {
            dwNormalAttack = (*it).dwSkillID;
            _oFighterInfo.vActiveSkill.erase(it);
        }
        InitNormalAttack(dwNormalAttack);
    }

    TVecUINT32 vecActiveSkill;
    TVecUINT32 vecSymbolSkill;
    TVecUINT32 vecPassiveSkill;

    UINT32     dwPeerless = 0;

    dwPeerless  = _oFighterInfo.oPeerLees.dwSkillID;
    _dwPlSymbol = _oFighterInfo.oPeerLees.dwSymboleID;

    for (auto it = _oFighterInfo.vActiveSkill.begin(); it != _oFighterInfo.vActiveSkill.end(); ++it)
    {
        vecActiveSkill.push_back((*it).dwSkillID);
        vecSymbolSkill.push_back((*it).dwSymboleID);
    }

    InitActiveSkill(vecActiveSkill, dwPeerless);
    InitSymbolSkill(vecSymbolSkill);

    for (auto& rInfo : _oFighterInfo.vPassiveSkill)
    {
        vecPassiveSkill.push_back(rInfo.dwSkillID);
    }


    InitPassiveSkill(vecPassiveSkill);

    SyncSkillsToSkillsEx();

    // 将技能信息加载进战报中
    InitSkillInfo();

    DumpCurrentSkills();

    return true;
}		// -----  end of function InitFromInfo  ----- //

UINT8 CBattleFighter::GetIndex() const
{ 
    return _byIndex;
}

UINT8 CBattleFighter::GetGroupID() const
{ 
    return _byGroupID;
}

UINT8 CBattleFighter::GetField() const
{ 
    return _byField;
}

UINT8 CBattleFighter::GetSide() const
{ 
    return _bySide;
}

UINT8 CBattleFighter::GetTeamID() const
{
    return _oFighterInfo.byTeamID;
}

void  CBattleFighter::SetSide(UINT8 bySide) 
{ 
    _bySide = bySide;
}

INT32 CBattleFighter::GetPos() const
{ 
    return _oFighterInfo.iPos;
}

SFeatureBasePtr CBattleFighter::GetFeature()
{
    return _oFighterInfo.pFeature;
}

void  CBattleFighter::SetPos(INT32 dwPos) 
{ 
    _oFighterInfo.iPos  = dwPos;
}

const string& CBattleFighter::GetName() const
{ 
    return _oFighterInfo.strName;
}

UINT16  CBattleFighter::GetLevel() const
{
	return _oFighterInfo.byLevel;
}

void   CBattleFighter::SetLevel(UINT32 dwLevel)
{
    _oFighterInfo.byLevel = dwLevel;
}

// ===  FUNCTION  ======================================================================
//         Name:  UpdateIndex
//  Description:  更新场地编号
// =====================================================================================
void CBattleFighter::UpdateIndex()
{
    _byField = 0;
    _byGroupID = _bySide;

    if (_oFighterInfo.iPos == SCENE_POS) //  这个是场景对象
        _byIndex = SCENE_POS;
    else if (_oFighterInfo.iPos > MAX_POS * 2)
        _byIndex = _bySide + _oFighterInfo.iPos;
    else
        _byIndex = _bySide * MAX_POS + _oFighterInfo.iPos;
}		// -----  end of function UpdateIndex  ----- //

FLOAT CBattleFighter::GetAttr(EFighterAttr eIdx) const
{
    return VECATTR_GET(_vecAttrBase, eIdx);
}

FLOAT CBattleFighter::GetAttrExtra(EFighterAttr eIdx) const
{
    return VECATTR_GET(_vecAttrExtra, eIdx);
}

FLOAT CBattleFighter::GetAttrFinal(EFighterAttr eIdx) const
{
    return VECATTR_GET(_vecAttrBase, eIdx) + VECATTR_GET(_vecAttrExtra, eIdx);
}

FLOAT CBattleFighter::GetAttack() const
{
    if (IsPhyJob())
        return GetAttrFinal(EFIGHTATTR_PHYATK);
    else if (IsMgcJob())
        return GetAttrFinal(EFIGHTATTR_MGCATK);
    return 0;
}

FLOAT CBattleFighter::GetSpeed() const
{
    return GetAttrFinal(EFIGHTATTR_SPEED) * (1 + GetAttrFinal(EFIGHTATTR_SPEED_PER));
}

void CBattleFighter::AddAura(UINT32 dwAura)
{
    _oFighterInfo.dwAura += dwAura;
    if(_oFighterInfo.dwAura > GetAttr(EFIGHTATTR_MAXAURA))
        _oFighterInfo.dwAura = GetAttr(EFIGHTATTR_MAXAURA);
}

void CBattleFighter::SubAura(UINT32 dwAura)
{
    if (_oFighterInfo.dwAura < dwAura)
        _oFighterInfo.dwAura = 0;
    else
        _oFighterInfo.dwAura -= dwAura;
}

void CBattleFighter::SetAura(UINT32 dwAura)
{
    _oFighterInfo.dwAura = dwAura;
}

UINT32 CBattleFighter::GetAura() const 
{ 
    return _oFighterInfo.dwAura; 
}

UINT32 CBattleFighter::GetMaxAura() const
{
    return GetAttr(EFIGHTATTR_MAXAURA);
}

UINT32 CBattleFighter::MakeDmg(UINT32 dwDmg)
{
    if(dwDmg > _oFighterInfo.dwHp)
        _oFighterInfo.dwHp = 0;
    else
        _oFighterInfo.dwHp -= dwDmg;

    return dwDmg;
}

// ===  FUNCTION  ======================================================================
//         Name:  MakeShieldDmg
//  Description:  对护盾造成伤害
// =====================================================================================
UINT32 CBattleFighter::MakeShieldDmg(UINT32& dwDmg, TVecUINT32& rvecBuffKey)
{
    UINT32 dwShield = GetStateValue(EBFBuffTypeShield);
    UINT32 dwShieldDmg = 0;
    if (dwShield)
    {
        if (dwDmg >= dwShield)
        {
            dwShieldDmg = dwShield + 1; // XXX: 因为有效位数问题，没法降到0.0001以下
            dwDmg -= dwShield;
        }
        else
        {
            dwShieldDmg = dwDmg;
            dwShield -= dwDmg;
            dwDmg = 0;
        }
        SubStateValue(EBFBuffTypeShield, dwShieldDmg, rvecBuffKey);
    }
    return dwShieldDmg;
}		// -----  end of function MakeShieldDmg  ----- //

UINT32 CBattleFighter::RegenHP(UINT32 rhp)
{
    if(rhp + _oFighterInfo.dwHp > GetAttr(EFIGHTATTR_MAXHP))
        _oFighterInfo.dwHp = GetAttr(EFIGHTATTR_MAXHP);
    else
        _oFighterInfo.dwHp += rhp;

    return rhp;
}

UINT32 CBattleFighter::RegenAllHP()
{
    _oFighterInfo.dwHp = GetAttr(EFIGHTATTR_MAXHP);
    return _oFighterInfo.dwHp;
}

void CBattleFighter::SetHP(UINT32 dwHP)
{
    _oFighterInfo.dwHp = dwHP;
    if (_oFighterInfo.dwHp >= _oFighterInfo.dwHpMax)
        _oFighterInfo.dwHp = _oFighterInfo.dwHpMax;
}

void CBattleFighter::SetMaxHP(UINT32 dwMaxHP)
{
    _oFighterInfo.dwHpMax = dwMaxHP;
    SetFighterAttr(EFIGHTATTR_MAXHP,dwMaxHP);
}

UINT32 CBattleFighter::GetHP() const 
{ 
    return _oFighterInfo.dwHp; 
}

UINT32 CBattleFighter::GetHPP() const
{
    FLOAT fPercent = static_cast<FLOAT>(GetHP())/ GetMaxHP();
    return static_cast<UINT32>(fPercent * 10000);
}

UINT32 CBattleFighter::GetLostHPP() const
{
    FLOAT fPercent = static_cast<FLOAT>(GetHP())/ GetMaxHP();
    return  10000 - static_cast<UINT32>(fPercent * 10000);
}

UINT32 CBattleFighter::GetMaxHP() const
{
    return _oFighterInfo.dwHpMax;
}

// ===  FUNCTION  ======================================================================
//         Name:  GetBattlePoint
//  Description:  获取总的战斗力
// =====================================================================================
UINT32 CBattleFighter::GetBattlePoint() const
{
    UINT32 dwBattlePoint = 0;
    dwBattlePoint += GetAttrBattlePoint();
    dwBattlePoint += GetSkillBattlePoint();

    return dwBattlePoint;
}		// -----  end of function GetBattlePoint  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAttrBattlePoint
//  Description:  获取属性的战斗力
// =====================================================================================
UINT32 CBattleFighter::GetAttrBattlePoint() const
{

    UINT32 dwBattlePoint = 0;

    if (GetPos() < MAX_POS)
        dwBattlePoint += _funAttrBP(_vecAttrBase);

    return dwBattlePoint;
}		// -----  end of function GetAttrBattlePoint  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSkillBattlePoint
//  Description:  获取技能的战斗力
// =====================================================================================
UINT32 CBattleFighter::GetSkillBattlePoint() const
{

    UINT32 dwBattlePoint = 0;
    TVecUINT32 vecSkillID;
    for (UINT32 dwIndex = 0; dwIndex < MAX_SKILL_POS; ++dwIndex)
    {
        if (_dwActiveSkill[dwIndex])
            vecSkillID.push_back(_dwActiveSkill[dwIndex]);
    }
    if (_dwPeerless)
        vecSkillID.push_back(_dwPeerless);

    vecSkillID.insert(vecSkillID.end(), _vecPassiveSkill.begin(), _vecPassiveSkill.end());
    for (auto & rInfo : _vecCombineSkill)
    {
        vecSkillID.push_back(rInfo.dwSkillID);
    }

    dwBattlePoint +=_funSkillBP(vecSkillID);
    return dwBattlePoint;
}		// -----  end of function GetSkillBattlePoint  ----- //

UINT32 CBattleFighter::LaunchActiveSkill(TVecBattleSkillEffect& vecEfOut, bool bForceNormal, bool bNoPeerless, ESkillLaunchType& eType, TVecUINT16& rvecProb)
{
    if (bForceNormal)
    {
        eType = eSkillActiveNormal;
        return LaunchNormalAttack(vecEfOut, rvecProb);
    }

    if(!bNoPeerless && _dwPeerless && _oFighterInfo.dwAura >= PEERLEES_AURA)
    {
        CBattleSkillMgr::Instance().GetSkillEffectWithProb(_dwPeerless, _dwPlSymbol, vecEfOut, rvecProb);
        eType = eSkillActivePeerless;
        return _dwPeerless;
    }

    UINT32 dwActiveSkillID = _dwActiveSkill[_dwActiveSkillIdx];
    UINT32 dwActiveSymbolID = _dwActiveSymbol[_dwActiveSkillIdx];
    if(dwActiveSkillID == 0)
    {
        eType = eSkillActiveNormal;
        return LaunchNormalAttack(vecEfOut, rvecProb);
    }

    CBattleSkillMgr::Instance().GetSkillEffectWithProb(dwActiveSkillID, dwActiveSymbolID, vecEfOut, rvecProb);
    eType = eSkillActiveSkill;
    return dwActiveSkillID;
}

void CBattleFighter::ReadyForNextSkill()
{
    ++ _dwActiveSkillIdx;
    if (_dwActiveSkillIdx >= MAX_SKILL_POS)
        _dwActiveSkillIdx = 0;
}

UINT32 CBattleFighter::LaunchBeautySkill(TVecBattleSkillEffect& vecEfOut, TVecUINT16& rvecProb)
{
    if(_dwPeerless != 0 && _oFighterInfo.dwAura >= MAX_REIATSU)
    {
        CBattleSkillMgr::Instance().GetSkillEffectWithProb(_dwPeerless, _dwPlSymbol, vecEfOut, rvecProb);
        return _dwPeerless;
    }
    return 0;
}

UINT32 CBattleFighter::LaunchNormalAttack(TVecBattleSkillEffect& vecEfOut, TVecUINT16& rvecProb)
{
    CBattleSkillMgr::Instance().GetSkillEffectWithProb(_dwNormalAtk, 0, vecEfOut, rvecProb);
    return _dwNormalAtk;
}

// ===  FUNCTION  ======================================================================
//         Name:  TryToggleSkills
//  Description:  切换技能
// =====================================================================================
bool CBattleFighter::TryToggleSkills(UINT8 byIndex) 
{
    if (byIndex >= _vecvecActiveSkill.size())
    {
        LOG_CRI << "TryToggleSkills error: " << static_cast<UINT32>(byIndex) << ":" << _vecvecActiveSkill.size() << ".";
        return false;
    }

    ClearPassiveSkillBuff();

    UINT8 bySkillIndex = 0;
    for (auto it = _vecvecActiveSkill[byIndex].begin(); it != _vecvecActiveSkill[byIndex].end(); ++it)
    {
        if (bySkillIndex >= MAX_SKILL_POS)
        {
            LOG_CRI << "ActiveSkillEx to many: " << _vecvecActiveSkill.size() << ".";
            break;
        }
        _dwActiveSkill[bySkillIndex ++] = *it;
    }

    bySkillIndex = 0;
    for (auto it = _vecvecSymbol[byIndex].begin(); it != _vecvecSymbol[byIndex].end(); ++it)
    {
        if (bySkillIndex >= MAX_SKILL_POS)
        {
            LOG_CRI << "SymbolEx to many: " << _vecvecSymbol.size() << ".";
            break;
        }
        _dwActiveSymbol[bySkillIndex ++] = *it;
    }

    _dwActiveSkillIdx = 0;
    _dwPeerless = _vecPeerless[byIndex];
    _dwNormalAtk = _vecNormalAttack[byIndex];

    _vecPassiveSkill = _vecvecPassiveSkill[byIndex];

    InitCombineSkill();

    InitPassiveSkillBuff();

    return true;
}		// -----  end of function TryToggleSkills  ----- //

bool CBattleFighter::CanCounter() const
{
    if (GetHP() <= 0 || HaveState(EBFBuffTypeStun)  || HaveState(EBFBuffTypeFreeze))
        return false;
    else
        return true;
}

bool   CBattleFighter::CheckEffectMaxCount(UINT32 dwSkillID, FLOAT fValue) const
{
    //BATTLE_DBG << "dwSkillID = " << dwSkillID << ", fValue = " << fValue << ".";
    if (fValue <= 0.01f)
        return true;
    auto it = _mapEffectParam.find(dwSkillID);
    if (it == _mapEffectParam.end())
        return true;
    return it->second + 1 - fValue <= 0.01f;
}

void   CBattleFighter::SetEffectParam(UINT32 dwSkillID, FLOAT fValue)
{
    _mapEffectParam[dwSkillID] = fValue;
}

void   CBattleFighter::AddEffectParam(UINT32 dwSkillID, FLOAT fValue)
{
    _mapEffectParam[dwSkillID] += fValue;
}

FLOAT  CBattleFighter::GetEffectParam(UINT32 dwSkillID) const
{
    auto it = _mapEffectParam.find(dwSkillID);
    if (it == _mapEffectParam.end())
        return 0.0f;
    else
        return it->second;
}

void CBattleFighter::ClearEffectParam()
{
    _mapEffectParam.clear();
}

void CBattleFighter::ResetTurnCD()
{
    for (auto it = _mapBuff.begin(); it != _mapBuff.end(); ++it)
    {
        string strInfo;
#ifdef BATTLE_SKILL_BUFF_CD
        BUFF_DEBUG << "ResetTurnCD Buff CD: " << (strInfo << it->second) << ".";
#endif
        (it->second).ResetTurnCD();
    }

}

bool CBattleFighter::IsAuraGainDisabel() const
{
    for (auto& rPair: _mapEffectParam)
    {
        if (CBattleSkillMgr::Instance().GetSkillEffectType(rPair.first) == ENoGainAura && rPair.second > 0.1f)
            return true;
    }
    return false;
}

// ===  FUNCTION  ======================================================================
//         Name:  InitNormalAttack
//  Description:  初始化平砍技能
// =====================================================================================
bool CBattleFighter::InitNormalAttack(UINT32 dwNormalAttack)
{
    bool bRet = true;
    if (!dwNormalAttack)
    {
        switch (_oFighterInfo.eCareer)
        {
            case ECAREER_SHI:
                dwNormalAttack = DEFAULT_PHY_JOB_ATTACK_SHI;
                break;
            case ECAREER_MO:
                dwNormalAttack = DEFAULT_PHY_JOB_ATTACK_MO;
                break;
            case ECAREER_RU:
                dwNormalAttack = DEFAULT_MGC_JOB_ATTACK_RU;
                break;
            case ECAREER_DAO:
                dwNormalAttack = DEFAULT_MGC_JOB_ATTACK_DAO;
                break;
            default:            // 没有任何平砍技能的
                bRet = false;
                break;
        }
    }

    _dwNormalAtk = dwNormalAttack;
    return bRet;
}		// -----  end of function InitNormalAttack  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitActiveSkill
//  Description:  初始化主动技能 
// =====================================================================================
bool CBattleFighter::InitActiveSkill(const TVecUINT32& rvecActiveSkill, UINT32 dwPeerless)
{
#ifdef _DEBUG
    if (IsActiveDisable())
    {
        memset (_dwActiveSkill, 0, sizeof(_dwActiveSkill));
        _dwPeerless = 0;
        return true;
    }
#endif
    memset (_dwActiveSkill, 0, sizeof(_dwActiveSkill));
    for (auto it = rvecActiveSkill.begin(); it != rvecActiveSkill.end(); ++it)
    {
        size_t szIndex = it - rvecActiveSkill.begin();
        if(szIndex >= MAX_SKILL_POS)
            break;
        _dwActiveSkill[szIndex] = *it;
        
    }
    _dwPeerless = dwPeerless;
    return true;
}		// -----  end of function InitActiveSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitSymbolSkill
//  Description:  初始化技能符文
// =====================================================================================
bool CBattleFighter::InitSymbolSkill(const TVecUINT32& rvecSymbolSkill)
{
    memset (_dwActiveSymbol, 0, sizeof(_dwActiveSymbol));
    for (auto & rID : rvecSymbolSkill)
    {
        for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
        {
            UINT32 dwSkillID = 0;
            dwSkillID = CBattleSkillMgr::Instance().GetSymbolSkillID(SKILL_ID(_dwActiveSkill[byIndex]));
            if (SKILL_ID(rID) == dwSkillID)
            {
                _dwActiveSymbol[byIndex] = dwSkillID; // 技能符文的加载
                break;
            }
        }
    }
    return true;
}		// -----  end of function InitSymbolSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitPassiveSkill
//  Description:  初始化被动技能
// =====================================================================================
bool CBattleFighter::InitPassiveSkill(const TVecUINT32& rvecPassiveSkill)
{
#ifdef _DEBUG
    if (IsPassiveDisable())
        return false;
#endif
    _vecPassiveSkill = rvecPassiveSkill;
    InitCombineSkill();

    return InitPassiveSkillBuff();
}		// -----  end of function InitPassiveSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearPassiveSkillBuff
//  Description:  清除当前被动技能的相关Buff
// =====================================================================================
bool CBattleFighter::ClearPassiveSkillBuff()
{
    for (auto & rID : _vecPassiveSkill)
    {
        TVecBattleSkillEffect vecBattleSkillEffect;
        CBattleSkillMgr::Instance().GetPassiveSkillEffect(rID, vecBattleSkillEffect);
        for (auto & rSkillEffect : vecBattleSkillEffect)
        {
            RemoveBattleBuff(rSkillEffect.GetID());
        }
    }
    return true;
}		// -----  end of function ClearPassiveSkillBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitPassiveSkillBuff
//  Description:  初始化被动技能的相关Buff
// =====================================================================================
bool CBattleFighter::InitPassiveSkillBuff()
{
#ifdef _DEBUG
    if (IsPassiveDisable())
        return false;
#endif
    for (auto& rID : _vecPassiveSkill)
    {
        TVecBattleSkillEffect vecBattleSkillEffect;
        CBattleSkillMgr::Instance().GetPassiveSkillEffect(rID, vecBattleSkillEffect);
        for (auto& rSkillEffect : vecBattleSkillEffect)
        {
            CBattleBuff sBuff;
            CBattleFighter* pOwner;
            if (GetPos() != SCENE_POS)
                pOwner = this;
            else
                pOwner = NULL;
            if (sBuff.Build(rSkillEffect, this, pOwner))
            {
                sBuff.SetLast(INFINIT_CD);
                AddPassiveSkillBuff(sBuff);
                _setPassiveEffectID.insert(sBuff.GetID());
            }
            else
                LOG_CRI << "Build BattleBuff failed.(" << rSkillEffect.GetID() << ")";
        }
    }
    return true;
}		// -----  end of function InitPassiveSkillBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitCombineSkill
//  Description:  从被动技能中剔除出组合技能
// =====================================================================================
bool CBattleFighter::InitCombineSkill()
{
    for (size_t szIndex = 0; szIndex <  _vecPassiveSkill.size();)
    {
        UINT32 dwSkillID = SKILL_ID(_vecPassiveSkill[szIndex]);
        switch (CBattleSkillMgr::Instance().GetSkillType(dwSkillID))
        {
            case eSkillCombine: // 连携技能
                _vecCombineSkill.push_back(STeamSkillInfo(GetIndex(), 0, _vecPassiveSkill[szIndex]));
                _vecPassiveSkill.erase(_vecPassiveSkill.begin() + szIndex);
                break;
            default:
                ++szIndex;
                break;
        }
    }
    return true;
}		// -----  end of function InitCombineSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCombineSkill
//  Description:  获取组合技能（并且更具外部参数编号序数）
// =====================================================================================
const TVecTeamSkillInfo& CBattleFighter::GetCombineSkill(UINT8& rIndex)
{
    for (auto& rInfo : _vecCombineSkill)
    {
        rInfo.byIndex = (GetSide() + 1) * 100 + _oFighterInfo.byTeamID * 10 + rIndex ++;
    }
    return _vecCombineSkill;
}		// -----  end of function GetCombineSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitSkillInfo
//  Description:  将所有技能信息序列化到协议结构体中
// =====================================================================================
void CBattleFighter::InitSkillInfo()
{
    ClearSkillInfo();

    SBattleFightSkillInfo sSkillInfo;

    sSkillInfo.dwSkillID = _dwNormalAtk;
    _oFighterInfo.vActiveSkill.push_back(sSkillInfo);

    for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
    {
        if (_dwActiveSkill[byIndex])
        {
            SBattleFightSkillInfo sSkillInfo;
            sSkillInfo.dwSkillID = _dwActiveSkill[byIndex];
            sSkillInfo.dwSymboleID = _dwActiveSymbol[byIndex];
            _oFighterInfo.vActiveSkill.push_back(sSkillInfo);
        }
    }

    for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
    {
        if (_dwActiveSkillEx[byIndex])
        {
            SBattleFightSkillInfo sSkillInfo;
            sSkillInfo.dwSkillID = _dwActiveSkillEx[byIndex];
            sSkillInfo.dwSymboleID = _dwActiveSymbolEx[byIndex];
            _oFighterInfo.vActiveSkill.push_back(sSkillInfo);
        }
    }

    for (auto & rID : _vecPassiveSkill)
    {
        SBattleFightSkillInfo sSkillInfo;
        sSkillInfo.dwSkillID = rID;
        _oFighterInfo.vPassiveSkill.push_back(sSkillInfo);
    }

    for (auto & rID : _vecPassiveSkillEx)
    {
        SBattleFightSkillInfo sSkillInfo;
        sSkillInfo.dwSkillID = rID;
        _oFighterInfo.vPassiveSkill.push_back(sSkillInfo);
    }
    for (auto & rInfo : _vecCombineSkill)
    {
        SBattleFightSkillInfo sSkillInfo;
        sSkillInfo.dwSkillID = rInfo.dwSkillID;
        _oFighterInfo.vPassiveSkill.push_back(sSkillInfo);
    }

    _oFighterInfo.oPeerLees.dwSkillID   = _dwPeerless;
    _oFighterInfo.oPeerLees.dwSymboleID = _dwPlSymbol;
    _oFighterInfo.oPeerLeesEx.dwSkillID   = _dwPeerless;
    _oFighterInfo.oPeerLeesEx.dwSymboleID = _dwPlSymbol;

}		// -----  end of function InitSkillInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearSkillInfo
//  Description:  清空协议结构体中的技能信息
// =====================================================================================
void CBattleFighter::ClearSkillInfo()
{
    _oFighterInfo.vActiveSkill.clear();
    _oFighterInfo.vPassiveSkill.clear();
    _oFighterInfo.oPeerLees.dwSkillID       = 0;
    _oFighterInfo.oPeerLees.dwSymboleID     = 0;
    _oFighterInfo.oPeerLeesEx.dwSkillID       = 0;
    _oFighterInfo.oPeerLeesEx.dwSymboleID     = 0;
}		// -----  end of function ClearSkillInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPassiveSkillBuff
//  Description:  增加被动技能Buff
// =====================================================================================
bool CBattleFighter::AddPassiveSkillBuff(const CBattleBuff& rBuff)
{
    _mapBuff[rBuff.GetID()] = rBuff;

    // 特定条件才会触发的Buff类型
    if(rBuff.GetEffectCond() != eMSNone)
        _vecBuffCond[rBuff.GetEffectCond()].push_back(rBuff.GetID());
    if(rBuff.GetOutEffectCond() != eMSNone)
        _vecBuffOutCond[rBuff.GetOutEffectCond()].push_back(rBuff.GetID());

    _vecBuffOutCond[eMSRelease].push_back(rBuff.GetID());
    return true;
}		// -----  end of function AddPassiveSkillBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SyncSkillsToSkillsEx
//  Description:  将当前技能同步至所有技能
// =====================================================================================
void CBattleFighter::SyncSkillsToSkillsEx()
{
    // 平砍技能
    if (_vecNormalAttack.empty())
        _vecNormalAttack.push_back(_dwNormalAtk);
    else
        _vecNormalAttack[0] = _dwNormalAtk;

    // 主动技能
    TVecUINT32 vecActiveSkill;
    for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
    {
        vecActiveSkill.push_back(_dwActiveSkill[byIndex]);
    }
    if (_vecvecActiveSkill.empty())
        _vecvecActiveSkill.push_back(vecActiveSkill);
    else
        _vecvecActiveSkill[0] = vecActiveSkill;

    // 技能符文
    TVecUINT32 vecSymbol;
    for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
    {
        vecSymbol.push_back(_dwActiveSymbol[byIndex]);
    }
    if (_vecvecSymbol.empty())
        _vecvecSymbol.push_back(vecSymbol);
    else
        _vecvecSymbol[0] = vecSymbol;

    // 无双技能
    if (_vecPeerless.empty())
        _vecPeerless.push_back(_dwPeerless);
    else
        _vecPeerless[0] = _dwPeerless;

    // 被动技能
    if (_vecvecPassiveSkill.empty())
        _vecvecPassiveSkill.push_back(_vecPassiveSkill);
    else
        _vecvecPassiveSkill[0] = _vecPassiveSkill;

    // 连携技能
    for (auto& rInfo : _vecCombineSkill)
    {
        _vecvecPassiveSkill[0].push_back(rInfo.dwSkillID);
    }

}		// -----  end of function SyncSkillsToSkillsEx  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  DumpCurrentSkills
//  Description:  调试输出当前的技能信息
// =====================================================================================
void CBattleFighter::DumpCurrentSkills() const
{
#ifdef BATTLE_FIGHTER_DEBUG_SKILL
    ostringstream strInfo;
    strInfo << "平砍技能：";
    strInfo << CBattleSkillMgr::Instance().GetSkillName(_dwNormalAtk) << "\n";

    strInfo << "主动技能：";
    for (UINT8 byIndex = 0; byIndex < MAX_SKILL_POS; ++byIndex)
    {
        if (_dwActiveSkill[byIndex])
            strInfo << CBattleSkillMgr::Instance().GetSkillName(_dwActiveSkill[byIndex]) << "\t";
    }
    strInfo << "\n";

    strInfo << "无双技能: ";
    if (_dwPeerless)
        strInfo << CBattleSkillMgr::Instance().GetSkillName(_dwPeerless);
    strInfo << "\n";

    strInfo << "被动技能: ";
    for (auto it = _vecPassiveSkill.begin(); it != _vecPassiveSkill.end(); ++it)
    {
        if (*it)
            strInfo << CBattleSkillMgr::Instance().GetSkillName(*it) << "\t";
    }
    strInfo << "\n";

    BATTLE_DBG << "技能战斗力: " << GetSkillBattlePoint();
    BATTLE_DBG << strInfo.str() << "\n";
#endif
}		// -----  end of function DumpCurrentSkills  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  DumpAllSkills
//  Description:  调试输出所有的技能信息
// =====================================================================================
void CBattleFighter::DumpAllSkills() const
{
#ifdef BATTLE_FIGHTER_DEBUG_SKILL
    ostringstream strInfo;
    strInfo << "主动技能：\n";
    for (auto it = _vecvecActiveSkill.begin(); it != _vecvecActiveSkill.end(); ++it)
    {
        const TVecUINT32& vecActiveSkill = *it;
        for (auto it2 = vecActiveSkill.begin(); it2 != vecActiveSkill.end(); ++it2)
        {
            if (*it2)
                strInfo << CBattleSkillMgr::Instance().GetSkillName(*it2) << "\t";
        }
        strInfo << "\n";
    }
    strInfo << "平砍技能：\n";
    for (auto it = _vecNormalAttack.begin(); it != _vecNormalAttack.end(); ++it)
    {
        strInfo << CBattleSkillMgr::Instance().GetSkillName(*it) << "\n";
    }

    strInfo << "无双技能: \n";
    for (auto it = _vecPeerless.begin(); it != _vecPeerless.end(); ++it)
    {
        strInfo << CBattleSkillMgr::Instance().GetSkillName(*it) << "\n";
    }

    strInfo << "被动技能: \n";
    for (auto it = _vecvecPassiveSkill.begin(); it != _vecvecPassiveSkill.end(); ++it)
    {
        const TVecUINT32& vecPassiveSkill = *it;
        for (auto it2 = vecPassiveSkill.begin(); it2 != vecPassiveSkill.end(); ++it2)
        {
            if (*it2)
                strInfo << CBattleSkillMgr::Instance().GetSkillName(*it2) << "\t";
        }
        strInfo << "\n";
    }

    BATTLE_DBG << "技能战斗力: " << GetSkillBattlePoint();
    BATTLE_DBG << strInfo.str() << "\n";
#endif
}		// -----  end of function DumpAllSkills  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetBuff
//  Description:  重置所有buff状态
// =====================================================================================
void CBattleFighter::ResetBuff ()
{
    VECATTR_RESET(_vecAttrExtra);

    _mapEffectParam.clear();
    _mapBuff.clear();

    _vecStateValue.clear();
    _vecStateFactor.clear();
    _vecResistFactor.clear();

    _vecStateID.clear();

    _vecBuffCond.clear();
    _vecBuffOutCond.clear();

    _vecStateValue.resize(EBFBuffTypeMax);
    _vecStateFactor.resize(EBFBuffTypeMax);
    _vecResistFactor.resize(eResistTypeMax);

    _vecStateID.resize(EBFBuffTypeMax);

    _vecBuffCond.resize(eMSMax);
    _vecBuffOutCond.resize(eMSMax);

    InitPassiveSkillBuff();

}		// -----  end of function ResetBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetPassiveSkillCD
//  Description:  重置所有被动技能CD
// =====================================================================================
void CBattleFighter::ResetPassiveSkillCD ()
{
    for (auto& rPair : _mapBuff)
    {
        if (IsPassiveSkillID(rPair.second.GetID()))
        {
            rPair.second.ResetCondCount();
            rPair.second.ResetCD(true);
            rPair.second.ResetTurnCD();
        }
    }
}		// -----  end of function ResetPassiveSkillCD  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CheckAddBattleBuff
//  Description:  检查增加新Buff后抵消的老Buff，更新需要新增的Buff数据
//     调用地点： CBuffMachineState::AddProcess()
// =====================================================================================
bool CBattleFighter::CheckAddBattleBuff(CBattleBuff& rBuff, UINT32& rBuffKeyToRemove) 
{
    rBuffKeyToRemove = 0;
    return CheckTryAddStateValue(rBuff, rBuffKeyToRemove);
}		// -----  end of function CheckAddBattleBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddBattleBuff
//  Description:  在CheckAddBattleBuff之后，触发老Buff消失的状态，然后再实际装上新的Buff
//     调用地点： CBuffMachineState::AddProcess()
// =====================================================================================
bool CBattleFighter::AddBattleBuff(CBattleBuff& rBuff) 
{
    if (!TryAddStateValue(rBuff))
        return false;
    AddBuffMap(rBuff);
    return true;
}		// -----  end of function AddBattleBuff  ----- //

void CBattleFighter::AddBuffMap(CBattleBuff& rBuff)
{
    _mapBuff[rBuff.GetID()] = rBuff;

    // 特定条件才会触发的Buff类型
    if(rBuff.GetEffectCond() != eMSNone)
        _vecBuffCond[rBuff.GetEffectCond()].push_back(rBuff.GetID());
    if(rBuff.GetOutEffectCond() != eMSNone)
        _vecBuffOutCond[rBuff.GetOutEffectCond()].push_back(rBuff.GetID());

    // 持续时间无限长的Buff技能
    _vecBuffOutCond[eMSRelease].push_back(rBuff.GetID());

}

bool CBattleFighter::RemoveBattleBuff(UINT32 dwBuffID)
{
    auto it = _mapBuff.find(dwBuffID);
    if(it == _mapBuff.end())
    {
        BUFF_DEBUG << "Start RemoveBattleBuff(" << dwBuffID << ") failed.";
        return false;
    }

    CBattleBuff& rBuff = it->second;
    string strInfo;
    BUFF_DEBUG << "Start RemoveBattleBuff " << (strInfo << rBuff) << ".";
    UINT32 dwRet = TrySubStateValue(rBuff, false);

    strInfo = "";
    BUFF_DEBUG << "Remove(" << (!dwRet?"True":"False") << ") "<< (strInfo << *this << rBuff);
    if (!dwRet)
        RemoveBuffMap(rBuff);
    return (!dwRet)?true:false;

}

// ===  FUNCTION  ======================================================================
//         Name:  RemoveBuffMap
//  Description:  清除类中Buff相关保存变量
//     调用地点： RemoveBattleBuff
//                ReduceBattleBuff
//                SubStateValue (EBStateBuffType eBStateBuffType, FLOAT fValue)
// =====================================================================================
void CBattleFighter::RemoveBuffMap(CBattleBuff& rBuff)
{
    if(rBuff.GetEffectCond() != 0)
    {
        TVecUINT32& vBuffID = _vecBuffCond[rBuff.GetEffectCond()];
        if (!vBuffID.empty())
            vBuffID.erase(std::find(vBuffID.begin(), vBuffID.end(), rBuff.GetID()));

    }
    if(rBuff.GetOutEffectCond() != 0 && rBuff.GetEffectCond() != rBuff.GetOutEffectCond())
    {
        TVecUINT32& vBuffID = _vecBuffOutCond[rBuff.GetOutEffectCond()];
        if (!vBuffID.empty())
            vBuffID.erase(std::find(vBuffID.begin(), vBuffID.end(), rBuff.GetID()));
    }
    TVecUINT32& vBuffID = _vecBuffOutCond[eMSRelease];
    if (!vBuffID.empty())
        vBuffID.erase(std::find(vBuffID.begin(), vBuffID.end(), rBuff.GetID()));
    _mapBuff.erase(rBuff.GetID());
}		// -----  end of function RemoveBuffMap  ----- //

bool CBattleFighter::RemoveBattleBuff(const TSetUINT32 setBuffID)
{
    for (auto it = setBuffID.begin(); it != setBuffID.end(); ++it)
        RemoveBattleBuff(*it);
    return true;
}

UINT32 CBattleFighter::ReduceBattleBuff(UINT32 dwBuffID)
{
    UINT32 dwRet = 0;
    BUFF_DEBUG << "Start ReduceBattleBuff(" << dwBuffID << ").";
    auto it = _mapBuff.find(dwBuffID);
    if(it == _mapBuff.end())
        return 0;
    CBattleBuff& rBuff = it->second;
    dwRet = TrySubStateValue(rBuff, true);
    if (!dwRet) // 需要移除所有Buff
    {
        RemoveBuffMap(rBuff);
        dwRet = 0;
    }
    return dwRet;

}

// ===  FUNCTION  ======================================================================
//         Name:  RemoveStateValue
//  Description:  移除某一种状态的所有Buff
// =====================================================================================
bool CBattleFighter::RemoveStateValue(EBStateBuffType eBStateBuffType)
{
    std::set<UINT32> setBuffID;

    setBuffID = _vecStateID[eBStateBuffType];
    return RemoveBattleBuff(setBuffID);
}		// -----  end of function RemoveStateValue  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBuffResist
//  Description:  获得临时抵抗的BuffID
// =====================================================================================
UINT32 CBattleFighter::GetBuffResist () const
{
    return _dwBuffResist;
}		// -----  end of function GetBuffResist  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetBuffResist
//  Description:  设置临时抵抗的BuffID
// =====================================================================================
void CBattleFighter::SetBuffResist (UINT32 dwBuffID)
{
    _dwBuffResist = dwBuffID;
}		// -----  end of function SetBuffResist  ----- //

bool CBattleFighter::GetReleaseBuffID(UINT32 dwBuffID)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
    {
        LOG_WRN << "No buff(" << dwBuffID << ") in _mapBuff when ReleaseBuff.";
        return false;
    }

    CBattleBuff& cBuff = it->second;
    string strInfo;
    BUFF_DEBUG << (strInfo << *this << cBuff);

    UINT8 byLast = cBuff.GetLast();
    if(byLast && byLast != INFINIT_CD)
        cBuff.SetLast(--byLast);
    if(byLast == 0)
        return true;
    else
        return false;
}

void CBattleFighter::GetReleaseBuffID(TVecUINT32& rvecBUffID)
{
    TVecUINT32& vecBuffs = GetOutCondBuffID(eMSRelease);
    for(auto itBuf = vecBuffs.begin(); itBuf != vecBuffs.end(); ++ itBuf)
    {
        UINT32 dwBuffID = *itBuf;
        if (_mapBuff.find(dwBuffID) == _mapBuff.end())
        {
            LOG_WRN << "No buff(" << dwBuffID << ") in _mapBuff when ReleaseBuff.";
            continue;
        }

        CBattleBuff& cBuff = _mapBuff[dwBuffID];
        string strInfo;
        BUFF_DEBUG << (strInfo << *this << cBuff);

        UINT8 byLast = cBuff.GetLast();
        if(byLast && byLast != INFINIT_CD)
            cBuff.SetLast(--byLast);
        if(byLast == 0)
            rvecBUffID.push_back(dwBuffID);
    }
}

void CBattleFighter::ReleaseCD()
{
    for (auto it = _mapBuff.begin(); it != _mapBuff.end(); ++it)
    {
        string strInfo;
#ifdef BATTLE_SKILL_BUFF_CD
        BUFF_DEBUG << "Release Buff CD: " << (strInfo << it->second) << ".";
#endif
        (it->second).ReleaseCD();
    }
}

void CBattleFighter::ReleaseCD(UINT32 dwBuffID)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
        return;

    string strInfo;
#ifdef BATTLE_SKILL_BUFF_CD
    BUFF_DEBUG << "Release Buff CD: " << (strInfo << it->second) << ".";
#endif
    (it->second).ReleaseCD();
}

void CBattleFighter::ReleaseBuff()
{
    EMachineState eMachineState = eMSRelease;
    TVecUINT32& vecBuffs = GetOutCondBuffID(eMachineState);
    TSetUINT32 setBuffID;
    for(auto itBuf = vecBuffs.begin(); itBuf != vecBuffs.end(); ++ itBuf)
    {
        UINT32 dwBuffID = *itBuf;
        if (_mapBuff.find(dwBuffID) == _mapBuff.end())
        {
            LOG_WRN << "No buff(" << dwBuffID << ") in _mapBuff when ReleaseBuff.";
            continue;
        }
        CBattleBuff& cBuff = _mapBuff[dwBuffID];

        string strInfo;
        BUFF_DEBUG << (strInfo << *this << cBuff);

        UINT8 byLast = cBuff.GetLast();
        if(byLast && byLast != INFINIT_CD)
            cBuff.SetLast(--byLast);
        if(byLast == 0)
            setBuffID.insert(dwBuffID);
    }
    RemoveBattleBuff(setBuffID);
    for (auto it = _mapBuff.begin(); it != _mapBuff.end(); ++it)
    {
        string strInfo;
        BUFF_DEBUG << "Release Buff: " << (strInfo << it->second) << ".";
        (it->second).ReleaseCD();
    }
}

bool CBattleFighter::HaveState(EBStateBuffType eBStateBuffType) const
{
    return _vecStateID[eBStateBuffType].empty()?false:true;
}

// 返回玩家身上对应状态的值
FLOAT CBattleFighter::GetStateValue(EBStateBuffType eBStateBuffType) const
{
    return _vecStateValue[eBStateBuffType];
}

bool CBattleFighter::GetStateBuffID(EBStateBuffType eBStateBuffType, TSetUINT32& rsetBuffID)
{
    rsetBuffID = _vecStateID[eBStateBuffType];
    return !rsetBuffID.empty();
}

// 根据新增加的buff更新玩家身上的状态
// 调用地点：   CheckAddBattleBuff
bool CBattleFighter::CheckTryAddStateValue (CBattleBuff& rBuff, UINT32& rBuffKeyToRemove)
{
    bool bRet = false;
    bool bAttr = false;
    EFighterAttr eAttrTypeSrc = EFIGHTATTR_MAX;
    FLOAT fValue1 = 0.0f;
    FLOAT fValue2 = 0.0f;
    FLOAT fValue3 = 0.0f;
    switch (rBuff.GetType())
    {
        case EShield:
            fValue1 = GetMaxHP();
            break;
        case EAttrSub:
        case EAttrAdd:
            bAttr = true;
            eAttrTypeSrc = EFIGHTATTR_MAX;
            break;
        case EAttr2AttrAdd:
            bAttr = true;
            eAttrTypeSrc = EFIGHTATTR_MAX;
            if (static_cast<UINT32>(rBuff.GetValue3()) < EFIGHTATTR_MAX)
            {
                eAttrTypeSrc = static_cast<EFighterAttr>(rBuff.GetDefaultValue3());
                VECATTR_SET(_vecAttrExtra, eAttrTypeSrc, fValue1);
            }
            break;
        default:
            break;
    }
    rBuff.ResetValue(fValue1, fValue2, fValue3);
    if (bAttr)
        bRet = CheckAddAttrBuff(rBuff, rBuffKeyToRemove, eAttrTypeSrc);
    else
        bRet = CheckAddStateValue(rBuff, rBuffKeyToRemove);
    return bRet;
}

// 根据新增加的buff更新玩家身上的状态
// 调用地点：   AddBattleBuff
bool CBattleFighter::TryAddStateValue (CBattleBuff& rBuff)
{
    bool bRet = false;
    bool bAttr = false;
    EFighterAttr eAttrTypeSrc = EFIGHTATTR_MAX;
    bool bEffect = false; // 效果增益参数
    bool bResist = false;  // 抵抗增益参数
    switch (rBuff.GetType())
    {
        case EAttrSub:
        case EAttrAdd:
            bAttr = true;
            break;
        case EAttr2AttrAdd:
            bAttr = true;
            eAttrTypeSrc = EFIGHTATTR_MAX;
            if (static_cast<UINT32>(rBuff.GetValue3()) < EFIGHTATTR_MAX)
                eAttrTypeSrc = static_cast<EFighterAttr>(rBuff.GetDefaultValue3());
            break;
        case EEffectAdd:
        case EEffectSub:
            bEffect = true;
        case EResistAdd:
        case EResistSub:
            bResist = true;
            break;
        default:
            break;
    }
    if (bAttr)
        bRet = AddAttrBuff(rBuff, eAttrTypeSrc);
    else
    {
        bRet = AddStateValue(rBuff);
        if (bRet)
        {
            if (bEffect)
                AddStateFactor(rBuff);
            if (bResist)
                AddResistFactor(rBuff);
        }
    }
    return bRet;
}

// 根据需要移除的buff更新玩家身上的状态
// 调用地点：   RemoveBattleBuff
//              ReduceBattleBuff
UINT32 CBattleFighter::TrySubStateValue (CBattleBuff& rBuff, bool bReduce)
{
    UINT32 dwRet = 0;
    bool bEffect = false;
    switch (rBuff.GetType())
    {
        case EEffectAdd:
        case EEffectSub:
            bEffect = true;
        case EShield: //护盾
        case EAttackAddP: // 攻击提升
        case EAttackSubP: // 攻击减少
        case EDefendAddP: // 防御提升
        case EDefendSubP: // 防御减少
        case EAssist:
            dwRet = SubStateValue(rBuff, bReduce);
            if (bEffect)
                SubStateFactor(rBuff, dwRet?true:false);
            break;
        case EResistAdd:
        case EResistSub:
            dwRet = SubStateValue(rBuff, bReduce);
            SubResistFactor(rBuff, dwRet?true:false);
            break;
        case EAttrAdd:
        case EAttrSub:
        case EAttr2AttrAdd:
            dwRet = SubAttrBuff(rBuff, bReduce);
            break;
        default:
            dwRet = ClearState(rBuff.GetGroupBuffType())?1:0;
            break;
    }
    return dwRet;
}

// 增加触发参数
bool CBattleFighter::AddBuffCondCount(UINT32 dwBuffID, UINT32 dwBuffIDEX, CBattleFighter* pBF)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
        return false;
    if (!(it->second).IsTurnEnable())
        return false;
    if ((it->second).GetCondRate())
    {
#ifdef _DEBUG
        if (!IsRate100())
        {
            UINT16 wRand = CRandom::RandInt(0, 9999);
            if (wRand > (it->second).GetCondRate())
                return false;
        }
#else
        UINT16 wRand = CRandom::RandInt(0, 9999);
        if (wRand > (it->second).GetCondRate())
            return false;
#endif
    }
    bool bRet = CheckCondValue((it->second).GetEffectCondValue(), (it->second).GetEffectCond(), false, dwBuffID, dwBuffIDEX, pBF);
#ifdef BATTLE_SKILL_BUFF_COND
    CBattleBuff cBuff;
    GetBuff(dwBuffID, cBuff);
    CBattleBuff cBuff2;
    GetBuff(dwBuffIDEX, cBuff2);
    string strInfo;
    strInfo << *this << cBuff << cBuff2;
    if (pBF)
        strInfo << *pBF;
    BATTLE_DBG << "CheckCondValue" << ": " << strInfo << ". " << (bRet?"true":"false");
#endif
    if (!bRet)
        return bRet;
    bRet = (it->second).AddCondCount();
    if (bRet)
    {
        bRet = (it->second).GetCD() <= 0 ? true:false;
        if (bRet)
        {
            (it->second).ResetCondCount();
            (it->second).ResetCD();
            (it->second).AddTurnCD(1);
            UpdateCondValue(dwBuffID, false);
            string strInfo;
            BATTLE_DBG << "AddBuffCondCount" << (strInfo << it->second) << ".";
        }
    }
    return bRet;
}

// 增加消失参数
bool CBattleFighter::AddBuffOutCondCount(UINT32 dwBuffID, UINT32 dwBuffIDEX, CBattleFighter* pBF)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
        return false;
    if (!(it->second).IsTurnEnable())
        return false;
    bool bRet = CheckCondValue((it->second).GetOutEffectCondValue(), (it->second).GetOutEffectCond(), true, dwBuffID, dwBuffIDEX, pBF);
#ifdef BATTLE_SKILL_BUFF_COND
    CBattleBuff cBuff;
    GetBuff(dwBuffID, cBuff);
    CBattleBuff cBuff2;
    GetBuff(dwBuffIDEX, cBuff2);
    string strInfo;
    strInfo << *this << cBuff << cBuff2;
    if (pBF)
        strInfo << *pBF;
    BATTLE_DBG << "Out CheckCondValue" << ": " << strInfo << ". " << (bRet?"true":"false");
#endif
    if (!bRet)
        return bRet;
    bRet = (it->second).AddOutCondCount();
    if (bRet)
    {
        bRet = (it->second).GetCD() <= 0 ? true:false;
        if (bRet)
        {
            (it->second).ResetOutCondCount();
            (it->second).ResetCD();
            (it->second).AddTurnCD(1);
            UpdateCondValue(dwBuffID, true);
            string strInfo;
            BATTLE_DBG << "AddBuffOutCondCount" << (strInfo << it->second) << ".";
        }
    }
    return bRet;
}

bool CBattleFighter::CheckCondValue(const TVecUINT32& rvecCondValue, EMachineState eMachineState, bool bOut, UINT32 dwBuffID, UINT32 dwBuffIDEX, CBattleFighter* pBF)
{
    bool bRet = false;
    switch(eMachineState)
    {
        case eMSOnAuraAdd: // 增加灵气时触发
            if (!rvecCondValue.empty() &&
                (GetAura() >= rvecCondValue[0]))
                    bRet = true;
            break;
        case eMSOnAuraSub: // 减少灵气时触发
            if (!rvecCondValue.empty() &&
                (GetAura() <= rvecCondValue[0]))
                    bRet = true;
            break;
        case eMSAftHit:
        case eMSHit:
        case eMSOnAtkDmg:
        case eMSOnOtherBeDmged:
        case eMSOnOtherBounceDmg:
        case eMSOnSelfCrit:
            if (rvecCondValue.empty())
                bRet = true;
            else
            {
                for (auto it = rvecCondValue.begin(); it != rvecCondValue.end(); ++it)
                {
                    if ((*it) >= static_cast<UINT32>(EBFBuffTypeMax))
                        continue;
                    if (pBF && pBF->GetStateValue(static_cast<EBStateBuffType>(*it)) > 0.0001f)
                    {
                        bRet = true;
                        break;
                    }
                }
            }
            break;
        case eMSBeforeDead:
            if (rvecCondValue.empty())
                bRet = true;
            else
            {
                for (auto it = rvecCondValue.begin(); it != rvecCondValue.end(); ++it)
                {
                    if ((*it) >= static_cast<UINT32>(EBFBuffTypeMax))
                        continue;
                    if (GetStateValue(static_cast<EBStateBuffType>(*it)) > 0.0001f)
                    {
                        bRet = true;
                        break;
                    }
                }
            }
            break;
        case eMSOnSelfSideBuffGet:
        case eMSOnAllBuffGet:
        case eMSOnAllLostBuff:
        case eMSOnOtherSideBuffAct:
        case eMSOnBuffSet:
        case eMSOnBuffAct:
        case eMSOnLostBuff:
        case eMSOnClearBuff:
            for (auto it = rvecCondValue.begin(); it != rvecCondValue.end(); ++it)
            {
                if ((*it) >= static_cast<UINT32>(EBFBuffTypeMax))
                    continue;
                if (CBattleSkillMgr::Instance().GetGroupBuffType(dwBuffIDEX) == *it)
                {
                    bRet = true;
                    break;
                }
            }
            break;
        case eMSState:
            for (auto it = rvecCondValue.begin(); it != rvecCondValue.end(); ++it)
            {
                SSkillEffect* pEffect = CBattleSkillMgr::Instance().GetSkillEf(dwBuffIDEX);
                if (pEffect && pEffect->_eResistType == *it)
                {
                    bRet = true;
                    break;
                }
            }
            break;
        case eMSOnBuffGet:
            {
                auto it2 = _mapBuff.find(dwBuffIDEX);
                if (it2 == _mapBuff.end())
                    break;
                for (auto it = rvecCondValue.begin(); it != rvecCondValue.end(); ++it)
                {
                    if ((*it) >= static_cast<UINT32>(EBFBuffTypeMax))
                        continue;
                    if ((it2->second).GetGroupBuffType() == *it)
                    {
                        bRet = true;
                        break;
                    }
                }
            }
            break;
        case eMSOnHPLow:
            if (!rvecCondValue.empty())
            {
                auto it = _mapBuff.find(dwBuffID);
                if (it != _mapBuff.end())
                {
                    CBattleBuff& rBuff = it->second;
                    UINT32 dwParam = static_cast<UINT32>(rBuff.GetCondParam(bOut) + 0.5f);
                    if (GetHP() > 0 && GetLostHPP() >= rvecCondValue[0] * (dwParam + 1))
                        bRet = true;
#ifdef BATTLE_SKILL_BUFF_COND
                    BATTLE_DBG << "GetLostHPP() = " << GetLostHPP() << ".";
#endif
#ifdef BATTLE_SKILL_BUFF_COND
                    BATTLE_DBG << "bOut = " << (bOut?"true":"false") << ", dwParam = " << dwParam << ", fValue = " << rvecCondValue[0] << ".";
#endif
                }
            }
            break;
        case eMSOnHPHigh:
            if (!rvecCondValue.empty())
            {
                auto it = _mapBuff.find(dwBuffID);
                if (it != _mapBuff.end())
                {
                    CBattleBuff& rBuff = it->second;
                    UINT32 dwParam = static_cast<UINT32>(rBuff.GetCondParam(bOut) + 0.5f);
                    if (GetHP() > 0 && GetLostHPP() < rvecCondValue[0] * (dwParam + 1))
                        bRet = true;
#ifdef BATTLE_SKILL_BUFF_COND
                    BATTLE_DBG << "GetLostHPP() = " << GetLostHPP() << ".";
#endif
#ifdef BATTLE_SKILL_BUFF_COND
                    BATTLE_DBG << "bOut = " << (bOut?"true":"false") << ", dwParam = " << dwParam << ", fValue = " << rvecCondValue[0] << ".";
#endif
                }
            }
            break;
        case eMSOnReiatsuAdd:
            if (!rvecCondValue.empty() && GetAura() >= rvecCondValue[0])
                bRet = true;
            break;
        default:
            bRet = true;
    }
    return bRet;
}

void CBattleFighter::UpdateCondValue(UINT32 dwBuffID, bool bOut)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
        return;
    CBattleBuff& rBuff = it->second;
    EMachineState eMachineState = bOut?rBuff.GetOutEffectCond():rBuff.GetEffectCond();
    switch(eMachineState)
    {
        case eMSOnHPLow:
            {
                UINT32 dwParam = static_cast<UINT32>(rBuff.GetCondParam(bOut) + 0.5f);
                rBuff.SetCondParam(++dwParam, bOut);
#ifdef BATTLE_SKILL_BUFF_COND
                    BATTLE_DBG << "bOut = " << (bOut?"true":"false") << ", dwParam = " << dwParam << ", fValue = " << rBuff.GetCondParam(bOut) << ".";
#endif
            }
            break;
        case eMSOnHPHigh:
            {
                UINT32 dwParam = static_cast<UINT32>(rBuff.GetCondParam(bOut) + 0.5f);
                rBuff.SetCondParam(++dwParam, bOut);
#ifdef BATTLE_SKILL_BUFF_COND
                    BATTLE_DBG << "bOut = " << (bOut?"true":"false") << ", dwParam = " << dwParam << ", fValue = " << rBuff.GetCondParam(bOut) << ".";
#endif
            }
            break;
        default:
            break;
    }
}

bool CBattleFighter::IsHide() const
{
    if (GetStateValue(EBFBuffTypeHide) > 0.1f)
        return true;
    else
        return false;
}

bool CBattleFighter::IsControled() const
{
    for (auto it = _mapBuff.begin(); it != _mapBuff.end(); ++it)
    {
        string strInfo;
        BATTLE_DBG << "IsControled: " << (strInfo << it->second) << ".";
        if ((it->second).CanClearControl())
        {
            BATTLE_DBG << "True.";
            return true;
        }
    }
    return false;
}

bool CBattleFighter::IsPassiveSkillID(UINT32 dwSkillID) const
{
    return _setPassiveEffectID.find(dwSkillID) != _setPassiveEffectID.end();
}

void CBattleFighter::GetDebuffCanClear(TVecUINT32& rvecBuffID, EResistType eType) const
{
    for (auto it = _mapBuff.begin(); it != _mapBuff.end(); ++it)
    {
        if ((it->second).CanClear(eType))
            rvecBuffID.push_back(it->first);
    }
}

UINT8 CBattleFighter::GetSummonLast() const
{
    return _bySummonLast;
}

void CBattleFighter::SetSummonLast(UINT8 bySumonLast)
{
    _bySummonLast = bySumonLast;
}

// ===  FUNCTION  ======================================================================
//         Name:  CheckAddStateValue
//  Description:  增加玩家对应状态的值
//     调用地点： CheckTryAddStateValue
// =====================================================================================
bool CBattleFighter::CheckAddStateValue(CBattleBuff& rBuff, UINT32& rBuffKeyToRemove)
{
    bool bRet = false;
    EBStateBuffType eBStateBuffType = rBuff.GetGroupBuffType();
    EStateAddType eAddType = CBattleSkillMgr::Instance().GetStateBuffAddType(eBStateBuffType);
    rBuff.SetValue1((rBuff.GetValue1() * (1 + GetStateFactor(eBStateBuffType)))); // Buff修正参数
    switch (eAddType)
    {
        case eStateAddAdd:  // 值增加，不会覆盖同类型的
            {
                bool bNew = true;
                BUFF_DEBUG << "Check eStateAddAdd: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
                auto it = _vecStateID[eBStateBuffType].find(rBuff.GetID());
                if (it != _vecStateID[eBStateBuffType].end())
                {
                    CBattleBuff cBattleBuff;
                    if (GetBuff(*it, cBattleBuff)) // 存在相同的Buff
                    {
                        FLOAT fDefaultCount = cBattleBuff.GetDefaultValue3();
                        if (fDefaultCount > 0.1f && cBattleBuff.GetValue3() <= 0.1f) // 叠加次数已经满了
                            return false;

                        rBuffKeyToRemove = cBattleBuff.GetInstID();
#ifdef BATTLE_FIGHTER_DEBUG_ATTR
                        UINT8 byCount = static_cast<UINT8>(fDefaultCount - cBattleBuff.GetValue3());
#endif

                        if (fDefaultCount > 0.1f) 
                            cBattleBuff.SetValue3(cBattleBuff.GetValue3() - 1);
                        cBattleBuff.SetValue1( rBuff.GetValue1() + cBattleBuff.GetValue1());
                        cBattleBuff.SetLast(rBuff.GetLast());
                        UINT32 dwInstID = rBuff.GetInstID();
                        rBuff = cBattleBuff;
                        rBuff.SetInstID(dwInstID);
#ifdef BATTLE_FIGHTER_DEBUG_ATTR
                        BATTLE_DBG << "Check add value = " << rBuff.GetValue1() << ", count = " << (UINT32) byCount << ".";
#endif
                        bNew = false;
                    }
                }
                if (bNew)
                {
                    FLOAT fDefaultCount = rBuff.GetDefaultValue3();
                    if (fDefaultCount > 0.1f) // 有叠加次数
                        rBuff.SetValue3(rBuff.GetDefaultValue3() - 1);
                }
                bRet = true;
            }
            break;
        case eStateAddReplaceBig: // 大的替代小的
            if (_vecStateValue[eBStateBuffType] <= rBuff.GetValue1())
            {
                BUFF_DEBUG << "Check eStateAddReplaceBig: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
                auto it = _vecStateID[eBStateBuffType].begin();
                if (it != _vecStateID[eBStateBuffType].end())
                {
                    CBattleBuff cBattleBuff;
                    if (GetBuff(*it, cBattleBuff))
                        rBuffKeyToRemove = cBattleBuff.GetInstID();
                }
                bRet = true;
            }
            break;
        case eStateAddReplaceNew: // 新的代替旧的
            {
                BUFF_DEBUG << "Check eStateAddReplaceNew: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
                auto it = _vecStateID[eBStateBuffType].begin();
                if (it != _vecStateID[eBStateBuffType].end())
                {
                    CBattleBuff cBattleBuff;
                    if (GetBuff(*it, cBattleBuff))
                        rBuffKeyToRemove = cBattleBuff.GetInstID();
                }
                bRet = true;
            }
            break;
        default:    // 直接增加，不删其他东西
            auto it = _vecStateID[eBStateBuffType].find(rBuff.GetID());
            if (it != _vecStateID[eBStateBuffType].end())
            {
                CBattleBuff cBattleBuff;
                if (GetBuff(*it, cBattleBuff)) // 存在相同的Buff
                {
                    rBuffKeyToRemove = cBattleBuff.GetInstID();
                }
            }
            BUFF_DEBUG << "Check eStateAddInvalid: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
            bRet = true;
            break;
    }
    if (bRet)
    {
        BUFF_DEBUG << "Now "<< BFTValToStr(eBStateBuffType) << " value = "  << "(" << _vecStateValue[eBStateBuffType] << ").";
    }
    return bRet;
}		// -----  end of function CheckAddStateValue  ----- //

// 增加玩家对应状态的值
// 调用地点：   TryAddStateValue
bool CBattleFighter::AddStateValue(CBattleBuff& rBuff)
{
    bool bRet = false;
    EBStateBuffType eBStateBuffType = rBuff.GetGroupBuffType();
    EStateAddType eAddType = CBattleSkillMgr::Instance().GetStateBuffAddType(eBStateBuffType);
    switch (eAddType)
    {
        case eStateAddReplaceBig:
            BUFF_DEBUG << "eStateAddReplaceBig: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
            RemoveBattleBuff(rBuff.GetID());
            _vecStateValue[eBStateBuffType] = rBuff.GetValue1();
            _vecStateID[eBStateBuffType].clear();
            _vecStateID[eBStateBuffType].insert(rBuff.GetID());
            bRet = true;
            break;
        case eStateAddReplaceNew:
            {
                BUFF_DEBUG << "eStateAddReplaceNew: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
                TSetUINT32 setBuffID = _vecStateID[eBStateBuffType];
                for (auto rID : setBuffID)
                {
                    RemoveBattleBuff(rID);
                }
                RemoveBattleBuff(rBuff.GetID());
                _vecStateValue[eBStateBuffType] = rBuff.GetValue1();
                _vecStateID[eBStateBuffType].clear();
                _vecStateID[eBStateBuffType].insert(rBuff.GetID());
                bRet = true;
            }
            break;
        case eStateAddAdd:  // 值增加，不会覆盖同类型的
            BUFF_DEBUG << "eState Add: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
            RemoveBattleBuff(rBuff.GetID());
            _vecStateValue[eBStateBuffType] += rBuff.GetValue1();
            _vecStateID[eBStateBuffType].insert(rBuff.GetID());
            bRet = true;
            break;
        default:
            RemoveBattleBuff(rBuff.GetID());
            _vecStateID[eBStateBuffType].insert(rBuff.GetID());
            BUFF_DEBUG << "eStateAddInvalid: " << BFTValToStr(eBStateBuffType) << "(" << rBuff.GetValue1() << ").";
            bRet = true;
            break;
    }
    if (bRet)
    {
        BUFF_DEBUG << "Now "<< BFTValToStr(eBStateBuffType) << " value = "  << "(" << _vecStateValue[eBStateBuffType] << ").";
    }
    return bRet;
}

// ===  FUNCTION  ======================================================================
//         Name:  SubStateValue
//  Description:  减少玩家对应状态的值 返回0表示完全移除，非零表示只是减少层数
//     调用地点： MakeShieldDmg
// =====================================================================================
bool CBattleFighter::SubStateValue(EBStateBuffType eBStateBuffType, FLOAT fValue, TVecUINT32& rvecBuffKey)
{
    bool bRet = false;

    bRet = true;
    _vecStateValue[eBStateBuffType] -= fValue;
    EStateSubType eSubType = CBattleSkillMgr::Instance().GetStateBuffSubType(eBStateBuffType);
    switch (eSubType)
    {
        case eStateSubNoNagetive:
            if (_vecStateValue[eBStateBuffType] <= 0.001f)
            {
                _vecStateValue[eBStateBuffType] = 0.0f;
                for (auto rID : _vecStateID[eBStateBuffType])
                {
                    CBattleBuff& rBuff = GetBuffData(rID, bRet);
                    if (bRet)
                    {
                        RemoveBuffMap(rBuff);
                        rvecBuffKey.push_back(rBuff.GetInstID());
                    }
                }
                _vecStateID[eBStateBuffType].clear();
            }
            else
            {
                for (auto it = _vecStateID[eBStateBuffType].begin(); it != _vecStateID[eBStateBuffType].end(); )
                {
                    bool bRemove = false;
                    CBattleBuff& rBuff = GetBuffData(*it, bRet);
                    if (bRet)
                    {
                        FLOAT fValue1 = rBuff.GetValue1();
                        if (fValue1 >= fValue)
                        {
                            rBuff.SetValue1(fValue1 - fValue);
                            break;
                        }
                        else
                        {
                            fValue -= fValue1;
                            RemoveBuffMap(rBuff);
                            rvecBuffKey.push_back(rBuff.GetInstID());
                            bRemove = true;
                        }
                    }
                    if (bRemove)
                        _vecStateID[eBStateBuffType].erase(it++);
                    else
                        ++it;
                }
            }
            break;
        case eStateSubCanNagetive:
            if (_vecStateValue[eBStateBuffType] <= 0.001f && _vecStateValue[eBStateBuffType] >= -0.001f)
            {
                for (auto rID : _vecStateID[eBStateBuffType])
                {
                    CBattleBuff& rBuff = GetBuffData(rID, bRet);
                    if (bRet)
                    {
                        RemoveBuffMap(rBuff);
                        rvecBuffKey.push_back(rBuff.GetInstID());
                    }
                }
                _vecStateID[eBStateBuffType].clear();
            }
            else
            {
                for (auto it = _vecStateID[eBStateBuffType].begin(); it != _vecStateID[eBStateBuffType].end(); )
                {
                    bool bRemove = false;
                    CBattleBuff& rBuff = GetBuffData(*it, bRet);
                    if (bRet)
                    {
                        FLOAT fValue1 = rBuff.GetValue1();
                        if (fValue1 >= fValue)
                        {
                            rBuff.SetValue1(fValue1 - fValue);
                            break;
                        }
                        else if (fValue1 > 0)
                        {
                            fValue -= fValue1;
                            RemoveBuffMap(rBuff);
                            rvecBuffKey.push_back(rBuff.GetInstID());
                            bRemove = true;
                        }
                    }
                    if (bRemove)
                        _vecStateID[eBStateBuffType].erase(it++);
                    else
                        ++it;
                }
            }
            break;
        default:
            for (auto it = _vecStateID[eBStateBuffType].begin(); it != _vecStateID[eBStateBuffType].end(); )
            {
                bool bRemove = false;
                CBattleBuff& rBuff = GetBuffData(*it, bRet);
                if (bRet)
                {
                    FLOAT fValue1 = rBuff.GetValue1();
                    fValue -= fValue1;
                    RemoveBuffMap(rBuff);
                    rvecBuffKey.push_back(rBuff.GetInstID());
                    bRemove = true;
                }
                if (bRemove)
                    _vecStateID[eBStateBuffType].erase(it++);
                else
                    ++it;
            }
            break;
    }
    if (bRet)
    {
        BUFF_DEBUG << "eStateSub: " << BFTValToStr(eBStateBuffType) << "(" << _vecStateValue[eBStateBuffType] << ").";
    }
    return bRet;
}

// ===  FUNCTION  ======================================================================
//         Name:  SubStateValue
//  Description:  减少玩家对应状态的值 返回0表示完全移除，非零表示只是减少层数
//     调用地点： TrySubStateValue
// =====================================================================================
UINT32 CBattleFighter::SubStateValue(CBattleBuff& rBuff, bool bReduce)
{
    UINT32 dwRet = 0;

    EBStateBuffType eBStateBuffType = rBuff.GetGroupBuffType();

    if (bReduce)
    {
        _vecStateValue[eBStateBuffType] -= rBuff.GetDefaultResetValue1();
        if (rBuff.GetDefaultResetValue1() - rBuff.GetValue1() < 0.001 && 
                rBuff.GetDefaultResetValue1() - rBuff.GetValue1() > -0.001 )
            bReduce = false;
    }
    else
        _vecStateValue[eBStateBuffType] -= rBuff.GetValue1();
    EStateSubType eSubType = CBattleSkillMgr::Instance().GetStateBuffSubType(eBStateBuffType);
    switch (eSubType)
    {
        case eStateSubNoNagetive:
            if (_vecStateValue[eBStateBuffType] <= 0.001f)
            {
                _vecStateValue[eBStateBuffType] = 0.0f;
                _vecStateID[eBStateBuffType].clear();
            }
            else if (!bReduce)
            {
                _vecStateID[eBStateBuffType].erase(rBuff.GetID());
            }
            else
            {
                rBuff.SetValue1(rBuff.GetValue1()- rBuff.GetDefaultResetValue1());
                dwRet = rBuff.GetID();
            }
            break;
        case eStateSubCanNagetive:
            if (_vecStateValue[eBStateBuffType] <= 0.001f && _vecStateValue[eBStateBuffType] >= -0.001f)
                _vecStateID[eBStateBuffType];
            else if (!bReduce)
            {
                _vecStateID[eBStateBuffType].erase(rBuff.GetID());
            }
            else
            {
                rBuff.SetValue1(rBuff.GetValue1()- rBuff.GetDefaultResetValue1());
                dwRet = rBuff.GetID();
            }
            break;
        default:
            if (!bReduce)
                _vecStateID[eBStateBuffType].erase(rBuff.GetID());
            break;
    }
    if (!dwRet)
        BUFF_DEBUG << "eStateSub: " << BFTValToStr(eBStateBuffType) << "(" << _vecStateValue[eBStateBuffType] << ").";
    else
        BUFF_DEBUG << "reduce eStateSub: " << BFTValToStr(eBStateBuffType) << "(" << _vecStateValue[eBStateBuffType] << ").";
    return dwRet;
}		// -----  end of function SubStateValue  ----- //

UINT32 CBattleFighter::ClearState (EBStateBuffType eBStateBuffType)
{
    _vecStateValue[eBStateBuffType] = 0.0f;
    _vecStateID[eBStateBuffType].clear();
    return 0;
}

bool CBattleFighter::AddStateFactor(CBattleBuff& rBuff)
{
    if (static_cast<UINT32>(rBuff.GetDefaultValue2()) >= EBFBuffTypeMax)
        return false;
    EBStateBuffType eBStateBuffType = static_cast<EBStateBuffType>(rBuff.GetDefaultValue2());
    _vecStateFactor[eBStateBuffType] += rBuff.GetDefaultResetValue1();
    BUFF_DEBUG << "AddStateFactor: " << BFTValToStr(eBStateBuffType) << "(" << _vecStateFactor[eBStateBuffType] << ").";
    return true;
}

bool CBattleFighter::SubStateFactor( CBattleBuff& rBuff, bool bReduce)
{
    if (static_cast<UINT32>(rBuff.GetDefaultValue2()) >= EBFBuffTypeMax)
        return false;
    EBStateBuffType eBStateBuffType = static_cast<EBStateBuffType>(rBuff.GetDefaultValue2());
    if (bReduce)
        _vecStateFactor[eBStateBuffType] -= rBuff.GetDefaultResetValue1();
    else
        _vecStateFactor[eBStateBuffType] -= rBuff.GetDefaultResetValue1();
    BUFF_DEBUG << "SubStateFactor: " << BFTValToStr(eBStateBuffType) << "(" << _vecStateFactor[eBStateBuffType] << ").";
    return true;
}

bool CBattleFighter::AddResistFactor(CBattleBuff& rBuff)
{
    if (static_cast<UINT32>(rBuff.GetDefaultValue2()) >= eResistTypeMax)
        return false;
    EResistType eType = static_cast<EResistType>(rBuff.GetDefaultValue2());
    _vecResistFactor[eType] += rBuff.GetDefaultResetValue1();
    BUFF_DEBUG << "AddResistFactor: " << static_cast<UINT32>(eType) << "(" << _vecResistFactor[eType] << ").";
    return true;
}

bool CBattleFighter::SubResistFactor( CBattleBuff& rBuff, bool bReduce)
{
    if (static_cast<UINT32>(rBuff.GetDefaultValue2()) >= eResistTypeMax)
        return false;
    EResistType eType = static_cast<EResistType>(rBuff.GetDefaultValue2());
    if (bReduce)
        _vecResistFactor[eType] -= rBuff.GetDefaultResetValue1();
    else
        _vecResistFactor[eType] -= rBuff.GetDefaultResetValue1();
    BUFF_DEBUG << "SubResistFactor: " << static_cast<UINT32>(eType) << "(" << _vecResistFactor[eType] << ").";
    return true;
}

// ===  FUNCTION  ======================================================================
//         Name:  CheckAddAttrBuff
//  Description:  增加属性相关增减益buff
//     调用地点： TryAddStateValue (bCheck == true)
// =====================================================================================
bool CBattleFighter::CheckAddAttrBuff(CBattleBuff& rBuff, UINT32& rBuffKeyToRemove, EFighterAttr eAttrTypeSrc)
{
    if (static_cast<UINT32>(rBuff.GetValue2()) >= EFIGHTATTR_MAX)
        return false;

    bool bAttr2Attr = false; // 是否其他属性增益该属性
    EFighterAttr eAttrTypeDst = static_cast<EFighterAttr>(rBuff.GetValue2());
    if (eAttrTypeSrc == EFIGHTATTR_MAX)
    {
        bAttr2Attr = false;
        eAttrTypeSrc = eAttrTypeDst;
    }
    else
        bAttr2Attr = true;

    // 获取需要覆盖的BuffID
    CBattleBuff cBattleBuff;
    if (GetBuff(rBuff.GetID(), cBattleBuff))
    {
        rBuffKeyToRemove = cBattleBuff.GetInstID();
        cBattleBuff.SetValue1(cBattleBuff.GetValue1() + rBuff.GetValue1());
        UINT32 dwInstID = rBuff.GetInstID();
        rBuff = cBattleBuff;
        rBuff.SetInstID(dwInstID);
    }

    if (!bAttr2Attr) // 可能存在叠加层数
    {
        FLOAT fDefaultCount = rBuff.GetDefaultValue3();
        if (fDefaultCount > 0.1f) // 有叠加层数
        {
            if (rBuff.GetValue3() <= 0.1f) // 叠加次数已经满了
            {
                // 刷新叠加时间
                rBuff.SetValue3(0.0f); 
                rBuff.SetLast(rBuff.GetDefaultLast());
            }
            else
                rBuff.SetValue3(rBuff.GetValue3() - 1);  // 增加叠加次数
        }
    }

#ifdef BATTLE_FIGHTER_DEBUG_ATTR
    FLOAT fDefaultCount = 0;
    if (!bAttr2Attr) // 可能存在叠加层数
        fDefaultCount = rBuff.GetDefaultValue3();
    UINT8 byCount = static_cast<UINT8>(fDefaultCount - rBuff.GetValue3());
    BATTLE_DBG << "(Check) Type: " << AttrTypeToStr(eAttrTypeDst) << ", "
        "add value = " << rBuff.GetValue1() << ", "
        "count = " << (UINT32) byCount << "now value = " << VECATTR_GET(_vecAttrExtra, eAttrTypeDst) << ".";
#endif
    return true;
}		// -----  end of function CheckAddAttrBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddAttrBuff
//  Description:  增加属性相关增减益buff
//     调用地点： TryAddStateValue (bCheck == false)
// =====================================================================================
bool CBattleFighter::AddAttrBuff(CBattleBuff& rBuff, EFighterAttr eAttrTypeSrc)
{
    if (static_cast<UINT32>(rBuff.GetValue2()) >= EFIGHTATTR_MAX)
        return false;

#ifdef BATTLE_FIGHTER_DEBUG_ATTR
    bool bAttr2Attr = true; // 是否其他属性增益该属性
#endif
    EFighterAttr eAttrTypeDst = static_cast<EFighterAttr>(rBuff.GetValue2());
    if (eAttrTypeSrc == EFIGHTATTR_MAX)
    {
#ifdef BATTLE_FIGHTER_DEBUG_ATTR
        bAttr2Attr = false;
#endif
        eAttrTypeSrc = eAttrTypeDst;
    }

    CBattleBuff cBattleBuff;
    if (GetBuff(rBuff.GetID(), cBattleBuff))
        RemoveBattleBuff(rBuff.GetID());

    VECATTR_ADD(_vecAttrExtra, eAttrTypeDst, rBuff.GetValue1());

#ifdef BATTLE_FIGHTER_DEBUG_ATTR
    FLOAT fDefaultCount = 0;
    if (!bAttr2Attr)
        fDefaultCount = rBuff.GetDefaultValue3();
    UINT8 byCount = static_cast<UINT8>(fDefaultCount - rBuff.GetValue3());
    BATTLE_DBG << "Type: " << AttrTypeToStr(eAttrTypeDst) << ", "
        "add value = " << rBuff.GetValue1() << ", "
        "count = " << (UINT32) byCount << ", now value = " << VECATTR_GET(_vecAttrExtra, eAttrTypeDst) << ".";
#endif
    return true;
}		// -----  end of function AddAttrBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SubAttrBuff
//  Description:  去除属性相关增减益buff
//     调用地点： TrySubStateValue
// =====================================================================================
UINT32 CBattleFighter::SubAttrBuff(CBattleBuff& rBuff, bool bReduce)
{
    UINT32 dwRet = 0;

    if (rBuff.GetValue2() > EFIGHTATTR_MAX)     // 属性索引值不对
        return dwRet;

    EFighterAttr eAttrType = static_cast<EFighterAttr>(rBuff.GetValue2());

    UINT8 byCount = 1; // 叠加层数

    if (rBuff.GetType() != EAttr2AttrAdd)
    {
        bool bLayer = false;    // 该Buff是否有叠加层数

        if (rBuff.GetDefaultValue3() > 0.1f) // 有叠加层数
        {
            byCount = static_cast<UINT8>(rBuff.GetDefaultValue3() - rBuff.GetValue3());
            bLayer = true;
        }

        if (bReduce) // 只是清除一层
        {
            if (bLayer)     // 有叠加层数
            {
                rBuff.SetValue3(rBuff.GetValue3() - 1);
                if (--byCount < 1)
                    bReduce = false;
            }
            else if (rBuff.GetDefaultResetValue1() - rBuff.GetValue1() < 0.0001
                        && rBuff.GetDefaultResetValue1() - rBuff.GetValue1() > -0.0001)
                bReduce = false;    //  直接清除该Buff
        }

        if (bReduce) // 真的只是清除一层Buff
        {
            VECATTR_ADD(_vecAttrExtra, eAttrType, -rBuff.GetDefaultResetValue1());
            rBuff.SetValue1(rBuff.GetValue1() - rBuff.GetDefaultResetValue1());
        }
        else    // 全部清除
        {
            VECATTR_ADD(_vecAttrExtra, eAttrType, -rBuff.GetValue1());
            bReduce = false;
        }
    }
    else // 属性增益属性直接移除
    {
        VECATTR_ADD(_vecAttrExtra, eAttrType, -rBuff.GetValue1());
        bReduce = false;
    }

#ifdef BATTLE_FIGHTER_DEBUG_ATTR
    BATTLE_DBG << "Type: " << AttrTypeToStr(eAttrType) << ", "
        "sub value = " << rBuff.GetValue1() << ", "
        "count = " << (UINT32) byCount << ", "
        "now value = " << VECATTR_GET(_vecAttrExtra, eAttrType) << ".";
#endif
    if (bReduce)
        dwRet = rBuff.GetID();
    else
        dwRet = 0;
    return dwRet;
}		// -----  end of function SubAttrBuff  ----- //

void CBattleFighter::GetAllBuffID(TSetUINT32& rsetBuffID)
{
    for (auto it = _mapBuff.begin(); it != _mapBuff.end(); ++it)
    {
        rsetBuffID.insert(it->first);
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  HasStateBuff
//  Description:  是否拥有该状态的相关Buff
// =====================================================================================
bool CBattleFighter::HasStateBuff (EMachineState eMachineState) const
{
    return !_vecBuffCond[eMachineState].empty() || !_vecBuffOutCond[eMachineState].empty();
}		// -----  end of function HasStateBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCondBuffID
//  Description:  获取某个触发状态的所有Buff
//     调用地点:  入场Buff,不同状态Process的状态检测触发，回合结束BuffRelease
// =====================================================================================
TVecUINT32& CBattleFighter::GetCondBuffID(EMachineState eMachineState)
{
    return _vecBuffCond[eMachineState];
}		// -----  end of function GetCondBuffID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetOutCondBuffID
//  Description:  获取某个消失状态的所有Buff
//     调用地点:  不同状态Process的状态检测触发
// =====================================================================================
TVecUINT32& CBattleFighter::GetOutCondBuffID(EMachineState eMachineState)
{
    return _vecBuffOutCond[eMachineState];
}		// -----  end of function GetOutCondBuffID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBuffWithState
//  Description:  在当前的状态下获取被动技能
// =====================================================================================
bool CBattleFighter::GetBuffWithState(UINT32 dwBuffID, CBattleBuff& rBuffOut)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
        return false;

    //  封印状态无法触发的自身的被动技能
    if (HaveState(EBFBuffTypeSealed) && 
            (_setPassiveEffectID.find(dwBuffID) != _setPassiveEffectID.end()))
            return false;

    rBuffOut = it->second;
    return true;
}		// -----  end of function GetBuffWithState  ----- //

bool CBattleFighter::HaveBuff(UINT32 dwBuffID) const
{
    return (_mapBuff.find(dwBuffID) == _mapBuff.end())?false:true;
}

bool CBattleFighter::GetBuff(UINT32 dwBuffID, CBattleBuff& rBuffOut)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
        return false;
    else
    {
        CBattleBuff& rBuff = it->second;
        rBuffOut = rBuff;
        return true;
    }
}

CBattleBuff& CBattleFighter::GetBuffData(UINT32 dwBuffID, bool& bRet)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it == _mapBuff.end())
    {
        bRet = false;
        return s_cTmpBuff;
    }
    else
    {
        bRet = true;
        return it->second;
    }
}

bool CBattleFighter::GetBuffData(UINT32 dwBuffID, CBattleBuff& rBuffOut)
{
    auto it = _mapBuff.find(dwBuffID);
    if (it != _mapBuff.end())
    {
        rBuffOut = it->second;
        return true;
    }
    return false;
}

FLOAT CBattleFighter::GetStateFactor(EBStateBuffType eBStateBuffType) const
{
    return _vecStateFactor[eBStateBuffType];
}

FLOAT CBattleFighter::GetResistFactor(EResistType eType) const
{
    return _vecResistFactor[eType];
}

} // namespace NBattle

