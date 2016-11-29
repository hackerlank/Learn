#ifndef ARENAMANAGER_H__
#define ARENAMANAGER_H__
#include "ArenaGSSvr.h"
#include "RankData.h"
#include <unordered_map>
#include "stdafx.h"
using namespace NArenaGS;
#define CLOSEARENA //是否关闭历练
namespace NRoleInfoDefine
{
    struct SRoleArenaInfo;
}
enum EICON_TYPE
{
    Type_Arena = 15,
    Type_Ladder =30,
    Award_Arena = 1<<0,
    Award_Ladder =1<<1,
    EnemyLockTimer = 3,
    MaxRobotID = 65535,
};
struct LadderRankAward
{
    UINT16 wItemId;
    UINT32 dwItenNum;
    LadderRankAward()
    {
        wItemId = 0;
        dwItenNum = 0;
    }
};

struct ArenaConfig
{
    struct ArenaNum
    {
        UINT8 byFreeTimes;//每日免费挑战次数
        UINT8 byExtraTimes;//每日额外挑战次数
        UINT8 byExtraVip;//获得额外挑战次数的vip等级
        UINT32 dwExtraCost;//获得额外挑战单次花费仙石
        UINT8 byReflushTimer;//刷新每日挑战次数的时间
        UINT32 dwCDTimer;//挑战冷却时间
        UINT32 dwClearCDCost;//挑战冷却时间
        UINT8  byWinLadderMoneyType1;//天梯挑战胜利获取资源1类型
        UINT32 dwWinLadderMoneyValue1;//天梯挑战胜利获取资源1数字
        UINT8  byWinLadderMoneyType2;//天梯挑战胜利获取资源2类型
        UINT32 dwWinLadderMoneyValue2;//天梯挑战胜利获取资源2数字
        UINT8  byFailLadderMoneyType1;//天梯挑战失败获取资源1类型
        UINT32 dwFailLadderMoneyValue1;//天梯挑战失败获取资源1数字
        UINT8  byFailLadderMoneyType2;//天梯挑战失败获取资源2类型
        UINT32 dwFailLadderMoneyValue2;//天梯挑战失败获取资源2数字


    };
    struct FlushChallenger
    {
        vector<UINT8> vecFlushTimer;//对手刷新时间
        vector<UINT8> vecFlushLevel;//对手刷新的段位分布
        UINT32 dwBaseFlushCost;//自费刷新对手的基础花费
        UINT32 dwAddFlushCost;//自费刷新对手的递增花费
        UINT8  byReflushTimer;//清除自费刷新对手记录的时间
    };
    struct Worship
    {
        UINT8 byMaxNum;//膜拜最大次数
        UINT8 byShowworshipNum;//展示膜拜对象数目
        UINT32 dwLootId;//膜拜奖励
        UINT8 byReflushTimer;//清除膜拜记录时间
    };
    struct DelCondition
    {
        UINT8 byDelLevel;
        UINT8 byDays;
    };
    UINT8 byCalTimer;//计算时间
    ArenaNum stArenaNum;
    FlushChallenger stFlushChallenger;
    vector<UINT16> vecRobot;//机器人库
    Worship stWorship;
    DelCondition stDelCon;
};
class CCenterVar;
typedef std::shared_ptr<SArenaPlayerBaseData2Client>  Data2ClientPtr;
typedef function<void(Data2ClientPtr)> FunInfo;
typedef std::shared_ptr<TVecSFlushFitherForClient>  FlushClientVecPtr;
typedef function<void(FlushClientVecPtr)> FunFlushClientInfo;
typedef std::shared_ptr<SFlushFitherForClient> SFlushFitherForClientPtr;
typedef function<void(UINT8 byRet,UINT8 bySuc,UINT64 qwBattleID)> FunBattle;
typedef function<void(SArenaPlayerData * pPlayer)> CreateFun;
class CArenaManager
{
    public:
        static void InsertPlayer(const TVecArenaPlayerData& vecDatarr);
        static void PlayerEnter(UINT64 qwRoleID,UINT32 dwCalTimer,CreateFun Fun);
        static bool Init();
        static bool ReloadTable(const string& strFile);
        static SArenaPlayerData *GetPlayer(UINT64 qwRoleID);
        static CRankData* GetRankData(EArenaLevel eLevel);
        static bool LoadArenaConfig(const string& strPath);
        static bool IsLoad(){return _bLoadFromDB;}
        static bool IsDoInitCase(){return _bInitCase;}
        static void LoadFromDB();
        static void DoInitCase();
        static void RecieveDBData(UINT32 dwCurPage,UINT32 dwTotalPage,const NArenaGS::TVecArenaPlayerData& vecSendData);
        static void CalRank();
        static const ArenaConfig& GetArenaConfig(){return _stConfig;}
        static void UpAllDataToDB(const vector<UINT64> &rvecDel);
        static void PlayerGetInfo(UINT64 qwRoleID,UINT32 dwCalTimer,FunInfo Fun);
        static void UpadateBaseToDB(UINT64 qwRoleID);
        static void UpadateBaseToDB(const TSetUINT64& setRoleID);
        static void GetPlayerListByRank(TVecArenaRank2Client &rVec,EArenaLevel eLevel,UINT32 dwFrom,UINT8 byNum);
        static UINT32 GetPlayerSizeByRank(EArenaLevel eLevel);

        static bool  CheckAward(NRoleInfoDefine::SRoleArenaInfo &rInfo,SArenaPlayerData *pPlayer,UINT32 dwCalTimer);    
        //刷对手，如果有更新返回true,否则返回false,更新的数据放到Player身上
        static bool  CheckFlush(UINT64 qwRoleID);
        static void  DoFlush(UINT64 qwRoleID);

        //根据玩家数据完善展示数据
        static void  GetFlushClient(UINT64 qwRoleID,FunFlushClientInfo funFlush);        
        //更新玩家竞技场信息数据库
        static void UpdatePlayerDataToDB(UINT64 qwRoleID);
        //更新玩家等级
        static void UpdatePlayerLevel(UINT64 qwRoleID,UINT8 byLevel);
        static void UpdatePlayerQuality(UINT64 qwRoleID,UINT8 byQuality);
        static void UpdatePlayerVIPLevel(UINT64 qwRoleID,UINT8 byVIPLevel);
        //玩家斗剑
        static void DoArenaChallenge(UINT64 qwRoleID,UINT64 qwDefense,shared_func<CArenaGSSvr::SArenaChallengeReqAck>& fnAck);
        static void DoFighterToEnemy(UINT64 qwRoleID,UINT64 qwDefense,UINT32 dwCost, FunBattle fun);
        //膜拜
        static void ResetWirship();

        static const TVecArenaRank2Client& GetWirship(){return _vecWirship;} 
        static void CalAwardInfo(SArenaPlayerData *pPlayer,TVecArenaAward &vecAwards);
        static void  DoBuyArenaChallengeTimes(SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SArenaByChallengeTimesAck>& fnAck);
        static void  DoBuyLadderTimes(SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SArenaBuyLadderTimesAck>& fnAck);
    public:
        static void GetLadderAward(CUserPtr pUser,SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SGetLadderAwardAck>& fnAck);
        static void  GetArenaAward(CUserPtr pUser,SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SGetArenaAwardAck>& fnAck);
        static void GetLadderReport(CUserPtr pUser,SArenaPlayerData *pPlayer,shared_func<CArenaGSSvr::SGetLadderReportAck>& fnAck);
        static void LadderBattle(CUserPtr pUser,SArenaPlayerData *pPlayer,UINT64 qwEnemyID,UINT32 dwEnemyRank, shared_func<CArenaGSSvr::SLadderBattleAck>& fnAck);
        static void  ReFluseLadderEnemy(CUserPtr pUser,SArenaPlayerData *pPlayer,UINT8 byType,shared_func<CArenaGSSvr::SReFluseLadderEnemyAck>& fnAck);
        static void LadderPageUpReq(CUserPtr pUser,UINT32 dwRank,UINT8 byNum,shared_func<CArenaGSSvr::SLadderPageUpReqAck>& fnAck);
        static bool GetRankInfo (UINT64 qwRoleID, UINT32 dwIndex, UINT32 dwCount, UINT32& dwMaxCount, UINT32& dwCurIndex, UINT32& dwSelfRank, TVecArenaRank2Client& vecRankInfo, SArenaRank2Client& stClient);
        static bool CanLadderByRank(UINT64 qwRoleID,UINT32 dwAttackRank,UINT64 qwDeFense);
        static void SelectLadderEnemyByType(UINT64 qwRoleID,TVecUINT64 &rvecEnemy,UINT32 dwRank,UINT8 byType = 0);
        static void   LadderNoticeServer(UINT64 qwRoleID,SArenaPlayerData * pPlayer,UINT32 dwOldRank);
        static void   GetFlushFitherLadder(TVecSFlushFitherForClient &rVec,SArenaPlayerData *pPlayer,UINT8 byType = 0); 
        static bool   GetFlushFitherByID(UINT64 qwRoleID,SFlushFitherForClient &rClient,bool bLadder,UINT8 bySuc =0 );
        static bool  GetRankClient(UINT64 qwRoleID,SArenaRank2Client &stClient,UINT32 dwRank ,bool bforLadder);
        static void  SendLadderRankAward(UINT64 qwRoleID,UINT32 dwLastRank,UINT32 dwNowRank); 
        static UINT16 GetRobotRankById(UINT16 wMonster);
        static void OnRecv_SendAllRobot(const TVecLadderRobot& vecRobot);
        static bool IsRobot(UINT64 qwRobot,bool bIsLadderRobot );
        static bool LockEnemy(UINT64 qwEnemyID);
        static void UnLockEnemy(UINT64 qwEnemyID);
    private:
        static void ResetFlushChallengerVar(CCenterVar& rVar);
        static bool GetFlushChallengerVar(CCenterVar& rVar);
        static void GetRandRomPlayer(TVecUINT64 &vecSel,const set<UINT64>&vecSet);
        static void  DoFlushSel(UINT64 qwRoleID,TVecUINT64 &rSel);
        static void  GetAward(EArenaLevel eCurLevel,UINT32 dwLastLadderRank,EArenaLevel eLastLevel,UINT32 dwLastRank,TVecArenaAward &vecAwards);
        static NRoleInfoDefine::SRoleArenaInfo *GetPlayerInfo(UINT64 qwRoleID);
        static UINT32  GetLadderAwardByRank(UINT32 dwLadderRank);
    public:
        static UINT32  LadderRankNoRank;
        static UINT32  LadderRankInit;
    private:
        static bool _bLoadFromDB;
        static  bool _bInitCase;
        static UINT8 _byLoadOver;
        static unordered_map<UINT64,SArenaPlayerData> _mapAllPlayer;
        static map<EArenaLevel, CRankData> _mapAllRank;
        static ArenaConfig _stConfig;
        static TVecArenaRank2Client _vecWirship;
        static TVecUINT64 _vecLadderRank;//前2000名玩家
        static map<UINT16,vector<LadderRankAward> > _mapLadderAward;
        static map<UINT16,UINT16> _mapLadderRobotIDRankFirst;//配置文件
        static map<UINT16,UINT32 > _mapLadder;
        static map<UINT16,UINT16> _mapLadderRobotIDIDFirst;//存档文件
        static map<UINT64,UINT32> _mapLadderEnemyLock;
    private:
        //for test
        static NArenaGS::TVecArenaPlayerData _vecErr;
        static map<UINT16,TVecUINT64> _mapErrForLadder;
        static TVecLadderRobot _vecRobot;
        static void InsertErrPlayer();
};
#endif
