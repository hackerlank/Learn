
#include "stdafx.h"
#include "Protocols.h"
#include "HeroFighterSkills.h"
#include "FighterMgr.h"
#include "Player.h"
#include "Fighter.h"
#include "RTime.h"
#include "Skill.h"
#include "PassiveSkill.h"
#include "SkillAttr.h"

const UINT8 g_byPeerlessSkillIndex = 3;
const UINT8 g_byPassiveSkillStartIndex = 4;

CHeroFighterSkills::CHeroFighterSkills()
{
}

CHeroFighterSkills::~CHeroFighterSkills()
{
}

void CHeroFighterSkills::SetUser(const CUserPtr& pUser) 
{ 
    _pUser = pUser; 
}

CUserPtr CHeroFighterSkills::GetUser() const 
{ 
    return _pUser.lock(); 
}

void CHeroFighterSkills::SetFighter(const CFighterPtr& pFighter) 
{ 
    _pFighter = pFighter; 
}

CFighterPtr CHeroFighterSkills::GetFighter() const 
{ 
    return _pFighter.lock(); 
}

void CHeroFighterSkills::GetAllUpSkills(TVecUINT32& vecSkills) const
{
    _oUpSkills.GetAllSkills(vecSkills);
}

void CHeroFighterSkills::GetActiveSkills(TVecUINT32& vecSkills) const
{
    for (int i = 0; i < g_byPeerlessSkillIndex; ++ i)
    {
        UINT32 dwSkillID = _oUpSkills.HasObj(i) ? _oUpSkills.Get(i) : 0;
        if (dwSkillID)
            vecSkills.push_back(dwSkillID);
    }
}

void CHeroFighterSkills::GetPassiveSkills(TVecUINT32& vecSkills) const
{
    vecSkills.insert(vecSkills.end(), _vecPassiveSkill.begin(), _vecPassiveSkill.end());
}

UINT32 CHeroFighterSkills::GetPeerLessID() const
{
    return _oUpSkills.HasObj(g_byPeerlessSkillIndex) ? _oUpSkills.Get(g_byPeerlessSkillIndex) : 0;
}

void CHeroFighterSkills::GetAllCombineSkills(TVecUINT32& vecSkills) const
{
    for (size_t i = 0; i < _vecCombinationSkillID.size(); ++ i)
    {
        vecSkills.push_back(_vecCombinationSkillID[i]);
    }
}

ESkillResult CHeroFighterSkills::UpgradeActiveSkill(UINT32 dwSkillID)
{
    CUserPtr pUser = GetUser();
    CFighterPtr pFighter = GetFighter();
    if (!dwSkillID || !pUser || !pFighter)
        return eSkillFailed;

    int iSlot = _oUpSkills.GetSkillSlot(dwSkillID);
    if (iSlot == INVALID_SLOT)
        return eSkillNotExist;

    UINT16 wLevel = SKILL_LEVEL(dwSkillID);

    SSkillPtr pSkill = CSkillMgr::Instance().GetSkill(SKILL_ID(dwSkillID));
    if (!pSkill || pSkill->_vecEffectID.empty())
        return eSkillFailed;

    SSkillEfPtr pSkillEffectCfg = SkillMgr.GetSkillEf(SkillMgr.GetSkillIDQualityLevel(pSkill->_vecEffectID[0], wLevel));
    if (!pSkillEffectCfg)
        return eSkillLevelMax;

    if (SKILL_LEVEL(pSkillEffectCfg->_dwID) < wLevel)
        return eSkillLevelMax;

    if (pSkillEffectCfg->_byNeedLevel && pUser->GetPlayer()->GetLevel() < pSkillEffectCfg->_byNeedLevel)
        return eSkillLevelErr;

    SSkillEfPtr pSkillEffectCfgNext = SkillMgr.GetSkillEf(SkillMgr.GetSkillIDQualityLevel(pSkill->_vecEffectID[0], wLevel+1));
    if (!pSkillEffectCfgNext)
        return eSkillLevelMax;

    if (pSkillEffectCfg->_wCostType == EMONEY_NONE || !pSkillEffectCfg->_dwCost)
        return eSkillFailed;

    if (!pUser->CanSubMoney((EMoneyType)pSkillEffectCfg->_wCostType, pSkillEffectCfg->_dwCost))
        return eItemNotEnough;
    
    if (pSkillEffectCfg->_wCostType < MAX_MONEY_TYPE && pSkillEffectCfg->_dwCost)
        pUser->SubMoney((EMoneyType)pSkillEffectCfg->_wCostType, pSkillEffectCfg->_dwCost,NLogDataDefine::ItemTo_HeroSkillUpgrade);
    
    ++dwSkillID;
    _oUpSkills.Set(iSlot, dwSkillID);

    Update2DB(eOpUpdate);
    pFighter->SetDirty(true);

    //记入LogServer日志
    WriteFighterLog(eOptType_Skill, SKILL_ID(dwSkillID), wLevel + 1, pFighter->GetID());

    //散仙技能升级事件
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pFighter->GetID());
        vecParam.push_back(dwSkillID);

        //主动、天赋技能
        TVecUINT32 vecSkills;
        pFighter->GetAllSkillsID(vecSkills);
        for (auto it = vecSkills.begin(); it!=vecSkills.end(); ++it)
        {
            vecParam.push_back(SKILL_LEVEL(*it));
        }

        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_FighterSkillUpgrade, vecParam);
        
        pUser->GetTaskPkg().OnAction(*pPlayer, eProcessAction_SpecialHeroSkillLvl); 
    }

    return eSkillSucc;
}

ESkillResult CHeroFighterSkills::UpgradePassiveSkill(UINT32 dwSkillID)
{
    CUserPtr pUser = GetUser();
    CFighterPtr pFighter = GetFighter();
    if (!dwSkillID || !pUser || !pFighter)
        return eSkillFailed;

    UINT32 dwNextSkillID = 0;
    for (auto rID : _vecPassiveSkill)
    {
        if (rID == dwSkillID)
        {
            dwNextSkillID = dwSkillID + 1;
            break;
        }
    }
    if (!dwNextSkillID)
        return eSkillNotExist;

    const STalentSkillCFG* pCFG = CPassiveSkillMgr::Instance().GetCFG(dwSkillID);
    if (!pCFG)
        return eSkillLevelMax;

    if (pCFG->_needLvl && pUser->GetPlayer()->GetLevel() < pCFG->_needLvl)
        return eSkillLevelErr;

    const STalentSkillCFG* pNextCFG = CPassiveSkillMgr::Instance().GetCFG(dwNextSkillID);
    if (!pNextCFG)
        return eSkillLevelMax;

    if (pCFG->_skillCostType == EMONEY_NONE || !pCFG->_skillCost)
        return eSkillFailed;

    if (!pUser->CanSubMoney((EMoneyType)pCFG->_skillCostType, pCFG->_skillCost))
        return eItemNotEnough;
    
    if (pCFG->_skillCostType < MAX_MONEY_TYPE && pCFG->_skillCost)
        pUser->SubMoney((EMoneyType)pCFG->_skillCostType, pCFG->_skillCost,NLogDataDefine::ItemTo_HeroSkillUpgrade);
    
    for (auto& rID : _vecPassiveSkill)
    {
        if (rID == dwSkillID)
        {
            ++rID;
            break;
        }
    }

    UpdatePassiveSkill2DB(eOpUpdate);
    pFighter->SetDirty(true);

    //记入LogServer日志
    WriteFighterLog(eOptType_PassiveSkill, SKILL_ID(dwSkillID), SKILL_LEVEL(dwNextSkillID), pFighter->GetID());

    // TODO: 散仙技能升级事件
#if 0
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pFighter->GetID());
        vecParam.push_back(dwSkillID);

        //主动、天赋技能
        TVecUINT32 vecSkills;
        pFighter->GetAllSkillsID(vecSkills);
        for (auto & rID : vecSkills)
        {
            vecParam.push_back(SKILL_LEVEL(rID));
        }

        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_FighterSkillUpgrade, vecParam);
        
        pUser->GetTaskPkg().OnAction(*pPlayer, eProcessAction_SpecialHeroSkillLvl); 
    }
#endif

    return eSkillSucc;
}

ESkillResult CHeroFighterSkills::UpSkill(UINT32 dwSkillID, int iSlot)
{
    // FIXME: 这里没检查对应的槽是否解锁
    CUserPtr pUser = GetUser();
    CFighterPtr pFighter = GetFighter();
    if (!dwSkillID || !pUser || !pFighter)
        return eSkillFailed;

    int iSlotUp = _oUpSkills.GetSkillSlot(dwSkillID);
    if (iSlotUp == iSlot)
        return eSkillSucc;

    if (iSlotUp == INVALID_SLOT)
        return eSkillFailed;
    
    if (_oUpSkills.HasObj(iSlot))
    {
        UINT32 yadwSkillID = _oUpSkills.Get(iSlot);
        _oUpSkills.Swap(iSlotUp, iSlot);
        if (yadwSkillID)
            pUser->SendPkg(g_FighterProtS.BuildPkg_SkillUpNotify(yadwSkillID, iSlotUp));
        pUser->SendPkg(g_FighterProtS.BuildPkg_SkillUpNotify(dwSkillID, iSlot));
    }
    else
    {
        _oUpSkills.Move(iSlotUp, iSlot);
        _oUpSkills.Set(iSlotUp, 0);
        pUser->SendPkg(g_FighterProtS.BuildPkg_SkillUpNotify(dwSkillID, iSlot));
    }

    Update2DB(eOpUpdate);

    pFighter->SetDirty(true);

    //Event事件
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (pPlayer)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pFighter->GetID());
        for (UINT8 i = 0; i < _oUpSkills.GetSlots(); ++i)
        {
            if (_oUpSkills.HasObj(i))
                vecParam.push_back(_oUpSkills.Get(i));
        }
        pPlayer->OnEvent(eEventType_FighterSkillExchange, vecParam);
    }
    return eSkillSucc;
}

void CHeroFighterSkills::UpSkillFromDB(UINT32 dwSkillID, int iSlot)
{
    if (dwSkillID)
        _oUpSkills.Set(iSlot, dwSkillID);
}

void CHeroFighterSkills::UpPassiveSkillFromDB(UINT32 dwSkillID, UINT32 dwSkillQuality, UINT32 dwSkillLevel)
{
    UINT32 dwPassiveSkill = SKILLID_QUALITY_LEVEL(dwSkillID, dwSkillQuality, dwSkillLevel);
    const STalentSkillCFG* pCFG = CPassiveSkillMgr::Instance().GetCFG(dwPassiveSkill);
    if (!pCFG)
    {
        LOG_CRI << "NO PassiveSkill(" << dwPassiveSkill << ").";
        return;
    }
    for (auto & rID : _vecPassiveSkill)
    {
        if (SKILL_ID(rID) == SKILL_ID(dwPassiveSkill))
        {
            LOG_CRI << "Same PassiveSkill(" << dwPassiveSkill << ").";
            rID = dwPassiveSkill > rID ? dwPassiveSkill : rID;
            return;
        }
    }
    _vecPassiveSkill.push_back(dwPassiveSkill);
}

void CHeroFighterSkills::Update2DB(EDataChange eDataChange)
{
    UINT64 qwUserID = 0;
    UINT64 qwFighterID = 0;

    if (GetUser())
        qwUserID = GetUser()->GetUserID();

    if (GetFighter())
        qwFighterID = GetFighter()->GetInstID();

    if (!qwFighterID)
    {
        LOG_WRN << "Have no Fighter!!!";
        return;
    }

    string strData;
    COutArchive iar(strData);
    SSkillDBInfo oSkillDBInfo;

    memset(&oSkillDBInfo, 0x00, sizeof(oSkillDBInfo));
    oSkillDBInfo.qwOwnerID = qwFighterID;
    oSkillDBInfo.dwUpSkill1 = _oUpSkills.HasObj(0)?_oUpSkills.Get(0):0;
    oSkillDBInfo.dwUpSkill2 = _oUpSkills.HasObj(1)?_oUpSkills.Get(1):0;
    oSkillDBInfo.dwUpSkill3 = _oUpSkills.HasObj(2)?_oUpSkills.Get(2):0;
    oSkillDBInfo.dwUpSkill4 = _oUpSkills.HasObj(g_byPeerlessSkillIndex)?_oUpSkills.Get(g_byPeerlessSkillIndex):0;

    // XXX: 新版本的技能清空
    oSkillDBInfo.dwUpSkill5 = 0;
    oSkillDBInfo.dwUpSkill6 = 0;
    //oSkillDBInfo.dwUpSkill5 = _oUpSkills.HasObj(g_byPassiveSkillStartIndex)?_oUpSkills.Get(g_byPassiveSkillStartIndex):0;
    //oSkillDBInfo.dwUpSkill6 = _oUpSkills.HasObj(5)?_oUpSkills.Get(5):0;
    if (!oSkillDBInfo.dwUpSkill1 && !oSkillDBInfo.dwUpSkill2 && !oSkillDBInfo.dwUpSkill3 && !oSkillDBInfo.dwUpSkill4
            && !oSkillDBInfo.dwUpSkill5 && !oSkillDBInfo.dwUpSkill6)
        return;

    iar << oSkillDBInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(qwUserID, eTypeSkillInfo, eDataChange, strData);
}

void CHeroFighterSkills::UpdatePassiveSkill2DB(EDataChange eDataChange)
{
    UINT64 qwUserID = 0;
    UINT64 qwFighterID = 0;

    if (GetUser())
        qwUserID = GetUser()->GetUserID();

    if (GetFighter())
        qwFighterID = GetFighter()->GetInstID();

    if (!qwFighterID)
    {
        LOG_CRI << "Have no Fighter!!!";
        return;
    }

    SPassiveSkillDBInfo sInfo;

    sInfo.qwOwnerID         = qwFighterID;
    sInfo.qwRoleID          = qwUserID;
    for (auto & rID : _vecPassiveSkill)
    {
        sInfo.dwSkillID         = SKILL_ID(rID);
        sInfo.dwSkillQuality    = SKILL_QUALITY(rID);
        sInfo.dwSkillLevel      = SKILL_LEVEL(rID);

        string strData;
        COutArchive iar(strData);
        iar << sInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(qwUserID, eTypePassiveSkillInfo, eDataChange, strData);
    }
}

bool CHeroFighterSkills::UnlockAllSkillByDujie(bool bInit)
{
    CFighterPtr pFighter = GetFighter();
    if (!pFighter)
        return false;

    SDujieTemplateCFGEx* pDujieCFG = CFighterMgr::GetDujieCFG(pFighter->GetDujieTemplateID(), pFighter->GetDujieLevel());
    SFighterPropCFGEx* pFighterCFG = CFighterMgr::GetFighterPropCfg(pFighter->GetID());
    if (!pDujieCFG || !pFighterCFG)
        return false;

    if (pFighterCFG->_vecSkillID.empty() || pFighterCFG->_vecPeerless.empty())
        return false;

    // 解锁主动技能
    for (size_t i = 0; i < pDujieCFG->_vecActiveUnlock.size(); ++ i)
    {
        if (i >= g_byPeerlessSkillIndex || i >= pFighterCFG->_vecSkillID.size())
            break;
        if (!pDujieCFG->_vecActiveUnlock[i])
            continue;

        UINT32 dwActiveID = pFighterCFG->_vecSkillID[i];
        if (!dwActiveID)
            continue;

        if (_oUpSkills.HasSkillID(SKILL_ID(dwActiveID)))
            continue;

        for (size_t j = 0; j < g_byPeerlessSkillIndex; ++j)
        {
            if (!_oUpSkills.HasObj(j) || !_oUpSkills.Get(j))
            {
                _oUpSkills.Set(j, dwActiveID);
                break;
            }
        }
    }

    // 解锁无双技能
    if (pDujieCFG->_MasterSkillUnlock > 0)
    {
        UINT32 dwPeerID = _oUpSkills.HasObj(g_byPeerlessSkillIndex) ? _oUpSkills.Get(g_byPeerlessSkillIndex) : 0;
        if (!dwPeerID)
            dwPeerID = pFighterCFG->_vecPeerless[0];
        _oUpSkills.Set(g_byPeerlessSkillIndex, dwPeerID);
    }

    // 解锁被动技能
    for (size_t i = 0; i < pDujieCFG->_vecPassiveUnlock.size() && i < 2; ++ i)
    {
        if (!pDujieCFG->_vecPassiveUnlock[i])
            continue;

        // 寻找是否已经开启
        bool bSame = false;
        for (auto & rID : _vecPassiveSkill)
        {
            if (SKILL_ID(rID) == SKILL_ID(pFighterCFG->_vecPassive[i]))
            {
                bSame = true;
                break;
            }
        }
        if (bSame)
            continue;

        UINT32 dwPassiveSkill = pFighterCFG->_vecPassive[i];

        _vecPassiveSkill.push_back(dwPassiveSkill);
        pFighter->SetDirty(true);
    }
    if (!bInit)
        UpdatePassiveSkill2DB(eOpUpdate);
    return true;
}

void CHeroFighterSkills::FighterSkillDismiss(TVecItemGenInfo& vecItems)
{
    SItemGenInfo stItemGen;

    // 主动技能和无双重置
    for (int i = 0; i < HERO_UPSKILL_SLOTS; ++ i)
    {
        UINT32 dwSkillID = _oUpSkills.HasObj(i) ? _oUpSkills.Get(i) : 0;
        if (!dwSkillID)
            continue;
        UINT8 byLvl = SKILL_LEVEL(dwSkillID);
        UINT8 byQuality = SKILL_QUALITY(dwSkillID);
        UINT32 dwID = SKILL_ID(dwSkillID);
        for (int j = 1; j < byLvl; ++ j)
        {
            dwSkillID = SkillMgr.GetSkillIDQualityLevel(dwID, j, byQuality);
            SSkillEfPtr pSkillEfCfg = SkillMgr.GetSkillEf(dwSkillID);
            if (!pSkillEfCfg)
                continue;
            if (pSkillEfCfg->_wCostType != EMONEY_NONE)
            {
                stItemGen.wItemID = pSkillEfCfg->_wCostType;
                stItemGen.dwCount += pSkillEfCfg->_dwCost;
            }
        }
        _oUpSkills.Set(i, 0);
    }
    // 被动技能清空
    for (auto& rID : _vecPassiveSkill)
    {
        UINT32 dwSkillID = SKILL_ID(rID);
        UINT32 dwSkillQuality = SKILL_QUALITY(rID);
        UINT32 dwSkillLevel = SKILL_LEVEL(rID);

        for (UINT32 dwLevel = 1; dwLevel < dwSkillLevel; ++ dwLevel)
        {
            const STalentSkillCFG* pCFG2 = CPassiveSkillMgr::Instance().GetCFG(SKILLID_QUALITY_LEVEL(dwSkillID, dwSkillQuality, dwLevel));
            if (!pCFG2)
                continue;
            if (pCFG2->_skillCostType != EMONEY_NONE)
            {
                stItemGen.wItemID = pCFG2->_skillCostType;
                stItemGen.dwCount += pCFG2->_skillCost;
            }
        }

        SPassiveSkillDBInfo sInfo;

        UINT64 qwUserID = 0;
        UINT64 qwFighterID = 0;

        if (GetUser())
            qwUserID = GetUser()->GetUserID();

        if (GetFighter())
            qwFighterID = GetFighter()->GetInstID();

        sInfo.qwOwnerID         = qwFighterID;
        sInfo.qwRoleID          = qwUserID;

        sInfo.dwSkillID         = dwSkillID;
        sInfo.dwSkillQuality    = dwSkillQuality;
        sInfo.dwSkillLevel      = dwSkillLevel;

        string strData;
        COutArchive iar(strData);
        iar << sInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(qwUserID, eTypePassiveSkillInfo, eOpDel, strData);
    }


    if (stItemGen.wItemID && stItemGen.dwCount)
        vecItems.push_back(stItemGen);
    _vecPassiveSkill.clear();

    UnlockAllSkillByDujie(false);    //XXX 还原回初始技能
    Update2DB(eOpUpdate);
    UpdatePassiveSkill2DB(eOpUpdate);
}

void CHeroFighterSkills::WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID)
{
    CFighterPtr pFighter = GetFighter();
    if(!pFighter)
        return ;
    NLogDataDefine::SFighterLogPtr ptrLog(new NLogDataDefine::SFighterLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SFighterLog& rLog = *ptrLog;
    rLog.dwServerId   = Config._wGroup;
    rLog.qwUserId     = GetUser()->GetRoleID();
    rLog.wFighterId   = wID;
    rLog.sName        = pFighter->GetName();
    rLog.wLevel       = pFighter->GetLevel();
    rLog.byQuality    = pFighter->GetColor();
    rLog.eOptType     = eType;
    rLog.dwType       = dwDetail;
    rLog.qwResult     = qwResult;
    rLog.happenedTime = Time::Now();
    CGameServerLog::LogToDB(ptrLog);
}

//散仙组合技能
void CHeroFighterSkills::AddCombinationSkill(UINT32 dwSkillID)
{
    if(!dwSkillID)
        return;
    _vecCombinationSkillID.push_back(dwSkillID);
}

void CHeroFighterSkills::ClearCombinationSkill() 
{ 
    _vecCombinationSkillID.clear(); 
}

void CHeroFighterSkills::GetPassiveSkillAttr(TVecFloat& vecAttr) const
{
    for(auto rID : _vecPassiveSkill)
    {
        const STalentSkillCFG* pCFG = CPassiveSkillMgr::Instance().GetCFG(rID);
        if (!pCFG)
        {
            LOG_CRI<< "Error PassiveSkillID: " << rID << ".";
            continue;
        }

        SSkillAttrPtr pSkillAttr = g_SkillAttrMgr.GetSkillAttrByID(pCFG->_SkillAttr);
        if(!pSkillAttr)
        {
            LOG_CRI<<"Error SkillAttr: " << pCFG->_SkillAttr << ".";
            continue;
        }
        vecAttr += pSkillAttr->_vecAttr; 
    }

}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

