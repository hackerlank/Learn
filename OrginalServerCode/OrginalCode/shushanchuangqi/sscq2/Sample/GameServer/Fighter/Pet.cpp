
#include "stdafx.h"
#include "Protocols.h"
#include "Pet.h"
#include "FighterMgr.h"
#include "Battle.h"

bool CPet::Init(UINT16 wPetID)
{
    /*SPetCFGEx* pPetCfg = CFighterMgr::GetPetCfg(wPetID);
    if (!pPetCfg)
        return false;
    _wPetID = wPetID;
    if (pPetCfg->_SkillId)
        _oUpSkills.Set(0, SkillMgr.GetSkillIDQualityLevel(pPetCfg->_SkillId, 1));
        //_oUpSkills.Set(0, SKILLANDLEVEL(pPetCfg->_SkillId, 1));
    return true;*/

    _wPetID = wPetID;
    _bySelected = 2;
    _byLevel = 1;

    SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(_wPetID, _byLevel);
    if (NULL == pPetLevelCFG)
        return false;

    if (pPetLevelCFG->_SkillID > 0)
         _oUpSkills.Set(0, SkillMgr.GetSkillIDQualityLevel(pPetLevelCFG->_SkillID, pPetLevelCFG->_SkillLevel));
         //_oUpSkills.Set(0, SKILLANDLEVEL(pPetLevelCFG->_SkillID, pPetLevelCFG->_SkillLevel));
    
    InitPetAttr();
    return true;
}

bool CPet::Load(const SPetDataInfo& sPetDataInfo)
{
    _wPetID = sPetDataInfo.wPetID;
    _bySelected = sPetDataInfo.bySelected;
    _byLevel = sPetDataInfo.byLevel;
    _dwExp = sPetDataInfo.dwExp;

    SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(_wPetID, _byLevel);
    if (NULL == pPetLevelCFG)
        return false;

    if (pPetLevelCFG->_SkillID > 0)
         _oUpSkills.Set(0, SkillMgr.GetSkillIDQualityLevel(pPetLevelCFG->_SkillID, pPetLevelCFG->_SkillLevel));
    
    InitPetAttr();
    return true;
}

IBattleFighterPtr CPet::ToBattleFighter(const TVecFloat& allPetAttr) const
{
    SPetCFGEx* pPetCfg = CFighterMgr::GetPetCfg(_wPetID);
    if (!pPetCfg)
        return NULL;
    SFighterPropCFGEx* pFighterCFG = CFighterMgr::GetFighterPropCfg(pPetCfg->_FighterProp);
    if (!pFighterCFG)
        return NULL;

    IBattleFighterPtr pBattleFighter = CreateBattleFighter();
    if (!pBattleFighter)
        return NULL;

    SBFInfo sBFInfo;
    sBFInfo.qwInstID    = 0;                                            //将唯一ID
    sBFInfo.wFighterID  = pPetCfg->_FighterProp;                        //将类型ID
    sBFInfo.dwPos       = IBattleFighter::GetPetPos();                  //阵型中的位置(BattleSimulator加载的时候会重新设置)
	sBFInfo.byLevel     = 1;                                            //等级
    sBFInfo.eJob        = static_cast<ECareerType>(pFighterCFG->_Job);  //职业
    if (pPetCfg)
        sBFInfo.strName = pPetCfg->_Name;                               //姓名
    else
        sBFInfo.strName = "无名阵灵"; 
    sBFInfo.eSex        = ESEX_FEMALE;                                  //性别

    SFormationFeaturePtr pSFormationFeature(new SFormationFeature);
    if(pSFormationFeature == NULL)
        LOG_CRI << "New SFormationFeature ERR";
    else
        pSFormationFeature->wFormationID = pPetCfg->_FighterProp;
    sBFInfo.pFeature = dynamic_pointer_cast<SFeatureBase>(pSFormationFeature);

    if (!pBattleFighter->InitFighter(sBFInfo))
        return NULL;

    pBattleFighter->InitFighterAttr(allPetAttr);
    pBattleFighter->InitFighterBattleInfo(100, 100, pFighterCFG->_EFIGHTATTR_INITAURA, pFighterCFG->_EFIGHTATTR_MAXAURA);
    pBattleFighter->SetMaxHP(100);
    pBattleFighter->SetHP(100);

    TVecUINT32 vecPetSkills;
    _oUpSkills.GetAllSkills(vecPetSkills);
    if (!vecPetSkills.empty())
        pBattleFighter->InitFighterSkills(vecPetSkills, 0);

    return pBattleFighter;
}

void CPet::SetPetSkill()
{
    SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(_wPetID, _byLevel);
    if (!pPetLevelCFG)
        return;

    if (pPetLevelCFG->_SkillID > 0)
        _oUpSkills.Set(0, SkillMgr.GetSkillIDQualityLevel(pPetLevelCFG->_SkillID, pPetLevelCFG->_SkillLevel));
}

void CPet::InitPetAttr()
{
    SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(_wPetID, _byLevel);
    if (!pPetLevelCFG)
        return;

    VECATTR_RESET(_vecAttr);
    PHYATK_SET(_vecAttr, pPetLevelCFG);
    MGCATK_SET(_vecAttr, pPetLevelCFG);
    PHYDEF_SET(_vecAttr, pPetLevelCFG);
    MGCDEF_SET(_vecAttr, pPetLevelCFG);
    PHYRDC_SET(_vecAttr, pPetLevelCFG);
    MGCRDC_SET(_vecAttr, pPetLevelCFG);
    MAXHP_SET(_vecAttr, pPetLevelCFG);
    SPEED_SET(_vecAttr, pPetLevelCFG);
    HIT_SET(_vecAttr, pPetLevelCFG);
    HITRATE_SET(_vecAttr, pPetLevelCFG);
    DODGE_SET(_vecAttr, pPetLevelCFG);
    DODGERATE_SET(_vecAttr, pPetLevelCFG);
    CRITICAL_SET(_vecAttr, pPetLevelCFG);
    CRTRATE_SET(_vecAttr, pPetLevelCFG);
    ANTICRITCAL_SET(_vecAttr, pPetLevelCFG);
    ANTICRTRATE_SET(_vecAttr, pPetLevelCFG);
    BLOCK_SET(_vecAttr, pPetLevelCFG);
    BLOCKRATE_SET(_vecAttr, pPetLevelCFG);
    PIERCE_SET(_vecAttr, pPetLevelCFG);
    PIERCERATE_SET(_vecAttr, pPetLevelCFG);
    COUNTER_SET(_vecAttr, pPetLevelCFG);
    COUNTERRATE_SET(_vecAttr, pPetLevelCFG);
    RESIST_SET(_vecAttr, pPetLevelCFG);
    RESISTRATE_SET(_vecAttr, pPetLevelCFG);
    INITAURA_SET(_vecAttr, pPetLevelCFG);
    MAXAURA_SET(_vecAttr, pPetLevelCFG);
    CRIEXTRAADD_SET(_vecAttr, pPetLevelCFG);
    CRIEXTRARDC_SET(_vecAttr, pPetLevelCFG);
    METALATK_SET(_vecAttr, pPetLevelCFG);
    WOODATK_SET(_vecAttr, pPetLevelCFG);
    WATERATK_SET(_vecAttr, pPetLevelCFG);
    FIREATK_SET(_vecAttr, pPetLevelCFG);
    EARTHATK_SET(_vecAttr, pPetLevelCFG);
    METALDEF_SET(_vecAttr, pPetLevelCFG);
    WOODDEF_SET(_vecAttr, pPetLevelCFG);
    WATERDEF_SET(_vecAttr, pPetLevelCFG);
    FIREDEF_SET(_vecAttr, pPetLevelCFG);
    EARTHDEF_SET(_vecAttr, pPetLevelCFG);
    PHYATK_PER_SET(_vecAttr, pPetLevelCFG);
    MGCATK_PER_SET(_vecAttr, pPetLevelCFG);
    PHYDEF_PER_SET(_vecAttr, pPetLevelCFG);
    MGCDEF_PER_SET(_vecAttr, pPetLevelCFG);
    MAXHP_PER_SET(_vecAttr, pPetLevelCFG);
    SPEED_PER_SET(_vecAttr, pPetLevelCFG);
    HIT_PER_SET(_vecAttr, pPetLevelCFG);
    DODGE_PER_SET(_vecAttr, pPetLevelCFG);
    CRITICAL_PER_SET(_vecAttr, pPetLevelCFG);
    ANTICRITCAL_PER_SET(_vecAttr, pPetLevelCFG);
    BLOCK_PER_SET(_vecAttr, pPetLevelCFG);
    PIERCE_PER_SET(_vecAttr, pPetLevelCFG);
    COUNTER_PER_SET(_vecAttr, pPetLevelCFG);
    RESIST_PER_SET(_vecAttr, pPetLevelCFG);
    ANTIEFFECT_SET(_vecAttr, pPetLevelCFG);
    //COUTEREXTRAADD_SET(_vecAttr, pPetLevelCFG);
    //COUTEREXTRARDC_SET(_vecAttr, pPetLevelCFG);
}

void CPet::RebuildAttr()
{
    if (!IsDirty())
        return;
    InitPetAttr();
    SetDirty(false);
}

void CPet::AppendAttr(TVecFloat& vecAttr)
{
    if (IsDirty())
        RebuildAttr();
    vecAttr += _vecAttr;
}

void CPet::GetAllSkillID(TVecUINT32& rvecSkillID) const
{
    _oUpSkills.GetAllSkills(rvecSkillID);
}

void CPet::GetShowInfo(NGlobalChatProt::SShowInfo& stShow)
{
    NGlobalChatProt::SFlauntPet sInfo;  
    sInfo.wFighterID = _wPetID;
    sInfo.byLevel = _byLevel;
    COutArchive iar(stShow.strShowInfo);
    iar << UINT8(NGlobalChatProt::eShowPet); 
    iar << sInfo;
}

// ===  FUNCTION  ======================================================================
//         Name:  Super
//  Description:  阵灵变得超级牛逼
// =====================================================================================
void CPet::Super ()
{
    UINT8 byLevel = GetPetLevel() + 1;

    SPetLevelCFG* pPetLevelCFG = CFighterMgr::GetPetLevelCfg(GetID(), byLevel);
    while(pPetLevelCFG)
    {
        SetPetExp(pPetLevelCFG->_LevelUpExp);
        SetPetLevel(byLevel++);
        SetPetSkill();
        SetDirty(true);
        pPetLevelCFG = CFighterMgr::GetPetLevelCfg(GetID(), byLevel);
    }


}		// -----  end of function Super  ----- //

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

