#ifndef _SHUSHANBATTLE_H_
#define _SHUSHANBATTLE_H_


#include "MapMgr.h"
#include "Singleton.h"

#define MAX_ACHLEVEL 9
#define INIT_MAPID 12
#define ENTER_MAPID 2001
#define FIGHT_MAPID 2002

struct PairPlayerInfo
{
    PairPlayerInfo(UINT64 qwAtkerID, UINT64 qwDeferID) : _qwAtkerRoleID(qwAtkerID), _qwDeferRoleID(qwDeferID)
    {
        _pFightMap = CMapMgr::CreateMap(FIGHT_MAPID);
        if (_pFightMap == NULL)
            LOG_CRI << "Creat ShushanBattle FightMap error";
    }
    UINT64 _qwAtkerRoleID;
    UINT64 _qwDeferRoleID;
    CGameMapPtr _pFightMap;

    void Reset()
    {
        _qwAtkerRoleID = 0;
        _qwDeferRoleID = 0;
    }
    void SetRoleID(UINT64 qwAtkerID, UINT64 qwDeferID)
    {
        if (qwAtkerID == qwDeferID)
            return;
        _qwAtkerRoleID = qwAtkerID;
        _qwDeferRoleID = qwDeferID;
    }
};
typedef std::map<UINT32, PairPlayerInfo> TMapPairPlayerInfo;

struct SSBPlayerData
{
	SSBPlayerData()
        :_qwRoleID(0), /*_pPlayer(NULL), */_wHonor(0), _byHonorLvl(0), _byTotalWin(0), _byTotalLose(0), _byMaxKill(0), _byCurrKill(0),
            _byDomineer(0), _byAnger(0), _wSkillFlags(0), _byType(0xFF) {}

    UINT64 _qwRoleID;
    CPlayerWtr _pPlayer;
	UINT16 _wHonor;
	UINT8 _byHonorLvl;
	UINT8 _byTotalWin;
	UINT8 _byTotalLose;
	UINT8 _byMaxKill;
	UINT8 _byCurrKill;
    UINT8 _byDomineer; //霸气值
    UINT8 _byAnger;   //怒气值
    UINT16 _wSkillFlags; //技能域值
	UINT8 _byType; //0:进入 1:离开 2:轮空 3:战斗
    TVecTaskData _vecTaskInfo;  //需要完成的任务(5个)
    TVecSSBattleReport _vecBattleReport; //玩家的所有战报

    UINT8 UpdateTaskInfo(UINT8);
    void SetAllTaskInfo();
    void SetSkillFlag(UINT8 bySkillId) { _wSkillFlags |= 1 << (bySkillId-1); }
    bool CanAddSkillFlag(UINT8);
    bool AddAngerDomineer(UINT8, UINT8);
    void SetHonorLevel(UINT16 wHonor = 0);
    void SendBattleReport();
    bool IsQuit() { return _byType == eSSBattle_QUIT; }
    CPlayerPtr GetPlayer() { return _pPlayer.lock(); }
};
typedef std::map<UINT64, SSBPlayerDataPtr> TMapSSBPlayerData;

class CShushanBattle : public Singleton<CShushanBattle>
{
public:
    CShushanBattle();
	void Process(UINT32);
	void Prepare();
	void End();
	ESSBattleResult PlayerEnter(CPlayerPtr);
	ESSBattleResult PlayerLeave(CPlayerPtr);
    ESSBattleResult UseSkill(CPlayerPtr, UINT8);
    ESSBattleResult BuySkill(CPlayerPtr, UINT8);
    void SendSelfInfo(CPlayerPtr);
    void SendSelfInfo(CPlayerPtr, SSBPlayerDataPtr);
    void AllotPlayers();
    void MakePairPlayers();
    void GetAddAttr(TVecFloat& rvecAttr, UINT64 qwRoleID);
    void GetFirstPlayer(CPlayerPtr);
    SSBPlayerDataPtr FindSSBPlayerData(UINT64 qwRoleID)
    {
        TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwRoleID);
        if (iter != _mapSSBPlayerData.end())
            return iter->second;
        return NULL;
    }
    bool IsPlayerInShushanBattle(UINT64 qwRoleID)
    {
        TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwRoleID);
        if (iter == _mapSSBPlayerData.end())
            return false;
        return true;
    }
private:
    CPlayerPtr GetPlayerByRoleID(UINT64 qwRoleID);
    bool Challenge(CPlayerPtr, CPlayerPtr, SSSBattleReport&);
    void CompleteTask(SSBPlayerDataPtr, SSBPlayerDataPtr);
    void CompleteTask1(SSBPlayerDataPtr);
    void PlayerEnterInSpecialTime(CPlayerPtr);
	void CheckAddExp(UINT32);
    UINT64 FindPairPlayer(UINT64);
    PairPlayerInfo * FindPairInfoByRoleID(UINT64);
    PairPlayerInfo * FindPairInfoByPairID(UINT32);
    void JoinBye();
    void SendFirstAward();
    void SendAllInfo();
    void UpdateFirst();
    void HandleBattle();
    void ChallengeResult(SSBPlayerDataPtr, SSBPlayerDataPtr, SSSBattleReport&);
    bool IsRunAway(SSBPlayerDataPtr, SSBPlayerDataPtr);
    void InsertPairID(UINT32 dwPairID);
    UINT32 GetPairID();
    UINT8 GetRound();
    void SetJoinByeRoleID(UINT64 qwRoleID) { _qwJoinByeRoleID = qwRoleID; }
private:
    static UINT32 _dwPairID;    //自增长配对ID
    CGameMapPtr _pMap;
    TMapSSBPlayerData _mapSSBPlayerData;
    //新阵营战(蜀山论剑)技能
    TVecUINT64 _vecAllPlayers[MAX_ACHLEVEL];
    UINT64 _qwJoinByeRoleID; //轮空玩家ID
    TMapPairPlayerInfo _mapPairPlayerInfo;
    TVecUINT32 _vecPairID;
	UINT32 _dwExpTime;
	UINT32 _dwTickTime;
    UINT64 _qwTopKiller;
	UINT8 _byTopStreak;
    UINT64 _qwHonorKing;
	UINT16 _wMaxHonor;
    TVecSSBattleReport _vecSSBattleReport;  //每轮战斗的战报
};

#define ShushanBattle CShushanBattle::Instance()

#endif // _SHUSHANBATTLE_H_
