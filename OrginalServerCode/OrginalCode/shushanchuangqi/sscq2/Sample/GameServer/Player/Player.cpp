#include "stdafx.h"

#include "Player.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "Map.h"
#include "MapMgr.h"
#include "RoleInfoDefine.h"
#include "Dungeon.h"
#include "DungeonMgr.h"
#include "Pack.h"
#include "Depot.h"
#include "Parameter.h"
#include "ItemMgr.h"
#include "Game2CenterCommC.h"
#include "Title.h"
#include "HeroFighter.h"
#include "FighterMgr.h"
#include "FighterManager.h"
#include "Monster.h"
#include "ItemProt.h"
#include "Task.h"
#include "GatherMgr.h"
#include "ExpMgr.h"
#include "FormationPet.h"
#include "FashionSlots.h"
#include "FighterProt.h"
#include "IconAppearManager.h"
#include "Game2CenterDemonTowerC.h"
#include "Game2CenterTeamC.h"
#include "RTime.h"
#include "TrumpSlots.h"
#include "Trump.h"
#include "EquipTrumpSlot.h"
#include "EquipTrump.h"
#include "HorseSvrS.h"
#include "HorseMgr.h"
#include "SoulSpaceMgr.h"
#include "Bubble.h"
#include "DemonTowerSvrS.h"
#include "AchievementMgr.h"
#include "CollectionMgr.h"
#include "GuildBattleMgr.h"
#include "NewGuildBattleMgr.h"
#include "AttackedMgr.h"
#include "ExchangeShopMgr.h"
#include "EnergyMgr.h"
#include "WorldBossMgr.h"
#include "LevelPrizeAct.h"
#include "ShushanBattle.h"
#include "ShopItemMgr.h"
#include "DayTargetMgr.h"
#include "TreasureHunt.h"
#include "GuardEMei.h"
#include "MoneyTree.h"
#include "RegisterSevenDays.h"

#include "RankProt.h"
#include "AutoStoreMgr.h"
#include "BattleArrayMgr.h"
#include "BeautyMgr.h"
#include "FightFormationMgr.h"
#include "FightHeroInfoMgr.h"
#include "BoostMgr.h"
#include "ZhanQiMgr.h"
#include "GodChest.h"
#include "Random.h"
#include "EverydayRecharge.h"
#include "FeedBackMgr.h"

using namespace NRoleInfoDefine;
using namespace NItemProt;
using namespace NRankProt;

CPlayer::CPlayer(UINT64 qwRoleID, const CUserPtr& pUser) : 
    _qwRoleID(qwRoleID), _pUser(pUser), _wMapID(0),
    _qwCurNpcID(0), _ePlayerState(ePlayerNone), 
    _dwSpeed(PLAYER_BASESPEED),
    _DgnPkg(*this),_sActionManager(*this),
    _dwGatherID(0),_bInTeam(false), _qwDemonToweInstID(0), _dwCurTowerFlorrID(0),
    _tLastMidNight(0), 
    _GroupTaskPkg(*this),_YaMenTaskPkg(*this), 
    _ActivityPkg(*this),_TitlePkg(*this), _SignInPkg(*this),
    _bPackUnlockNotified(false),
    _tReliveTime(0), _bInLoad(true), _dwBattleCD(0),
    _dwTotalBattelPoint(0), _dwMainFighterBP(0),
    _bCittaFirst(true)
{
}

CPlayer::~CPlayer()
{
    CGameBuffMgr::Instance().RemoveBuffManager(_qwRoleID);
    //LOG_CRI << "Delete Player";
    //LOG_CRI << "_pMainFighter Ref :" << _pMainFighter.lock().use_count();
    //LOG_CRI << "_pFighterManager Ref :" << _pFighterManager.use_count();

}

bool CPlayer::Init()
{
    _pFighterManager.reset(new CFighterManager(GetUser()));
    if (!_pFighterManager) return false;
    _pFighterManager->GetFashionSlots().SetUser(GetUserPtr());
    _pFighterManager->GetCittaSlots().SetUser(GetUserPtr());

    _pSoulSpaceMgr.reset(new CSoulSpaceMgr(this));
    if(!_pSoulSpaceMgr) return false;

    _pAchievementMgr.reset(new CAchievementMgr(*this));
    if(!_pAchievementMgr) return false;

    _pHorseMgr.reset(new CHorseMgr(GetUser()));
    if(!_pHorseMgr) return false;

    _pCollectionMgr.reset(new CCollectionMgr(*this));
    if(!_pCollectionMgr) return false;

    _pAttackedMgr.reset(new CAttackedMgr(*this));
    if(!_pAttackedMgr) return false;

    _pExchangeShopMgr.reset(new CExchangeShopMgr(*this));
    if(!_pExchangeShopMgr) return false;

    _pEnergyMgr.reset(new CEnergyMgr(*this));
    if(!_pEnergyMgr) return false;

    _pLevelPrizeAct.reset(new CLevelPrizeAct(*this));
    if(!_pLevelPrizeAct) return false;

    _pLoginPkgMgr.reset(new CLoginPkgMgr(*this));
    if(!_pLoginPkgMgr) return false;

    _pShushanweiwei.reset(new CShushanweiwei(*this));
    if(!_pShushanweiwei) return false;

    _pShengLing.reset(new CShengLing(*this));
    if(!_pShengLing) return false;
    
    _pFenbaoyan.reset(new CFenbaoyanMgr(*this));
    if(!_pFenbaoyan) return false;
   
    _pEventMgr.reset(new CEventMgr(*this));
    if(!_pEventMgr) return false;

    _pShopItemMgr.reset(new CShopItemMgr(*this));
    if(!_pShopItemMgr) return false;

    _pDayTargetMgr.reset(new CDayTargetMgr(*this));
    if(!_pDayTargetMgr) return false;

    _pTreasureHunt.reset(new CTreasureHunt(*this));
    if(!_pTreasureHunt) return false;

    _pMoneyTree.reset(new CMoneyTree(*this));
    if(!_pMoneyTree) return false;

    _pRegisterSevenDays.reset(new CRegisterSevenDays(*this));
    if(!_pRegisterSevenDays) return false;

    _pGuardEMei.reset(new CGuardEMei(*this));
    if(!_pGuardEMei) return false;

    _pAutoStoreMgr.reset(new CAutoStoreMgr(*this));
    if(!_pAutoStoreMgr) return false;

    _pBattleArrayMgr.reset(new CBattleArrayMgr(*this));
    if(!_pBattleArrayMgr) return false;

    _pFightFormationMgr.reset(new CFightFormationMgr(*this));
    if(!_pFightFormationMgr) return false;

    _pFightHeroInfoMgr.reset(new CFightHeroInfoMgr(*this));
    if(!_pFightHeroInfoMgr) return false;


    _pBeautyMgr.reset(new CBeautyMgr(*this));
    if(!_pBeautyMgr) return false;


    CGameBuffMgr::Instance().AddBuffManager(_qwRoleID, this);
    return true;
}

CUserPtr CPlayer::GetUserPtr() const
{
    return _pUser.lock();
}

CUser& CPlayer::GetUser()
{
    CUserPtr pUser = GetUserPtr();
    if(pUser == NULL)
    {
        LOG_CRI << "pUser is NULL!";
        DebugBreak();
    }
    return *pUser;
}

UINT64 CPlayer::GetUserID() const
{
    CUserPtr pUser = GetUserPtr();
    if(pUser == NULL)
    {
        LOG_CRI << "pUser is NULL! RoleID: " << _qwRoleID;
        return 0;
    }
    return pUser->GetUserID();
}

void CPlayer::SetCurMapID(UINT16 wMapID)
{
    if(_wMapID == wMapID)
        return;
    _wMapID = wMapID;
}

bool CPlayer::StopMove(const SPoint& rPoint, float fDir)
{
    if(!CCreature::StopMove(rPoint, fDir))
        return false;
    TVecPosition tvec;
    return NotifyMeAndSurround(g_MapProtS.BuildPkg_PlayerMoveFail(_qwRoleID, rPoint,tvec));
}

bool CPlayer::IsOnActiveMap() const
{
    CUserPtr pUser = GetUserPtr();
    if(pUser == NULL)
    {
        LOG_CRI << "pUser is NULL! RoleID: " << _qwRoleID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_CRI << "User has no active player! UsrID: " << pUser->GetUserID();
        PRINT_CALL_STACK;
        return false;
    }
    if(CMapMgr::IsDgnMap(_wMapID))
    {
        CGameMapPtr pMap = GetMap();
        if(pMap != NULL)
            return pPlayer->GetMap() == pMap;
    }
    return pPlayer->GetCurMapID() == _wMapID;
}

void CPlayer::GetPlayerAppear(SPlayerAppear& appear)
{
    appear.strName = _strName;
    appear.eCareer = static_cast<NProtoCommon::ECareerType>(GetJob());
    appear.byLevel = GetLevel();
    appear.eSex = _sBaseInfo.eSex; 
    appear.dwSpeed = _dwSpeed;
    SPlayerFeaturePtr pPlayerFeature = GetAppearFeature();
    appear.pFeature = dynamic_pointer_cast<SFeatureBase>(pPlayerFeature);

    CHorseMgrPtr pHorseMgr = GetHorseMgr();
    if(pHorseMgr)
    {
        pHorseMgr->GetAppearHorse(appear.dwHorseID,appear.dwHorseLevel);
    }

    //美女

    if(_pBeautyMgr)
    {
        _pBeautyMgr->GetAppear(appear.wBeautyID,appear.byBeautyLevel);
    }

    //阵灵及其等级
    CFighterManagerPtr pFighterManager = GetFighterManager();
    if(pFighterManager == NULL)
    {
        LOG_CRI <<  "GetFighterManager() iS NULL";
        return ;
    }
    CFormationPet& rForFormationPet = pFighterManager->GetFormationPet();
    CPetSlots& rPetSlots =  rForFormationPet.GetPetSlots();
    //appear.byPetLevel = rPetSlots.GetLevel();
    CPetPtr pPet = rPetSlots.GetCurrPet();
    if(pPet != NULL && pPet->GetSelected() == 1)
    {
        appear.wPetID = pPet->GetID();
        appear.byPetLevel = pPet->GetPetLevel();
    }
    else
    {
        appear.wPetID = 0;
        appear.byPetLevel = 0;
    }
    if(_sActionManager.HasAction(eACTION_SIT))
    {
        if(GetSitToGatherPlayer() != 0)
        {
            appear.bIsSitting = 2;
            appear.qwOtherSitID = GetSitToGatherPlayer();
        }
        else
        {
            appear.bIsSitting = 1;
        }

    }
    else
    {
        appear.bIsSitting = 0;
    }
    appear.vecPlatforms = GetUser().GetPlatformParam();
}

SPlayerFeaturePtr CPlayer::GetAppearFeature()
{
    SPlayerFeaturePtr pPlayerFeature (new SPlayerFeature);
    if (pPlayerFeature)
    {
        pPlayerFeature->strName = GetName();
        if (_pMainFighter.lock())
        {
            pPlayerFeature->eJob = static_cast<NProtoCommon::ECareerType>(GetJob());
            pPlayerFeature->eSex = _sBaseInfo.eSex; 
            pPlayerFeature->byQuality = _pMainFighter.lock()->GetColor();
            pPlayerFeature->byDujieLevel = _pMainFighter.lock()->GetDujieLevel();

            CFashionSlots& rFashionSlots = GetFighterManager()->GetFashionSlots();

            CFashionPtr pW = rFashionSlots.GetCurrW();
            CFashionPtr pD = rFashionSlots.GetCurrD();

            if (pW && !pW->GetHide())
            {
                SEquipShowInfo sEquipInfo;
                sEquipInfo.wEquipID = pW->GetItemID();
                sEquipInfo.byStrengthenLevel = pW->GetLevel();
                sEquipInfo.byPos = 0;
                (pPlayerFeature->vEquip).push_back(sEquipInfo);
            }
            if (pD && !pD->GetHide())
            {
                SEquipShowInfo sEquipInfo;
                sEquipInfo.wEquipID = pD->GetItemID();
                sEquipInfo.byStrengthenLevel = pD->GetLevel();
                sEquipInfo.byPos = 0;
                (pPlayerFeature->vEquip).push_back(sEquipInfo);
            }
            CTrumpSlots& rTrumpSlots = GetFighterManager()->GetTrumpSlots();
            CTrumpPtr pTrump = rTrumpSlots.GetActiveTrump();
            if (pTrump)
            {
                SEquipShowInfo sEquipInfo;
                sEquipInfo.wEquipID = pTrump->GetItemID();
                sEquipInfo.byStrengthenLevel = pTrump->GetRank();
                sEquipInfo.byPos = 0;
                (pPlayerFeature->vEquip).push_back(sEquipInfo);
            }
        }
        map<UINT8,UINT16> mapTitle;
        GetTitlePkg().GetTitleApear(mapTitle);
        for(auto it = mapTitle.begin();it != mapTitle.end();it++)
        {
            STitleAppear sTitle;
            sTitle.byPos =it->first;
            sTitle.wID = it->second;
            pPlayerFeature->vecTitle.push_back(sTitle);
        }
        pPlayerFeature->strGuildName = GetGuildName();
        CUserPtr pUser = GetUserPtr();
        if (pUser)
            pPlayerFeature->byVIPLevel = pUser->GetVIPLevel();
    }
    return pPlayerFeature;
}

SPlayerFeatureWithBuffPtr CPlayer::GetBattleAppear(EBattleType eBattleType)
{
    SPlayerFeatureWithBuffPtr pPlayerFeature (new SPlayerFeatureWithBuff);
    if (pPlayerFeature)
    {
        pPlayerFeature->strName = GetName();
        if (_pMainFighter.lock())
        {
            pPlayerFeature->eJob = static_cast<NProtoCommon::ECareerType>(GetJob());
            pPlayerFeature->eSex = _sBaseInfo.eSex; 
            pPlayerFeature->byQuality = _pMainFighter.lock()->GetColor();
            pPlayerFeature->byDujieLevel = _pMainFighter.lock()->GetDujieLevel();

            CFashionSlots& rFashionSlots = GetFighterManager()->GetFashionSlots();

            CFashionPtr pW = rFashionSlots.GetCurrW();
            CFashionPtr pD = rFashionSlots.GetCurrD();

            if (pW && !pW->GetHide())
            {
                SEquipShowInfo sEquipInfo;
                sEquipInfo.wEquipID = pW->GetItemID();
                sEquipInfo.byStrengthenLevel = pW->GetLevel();
                sEquipInfo.byPos = 0;
                (pPlayerFeature->vEquip).push_back(sEquipInfo);
            }
            if (pD && !pD->GetHide())
            {
                SEquipShowInfo sEquipInfo;
                sEquipInfo.wEquipID = pD->GetItemID();
                sEquipInfo.byStrengthenLevel = pD->GetLevel();
                sEquipInfo.byPos = 0;
                (pPlayerFeature->vEquip).push_back(sEquipInfo);
            }
            CTrumpSlots& rTrumpSlots = GetFighterManager()->GetTrumpSlots();
            CTrumpPtr pTrump = rTrumpSlots.GetActiveTrump();
            if (pTrump)
            {
                SEquipShowInfo sEquipInfo;
                sEquipInfo.wEquipID = pTrump->GetItemID();
                sEquipInfo.byStrengthenLevel = pTrump->GetRank();
                sEquipInfo.byPos = 0;
                (pPlayerFeature->vEquip).push_back(sEquipInfo);
            }
        }
        map<UINT8,UINT16> mapTitle;
        GetTitlePkg().GetTitleApear(mapTitle);
        for(auto & rPair : mapTitle)
        {
            STitleAppear sTitle;
            sTitle.byPos    = rPair.first;
            sTitle.wID      = rPair.second;
            pPlayerFeature->vecTitle.push_back(sTitle);
        }
        pPlayerFeature->strGuildName = GetGuildName();
        CUserPtr pUser = GetUserPtr();
        if (pUser)
            pPlayerFeature->byVIPLevel = pUser->GetVIPLevel();
    }



    UINT32 dwMapID = 0;
    CGameMapPtr pMap = GetMap();
    if(pMap)
        dwMapID = pMap->GetMapID();

    for (auto & rPair : _mapInfo)
    {
        if (rPair.second.eBuffEffectType != eBETAttr)
            continue;
        SBattleBuffInfo sInfo;
        sInfo.wBuffID = rPair.first;

        sInfo.vecBuffData = rPair.second.vecBuffParam;
        if (rPair.second.dwBuffTime)
            sInfo.dwBuffTime = rPair.second.dwBuffTime - Time::Now(); //Buff失效时间

        //战斗类型相关的buffer单独算
        if (!rPair.second.byBattleType)
        {
            bool bNeedSet = true;
            for (auto & rMapID : rPair.second.vecEffectMapID)
            {
                if(rMapID == dwMapID)
                    bNeedSet = true;
            }

            if (!bNeedSet)
                continue;
        }
        else if (static_cast<UINT8>(eBattleType) != rPair.second.byBattleType)
            continue;
        if (rPair.second.vecBuffParam.size() >= 2)
            sInfo.dwBuffCount = rPair.second.vecBuffParam[1];
        pPlayerFeature->vecBuffInfo.push_back(sInfo);

    }
    return pPlayerFeature;
}

bool CPlayer::IsRobot()
{
#if ENABLE_ROBOT
    if(_strName.compare(0, 6, "Robot_") == 0)
        return true;
#endif
    return false;
}

bool CPlayer::SendPkg(const string& strPkg)
{
    CUserPtr pUser = GetUserPtr();
    if(pUser == NULL)
    {
        LOG_CRI << "pUser is NULL! RoleID: " << _qwRoleID;
        return false;
    }
    return pUser->SendPkg(strPkg);
}

bool CPlayer::SendCenterSvrPkg(const string& strPkg)
{
    CUserPtr pUser = GetUserPtr();
    if(pUser == NULL)
    {
        LOG_CRI << "pUser is NULL! RoleID: " << _qwRoleID;
        return false;
    }
    return pUser->SendCenterSvrPkg(strPkg);
}

void CPlayer::OnEnter()
{

    CSoulSpaceMgrPtr pSoulSpaceMgrPtr = this->GetSoulSpaceMgr();
    if(pSoulSpaceMgrPtr)
        pSoulSpaceMgrPtr->NotifyList();

    CalSpeed(true);

    CGameMapPtr pMap = GetMap(); 
    if(NULL == pMap)
        return;

    switch(pMap->GetMapInfo().eMapType)
    {
        case eMapWorldBoss:
            CWorldBossMgr::Instance().OnLeaveMap(*this);
            break;
        case eMapDemonTower:
        default:
            break;
    }


}

void CPlayer::OnLeaveAway()
{
    CGameMapPtr pMap = GetMap();
    CPlayerPtr pPlayer = dynamic_pointer_cast<CPlayer>(shared_from_this());
    if(pMap != NULL)
    {
        bool bDisappear = true;
        switch(pMap->GetMapInfo().eMapType)
        {
            case eMapGuildBattle: // 帮派战地图
                if(pPlayer != NULL)
                    CGuildBattleMgr::Instance().UserOffline(pPlayer);
                bDisappear = false;
                break;
            case eMapShushanBattle: // 蜀山论剑地图
                bDisappear = false;
                break;
            default:
                break;
        }

        //这行代码后面不能操作和地图相关的操作
        if (bDisappear && !pMap->PlayerDisappear(*this))
            LOG_CRI << "PlayerDisappear fails! RoleID: " << GetUserID();
    }
    _pShengLing->UserOffLine();
    GetActionManager().CancelAction(eACTION_SIT);

#if 0 // 下线不算离开了
    NNewGuildBattle::CPlayerPtr pNGBPlayer = NNewGuildBattle::CBattleMgr::Instance().GetPlayer(GetRoleID());
    if (pNGBPlayer)
        NNewGuildBattle::CBattleMgr::Instance().PlayerQuit(pNGBPlayer);
#endif
}

void CPlayer::OnLeaveOff()
{
    if (IsInDungeon())//先离开副本
        CDungeonMgr::PlayerLeaveDungeon(*this);

    CDungeonPtr pDgn = GetDgn();
    if(pDgn)
    {
        EDgnType eDgnType = pDgn->GetDgnType();
        switch(eDgnType)
        {
            case eDemonTowerDgn:
                pDgn->PlayerLeave(*this);
            default:
                break;
        }
    }
    OnLeaveAway();
}

void CPlayer::OnReplace()
{
#if 0 // 下线不算离开了
    NNewGuildBattle::CPlayerPtr pNGBPlayer = NNewGuildBattle::CBattleMgr::Instance().GetPlayer(GetRoleID());
    LOG_WRN << "Player Quit NewGuildBattle.";
    if (pNGBPlayer)
        NNewGuildBattle::CBattleMgr::Instance().PlayerQuit(pNGBPlayer);
#endif
}

// ===  FUNCTION  ======================================================================
//         Name:  AddExp
//  Description:  增加经验值
// =====================================================================================
bool CPlayer::AddExp(UINT64 qwExp, bool bNotify)
{
    // 经验值倍率调整（防沉迷）
    qwExp = qwExp * GetUser().GetIndulgeRate();

    // 经验值为0或者已经是最高等级
    if(qwExp == 0 || GetLevel() >= CExpMgr::GetLevelMax())
        return false;

    // 经验值溢出的话调整为最高经验值
    if(qwExp > 0xFFFFFFFFFFFFFFFFull - _sBaseInfo.qwExp)
        qwExp = 0xFFFFFFFFFFFFFFFFull - _sBaseInfo.qwExp;

    _sBaseInfo.qwExp += qwExp;

    // 经验值系统通知
    CUserPtr pUser = GetUserPtr();
    CHeroFighterPtr pMainFighter = GetMainFighter();
    if (bNotify && pUser && pMainFighter)
    {
        string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGetEXP, 
                BuildStrVec(pMainFighter->GetColor(), pMainFighter->GetName(), qwExp));
        pUser->SendPkg(strPkg);
    }

    UINT8 byOldLevel = GetLevel();
    bool bLevelUp = CExpMgr::TestLevelUp(_sBaseInfo.byLevel, _sBaseInfo.qwExp);
    g_PropInfoS.PropQWNotify(*this, GetMainFighter()->GetInstID(), eClassFighter, ePropExp, GetExp());
    if (bLevelUp)
        OnLevelChanged(byOldLevel);
    else if (_bCittaFirst)
    {
        GetFighterManager()->GetCittaSlots().TestUnlockSlot(GetLevel());;
        _bCittaFirst = false;
    }
    UpdateBaseInfo2DB();

    return true;
}		// -----  end of function AddExp  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SubExp
//  Description:  减少经验值
// =====================================================================================
bool CPlayer::SubExp(UINT64 qwExp, bool bNotify)
{
    if(qwExp == 0)
        return false;

    if (qwExp >= _sBaseInfo.qwExp)
        _sBaseInfo.qwExp = 0;
    else
        _sBaseInfo.qwExp -= qwExp;

    UINT8 byOldLevel = GetLevel();
    CExpMgr::TestLevelDown(_sBaseInfo.byLevel, _sBaseInfo.qwExp);

    g_PropInfoS.PropQWNotify(*this, GetMainFighter()->GetInstID(), eClassFighter, ePropExp, GetExp());
    OnLevelChanged(byOldLevel);
    UpdateBaseInfo2DB();

    return true;
}		// -----  end of function SubExp  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetLevel
//  Description:  获取等级
// =====================================================================================
UINT8 CPlayer::GetLevel() const
{
    return _sBaseInfo.byLevel;
}		// -----  end of function GetLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetLevel
//  Description:  设置等级
// =====================================================================================
void CPlayer::SetLevel(UINT8 byLevel)
{
    if (byLevel == GetLevel())
        return;
    UINT64 qwExp = CExpMgr::GetLevelMin(byLevel);
    if (qwExp > GetExp())
        AddExp(qwExp);
    else
        SubExp(GetExp() - qwExp);
}		// -----  end of function SetLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnLevelChanged
//  Description:  等级改变
// =====================================================================================
void CPlayer::OnLevelChanged(UINT8 byOldLevel /* = 0 */)
{
    CCreature::SetLevel(GetLevel());
    _pFighterManager->FighterInitLevelAttr();
    // 升级信息通知
    NotifyLevelUp();
    CUserPtr pUser = GetUserPtr();
    if (pUser)
    {
        string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLevelUP, BuildStrVec(GetColor(),GetName(), GetLevel()));
        pUser->SendPkg(strPkg);
    }

    CFighterManagerPtr pFighterManager = GetFighterManager();
    pFighterManager->GetCittaSlots().TestUnlockSlot(GetLevel());;

    // 升级事件
    CEventMgrPtr pEventMgr = GetEventMgr();
    if(pEventMgr)
    {
        TVecINT32 vecParam;
        CHeroFighterPtr pMainFighter = GetMainFighter();
        if (pMainFighter)
        {
            vecParam.push_back(pMainFighter->GetID());
            vecParam.push_back(GetLevel());
            pEventMgr->OnEvent(eEventType_FighterLevelUp, vecParam);
        }

        vecParam.clear();
        vecParam.push_back(GetLevel());
        pEventMgr->OnEvent(eEventType_PlayerLevelChanging,vecParam);
    }

    // 排行榜根据等级解封
    TryUnlockRankData(byOldLevel);


    g_Game2CenterTeamC.UpFighter2Center(GetUserID(),_pMainFighter.lock()->GetID()); //成长任务
    GetUser().GetTaskPkg().OnGrow(*this, eProcessRoleProperty_level);
    CIconAppearMgr::Instance().UserLevelUp(GetUser());
    _ActivityPkg.OnLevelUp();

    // 脚本注册的升级事件
    SCRIPT.VCall("OnLevelUp", this);
}		// -----  end of function OnLevelChanged  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  TryUnlockRankData
//  Description:  解锁排行榜数据
// =====================================================================================
void CPlayer::TryUnlockRankData (UINT8 byOldLevel)
{
    //  总战力榜
    if (byOldLevel < SParamConfig::wRankLevelLimit2 && GetLevel() >= SParamConfig::wRankLevelLimit2)
        UpdateBattlePointRank();

    // 阵灵榜
    if (byOldLevel < SParamConfig::wRankLevelLimit3 && GetLevel() >= SParamConfig::wRankLevelLimit3)
    {
        CFighterManagerPtr pFighterManager = GetFighterManager();
        CFormationPet& rForFormationPet = pFighterManager->GetFormationPet();
        CPetSlots& rPetSlots =  rForFormationPet.GetPetSlots();
        rPetSlots.UpdateRankInfo();
    }

    // 散仙榜
    if (byOldLevel < SParamConfig::wRankLevelLimit4 && GetLevel() >= SParamConfig::wRankLevelLimit4)
    {
        CFighterManagerPtr pFighterManager = GetFighterManager();
        if(pFighterManager)
            pFighterManager->UpdateHeroFighterRankInfo();
    }

    // 法宝榜
    if (byOldLevel < SParamConfig::wRankLevelLimit5 && GetLevel() >= SParamConfig::wRankLevelLimit5)
    {
        if (_pMainFighter.lock())
        {
            CTrumpSlots& rTrumpSlot = GetFighterManager()->GetTrumpSlots();
            rTrumpSlot.UpdateRankInfo();
        }
    }

    // 等级榜
    if (GetLevel() >= SParamConfig::wRankLevelLimit8)
        UpdateLevelRank(true);
}		// -----  end of function TryUnlockRankData  ----- //

void CPlayer::NotifyLevelUp()
{
    SendCenterSvrPkg(g_Game2CenterCommC.BuildPkg_UserSyncPropNtf(GetUserID(), eSyncPropLevel, NumberToString(GetLevel())));
    g_PropInfoS.PropNotify(*this, GetMainFighter()->GetInstID(), eClassFighter, ePropLevel, GetLevel());
}

bool AddItem2PackOrDepot(CStore* pStore, const SItem& rItemInfo)
{

    INT16 wIndex = rItemInfo.sItemInfo.wIndex;
    CItemPtr pItem = CItemMgr::CreateItem(rItemInfo);
    if(pItem == NULL)
    {
        LOG_CRI << "CItemMgr::CreateItem fails! InstID: " << rItemInfo.sItemInfo.qwInstID;
        return false;
    }

    if(!pStore->AddItem(*pItem, wIndex, false/*notify*/, false/*new*/, false/*update*/, 0/*logDB*/))
    {
        LOG_CRI << "AddItem fails! InstID: " << rItemInfo.sItemInfo.qwInstID;
        return false;
    }
    return true;
}

bool CPlayer::HasAcceptedMonsterTask(CMonster& rMonster)
{
    TVecUINT16 vecTaskID;
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetMonsterTask(rMonster.GetMonsterID());
    if(pTaskList != NULL && !pTaskList->empty())
        vecTaskID.assign(pTaskList->begin(), pTaskList->end());
    pTaskList = CTaskConfMgr::Instance().GetCollectKillTask(rMonster.GetMonsterID());
    if(pTaskList != NULL && !pTaskList->empty())
        vecTaskID.insert(vecTaskID.end(), pTaskList->begin(), pTaskList->end());
    for(UINT16 wTaskID : vecTaskID)
    {
        CTaskPtr pTask = GetUser().GetTaskPkg().FindTask(wTaskID);
        if(pTask != NULL && pTask->GetTaskState() == eTaskAccept)
            return true;
    }
    return false;
}

bool CPlayer::CheckFinishMonsterTask(CMonster& rMonster, UINT16 wFinishID)
{
    TVecUINT16 vecTaskID;
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetMonsterTask(rMonster.GetMonsterID());
    if(pTaskList != NULL && !pTaskList->empty())
        vecTaskID.assign(pTaskList->begin(), pTaskList->end());
    pTaskList = CTaskConfMgr::Instance().GetCollectKillTask(rMonster.GetMonsterID());
    if(pTaskList != NULL && !pTaskList->empty())
        vecTaskID.insert(vecTaskID.end(), pTaskList->begin(), pTaskList->end());
    if(!vecTaskID.empty())
    {
        bool bHasFinishedTask = false;
        bool bHasOtherTask = false;
        for(UINT16 wTaskID : vecTaskID)
        {
            CTaskPtr pTask = GetUser().GetTaskPkg().FindTask(wTaskID);
            if(pTask != NULL && pTask->GetTaskState() == eTaskAccept)
            {
                if(wTaskID == wFinishID)
                    bHasFinishedTask = true;
                else
                    bHasOtherTask = true;
            }
        }
        return bHasFinishedTask && !bHasOtherTask;
    }
    return false;
}

void CPlayer::UpdateLevelRank(bool bCached) const
{
    SRRLevelInfoPtr pInfo (new SRRLevelInfo);
    pInfo->dwValue = GetLevel();
    pInfo->dwUpdateTime = Time::Now();
    pInfo->qwRoleID = GetRoleID();
    pInfo->strName = GetName();
    pInfo->wLevel = GetLevel();
    pInfo->qwExp = _pMainFighter.lock()->GetExp();
    pInfo->wPlayerFighterID = _pMainFighter.lock()->GetID();
    pInfo->byQuality = _pMainFighter.lock()->GetColor();
    CUserPtr pUser = GetUserPtr();
    if (pUser)
    {
        pInfo->vecPlatforms = pUser->GetPlatformParam();
        pInfo->byVIPLevel = pUser->GetVIPLevel();
    }
    if (!bCached)
    {
        TVecRankInfo vecRankInfo;
        vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
        g_Game2CenterRankC.Send_UpdateRankInfo(eRTLevel, GetRoleID(), vecRankInfo);
        CUserMgr::EraseLevelRank(GetRoleID());
    }
    else
        CUserMgr::InsertLevelRank(GetRoleID(), pInfo);
}

// ===  FUNCTION  ======================================================================
//         Name:  UpdateBattlePointRank
//  Description:  更新战斗力排行
// =====================================================================================
void CPlayer::UpdateBattlePointRank () const
{
    UINT32 dwBattlePoint = GetBattlePoint();
    TVecRankInfo vecRankInfo;
    SRRBattlePointInfoPtr pInfo (new SRRBattlePointInfo);
    pInfo->dwValue = dwBattlePoint;
    pInfo->dwUpdateTime = Time::Now();
    pInfo->qwRoleID = GetRoleID();
    pInfo->strName = GetName();
    pInfo->strGuildName = GetGuildName();
    pInfo->dwBattlePoint = dwBattlePoint;

    CHeroFighterPtr pMainFighter = GetMainFighter();
    if (pMainFighter)
    {
        pInfo->byQuality = pMainFighter->GetColor();
        pInfo->wPlayerFighterID = pMainFighter->GetID();
    }
    pInfo->vecPlatforms = GetUserPtr()->GetPlatformParam();
    pInfo->byVIPLevel = GetUserPtr()->GetVIPLevel();

    vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    g_Game2CenterRankC.Send_UpdateRankInfo(eRTBattlePoint, GetRoleID(), vecRankInfo);
}		// -----  end of function UpdateBattlePointRank  ----- //

bool SlotsFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    const TVecRoleSlotsInfo& rvecRoleSlotsInfo = Info.vecRoleSlotsInfo;
    for (auto& rRoleSlotsInfo : rvecRoleSlotsInfo)
    {
        if (rUser.GetUserID() != rRoleSlotsInfo.qwRoleID)
        {
            LOG_CRI << "rUser.GetUserID() = " << rUser.GetUserID() << ", "
                "rRoleSlotsInfo.qwRoleID = " << rRoleSlotsInfo.qwRoleID << ".";
            continue;
        }
        switch(rRoleSlotsInfo.eStoreType)
        {
            case eStorePack: //道具包裹
                {
                    CStore* pStore = &rUser.GetPack();
                    UINT16 wPackCapacity = rRoleSlotsInfo.wMaxSlot;
                    if (SParamConfig::wPackInitCount > wPackCapacity)
                        wPackCapacity = SParamConfig::wPackInitCount;
                    pStore->SetCapacity(wPackCapacity);
                }
                break;
            case eStoreDepot: //角色仓库
                {
                    CStore* pStore = &rUser.GetDepot();
                    UINT16 wPackCapacity = rRoleSlotsInfo.wMaxSlot;
                    if(SParamConfig::wDepotInitCount > wPackCapacity)
                        wPackCapacity = SParamConfig::wDepotInitCount;
                    pStore->SetCapacity(wPackCapacity);
                }
                break;
            case eStorePlayerTrump: //法宝栏
                {
                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (pPlayer)
                    {
                        CStore* pStore = &pPlayer->GetFighterManager()->GetTrumpSlots();
                        UINT16 wPackCapacity = rRoleSlotsInfo.wMaxSlot;
                        pStore->SetCapacity(wPackCapacity);
                    }
                }
                break;
            case eStorePlayerCitta: //心法栏
                {
                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (pPlayer)
                    {
                        CCittaSlots& rCittaSlots = pPlayer->GetFighterManager()->GetCittaSlots();
                        rCittaSlots.InitSlot(rRoleSlotsInfo.wMaxSlot, rRoleSlotsInfo.wMaxAvaliableSlot);
                    }
                }
                break;
            case eStoreEquipTrump: //装备法宝栏
                {
                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (!pPlayer)
                    {
                        LOG_CRI << "pPlayer = NULL.";
                        break;
                    }

                    CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(rRoleSlotsInfo.qwOwnerID);
                    if (!pFighter)
                    {
                        LOG_CRI << "pFighter( " << rRoleSlotsInfo.qwOwnerID << ") = NULL.";
                        break;
                    }
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if(!pHeroFighter)
                    {
                        LOG_CRI << "pHeroFighter( " << rRoleSlotsInfo.qwOwnerID << ") = NULL.";
                        break;
                    }
                    CEquipTrumpSlot& rSlot = pHeroFighter->GetEquipTrumpSlot();
                    rSlot.InitSlot(rRoleSlotsInfo.wMaxSlot, rRoleSlotsInfo.wMaxAvaliableSlot);
                }
                break;
            case eStoreNone: //无
            default:
                break;
        }
    }
    return true;
}

bool StoreFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    size_t szItems = Info.vecRoleItemInfo.size();
    NItemProt::TVecItem& vecErrItem = rUser.GetPlayer()->GetErrItem();
    for (size_t i = 0; i < szItems; ++i)
    {

        const SItem& rItemInfo = *Info.vecRoleItemInfo[i];
        UINT8 byStoreType = rItemInfo.sItemInfo.byStoreType;
        if(rItemInfo.sItemInfo.dwMark > 0)
        {
            LOG_CRI << "Find Mark Item :" << rItemInfo.sItemInfo.qwInstID << "User "  <<rUser.GetUserID();
            continue; 
        }

        bool bErr = true;
        switch (byStoreType)
        {
            case eStoreDepot:   // 仓库
            case eStorePack:    // 背包
                {
                    CStore* pStore = rUser.GetStoreByType((EStoreType)byStoreType);
                    if (pStore)
                    {
                        if (AddItem2PackOrDepot(pStore, rItemInfo))
                            bErr = false;
                    }
                    else
                        LOG_CRI << "Item (" << rItemInfo.sItemInfo.qwInstID << ", " << rItemInfo.sItemInfo.wItemID << ")not in store.";
                }
                break;
            case eStorePlayerCitta:     // 玩家心法
                {
                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (pPlayer)
                    {
                        CStore& rStore = pPlayer->GetFighterManager()->GetCittaSlots();
                        if (AddItem2PackOrDepot(&rStore, rItemInfo))
                            bErr = false;
                    }
                }
                break;

            case eStorePlayerTrump:     // 玩家法宝
                {
                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (pPlayer)
                    {
                        CStore& rStore = pPlayer->GetFighterManager()->GetTrumpSlots();
                        if (AddItem2PackOrDepot(&rStore, rItemInfo))
                            bErr = false;
                    }
                }
                break;

            case eStoreFashion:         // 时装
                {
                    SFashionPtr pSFashion = dynamic_pointer_cast<SFashion>(Info.vecRoleItemInfo[i]);
                    if (!pSFashion)
                        break;
                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (!pPlayer)
                        break;
                    CItemPtr pItem = CItemMgr::CreateItem(*pSFashion);
                    if (!pItem)
                        break;
                    if (!pPlayer->GetFighterManager()->GetFashionSlots().AdoptFashion(pItem, false))
                        break;
                    bErr = false;

                }
                break;
            case eStoreGemstone://宝石
                {
                    SGemstonePtr pSGemstone = dynamic_pointer_cast<SGemstone>(Info.vecRoleItemInfo[i]);
                    if (!pSGemstone)
                        break;
                    //找到Fighetr
                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (!pPlayer)
                        break;
                    CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(pSGemstone->qwOwnerID);
                    if(pFighter ==NULL)
                        break;
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if(pHeroFighter == NULL)
                        break;
                    CItemPtr pItem = CItemMgr::CreateItem(*pSGemstone);
                    if (!pItem)
                        break;
                    CGemstonePtr pStone = dynamic_pointer_cast<CGemstone>(pItem);
                    if(!pStone)
                        break;
                    if(!pHeroFighter->GetGemstoneSlots().AddItemFromDB(pStone))
                        break;
                    bErr = false;
                }
                break;
            case eStoreEquipTrump: //装备法宝栏
                {
                    SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(Info.vecRoleItemInfo[i]);
                    if (!pEquipTrump)
                        break;

                    CPlayerPtr pPlayer = rUser.GetPlayer();
                    if (!pPlayer)
                        break;
                    CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(pEquipTrump->qwOwnerID);
                    if(!pFighter)
                        break;
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if(!pHeroFighter)
                        break;

                    CItemPtr pItem = CItemMgr::CreateItem(*pEquipTrump);
                    if (!pItem)
                        break;
                    CEquipTrumpPtr pEquipTrumpItem = dynamic_pointer_cast<CEquipTrump>(pItem);
                    if(!pEquipTrumpItem)
                        break;
                    CEquipTrumpSlot& rSlot = pHeroFighter->GetEquipTrumpSlot();
                    bErr = rSlot.AddItemFromDB(pEquipTrumpItem) ? false:true;
                }
                break;

            default:
                LOG_WRN << "Item: " << rItemInfo.sItemInfo.qwInstID << ", "
                    "Role: " << rUser.GetUserID() << ", "
                    "StoreType: " << rItemInfo.sItemInfo.byStoreType << ", "
                    "Type: " << rItemInfo.sItemInfo.wItemID;
                break;
        }
        if(bErr)
            vecErrItem.push_back(Info.vecRoleItemInfo[i]);
    }

    if(!vecErrItem.empty())
    {
        ostringstream ssErr;
        for(auto& pItem : vecErrItem)
        {
            ssErr << pItem->sItemInfo.qwInstID << ", ";
        }
        LOG_CRI << " rUser" << rUser.GetUserID() << " has " << vecErrItem.size() << "Err,Detail is [" <<  ssErr.str() << "]";

    }
    return true;
}

bool VarsFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;

    size_t szVars = Info.vecGameVars.size();
    for (size_t i = 0; i < szVars; ++i)
    {

        const SVarsDBInfo& rVarDBInfo = Info.vecGameVars[i];
        if(rVarDBInfo.byServerType != eHostGame)
        {
            continue;
        }
        rUser.GetVars().SetVarFromDB(rVarDBInfo.wVar, rVarDBInfo.qwValue, rVarDBInfo.dwExpired);
    }

    return true;
}

bool FormationsFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;

    /*
       CFighterManagerPtr& rFighterManager = rUser.GetPlayer()->GetFighterManager();
       if (!rFighterManager)
       return false;
       CFormationPet& rFormationPet = rFighterManager->GetFormationPet();
       size_t szFormations = Info.vecFormationInfo.size();
       for (size_t i = 0; i < szFormations; ++i)
       rFormationPet.LoadFormationFromDB(Info.vecFormationInfo[i]);
       */
    return true;
}

bool PetsFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;

    CFighterManagerPtr& rFighterManager = rUser.GetPlayer()->GetFighterManager();
    if (!rFighterManager)
        return false;
    CFormationPet& rFormationPet = rFighterManager->GetFormationPet();
    size_t szPets = Info.vecPetDataInfo.size();
    for (size_t i = 0; i < szPets; ++i)
        rFormationPet.LoadPetDataFromDB(Info.vecPetDataInfo[i]);

    rFormationPet.LoadRolePetFromDB(Info.oRolePetInfo);
    return true;
}

bool BeastSoulFormDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;

    CFighterManagerPtr& rFighterManager = rUser.GetPlayer()->GetFighterManager();
    if (!rFighterManager)
        return false;
    CFormationPet& rFormationPet = rFighterManager->GetFormationPet();
    rFormationPet.LoadBeastSoulFromDB(Info.vecBeastSoulInfo);
    return true;

}

void CPlayer::Init888Coupon(CUser& rUser)
{
    rUser.AddMoney(EMONEY_COUPON,888,0,false);
    g_PropInfoS.ChangeCoupon(*this,EMONEY_COUPON,888);
}

bool FightersFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;

    for (auto & rFighterDBInfo : Info.vecFighterInfo)
    {
        CFighterPtr pFighter = CFighterMgr::Create(rFighterDBInfo, ToThisPtr(rUser));
        if (!pFighter)
            return false;

        INT32 iSlot = rFighterDBInfo.iSlot;
        if (iSlot != 0 && pFighter->IsMainFighter())
            pFighter->SetSlot(0);
        if (!rUser.GetPlayer()->AddFighterFromDB(pFighter))
            return false;
    }

    // 加载完依然没有主将，新建一个主将
    if (!rUser.GetPlayer()->GetMainFighter())
    {
        CFighterPtr pFighter = CFighterMgr::Create(CFighterMgr::GetDefaultFighterID(rUser.GetPlayer()->GetJob(), rUser.GetPlayer()->GetSex()), true, ToThisPtr(rUser));
        if (!pFighter)
            return false;

        pFighter->SetRecruited(true);
        pFighter->SetSlot(0);
        pFighter->SetPos(-1);
        if (!rUser.GetPlayer()->AddFighterFromDB(pFighter))
            return false;

        pFighter->Update2DB(eOpAdd);
        rUser.GetPlayer()->SetMainFighter(pFighter);
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
        if (pHeroFighter)
        {
            pHeroFighter->GetSkills().UnlockAllSkillByDujie(true);
            pHeroFighter->GetSkills().Update2DB(eOpAdd); // XXX: 只能在招募时新建记录了
        }

        CFighterManagerPtr& rFighterManager = rUser.GetPlayer()->GetFighterManager();
        if (!rFighterManager)
            return false;
        rFighterManager->GetFashionSlots().SetFighter(pFighter);
        rFighterManager->InitDefaultFashion();
        return true;
    }

    return true;
}

// 加载散仙技能信息
bool SkillsFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;

    size_t szSkills = Info.vecSkillInfo.size();
    for (size_t i = 0; i < szSkills; ++i)
    {
        const SSkillDBInfo& rSkillDBInfo = Info.vecSkillInfo[i];
        CFighterPtr pFighter = rUser.GetPlayer()->GetFighterByInstID(rSkillDBInfo.qwOwnerID);
        if (!pFighter)
            continue;

        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
        CHeroFighterSkills& rSkills = pHeroFighter->GetSkills();
        rSkills.UpSkillFromDB(rSkillDBInfo.dwUpSkill1, 0);
        rSkills.UpSkillFromDB(rSkillDBInfo.dwUpSkill2, 1);
        rSkills.UpSkillFromDB(rSkillDBInfo.dwUpSkill3, 2);
        rSkills.UpSkillFromDB(rSkillDBInfo.dwUpSkill4, 3);
        //rSkills.UpSkillFromDB(rSkillDBInfo.dwUpSkill5, 4);
        //rSkills.UpSkillFromDB(rSkillDBInfo.dwUpSkill6, 5);
        pHeroFighter->GetSkills().UnlockAllSkillByDujie(true);
    }
    return true;
}

// 加载散仙被动技能信息
bool PassiveSkillsFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;
    for (auto  & rInfo : Info.vecPassiveSkillInfo)
    {
        CFighterPtr pFighter = rUser.GetPlayer()->GetFighterByInstID(rInfo.qwOwnerID);
        if (!pFighter)
        {
            LOG_CRI << "Player(" << rUser.GetRoleID() << ") No Fighter: " << rInfo.qwOwnerID << ".";
            continue;
        }

        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
        CHeroFighterSkills& rSkills = pHeroFighter->GetSkills();
        rSkills.UpPassiveSkillFromDB(rInfo.dwSkillID, rInfo.dwSkillQuality, rInfo.dwSkillLevel);
    }
    return true;
}

// 加载Buff数据
bool BuffFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    for (auto it = Info.vecDBBuffInfo.begin(); it != Info.vecDBBuffInfo.end(); ++it)
    {
        const SDBBuffInfo& rDBBuffInfo = *it;
        CPlayerPtr pPlayer = rUser.GetPlayer();
        if (!pPlayer)
            continue;
        if (pPlayer->GetRoleID() != rDBBuffInfo.qwRoleID)
            continue;
        switch(rDBBuffInfo.eBuffType)
        {
            case eBTPlayer: //玩家自带Buff类型
                if (rDBBuffInfo.qwOwnerID != pPlayer->GetRoleID())
                    LOG_WRN << "rDBBuffInfo.qwOwnerID = " << rDBBuffInfo.qwOwnerID << ", RoleID = " << pPlayer->GetRoleID() << ".";
                pPlayer->SetBuff(rDBBuffInfo.wBuffID, rDBBuffInfo.vecBuffParam, rDBBuffInfo.dwBuffTime, true);
                break;
            case eBTMainFighter: // TODO: 主将相关Buff类型
                break;
            case eBTFighter: //散仙相关Buff类型
                {
                    CFighterPtr pFighter = pPlayer->GetFighterByInstID(rDBBuffInfo.qwOwnerID);
                    if (pFighter)
                    {
                        if (rDBBuffInfo.qwOwnerID != pFighter->GetInstID())
                            LOG_WRN << "rDBBuffInfo.qwOwnerID = " << rDBBuffInfo.qwOwnerID << ", InstID = " << pFighter->GetInstID() << ".";
                        pFighter->SetBuff(rDBBuffInfo.wBuffID, rDBBuffInfo.vecBuffParam, rDBBuffInfo.dwBuffTime, true);
                    }
                }
                break;
            case eBTNone: //无效Buff大类
            case eBTMax: //Buff大类最大值
            default:
                break;
        }
    }
    return true;
}

//魄空间
bool SoulSpaceFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CSoulSpaceMgrPtr pSoulSpaceMgrPtr = rPlayer.GetSoulSpaceMgr();
    if(!pSoulSpaceMgrPtr)
    {
        return false;
    }

    pSoulSpaceMgrPtr->LoadFromDB(rInfo.vecSoulSpaceInfo);
    return true;
}

//坐骑
bool HorseFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CHorseMgrPtr pHorseMgrPtr = rPlayer.GetHorseMgr();
    if(!pHorseMgrPtr)
    {
        return false;
    }

    pHorseMgrPtr->LoadFromDB(rInfo.vecHorseDB);
    return true;
}

//成就
bool AchievementFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CAchievementMgrPtr pAchievementPtr = rPlayer.GetAchievementMgr();
    if(!pAchievementPtr)
    {
        return false;
    }

    pAchievementPtr->LoadFromDB(rInfo.vecAchievementInfo);
    return true;
}

//圣陵
bool ShengLingFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CShengLingPtr pShengLingPtr = rPlayer.GetShengLing();
    if(!pShengLingPtr)
    {
        return false;
    }

    pShengLingPtr->LoadFromDB(rInfo.vecShengLing,rInfo.vecShengLingPrize);
    return true;
}

//成就
bool CollectionFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CCollectionMgrPtr pCollectionPtr = rPlayer.GetCollectionMgr();
    if(!pCollectionPtr)
    {
        return false;
    }
    pCollectionPtr->LoadFromDB(rInfo.vecCollectionInfo);
    return true;
}

bool BubbleFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CBubbleOwnerPtr pOwner = rUser.GetBubbleOwner();
    if (!pOwner)
        return false;
    return pOwner->InitFromDB(rInfo.vecBubbleInfo);
}

bool AttackedFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CAttackedMgrPtr pAttackedMgr = rPlayer.GetAttackedMgr();
    if(pAttackedMgr)
    {
        return  pAttackedMgr->LoadFromDB(rInfo);
    }

    return true;
}

bool ExchangeShopFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CExchangeShopMgrPtr pExchangeShopMgr = rPlayer.GetExchangeShopMgr();
    if(pExchangeShopMgr) return pExchangeShopMgr->LoadFromDB(rInfo);
    return true;
}

bool EnergyFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    return true;
}

bool EventFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CEventMgrPtr pEventMgr = rPlayer.GetEventMgr();
    if(pEventMgr)
    {
        pEventMgr->LoadFromDB(rInfo);
    }
    return true;
}

bool LevelPrizeFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CLevelPrizeActPtr pLevelPrizeAct = rPlayer.GetLevelPrizeAct();
    if(pLevelPrizeAct)
    {
        pLevelPrizeAct->LoadFromDB(rInfo);
    }
    return true;
}

bool DayTargetFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CDayTargetMgrPtr pDayTarget = rPlayer.GetDayTargetMgr();
    if(pDayTarget)
    {
        pDayTarget->LoadFromDB(rInfo.vecDayTargetDBInfo);
    }
    return true;
}

bool AutoStoreFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CAutoStoreMgrPtr pAutoStore = rPlayer.GetAutoStoreMgr();
    if(pAutoStore)
    {
        pAutoStore->LoadFromDB(rInfo);
    }
    return true;
}

bool BattleArrayFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CBattleArrayMgrPtr pBattleArray = rPlayer.GetBattleArrayMgr();
    if(pBattleArray)
    {
        return pBattleArray->LoadFromDB(rInfo);
    }
    return false;
}

bool BeautyFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CBeautyMgrPtr pBeauty = rPlayer.GetBeautyMgr();
    if(pBeauty)
    {
        return pBeauty->LoadFromDB(rInfo);
    }
    return false;
}

bool FightFormationFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CFightFormationMgrPtr pFightFormation = rPlayer.GetFightFormationMgr();
    if(pFightFormation)
    {
        return pFightFormation->LoadFromDB(rInfo);
    }

    return false;
}

bool FightHeroInfoFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CFightHeroInfoMgrPtr pFightHeroInfo = rPlayer.GetFightHeroInfoMgr();
    if(pFightHeroInfo)
    {
        return pFightHeroInfo->LoadFromDB(rInfo);
    }
    return false;
}

bool ShopItemFromDB(CPlayer& rPlayer, const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    CShopItemMgrPtr pShopItemMgr= rPlayer.GetShopItemMgr();
    if(pShopItemMgr)
    {
        pShopItemMgr->LoadFromDB(rInfo);
    }
    return true;
}

bool SweepFromDB(CPlayer& rPlayer,const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    rPlayer.GetActionManager().LoadFromDB(rInfo);
    return true;
}

bool XinFaFromDB(CUser& rUser, const NRoleInfoDefine::RoleDataInfo& Info)
{
    if (!rUser.GetPlayer())
        return false;

    for (size_t i = 0; i < Info.vecXinFaDBInfo.size(); ++i)
    {
        const SXinFaDBInfo& rXinFaDBInfo = Info.vecXinFaDBInfo[i];
        CFighterPtr pFighter = rUser.GetPlayer()->GetFighterByInstID(rXinFaDBInfo.qwOwnerID);
        if (!pFighter)
            continue;

        if (pFighter->IsHeroFighter())
        {
            CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
            if (pHeroFighter)
                pHeroFighter->GetXinFas().AddXinFaFromDB(rXinFaDBInfo.dwXinFaID, rXinFaDBInfo.byXinFaLvl, rXinFaDBInfo.iSlot);
        }
    }
    return true;
}

bool THFromDB(CPlayer& rPlayer,const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    for (size_t i = 0; i < rInfo.vecTHDBInfo.size(); ++i)
    {
        const STHDBInfo& sTHDBInfo = rInfo.vecTHDBInfo[i];

        CTreasureHuntPtr _pTreasureHunt = rPlayer.GetTreasureHunt();
        if(_pTreasureHunt)
            _pTreasureHunt->LoadFromDB(
                    sTHDBInfo.byCopyID,
                    sTHDBInfo.byStatus, 
                    sTHDBInfo.dwBossCurHP,
                    sTHDBInfo.dwLastTime,
                    sTHDBInfo.dwTime, 
                    sTHDBInfo.dwNum,
                    sTHDBInfo.strAward
                    );
    }

    return true;
}

bool GEMFromDB(CPlayer& rPlayer,const NRoleInfoDefine::RoleDataInfo& rInfo)
{
    for (size_t i = 0; i < rInfo.vecGEMDBInfo.size(); ++i)
    {
        const SGEMDBInfo& sGEMDBInfo = rInfo.vecGEMDBInfo[i];

        CGuardEMeiPtr _pGuardEMei = rPlayer.GetGuardEMei();
        if(_pGuardEMei)
            _pGuardEMei->LoadFromDB(sGEMDBInfo);
    }

    return true;
}

bool CPlayer::LoadFromDB(const NRoleInfoDefine::RoleDataInfo& rUserInfo)
{
    _sBaseInfo = rUserInfo.stBaseInfo;

    // Player
    SetLevel(_sBaseInfo.byLevel);
    SetJob(_sBaseInfo.eCareer);
    SetName(_sBaseInfo.strName);
    GetUser().SetUserName(_sBaseInfo.strName);

    _DgnPkg.Init(rUserInfo.vecRoleDgnInfo);
    if (!VarsFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"VarsFromDB fail!";
        return false;
    }

    if(!AutoStoreFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"AutoStoreFromDB fail!!!";
        return false;
    }

    if(!EventFromDB(*this,rUserInfo))
    {
        return false;
    }

    if(!AchievementFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"AchievementFromDB fail!";
        return false;
    }

    if(!ShengLingFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"ShengLingFromDB fail!";
        return false;
    }
    if(!CollectionFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"CollectionFromDB failed !!";
        return false;
    }
    if (!FormationsFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"FormationsFromDB fail!";
        return false;
    }
    if (!PetsFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"PetsFromDB fail!";
        return false;
    }
    if (!BeastSoulFormDB(GetUser(), rUserInfo))
    {
        LOG_CRI << "BeastSoulFormDB fail!";
        return false;
    }
    if (!FightersFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"FightersFromDB fail!";
        return false;
    }

    // XXX: must be here
    if (!SlotsFromDB(GetUser(), rUserInfo)) 
    {
        LOG_CRI<<"SlotsFromDB fail!";
        return false;
    }
    if (!SkillsFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"SkillsFromDB fail!";
        return false;
    }
    if (!PassiveSkillsFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"PassiveSkillsFromDB fail!";
        return false;
    }
    if (!StoreFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"StoreFromDB fail!";
        return false;
    }
    if (!BuffFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"BuffFromDB fail!";
        return false;
    }
    if(!SoulSpaceFromDB(*this, rUserInfo))
    {
        LOG_CRI<<"SoulSpaceFromDB fail!";
        return false;
    }
    if(!HorseFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"HorseFromDB fail";
        return false;
    }
    if (!BubbleFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"BubbleFromDB fail!";
        return false;
    }
    if (!AttackedFromDB(*this, rUserInfo))
    {
        LOG_CRI<<"AttackedFromDB fail!";
        return false;
    }
    if(!ExchangeShopFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"ExchangeShopFromDB Error!!";
        return false;
    }

    if(!EnergyFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"impossible!!";
        return false;
    }

    if(!LevelPrizeFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"LevelPrizeFromDB false!!";
        return false;
    }

    if(!DayTargetFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"DayTargetFromDB false!!";
        return false;
    }

    if(!BattleArrayFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"BattleArrayFromDB error";
        return false;
    }

    if(!BeautyFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"BeautyFromDB error";
        LOG_CRI<<"BattleArrayFromDB failse!!!";
        return false;
    }

    if(!FightFormationFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"FightFormationFromDB failse!!";
        return false;
    }

    if(!FightHeroInfoFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"FightHeroInfoFromDB  failse!!"; 
        return false;
    }

    if(!ShopItemFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"ShopItemFromDB error!!";
        return false;
    }

    if(!GetUser().PlatformParamFromDB(rUserInfo.vecPlatformParam))
    {
        LOG_CRI << " LoadYDFromDB Error";
        return false;
    }

    if(!SweepFromDB(*this,rUserInfo))
    {
        LOG_CRI<<"SweepFromDB Error!!";
        return false;
    }

    if(!XinFaFromDB(GetUser(), rUserInfo))
    {
        LOG_CRI<<"XinFaFromDB Error!!";
        return false;
    }

    if(!THFromDB(*this, rUserInfo))
    {
        LOG_CRI<<"THFromDB Error!!";
        return false;
    }

    if(!GEMFromDB(*this, rUserInfo))
    {
        LOG_CRI<<"GEMFromDB Error!!";
        return false;
    }

    GetUser().GetTaskPkg().InitTaskFromDB(rUserInfo.vecRoleTaskInfo);
    GetGroupPkg().Init(rUserInfo.sGroupInfo);
    GetYaMenPkg().Init(rUserInfo.sYaMenInfo);
    GetActivityPkg().Init(rUserInfo.vecActivityTask);
    GetTitlePkg().Init(rUserInfo.vecTitle);
    GetFighterManager()->GetHeroFighterCombinationSlots().LoadFromDB(rUserInfo.vecFighterCombination);
    GetFighterManager()->EquipToCombinationSkillAfterLoadDB();   //散仙组合技能
    //Pend
    for(auto it=rUserInfo.vecPendRes.begin();it != rUserInfo.vecPendRes.end();it++)
    {
        const SPendRes& rRes = *(it);
        SResource res;
        if(rRes.byResType >  EMONEY_END )
        {
            continue;
        }
        else if( rRes.byResType == EMONEY_NONE)
        {
            _mapLastParam[rRes.bySource].push_back(rRes.dwValue);
            _mapLastParam[rRes.bySource].push_back(rRes.dwParam);
            continue;
        }
        res._eRes =static_cast<NProtoCommon::EMoneyType>(rRes.byResType);
        res._dwValue = rRes.dwValue;
        _mapPendRes[rRes.bySource].push_back(res); 
    }

    return true;
}

bool CPlayer::InitAfterLoaded(bool bReEnter)
{
    LOG_INF<<GetUserID()<<" InitAfterLoaded";

    _bInLoad = false ;
    DoSitOnLine();

    //GetActionManager().SetLoadedOk();

    CLoginPkgMgrPtr pLoginPkg = GetLoginPkgMgr();
    LOG_INF << "Do RegisterLoginEvent GetUserID :" << GetUserID();
    if(pLoginPkg)
    {
        pLoginPkg->RegisterLoginEvent();
    }
    //玩家注册活动事件
    LOG_INF << "Do DoOffLineEvent GetUserID :" << GetUserID();
    DoOffLineEvent();
    LOG_INF << "Do RegisterAct() GetUserID :" << GetUserID();
    RegisterAct();
    LOG_INF << "Do  pEnergyMgr->OnLoad() GetUserID :" << GetUserID();
    CEnergyMgrPtr pEnergyMgr = GetEnergyMgr();
    if(pEnergyMgr)
    {
        pEnergyMgr->OnLoad();
        LOG_CRI << GetUserID() << " pEnergyMgr->OnLoad()";
    }
    else
    {
        LOG_CRI<<GetUserID() <<" NULL==pEnergyMgr";
    }
    LOG_INF << "Do  GetEventMgr() GetUserID :" << GetUserID();
    CEventMgrPtr pEventMgr = GetEventMgr();
    if(pEventMgr)
    {
        { //登陆事件
            TVecINT32 vecParam;
            vecParam.push_back(1);
            pEventMgr->OnEvent(eEventType_PlayerLogin,vecParam);
        }

        { //等级事件
            TVecINT32 vecParam;
            vecParam.push_back(GetLevel());
            pEventMgr->OnEvent(eEventType_PlayerLevelChanging,vecParam,"",false);
        }
    }

    //豪华黄钻神力buff = 20
    if(GetUser().IsYellowDiamond())
    {
        if(!HasBuff(20))
            AddBuff(20);
    }
    else
    {
        if(HasBuff(20))
            RemoveBuff(20);
    }

    //check icon
    CIconAppearMgr::Instance().UserLevelUp(GetUser());
    CIconAppearMgr::Instance().UserFinishTask(GetUser());
    //CIconAppearMgr::Instance().IconControlBySelf(GetUser());

    GetUser().SetVIPLevel(GetUser().CalcVIPLevel());
    DoCheckErrItem();
    CheckLastPend();
    //if (_pTreasureHunt)
    //_pTreasureHunt->PlayerLeaveCleanTHInfo();

    if (_pTreasureHunt)
        _pTreasureHunt->PlayerLeaveSetTHStatus();

    if (_pGuardEMei)
        _pGuardEMei->GEMSpecialSweep();

    //检测天赐宝箱活动
    g_GodChest.CheckChest(*this);
    GetUser().GetTaskPkg().AcceptTaskFromSystem();
    GetUser().SendMonthCardAward();

    CUser& rUser = GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT32 dwValue = rCGameVar.GetVar(NVarDefine::ePlayerVarDayEvent);
    if(0 == dwValue)
    {
        OnMidNight(eTimePointDaily19);
    }
    UINT32 dwPassTag = rCGameVar.GetVar(NVarDefine::ePlayerMallDayLimitFresh);
    if(0 == dwPassTag)
    {
        CShopItemMgrPtr pShopItemMgr = GetShopItemMgr();
        if(pShopItemMgr)
        {
            pShopItemMgr->ClearItemCount();
        }
        rCGameVar.SetVar(NVarDefine::ePlayerMallDayLimitFresh,1);
    }
    CIconAppearMgr::Instance().DoActiveIconForOnLine(GetUser());

    if(_pBeautyMgr)
    {
        _pBeautyMgr->OnLogin();
    }
    TVecUINT16 vecIcon;
    GetOpenIcon(vecIcon,false);
    bool bfindIcon = false;
    for(auto it = vecIcon.begin();it != vecIcon.end();it++)
    {
        if (CIconAppearMgr::Instance().IsActive(*it))
        {
            TITLE_DATA::DelNum(*it,_sBaseInfo.szIcon);
            TITLE_DATA::AddNum(*it,_sBaseInfo.szIconActive);
            bfindIcon = true;
            CIconAppearMgr::Instance().CloseActionToClient(GetUser(),*it);
        }
    }
    if(bfindIcon)
        UpdateBaseInfo2DB();

    g_EveryDayRechargeMgr.CheckIconIsOpen(GetUser(),false);


    _sActionManager.ClearAction(eACTION_TOWER);
    
    //分宝岩活动
    if(_pFenbaoyan)
        _pFenbaoyan->OnUserLogin();

    g_FeedBackMgr.OnLogin(*this);
    g_ZhanQiMgr.OnLogin(*this);

    //XXX 注意：玩家若重复登录游戏以下不会执行！！！
    if(bReEnter)
        return true;

    //非重新进入 的 事情 
    GetPackNextUnlockTime(true);
    RegenAllHP();
    const RoleBaseInfo &rBaseInfo =  GetBaseInfo();
    if(rBaseInfo.dwLoginTime == 0)
    {   //注册log
        TVecString vecRegist;
        GetUser().SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogRegister(GetUserID(), vecRegist));
        RegistInit();
        // 888礼券
        //Init888Coupon(GetUser());
        if(pEnergyMgr)
        {
            pEnergyMgr->OnFirstLogin();
        }
        //GetUser().AddMoney(NProtoCommon::EMONEY_GOLD,2000);
        //注册可删除的icon
        if(GetUser().IsYellowDiamond())
        {
            TVecINT32 vecParam;
            vecParam.push_back(1);
            OnEvent(eEventType_YellowDiamondNum,vecParam);
        }

    }

    return true;
}

//用于玩家注册，初始化一些数据
bool CPlayer::RegistInit()
{
    return true;
}

// XXX: 背包解锁对属性的加成
void CPlayer::GetPackUnlockAttr(TVecFloat& rvecAttr)
{
    CStore& rStore = GetUser().GetPack();
    UINT16 wCapacity = rStore.GetCapacity();
    for (size_t i = 0; i < wCapacity; ++i)
    {
        SBagCostCFG* pCfg = CItemMgr::GetBagCost(i+1);
        if (!pCfg || !pCfg->_BagAttr)
            continue;
        CItemMgr::AppendAttr2(pCfg->_BagAttr, rvecAttr);
    }
}

UINT32 CPlayer::GetPackNextUnlockTime(bool bLoginSet )
{
    UINT32 dwNow = Time::Now();
    if(bLoginSet)
    {
        if (!_sBaseInfo.dwPackNextUnlockTime)
        {
            SBagCostCFG* pCfg = CItemMgr::GetBagCost(SParamConfig::wPackInitCount+1);
            if (!pCfg)
            {
                _sBaseInfo.dwPackNextUnlockTime = 0XFFFFFFFF;
                UpdateBaseInfo2DB();
                return 0XFFFFFFFF;
            }
            _sBaseInfo.dwPackNextUnlockTime = dwNow + pCfg->_Time;
            UpdateBaseInfo2DB();
        }
        else if (_sBaseInfo.dwPackNextUnlockTime != 0xFFFFFFFF)
        {
            UINT32 dwOffTime = GetPackUnlockOfflineTime();
            if (dwOffTime)
            {
                _sBaseInfo.dwPackNextUnlockTime += dwOffTime;
                UpdateBaseInfo2DB();
            }
        }
    }
    if(_sBaseInfo.dwPackNextUnlockTime == 0XFFFFFFFF)
    {
        return _sBaseInfo.dwPackNextUnlockTime;
    }
    UINT32 dwTime = _sBaseInfo.dwPackNextUnlockTime>=dwNow?_sBaseInfo.dwPackNextUnlockTime - dwNow:0;
    return dwTime;
}

bool CPlayer::JumpMap(UINT16 wMapID, const SPoint& rDestPoint,UINT16 wJumpID)
{
    if (!Config.CheckMapInServer(wMapID))
    {
        return JumpServer(wMapID, rDestPoint);
    }
    CGameMapPtr pMap = NULL; 
    if(wJumpID > 0  && wMapID == GetCurMapID())
    {
        pMap = GetMap();
    }
    else
    {
        pMap = CMapMgr::GetMap(wMapID);
    }
    if(pMap == NULL)
        return false;
    return JumpMap(pMap, rDestPoint,wJumpID);
}

bool CPlayer::JumpServer(UINT16 wMapID, const SPoint& rDestPoint)
{
    CGameMapPtr pMap = GetMap();
    CUserPtr pUser = GetUserPtr();
    if(pMap != NULL && !pMap->PlayerDisappear(*this))
    {
        LOG_CRI << "PlayerDisappear fails! RoleID:" << _qwRoleID;
        return false;
    }
    SetPoint(rDestPoint);
    SetCurMapID(wMapID);
    UpdateBaseInfo2DB();
    if(!g_Game2DBCommC.SaveDataReq(GetUser(), eSaveJump, pUser->GetPlatformParam()))
    {
        LOG_CRI << "Jump Server Fails! RoleID: " << _qwRoleID;
        CUserMgr::KickUserOffLine(GetUserID());
        return false;
    }
    SetPlayerState(ePlayerJump);
    return true;
}

bool CPlayer::JumpMap(CGameMapPtr& rDestMap, const SPoint& rDestPoint,UINT16 wJumpID)
{
    return JumpMap(rDestMap, rDestPoint, wJumpID, false);
}

bool CPlayer::JumpMap(CGameMapPtr& rDestMap, const SPoint& rDestPoint, UINT16 wJumpID, bool bForce)
{
    if(rDestMap == NULL)
        return false;

    CUserPtr pUser = GetUserPtr();
    if(pUser == NULL)
    {
        LOG_CRI << "pUser is NULL! RoleID: " << _qwRoleID;
        return false;
    }
    GetWalker().ClearPath();
    CGameMapPtr pMap = GetMap();

    if(pMap && pMap->IsNormalMap() && (!rDestMap->IsNormalMap()))
    {
        SaveLastNormalMap();
    }
    if(rDestMap->GetMapInfo().IsBlock(rDestPoint))
    {
        LOG_CRI << "rDestPoint is blocked! rDestPoint: " << rDestPoint << ", FromMapID: " << (pMap != NULL ? pMap->GetMapID() : 0) << ", ToMapID: " << rDestMap->GetMapID();
        PRINT_CALL_STACK_DEBUG;
        if(!rDestMap->GetRandPoint((SPoint&)rDestPoint))
        {
            LOG_CRI << "GetRandPoint fails!";
            return false;
        }
    }

    CDungeonPtr pOldDgn = NULL;
    CDungeonPtr pEnterDgn = rDestMap->GetDungeon();
    if(pMap)
    {
        pOldDgn = pMap->GetDungeon();
    }
    /*
       if(rDestMap != NULL)
       {
       g_GodChest.JumpMap(*this,rDestMap);
       }
       */
    if(pMap != NULL)
    {
        if(pMap == rDestMap && !bForce)
        {
            NotifyMeAndSurround(g_MapProtS.BuildPkg_NotifyCreatureJump(_qwRoleID, rDestPoint,wJumpID));
            GetWalker().ClearPath();
            pMap->CreatureMoveTo(*this, rDestPoint);
            pMap->CheckAllPosForJump(*this);
            GetActionManager().CancelAction(eACTION_SIT);
            return true;
        }


        // -qf- 2014/05/28
        //副本之间的地图跳转
        if(pOldDgn&& pEnterDgn)
        {
            if(!pEnterDgn->IsCanJumpMap(this,pMap,rDestMap))
            {
                return false;
            }
        }

        UINT16 wDestMapID = rDestMap->GetMapID();
        UINT16 wCurMapID = pMap->GetMapID();
        if(CMapMgr::IsDgnMap(wDestMapID))
        {	
            if(!CMapMgr::IsDgnMap(wCurMapID))
            {
                /*
                   SetPreDgnMapID(wCurMapID);
                   SetPreDgnPoint(GetPoint());
                   */
                //note yhs:切副本不应在地图转换时登记，应在进出副本时登记
            }
        }
        else
        {
            if(CMapMgr::IsDgnMap(wCurMapID))
            {
                // ClearDgnInfo();
                GetWalker().ClearPath();
            }
        }
        if(!pMap->PlayerDisappear(*this))
        {
            LOG_CRI << "PlayerDisappear fails! RoleID:" << _qwRoleID;
            return false;
        }
        SetPlayerState(ePlayerJump);
    }

    // -qf- 2014/05/28
    //离开副本之前
    if( pOldDgn  && (pOldDgn != pEnterDgn) )
    {
        pOldDgn->OnBeforeLeaveDgn(this);
        Relive();

    }

    UINT16 wDestMapID = rDestMap->GetMapID();
    SetCurMapID(wDestMapID);
    SetMap(rDestMap);
    SetPoint(rDestPoint);
    UpdateBaseInfo2DB();
    g_MapProtS.NotifyUserEnterMap(*this,rDestMap);
    rDestMap->PlayerAppear(*this);

    // -qf- 2014/05/28

    //进入副本
    if( pEnterDgn && (pOldDgn != pEnterDgn) )
    {
        pEnterDgn->OnEnterDgn(this);
    }

    //进入副本地图
    if(pEnterDgn)
    {
        pEnterDgn->OnEnterMap(this,rDestMap);
    }

    rDestMap->CheckAllPosForJump(*this);
    GetActionManager().CancelAction(eACTION_SIT);
    BufferRebuildAttr(); 
    return true;
}

void CPlayer::SaveMapPoint(UINT16 wMapId,float fx,float fy)
{

    string strData;
    COutArchive iar(strData);
    RoleBaseInfo sBaseInfo(_sBaseInfo);
    sBaseInfo.wMapID = wMapId;
    sBaseInfo.fX =  fx;
    sBaseInfo.fY = fy ;
    iar << sBaseInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypeRoleBaseInfo, eOpUpdate, strData);

}
void CPlayer::UpdateBaseInfo2DB()
{
    if(_bInLoad)
    {
        LOG_CRI<<"UpdateBaseInfo2DB in LoadDB!!!";
        return ;
    }
    SynBaseInfo();
    string strData;
    COutArchive iar(strData);
    iar << _sBaseInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypeRoleBaseInfo, eOpUpdate, strData);
}

void CPlayer::UpdateBaseInfo2DB1()
{
    SynBaseInfo();
    string strData;
    COutArchive iar(strData);
    iar << _sBaseInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypeRoleBaseInfo, eOpUpdate, strData);
}

void  CPlayer::SynBaseInfo()
{
    RoleBaseInfo &info = _sBaseInfo;
    GetUser().SyncData(_sBaseInfo);
    info.eCareer = static_cast<NProtoCommon::ECareerType>(GetJob());
    info.strName = GetName();
    info.byLevel = GetLevel();
    UINT16 wCurMapID = _wMapID; 
    if(_wMapID == 0)
    {
        LOG_CRI << "NO MAP";
        _wMapID  = 1;
    }
    if (CMapMgr::IsDgnMap(wCurMapID))
    {
        info.wDgnMapId = wCurMapID;
        info.fDgnfX = GetPoint().fX;
        info.fDgnfY = GetPoint().fY;
    }
    else
    {
        info.wMapID = wCurMapID;
        info.fX = GetPoint().fX;
        info.fY = GetPoint().fY;

    }
}

void CPlayer::EnterDgn( const CDungeon *pDgn,bool bTransDB)
{
    _sActionManager.AddAction(eACTION_DGN);
    if ( pDgn == NULL)
    {
        LOG_CRI << "Enter NULL DGN !";
        return ;
    }
    SetDgnID(pDgn->GetDgnID());
    SetDgnInstID(pDgn->GetDgnInstID());
    if(bTransDB)
    {
        UpdateBaseInfo2DB();
    }
}

CDungeonPtr CPlayer::GetDgn()
{
    if(_sBaseInfo.qwDgnId == 0)
    {
        return NULL;
    }
    return CDungeonMgr::GetDungeon(_sBaseInfo.qwDgnId);
}

bool CPlayer::CanRemove()
{
    bool bRet = !IsInDungeon();
    if (bRet)
        bRet = !(CGuildBattleMgr::Instance().IsPlayerInGuildBattleField(GetRoleID()));
    if (bRet)
        bRet = !(ShushanBattle.IsPlayerInShushanBattle(GetRoleID()));
    if (bRet)
        bRet = !(NNewGuildBattle::CBattleMgr::Instance().IsPlayerInBattle(GetRoleID()));
    if(bRet)
        bRet = !g_ZhanQiMgr.IsInAct(GetRoleID());
    return bRet;
}

bool CPlayer::LeaveDgn(bool bTransDB,const DgnOutConfig& rOutConfig)
{
    _sActionManager.ClearAction(eACTION_DGN);
    DgnOutConfig   sOutConfig(rOutConfig);

    if(sOutConfig.wMapId == 0 )
    {
        sOutConfig.wMapId = _sBaseInfo.wMapID;
        sOutConfig.fPosX =_sBaseInfo.fX;
        sOutConfig.fPosY = _sBaseInfo.fY;
    }
    if(GetPlayerState() == ePlayerLeave)
    {
        SetPoint(SPoint(sOutConfig.fPosX,sOutConfig.fPosY));
        SetCurMapID(sOutConfig.wMapId);
        ClearDgnInfo();
        if(bTransDB)
        {
            UpdateBaseInfo2DB();
        }
        return true;
    }
    if(!JumpMap(sOutConfig.wMapId,SPoint(sOutConfig.fPosX,sOutConfig.fPosY)))
    {
        LOG_CRI << "Player Jump To Previous Dungeon Map fails! PreMapID: " <<_sBaseInfo.wMapID << ", RoleID: " << _qwRoleID;
        return false;
    }
    else
    {
        ClearDgnInfo();
        if(bTransDB)
        {
            UpdateBaseInfo2DB();
        }
    }
    return true;
}

bool CPlayer::IsTrumpActived(UINT16 wItemID) const 
{ 
    return GetFighterManager()->GetTrumpSlots().IsTrumpActived(wItemID);
}

void CPlayer::SetDgnID(UINT16 wDgnID)
{
    _sBaseInfo.dwDgnTypeID = wDgnID;
}

void CPlayer::SetDgnInstID(UINT64 qwInstID)
{
    _sBaseInfo.qwDgnId = qwInstID;
}

bool CPlayer::PHPSetLevel(UINT16 wLevel)
{
    wLevel = wLevel < 1 ? 1 : wLevel;

    UINT64 qwExp = CExpMgr::GetLevelMin(wLevel);
    UINT64 qwOldExp = CExpMgr::GetLevelMin(GetLevel());
    while (!qwExp && wLevel > 1)
        qwExp = CExpMgr::GetLevelMin(--wLevel);

    if (qwOldExp <= qwExp)
        AddExp(qwExp - qwOldExp);
    else
        SubExp(qwOldExp - qwExp);

    return true;
}

bool CPlayer::IsInDungeon()
{
    if(GetDgnInstID() != 0)
        return true;
    return false;
}

void CPlayer::ClearDgnInfo()
{
    SetDgnInstID(0);
}

void CPlayer::SetMainFighter(const CFighterPtr& pFighter)
{
    if (_pMainFighter.lock())
        return;
    _pMainFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
    _pFighterManager->GetFashionSlots().SetFighter(pFighter);

}

CHeroFighterPtr CPlayer::GetMainFighter()
{
    // XXX: 主将是不可能会被换掉的，否则就天下大乱了
    if (!_pMainFighter.lock())
        _pMainFighter = dynamic_pointer_cast<CHeroFighter>(_pFighterManager->GetMainFighter());
    return _pMainFighter.lock();
}

CHeroFighterPtr CPlayer::GetMainFighter() const
{
    return _pMainFighter.lock();
}

UINT16 CPlayer::GetPlayerFighterID() const
{
    if (_pMainFighter.lock())
        return _pMainFighter.lock()->GetID();
    else
        return 0;
}

CFighterPtr CPlayer::GetFighterByInstID(UINT64 qwInstID)
{
    if (!qwInstID)
        return NULL;
    if (_pMainFighter.lock() != NULL && qwInstID == _pMainFighter.lock()->GetInstID())
        return _pMainFighter.lock();
    return _pFighterManager->GetFighterByInstID(qwInstID);
}

CFighterPtr CPlayer::GetFighterByID(UINT16 wFighterID)
{
    if (!wFighterID)
        return NULL;
    if (_pMainFighter.lock() != NULL && wFighterID == _pMainFighter.lock()->GetFighterID())
        return _pMainFighter.lock();
    return _pFighterManager->GetFighterByID(wFighterID);
}

bool CPlayer::HasFighter(UINT16 wFighterID)
{
    return _pFighterManager->HasFighter(wFighterID);
}

bool CPlayer::AddFighterFromDB(CFighterPtr& pFighter)
{
    _pFighterManager->AddFighterFromDB(pFighter);
    if (pFighter->IsMainFighter())
        SetMainFighter(pFighter);
    return true;
}

bool CPlayer::RecruitFighterByForce(UINT16 wFighterID)
{
    if (wFighterID <= SParamConfig::dwMainFigherIDMax)
        return false;
    bool bRes = false;
    if (GetFighterManager())
    {
        bRes = GetFighterManager()->GetFighterForce(wFighterID);
        if (bRes)
            SendPkg(g_FighterProtS.BuildPkg_RecruitSuccNotify(wFighterID));
    }
    return bRes;
}

// ===  FUNCTION  ======================================================================
//         Name:  ToBattleFighterGetBattleFighterList
//  Description:  获取所有将的BattleFighter对象
// =====================================================================================
UINT64 CPlayer::GetBattleFighterList(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType)
{
    if (!_pFighterManager)
        return 0;

    UINT64 qwMainInstID = _pFighterManager->GetBattleFighters(vecBattleFighter, eBattleType);

    UINT32 dwTotalBP = GetBattlePoint();
    UINT32 dwMainBP  = 0;

    if (GetMainFighter())
        dwMainBP = GetMainFighter()->GetBattlePoint();

    bool bBPUpdated = false;

    if (dwTotalBP != _dwTotalBattelPoint)
    {
        _dwTotalBattelPoint = dwTotalBP;

        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(dwTotalBP);
        OnEvent(eEventType_FightingPowerChanging, vecParam);
        bBPUpdated = true;
    }

    if (dwMainBP != _dwMainFighterBP)
    {
        _dwMainFighterBP = dwMainBP;

        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(dwMainBP);
        OnEvent(eEventType_FightingPowerChangingPlayer, vecParam);
        bBPUpdated = true;
    }

    if (bBPUpdated)
    {
        //Event事件
        TVecINT32 vecParam;
        TVecUINT16 vecFighterID;
        _pFighterManager->GetRecruitedFigterIDList(vecFighterID);
        for (size_t i = 0; i < vecFighterID.size(); ++ i)
        {
            vecParam.push_back(_pFighterManager->GetHeroFighterBattlePoint(vecFighterID[i]));
        }
        OnEvent(eEventType_FightingPowerChangingAnyFigher, vecParam);

        if(eBattleType != EGuardEMei)
        {
            UpdateBattlePointRank();
        }
    }

    return qwMainInstID;
}		// -----  end of function ToBattleFighterGetBattleFighterList  ----- //

//保存当前战斗散仙数据
void CPlayer::SaveBattleFighterInfo(EBattleType eBattleType,TVecBattleFighterPtr& vecBattleFighter)
{
    if(_pFightHeroInfoMgr) 
        _pFightHeroInfoMgr->SaveBattleFighterInfo(eBattleType,vecBattleFighter);
}


IBattleFighterPtr CPlayer::GetSceneFighter()
{
    return CMapMgr::ToBattleFighter(GetCurMapID());
}

UINT32 CPlayer::GetCurrHP()
{
    if (!_pFighterManager)
        return 0;
    return _pFighterManager->GetFightersCurrHP();
}

UINT32 CPlayer::GetMaxHP()
{
    if (!_pFighterManager)
        return 0;
    return _pFighterManager->GetFightersMaxHP();
}

UINT32 CPlayer::GetMaxHP2()
{
    if (!_pFighterManager)
        return 0;
    return _pFighterManager->GetFightersMaxHP2();
}

void CPlayer::RegenAllHP()
{
    if (!_pFighterManager)
        return;
    _pFighterManager->RegenAllHP();
}

bool CPlayer::RecoverFighters(TVecBattleFighterPtr& vecBattleFighter)
{
    if (!_pFighterManager)
        return false;
    return _pFighterManager->RecoverFighters(vecBattleFighter);
}

void CPlayer::AddCurrHP(UINT32 dwHP)
{
    if (!_pFighterManager || !dwHP)
        return;
    _pFighterManager->AddFightersCurrHP(dwHP);
}

void CPlayer::AddCurrHPPer(float fFactor)
{
    if (!_pFighterManager || !fFactor)
        return;
    _pFighterManager->AddFightersCurrHPPer(fFactor);
}

//玩家总战斗力
UINT32 CPlayer::GetBattlePoint() const
{
    CFighterManagerPtr pFighterManager = GetFighterManager();
    if(!pFighterManager)
        return 0;
    return pFighterManager->GetBattlePoint();
}

void CPlayer::GetUserCenterInfo(NGame2CenterComm::SUserEnterInfo &info)
{
    info.wHeroID = _pMainFighter.lock()->GetFighterID();
    info.eSex = _sBaseInfo.eSex;
    info.eCareer = _sBaseInfo.eCareer;
    info.strName = _sBaseInfo.strName;
    info.byLevel = _sBaseInfo.byLevel ; //玩家
    info.byNation = _sBaseInfo.byNation; //国家
    info.byGMLvl = _sBaseInfo.byGMLvl; //GM权限
    info.dwTotalRecharge = _sBaseInfo.dwTotalRecharge; //充值金额
    info.dwCreateTime = _sBaseInfo.dwCreateTime; //创角时间
    info.dwLoginTime = _sBaseInfo.dwLoginTime; //上次登陆时间
    info.dwOfflineTime = _sBaseInfo.dwOfflineTime; //上次下线时间
    info.dwLockExpireTime = _sBaseInfo.dwLockExpireTime; //被封禁结束时间
    info.dwForbExpireTime = _sBaseInfo.dwForbExpireTime; //被禁言结束时间
    info.dwGold = _sBaseInfo.dwGold + _sBaseInfo.dwFreeGold; //仙石(充值+免费)
    info.dwSilver = _sBaseInfo.dwSilver; //银币
    info.dwCoupon = _sBaseInfo.dwCoupon; //礼券
    info.dwSoul = _sBaseInfo.dwSoul; //魂魄
    info.dwPrestige = _sBaseInfo.dwPrestige; //声望
    info.dwHonor = _sBaseInfo.dwHonor; //荣誉
    info.dwAction = _sBaseInfo.dwAction; //体力
    TITLE_DATA::CharToVecNum(info.vecOwnTitle,_sBaseInfo.szOwnTitle);
    TITLE_DATA::CharToVecNum(info.vecEquipTitle,_sBaseInfo.szEquipTitle);
    info.byDomain = _sBaseInfo.byDomain; //渠道
    info.byDomainLvl = _sBaseInfo.byDomainLvl; //渠道等级
    info.byDisplayLvl = _sBaseInfo.byDisplayLvl; //显示等级
    info.byDomainYear = _sBaseInfo.byDisplayLvl; //年费
    info.szOpenId = _sBaseInfo.szOpenId ; //szOpenId
    info.szOpenKey = _sBaseInfo.szOpenKey; //szOpenKey
    info.qwInvitedID = _sBaseInfo.qwInvitedID; //邀请
    info.byWallow = _sBaseInfo.byWallow; //防沉迷
    info.strSign = _sBaseInfo.strSign; //签名
    info.wMood = _sBaseInfo.wMood; //心情表情
    info.qwInvitedID = _sBaseInfo.qwInvitedID; //被邀请好友id
    info.byVIPLvl = GetUser().GetVIPLevel(); //VIP等级
    info.dwFighterPower = GetBattlePoint();
    info.szIconAppear = _sBaseInfo.szIcon;
    info.byYDLvl = GetUser().GetYelloDiamondLevel();
    info.vecPlatform = GetUser().GetPlatformParam();
    if (_pMainFighter.lock())
    {
        info.byQuality = _pMainFighter.lock()->GetColor();
        info.wPlayerFighterID = _pMainFighter.lock()->GetID();
    }

    //临时战斗力 用于OnEvent
    _dwTotalBattelPoint = info.dwFighterPower;
    if (GetMainFighter())
        _dwMainFighterBP = GetMainFighter()->GetBattlePoint();
}

bool CPlayer::HasOwnTitle(UINT16 wTitle)
{
    return TITLE_DATA::TestNum(wTitle,_sBaseInfo.szOwnTitle);
}

bool CPlayer::CheckIconIsOpen(UINT16 wIcon)
{
    if(CIconAppearMgr::Instance().IsActive(wIcon))
        return TITLE_DATA::TestNum(wIcon,_sBaseInfo.szIconActive); 
    return TITLE_DATA::TestNum(wIcon,_sBaseInfo.szIcon);
}

bool CPlayer::HasEquipTitle(UINT16 wTitle)
{
    return TITLE_DATA::TestNum(wTitle,_sBaseInfo.szEquipTitle);
}

void CPlayer::AddOwnTitle(UINT16 wTitle)//增加拥有的头衔
{ 
    if(!TITLE_DATA::NumTitleIsValid(wTitle))
    {
        return ;
    }
    if(HasOwnTitle(wTitle))
    {
        return;
    }
    TITLE_DATA::AddNum(wTitle,_sBaseInfo.szOwnTitle);
    UpdateBaseInfo2DB();

}

void CPlayer::OpenIcon(UINT16 wIcon)//增加拥有的头衔
{ 
    if(!TITLE_DATA::NumTitleIsValid(wIcon))
    {
        return ;
    }
    if(CheckIconIsOpen(wIcon) || IconIsClose(wIcon))
    {
        return;
    }
    if(!CIconAppearMgr::Instance().IsActive(wIcon))
    {
        TITLE_DATA::AddNum(wIcon,_sBaseInfo.szIcon);
        g_Game2CenterCommC.Send_SynIconAppear(GetRoleID(),_sBaseInfo.szIcon);

    }
    else
    {
        TITLE_DATA::AddNum(wIcon,_sBaseInfo.szIconActive);
    }
    UpdateBaseInfo2DB();
    if(wIcon == ActivityIcon)
    {
        _ActivityPkg.OpenIcon();
    }
    if(wCircleIcon == wIcon)
    {
        GetUser().GetTaskPkg().AcceptCircleTask();
    }
    LOG_CRI<<"wIconID : " << wIcon<<" open.";
}

bool CPlayer::DelIcon(UINT16 wIcon)
{
    if(!TITLE_DATA::NumTitleIsValid(wIcon) || IconIsClose(wIcon))
    {
        return false;
    }
    do{
        if(CIconAppearMgr::Instance().IsActive(wIcon))
        {
            break;
        }
        if(!CheckIconIsOpen(wIcon))
        {
            break;
        }
        TITLE_DATA::DelNum(wIcon,_sBaseInfo.szIcon);
        g_Game2CenterCommC.Send_SynIconAppear(GetRoleID(),_sBaseInfo.szIcon);
        LOG_INF<<"wIconID : " << wIcon<<" close.";
    }while(0);
    TITLE_DATA::AddNum(wIcon,_sBaseInfo.szIconDel);
    UpdateBaseInfo2DB();
    return true;
}
bool CPlayer::IconIsClose(UINT16 wIcon)
{
    if(!TITLE_DATA::NumTitleIsValid(wIcon))
    {
        return false;
    }
    return TITLE_DATA::TestNum(wIcon,_sBaseInfo.szIconDel);
}

void CPlayer::DelOwnTitle(UINT16 wTitle)//删除拥有的头衔
{
    if(!TITLE_DATA::NumTitleIsValid(wTitle))
    {
        return ;
    }
    if(!HasOwnTitle(wTitle))
    {
        return;
    }
    if(HasEquipTitle(wTitle))
    {
        TITLE_DATA::DelNum(wTitle,_sBaseInfo.szEquipTitle);
    }
    TITLE_DATA::DelNum(wTitle,_sBaseInfo.szOwnTitle);
    UpdateBaseInfo2DB();

}

void CPlayer::GetOwnTitle(TVecUINT16 &vecOwnTitle)//获取拥有的头衔
{
    TITLE_DATA::CharToVecNum(vecOwnTitle,_sBaseInfo.szOwnTitle);
}

void CPlayer::AddEquipTitle(UINT16 wTitle)//增加装备的头衔
{
    if(!TITLE_DATA::NumTitleIsValid(wTitle))
    {
        return ;
    }
    if(!HasOwnTitle(wTitle))
    {
        return;
    }
    if(HasEquipTitle(wTitle))
    {
        return;
    }
    TITLE_DATA::AddNum(wTitle,_sBaseInfo.szEquipTitle);
    UpdateBaseInfo2DB();

}

void CPlayer::DelEquipTitle(UINT16 wTitle)//删除装备的头衔
{
    if(!TITLE_DATA::NumTitleIsValid(wTitle))
    {
        return ;
    }
    if(!HasEquipTitle(wTitle))
    {
        return;
    }
    TITLE_DATA::DelNum(wTitle,_sBaseInfo.szEquipTitle);
    UpdateBaseInfo2DB();

}

void CPlayer::GetEquipTitle(TVecUINT16 &vecEquipTitle)//获取装备的头衔
{
    TITLE_DATA::CharToVecNum(vecEquipTitle,_sBaseInfo.szEquipTitle);
}

void CPlayer::GetOpenIcon(TVecUINT16 &vecIcon,bool bActivity)//获取开放的功能
{
    if(!bActivity)
    {
        TITLE_DATA::CharToVecNum(vecIcon,_sBaseInfo.szIcon);
    }
    else
    {
        TITLE_DATA::CharToVecNum(vecIcon,_sBaseInfo.szIconActive);
    }
}

void CPlayer::CheckLastPend(UINT8 bySource)
{
    if( bySource == PendALL )
    {
        for(auto iter = _mapPendRes.begin(); iter != _mapPendRes.end();iter ++)
        {

            TVecResource &vecPendRes = iter->second;
            for(auto it = vecPendRes.begin();it != vecPendRes.end();it++)
            {
                SResource &rRes = *it;
                SPendRes res;
                res.byResType = rRes._eRes;
                res.dwValue = rRes._dwValue;
                res.bySource = iter->first;
                string strData;
                COutArchive iar(strData);
                iar << res;
                g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypePendRes, eOpDel, strData);
            }

            if(!vecPendRes.empty())
            {
                CStore::AddResource(GetUser(),vecPendRes,NLogDataDefine::ItemFrom_Pend);
            }
        }
        _mapPendRes.clear();
        for(auto iter = _mapLastLoot.begin() ;iter != _mapLastLoot.end();iter ++)
        {
            TVecItemGenInfo &vecLastLoot  = iter->second;
            TVecAddItemMsg vecItemMsg;
            for(auto it = vecLastLoot.begin();it != vecLastLoot.end();it++)
            {
                const SItemGenInfo& rItemGenInfo = *it;
                SItemInfo* pItemInfo = CItemMgr::GetItemConfig(it->wItemID);
                if (!pItemInfo)
                    continue;
                SAddItemMsg rAddItemMsg;
                rAddItemMsg.wItemID = rItemGenInfo.wItemID;
                rAddItemMsg.byQuality = rItemGenInfo.byQuality;
                rAddItemMsg.wCount = rItemGenInfo.dwCount;
                vecItemMsg.emplace_back(std::move(rAddItemMsg));
            }
            GetUser().SendPkg(g_ItemProtS.BuildPkg_AddItemSystemMsg(vecItemMsg)); 

        }
        _mapLastLoot.clear();
        for(auto iter = _mapLastParam.begin();iter != _mapLastParam.end();iter++)
        {
            TVecUINT32 & rVec = iter->second;
            if(rVec.size() >= 2)
            {

                DoLastParam(iter->first,rVec[0],rVec[1]);
            }

        }
        _mapLastParam.clear();

    }

    auto iter = _mapPendRes.find(bySource);
    if(iter != _mapPendRes.end())
    {
        TVecResource &vecPendRes = iter->second;
        for(auto it = vecPendRes.begin();it != vecPendRes.end();it++)
        {
            SResource &rRes = *it;
            SPendRes res;
            res.byResType = rRes._eRes;
            res.dwValue = rRes._dwValue;
            res.bySource = iter->first;
            string strData;
            COutArchive iar(strData);
            iar << res;
            g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypePendRes, eOpDel, strData);
        }

        if(!vecPendRes.empty())
        {
            CStore::AddResource(GetUser(),vecPendRes,NLogDataDefine::ItemFrom_Pend);
        }
        _mapPendRes.erase(iter);
    }
    auto pos = _mapLastLoot.find(bySource);
    if(pos != _mapLastLoot.end())
    {
        TVecItemGenInfo &vecLastLoot  = pos->second;
        TVecAddItemMsg vecItemMsg;
        for(auto it = vecLastLoot.begin();it != vecLastLoot.end();it++)
        {
            const SItemGenInfo& rItemGenInfo = *it;
            SItemInfo* pItemInfo = CItemMgr::GetItemConfig(it->wItemID);
            if (!pItemInfo)
                continue;
            SAddItemMsg rAddItemMsg;
            rAddItemMsg.wItemID = rItemGenInfo.wItemID;
            rAddItemMsg.byQuality = rItemGenInfo.byQuality;
            rAddItemMsg.wCount = rItemGenInfo.dwCount;
            vecItemMsg.emplace_back(std::move(rAddItemMsg));
        }
        GetUser().SendPkg(g_ItemProtS.BuildPkg_AddItemSystemMsg(vecItemMsg)); 

        _mapLastLoot.erase(pos);
    }
    auto itr = _mapLastParam.find(bySource);
    if(itr != _mapLastParam.end())
    {
        TVecUINT32 & rVec = itr->second;
        if(rVec.size() >= 2)
        {

            DoLastParam(itr->first,rVec[0],rVec[1]);
        }
        _mapLastParam.erase(itr);
    }



}

void CPlayer::SetSign(const std::string& strSign)
{
    _sBaseInfo.strSign = strSign;
    UpdateBaseInfo2DB();
}

void CPlayer::SetMood(UINT16 wMood)
{
    _sBaseInfo.wMood = wMood;
    UpdateBaseInfo2DB();
}

void CPlayer::SetYDLevel(UINT8 byLevel)
{
    _sBaseInfo.byYDLevel = byLevel;
    UpdateBaseInfo2DB();

}

void CPlayer::SetGuide(const std::string& strGuide)
{
    _sBaseInfo.strGuide = strGuide;
    UpdateBaseInfo2DB();
}

void CPlayer::SetPackCapacity(UINT16 wCapacity)
{
    _sBaseInfo.wBagMax = wCapacity;
}

void CPlayer::SetDepotCapacity(UINT16 wCapacity)
{
    _sBaseInfo.wDepotMax = wCapacity;
}

void CPlayer::SetAchievementLevel(UINT16 wAchievementLevel)
{
    _sBaseInfo.wAchievementLevel = wAchievementLevel;
    UpdateBaseInfo2DB();
}

UINT16 CPlayer::GetAchievementLevel()
{
    return _sBaseInfo.wAchievementLevel;
}

void CPlayer::SetCollectionLevel(UINT16 wCollectLevel)
{
    _sBaseInfo.wCollectLevel = wCollectLevel;
    UpdateBaseInfo2DB();
}

UINT16 CPlayer::GetCollectionLevel()
{
    return _sBaseInfo.wCollectLevel;
}

//0点事件,不在线玩家登陆后执行这事件
void CPlayer::OnMidNight(ETimePointType eType)
{

    switch(eType)
    {
        case eTimePointDaily19:
            {
                //玩家不在线
                if(_bInLoad)
                    return;

                CUser& rUser = GetUser();
                CGameVar& rCGameVar = rUser.GetVars();
                //UINT32 dwValue = rCGameVar.GetVar(NVarDefine::ePlayerVarDayEvent);
                rCGameVar.SetVar(NVarDefine::ePlayerVarDayEvent,1,3600*19);

                //防止此函数执行两遍
                if( time(NULL) - _tLastMidNight < 600)
                {
                    return;
                }
                _tLastMidNight = time(NULL);

                //ToDo:

                SetPrizeDemonFloorID(GetTopDemonFloorID());

                SendPkg(g_DemonTowerSvrS.BuildPkg_DayPrizeResetNotify(GetPrizeDemonFloorID()));

                SendCenterSvrPkg(g_Game2CenterDemonTowerC.BuildPkg_OnPlayerReset(GetUserID()));
            }
            break;
        case eTimePointDaily0: //不在线玩家不执行
            {
                { //登陆事件
                    TVecINT32 vecParam;
                    vecParam.push_back(1);
                    OnEvent(eEventType_PlayerLogin,vecParam);
                }

                g_FeedBackMgr.OnPlayerMidNight(*this);

                _GroupTaskPkg.SendAllInfoTask(); 
                _YaMenTaskPkg.SendAllInfoTask();
                _ActivityPkg.SendAllInfoActivity();
                _DgnPkg.UpdateTeamAward();
                GetUser().GetTaskPkg().AcceptTaskForZero();
                GetUser().GetTaskPkg().SendCircleInfo();
                _pLoginPkgMgr->SendPkgInfoFor0();
                //GetUser().CheckVIPGrowthValue();
                GetUser().SendMonthCardAward();
                GetUser().SendVIPInfoToClt();
                _DgnPkg.SendDgnInfoForAll();
                if(_pBattleArrayMgr)
                {
                    _pBattleArrayMgr->OnMidNight();
                }
                if(_pShengLing)
                    _pShengLing->SyncData();
                if(_pFenbaoyan)
                    _pFenbaoyan->CheckTime();
                g_EveryDayRechargeMgr.CheckIconIsOpen(GetUser(),true);
                GetUser().SendPkg(g_MiscProtS.BuildPkg_SyncRechargeToday(GetUser().GetVars().GetVar(NVarDefine::ePlayerVarRechargeToday)));
            }
            break;
        default:
            break;
    }
}

//0点或者是隔天登陆调用(XXX 只调用一次)
void CPlayer::OnDayPass()
{
    LOG_INF<<"roleId:"<<GetRoleID()<<"OnDayPass";
    CShopItemMgrPtr pShopItemMgr = GetShopItemMgr();
    if(pShopItemMgr)
    {
        pShopItemMgr->ClearItemCount();
    }

    if(_pAutoStoreMgr)
    {
        _pAutoStoreMgr->OnMidNight();
    }

    if(_pBeautyMgr)
    {
        _pBeautyMgr->OnMidNight();
    }
    //XXX 蜀山基金统计累计登陆天数
    if(!IconIsClose(100))
    {
        LOG_CRI<<"ShushanFoundaton Icon(100) is Open.";
        if (!GetUser().CanDelShushanFoundIcon())
        {
            UINT64 qwValue = GetUser().GetVars().GetVar(ePlayerVarShushanFoundInfo);
            UINT64 qwDays  = GetUser().GetVars().GetVar(ePlayerVarShushanFoundLoginDays);
            for (int i = 0; i < 4; ++ i)
            {
                UINT16 wValue = GET_BIT_16(qwValue, i);
                UINT8  byDay  = GET_BIT_8(qwDays, i);
                if (GET_BIT(wValue, 0))
                {
                    if (byDay < 255)
                        ++ byDay;
                    qwDays = SET_BIT_8(qwDays, i, byDay);
                }
            }
            GetUser().GetVars().SetVar(NVarDefine::ePlayerVarShushanFoundLoginDays, qwDays);
            GetUser().SendShushanFoundInfo();
            LOG_CRI<<"ShushanFoundation SetDay qwDays ="<<qwDays;
        }
        else
            CIconAppearMgr::Instance().DelAction(*GetUserPtr(), 100);
    }
}

//镇妖塔相关
UINT32 CPlayer::GetTopDemonFloorID()
{
    LOG_INF<<"GetTopDemonFloorID:"<<_sBaseInfo.dwDemonTowerFloorID;
    return _sBaseInfo.dwDemonTowerFloorID & 0xFFFF;
}

void CPlayer::SetTopDemonFloorID(UINT32 dwDemonFloorID)
{
    _sBaseInfo.dwDemonTowerFloorID = dwDemonFloorID;
    UpdateBaseInfo2DB();
}

UINT32 CPlayer::GetPrizeDemonFloorID()
{
    return _sBaseInfo.dwDemonTowerPrizeFloorID&0xFFFF;
}

void CPlayer::SetPrizeDemonFloorID(UINT32 dwDemonFloorID)
{
    UDemonTowerPrize uDemonTowerPrize;
    uDemonTowerPrize.dwPrizeID = _sBaseInfo.dwDemonTowerPrizeFloorID;
    uDemonTowerPrize.oPrizeID.wTopPrizeID = dwDemonFloorID;

    _sBaseInfo.dwDemonTowerPrizeFloorID = uDemonTowerPrize.dwPrizeID;
    UpdateBaseInfo2DB();
}

//镇妖塔已领奖层数
UINT32 CPlayer::GetLayerPrizeDemonFloorID()
{
    UDemonTowerPrize uDemonTowerPrize;
    uDemonTowerPrize.dwPrizeID = _sBaseInfo.dwDemonTowerPrizeFloorID;

    return uDemonTowerPrize.oPrizeID.wLayerPrizeID;
}

void CPlayer::SetLayerPrizeDemonFloorID(UINT32 dwDemonFloorID)
{
    UDemonTowerPrize uDemonTowerPrize;
    uDemonTowerPrize.dwPrizeID = _sBaseInfo.dwDemonTowerPrizeFloorID;
    uDemonTowerPrize.oPrizeID.wLayerPrizeID = dwDemonFloorID;
    _sBaseInfo.dwDemonTowerPrizeFloorID = uDemonTowerPrize.dwPrizeID;

    UpdateBaseInfo2DB();

}

//锁妖塔采集相关
void  CPlayer::SetDemonFloorGather()
{

    LOG_INF<<"SetDemonFloorGather dwDemonTowerFloorID:"<<_sBaseInfo.dwDemonTowerFloorID<<"->|"<<(_sBaseInfo.dwDemonTowerFloorID | 0x10000);
    _sBaseInfo.dwDemonTowerFloorID |= 0x10000;
    UpdateBaseInfo2DB();
}

void  CPlayer::OnDemonFloorGathered()
{
    _sBaseInfo.dwDemonTowerFloorID &= 0xFFFF;
    LOG_INF<<"OnDemonFloorGathered:"<<_sBaseInfo.dwDemonTowerFloorID;
    UpdateBaseInfo2DB();
}

bool  CPlayer::IsSpawGather()
{
    UINT32 dwTag = _sBaseInfo.dwDemonTowerFloorID & 0x10000;
    LOG_INF<<"IsSpawGather:"<<dwTag;
    return (0 != dwTag);
}

void CPlayer::RobotHorseBoost(UINT32 dwMode)
{
    CHorseMgrPtr pHorseMgr = GetHorseMgr();
    if(pHorseMgr)
    {
        do
        {
            UINT32 dwActiveID = CRandom::RandInt(1,6);
            pHorseMgr->ActiveHorse(dwActiveID, true);
            pHorseMgr->SetHorseStatus(dwActiveID, eHorseStatusMounted);
        }while(false);
    }
}

void CPlayer::AddFashionItemForRobot()
{
    TVecItemGenInfo vecItem;
    for(size_t i=600; i<604; ++i)
    {
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.wItemID = i;
        oItemGenInfo.dwCount = 1;
        vecItem.push_back(oItemGenInfo);
    }
    if(GetUserPtr())
    {
        CStore& rStore = GetUserPtr()->GetPack();
        rStore.AddItem(vecItem, (NLogDataDefine::ItemFrom_System));
    }
}

//RobotBoost
void CPlayer::RobotBoost(UINT32 dwMode)
{
    LevelBoost(dwMode);
    RobotTrumpBoost(dwMode);
    RobotFormationBoost(dwMode);
    RobotHorseBoost(dwMode);
    RobotFashionBoost(dwMode);
    if (GetUserPtr())
        GetUserPtr()->GetTaskPkg().GMAddTask(SParamConfig::wGulidFinTask);
    UINT16 wDgnID[] = {1, 2, 3, 4, 5, 6, 8, 9, 10};
    TVecUINT16 vecDgnID;
    vecDgnID.insert(vecDgnID.begin(), wDgnID, wDgnID + sizeof(wDgnID)/sizeof(UINT16));
    for (auto& rID : vecDgnID)
    {
        GetDgnPkg().PlayerCompleteDgn(rID, 1);//记录玩家完成副本
    }

    UINT16 wIconID[] = {2, 3, 4, 6, 7, 10, 14};
    TVecUINT16 vecIconID;
    vecIconID.insert(vecIconID.begin(), wIconID, wIconID + sizeof(wIconID)/sizeof(UINT16));
    TVecUINT16 vecIconAppear;
    for (auto& rID : vecIconID)
    {
        GetUserPtr()->GetPlayer()->OpenIcon(rID);
        vecIconAppear.push_back(rID);
    }
    CIconAppearMgr::Instance().SynToClientAddIconAppear(*GetUserPtr(),vecIconAppear);
    /* 
       CGameMapPtr pMap = CMapMgr::GetMap(10);
       if(NULL == pMap)
       {
       return ;
       }

       SPoint oPoint(pMap->GetMapInfo().oRealivePoint.fX,pMap->GetMapInfo().oRealivePoint.fY);
       JumpMap(pMap,oPoint,0);
       */
}

// 新手速成
void CPlayer::Boost(UINT32 dwMode)
{
    LevelBoost(dwMode);

    //TrumpBoost(dwMode);
    FormationBoost(dwMode);
    FighterBoost(dwMode);
    CHorseMgrPtr pHorseMgr = GetHorseMgr();
    if(pHorseMgr)
    {
        pHorseMgr->ActiveHorse(1, true);
        pHorseMgr->SetHorseStatus(1, eHorseStatusMounted);
    }
    if (GetUserPtr())
        GetUserPtr()->GetTaskPkg().GMAddTask(SParamConfig::wGulidFinTask);
    UINT16 wDgnID[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    TVecUINT16 vecDgnID;
    vecDgnID.insert(vecDgnID.begin(), wDgnID, wDgnID + sizeof(wDgnID)/sizeof(UINT16));
    for (auto& rID : vecDgnID)
    {
        GetDgnPkg().PlayerCompleteDgn(rID, 1);//记录玩家完成副本
    }

    UINT16 wIconID[] = {2, 3, 4, 6, 7, 10, 14};
    TVecUINT16 vecIconID;
    vecIconID.insert(vecIconID.begin(), wIconID, wIconID + sizeof(wIconID)/sizeof(UINT16));
    TVecUINT16 vecIconAppear;
    for (auto& rID : vecIconID)
    {
        GetUserPtr()->GetPlayer()->OpenIcon(rID);
        vecIconAppear.push_back(rID);
    }
    CIconAppearMgr::Instance().SynToClientAddIconAppear(*GetUserPtr(),vecIconAppear);

}

// 变成超级牛逼的号
void CPlayer::Super()
{
    UINT32 dwMode = 0;
    LevelSuper(dwMode);

    TrumpSuper(dwMode);

    FighterSuper(dwMode);
    CHorseMgrPtr pHorseMgr = GetHorseMgr();
    if(pHorseMgr)
    {
        pHorseMgr->ActiveHorse(1, true);
        pHorseMgr->SetHorseStatus(1, eHorseStatusMounted);
    }
    if (GetUserPtr())
        GetUserPtr()->GetTaskPkg().GMAddTask(SParamConfig::wGulidFinTask);
    UINT16 wDgnID[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    TVecUINT16 vecDgnID;
    vecDgnID.insert(vecDgnID.begin(), wDgnID, wDgnID + sizeof(wDgnID)/sizeof(UINT16));
    for (auto& rID : vecDgnID)
    {
        GetDgnPkg().PlayerCompleteDgn(rID, 1);//记录玩家完成副本
    }
    TVecUINT16 vecIconAppear;
    for (UINT16 wIconID = 1; wIconID < 42; ++wIconID)
    {
        GetUserPtr()->GetPlayer()->OpenIcon(wIconID);
        vecIconAppear.push_back(wIconID);
    }
    CIconAppearMgr::Instance().SynToClientAddIconAppear(*GetUserPtr(),vecIconAppear);

    // 图标解锁
    const TVecUINT16& rvecIconAppearID = CBoostMgr::Instance().GetIconAppearID();
    CIconAppearMgr::Instance().SynToClientAddIconAppear(*GetUserPtr(),rvecIconAppearID);
}

void CPlayer::LevelBoost(UINT32 dwMode)
{
    if (_pFighterManager)
    {
        _pFighterManager->AddToLevel(30);
        _pFighterManager->AddExp(76866);
    }
}

// 升到100级
void CPlayer::LevelSuper(UINT32 dwMode)
{
    if (_pFighterManager)
        _pFighterManager->AddToLevel(CBoostMgr::Instance().GetPlayerLevel());
}

// 新手法宝解锁
void CPlayer::TrumpBoost(UINT32 dwMode)
{
    if (!_pMainFighter.lock())
        return;
    CTrumpSlots& rTrumpSlot = GetFighterManager()->GetTrumpSlots();
    rTrumpSlot.Boost(_pMainFighter.lock()->GetJob());
}

// 法宝全部解锁
void CPlayer::TrumpSuper(UINT32 dwMode)
{
    if (!_pMainFighter.lock())
        return;
    CTrumpSlots& rTrumpSlot = GetFighterManager()->GetTrumpSlots();
    rTrumpSlot.SuperBoostObjects();
}

void CPlayer::RobotFashionBoost(UINT32 dwMode)
{
    /*
       UINT16 wItemIDForW = 0;
       UINT16 wItemIDForD = 0;
       size_t index = CRandom::RandInt(0,1);
       switch (GetPlayerFighter()->GetJob())
       {
       case ECAREER_RU:
       {
       switch(index)
       {
       case 0:
       {
       wItemIDForW = 6508;
       wItemIDForD = 6509;
       }
       break;
       case 1:
       {
       wItemIDForW = 6516;
       wItemIDForD = 6517;
       }
       break;
       default:
       break;
       }
       }
       break;
       case ECAREER_SHI:
       {
       switch(index)
       {
       case 0:
       {
       wItemIDForW = 6510;
       wItemIDForD = 6511;
       }
       break;
       case 1:
       {
       wItemIDForW = 6518;
       wItemIDForD = 6519;
       }
       break;
       default:
       break;
       }
       }
       break;
       case ECAREER_DAO:
       {
       switch(index)
       {
       case 0:
       {
       wItemIDForW = 6512;
       wItemIDForD = 6513;
       }
       break;
       case 1:
       {
       wItemIDForW = 6520;
       wItemIDForD = 6521;
       }
       break;
       default:
       break;
       }
       }
       break;
       case ECAREER_MO:
       {
    switch(index)
    {
        case 0:
            {
                wItemIDForW = 6514;
                wItemIDForD = 6515;
            }
            break;
        case 1:
            {
                wItemIDForW = 6522;
                wItemIDForD = 6523;
            }
            break;
        default:
            break;
    }
}
break;
default:
break;
}
//武器
GetPlayerFighter()->GetFashions().AdoptFashion(wItemIDForW);
CItemPtr pItemW = GetPlayerFighter()->GetFashions().GetSlotByID(wItemIDForW);
if (!pItemW)
    return;
    GetPlayerFighter()->GetFashions().ActiveFashion(pItemW->GetInstID());
    //衣服
    GetPlayerFighter()->GetFashions().AdoptFashion(wItemIDForD);
    CItemPtr pItemD = GetPlayerFighter()->GetFashions().GetSlotByID(wItemIDForD);
if (!pItemD)
    return;
    GetPlayerFighter()->GetFashions().ActiveFashion(pItemD->GetInstID());
    */
    }

//robot法宝解锁
void CPlayer::RobotTrumpBoost(UINT32 dwMode)
{
    if (!_pMainFighter.lock())
        return;
    CTrumpSlots& rTrumpSlot = GetFighterManager()->GetTrumpSlots();
    rTrumpSlot.RobotBoost(_pMainFighter.lock()->GetJob());
}

// 阵灵阵型超级牛逼
void CPlayer::FormationBoost(UINT32 dwMode)
{
    GetFighterManager()->FormationBoost(dwMode);
}

// 机器人阵灵阵型超级牛逼
void CPlayer::RobotFormationBoost(UINT32 dwMode)
{
    GetFighterManager()->RobotFormationBoost(dwMode);
}

// 招募到超级牛逼的散仙
void CPlayer::FighterBoost(UINT32 dwMode)
{
    UINT16 wFighterID[] = {100, 101, 102};

    for (UINT16 wIndex = 0; wIndex < (sizeof(wFighterID)/sizeof(UINT16)); ++wIndex)
    {
        GetFighterManager()->GetFighterForce(wFighterID[wIndex]);
    }
    GetFighterManager()->HeroFighterBoost(dwMode);
}

// 招募到超级牛逼的散仙
void CPlayer::FighterSuper(UINT32 dwMode)
{
    GetFighterManager()->SuperBoostObjects();
}

// 保存Buff信息
void CPlayer::UpdateBuff2DB(const SDBBuffInfo& rDBBuffInfo, EDataChange eDataChange)
{
    string strData;
    COutArchive iar(strData);
    iar << rDBBuffInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypeBuffInfo, eDataChange, strData);
}

void CPlayer::OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo)
{
    TVecBuffInfo vecInfo;
    vecInfo.push_back(rInfo);
    string strData = g_RoleEventProtS.BuildPkg_BuffNotify(eType, vecInfo);
    SendPkg(strData);
    LOG_WRN << "eType = "<< static_cast<UINT32>(eType) << ", dwBuffTime = " << rInfo.dwBuffTime << ", BuffID:" << rInfo.wBuffID;
    if (rInfo.wBuffID == SParamConfig::wTempVIPPrivilege)
    {
        g_Game2CenterCommC.Send_SyncGameBuffUseInCenter(GetRoleID(), rInfo.wBuffID, rInfo.dwBuffTime+time(NULL));
    }

    //重新计算buffer属性
    BufferRebuildAttr();
}

EBuffOpResult CPlayer::AddBuffLua(UINT16 wBuffID)
{
    return AddBuff(wBuffID);
}

void CPlayer::OnRecv_GatherReq(UINT32 dwGatherId,shared_func<CGatherProtSvr::SGatherReqAck>& fnAck)
{
    GetWalker().Abort();
    if(_sActionManager.CanAddAction(eACTION_GATHER,true) != eACTION_NONE)
    {
        fnAck->eResult = eGatherBusy; 
        return ;
    }
    if(GetGatherID() != 0)
    {
        fnAck->eResult = eGatherBusy; 
        return ;
    }
    EGatherResult eRsult = eGatherSuccess;
    IGatherPtr pGather = CGatherMgr::GetGatherByID(dwGatherId);
    if(pGather == NULL)
    {
        fnAck->eResult = eGatherNotExist; 
        return ;
    }
    eRsult = pGather->CanGater(*this,false);
    if(eRsult != eGatherSuccess)
    {
        fnAck->eResult = eRsult; 
        return ;
    }
    fnAck->eResult = eGatherSuccess;
    fnAck->dwGatherTimer = pGather->AddGather(*this);
}

void CPlayer::OnRecv_CancelGather(shared_func<CGatherProtSvr::SCancelGatherAck>& fnAck)
{
    UINT32 dwGatherId = GetGatherID();
    if(dwGatherId == 0)
    {
        fnAck->eResult = eGatherNotExist; 
        return ;
    }
    IGatherPtr pGather = CGatherMgr::GetGatherByID(dwGatherId);
    if(pGather == NULL)
    {
        SetGatherID(0);
        fnAck->eResult = eGatherNotExist; 
        return ;
    }
    LOG_CRI << "OnRecv_CancelGather";
    pGather->CancelGather(*this);
    fnAck->eResult = eGatherCancel;
}

void  CPlayer::OnRecv_GetGatherInfo(shared_func<CGatherProtSvr::SGetGatherInfoAck>& fnAck)
{
    UINT32 dwGatherId = GetGatherID();
    if(dwGatherId != 0)
    {
        fnAck->dwGtatherId = 0; 
        return ;
    }
    IGatherPtr pGather = CGatherMgr::GetGatherByID(dwGatherId);
    if(pGather == NULL)
    {
        fnAck->dwGtatherId = 0; 
        SetGatherID(0);
        return ;
    }
    fnAck->dwGtatherId = dwGatherId;
    fnAck->dwReserverTimer = pGather->GetReserverTimer();
}

void  CPlayer::PendParam(UINT8 bySource,UINT32 dwValue, UINT32 dwParam)
{

    //类型为0 ，来源参数
    SPendRes res;
    res.dwValue = dwValue;
    res.bySource = bySource;
    res.dwParam = dwParam;
    string strData;
    COutArchive iar(strData);
    iar << res;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypePendRes, eOpAdd, strData);
    _mapLastParam[bySource].push_back(dwValue) ;
    _mapLastParam[bySource].push_back(dwParam);

}

void CPlayer::PendDrop(TVecItemGenInfo &vecItem,TVecResource& vecRes,UINT8 bySource)
{
    CheckLastPend(bySource);
    _mapLastLoot[bySource] = vecItem;
    CStore::MergeResource(vecRes);
    _mapPendRes[bySource] = vecRes;
    for(auto it = vecRes.begin();it != vecRes.end();it++)
    {
        SResource &rRes = *it;
        SPendRes res;
        res.byResType = rRes._eRes;
        res.dwValue = rRes._dwValue;
        res.bySource = bySource;
        string strData;
        COutArchive iar(strData);
        iar << res;
        g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypePendRes, eOpAdd, strData);
    }

}

void CPlayer::FitherToMonster(UINT16 wMonsterGroup)
{
    g_Game2CenterCommC.FighterToOther(GetUserID(),wMonsterGroup,true,NBattleGS::EBTMonster,0,0,0,NULL);
}

void CPlayer::ElasticFrame(UINT16 wMsgID)
{
    SendPkg(g_ChatProtS.BuildPkg_ElasticFrameNotify(wMsgID));
}

void CPlayer::OnDie(CCreature& rKiller)
{
    LOG_CRI << "Player dead";
    AddBuff(eDeadInDgn);
}

void CPlayer::Relive()
{
    LOG_CRI << "Player Relive";
    RemoveBuff(eDeadInDgn); 
}

void CPlayer::CalcPackNextUnlockTime(CStore& rStore)
{
    UINT16 wCapacity = rStore.GetCapacity();
    SBagCostCFG* pCfg = CItemMgr::GetBagCost(wCapacity+1);
    if (!pCfg)
    {
        _sBaseInfo.dwPackNextUnlockTime = 0XFFFFFFFF;
        return;
    }
    _sBaseInfo.dwPackNextUnlockTime = Time::Now()+pCfg->_Time;
    GetUser().SendPkg(g_ItemProtS.BuildPkg_PackNextUnlockTime(pCfg->_Time)); 
    _bPackUnlockNotified = false;
}

UINT32 CPlayer::GetPackUnlockOfflineTime()
{
    UINT32 dwCfgTime = 0;
    SBagCostCFG* pCfg = CItemMgr::GetBagCost(GetUser().GetPack().GetCapacity()+1);
    if (pCfg)
        dwCfgTime = pCfg->_Time;
    UINT32 dwOfflineTime = GetLastOfflineTime();
    UINT32 dwNowTime = time(NULL);
    if (dwOfflineTime && _sBaseInfo.dwPackNextUnlockTime > dwOfflineTime)
    {
        if (_sBaseInfo.dwPackNextUnlockTime - dwCfgTime < dwOfflineTime)
        {
            if (dwNowTime > dwOfflineTime)
                return dwNowTime - dwOfflineTime;
        }
    }
    return 0;
}

bool CPlayer::UnlockPack()
{
    UINT32 dwNow = Time::Now();
    if (!_sBaseInfo.dwPackNextUnlockTime || _sBaseInfo.dwPackNextUnlockTime == 0xFFFFFFFF)
        return false;

    //if (dwNow - GetPackUnlockOfflineTime() < _sBaseInfo.dwPackNextUnlockTime)
    if (dwNow < _sBaseInfo.dwPackNextUnlockTime)
        return false;

    CStore& rStore = GetUser().GetPack();
    if (rStore.Expand(1) != eItemSucceed)
        return false;
    if (_pFighterManager)
        _pFighterManager->SetDirty(eAttrGpBag);

    UpdateBaseInfo2DB();
    return true;
}

void CPlayer::TimerCheck(UINT32 dwNow)
{
    if (_sBaseInfo.dwPackNextUnlockTime
            && _sBaseInfo.dwPackNextUnlockTime != 0xFFFFFFFF
            && dwNow >= _sBaseInfo.dwPackNextUnlockTime)
    {
        //if (!_bPackUnlockNotified && dwNow - GetPackUnlockOfflineTime() >= _sBaseInfo.dwPackNextUnlockTime)
        if (!_bPackUnlockNotified && dwNow >= _sBaseInfo.dwPackNextUnlockTime)
        {
            GetUser().SendPkg(g_ItemProtS.BuildPkg_PackNextUnlockTime(0)); 
            _bPackUnlockNotified = true;
        }
    }
    _TitlePkg.TimerCheck(dwNow);
    /*
       {   //VIP特权是否过期
       UINT32 dwEndTime = GetUser().GetVars().GetVar(NVarDefine::ePlayerVIPEndTime);
       if (dwEndTime && dwNow > dwEndTime)     //VIP特权过期
       GetUser().SetVIPLevel(0);
       }
       */
    if(_pEnergyMgr)
    {
        _pEnergyMgr->TimerCheck(dwNow);
    }

    if(_pTreasureHunt)
    {
        _pTreasureHunt->THTimerCheck(dwNow);
    }

    if(_pGuardEMei)
    {
        _pGuardEMei->GEMSweepTimerCheck(dwNow);
    }

    CUser& rUser = GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    if(0 == rCGameVar.GetVar(NVarDefine::ePlayerZeroDay))
    {
        OnDayPass();
        rCGameVar.SetVar(NVarDefine::ePlayerZeroDay,1);
    }
}

//重新计算行走速度  
void CPlayer::CalSpeed(bool bInit)
{

    UINT32 dwOldSpeed = _dwSpeed;
    _dwSpeed = PLAYER_BASESPEED;
    if(_pHorseMgr)
    {
        if(_pHorseMgr->GetHorseSpeed())
        {
            _dwSpeed = _pHorseMgr->GetHorseSpeed();
        }
        else
        {
            _dwSpeed = PLAYER_BASESPEED;
        }
    }

    if(bInit)
    {
        SendPkg(g_HorseSvrS.BuildPkg_SpeedChangeNotify(_dwSpeed));

    }
    else if(dwOldSpeed != _dwSpeed)
    {
        SendPkg(g_HorseSvrS.BuildPkg_SpeedChangeNotify(_dwSpeed));

    }

    //LOG_CRI<<"CalSpeed!!!:"<<_dwSpeed;
}

UINT32 CPlayer::GetTotalActivity()
{
    return _sBaseInfo.dwActivity;
}

void   CPlayer::SetTotalActivity(UINT32 dwTotalActivity)
{
    _sBaseInfo.dwActivity = dwTotalActivity;
    UpdateBaseInfo2DB();
}

void CPlayer::SetGatherID(UINT32 dwGatherID)
{
    if(dwGatherID != 0)
    {
        _sActionManager.AddAction(eACTION_GATHER);
    }
    else
    {
        _sActionManager.ClearAction(eACTION_GATHER);
    }
    _dwGatherID = dwGatherID;
}

UINT32 CPlayer::GetGatherID()
{
    return _dwGatherID;
}

UINT64 CPlayer::GetSitToGatherPlayer()
{

    return _sBaseInfo.qwSittingPlayer;
}

void  CPlayer::SetSitToGatherPlayer(UINT64 qwRoleID,bool bNotice)
{
    if(_sBaseInfo.qwSittingPlayer == qwRoleID)
    {
        return ;
    }
    UINT64 qwOldRoleID =  _sBaseInfo.qwSittingPlayer;
    _sBaseInfo.qwSittingPlayer = qwRoleID;
    UpdateBaseInfo2DB();
    if(!bNotice)
        return ;
    if(!_sActionManager.HasAction(eACTION_SIT))
        return ;
    if(qwRoleID == 0 )
    {
        if(qwOldRoleID != 0)//双修变单修结算
        {
            UINT32 dwTimer = GetUser().GetVars().GetVar(NVarDefine::ePlayerVarSittingTime);
            if(dwTimer != 0)
            {
                dwTimer  = time(NULL) - dwTimer;
                TVecResource vecRes;
                _sActionManager.CalSittingAward(vecRes,dwTimer,true);
                if(!vecRes.empty())
                {
                    CStore::AddResource(GetUser(),vecRes,NLogDataDefine::ItemFrom_Siting);
                    SendPkg(g_SittingProtS.BuildPkg_CancelSittingOffLine(1,vecRes,dwTimer));
                    LOG_INF <<GetRoleID()<< "双修变单修收益 :" <<"Timer:" << dwTimer << "double :" << qwOldRoleID;
                    CStore::PrintResInfo(vecRes);
                }

            }

        }
        //通告处于单修
        GetUser().GetVars().SetVar(NVarDefine::ePlayerVarSittingTime,time(NULL));
        NMapProt::TVecPlayerAppear vecAppear; 
        SendPkg(g_SittingProtS.BuildPkg_UpdateSitting(1,vecAppear,time(NULL)));
        CGameMapPtr pMap = GetMap();
        if(pMap)
            pMap->AppearToSurround(*this);
        LOG_INF <<GetRoleID() << "开始单修";

    }
    else 
    {
        if(qwOldRoleID == 0)//单修变双修结算
        {
            UINT32 dwTimer = GetUser().GetVars().GetVar(NVarDefine::ePlayerVarSittingTime);
            if(dwTimer != 0)
            {
                dwTimer  = time(NULL) - dwTimer;
                TVecResource vecRes;
                _sActionManager.CalSittingAward(vecRes,dwTimer,false);
                if(!vecRes.empty())
                {
                    CStore::AddResource(GetUser(),vecRes,NLogDataDefine::ItemFrom_Siting);
                    SendPkg(g_SittingProtS.BuildPkg_CancelSittingOffLine(0,vecRes,dwTimer));
                    LOG_INF <<GetRoleID()<< "单修修变双修收益 :" <<"Timer:" << dwTimer << "double :" << qwOldRoleID;
                    CStore::PrintResInfo(vecRes);
                }

            }

        }
        //通告处于双修
        GetUser().GetVars().SetVar(NVarDefine::ePlayerVarSittingTime,time(NULL));
        CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwRoleID);   
        if(NULL == pOtherUser)
        {
            return ;
        }
        NMapProt::TVecPlayerAppear vecAppear; 
        if(pOtherUser)
        {
            SPlayerAppear appear;
            pOtherUser->GetPlayer()->GetPlayerAppear(appear);
            vecAppear.push_back(appear);
        }
        SendPkg(g_SittingProtS.BuildPkg_UpdateSitting(1,vecAppear,time(NULL)));
        CGameMapPtr pMap = GetMap();
        if(pMap)
            pMap->AppearToSurround(*this);
        LOG_INF <<GetRoleID() << "开始双修";


    }
}

void CPlayer::DoSitOnLine()
{
    if(_sActionManager.HasAction(eACTION_SIT))
    {
        if( _sBaseInfo.qwSittingPlayer == 0 )
        {
            //通告处于单修
            NMapProt::TVecPlayerAppear vecAppear; 
            SendPkg(g_SittingProtS.BuildPkg_UpdateSitting(1,vecAppear,GetUser().GetVars().GetVar(NVarDefine::ePlayerVarSittingTime)));

        }
        else 
        {
            //通告处于双修
            CUserPtr pOtherUser = CUserMgr::GetUserByUserID(_sBaseInfo.qwSittingPlayer);   
            NMapProt::TVecPlayerAppear vecAppear; 
            if(pOtherUser)
            {
                SPlayerAppear appear;
                pOtherUser->GetPlayer()->GetPlayerAppear(appear);
                vecAppear.push_back(appear);
            }
            SendPkg(g_SittingProtS.BuildPkg_UpdateSitting(1,vecAppear,GetUser().GetVars().GetVar(NVarDefine::ePlayerVarSittingTime)));
        }
    }

    else //结算离线收益
    {
        if(GetLevel() < SParamConfig::bySitLimitLevel)
        {
            return  ;
        }
        TVecResource vecRes;
        UINT32 dwTimes =0;
        do{
            CGameMapPtr pMap = GetMap();
            if(pMap == NULL)
                break ;
            if(!pMap->GetMapInfo().IsNormal())
                break; 
            if(_sBaseInfo.dwOfflineTime == 0)
                break;
            if(GetUser().GetVars().GetVar(NVarDefine::ePlayerVarSittingTime) > 0)
            {
                dwTimes = time(NULL) - GetUser().GetVars().GetVar(NVarDefine::ePlayerVarSittingTime);
                GetUser().GetVars().SetVar(NVarDefine::ePlayerVarSittingTime,0);
            }
            else
            {
                dwTimes = time(NULL) - _sBaseInfo.dwOfflineTime;
            }
            if(dwTimes == 0)
                break; 
            _sActionManager.CalSittingAward(vecRes,dwTimes,_sBaseInfo.qwSittingPlayer != 0);
        }while(0);

        if(!vecRes.empty())
        {
            CStore::AddResource(GetUser(),vecRes,NLogDataDefine::ItemFrom_Siting);
            SendPkg(g_SittingProtS.BuildPkg_CancelSittingOffLine(_sBaseInfo.qwSittingPlayer == 0 ? 0 : 1,vecRes,dwTimes));
            LOG_INF <<GetRoleID()<< "修行获得离线收益 :" <<"Timer:" << dwTimes << "double :" << _sBaseInfo.qwSittingPlayer;
            CStore::PrintResInfo(vecRes);

        }
        if(_sBaseInfo.qwSittingPlayer != 0)
        {
            //双修终止
            CUserPtr pOtherUser = CUserMgr::GetUserByUserID(_sBaseInfo.qwSittingPlayer);
            if(pOtherUser && pOtherUser->GetPlayer()->GetSitToGatherPlayer() == GetRoleID() && pOtherUser->GetPlayer()->GetActionManager().HasAction(eACTION_SIT))
            {
                pOtherUser->GetPlayer()->SetSitToGatherPlayer(0,true);
            }
            SetSitToGatherPlayer(0,false);
        }

    }


}

UINT16 CPlayer::GetGuildLevel() const
{
    return _wGuildLevel;
}

void CPlayer::SetGuildLevel(UINT16 wLevel)
{
    _wGuildLevel = wLevel;
}

const string& CPlayer::GetGuildName() const
{ 
    return _strGuildName;
}

void CPlayer::SetGuildName(const string& strGuildName) 
{ 
    _strGuildName = strGuildName; 
    CGameMapPtr pMap = GetMap();
    if (pMap)
        pMap->AppearToSurround(*GetUser().GetPlayer());

    if (GetLevel() >= SParamConfig::wRankLevelLimit3)
    {
        CFighterManagerPtr pFighterManager = GetFighterManager();
        CFormationPet& rForFormationPet = pFighterManager->GetFormationPet();
        CPetSlots& rPetSlots =  rForFormationPet.GetPetSlots();
        rPetSlots.UpdateRankInfo();
    }
    if (GetLevel() >= SParamConfig::wRankLevelLimit4)
    {
        CFighterManagerPtr pFighterManager = GetFighterManager();
        if(pFighterManager)
            pFighterManager->UpdateHeroFighterRankInfo();
    }
    if (GetLevel() >= SParamConfig::wRankLevelLimit5)
    {
        if (_pMainFighter.lock())
        {
            CTrumpSlots& rTrumpSlot = GetFighterManager()->GetTrumpSlots();
            rTrumpSlot.UpdateRankInfo();
        }
    }
}

void CPlayer::BufferRebuildAttr()
{
    CCreature::BufferRebuildAttr();

    CFighterManagerPtr& pFighterManager = GetFighterManager();
    if(pFighterManager)
    {
        pFighterManager->SetDirty(eAttrGpBuffer);
    }

}

//设置战斗类型
void CPlayer::SetBattleType(EBattleType eFightType)
{
    CFighterManagerPtr& pFighterManager = GetFighterManager();
    if(pFighterManager && pFighterManager->GetBattleType() != eFightType)
    {
        pFighterManager->SetBattleType(eFightType);
        pFighterManager->SetDirty(eAttrGpBuffer);
    }
}

EBattleType CPlayer::GetBattleType()
{

    CFighterManagerPtr& pFighterManager = GetFighterManager();
    if(pFighterManager)
    {
        return pFighterManager->GetBattleType();
    }

    return EBTMonster;
}

//保存离开的正常地图坐标
bool CPlayer::SaveLastNormalMap()
{
    CGameMapPtr pMap = GetMap(); 
    if(pMap)
    {
        _sBaseInfo.wLastSaveMapID = GetCurMapID();
        SPoint& oPoint = GetPoint();
        _sBaseInfo.fLastSaveX = oPoint.fX;
        _sBaseInfo.fLastSaveY = oPoint.fY;

        return true;
    }

    return false;
}

//回到先前的普通地图
bool CPlayer::ReturnLastNormalMap()
{
    SPoint oPoint;
    oPoint.fX = _sBaseInfo.fLastSaveX;
    oPoint.fY = _sBaseInfo.fLastSaveY;

    return JumpMap(_sBaseInfo.wLastSaveMapID,oPoint);
}

void CPlayer::AddActID(UINT16 wID)
{
    _setActIDs.insert(wID);
}

void CPlayer::DelActID(UINT16 wID)
{
    _setActIDs.erase(wID);
}

void CPlayer::RegisterAct()
{
    TSetUINT16 setIDs = g_WondActMgr.GetActList();
    TVecID2PrizePtr vecID2Prizes;
    bool bUpdate;
    UINT16 wType = 0;
    for(auto it=setIDs.begin(); it!=setIDs.end(); ++it)
    {
        wType = g_WondActMgr.GetActType(*it);
        if(wType == 0)
            continue;
        switch(wType)
        {
            case eWondActType_CONDPRIZE:
                {
                    vecID2Prizes =  g_WondActMgr.GetConds(*it);
                    TVecPrize2DB vecPrize2DB = _pLevelPrizeAct->GetPrize2DB();
                    for(UINT8 i=0; i<vecID2Prizes.size(); ++i) //遍历奖励列表
                    {
                        bUpdate = true;
                        SID2PrizePtr pID2Prize = vecID2Prizes[i];
                        for(UINT8 j=0; j<vecPrize2DB.size(); ++j) //根据配置的奖励，查看数据库中是否有记录
                        {
                            SPrize2DB sPrize = vecPrize2DB[j];
                            if(sPrize.wLevel == i+1) //在数据库中找到，不必重新注册事件
                            {
                                bUpdate = false;
                                break;
                            }
                        }
                        if(bUpdate) //在数据库中没有查到，需要重新为刚刚登入的玩家注册事件
                        {
                            _pLevelPrizeAct->RegisterActEvent(*it, i+1,pID2Prize->vecConds);
                            _setActIDs.insert(*it); 
                        }
                    }
                }
                break;
        }
    }
}

void CPlayer::DoOffLineEvent()//处理数据库传来的离线事件
{
    if(_vecOffEvent.empty())
        return ;
    //TODO:

    for(auto iter = _vecOffEvent.begin();iter != _vecOffEvent.end();iter ++)
    {
        SEventOffLine &sEvent = *iter;
        TVecINT32 vecParam;
        buf::Tokenizer tkParam(sEvent.strParam1, ',');
        for(size_t iter = 0; iter < tkParam.size();iter++)
        {
            vecParam.push_back(atoi(tkParam[iter].c_str()));
        }

        EventType eEvent = static_cast<EventType>(sEvent.dwEventType);

        OnEvent(eEvent,vecParam,sEvent.strParam2,true,sEvent.dwTime);
    }

    g_Game2DBCommC.Send_DelOffLineEvent(_qwRoleID,_vecOffEvent);
    _vecOffEvent.clear();

}

void CPlayer::DoOffLineEventNotice(const SEventOffLine &sEvent)
{
    TVecEventOffLine vecDel;
    TVecINT32 vecParam;
    buf::Tokenizer tkParam(sEvent.strParam1, ',');
    for(size_t iter = 0; iter < tkParam.size();iter++)
    {
        vecParam.push_back(atoi(tkParam[iter].c_str()));
    }

    EventType eEvent = static_cast<EventType>(sEvent.dwEventType);
    OnEvent(eEvent,vecParam,sEvent.strParam2,true,sEvent.dwTime);
    vecDel.push_back(sEvent);
    g_Game2DBCommC.Send_DelOffLineEvent(_qwRoleID,vecDel);
}

void CPlayer::AddOffLineEvent(const TVecUINT64& vecRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam )//蒋离线时间放入数
{
    SEventOffLine sEvent;
    sEvent.dwEventType = eEvent;
    sEvent.dwTime = time(NULL);
    sEvent.strParam2 = strParam;
    ostringstream strInfo;
    for(size_t it = 0; it != vecParam.size();it++)
    {
        if(it != 0)
            strInfo  << ",";
        strInfo  << vecParam[it];
    }
    sEvent.strParam1 = strInfo.str();
    sEvent.strParam2 = strParam;
    g_Game2DBCommC.Send_AddOffLineEvent(vecRoleID,sEvent);
}

void CPlayer::AddOffLineEvent(UINT64 qwRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam )//蒋离线时间放入数
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser && pUser->GetPlayer())
    {
        pUser->GetPlayer()->OnEvent(eEvent,vecParam,strParam);
        return;
    }

    TVecUINT64 vecRoleID;
    vecRoleID.push_back(qwRoleID);
    AddOffLineEvent(vecRoleID,eEvent,vecParam,strParam);

}

void CPlayer::SaveOffLineEvent(const TVecEventOffLine& vecEvent)
{
    _vecOffEvent = vecEvent;
}

UINT8  CPlayer::GetColor()
{
    if(_pMainFighter.lock())
        return _pMainFighter.lock()->GetColor();
    return 0;
}

// ===  FUNCTION  ======================================================================
//         Name:  OnColorChanged
//  Description:  玩家品质有变化
// =====================================================================================
void CPlayer::OnColorChanged(UINT8 byOldColor)
{
    //  总战力榜
    if (GetLevel() >= SParamConfig::wRankLevelLimit2)
        UpdateBattlePointRank();

    // 阵灵榜
    if (GetLevel() >= SParamConfig::wRankLevelLimit3)
    {
        CFighterManagerPtr pFighterManager = GetFighterManager();
        CFormationPet& rForFormationPet = pFighterManager->GetFormationPet();
        CPetSlots& rPetSlots =  rForFormationPet.GetPetSlots();
        rPetSlots.UpdateRankInfo();
    }

    // 散仙榜
    if (GetLevel() >= SParamConfig::wRankLevelLimit4)
    {
        CFighterManagerPtr pFighterManager = GetFighterManager();
        if(pFighterManager)
            pFighterManager->UpdateHeroFighterRankInfo();
    }

    // 法宝榜
    if (GetLevel() >= SParamConfig::wRankLevelLimit5)
    {
        if (_pMainFighter.lock())
        {
            CTrumpSlots& rTrumpSlot = GetFighterManager()->GetTrumpSlots();
            rTrumpSlot.UpdateRankInfo();
        }
    }

    // 等级榜
    if (GetLevel() >= SParamConfig::wRankLevelLimit8)
        UpdateLevelRank(true);
}		// -----  end of function OnColorChanged  ----- //

extern UINT32 DiffDays(UINT32 dwTime1,UINT32 dwTime2);
//获取从角色创建到现在的天数，创建当天为第1天
UINT32 CPlayer::GetFromCreateDays()
{
    return DiffDays(_sBaseInfo.dwCreateTime,time(NULL)) + 1; 
}

//发送客户端提示消息
void CPlayer::SendSysMsg(UINT32 dwMsgID)
{

    SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(dwMsgID));
}

bool CPlayer::IsBattleCD()
{
    return time(NULL) < _dwBattleCD;
}
void CPlayer::SetBattleCD()
{
    _dwBattleCD = time(NULL) + SParamConfig::wBattleCD;
    return;
}

UINT32 CPlayer::GetBattleCDTime()
{
    return _dwBattleCD;
}

void CPlayer::CleanBattleCD()
{
    _dwBattleCD = 0;
}

void CPlayer::DoLastParam(UINT8 bySource,UINT32 dwValue,UINT32 dwParam)
{
    switch (bySource)
    {
        case PendBattle://杀怪掉落
            {
                GetUser().GetTaskPkg().OnKillMonster(dwValue);
                TVecINT32 vecData;
                vecData.push_back(1);
                GetEventMgr()->OnEvent(eEventType_DungeonBattleWin,vecData);
            }
            break;
        case PendDgn://副本通关
            {
                TVecINT32 vecParam;
                vecParam.push_back(dwValue);
                vecParam.push_back(dwParam);
                OnEvent(eEventType_DungeonStar,vecParam);
            }
            break;
    }
    SPendRes res;
    res.byResType = NProtoCommon::EMONEY_NONE;
    res.dwValue = dwValue;
    res.bySource = bySource;
    string strData;
    COutArchive iar(strData);
    iar << res;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUserID(), eTypePendRes, eOpDel, strData);

}

void CPlayer::DoCheckErrItem()
{
    if(_vecErrItem.empty())
        return;
    for(auto it = _vecErrItem.begin();it != _vecErrItem.end();it++)
    {
        string strData;
        COutArchive iar(strData);
        (*it)->sItemInfo.dwMark = time(NULL);
        SItem_Wrapper wrapper(*it);
        iar << wrapper;
        g_Game2DBCommC.Send_RoleDataUpdate(_qwRoleID, eTypeItemInfo, eOpUpdate, strData);
    }
    _vecErrItem.clear();

}

//客户端发送战斗结束消息
void CPlayer::OnFighterEnd()
{
    if(_pBattleArrayMgr)
    {
        _pBattleArrayMgr->OnFighterEnd();
    }
}

UINT32 CPlayer::ToSize()
{
    UINT32 dwSize = sizeof(*this);
    LOG_INF<<"CPlayer:"<<dwSize;
    return dwSize;
}

bool CPlayer::CheckStarAwardIsGet(UINT16 wStarAward)//检查星级奖励是否打开
{
    return TITLE_DATA::TestNum(wStarAward,_sBaseInfo.szDgnStarAward);   
}

void CPlayer::AddStarAwardInfo(UINT16 wStarAward)//开启一个星级奖励
{
    if(!TITLE_DATA::NumTitleIsValid(wStarAward))
    {
        return ;
    }
    if(CheckStarAwardIsGet(wStarAward))
    {
        return;
    }
    TITLE_DATA::AddNum(wStarAward,_sBaseInfo.szDgnStarAward);
    UpdateBaseInfo2DB();
}

void CPlayer::GetStarAwardInfo(TVecUINT16 &vecStarAward)//获取开放的星级奖励
{
    TITLE_DATA::CharToVecNum(vecStarAward,_sBaseInfo.szDgnStarAward);
}

void CPlayer::GetGuardEMeiFighterID(TVecUINT16& vecFgtID)
{
    if (!_pFightFormationMgr || !_pFighterManager)
        return;
    FightFormationInfo oFightFormationInfo = _pFightFormationMgr->GetFormationByType(EGuardEMei);
    for(auto & rPosInfo : oFightFormationInfo.vecBattlePosInfo)
    {
        CFighterPtr pFighter = _pFighterManager->GetFighterByInstID(rPosInfo.qwInstID);
        if(NULL == pFighter)
            continue;
        vecFgtID.push_back(pFighter->GetID());
    }
}

//获取礼包使用次数
UINT32 CPlayer::GetItemUserCount(UINT16 wItemID)
{
   if(_pAutoStoreMgr)
   {
       return _pAutoStoreMgr->GetValue(eAutoStore_ItemUse,wItemID);
   }

   return 0;
}

//设置礼包使用次数
void CPlayer::SetItemUserCount(UINT16 wItemID,UINT32 dwCount)
{
   if(_pAutoStoreMgr)
   {
       _pAutoStoreMgr->SetValue(eAutoStore_ItemUse,wItemID,dwCount);
   }

}


