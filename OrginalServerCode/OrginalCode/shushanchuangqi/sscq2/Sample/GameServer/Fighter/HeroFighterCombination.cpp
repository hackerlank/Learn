// =====================================================================================
//
//       Filename:  HeroFighterCombination.cpp
//
//    Description:  散仙组合
//
//        Version:  1.0
//        Created:  12/04/2014 05:13:05 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  SunTao (Steven), sunt@kingnet.com
//   Organization:
//
// =====================================================================================

#include "HeroFighterCombination.h"
#include "FighterMgr.h"

CHeroFighterCombination::CHeroFighterCombination(UINT8 byGroupID)
    : _byGroupID(byGroupID), _byGroupLvl(1), _dwGroupExp(0), _bInLineUp(false), _bInEMei(false), _bDirty(true)
{
}

void CHeroFighterCombination::ToProt(SFighterCombination& rInfo)
{
    rInfo.byGroupID  = GetID();
    rInfo.byGroupLvl = GetLevel();
    rInfo.dwGroupExp = GetExp();
    rInfo.byInLineUp = IsFightInLineUp() ? 1 : 0;
    rInfo.byInEMei   = IsFightInEMei() ? 1 : 0;
}

void CHeroFighterCombination::RebuildAttr()
{
    if (!IsDirty())
        return;
    SFighterCombinationEffectCFGEx* pCFG = CFighterMgr::GetFighterCombinationEffectCFG(GetID(), GetLevel());
    if (!pCFG)
        return;
    VECATTR_RESET(_vecFinalAttr);
    PHYATK_ADD(_vecFinalAttr, pCFG);
    MGCATK_ADD(_vecFinalAttr, pCFG);
    PHYDEF_ADD(_vecFinalAttr, pCFG);
    MGCDEF_ADD(_vecFinalAttr, pCFG);
    PHYRDC_ADD(_vecFinalAttr, pCFG);
    MGCRDC_ADD(_vecFinalAttr, pCFG);
    MAXHP_ADD(_vecFinalAttr, pCFG);
    SPEED_ADD(_vecFinalAttr, pCFG);
    HIT_ADD(_vecFinalAttr, pCFG);
    HITRATE_ADD(_vecFinalAttr, pCFG);
    DODGE_ADD(_vecFinalAttr, pCFG);
    DODGERATE_ADD(_vecFinalAttr, pCFG);
    CRITICAL_ADD(_vecFinalAttr, pCFG);
    CRTRATE_ADD(_vecFinalAttr, pCFG);
    ANTICRITCAL_ADD(_vecFinalAttr, pCFG);
    ANTICRTRATE_ADD(_vecFinalAttr, pCFG);
    BLOCK_ADD(_vecFinalAttr, pCFG);
    BLOCKRATE_ADD(_vecFinalAttr, pCFG);
    PIERCE_ADD(_vecFinalAttr, pCFG);
    PIERCERATE_ADD(_vecFinalAttr, pCFG);
    COUNTER_ADD(_vecFinalAttr, pCFG);
    COUNTERRATE_ADD(_vecFinalAttr, pCFG);
    RESIST_ADD(_vecFinalAttr, pCFG);
    RESISTRATE_ADD(_vecFinalAttr, pCFG);
    INITAURA_ADD(_vecFinalAttr, pCFG);
    MAXAURA_ADD(_vecFinalAttr, pCFG);
    CRIEXTRAADD_ADD(_vecFinalAttr, pCFG);
    CRIEXTRARDC_ADD(_vecFinalAttr, pCFG);
    METALATK_ADD(_vecFinalAttr, pCFG);
    WOODATK_ADD(_vecFinalAttr, pCFG);
    WATERATK_ADD(_vecFinalAttr, pCFG);
    FIREATK_ADD(_vecFinalAttr, pCFG);
    EARTHATK_ADD(_vecFinalAttr, pCFG);
    METALDEF_ADD(_vecFinalAttr, pCFG);
    WOODDEF_ADD(_vecFinalAttr, pCFG);
    WATERDEF_ADD(_vecFinalAttr, pCFG);
    FIREDEF_ADD(_vecFinalAttr, pCFG);
    EARTHDEF_ADD(_vecFinalAttr, pCFG);
    PHYATK_PER_ADD(_vecFinalAttr, pCFG);
    MGCATK_PER_ADD(_vecFinalAttr, pCFG);
    PHYDEF_PER_ADD(_vecFinalAttr, pCFG);
    MGCDEF_PER_ADD(_vecFinalAttr, pCFG);
    MAXHP_PER_ADD(_vecFinalAttr, pCFG);
    SPEED_PER_ADD(_vecFinalAttr, pCFG);
    HIT_PER_ADD(_vecFinalAttr, pCFG);
    DODGE_PER_ADD(_vecFinalAttr, pCFG);
    CRITICAL_PER_ADD(_vecFinalAttr, pCFG);
    ANTICRITCAL_PER_ADD(_vecFinalAttr, pCFG);
    BLOCK_PER_ADD(_vecFinalAttr, pCFG);
    PIERCE_PER_ADD(_vecFinalAttr, pCFG);
    COUNTER_PER_ADD(_vecFinalAttr, pCFG);
    RESIST_PER_ADD(_vecFinalAttr, pCFG);
    ANTIEFFECT_ADD(_vecFinalAttr, pCFG);
    //COUTEREXTRAADD_ADD(_vecFinalAttr, pCFG);
    //COUTEREXTRARDC_ADD(_vecFinalAttr, pCFG);

    SetDirty(false);
}

void CHeroFighterCombination::AppendAttr(TVecFloat& vecAttr)
{
    if (IsDirty())
        RebuildAttr();
    vecAttr += _vecFinalAttr;
}

