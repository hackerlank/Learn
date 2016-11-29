
#include "stdafx.h"

#include "Protocols.h"
#include "HeroFighter.h"
#include "FighterMgr.h"
#include "ItemMgr.h"
#include "User.h"
#include "Player.h"
#include "FighterProt.h"
#include "CommonDef.h"
#include "ProtoCommon.h"
#include "VecSlots.h"
#include "RoleInfoDefine.h"
#include "ExpMgr.h"
#include "PropInfoS.h"
#include "FighterManager.h"
#include "Battle.h"
#include "GameServerSysMail.h"
#include "RankProt.h"
#include "Random.h"
#include "Item.h"
#include "EquipTrump.h"

using namespace NRankProt;

CHeroFighter::CHeroFighter(UINT16 wFighterID) : CFighter(wFighterID, eFighterHero),_oGemStone(*this)
{
    _vecCuiTi.resize(EFIGHTATTR_MAX, 0.0f);
    _vecDujieAttr.resize(EFIGHTATTR_MAX, 0.0f);
    InitDujieAttr();
}

// ===  FUNCTION  ======================================================================
//         Name:  ~CHeroFighter
//  Description:  析构函数
// =====================================================================================
CHeroFighter::~CHeroFighter ()
{
}		// -----  end of function ~CHeroFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetLevel
//  Description:  获取等级
// =====================================================================================
UINT8 CHeroFighter::GetLevel () const
{
    CUserPtr pUser = GetUser();
    if (pUser)
        return pUser->GetLevel();
    else
        return CFighter::GetLevel();
}		// -----  end of function GetLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetExp
//  Description:  获取经验值
// =====================================================================================
UINT64 CHeroFighter::GetExp () const
{
    CUserPtr pUser = GetUser();
    if (pUser && GetID() <= 20)
        return pUser->GetPlayer()->GetExp();
    else
        return CFighter::GetExp();
}		// -----  end of function GetExp  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetName
//  Description:  获取姓名
// =====================================================================================
const string CHeroFighter::GetName() const
{
    if (GetID() <= SParamConfig::dwMainFigherIDMax)
    {
        if (!GetUser())
            return "配置没有";
        return GetUser()->GetUserName();
    }
    else
    {
        SFighterPropCFG* pFighterPropCFG = GetFighterPropConfig();
        if (!pFighterPropCFG)
            return "配置没有";
        return pFighterPropCFG->_Name;
    }
}

void CHeroFighter::SetUser(const CUserPtr& pUser)
{
    CFighter::SetUser(pUser);
    _oSkills.SetUser(pUser);
    _oSkills.SetFighter(ToThisPtr(this));
    _oXinFas.SetUser(pUser);
    _oXinFas.SetFighter(ToThisPtr(this));

    _oEquipTrumpSlot.SetUser(pUser);
    _oEquipTrumpSlot.SetFighter(ToThisPtr(this));
}

void CHeroFighter::GetAllSkillsID(TVecUINT32& vecSkillsID) const
{
    GetSkills().GetAllUpSkills(vecSkillsID);         //技能
    _oEquipTrumpSlot.GetAllSkills(vecSkillsID);
}

bool CHeroFighter::ToProt(SFighterSpecInfo& sFighterInfo) const
{
    if (!CFighter::ToProt(sFighterInfo))
        return false;

    // 散仙属性
    SFighterInfo& rFighterInfo = sFighterInfo.oFighterInfo;
    for (size_t i = 1; i < _vecFighterAttr.size(); ++i)
    {
        rFighterInfo.oAttrVec.push_back(SFtAttrMod((EFighterAttr)i, _vecFighterAttr[i]));
    }

    // 主动技能
    TVecUINT32 oActiveSkills;
    _oSkills.GetActiveSkills(oActiveSkills);
    for (size_t i = 0; i < oActiveSkills.size(); ++i)
    {
        rFighterInfo.vActiveSkill.push_back(SFightSkillInfo(i, oActiveSkills[i]));
    }

    // 被动技能
    TVecUINT32 oPassiveSkills;
    _oSkills.GetPassiveSkills(oPassiveSkills);
    for (auto & rID : oPassiveSkills)
    {
        rFighterInfo.vPassiveSkill.push_back(SFightSkillInfo(0, rID));
    }

    // 无双技能
    rFighterInfo.oPeerLees.byIdx = 0;
    rFighterInfo.oPeerLees.dwSkillID = _oSkills.GetPeerLessID();

    //心法
    TVecXinFaInfo vecXinFaInfo;
    _oXinFas.HeroFighterXFInfo(vecXinFaInfo);
    rFighterInfo.vecXinFa = vecXinFaInfo;

    //宝石
    TVecGemstonePtr vecStone;
    _oGemStone.GetGemstoneAll(vecStone);
    for(auto pos = vecStone.begin();pos != vecStone.end(); pos++)
    {
        rFighterInfo.vecStoneItem.push_back((*pos)->ToProt()); 
    }

    // 经验等级
    rFighterInfo.oBaseInfo.byLevel = GetLevel();
    rFighterInfo.oBaseInfo.qwExp = GetExp();

    _oEquipTrumpSlot.GetAllInfo(rFighterInfo.vecEquipTrump);

    return true;
}

void CHeroFighter::InitSkills(const TVecUINT32& vecSkillID)
{
    // XXX: 如果技能等级为1，则在数据库里没有存储
    CFighter::InitSkills(vecSkillID);
    /*
       const TVecUINT32& vecInitSkills = GetInitSkills();
       for (size_t i = 0; i < vecInitSkills.size(); ++i)
       _oSkills.UpSkillFromDB(vecInitSkills[i], i);
       */
}

void CHeroFighter::Init()
{
    if(!GetUser())
        return;

    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if(!pPlayer)
        return;
}

void CHeroFighter::InitDujieAttr()
{
    SDujieTemplateCFGEx* pDujieCFG = CFighterMgr::GetDujieCFG(GetDujieTemplateID(), GetDujieLevel());
    if (!pDujieCFG)
        return;
    VECATTR_RESET(_vecDujieAttr);
    _vecDujieAttr = pDujieCFG->_vecAddAttr;
}

const TVecFloat& CHeroFighter::GetCuiTiAttr() const
{
    if (!IsDirty())
        return _vecCuiTi;

    VECATTR_RESET(_vecCuiTi);

    // TODO: 如果增加了属性加成项，这里需要做相应增加
    SFighterCuiTiCFG* pFighterCuiTiCfg = NULL;
#define CUITI_ATTR(T, L, I)                                                                                                     \
    do {                                                                                                                        \
        SFighterStarGrowthCFG* pFighterStarGrowthCfg = CFighterMgr::GetFighterStarGrowthCfg(pFighterStarCfg->_EFIGHTATTR_##I);  \
        if (pFighterStarGrowthCfg)                                                                                              \
        {                                                                                                                       \
            pFighterCuiTiCfg = CFighterMgr::GetFighterCuiTiCfg((UINT8)(T), (L));                                                \
            if (pFighterCuiTiCfg)                                                                                               \
            {                                                                                                                   \
                VECATTR_ADD(_vecCuiTi, EFIGHTATTR_##I, pFighterCuiTiCfg->_EFIGHTATTR_##I*pFighterStarGrowthCfg->_Ratio);        \
                pFighterCuiTiCfg = NULL;                                                                                        \
            }                                                                                                                   \
        }                                                                                                                       \
    } while(0)

    SFighterStarCFG* pFighterStarCfg = CFighterMgr::GetFighterStarCfg(GetFighterInclination(), GetStar());
    if (!pFighterStarCfg)
    {
        LOG_CRI << "HAVE NO FIGHTER STAR: " << GetStar() << ",FIGHTER ID: " << GetID();
        return _vecCuiTi;
    }

    for (UINT8 idx = 0; idx < eCuiTiMax; ++ idx)
    {
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PHYATK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MGCATK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PHYDEF);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MGCDEF);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PHYRDC);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MGCRDC);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MAXHP);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), SPEED);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), HIT);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), HITRATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), DODGE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), DODGERATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), CRITICAL);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), CRTRATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), ANTICRITCAL);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), ANTICRTRATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), BLOCK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), BLOCKRATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PIERCE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PIERCERATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), COUNTER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), COUNTERRATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), RESIST);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), RESISTRATE);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), INITAURA);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MAXAURA);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), CRIEXTRAADD);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), CRIEXTRARDC);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), METALATK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), WOODATK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), WATERATK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), FIREATK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), EARTHATK);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), METALDEF);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), WOODDEF);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), WATERDEF);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), FIREDEF);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), EARTHDEF);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PHYATK_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MGCATK_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PHYDEF_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MGCDEF_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), MAXHP_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), SPEED_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), HIT_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), DODGE_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), CRITICAL_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), ANTICRITCAL_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), BLOCK_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), PIERCE_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), COUNTER_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), RESIST_PER);
        CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), ANTIEFFECT);
        //CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), COUTEREXTRAADD);
        //CUITI_ATTR(idx, GetCuiTiLevel((ECuiTiType)idx), COUTEREXTRARDC);
    }

    return _vecCuiTi;
}

bool CHeroFighter::RebuildAttr() const
{
    CFighter::RebuildAttr();
    _vecFinalAttr += GetCuiTiAttr(); // _vecFinalAttr from Fighter
    _vecFinalAttr += _oXinFas.GetHeroFighterXinFaAttr(); // 散仙心法属性加成
    _vecFinalAttr += _vecDujieAttr;

    _oEquipTrumpSlot.GetAddAttr(_vecFinalAttr);

    _oSkills.GetPassiveSkillAttr(_vecFinalAttr);
    _oGemStone.GetAddAttr(_vecFinalAttr);
    if (GetFighterManager())
        GetFighterManager()->GetHeroAddAttr(_vecFinalAttr);

    _vecBPAttr += GetCuiTiAttr(); // _vecBPAttr from Fighter
    _vecBPAttr += _oXinFas.GetHeroFighterXinFaAttr(); // 散仙心法属性加成
    _vecBPAttr += _vecDujieAttr;

    _oEquipTrumpSlot.GetAddAttr(_vecBPAttr);

    _oSkills.GetPassiveSkillAttr(_vecBPAttr);
    _oGemStone.GetAddAttr(_vecBPAttr);
    if (GetFighterManager())
        GetFighterManager()->GetHeroAddAttr(_vecBPAttr);

    _vecFinalAttr2 = _vecFinalAttr;
    //计算百分比加成
    {
        _vecFinalAttr2[EFIGHTATTR_PHYATK]           = _vecFinalAttr2[EFIGHTATTR_PHYATK]         * (1 + _vecFinalAttr2[EFIGHTATTR_PHYATK_PER]);
        _vecFinalAttr2[EFIGHTATTR_MGCATK]           = _vecFinalAttr2[EFIGHTATTR_MGCATK]         * (1 + _vecFinalAttr2[EFIGHTATTR_MGCATK_PER]);
        _vecFinalAttr2[EFIGHTATTR_PHYDEF]           = _vecFinalAttr2[EFIGHTATTR_PHYDEF]         * (1 + _vecFinalAttr2[EFIGHTATTR_PHYDEF_PER]);
        _vecFinalAttr2[EFIGHTATTR_MGCDEF]           = _vecFinalAttr2[EFIGHTATTR_MGCDEF]         * (1 + _vecFinalAttr2[EFIGHTATTR_MGCDEF_PER]);
        _vecFinalAttr2[EFIGHTATTR_MAXHP]            = _vecFinalAttr2[EFIGHTATTR_MAXHP]          * (1 + _vecFinalAttr2[EFIGHTATTR_MAXHP_PER]);
        _vecFinalAttr2[EFIGHTATTR_SPEED]            = _vecFinalAttr2[EFIGHTATTR_SPEED]          * (1 + _vecFinalAttr2[EFIGHTATTR_SPEED_PER]);
        _vecFinalAttr2[EFIGHTATTR_HIT]              = _vecFinalAttr2[EFIGHTATTR_HIT]            * (1 + _vecFinalAttr2[EFIGHTATTR_HIT_PER]);
        _vecFinalAttr2[EFIGHTATTR_DODGE]            = _vecFinalAttr2[EFIGHTATTR_DODGE]          * (1 + _vecFinalAttr2[EFIGHTATTR_DODGE_PER]);
        _vecFinalAttr2[EFIGHTATTR_CRITICAL]         = _vecFinalAttr2[EFIGHTATTR_CRITICAL]       * (1 + _vecFinalAttr2[EFIGHTATTR_CRITICAL_PER]);
        _vecFinalAttr2[EFIGHTATTR_ANTICRITCAL]      = _vecFinalAttr2[EFIGHTATTR_ANTICRITCAL]    * (1 + _vecFinalAttr2[EFIGHTATTR_ANTICRITCAL_PER]);
        _vecFinalAttr2[EFIGHTATTR_BLOCK]            = _vecFinalAttr2[EFIGHTATTR_BLOCK]          * (1 + _vecFinalAttr2[EFIGHTATTR_BLOCK_PER]);
        _vecFinalAttr2[EFIGHTATTR_PIERCE]           = _vecFinalAttr2[EFIGHTATTR_PIERCE]         * (1 + _vecFinalAttr2[EFIGHTATTR_PIERCE_PER]);
        _vecFinalAttr2[EFIGHTATTR_COUNTER]          = _vecFinalAttr2[EFIGHTATTR_COUNTER]        * (1 + _vecFinalAttr2[EFIGHTATTR_COUNTER_PER]);
        _vecFinalAttr2[EFIGHTATTR_RESIST]           = _vecFinalAttr2[EFIGHTATTR_RESIST]         * (1 + _vecFinalAttr2[EFIGHTATTR_RESIST_PER]);
        _vecFinalAttr2[EFIGHTATTR_PHYATK_PER]       = 0;
        _vecFinalAttr2[EFIGHTATTR_MGCATK_PER]       = 0;
        _vecFinalAttr2[EFIGHTATTR_PHYDEF_PER]       = 0;
        _vecFinalAttr2[EFIGHTATTR_MGCDEF_PER]       = 0;
        _vecFinalAttr2[EFIGHTATTR_MAXHP_PER]        = 0;
        _vecFinalAttr2[EFIGHTATTR_SPEED_PER]        = 0;
        _vecFinalAttr2[EFIGHTATTR_HIT_PER]          = 0;
        _vecFinalAttr2[EFIGHTATTR_DODGE_PER]        = 0;
        _vecFinalAttr2[EFIGHTATTR_CRITICAL_PER]     = 0;
        _vecFinalAttr2[EFIGHTATTR_ANTICRITCAL_PER]  = 0;
        _vecFinalAttr2[EFIGHTATTR_BLOCK_PER]        = 0;
        _vecFinalAttr2[EFIGHTATTR_PIERCE_PER]       = 0;
        _vecFinalAttr2[EFIGHTATTR_COUNTER_PER]      = 0;
        _vecFinalAttr2[EFIGHTATTR_RESIST_PER]       = 0;
    }

    SetDirty(false);
    OnAttrRebuilded();

    //重新生成log信息
    BuildBattleInfo();

    return true;
}

void CHeroFighter::OnAttrRebuilded() const
{
    // 属性变化后的其他调用处理
    if (GetFighterManager())
        GetFighterManager()->UpdateHeroFighterRankInfo();
    //UpdateRankInfo();
}

const static UINT8 CuiTiLevelLimit[6] = { 15,24,30,36,38,40 };

ECuiTiResult CHeroFighter::CuiTiUpgrade(ECuiTiType eCuiTiType, UINT8& byLevel, bool bForce /* = false */)
{
    if (!GetUser())
        return eCuiTiResultFailed;
    if (eCuiTiType >= eCuiTiMax)
        return eCuiTiResultFailed;
    if (CuiTiLevelLimit[(UINT8)eCuiTiType] > GetLevel())
        return eCuiTiResultUnlock;

    UINT8 byLvl = GetCuiTiLevel(eCuiTiType);
    SFighterCuiTiCFG* pFighterCuiTiCfg = CFighterMgr::GetFighterCuiTiCfg((UINT8)eCuiTiType, byLvl+1);
    if (!pFighterCuiTiCfg)
        return eCuiTiResultLvlMaxErr;
    if (GetLevel() < pFighterCuiTiCfg->_LimitLevel)
        return eCuiTiResultPlayerLvlErr;

    if (!bForce)
    {
        if (!GetUser()->CanSubMoney(EMONEY_SILVER,pFighterCuiTiCfg->_SilverNeed))
            return eCuiTiResultSilverErr;
        GetUser()->SubMoney(EMONEY_SILVER,pFighterCuiTiCfg->_SilverNeed,NLogDataDefine::ItemTo_HeroCuiTiUpgrade);
    }

    ++ byLvl;
    byLevel = byLvl;

    SetCuiTiLevel(eCuiTiType, byLvl);
    Update2DB(eOpUpdate);


    //CuiTi   记入LogServer
    UINT64 qwResult = static_cast<UINT64>(byLvl);
    UINT32 dwDetail = static_cast<UINT32>(eCuiTiType);
    WriteFighterLog(eOptType_CuiTi,dwDetail,qwResult,GetID());

    //GetUser()->GetPlayer()->GetActivityPkg().CheckActivityPoint(EPOINTTYPE_HARDENE_BODY);
    UINT32 dwCuiTiCount = 0;
    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if (pPlayer)
    {
        GetUser()->GetTaskPkg().OnAction(*pPlayer, eProcessAction_FighterCT);
        GetUser()->GetTaskPkg().OnAction(*pPlayer, eProcessAction_SpecialHeroToTalCTLv); 
        GetUser()->GetTaskPkg().OnAction(*pPlayer, eProcessAction_SpecialHeroCTLvl); 
        //散仙淬体升级事件
        TVecINT32 vecParam;
        vecParam.push_back(GetID());
        vecParam.push_back(eCuiTiType);
        vecParam.push_back(byLvl);
        for(UINT32 i = 0; i < eCuiTiMax; i++)
        {
            //统计崔体等级总和
            dwCuiTiCount += _byCuiTiLvl[i];
            
            if(i != eCuiTiType)
                vecParam.push_back(_byCuiTiLvl[i]);
        }

        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_FighterCuiTi, vecParam);
       GetUser()->GetVars().SetVar(NVarDefine::ePlayerVarCuiTiCount,dwCuiTiCount); 
    }
    SetDirty(true);

    return eCuiTiResultSucc;
}

EShiftResult CHeroFighter::Shift(CFighterPtr& _pFighter)
{
    if (!_pFighter->IsHeroFighter())
        return eShiftFailed;

    if (!GetUser()->CanSubMoney(EMONEY_GOLD,SParamConfig::wShiftCost))
        return eShiftGoldErr;

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(_pFighter);
    if (!CFighter::SwapCuiTi(_pFighter))
        return eShiftFailed;
    GetUser()->SubMoney(EMONEY_GOLD,SParamConfig::wShiftCost,NLogDataDefine::ItemTo_HeroShift);

    // XXX: Notify
    TVecFighterSpecInfo info(2);
    ToProt(info[0]);
    pFighter->ToProt(info[1]);
    GetUser()->SendPkg(g_RoleEventProtS.BuildPkg_FighterInfoNotify(info));

    SetDirty(true);
    pFighter->SetDirty(true);
    //GetUser()->GetPlayer()->GetActivityPkg().CheckActivityPoint(EPOINTTYPE_HERO_TRANS);    i
    UINT64 qwResult =  pFighter->GetID();
    UINT32 dwDetail = 0;
    WriteFighterLog(eOptType_Shift,dwDetail,qwResult,GetID());
    return eShiftSucc;
}

EDismissResult CHeroFighter::FighterDismiss()
{
    if (!GetUser())
        return eDismissFailed;
    /*
    TVecGemstonePtr vecStone;
    _oGemStone.GetGemstoneAll(vecStone);
    if(!vecStone.empty())
    {
        return eNeedTakeOffStone;
    }
    */
    if (!GetUser()->CanSubMoney(EMONEY_SILVER, SParamConfig::wRecyclePrice))
        return eDismissFailed;
    TVecItemGenInfo vecItems;
    {   //XXX 散功渡劫 //渡劫符
        UINT32 dwDujieItem = GetDujieExp() / SParamConfig::wDujieFosterAverage;
        SItemGenInfo stItemGen;
        stItemGen.wItemID = EMONEY_DUJIEFU;
        stItemGen.dwCount = dwDujieItem;
        stItemGen.eBindType = eBindGet;
        if (stItemGen.wItemID && stItemGen.dwCount)
            vecItems.push_back(stItemGen);
        SetDujieExp(0);
        SetDujieLevel(1);
        InitDujieAttr();
        //SetColor(1);
        SDujieTemplateCFGEx* pDujieCFGNext = CFighterMgr::GetDujieCFG(GetDujieTemplateID(), 1);
        if (pDujieCFGNext)
            SetColor(pDujieCFGNext->_Color);
    }
    {   //XXX 散功萃体
        UINT32 dwSilver = 0;
        for(size_t i = 0; i < eCuiTiMax; ++ i)
        {
            UINT8 byCuiLvl = GetCuiTiLevel(ECuiTiType(i));
            for (int j = 1; j <= byCuiLvl; ++ j)
            {
                SFighterCuiTiCFG* pCuiTiCFG = CFighterMgr::GetFighterCuiTiCfg(i, j);
                if (pCuiTiCFG)
                    dwSilver += pCuiTiCFG->_SilverNeed;
            }
            SetCuiTiLevel(ECuiTiType(i), 0);
        }
        SItemGenInfo stItemGen;
        stItemGen.wItemID = EMONEY_SILVER;
        stItemGen.dwCount = dwSilver;
        stItemGen.eBindType = eBindGet;
        if (stItemGen.wItemID && stItemGen.dwCount)
            vecItems.push_back(stItemGen);
    }
    //XXX 散功技能
    GetSkills().FighterSkillDismiss(vecItems);
    //XXX 散功心法
    GetXinFas().FighterXinFaDismiss(vecItems);
    //XXX 散功宝石
    _oGemStone.GemstoneDismiss(vecItems);
    if (vecItems.empty())
        return eDismissFailed;

    // TODO: 装备法宝
    /*
    vector<CItemPtr> vecItemInst;
    {
        TVecEquipTrumpPtr vecEquipTrump;
        _oEquipTrumpSlot.GetAllEquipTrump(vecEquipTrump);
        for (auto & pEquipTrump : vecEquipTrump)
        {
            vecItemInst.push_back(dynamic_pointer_cast<CItem>(pEquipTrump));
        }
    }
    */

    SetDirty(true);
    Update2DB();

    //发送邮件
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_FIGHTERDISMISS;
    stBody.vecParam.push_back(GetName());
    TVecUINT64 vecTargets;
    vecTargets.push_back(GetUser()->GetUserID());
    //GameServerSysMail::SendSysMail(SEND_FIGHTERDISMISS, TITLE_FIGHTERDISMISS, stBody, vecTargets, &vecItems, &vecItemInst);
    GameServerSysMail::SendSysMail(SEND_FIGHTERDISMISS, TITLE_FIGHTERDISMISS, stBody, vecTargets, &vecItems);

    GetUser()->SubMoney(EMONEY_SILVER, SParamConfig::wRecyclePrice, NLogDataDefine::ItemTo_FighterDismiss);
    return eDismissSucc;
}

//渡劫相关
EDujieResult CHeroFighter::DujieUpgrade(bool bOneKey)
{
    CUserPtr pUser = GetUser();
    if (!pUser)
        return eDujieFailed;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
        return eDujieFailed;

    // 操作未开放
    if(!pUser->GetOpLock().AddLock(eLock_DujieUpgrade, 1))
        return eDujieFailed;

    UINT8 byTemplateID = GetDujieTemplateID();
    UINT8 byDujieLvl = GetDujieLevel();

    // 渡劫到最高
    if (CFighterMgr::IsDujieMaxLevel(byTemplateID, byDujieLvl))
        return eDujieLevelMaxErr;

    SDujieTemplateCFGEx* pDujieCFG = CFighterMgr::GetDujieCFG(byTemplateID, byDujieLvl);
    if (!pDujieCFG)
        return eDujieFailed;

    // 等级限制
    if (pUser->GetLevel() < pDujieCFG->_RequiredLevel)
        return eDujieFailed;

    // 渡劫符不足
    if (!pUser->CanSubMoney(EMoneyType(pDujieCFG->_EvolveItemID), pDujieCFG->_UsingNum))
        return eDujieItemErr;

    UINT32 dwMaxCount = pUser->GetMoney(EMoneyType(pDujieCFG->_EvolveItemID));
    UINT32 dwFailTimes = pUser->GetVars().GetVar(NVarDefine::ePlayerDujieFailTimes);
    UINT32 dwNeedCount = 0;
    UINT32 dwDujieExp = GetDujieExp();
    UINT32 dwCount = pUser->GetVars().GetVar(NVarDefine::ePlayerDujieCount);

    do
    {
        if (dwNeedCount >= dwMaxCount)
            break;
        dwNeedCount += pDujieCFG->_UsingNum;

        UINT16 wRand = CRandom::RandInt(0, MAX_RANDNUM);

        // 主将第一次渡劫必定不暴击，第二第三次渡劫必定暴击
        if (IsMainFighter())
        {
            if (dwCount == 0)
                wRand = 9999;
            else if (dwCount == 1 || dwCount == 2)
                wRand = 1;
            ++ dwCount;
        }

        // 十倍暴击
        if (wRand < SParamConfig::wDujieFosterHitChance3)
        {
            dwFailTimes = 0;
            dwDujieExp += SParamConfig::wDujieFosterValue * 10;

            TVecString vecstring;
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecstring.push_back(NumberToString(10));
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgDujieHit, vecstring);
            pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eDujieCrit, eTenMultipleCrit));
        }
        // 五倍暴击
        else if (wRand < SParamConfig::wDujieFosterHitChance2)
        {
            dwFailTimes = 0;
            dwDujieExp += SParamConfig::wDujieFosterValue * 5;
            pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eDujieCrit, eFiveMultipleCrit));
        }
        // 两倍暴击
        else if (wRand < SParamConfig::wDujieFosterHitChance1 || dwFailTimes >= SParamConfig::wDujieFosterProtectNum)
        {
            dwFailTimes = 0;
            dwDujieExp += SParamConfig::wDujieFosterValue * 2;
            pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eDujieCrit, eTwoMultipleCrit));
        }
        // 不暴击
        else
        {
            dwDujieExp += SParamConfig::wDujieFosterValue * 1;
            ++ dwFailTimes;
        }

        // 升级了
        if (dwDujieExp >= pDujieCFG->_Exp) 
        {
            byDujieLvl = CFighterMgr::GetDujieLvlByExp(byTemplateID, dwDujieExp);
            bOneKey = false;
        }

    } 
    while(bOneKey);

    pUser->GetVars().SetVar(NVarDefine::ePlayerDujieCount, dwCount);

    if (byDujieLvl != GetDujieLevel())
        OnDujieLevelChanged(byDujieLvl);

    SetDujieExp(dwDujieExp);

    Update2DB();
    pUser->SubMoney(EMoneyType(pDujieCFG->_EvolveItemID), dwNeedCount, NLogDataDefine::ItemTo_DujieConsume);
    pUser->GetVars().SetVar(NVarDefine::ePlayerDujieFailTimes, dwFailTimes);
    pUser->SendPkg(g_FighterProtS.BuildPkg_UpdateDujieValue(GetInstID(), GetDujieLevel(), GetDujieExp(), GetSpiritPower()));

    //写Log日志
    SDujieTemplateCFGEx* pDujieCfgA = CFighterMgr::GetDujieCFG(byTemplateID, GetDujieLevel());
    if (pDujieCfgA)
        WriteDujieLog(pDujieCfgA->_PeriodName);
    pUser->GetOpLock().UnLock(eLock_DujieUpgrade);
    return eDujieSucc;
}

void CHeroFighter::SetDujieLevelByGM(UINT8 byLevel)
{
    UINT8 byTemplateID = GetDujieTemplateID();
    UINT8 byDujieMaxLevel = CFighterMgr::GetDujieMaxLevel(byTemplateID);
    if (!byDujieMaxLevel)
        return;
    if (byLevel > byDujieMaxLevel)
        byLevel = byDujieMaxLevel;

    SDujieTemplateCFGEx* pDujieCFG = CFighterMgr::GetDujieCFG(byTemplateID, byLevel);
    if (!pDujieCFG)
        return;
    OnDujieLevelChanged(byLevel);
    SetDujieExp(pDujieCFG->_Exp);
    Update2DB();
    GetFighterManager()->OnFighterColorChange(GetColor());
}

//购买散仙时渡劫
bool CHeroFighter::BuyFighterDujie(UINT8 byDujieLvl)
{
    if (!GetUser())
        return false;

    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if (!pPlayer)
        return false;

    UINT8 byTemplateId = GetDujieTemplateID();
    SDujieTemplateCFGEx* pDujieCFG = CFighterMgr::GetDujieCFG(byTemplateId, byDujieLvl-1);
    if (!pDujieCFG)
        return false;

    UINT32 dwDujieExp = pDujieCFG->_Exp;
    SetDujieLevel(byDujieLvl);
    SetDujieExp(dwDujieExp);
    Update2DB();

    InitDujieAttr();
    SetDirty(true);
    SDujieTemplateCFGEx* pDujieCFGNext = CFighterMgr::GetDujieCFG(byTemplateId, byDujieLvl);
    if (pDujieCFGNext)
        SetColor(pDujieCFGNext->_Color);

    if (!GetSkills().UnlockAllSkillByDujie(false))
        LOG_CRI << "Unlock hero All Skill By Dujie Error!!";
    else
        GetSkills().Update2DB(eOpUpdate);
    
    if (GetUser())
        GetUser()->SendPkg(g_FighterProtS.BuildPkg_UpdateDujieValue(GetInstID(), GetDujieLevel(), GetDujieExp(), GetSpiritPower()));
    
    return true;
}

void CHeroFighter::OnDujieLevelChanged(UINT8 byNewLevel)
{
    if (byNewLevel == GetDujieLevel())
        return;

    SetDujieLevel(byNewLevel);

    InitDujieAttr();

    SetDirty(true);

    SDujieTemplateCFGEx* pDujieCFGNext = CFighterMgr::GetDujieCFG(GetDujieTemplateID(), byNewLevel);
    if (pDujieCFGNext)
        SetColor(pDujieCFGNext->_Color);

    if (!GetSkills().UnlockAllSkillByDujie(false))
        LOG_CRI << "Unlock hero All Skill By Dujie Error!!";
    else
        GetSkills().Update2DB(eOpUpdate);

    _oEquipTrumpSlot.TryUnlockSlot(byNewLevel);

    //Event事件及广播
    DujieUpgradeEvent();
}

void CHeroFighter::DujieUpgradeEvent()
{
    CUserPtr pUser = GetUser();
    if (!pUser)
        return;
    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if (!pPlayer)
        return ;
    if (!GetFighterManager())
        return;

    //Event事件
    UINT8 byDujieLvl = GetDujieLevel();
    UINT8 byTemplateId = GetDujieTemplateID();
    TVecINT32 vecParam;
    vecParam.push_back(GetID());
    vecParam.push_back(byDujieLvl);
    ostringstream os;
    os << GetID() << ";";
    os << static_cast<UINT32>(byDujieLvl) << ";";
    CFighterSlots& rFighterSlots = GetFighterManager()->GetFighterSlots();
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(rFighterSlots.GetSlots()); ++ iSlot)
    {
        CFighterPtr pFighter = rFighterSlots.Get(iSlot);
        if (pFighter && pFighter->GetRecruited())
        {
            vecParam.push_back(pFighter->GetDujieLevel());
            os << pFighter->GetID() << ",";
            os << (int)pFighter->GetDujieLevel() << "$";
        }
    }

    pPlayer->OnEvent(eEventType_PlayerDujieSuccess, vecParam);

    //升级广播
    if (byDujieLvl / 10 > 1 && byDujieLvl % 10 == 1)
    {   
        NGlobalChatProt::TVecShowInfo vecShow;
        TVecString vecstring;
        UINT16 wMsgID = 0;
        SDujieTemplateCFGEx* pDujieCfg = CFighterMgr::GetDujieCFG(byTemplateId, byDujieLvl);
        if(pDujieCfg)
        {
            Tokenizer tk(pDujieCfg->_PeriodName, "1");
            string strPeriodName = tk[0];
            if(IsMainFighter())
            {
                wMsgID = eMsgPurpleCharDujie;
                vecstring.push_back(NumberToString(pDujieCfg->_Color));
                vecstring.push_back(strPeriodName);
            }
            else
            {
                wMsgID = eMsgPurplePartnerDujie;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecstring.push_back(NumberToString(pDujieCfg->_Color));
                vecstring.push_back(strPeriodName);
            }
        }
        if(wMsgID)
        {
            NGlobalChatProt::SShowInfo stShow;
            GetShowInfo(stShow);
            vecShow.push_back(stShow);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL, 0, wMsgID, vecstring, vecShow);
        }
    }
}

void CHeroFighter::WriteDujieLog(string &rPeriodName)
{
    NLogDataDefine::SDujieLogPtr ptrLog(new NLogDataDefine::SDujieLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SDujieLog& rLog = *ptrLog;
    rLog.dwServerId = Config._wGroup;
    rLog.qwPlayerId = GetRoleID();
    rLog.wFighterId = GetID();
    rLog.sFighterName = GetName();
    rLog.sPeriodName  = rPeriodName;
    rLog.dwExp        = GetDujieExp();
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

void CHeroFighter::WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID)
{
    NLogDataDefine::SFighterLogPtr ptrLog(new NLogDataDefine::SFighterLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SFighterLog& rLog = *ptrLog;
    rLog.dwServerId  = Config._wGroup;
    rLog.qwUserId    = GetUser()->GetRoleID();
    rLog.wFighterId  = wID;
    rLog.sName       = GetName();
    rLog.wLevel      = GetLevel();
    rLog.byQuality   = GetColor();
    rLog.eOptType    = eType;
    rLog.dwType      = dwDetail;
    rLog.qwResult    = qwResult;
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

void CHeroFighter::UpdateRankInfo() const
{
    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if (!pPlayer || pPlayer->GetLevel() < SParamConfig::wRankLevelLimit4)
        return;
    CHeroFighterPtr pMainFighter = pPlayer->GetMainFighter();
    if (!pMainFighter)
        return;
    UINT32 dwBattlePoint = GetBattlePoint();
    TVecRankInfo vecRankInfo;
    SRRHeroFighterInfoPtr pInfo (new SRRHeroFighterInfo);
    pInfo->dwValue = dwBattlePoint;
    pInfo->dwUpdateTime = Time::Now();
    pInfo->qwRoleID = pPlayer->GetRoleID();
    pInfo->strName = pPlayer->GetName();
    pInfo->strGuildName = pPlayer->GetGuildName();
    pInfo->wID = GetID();
    pInfo->dwBattlePoint = dwBattlePoint;
    pInfo->byQuality = pMainFighter->GetColor();
    pInfo->wPlayerFighterID = pMainFighter->GetID();
    pInfo->byInfoQuality = GetColor();
    pInfo->vecPlatforms = GetUser()->GetPlatformParam();
    pInfo->byVIPLevel = GetUser()->GetVIPLevel();

    vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    g_Game2CenterRankC.Send_UpdateRankInfo(eRTHeroFighter, pPlayer->GetRoleID(), vecRankInfo);
}

void CHeroFighter::Super()
{
    // 淬体等级最高
    for (UINT8 byIndex = eCuiTiLianPi; byIndex < eCuiTiMax; ++byIndex)
    {
        ECuiTiType eType = static_cast<ECuiTiType>(byIndex);
        ECuiTiResult eResult = eCuiTiResultFailed;
        do
        {
            UINT8 byLevel = 0;
            eResult = CuiTiUpgrade(eType, byLevel, true);
        } while (eResult == eCuiTiResultSucc);
    }

    // TODO :渡劫等级弄至最高 

    if (!IsMainFighter())
    {
        //心法
        SFighterPropCFGEx* pFighterCFG = CFighterMgr::GetFighterPropCfg(GetID());
        if (!pFighterCFG)
            return;

        for (size_t i=0; i<pFighterCFG->_vecXinFaID.size(); i++)
        {
            if (pFighterCFG->_vecXinFaID[i])
            {

                if(!_oXinFas.GMLearnXinFa(pFighterCFG->_vecXinFaID[i]))
                    continue;
                if(!_oXinFas.GMXinFaUpgrade(pFighterCFG->_vecXinFaID[i]))
                    continue;
            }
        } 
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  GetAllSkills
//  Description:  获取所有战斗技能
// =====================================================================================
bool CHeroFighter::GetAllSkills(TVecUINT32& rvecAllSklls, UINT32& dwNormalAttack) const
{
    _oSkills.GetAllUpSkills(rvecAllSklls);

    _oSkills.GetAllCombineSkills(rvecAllSklls);

    // 死亡动画技能
    SFighterPropCFGEx* pFighterCfg = (SFighterPropCFGEx*)GetFighterPropConfig();
    if (pFighterCfg && pFighterCfg->_NormalDead)
        rvecAllSklls.push_back(CSkillMgr::Instance().GetSkillIDQualityLevel(pFighterCfg->_NormalDead, 1));

    // 主将会带有法宝系统带出的被动技能
    if (IsMainFighter() && GetFighterManager())
    {
        CTrumpSlots& rTrumpSlots = GetFighterManager()->GetTrumpSlots();
        UINT32 dwSkillID = rTrumpSlots.GetPeerlessSkill();
        if (dwSkillID)
            rvecAllSklls.push_back(dwSkillID);
        rTrumpSlots.GetPassiveSkills(rvecAllSklls);
    }

    _oEquipTrumpSlot.GetAllSkills(rvecAllSklls);

    dwNormalAttack = GetNormalAttack();
    return true;
}		// -----  end of function GetAllSkills  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAppear
//  Description:  获取外观
// =====================================================================================
SFeatureBasePtr CHeroFighter::GetAppear() const
{
    if (IsMainFighter())
    {
        if (!GetUser())
            return NULL;
        CPlayerPtr pPlayer = GetUser()->GetPlayer();
        if(!pPlayer)
            return NULL;
        return dynamic_pointer_cast<SFeatureBase>(pPlayer->GetAppearFeature());
    }
    else
    {
        SHeroFeaturePtr pSHeroFeature(new SHeroFeature);
        if(pSHeroFeature == NULL)
            LOG_CRI << "New SHeroFeature ERR";
        else
        {
            pSHeroFeature->byQuality = GetColor();
            pSHeroFeature->wHeroID = GetID();
            pSHeroFeature->byDujieLevel = GetDujieLevel();
        }
        return dynamic_pointer_cast<SFeatureBase>(pSHeroFeature);
    }
    return NULL;
}		// -----  end of function GetAppear  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleAppear
//  Description:  获取战斗时的外观
// =====================================================================================
SFeatureBasePtr CHeroFighter::GetBattleAppear(EBattleType eBattleType) const
{
    if (IsMainFighter())
    {
        if (!GetUser())
            return NULL;
        CPlayerPtr pPlayer = GetUser()->GetPlayer();
        if(!pPlayer)
            return NULL;
        return dynamic_pointer_cast<SFeatureBase>(pPlayer->GetBattleAppear(eBattleType));
    }
    else
    {
        SHeroFeaturePtr pSHeroFeature(new SHeroFeature);
        if(pSHeroFeature == NULL)
            LOG_CRI << "New SHeroFeature ERR";
        else
        {
            pSHeroFeature->byQuality = GetColor();
            pSHeroFeature->wHeroID = GetID();
            pSHeroFeature->byDujieLevel = GetDujieLevel();
        }
        return dynamic_pointer_cast<SFeatureBase>(pSHeroFeature);
    }
    return NULL;
}		// -----  end of function GetBattleAppear  ----- //

void CHeroFighter::BuildBattleInfo() const
{
    TVecUINT32 rvecAllSklls;
    UINT32 dwNormalAttack;

    GetAllSkills(rvecAllSklls,dwNormalAttack);

    TVecXinFaInfo vecXinFa;
    _oXinFas.HeroFighterXFInfo(vecXinFa);


    TVecGemstonePtr vecStone;
    _oGemStone.GetGemstoneAll(vecStone);

    ostringstream os;
    os<<"<Fighter ID=\""<<GetFighterID()<<"\">";
    os<<"<Pos>"<<(UINT32)GetPos()<<"</Pos>";
    os<<"<Dunjie>"<<(UINT32)GetDujieLevel()<<"</Dunjie>";
    os<<"<Skill>";
    for(UINT32 i=0; i < rvecAllSklls.size();i++)
    {
        os<<rvecAllSklls[i];
        if(i != (rvecAllSklls.size()-1))
            os<<",";
    }
    os<<"</Skill>";
    os<<"<CuiTi>";
    for(UINT32 i=0; i <eCuiTiMax; i++)
    {
        os<<"<Member Type=\""<<i<<"\"";
        os<<"Level=\""<<(UINT32)GetCuiTiLevel((ECuiTiType)i)<<"\"";
        os<<"/>";
    }

    os<<"</CuiTi>";
    os<<"<XinFa>";
    for(UINT32 i=0;i < vecXinFa.size();i++)
    {
        os<<"<Member ID=\""<<vecXinFa[i].dwXinFaID<<"\"";
        os<<"Level=\""<<(UINT32)vecXinFa[i].byXinFaLvl<<"\"";
        os<<"/>";
    }
    os<<"</XinFa>";

    os<<"<Stone>"; 
    for(UINT32 i=0;i <vecStone.size();i++)
    {
        if(vecStone[i])
        {
            os<<"<Member ID=\""<<vecStone[i]->GetItemID()<<"\"";
            os<<"Level=\""<<(UINT32)vecStone[i]->GetStoneLevel()<<"\"";
            os<<"/>";
        }
    }
    os<<"</Stone>"; 
    os<<"</Fighter>";

    _strInfoLog = os.str();
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

