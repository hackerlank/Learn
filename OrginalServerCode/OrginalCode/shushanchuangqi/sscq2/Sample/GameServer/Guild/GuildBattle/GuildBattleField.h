// =====================================================================================
//
//       Filename:  GuildBattleField.h
//
//    Description:  帮派战场地/据点
//
//        Version:  1.0
//        Created:  07/24/2014 05:42:07 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef GUILD_BATTLE_FIELD_H
#define GUILD_BATTLE_FIELD_H

#include "stdafx.h"
#include "GuildBattleProt.h"

using namespace NGuildBattleProt;

// =====================================================================================
//        Class:  CGuildBattleField
//  Description:  帮派战场地（包括N个战斗据点）
// =====================================================================================
class CGuildBattleField
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGuildBattleField ();                             // constructor //

        virtual ~CGuildBattleField();

        // ====================  ACCESSORS     ======================================= //
        UINT64 GetGuildID(EGBSide eSide) const;
        const string& GetGuildName(EGBSide eSide) const;
        
        EGBSide GetGuildSide(UINT64 qwGuildID) const;
        bool GetAllInfo(SFieldInfo& rFieldInfo, EGBState eState, UINT64 qwGuildID = 0) const;

        bool GetSpotInfo(CPlayerPtr pPlayer, EGBSpot eSpotType, TVecSpotInfo& rvecSpotInfo, EGBResult& eResult) const;
        UINT32 GetPlayerCount(EGBSide eSide) const;
        UINT32 GetSpotPlayerCount(UINT64 qwGuildID, EGBSpot eType) const;

        void PopBattlePlayerPairs(TVecGBPlayerPtr& rvecPlayerA, TVecGBPlayerPtr& rvecPlayerB, UINT8 byCount = 3);

        UINT32 GetScore(EGBSide eGBSideA, bool bFinal = false) const;
        EGBSpot GetPlayerSpot(UINT64 qwRoleID) const;

        EGBState GetState() const;

        bool GetBattleInfo(EGBSpot eSpotType, EGBBattleResult& eResult, TVecBattleData& rvecBattleData) const;

        void ResetOBSpot(map<UINT64, EGBSpot>& rmapOBSpot) const;

        bool UpdateScore(UINT32 dwScore[2], EGBSide& eBiggerSide) const;

        bool GetSkillInfo(TVecSkillInfo& rvecSkillInfo, UINT64 qwGuildID, EGBSkillResult& eResult) const;

        void GetRoleID(EGBSide eSide, TVecUINT64& rvecRoleID) const;

        const set<EGBSkill>& GetSkill(EGBSide eSide) const;

        void GetPlayerNotInPrepareMap (TVecUINT64& rvecRoleID);

        string GetDumpInfo() const;

        // ====================  MUTATORS      ======================================= //
        void InitMap();
        void InitPlayer();
        bool InitInfo (CGuildBattleFieldPtr pField, EGBSide eSide , EGBSide eSide2);
        void SetBattle(CGuildBattlePtr pBattle);

        void SetGuildID(UINT64 qwGuildID, EGBSide eGBSide);
        void SetGuildName(const string& strGuildName, EGBSide eGBSide);

        SGuildBattleSpotPlayerPtr AddPlayer (CPlayerPtr pPlayer, EGBSide eSide, EGBSpot eSpotType, 
                EGBSignUpResult& eResult, UINT8 byIndex = 0, UINT32 dwPreCount = 0);
        SGuildBattleSpotPlayerPtr ForceAddPlayer (CPlayerPtr pPlayer, EGBSide eSide, EGBSpot eSpotType, 
                EGBSignUpResult& eResult, UINT8 byIndex);
        EGBQuitResult   RemovePlayer (CPlayerPtr pPlayer);

        void CleanMap(bool bFinal);

        void Adjust(UINT64 qwRoleID, EGBSpot eSpotType, UINT8 byIndex, EGBAdjustResult& eResult);

        void AddOB(UINT64 qwRoleID, EGBSpot eSpotType);
        void RemoveOB(UINT64 qwRoleID, EGBSpot eSpotType);

        void UserOnline (UINT64 qwRoleID);

        // ====================  OPERATORS     ======================================= //
        bool CatFieldInfo(CGuildBattleFieldPtr pField, EGBSide eSide, EGBSide eSide2, bool bCleanSrc = false );

        // ====================  METHODS       ======================================= //
        void RefreshState(bool bBattle);
        void End();
        void NotifyAllOBSpotInfo() const;
        void NotifyBattleInfo() const;
        void NotifyFieldInfo(EGBState eState, EGBSide eSide = eGBSideInvalid) const;
        void NotifySkillInfo(EGBSide eSide) const;

        void UpdateSpotCache();
        void UpdateSpotCache(UINT64 qwRoleID, EGBUserState eState);

        bool BuySkill(CPlayerPtr pPlayer, UINT64 qwGuildID, EGBSkill eSkillType, EGBSkillResult& eResult);
        void ClearSkill();

    private:
        // ====================  DATA MEMBERS  ======================================= //
        CGuildBattleWtr _pBattle;   //所属战斗

        UINT64                  _qwGuildID[2];      // 参战双方帮派ID
        string                  _strGuildName[2];   // 参战双方帮派名称

        map<EGBSpot, TVecSpotInfo>    _mapSpotInfoCache; // 据点状态变化前的缓存信息

        map<EGBSpot, CGuildBattleSpotPtr>   _mapSpot;
        map<UINT64, EGBSpot>                _mapPlayerID2Spot;

        set<EGBSkill>              _setSkillBuff[2];   // 双方帮派战技能
}; // -----  end of class CGuildBattleField  ----- //

#endif // #ifndef GUILD_BATTLE_FIELD_H

