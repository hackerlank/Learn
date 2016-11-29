
#include "stdafx.h"
#include "Creature.h"
#include "Protocols.h"
#include "Map.h"
#include "SkillAttr.h"
CCreature::CCreature() : _dwAppearState(0), _dwTimerMapIndex(0), _byJob(0), _dwNextBattleTime(0), _byLevel(0), _bDead(false), _oWalker(*this)
{}

CCreature::~CCreature()
{}

void CCreature::ResetNextBattleTime(UINT16 wNextBattleTime /* = 3 */)
{
   _dwNextBattleTime = time(NULL) + wNextBattleTime;
}

bool CCreature::CanFight(CCreature& rCreature) 
{
    if(time(NULL) <= _dwNextBattleTime
            || IsDead()
            || rCreature.IsDead())
        return false;
    else
        return true;
}

bool CCreature::NotifyMeAndSurround(const string& strPkg)
{
    CGameMapPtr pMap = GetMap();
    if(pMap == NULL || strPkg.empty())
        return false;
    return pMap->NotifyMeAndSurround(*this, strPkg);
}

bool CCreature::NotifySurround(const string& strPkg)
{
    CGameMapPtr pMap = GetMap();
    if(pMap == NULL || strPkg.empty())
        return false;
    return pMap->NotifySurround(*this, strPkg);
}

void CCreature::SetAppearState(EAppearState eAppearState, bool bNotify /*= true*/)
{
    _dwAppearState |= eAppearState;
    if(bNotify)
    {
        std::string& strAppear = g_MapProtS.BuildPkg_NotifyCreatureState(GetCreatureID(), GetAppearState());
        NotifyMeAndSurround(strAppear);
    }
}

void CCreature::ClearAppearState(EAppearState eAppearState, bool bNotify /*= true*/)
{
    _dwAppearState &= ~eAppearState;
    if(bNotify)
    {
        std::string& strAppear = g_MapProtS.BuildPkg_NotifyCreatureState(GetCreatureID(), GetAppearState());
        NotifyMeAndSurround(strAppear);
    }
}

bool CCreature::CanUseItem()
{
    if(HasAppearState(eAppearDie) || HasAppearState(eAppearGhost)) //死亡等无法控制角色
        return false;
    return true;
}

bool CCreature::MoveTo(const vector<SPoint>& vecPoint, float fDir, bool bStart)
{
    CGameMapPtr pMap = GetMap();
    if(pMap == NULL)
        return false;
    return pMap->CreatureMoveTo(*this, vecPoint, fDir, bStart);
}

bool CCreature::StopMove(const SPoint& rPoint, float fDir)
{
    CGameMapPtr pMap = GetMap();
    if(pMap == NULL)
        return false;
    return pMap->CreatureStopMove(*this, rPoint, fDir);
}

void CCreature::BufferRebuildAttr()
{
    UINT32 dwMapID = 0;
    CGameMapPtr pMap = GetMap();
    if(pMap)
    {
        dwMapID = pMap->GetMapID();
    }

    _vecBufferAttr.clear();
    VECATTR_RESET(_vecBufferAttr);

    for (auto it  = _mapInfo.begin(); it != _mapInfo.end(); ++it)
    {
        
        SDBBuffInfo& rBufferInfo = it->second;
        
        //战斗类型相关的buffer单独算
        if(rBufferInfo.byBattleType)
            continue;

        bool bNeedSet = true;
        for (auto it = rBufferInfo.vecEffectMapID.begin(); it != rBufferInfo.vecEffectMapID.end(); ++it)
        {
            bNeedSet = false;
            if(*it == dwMapID)
            {
                bNeedSet = true;
                break;
            }
        }
        if (bNeedSet)
        {
            if(rBufferInfo.vecBuffParam.size() < 2)
                continue;

            SSkillAttrPtr pSkillAttr= g_SkillAttrMgr.GetSkillAttrByID(rBufferInfo.vecBuffParam[0]);
            if(pSkillAttr)
            {
                TVecFloat vecAttr = pSkillAttr->GetVecAttr();
                for (auto it = vecAttr.begin(); it != vecAttr.end(); ++it)
                {
                    *it *= rBufferInfo.vecBuffParam[1];
                }

                //元神衰减特做
                if(rBufferInfo.vecBuffParam[0] == 4200)
                {
                    for (auto it = vecAttr.begin(); it != vecAttr.end(); ++it)
                    {
                            *it *= -1.0;
                    }
                }
                _vecBufferAttr += vecAttr;
            }
            else
                LOG_CRI<<"ERROR SkillAttrID:"<<rBufferInfo.vecBuffParam[0];
        }

    }
}

TVecFloat CCreature::GetBattleAttrVec(UINT8 byBattleType)
{
    TVecFloat vecFloat;
    VECATTR_RESET(vecFloat);

    //无效战斗类型
    if(0 == byBattleType)
    {
        return vecFloat;
    }

    for (auto it = _mapInfo.begin(); it != _mapInfo.end(); ++it)
    {
        SDBBuffInfo& rBufferInfo = it->second;
        if (rBufferInfo.byBattleType == byBattleType)
        {
            if(rBufferInfo.vecBuffParam.size() < 2)
                continue;

            SSkillAttrPtr pSkillAttr= g_SkillAttrMgr.GetSkillAttrByID(rBufferInfo.vecBuffParam[0]);
            if(pSkillAttr)
            {
                TVecFloat vecAttr = pSkillAttr->GetVecAttr();
                for (auto & rValue : vecAttr)
                {
                    rValue *= rBufferInfo.vecBuffParam[1];

                }
                //元神衰减特做
                /*if(rBufferInfo.vecBuffParam[0] == 4200)
                {
                    for (auto it = vecAttr.begin(); it != vecAttr.end(); ++it)
                    {
                            *it *= -1.0;
                    }
                }
                */
                vecFloat += vecAttr;
            }
            else
                LOG_CRI<<"ERROR SkillAttrID:"<<rBufferInfo.vecBuffParam[0];
        }

    }
    return  vecFloat;
}


