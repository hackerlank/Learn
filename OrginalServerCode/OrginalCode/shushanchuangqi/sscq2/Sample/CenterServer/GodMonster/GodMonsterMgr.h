
#ifndef GODMONSTERMGR_H_
#define GODMONSTERMGR_H_

#include "GodMonster.h"
#include "GodMonsterProtS.h"
#include "GodMonsterCFG.h"
#include "GodMonsterDayPkgCFG.h"
#include "GodMonsterGuildPkgCFG.h"
#include "GodMonsterPersonPkgCFG.h"
#include "GodMonsterLimitPrizeCFG.h"
#include "ItemProt.h"

using namespace NItemProt;
enum EGodMonsterPkg
{
    eGodMonsterConfig      = 1,
    eGodMonsterPersonRank,
    eGodMonsterGuildRank,
    eGodMonsterDayPkg
};

struct SGodMonsterCFGEx
{
    UINT8 byID;
    UINT32 dwDayScore;
    UINT16 wFieldDown;
    UINT16 wFieldUp;
    TVecItemGenInfo vecItems;
    SGodMonsterCFGEx()
    {
        byID = 0;
        wFieldDown = 0;
        dwDayScore = 0;
        wFieldUp = wFieldDown;
    }

};
typedef shared_ptr<SGodMonsterCFGEx> GodMonsterCFGPtr;
typedef std::map<UINT8, GodMonsterCFGPtr> TMapID2ConfigPtr;

struct SGodMonsterLimitPrizeCFGEx
{
    UINT16 wID;
    UINT16 wCurPrice;
    float  fDiscount;
    UINT16 wOrigPrice;
    UINT8  byCond;
    UINT8  byNum;
    UINT32 dwDevote;
    TVecItemGenInfo vecItems;
    SGodMonsterLimitPrizeCFGEx()
    {
        wID = wCurPrice = wOrigPrice = byCond = byNum = dwDevote = 0;
        fDiscount = 0.0;
    }
};
typedef shared_ptr<SGodMonsterLimitPrizeCFGEx> GodMonsterLimitPrizeCFGPtr;
typedef std::map<UINT16, GodMonsterLimitPrizeCFGPtr> TMapID2LimitPrizePtr;

struct SRankKey
{
    UINT64 qwID;
    string strName;
    UINT32 dwScore;
    SRankKey()
    {
        qwID = 0;
        strName = "";
        dwScore = 0;
    }

    SRankKey(UINT64 qwID_,string strName_,UINT32 dwScore_)
    {
        qwID = qwID_;
        strName = strName_;
        dwScore = dwScore_;
    }
    bool operator < (const SRankKey& oKey) const
    {
        if(qwID == oKey.qwID)
            return false;
        if(dwScore != oKey.dwScore)
            return dwScore > oKey.dwScore;
        return qwID > oKey.qwID;
    }
};

class CGodMonsterMgr 
{
public:
    CGodMonsterMgr();
    virtual ~CGodMonsterMgr() { };
    bool Init();
    //初始化活动时间
    //TODO
    
    bool LoadConfig();
    //数据库加载信息
    void LoadFromDB();
    void Load(const TVecGuildUser2DB& vecUser);
    
    //玩家进入活动
    bool Enter(CUser& rUser,SyncInfoToClient& sInfo);
    //玩家喂养神兽
    EMonsterResult OneFeed(CUser& rUser,UINT32 dwFruit = 1);
    //玩家一键喂养神兽
    EMonsterResult AllFeed(CUser& rUser);
    //玩家领取奖励
    EMonsterResult TakePrize(CUser& rUser,EMonsterPrizeType eType);
    //玩家购买限购礼包
    EMonsterResult Buy(CUser& rUser,UINT16 wIndex,UINT8 byCount);
    void OnPraise(CUser& rUser,UINT64 qwRoleID);
    void OnUrge(CUser& rUser,UINT64 qwRoleID);

public:
    enum EState
    {
        eNone,
        eAlarm,
        eBegin,
        eEnd
    };
    void OnBegin();
    void OnEnd();
    void OnAlarm();
    void TimerCheck(time_t tNow);
    void UpdateState();
    EState GetState() { return _eState; }
    void   SetState(EState eM) { _eState = eM; }
    bool   IsRuning() { return _eState == eBegin ; }
public:
    bool CreateGuild(UINT64 qwMonsterID,GodMonsterPtr& p);
    GodMonsterPtr GetMonster(UINT64 qwMonsterID);
    bool OnRank(EMonsterRank eRank,UINT64 qwID);
    GodMonsterCFGPtr GetConfig(EGodMonsterPkg eType,UINT8 byID);
    void GetMonsterUser(UINT64 qwRoleID,GodMonsterUserPtr& pUser);
    GodMonsterLimitPrizeCFGPtr GetLimitPrizeConfig(UINT16 wID);
    void InitMonsterFromGuild(UINT64 qwMonsterID,UINT32 dwScore);
    void OnMail();
    void CalcMonsterPeroid();
private:
    bool LoadMonsterConfig();
    bool LoadMonsterGuildPkg();
    bool LoadMonsterPersonPkg();
    bool LoadMonsterDayPkg();
    bool LoadLimitPrizeConfig();
    //排名邮件
    void SendMailForUser(UINT64 qwRoleID,UINT8 byIndex);
    void SendMailForGuild(UINT64 qwMonsterID,UINT8 byIndex);
    //贡献邮件
    void SendMailForDevote(GodMonsterPtr pMonster);

    UINT32 GetRank(EMonsterRank eType,UINT64 qwID);
    bool ParsePrize(string& strContent, TVecItemGenInfo& vecItem);
    bool InitMonsterUser(const SGuildUser2DB &rUser);
    //玩家更换帮派
    bool ChangeGuild(UINT64 qwRoleID,GodMonsterPtr pMonster,UINT64 qwGuildID);
    void InitMailItem(TVecItemGenInfo& vecSource,TVecMailItemInfo& vecDesc);
    UINT64 GetGuildIDByUserID(UINT64 qwRoleID);
    void CheckGuildID(UINT64 qwRoleID);
    void GetRankInfo(TVecMonsterRank& vecRank);
    void GetAllDevote(GodMonsterUserPtr pUser,TVecGuildUserDevote& vecUser);
    void OnSync(GodMonsterUserPtr pUser,GodMonsterPtr pMonster, UINT64 qwRoleID);
    void GetLimitPrize(GodMonsterUserPtr pUser,TVecLimitPrize & vecLimitPrize);
private:
    TMapID2Monster _mapID2Monster; 
    std::set<UINT64> _setUser; //没有进入帮派的玩家
    std::set<SRankKey> _setMonsterRank;
    std::set<SRankKey> _setUserRank;
    map<UINT8,TMapID2ConfigPtr> _mapType2MapConfig;
    TMapID2LimitPrizePtr _mapID2LimitPrize;
    std::map<UINT64,UINT32> _mapID2ScoreCache; //帮派数据传过来的 临时积分
    bool _bInit;
    EState _eState;
    UINT32 _dwAlarmTime;
    UINT32 _dwBeginTime; 
    UINT32 _dwEndTime;
    
};
#endif 
extern  CGodMonsterMgr g_GodMonsterMgr;
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

