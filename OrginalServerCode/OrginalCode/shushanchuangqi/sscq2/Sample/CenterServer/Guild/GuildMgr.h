#ifndef GUILD_MGR_H
#define GUILD_MGR_H

#include "stdafx.h"
#include "Singleton.h"
#include "ProtoCommon.h"
#include "Guild.h"
#include "GuildApplyInfo.h"
#include "GuildProt.h"
#include "GuildLevelCFG.h"
#include "GuildBuildingCFG.h"
#include "GuildTechCFG.h"
#include "GuildStepAwardCFG.h"
#include "XiHeTruckCFG.h"
#include "Center2DBGuild.h"
#include "ItemProt.h"
#include "Game2CenterGuildBattle.h"
#include "LingMountainShopCFG.h"
#include "Game2CenterComm.h"

using namespace NGuildProt;
using namespace NProtoCommon;
using namespace NCenter2DBGuild;
using namespace NItemProt;
using namespace NGame2CenterGuildBattle;
using namespace NGame2CenterComm;

typedef vector<SGuildBuildingCFG*> TVecPGuildBuildingCFG;
typedef map<UINT8, TVecPGuildBuildingCFG> TMapGuildBuildingCFG;
typedef map<UINT32, SLingMountainShopCFG> TMapLingMountainShopCFG;

struct SGuildTechCFGEx: public SGuildTechCFG
{
    void SetConfig(const SGuildTechCFG& rGuildTechCFG)
    {
        *(SGuildTechCFG*)this = rGuildTechCFG;
    }
    TVecFtAttrMod _vecFtAttrMod;
};

typedef vector<SGuildTechCFGEx*> TVecPGuildTechCFG;
typedef map<ETechType, TVecPGuildTechCFG> TMapGuildTechCFG;


struct SGuildStepAwardCFGEx
{
    UINT8 byRank;                   // 排名
    TVecItemCount vecItemCount;     // 奖励物品
};

typedef vector <SGuildStepAwardCFGEx*> TVecPGuildBattleAward;

enum ELogOpType
{
    eOpType_Create = 1, //创建Guild
    eOpType_Apply  = 2, //加人
    eOpType_Donate = 3, //加钱
    eOpType_Score = 4,  //积分
    eOpType_Tower = 5,  // 神谕塔
    eOpType_Store = 6,  //仓库
    eOpType_Hourse = 7  //剑阁
};
struct SLogOp
{
    ELogOpType eType;
    UINT64 qwGuildID;
    UINT8  byParam;
};

//帮派按等级排名
struct SGuildRankByLevel
{
    SGuildRankByLevel(UINT64 qwID,UINT8 byLv,UINT32 dwT,UINT32 dwE) : 
        qwGuildID(qwID) ,byLevel(byLv) ,dwTime(dwT) ,dwExp(dwE)
    { }
    UINT64 qwGuildID;
    UINT8  byLevel;
    UINT32 dwTime;
    UINT32 dwExp;

    bool operator < (const SGuildRankByLevel& sRankInfo) const
    {
        if(qwGuildID == sRankInfo.qwGuildID)
            return false;
        if(byLevel != sRankInfo.byLevel)
             return byLevel > sRankInfo.byLevel;
        if(dwExp != sRankInfo.dwExp)
             return dwExp >sRankInfo.dwExp;
        if(dwTime != sRankInfo.dwTime)
             return sRankInfo.dwTime > dwTime;
        return qwGuildID > sRankInfo.qwGuildID;
    }
};

struct SOrderListInfo
{
    SOrderListInfo(UINT64 qwGuildID, UINT32 dwScore, UINT16 wCount):
        qwGuildID(qwGuildID), dwScore(dwScore), wCount(wCount)
    {
    }
    UINT64 qwGuildID;
    UINT32 dwScore;
    UINT16 wCount;

    bool operator < (const SOrderListInfo& rOrderListInfo) const
    {
        if(qwGuildID == rOrderListInfo.qwGuildID)
            return false;
        if(dwScore != rOrderListInfo.dwScore)
             return dwScore > rOrderListInfo.dwScore;
        if(wCount != rOrderListInfo.wCount)
             return wCount > rOrderListInfo.wCount;
        return qwGuildID < rOrderListInfo.qwGuildID;
    }
};

 
typedef set <SOrderListInfo> TSetOrderListInfo;
typedef TSetOrderListInfo::iterator TItSetOrderListInfo;
typedef map<UINT64, TItSetOrderListInfo> TMapITOrderInfo;

struct SXiHeTruckCFGEx : public SXiHeTruckCFG
{
    void SetConfig(const SXiHeTruckCFG& rXiHeTruckCFG)
    {
        *(SXiHeTruckCFG*)this = rXiHeTruckCFG;
    }
    TVecItemCount _vecItemAward;
    TVecItemCount _vecItemCost;
    UINT8 _byMinLvl;
    UINT8 _byMaxLvl;

    SXiHeTruckCFGEx(): _byMinLvl(0), _byMaxLvl(0) {}
};

class CGuildMgr : public Singleton<CGuildMgr>
{
    public:
        enum EOpDisableType
        {
            eOPDNone = 0,
            eOPDGuildBattle,
            eOPDNewGuildBattle,
            eOPDMax
        };
    public:
        bool Init();
        bool LoadConfig();
        bool ReloadTable(const string& strFile);
        void LoadFromDB();
        void LoadAllGuildExchangedItemFromDB();

        void InitPubInfo(UINT32 dwCurSize, UINT32 dwTotalSize, const TVecPubGuildAllInfo& vecPubGuildAllInfo);
        void InitGuildInfo(UINT64 qwGuildID, const SDBGuildAllInfo& rData);
        void InitGuildInfo(const SDBGuildAllInfo& rData);

        void InitGuildExchangedItem(const NGuildProt::TVecGuildExchangedItem& vecGuildExchangedItem);
        
        void CreateGuild(UINT64 qwRoleID, string strName, ECreateResult& eResult, function<void(UINT8 byRet, CGuildPtr pGuild)> func);

        bool DisbandGuild(UINT64 qwGuildID);
        bool DisbandGuild(CGuildPtr pGuild);

        bool GetListInfo(UINT32 dwFirstRank, UINT32 dwCount, SOtherGuildListInfo& rOtherGuildListInfo, CGuildUserPtr pGuildUser);

        bool ApplyForGuild(UINT64 qwGuildID, CGuildUserPtr pGuildUser, EApplyResult& eResult, 
                function<void(EApplyResult eResult)> func);

        bool RejectApplyForGuild(UINT64 qwRoleID, CGuildApplyInfoPtr pApplyInfo);
        bool AgreeApplyForGuild(UINT64 qwRoleID, CGuildApplyInfoPtr pApplyInfo);

        bool GetBuildingConfig(UINT8 byID, TVecPGuildBuildingCFG& rvecPGuildBuildingCFG) const;
        bool GetTechConfig(ETechType eType, TVecPGuildTechCFG& rvecPGuildTechCFG) const;

        SLingMountainShopCFG* GetGuildExchangedItemConfig(UINT32 dwID);

        string GetAllGuildInfo(const char chSplit);   // 调试用输出字符串信息

        //LogServer 日志
        void WriteGuildLog(SLogOp &);
        CGuildPtr GetGuild(UINT64 qwGuildID);
        CGuildListInfoPtr GetListInfo(UINT64 qwGuildID);
        void GuildExchangedBegin(const TVecLingShanShopData vecLingShanShopData);

        UINT64 GetGuildID(const string& strName) const;
        void   GetGuildIDGrep(const string& strName, TVecUINT64& rvecGuildID) const;
        UINT64 GetGuildIDByOwnerName(const string& strName) const;
        void   GetGuildIDByOwnerNameGrep(const string& strName, TVecUINT64& rvecGuildID) const;
        void   GetGuildIDByBothNameGrep(const string& strName, const string& strOwnerName, TVecUINT64& rvecGuildID) const;

        const SGuildLevelCFG* GetLevelConfig(UINT16 wLevel) const;
        const SGuildLevelCFG* GetStatueConfig(UINT16 wLevel) const;
        const SGuildLevelCFG* GetStatueConfigByExp(UINT32 dwExp) const;
        UINT16 GetStatueConfigMaxLeve() const;

        UINT32 TestWorshipCond(CGuildUserPtr pGuildUser, EWorshipType eType, EStatueResult& eResult) const;
        UINT32 ProcessWorshipCond(CGuildUserPtr pGuildUser, EWorshipType eType, EStatueResult& eResult, function<void(UINT8 byRet)> func, function<void(UINT32 dwContribution, UINT32 dwCost)> func2) const;

        void   AddBattleScore(UINT64 qwGuildID, UINT32 dwScore, const TVecMemberScore& vecMemberScore);
        UINT32 GetBattleScore(UINT64 qwGuildID) const;
        bool   GetBattlePanelInfo(UINT64 qwRoleID, UINT32& rdwSelfScore, UINT32& rdwGuildScore, UINT32& rdwGuildRank) const;

        void   AddGuildBattleScore(UINT64 qwGuildID, UINT32 dwScore);
        void   RemoveGuildBattleScore(UINT64 qwGuildID);
        void   AddMemberBattleScore(UINT64 qwGuildID, const TVecMemberScore& vecMemberScore);

        void   SyncBattleRank();
        //帮派活动
        void   InitGuildRankByLevel();
        bool   SyncGuildRankByLevel(UINT64 qwGuildID,bool bFair = false);
        UINT64 GetFirstGuildByLevel();
        UINT32 GetRankForLevel(UINT64 &qwGuildID);
        bool   GetGuildLevelRank(std::set<SGuildRankByLevel> &setRank);
        UINT32 GetBattleRank(UINT64 qwRoleID) const;

        bool IsGuildOpEnable() const;
        void SetGuildOpEnable(bool bEnable, EOpDisableType eType);
        EOpDisableType GetOpDisableType() const;

        void TimeCheck(time_t tNow);

        bool StatueReward(const TVecGSWorshipInfo& rvecInfo);

        const SGuildStepAwardCFGEx* GetBattleAward(UINT16 wLevel) const;

        SXiHeTruckCFGEx* GetXiHeTruckCfg(UINT8 byTruckID);
        void GetTruckIDRandom(UINT8 byLevel, TVecUINT8& vecIDs) const;

        void UpdateOrderListMemberCount(UINT64 qwGuildID, UINT16 wLevel, UINT16 wMemberCount);
        void UpdateOrderListBattleScore(UINT64 qwGuildID);
        void RemoveOrderList(UINT64 qwGuildID);

    private:
        bool LoadLevelConfig(const string& strPath);
        bool LoadBuildingConfig(const string& strPath);
        bool LoadTechConfig(const string& strPath);
        bool LoadGuildBattleAwardConfig(const string& strPath);
        bool LoadGuildXiheConfig(const string& strPath);
        bool LoadGuildExchangedItemConfig(const string& strPath);

    private:
        map <UINT64, CGuildPtr>                 _mapGuild;
        map <UINT64, CGuildListInfoPtr>         _mapGuildListInfo;
        map <UINT64, UINT32>                    _mapGuildBattleScore;       // 帮派战积分
        map <UINT64, UINT32>                    _mapGuildBattleRank;        // 帮派战积分排名
        map <string, UINT64>                    _mapNameIndex;
        map <string, UINT64>                    _mapOwnerNameIndex;
        map <UINT64, TVecGuildApplyInfoPtr>     _mapGuildApplyCache;        // 用于还没加载进来的帮派缓存申请列表的
        map <UINT64, TVecGuildApplyInfoPtr>     _mapGuildApplyRejectCache;  // 用于还没加载进来的帮派缓存申请列表的
        map <UINT64, TVecGuildApplyInfoPtr>     _mapGuildApplyAgreeCache;   // 用于还没加载进来的帮派缓存申请列表的
        map <UINT8, SXiHeTruckCFGEx>            _mapID2XiHeTruckCFG;
        map <string, TVecUINT8>                 _mapLevelStr2TruckID;

        //帮派等级排名
        set<SGuildRankByLevel>                  _setGuildRankByLevel;

        TSetOrderListInfo                       _setOrderListInfo;
        TMapITOrderInfo                         _mapItOrderInfo;

        CGuildLevelLoader       _cLevelLoader;
        CGuildBuildingLoader    _cBuildingLoader;
        CGuildTechLoader        _cTechLoader;
        CGuildStepAwardLoader   _cBattleAwardLoader;
        CXiHeTruckLoader        _cXiheTruckLoader;
        CLingMountainShopLoader _cLingMountainShopLoader;

        TMapGuildBuildingCFG    _mapBuildingCFG;
        TMapGuildTechCFG        _mapTechCFG;
        TVecPGuildBattleAward   _vecBattleAward;
        TMapLingMountainShopCFG _mapLingMountainShopCFG;

        bool                    _bGuildOpEnable;
        EOpDisableType          _eOpDisableType;

        UINT32                  _dwStatueCheckTime;     // 神像奖励结算时间
        UINT32                  _dwBattleAwardTime;     // 帮派战奖励结算时间
        UINT32                  _dwBattleCleanTime;     // 帮派战积分清零时间
        UINT32                  _dwGuildExchangedItemCleanTime;     // 帮派兑换物品清零时间
        TVecUINT64              _vecGuidID;             //能够兑换物品的帮派ID
};

#endif // #ifndef GUILD_MGR_H

