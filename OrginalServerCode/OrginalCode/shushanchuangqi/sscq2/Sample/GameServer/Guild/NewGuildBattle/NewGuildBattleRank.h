// =====================================================================================
//
//       Filename:  NewGuildBattleRank.cpp
//
//    Description:  新帮派战排行榜
//
//        Version:  1.0
//        Created:  03/24/2015 11:41:26 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_RANK_H
#define NEW_GUILD_BATTLE_RANK_H

#include "stdafx.h"

#include "NewGuildBattleProt.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{

// 帮派战功数据
struct SGuildScore 
{
    UINT64 _qwGuildID;
    string _strName;
    UINT32 _dwScore;
    UINT32 _dwTime;

    SGuildScore(UINT64 qwGuildID, const string& strName, UINT32 dwScore, UINT32 dwTime):
        _qwGuildID(qwGuildID), _strName(strName), _dwScore(dwScore), _dwTime(dwTime)
    {
    }

    bool operator < (const SGuildScore& rOther) const
    {
        if (_qwGuildID == rOther._qwGuildID)
            return false;
        if (_dwScore != rOther._dwScore)
            return _dwScore > rOther._dwScore;
        if (_dwTime != rOther._dwTime)
            return _dwTime < rOther._dwTime;
        return _qwGuildID > rOther._qwGuildID;
    }
};				// ----------  end of struct SGuildScore  ---------- //

// =====================================================================================
//        Class:  CGuildRankMgr
//  Description:  帮派排行
// =====================================================================================
class CGuildRankMgr
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGuildRankMgr ();                             // constructor //
        virtual ~CGuildRankMgr();

        // ====================  ACCESSORS     ======================================= //
        ENGBResult GetRankInfo (ENGBMountain eMountainType,
                UINT32 dwIndex, UINT32 dwCount, 
                UINT32& dwCurIndex, UINT32& dwMaxCount,
                NNewGuildBattleProt::TVecGuildRankInfo& rvecRankInfo) const;

        UINT32 GetGuildScore(UINT64 qwGuildID, ENGBMountain eMountainType) const;

        // ====================  MUTATORS      ======================================= //
        void AddGuildScore(ENGBMountain eMountainType, UINT64 qwGuildID, const string& strName, UINT32 dwScore);

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        set<SGuildScore>        _setGuildScore;
        map<ENGBMountain, set<SGuildScore>> _mapMountainGuildScore;

}; // -----  end of class CGuildRankMgr  ----- //

// 玩家战功数据
struct SGuildMemberScore 
{
    UINT64 _qwGuildID;
    UINT64 _qwRoleID;
    string _strName;
    UINT32 _dwScore;
    UINT32 _dwTime;

    SGuildMemberScore(UINT64 qwGuildID, UINT64 qwRoleID, const string& strName, UINT32 dwScore, UINT32 dwTime):
        _qwGuildID(qwGuildID), _qwRoleID(qwRoleID), _strName(strName), _dwScore(dwScore), _dwTime(dwTime)
    {
    }

    bool operator < (const SGuildMemberScore& rOther) const
    {
        if (_qwRoleID == rOther._qwRoleID)
            return false;
        if (_dwScore != rOther._dwScore)
            return _dwScore > rOther._dwScore;
        if (_dwTime != rOther._dwTime)
            return _dwTime < rOther._dwTime;
        return _qwRoleID > rOther._qwRoleID;
    }
};				// ----------  end of struct SGuildMemberScore  ---------- //

typedef map<UINT64, set<SGuildMemberScore>> MapGuildMemberScore;

// =====================================================================================
//        Class:  CGuildMemberRankMgr
//  Description:  帮派成员排行
// =====================================================================================
class CGuildMemberRankMgr
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGuildMemberRankMgr ();                             // constructor //
        virtual ~CGuildMemberRankMgr();

        // ====================  ACCESSORS     ======================================= //
        ENGBResult GetRankInfo (ENGBMountain eMountainType, UINT64 qwGuildID,
                UINT32 dwIndex, UINT32 dwCount, 
                UINT32& dwCurIndex, UINT32& dwMaxCount,
                TVecGuildMemberRankInfo& rvecRankInfo) const;

        UINT32 GetGuildMemberScore(UINT64 qwGuildID, UINT64 qwRoleID, ENGBMountain eMountainType) const;

        // ====================  MUTATORS      ======================================= //
        void AddGuildMemberScore(ENGBMountain eMountainType, UINT64 qwGuildID, 
                UINT64 qwRoleID, const string& strName, UINT32 dwScore);
    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        MapGuildMemberScore                    _mapGuildMemberScore;
        map<ENGBMountain, MapGuildMemberScore> _mapMountainGuildMemberScore;
}; // -----  end of class CGuildMemberRankMgr  ----- //

// 玩家战功数据
struct SPlayerScore 
{
    UINT64 _qwRoleID;
    string _strName;
    UINT32 _dwScore;
    UINT32 _dwTime;

    SPlayerScore(UINT64 qwRoleID, const string& strName, UINT32 dwScore, UINT32 dwTime):
        _qwRoleID(qwRoleID), _strName(strName), _dwScore(dwScore), _dwTime(dwTime)
    {
    }

    bool operator < (const SPlayerScore& rOther) const
    {
        if (_qwRoleID == rOther._qwRoleID)
            return false;
        if (_dwScore != rOther._dwScore)
            return _dwScore > rOther._dwScore;
        if (_dwTime != rOther._dwTime)
            return _dwTime < rOther._dwTime;
        return _qwRoleID > rOther._qwRoleID;
    }
};				// ----------  end of struct SPlayerScore  ---------- //

// =====================================================================================
//        Class:  CPlayerRankMgr
//  Description:  玩家排行
// =====================================================================================
class CPlayerRankMgr
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CPlayerRankMgr ();                             // constructor //
        virtual ~CPlayerRankMgr();

        // ====================  ACCESSORS     ======================================= //
        ENGBResult GetRankInfo (ENGBMountain eMountainType,
                UINT32 dwIndex, UINT32 dwCount, 
                UINT32& dwCurIndex, UINT32& dwMaxCount,
                TVecPlayerRankInfo& rvecRankInfo) const;

        UINT32 GetPlayerScore(UINT64 qwPlayerID, ENGBMountain eMountainType) const;

        // ====================  MUTATORS      ======================================= //
        void AddPlayerScore(ENGBMountain eMountainType, UINT64 qwRoleID, const string& strName, UINT32 dwScore);

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        set<SPlayerScore>        _setPlayerScore;
        map<ENGBMountain, set<SPlayerScore>> _mapMountainPlayerScore;
}; // -----  end of class CPlayerRankMgr  ----- //

} // namespace NNewGuildBattle;

#endif

