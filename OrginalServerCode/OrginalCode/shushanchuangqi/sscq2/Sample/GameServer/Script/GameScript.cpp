#include "stdafx.h"
#include "GameScript.h"
#include "GameConfig.h"
#include "User.h"
#include "Item.h"
#include "StackItem.h"
#include "NPCMgr.h"
#include "MapMgr.h"
#include "HeroFighter.h"
#include "FighterMgr.h"
#include "FighterManager.h"
#include "FighterSlots.h"
#include "TaskMgr.h"
#include "PlayerDgn.h"
#include "DungeonMgr.h"
#include "GatherMgr.h"
#include "MapAreaManager.h"
#include "RTime.h"

struct ENUMS {};
template <typename Base, typename Drived> Base* upcast(Drived* p) { return p; }

UINT32 CGameScript::GetSharpDay(UINT32 dwTime)
{
    return Time::TheDay(0,dwTime);
}

void CGameScript::SetGlobals()
{
    Set("SCRIPT_TYPE_ITEMUSE", SCRIPT_TYPE_ITEMUSE);
    Set("SCRIPT_TYPE_ACT", SCRIPT_TYPE_ACT);
    Set("SCRIPT_TYPE_SYS", SCRIPT_TYPE_SYS);
    Set("SCRIPT_TYPE_TASK", SCRIPT_TYPE_SYS);
    Set("SCRIPT_TYPE_NPC", SCRIPT_TYPE_NPC);
    Set("SCRIPT_TYPE_DGN", SCRIPT_TYPE_DGN);
    Set("SCRIPT_TYPE_GATHER", SCRIPT_TYPE_GATHER);
    Set("SCRIPT_TYPE_AREA", SCRIPT_TYPE_AREA);

}

bool CGameScript::Register()
{
    CScript::Register();
    SetGlobals();

    try
    {
        // XXX: 系统相关注册
        module(GetState())
            [
            class_<CGameConfig>("GameConfig")
            .def("GetServerID", &CGameConfig::GetServerID)
            ];

        // XXX: enum注册
        module(GetState())
            [
            class_<ENUMS>("ENUMS")
            .enum_("EHostType")
            [
            value("eHostNone", eHostNone),
            value("eHostClient", eHostClient),
            value("eHostGate", eHostGate),
            value("eHostLogin", eHostLogin),
            value("eHostCenter", eHostCenter),
            value("eHostGame", eHostGame),
            value("eHostDB", eHostDB),
            value("eHostLog", eHostLog),
            value("eHostControl", eHostControl)
                ]
                .enum_("ECareerType")
                [
                value("ECAREER_ALL",ECAREER_ALL),
            value("ECAREER_RU",ECAREER_RU),
            value("ECAREER_SHI",ECAREER_SHI),
            value("ECAREER_DAO",ECAREER_DAO),
            value("ECAREER_MO",ECAREER_MO),
            value("ECAREER_MAX",ECAREER_MAX)
                ]
                .enum_("ESexType")
                [
                value("ESEX_ALL",ECAREER_ALL),
            value("ESEX_MALE",ESEX_MALE),
            value("ESEX_FEMALE",ESEX_FEMALE),
            value("ESEX_MAX",ESEX_MAX),
            value("ECAREER_MO",ECAREER_MO),
            value("ECAREER_MAX",ECAREER_MAX)
                ]
                .enum_("EObjType")
                [
                value("eObjNone", eObjNone),
            value("eObjPlayer", eObjPlayer),
            value("eObjMonster", eObjMonster),
            value("eObjNpc", eObjNpc),
            value("eObjGather", eObjGather),
            value("eObjSwitcher", eObjSwitcher),
            value("eObjBlocker", eObjBlocker),
            value("eObjArea", eObjArea)
                ]
                .enum_("EPlayerState")
                [
                value("ePlayerNone", ePlayerNone),
            value("ePlayerBorn", ePlayerBorn),
            value("ePlayerInGame", ePlayerInGame),
            value("ePlayerJump", ePlayerJump),
            value("ePlayerSwitch", ePlayerSwitch),
            value("ePlayerLeave", ePlayerLeave)
                ]
                .enum_("EBindUseType")
                [
                value("eBindUseNone", eBindUseNone),
            value("eBindUseBind", eBindUseBind),
            value("eBindUseNoneFirst", eBindUseNoneFirst),
            value("eBindUseBindFirst", eBindUseBindFirst)
                ]
                .enum_("EItemType")
                [
                value("eItemNone", eItemNone),
            value("eItemNormal", eItemNormal),
            value("eItemSkillBook", eItemSkillBook),
            value("eItemStone", eItemStone),
            value("eItemStuff", eItemStuff),
            value("eItemOther", eItemOther),
            value("eItemTask", eItemTask),
            value("eItemResource", eItemResource),
            value("eItemEnd", eItemEnd)
                ]
                .enum_("EItemSubType")
                [
                value("eItemSubNone" , eItemSubNone),
            value("eItemSubResource" , eItemSubResource),
            value("eItemSubNormal" , eItemSubNormal),
            value("eItemSubZTMaterial" , eItemSubZTMaterial),
            value("eItemSubWepaon" , eItemSubWepaon),
            value("eItemSubRing" , eItemSubRing),
            value("eItemSubNeck" , eItemSubNeck),
            value("eItemSubHead" , eItemSubHead),
            value("eItemSubChest" , eItemSubChest),
            value("eItemSubLegging" , eItemSubLegging),
            value("eItemSubMounts" , eItemSubMounts),
            value("eItemSubActiveTrump" , eItemSubActiveTrump),
            value("eItemSubPassiveTrump" , eItemSubPassiveTrump),
            value("eItemSubFashion" , eItemSubFashion),
            value("eItemSubFashion2" , eItemSubFashion2),
            value("eItemSubSpirit" , eItemSubSpirit),
            value("eItemSubPetSoul" , eItemSubPetSoul)
                ]
                .enum_("EFighterType")
                [
                value("eFighter", eFighter),
            value("eFighterPlayer", eFighterPlayer),
            value("eFighterHero", eFighterHero),
            value("eFighterMonster", eFighterMonster),
            value("eFighterMax", eFighterMax)
                ]
                ];

        // XXX: 玩家相关注册
        module(GetState())
            [
            DEF_PTR(CPlayer),
            DEF_PTR(CUser),
            class_<CStore>("Store")
                .def("CanAddItemWithID",&CStore::CanAddItemWithID)
                .def("AddItemWithID",&CStore::AddItemWithID)
                .def("GetEmptyCount",&CStore::GetEmptyCount)
                .def("GetItemCount",(UINT32(CStore::*)(UINT16) const) &CStore::GetItemCount)
                .def("GetItemCount",(UINT16(CStore::*)(UINT16,EBindUseType) const) &CStore::GetItemCount)
                .def("CanSubItemWithID",&CStore::CanSubItemWithID)
                .def("SubItemWithID",&CStore::SubItemWithID)
                ,
            class_<CPack,CStore>("Pack")
                .def("upcast", &upcast<CStore, CPack>)
                ,
            class_<CUser>("User")
                .def("GetUserID", &CUser::GetUserID)
                .def("GetUserName", &CUser::GetUserName)
                .def("GetFixedUserName", &CUser::GetFixdUserName)
                .def("GetCUserName", &CUser::GetCUserName)
                .def("GetFixedCUserName", &CUser::GetFixdCUserName)
                .def("GetPlayer", &CUser::GetpPlayer)
                .def("GetPack", &CUser::GetPack)
                .def("GetDepot", &CUser::GetDepot)
                .def("GetVars", &CUser::GetVars)
                .def("GetStoreByType", &CUser::GetStoreByType)
                .def("CanSubGoldOrCoupon", &CUser::CanSubGoldOrCoupon)
                .def("SubGoldOrCoupon", &CUser::SubGoldOrCoupon)
                .def("NoticeStory", &CUser::NoticeStory)
                .def("Test64", &CUser::Test64) // for Test
                .def("SendMsg",&CUser::SendSysMsg)
                .def("ActiveTripodFire",&CUser::ActiveTripodFire)
                .def("AddVIPGrowthValue",&CUser::AddVIPGrowthValue)
                .def("AddTotalRechargeByLua",&CUser::AddTotalRechargeByLua)
                .def("AddIconByLua",&CUser::AddIconByLua)
                .def("DelIconByLua",&CUser::DelIconByLua)
                ,
            class_<CBaseObj>("BaseObj")
                .def("GetObjType", &CBaseObj::GetObjType)
                .def("GetDescription", &CBaseObj::GetDescription)
                .def("GetName", &CBaseObj::GetName)
                .def("GetLocaleName", &CBaseObj::GetLocaleName)
                .def("GetPoint", &CBaseObj::CopyPoint)
                .def("GetDir", &CBaseObj::GetDir)
                .def("GetMap", &CBaseObj::GetMap)
                .def("GetGrid", &CBaseObj::GetGrid)
                .def("IsOnMap", &CBaseObj::IsOnMap)
                .def("GetCoord", &CBaseObj::CopyCoord)
                ,
            class_<CCreature, CBaseObj>("Creature")
                .def("GetCreatureID", &CCreature::GetCreatureID)
                .def("IsDead", &CCreature::IsDead)
                .def("OnKill", &CCreature::OnKill)
                .def("OnDie", &CCreature::OnDie)
                .def("OnAttacked", &CCreature::OnAttacked)
                .def("CanUseItem", &CCreature::CanUseItem)
                .def("IsAttackable", &CCreature::IsAttackable)
                .def("GetAppearState", &CCreature::GetAppearState)
                .def("GetJob", &CCreature::GetJob)
                .def("upcast", &upcast<CBaseObj, CCreature>)
                ,
            class_<CPlayer, CCreature>("Player")
                .def("GetUserID", &CPlayer::GetUserID)
                .def("GetObjType", &CPlayer::GetObjType)
                .def("GetUser", &CPlayer::GetUser)
                .def("GetUserPtr", &CPlayer::GetpUser) // XXX: SharePtr
                .def("GetPlayerState", &CPlayer::GetPlayerState)
                .def("IsRobot", &CPlayer::IsRobot)
                .def("GetCurMapID", &CPlayer::GetCurMapID)
                //.def("GetPreDgnMapID", &CPlayer::GetPreDgnMapID)
                .def("GetCurNpcID", &CPlayer::GetCurNpcID)
                .def("GetDgnID", &CPlayer::GetDgnID)
                .def("GetDgnInstID", &CPlayer::GetDgnInstID)
                .def("GetDgn", &CPlayer::GetpDgn)
                .def("IsInDungeon", &CPlayer::IsInDungeon)
                .def("GetLevel", &CPlayer::GetLevel)
                .def("AddExp", &CPlayer::AddExp)
                .def("SubExp", &CPlayer::SubExp)
                .def("UpdateBaseInfo2DB", &CPlayer::UpdateBaseInfo2DB)
                .def("FitherToMonster", &CPlayer::FitherToMonster)
                .def("ElasticFrame", &CPlayer::ElasticFrame)
                .def("upcast", &upcast<CCreature, CPlayer>)
                .def("IsTrumpActived", &CPlayer::IsTrumpActived)
                .def("AddBuff", &CPlayer::AddBuffLua)
                .def("GetItemUserCount",&CPlayer::GetItemUserCount)
                .def("SetItemUserCount",&CPlayer::SetItemUserCount)
                ,
            class_<CFighter>("Fighter")
                .def("GetFighterID", &CFighter::GetFighterID)
                .def("GetInstID", &CFighter::GetInstID)
                .def("GetType", &CFighter::GetType)
                .def("IsMainFighter", &CFighter::IsMainFighter)
                .def("IsHeroFighter", &CFighter::IsHeroFighter)
                .def("IsMonsterFighter", &CFighter::IsMonsterFighter)
                ,
            DEF_PTR(CFighter),
            class_<CHeroFighter, CFighter>("HeroFighter")
                ,
            DEF_PTR(CHeroFighter),

            class_<CFighterManager>("FigherManager")
                //.def("GetUserPtr", &CFighterManager::GetUserPtr)
                .def("GetMainFighter", &CFighterManager::GetpMainFighter)
                .def("GetFighterByInstID", &CFighterManager::GetpFighterByInstID)
                .def("GetFighterByID", &CFighterManager::GetpFighterByID)
                .def("GetFighterForce", &CFighterManager::GetFighterForce)
                .def("HasFighter", &CFighterManager::HasFighter)
                ,
            DEF_PTR(CFighterManager),
            class_<CGameVar>("GameVar")
                .def("GetVar", &CGameVar::GetVar)
                .def("SetVar", &CGameVar::SetVar)
                .def("AddVar", &CGameVar::AddVar)
                .def("DelVar", &CGameVar::DelVar)
                .def("GetVar32", &CGameVar::GetVar32)
                ,
            class_<CVar,CGameVar>("CVar")
                .def("upcast", &upcast<CGameVar, CVar>)
                ];


        // XXX: 道具系统相关注册
        module(GetState())
            [
            class_<CItem>("Item")
            .def("GetItemID", &CItem::GetItemID)
            .def("GetInstID", &CItem::GetInstID)
            .def("GetCount", &CItem::GetCount)
            .def("GetItemExp", &CItem::GetItemExp)
            .def("GetSellPrice", &CItem::GetSellPrice)
            .def("GetLevel", &CItem::GetLevel)
            .def("GetItemName", &CItem::GetItemName)
            .def("GetBindType", &CItem::GetBindType)
            .def("IsBind", &CItem::IsBind)
            .def("SetBind", &CItem::SetBind)
            ,
            class_<CStackItem, CItem>("StackItem")
                .def("upcast", &upcast<CItem, CStackItem>)
                ,
            DEF_PTR(CItem),
            DEF_PTR(CStackItem)

                ];

        // XXX: 地图相关注册
        module(GetState())
            [
            class_<SPoint>("Point")
            .def_readwrite("fX", &SPoint::fX)
            .def_readwrite("fY", &SPoint::fY)
            .def("Clear", &SPoint::Clear)
            .def("IsValid", &SPoint::IsValid)
            ,
            class_<SMapInfo>("MapInfo")
                ,
            class_<SCoord>("Coord")
                .def_readwrite("dwX", &SCoord::dwX)
                .def_readwrite("dwY", &SCoord::dwY)
                ,
            class_<CGrid>("Grid")
                .def("AddObj", &CGrid::AddObj)
                .def("DelObj", &CGrid::DelObj)
                .def("HasObj", &CGrid::HasObj)
                ,
            class_<CGameMap>("GameMap")
                .def("GetMapID", &CGameMap::GetMapID)
                .def("PlayerAppear", &CGameMap::PlayerAppear)
                .def("PlayerDisappear", &CGameMap::PlayerDisappear)
                .def("AddNpc", &CGameMap::AddNpc)
                .def("AddMonster", &CGameMap::AddMonster)
                .def("AddMonsterIfNotExist", &CGameMap::AddMonsterIfNotExist)
                ,
            class_<CMapMgr>("MapMgr")
                .def("IsDgnMap", &CMapMgr::IsDgnMap)
                .def("GetMapInfo", &CMapMgr::GetMapInfo)
                .def("GetMap", &CMapMgr::GetpMap)
                ,
            // XXX: 接口都返回shared/weak_ptr,使用get取得裸指针
            DEF_PTR(CGameMap),
            DEF_PTR(SMapInfo)
                ];
        Set("MapMgr", boost::ref(CMapMgr::Instance()));

        // XXX: NPC和Monster相关
        module(GetState())
            [
            class_<CNpcMgr>("NpcMgr")
            .def("CreateNpc", &CNpcMgr::CreateNpc)
            .def("GetNpc", &CNpcMgr::GetpNpc)
            ,
            DEF_PTR(CNpc)
                ];
        Set("NpcMgr", boost::ref(CNpcMgr::Instance()));

        // XXX: 副本相关注册
        module(GetState())
            [
            DEF_PTR(CDungeon),
            DEF_PTR(CPlayerDgn),
            class_<CDungeon>("Dungeon")
                .def("SetTimer", &CDungeon::SetTimer)
                .def("EndTimer",&CDungeon::EndTimer)
                .def("SetParam", &CDungeon::SetParam)
                .def("GetParam", &CDungeon::GetParam)
                .def("GetDgnType", &CDungeon::GetDgnType)
                .def("SetDgnState", &CDungeon::GetDgnType)
                .def("CreateMonster", &CDungeon::CreateMonster)
                .def("CreateMonsterIfNotExist", &CDungeon::CreateMonsterIfNotExist)
                .def("DestroyMonster", &CDungeon::DestroyMonster)
                .def("CreateGather", &CDungeon::CreateGather)
                .def("DestroyGather", &CDungeon::DestroyGather)
                .def("TransMap", &CDungeon::TransMap)
                .def("CreateBlockByIndex", &CDungeon::CreateBlockByIndex)
                .def("DestroyBlockByIndex", &CDungeon::DestroyBlockByIndex)
                .def("CreateAreaByIndex", &CDungeon::CreateAreaByIndex)
                .def("DestroyAreaByIndex", &CDungeon::DestroyAreaByIndex)
                .def("AddSwitcherByIndex",&CDungeon::AddSwitcherByIndex)
                .def("SwitcherDestroyByIndex",&CDungeon::SwitcherDestroyByIndex)
                .def("AddGatherByIndex",&CDungeon::AddGatherByIndex)
                .def("GatherDestroyByIndex",&CDungeon::GatherDestroyByIndex)
                .def("AddNpcByIndex",&CDungeon::AddNpcByIndex)
                .def("NpcDestroyByIndex",&CDungeon::NpcDestroyByIndex)
                .def("DestroyNpc",&CDungeon::DestroyNpc)

                ,
            class_<CPlayerDgn, CDungeon>("PlayerDgn")
                .def("GetPlayer", &CPlayerDgn::GetpPlayer)
                .def("upcast", &upcast<CDungeon,CPlayerDgn>)
                ];

        // XXX: 脚本系统自身相关注册
        module(GetState())
            [
            class_<CGameScript>("GameScript")
            .def("GetUser", &CGameScript::GetUser)
            .def("GetOther", &CGameScript::GetOther)
            .def("GetSharpDay", &CGameScript::GetSharpDay)
            ];
        Set("GameScript", boost::ref(*this)); // XXX: 对象传值必须使用boost::ref

        // TODO END
    }
    catch (...)
    {
        LuaError_CallBack(GetState());
        return false;
    }

    return true;
}

bool CGameScript::ReloadScripts(int flag)
{
    if (!Reload(flag))
    {
        LOG_CRI << "_oScript.Init fails!";
        return false;
    }
    if((flag & SCRIPT_TYPE_TASK) > 0)
    {
        CTaskMgr::ClearTaskScript();
    }
    if((flag & SCRIPT_TYPE_DGN) >0 )
    {
        CDungeonMgr::ClearLua(); 
    }
    if((flag & SCRIPT_TYPE_GATHER) >0 )
    {
        CGatherMgr::ClearAllLua(); 
    }
    if((flag & SCRIPT_TYPE_AREA) >0 )
    {
        g_AreaManager.ClearAllLua(); 
    }
    _bHasItemUseNormal = false;
    return true;
}

bool CGameScript::HasUseFunction(UINT16 wItemID)
{
    bool bHas = false;
    bool bRet = Call("HasUseFunction", bHas, wItemID);
    return bRet && bHas;
}

bool CGameScript::HasOnAcceptTaskFunction(UINT16 wTaskID)
{
    bool bHas = false;
    bool bRet = Call("HasOnAcceptTaskFunction", bHas, wTaskID);
    return bRet && bHas;
}

bool CGameScript::HasCanFinishTaskFunction(UINT16 wTaskID)
{
    bool bHas = false;
    bool bRet = Call("HasCanFinishTaskFunction", bHas, wTaskID);
    return bRet && bHas;
}

bool CGameScript::HasCanAcceptTaskFunction(UINT16 wTaskID)
{
    bool bHas = false;
    bool bRet = Call("HasCanAcceptTaskFunction", bHas, wTaskID);
    return bRet && bHas;
}
bool CGameScript::HasDoCaseForDgnFunction(UINT16 wTaskID)
{
    bool bHas = false;
    bool bRet = Call("HasDoCaseForDgnFunction", bHas, wTaskID);
    return bRet && bHas;
}

bool CGameScript::HasOnGiveUpTaskFunction(UINT16 wTaskID)
{
    bool bHas = false;
    bool bRet = Call("HasOnGiveUpTaskFunction", bHas, wTaskID);
    return bRet && bHas;
}

bool CGameScript::HasOnFinishTaskFunction(UINT16 wTaskID)
{
    bool bHas = false;
    bool bRet = Call("HasOnFinishTaskFunction", bHas, wTaskID);
    return bRet && bHas;
}


void CGameScript::OnFinishTask(UINT16 wTaskID,CUser& rUser)
{
    if (!IsLoaded())
        return ;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    VCall("OnFinishTask", wTaskID);
    SetUser(pSaveUser);

}

void CGameScript::OnAcceptTask(UINT16 wTaskID,CUser& rUser)
{
    if (!IsLoaded())
        return ;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    VCall("OnAcceptTask", wTaskID);
    SetUser(pSaveUser);
}

bool CGameScript::CanFinishTask(UINT16 wTaskID,CUser& rUser)
{
    if (!IsLoaded())
        return false;

    bool bCan = false;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    bool bRet = Call("CanFinishTask", bCan, wTaskID);
    SetUser(pSaveUser);
    return bRet && bCan;
}

bool CGameScript::CanAcceptTask(UINT16 wTaskID,CUser& rUser)
{
    LOG_INF << "call CGameScript::CanAcceptTask" << wTaskID;
    if (!IsLoaded())
        return false;

    bool bCan = false;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    bool bRet = Call("CanAcceptTask", bCan, wTaskID);
    SetUser(pSaveUser);
    return bRet && bCan;
}

void CGameScript::DoCaseForDgn(UINT16 wTaskID,UINT16 wDgnId,CUser& rUser)
{
    LOG_INF << "call CGameScript::DoCaseForDgn" << wTaskID;
    if (!IsLoaded())
        return ;

    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    VCall("DoCaseForDgn", wTaskID,wDgnId);
    SetUser(pSaveUser);
}

bool CGameScript::NpcTalk(string &strText,const string& strFunName,UINT16 wNPCTypeId,CUser& rUser)
{
    LOG_INF << "call CGameScript::NpcTalk" <<  wNPCTypeId;
    if (!IsLoaded())
        return false;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    bool bCallRet = Call("NpcTalk",strText, wNPCTypeId,strFunName);
    SetUser(pSaveUser);
    return  bCallRet;
}

void CGameScript::OnGiveUpTask(UINT16 wTaskID,CUser& rUser)
{
    if (!IsLoaded())
        return ;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    VCall("OnGiveUpTask", wTaskID);
    SetUser(pSaveUser);
}


UINT16 CGameScript::ItemUseNormal(CUser& rUser, CItem& rItem, UINT16 wCount, UINT64 qwMercenID, CUser* pOtherUser)
{
    return ItemUseNormal(rUser, rItem.GetItemID(), wCount, rItem.IsBind(), qwMercenID, pOtherUser);
}

UINT16 CGameScript::ItemUseNormal(CUser& rUser, UINT16 wItemID, UINT16 wCount, UINT8 byBind, UINT64 qwMercenID, CUser* pOtherUser)
{
    if (!IsLoaded())
        return 0;

    CUser* pSaveUser = GetUser();
    CUser* pSaveOther = GetOther();

    SetUser(&rUser);
    if (pOtherUser)
        SetOther(pOtherUser);

    if (!_bHasItemUseNormal)
        _bHasItemUseNormal = HasFunction("ItemUseNormal");

    bool bRet = false;
    UINT16 wRetCnt = 0;
    if (_bHasItemUseNormal)
        bRet = Call("ItemUseNormal", wRetCnt, wItemID, wCount, byBind, qwMercenID);

    if (!bRet)
        LOG_WRN << __PRETTY_FUNCTION__ << ": ItemUseNormalByID return false.";

    SetUser(pSaveUser);
    SetOther(pSaveOther);

    return wRetCnt;
}

bool CGameScript::Dungeon_HasOnEnterLimit(UINT16 wDgnId)
{
    bool bHas = false;
    bool bRet = Call("DungeonHasOnEnterLimitFunction", bHas, wDgnId);
    return bRet && bHas;
}

bool CGameScript::Dungeon_HasOnInit(UINT16 wDgnId)
{
    bool bHas = false;
    bool bRet = Call("DungeonHasOnInitFunction", bHas, wDgnId);
    return bRet && bHas;

}

bool CGameScript::Dungeon_HasOnTimer(UINT16 wDgnId)
{
    bool bHas = false;
    bool bRet = Call("DungeonHasOnTimerFunction", bHas, wDgnId);
    return bRet && bHas;

}

bool CGameScript::Dungeon_HasOnEnd(UINT16 wDgnId)
{
    bool bHas = false;
    bool bRet = Call("DungeonHasOnEndFunction", bHas, wDgnId);
    return bRet && bHas;

}

bool CGameScript::Dungeon_HasOnFinish(UINT16 wDgnId)
{
    bool bHas = false;
    bool bRet = Call("DungeonHasOnFinishFunction", bHas, wDgnId);
    return bRet && bHas;

}

UINT8 CGameScript::Dungeon_OnEnterLimit(UINT16 wDgnId,CUser& rUser)
{
    if (!IsLoaded())
        return 0;
    UINT8 byCan = 0;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    bool bRet = Call("DungeonOnEnterLimit", byCan, wDgnId);
    SetUser(pSaveUser);
    if(!bRet)
    {
        return 0;
    }
    return  byCan;
}

void CGameScript::Dungeon_OnInit(UINT16 wDgnId,CDungeon* pDgn)
{
    if (!IsLoaded())
        return ;
    VCall("DungeonOnInit",wDgnId,pDgn);
}

void CGameScript::Dungeon_OnTimer(UINT16 wDgnId,CDungeon* pDgn,UINT16 wTimerId)
{
    if (!IsLoaded())
        return ;
    VCall("DungeonOnTimer",wDgnId,pDgn,wTimerId);
}

void CGameScript::Dungeon_OnEnd(UINT16 wDgnId,CDungeon* pDgn)
{
    if (!IsLoaded())
        return ;
    VCall("DungeonOnEnd",wDgnId,pDgn);
}

void CGameScript::Dungeon_OnFinish(UINT16 wDgnId,CDungeon* pDgn)
{
    if (!IsLoaded())
        return ;
    VCall("DungeonOnFinish", wDgnId,pDgn);
}

bool CGameScript::HasCanGatherFunction(UINT16 wGatherID)
{
    bool bHas = false;
    bool bRet = Call("HasCanGatherFunction", bHas, wGatherID);
    return bRet && bHas;
}

bool CGameScript::HasOnFinishGatherFunction(UINT16 wGatherID)
{
    bool bHas = false;
    bool bRet = Call("HasOnFinishGatherFunction", bHas, wGatherID);
    return bRet && bHas;

}

UINT8 CGameScript::CanGather(UINT16 wGatherID,CUser& rUser)
{
    if (!IsLoaded())
        return 0;
    UINT8 byCan = 0;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    bool bRet = Call("CanGather", byCan, wGatherID);
    SetUser(pSaveUser);
    if(!bRet)
    {
        return 0;
    }
    return  byCan;

}

void  CGameScript::OnFinishGather(UINT16 wGatherID,CUser& rUser)
{
    if (!IsLoaded())
        return ;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    VCall("OnFinishGather", wGatherID);
    SetUser(pSaveUser);
}
bool CGameScript::HasInAreaFunction(UINT16 wArea)
{
    bool bHas = false;
    bool bRet = Call("HasInAreaFunction", bHas, wArea);
    return bRet && bHas;
}
void  CGameScript::InArea(UINT16 wArea,CUser& rUser)
{
    if (!IsLoaded())
        return ;
    CUser* pSaveUser = GetUser();
    SetUser(&rUser);
    VCall("InArea",wArea);
    SetUser(pSaveUser);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

