#include "GM.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "Regular.h"
#include "GUIDMgr.h"
#include "CenterGameVar.h"
#include "VarDefine.h"
#include "GuildMgr.h"
#include "DemonTowerMgr.h"
#include "GuildUser.h"
#include "GuildStatue.h"
#include "CenterConfig.h"
#include "RankMgr.h"
#include "TripodManager.h"
#include "TripodSlots.h"
#include "Tripod.h"
#include "PHPProtS.h"
#include "WonderActivityMgr.h"
#include "Answer.h"
#include "GuildXihe.h"
#include "GuildXiheManager.h"
#include "GodMonsterMgr.h"

using namespace buf;
using namespace NPHPProt;
namespace GM
{

#define CURRENT_USER(x)             \
    CUserPtr x;                     \
    if (!NetMgr.GetCurUser(&x))     \
        return;

// XXX: 需要去游戏服务器处理的指令必须注册这个函数，以便把指令转给相应的GameServer
void Proxy2Game(const char* cmd, const Tokenizer& params, void* p = NULL);

void Help(const char* cmd, const Tokenizer& params, void* p = NULL);
void GmTest(const char* cmd, const Tokenizer& params, void* p = NULL);
void ReloadLua(const char* cmd, const Tokenizer& params, void* p = NULL);
void FriendAdd(const char* cmd, const Tokenizer& params, void* p = NULL);
void FriendAddAck(const char* cmd, const Tokenizer& params, void* p = NULL);
void FriendRm(const char* cmd, const Tokenizer& params, void* p = NULL);
void FriendMv(const char* cmd, const Tokenizer& params, void* p = NULL);
void ClearArenaSysVar(const char* cmd, const Tokenizer& params, void* p = NULL);
void ClearArenaPlayerVar(const char* cmd, const Tokenizer& params, void* p = NULL);
void DumpInfo(const char* cmd, const Tokenizer& params, void* p = NULL);
void AddGuildMoney(const char* cmd, const Tokenizer& params, void* p = NULL);
void AddGuildContribution(const char* cmd, const Tokenizer& params, void* p = NULL);
void AddGuildExp(const char* cmd, const Tokenizer& params, void* p = NULL);
void ShowTime(const char* cmd, const Tokenizer& params, void* p = NULL);
void ReloadTable(const char* cmd,const Tokenizer& params,void* p = NULL);
void GmSay(const char* cmd,const Tokenizer& params,void* p = NULL);
void Tripod(const char* cmd, const Tokenizer& params, void* p = NULL);
void GuildXiheShenche(const char* cmd, const Tokenizer& params, void* p = NULL);
void SendClanItem(const char* cmd, const Tokenizer& params, void* p = NULL);
void GlobalSendItem(const char* cmd, const Tokenizer& params, void* p = NULL);
void PersonalSendItem(const char* cmd, const Tokenizer& params, void* p = NULL);
void LockUser(const char* cmd, const Tokenizer& params, void* p = NULL);
void LockSpeck(const char* cmd, const Tokenizer& params, void* p = NULL);
void SendNotice(const char* cmd, const Tokenizer& params, void* p = NULL);
void OpenDragonBall(const char* cmd, const Tokenizer& params, void* p = NULL);
void OpenAnswer(const char* cmd, const Tokenizer& params, void* p = NULL);
void Robot(const char* cmd, const Tokenizer& params, void* p = NULL);

void ChatSysLog(const string& strInfo, CUser& rUser, const char chSplit = '\0');

static GMHandler GMCMD[] ={
    {GMT_ALL, "help", &Help, "//help: for this page."},
    {GMT_ALL, "reload", &ReloadLua, "//reload [TASK|ITEM]+* => reload scripts for CenterServer"},
    {GMT_ALL, "gsreload", &Proxy2Game, "//gsreload [TASK|ITEM]+* => reload scripts for GameServer."},
    {GMT_ALL, "gcreload", &Proxy2Game, "//gcreload => reload all configuration."},

    {GMT_SUPER, "item", &Proxy2Game, "//item wItemID [wCount [bBind [byQuality]]] => add item to package."},
    {GMT_SUPER, "itemdel", &Proxy2Game, "//itemdel wItemID [wCount [bBind [byQuality]]] => del item to package."},
    {GMT_SUPER, "itemuse", &Proxy2Game, "//itemuse wItemID [wCount [bBind [byQuality]]] => use item."},
    {GMT_SUPER, "itemu", &Proxy2Game, "//itemu id=qwInstID count=wCount bind=bBind quality=byQuality => use item."},
    {GMT_SUPER, "itemswap", &Proxy2Game, "//itemswap fromtype fromidx totype toidx - [1-pack 2-depot]"},
    {GMT_SUPER, "itemsell", &Proxy2Game, "//itemsell wItemID [wCount [bBind]]"},
    {GMT_SUPER, "addloot", &Proxy2Game,"// lootid"},
    {GMT_SUPER, "npc", &Proxy2Game, "//npc id x y"},
    {GMT_SUPER, "levelup", &Proxy2Game, "//levelup [num]"},
    {GMT_SUPER, "level", &Proxy2Game, "//level [num]"},
    {GMT_SUPER, "exp", &Proxy2Game, "//exp [num]"},
    {GMT_SUPER, "gold", &Proxy2Game, "//gold [-]num"},
    {GMT_SUPER, "coupon", &Proxy2Game, "//coupon [-]num"},
    {GMT_SUPER, "silver", &Proxy2Game, "//silver [-]num"},
    {GMT_SUPER, "star", &Proxy2Game, "//star [-]num"},
    {GMT_SUPER, "soul", &Proxy2Game, "//soul [-]num (增加魂魄)"},
    {GMT_SUPER, "prestige", &Proxy2Game, "//prestige [-]num"},
    {GMT_SUPER, "honor", &Proxy2Game, "//honor [-]num"},
    {GMT_SUPER, "pexp", &Proxy2Game, "//pexp [num]"},
    {GMT_SUPER, "sigil", &Proxy2Game, "//sigil [-]num"},
    {GMT_SUPER, "centsy", &Proxy2Game, "//centsy [-]num"},
    {GMT_SUPER, "action", &Proxy2Game, "//action [-]num"},
    {GMT_SUPER, "sop", &Proxy2Game, "//sop [-]num"},
    {GMT_SUPER, "poten", &Proxy2Game, "//poten [-]num"},
    {GMT_SUPER, "taoism", &Proxy2Game, "//taoism [-]num"},
    {GMT_SUPER, "addmoney", &Proxy2Game, "//addmoney moneytype num"},
    {GMT_SUPER, "topup", &Proxy2Game, "//topup goldid num (模拟充值,goldid为41,42,43,44,45,46六种)"},

    {GMT_DEBUG, "boost",&Proxy2Game,"//boost(新手速成)"},
    {GMT_DEBUG, "robotboost",&Proxy2Game,"//robotboost(新手速成)"},

    {GMT_DEBUG, "super",&Proxy2Game,"//super(这下我的号牛逼了)"},
    {GMT_DEBUG, "enterplayerdgn", &Proxy2Game, "//enterplayerdgn wdgntype"},
    {GMT_DEBUG, "leaveplayerdgn", &Proxy2Game, "//leaveplayerdgn"},
    {GMT_DEBUG, "finishplayerdgn", &Proxy2Game, "//finishplayerdgn"},
    {GMT_DEBUG, "playerdgnkillall", &Proxy2Game, "//playerdgnkillall"},

    {GMT_DEBUG, "addowntitle", &Proxy2Game, "//addOwnTitle wTitletype "},
    {GMT_DEBUG, "delowntitle", &Proxy2Game, "//delOwnTitle wTitletype "},
    {GMT_DEBUG, "showowntitle", &Proxy2Game, "//showowntitle "},
    {GMT_DEBUG, "addequiptitle", &Proxy2Game, "//addequipTitle wTitletype "},
    {GMT_DEBUG, "delequiptitle", &Proxy2Game, "//delequipTitle wTitletype "},
    {GMT_DEBUG, "showequiptitle", &Proxy2Game, "//showequiptitle "},

    {GMT_DEBUG, "accepttask", &Proxy2Game, "//accepttask wtaskid "},
    {GMT_DEBUG, "giveuptask", &Proxy2Game, "//giveuptask wtaskid "},
    {GMT_DEBUG, "committask", &Proxy2Game, "//committask wtaskid byForce"},

    {GMT_DEBUG, "vardec", &Proxy2Game, "//varadd id type"},
    {GMT_DEBUG, "varadd", &Proxy2Game, "//varadd id value"},
    {GMT_DEBUG, "varget", &Proxy2Game, "//varget"},
    {GMT_DEBUG, "vardel", &Proxy2Game, "//vardel id"},

    {GMT_DEBUG, "cgm", &GmTest, "cgm"},
    
    {GMT_DEBUG, "friendadd", &FriendAdd, "//friendadd userid"},
    {GMT_DEBUG, "friendack", &FriendAddAck, "//friendack userid [agree=0/1]"},
    {GMT_DEBUG, "friendrm", &FriendRm, "//friendrm userid"},
    {GMT_DEBUG, "friendmv", &FriendMv, "//friendmv userid group"},

    // Battle
    {GMT_DEBUG, "sb", &Proxy2Game, "//sb(StartBattle) skillIndex fighterCount"},
    {GMT_DEBUG, "ap",&Proxy2Game,"//ap(AttackPlayer) qwPlayerID"},
    {GMT_DEBUG, "attack",&Proxy2Game,"//attack id"},
    {GMT_DEBUG, "bi",&Proxy2Game,"//bi(BattleInfo) id"},
    {GMT_DEBUG, "br",&Proxy2Game,"//br(BattleRestart) id"},
    {GMT_DEBUG, "bc", &Proxy2Game, "//bc(BattleCheat)"},

    {GMT_DEBUG, "info", &Proxy2Game, "//info type(skill/fashion/trump/citta/horse/Achieve/formation/bag/attr/pet/title/guild/cuiti/zodtrump/collect)"},
    {GMT_DEBUG, "SysMailTest",&Proxy2Game,"//BodyID,BodyParam,Title,AttachType,AttachId,AttachNum"},
    {GMT_DEBUG, "recruit",&Proxy2Game,"//recruit fighterid"},
    {GMT_DEBUG, "fighter",&Proxy2Game,"//fighter fighterid (强行招募散仙)"},
    {GMT_DEBUG, "dujie",&Proxy2Game,"//dujie level fighterid (指定ID散仙渡劫等级)"},

    //  arena
    {GMT_DEBUG, "ClearArenaSysVar",&ClearArenaSysVar,"//ClearArenaSysVar "},
    {GMT_DEBUG, "ClearArenaPlayerVar",&ClearArenaPlayerVar,"//ClearArenaPlayerVar wID"},

    {GMT_DEBUG, "pet",&Proxy2Game,"//pet wPetID"},
    {GMT_DEBUG, "chgpet",&Proxy2Game,"//chgpet wPetID"},

    // fashion
    {GMT_DEBUG, "fashion",&Proxy2Game,"//fashion wItemID"},
    {GMT_DEBUG, "setfashion",&Proxy2Game,"//setfashion wItemID"},

    {GMT_SUPER, "gm", &Proxy2Game, "//GmTest"},

    {GMT_DEBUG, "createmonster",&Proxy2Game,"//createmonster wGroupID"},
    {GMT_DEBUG, "creategather",&Proxy2Game,"//creategather wGather"},

    // guild
    {GMT_DEBUG, "dump",&DumpInfo,"//dump"},
    {GMT_DEBUG, "guildmoney", &AddGuildMoney, "//guildmoney (数值)" },
    {GMT_DEBUG, "guildcontribution", &AddGuildContribution, "//guildcontribution (数值)" },
    {GMT_DEBUG, "guildexp", &AddGuildExp, "//guildexp (数值)" },
    {GMT_DEBUG, "ge", &AddGuildExp, "//ge(guildexp) (数值)" },
    {GMT_DEBUG, "gc", &AddGuildContribution, "//gc(guildcontribution) (数值)" },
    {GMT_DEBUG, "gb", &Proxy2Game, "//gb(GuildBattle) info/start/debug/set/fast"},
    {GMT_DEBUG, "ngb", &Proxy2Game, "//ngb(NewGuildBattle) start/time/set/dump"},

    {GMT_DEBUG, "entermap",&Proxy2Game,"//entermap wMapId"},
    {GMT_DEBUG, "worldboss",&Proxy2Game,"//worldboss wWorldBossID"},
    {GMT_DEBUG, "buy",&Proxy2Game,"//buy storetype[0-5] wItemID wCount"},
    {GMT_DEBUG, "enterssb",&Proxy2Game,"//enterssb"},
    {GMT_DEBUG, "buff", &Proxy2Game, "//buff"},
    {GMT_DEBUG, "testactivity", &Proxy2Game, "//testactivity pointtype"},
    {GMT_DEBUG, "setvip", &Proxy2Game, "//setvip level"},
    {GMT_DEBUG, "bp", &Proxy2Game, "//bp(BattlePoint)"},
    {GMT_DEBUG, "hp", &Proxy2Game, "//hp(GetPlayerHP)"},
    {GMT_DEBUG, "time", &ShowTime, "//time(显示时间)" },
    {GMT_DEBUG, "sit", &Proxy2Game, "//sit qwRoleId"},
    {GMT_DEBUG, "loot", &Proxy2Game, "//loot lootid"},
    {GMT_SUPER, "reloadtable", &ReloadTable, "//reload tablename1 tablename2"},
    {GMT_SUPER, "say", &GmSay, "//gm something..."},
    {GMT_DEBUG, "beastsoul", &Proxy2Game, "//beastsoul"},
    {GMT_DEBUG, "tripod", &Tripod, "//tripod byTripodID [agree=0/1]"},
    {GMT_DEBUG, "xihe", &GuildXiheShenche, "//xihe"},
    {GMT_DEBUG, "dis", &Proxy2Game, "//dis(BattleCheat)"},
    {GMT_DEBUG, "OpenAct", &Proxy2Game, "//openact(开启精彩活动) wActID sAdvance sBegin sEnd sRetain(非必须)"},
    {GMT_DEBUG, "EndAct", &Proxy2Game, "//endact wActID"},

    {GMT_DEBUG, "sendclanitem", &SendClanItem, "//sendclanitem [wServerNo] [qwClanID] [byTarget] [ItemAID,ItemANum|ItemBID,ItemBNum|..] [strTitle] [strContent]" },
    {GMT_DEBUG, "gsenditem", &GlobalSendItem, "//gsenditem [ItemAID,ItemANum|ItemBID,ItemBNum|..] [strTitle] [strContent]" },
    {GMT_DEBUG, "psenditem", &PersonalSendItem, "//psenditem [wServerNo] [qwUserID] [ItemAID,ItemANum|ItemBID,ItemBNum|..] [strTitle] [strContent]" },
    {GMT_DEBUG, "lockuser", &LockUser, "//lockuser [wServerNo] [qwUserID] [byOptType] [dwEndTime]" },
    {GMT_DEBUG, "lockspeck", &LockSpeck, "//lockspeck [wServerNo] [qwUserID] [byOptType] [dwEndTime]" },
    {GMT_DEBUG, "sendnotice", &SendNotice, "//sendnotice [strContent]" },
    {GMT_DEBUG, "dragonball", &OpenDragonBall, "//dragonball" },
    {GMT_DEBUG, "showmem", &Proxy2Game, "//showmem" },
    {GMT_DEBUG, "oi", &Proxy2Game, "//OpenIcon" },
    {GMT_DEBUG, "change", &Proxy2Game, "//Change [srcType destType dwCount]" },
    {GMT_DEBUG, "openAnswer", &OpenAnswer, "//Answer Activity Open:" },
    {GMT_DEBUG, "recharge", &Proxy2Game, "//recharge dwRecharge"},
    {GMT_DEBUG, "robotc", &Robot, "//rbotoc(CenterServer)"},
};


void GmTest(const char* cmd, const Tokenizer& params, void* p)
{
    CURRENT_USER(pUser);
    if (!pUser)                             
       return;                             
    if (!params.size()) 
       return;

    string opCode = params[0].c_str();
    if(opCode == "loadcfg")
    {
        if(params.size() < 2)
            return;
        TVecString vecString;
        for(size_t i = 1; i < params.size() ; ++i)
        {
            vecString.push_back(params[i]);
            LOG_CRI<< " GM命令 接收到的XML文件名字为：" << params[i];
        }
        if(!vecString.empty())
        {
            CCenterConfig::Instance().ReloadTable(vecString);
        }
    }

    if(opCode == "entertower")
    {

        if (params.size()<2)
              return; 
        UINT32 dwFloorID = atoi(params[1].c_str());

        g_DemonTowerMgr.PlayerEnter(pUser->GetUserID(),dwFloorID);
    }
    /*
    if(opCode == "itemmail")
    {
        string strName = "dsfdsfdsf"; 
        string strItem = "1001,10";
        string strTitle = "ceshi";
        string strContent = "ceshi";
        string strArg = "ceshi";
        g_PHPProtS.OnSendItem(1,params[1],strName,strItem,strTitle,strContent,strArg);
        //g_DemonTowerMgr.PlayerEnter(pUser->GetUserID(),dwFloorID);
    }
    */
    if(opCode == "OnEx")
    {
        UINT8 wIndex = atoi(params[1].c_str());
        g_WonderActivityMgr.ExChange(*pUser,wIndex);
    }
    if(opCode == "OnSync")
    {
        g_WonderActivityMgr.SyncCoinInfo(*pUser);
    }
    if(opCode == "setpool")
    {
        UINT8 byType = atoi(params[1].c_str());
        UINT32 dwTmp = atoi(params[2].c_str());
        g_WonderActivityMgr.SetPoolValue(byType,dwTmp);
    }
    if(opCode == "OnFeed")
    {
        g_GodMonsterMgr.OneFeed(*pUser);
    }
    if(opCode == "OnFeedAll")
    {
        g_GodMonsterMgr.AllFeed(*pUser);
    }
    if(opCode == "OnEnter")
    {
        SyncInfoToClient sClient;
        g_GodMonsterMgr.Enter(*pUser,sClient);
    }
    if(opCode == "OnTake")
    {
        EMonsterPrizeType eType  =(EMonsterPrizeType)(atoi(params[1].c_str()));
        g_GodMonsterMgr.TakePrize(*pUser,eType);
    }
    if(opCode =="OnBuy")
    {
        UINT16 wIndex = atoi(params[1].c_str());
        UINT8 byCount = atoi(params[2].c_str());
        g_GodMonsterMgr.Buy(*pUser,wIndex,byCount);
    }
    if(opCode == "openwact")
    {

        if (params.size()<4)
              return; 
        UINT16 wActID = atoi(params[1].c_str());
        string sAdv(params[2]);
        string sBegin(params[3]);
        string sEnd(params[4]);
        string sRetain(params[5]);
        g_WonderActivityMgr.OpenActivity(wActID,sAdv,sBegin,sEnd,sRetain);
    }
    if(opCode == "testphp")
    {
       if(params.size() < 5)
           return ;
       EActivityType eType = static_cast<EActivityType>(atoi(params[1].c_str()));
       //UINT32 dwBegin = atoi(params[2].c_str());
       //UINT32 dwEnd = atoi(params[3].c_str());
       UINT32 dwType = atoi(params[4].c_str());
       //shared_fun<SOpenActAck> eResult; 
       switch(dwType)
       {
           case 1: 
       //        g_PHPProtS.OnRecv_OpenAct(eType,dwBegin,dwEnd,eResult);
           case 2:
               g_PHPProtS.IsActOpen(eType);
       }

    }


   if(opCode == "leavetower")
    {
        g_DemonTowerMgr.PlayerLeave(pUser->GetUserID());
    }

    if(opCode == "guardtower")
    {
        if (params.size()<3)                       
                  return; 
        UINT32 dwFloorID = atoi(params[1].c_str());
        UINT32 dwPos = atoi(params[2].c_str());
        g_DemonTowerMgr.Guard(pUser->GetUserID(),dwFloorID,dwPos);
    }

    if(opCode == "atktower")
    {
        if (params.size()<3)                                      
                      return;                                         
        UINT32 dwFloorID = atoi(params[1].c_str());
        UINT32 dwPos = atoi(params[2].c_str());                   
        g_DemonTowerMgr.AtkPlayer(pUser->GetUserID(),dwFloorID,dwPos);
    }

    if(opCode == "prize1tower")
    {
        g_DemonTowerMgr.TakePassDayPrize(pUser->GetUserID());
 
    }


    if(opCode == "prize2tower2")
    {
        g_DemonTowerMgr.TakeGuardFailPrize(pUser->GetUserID());
 
    }

    if(opCode == "toptower")
    {
        SDemonFloorPage oDemonFloorPage;
        g_DemonTowerMgr.GetTopList(1,10,oDemonFloorPage);
 
    }

    if(opCode == "towerspeed")
    {
        g_DemonTowerMgr.AddSpeed(pUser->GetUserID(),1);
    }

    if(opCode == "towerstore")
    {
        g_DemonTowerMgr.Restore(pUser->GetUserID(),1);
    }

    if(opCode == "towergm")
    {
        g_DemonTowerMgr.GMSet();

    }
   
    if(opCode == "abandontower")
    {
        g_DemonTowerMgr.AbandonGuard(pUser->GetUserID());
 
    }

    if(opCode == "resettower")
    {
        g_DemonTowerMgr.OnReset();
    }

    if(opCode == "udpopen")
    {
        CUser::bUdpTest = true;
    }

    if(opCode == "udpclose") 
    {
        CUser::bUdpTest = false; 
    }
}

void Help(const char* cmd, const Tokenizer& params, void* p)
{
    CURRENT_USER(pUser);

    Regular* pRegex = NULL;
    if (params.size() >= 1)
    {
        char szRegex[1024] = {0,};
        SNPRINTF(szRegex, sizeof(szRegex)-1, "%s", params[0].c_str());
        pRegex = new Regular(szRegex);
    }

    std::ostringstream strInfo;
    for (size_t i = 0; i < sizeof(GMCMD)/sizeof(GMHandler); ++i)
    {
        if (GMCMD[i].desc)
        {
            if (pRegex)
            {
                if (pRegex->matchFirst(GMCMD[i].desc))
                    strInfo << GMCMD[i].desc << std::endl;
            }
            else
                strInfo << GMCMD[i].desc << std::endl;
        }
    }

    ChatSysLog (strInfo.str(), *pUser, '\n');

    if (pRegex)
        delete pRegex;
}

void ReloadLua(const char* cmd, const Tokenizer& params, void* p)
{
}

void FriendAdd(const char* cmd, const Tokenizer& params, void* p)
{
    if (!params.size())
        return;
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;

    UINT64 qwRoleID = rUser.GetUserID();
    UINT64 qwUserID = atol(params[0].c_str());
    qwUserID = CGUIDMgr::GetGUID(CGUIDMgr::GetGroupId(qwRoleID), CGUIDMgr::GetIndex(qwRoleID), CGUIDMgr::GetType(qwRoleID), qwUserID);
    rUser.GetFriend().AddFriend(qwUserID);
}

void FriendAddAck(const char* cmd, const Tokenizer& params, void* p)
{
    if (!params.size())
        return;
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;
    UINT64 qwRoleID = rUser.GetUserID();
    UINT64 qwUserID = atol(params[0].c_str());
    qwUserID = CGUIDMgr::GetGUID(CGUIDMgr::GetGroupId(qwRoleID), CGUIDMgr::GetIndex(qwRoleID), CGUIDMgr::GetType(qwRoleID), qwUserID);

    bool bAgree = true;
    if (params.size() > 1)
        bAgree = atoi(params[1].c_str());
    rUser.GetFriend().AnswerAddFriend(bAgree, qwUserID);
}

void FriendRm(const char* cmd, const Tokenizer& params, void* p)
{
    if (!params.size())
        return;
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;
    UINT64 qwRoleID = rUser.GetUserID();
    UINT64 qwUserID = atol(params[0].c_str());
    qwUserID = CGUIDMgr::GetGUID(CGUIDMgr::GetGroupId(qwRoleID), CGUIDMgr::GetIndex(qwRoleID), CGUIDMgr::GetType(qwRoleID), qwUserID);
    bool bBlackList = false;
    if (params.size() > 1)
        bBlackList = atoi(params[1].c_str());
    rUser.GetFriend().RemoveFriend(qwUserID, bBlackList);
}

void FriendMv(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 2)
        return;
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;
    UINT64 qwRoleID = rUser.GetUserID();
    UINT64 qwUserID = atol(params[0].c_str());
    qwUserID = CGUIDMgr::GetGUID(CGUIDMgr::GetGroupId(qwRoleID), CGUIDMgr::GetIndex(qwRoleID), CGUIDMgr::GetType(qwRoleID), qwUserID);
    EFriendGroupType eGroupType = (EFriendGroupType)atoi(params[1].c_str());
    rUser.GetFriend().MoveFriend(qwUserID, eGroupType);
}


void ClearArenaSysVar(const char* cmd, const Tokenizer& params, void* p)
{
    g_CenterGameVar.DelVar(NVarDefine::eSystemVarArena);
}

void ClearArenaPlayerVar(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 1)
        return;
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;
    UINT16 wVar =  atoi(params[0].c_str()); 
    if(wVar > NVarDefine::ePlayerVarNone && wVar <= NVarDefine::ePlayerVarArenaChallenge18)
    {
       rUser.GetCenterVar().DelVar(wVar);
    }

}

void DumpInfo(const char* cmd, const Tokenizer& params, void* p)
{
    using namespace NGuildProt;
    if (params.size() < 1)
        return;
    CURRENT_USER(pUser);
    if (!pUser)
        return;
    std::string strType;
    if (params.size())
        strType = params[0];
    ostringstream strInfo;
    char chSplit = '\n';
    if (strType.compare("guildlist") == 0)
    {
        ChatSysLog ("Guild List:", *pUser);
        SOtherGuildListInfo sOtherGuildListInfo;
        CGuildMgr::Instance().GetListInfo(0, 100, sOtherGuildListInfo, NULL);
        for (auto & rInfo : sOtherGuildListInfo.vecGuildListInfo)
        {
            strInfo << rInfo.strName << "(" << rInfo.qwGuildID << ")." << chSplit;
        }
    }
    if (strType.compare("guild") == 0)
    {
        strInfo << CGuildMgr::Instance().GetAllGuildInfo(chSplit);
    }
    ChatSysLog (strInfo.str(), *pUser, chSplit);
}

void AddGuildMoney(const char* cmd, const Tokenizer& params, void* p)
{
    using namespace NGuildProt;
    if (params.size() < 1)
        return;
    CURRENT_USER(pUser);
    if (!pUser)
        return;
    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (!pGuildUser)
        return;
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
        return;

    INT32 dwMoney = 0;
    if (params.size())
        dwMoney = atoi(params[0].c_str());

    if (dwMoney == 0)
        return;
    if (dwMoney > 0)
        pGuild->AddMoney(dwMoney);
    else
        pGuild->SubMoney(-dwMoney);
    pGuild->NotifyBaseInfo();
}

void AddGuildContribution(const char* cmd, const Tokenizer& params, void* p)
{
    using namespace NGuildProt;
    if (params.size() < 1)
        return;
    CURRENT_USER(pUser);
    if (!pUser)
        return;
    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (!pGuildUser)
        return;
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
        return;

    INT32 dwMoney = 0;
    if (params.size())
        dwMoney = atoi(params[0].c_str());

    if (dwMoney == 0)
        return;
    pGuildUser->AddContribution(dwMoney);
    pGuild->NotifyBaseInfo();
}

void AddGuildExp(const char* cmd, const Tokenizer& params, void* p)
{
    using namespace NGuildProt;
    if (params.size() < 1)
        return;
    CURRENT_USER(pUser);
    if (!pUser)
        return;
    CGuildUserPtr pGuildUser = pUser->GetGuildUser();
    if (!pGuildUser)
        return;
    CGuildPtr pGuild = pGuildUser->GetGuild();
    if (!pGuild)
        return;

    INT32 dwMoney = 0;
    if (params.size())
        dwMoney = atoi(params[0].c_str());

    if (dwMoney == 0)
        return;
    CGuildStatueOwnerPtr pStatueOwner = pGuild->GetStatueOwner();
    if (pStatueOwner)
        pStatueOwner->AddExp(dwMoney);
    pGuild->NotifyBaseInfo();
}

void ShowTime(const char* cmd, const Tokenizer& params, void* p)
{
    CURRENT_USER(pUser);

    std::ostringstream strInfo;

    Time cTime(Time::Now());
    strInfo << cTime.yymmddhhmmss();
    ChatSysLog (strInfo.str(), *pUser, '\n');

}
void Proxy2Game(const char* cmd, const Tokenizer& params, void* p)
{
    std::ostringstream strInfo;
    strInfo << cmd;
    for (size_t i = 0; i < params.size(); ++i)
        strInfo << " " << params[i];
    CURRENT_USER(pUser);
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_GMCmd(&dwServerID, 1, pUser->GetUserID(), strInfo.str());
}


void ReloadTable(const char* cmd,const Tokenizer& params,void* p )
{
    TVecString strTable;
    for (size_t i = 0; i < params.size(); ++i)
        strTable.push_back(params[i]);
    //do case for Center
    Config.ReloadTable(strTable);
    //do case for Game
    g_Game2CenterCommS.SendSvr_ReloadTable(NULL,0,strTable);
    //do case for DB
    g_Center2DBCommC.Send_ReloadTable(strTable);

}

void GmSay(const char* cmd,const Tokenizer& params,void* p )
{
    if (params.size() < 1)
        return;
    for (size_t i = 0; i < params.size(); ++i)
    {
        SSenderInfo oSenderInfo;
        oSenderInfo.qwUsrID = 0;
        oSenderInfo.strName = "系统";
        oSenderInfo.byNation = 0;
        TVecShowInfo vecShowInfo;
        g_GlobalChatProtS.Send_ChatInfoNotify(eChannelAll, oSenderInfo, params[i], vecShowInfo);
    }
}

void Tripod(const char* cmd, const Tokenizer& params, void* p)
{
    if (!params.size())
        return;
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;

    UINT64 qwRoleID = rUser.GetUserID();
    UINT8 byTripodID = atoi(params[0].c_str());
    UINT8 byType = atoi(params[1].c_str());

    CTripodSlots& rTripodSlots = TripodManager.GetTripodSlots(qwRoleID);
    CTripodPtr pTripod = rTripodSlots.GetTripod(byTripodID);
    if (!pTripod)
        return;
    switch(byType)
    {
        case 1:
            if (pTripod->GetTripodData()._wFireID)
            {
                UINT32 dwCnt = atoi(params[2].c_str());
                pTripod->AddSoul(dwCnt);
                pTripod->Update2DB();
            }
            break;
        case 2:
            break;
    }
}

void GuildXiheShenche(const char* cmd, const Tokenizer& params, void* p)
{
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;

    UINT64 qwRoleID = rUser.GetUserID();

    CGuildXihePtr pGuildXihe = GuildXiheManager.GetGuildXihe(qwRoleID);
    if (!pGuildXihe)
        return;
    pGuildXihe->SetEndTime(time(NULL)+180);
    pGuildXihe->Update2DB(eOpUpdate);
    pGuildXihe->UpdateGuildXiheInfo(pUser);
    GuildXiheManager.AddXiheTimer(qwRoleID, pGuildXihe->GetEndTime());

    std::ostringstream strInfo;
    char chSplit = '\n';
    Time cTime(pGuildXihe->GetEndTime());
    strInfo << "Stage:" << pGuildXihe->GetStage() << " EndTime:" << cTime.yymmddhhmmss() << " Request:" << pGuildXihe->GetRequest() << "\n";
    TVecTruckInfo& vecTruck = pGuildXihe->GetTruckInfo();
    for (size_t i = 0; i < vecTruck.size(); ++ i)
    {
        strInfo << "TruckID:" << vecTruck[i].byTruckID << " Pos:" << vecTruck[i].byPos << " Status:" << vecTruck[i].byStatus << "\n";
    }
    ChatSysLog (strInfo.str(), *pUser, chSplit);
}

void OpenDragonBall(const char* cmd, const Tokenizer& params, void* p)
{
    if (!params.size())
        return;
    CURRENT_USER(pUser);
    CUser& rUser = *pUser;

    UINT8 byType = atoi(params[0].c_str());
    switch(byType)
    {
        case 1:
            {
                UINT32 dwBegin = Time::TheDay(0, time(NULL));
                UINT32 dwEnd   = dwBegin + 86400 * 7;
                g_CenterGameVar.SetVar(NVarDefine::eSystemVar_DragonBallActBeginTime, dwBegin);
                g_CenterGameVar.SetVar(NVarDefine::eSystemVar_DragonBallActEndTime, dwEnd);
            }
            break;
        case 2:
            rUser.GetCenterVar().DelVar(NVarDefine::ePlayerVarDayRechargeCenter);
            rUser.GetCenterVar().DelVar(NVarDefine::ePlayerVarDragonBall_AllCount);
            rUser.GetCenterVar().DelVar(NVarDefine::ePlayerVarDragonBall_TodayCount);
            break;
        case 3:
            {
                UINT32 dwBegin = Time::TheDay(0, time(NULL));
                UINT32 dwEnd   = dwBegin + 86400 * 7;
                g_CenterGameVar.SetVar(NVarDefine::eSystemVar_SevenConsumeActBeginTime, dwBegin);
                g_CenterGameVar.SetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime, dwEnd);
            }
            break;
        case 4:
            rUser.GetCenterVar().DelVar(NVarDefine::ePlayerVarSevenConsumeGold);
            rUser.GetCenterVar().DelVar(NVarDefine::ePlayerVarSevenConsumeAwardInfo);
            break;
    }

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
    oSenderInfo.byQuality = rUser.GetQuality();
    TVecShowInfo vecShowInfo;

    Tokenizer tk(strInfo, chSplit);
    for (size_t szIndex = 0; szIndex < tk.size(); ++szIndex)
    {
        g_GlobalChatProtS.Send_ChatInfoNotify(eChannelAll, oSenderInfo, tk[szIndex], vecShowInfo);
    }


}		// -----  end of function ChatSysLog  ----- //

void SendClanItem(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 4)
        return;

    UINT64 qwClanID = atol(params[0].c_str());
    g_PHPProtS.GMSendClanItem(qwClanID, params[1].c_str(), params[2].c_str(), params[3].c_str());
}

void GlobalSendItem(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 3)
        return;

    g_PHPProtS.GMGlobalSendItem(params[0].c_str(), params[1].c_str(), params[2].c_str());
}

void PersonalSendItem(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 5)
        return;

    UINT16 wServerNo = atoi(params[0].c_str());
    UINT64 qwUserID = atol(params[1].c_str());

    g_PHPProtS.GMSendItem(wServerNo, qwUserID, params[2].c_str(), params[3].c_str(), params[4].c_str());
}

void LockUser(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 4)
        return;

    UINT16 wServerNo = atoi(params[0].c_str());
    UINT64 qwUserID = atol(params[1].c_str()); 
    UINT8 byOptType = atoi(params[2].c_str()); 
    UINT32 dwTime = atoi(params[3].c_str()); 
    g_PHPProtS.GMLockOrUnlockUser(wServerNo, qwUserID, byOptType, dwTime);
}

void LockSpeck(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 4)
        return;

    UINT16 wServerNo = atoi(params[0].c_str());
    UINT64 qwUserID = atol(params[1].c_str()); 
    UINT8 byOptType = atoi(params[2].c_str()); 
    UINT32 dwTime = atoi(params[3].c_str()); 
    g_PHPProtS.GMLockOrUnlockSpeak(wServerNo, qwUserID, byOptType, dwTime);
}

void SendNotice(const char* cmd, const Tokenizer& params, void* p)
{
    if (params.size() < 1)
        return;

    g_PHPProtS.GMGlobalSendNotice(params[0].c_str());
}

void OpenAnswer(const char* cmd, const Tokenizer& params, void* p)
{
    UINT8 byPeroid = atoi(params[0].c_str());
    if(!byPeroid)
        return;
    AnswerMgr.GMOpen(byPeroid);
}


void Robot(const char* cmd, const Tokenizer& params, void* p)
{
    CURRENT_USER(pUser);
    if (!params.size() || !pUser)
        return;
    string opCode = params[0].c_str();
    if(opCode == "createguild")
    {
        ostringstream strInfo;
        strInfo << "Robot_" << (pUser->GetRoleID() & 0xFFFF);
        ECreateResult eResult;
        CGuildMgr::Instance().CreateGuild(pUser->GetRoleID(), strInfo.str(), eResult,
                [](UINT8 byRet, CGuildPtr pGuild)
                {
                    if (byRet == 0 && pGuild)
                        LOG_DBG << "Robot create guild: " << pGuild->GetName() << ".";
                    else
                        LOG_DBG << "Robot create guild failed: " << static_cast<UINT32>(byRet) << ".";
                });
    }
    else if(opCode == "joinguild" && params.size() >= 2)
    {
    }
}


// TODO: 在这之上增加函数并在GMCMD里注册

// XXX: readonly
void GM(const char* cmd, int mode, void* p)
{
    GMParse(GMCMD, sizeof(GMCMD)/sizeof(GMHandler), cmd, mode, p);
}

} // namespace GM

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

