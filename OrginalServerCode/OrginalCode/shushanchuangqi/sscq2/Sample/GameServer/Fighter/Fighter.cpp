
#include "stdafx.h"
#include "Protocols.h"
#include "Game2CenterTeamC.h"
#include "Fighter.h"
#include "FighterMgr.h"
#include "Player.h"
#include "ItemMgr.h"
#include "ExpMgr.h"
#include "Battle.h"
#include "PropInfoS.h"
#include "FighterManager.h"
#include "Creature.h"
#include "GetCondMgr.h"
#include "HeroFighter.h"
#include "DungeonMgr.h"
#include "SysMsgDefine.h"
#include "Loot.h"
#include "GameServerLog.h"
#include "Parameter.h"

using namespace NPropInfo;

CFighter::CFighter(UINT16 wFighterID, EFighterType eFighterType, CCreature* pCreature /* = NULL */, UINT64 qwInstID /* = 0 */) : 
    _qwInstID(qwInstID), _eType(eFighterType),
    _wFighterID(wFighterID), _bRecruited(false), _byStar(1), _iSlot(INVALID_POS), _iPos(INVALID_POS), 
    _byLevel(1), _qwExp(0LL), 
    _wFormationID(-1), _dwHP(0),
    _byDujieLevel(1), _dwDujieExp(0), _byColor(0), _dwSpiritPower(0),  _bDirty(true),
    _pCreature(pCreature)
{
    _vecFighterAttr.resize(EFIGHTATTR_MAX, 0.f);
    _vecFinalAttr.resize(EFIGHTATTR_MAX, 0.f);
    _vecFinalAttr2.resize(EFIGHTATTR_MAX, 0.f);
    _pFighterCfg = CFighterMgr::GetFighterPropCfg(wFighterID);
    _pFighterLvAttrCfg = CFighterMgr::GetFighterLvAttrCfg(wFighterID);
    memset(_byCuiTiLvl, 0, sizeof(_byCuiTiLvl));

    //XXX 策划取消1级
    //_byLianPi = _byTongJin = _byQiangJi = _byDuanGu = _byHuoLuo = _byXiSui = 1;
    InitFighterInfo();
    InitFighterAttr();
}

CFighter::~CFighter()
{
    CGameBuffMgr::Instance().RemoveBuffManager(_qwInstID);
}

SFighterPropCFG* CFighter::GetFighterPropConfig() const
{
    if (!_pFighterCfg || GetVersion() != CFighterMgr::GetVersion())
        _pFighterCfg = CFighterMgr::GetFighterPropCfg(GetFighterID());
    return _pFighterCfg;
}

UINT8 CFighter::GetFighterInclination() const
{
    SFighterPropCFG* pFighterCfg = GetFighterPropConfig();
    if (!pFighterCfg)
        return 0;
    return pFighterCfg->_Inclination;
}

UINT8 CFighter::GetDujieTemplateID() const
{
    SFighterPropCFG* pFighterCfg = GetFighterPropConfig();
    if (!pFighterCfg)
        return 1;
    return pFighterCfg->_DujieTemplateId;
}

UINT8 CFighter::GetColor() const
{
    if (!_byColor)
    {
        SDujieTemplateCFGEx* pDujieCFG = CFighterMgr::GetDujieCFG(GetDujieTemplateID(), GetDujieLevel());
        if (pDujieCFG)
            _byColor = pDujieCFG->_Color;
    }
   // LOG_WRN<<"_byColor = " << _byColor;
    return _byColor;
}

void CFighter::SetColor(UINT8 byColor, bool bInit /* = false */)
{
    if (_byColor != byColor)
    {
        UINT8 byOldColor = _byColor;
        _byColor = byColor;
        if (!bInit && IsMainFighter() && GetUser())
        {
            string strPkg = g_Game2CenterCommC.BuildPkg_UserSyncPropNtf(GetUser()->GetUserID(), eSyncPropQuality, NumberToString(byColor));
            GetUser()->SendCenterSvrPkg(strPkg);
            CPlayerPtr pPlayer = GetUser()->GetPlayer();
            if (pPlayer && !bInit)
                pPlayer->OnColorChanged(byOldColor);
        }
    }
}

void CFighter::ResetColor()
{
    SDujieTemplateCFGEx* pDujieCFG = CFighterMgr::GetDujieCFG(GetDujieTemplateID(),1);
    if (!pDujieCFG)
        return;
    if (IsMainFighter() && GetUser())
    {
        string strPkg = g_Game2CenterCommC.BuildPkg_UserSyncPropNtf(GetUser()->GetUserID(), eSyncPropQuality, NumberToString(pDujieCFG->_Color));
        GetUser()->SendCenterSvrPkg(strPkg);
        CPlayerPtr pPlayer = GetUser()->GetPlayer();
        if (pPlayer)
            pPlayer->OnColorChanged(_byColor);
        _byColor = pDujieCFG->_Color;
    }
}

SFighterLvAttrCFG* CFighter::GetFighterLvAttrConfig() const
{
    if (!_pFighterLvAttrCfg || GetVersion() != CFighterMgr::GetVersion())
        _pFighterLvAttrCfg = CFighterMgr::GetFighterLvAttrCfg(GetFighterID());
    return _pFighterLvAttrCfg;
}

UINT64 CFighter::GetRoleID() const
{
    if (!GetFighterManager())
        return 0;
    CUserPtr pUser = GetFighterManager()->GetUserPtr();
    if (!pUser)
        return 0;
    return pUser->GetRoleID();
}

ESexType CFighter::GetSex() const
{
    switch (GetFighterID())
    {
        case 1:
        case 3:
        case 5:
        case 7:
            return ESEX_MALE;
        case 2:
        case 4:
        case 6:
        case 8:
            return ESEX_FEMALE;
    }
    return ESEX_FEMALE; // 客户端要求的，普通散仙和NPC性别都是女的
}

void CFighter::SetUser(const CUserPtr& pUser) 
{ 
    _pUser = pUser;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (pPlayer)
       _pFighterManager  = pPlayer->GetFighterManager();
}

void CFighter::InitFighterInfo()
{
    SFighterPropCFG* pFighterCfg = GetFighterPropConfig();
    if (!pFighterCfg)
        return;
    _byLevel = pFighterCfg->_Level;
}

void CFighter::InitFighterAttr()
{
    VECATTR_RESET(_vecFighterAttr);
    SFighterPropCFG* pFighterPropCFG = GetFighterPropConfig();
    PHYATK_SET(_vecFighterAttr, pFighterPropCFG);
    MGCATK_SET(_vecFighterAttr, pFighterPropCFG);
    PHYDEF_SET(_vecFighterAttr, pFighterPropCFG);
    MGCDEF_SET(_vecFighterAttr, pFighterPropCFG);
    PHYRDC_SET(_vecFighterAttr, pFighterPropCFG);
    MGCRDC_SET(_vecFighterAttr, pFighterPropCFG);
    MAXHP_SET(_vecFighterAttr, pFighterPropCFG);
    SPEED_SET(_vecFighterAttr, pFighterPropCFG);
    HIT_SET(_vecFighterAttr, pFighterPropCFG);
    HITRATE_SET(_vecFighterAttr, pFighterPropCFG);
    DODGE_SET(_vecFighterAttr, pFighterPropCFG);
    DODGERATE_SET(_vecFighterAttr, pFighterPropCFG);
    CRITICAL_SET(_vecFighterAttr, pFighterPropCFG);
    CRTRATE_SET(_vecFighterAttr, pFighterPropCFG);
    ANTICRITCAL_SET(_vecFighterAttr, pFighterPropCFG);
    ANTICRTRATE_SET(_vecFighterAttr, pFighterPropCFG);
    BLOCK_SET(_vecFighterAttr, pFighterPropCFG);
    BLOCKRATE_SET(_vecFighterAttr, pFighterPropCFG);
    PIERCE_SET(_vecFighterAttr, pFighterPropCFG);
    PIERCERATE_SET(_vecFighterAttr, pFighterPropCFG);
    COUNTER_SET(_vecFighterAttr, pFighterPropCFG);
    COUNTERRATE_SET(_vecFighterAttr, pFighterPropCFG);
    RESIST_SET(_vecFighterAttr, pFighterPropCFG);
    RESISTRATE_SET(_vecFighterAttr, pFighterPropCFG);
    INITAURA_SET(_vecFighterAttr, pFighterPropCFG);
    MAXAURA_SET(_vecFighterAttr, pFighterPropCFG);
    CRIEXTRAADD_SET(_vecFighterAttr, pFighterPropCFG);
    CRIEXTRARDC_SET(_vecFighterAttr, pFighterPropCFG);
    METALATK_SET(_vecFighterAttr, pFighterPropCFG);
    WOODATK_SET(_vecFighterAttr, pFighterPropCFG);
    WATERATK_SET(_vecFighterAttr, pFighterPropCFG);
    FIREATK_SET(_vecFighterAttr, pFighterPropCFG);
    EARTHATK_SET(_vecFighterAttr, pFighterPropCFG);
    METALDEF_SET(_vecFighterAttr, pFighterPropCFG);
    WOODDEF_SET(_vecFighterAttr, pFighterPropCFG);
    WATERDEF_SET(_vecFighterAttr, pFighterPropCFG);
    FIREDEF_SET(_vecFighterAttr, pFighterPropCFG);
    EARTHDEF_SET(_vecFighterAttr, pFighterPropCFG);
    PHYATK_PER_SET(_vecFighterAttr, pFighterPropCFG);
    MGCATK_PER_SET(_vecFighterAttr, pFighterPropCFG);
    PHYDEF_PER_SET(_vecFighterAttr, pFighterPropCFG);
    MGCDEF_PER_SET(_vecFighterAttr, pFighterPropCFG);
    MAXHP_PER_SET(_vecFighterAttr, pFighterPropCFG);
    SPEED_PER_SET(_vecFighterAttr, pFighterPropCFG);
    HIT_PER_SET(_vecFighterAttr, pFighterPropCFG);
    DODGE_PER_SET(_vecFighterAttr, pFighterPropCFG);
    CRITICAL_PER_SET(_vecFighterAttr, pFighterPropCFG);
    ANTICRITCAL_PER_SET(_vecFighterAttr, pFighterPropCFG);
    BLOCK_PER_SET(_vecFighterAttr, pFighterPropCFG);
    PIERCE_PER_SET(_vecFighterAttr, pFighterPropCFG);
    COUNTER_PER_SET(_vecFighterAttr, pFighterPropCFG);
    RESIST_PER_SET(_vecFighterAttr, pFighterPropCFG);
    ANTIEFFECT_SET(_vecFighterAttr, pFighterPropCFG);
    InitFighterLvAttr();

    //仅对monster有效
    if(_pCreature)
        _vecFighterAttr += _pCreature->GetBufferAttrVec(); 
    SetDirty(true);
}

void CFighter::InitFighterLvAttr()
{
    if (IsMonsterFighter())
        return;
    if (GetLevel() <= 1)
        return;
    SFighterLvAttrCFG* pFighterLvAttrCFG = GetFighterLvAttrConfig();
    if (!pFighterLvAttrCFG)
        return;
    SFighterStarCFG* pFighterStarCfg = CFighterMgr::GetFighterStarCfg(GetFighterInclination(), GetStar());
    if (!pFighterStarCfg)
    {
        LOG_CRI << "HAVE NO FIGHTER STAR: " << GetStar() << ",FIGHTER ID: " << GetID();
        return;
    }

    UINT8 byLvl = GetLevel() - 1;
#define STAR_ATTR(T, L, I)                                                                                                          \
    do {                                                                                                                            \
        float fRatio = 1.0f;                                                                                                        \
        if (pFighterLvAttrCFG->_StarType > 0)                                                                                       \
        {                                                                                                                           \
            SFighterStarGrowthCFG* pFighterStarGrowthCfg = CFighterMgr::GetFighterStarGrowthCfg(pFighterStarCfg->_EFIGHTATTR_##I);  \
            if (pFighterStarGrowthCfg)                                                                                              \
                fRatio *= pFighterStarGrowthCfg->_Ratio;                                                                            \
            else                                                                                                                    \
                fRatio *= 0.0f;                                                                                                     \
        }                                                                                                                           \
        I##_ADDMUL(T, L, byLvl*fRatio);                                                                                             \
    } while(0)

    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PHYATK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MGCATK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PHYDEF);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MGCDEF);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PHYRDC);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MGCRDC);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MAXHP);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, SPEED);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, HIT);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, HITRATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, DODGE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, DODGERATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, CRITICAL);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, CRTRATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, ANTICRITCAL);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, ANTICRTRATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, BLOCK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, BLOCKRATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PIERCE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PIERCERATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, COUNTER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, COUNTERRATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, RESIST);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, RESISTRATE);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, INITAURA);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MAXAURA);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, CRIEXTRAADD);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, CRIEXTRARDC);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, METALATK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, WOODATK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, WATERATK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, FIREATK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, EARTHATK);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, METALDEF);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, WOODDEF);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, WATERDEF);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, FIREDEF);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, EARTHDEF);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PHYATK_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MGCATK_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PHYDEF_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MGCDEF_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, MAXHP_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, SPEED_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, HIT_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, DODGE_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, CRITICAL_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, ANTICRITCAL_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, BLOCK_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, PIERCE_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, COUNTER_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, RESIST_PER);
    STAR_ATTR(_vecFighterAttr, pFighterLvAttrCFG, ANTIEFFECT);
}

float CFighter::GetAttr(EFighterAttr eFighterAttr) const
{
    if (IsDirty())
        RebuildAttr();
    if (eFighterAttr > _vecFinalAttr.size())
    {
        LOG_CRI << "eFighterAttr = " << static_cast<UINT32>(eFighterAttr) << "_vecFinalAttr.size() = " << _vecFinalAttr.size() << ".";
        return 0.f;
    }
    return _vecFinalAttr[eFighterAttr];
}

float CFighter::GetAttr2(EFighterAttr eFighterAttr) const
{
    if (IsDirty())
        RebuildAttr();
    if (eFighterAttr > _vecFinalAttr2.size())
    {
        LOG_CRI << "eFighterAttr = " << static_cast<UINT32>(eFighterAttr) << "_vecFinalAttr2.size() = " << _vecFinalAttr2.size() << ".";
        return 0.f;
    }
    return _vecFinalAttr2[eFighterAttr];
}

bool CFighter::SetAttr(EFighterAttr eFighterAttr, float fValue)
{
    if (IsDirty())
        RebuildAttr();
    if (eFighterAttr >= EFIGHTATTR_MAX)
        return false;
    _vecFinalAttr[eFighterAttr] = fValue;
    return true;
}

bool CFighter::SetAttr2(EFighterAttr eFighterAttr, float fValue)
{
    if (IsDirty())
        RebuildAttr();
    if (eFighterAttr >= EFIGHTATTR_MAX)
        return false;
    _vecFinalAttr2[eFighterAttr] = fValue;
    return true;
}

TVecFtAttrMod CFighter::GetFtAttrMod()
{
    TVecFtAttrMod attrs;
    if (IsDirty())
        RebuildAttr();

    size_t size = _vecFinalAttr.size();
    attrs.resize(size);
    for (size_t i = 0; i < size; ++i)
    {
        if (_vecFinalAttr[i] > 0.0001f)
        {
            attrs[i]._eAttr = (EFighterAttr)i;
            attrs[i]._fValue = _vecFinalAttr[i];
        }
    }
    return attrs;
}

void CFighter::ApplyFtAttrMod(const TVecFtAttrMod& attrs)
{
    size_t size = attrs.size();
    for (size_t i = 0; i < size; ++i)
    {
        if ((UINT32)attrs[i]._eAttr >= _vecFinalAttr.size())
        {
            LOG_WRN << "ApplyFtAttrMod: idx=" << (INT32)attrs[i]._eAttr << " value=" << attrs[i]._fValue;
            continue;
        }
        _vecFinalAttr[attrs[i]._eAttr] += attrs[i]._fValue;
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  GetAllSkillsID
//  Description:  获取所有的技能ID
// =====================================================================================
void CFighter::GetAllSkillsID(TVecUINT32& rvecSkillsID) const
{
    UINT32 dwNormalAttack = 0;
    GetAllSkills(rvecSkillsID, dwNormalAttack);
}		// -----  end of function GetAllSkillsID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AppendAttr
//  Description:  获取所有的属性
// =====================================================================================
void CFighter::AppendBPAttr (TVecFloat& rvecAttr) const
{
    rvecAttr = _vecBPAttr;
}		// -----  end of function AppendAttr  ----- //

UINT32 CFighter::GetHP() const
{
    if (IsDirty())
        RebuildAttr();
    return _dwHP;
}

void CFighter::SetHP(UINT32 dwHP)
{
    _dwHP = dwHP;
    UINT32 maxHP = static_cast<UINT32>(GetHPMax2());
    if (_dwHP > maxHP)
        _dwHP = maxHP;
}

void CFighter::AddHP(UINT32 dwHP)
{
    _dwHP += dwHP;
    UINT32 maxHP = static_cast<UINT32>(GetHPMax2());
    if (_dwHP > maxHP)
        _dwHP = maxHP;
}

void CFighter::SubHP(UINT32 dwHP)
{
    if (_dwHP >= dwHP)
        _dwHP -= dwHP;
    else
        _dwHP = 0;
}

UINT32 CFighter::GetHPMax() const
{
    if (IsDirty())
        RebuildAttr();
    return static_cast<UINT32>(GetAttr(EFIGHTATTR_MAXHP));
}

UINT32 CFighter::GetHPMax2() const
{
    if (IsDirty())
        RebuildAttr();
    return static_cast<UINT32>(GetAttr2(EFIGHTATTR_MAXHP));
}

void CFighter::SetHPMax(UINT32 dwHPMax)
{
    SetAttr(EFIGHTATTR_MAXHP, static_cast<float>(dwHPMax));
}

void CFighter::SetHPMax2(UINT32 dwHPMax)
{
    SetAttr2(EFIGHTATTR_MAXHP, static_cast<float>(dwHPMax));
}

ECareerType CFighter::GetJob() const
{
    SFighterPropCFG* pFighterPropCFG = GetFighterPropConfig();
    if (!pFighterPropCFG)
        return ECAREER_MAX;
    return ECareerType(pFighterPropCFG->_Job);
}

const string CFighter::GetName() const
{
    SFighterPropCFG* pFighterPropCFG = GetFighterPropConfig();
    if (!pFighterPropCFG)
        return 0;
    return pFighterPropCFG->_Name;
}

UINT32 CFighter::GetNormalAttack() const
{
    SFighterPropCFG* pFighterPropCFG = GetFighterPropConfig();
    if (!pFighterPropCFG)
        return 0;
    return SkillMgr.GetSkillIDQualityLevel(pFighterPropCFG->_NormalAttack);
}

bool CFighter::IsMainFighter() const 
{ 
    return GetID() <= SParamConfig::dwMainFigherIDMax; 
}

UINT8 CFighter::GetLevel() const
{
    if (GetFighterManager() && GetFighterManager()->GetUserPtr())
    {
        return GetFighterManager()->GetUserPtr()->GetLevel();
    }
    return _byLevel;
}

void CFighter::SetLevel(UINT8 byLevel, bool bUpdate)
{
    if (byLevel == _byLevel)
        return;
    UINT64 qwExp = CExpMgr::GetLevelMin(byLevel);
    _qwExp = qwExp;
    _byLevel = byLevel;
    if (bUpdate)
        Update2DB();
}

bool CFighter::AddExp(UINT64 qwExp, bool bNotify)
{
    if(qwExp == 0 || GetLevel() >= CExpMgr::GetLevelMax())
        return false;

    if(qwExp > 0xFFFFFFFFFFFFFFFFull - _qwExp)
        _qwExp = 0xFFFFFFFFFFFFFFFFull;
    else
        _qwExp += qwExp;
    if (IsHeroFighter() && GetUser() && GetUser()->GetPlayer() && GetUser()->GetPlayer()->GetMainFighter())
    {
        UINT64 qwMainExp = GetUser()->GetPlayer()->GetMainFighter()->GetExp();
        if (_qwExp > qwMainExp)
            _qwExp = qwMainExp;
    }

    bool bRes = CExpMgr::TestLevelUp(_byLevel, _qwExp);
    if (bRes)
    {
        InitFighterAttr();

        //散仙升级事件
        if(IsHeroFighter())
        {
            CPlayerPtr pPlayer = GetUser()->GetPlayer();
            if (pPlayer)
            {
                TVecINT32 vecParam;
                vecParam.push_back(GetID());
                vecParam.push_back(GetLevel());
                if (GetFighterManager())
                {
                    TVecFighterPtr rvecFighters;
                    GetFighterManager()->GetAllFighters(rvecFighters);
                    for (size_t i=0; i<rvecFighters.size(); i++)
                    {
                        vecParam.push_back(rvecFighters[i]->GetLevel());
                    }
                }
                CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
                if(pEventMgr)
                    pEventMgr->OnEvent(eEventType_FighterLevelUp, vecParam);
            }
        }
    }

    g_Game2CenterTeamC.UpFighter2Center(GetUser()->GetUserID(),_qwInstID);
    Update2DB();
    if (GetUser() && bNotify)
    {
        g_PropInfoS.PropQWNotify(*GetUser()->GetPlayer(), GetInstID(), eClassFighter, ePropExp, _qwExp);
        g_PropInfoS.PropNotify(*GetUser()->GetPlayer(), GetInstID(), eClassFighter, ePropLevel, GetLevel());
    }
    if (GetUser())
    {
        string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGetEXP, BuildStrVec(GetColor(),GetName(),qwExp));
        GetUser()->SendPkg(strPkg);
        if (bRes)
        {
            strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLevelUP, BuildStrVec(GetColor(),GetName(),GetLevel()));
            GetUser()->SendPkg(strPkg);
        }
    }
    return true;
}

bool CFighter::SubExp(UINT64 qwExp, bool bNotify)
{
    if(qwExp == 0)
        return false;

    if (qwExp >= _qwExp)
        _qwExp = 0;
    else
        _qwExp -= qwExp;

    bool r = CExpMgr::TestLevelDown(_byLevel, _qwExp);
    if (r)
        InitFighterAttr();

    g_Game2CenterTeamC.UpFighter2Center(GetUser()->GetUserID(),GetID());
    if (GetUser() && bNotify)
    {
        g_PropInfoS.PropQWNotify(*GetUser()->GetPlayer(), GetInstID(), eClassFighter, ePropExp, _qwExp);
        g_PropInfoS.PropNotify(*GetUser()->GetPlayer(), GetInstID(), eClassFighter, ePropLevel, GetLevel());
    }
    Update2DB();
    return true;
}

bool CFighter::RebuildAttr() const
{
    if (!IsDirty())
        return false;
    VECATTR_RESET(_vecFinalAttr);
    VECATTR_RESET(_vecBPAttr);
    VECATTR_RESET(_vecFinalAttr2);
    _vecFinalAttr += _vecFighterAttr;

    if (GetFighterManager())
    {
        if (IsMainFighter())
            GetFighterManager()->GetPlayerAddAttr(_vecFinalAttr);
        GetFighterManager()->GetHeroAndPlayerAddAttr(_vecFinalAttr);
    }

    _vecBPAttr += _vecFighterAttr;

    if (GetFighterManager())
    {
        if (IsMainFighter())
            GetFighterManager()->GetPlayerAddAttr(_vecBPAttr);
        GetFighterManager()->GetHeroAndPlayerAddAttrWithoutBuffer(_vecBPAttr);
    }
    //SetDirty(false);          //改为RebuildAttr()重载的地方调用！！
    return true;
}

void CFighter::SetDirty(bool bDirty, EAttrGroupType eType /* = eAttrGpMax */, bool bFromFgtManager /* = false */) const
{ 
    _bDirty = bDirty; 
    if (eType < eAttrGpMax && bDirty && GetFighterManager() && !bFromFgtManager)
        GetFighterManager()->SetDirty(eType);
    if (bDirty)
        CBattlePointOwner::SetDirty();
    //LOG_WRN << "FighterID:" << GetID() << " SetDirty " << (bDirty?"true":"false") << ". bFromFgtManager = " << (bFromFgtManager?"true":"false") << ".";
    if (!bDirty && eType == eAttrGpMax)
        OnAttrRebuilded();
} // XXX: const because of RebuildAttr is const

void CFighter::OnAttrRebuilded() const
{
}

const TVecFloat& CFighter::GetAttrVec() const
{
    if (IsDirty())
        RebuildAttr(); // XXX: 调用PlayerFighter::RebuildAttr or HeroFighter::RebuildAttr
    return _vecFinalAttr;
}

const TVecFloat& CFighter::GetBPAttrVec() const
{
    if (IsDirty())
        RebuildAttr(); // XXX: 调用PlayerFighter::RebuildAttr or HeroFighter::RebuildAttr
    return _vecBPAttr;
}

const TVecFloat& CFighter::GetAttrVec2() const
{
    if (IsDirty())
        RebuildAttr(); // XXX: 调用PlayerFighter::RebuildAttr or HeroFighter::RebuildAttr

    return _vecFinalAttr2;
}

bool CFighter::ToProt(SFighterSpecInfo& sFighterInfo) const
{
    SFighterBaseInfo& oBaseInfo = sFighterInfo.oFighterInfo.oBaseInfo;
    oBaseInfo.qwInstID      = _qwInstID;
    oBaseInfo.wFighterID    = _wFighterID;
    oBaseInfo.byRecruited   = _bRecruited?1:0;
    oBaseInfo.byStar        = _byStar;
    oBaseInfo.iSlot         = _iSlot;
    oBaseInfo.iPos          = _iPos;
    oBaseInfo.byLevel       = GetLevel();
    oBaseInfo.qwExp         = _qwExp;

    if (IsMainFighter() && GetUser())
        oBaseInfo.strName = GetUser()->GetRoleName();
    else
        oBaseInfo.strName = GetName();

    oBaseInfo.dwHpMax       = GetHPMax();
    oBaseInfo.dwHp          = GetHP();
    oBaseInfo.dwAura        = GetAttr(EFIGHTATTR_INITAURA);
    oBaseInfo.dwAuraMax     = GetAttr(EFIGHTATTR_MAXAURA);

    oBaseInfo.byLianPi      = GetLianPi();
    oBaseInfo.byTongJin     = GetTongJin();
    oBaseInfo.byQiangJi     = GetQiangJi();
    oBaseInfo.byDuanGu      = GetDuanGu();
    oBaseInfo.byHuoLuo      = GetHuoLuo();
    oBaseInfo.byXiSui       = GetXiSui();

    oBaseInfo.byDujieLevel  = GetDujieLevel();
    oBaseInfo.dwDujieExp    = GetDujieExp();

    oBaseInfo.byQuality     = GetColor();

    oBaseInfo.dwSpiritPower = GetSpiritPower();
    return true;
}

bool CFighter::SwapCuiTi(CFighterPtr& pFighter)
{
    for (UINT8 i = 0; i < eCuiTiMax; ++ i)
    {
        std::swap(_byCuiTiLvl[i], pFighter->_byCuiTiLvl[i]);
    }
    return true;
}

void CFighter::Update2DB(EDataChange eDataChange/* = eOpUpdate*/)
{
    if (!GetUser())
    {
        LOG_WRN << "Save a fighter without OWNER.";
        return;
    }

    string strData;
    COutArchive iar(strData);
    SFighterDBInfo oFighterDBInfo;
    oFighterDBInfo.qwInstID     = _qwInstID;
    oFighterDBInfo.qwRoleID     = GetUser()->GetUserID();
    oFighterDBInfo.wFighterID   = _wFighterID;
    oFighterDBInfo.byRecruited  = _bRecruited?1:0;
    oFighterDBInfo.byStar       = _byStar;
    oFighterDBInfo.iSlot        = _iSlot;
    oFighterDBInfo.iPos         = _iPos;
    oFighterDBInfo.byLevel      = GetLevel();
    oFighterDBInfo.qwExp        = _qwExp;
    oFighterDBInfo.byLianPi     = GetLianPi();
    oFighterDBInfo.byTongJin    = GetTongJin();
    oFighterDBInfo.byQiangJi    = GetQiangJi();
    oFighterDBInfo.byDuanGu     = GetDuanGu();
    oFighterDBInfo.byHuoLuo     = GetHuoLuo();
    oFighterDBInfo.byXiSui      = GetXiSui();
    oFighterDBInfo.dwDujieExp   = GetDujieExp();
    oFighterDBInfo.dwSpiritPower = GetSpiritPower();
    iar << oFighterDBInfo;

    g_Game2DBCommC.Send_RoleDataUpdate(GetUser()->GetUserID(), eTypeFighterInfo, eDataChange, strData);
}

// 保存
void CFighter::UpdateBuff2DB(const SDBBuffInfo& rDBBuffInfo, EDataChange eDataChange)
{
    if (GetFighterManager())
    {
        CUserPtr pUser = GetFighterManager()->GetUserPtr();
        if (pUser)
        {
            CPlayerPtr pPlayer = pUser->GetPlayer();
            if (pPlayer)
            {
                pPlayer->UpdateBuff2DB(rDBBuffInfo, eDataChange);
            }
        }
    }
}

void CFighter::OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo)
{
}

void CFighter::SetCreatureBufferAttr(TVecFloat& _vecCreatureBufferAtt)
{
    _vecCreatureBufferAttr.clear();

    _vecCreatureBufferAttr += _vecCreatureBufferAtt;

    SetDirty(true);  
}

void CFighter::GetShowInfo(NGlobalChatProt::SShowInfo& stShow)
{
    NGlobalChatProt::SFlauntHero sInfo;
    if(IsMainFighter())
    {
        sInfo.strName = GetUser()->GetPlayer()->GetName();
    }
    sInfo.qwInstID = GetInstID();
    sInfo.wFighterID = GetID();
    sInfo.byLevel = GetLevel();
    sInfo.byQuilty = GetColor();
    sInfo.dwPower = GetBattlePoint();
    sInfo.oAttrVec = GetFtAttrMod();
    stShow.qwInstID = GetRoleID();
    COutArchive iar(stShow.strShowInfo);
    iar << UINT8(NGlobalChatProt::eShowRole);
    iar << sInfo;
}

// ===  FUNCTION  ======================================================================
//         Name:  ToBattleFighter
//  Description:  生成战斗对象
// =====================================================================================
IBattleFighterPtr CFighter::ToBattleFighter(UINT8 byTeamID, EBattleType eBattleType)
{
    IBattleFighterPtr pBattleFighter = CreateBattleFighter();
    if (!pBattleFighter)
        return NULL;

    // 把Fighter转换成BattleFighter
    SBFInfo sBFInfo;

    sBFInfo.qwInstID    = GetInstID();              //将唯一ID
    sBFInfo.wFighterID  = GetFighterID();           //将类型ID
    sBFInfo.byTeamID    = byTeamID;                 //所属队伍ID
    sBFInfo.dwPos       = GetPos();                 //阵型中的位置
    sBFInfo.byLevel     = GetLevel();               //等级
    sBFInfo.eJob        = ECareerType(GetJob());    //职业
    sBFInfo.strName     = GetName();                //姓名
    sBFInfo.eSex        = GetSex();
    sBFInfo.pFeature    = GetBattleAppear(eBattleType);
    //sBFInfo.pFeature    = GetAppear();

    if (!pBattleFighter->InitFighter(sBFInfo))
        return NULL;

    SFighterPropCFGEx* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(GetID());
    if (pFighterPropCFG && IsMonsterFighter())
    {
        pBattleFighter->InitFighterAttr(GetAttrVec());
        pBattleFighter->InitFighterBattleInfo(GetAttr(EFIGHTATTR_MAXHP), GetAttr(EFIGHTATTR_MAXHP), GetAttr(EFIGHTATTR_INITAURA), GetAttr(EFIGHTATTR_MAXAURA));
    }
    else
    {
        pBattleFighter->InitFighterAttr(GetAttrVec2());
        pBattleFighter->InitFighterBattleInfo(GetHPMax2(), GetHP(), GetAttr2(EFIGHTATTR_INITAURA), GetAttr2(EFIGHTATTR_MAXAURA));
    }

    TVecUINT32 vecAllSkill;
    UINT32 dwNormalAttack = 0;
    if (!GetAllSkills(vecAllSkill, dwNormalAttack))
        return NULL;

    pBattleFighter->InitFighterSkills(vecAllSkill, dwNormalAttack);

    //if (pFighterPropCFG && CFighterMgr::IsMonsterOrWorldBossFighter(*pFighterPropCFG))
        pBattleFighter->InitFighterSkillsEx(pFighterPropCFG->_vecSkillIDEx, pFighterPropCFG->_vecNormalAttackEx);

    if (GetUser() && GetUser()->GetPlayer())
    {
        CPlayerPtr pPlayer =  GetUser()->GetPlayer();
        UINT32 dwBattlePoint = GetBattlePoint(); 
        TVecINT32 vecParam;
        vecParam.push_back(GetID());
        vecParam.push_back(dwBattlePoint);
        pPlayer->OnEvent(eEventType_FighterBatterPoint,vecParam);
    }
    return pBattleFighter;
}		// -----  end of function ToBattleFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllSkills
//  Description:  获取所有的战斗技能
// =====================================================================================
bool CFighter::GetAllSkills(TVecUINT32& rvecAllSklls, UINT32& dwNormalAttack) const
{
    SFighterPropCFGEx* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(GetID());
    if (pFighterPropCFG && IsMonsterFighter())
    {
        dwNormalAttack = CSkillMgr::Instance().GetSkillIDQualityLevel(pFighterPropCFG->_NormalAttack);

        for (auto& rID : pFighterPropCFG->_vecSkillID)
        {
            rvecAllSklls.push_back(rID);
        }

        // 死亡技能
        if (pFighterPropCFG->_NormalAttack)
        {
            UINT32 dwSkillID = CSkillMgr::Instance().GetSkillIDQualityLevel(pFighterPropCFG->_NormalDead, 1);
            rvecAllSklls.push_back(dwSkillID);
        }
    }

    return true;
}		// -----  end of function GetAllSkills  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAppear
//  Description:  获取该散仙的外观
// =====================================================================================
SFeatureBasePtr CFighter::GetAppear() const
{
    SFighterPropCFG* pFighterPropCFG = GetFighterPropConfig();
    if (pFighterPropCFG && IsMonsterFighter())
    {
        SMonsterFeaturePtr pMonsterFeature(new SMonsterFeature);
        if (pMonsterFeature)
            pMonsterFeature->wMonsterID = GetID();
        return dynamic_pointer_cast<SFeatureBase>(pMonsterFeature);
    }
    else    //  其他类型让派生类重载该函数返回
        return NULL;
}		// -----  end of function GetAppear  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleAppear
//  Description:  获取战斗时该散仙的外观
// =====================================================================================
SFeatureBasePtr CFighter::GetBattleAppear(EBattleType eBattleType) const
{
    SFighterPropCFG* pFighterPropCFG = GetFighterPropConfig();
    if (pFighterPropCFG && IsMonsterFighter())
    {
        SMonsterFeatureWithBuffPtr pMonsterFeature(new SMonsterFeatureWithBuff);
        if (pMonsterFeature)
            pMonsterFeature->wMonsterID = GetID();
        return dynamic_pointer_cast<SFeatureBase>(pMonsterFeature);
    }
    else    //  其他类型让派生类重载该函数返回
        return NULL;
}		// -----  end of function GetBattleAppear  ----- //

