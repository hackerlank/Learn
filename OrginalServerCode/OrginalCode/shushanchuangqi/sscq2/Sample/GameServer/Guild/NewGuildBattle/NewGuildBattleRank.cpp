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

#include "NewGuildBattleRank.h"

#include "RTime.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  CGuildRankMgr
//  Description:  构造函数
// =====================================================================================
CGuildRankMgr::CGuildRankMgr ()
{
    for (UINT8 byIndex = eNGBMNone + 1; byIndex < eNGBMMax; ++ byIndex)
    {
        ENGBMountain eMountainType = static_cast<ENGBMountain>(byIndex);
        _mapMountainGuildScore[eMountainType];
    }
}		// -----  end of function CGuildRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CGuildRankMgr
//  Description:  析构函数
// =====================================================================================
CGuildRankMgr::~CGuildRankMgr ()
{
}		// -----  end of function ~CGuildRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRankInfo
//  Description:  获取排行榜数据
// =====================================================================================
ENGBResult CGuildRankMgr::GetRankInfo (ENGBMountain eMountainType, UINT32 dwIndex, UINT32 dwCount, 
        UINT32& dwCurIndex, UINT32& dwMaxCount,
        NNewGuildBattleProt::TVecGuildRankInfo& rvecRankInfo) const
{
    if (eMountainType == eNGBMNone)
    {
        dwMaxCount = _setGuildScore.size();
        if (_setGuildScore.size() < dwIndex)
            dwIndex = 1;

        if (!dwIndex)
            dwIndex = 1;
        if (!dwCount)
            dwCount = 1;
        dwCurIndex = dwIndex;
        auto it = _setGuildScore.begin();
        advance(it, dwIndex - 1);
        for (;dwCount && it != _setGuildScore.end(); ++it, --dwCount)
        {
            SGuildRankInfo sInfo;
            sInfo.wRank     = dwCurIndex ++;
            sInfo.qwGuildID = (*it)._qwGuildID;
            sInfo.strName   = (*it)._strName;
            sInfo.dwScore   = (*it)._dwScore;

            rvecRankInfo.push_back(sInfo);
        }
    }
    else
    {
        auto it = _mapMountainGuildScore.find(eMountainType);
        if (it != _mapMountainGuildScore.end())
        {
            dwMaxCount = it->second.size();
            if (it->second.size() < dwIndex)
                dwIndex = 1;

            if (!dwIndex)
                dwIndex = 1;
            if (!dwCount)
                dwCount = 1;
            dwCurIndex = dwIndex;
            UINT32 dwRank = dwCurIndex;
            auto it2 = it->second.begin();
            advance(it2, dwIndex - 1);
            for (;dwCount && it2 != it->second.end(); ++it2, --dwCount)
            {
                SGuildRankInfo sInfo;
                sInfo.wRank     = dwRank ++;
                sInfo.qwGuildID = (*it2)._qwGuildID;
                sInfo.strName   = (*it2)._strName;
                sInfo.dwScore   = (*it2)._dwScore;

                rvecRankInfo.push_back(sInfo);
            }
        }
    }
    return eNGBRSuccess;
}		// -----  end of function GetRankInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildScore
//  Description:  获取指定帮派分数
// =====================================================================================
UINT32 CGuildRankMgr::GetGuildScore (UINT64 qwGuildID, ENGBMountain eMountainType) const
{
    if (eMountainType == eNGBMNone)
    {
        for (auto it = _setGuildScore.begin(); it != _setGuildScore.end(); ++it)
        {
            if ((*it)._qwGuildID == qwGuildID)
                return (*it)._dwScore;
        }
        return 0;
    }
    else
    {
        auto it0 = _mapMountainGuildScore.find(eMountainType);
        if (it0 == _mapMountainGuildScore.end())
            return 0;
        for (auto it = it0->second.begin(); it != it0->second.end(); ++ it)
        {
            if ((*it)._qwGuildID == qwGuildID)
                return (*it)._dwScore;
        }
            return 0;
    }
}		// -----  end of function GetGuildScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddGuildScore
//  Description:  增加帮派战功
// =====================================================================================
void CGuildRankMgr::AddGuildScore (ENGBMountain eMountainType, UINT64 qwGuildID, const string& strName, UINT32 dwScore)
{
    time_t tNow = Time::Now();
    UINT32 dwOldScore = GetGuildScore(qwGuildID, eNGBMNone);
    SGuildScore sInfo(qwGuildID, strName, dwOldScore + dwScore, tNow);
#if 0
    auto it = _setGuildScore.find(sInfo);
    if (it != _setGuildScore.end())
        _setGuildScore.erase(it);
#else
    for (auto it = _setGuildScore.begin();
            it != _setGuildScore.end();
        )
    {
        if ((*it)._qwGuildID == qwGuildID)
            _setGuildScore.erase(it ++);
        else
            ++it;
    }
#endif
    _setGuildScore.insert(sInfo);

    dwOldScore = GetGuildScore(qwGuildID, eMountainType);
    sInfo._dwScore = dwOldScore + dwScore;
#if 0
    it = _mapMountainGuildScore[eMountainType].find(sInfo);
    if (it != _mapMountainGuildScore[eMountainType].end())
        _mapMountainGuildScore[eMountainType].erase(it);
#else
    for (auto it = _mapMountainGuildScore[eMountainType].begin();
            it != _mapMountainGuildScore[eMountainType].end();
        )
    {
        if ((*it)._qwGuildID == qwGuildID)
            _mapMountainGuildScore[eMountainType].erase(it ++);
        else
            ++it;
    }

#endif
    _mapMountainGuildScore[eMountainType].insert(sInfo);
}		// -----  end of function AddGuildScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CGuildMemberRankMgr
//  Description:  构造函数
// =====================================================================================
CGuildMemberRankMgr::CGuildMemberRankMgr ()
{
    for (UINT8 byIndex = eNGBMNone + 1; byIndex < eNGBMMax; ++ byIndex)
    {
        ENGBMountain eMountainType = static_cast<ENGBMountain>(byIndex);
        _mapMountainGuildMemberScore[eMountainType];
    }
}		// -----  end of function CGuildMemberRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CGuildMemberRankMgr
//  Description:  析构函数
// =====================================================================================
CGuildMemberRankMgr::~CGuildMemberRankMgr ()
{
}		// -----  end of function ~CGuildMemberRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRankInfo
//  Description:  获取排行榜数据
// =====================================================================================
ENGBResult CGuildMemberRankMgr::GetRankInfo (ENGBMountain eMountainType, UINT64 qwGuildID, 
        UINT32 dwIndex, UINT32 dwCount, 
        UINT32& dwCurIndex, UINT32& dwMaxCount,
        TVecGuildMemberRankInfo& rvecRankInfo) const
{
    if (eMountainType == eNGBMNone)
    {
        auto it0 = _mapGuildMemberScore.find(qwGuildID);
        if (it0 == _mapGuildMemberScore.end())
        {
            dwCurIndex = 1; 
            dwMaxCount = 0;
            return eNGBRSuccess;
        }
        dwMaxCount = it0->second.size();
        if (it0->second.size() < dwIndex)
            dwIndex = 1;

        if (!dwIndex)
            dwIndex = 1;
        if (!dwCount)
            dwCount = 1;
        dwCurIndex = dwIndex;
        auto it = it0->second.begin();
        advance(it, dwIndex - 1);
        for (;dwCount && it != it0->second.end(); ++it, --dwCount)
        {
            SGuildMemberRankInfo sInfo;
            sInfo.wRank     = dwCurIndex ++;
            sInfo.qwRoleID  = (*it)._qwRoleID;
            sInfo.strName   = (*it)._strName;
            sInfo.dwScore   = (*it)._dwScore;

            rvecRankInfo.push_back(sInfo);
        }
    }
    else
    {
        auto it = _mapMountainGuildMemberScore.find(eMountainType);
        if (it == _mapMountainGuildMemberScore.end())
        {
            dwCurIndex = 1; 
            dwMaxCount = 0;
            return eNGBRSuccess;
        }
        auto it0 = it->second.find(qwGuildID);
        if (it0 == it->second.end())
        {
            dwCurIndex = 1; 
            dwMaxCount = 0;
            return eNGBRSuccess;
        }
        dwMaxCount = it0->second.size();
        if (it0->second.size() < dwIndex)
            dwIndex = 1;

        if (!dwIndex)
            dwIndex = 1;
        if (!dwCount)
            dwCount = 1;
        dwCurIndex = dwIndex;
        UINT32 dwRank = dwCurIndex;
        auto it2 = it0->second.begin();
        advance(it2, dwIndex - 1);
        for (;dwCount && it2 != it0->second.end(); ++it2, --dwCount)
        {
            SGuildMemberRankInfo sInfo;
            sInfo.wRank     = dwRank ++;
            sInfo.qwRoleID  = (*it2)._qwRoleID;
            sInfo.strName   = (*it2)._strName;
            sInfo.dwScore   = (*it2)._dwScore;

            rvecRankInfo.push_back(sInfo);
        }

    }
    return eNGBRSuccess;
}		// -----  end of function GetRankInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildMemberScore
//  Description:  获取指定帮派分数
// =====================================================================================
UINT32 CGuildMemberRankMgr::GetGuildMemberScore (UINT64 qwGuildID, UINT64 qwRoleID, ENGBMountain eMountainType) const
{
    if (eMountainType == eNGBMNone)
    {
        auto it0 = _mapGuildMemberScore.find(qwGuildID);
        if (it0 == _mapGuildMemberScore.end())
            return 0;
        for (auto it = it0->second.begin(); it != it0->second.end(); ++it)
        {
            if ((*it)._qwRoleID == qwRoleID)
                return (*it)._dwScore;
        }
        return 0;
    }
    else
    {
        auto it = _mapMountainGuildMemberScore.find(eMountainType);
        if (it == _mapMountainGuildMemberScore.end())
            return 0;
        auto it0 = it->second.find(qwGuildID);
        if (it0 == it->second.end())
            return 0;

        for (auto it = it0->second.begin(); it != it0->second.end(); ++ it)
        {
            if ((*it)._qwRoleID == qwRoleID)
                return (*it)._dwScore;
        }
            return 0;
    }
}		// -----  end of function GetGuildMemberScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddGuildMemberScore
//  Description:  更新玩家战功
// =====================================================================================
void CGuildMemberRankMgr::AddGuildMemberScore (ENGBMountain eMountainType, UINT64 qwGuildID, 
        UINT64 qwRoleID, const string& strName, UINT32 dwScore)
{
    time_t tNow = Time::Now();
    UINT32 dwOldScore = GetGuildMemberScore(qwGuildID, qwRoleID, eNGBMNone);
    SGuildMemberScore sInfo(qwGuildID, qwRoleID, strName, dwOldScore + dwScore, tNow);
#if 0
    auto it = _setGuildMemberScore.find(sInfo);
    if (it != _setGuildMemberScore.end())
        _setGuildMemberScore.erase(it);
#else
    for (auto it = _mapGuildMemberScore[qwGuildID].begin();
            it != _mapGuildMemberScore[qwGuildID].end();
        )
    {
        if ((*it)._qwRoleID == qwRoleID)
            _mapGuildMemberScore[qwGuildID].erase(it ++);
        else
            ++it;
    }
#endif
    _mapGuildMemberScore[qwGuildID].insert(sInfo);

    dwOldScore = GetGuildMemberScore(qwGuildID, qwRoleID, eMountainType);
    sInfo._dwScore = dwOldScore + dwScore;
#if 0
    it = _mapMountainGuildMemberScore[eMountainType].find(sInfo);
    if (it != _mapMountainGuildMemberScore[eMountainType].end())
        _mapMountainGuildMemberScore[eMountainType].erase(it);
#else
    for (auto it = _mapMountainGuildMemberScore[eMountainType][qwGuildID].begin();
            it != _mapMountainGuildMemberScore[eMountainType][qwGuildID].end();
        )
    {
        if ((*it)._qwRoleID == qwRoleID)
        {
            _mapMountainGuildMemberScore[eMountainType][qwGuildID].erase(it ++);
        }
        else
            ++it;
    }

#endif
    _mapMountainGuildMemberScore[eMountainType][qwGuildID].insert(sInfo);
}		// -----  end of function AddGuildMemberScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CPlayerRankMgr
//  Description:  构造函数
// =====================================================================================
CPlayerRankMgr::CPlayerRankMgr ()
{
    for (UINT8 byIndex = eNGBMNone + 1; byIndex < eNGBMMax; ++ byIndex)
    {
        ENGBMountain eMountainType = static_cast<ENGBMountain>(byIndex);
        _mapMountainPlayerScore[eMountainType];
    }
}		// -----  end of function CPlayerRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CPlayerRankMgr
//  Description:  析构函数
// =====================================================================================
CPlayerRankMgr::~CPlayerRankMgr ()
{
}		// -----  end of function ~CPlayerRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRankInfo
//  Description:  获取排行榜数据
// =====================================================================================
ENGBResult CPlayerRankMgr::GetRankInfo (ENGBMountain eMountainType,
        UINT32 dwIndex, UINT32 dwCount, 
        UINT32& dwCurIndex, UINT32& dwMaxCount,
        TVecPlayerRankInfo& rvecRankInfo) const
{
    if (eMountainType == eNGBMNone)
    {
        dwMaxCount = _setPlayerScore.size();
        if (_setPlayerScore.size() < dwIndex)
            dwIndex = 1;

        if (!dwIndex)
            dwIndex = 1;
        if (!dwCount)
            dwCount = 1;
        dwCurIndex = dwIndex;
        auto it = _setPlayerScore.begin();
        advance(it, dwIndex - 1);
        for (;dwCount && it != _setPlayerScore.end(); ++it, --dwCount)
        {
            SPlayerRankInfo sInfo;
            sInfo.wRank     = dwCurIndex ++;
            sInfo.qwRoleID  = (*it)._qwRoleID;
            sInfo.strName   = (*it)._strName;
            sInfo.dwScore   = (*it)._dwScore;

            rvecRankInfo.push_back(sInfo);
        }
    }
    else
    {
        auto it = _mapMountainPlayerScore.find(eMountainType);
        if (it != _mapMountainPlayerScore.end())
        {
            dwMaxCount = it->second.size();
            if (it->second.size() < dwIndex)
                dwIndex = 1;

            if (!dwIndex)
                dwIndex = 1;
            if (!dwCount)
                dwCount = 1;
            dwCurIndex = dwIndex;
            UINT32 dwRank = dwCurIndex;
            auto it2 = it->second.begin();
            advance(it2, dwIndex - 1);
            for (;dwCount && it2 != it->second.end(); ++it2, --dwCount)
            {
                SPlayerRankInfo sInfo;
                sInfo.wRank     = dwRank ++;
                sInfo.qwRoleID  = (*it2)._qwRoleID;
                sInfo.strName   = (*it2)._strName;
                sInfo.dwScore   = (*it2)._dwScore;

                rvecRankInfo.push_back(sInfo);
            }
        }

    }
    return eNGBRSuccess;
}		// -----  end of function GetRankInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerScore
//  Description:  获取指定帮派分数
// =====================================================================================
UINT32 CPlayerRankMgr::GetPlayerScore (UINT64 qwRoleID, ENGBMountain eMountainType) const
{
    if (eMountainType == eNGBMNone)
    {
        for (auto it = _setPlayerScore.begin(); it != _setPlayerScore.end(); ++it)
        {
            if ((*it)._qwRoleID == qwRoleID)
                return (*it)._dwScore;
        }
        return 0;
    }
    else
    {
        auto it0 = _mapMountainPlayerScore.find(eMountainType);
        if (it0 == _mapMountainPlayerScore.end())
            return 0;
        for (auto it = it0->second.begin(); it != it0->second.end(); ++ it)
        {
            if ((*it)._qwRoleID == qwRoleID)
                return (*it)._dwScore;
        }
            return 0;
    }
}		// -----  end of function GetPlayerScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayerScore
//  Description:  更新玩家战功
// =====================================================================================
void CPlayerRankMgr::AddPlayerScore (ENGBMountain eMountainType, UINT64 qwRoleID, const string& strName, UINT32 dwScore)
{
    time_t tNow = Time::Now();
    UINT32 dwOldScore = GetPlayerScore(qwRoleID, eNGBMNone);
    SPlayerScore sInfo(qwRoleID, strName, dwOldScore + dwScore, tNow);
#if 0
    auto it = _setPlayerScore.find(sInfo);
    if (it != _setPlayerScore.end())
        _setPlayerScore.erase(it);
#else
    for (auto it = _setPlayerScore.begin();
            it != _setPlayerScore.end();
        )
    {
        if ((*it)._qwRoleID == qwRoleID)
            _setPlayerScore.erase(it ++);
        else
            ++it;
    }
#endif
    _setPlayerScore.insert(sInfo);

    dwOldScore = GetPlayerScore(qwRoleID, eMountainType);
    sInfo._dwScore = dwOldScore + dwScore;
#if 0
    it = _mapMountainPlayerScore[eMountainType].find(sInfo);
    if (it != _mapMountainPlayerScore[eMountainType].end())
        _mapMountainPlayerScore[eMountainType].erase(it);
#else
    for (auto it = _mapMountainPlayerScore[eMountainType].begin();
            it != _mapMountainPlayerScore[eMountainType].end();
        )
    {
        if ((*it)._qwRoleID == qwRoleID)
        {
            _mapMountainPlayerScore[eMountainType].erase(it ++);
        }
        else
            ++it;
    }

#endif
    _mapMountainPlayerScore[eMountainType].insert(sInfo);
}		// -----  end of function AddPlayerScore  ----- //

} // namespace NNewGuildBattle;

