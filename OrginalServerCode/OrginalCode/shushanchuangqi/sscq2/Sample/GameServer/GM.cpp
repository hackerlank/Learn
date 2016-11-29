#include "stdafx.h"
#include "Protocols.h"
#include "GM.h"
#include "UserMgr.h"
#include "Random.h"
#include "Player.h"
#include "MapMgr.h"
#include "DungeonMgr.h"
#include "boost/pointer_cast.hpp"
#include "ItemType.h"
#include "ItemProtSvr.h"
#include "ItemMgr.h"
#include "FighterMgr.h"
#include "Battle.h"
#include <sstream>
#include "Chat.h"
#include "ExpMgr.h"
#include "MonsterMgr.h"
#include "FighterManager.h"
#include "CommonDef.h"
#include "HeroFighter.h"
#include "GameVar.h"
#include "TrumpSlots.h"
#include "DemonTowerDgn.h"
#include "Skill.h"
#include "WorldBossMgr.h"
#include "Mall.h"
#include "ShushanBattle.h"
#include "ShushanBattleMgr.h"
#include "HorseMgr.h"
#include "WorldBossMgr.h"
#include "VIPMgr.h"
#include "BattlePoint.h"
#include "DayActivityMgr.h"
#include "GuildBattleConfig.h"
#include "GuildBattleMgr.h"
#include "NewGuildBattleConfig.h"
#include "NewGuildBattleMgr.h"
#include "NewGuildBattlePlayer.h"
#include "EventMgr.h"
#include "AchievementMgr.h"
#include "CollectionMgr.h"
#include "LangHuanBlessMgr.h"
#include "ExchangeShopMgr.h"
#include "YelloDiamondMgr.h"
#include "EnergyMgr.h"
#include "Item/Loot.h"
#include "BeastSoul.h"
#include "WondActMgr.h"
#include "ShopItemMgr.h"
#include "DayTargetMgr.h"
#include "BattleArrayMgr.h"
#include "LoginPkgMgr.h"
#include "AutoStoreMgr.h"
#include "BattleArraySvr.h"
#include "DemonTowerMgr.h"
#include "BeautyMgr.h"
#include "Shushanweiwei.h"
#include "AllTimers.h"
#include "TaskMarket.h"
#include "IconAppearManager.h"
#include "ZhanQiMgr.h"
#include "LingShanProtS.h"
#include "GodChest.h"
#include "Lottery.h"
#include "GUIDMgr.h"
#include "EquipTrumpProtS.h"
#include "EquipTrump.h"
#include "ViewInfoProtS.h"
#include "FeedBackMgr.h"
#ifdef _DEBUG
#include "Directory.h"
#endif

using namespace NLingShanProt;
using namespace NItemProt;
using namespace buf;
using namespace NEquipTrumpProt;

namespace GM
{

    void GameReloadLua(const char* cmd, const Tokenizer& params, void* p = NULL);
    void GameCfgReload(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Item(const char* cmd, const Tokenizer& params, void* p = NULL);
    void AddLoot(const char* cmd, const Tokenizer& params, void* p = NULL);
    void UseItem(const char* cmd, const Tokenizer& params, void* p = NULL);
    void UItem(const char* cmd, const Tokenizer& params, void* p = NULL);
    void DelItem(const char* cmd, const Tokenizer& params, void* p = NULL);
    void SwapItem(const char* cmd, const Tokenizer& params, void* p = NULL);
    void SellItem(const char* cmd, const Tokenizer& params, void* p = NULL);
    void NPC(const char* cmd, const Tokenizer& params, void* p = NULL);
    void LevelUp(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Level(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Exp(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Star(const char* cmd, const Tokenizer& params, void* p = NULL);
    void EnterPlayerDgn(const char* cmd, const Tokenizer& params, void* p = NULL);
    void LeavePlayerDgn(const char* cmd, const Tokenizer& params, void* p = NULL);
    void FinishPlayerDgn(const char* cmd, const Tokenizer& params, void* p = NULL);
    void PlayerDgnKillAll(const char* cmd, const Tokenizer& params, void* p = NULL);
    void AddOwnTitle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void DelOwnTitle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void ShowOwnTitle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void AddEquipTitle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void DelEquipTitle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void ShowEquipTitle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Gold(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Coupon(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Silver(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Soul(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Honor(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Prestige(const char* cmd, const Tokenizer& params, void* p = NULL);
    void PExp(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Sigil(const char* cmd, const Tokenizer& params, void* p = NULL);
    void CentsY(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Action(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Sop(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Poten(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Taoism(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Boost(const char* cmd, const Tokenizer& params, void* p = NULL);
    void RobotBoost(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Super(const char* cmd, const Tokenizer& params, void* p = NULL);
    void AcceptTask(const char* cmd, const Tokenizer& params, void* p = NULL);
    void GiveupTask(const char* cmd, const Tokenizer& params, void* p = NULL);
    void CommitTask(const char* cmd, const Tokenizer& params, void* p = NULL);
    void VarDec(const char* cmd, const Tokenizer& params, void* p = NULL);
    void VarAdd(const char* cmd, const Tokenizer& params, void* p = NULL);
    void VarGet(const char* cmd, const Tokenizer& params, void* p = NULL);
    void VarDel(const char* cmd, const Tokenizer& params, void* p = NULL);

    void StartBattle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void AttackPlayer(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Attack(const char* cmd, const Tokenizer& params, void* p = NULL);
    void BattleInfo(const char* cmd, const Tokenizer& params, void* p = NULL);
    void BattleRestart(const char* cmd, const Tokenizer& params, void* p = NULL);
    void BattleCheat(const char* cmd, const Tokenizer& params, void* p = NULL);

    void SendInfo(const char* cmd, const Tokenizer& params, void* p = NULL);
    void SysMailTest(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Recruit(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Fighter(const char* cmd, const Tokenizer& params, void* p = NULL);
    void FighterDujie(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Pet(const char* cmd, const Tokenizer& params, void* p = NULL);
    void ChgPet(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Fashion(const char* cmd, const Tokenizer& params, void* p = NULL);
    void SetFashion(const char* cmd, const Tokenizer& params, void* p = NULL);
    void AddMoney(const char* cmd, const Tokenizer& params, void* p = NULL);
    void GmTest(const char* cmd, const Tokenizer& params, void* p = NULL);
    void TopUp(const char* cmd, const Tokenizer& params, void* p = NULL);
    void CreateMonster(const char* cmd, const Tokenizer& params, void* p = NULL);
    void EnterMap(const char* cmd, const Tokenizer& params, void* p = NULL);
    void WorldBoss(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Buy(const char* cmd, const Tokenizer& params, void* p = NULL);
    void EnterShushanBattle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void CreateGather(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Buff(const char* cmd, const Tokenizer& params, void* p = NULL);
    void TestActivity(const char* cmd, const Tokenizer& params, void* p = NULL);
    void SetVIP(const char* cmd, const Tokenizer& params, void* p = NULL);
    void BattlePoint(const char* cmd, const Tokenizer& params, void* p = NULL);
    void GetPlayerHP(const char* cmd, const Tokenizer& params, void* p = NULL);
    void GuildBattle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void NewGuildBattle(const char* cmd, const Tokenizer& params, void* p = NULL);
    void DoSit(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Loot(const char* cmd, const Tokenizer& params, void* p = NULL);
    void BeastSoul(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Discount(const char* cmd, const Tokenizer& params, void* p = NULL);
    void OpenAct(const char* cmd, const Tokenizer& params, void* p = NULL);
    void EndAct(const char* cmd, const Tokenizer& params, void* p = NULL);
    void ShowMem(const char* cmd, const Tokenizer& params, void* p = NULL);
    void OpenIcon(const char* cmd, const Tokenizer& params, void* p = NULL);
    void MoneyChange(const char* cmd, const Tokenizer& params, void* p = NULL);
    void Recharge(const char* cmd, const Tokenizer& params, void* p = NULL);

    void ChatSysLog(const string& strInfo, CUser& rUser, const char chSplit = '\0');

    static GMHandler GMCMD[] =
    {
        {GMT_ALL, "gsreload", &GameReloadLua, "//gsreload [TASK|ITEM]+* => reload scripts for GameServer."},
        {GMT_ALL, "gcreload", &GameCfgReload, "//gcreload => reload all configuration."},

        {GMT_SUPER, "item", &Item, "//item wItemID [wCount [bBind [byQuality]]] => add item to package."},
        {GMT_SUPER, "itemdel", &DelItem, "//itemdel wItemID [wCount [bBind [byQuality]]] => del item."},
        {GMT_SUPER, "itemuse", &UseItem, "//itemuse wItemID [wCount [bBind [byQuality]]] => use item."},
        {GMT_SUPER, "itemu", &UItem, "//itemu id=qwInstID count=wCount bind=bBind quality=byQuality => use item."},
        {GMT_SUPER, "itemswap", &SwapItem, "//itemswap fromtype fromidx totype toidx - [1-pack 2-depot]"},
        {GMT_SUPER, "itemsell", &SellItem, "//itemsell wItemID [wCount [bBind]]"},
        {GMT_SUPER, "addloot", &AddLoot, "//lootid"},
        {GMT_SUPER, "npc", &NPC, "//npc wNpcID x y"},
        {GMT_SUPER, "levelup", &LevelUp, "//levelup [num]"},
        {GMT_SUPER, "level", &Level, "//level [num]"},
        {GMT_SUPER, "exp", &Exp, "//exp [num]"},
        {GMT_SUPER, "gold", &Gold, "//gold [-]num"},
        {GMT_SUPER, "coupon", &Coupon, "//coupon [-]num"},
        {GMT_SUPER, "silver", &Silver, "//silver [-]num"},
        {GMT_SUPER, "star", &Star, "//silver [-]num"},
        {GMT_SUPER, "soul", &Soul, "//soul [-]num"},
        {GMT_SUPER, "prestige", &Prestige, "//prestige [-]num"},
        {GMT_SUPER, "honor", &Honor, "//honor [-]num"},
        {GMT_SUPER, "pexp", &PExp, "//pexp [num]"},
        {GMT_SUPER, "sigil", &Sigil, "//sigil [-]num"},
        {GMT_SUPER, "centsy", &CentsY, "//centsy [-]num"},
        {GMT_SUPER, "action", &Action, "//action [-]num"},
        {GMT_SUPER, "sop", &Sop, "//sop [-]num"},
        {GMT_SUPER, "poten", &Poten, "//poten [-]num"},
        {GMT_SUPER, "taoism", &Taoism, "//taoism [-]num"},
        {GMT_SUPER, "addmoney", &AddMoney, "//addmoney type num"},
        {GMT_SUPER, "topup", &TopUp, "//topup goldid num (模拟充值,goldid为41,42,43,44,45,46六种)"},

        {GMT_DEBUG, "boost",&Boost,"//boost(新手速成)"},
        {GMT_DEBUG, "robotboost",&RobotBoost,"//robotboost(机器人速度成功)"},

        {GMT_DEBUG, "super",&Super,"//super(这下我的号牛逼了)"},
        {GMT_DEBUG, "enterplayerdgn", &EnterPlayerDgn, "//enterplayerdgn wdgnid "},
        {GMT_DEBUG, "leaveplayerdgn", &LeavePlayerDgn, "//leaveplayerdgn"},
        {GMT_DEBUG, "finishplayerdgn", &FinishPlayerDgn, "//leaveplayerdgn"},
        {GMT_DEBUG, "playerdgnkillall", &PlayerDgnKillAll, "//playerdgnkillall"},

        {GMT_DEBUG, "addowntitle", &AddOwnTitle, "//addOwnTitle wTitletype "},
        {GMT_DEBUG, "delowntitle", &DelOwnTitle, "//delOwnTitle wTitletype "},
        {GMT_DEBUG, "showowntitle", &ShowOwnTitle, "//showowntitle "},
        {GMT_DEBUG, "addequiptitle", &AddEquipTitle, "//addequipTitle wTitletype "},
        {GMT_DEBUG, "delequiptitle", &DelEquipTitle, "//delequipTitle wTitletype "},
        {GMT_DEBUG, "showequiptitle", &ShowEquipTitle, "//showequiptitle "},

        {GMT_DEBUG, "accepttask", &AcceptTask, "//accepttask wtaskid "},
        {GMT_DEBUG, "giveuptask", &GiveupTask, "//giveuptask wtaskid "},
        {GMT_DEBUG, "committask", &CommitTask, "//committask wtaskid "},

        {GMT_DEBUG, "vardec", &VarDec, "//varadd id type"},
        {GMT_DEBUG, "varadd", &VarAdd, "//varadd id value"},
        {GMT_DEBUG, "varget", &VarGet, "//varget"},
        {GMT_DEBUG, "vardel", &VarDel, "//vardel id"},

        // Battle
        {GMT_DEBUG, "sb", &StartBattle, "//sb(StartBattle)"},
        {GMT_DEBUG, "ap",&AttackPlayer,"//ap(AttackPlayer) qwPlayerID"},
        {GMT_DEBUG, "attack",&Attack,"//attack id"},
        {GMT_DEBUG, "bi",&BattleInfo,"//bi(BattleInfo) id"},
        {GMT_DEBUG, "br",&BattleRestart,"//br(BattleRestart) id"},
        {GMT_DEBUG, "bc", &BattleCheat, "//bc(BattleCheat)"},

        {GMT_DEBUG, "info", &SendInfo, "//info type(skill/fashion/trump/citta/horse/Achieve/formation/bag/attr/pet/title/guild/cuiti/zodtrump/collect)"},
        {GMT_DEBUG, "SysMailTest",&SysMailTest,"//BodyID,BodyParam,Title,AttachType,AttachId,AttachNum"},
        {GMT_DEBUG, "recruit",&Recruit,"//recruit fighterid"},
        {GMT_DEBUG, "fighter",&Fighter,"//fighter fighterid (强行招募散仙)"},
        {GMT_DEBUG, "dujie",&FighterDujie,"//dujie level fighterid (指定ID散仙渡劫等级)"},

        {GMT_DEBUG, "pet",&Pet,"//pet wPetID"},
        {GMT_DEBUG, "chgpet",&ChgPet,"//chgpet wPetID"},

        {GMT_DEBUG, "fashion",&Fashion,"//fashion wItemID"},
        {GMT_DEBUG, "setfashion",&SetFashion,"//setfashion wItemID"},

        {GMT_DEBUG, "gm",&GmTest,"//GmTest"},

        {GMT_DEBUG, "createmonster",&CreateMonster,"//createmonster wGroupID"},
        {GMT_DEBUG, "creategather",&CreateGather,"//creategather wGather"},
        {GMT_DEBUG, "entermap",&EnterMap,"//entermap wMapId"},
        {GMT_DEBUG, "worldboss",&WorldBoss,"//worldboss wWorldBossID"},
        {GMT_DEBUG, "buy",&Buy,"//buy storetype[0-5] wItemID wCount"},
        {GMT_DEBUG, "enterssb",&EnterShushanBattle,"//enterssb"},
        {GMT_DEBUG, "buff", &Buff, "//buff"},
        {GMT_DEBUG, "testactivity", &TestActivity, "//testactivity wtype"},
        {GMT_DEBUG, "setvip", &SetVIP, "//setvip level"},
        {GMT_DEBUG, "bp", &BattlePoint, "//bp(BattlePoint)"},
        {GMT_DEBUG, "hp", &GetPlayerHP, "//hp(GetPlayerHP)"},
        {GMT_DEBUG, "gb", &GuildBattle, "//gb(GuildBattle) info/start/debug/set/fast"},
        {GMT_DEBUG, "ngb", &NewGuildBattle, "//ngb(NewGuildBattle) start/time/set/dump"},
        {GMT_DEBUG, "sit", &DoSit, "//sit qwRoleID"},
        {GMT_DEBUG, "loot", &Loot, "//loot lootid"},
        {GMT_DEBUG, "beastsoul", &BeastSoul, "//beastsoul"},
        {GMT_DEBUG, "dis", &Discount, "//dis(Discount)"},
        {GMT_DEBUG, "openact", &OpenAct, "//openact(开启精彩活动) wActID sAdvance sBegin sEnd sRetain(非必须)"},
        {GMT_DEBUG, "endact", &EndAct, "//openact wActID"},
        {GMT_DEBUG, "showmem", &ShowMem, "//showmem"},
        {GMT_DEBUG, "oi", &OpenIcon, "//OpenIcon"},
        {GMT_DEBUG, "change", &MoneyChange, "//Change [srcType destType dwCount]" },
        {GMT_DEBUG, "recharge", &Recharge, "//recharge dwRecharge"},
    };

    void GameReloadLua(const char* cmd, const Tokenizer& params, void*)
    {
        if (!Config.GetScript().ReloadScripts(SCRIPT_TYPE_ALL))
        {
            LOG_CRI << __PRETTY_FUNCTION__ << ": reloading lua error.";
        }
    }

    void ShowMem(const char* cmd, const Tokenizer& params, void*)
    {
        CTimerMgr::Instance().CallMem();
    }

    void GameCfgReload(const char* cmd, const Tokenizer& params, void*)
    {
        CItemMgr::LoadConfig(true);
        CSkillMgr::Instance().ReloadCfg(Config._strConfigDir);
        CFighterMgr::LoadConfig(true);
        BattleConfigReload(Config._strConfigDir);
        CGuildBattleConfigMgr::Instance().Reload();

    }

    void Item(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 1)
            return;
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.wItemID = atoi(params[0].c_str());
        if (params.size() >= 2)
            oItemGenInfo.dwCount = atoi(params[1].c_str());
        if (params.size() >= 3)
            oItemGenInfo.eBindType = atoi(params[2].c_str())?eBindGet:eBindNone;
        if (params.size() >= 4)
            oItemGenInfo.byQuality = atoi(params[3].c_str());

        CUserPtr pUser = *(CUserPtr*)p;
        if (CItemType::IsTrump(oItemGenInfo.wItemID))
        {
            LOG_INF << "AddTrump: " << oItemGenInfo.wItemID << ", " << oItemGenInfo.dwCount << ", " << oItemGenInfo.eBindType << ".";
            CPlayerPtr pPlayer = pUser->GetPlayer();
            if (!pPlayer)
                return;
            pPlayer->GetFighterManager()->GetTrumpSlots().ActiveTrump(oItemGenInfo.wItemID);
        }
        else
        {
            CStore& rStore = pUser->GetPack();
            rStore.AddItem(oItemGenInfo, (NLogDataDefine::ItemFrom_System));
        }
        return;
    }

    void AddLoot(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 1)
        {
            return ;
        }
         UINT16 wLoot = atoi(params[0].c_str());
         CPlayerPtr pPlayer;
         CUserPtr pUser = *(CUserPtr*)p;
         pPlayer = pUser->GetPlayer();
         if(NULL == pPlayer)
         {
             return ;
         }
         LOOT.CheckAndAddItem(wLoot,pUser);

    }

    void OpenAct(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 3)
            return;
        UINT16 wActID = atoi(params[0].c_str());
        string sAdv(params[1]);
        string sBegin(params[2]);
        string sEnd(params[3]);
        string sRetain(params[4]);
        g_WondActMgr.OpenActivity(wActID,sAdv,sBegin,sEnd,sRetain);
    }

    void EndAct(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 1)
            return;
        UINT16 wActID = atoi(params[0].c_str());
        g_WondActMgr.EndActivity(wActID);
    }

    void LeavePlayerDgn(const char* cmd, const Tokenizer& params, void* p)
    {
        CPlayerPtr pPlayer;
        CUserPtr pUser = *(CUserPtr*)p;
        pPlayer = pUser->GetPlayer();
        if (NULL == pPlayer)
        {
            return;
        }
        CDungeonMgr::PlayerLeaveDungeon(*pPlayer);
    }

    void FinishPlayerDgn(const char* cmd, const Tokenizer& params, void* p)
    {
        CPlayerPtr pPlayer;
        CUserPtr pUser = *(CUserPtr*)p;
        pPlayer = pUser->GetPlayer();
        if (NULL == pPlayer)
        {
            return;
        }
        CDungeonMgr::PlayerFinishDungeon(*pPlayer);
    }

    void PlayerDgnKillAll(const char* cmd, const Tokenizer& params, void* p)
    {
        CPlayerPtr pPlayer;
        CUserPtr pUser = *(CUserPtr*)p;
        pPlayer = pUser->GetPlayer();
        if (NULL == pPlayer)
        {
            return;
        }
        CDungeonMgr::PlayerDungeonKillAll(*pPlayer);
    }

    void EnterPlayerDgn(const char* cmd, const Tokenizer& params, void* p)
    { 
        if (params.size() < 1)
            return;
        CPlayerPtr pPlayer;
        CUserPtr pUser = *(CUserPtr*)p;
        pPlayer = pUser->GetPlayer();
        if (NULL == pPlayer)
        {
            return;
        }
        UINT32 wDgnType = atoi(params[0].c_str());
        CDungeonMgr::PlayerEnterNewDungeon(*pPlayer, wDgnType,NULL,true);


    }

    void UseItem(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 1)
            return;

        UINT16 wCount = 0;
        UINT8 byBind = 0;
        UINT16 wItemID = atoi(params[0].c_str());
        if (params.size() >= 2)
            wCount = atoi(params[1].c_str());
        if (params.size() >= 3)
            byBind = atoi(params[2].c_str());

        CUserPtr pUser = *(CUserPtr*)p;
        CPack& rPack = pUser->GetPack();
        rPack.UseItem((UINT64)0, wItemID, wCount, (bool)byBind);
    }

    void UItem(const char* cmd, const Tokenizer& params, void* p)
    {
    }

    void DelItem(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 1)
            return;

        UINT16 wCount = 0;
        UINT16 wItemID = atoi(params[0].c_str());
        if (params.size() >= 2)
            wCount = atoi(params[1].c_str());

        CUserPtr pUser = *(CUserPtr*)p;
        CPack& rPack = pUser->GetPack();
        rPack.DelItemByItemID(wItemID, wCount, true, NLogDataDefine::ItemTo_GM);
    }

    void SwapItem(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 4)
            return;

        EStoreType eFromStoreType = (EStoreType)atoi(params[0].c_str());
        INT16 wFromIndex = atoi(params[1].c_str());
        EStoreType eToStoreType = (EStoreType)atoi(params[2].c_str());
        INT16 wIndex = atoi(params[3].c_str());

        CUserPtr pUser = *(CUserPtr*)p;
        CStore* pFromStore = pUser->GetStoreByType(eFromStoreType);
        CStore* pToStore = pUser->GetStoreByType(eToStoreType);
        if(pFromStore == NULL || pToStore == NULL)
            return;
        if(wIndex == -1 && pToStore->IsStoreFull())
            return;

        CItemPtr pFromItem = pFromStore->GetItem(wFromIndex);
        if(pFromItem == NULL)
            return;

        if(eItemTask == pFromItem->GetItemType())
            return;

        CItemPtr pToItem = pToStore->GetItem(wIndex);
        if(pToItem == NULL)//目标容器制定位置有道具则交换
        {
            if(pToStore->AddItem(*pFromItem, wIndex, true, false, true, NLogDataDefine::ItemFrom_GM))
            {
                pFromStore->DelItem(*pFromItem, true, true, NLogDataDefine::ItemTo_GM);
            }
        }
        else
        {
            if(eItemTask == pToItem->GetItemType())
                return;

            if(CItemMgr::MergeStackItem(*pFromStore, *pToStore, *pFromItem, *pToItem))
                return;
            else
            {
                if(CItemMgr::TransferStoreItem(*pFromStore, *pToStore, *pFromItem, wFromIndex, *pToItem, wIndex))
                    return;
            }
        }
    }

    void SellItem(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 2)
            return;
        UINT16 wCount = 0;
        UINT8 byBind = 0;
        UINT16 wItemID = atoi(params[0].c_str());
        if (params.size() >= 2)
            wCount = atoi(params[1].c_str());
        if (params.size() >= 3)
            byBind = atoi(params[2].c_str());

        CUserPtr pUser = *(CUserPtr*)p;
        CPack& rPack = pUser->GetPack();
        rPack.SellItemWithCount((UINT64)0, wItemID, wCount, (bool)byBind);
    }

    void NPC(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 3)
            return;

        UINT16 wNpcID = atoi(params[0].c_str());
        float fX = atof(params[1].c_str());
        float fY = atof(params[2].c_str());

        CUserPtr pUser = *(CUserPtr*)p;
        SPoint sPoint(fX, fY);
        pUser->GetPlayer()->GetMap()->AddNpc(wNpcID, &sPoint);
    }

    void LevelUp(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        int level = 1;
        if (params.size())
            level = atoi(params[0].c_str());
        level = level < 1 ? 1 : level;

        UINT64 qwExp = CExpMgr::GetLevelMin(level);
        UINT64 qwOldExp = CExpMgr::GetLevelMin(pUser->GetPlayer()->GetLevel());
        while (!qwExp && level > 1)
            qwExp = CExpMgr::GetLevelMin(--level);
        if (qwOldExp < qwExp)
            pUser->GetPlayer()->AddExp(qwExp - qwOldExp);
        ostringstream strInfo;
        strInfo << "等级： " << static_cast<UINT32>(pUser->GetPlayer()->GetLevel()) << ".\n";
        strInfo << "经验值： " << pUser->GetPlayer()->GetExp() << ".\n";
        ChatSysLog(strInfo.str(), *pUser);
    }

    void Level(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        int level = 1;
        if (params.size())
            level = atoi(params[0].c_str());
        level = level < 1 ? 1 : level;

        UINT64 qwExp = CExpMgr::GetLevelMin(level);
        UINT64 qwOldExp = CExpMgr::GetLevelMin(pUser->GetPlayer()->GetLevel());
        while (!qwExp && level > 1)
            qwExp = CExpMgr::GetLevelMin(--level);
        if (qwOldExp <= qwExp)
            pUser->GetPlayer()->AddExp(qwExp - qwOldExp);
        else
            pUser->GetPlayer()->SubExp(qwOldExp - qwExp);

        ostringstream strInfo;
        strInfo << "等级： " << static_cast<UINT32>(pUser->GetPlayer()->GetLevel()) << ".\n";
        strInfo << "经验值： " << pUser->GetPlayer()->GetExp() << ".\n";
        ChatSysLog(strInfo.str(), *pUser);
    }

    void Exp(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 iExp = 1;
        if (params.size())
            iExp = atoi(params[0].c_str());

        if (iExp > 0)
            pUser->GetPlayer()->AddExp(iExp);
        else
            pUser->GetPlayer()->SubExp(abs(iExp));
        ostringstream strInfo;
        strInfo << "等级： " << static_cast<UINT32>(pUser->GetPlayer()->GetLevel()) << ".\n";
        strInfo << "经验值： " << pUser->GetPlayer()->GetExp() << ".\n";
        ChatSysLog(strInfo.str(), *pUser);
    }

    void PExp(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 iPExp = 1;
        if (params.size())
            iPExp = atoi(params[0].c_str());

        if (iPExp > 0)
            pUser->AddMoney(EMONEY_PEXP,iPExp,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_PEXP,abs(iPExp),NLogDataDefine::ItemTo_GM);
    }

   void TestActivity(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wNum = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        pUser->GetPlayer()->GetActivityPkg().AddActivity(wNum);


    }

    void SetVIP(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 1)
        {
            return;
        }
        UINT8 byLevel = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        byLevel = byLevel > 15 ? 15 : byLevel;
        /*
        if (byLevel == 0)
        {
            pUser->SetVIPLevel(byLevel);
            pUser->GetVars().DelVar(NVarDefine::ePlayerVIPGrowthValue);
            pUser->GetVars().DelVar(NVarDefine::ePlayerVIPEndTime);
            pUser->GetVars().DelVar(NVarDefine::ePlayerVIPType);
            pUser->GetVars().DelVar(NVarDefine::ePlayerVIPGetDayPack);
            pUser->GetVars().DelVar(NVarDefine::ePlayerVIPGetLevelAward);
            return;
        }
        SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(byLevel);
        if (pVIPLvlCfg)
            pUser->GetVars().SetVar(NVarDefine::ePlayerVIPGrowthValue, pVIPLvlCfg->_Exp);
        SVIPBaseCFGEx* pVIPBaseCfg = VIPMgr.GetVIPBaseCfg(CRandom::RandInt(1, 3));
        if (pVIPBaseCfg)
        {
            pUser->GetVars().SetVar(NVarDefine::ePlayerVIPEndTime, time(NULL)+pVIPBaseCfg->_Days*86400);
            pUser->GetVars().SetVar(NVarDefine::ePlayerVIPType, pVIPBaseCfg->_ID);
            pUser->GetVars().SetVar(NVarDefine::ePlayerVIPDayTime, Time::TheDay(1));
        }
        */
        SVIPLevelCFGEx* pVIPCfg = CVIPMgr::GetVIPLevelCfg(byLevel);
        if (!pVIPCfg)
            return;
        pUser->SetTotalRecharge(pVIPCfg->_Exp);
        pUser->SetVIPLevel(byLevel);
        pUser->SendVIPInfoToClt();
        g_PropInfoS.ChangeTotalRecharge(*(pUser->GetPlayer()), pUser->GetTotalRecharge());
    }

    void AddOwnTitle(const char* cmd, const Tokenizer& params, void* p )
    {
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wTitle = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        UINT32 dwtime = 0;
        if(params.size() >= 2)
        {
           dwtime = atoi(params[1].c_str());
        }
        //pUser->GetPlayer()->AddOwnTitle(wTitle);
        pUser->GetPlayer()->GetTitlePkg().AddTitle(wTitle,dwtime);

    }

    void DelOwnTitle(const char* cmd, const Tokenizer& params, void* p )
    {
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wTitle = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        //pUser->GetPlayer()->DelOwnTitle(wTitle);
        pUser->GetPlayer()->GetTitlePkg().DelTitle(wTitle);
    }

    void CreateMonster(const char* cmd, const Tokenizer& params, void* p )
    {
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wGroup = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        SPoint point(pUser->GetPlayer()->GetPoint());

        if(params.size() == 3)
        {
            point.fX =atof(params[1].c_str());
            point.fY=atof(params[2].c_str());
        }
        pUser->GetPlayer()->GetMap()->AddMonster(wGroup,&point);

    }

    void CreateGather(const char* cmd, const Tokenizer& params, void* p )
    {
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wGather = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        SPoint point(pUser->GetPlayer()->GetPoint());

        if(params.size() == 3)
        {
            point.fX =atof(params[1].c_str());
            point.fY=atof(params[2].c_str());
        }
        pUser->GetPlayer()->GetMap()->AddGather(wGather,&point);

    }

    void Buff(const char* cmd, const Tokenizer& params, void* p )
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        ostringstream strInfo;
        if (params.size() <= 0)
        {
            strInfo << "Buff: ";
            TVecUINT16 vecBuffID;
            TVecBuffInfo vecBuffInfo;
            if (pPlayer->GetAllBuffData(vecBuffID, vecBuffInfo) == eBORSuccess)
            {
                auto it = vecBuffID.begin();
                auto it2 = vecBuffInfo.begin(); 
                 for (;it != vecBuffID.end() && it2 != vecBuffInfo.end(); 
                        ++it, ++it2)
                {
                    strInfo << *it << ", " << (*it2).wBuffID << "(" << (*it2).dwBuffTime << ")" << (*it2).dwBuffCount << "; ";
                }
            }
        }
        else
        {
            string strType = params[0];
            if (strType.compare("add") == 0)
            {
                if (params.size() < 2)
                    return;
                pPlayer->AddBuff(atoi(params[1].c_str()));
            }
            else if (strType.compare("clear") == 0)
            {
                TVecUINT16 vecBuffID;
                TVecBuffInfo vecBuffInfo;
                pPlayer->GetAllBuffData(vecBuffID, vecBuffInfo);
                for (auto& rID : vecBuffID)
                {
                    pPlayer->RemoveBuff(rID);
                }
            }
        }

        ChatSysLog(strInfo.str(), *pUser, '\n');
    }

    void EnterMap(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wMapID = atoi(params[0].c_str());;
        CGameMapPtr pMap = CMapMgr::GetMap(wMapID);
        if(NULL == pMap)
        {
            return ;
        }
        SPoint oPoint(pMap->GetMapInfo().oRealivePoint.fX,pMap->GetMapInfo().oRealivePoint.fY);
        pPlayer->JumpMap(pMap,oPoint,0);

    }

    void WorldBoss(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (params.size() < 1)
            return ;
        UINT16 wBossID = atoi(params[0].c_str());;
        CWorldBossMgr::Instance().BossAppear(wBossID);
    }

    void Buy(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (params.size() < 3)
            return ;

        UINT8 byType = atoi(params[0].c_str());
        UINT16 wItemID = atoi(params[1].c_str());
        UINT16 wCount = atoi(params[2].c_str());
        CMall::Instance().BuyItem(*pUser, (EUseMoneyMark)0, (EMallType)byType, wItemID, wCount);
    }

    void ShowOwnTitle(const char* cmd, const Tokenizer& params, void* p )
    {
        CUserPtr pUser = *(CUserPtr*)p;
        TVecUINT16 vecTitles;
        pUser->GetPlayer()->GetOwnTitle(vecTitles);
        LOG_DBG << "OwnTitle Size is "<<vecTitles.size();
        if (!vecTitles.empty()) 
        {
            stringstream buff;
            for (size_t sz = 0; sz != vecTitles.size()  ;sz++)
            {
                if(sz != 0)
                    buff << ",";
                else 
                    buff << "(";
                buff << vecTitles[sz];
                if (sz == vecTitles.size()-1)
                    buff << ")";
            }
            LOG_DBG <<"NUMberIs :" <<buff.str();
        }

    }

    void AddEquipTitle(const char* cmd, const Tokenizer& params, void* p )
    {
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wTitle = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        pUser->GetPlayer()->AddEquipTitle(wTitle);

    }

    void DelEquipTitle(const char* cmd, const Tokenizer& params, void* p )
    {
        if (params.size() < 1)
        {
            return ;
        }
        UINT16 wTitle = atoi(params[0].c_str());
        CUserPtr pUser = *(CUserPtr*)p;
        pUser->GetPlayer()->DelEquipTitle(wTitle);

    }

    void ShowEquipTitle(const char* cmd, const Tokenizer& params, void* p )
    {
        CUserPtr pUser = *(CUserPtr*)p;
        TVecUINT16 vecTitles;
        pUser->GetPlayer()->GetEquipTitle(vecTitles);
        LOG_DBG << "EquipTitle Size is "<<vecTitles.size();
        if (!vecTitles.empty()) 
        {
            stringstream buff;
            for (size_t sz = 0; sz != vecTitles.size()  ;sz++)
            {
                if(sz != 0)
                    buff << ",";
                else 
                    buff << "(";
                buff << vecTitles[sz];
                if (sz == vecTitles.size()-1)
                    buff << ")";
            }
            LOG_DBG <<"NUMberIs :" <<buff.str();
        }
    }

    void Gold(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_GOLD,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_GOLD,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Star(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_REIKI,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_REIKI,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Coupon(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_COUPON,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_COUPON,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Silver(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_SILVER,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_SILVER,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Soul(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_SOUL,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_SOUL,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Honor(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_HONOR,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_HONOR,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Prestige(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_PRESTIGE,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_PRESTIGE,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Sigil(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_SIGIL,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_SIGIL,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void CentsY(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_CENTSY,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_CENTSY,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Action(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_ACTION,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_ACTION,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Sop(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_SOP,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_SOP,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Poten(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_POTEN,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_POTEN,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void Taoism(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 value = atoi(params[0].c_str());
        if (value > 0)
            pUser->AddMoney(EMONEY_TAOISM,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney(EMONEY_TAOISM,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void AddMoney(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size()<2)
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        INT32 dwMoneyType = atoi(params[0].c_str());
        INT32 value = atoi(params[1].c_str());
        if (value > 0)
            pUser->AddMoney((EMoneyType)dwMoneyType,value,NLogDataDefine::ItemFrom_GM);
        else
            pUser->SubMoney((EMoneyType)dwMoneyType,abs(value),NLogDataDefine::ItemTo_GM);
    }

    void TopUp(const char* cmd, const Tokenizer& params, void* p)
    {
        if (params.size() < 2)
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        UINT16 wGoldID = atoi(params[0].c_str());
        UINT32 dwCount = atoi(params[1].c_str());
        if (!dwCount)
            return;
        if ((wGoldID < 41 || wGoldID > 46) && (wGoldID < 180 || wGoldID > 185))
            return;
        string strNo = NumberToString(time(NULL)) +"_123456";
        static const UINT32 dwGolds[6] = { 10, 100, 300, 500, 1000, 3000 };    //XXX 仙石包ID对应的仙石单价
        int idx = 0;
        if (wGoldID >= 41 && wGoldID <= 46)
            idx = wGoldID - 41;
        else
            idx = wGoldID - 180;
        SRecharge oRecharge(strNo, pUser->GetUserID(), wGoldID, dwCount, dwCount*dwGolds[idx], 0, time(NULL));
        g_Game2DBCommC.Send_UpdateRecharge(oRecharge);
        sleep(2);
        oRecharge.byStatus = 1;
        bool bRes = pUser->AddTotalRecharge(oRecharge.dwGold);
        if (bRes)
        {
            g_Game2DBCommC.Send_UpdateRecharge(oRecharge);
            CMall::Instance().OnChongZhiAward(wGoldID, dwCount, pUser);
        }
    }

    void RobotBoost(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        UINT32 dwMode = 0;
        if (params.size() >= 1)
            dwMode = atoi(params[0].c_str());
        CDungeonMgr::PlayerFinishDungeon(*pPlayer);

        UINT64 qwInstID = pPlayer->GetDgnInstID();
        if(qwInstID)
        {
            CDungeonPtr pDungeon = CDungeonMgr::GetDungeon(qwInstID);
            if(pDungeon)
                pDungeon->PlayerLeave(*pPlayer);
        }
        pUser->RobotBoost(dwMode);
    }

    void Boost(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        UINT32 dwMode = 0;
        if (params.size() >= 1)
            dwMode = atoi(params[0].c_str());
        CDungeonMgr::PlayerFinishDungeon(*pPlayer);

        UINT64 qwInstID = pPlayer->GetDgnInstID();
        if(qwInstID)
        {
            CDungeonPtr pDungeon = CDungeonMgr::GetDungeon(qwInstID);
            if(pDungeon)
                pDungeon->PlayerLeave(*pPlayer);
        }
        pUser->Boost(dwMode);
    }

    void Super(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        pUser->Super();
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        UINT64 qwInstID = pPlayer->GetDgnInstID();
        if(qwInstID)
        {
            CDungeonPtr pDungeon = CDungeonMgr::GetDungeon(qwInstID);
            if(pDungeon)
                pDungeon->PlayerLeave(*pPlayer);
        }
        pPlayer->Super();

    }

    void AcceptTask(const char* cmd, const Tokenizer& params, void* p )
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        UINT16 wTaskId = atoi(params[0].c_str());
        pUser->GetTaskPkg().GMAddTask(wTaskId);


    }

    void GiveupTask(const char* cmd, const Tokenizer& params, void* p )
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        UINT16 wTaskId = atoi(params[0].c_str());
        pUser->GetTaskPkg().GiveUpTask(wTaskId);


    }

    void CommitTask(const char* cmd, const Tokenizer& params, void* p )
    {
        if (!params.size())
            return;
        bool force = false;
        bool bMulti = false;
        if(params.size() >= 2)
        {
            force  = true;
            UINT16 wMulti = atoi(params[1].c_str());
            if(wMulti == 255)
            {
                bMulti = true;
            }
        }
                
        CUserPtr pUser = *(CUserPtr*)p;
        UINT16 wTaskId = atoi(params[0].c_str());
        if(!bMulti)
        {
        if(!force)
        {
          pUser->GetTaskPkg().FinishTask(wTaskId,0,false);
        }
        else
        {
            pUser->GetTaskPkg().SetFinishTask(wTaskId);
        }
        }
        else
        {
            pUser->GetTaskPkg().FinishAllMainTask(wTaskId);
        }

    }

    void VarDec(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;

        UINT16 wVar = atoi(params[0].c_str());
        int iType = -1;
        if (params.size() > 1)
            iType = atoi(params[1].c_str());
        CGameVar::DecVar(wVar, (VarRecycle_e)iType);
    }

    void VarAdd(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        UINT16 wVar = atoi(params[0].c_str());
        UINT64 qwValue = 1;
        if (params.size() > 1)
            qwValue = atol(params[1].c_str());
        pUser->GetVars().AddVar(wVar, qwValue);
    }

    void VarGet(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        UINT16 wVar = atoi(params[0].c_str());
        UINT64 qwValue = pUser->GetVars().GetVar(wVar);
        ostringstream strInfo;
        strInfo << "Var(" << wVar << "): " << qwValue << ".";
        ChatSysLog(strInfo.str(), *pUser, '\n');
    }

    void VarDel(const char* cmd, const Tokenizer& params, void* p)
    {
        if (!params.size())
            return;
        CUserPtr pUser = *(CUserPtr*)p;
        UINT16 wVar = atoi(params[0].c_str());
        pUser->GetVars().DelVar(wVar);
    }

    // GM 发起战斗
    void StartBattle(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;

        UINT16 wMaxCount = 1;
        if (params.size())
            wMaxCount = atoi(params[0].c_str());

        for (UINT16 wCount = 0; wCount < wMaxCount; ++wCount)
        {
            IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));

            TVecBattleFighterPtr vecBattleFighter;
            pPlayer->GetBattleFighterList(vecBattleFighter);

            TVecBattleFighterPtr vecBattleFighter2;
            pPlayer->GetBattleFighterList(vecBattleFighter2);
            pBS->PutFighters(0, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter, pPlayer->GetRoleID());
            pBS->PutFighters(1, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter2, pPlayer->GetRoleID() + 1);
            pBS->PutScene(pPlayer->GetSceneFighter());

            pBS->Start(EBTPlayer);

            std::string strReport;
            pBS->GetReport(strReport);

            std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID());
            pPlayer->SendPkg(strData);

            ostringstream strInfo;
            strInfo << pBS->GetBattleID();
            ChatSysLog(strInfo.str(), *pUser, '\n');
        }
    }

    void AttackPlayer(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (!params.size())
            return;
        UINT64 qwTargetID = atol(params[0].c_str());
        if (!qwTargetID)
            return;
        if (qwTargetID <= 0xFFFFFFFF)
            qwTargetID = CGUIDMgr::GetGUID(Config._wGroup, 0, GUID_ROLE, qwTargetID);
        CUserPtr pUser2 = CUserMgr::GetUserByUserID(qwTargetID);
        if (!pUser2)
        {
            CUserMgr::LoadUser(qwTargetID,
                    [pPlayer](CUserPtr pOthUser)
                    {
                        if (!pOthUser || !pOthUser->GetPlayer())
                            return;
                        CPlayerPtr pPlayer2 = pOthUser->GetPlayer();

                        IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
                        TVecBattleFighterPtr vecBattleFighter;
                        pPlayer->GetBattleFighterList(vecBattleFighter);


                        TVecBattleFighterPtr vecBattleFighter2;
                        pPlayer2->GetBattleFighterList(vecBattleFighter2);
                        pBS->PutFighters(0, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter, pPlayer->GetRoleID());
                        pBS->PutFighters(1, pPlayer2->GetMainFighter()->GetInstID(), pPlayer2->GetLevel(), vecBattleFighter2, pPlayer2->GetRoleID() + 1);
                        pBS->PutScene(pPlayer->GetSceneFighter());

                        pBS->Start(EBTPlayer);

                        std::string strReport;
                        pBS->GetReport(strReport);

                        std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID());
                        pPlayer->SendPkg(strData);
                    });
            return;
        }

        CPlayerPtr pPlayer2 = pUser2->GetPlayer();
        if (!pPlayer2)
            return;

        IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
        TVecBattleFighterPtr vecBattleFighter;
        pPlayer->GetBattleFighterList(vecBattleFighter);

        TVecBattleFighterPtr vecBattleFighter2;
        pPlayer2->GetBattleFighterList(vecBattleFighter2);
        pBS->PutFighters(0, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter, pPlayer->GetRoleID());
        pBS->PutFighters(1, pPlayer2->GetMainFighter()->GetInstID(), pPlayer2->GetLevel(), vecBattleFighter2, pPlayer2->GetRoleID() + 1);
        pBS->PutScene(pPlayer->GetSceneFighter());

        pBS->Start(EBTPlayer);

        std::string strReport;
        pBS->GetReport(strReport);

        std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID());
        pPlayer->SendPkg(strData);
    }

    void Attack(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        UINT32 dwEnemyID = 1;
        if (params.size())
            dwEnemyID = atoi(params[0].c_str());

        UINT32 wMaxCount = 1;
        if (params.size() >= 2)
            wMaxCount = atoi(params[1].c_str());

        for (UINT16 wCount = 0; wCount < wMaxCount; ++wCount)
        {
            IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));

            TVecBattleFighterPtr vecBattleFighter;
            pPlayer->GetBattleFighterList(vecBattleFighter);


            vector<TVecBattleFighterPtr> vecvecBattleFighter2;
            UINT64 qwTmpInstID =  1;
            qwTmpInstID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, dwEnemyID, qwTmpInstID, vecBattleFighter);
            if (!qwTmpInstID)
                return;
            pBS->PutFighters(0, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter, pPlayer->GetRoleID());
            pBS->PutFighters(1, qwTmpInstID, CMonsterMgr::GetMonsterLevel(dwEnemyID), vecvecBattleFighter2[0], 1);

            IBattleFighterPtr pFighter = CMonster::GetSceneFighter(dwEnemyID);
            if (!pFighter)
                pFighter = pPlayer->GetSceneFighter();
            pBS->PutScene(pFighter);
            pBS->Start(EBTMonster);

            std::string strReport;
            pBS->GetReport(strReport);

            std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID());
            pPlayer->SendPkg(strData);

            ostringstream strInfo;
            strInfo << pBS->GetBattleID();
            ChatSysLog(strInfo.str(), *pUser, '\n');
        }
    }

    void BattleInfo(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (!params.size())
            return;
        UINT64 qwReportID = atol(params[0].c_str());
        GetBattleReport(qwReportID, 
                [pPlayer](string* pstrData)
                {
                    if (pstrData)
                    {
#ifdef _DEBUG
                        CInArchive ar(*pstrData);
                        NBattleGS::SBattleReport sReport;
                        ar >> sReport;
                        CreateDirectory("BattleProtocol");
                        ostringstream ostrName;
                        ostrName << sReport.qwBattleID << ".xml";
                        TiXmlElement* pElement = new TiXmlElement(ostrName.str().c_str());
                        if(pElement)
                        {
                            if(ToXML(sReport, *pElement))
                            {
                                TiXmlDocument doc;
                                TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
                                if(pDecl)
                                {
                                    doc.LinkEndChild(pDecl);
                                    doc.LinkEndChild(pElement);
                                    ostrName.str("");
                                    ostrName << "BattleProtocol/" << sReport.qwBattleID << ".xml";
                                    doc.SaveFile(ostrName.str().c_str());
                                }
                            }
                        }
#endif
                        string strData = g_BattleGSS.BuildPkg_BattleReportData(*pstrData, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID());
                        pPlayer->SendPkg(strData);
                    }
                });
    }

    void BattleRestart(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (!params.size())
            return;
        UINT64 qwReportID = atol(params[0].c_str());
        GetBattleReport(qwReportID, 
                [pPlayer](string* pstrData)
                {
                    if (pstrData)
                    {
#ifdef _DEBUG
                        CInArchive ar(*pstrData);
                        NBattleGS::SBattleReport sReport;
                        ar >> sReport;
                        if (sReport.vAGroups.empty() || sReport.vBGroups.empty())
                            return;
                        IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
                        TVecBattleFighterPtr vecBattleFighter;
                        TVecBattleFighterPtr vecBattleFighter2;
                        for (auto& rInfo : sReport.vAGroups[0].vFighters)
                        {
                            IBattleFighterPtr pBattleFighter = CreateBattleFighter();
                            if (!pBattleFighter || !pBattleFighter->InitFromInfo(rInfo, vecBattleFighter))
                                return;
                            vecBattleFighter.push_back(pBattleFighter);
                        }
                        for (auto& rInfo : sReport.vBGroups[0].vFighters)
                        {
                            IBattleFighterPtr pBattleFighter = CreateBattleFighter();
                            if (!pBattleFighter || !pBattleFighter->InitFromInfo(rInfo, vecBattleFighter2))
                                return;
                            vecBattleFighter2.push_back(pBattleFighter);

                        }

                        pBS->PutFighters(0, sReport.vAGroups[0].qwCreatrueID, sReport.vAGroups[0].wLevel, vecBattleFighter, sReport.vAGroups[0].qwLeaderID);
                        pBS->PutFighters(1, sReport.vBGroups[0].qwCreatrueID, sReport.vBGroups[0].wLevel, vecBattleFighter2, sReport.vBGroups[0].qwLeaderID);
                        pBS->Start(EBTPlayer);

                        std::string strReport;
                        pBS->GetReport(strReport);

                        std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID());
                        pPlayer->SendPkg(strData);
#endif
                    }
                });
    }

    void BattleCheat(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        UINT32 dwParam = 0;
        char chSplit = '\n';
        ostringstream strInfo;
        if (params.size() >= 1)
        {
            dwParam = atoi(params[0].c_str());
            strInfo << "战斗作弊模式: ";
            dwParam = BattleCheatMode(dwParam);
            strInfo  << dwParam << ".";
        }
        else
        {
            strInfo << "作弊模式(" << "???" << ")" << chSplit;
            strInfo << "1. 100%概率" << chSplit;
            strInfo << "2. 不开启被动技能" << chSplit;
            strInfo << "4. 100%暴击" << chSplit;
            strInfo << "8. 主将不出战" << chSplit;
            strInfo << "16. 不开启主动技能" << chSplit;
            strInfo << "32. 100%反击" << chSplit;
            strInfo << "64. 50%闪避" << chSplit;
        }

        ChatSysLog(strInfo.str(), *pUser, chSplit);
        LOG_DBG << strInfo.str();
    }

    // 发送玩家具体信息
    void SendInfo(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
        if (!pFighterManager)
            return;

        ostringstream strInfo;
        std::string strType;
        if (params.size())
            strType = params[0];

        if (strType.compare("trump") == 0 || strType.compare("all") == 0)
        {
            strInfo << "光环属性：\n" ;
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpTrumpHalo);
            strInfo << GetAddAttrStr(vecAttr) << "\n";

            strInfo << "附加属性：\n" ;
            vecAttr = pFighterManager->GetGroupAttr(eAttrGpTrumpExtra);
            strInfo << GetAddAttrStr(vecAttr) << "\n";

            strInfo << "激活属性：\n" ;
            vecAttr = pFighterManager->GetGroupAttr(eAttrGpTrumpActive);
            strInfo << GetAddAttrStr(vecAttr) << "\n";

            strInfo << "技能：\n";
            CTrumpSlots& rTrumpSlot = pFighterManager->GetTrumpSlots();
            UINT32 dwPeerless = rTrumpSlot.GetPeerlessSkill();

            if (dwPeerless)
            {
                SSkillPtr pSkill = CSkillMgr::Instance().GetSkill(SKILL_ID(dwPeerless));
                if (pSkill)
                    strInfo << pSkill->_strName << "(LV" << SKILL_LEVEL(dwPeerless) << ")\t";
            }

            TVecUINT32 vecPassiveSkill;
            rTrumpSlot.GetPassiveSkills(vecPassiveSkill);
            for (auto it = vecPassiveSkill.begin(); it != vecPassiveSkill.end(); ++it)
            {
                SSkillPtr pSkill = CSkillMgr::Instance().GetSkill(SKILL_ID(*it));
                if (pSkill)
                    strInfo << pSkill->_strName << "(LV" << SKILL_LEVEL(*it) << ")\t";
            }
            strInfo << "\n";
        }
        if (strType.compare("fashion") == 0 || strType.compare("all") == 0)
        {
            strInfo << "时装属性：\n" ;
            TVecFloat vecAttr;
            if (pFighterManager->GetFashionSlots().GetAddAttr(vecAttr))
                strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("citta") == 0 || strType.compare("all") == 0)
        {
            strInfo << "天书属性：\n" ;
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpCitta);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("horse") == 0 || strType.compare("all") == 0)
        {
            strInfo << "坐骑属性：\n" ;
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpHorse);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("Achieve") == 0 || strType.compare("all") == 0)
        {
            strInfo << "成就属性：\n" ;
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpAchievement);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("formation") == 0 || strType.compare("all") == 0)
        {
            strInfo << "阵型属性：\n" ;
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpFormation);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("bag") == 0 || strType.compare("all") == 0)
        {
            strInfo << "背包属性：\n" ;
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpBag);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("pet") == 0 || strType.compare("all") == 0)
        {
            strInfo << "阵灵属性: "<< "\n";
            CPetPtr pPet = pFighterManager->GetFormationPet().GetCurrPet();
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpPet);
            if (pPet)
            {
                strInfo << "ID: " << pPet->GetID() << ", bySelected = " << static_cast<UINT32>(pPet->GetSelected()) << "\n";
                strInfo << GetAddAttrStr(vecAttr) << "\n";
            }
        }
        if (strType.compare("title") == 0 || strType.compare("all") == 0)
        {
            strInfo << "称号属性: "<< "\n";
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpTitle);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("guild") == 0 || strType.compare("all") == 0)
        {
            strInfo << "淬体帮派: "<< "\n";
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpGuildTech);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("cuiti") == 0 || strType.compare("all") == 0)
        {
            strInfo << "淬体属性: "<< "\n";
            TVecLineup vecLineup;
            CFormation& rFormation = pFighterManager->GetFormation();
            rFormation.GetLineup(vecLineup);
            for (size_t i = 0; i < vecLineup.size(); ++i)
            {
                if (!vecLineup[i].pFighter)
                    continue;
                if (!vecLineup[i].pFighter->IsHeroFighter())
                    continue;
                CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(vecLineup[i].pFighter);
                TVecFloat vecAttr = pHeroFighter->GetCuiTiAttr();
                strInfo << GetAddAttrStr(vecAttr) << "\n";
            }
        }
        if (strType.compare("collect") == 0 || strType.compare("all") == 0)
        {
            strInfo << "收集属性: "<< "\n";
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpCollection);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }
        if (strType.compare("beastsoul") == 0 || strType.compare("all") == 0)
        {
            strInfo << "兽魂属性: "<< "\n";
            TVecFloat vecAttr = pFighterManager->GetGroupAttr(eAttrGpBeastSoul);
            strInfo << GetAddAttrStr(vecAttr) << "\n";
        }

        ChatSysLog(strInfo.str(), *pUser, '\n');
    }

    void SysMailTest(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        if (params.size() < 3)
            return;
        UINT32 dwBodyID = atoi(params[0].c_str());
        string strParam = params[1];
        string Title = params[2];
        NMailProt::TVecMailAttachment vecAttach;
        TVecUINT64 vecTargets;
        vecTargets.push_back(pUser->GetUserID());
        if(params.size() >=6)
        {
            UINT8 dwType = atoi(params[3].c_str());
            UINT16 wItemType =atoi(params[4].c_str());
            UINT16 wItemCount = atoi(params[5].c_str());
            if(dwType == 0)//模板附件
            {
                SMailItemInfo stAttach;
                stAttach.wItemID = wItemType;
                stAttach.wCount = wItemCount;
                SItemAttachmentPtr ItemPtr(new SItemAttachment());
                ItemPtr->vecItemInfo.push_back(stAttach);
                vecAttach.push_back(ItemPtr);

            }
            else//实例附件
            {
                CItemPtr ItemPtr =  CItemMgr::CreateAllTypeItem(wItemType,wItemCount);
                if(ItemPtr != NULL)
                {

                    SItemInfo* pCfg = CItemMgr::GetItemConfig(wItemType);
                    if(NULL != pCfg)
                    {
                        switch (CItem::GetItemType(pCfg->oItemCfg))
                        {
                            case eItemCitta:
                                {
                                    CCitta& rCitta =  static_cast<CCitta&>(*ItemPtr);  
                                    SCittaPtr pSItemPtr(new SCitta());
                                    rCitta.ToStream(*pSItemPtr);
                                    SItemBaseCTPtr InsItemPtr(new SItemBaseCT());
                                    InsItemPtr->vecItems.push_back(pSItemPtr);
                                    vecAttach.push_back(InsItemPtr);

                                }
                                break;
                            case eItemFashion:
                                {
                                    CFashion& rFashion = static_cast<CFashion&>(*ItemPtr); 
                                    SFashionPtr pSItemPtr(new SFashion());
                                    rFashion.ToStream(*pSItemPtr);
                                    SItemBaseCTPtr InsItemPtr(new SItemBaseCT());
                                    InsItemPtr->vecItems.push_back(pSItemPtr);
                                    vecAttach.push_back(InsItemPtr);

                                }
                                break;
                            default:
                                {
                                    SItemPtr pSItemPtr(new SItem());
                                    ItemPtr->ToStream(*pSItemPtr);
                                    SItemBaseCTPtr InsItemPtr(new SItemBaseCT());
                                    InsItemPtr->vecItems.push_back(pSItemPtr);
                                    vecAttach.push_back(InsItemPtr);
                                }
                                break;
                        }
                    }

                }
            }
        }
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = dwBodyID;
        stBody.vecParam.push_back(strParam);
        g_Game2CenterCommC.Send_SendMail("系统",Title,stBody,vecAttach,vecTargets);
    }

    void Recruit(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        if (params.size() < 1)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;

        UINT16 wFighterID = atoi(params[0].c_str());
        pPlayer->GetFighterManager()->Recruit(wFighterID);
    }

    void Fighter(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        if (params.size() < 1)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;

        UINT16 wFighterID = atoi(params[0].c_str());
        pPlayer->GetFighterManager()->GetFighterForce(wFighterID);
    }

    void FighterDujie(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;

        if (params.size() < 1)
            return;
        UINT8 byLevel = atoi(params[0].c_str());

        UINT16 wFighterID = 0;
        if (params.size() >= 2)
            wFighterID = atoi(params[1].c_str());

        if (wFighterID)
        {
            CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByID(wFighterID);
            if (!pFighter)
                return;
            CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
            if (!pHeroFighter)
                return;
            pHeroFighter->SetDujieLevelByGM(byLevel);
        }
    }

    void Pet(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (!params.size())
            return;
        UINT16 wPetID = atoi(params[0].c_str());
        pPlayer->GetFighterManager()->GetFormationPet().GetPetSlots().AdoptPet(wPetID);
    }

    void ChgPet(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (!params.size())
            return;
        UINT16 wPetID = atoi(params[0].c_str());
        pPlayer->GetFighterManager()->GetFormationPet().GetPetSlots().ActivePet(wPetID, 1);
    }

    void Fashion(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (!params.size())
            return;
        UINT16 wItemID = atoi(params[0].c_str());
        pPlayer->GetFighterManager()->GetFashionSlots().AdoptFashion(wItemID);
    }

    void SetFashion(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (!params.size())
            return;
        UINT16 wItemID = atoi(params[0].c_str());
        CItemPtr pItem = pPlayer->GetFighterManager()->GetFashionSlots().GetSlotByID(wItemID);
        if (!pItem)
            return;
        pPlayer->GetFighterManager()->GetFashionSlots().ActiveFashion(pItem->GetInstID());
    }

    void EnterShushanBattle(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser || !pUser->GetPlayer())
            return;

        UINT32 dwType = atoi(params[0].c_str());
        switch(dwType)
        {
            case 1:
                {
                    int iIdx = 0;
                    auto& mapUser = CUserMgr::GetUsrMap();
                    for(auto itr = mapUser.begin(); itr != mapUser.end(); ++itr)
                    {
                        CUserPtr pCurrUser = itr->second;
                        if (pCurrUser && pCurrUser->GetLevel() >= 30)
                        {
                            if (eSSBattle_Suc == ShushanBattle.PlayerEnter(pCurrUser->GetPlayer()))
                                iIdx ++;
                        }
                        if (iIdx >= 100)
                            break;
                    }
                }
                break;
            case 2:
                {
                    SSBPlayerDataPtr pPlayerData = ShushanBattle.FindSSBPlayerData(pUser->GetUserID());
                    if (pPlayerData == NULL)
                        return;
                    INT32 value = atoi(params[1].c_str());
                    if (value > 0)
                    {
                        pPlayerData->_byDomineer += value;
                        pPlayerData->_byAnger += value;
                    }
                    else
                    {
                        if (pPlayerData->_byDomineer < abs(value))
                            pPlayerData->_byDomineer = 0;
                        else
                            pPlayerData->_byDomineer += value;
                        if (pPlayerData->_byAnger < abs(value))
                            pPlayerData->_byAnger = 0;
                        else
                            pPlayerData->_byAnger += value;
                    }
                    ShushanBattle.SendSelfInfo(pUser->GetPlayer(), pPlayerData);
                }
                break;
            default:
                break;
        }
    }

    void GmTest(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!params.size() || !pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        CGameMapPtr pMap = pPlayer->GetMap();
        if (!pMap)
            return;
        string opCode = params[0].c_str();
        if(opCode == "loadcfg" && params.size() >= 2)
        {
            TVecString vecString;
            for(size_t i = 1; i < params.size(); ++i)
                vecString.push_back(params[i]);
            if(!vecString.empty())
                CGameConfig::Instance().ReloadTable(vecString);
        }
        else if(opCode == "tower" && params.size() >= 2)
        {
            UINT32 dwFloorID = atoi(params[1].c_str());
            EDungeonResult eResult;
            CDemonTowerDgnPtr pDemonTowerDgn = CDungeonMgr::CreateDemonTowerDgn(1001,*pPlayer,eResult);
            if(pDemonTowerDgn)
                pDemonTowerDgn->PlayerEnterFloor(*pPlayer,dwFloorID);
        }
        else if(opCode == "towermoney") 
        {
            for(UINT32 i = 18; i < 27; i++)
            {
                char szTmp[1024];
                memset(szTmp,0,sizeof(szTmp));
                sprintf(szTmp,"moneytype:%d,moneyvalue:%d",i,pUser->GetMoney((EMoneyType)i));
                pPlayer->SendPkg(g_ChatProtS.BuildPkg_SystemMsgNotify(eChannelAll,szTmp,eSubNone));
            }
        }
        else if(opCode == "towerprize3" && params.size() >= 2) 
        {
            UINT32 dwFloorID = atoi(params[1].c_str());
            UINT32 dwRetFloorID = 0;
            g_DemonTowerMgr.TakeLayerPrize(*pPlayer,dwFloorID,dwRetFloorID);
        }
        else if(opCode == "toweratk" && params.size() >= 2) 
        {
            UINT32 dwFloorID = atoi(params[1].c_str());
            g_DemonTowerMgr.AttackMonster(*pPlayer,dwFloorID);
        }
        else if(opCode == "setonline" && params.size() >= 2)
        {
            UINT32 dwTime = atoi(params[1].c_str());
            pUser->GetVars().SetVar(NVarDefine::ePlayerOnLineTime,dwTime);
        }
        else if(opCode == "setvar" && params.size() >= 3)
        {
            UINT32 dwVarType = atoi(params[1].c_str());
            UINT32 dwValue = atoi(params[2].c_str());
            pUser->GetVars().SetVar((NVarDefine::EPlayerVar)dwVarType,dwValue);
        }
        else if(opCode == "clearcr")
            pMap->ClearAllMonsters();
        else if(opCode == "createcr" && params.size() >= 2)
        {
            UINT32 dwMonsterID = atoi(params[1].c_str());
            pMap->AddMonster(dwMonsterID);
        }
        else if(opCode == "randgrid")
        {
            CShengLingPtr pShengLing = pPlayer->GetShengLing();
            pShengLing->RandAllGrid();
        }
        else if(opCode =="viewplayer")
        {
            UINT64 qwRoleID = pUser->GetRoleID();
            NViewInfoProt::SRoleData roleData;
            g_ViewInfoProtS.GetRoleInfo(qwRoleID,roleData);
        }
        else if(opCode == "drawdice")
        {
            CShengLingPtr pShengLing = pPlayer->GetShengLing();
            NShengLingProt::SPlayerInfo sInfo;
            UINT64 qwBattleID = 0;
            UINT8 byNum = 0;
            pUser->GetVars().SetVar(NVarDefine::ePlayerVarShengLingBuyLife,9999);
            EShengLingResult eResult;
            eResult = pShengLing->OnDrawDice(byNum,sInfo,false,qwBattleID);
            if(eResult != EShengLingResultSuc) 
                LOG_DBG<<"eResult = " <<eResult;
            else
            {
                LOG_CRI << " byNum=" <<byNum;
                LOG_CRI<<"qwBattleID=" <<qwBattleID;
                LOG_CRI<<"qwRoleID="<<sInfo.qwRoleID<<",byCurLevel="<<sInfo.byCurLevel<<",byCurIndex="<<sInfo.byCurIndex<<",byPreLevel="<<sInfo.byPreLevel<<",byPreIndex="<<sInfo.byPreIndex<<",byUseLife="<<sInfo.byUse<<",byBuy="<<sInfo.byBuy;
            }
        }
        else if(opCode == "entersl")
        {
            CShengLingPtr pShengLing = pPlayer->GetShengLing();
            pUser->GetVars().SetVar(NVarDefine::ePlayerVarShengLingBuyEnter,9999);
            NShengLingProt::SShengLingInfo sInfo;
            pShengLing->OnEnter(sInfo);
                LOG_CRI<<"qwRoleID="<<sInfo.qwRoleID<<",byCurLevel="<<sInfo.byLevel<<",byIndex="<<sInfo.byIndex<<",byDir="<<sInfo.byDir<<",byUseLife="<<sInfo.byUseLife<<",byBuyLife="<<sInfo.byBuyLife<<",byStep="<<sInfo.byStep<<",wScore="<<sInfo.byScore<<",byBit="<<sInfo.byBit<<",wPassword="<<sInfo.wPassword;
            

        }
        else if(opCode == "usecard")
        {
            CShengLingPtr pShengLing = pPlayer->GetShengLing();
            NShengLingProt::SPlayerInfo sInfo;
            NShengLingProt::SCard rCard;
            UINT64 qwBattleID = 0;
            ECardType eType =(ECardType)atoi(params[1].c_str());
            pShengLing->OnUseCard(eType,1,rCard,sInfo,qwBattleID);
        }
        else if(opCode == "onbuy")
        {
            CShengLingPtr pShengLing = pPlayer->GetShengLing();
            EBuyType eType =(EBuyType)atoi(params[1].c_str());
            UINT8 byBuy = 0;
            UINT8 byUse = 0;
            UINT8 byBuyToday = 0;
            pShengLing->OnBuy(eType,1,byBuy,byUse,byBuyToday);
        }
        else if(opCode == "sysmsg" && params.size() >= 2)
        {
            UINT32 wMsgID  = atoi(params[1].c_str());
            pPlayer->SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID));
        }
        else if(opCode == "openhorse")
        {
            CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();
            if(pHorseMgr)
                pHorseMgr->Open();
        }
        else if(opCode == "upgradehorse" && params.size() >= 2)
        {
            UINT32 dwHorseID  = atoi(params[1].c_str());
            CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();
            if(pHorseMgr)
                pHorseMgr->UpgradeHorse(dwHorseID);
        }
        else if(opCode == "lottery")
        {
            UINT16 wIndex;
            g_Lottery.Draw(*pUser,wIndex);
            LOG_CRI<<"wIndex = " << wIndex;
        }else if(opCode == "getlogininfo")
        {
            UINT16 wDays;
            UINT16 wPkgInfo;
            CLoginPkgMgrPtr pLoginPkgMgr = pPlayer->GetLoginPkgMgr();
            if(pLoginPkgMgr)
                pLoginPkgMgr->GetPkgInfo(*pUser,wDays,wPkgInfo);
            LOG_CRI << wPkgInfo << " | " << wDays;
        }
        else if(opCode == "activehorse" && params.size() >= 2)
        {
            UINT32 dwHorseID  = atoi(params[1].c_str());
            CHorseMgrPtr pHorseMgr = pPlayer->GetHorseMgr();
            if(pHorseMgr)
                pHorseMgr->ActiveHorse(dwHorseID);
        }
        else if(opCode == "lshanreg") 
        {
            g_ZhanQiMgr.OnPlayerReg(pPlayer);
        }
        else if(opCode == "lshanmove"&& params.size() >= 2) 
        {
            UINT32 dwPos  = atoi(params[1].c_str()); 
            UINT32 dwCd = 0;
            g_ZhanQiMgr.OnPlayerMove(*pPlayer,dwPos,dwCd);
        }
        else if(opCode == "lshanmath")
        {
            shared_func<CLingShanProtS::SGetMatchInfoAck> fnAck(new CLingShanProtS::SGetMatchInfoAck(g_LingShanProtS,0,0));
            g_ZhanQiMgr.OnGetMatchInfo(*pPlayer,fnAck);
        }
        else if(opCode == "lshanself")
        {
            shared_func<CLingShanProtSvr::SGetMathSelInfoAck> fnAck(new CLingShanProtSvr::SGetMathSelInfoAck(g_LingShanProtS,0,0));
            g_ZhanQiMgr.OnGetMathSelInfo(*pPlayer,fnAck);
        }
        else if(opCode == "lshanself"&& params.size() >= 2)
        {
            UINT32 dwModelID  = atoi(params[1].c_str());
            g_ZhanQiMgr.OnChangeModel(*pPlayer,dwModelID,dwModelID);
        }
        else if(opCode == "hasbuffer" && params.size() >= 2)
        {
            UINT32 dwBuffID  = atoi(params[1].c_str());
            bool bRet = pPlayer->HasBuff(dwBuffID);

            char szTmp[1024];
            memset(szTmp,0,sizeof(szTmp));
            if(bRet)
                sprintf(szTmp,"dwBuffID:%d exists!",dwBuffID);
            else
                sprintf(szTmp,"dwBuffID:%d not exists!",dwBuffID);

            pPlayer->SendPkg(g_ChatProtS.BuildPkg_SystemMsgNotify(eChannelAll,szTmp,eSubNone));

        }

        else if(opCode == "etstr" && params.size() >= 3)
        {
            UINT64 qwInstanceID = 0;
            if(params.size() > 0)
            {
                sscanf(params[1].c_str(),"%" I64_FMT "d", &qwInstanceID);
            }

            UINT32 eType = atoi(params[2].c_str());
            CEquipTrumpPtr pEquipTrump = pPlayer->GetFighterManager()->GetEquipTrumpByInstID(qwInstanceID);
            if(pEquipTrump)
            {


     shared_func<CEquipTrumpProtSvr::SIntensifyAck> fnAck(new CEquipTrumpProtSvr::SIntensifyAck(g_EquipTrumpProtS, pUser->GetUserID(), 0));
                pEquipTrump->OnIntensify(*pUser,(ETIntensifyType)eType,fnAck);
            }
            else
            {
                LOG_CRI<<"Error qwInstanceID:"<<qwInstanceID;
            }
        }
        else if(opCode == "etqstr" && params.size() >= 3)
        {
            UINT64 qwInstanceID = 0;
            if(params.size() > 0)
            {
                sscanf(params[1].c_str(),"%" I64_FMT "d", &qwInstanceID);
            }

            UINT32 eType = atoi(params[2].c_str());
            CEquipTrumpPtr pEquipTrump = pPlayer->GetFighterManager()->GetEquipTrumpByInstID(qwInstanceID);
            if(pEquipTrump)
            {


     shared_func<CEquipTrumpProtSvr::SIntensifyOneKeyAck> fnAck(new CEquipTrumpProtSvr::SIntensifyOneKeyAck(g_EquipTrumpProtS, pUser->GetUserID(), 0));
                pEquipTrump->OnIntensifyOneKey(*pUser,(ETIntensifyType)eType,fnAck);
            }
            else
            {
                LOG_CRI<<"Error qwInstanceID:"<<qwInstanceID;
            }
        }
 
        else if(opCode == "etxilian" && params.size() >= 3)
        {
            UINT64 qwInstanceID = 0;
            if(params.size() > 0)
            {
                sscanf(params[1].c_str(),"%" I64_FMT "d", &qwInstanceID);
            }

            UINT32 dwLock = atoi(params[2].c_str());
            CEquipTrumpPtr pEquipTrump = pPlayer->GetFighterManager()->GetEquipTrumpByInstID(qwInstanceID);
            if(pEquipTrump)
            {
                pEquipTrump->OnShuffleResult(*pUser,dwLock);
            }
            else
            {
                LOG_CRI<<"Error qwInstanceID:"<<qwInstanceID;
            }

        }
        else if(opCode == "chestopen")
        {
            g_GodChest.GMOpen();
        }
        else if(opCode == "chestreflush")
        {
            g_GodChest.Reflush();
        }
        else if(opCode == "chestclear")
        {
            g_GodChest.ClearChest();
        }
        else if(opCode == "chestclose")
        {
            g_GodChest.OnEnd();
        }
        else if(opCode == "bossopen" && params.size() >= 2)
        {
            UINT32 dwBossID = atoi(params[1].c_str());
            UINT32 dwProcessTime = 33600;
            if(params.size() >= 3)
                dwProcessTime = atoi(params[2].c_str());
            CWorldBossMgr::Instance().GMOpenBoss(dwBossID,dwProcessTime);
        }
        else if(opCode == "worldbosshp" && params.size() >= 2)
        {
            UINT32 dwHp  = atoi(params[1].c_str());
            CWorldBossMgr::Instance().ChangeBossHp(dwHp);
        }
        else if(opCode == "aprize" && params.size() >= 2)
        {
            UINT32 wAchievementID  = atoi(params[1].c_str());
            CAchievementMgrPtr pAchievementMg =  pPlayer->GetAchievementMgr();
            if(pAchievementMg)
                pAchievementMg->OnTakePrize(wAchievementID);

        }
        else if(opCode == "rebeginboss")
            CWorldBossMgr::Instance().OnReBegin();
        else if(opCode == "openworldboss")
            CWorldBossMgr::Instance().OnBegin();
        else if(opCode == "endworldboss")
            CWorldBossMgr::Instance().OnEnd();
        else if(opCode == "enterworldboss")
            CWorldBossMgr::Instance().OnEnterMap(*pPlayer);
        else if(opCode == "leaveworldboss")
            CWorldBossMgr::Instance().OnLeaveMap(*pPlayer);
        else if(opCode == "bossinfo")
            CWorldBossMgr::Instance().PrintBossInfo(*pPlayer);
        else if(opCode == "bosstime" && params.size() >= 2)
        {
            UINT32 dwSec  = atoi(params[1].c_str());
            CWorldBossMgr::Instance().ChangeBossFactor(dwSec);
        }
        else if(opCode == "attackdboss")
            CWorldBossMgr::Instance().AttackBoss(*pPlayer);
        else if(opCode == "openlanghuanbless")
            CLangHuanBlessMgr::Instance().OnBegin();
        else if(opCode == "endlanghuanbless")
            CLangHuanBlessMgr::Instance().OnEnd();
        else if(opCode == "enterlanghuanbless")
            CLangHuanBlessMgr::Instance().OnEnterMap(*pPlayer);
        else if(opCode == "leavelanghuanbless")
            CLangHuanBlessMgr::Instance().OnLeaveMap(*pPlayer);
        else if(opCode == "useskill" && params.size() >= 3)
        {
            UINT64 qwPlayerID = atof(params[1].c_str());
            UINT32 dwSkillID = atoi(params[2].c_str());
            CLangHuanBlessMgr::Instance().OnUseSkill(*pPlayer,qwPlayerID,static_cast<ELHBSkillType>(dwSkillID));
        }
        else if(opCode == "takeprize" && params.size() >= 3)
        {
            UINT16 wID = atoi(params[1].c_str());
            UINT8 byIndex = atoi(params[2].c_str());
            g_WondActMgr.TakePrize(*pPlayer,wID,byIndex);
        }
        else if(opCode == "fcmopen" && params.size() >= 2)
            pUser->SetIndulge( atoi(params[1].c_str()) ? true: false);
        else if(opCode == "fcmtime")
        {
            UINT32 dwTime = 3600;
            if (params.size() >= 2)
                dwTime  = atoi(params[1].c_str());
            pUser->GMAddIndulgeTime(dwTime);
        }
        else if(opCode == "openact" && params.size() >= 2)
        {
            UINT32 dwActID  = atoi(params[1].c_str());
            g_DayActivityMgr.OpenActivity(dwActID);
        }
        else if(opCode == "actiontime" && params.size() >= 2)
        {
            UINT32 dwtime = atoi(params[1].c_str());
            SParamConfig::wEnergyNormalRegainTime = dwtime;
        }
        else if(opCode == "actionbuy")
        {
            CEnergyMgrPtr pMgr = pPlayer->GetEnergyMgr();
            pMgr->BuyAction();
            LOG_INF<<"COUNT:"<<pMgr->GetBuyActionCount()<<" Price:"<<pMgr->GetBuyPrice();
        }
        else if(opCode == "actionset" && params.size() >= 2)
        {
            UINT32 dwValue  = atoi(params[1].c_str());
            pUser->AddMoney(EMONEY_ACTION,dwValue,NLogDataDefine::ItemFrom_GM);
        }
        else if(opCode == "exchange" && params.size() >= 2)
        {
            UINT32 dwID = atoi(params[1].c_str());
            CExchangeShopMgrPtr pMgr = pPlayer->GetExchangeShopMgr();
            if(pMgr) 
            {
                UINT32 dwRet = pMgr->ExchangeItem(dwID,1,[](UINT32 dwRet){});
                LOG_INF<<"exchange RET:"<<dwRet;
            }
        }
        else if(opCode == "sweep" && params.size() >= 3)
        {
            UINT32 wDgnID  = atoi(params[1].c_str());
            UINT32 wCount  = atoi(params[2].c_str());
            UINT32 dwSweepEndTime;
            pPlayer->GetActionManager().AddSweePing(wDgnID,wCount,dwSweepEndTime);
        }
        else if(opCode == "feedbackget" && params.size() >= 1)
        {
            TVecFeedBackInfo vec1;
            TVecSBuyDiscountInfo vec2;
            g_FeedBackMgr.OnGetFeedBackList(*pPlayer,vec1,vec2);
        }
        else if(opCode == "feedbackbuy" && params.size() >= 3)
        {
            UINT32 wType  = atoi(params[1].c_str());
            UINT32 wCount  = atoi(params[2].c_str());
            g_FeedBackMgr.OnBuyDisCountItem(*pPlayer,wType,wCount);
        }
        else if(opCode == "feedbackprize" && params.size() >= 3)
        {
            UINT32 wID  = atoi(params[1].c_str());
            g_FeedBackMgr.OnTakeFeedBackPrize(*pPlayer,wID);
        }
        if(opCode == "event" && params.size() >= 2)
        {
            UINT32 dwEventID  = atoi(params[1].c_str());
            TVecINT32 vecParam;
            for(UINT32 i = 2; i < params.size(); i ++)
                vecParam.push_back(atoi(params[i].c_str()));
            pPlayer->GetEventMgr()->OnEvent((EventType)dwEventID,vecParam);
        }
        else if(opCode == "eventprint")
            pPlayer->GetEventMgr()->PrintEventSize();
        else if(opCode == "eventclear") 
            pPlayer->GetEventMgr()->ClearEventByActClassID((EActClass)1);
        else if(opCode == "collectionap" && params.size() >= 2)
        {
            UINT32 dwAP = atoi(params[1].c_str());
            pUser->AddMoney(EMONEY_COLLECTAP,dwAP,NLogDataDefine::ItemFrom_GM);
            CCollectionMgrPtr pChieve = pPlayer->GetCollectionMgr();
            if(pChieve)
                pChieve->OnCheckLevel();
        }
        else if(opCode == "achievementap" && params.size() >= 2)
        {
            UINT32 dwAP  = atoi(params[1].c_str());
            pUser->AddMoney(EMONEY_ACHIEVEMENTAP,dwAP,NLogDataDefine::ItemFrom_GM);
            CAchievementMgrPtr pChieve = pPlayer->GetAchievementMgr();
            if(pChieve)
                pChieve->OnCheckLevel();
        }
        else if(opCode == "udptest")
        {
            TVecString vecRegist;
            g_Game2CenterLog.Send_LogRegister(pUser->GetUserID(), vecRegist);

        }
        else if(opCode == "yd" && params.size() >= 3)
        {
            UINT8 eBagType = atoi(params[1].c_str());
            UINT16 dLevel = atoi(params[2].c_str());
            CYelloDiamondMgr::Instance().GainYDBag(*pUser,static_cast<EBagType>(eBagType),dLevel);
        }
        else if (opCode == "getyd")
        {
            SYDInfo info;
            CYelloDiamondMgr::Instance().GetYDInfo(*pUser,info);
        }
        else if (opCode == "shopitem")
        {
            CShopItemMgrPtr pTmp = pPlayer->GetShopItemMgr();
            if(pTmp)
            {
                TVecBuyItemInfo vecBuyItemInfo;
                pTmp->GetShopItemList(vecBuyItemInfo);
            }
        }
        else if (opCode == "shopitemclear")
        {
            CShopItemMgrPtr pTmp = pPlayer->GetShopItemMgr();
            if(pTmp)
            {
                TVecBuyItemInfo vecBuyItemInfo;
                pTmp->ClearItemCount();
            }
        }
        else if(opCode == "7dtlist")
        {
            TVecDayTargetTask VecDayTargetTask;
            pPlayer->GetDayTargetMgr()->GetTaskList(VecDayTargetTask);
        }
        else if(opCode == "7dtprize" && params.size() >= 2)
        {
            UINT32 wTaskID = atoi(params[1].c_str());
            pPlayer->GetDayTargetMgr()->TakePrize(wTaskID);
        }
        else if(opCode == "atkba" && params.size() >= 2)
        {
            UINT32 dwLevelID = atoi(params[1].c_str());
            CBattleArrayMgrPtr pMgr = pPlayer->GetBattleArrayMgr();
            if(pMgr)
                pMgr->OnAttackBattleArray(dwLevelID);
        }
        else if(opCode == "swpba" && params.size() >= 2)
        {
            UINT32 dwLevelID = atoi(params[1].c_str());
            CBattleArrayMgrPtr pMgr = pPlayer->GetBattleArrayMgr();
            if(pMgr)
                pMgr->OnSweepBattleArray(dwLevelID);
        }
        else if(opCode == "clearba")
        {
            CAutoStoreMgrPtr pMgr = pPlayer->GetAutoStoreMgr();
            if(pMgr)
                pMgr->OnMidNight();
        }
        else if(opCode == "btmeet" && params.size() >= 2)
        {
            UINT32 dwBeautyID = atoi(params[1].c_str());
            CBeautyMgrPtr pMgr = pPlayer->GetBeautyMgr();
            if(pMgr)
                pMgr->OnMeetBeauty(dwBeautyID);
        }
        else if(opCode == "btchat" && params.size() >= 2)
        {
            UINT32 dwBeautyID = atoi(params[1].c_str());
            CBeautyMgrPtr pMgr = pPlayer->GetBeautyMgr();
            if(pMgr)
                pMgr->OnChatBeauty(dwBeautyID);
        }
        else if(opCode == "btsendprize" && params.size() >= 3)
        {
            UINT32 dwBeautyID = atoi(params[1].c_str());
            UINT32 dwItemID   = atoi(params[2].c_str());
            CBeautyMgrPtr pMgr = pPlayer->GetBeautyMgr();
            if(pMgr)
            {
                NItemProt::TVecItemCount vecItemCount;
                SItemCount oItemCount;
                oItemCount.wItemID = dwItemID;
                oItemCount.wCount = 1;
                vecItemCount.push_back(oItemCount);
                pMgr->OnSendPrizeBeauty(dwBeautyID, vecItemCount);
            }
        }
        else if(opCode == "btrandom" && params.size() >= 2)
        {
            UINT32 eLotteryBeautyType = atoi(params[1].c_str());
            CBeautyMgrPtr pMgr = pPlayer->GetBeautyMgr();
            if(pMgr)
            {
                NItemProt::TVecItemGenInfo vecItemGenInfo;
                pMgr->OnLotteryBeauty((ELotteryBeautyType)eLotteryBeautyType,vecItemGenInfo);
            }
        }
        
        else if(opCode == "btfreecnt" && params.size() >= 2)
        {
            UINT32 dwCnt  = atoi(params[1].c_str());
            CBeautyMgrPtr pMgr = pPlayer->GetBeautyMgr();
            if(pMgr)
            {
                pMgr->SetFreeCnt(dwCnt);
                pPlayer->SendPkg(g_BeautyS.BuildPkg_LotteryFreeCntNotify(dwCnt));
            }
        }

        else if(opCode == "btfight" && params.size() >= 2)
        {
            UINT32 dwBeautyID = atoi(params[1].c_str());
            CBeautyMgrPtr pMgr = pPlayer->GetBeautyMgr();
            if(pMgr)
                pMgr->OnBeautyFight(dwBeautyID);
        }
        else if(opCode == "btprint")
        {
            CBeautyMgrPtr pMgr = pPlayer->GetBeautyMgr();
            if(pMgr)
            {
                const TVecFloat& vecFloat = pMgr->GetAttrVec();
                for(UINT32 i = 0; i < vecFloat.size(); i++)
                {
                    if(vecFloat[i]>0)
                    {
                        char szTmp[1024];
                        memset(szTmp,0,sizeof(szTmp));
                        sprintf(szTmp,"attrid:%d,value:%f",i,vecFloat[i]);
                        pPlayer->SendPkg(g_ChatProtS.BuildPkg_SystemMsgNotify(eChannelAll,szTmp,eSubNone));
                        LOG_CRI<<"attrid:"<<i<<"|"<<vecFloat[i];
                    }
                }
            }
        }
    }

    void DoSit(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        UINT64 qwRoleId = 0;
        if(params.size() > 0)
        {
            sscanf(params[0].c_str(),"%" I64_FMT "d", &qwRoleId);
        }
        pUser->GetPlayer()->GetActionManager().DoSitting(qwRoleId);

    }

    void Loot(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        if(params.size() < 1)
            return ;
        UINT32 dwID = atoi(params[0].c_str());

        TVecResource vecRes;
        std::vector<SItemGenInfo> vecItems;

        LOOT.Roll(dwID, vecItems, vecRes);

        CPack& oPack = pUser->GetPack();
        if(!oPack.CanAddItem(vecItems))
        {
            UINT64 qwUsrID = pUser->GetUserID();
            g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUsrID, 1 , eMsgPackFullErr);
            return;
        }

        oPack.AddItem(vecItems, NLogDataDefine::ItemFrom_GM, true);
        oPack.AddResource(*pUser, vecRes,NLogDataDefine::ItemFrom_GM, NULL, true); // XXX: From where?
    }

    void BattlePoint(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        CHeroFighterPtr pMainFighter = pPlayer->GetMainFighter();
        CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
        if (!pMainFighter || !pFighterManager)
            return;
        ostringstream strInfo;
        string opCode = params[0].c_str();
        char chSplit = '\n';
        if (opCode == "1")
        {
                strInfo << "玩家总战斗力: ";
                strInfo << pPlayer->GetBattlePoint() << chSplit;
        }
        else if (opCode == "2")
        {
                strInfo << "玩家总战斗力: " << pPlayer->GetBattlePoint()                        << chSplit;
                strInfo << "散仙战力: "     << pFighterManager->CalcHeroFighterBattlePoint()    << chSplit;
                strInfo << "仙女战力："     << pFighterManager->GetBeautyBattlePoint()          << chSplit;
                strInfo << "法宝属性战力：" << pFighterManager->GetTrumpAttrBattlePoint()       << chSplit;
                strInfo << "法宝技能战力：" << pFighterManager->GetTrumpSkillBattlePoint()      << chSplit;
                strInfo << "坐骑战力："     << pFighterManager->GetHorseBattlePoint()           << chSplit;
                strInfo << "渡劫战力："     << pFighterManager->GetDujieBattlePoint()           << chSplit;
                strInfo << "心法战力："     << pFighterManager->GetXinfaBattlePoint()           << chSplit;
                strInfo << "帮派战力："     << pFighterManager->GetGuildBattlePoint()           << chSplit;
                strInfo << "BUFF战力："     << pFighterManager->GetBufferBattlePoint()          << chSplit;
        }
        else if (opCode == "3")
        {
            CFormation& rFormation = pFighterManager->GetFormation();
            TVecLineup vecLineup;
            rFormation.GetLineup(vecLineup);
            for (size_t i = 0; i < vecLineup.size(); ++i)
            {
                CFighterPtr pFighter = vecLineup[i].pFighter;
                if (!pFighter)
                    continue;
                strInfo << "出战散仙名：" << pFighter->GetName() << chSplit;
                strInfo << GetAddAttrStr(pFighter->GetAttrVec()) << chSplit;
                TVecUINT32 vecSkillsID;
                pFighter->GetAllSkillsID(vecSkillsID);
                if (pFighter->IsHeroFighter())
                {
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if (pHeroFighter)
                    {
                        TVecFloat vecAttr;
                        VECATTR_RESET(vecAttr);
                        strInfo << "装备法宝：" << chSplit;
                        CEquipTrumpSlot& rSlot = pHeroFighter->GetEquipTrumpSlot();
                        rSlot.GetAddAttr(vecAttr);
                        strInfo << GetAddAttrStr(vecAttr) << chSplit;
                    }
                }
                for (auto& rID : vecSkillsID)
                {
                    SSkillPtr pSkill = CSkillMgr::Instance().GetSkill(SKILL_ID(rID));
                    if (!pSkill)
                        continue;
                    UINT32 dwBattlePoint = 0;
                    SSkillEfPtr pSkillEffect = CSkillMgr::Instance().GetSkillEf(rID);
                    if (pSkillEffect)
                        dwBattlePoint = pSkillEffect->_dwBattlePoint;
                    strInfo << pSkill->_strName << "(" << pSkill->_dwID << "): " << dwBattlePoint << chSplit;
                }
            }
        }
        else if (opCode == "4")
        {
            TVecFloat vecAttr;
            VECATTR_RESET(vecAttr);
            pFighterManager->GetHeroAndPlayerAddAttr(vecAttr);
            strInfo << GetAddAttrStr(vecAttr) << chSplit;
            UINT32 dwBattlePoint = BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
            strInfo << "增加到每一个出战将领的战斗力: " << dwBattlePoint;
        }
        else if (opCode == "5" || opCode == "et")
        {
            CFormation& rFormation = pFighterManager->GetFormation();
            TVecLineup vecLineup;
            rFormation.GetLineup(vecLineup);
            for (size_t i = 0; i < vecLineup.size(); ++i)
            {
                CFighterPtr pFighter = vecLineup[i].pFighter;
                if (!pFighter)
                    continue;
                strInfo << "出战散仙名：" << pFighter->GetName() << chSplit;
                if (pFighter->IsHeroFighter())
                {
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if (pHeroFighter)
                    {
                        TVecFloat vecAttr;
                        VECATTR_RESET(vecAttr);
                        strInfo << "装备法宝：" << chSplit;
                        CEquipTrumpSlot& rSlot = pHeroFighter->GetEquipTrumpSlot();
                        rSlot.GetAddAttr(vecAttr);
                        strInfo << GetAddAttrStr(vecAttr) << chSplit;

                        TVecUINT32 vecSkillsID;
                        rSlot.GetAllSkills(vecSkillsID);
                        for (auto& rID : vecSkillsID)
                        {
                            SSkillPtr pSkill = CSkillMgr::Instance().GetSkill(SKILL_ID(rID));
                            if (!pSkill)
                                continue;
                            UINT32 dwBattlePoint = 0;
                            SSkillEfPtr pSkillEffect = CSkillMgr::Instance().GetSkillEf(rID);
                            if (pSkillEffect)
                                dwBattlePoint = pSkillEffect->_dwBattlePoint;
                            strInfo << pSkill->_strName << "(" << pSkill->_dwID << "): " << dwBattlePoint << chSplit;
                        }
                    }
                }
            }

        }
        else if (opCode == "6" || opCode == "et2")
        {
            CFormation& rFormation = pFighterManager->GetFormation();
            TVecLineup vecLineup;
            rFormation.GetLineup(vecLineup);
            for (size_t i = 0; i < vecLineup.size(); ++i)
            {
                CFighterPtr pFighter = vecLineup[i].pFighter;
                if (!pFighter)
                    continue;
                strInfo << "出战散仙名：" << pFighter->GetName() << chSplit;
                if (pFighter->IsHeroFighter())
                {
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if (pHeroFighter)
                    {
                        CEquipTrumpSlot& rSlot = pHeroFighter->GetEquipTrumpSlot();
                        for (UINT8 byIndex = 0; byIndex < EQUIP_TRUMP_SLOTS; ++byIndex)
                        {
                            if (!rSlot.HasObj(byIndex))
                                continue;
                            CItemPtr pItem = rSlot.Get(byIndex);
                            if (!pItem)
                                continue;
                            if (!pItem->IsEquipTrumpItem())
                                continue;
                            CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
                            if (!pEquipTrump)
                                continue;
                            strInfo << pEquipTrump->GetItemName() << ":" << chSplit;
                            TVecFloat vecAttr;
                            VECATTR_RESET(vecAttr);
                            pEquipTrump->GetAttr(vecAttr);
                            strInfo << GetAddAttrStr(vecAttr) << chSplit;
                            TVecUINT32 vecSkillsID;
                            UINT32 dwSkillID = pEquipTrump->GetSkillID();
                            if (!dwSkillID)
                                continue;
                            SSkillPtr pSkill = CSkillMgr::Instance().GetSkill(SKILL_ID(dwSkillID));
                            if (!pSkill)
                                continue;
                            UINT32 dwBattlePoint = 0;
                            SSkillEfPtr pSkillEffect = CSkillMgr::Instance().GetSkillEf(dwSkillID);
                            if (pSkillEffect)
                                dwBattlePoint = pSkillEffect->_dwBattlePoint;
                            strInfo << pSkill->_strName << "(" << pSkill->_dwID << "): " << dwBattlePoint << chSplit;
                        }
                    }
                }
            }

        }
        ChatSysLog(strInfo.str(), *pUser, chSplit);
    }

    void GetPlayerHP(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        ostringstream strInfo;
        UINT32 dwType = atoi(params[0].c_str());
        switch(dwType)
        {
            case 1:
                {
                    strInfo << "玩家总血量上限: ";
                    CFighterPtr pFighter = pPlayer->GetMainFighter();
                    strInfo << pPlayer->GetMaxHP2() << "\n";
                    strInfo << "玩家当前总血量: ";
                    strInfo << pPlayer->GetCurrHP() << "\n";
                }
                break;
            case 2:
                {
                    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
                    if (!pFighterManager)
                        return;
                    CFormation& rFormation = pFighterManager->GetFormation();
                    TVecLineup vecLineup;
                    rFormation.GetLineup(vecLineup);
                    for (size_t i = 0; i < vecLineup.size(); ++i)
                    {
                        CFighterPtr pFighter = vecLineup[i].pFighter;
                        if (!pFighter)
                            continue;
                        strInfo << "散仙名字: " << pFighter->GetName() << " 散仙ID:" << pFighter->GetID();
                        strInfo << "血量上限: " << pFighter->GetHPMax() << " 当前血量: " << pFighter->GetHP() << "\n";
                    }
                }
                break;
            default:
                return;
        }
        ChatSysLog(strInfo.str(), *pUser, '\n');
        LOG_CRI << strInfo.str();
    }

    void GuildBattle(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        ostringstream strInfo;
        if (params.size() >= 1)
        {
            string opCode = params[0].c_str();
            if(opCode == "start")
            {
                CGuildBattleMgr::Instance().ForceEndBattle();
                CGuildBattleConfigMgr::Instance().ForceStart();
            }
            if (opCode == "info")   
                strInfo << CGuildBattleMgr::Instance().GetDumpInfo(pPlayer);
            if (opCode == "debug")
            {
                strInfo << "相关时间：\n";
                strInfo << "2.布阵时间: "       << CGuildBattleConfigMgr::Instance().GetDebugPrepareTime()      << "\n";
                strInfo << "3.战役时间: "       << CGuildBattleConfigMgr::Instance().GetDebugCampaignTime()     << "\n";
                strInfo << "4.战役场数: "       << CGuildBattleConfigMgr::Instance().GetDebugCampaignCount()    << "\n";
            }
            if (opCode == "set")
            {
                if (params.size() >= 3)
                {
                    UINT32 dwType = atoi(params[1].c_str());
                    switch(dwType)
                    {
                        case 2:
                            CGuildBattleConfigMgr::Instance().SetDebugPrepareTime(atoi(params[2].c_str()));
                            break;
                        case 3:
                            CGuildBattleConfigMgr::Instance().SetDebugCampaignTime(atoi(params[2].c_str()));
                            break;
                        case 4:
                            CGuildBattleConfigMgr::Instance().SetDebugCampaignCount(atoi(params[2].c_str()));
                            break;
                    }
                }
                strInfo << "2.布阵时间: "       << CGuildBattleConfigMgr::Instance().GetDebugPrepareTime()      << "\n";
                strInfo << "3.战役时间: "       << CGuildBattleConfigMgr::Instance().GetDebugCampaignTime()     << "\n";
                strInfo << "4.战役场数: "       << CGuildBattleConfigMgr::Instance().GetDebugCampaignCount()    << "\n";
            }
            if (opCode == "fast")
            {
                UINT32 dwCount = 1;
                if (params.size() >= 2)
                    dwCount = atoi(params[1].c_str());
                CGuildBattleConfigMgr::Instance().SetMinUserCount(dwCount);
                strInfo << "当前最少人数：" << CGuildBattleConfigMgr::Instance().GetMinUserCount() << ".";
            }
            if (opCode == "end")
                CGuildBattleMgr::Instance().OnEnd();
        }
        ChatSysLog(strInfo.str(), *pUser, '\n');
        LOG_DBG << strInfo.str();
    }

    void NewGuildBattle(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;

        if (!params.size())
            return;

        ostringstream strInfo;

        string opCode = params[0].c_str();
        if(opCode == "start")
            NNewGuildBattle::CBattleMgr::Instance().GMOpen();
        if (opCode == "set" && params.size() >= 3)
        {
            UINT32 dwType = atoi(params[1].c_str());
            UINT32 dwValue = atoi(params[2].c_str());
            switch(dwType)
            {
                case 1:
                    SParamConfig::wLingMountainWarReadyTime = dwValue;
                    break;
                case 2:
                    SParamConfig::wLingMountainReliveTime = dwValue;
                    break;
                case 3:
                    NNewGuildBattle::CConfigMgr::Instance().SetCampaignTime(dwValue);
                    break;
                case 4:
                    {
                        NNewGuildBattle::CPlayerPtr pNGBPlayer = NNewGuildBattle::CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
                        if (pNGBPlayer && pNGBPlayer->GetMountain() != NNewGuildBattleProt::eNGBMNone)
                            NNewGuildBattle::CBattleMgr::Instance().SetGateHP(pNGBPlayer->GetMountain(), dwValue);
                    }
                    break;
                case 5:
                    NNewGuildBattle::CConfigMgr::Instance().SetResCalcTime(dwValue);
                    break;
                case 6: 
                    NNewGuildBattle::CConfigMgr::Instance().SetDebugStartTime(dwValue);
                    break;
                default:
                    break;
            }
        }
        if (opCode == "info" || opCode == "set")
        {
            strInfo << "相关参数：\n";
            strInfo << "1.战斗准备时间: " << SParamConfig::wLingMountainWarReadyTime << "\n";
            strInfo << "2.战斗复活时间: " << SParamConfig::wLingMountainReliveTime << "\n";
            strInfo << "3.战斗持续时间: " << NNewGuildBattle::CConfigMgr::Instance().GetCampaignTime() << "\n";
            NNewGuildBattle::CPlayerPtr pNGBPlayer = NNewGuildBattle::CBattleMgr::Instance().GetPlayer(pPlayer->GetRoleID());
            if (pNGBPlayer && pNGBPlayer->GetMountain() != NNewGuildBattleProt::eNGBMNone)
                strInfo << "4.当前城门血量: " << NNewGuildBattle::CBattleMgr::Instance().GetGateHP(pNGBPlayer->GetMountain()) << "\n";
            strInfo << "5.战斗资源增长时间: " << NNewGuildBattle::CConfigMgr::Instance().GetResCalcTime() << "\n";
            strInfo << "6.GM开启准备时间: "   << NNewGuildBattle::CConfigMgr::Instance().GetDebugStartTime() << "\n";
        }
        if (opCode == "cap" )
        {
            if (params.size() >= 2)
            {
                UINT8 byType = atoi(params[1].c_str());
                if (byType > NNewGuildBattleProt::ENGBMountain::eNGBMNone && byType < NNewGuildBattleProt::ENGBMountain::eNGBMMax)
                {
                    NNewGuildBattleProt::ENGBMountain eMountainType = static_cast<ENGBMountain>(byType);
                    g_Game2CenterCommC.Send_GetGuildID(pUser->GetUserID(),
                            [pUser, eMountainType](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
                            {
                                ostringstream strInfo;
                                bool bRet = false;
                                if (byRet == 0 && qwGuildID)
                                {
                                    bRet = NNewGuildBattle::CBattleMgr::Instance().GMCapture(eMountainType, qwGuildID, strGuildName, byGuildLvl);
                                    strInfo << strGuildName << " 占领 (" << static_cast<UINT32>(eMountainType) << "):" << (bRet ? "成功" : "失败") << ".";
                                }
                                ChatSysLog(strInfo.str(), *pUser, '\n');
                                LOG_DBG << strInfo.str();
                            });
                }
            }
        }
        if (opCode == "end" )
            NNewGuildBattle::CBattleMgr::Instance().OnEnd();
        ChatSysLog(strInfo.str(), *pUser, '\n');
        LOG_DBG << strInfo.str();
    }

    void BeastSoul(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
        if (!pFighterManager)
            return;
        ostringstream strInfo;
        CBeastSoul& rBeastSoul =  pFighterManager->GetFormationPet().GetBeastSoul();
        if (params.size() >= 1)
        {
            UINT8 byType = atoi(params[0].c_str());
            if (byType > eBeastSoulNone && byType < eBeastSoulMax)
            {
                EBeastSoulType eType = static_cast<EBeastSoulType>(byType);
                TVecBeastSoulItem vecItems;
                EBeastSoulResult eResult = rBeastSoul.UpgradeBeastSoul(eType, vecItems);
                strInfo << "Upgrade " << static_cast<UINT32>(eType) << ": " << static_cast<UINT32>(eResult);
            }
        }
        strInfo << "兽魂信息: \n";
        TVecBeastSoulInfo vecBeastSoulInfo;
        rBeastSoul.GetAllInfo(vecBeastSoulInfo);
        for (auto& rInfo : vecBeastSoulInfo)
        {
            strInfo << static_cast<UINT32>(rInfo.eType) << ", "
                << static_cast<UINT32>(rInfo.byRank) << ", "
                << static_cast<UINT32>(rInfo.byLevel) << ". \n";
        }

        ChatSysLog(strInfo.str(), *pUser, '\n');
        LOG_DBG << strInfo.str();
    }

    void Discount(const char* cmd, const Tokenizer& params, void* p)
    {
        for (int i = 0; i < 3; ++ i)
        {
            NMallProt::SDiscount oDiscount;
            oDiscount.byPos = i;
            oDiscount.byLimitType  = 2-i;
            oDiscount.dwLimitValue = i*100+99;
            oDiscount.wLimitCount  = (2-i)*100+99;
            oDiscount.dwBeginTime  = time(NULL);
            oDiscount.dwEndTime    = time(NULL)+(i+1)*3600;
            int j = CRandom::RandInt(1, 4);
            for (; j > 0; -- j)
            {
                NMallProt::SDiscountItem oDiscountItem;
                oDiscountItem.wItemID = 1000+j;
                oDiscountItem.wOriginalPrice = 200*j;
                oDiscountItem.wDiscountPrice = 200*j/10;
                oDiscount.vecDisItems.push_back(oDiscountItem);
            }
            CMall::Instance().ClearMallDiscount(oDiscount.byPos);
            CMall::Instance().AddDiscountFromBS(oDiscount);
        }
        CMall::Instance().UpdateDiscountToDB();
    }

    void OpenIcon(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        UINT16 wIconID = 0;
        ostringstream strInfo;
        if (params.size() < 1)
            return;
        wIconID = atoi(params[0].c_str());
        TVecUINT16 vecIconAppear;
        pPlayer->OpenIcon(wIconID);
        vecIconAppear.push_back(wIconID);
        CIconAppearMgr::Instance().SynToClientAddIconAppear(*pUser,vecIconAppear);
    }

    void MoneyChange(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if (!pPlayer)
            return;
        if (params.size() < 3)
            return;
        pUser->ExchangeMoney(static_cast<EPropType>(atoi(params[0].c_str())),
                static_cast<EPropType>(atoi(params[1].c_str())),
                static_cast<UINT32>(atoi(params[2].c_str())));
    }

    void Recharge(const char* cmd, const Tokenizer& params, void* p)
    {
        CUserPtr pUser = *(CUserPtr*)p;
        if (!pUser)
            return;

        if (0 == params.size())
            return;
        
        UINT32 dwRecharge = atoi(params[0].c_str());
        if (0 == dwRecharge)
            return;

        pUser->AddTotalRecharge(dwRecharge, false);    
    }

    // ===  FUNCTION  ======================================================================
    //         Name:  ChatSysLog
    //  Description:  输出一条调试信息
    // =====================================================================================
    void ChatSysLog (const string& strInfo, CUser& rUser, const char chSplit /* = '\0' */)
    {
        SSenderInfo oSenderInfo;
        oSenderInfo.qwUsrID = rUser.GetUserID();
        oSenderInfo.strName = rUser.GetFixdUserName();
        oSenderInfo.byNation = rUser.GetNation();
        oSenderInfo.byQuality = rUser.GetPlayer()->GetColor();
        TVecShowInfo vecShowInfo;

        Tokenizer tk(strInfo, chSplit);
        for (size_t szIndex = 0; szIndex < tk.size(); ++szIndex)
        {
            std::string strData = g_ChatProtS.BuildPkg_ChatInfoNotify(eChannelAll, oSenderInfo, tk[szIndex], vecShowInfo);
            rUser.SendPkg(strData);
        }
    }		// -----  end of function ChatSysLog  ----- //

    // TODO: 在这之上增加函数并在GMCMD里注册

    // XXX: readonly
    void GM(const char* cmd, int mode, void* p)
    {
        GMParse(GMCMD, sizeof(GMCMD)/sizeof(GMHandler), cmd, mode, p);
    }

} // namespace GM

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

