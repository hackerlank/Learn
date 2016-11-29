// =====================================================================================
//
//       Filename:  BattleCombine.cpp
//
//    Description:  战斗的连携点数
//
//        Version:  1.0
//        Created:  12/29/2014 08:57:32 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "BattleCombine.h"

#include "BattleSkill.h"
#include "BattleFighter.h"
#include "BattleArea.h"

namespace NBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  CBattleCombine
//  Description:  构造函数
// =====================================================================================
CBattleCombine::CBattleCombine ()
{
}		// -----  end of function CBattleCombine  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CBattleCombine
//  Description:  析构函数
// =====================================================================================
CBattleCombine::~CBattleCombine ()
{
}		// -----  end of function ~CBattleCombine  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCombine
//  Description:  根据对应散仙获取连携点数
// =====================================================================================
UINT8 CBattleCombine::GetCombine(CBattleFighter* pFighter) const
{
    if (!pFighter)
        return 0;
    UINT8 bySide = pFighter->GetSide();
    if (bySide >= eBSideMax)
        return 0;
    UINT16 wID = pFighter->GetID();
    for (auto& rInfo : _vecCombinePosition[bySide])
    {
        if (rInfo.byTeamID != pFighter->GetTeamID())
            continue;
        for (auto& rID : rInfo.setFighterID)
        {
            if (rID == wID)
                return rInfo.byCombineCount;
        }
    }
    return 0;
}		// -----  end of function GetCombine  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCombineSkill
//  Description:  返回需要释放的组合技能
// =====================================================================================
UINT32 CBattleCombine::GetCombineSkill(UINT8 bySide, UINT8& byIndex, UINT8& byTeamID) const
{
    for (auto& rInfo : _vecCombinePosition[bySide])
    {
        UINT8 byMaxCombineCount = CBattleSkillMgr::Instance().GetCombineCount(SKILL_ID(rInfo.dwSkillID));
        if (byMaxCombineCount && !rInfo.bLock && rInfo.byCombineCount >= byMaxCombineCount)
        {
            byIndex = rInfo.byIndex;
            byTeamID = rInfo.byTeamID;
            rInfo.bLock = true;
            return rInfo.dwSkillID;
        }
    }
    return 0;
}		// -----  end of function GetCombineSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetNewCombineCount
//  Description:  获取需要更新连携点数组合技能
// =====================================================================================
bool CBattleCombine::GetNewCombineCount (UINT8 bySide, UINT8& byIndex, UINT8& byCount, TVecUINT8& rvecType) const
{
    for (auto& rInfo : _vecCombinePosition[bySide])
    {
        if (rInfo.setType.empty())
            continue;

        byIndex = rInfo.byIndex;
        byCount = rInfo.byCombineCount;
        for (auto& rType : rInfo.setType)
        {
            rvecType.push_back(static_cast<UINT8>(rType));
        }

        rInfo.setType.clear();
        return true;
    }
    return false;
}		// -----  end of function GetNewCombineCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCombineSkillFighterID
//  Description:  获取连携技能的散仙ID
// =====================================================================================
bool CBattleCombine::GetCombineSkillFighterID (UINT8 bySide, UINT8 byIndex, TSetUINT16& rsetFighterID) const
{
    for (auto& rInfo : _vecCombinePosition[bySide])
    {
        if (rInfo.byIndex == byIndex)
        {
            for (auto& rID : rInfo.setFighterID)
            {
                rsetFighterID.insert(rID);
            }
            return true;
        }
    }
    return false;
}		// -----  end of function GetCombineSkillFighterID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PushCombineSkill
//  Description:  增加新的连携技能
// =====================================================================================
bool CBattleCombine::PushCombineSkill (UINT8 bySide, UINT8 byTeamID, UINT8 byIndex, UINT32 dwSkillID)
{
    UINT32 dwBaseSkillID = SKILL_ID(dwSkillID);
    UINT32 dwSkillQuality = SKILL_QUALITY(dwSkillID);
    UINT32 dwSkillLevel = SKILL_LEVEL(dwSkillID);

    SSkill* pSkill = CBattleSkillMgr::Instance().GetSkill(dwBaseSkillID);
    if (!pSkill || pSkill->_eType != eSkillCombine)
        return false;

    SCombinePosition sCombinePostion;


    // 获取涉及到连携技能的散仙ID
    for (auto& rID : pSkill->_vecEffectID)
    {
        UINT32 dwSkillEffectID = CBattleSkillMgr::Instance().GetSkillIDQualityLevel(rID, dwSkillLevel, dwSkillQuality);
        SSkillEffect* pSkillEffect = CBattleSkillMgr::Instance().GetSkillEf(dwSkillEffectID);
        if (!pSkillEffect)
            continue;
        CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(pSkillEffect->_wArea);
        if (!pArea)
            continue;
        if (pArea->GetFighterID().empty())
            continue;
        sCombinePostion.setFighterID = pArea->GetFighterID();
    }
    for (auto& rID : pSkill->_vecProbEffectID)
    {
        UINT32 dwSkillEffectID = CBattleSkillMgr::Instance().GetSkillIDQualityLevel(rID, dwSkillLevel, dwSkillQuality);
        SSkillEffect* pSkillEffect = CBattleSkillMgr::Instance().GetSkillEf(dwSkillEffectID);
        if (!pSkillEffect)
            continue;
        CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(pSkillEffect->_wArea);
        if (!pArea)
            continue;
        if (pArea->GetFighterID().empty())
            continue;
        sCombinePostion.setFighterID = pArea->GetFighterID();
    }

    if (sCombinePostion.setFighterID.empty())
        return false;
    sCombinePostion.dwSkillID = dwSkillID;
    sCombinePostion.byIndex = byIndex;
    sCombinePostion.byTeamID = byTeamID;
    _vecCombinePosition[bySide].push_back(sCombinePostion);
    return true;
}		// -----  end of function PushCombineSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddCombine
//  Description:  增加连携点数
// =====================================================================================
bool CBattleCombine::AddCombine(CBattleFighter* pFighter, ECombineType eType, UINT8 byCount /* = 1 */)
{
    if (!pFighter)
        return false;
    UINT8 bySide = pFighter->GetSide();
    if (bySide >= eBSideMax)
        return false;
    UINT16 wID = pFighter->GetID();
    for (auto& rInfo : _vecCombinePosition[bySide])
    {
        for (auto& rID : rInfo.setFighterID)
        {
            if (rID == wID)
            {
                UINT8 byMaxCombineCount = CBattleSkillMgr::Instance().GetCombineCount(SKILL_ID(rInfo.dwSkillID));
                if (byMaxCombineCount && 
                        rInfo.setType.find(eType) == rInfo.setType.end() && 
                        rInfo.byCombineCount < byMaxCombineCount)
                {
                    rInfo.byCombineCount += byCount;
                    rInfo.byCombineCount = byMaxCombineCount < rInfo.byCombineCount? byMaxCombineCount : rInfo.byCombineCount;
                    rInfo.setType.insert(eType);
#ifdef BATTLE_SKILL_COMBINE
                    string strInfo;
                    BATTLE_DBG << "AddCombine(" << static_cast<UINT32>(eType) << "): " << (strInfo << *pFighter ) << ", "\
                         << static_cast<UINT32>(rInfo.byCombineCount) << "/" << static_cast<UINT32>(byMaxCombineCount);
#endif
                    return true;
                }
                else
                    return false;
            }
        }
    }
    return false;
}		// -----  end of function AddCombine  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UnlockCombineSkill
//  Description:  返回需要释放的组合技能
// =====================================================================================
void CBattleCombine::UnlockCombineSkill()
{
    for (UINT8 bySide = 0; bySide < eBSideMax; ++ bySide)
    {
        for (auto& rInfo : _vecCombinePosition[bySide])
        {
            rInfo.bLock = false;
        }
    }
}		// -----  end of function UnlockCombineSkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetCombine
//  Description:  重置连携点数
// =====================================================================================
void CBattleCombine::ResetCombine(UINT8 bySide, UINT32 dwSkillID)
{
    for (auto& rInfo : _vecCombinePosition[bySide])
    {
        if (rInfo.dwSkillID == dwSkillID)
        {
            rInfo.byCombineCount = 0;
#ifdef BATTLE_SKILL_COMBINE
            ostringstream strInfo;
            strInfo << CBattleSkillMgr::Instance().GetSkillName(dwSkillID) << ".";
            BATTLE_DBG << "ResetCombine CombineSkill: " << strInfo.str();
#endif
            return;
        }
    }
}		// -----  end of function ResetCombine  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearCombine
//  Description:  清除连携点数
// =====================================================================================
void CBattleCombine::ClearCombine (UINT8 bySide)
{
    _vecCombinePosition[bySide].clear();
}		// -----  end of function ClearCombine  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemoveCombineFighter
//  Description:  移除和某一个战斗对象有关的所有连携技能
// =====================================================================================
void CBattleCombine::RemoveCombineFighter (CBattleFighter* pFighter, TVecUINT8& rvecIndex)
{
    if (!pFighter)
        return;
    UINT8 bySide = pFighter->GetSide();
    if (bySide >= eBSideMax)
        return;
    for (size_t i = 0; i < _vecCombinePosition[bySide].size();)
    {
        bool bRemove = false;
        const SCombinePosition& rInfo = _vecCombinePosition[bySide][i];
        for (auto & rID : rInfo.setFighterID)
        {
            if (pFighter->GetTeamID() == rInfo.byTeamID && pFighter->GetID() == rID)
            {
                rvecIndex.push_back(rInfo.byIndex);
                _vecCombinePosition[bySide].erase(_vecCombinePosition[bySide].begin() + i);
                bRemove = true;
                break;
            }
        }
        if (!bRemove)
            ++i;
    }
}		// -----  end of function RemoveCombineFighter  ----- //

} // namespace NBattle

