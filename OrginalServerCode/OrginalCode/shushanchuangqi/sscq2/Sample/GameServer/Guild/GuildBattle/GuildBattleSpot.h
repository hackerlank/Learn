// =====================================================================================
//
//       Filename:  GuildBattleSpot.h
//
//    Description:  帮派战据点
//
//        Version:  1.0
//        Created:  07/28/2014 10:38:39 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef GUILD_BATTLE_SPOT_H
#define GUILD_BATTLE_SPOT_H

#include "stdafx.h"

#include "GuildBattleProt.h"

using namespace NGuildBattleProt;


struct SGuildBattleSpotPlayer
{
    EGBUserState        eState;
    UINT8               byWinCount;
    CPlayerWtr          pPlayer;
    CGuildBattleSpotWtr pSpot;
    bool                bLeave;
    UINT16              wFighterID;
    set<EGBSkill> setSkillBuff;

    SGuildBattleSpotPlayer(CPlayerPtr pPlayer, CGuildBattleSpotPtr pSpot):
        eState(eGBUserStateNone), byWinCount(0), pPlayer(pPlayer), pSpot(pSpot), bLeave(false)
    {
    }
    bool GetAllInfo(SBattleUserAllInfo& rInfo) const;
};

// =====================================================================================
//        Class:  CGuildBattleSpot
//  Description:  帮派战战斗据点
// =====================================================================================
class CGuildBattleSpot: public enable_shared_from_this<CGuildBattleSpot>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGuildBattleSpot (EGBSpot eType);                             // constructor //
        virtual ~CGuildBattleSpot();

        // ====================  ACCESSORS     ======================================= //
        EGBSpot GetType() const;

        void PopBattlePlayerPairs(TVecGBPlayerPtr& rvecPlayerA, TVecGBPlayerPtr& rvecPlayerB, UINT8 byCount = 3);
        UINT32 GetPlayerCount(EGBSide eSide) const;
        SGuildBattleSpotPlayerPtr GetSpotPlayer(UINT64 qwRoleID);
        EGBSide GetPlayerSide(UINT64 qwRoleID) const;

        void GetRoleID(EGBSide eSide, TVecUINT64& rvecRoleID) const;

        bool GetAllInfo(SSpotAllInfo& rSpotInfo) const;
        bool GetAllInfo(SSpotBriefInfo& rSpotInfo) const;
        bool GetAllInfo(SSpotReadyInfo& rSpotInfo) const;

        bool GetAllBattleInfo(TVecBattleData& rvecBattleData) const;

        void AppendOBSpot(map<UINT64, EGBSpot>& rmapOBSpot) const;

        TVecUINT64 GetAllOB() const;

        bool GetScore(UINT32& dwScore, EGBSide& eWinnerSide) const;

        bool IsPlayerHere(CPlayerPtr pPlayer) const;

        void GetPlayerNotInPrepareMap(TVecUINT64& rvecRoleID);

        string GetDumpInfo() const;
        // ====================  MUTATORS      ======================================= //
        void InitMap(UINT64 qwGuildIDA, UINT64 qwGuildIDB);
        void InitPlayer(set<EGBSkill> setSkillBuff[2]);

        SGuildBattleSpotPlayerPtr AddPlayer(CPlayerPtr pPlayer, EGBSide eSide, 
                EGBSignUpResult& eResult, UINT8 byIndex, UINT32 dwPreCount);
        EGBSide RemovePlayer (CPlayerPtr pPlayer, bool bCleanMark=true/*默认清除buff*/, SGuildBattleSpotPlayerPtr pSpotPlayer = NULL);

        void CatSpotInfo(CGuildBattleSpotPtr pSpot, EGBSide eSide, EGBSide eSide2, bool bCleanSrc, TVecUINT64& rvecRoleID);

        void PushBattleInfo(CGuildBattleInfoPtr pInfo);

        void CleanMap(bool bFinal);

        void AddOB(UINT64 qwRoleID);
        void RemoveOB(UINT64 qwRoleID);

        void ClearBattleInfo();

        // ====================  OPERATORS     ======================================= //
       
        // ====================  METHODS       ======================================= //
        void RefreshState(bool bBattle);
        void End();

        void NotifySpotInfo(EGBState eState, UINT64 qwGuildID = 0) const;
        void NotifyBattleInfo() const;

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        EGBSpot                 _eType;         // 场地类型
        EGBSpotState            _eState;        // 据点状态

        CGameMapPtr             _pMap;          // 据点所在地图

        TListGBPlayerPtr        _listPlayer[2];
        TListGBPlayerPtr        _listNextPlayer[2];
        TVecGuildBattleInfoPtr  _vecInfo;
        TVecGuildBattleInfoPtr  _vecLastInfo;
        TSetUINT64              _setOBID;       // 观看本据点战斗的玩家
        map<UINT64, string>     _mapReport;
}; // -----  end of class CGuildBattleSpot  ----- //

#endif // #ifndef GUILD_BATTLE_SPOT_H

