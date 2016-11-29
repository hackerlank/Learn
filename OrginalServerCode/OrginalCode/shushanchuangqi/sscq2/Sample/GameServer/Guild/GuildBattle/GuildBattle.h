// =====================================================================================
//
//       Filename:  GuildBattle.h
//
//    Description:  帮派战战斗类
//
//        Version:  1.0
//        Created:  07/25/2014 10:53:43 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef GUILD_BATTLE_H
#define GUILD_BATTLE_H

#include "stdafx.h"

#include "GuildBattleProtS.h"

using namespace NGuildBattleProt;

typedef map<UINT32, TVecPlayerPtr> TMapPlayerMap;

// =====================================================================================
//        Class:  CGuildBattle
//  Description:  帮派战一场战斗（两个帮派对战的所有战斗）
// =====================================================================================
class CGuildBattle: public enable_shared_from_this<CGuildBattle>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGuildBattle(); // constructor //
        virtual ~CGuildBattle();

        // ====================  ACCESSORS     ======================================= //
        bool IsInBattle(UINT64 qwRoleID) const;
        EGBState GetState() const;
        CGuildBattleFieldPtr GetField();

        bool GetSpotInfo(CPlayerPtr pPlayer, EGBSpot, TVecSpotInfo& rvecSpotInfo, EGBResult& eResult);

        void GetAllOB(TVecUINT64& rvecRoleID) const;

        bool GetBattleInfo(EGBSpot eSpotType, EGBBattleResult& eResult, TVecBattleData& rvecBattleData) const;

        UINT32 GetCurrentScore(EGBSide eSide) const;

        // ====================  MUTATORS      ======================================= //
        bool InitField(CGuildBattleFieldPtr pField, EGBSide eSide, EGBSide eSide2);
        void InitTime(UINT32 dwTodayTime);
        void SetState(EGBState eState);

        void InitMap();
        void InitPlayer();

        void PlayerQuit(CPlayerPtr pPlayer);

        // ====================  OPERATORS     ======================================= //
        void Adjust(UINT64 qwRoleID, EGBSpot eSpotType, UINT8 byIndex, EGBAdjustResult& eResult);
        void UserOnline(UINT64 qwRoleID);
        
        // ====================  METHODS       ======================================= //
        void Process(UINT32 dwTodayTime);

        void RefreshSpotInfo();
        void RefreshState(bool bBattle);

        void EndBattle();
        void CleanMap(bool bFinal);
        void CleanToPrepare();

        void SaveSpotInfo();

        void UserOffline(UINT64 qwRoleID);

        void NotifyBattleStartInfo() const;
        void NotifyFieldInfo() const;
        void NotifyFieldInfo(EGBState eState) const;
        void NotifyAllOBSpotInfo() const;
        void NotifyBattleInfo() const;
    private:
        // ====================  METHODS       ======================================= //
        void StartOneRound();
        void UpdateScore(bool bForceEnd) const;

        // ====================  DATA MEMBERS  ======================================= //
        EGBState                _eState; //状态

        UINT32                  _dwPrepareTime;     // 准备时间
        UINT32                  _dwStartTime;       // 开始时间
        UINT32                  _dwNextBattleTime;  // 下一场战斗开始时间

        CGuildBattleFieldPtr    _pField;            // 战斗场地

        mutable UINT32          _dwScore[2];        // 双方积分

        mutable EGBSide                 _eWinnerSide;       // 最终胜利方
        map<UINT64, EGBSpot>    _mapPlayerOBSpot;   // 玩家正在观看的据点位置

        mutable bool                    _bEnded;            // 该战役是否结束
}; // -----  end of class CGuildBattle  ----- //

#endif // #ifndef GUILD_BATTLE_H
