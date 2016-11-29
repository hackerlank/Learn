
#include "stdafx.h"
#include "Protocols.h"
#include "FighterManager.h"
#include "User.h"
#include "Player.h"
#include "Random.h"
#include "PropInfo.h"
#include "RoleEvent.h"
#include "HeroFighter.h"
#include "GetCondMgr.h"
#include "ShushanBattle.h"
#include "AchievementMgr.h"
#include "EventMgr.h"
#include "CollectionMgr.h"
#include "ExpMgr.h"
#include "HorseMgr.h"
#include "BeautyMgr.h"
#include "FightFormationMgr.h"
#include "BoostMgr.h"
#include "HeroFighterTavern.h"
#include "GameServerLog.h"
#include "IconAppearManager.h"
#include "EquipTrump.h"

#include "Random.h"
using namespace NFighterProt;
using namespace NFighterProt;
using namespace NPropInfo;
using namespace NRoleEvent;

CFighterManager::CFighterManager(CUser& rUser) : 
    _rUser(rUser), _oFighterSlots(), _oFormationPet(rUser), _oHeroCombinationSlots(rUser),
    _oTrumps(ToThisPtr(&rUser))
{
    for (UINT8 byIndex = eAttrGpMin; byIndex < eAttrGpMax; ++byIndex)
    {
        _mapAttrGroupDirty[EAttrGroupType(byIndex)] = true;
    }
    _dwCombineSkillIDTeam   = 0;
    _dwCombineSkillIDLineUp = 0;
    _dwCombineSkillIDEMei   = 0;
}

CFighterManager::~CFighterManager()
{
    //LOG_CRI << "CFighterManager::~CFighterManager()";
}

bool CFighterManager::InitDefaultFashion()
{
    if (!GetMainFighter())
        return false;
    SFighterPropCFG* pFighterCfg = GetMainFighter()->GetFighterPropConfig();
    if (!pFighterCfg)
        return false;
    bool bRes = false;
    if (pFighterCfg->_Closes)
        bRes = _oFashions.AdoptFashion(pFighterCfg->_Closes);
    if (pFighterCfg->_Weapon)
        bRes = _oFashions.AdoptFashion(pFighterCfg->_Weapon);
    return bRes;
}

CUserPtr CFighterManager::GetUserPtr()
{
    return ToThisPtr(_rUser);
}

void CFighterManager::NotifyFighterInfo(const CFighterPtr& pFighter)
{
    TVecFighterSpecInfo vecFighters;
    g_RoleEventProtS.Send_FighterInfoNotify(vecFighters);
}

void CFighterManager::WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID)
{
    if (!wID)
        return;
    CFighterPtr pFighter = GetFighterByID(wID);
    if(!pFighter)
        return ;
    NLogDataDefine::SFighterLogPtr ptrLog(new NLogDataDefine::SFighterLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SFighterLog& rLog = *ptrLog;
    rLog.dwServerId  = Config._wGroup;
    rLog.qwUserId    = _rUser.GetRoleID();
    rLog.wFighterId  = wID;
    rLog.sName       = pFighter->GetName();
    rLog.wLevel      = pFighter->GetLevel();
    rLog.byQuality   = pFighter->GetColor();
    rLog.eOptType    = eType;
    rLog.dwType      = dwDetail;
    rLog.qwResult    = qwResult;
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

ERecruitResult CFighterManager::Recruit(UINT16 wFighterID)
{
    if (!wFighterID)
        return eRecruitFailed;

    CTavernPtr pTavern = CTavernMgr::Instance().GetTavernByFighterID(wFighterID);
    if (!pTavern)
        return eRecruitFailed;
    
    CUserPtr pUser = GetUserPtr();
    if (!pUser)
        return eRecruitFailed;
    if (pTavern->GetMinLevel() > pUser->GetLevel())
        return eRecruitLevelLimited;

    CHeroFighterInTavernPtr pHeroFighterInTavern = pTavern->GetHeroFighter(wFighterID);
    if (!pHeroFighterInTavern)
        return eRecruitFailed;


    if (!CGetCondMgr::Instance().TestCond(_rUser, pHeroFighterInTavern->GetGetCondID(), 0, true))
        return eRecruitLackOfMoney;
    if (!CGetCondMgr::Instance().ProcessCond(_rUser, pHeroFighterInTavern->GetGetCondID(), NLogDataDefine::ItemTo_Recruit))
        return eRecruitLackOfMoney;

    SFighterPropCFGEx* pFighterPropCFGEx = CFighterMgr::GetFighterPropCfg(wFighterID);
    if (!pFighterPropCFGEx)
        return eRecruitFailed;
    if (!GetFighterForce(wFighterID))
        return eRecruitAlready;

    //招募散仙事件
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        // 相关任务
        _rUser.GetTaskPkg().OnAction(*pPlayer, eProcessAction_RecruitCortege, 1);

        g_Game2CenterCommC.Send_SendWonderType(NGame2CenterComm::eActFighter,pPlayer->GetRoleID(),wFighterID);
    }


    //招募事件记入LogServer
    WriteFighterLog(eOptType_Recurit, 0, 1, wFighterID);

    return eRecruitSucc;
}

EFighterBuyResult CFighterManager::FighterBuy(UINT16 wFighterID)
{
    CUserPtr pUser = GetUserPtr();
    if (!pUser)
        return eFighterBuyFailed;

    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(!pPlayer)
        return eFighterBuyFailed;

    if (!wFighterID)
        return eFighterBuyFailed;

    if (wFighterID != SParamConfig::wInviteFighterID1 && wFighterID != SParamConfig::wInviteFighterID2)
        return eFighterBuyFailed;
    
    UINT8 byPos = 0;
    UINT32 dwCondB = 0;
    UINT32 dwCondC = 0;
    if (wFighterID == SParamConfig::wInviteFighterID1)
    {
        dwCondB = SParamConfig::wInviteFighterDujie1;
        dwCondC = SParamConfig::wInviteFighterCost1;
    }
    else
    {
        byPos = 1;
        dwCondB = SParamConfig::wInviteFighterDujie2;
        dwCondC = SParamConfig::wInviteFighterCost2;
    }
        
    CGameVar& rCGameVar = pUser->GetVars();
    UINT64 FighterBuyStatus = rCGameVar.GetVar(NVarDefine::ePlayerFighterBuyMark);
    UINT8 byStatus = GET_BIT(FighterBuyStatus, byPos);
    if (1 == byStatus)
        return eFighterBuyAlready;

    if(!pUser->CanSubMoney(EMONEY_GOLD, dwCondC))
    return eFighterBuyLackOfMoney;

    //先扣钱再加散仙、渡劫
    if (wFighterID == SParamConfig::wInviteFighterID1)
        pUser->SubMoney(EMONEY_GOLD, dwCondC, NLogDataDefine::ItemTo_FighterBuyLYQ);
    else
        pUser->SubMoney(EMONEY_GOLD, dwCondC, NLogDataDefine::ItemTo_FighterBuyQLY);

    //加散仙
    if (!GetFighterForce(wFighterID))
        return eFighterBuyFailed;

    CFighterPtr pFighter = GetFighterByID(wFighterID);
    if(!pFighter)
        return eFighterBuyFailed;

    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
    if (!pHeroFighter)
        return eFighterBuyFailed;

    //将该散仙渡劫
    if (!pHeroFighter->BuyFighterDujie(dwCondB))
        return eFighterBuyFailed;
        
    FighterBuyStatus = SET_BIT(FighterBuyStatus, byPos);
    rCGameVar.SetVar(NVarDefine::ePlayerFighterBuyMark, FighterBuyStatus);
   
    //世界广播
    TVecString vecstring;
    vecstring.push_back(NumberToString(pPlayer->GetColor()));
    vecstring.push_back(pPlayer->GetName());
    if (wFighterID == SParamConfig::wInviteFighterID1)
        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgFighter, vecstring);
    else
        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgFighter1, vecstring);

    //关闭ICON
    FighterBuyStatus = rCGameVar.GetVar(NVarDefine::ePlayerFighterBuyMark);
    if (1 == GET_BIT(FighterBuyStatus, 0) && 1 == GET_BIT(FighterBuyStatus, 1))
        CIconAppearMgr::Instance().DelAction(*pUser, 103);

    return eFighterBuySucc;
}

bool CFighterManager::GetFighterForce(UINT16 wFighterID)
{
    if (!wFighterID)
        return false;

    bool bNew = false;
    int idx = -1;
    EDataChange eOpType = eOpUpdate;

    CFighterPtr pFighter = _oFighterSlots.GetFighterByID(wFighterID, &idx);
    if (pFighter && pFighter->GetRecruited())
        return false;

    if (!pFighter)
    {
        pFighter = CFighterMgr::Create(wFighterID, true, GetUserPtr());
        bNew = true;
        eOpType = eOpAdd;
    }
    if (!pFighter)
        return false;

    if (!pFighter->IsHeroFighter())
        return false;

    int iSlot = _oFighterSlots.GetEmptySlot();
    if (iSlot != INVALID_SLOT)
    {
        pFighter->SetSlot(iSlot);
        _oFighterSlots.Set(iSlot, pFighter);
    }

    pFighter->SetRecruited(true);
    pFighter->Update2DB(eOpType);

    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
    if (pHeroFighter)
    {
        pHeroFighter->GetSkills().UnlockAllSkillByDujie(false);
        pHeroFighter->GetSkills().Update2DB(eOpAdd); // XXX: 只能在招募时新建记录了
    }

    pFighter->RegenAllHP();     //XXX 主动调用回满血
    RecruitNotify(pFighter, bNew);


    CPlayerPtr pPlayer = _rUser.GetPlayer();

    SFighterPropCFG* pFighterPropCFG = pFighter->GetFighterPropConfig();
    if(pFighterPropCFG&&pPlayer)
    {
        CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
        if(pBeautyMgr)
        {
            pBeautyMgr->DeleteDropItem(pFighterPropCFG->_RecruitItem);
        }
    }
            

    /*
    bool bRes = GetFormation().PutIntoFormation(pFighter);
    if (bRes)
        ResetCombinationSkill();
        */
    //招募散仙事件
    if(pPlayer)
    {
        // 相关任务
        _rUser.GetTaskPkg().OnAction(*pPlayer, eProcessAction_RecruitCortege, 1);

        //相关事件
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
        {
            TVecINT32 vecParam;
            vecParam.push_back(wFighterID);
            TVecFighterPtr rvecFighters;
            GetAllFighters(rvecFighters);
            vecParam.push_back(rvecFighters.size());

            ostringstream os;
            os<<wFighterID;
            os<<";";
            os<<rvecFighters.size();
            os<<";";
            for(size_t i = 0; i < rvecFighters.size(); i++)
            {
                if(rvecFighters[i])
                {
                    if(i != rvecFighters.size()-1)
                    {
                        os<<rvecFighters[i]->GetID()<<",";
                    }
                }
            }

            pEventMgr->OnEvent(eEventType_FighterEnlisted, vecParam,os.str());
            //g_Game2CenterCommC.Send_SendWonderType(NGame2CenterComm::eActFighter,pPlayer->GetRoleID(),wFighterID);

        }
    }
    
    //color change
    OnFighterColorChange(pFighter->GetStar());


    return true;
}

void CFighterManager::RecruitNotify(CFighterPtr& pFighter, bool bNew)
{
    if (!pFighter)
        return;
    TVecFighterSpecInfo info(1);
    pFighter->ToProt(info[0]);
    _rUser.SendPkg(g_RoleEventProtS.BuildPkg_FighterInfoNotify(info));

    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer && pFighter->GetColor() >= 3)
    {
        NGlobalChatProt::TVecShowInfo vecShow;
        NGlobalChatProt::SShowInfo stShow;
        pFighter->GetShowInfo(stShow);
        vecShow.push_back(stShow);
        TVecString vecstring;
        vecstring.push_back(NumberToString(pPlayer->GetColor()));
        vecstring.push_back(pPlayer->GetName());
        g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL, 0, eMsgInviteBoardCast, vecstring, vecShow);
    }
}

class EnumerateFighterClearCombine : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighterClearCombine() {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter && pFighter->IsHeroFighter())
                {
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if (pHeroFighter)
                        pHeroFighter->GetSkills().ClearCombinationSkill();
                }
            }
            return true;
        }
};

UINT32 CFighterManager::GetCombinationSkill(ECombEquipToType eType)
{
    UINT32 dwSkillID = 0;
    switch(eType)
    {
        case eCombEquipToLineUp:
            dwSkillID = _dwCombineSkillIDLineUp;
        break;
        case eCombEquipToEMei:
            dwSkillID = _dwCombineSkillIDEMei;
        break;
        case eCombEquipToTeam:
            dwSkillID = _dwCombineSkillIDTeam;
        break;
        default:
            break;
    }
    return dwSkillID;
}

void CFighterManager::SetCombinationSkill(ECombEquipToType eType, UINT32 dwSkillID)
{
    switch(eType)
    {
        case eCombEquipToLineUp:
            _dwCombineSkillIDLineUp = dwSkillID;
        break;
        case eCombEquipToEMei:
            _dwCombineSkillIDEMei = dwSkillID;
        break;
        case eCombEquipToTeam:
            _dwCombineSkillIDTeam = dwSkillID;
        break;
        default:
            break;
    }
}

void CFighterManager::ResetCombinationSkill(const TVecUINT16& rvecFighterID, ECombEquipToType eType, bool bInBattle/* = true */)
{
    if (rvecFighterID.empty())
        return;
    UINT32 dwSkillID = 0;
    switch(eType)
    {
        case eCombEquipToLineUp:
            dwSkillID = _dwCombineSkillIDLineUp;
        break;
        case eCombEquipToEMei:
            dwSkillID = _dwCombineSkillIDEMei;
        break;
        case eCombEquipToTeam:
            dwSkillID = _dwCombineSkillIDTeam;
        break;
        default:
            return;
    }
    if (bInBattle)
    {
        EnumerateFighterClearCombine en;
        _oFighterSlots.enumerate(en);
    }

    set<UINT32> setProbSkillID; // 新阵型可能的组合技能ID
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(_oHeroCombinationSlots.GetSlots()); ++ iSlot)
    {
        CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.Get(iSlot);
        if (!pFgtComb)
            continue;
        SFighterCombinationCFGEx* pFighterCombCfg = CFighterMgr::GetFighterCombinationCFG(pFgtComb->GetID());
        if (!pFighterCombCfg)
            continue;
        TVecUINT16 vecFighterIDTmp;
        for (auto & rFighterID : pFighterCombCfg->_vecFighterID)
        {
            for (auto & rID : rvecFighterID)
            {
                if (rID == rFighterID)
                {
                    vecFighterIDTmp.push_back(rFighterID);
                    break;
                }
            }
        }
        if (vecFighterIDTmp.size() == pFighterCombCfg->_vecFighterID.size())
            setProbSkillID.insert(SkillMgr.GetSkillIDQualityLevel(pFighterCombCfg->_Skill, pFgtComb->GetLevel()));
    }

    // 技能要换
    if (setProbSkillID.find(dwSkillID) == setProbSkillID.end())
    {
        if(setProbSkillID.empty())
            dwSkillID = 0;
        else
            dwSkillID = *(setProbSkillID.begin());
    }
    //XXX 二逼的设置出战方案
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(_oHeroCombinationSlots.GetSlots()); ++ iSlot)
    {
        CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.Get(iSlot);
        if (!pFgtComb)
            continue;
        SFighterCombinationCFGEx* pFighterCombCfg = CFighterMgr::GetFighterCombinationCFG(pFgtComb->GetID());
        if (!pFighterCombCfg || pFighterCombCfg->_vecFighterID.empty())
            continue;
        if (eType == eCombEquipToLineUp)
            pFgtComb->SetFightLineUp(false);
        else if (eType == eCombEquipToEMei)
            pFgtComb->SetFightEMei(false);
        UINT16 wFirstID = pFighterCombCfg->_vecFighterID[0];
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(GetFighterByID(wFirstID));
        if (pHeroFighter)
        {
            if (bInBattle)
            {
                pHeroFighter->GetSkills().ClearCombinationSkill();
                pHeroFighter->SetDirty(true);
            }
            if (pFighterCombCfg->_Skill == SKILL_ID(dwSkillID))
            {
                if (bInBattle)
                {
                    pHeroFighter->GetSkills().AddCombinationSkill(dwSkillID);
                    pHeroFighter->SetDirty(true);
                }
                if (eType == eCombEquipToLineUp)
                    pFgtComb->SetFightLineUp(true);
                else if (eType == eCombEquipToEMei)
                    pFgtComb->SetFightEMei(true);
            }
        }
        _oHeroCombinationSlots.Update2DB(pFgtComb, eOpUpdate);
    }
    switch(eType)
    {
        case eCombEquipToLineUp:
            _dwCombineSkillIDLineUp = dwSkillID;
            _oHeroCombinationSlots.UpdateToClient();
        break;
        case eCombEquipToEMei:
            _dwCombineSkillIDEMei = dwSkillID;
            _oHeroCombinationSlots.UpdateToClient();
        break;
        case eCombEquipToTeam:
            _dwCombineSkillIDTeam = dwSkillID;
        break;
        default:
            break;
    }
}

void CFighterManager::ResetCombinationSkill()
{
    CFormation& rFormation = GetFormation();
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);

    TVecUINT16 rvecFighterID;
    for (size_t j = 0; j < vecLineup.size(); ++ j)
    {
        if (!vecLineup[j].pFighter)
            continue;
        rvecFighterID.push_back(vecLineup[j].pFighter->GetID());
    }

    ResetCombinationSkill(rvecFighterID, eCombEquipToLineUp);
}

void CFighterManager::EquipToCombinationSkillAfterLoadDB()
{
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(_oHeroCombinationSlots.GetSlots()); ++ iSlot)
    {
        CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.Get(iSlot);
        if (!pFgtComb)
            continue;
        SFighterCombinationCFGEx* pFighterCombCfg = CFighterMgr::GetFighterCombinationCFG(pFgtComb->GetID());
        if (!pFighterCombCfg)
            continue;
        if (pFgtComb->IsFightInLineUp())
            _dwCombineSkillIDLineUp = SkillMgr.GetSkillIDQualityLevel(pFighterCombCfg->_Skill, pFgtComb->GetLevel());
        if (pFgtComb->IsFightInEMei())
            _dwCombineSkillIDEMei = SkillMgr.GetSkillIDQualityLevel(pFighterCombCfg->_Skill, pFgtComb->GetLevel());
    }
    ResetCombinationSkill();
}

ECombinationResult CFighterManager::ActiveCombination(UINT8 byGroupID)
{
    SFighterCombinationCFGEx* pFighterCombCfg = CFighterMgr::GetFighterCombinationCFG(byGroupID);
    if (!pFighterCombCfg)
        return eCombinationFailed;
    if (pFighterCombCfg->_Limit > _rUser.GetLevel())
        return eCombinationMainLevelErr;
    CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.GetFighterCombination(byGroupID);
    if (pFgtComb)
        return eCombinationHaved;
    if (!CGetCondMgr::Instance().TestCond(_rUser, pFighterCombCfg->_GetCond))
        return eCombinationFighterErr;
    if (!CGetCondMgr::Instance().ProcessCond(_rUser, pFighterCombCfg->_GetCond, NLogDataDefine::ItemTo_FighterCombination))
        return eCombinationFailed;
    for (size_t i = 0; i < pFighterCombCfg->_vecFighterID.size(); ++ i)
    {
        UINT16 wFighterID = pFighterCombCfg->_vecFighterID[i];
        if(!HasRecruitFighter(wFighterID))
            return eCombinationFighterErr;
    }
    pFgtComb.reset(new CHeroFighterCombination(byGroupID));
    _oHeroCombinationSlots.Set(byGroupID-1, pFgtComb);
    _oHeroCombinationSlots.Update2DB(pFgtComb, eOpAdd);

    SetDirty(eAttrGpFighterCombination);

    g_ChatProtS.Send_SystemMsgIDNotify(eMsgCombinationActivation);
    TVecString vecstring;
    vecstring.push_back(NumberToString(_rUser.GetPlayer()->GetColor()));
    vecstring.push_back(_rUser.GetPlayer()->GetName());
    vecstring.push_back(NumberToString(pFighterCombCfg->_Color));
    vecstring.push_back(pFighterCombCfg->_Name);
    g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgHeroZuHe,vecstring);
    ResetCombinationSkill();
         
    _rUser.GetTaskPkg().OnAction(*(_rUser.GetPlayer()), eProcessAction_CombinedActivation);

    if(_rUser.GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(byGroupID);
        _rUser.GetPlayer()->OnEvent(eEventType_FighterCombinationUnlock,vecParam);
    }

    return eCombinationSucc;
}

ECombinationResult CFighterManager::UpgradeCombination(UINT8 byGroupID, bool bOneKey, SFighterCombination& oCombinationInfo)
{
    CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.GetFighterCombination(byGroupID);
    if (!pFgtComb)
        return eCombinationNotHaved;
    UINT8 byGroupLevel = pFgtComb->GetLevel();
    SFighterCombinationEffectCFGEx* pCFG = CFighterMgr::GetFighterCombinationEffectCFG(byGroupID, byGroupLevel);
    if (!pCFG)
        return eCombinationFailed;

    if (CFighterMgr::IsMaxCombinationLevel(byGroupID, byGroupLevel))
        return eCombinationMaxLevel;
    CPack& rPack = _rUser.GetPack();
    UINT16 wMaxCount = rPack.GetItemCount(pCFG->_EvolveItemID);
    if (wMaxCount < pCFG->_EvolveItemCount)
        return eCombinationItemErr;

    UINT16 wNeedCount = 0;
    UINT32 dwTimes = 0;
    UINT32 dwGroupExp = pFgtComb->GetExp();
    while (dwGroupExp < pCFG->_ExpNeed)
    {
        if (wNeedCount >= wMaxCount)
            break;
        wNeedCount += pCFG->_EvolveItemCount;
        dwGroupExp += CRandom::RandInt(SParamConfig::wFighterCombinationEXPLow, SParamConfig::wFighterCombinationEXPMax);
        dwTimes++;
        if (dwGroupExp >= pCFG->_ExpNeed) // 升级了
        {
            ++ byGroupLevel;
            dwGroupExp = 0;
            break;
        }
        if (!bOneKey)
            break;
    }
    if (byGroupLevel != pFgtComb->GetLevel())
    {
        pFgtComb->SetLevel(byGroupLevel);
        pFgtComb->SetDirty(true);
        SetDirty(eAttrGpFighterCombination);
    }
    pFgtComb->SetExp(dwGroupExp);
    _oHeroCombinationSlots.Update2DB(pFgtComb, eOpUpdate);
    rPack.DelItemByItemID(pCFG->_EvolveItemID, wNeedCount, true, NLogDataDefine::ItemTo_FighterCombination);
    ResetCombinationSkill();
    oCombinationInfo.byGroupID  = byGroupID;
    oCombinationInfo.byGroupLvl = byGroupLevel;
    oCombinationInfo.dwGroupExp = dwGroupExp;

    g_ChatProtS.Send_SystemMsgIDNotify(eMsgCombinationCultivate);
    if(dwTimes > 0)
    {
         _rUser.GetTaskPkg().OnAction(*(_rUser.GetPlayer()), eProcessAction_HeroTeamUpLevel, dwTimes);
    }
    return eCombinationSucc;
}

ECombinationResult CFighterManager::EquipToCombinationSkill(UINT8 byGroupID, UINT8 byType, TVecUINT16& rvecFighterID)
{
    ECombEquipToType eType = ECombEquipToType(byType);
    if (rvecFighterID.empty() || (eType != eCombEquipToLineUp && eType != eCombEquipToEMei))
        return eCombinationFailed;
    CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.GetFighterCombination(byGroupID);
    if (!pFgtComb)
        return eCombinationNotHaved;
    SFighterCombinationCFGEx* pFighterCombCfg = CFighterMgr::GetFighterCombinationCFG(byGroupID);
    if (!pFighterCombCfg)
        return eCombinationFailed;
    if (pFighterCombCfg->_vecFighterID.empty())
        return eCombinationFailed;

    //判断散仙组合在不在阵型上
    TVecUINT16 vecFighterIDTmp;
    for (auto & rFighterID : pFighterCombCfg->_vecFighterID)
    {
        for (auto & rID : rvecFighterID)
        {
            if (rID == rFighterID)
            {
                vecFighterIDTmp.push_back(rFighterID);
                break;
            }
        }
    }
    if (vecFighterIDTmp.size() != pFighterCombCfg->_vecFighterID.size())
        return eCombinationFailed;
    //判断阵型上的散仙组合技能个数
    UINT8 bySize = 0;
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(_oHeroCombinationSlots.GetSlots()); ++ iSlot)
    {
        CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.Get(iSlot);
        if (!pFgtComb)
            continue;
        SFighterCombinationCFGEx* pCfg = CFighterMgr::GetFighterCombinationCFG(pFgtComb->GetID());
        if (!pCfg)
            continue;
        TVecUINT16 vecFighterIDTmp;
        for (auto & rFighterID : pFighterCombCfg->_vecFighterID)
        {
            for (auto & rID : rvecFighterID)
            {
                if (rID == rFighterID)
                {
                    vecFighterIDTmp.push_back(rFighterID);
                    break;
                }
            }
        }
        if (vecFighterIDTmp.size() == pCfg->_vecFighterID.size())
            ++ bySize;
    }
    if (bySize <= 1)
        return eCombinationFailed;

    //清除旧skillID 设置新skillID
    UINT16 wFirstID = pFighterCombCfg->_vecFighterID[0];
    UINT32 dwSkillID = SkillMgr.GetSkillIDQualityLevel(pFighterCombCfg->_Skill, pFgtComb->GetLevel());
    if (eType == eCombEquipToLineUp)
    {
        for (size_t j = 0; j < rvecFighterID.size(); ++ j)
        {
            CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(GetFighterByID(rvecFighterID[j]));
            if (!pHeroFighter)
                continue;
            pHeroFighter->GetSkills().ClearCombinationSkill();
            pHeroFighter->SetDirty(true);
            if (pHeroFighter->GetID() == wFirstID && pFighterCombCfg->_Skill)
            {
                pHeroFighter->GetSkills().AddCombinationSkill(dwSkillID);
                _dwCombineSkillIDLineUp = dwSkillID;
                break;
            }
        }
    }
    else
    {
        _dwCombineSkillIDEMei = dwSkillID;
    }
    //写DB
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(_oHeroCombinationSlots.GetSlots()); ++ iSlot)
    {
        CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.Get(iSlot);
        if (!pFgtComb)
            continue;
        if (eType == eCombEquipToLineUp)
            pFgtComb->SetFightLineUp(false);
        else
            pFgtComb->SetFightEMei(false);
        if (pFgtComb->GetID() == byGroupID)
        {
            if (eType == eCombEquipToLineUp)
                pFgtComb->SetFightLineUp(true);
            else
                pFgtComb->SetFightEMei(true);
        }
        _oHeroCombinationSlots.Update2DB(pFgtComb, eOpUpdate);
    }
    _oHeroCombinationSlots.UpdateToClient();
    return eCombinationSucc;
}

class EnumerateFighter4List : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighter4List(TVecFighterSpecInfo& vecFighters, size_t size) : _vecFighters(vecFighters), _maxsize(size), _size(0) {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(std::get<2>(*obj));
                if (pFighter && pFighter->GetRecruited())
                    pFighter->ToProt(_vecFighters[_size++]);

                if (_size >= _maxsize)
                    return false;
            }
            return true;
        }

    public:
        TVecFighterSpecInfo& _vecFighters;
        size_t _maxsize;
        size_t _size;
};

void CFighterManager::ToStream(TVecFighterSpecInfo& vecFighters)
{
    size_t size = _oFighterSlots.GetUsedCount();
    if (size)
    {
        if (vecFighters.size() < size)
            vecFighters.resize(size);
        EnumerateFighter4List en(vecFighters, size);
        _oFighterSlots.enumerate(en);
        vecFighters.resize(en._size);
    }
}

bool CFighterManager::AddFighterFromDB(CFighterPtr& pFighter)
{
    if (!pFighter)
        return false;

    INT32 iSlot = pFighter->GetSlot();
    INT32 iPos = pFighter->GetPos();

    if (pFighter->IsMainFighter() && iPos < 0) // XXX: 只有主将才考虑让他重新上阵
    {
       if (!GetFormation().PutIntoFormation(pFighter))
             return false;
    }

    if (iSlot < 0)
        return false;

    if (!iSlot && pFighter->IsMainFighter())
        _oFighterSlots.Set(0, pFighter);
    else
    {
        if (!iSlot && _oFighterSlots.HasObj(iSlot))
            return false;
        _oFighterSlots.Set(iSlot, pFighter);
    }

    // XXX: 在此之前必须先设置好阵型
    if (iPos >= 0 )
    {
        if (GetFormation().HasObj(iPos))
            return false;
        GetFormation().Set(iPos, pFighter);
    }

    pFighter->SetUser(GetUserPtr());
    return true;
}

UINT64 CFighterManager::GetBattleFighters(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType)
{
    //阵灵
    _oFormationPet.GetPetSlots().GetBattleFighters(vecBattleFighter);

    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI<<"NULL == pPlayer";
        return 0;
    }

    //美女
    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
    if(pBeautyMgr)
        pBeautyMgr->GetBattleFighters(vecBattleFighter);

    UINT64 qwMainInstID = 0;
    switch(eBattleType)
    {
        case EBLingshan:
        case EGuardEMei: //守卫峨嵋
        //case ETreasureHunt: // 寻宝
            {
                CFightFormationMgrPtr  pFightFormationMgr = pPlayer->GetFightFormationMgr();
                if(pFightFormationMgr)
                    qwMainInstID = pFightFormationMgr->GetBattleFighters(eBattleType, vecBattleFighter);

                // 战斗队伍里没有主将，还是需要主将头像显示
                if (qwMainInstID == 1 && GetMainFighter())
                {
                    IBattleFighterPtr pMainBattleFighter = GetMainFighter()->ToBattleFighter(0, eBattleType);
                    if (pMainBattleFighter)
                        qwMainInstID = GetMainFighter()->GetInstID();
                }
            }
            break;
        default:
            qwMainInstID = GetFormation().GetBattleFighters(vecBattleFighter, eBattleType);
            break;
    }

    return qwMainInstID;
}

//获取战斗信息
std::string  CFighterManager::GetInfoLog()
{
    return GetFormation().GetInfoLog();
}

void CFighterManager::GetDefaultFightFormation(FightFormationInfo& rFightFormationInfo)
{
    GetFormation().GetDefaultFightFormation(rFightFormationInfo);
}

IBattleFighterPtr CFighterManager::GetPetFighter(const TVecFloat& vecAttr)
{
    IBattleFighterPtr pBattle;
    CPetPtr pPet = _oFormationPet.GetPetSlots().GetCurrPet();
    if (pPet)
        pBattle = pPet->ToBattleFighter(vecAttr);
    return pBattle;
}

class EnumerateFighters : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighters(TVecFighterPtr& rvecFighters):_rvecFighters(rvecFighters) {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter)
                    _rvecFighters.push_back(pFighter);
            }
            return true;
        }
        TVecFighterPtr& _rvecFighters;
};

class EnumerateFighters2 : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighters2(map<UINT32, CFighterPtr>& rmapFighter):_rmapFighters(rmapFighter) {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter)
                    _rmapFighters[pFighter->GetBattlePoint()] = pFighter;
            }
            return true;
        }
        map<UINT32, CFighterPtr>& _rmapFighters;
};

bool CFighterManager::GetAllFighters(TVecFighterPtr& rvecFighters)
{
    EnumerateFighters en(rvecFighters);
    _oFighterSlots.enumerate(en);
    return true;
}

// 获取上次组队副本的散仙组合
bool CFighterManager::GetTeamFighters(TVecFighterPtr& rvecFighters)
{
    CGameVar& rCGameVar = _rUser.GetVars();
    UINT32 dwValue1 = rCGameVar.GetVar(NVarDefine::ePlayerTeamPos1Cache);
    UINT32 dwValue2 = rCGameVar.GetVar(NVarDefine::ePlayerTeamPos2Cache);
    UINT32 dwValue3 = rCGameVar.GetVar(NVarDefine::ePlayerTeamPos3Cache);
    if (dwValue1 && dwValue2 && dwValue3)
    {
        CFighterPtr pFighter1 = GetFighterByID(dwValue1);
        CFighterPtr pFighter2 = GetFighterByID(dwValue2);
        CFighterPtr pFighter3 = GetFighterByID(dwValue3);
        if (pFighter1 && pFighter2 && pFighter3)
        {
            rvecFighters.push_back(pFighter1);
            rvecFighters.push_back(pFighter2);
            rvecFighters.push_back(pFighter3);
            return true;
        }
    }

    map<UINT32, CFighterPtr> mapFighters;

    EnumerateFighters2 en(mapFighters);
    _oFighterSlots.enumerate(en);

    for (auto & rPair : mapFighters)
    {
        if (rPair.second && rPair.second->IsMainFighter())
            rvecFighters.push_back(rPair.second);
    }

    for (auto it = mapFighters.rbegin(); it != mapFighters.rend(); ++it)
    {
        if (it->second && !it->second->IsMainFighter())
            rvecFighters.push_back(it->second);
    }

    if (rvecFighters.size() >= 1)
        rCGameVar.SetVar(NVarDefine::ePlayerTeamPos1Cache, rvecFighters[0]->GetID());
    if (rvecFighters.size() >= 2)
        rCGameVar.SetVar(NVarDefine::ePlayerTeamPos2Cache, rvecFighters[1]->GetID());
    if (rvecFighters.size() >= 3)
        rCGameVar.SetVar(NVarDefine::ePlayerTeamPos3Cache, rvecFighters[2]->GetID());
    if (rvecFighters.size() > 3)
        rvecFighters.erase(rvecFighters.begin() + 3, rvecFighters.end());
    return true;
}

void CFighterManager::SetTeamFighters(const TVecUINT16& rvecFighterID, const TVecUINT8& rvecPos)
{
    CGameVar& rCGameVar = _rUser.GetVars();
    for (size_t sz = 0; sz < rvecPos.size(); ++sz)
    {
        switch (rvecPos[sz])
        {
            case 0:
                if (rvecFighterID.size() > rvecPos[sz])
                    rCGameVar.SetVar(NVarDefine::ePlayerTeamPos1Cache, rvecFighterID[sz]);
                break;
            case 1:
                if (rvecFighterID.size() > rvecPos[sz])
                    rCGameVar.SetVar(NVarDefine::ePlayerTeamPos2Cache, rvecFighterID[sz]);
                break;
            case 2:
                if (rvecFighterID.size() > rvecPos[sz])
                    rCGameVar.SetVar(NVarDefine::ePlayerTeamPos3Cache, rvecFighterID[sz]);
                break;
            default:
                break;
        }
    }
}

UINT32 CFighterManager::GetFightersCurrHP()
{
    //注:宠物没有血量
    return GetFormation().GetFightersCurrHP();
}

UINT32 CFighterManager::GetFightersMaxHP()
{
    //注:宠物没有血量
    return GetFormation().GetFightersMaxHP();
}

UINT32 CFighterManager::GetFightersMaxHP2()
{
    //注:宠物没有血量
    return GetFormation().GetFightersMaxHP2();
}

void CFighterManager::RegenAllHP()
{
    //GetFormation().RegenAllHP();
    size_t size = GetFighterSlots().GetSlots();
    for (size_t iIndex = 0; iIndex < size; ++ iIndex)
    {
        if (!GetFighterSlots().HasObj(iIndex))
            continue;
        CFighterPtr pFighter = GetFighterSlots().Get(iIndex);
        if (pFighter && pFighter->GetRecruited())
            pFighter->RegenAllHP();
    }
}

bool CFighterManager::RecoverFighters(TVecBattleFighterPtr& vecBattleFighter)
{
    return GetFormation().RecoverFighters(vecBattleFighter);
}

void CFighterManager::AddFightersCurrHP(UINT32 dwHP)
{
    GetFormation().AddFightersCurrHP(dwHP);
}

void CFighterManager::AddFightersCurrHPPer(float fFactor)
{
    GetFormation().AddFightersCurrHPPer(fFactor);
}

// 玩家属性相关
void CFighterManager::SetDirty(EAttrGroupType eType) 
{ 
    _mapAttrGroupDirty[eType] = true;

    //主将
    if(eType>eAttrGpPlayerBegin && eType<eAttrGpPlayerEnd)
    {
        CPlayerPtr pPlayer = _rUser.GetPlayer();
        if(pPlayer)
        {
            CHeroFighterPtr pMainFighter = pPlayer->GetMainFighter();
            pMainFighter->SetDirty(true, eType, true);
        }
    }

    //散仙
    if(eType>eAttrGpHeroBegin && eType<eAttrGpHeroEnd)
    {
        UINT32 count = _oFighterSlots.GetSlots();

        for(UINT32 i =1; i < count; ++i)
        {
            if (_oFighterSlots.HasObj(i))
            {
                CFighterPtr pFighter = _oFighterSlots.Get(i);
                if(pFighter)
                {
                    pFighter->SetDirty(true,eType,true);
                }
            }

        }
    }

    //所有属性
    if(eType>eAttrGpHeroAndPlayerBegin && eType<eAttrGpHeroAndPlayerEnd) 
    {
        CFormation& rFormation = GetFormation();
        TVecLineup vecLineup;
        rFormation.GetLineup(vecLineup);
        for (size_t i = 0; i < vecLineup.size(); ++i)
        {
            if (vecLineup[i].pFighter)
                vecLineup[i].pFighter->SetDirty(true, eType, true);
        }
    }
}

void CFighterManager::SetDirty(EAttrGroupType eType, const TVecFloat& vecAttr)
{
    SetDirty(eType);
    switch(eType)
    {
        case eAttrGpGuildTech:      //帮派技能属性加成
            VECATTR_RESET(_mapAttrGroupCache[eType]);
            _mapAttrGroupCache[eType] += vecAttr;
            break;
        case eAttrGpTripod:      //九疑鼎属性加成
            VECATTR_RESET(_mapAttrGroupCache[eType]);
            _mapAttrGroupCache[eType] += vecAttr;
            break;
        default:
            break;
    }
}

bool CFighterManager::IsDirty(EAttrGroupType eType) const   
{ 
    return _mapAttrGroupDirty[eType];
}

TVecFloat CFighterManager::GetAllAttr() const
{
    TVecFloat vecAttr;
    VECATTR_RESET(vecAttr);
    RebuildGroupAttr();
    for (UINT8 byIndex = EFIGHTATTR_MIN; byIndex < EFIGHTATTR_MAX; ++byIndex)
    {
        for (auto it = _mapAttrGroup.begin(); it != _mapAttrGroup.end(); ++it)
        {
            VECATTR_ADD(vecAttr, byIndex, (it->second)[byIndex]);
        }
    }
    return vecAttr;
}

TVecFloat CFighterManager::GetGroupAttr(EAttrGroupType eType) const
{
    RebuildGroupAttr(eType);
    TVecFloat vecAttr;
    VECATTR_RESET(vecAttr);
    for (UINT8 byIndex = EFIGHTATTR_MIN; byIndex < EFIGHTATTR_MAX; ++byIndex)
    {
        VECATTR_ADD(vecAttr, byIndex, _mapAttrGroup[eType][byIndex]);
    }
    return vecAttr;
}

bool CFighterManager::RebuildGroupAttr() const
{
    bool bRet = false;
    for (auto it = _mapAttrGroup.begin(); it != _mapAttrGroup.end(); ++it)
    {
        bRet = RebuildGroupAttr(it->first)? true:bRet;
    }
    return bRet;
}

// 各个类型的属性加成更新
bool CFighterManager::RebuildGroupAttr(EAttrGroupType eType) const
{
    if (!IsDirty(eType))
        return false;

    VECATTR_RESET(_mapAttrGroup[eType]);
    switch(eType)
    {
        case eAttrGpTrumpHalo: //法宝光环属性加成
            GetTrumpSlots().GetHaloAttr(_mapAttrGroup[eType]);
            break;
        case eAttrGpTrumpExtra: //法宝附加属性加成
            GetTrumpSlots().GetExtraAttr(_mapAttrGroup[eType]);
            break;
        case eAttrGpTrumpActive: //法宝激活属性加成
            GetTrumpSlots().GetActiveAttr(_mapAttrGroup[eType]);
            break;
        case eAttrGpCitta: //天书属性加成
            GetCittaSlots().GetAddAttr(_mapAttrGroup[eType]);
            break;
        case eAttrGpFashion:        //时装属性加成
            GetFashionSlots().GetAddAttr(_mapAttrGroup[eType]);
            break;
        case eAttrGpHorse: //坐骑加成
            {
                CPlayerPtr pPlayer = _rUser.GetPlayer();
                if(pPlayer)
                {
                    CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();
                    if(pHorseMgr)
                    {
                        pHorseMgr->RebuildAttr();
                        _mapAttrGroup[eType] += pHorseMgr->GetAttrVec();
                    }
                }
            }
            break;
        case eAttrBeauty:
            {
                CPlayerPtr pPlayer = _rUser.GetPlayer();
                if(pPlayer)
                {
                    CBeautyMgrPtr pBeautyMgr = pPlayer->GetBeautyMgr();
                    if(pBeautyMgr)
                    {
                        _mapAttrGroup[eType] += pBeautyMgr->GetAttrVec();
                    }
                }

            }
            break;
        case eAttrGpAchievement: //成就属性加成
            {
                CPlayerPtr pPlayer = _rUser.GetPlayer();
                if(pPlayer)
                {
                    CAchievementMgrPtr pAchievementMgr = pPlayer->GetAchievementMgr();
                    if(pAchievementMgr)
                    {
                        pAchievementMgr->RebuildAttr();
                        _mapAttrGroup[eType] += pAchievementMgr->GetAttrVec();
                    }
                }
            }
            break;
        case eAttrGpCollection: //收集属性加成
            {
                CPlayerPtr pPlayer = _rUser.GetPlayer();
                if(pPlayer)
                {
                    CCollectionMgrPtr pCollectionMgr = pPlayer->GetCollectionMgr();
                    if(pCollectionMgr)
                    {
                        pCollectionMgr->RebuildAttr();
                        _mapAttrGroup[eType] += pCollectionMgr->GetAttrVec();
                    }
                }
            }
            break;
        case eAttrGpShushanBattle: //蜀山论剑属性加成
            {
                ShushanBattle.GetAddAttr(_mapAttrGroup[eType], _rUser.GetUserID());
            }
            break;
        case eAttrGpBag:        //背包属性加成
            {
                CPlayerPtr pPlayer = _rUser.GetPlayer();
                if(pPlayer)
                {
                    pPlayer->GetPackUnlockAttr(_mapAttrGroup[eType]);
                }
            }
            break;
        case eAttrGpTitle: // 称号属性加成
            {
                CPlayerPtr pPlayer = _rUser.GetPlayer();
                CTitlePkg& rTitlePkg = pPlayer->GetTitlePkg();
                rTitlePkg.GetAllTitleAttr(_mapAttrGroup[eType]);
            }
            break;
        case eAttrGpFormation:   //阵形属性加成
            {
                /*
                const CFormationSlots& rFormation = GetFormation();
                TVecFloat rvec = rFormation.GetAttrVec();
                _mapAttrGroup[eType] = rvec;
                */
            }
            break;
        case eAttrGpPet:        //阵灵属性加成
            {
                /*
                const CPetSlots& rPet = _oFormationPet.GetPetSlots();
                TVecFloat rvec = rPet.GetAttrVec();
                _mapAttrGroup[eType] = rvec;
                rPet.UpdateRankInfo();
                */
            }
            break;
        case eAttrGpBeastSoul:
            {
                const CBeastSoul& rBeastSoul = _oFormationPet.GetBeastSoul();
                _mapAttrGroup[eType] = rBeastSoul.GetAttrVec();
            }
            break;
        case eAttrGpGuildTech:  // 帮派技能属性加成（已在SetDirty更新，这里不需要操作）
            {
                _mapAttrGroup[eType] += _mapAttrGroupCache[eType];
            }
            break;
        case eAttrGpBuffer: //外部buffer属性加成
            {
                CPlayerPtr pPlayer = _rUser.GetPlayer();

                _mapAttrGroup[eType] += pPlayer->GetBattleAttrVec((UINT8)_eBattleType );

                _mapAttrGroup[eType] += pPlayer->GetBufferAttrVec();
            }
            break;
        case eAttrGpTripod:  // 九疑鼎属性加成（已在SetDirty更新，这里不需要操作）
            {
                _mapAttrGroup[eType] += _mapAttrGroupCache[eType];
            }
            break;
        case eAttrGpFighterCombination: //散仙组合属性加成
            {
                for (size_t iSlot = 0; iSlot < static_cast<size_t>(_oHeroCombinationSlots.GetSlots()); ++ iSlot)
                {
                    CHeroFighterCombinationPtr pFgtComb = _oHeroCombinationSlots.Get(iSlot);
                    if (!pFgtComb)
                        continue;
                    pFgtComb->AppendAttr(_mapAttrGroup[eType]);
                }
            }
            break;
        default:
            break;
    }
    _mapAttrGroupDirty[eType] = false;
    return true;
}

//获取增加到主将的属性
void CFighterManager::GetPlayerAddAttr(TVecFloat&  vecAttr)
{
    for(UINT32 i = eAttrGpPlayerBegin+1; i < eAttrGpPlayerEnd; ++i)
    {
        vecAttr += this->GetGroupAttr((EAttrGroupType)i);
    }
}
//获得增加到所有单位的属性
void CFighterManager::GetHeroAndPlayerAddAttr(TVecFloat& vecAttr)
{
    for(UINT32 i = eAttrGpHeroAndPlayerBegin + 1; i < eAttrGpHeroAndPlayerEnd; ++i)
    {
        vecAttr += this->GetGroupAttr((EAttrGroupType)i);
    }
}

//获得增加到所有单位的属性
void CFighterManager::GetHeroAndPlayerAddAttrWithoutBuffer(TVecFloat& vecAttr)
{
    for(UINT32 i = eAttrGpHeroAndPlayerBegin + 1; i < eAttrGpHeroAndPlayerEnd; ++i)
    {
        if (static_cast<EAttrGroupType>(i) == eAttrGpBuffer)
            continue;
        vecAttr += this->GetGroupAttr((EAttrGroupType)i);
    }
}

//获取增加到散仙的属性
void CFighterManager::GetHeroAddAttr(TVecFloat&  vecAttr)
{
    for(UINT32 i = eAttrGpHeroBegin + 1; i < eAttrGpHeroEnd; ++i)
    {
        vecAttr += this->GetGroupAttr((EAttrGroupType)i);
    }
}

class EnumerateFighter4AddExp : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighter4AddExp(UINT64 qwExp, bool bNodify) : _qwExp(qwExp), _bNotify(bNodify) {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter && pFighter->GetRecruited() && pFighter->GetPos() >= 0)
                    pFighter->AddExp(_qwExp, _bNotify);
            }
            return true;
        }

    public:
        UINT64 _qwExp;
        bool _bNotify;
};

class EnumerateFighter4AddToLevel : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighter4AddToLevel(UINT16 wLevel) : _wLevel(wLevel){}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter && pFighter->GetRecruited() && pFighter->GetPos() >= 0)
                {
                    UINT64 qwOldExp = pFighter->GetExp();
                    UINT64 qwNewExp = CExpMgr::GetLevelMin(_wLevel - 1);
                    if (!qwNewExp && _wLevel > 1)
                        qwNewExp = CExpMgr::GetLevelMin(--_wLevel);
                    if (qwOldExp < qwNewExp)
                    {
                        pFighter->AddExp(qwNewExp - qwOldExp, true);
                        LOG_WRN << "AddExp " << qwOldExp << " + " << qwNewExp - qwOldExp << ".";
                    }
                }
            }
            return true;
        }

    public:
        UINT16 _wLevel;
        bool _bNotify;
};

class EnumerateFighterGetRecruitedIDList : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighterGetRecruitedIDList(TVecUINT16& vecFighterID) : vecFighterID(vecFighterID) {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter && pFighter->GetRecruited())
                    vecFighterID.push_back(pFighter->GetID());
            }
            return true;
        }

    public:
        TVecUINT16 vecFighterID;
};

void CFighterManager::AddExp(UINT64 qwExp, bool bNotify/* = true*/)
{
    EnumerateFighter4AddExp en(qwExp, bNotify);
    _oFighterSlots.enumerate(en);
}

void CFighterManager::AddToLevel(UINT16 wLevel)
{
    EnumerateFighter4AddToLevel en(wLevel);
    _oFighterSlots.enumerate(en);
}

void CFighterManager::GetRecruitedFigterIDList(TVecUINT16& vecFighterID)
{
    EnumerateFighterGetRecruitedIDList en(vecFighterID);
    _oFighterSlots.enumerate(en);
}

void CFighterManager::FighterInitLevelAttr()
{
    UINT32 count = _oFighterSlots.GetSlots();

    for(UINT32 i = 0; i < count; ++i)
    {
        if (_oFighterSlots.HasObj(i))
        {
            CFighterPtr pFighter = _oFighterSlots.Get(i);
            if (pFighter && pFighter->GetRecruited())
                pFighter->InitFighterAttr();
        }
    }
}

bool CFighterManager::FindHeroFighterSkillAndTrump(UINT32 skillOrTrumpID)
{
    UINT32 count = _oFighterSlots.GetSlots();

    for(UINT32 i =1; i < count; ++i)
    {
        if (_oFighterSlots.HasObj(i))
        {
            CFighterPtr pFighter = _oFighterSlots.Get(i);
            if (pFighter && pFighter->GetRecruited())
            {
                TVecUINT32 vecSkillID;
                dynamic_pointer_cast<CHeroFighter>(pFighter)->GetAllSkillsID(vecSkillID);
                for (auto it = vecSkillID.begin(); it != vecSkillID.end(); ++it)
                {
                    if (skillOrTrumpID == SKILL_ID(*it))
                        return true;
                }
            }
        }
    }
    return false;
}

UINT16 CFighterManager::GetHeroNum()
{
    UINT16 wCount = _oFighterSlots.GetUsedCount();
    return wCount >= 1? wCount-1:0;
}

UINT32 CFighterManager::GetBattlePoint()
{
    UINT32 dwBattlePoint = 0;
    CFormation& rFormation = GetFormation();
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!vecLineup[i].pFighter)
            continue;
        dwBattlePoint += vecLineup[i].pFighter->GetBattlePoint();
    }
    return dwBattlePoint + GetTrumpSkillBattlePoint();
}

UINT32 CFighterManager::GetHeroFighterBattlePoint(UINT16 wFighterID)
{
    CFormation& rFormation = GetFormation();
    UINT32 dwBattlePoint = 0;
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!vecLineup[i].pFighter)
            continue;
        if (vecLineup[i].pFighter->GetID() == wFighterID)
        {
            dwBattlePoint = vecLineup[i].pFighter->GetBattlePoint();
            break;
        }
    }
    return dwBattlePoint;
}

// XXX: 计算散仙总战斗力(渡劫和心法除外)
UINT32 CFighterManager::CalcHeroFighterBattlePoint()
{
    return GetBattlePoint() - GetDujieBattlePoint() - GetXinfaBattlePoint();
}

//计算仙女系统战斗力
UINT32 CFighterManager::GetBeautyBattlePoint()
{
    TVecFloat vecAttr = GetGroupAttr(eAttrBeauty);
    return BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
}

//计算法宝战斗力
UINT32 CFighterManager::GetTrumpBattlePoint()
{
    return GetTrumpAttrBattlePoint() + GetTrumpSkillBattlePoint();
}

//计算法宝属性战斗力
UINT32 CFighterManager::GetTrumpAttrBattlePoint()
{
    UINT32 dwBattlePoint = 0;

    TVecFloat vecAttr;
    VECATTR_RESET(vecAttr);

    vecAttr += GetGroupAttr(eAttrGpTrumpHalo);
    vecAttr += GetGroupAttr(eAttrGpTrumpExtra);
    vecAttr += GetGroupAttr(eAttrGpTrumpActive);

    dwBattlePoint += BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
    return dwBattlePoint;
}

//计算法宝技能战斗力
UINT32 CFighterManager::GetTrumpSkillBattlePoint()
{
    UINT32 dwBattlePoint = 0;
    CTrumpSlots& rTrumpSlots = GetTrumpSlots();

    TVecUINT32 vecSkillsID;
    UINT32 dwPeerless = rTrumpSlots.GetPeerlessSkill();     //法宝无双技能
    if (dwPeerless)
        vecSkillsID.push_back(dwPeerless);
    rTrumpSlots.GetPassiveSkills(vecSkillsID);   //法宝被动技能

    dwBattlePoint += BattlePointCalucator.CalcSkillBattlePoint(vecSkillsID);
    return dwBattlePoint;
}

//计算坐骑战斗力
UINT32 CFighterManager::GetHorseBattlePoint()
{
    TVecFloat vecAttr = GetGroupAttr(eAttrGpHorse);
    return BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
}

//计算渡劫战斗力
UINT32 CFighterManager::GetDujieBattlePoint()
{
    TVecFloat vecAttr;
    CFormation& rFormation = GetFormation();
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!vecLineup[i].pFighter)
            continue;
        CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter);
        if (!pFighter)
            continue;
        vecAttr += pFighter->GetDujieAttr();
    }
    return BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
}

//计算心法战斗力
UINT32 CFighterManager::GetXinfaBattlePoint()
{
    TVecFloat vecAttr;
    CFormation& rFormation = GetFormation();
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!vecLineup[i].pFighter)
            continue;
        CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter);
        if (!pFighter)
            continue;
        vecAttr += pFighter->GetXinFas().GetHeroFighterXinFaAttr();
    }
    return BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
}

//计算帮派战斗力
UINT32 CFighterManager::GetGuildBattlePoint()
{
    TVecFloat vecAttr = GetGroupAttr(eAttrGpGuildTech);
    return BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
}

//计算Buff战斗力
UINT32 CFighterManager::GetBufferBattlePoint()
{
    TVecFloat vecAttr = GetGroupAttr(eAttrGpBuffer);
    return BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
}

class EnumerateFighterMaxBPFighter : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighterMaxBPFighter():_qwInstID(0), _dwMaxBattlePoint(0) {}
        UINT32 GetMaxBattlePoint() const { return _dwMaxBattlePoint; }
        UINT64 GetInstID() const { return _qwInstID; }

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter && pFighter->IsHeroFighter())
                {
                    UINT32 dwBattlePoint = dynamic_pointer_cast<CHeroFighter>(pFighter)->GetBattlePoint();
                    if (dwBattlePoint > _dwMaxBattlePoint)
                    {
                        _dwMaxBattlePoint = dwBattlePoint;
                        _qwInstID = pFighter->GetInstID();
                    }
                }
            }
            return true;
        }
    private:
        UINT64 _qwInstID;
        UINT32 _dwMaxBattlePoint;
};

class EnumerateFighterUpdateRankInfo : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighterUpdateRankInfo() {}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter && pFighter->IsHeroFighter())
                    dynamic_pointer_cast<CHeroFighter>(pFighter)->UpdateRankInfo();
            }
            return true;
        }
};

void CFighterManager::UpdateHeroFighterRankInfo()
{
    CFormation& rFormation = GetFormation();
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);
    UINT16 wMainFgtID = GetMainFighter() ? GetMainFighter()->GetID() : 0;
    UINT32 dwMaxBattlePoint = 0;
    size_t szIndex = 255;
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!vecLineup[i].pFighter)
            continue;
        if (vecLineup[i].pFighter->GetID() == wMainFgtID)
            continue;
        if ((vecLineup[i].pFighter)->IsHeroFighter())
        {
            CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter);
            UINT32 dwBattlePoint = pFighter->GetBattlePoint();
            if (dwBattlePoint > dwMaxBattlePoint)
            {
                szIndex = i;
                dwMaxBattlePoint = dwBattlePoint;
            }
        }
    }
    EnumerateFighterMaxBPFighter en;
    _oFighterSlots.enumerate(en);

    CHeroFighterPtr pFighter;
    if (en.GetMaxBattlePoint() > dwMaxBattlePoint)
        pFighter = dynamic_pointer_cast<CHeroFighter>(_oFighterSlots.GetFighterByInstID(en.GetInstID()));
    else if (szIndex < 255)
        pFighter = dynamic_pointer_cast<CHeroFighter>(vecLineup[szIndex].pFighter);
    if (pFighter)
        pFighter->UpdateRankInfo();
    /*
       EnumerateFighterUpdateRankInfo en;
       _oFighterSlots.enumerate(en);
       */
}

class EnumerateFighterSuper : public Enumerator<typename CFighterSlots::value_type>
{
    public:
        typedef CFighterSlots::value_type value_type;

    public:
        EnumerateFighterSuper(){}

        bool operator()(value_type* obj)
        {
            if (obj && std::get<1>(*obj))
            {
                const CFighterPtr& pFighter = std::get<2>(*obj);
                if (pFighter && pFighter->IsHeroFighter())
                    dynamic_pointer_cast<CHeroFighter>(pFighter)->Super();
            }
            return true;
        }
};

// 新手阵灵阵型加速
void CFighterManager::FormationBoost(UINT32 dwMode)
{
    GetFormationPet().GetPetSlots().AdoptPet(1, true, true);
    GetFormationPet().GetPetSlots().ActivePet(1, 1);
}

// 机器人阵灵阵型加速
void CFighterManager::RobotFormationBoost(UINT32 dwMode)
{
    bool bSuc = false;
    do
    {
        UINT16 wActiveID = CRandom::RandInt(1,13);
        GetFormationPet().GetPetSlots().AdoptPet(wActiveID, true, true);
        bSuc = GetFormationPet().GetPetSlots().ActivePet(wActiveID, 1);
    }while(!bSuc);
}

// 阵灵阵型变得超级牛逼
void CFighterManager::FormationSuper()
{

}

// 散仙变得超级牛逼
void CFighterManager::HeroFighterBoost(UINT32 dwMode)
{
    CFormation& rFormation = GetFormation();
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!vecLineup[i].pFighter)
            continue;
        switch(vecLineup[i].pFighter->GetID())
        {
            case 100:
                dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter)->SetLevel(30);
                break;
            case 101:
                dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter)->SetLevel(29);
                break;
            case 102:
                dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter)->SetLevel(23);
                break;
        }
    }
}

void CFighterManager::OnFighterColorChange(UINT8 byStar)
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        
        TVecFighterPtr rvecFighters;
        GetAllFighters(rvecFighters);
        UINT32 dwCount = 0;
        for(size_t i = 0; i < rvecFighters.size(); i++)
        {
            if(rvecFighters[i] && (rvecFighters[i]->GetStar()>= byStar))
            {
                dwCount++;
            }

            //LOG_CRI<<"wId:"<<rvecFighters[i]->GetID()<<" star:"<<rvecFighters[i]->GetStar();
        }
 
        TVecINT32 vecParam;
        vecParam.push_back(byStar);
        vecParam.push_back(dwCount);
        pPlayer->OnEvent(eEventType_FighterCollected,vecParam);
    }

}

// ===  FUNCTION  ======================================================================
//         Name:  HeroFighterSuper
//  Description:  散仙变得超级牛逼
// =====================================================================================
void CFighterManager::HeroFighterSuper()
{
    // 先招募配置里指定的散仙们
    const TVecUINT16& rvecFighterID = CBoostMgr::Instance().GetFighterID(ECAREER_ALL);

    for (auto &rID : rvecFighterID)
    {
        GetFighterForce(rID);
    }

    CFormation& rFormation = GetFormation();
    TVecLineup vecLineup;
    rFormation.GetLineup(vecLineup);
    UINT16 wMainFgtID = GetMainFighter() ? GetMainFighter()->GetID() : 0;
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!vecLineup[i].pFighter)
            continue;
        if (vecLineup[i].pFighter->GetID() == wMainFgtID)
            continue;
        if ((vecLineup[i].pFighter)->IsHeroFighter())
            dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter)->Super();
    }

    EnumerateFighterSuper en;
    _oFighterSlots.enumerate(en);
}		// -----  end of function HeroFighterSuper  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SuperBoostObjects
//  Description:  类里面的boost对象都变得超级牛逼
// =====================================================================================
void CFighterManager::SuperBoostObjects ()
{
    HeroFighterSuper();

    GetFormationPet().GetPetSlots().SuperBoostObjects();
}		// -----  end of function SuperBoostObjects  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFashionSlots
//  Description:  获得时装槽
// =====================================================================================
CFashionSlots&  CFighterManager::GetFashionSlots ()
{
    return _oFashions;
}		// -----  end of function GetFashionSlots  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFashionSlots
//  Description:  获得时装槽
// =====================================================================================
const CFashionSlots&  CFighterManager::GetFashionSlots () const
{
    return _oFashions;
}		// -----  end of function GetFashionSlots  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTrumpSlots
//  Description:  获得法宝槽
// =====================================================================================
CTrumpSlots& CFighterManager::GetTrumpSlots ()
{
    return _oTrumps;
}		// -----  end of function GetTrumpSlots  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTrumpSlots
//  Description:  获得法宝槽
// =====================================================================================
const CTrumpSlots& CFighterManager::GetTrumpSlots () const
{
    return _oTrumps;
}		// -----  end of function GetTrumpSlots  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCittaSlots
//  Description:  获得心法槽（天书）
// =====================================================================================
CCittaSlots& CFighterManager::GetCittaSlots ()
{
    return _oCittas;
}		// -----  end of function GetCittaSlots  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCittaSlots
//  Description:  获得心法槽（天书）
// =====================================================================================
const CCittaSlots& CFighterManager::GetCittaSlots () const
{
    return _oCittas;
}		// -----  end of function GetCittaSlots  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  GetDraw
//  Description:  获取求签数据类
// =====================================================================================
CDraw& CFighterManager::GetDraw ()
{
    return _oDraw;
}		// -----  end of function GetDraw  ----- //


CEquipTrumpPtr CFighterManager::GetEquipTrumpByInstID(UINT64  qwInstID)
{
    CStore* pStore = _rUser.GetStoreByType(eStorePack);
    if(pStore)
    {
        CItemPtr pItem = pStore->GetItem(qwInstID);
        if(pItem)
        {
            return dynamic_pointer_cast<CEquipTrump>(pItem); 
        }
    }

    TVecFighterPtr rvecFighters;
    GetAllFighters(rvecFighters);

    for(size_t i = 0; i < rvecFighters.size(); i++)
    {
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(rvecFighters[i]);
        if(pHeroFighter)
        {
            CEquipTrumpSlot& rEquipTrumpSlot = pHeroFighter->GetEquipTrumpSlot(); 

            CItemPtr pItem = rEquipTrumpSlot.GetSlotByInstID(qwInstID);
            if(pItem)
            {
                return dynamic_pointer_cast<CEquipTrump>(pItem);
            }

        }
    }

    return NULL;
}

//获取一定条件的法宝数量
UINT32 CFighterManager::GetEquipTrumpCount(UINT8 byMinQuality,UINT8 byMinInsifyLevel)
{
    UINT32 dwCount = 0;
    CStore* pStore = _rUser.GetStoreByType(eStorePack);
    if(pStore)
    {
        dwCount += pStore->GetEquipTrumpCount(byMinQuality,byMinInsifyLevel);
    }

    TVecFighterPtr rvecFighters;
    GetAllFighters(rvecFighters);

    for(size_t i = 0; i < rvecFighters.size(); i++)
    {
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(rvecFighters[i]);
        if(pHeroFighter)
        {
            CEquipTrumpSlot& rEquipTrumpSlot = pHeroFighter->GetEquipTrumpSlot(); 

            dwCount += rEquipTrumpSlot.GetEquipTrumpCount(byMinQuality,byMinInsifyLevel);
           
        }
    }

    return dwCount;

}

//获取一定条件的宝石数量
UINT32 CFighterManager::GetStoneCount(UINT8 byMinLevel)
{
    UINT32 dwCount = 0;
    CStore* pStore = _rUser.GetStoreByType(eStorePack);
    if(pStore)
    {
        dwCount += pStore->GetStoneCount(byMinLevel);
    }

    TVecFighterPtr rvecFighters;
    GetAllFighters(rvecFighters);

    for(size_t i = 0; i < rvecFighters.size(); i++)
    {
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(rvecFighters[i]);
        if(pHeroFighter)
        {

            CGemstoneSlots& rGemstoneSlot = pHeroFighter->GetGemstoneSlots();
            dwCount += rGemstoneSlot.GetStoneCount(byMinLevel);
           
        }
    }

    return dwCount;

}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

