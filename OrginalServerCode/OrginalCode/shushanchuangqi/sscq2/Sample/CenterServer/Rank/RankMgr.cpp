// =====================================================================================
//
//       Filename:  RankMgr.cpp
//
//    Description:  排行榜管理
//
//        Version:  1.0
//        Created:  09/04/2014 09:39:35 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "RankMgr.h"
#include "Protocols.h"
#include "ArenaManager.h"
#include "SystemMail.h" 
#include "GuildUserMgr.h"
#include "User.h"
#include "UserMgr.h"
#include "RTime.h"
#include "EventCenter.h"
#include "RetainMgr.h"
#include "GuildMgr.h"

using namespace NEventCenter;

using NProtoCommon::ESexType;
using NProtoCommon::ESEX_MALE;
using NProtoCommon::ESEX_FEMALE;
static UINT16 GetDefaultFighterID(UINT8 byJob, ESexType eSex)
{
    UINT16 wRet = 1;
    switch (byJob)
    {
        case 1:
            if (eSex == ESEX_MALE)
                wRet = 1;
            else if (eSex == ESEX_FEMALE)
                wRet = 2;
            break;
        case 2:
            if (eSex == ESEX_MALE)
                wRet = 3;
            else if (eSex == ESEX_FEMALE)
                wRet = 4;
            break;
        case 3:
            if (eSex == ESEX_MALE)
                wRet = 5;
            else if (eSex == ESEX_FEMALE)
                wRet = 6;
            break;
        case 4:
            if (eSex == ESEX_MALE)
                wRet = 7;
            else if (eSex == ESEX_FEMALE)
                wRet = 8;
            break;
        default:
            break;
    }
    return wRet;
}

bool CRankInfoGreater::operator () (const SRankInfoPtr& pInfoA, const SRankInfoPtr& pInfoB)
{
    if (pInfoA->dwValue > pInfoB->dwValue)
        return true;
    if (pInfoA->dwValue < pInfoB->dwValue)
        return false;
    switch(pInfoA->GetClassType())
    {
        case eType_SGRBattleInfo: //类型：SGRBattleInfo
            {
                SGRBattleInfoPtr pGRInfoA = dynamic_pointer_cast<SGRBattleInfo>(pInfoA);
                SGRBattleInfoPtr pGRInfoB = dynamic_pointer_cast<SGRBattleInfo>(pInfoB);
                if (pGRInfoA->qwGuildID == pGRInfoB->qwGuildID)
                    return false;
                if (pGRInfoA->dwValue == pGRInfoB->dwValue)
                {
                    if (pGRInfoA->wLevel == pGRInfoB->wLevel)
                        return pGRInfoA->qwGuildID > pGRInfoB->qwGuildID;
                    else
                        return pGRInfoA->wLevel > pGRInfoB->wLevel;
                }
                else
                    return pGRInfoA->dwValue > pGRInfoB->dwValue;
            }
            break;
        case eType_SRRLevelInfo: //类型：SRRLevelInfo
            {
                SRRLevelInfoPtr pRRInfoA = dynamic_pointer_cast<SRRLevelInfo>(pInfoA);
                SRRLevelInfoPtr pRRInfoB = dynamic_pointer_cast<SRRLevelInfo>(pInfoB);
                if (pRRInfoA->qwRoleID == pRRInfoB->qwRoleID)
                    return false;
                if (pRRInfoA->dwValue == pRRInfoB->dwValue)
                {
                    if (pRRInfoA->qwExp == pRRInfoB->qwExp)
                        return pRRInfoA->qwRoleID > pRRInfoB->qwRoleID;
                    else
                        return pRRInfoA->qwExp > pRRInfoB->qwExp;
                }
                else
                    return pRRInfoA->dwValue > pRRInfoB->dwValue;
            }
            break;
        default:
            break;
    }
    if (pInfoA->dwUpdateTime < pInfoB->dwUpdateTime)
        return true;
    if (pInfoA->dwUpdateTime > pInfoB->dwUpdateTime)
        return false;
    return pInfoA > pInfoB;
}

// ===  FUNCTION  ======================================================================
//         Name:  Init
//  Description:  初始化
// =====================================================================================
bool CRankMgr::Init ()
{
    _dwNextAdoreTime = Time::TheWeek(1);
    _dwNextVoterTime = Time::TheDay(1);
    _bPlatFromInited = false;
    return true;
}		// -----  end of function Init  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  ~CRankMgr
//  Description:  析构函数
// =====================================================================================
CRankMgr::~CRankMgr ()
{
}		// -----  end of function ~CRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRankInfo
//  Description:  获取排名信息
// =====================================================================================
void CRankMgr::GetRankInfo (UINT64 qwRoleID, ERankType eType, UINT32 dwIndex, UINT32 dwCount,
        UINT32& dwMaxCount, UINT32& dwCurIndex, UINT32& dwSelfRank, 
        TVecRankInfo& rvecRankInfo, TVecRankInfo& rvecSelfRankInfo) const
{
    if (eType == eRTHead)
    {
        dwMaxCount = 3;
        dwCurIndex = 1;
        dwSelfRank = 0;
        return GetHeadInfo(rvecRankInfo);
    }
    switch (eType)
    {
        case eRTArena:
            return GetArenaInfo( qwRoleID, dwIndex, dwCount, dwMaxCount, dwCurIndex, dwSelfRank, rvecRankInfo, rvecSelfRankInfo);
            break;
        case eRTGuildBattle:
            qwRoleID = CGuildUserMgr::Instance().GetGuildID(qwRoleID);
            break;
        default:
            break;
    }
    auto it = _mapRankInfo.find(eType);
    if (it == _mapRankInfo.end())
    {
        dwMaxCount = 0;
        dwCurIndex = 1;
        dwSelfRank = 0;
        rvecRankInfo.clear();
        return;
    }
    const SetRankInfo& rsetRankInfo = it->second;
    auto it2 = _mapRankIndex.find(eType);
    if (it2 == _mapRankIndex.end())
        dwSelfRank = 0;
    else
    {
        const MapRankIndex& rmapRankIndex = it2->second;
        auto it3 = rmapRankIndex.find(qwRoleID);
        if (it3 == rmapRankIndex.end())
            dwSelfRank = 0;
        else
        {
            const VecItSetRank& rvecItSetRankInfo = it3->second;
            for(auto& it4 : rvecItSetRankInfo)
            {
                UINT32 dwRank = distance(rsetRankInfo.begin(), it4) + 1;
                if (!dwSelfRank || dwRank < dwSelfRank)
                    dwSelfRank = dwRank;
            }
        }
    }
    dwMaxCount = rsetRankInfo.size();
    if (rsetRankInfo.size() < dwIndex)
        dwCurIndex = 1;
    else
    {
        if (!dwIndex)
            dwIndex = 1;
        if (!dwCount)
            dwCount = 1;
        dwCurIndex = dwIndex;
        auto it3 = rsetRankInfo.begin();
        advance(it3, dwIndex - 1);
        for (;dwCount && it3 != rsetRankInfo.end(); ++it3, --dwCount)
        {
            rvecRankInfo.push_back(*it3);
        }
    }

    if (it2 == _mapRankIndex.end())
        return;
    auto it3 = (it2->second).find(qwRoleID);
    SRankInfoPtr pInfo;
    if (it3 != (it2->second).end())
    {
        for (auto& it4 : it3->second)
        {
            if (!pInfo)
                pInfo = *it4;
            else
            {
                if (pInfo->dwValue < (*it4)->dwValue)
                    pInfo = *it4;
                else if (pInfo->dwValue == (*it4)->dwValue)
                {
                    if (pInfo->dwUpdateTime > (*it4)->dwUpdateTime)
                        pInfo = *it4;
                }
            }
        }
    }
    if (pInfo)
        rvecSelfRankInfo.push_back(pInfo);
}		// -----  end of function GetRankInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetHeadInfo
//  Description:  获得魁首榜信息
// =====================================================================================
void CRankMgr::GetHeadInfo (TVecRankInfo& rvecRankInfo) const
{
    for (UINT8 byIndex = eRTRoleRankBegin; byIndex <= eRTRoleRankEnd; ++byIndex)
    {
        ERankType eType = static_cast<ERankType>(byIndex);
        auto it = _mapRankInfo.find(eType);
        if (it == _mapRankInfo.end())
            continue;
        if (it->second.empty())
            continue;
        SRoleRankInfoPtr pRoleRankInfo = dynamic_pointer_cast<SRoleRankInfo>(*(it->second.begin()));
        SRoleHeadInfoPtr pHeadInfo (new SRoleHeadInfo);

        switch(pRoleRankInfo->GetClassType())
        {
            case eType_SRRFormationInfo: //类型：SRRFormationInfo
                {
                    SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pRoleRankInfo);
                    pHeadInfo->wID = pInfo->wID;
                }
                break;
            case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                {
                    SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pRoleRankInfo);
                    pHeadInfo->wID = pInfo->wID;
                    pHeadInfo->byInfoQuality = pInfo->byInfoQuality;
                }
                break;
            case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                {
                    SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pRoleRankInfo);
                    pHeadInfo->wID = pInfo->wID;
                }
                break;
            default:
                break;
        }
        pHeadInfo->dwValue = pRoleRankInfo->dwValue;
        pHeadInfo->eType = eType;
        pHeadInfo->qwRoleID = pRoleRankInfo->qwRoleID;
        pHeadInfo->strName = pRoleRankInfo->strName;
        pHeadInfo->wPlayerFighterID = pRoleRankInfo->wPlayerFighterID;
        pHeadInfo->byQuality = pRoleRankInfo->byQuality;
        rvecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pHeadInfo));
    }

    // 斗剑
    GetArenaHeadInfo(rvecRankInfo);

    // 帮派战
    GetGuildBattleHeadInfo(rvecRankInfo);
}		// -----  end of function GetHeadInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRankRoleID
//  Description:  获取排行榜的玩家ID
// =====================================================================================
void CRankMgr::GetRankRoleID(ERankType eType, UINT32 dwIndex, UINT32 dwCount, TVecUINT64& rvecRoleID) const
{
    if (eType < eRTRoleRankBegin || eType >= eRTMax)
        return;
    auto it = _mapRankInfo.find(eType);
    if (it == _mapRankInfo.end())
    {
        LOG_INF << " NotFind "<< eType << " in _mapRankInfo";
        return;
    }

    const SetRankInfo& rsetRankInfo = it->second;
    if (rsetRankInfo.size() < dwIndex)
        dwIndex = 0;
    else
    {
        if (!dwIndex)
            dwIndex = 1;
        if (!dwCount)
            dwCount = 1;
        auto it3 = rsetRankInfo.begin();
        advance(it3, dwIndex - 1);
        for (;dwCount && it3 != rsetRankInfo.end(); ++it3, --dwCount)
        {
            SRoleRankInfoPtr pInfo = dynamic_pointer_cast<SRoleRankInfo>(*it3);
            rvecRoleID.push_back(pInfo->qwRoleID);
        }
    }

}		// -----  end of function GetRankRoleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateRankInfo
//  Description:  更新排行榜数据
// =====================================================================================
void CRankMgr::UpdateRankInfo (UINT64 qwInstID, ERankType eType, const TVecRankInfo& vecRankInfo)
{
    if (vecRankInfo.empty())
    {
        LOG_CRI << "vecRankInfo.empty().";
        return;
    }
    for (auto pBaseInfo : vecRankInfo)
    {
        UINT32 dwOldRank = 0;
        SetRankInfo& rsetRankInfo = _mapRankInfo[eType];
        MapRankIndex& rmapRankIndex = _mapRankIndex[eType];
        auto it = rmapRankIndex.find(qwInstID);
        if (it != rmapRankIndex.end())
        {
            VecItSetRank& rvecItSetRankInfo = it->second;
            for (size_t i = 0; i < rvecItSetRankInfo.size();)
            {
                if (IsSameRankInfo(pBaseInfo, *rvecItSetRankInfo[i]))
                {
                    SRankInfoPtr pOldInfo = *rvecItSetRankInfo[i];
                    dwOldRank = distance(rsetRankInfo.begin(), rvecItSetRankInfo[i]) + 1;
                    rsetRankInfo.erase(rvecItSetRankInfo[i]);
                    rvecItSetRankInfo.erase(rvecItSetRankInfo.begin() + i);
                    bool bRet = true;
                    string strData;
                    COutArchive iar(strData);
                    UINT64 qwRoleID = 0;
                    switch(pOldInfo->GetClassType())
                    {
                        case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                            {
                                SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pOldInfo);
                                qwRoleID = pInfo->qwRoleID;
                                iar << *pInfo;
                            }
                            break;
                        case eType_SRRFormationInfo: //类型：SRRFormationInfo
                            {
                                SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pOldInfo);
                                qwRoleID = pInfo->qwRoleID;
                                iar << *pInfo;
                            }
                            break;
                        case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                            {
                                SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pOldInfo);
                                qwRoleID = pInfo->qwRoleID;
                                iar << *pInfo;
                            }
                            break;
                        case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                            {
                                SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pOldInfo);
                                qwRoleID = pInfo->qwRoleID;
                                iar << *pInfo;
                            }
                            break;
                        case eType_SRRLevelInfo: //类型：SRRLevelInfo
                            {
                                SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(pOldInfo);
                                qwRoleID = pInfo->qwRoleID;
                                iar << *pInfo;
                            }
                            break;
                        default:
                            bRet = false;

                    }
                    if (bRet)
                        g_Center2DBCommC.Send_RankDataUpdate(qwRoleID, eType, eOpDel, strData);
                    continue;
                }
                else
                    ++i;
            }
        }
        auto pairRet = rsetRankInfo.insert(pBaseInfo);
        UINT32 dwNewRank = distance(rsetRankInfo.begin(), pairRet.first) + 1;
        rmapRankIndex[qwInstID].push_back(pairRet.first);
        if (dwOldRank != dwNewRank)
        {
            //LOG_WRN << "dwOldRank = " << dwOldRank << ", dwNewRank = " << dwNewRank << ".";
            UINT64 qwRoleID = qwInstID;
            EventType eEventType = eEventType_Max;
            switch (pBaseInfo->GetClassType())
            {
                case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                    {
                        SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
                        eEventType = eEventType_RankFightingPowerChanging;
                    }
                    break;
                case eType_SRRFormationInfo: //类型：SRRFormationInfo
                    {
                        SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfo);
                        eEventType = eEventType_RankPetChanging;
                    }
                    break;
                case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                    {
                        SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfo);
                        qwRoleID = pInfo->qwRoleID;
                        //LOG_WRN << "qwRoleID = " << qwRoleID << ", pInfo->qwRoleID = " << pInfo->qwRoleID << ".";
                        eEventType = eEventType_RankFighterChanging;
                    }
                    break;
                case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                    {
                        SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfo);
                        eEventType = eEventType_RankTrumpChanging;
                    }
                    break;
                default:
                    break;
            }
            if (eEventType != eEventType_Max)
            {
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
                TVecINT32 vecParam2;
                vecParam2.push_back(dwNewRank);
                if (pUser && (pUser->IsOnline()))
                {
                    pUser->OnEvent(eEventType, vecParam2);
                }
                else
                {
                    CUser::AddOffLineEvent(qwRoleID, eEventType,vecParam2);
                }

            }

        }

        bool bInited = false;
        string strData;
        COutArchive iar(strData);
        switch (eType)
        {
            case eRTBattlePoint:
                {
                    SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
                    iar << *pInfo;
                    bInited = true;
                }
                break;
            case eRTLevel:
                {
                    SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfo);
                    iar << *pInfo;
                    bInited = true;
                }
                break;
            case eRTFormation:
                {
                    SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfo);
                    iar << *pInfo;
                    bInited = true;
                }
                break;
            case eRTHeroFighter:
                {
                    SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfo);
                    iar << *pInfo;
                    bInited = true;
                }
                break;
            case eRTTrump:
                {
                    SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfo);
                    iar << *pInfo;
                    bInited = true;
                }
                break;
            case eRTArena:
                {
                    SRRArenaInfoPtr pInfo = dynamic_pointer_cast<SRRArenaInfo>(pBaseInfo);
                    iar << *pInfo;
                    bInited = true;
                }
                break;
            case eRTGuildBattle:
            default:
                bInited = false;
        }
        if (bInited)
            g_Center2DBCommC.Send_RankDataUpdate(qwInstID, eType, eOpUpdate, strData);
    }
}		// -----  end of function UpdateRankInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  DeleteRankInfo
//  Description:  删除排行榜数据
// =====================================================================================
void CRankMgr::DeleteRankInfo (UINT64 qwInstID, ERankType eType, const TVecRankInfo& vecRankInfo)
{
    for (auto& rInfo : vecRankInfo)
    {
        UINT64 qwRoleID = 0;
        string strData;
        COutArchive iar(strData);
        bool bDB = false;
        switch(rInfo->GetClassType())
        {
            case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                {
                    SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(rInfo);
                    qwRoleID = pInfo->qwRoleID;
                    iar << *pInfo;
                    bDB = true;
                }
                break;
            case eType_SRRLevelInfo: //类型：SRRLevelInfo
                {
                    SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(rInfo);
                    qwRoleID = pInfo->qwRoleID;
                    iar << *pInfo;
                    bDB = true;
                }
                break;
            case eType_SRRFormationInfo: //类型：SRRFormationInfo
                {
                    SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(rInfo);
                    qwRoleID = pInfo->qwRoleID;
                    iar << *pInfo;
                    bDB = true;
                }
                break;
            case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                {
                    SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(rInfo);
                    qwRoleID = pInfo->qwRoleID;
                    iar << *pInfo;
                    bDB = true;
                }
                break;
            case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                {
                    SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(rInfo);
                    qwRoleID = pInfo->qwRoleID;
                    iar << *pInfo;
                    bDB = true;
                }
                break;
            case eType_SGRBattleInfo:
                {
                    SGRBattleInfoPtr pInfo = dynamic_pointer_cast<SGRBattleInfo>(rInfo);
                    qwRoleID = pInfo->qwGuildID;
                    bDB = false;
                }
                break;
            default:
                break;
        }
        if (qwRoleID)
        {
            MapRankIndex& rmapRankIndex = _mapRankIndex[eType];
            auto it = rmapRankIndex.find(qwRoleID);
            if (it != rmapRankIndex.end())
            {
                VecItSetRank& rvecItSetRankInfo = it->second;
                for (size_t i = 0; i < rvecItSetRankInfo.size();)
                {
                    if (IsSameRankInfo(rInfo, *rvecItSetRankInfo[i]))
                    {
                        SetRankInfo& rsetRankInfo = _mapRankInfo[eType];
                        rsetRankInfo.erase(rvecItSetRankInfo[i]);
                        rvecItSetRankInfo.erase(rvecItSetRankInfo.begin() + i);
                        if (bDB)
                            g_Center2DBCommC.Send_RankDataUpdate(qwRoleID, eType, eOpDel, strData);
                    }
                    else
                        ++i;
                }
            }
        }
    }
}		// -----  end of function DeleteRankInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAdoreCount
//  Description:  获取被崇拜数
// =====================================================================================
UINT32 CRankMgr::GetAdoreCount(UINT64 qwRoleID)
{
    auto it = _mapAdore.find(qwRoleID);
    if (it == _mapAdore.end())
        return 0;
    return it->second;
}		// -----  end of function GetAdoreCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CheckAdorePlayer
//  Description:  检查是否崇拜过该人
// =====================================================================================
bool CRankMgr::CheckAdorePlayer(UINT64 qwOpID, UINT64 qwRoleID) const
{
    auto it2 = _mapAdoreIndex.find(qwOpID);
    if (it2 == _mapAdoreIndex.end())
        return true;
    auto it = it2->second.find(qwRoleID);
    if (it == it2->second.end())
        return true;
    else
        return false;
}		// -----  end of function CheckAdorePlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetArenaInfo
//  Description:  获取斗剑榜信息
// =====================================================================================
void CRankMgr::GetArenaInfo( UINT64 qwRoleID, UINT32 dwIndex, UINT32 dwCount,
        UINT32& dwMaxCount, UINT32& dwCurIndex, UINT32& dwSelfRank, 
        TVecRankInfo& rvecRankInfo, TVecRankInfo& rvecSelfRankInfo) const
{
    TVecArenaRank2Client vecRankInfo;
    SArenaRank2Client stClient;
    bool bRet = CArenaManager::GetRankInfo(qwRoleID, dwIndex, dwCount, dwMaxCount, dwCurIndex, dwSelfRank, vecRankInfo, stClient);
    for (auto& sInfo : vecRankInfo)
    {
        SRRArenaInfoPtr pInfo (new SRRArenaInfo);
        pInfo->dwValue          = sInfo.dwFighterPower;
        pInfo->qwRoleID         = sInfo.qwRoleID;
        pInfo->strName          = sInfo.stFighter.strName;
        pInfo->dwBattlePoint    = sInfo.dwFighterPower;
        pInfo->byQuality        = sInfo.byQuality;
        pInfo->byVIPLevel       = sInfo.byVIPLevel;
        pInfo->vecPlatforms     = CUserMgr::GetPlatformParam(sInfo.qwRoleID);

        // 机器人要特殊处理一下
        if (CArenaManager::IsRobot(sInfo.qwRoleID,true))
            pInfo->wPlayerFighterID = sInfo.qwRoleID;
        else
            pInfo->wPlayerFighterID = GetDefaultFighterID(sInfo.stFighter.stAppear.eJob, sInfo.stFighter.stAppear.eSex);
        CGuildUserMgr::Instance().GetGuildName(sInfo.qwRoleID, pInfo->strGuildName);
        rvecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    }
    if (bRet)
    {
        SRRArenaInfoPtr pInfo (new SRRArenaInfo);
        pInfo->dwValue          = stClient.dwFighterPower;
        pInfo->qwRoleID         = stClient.qwRoleID;
        pInfo->strName          = stClient.stFighter.strName;
        pInfo->dwBattlePoint    = stClient.dwFighterPower;
        pInfo->byQuality        = stClient.byQuality;
        pInfo->byVIPLevel       = stClient.byVIPLevel;
        pInfo->vecPlatforms     = CUserMgr::GetPlatformParam(stClient.qwRoleID);
        pInfo->wPlayerFighterID = GetDefaultFighterID(stClient.stFighter.stAppear.eJob, stClient.stFighter.stAppear.eSex);
        CGuildUserMgr::Instance().GetGuildName(stClient.qwRoleID, pInfo->strGuildName);
        rvecSelfRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    }
}		// -----  end of function GetArenaInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AdorePlayer
//  Description:  崇拜指定玩家
// =====================================================================================
bool CRankMgr::AdorePlayer(UINT64 qwOpID, UINT64 qwRoleID, ERankResult& eResult, UINT32& dwCount)
{
    auto it = _mapAdoreIndex[qwOpID].find(qwRoleID);
    if (it == _mapAdoreIndex[qwOpID].end())
    {
        eResult = eRRSuccess;
        dwCount = ++_mapAdore[qwRoleID];
        _mapAdoreIndex[qwOpID].insert(qwRoleID);

        string strData;
        COutArchive iar(strData);
        SDBAdoreInfo sDBInfo;
        sDBInfo.qwRoleID = qwRoleID;
        sDBInfo.dwCount = _mapAdore[qwRoleID];
        sDBInfo.dwUpdateTime = Time::Now();
        iar << sDBInfo;
        g_Center2DBCommC.Send_AdoreDataUpdate(qwRoleID, eOpUpdate, strData);

        CUserPtr pUser = CUserMgr::GetUserByUserID(qwOpID);
        TVecINT32 vecParam2;
        vecParam2.push_back(dwCount);
        if (pUser && pUser->IsOnLine())
        {
            pUser->OnEvent(eEventType_PlayerProstrate, vecParam2);
        }
        else
        {
            CUser::AddOffLineEvent(qwOpID, eEventType_PlayerProstrate,vecParam2);
        }

        CUserPtr pUser2 = CUserMgr::GetUserByUserID(qwRoleID);
        vecParam2.clear(); 
        vecParam2.push_back(_mapAdore[qwRoleID]);
        if (pUser2 && pUser2->IsOnLine())
        {
            pUser2->OnEvent(eEventType_ReceiveProstrate, vecParam2);
        }
        else
        {
            CUser::AddOffLineEvent(qwRoleID, eEventType_ReceiveProstrate,vecParam2);
        }
        return true;
    }
    else
        return false;
}		// -----  end of function AdorePlayer  ----- //

void CRankMgr::InitRankFromDB (const TVecRankInfo& vecRankInfo)
{
    if (vecRankInfo.empty())
    {
        LOG_CRI << "vecRankInfo.empty().";
        return;
    }
    for (auto pBaseInfo : vecRankInfo)
    {
        ERankType eType = eRTNone;
        UINT64 qwInstID = 0;
        switch(pBaseInfo->GetClassType())
        {
            case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                {
                    SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
                    qwInstID = pInfo->qwRoleID;
                    eType = eRTBattlePoint;
                }
                break;
            case eType_SRRFormationInfo: //类型：SRRFormationInfo
                {
                    SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfo);
                    qwInstID = pInfo->qwRoleID;
                    eType = eRTFormation;
                }
                break;
            case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                {
                    SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfo);
                    qwInstID = pInfo->qwRoleID;
                    eType = eRTHeroFighter;
                }
                break;
            case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                {
                    SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfo);
                    qwInstID = pInfo->qwRoleID;
                    eType = eRTTrump;
                }
                break;
            case eType_SRRArenaInfo: //类型：SRRArenaInfo
                {
                    SRRArenaInfoPtr pInfo = dynamic_pointer_cast<SRRArenaInfo>(pBaseInfo);
                    qwInstID = pInfo->qwRoleID;
                    eType = eRTArena;
                }
                break;
            case eType_SRRLevelInfo: //类型：SRRLevelInfo
                {
                    SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfo);
                    qwInstID = pInfo->qwRoleID;
                    eType = eRTLevel;
                }
                break;
            default:
                break;
        }
        if (eType == eRTNone)
        {
            LOG_WRN << "Type error: " << static_cast<UINT32>((pBaseInfo)->GetClassType()) << ",";
            continue;
        }
        SetRankInfo& rsetRankInfo = _mapRankInfo[eType];
        MapRankIndex& rmapRankIndex = _mapRankIndex[eType];
        auto pairRet = rsetRankInfo.insert(pBaseInfo);
        if (!pairRet.second)
            LOG_WRN << "RankInfo insert error.";
        (rmapRankIndex[qwInstID]).push_back(pairRet.first);
    }
}

void CRankMgr::InitAdoreFromDB(const TVecDBAdoreInfo& vecAdoreInfo)
{
    UINT32 dwTime = Time::TheWeek();
    for (auto& rInfo : vecAdoreInfo)
    {
        if (rInfo.dwUpdateTime <= dwTime)
            continue;
        _mapAdore[rInfo.qwRoleID] = rInfo.dwCount;
    }
}

void CRankMgr::UpdateRankGuildName(UINT64 qwRoleID, const string& strGuildName)
{
    for (auto& kv : _mapRankIndex)
    {
        auto it2 = kv.second.find(qwRoleID);
        if (it2!= kv.second.end())
        {
            const VecItSetRank& rvecItSetRankInfo = it2->second;
            for (auto& it : rvecItSetRankInfo)
            {
                bool bInited = false;
                string strData;
                COutArchive iar(strData);
                SRankInfoPtr pBaseInfo = *it;
                switch(pBaseInfo->GetClassType())
                {
                    case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                        {
                            SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
                            pInfo->strGuildName = strGuildName;
                            iar << *pInfo;
                            bInited = true;
                        }
                        break;
                    case eType_SRRFormationInfo: //类型：SRRFormationInfo
                        {
                            SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfo);
                            pInfo->strGuildName = strGuildName;
                            iar << *pInfo;
                            bInited = true;
                        }
                        break;
                    case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                        {
                            SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfo);
                            pInfo->strGuildName = strGuildName;
                            iar << *pInfo;
                            bInited = true;
                        }
                        break;
                    case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                        {
                            SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfo);
                            pInfo->strGuildName = strGuildName;
                            iar << *pInfo;
                            bInited = true;
                        }
                        break;
                    default:
                        break;
                }
                if (bInited)
                    g_Center2DBCommC.Send_RankDataUpdate(qwRoleID, kv.first, eOpUpdate, strData);
            }
        }

    }
}

void CRankMgr::UpdatePlatform()
{
    if (_bPlatFromInited)
        return;
    _bPlatFromInited = true;
    for (UINT8 byIndex = eRTRoleRankBegin; byIndex < eRTRoleRankEnd; ++byIndex)
    {
        ERankType eType = static_cast<ERankType>(byIndex);
        auto it = _mapRankInfo.find(eType);
        if (it == _mapRankInfo.end())
            continue;
        SetRankInfo& rsetRankInfo = it->second;
        for (auto rBaseInfo : rsetRankInfo)
        {
            string strData;
            COutArchive iar(strData);
            switch(rBaseInfo->GetClassType())
            {
                case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                case eType_SRRLevelInfo: //类型：SRRLevelInfo
                case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                case eType_SRRFormationInfo: //类型：SRRFormationInfo
                    {
                        SRoleRankInfoPtr pInfo = dynamic_pointer_cast<SRoleRankInfo>(rBaseInfo);
                        pInfo->vecPlatforms = CUserMgr::GetPlatformParam(pInfo->qwRoleID);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void CRankMgr::ClearSurplusRank()
{
    for (UINT8 byIndex = eRTRoleRankBegin; byIndex < eRTRoleRankEnd; ++byIndex)
    {
        ERankType eType = static_cast<ERankType>(byIndex);
        auto it = _mapRankInfo.find(eType);
        if (it == _mapRankInfo.end())
            continue;
        SetRankInfo& rsetRankInfo = it->second;
        if (rsetRankInfo.size() <= MAX_RANK_COUNT)
            continue;
        auto it2 = rsetRankInfo.begin();
        advance(it2, MAX_RANK_COUNT);
        while(it2 != rsetRankInfo.end())
        {
            UINT64 qwRoleID = 0;
            string strData;
            COutArchive iar(strData);
            SRankInfoPtr pBaseInfo = *it2;
            switch(pBaseInfo->GetClassType())
            {
                case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                    {
                        SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
                        qwRoleID = pInfo->qwRoleID;
                        iar << *pInfo;
                    }
                    break;
                case eType_SRRFormationInfo: //类型：SRRFormationInfo
                    {
                        SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfo);
                        qwRoleID = pInfo->qwRoleID;
                        iar << *pInfo;
                    }
                    break;
                case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                    {
                        SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfo);
                        qwRoleID = pInfo->qwRoleID;
                        iar << *pInfo;
                    }
                    break;
                case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                    {
                        SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfo);
                        qwRoleID = pInfo->qwRoleID;
                        iar << *pInfo;
                    }
                    break;
                case eType_SRRLevelInfo: //类型：SRRLevelInfo
                    {
                        SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfo);
                        qwRoleID = pInfo->qwRoleID;
                        iar << *pInfo;
                    }
                    break;
                default:
                    break;
            }
            if (qwRoleID)
            {
                MapRankIndex& rmapRankIndex = _mapRankIndex[eType];
                auto it = rmapRankIndex.find(qwRoleID);
                if (it != rmapRankIndex.end())
                {
                    VecItSetRank& rvecItSetRankInfo = it->second;
                    for (size_t i = 0; i < rvecItSetRankInfo.size();)
                    {
                        if (IsSameRankInfo(pBaseInfo, *rvecItSetRankInfo[i]))
                        {
                            rvecItSetRankInfo.erase(rvecItSetRankInfo.begin() + i);
                            g_Center2DBCommC.Send_RankDataUpdate(qwRoleID, eType, eOpDel, strData);
                        }
                        else
                            ++i;
                    }
                }
            }
            auto it3 = it2;
            ++it2;
            rsetRankInfo.erase(it3);
        }
    }
}

void CRankMgr::LoadFromDB()
{
    g_Center2DBCommC.Send_GetRankInfo();
    g_Center2DBCommC.Send_GetAdoreInfo();
}

void CRankMgr::TimeCheck(time_t tNow)
{
    if (tNow > _dwNextVoterTime)
    {
        _mapAdoreIndex.clear();
        _dwNextVoterTime = Time::TheDay(1);
    }
    if (tNow > _dwNextAdoreTime)
    {
        _dwNextAdoreTime = Time::TheWeek(1);
        _mapAdore.clear();
    }
}

bool CRankMgr::IsSameRankInfo(SRankInfoPtr pBaseInfoA, SRankInfoPtr pBaseInfoB) const
{
    bool bSame = false;;
    if (pBaseInfoA && pBaseInfoB && pBaseInfoA->GetClassType() == pBaseInfoB->GetClassType())
    {
        switch(pBaseInfoA->GetClassType())
        {
            case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                {
                    SRRBattlePointInfoPtr pInfoA = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfoA);
                    SRRBattlePointInfoPtr pInfoB = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfoB);
                    if (pInfoA->qwRoleID == pInfoB->qwRoleID)
                        bSame = true;
                }
                break;
            case eType_SRRFormationInfo: //类型：SRRFormationInfo
                {
                    SRRFormationInfoPtr pInfoA = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfoA);
                    SRRFormationInfoPtr pInfoB = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfoB);
                    if (pInfoA->qwRoleID == pInfoB->qwRoleID)
                        bSame = true;
                }
                break;
            case eType_SRRLevelInfo: //类型：SRRLevelInfo
                {
                    SRRLevelInfoPtr pInfoA = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfoA);
                    SRRLevelInfoPtr pInfoB = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfoB);
                    if (pInfoA->qwRoleID == pInfoB->qwRoleID)
                        bSame = true;
                }
                break;
            case eType_SRRHeroFighterInfo: //类型：SRRHeroFighterInfo
                {
                    SRRHeroFighterInfoPtr pInfoA = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfoA);
                    SRRHeroFighterInfoPtr pInfoB = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfoB);
                    if (pInfoA->qwRoleID == pInfoB->qwRoleID)
                        bSame = true;
                }
                break;
            case eType_SRRTrumpInfo: //类型：SRRTrumpInfo
                {
                    SRRTrumpInfoPtr pInfoA = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfoA);
                    SRRTrumpInfoPtr pInfoB = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfoB);
                    if (pInfoA->qwRoleID == pInfoB->qwRoleID)
                        bSame = true;
                }
                break;
            case eType_SGRBattleInfo: //类型：SGRBattleInfo
                {
                    SGRBattleInfoPtr pInfoA = dynamic_pointer_cast<SGRBattleInfo>(pBaseInfoA);
                    SGRBattleInfoPtr pInfoB = dynamic_pointer_cast<SGRBattleInfo>(pBaseInfoB);
                    if (pInfoA->qwGuildID == pInfoB->qwGuildID)
                        bSame = true;
                }
            default:
                break;
        }
    }
    return bSame;
}

// ===  FUNCTION  ======================================================================
//         Name:  GetArenaHeadInfo
//  Description:  获取帮派战的魁首信息
// =====================================================================================
void CRankMgr::GetArenaHeadInfo(TVecRankInfo& rvecRankInfo) const
{
    TVecArenaRank2Client vecRankInfo;
    SArenaRank2Client stClient;
    UINT32 dwCurIndex;
    UINT32 dwMaxCount;
    UINT32 dwSelfRank;
    CArenaManager::GetRankInfo(0, 0, 1, dwMaxCount, dwCurIndex, dwSelfRank, vecRankInfo, stClient);
    for (const auto& rInfo : vecRankInfo)
    {
        SRoleHeadInfoPtr pHeadInfo (new SRoleHeadInfo);
        pHeadInfo->dwValue          = (rInfo).dwFighterPower;
        pHeadInfo->eType            = eRTArena;
        pHeadInfo->qwRoleID         = (rInfo).qwRoleID;
        pHeadInfo->strName          = (rInfo).stFighter.strName;
        pHeadInfo->wPlayerFighterID = GetDefaultFighterID(rInfo.stFighter.stAppear.eJob, rInfo.stFighter.stAppear.eSex);
        pHeadInfo->byQuality        = (rInfo).byQuality;
        rvecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pHeadInfo));
    }

}		// -----  end of function GetGuildBattleHeadInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildBattleHeadInfo
//  Description:  获取帮派战的魁首信息
// =====================================================================================
void CRankMgr::GetGuildBattleHeadInfo(TVecRankInfo& rvecRankInfo) const
{
    ERankType eType = eRTGuildBattle;
    auto it = _mapRankInfo.find(eType);
    if (it == _mapRankInfo.end())
        return;
    if (it->second.empty())
        return;
    SGuildRankInfoPtr pGuildRankInfo = dynamic_pointer_cast<SGuildRankInfo>(*(it->second.begin()));
    SRoleHeadInfoPtr pHeadInfo (new SRoleHeadInfo);

    pHeadInfo->dwValue          = pGuildRankInfo->dwValue;
    pHeadInfo->eType            = eType;
    pHeadInfo->qwRoleID         = pGuildRankInfo->qwRoleID;
    pHeadInfo->strName          = pGuildRankInfo->strName;
    pHeadInfo->wPlayerFighterID = pGuildRankInfo->wPlayerFighterID;
    pHeadInfo->byQuality        = pGuildRankInfo->byQuality;
    pHeadInfo->strGuildName     = pGuildRankInfo->strGuildName;
    rvecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pHeadInfo));
}		// -----  end of function GetGuildBattleHeadInfo  ----- //

bool CRankMgr::GetGuildRankByLevel(UINT32 dwIndex,UINT32 dwCount,TVecUINT64& vecGuildID)
{
    std::set<SGuildRankByLevel> rsetRankInfo;
    if(!CGuildMgr::Instance().GetGuildLevelRank(rsetRankInfo))
    {
        LOG_WRN << " GetGuildLevelRank error";
        return false;
    }
    if(rsetRankInfo.size() == 0)
    {
        LOG_WRN << " rsetRankInfo size is 0";
        return false;
    }
    if (rsetRankInfo.size() < dwIndex)
        dwIndex = 0;
    else
    {
        if (!dwIndex)
            dwIndex = 1;
        if (!dwCount)
            dwCount = 1;
        auto it3 = rsetRankInfo.begin();
        advance(it3, dwIndex - 1);
        for (;dwCount && it3 != rsetRankInfo.end(); ++it3, --dwCount)
        {
            vecGuildID.push_back(it3->qwGuildID);
        }
    }
    return true;
}

bool CRankMgr::SendMailForGuild(UINT32& wHigh,UINT16& wLow,const TVecItemConfigPtr& vecItem,UINT16& wMailID,UINT16& wContentID)
{
    TVecUINT64 vecGuildID;
    TVecUINT64 vecRoleID;
    if(wHigh > wLow || wHigh < 1)
    {
        LOG_CRI << " wHigh > wLow Error";
        return false;
    }
    UINT32 dwCount = wLow - wHigh + 1;
    LOG_WRN << "GuildRank SendMail dwCount = " <<dwCount;
    SItemAttachmentPtr pItem(new SItemAttachment());
    LOG_CRI << "VecItem.size() = " << vecItem.size();
    for(auto oIt=vecItem.begin(); oIt!=vecItem.end(); ++oIt)
    {
        SMailItemInfo stAttach;
        stAttach.wItemID = (*oIt)->dwItemID;
        stAttach.wCount = (*oIt)->dwCount;
        stAttach.eBindType = NItemProt::eBindGet;
        pItem->vecItemInfo.push_back(stAttach);
    }
    if(!GetGuildRankByLevel(wHigh, dwCount, vecGuildID) || vecGuildID.size() == 0)
    {
        LOG_INF << " GetGuildRank error.size("<<vecGuildID.size()<<").";
        return false;
    }
    UINT32 dwRank = wHigh - 1;

    for(auto &it : vecGuildID)
    {
       CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(it); 
       if(pGuild == NULL)
       {
           LOG_WRN << "pGuild is NULL.";
           return false;
       }
       pGuild->GetAllUserID(vecRoleID);
       if(vecRoleID.size() == 0)
       {
           LOG_WRN << " Guild vecRoleID size 0.";
           return false;
       }
       dwRank ++;
       LOG_WRN <<"qwGuildID(" <<it<<"),Rank("<<dwRank <<" SendMail Begin.............";
       for(auto i = vecRoleID.begin(); i != vecRoleID.end(); ++i)
       {
            if(_setRoleID.count(*i))
            {
                 LOG_WRN <<" qwRoleID=" << *i<<" SendMail twice.";
                 continue;
            }
            CSystemMail sysMail;
            sysMail.AddTarget(*i);
            sysMail.SetSender("系统");
            sysMail.SetBody(SysMailSendTxt(wContentID, BuildStrVec(dwRank)));
            string strTile;
            CSystemMail::GetSysMailBody(wMailID,strTile);
            sysMail.SetSubject(strTile);
            sysMail.AddItemInfo(pItem->vecItemInfo);
            LOG_WRN <<" qwRoleID (" <<*i<<") Recv Mail.";
            sysMail.Send();
            _setRoleID.insert(*i);
       }
       LOG_WRN <<"qwGuildID(" <<it<<"),Rank("<<dwRank <<" SendMail Begin.............";
    }
    return true;
}



 
bool CRankMgr::SendMailForArena(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID)
{
    TVecUINT64 vecRoleID;
    UINT32 dwCount = wLow - wHigh + 1;
    if(wHigh > wLow)
    {
        LOG_CRI << " wHigh > wLow Error";
        return false;
    }
    LOG_WRN << "GuildRank SendMail dwCount = " <<dwCount;
    TVecArenaRank2Client vecRankInfo;
    SArenaRank2Client stClient;
    UINT32 dwCurIndex;
    UINT32 dwMaxCount;
    UINT32 dwSelfRank;
    CArenaManager::GetRankInfo(0, wHigh, dwCount, dwMaxCount, dwCurIndex, dwSelfRank, vecRankInfo, stClient);
    if(vecRankInfo.size() == 0)
    {
        LOG_WRN << " vecRankInfo size is 0";
        return false;
    }
    for(auto &oIt : vecRankInfo)
    {
        if(CArenaManager::IsRobot(oIt.qwRoleID,true))
            continue;
        LOG_WRN << " qwRoleID(" << oIt.qwRoleID<<") need Mail.";
        vecRoleID.push_back(oIt.qwRoleID);
    }
    SItemAttachmentPtr pItem(new SItemAttachment());
    for(auto oIt=vecItem.begin(); oIt!=vecItem.end(); ++oIt)
    {
        SMailItemInfo stAttach;
        stAttach.wItemID = (*oIt)->dwItemID;
        stAttach.wCount = (*oIt)->dwCount;
        stAttach.eBindType = NItemProt::eBindGet;
        pItem->vecItemInfo.push_back(stAttach);
    }
    for(auto it = vecRoleID.begin(); it != vecRoleID.end(); ++it, ++wHigh)
    { 
        CSystemMail sysMail;
        sysMail.AddTarget(*it);
        sysMail.SetSender("系统");
        sysMail.SetBody(SysMailSendTxt(wContentID, BuildStrVec(wHigh)));
        string strTile;
        CSystemMail::GetSysMailBody(wMailID,strTile);
        sysMail.SetSubject(strTile);
        sysMail.AddItemInfo(pItem->vecItemInfo);

        sysMail.Send();
    }
    return true;
}

bool CRankMgr::SendMail(ERankType eType,UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID)
{
    TVecUINT64 vecRoleID;
    LOG_CRI << "wHigh = " << wHigh<<"| wLow = " <<wLow;
    if(wHigh > wLow)
    {
        LOG_CRI << " wHigh > wLow Error";
        return false;
    }
    UINT32 dwCount = wLow - wHigh + 1;
    LOG_CRI << "RankMgr SendMail dwCount = " <<dwCount;
    GetRankRoleID(eType, wHigh, dwCount, vecRoleID);
    SItemAttachmentPtr pItem(new SItemAttachment());
    for(auto oIt=vecItem.begin(); oIt!=vecItem.end(); ++oIt)
    {
        SMailItemInfo stAttach;
        stAttach.wItemID = (*oIt)->dwItemID;
        stAttach.wCount = (*oIt)->dwCount;
        stAttach.eBindType = NItemProt::eBindGet;
        pItem->vecItemInfo.push_back(stAttach);
    }
    for(auto it = vecRoleID.begin(); it != vecRoleID.end(); ++it, ++wHigh)
    { 
        CSystemMail sysMail;
        sysMail.AddTarget(*it);
        sysMail.SetSender("系统");
        sysMail.SetBody(SysMailSendTxt(wContentID, BuildStrVec(wHigh)));
        string strTile;
        CSystemMail::GetSysMailBody(wMailID,strTile);
        sysMail.SetSubject(strTile);
        sysMail.AddItemInfo(pItem->vecItemInfo);

        sysMail.Send();
    }
    return true;
}

UINT32 CRankMgr::GetPoint(UINT64 qwRoleID)
{
    UINT32 dwPoint = 0;
    auto oIt = _mapRankIndex.find(eRTBattlePoint);
    if(oIt == _mapRankIndex.end())
    {
        LOG_INF << " _mapRankIndex error";
        return false;
    }
    const MapRankIndex& rmapRankIndex = oIt->second;
    auto it = rmapRankIndex.find(qwRoleID); 
    if(it == rmapRankIndex.end())
    {
        LOG_INF << "VecItSetRank error";
        return false;
    }
    const VecItSetRank& rvecItSetRankInfo = it->second;
    if (rvecItSetRankInfo.empty())
    {
        LOG_INF << "VecItSetRank empty";
        return false;
    }
    SRankInfoPtr pBaseInfo = *(rvecItSetRankInfo[0]);
    switch(pBaseInfo->GetClassType())
    {
        case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
            {
                SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
                dwPoint = pInfo->dwBattlePoint;
            }
            break;
        default:
            break;
    }
    return dwPoint;
}

UINT32 CRankMgr::GetCount(UINT32 dwPoint)
{
    UINT32 dwTmp = 0;
    UINT32 dwCount = 0;
    SRRBattlePointInfoPtr pInfo;
    auto it1 = _mapRankInfo.find(eRTBattlePoint);
    if(it1 == _mapRankInfo.end())
    {
//        LOG_INF << " mapRankinfo error";
        return 0;
    }
    const SetRankInfo& rsetRankInfo = it1->second;
    for(auto &oIt : rsetRankInfo)
    {
        SRankInfoPtr pBaseInfo = oIt;
        switch(pBaseInfo->GetClassType())
        {
            case eType_SRRBattlePointInfo: //类型：SRRBattlePointInfo
                {
                    pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
                    dwTmp = pInfo->dwBattlePoint;
                }
                break;
            default:
                break;
        }
        if(dwTmp >= dwPoint)
            dwCount ++;
        else 
            break;
    }
    return dwCount;
}

bool CRankMgr::GetPlayerInfo(UINT16 wActID,bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer,NWonderActivityProt::EWActState eActState)
{
    if(eActState == eWActState_End)
    {
        UINT16 wIndex = 1;
        SRetain sSaveInfo;
        if(bType)
            g_RetainMgr.GetRetainByType(wActID,wIndex,sSaveInfo);
        else
            g_RetainMgr.GetRetainByRoleID(qwPlayerID,wActID,sSaveInfo);
        sPlayer.dwValue1 = sSaveInfo.wType;
        sPlayer.dwValue2 = sSaveInfo.dwValue;
        sPlayer.strName = sSaveInfo.strName;
        sPlayer.eCareer = static_cast<ECareerType>(sSaveInfo.byCareer);
        sPlayer.eSex = static_cast<ESexType>(sSaveInfo.bySex);
        sPlayer.wID = sSaveInfo.wID;
        sPlayer.strName1 = sSaveInfo.strGuildName;
        return true;
    }

    UINT64 qwRoleID = qwPlayerID;
    if(bType)
    {
        TVecUINT64 vecRoleID;
        GetRankRoleID(eRTBattlePoint, 1, 1, vecRoleID);
        if(vecRoleID.size() == 0)
        {
            LOG_INF << " GetRankRoleID error";
            return false;
        }
    qwRoleID = vecRoleID.at(0);
    }else //0 表示自己，1 表示第一名
    {
        if(qwPlayerID == 0)
             return false;
    }
    auto it1 = _mapRankInfo.find(eRTBattlePoint);
    if(it1 == _mapRankInfo.end())
    {
        LOG_INF << " mapRankinfo error";
        return false;
    }
    const SetRankInfo& rsetRankInfo = it1->second;
    auto oIt = _mapRankIndex.find(eRTBattlePoint);
    if(oIt == _mapRankIndex.end())
    {
        LOG_INF << " _mapRankIndex error";
        return false;
    }
    const MapRankIndex& rmapRankIndex = oIt->second;
    auto it = rmapRankIndex.find(qwRoleID); 
    if(it == rmapRankIndex.end())
    {
        LOG_INF << "VecItSetRank error";
        return false;
    }
    const VecItSetRank& rvecItSetRankInfo = it->second;
    if (rvecItSetRankInfo.empty())
    {
        LOG_INF << "VecItSetRank empty";
        return false;
    }
    for(auto& it4 : rvecItSetRankInfo)
    {
        UINT32 dwRank = distance(rsetRankInfo.begin(), it4) + 1;
        sPlayer.dwValue1 = dwRank;
    }

    SRankInfoPtr pBaseInfo = *(rvecItSetRankInfo[0]);
    SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
    SRoleRankInfoPtr pRoleRankInfo = dynamic_pointer_cast<SRoleRankInfo>(pBaseInfo);
    sPlayer.dwValue2 = pInfo->dwBattlePoint;
    sPlayer.strName = pRoleRankInfo->strName;
    sPlayer.wID = 0;
    sPlayer.strName1 = pInfo->strGuildName;
    UINT16 wFighterID = pRoleRankInfo->wPlayerFighterID;    
    sPlayer.eCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
    UINT8 byIndex  = wFighterID % 2;
    if(byIndex)
       sPlayer.eSex = ESEX_MALE;
    else 
       sPlayer.eSex = ESEX_FEMALE;
    
    return true;
}

bool CRankMgr::SaveRoleInfoForAct(UINT16 wActID)
{
    SRetain sPlayer;

    auto it1 = _mapRankInfo.find(eRTBattlePoint);
    if(it1 == _mapRankInfo.end())
    {
        LOG_INF << " mapRankinfo error";
        return 0;
    }
    const SetRankInfo& rsetRankInfo = it1->second;
    UINT16 wRank = 1;
    for(auto &it : rsetRankInfo)
    {
        SRankInfoPtr pBaseInfo = it;
        SRRBattlePointInfoPtr pInfo = dynamic_pointer_cast<SRRBattlePointInfo>(pBaseInfo);
        
        sPlayer.qwRoleID = pInfo->qwRoleID;
        sPlayer.wActID = wActID;
        sPlayer.wType = wRank ++;

        sPlayer.dwValue = pInfo->dwBattlePoint;
        sPlayer.strName = pInfo->strName;
        UINT16 wFighterID = pInfo->wPlayerFighterID;    
        sPlayer.strGuildName = pInfo->strGuildName;
        sPlayer.wID = 0;
        sPlayer.byCareer = static_cast<UINT8>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
           sPlayer.bySex = static_cast<UINT8>(ESEX_MALE);
        else 
           sPlayer.bySex = static_cast<UINT8>(ESEX_FEMALE);
        
        g_RetainMgr.SetRetain(sPlayer);
        //第一名玩家 颁发称号2003
        if(sPlayer.wType == 1)
        {
            UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
            g_Game2CenterCommS.SendSvr_SyncTitle(&dwGameSvrIdx, 1, sPlayer.qwRoleID,2003);
        }
    }
    return true;
}

//等级榜活动
bool CRankMgr::GetPlayerInfoForLevel(UINT16 wActID,bool bType,UINT64 &qwPlayerID,SWActPlayerInfo &sPlayer,NWonderActivityProt::EWActState eActState)
{
    string s_strName1 = "NOGUILDNAME" ;
    if(eActState == eWActState_End)
    {
        UINT16 wIndex = 1;
        SRetain sSaveInfo;
        if(bType)
            g_RetainMgr.GetRetainByType(wActID,wIndex,sSaveInfo);
        else
            g_RetainMgr.GetRetainByRoleID(qwPlayerID,wActID,sSaveInfo);
        sPlayer.dwValue1 = sSaveInfo.wType;
        sPlayer.dwValue2 = sSaveInfo.dwValue;
        sPlayer.strName = sSaveInfo.strName;
        sPlayer.strName1 = sSaveInfo.strGuildName;
        sPlayer.wID = sSaveInfo.wID;
        sPlayer.eCareer = static_cast<ECareerType>(sSaveInfo.byCareer);
        sPlayer.eSex = static_cast<ESexType>(sSaveInfo.bySex);
        return true;
    }

    UINT64 qwRoleID = qwPlayerID;
    if(bType)
    {
        TVecUINT64 vecRoleID;
        GetRankRoleID(eRTLevel, 1, 1, vecRoleID);
        if(vecRoleID.size() == 0)
        {
            LOG_INF << " GetRankRoleID error";
            return false;
        }
        qwRoleID = vecRoleID.at(0);
     }else //false 表示自己，true 表示第一名
     {
        if(qwPlayerID == 0)
            return false;
     }
     auto it1 = _mapRankInfo.find(eRTLevel);
     if(it1 == _mapRankInfo.end())
     {
         LOG_INF << " mapRankinfo error";
         return false;
     }
     const SetRankInfo& rsetRankInfo = it1->second;
     auto oIt = _mapRankIndex.find(eRTLevel);
     if(oIt == _mapRankIndex.end())
     {
          LOG_INF << " _mapRankIndex error";
          return false;
     }
     const MapRankIndex& rmapRankIndex = oIt->second;
     auto it = rmapRankIndex.find(qwRoleID); 
     if(it == rmapRankIndex.end())
     {
          LOG_INF << "VecItSetRank error";
          return false;
     }
     const VecItSetRank& rvecItSetRankInfo = it->second;
     if (rvecItSetRankInfo.empty())
     {
         LOG_INF << "VecItSetRank empty";
         return false;
     }
     for(auto& it4 : rvecItSetRankInfo)
     {
          UINT32 dwRank = distance(rsetRankInfo.begin(), it4) + 1;
          sPlayer.dwValue1 = dwRank;
     }

     SRankInfoPtr pBaseInfo = *(rvecItSetRankInfo[0]);
     SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfo);
     SRoleRankInfoPtr pRoleRankInfo = dynamic_pointer_cast<SRoleRankInfo>(pBaseInfo);
     sPlayer.dwValue2 = static_cast<UINT32>(pInfo->wLevel);

     sPlayer.strName = pRoleRankInfo->strName;
     sPlayer.strName1 = s_strName1;
     sPlayer.wID = 0;
     UINT16 wFighterID = pRoleRankInfo->wPlayerFighterID;    
     sPlayer.eCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
     UINT8 byIndex  = wFighterID % 2;
     if(byIndex)
        sPlayer.eSex = ESEX_MALE;
     else 
        sPlayer.eSex = ESEX_FEMALE;
    return true;
}

//取等级排行榜上 第一名的等级(Q养成计划中使用)
UINT16 CRankMgr::GetFirstLevel()
{
    auto it1 = _mapRankInfo.find(eRTLevel);
    if(it1 == _mapRankInfo.end())
    {
        LOG_INF << " mapRankinfo error";
        return 0;
    }
    const SetRankInfo& rsetRankInfo = it1->second;
    if(rsetRankInfo.size() == 0)
    {
        LOG_INF << "rsetRankInfo Size 0";
        return 0;
    }
    SRankInfoPtr pBaseInfo = *(rsetRankInfo.begin());
    SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfo);
    return pInfo->wLevel;
}

bool CRankMgr::SaveRoleInfoForLevel(UINT16 wActID)
{
    SRetain sPlayer;

    auto it1 = _mapRankInfo.find(eRTLevel);
    if(it1 == _mapRankInfo.end())
    {
        LOG_INF << " mapRankinfo error";
        return 0;
    }
    const SetRankInfo& rsetRankInfo = it1->second;
    UINT16 wRank = 1;
    for(auto &it : rsetRankInfo)
    {
        SRankInfoPtr pBaseInfo = it;
        SRRLevelInfoPtr pInfo = dynamic_pointer_cast<SRRLevelInfo>(pBaseInfo);
        
        sPlayer.qwRoleID = pInfo->qwRoleID;
        sPlayer.wActID = wActID;
        sPlayer.wType = wRank ++;
        sPlayer.dwValue = static_cast<UINT32>(pInfo->wLevel);
        sPlayer.strName = pInfo->strName;
        sPlayer.strGuildName = "NOGUILDNAME";
        sPlayer.wID = 0;
        UINT16 wFighterID = pInfo->wPlayerFighterID;    
        sPlayer.byCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
            sPlayer.bySex = static_cast<UINT8>(ESEX_MALE);
        else 
            sPlayer.bySex = static_cast<UINT8>(ESEX_FEMALE);
        
        g_RetainMgr.SetRetain(sPlayer);
        //第一名玩家 颁发称号2002
        if(sPlayer.wType == 1)
        {
            UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
            g_Game2CenterCommS.SendSvr_SyncTitle(&dwGameSvrIdx, 1, sPlayer.qwRoleID,2002);
        }
    }
    return true;
}

//全服散仙榜活动
bool CRankMgr::GetPlayerInfoForFighter(UINT16 wActID,bool bType,UINT64& qwPlayerID,SWActPlayerInfo& sPlayer,NWonderActivityProt::EWActState eType)
{
    if(eType == eWActState_End)
    {
        UINT16 wIndex = 1;
        SRetain sSaveInfo;
        if(bType)
            g_RetainMgr.GetRetainByType(wActID,wIndex,sSaveInfo);
        else
            g_RetainMgr.GetRetainByRoleID(qwPlayerID,wActID,sSaveInfo);
        sPlayer.dwValue1 = sSaveInfo.wType;
        sPlayer.dwValue2 = sSaveInfo.dwValue;
        sPlayer.wID = sSaveInfo.wID;
        sPlayer.strName1 = sSaveInfo.strGuildName;
        sPlayer.strName = sSaveInfo.strName;
        sPlayer.eCareer = static_cast<ECareerType>(sSaveInfo.byCareer);
        sPlayer.eSex = static_cast<ESexType>(sSaveInfo.bySex);
        return true;
    }

    UINT64 qwRoleID = qwPlayerID;
    if(bType)
    {
        TVecUINT64 vecRoleID;
        GetRankRoleID(eRTHeroFighter, 1, 1, vecRoleID);
        if(vecRoleID.size() == 0)
        {
            LOG_INF << " GetRankRoleID error";
            return false;
        }
        qwRoleID = vecRoleID.at(0);
     }else //false 表示自己，true 表示第一名
     {
        if(qwPlayerID == 0)
            return false;
     }
     auto it1 = _mapRankInfo.find(eRTHeroFighter);
     if(it1 == _mapRankInfo.end())
     {
         LOG_INF << " mapRankinfo error";
         return false;
     }
     const SetRankInfo& rsetRankInfo = it1->second;
     auto oIt = _mapRankIndex.find(eRTHeroFighter);
     if(oIt == _mapRankIndex.end())
     {
          LOG_INF << " _mapRankIndex error";
          return false;
     }
     const MapRankIndex& rmapRankIndex = oIt->second;
     auto it = rmapRankIndex.find(qwRoleID); 
     if(it == rmapRankIndex.end())
     {
          LOG_INF << "VecItSetRank error";
          return false;
     }
     const VecItSetRank& rvecItSetRankInfo = it->second;
     if (rvecItSetRankInfo.empty())
     {
         LOG_INF << "VecItSetRank empty";
         return false;
     }
     for(auto& it4 : rvecItSetRankInfo)
     {
          UINT32 dwRank = distance(rsetRankInfo.begin(), it4) + 1;
          sPlayer.dwValue1 = dwRank;
     }

     SRankInfoPtr pBaseInfo = *(rvecItSetRankInfo[0]);
     SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfo);
     SRoleRankInfoPtr pRoleRankInfo = dynamic_pointer_cast<SRoleRankInfo>(pBaseInfo);
     sPlayer.dwValue2 = pInfo->dwBattlePoint;

     sPlayer.strName = pRoleRankInfo->strName;
     sPlayer.strName1 = pInfo->strGuildName;
     sPlayer.wID = pInfo->wID;
     UINT16 wFighterID = pRoleRankInfo->wPlayerFighterID;    
     sPlayer.eCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
     UINT8 byIndex  = wFighterID % 2;
     if(byIndex)
        sPlayer.eSex = ESEX_MALE;
     else 
        sPlayer.eSex = ESEX_FEMALE;
    return true;
}

bool CRankMgr::SaveRoleInfoForFighter(UINT16 wActID)
{
    SRetain sPlayer;

    auto it1 = _mapRankInfo.find(eRTHeroFighter);
    if(it1 == _mapRankInfo.end())
    {
        LOG_INF << " mapRankinfo error";
        return 0;
    }
    const SetRankInfo& rsetRankInfo = it1->second;
    UINT16 wRank = 1;
    for(auto &it : rsetRankInfo)
    {
        SRankInfoPtr pBaseInfo = it;
        SRRHeroFighterInfoPtr pInfo = dynamic_pointer_cast<SRRHeroFighterInfo>(pBaseInfo);
        
        sPlayer.qwRoleID = pInfo->qwRoleID;
        sPlayer.wActID = wActID;
        sPlayer.wType = wRank ++;
        sPlayer.dwValue = pInfo->dwBattlePoint;
        sPlayer.strName = pInfo->strName;
        sPlayer.strGuildName = pInfo->strGuildName;
        sPlayer.wID = pInfo->wID;

        UINT16 wFighterID = pInfo->wPlayerFighterID;    
        sPlayer.byCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
            sPlayer.bySex = static_cast<UINT8>(ESEX_MALE);
        else 
            sPlayer.bySex = static_cast<UINT8>(ESEX_FEMALE);
        
        g_RetainMgr.SetRetain(sPlayer);
        //第一名玩家 颁发称号2004
        if(sPlayer.wType == 1)
        {
            UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
            g_Game2CenterCommS.SendSvr_SyncTitle(&dwGameSvrIdx, 1, sPlayer.qwRoleID,2004);
        }
    }
    return true;
}

//全服阵灵榜活动
bool CRankMgr::GetPlayerInfoForPet(UINT16 wActID,bool bType,UINT64& qwPlayerID,SWActPlayerInfo& sPlayer,NWonderActivityProt::EWActState eType)
{
    if(eType == eWActState_End)
    {
        UINT16 wIndex = 1;
        SRetain sSaveInfo;
        if(bType)
            g_RetainMgr.GetRetainByType(wActID,wIndex,sSaveInfo);
        else
            g_RetainMgr.GetRetainByRoleID(qwPlayerID,wActID,sSaveInfo);
        sPlayer.dwValue1 = sSaveInfo.wType;
        sPlayer.dwValue2 = sSaveInfo.dwValue;
        sPlayer.strName = sSaveInfo.strName;
        sPlayer.strName1 = sSaveInfo.strGuildName;
        sPlayer.wID = sSaveInfo.wID;
        sPlayer.eCareer = static_cast<ECareerType>(sSaveInfo.byCareer);
        sPlayer.eSex = static_cast<ESexType>(sSaveInfo.bySex);
        return true;
    }

    UINT64 qwRoleID = qwPlayerID;
    if(bType)
    {
        TVecUINT64 vecRoleID;
        GetRankRoleID(eRTFormation, 1, 1, vecRoleID);
        if(vecRoleID.size() == 0)
        {
            LOG_INF << " GetRankRoleID error";
            return false;
        }
        qwRoleID = vecRoleID.at(0);
     }else //false 表示自己，true 表示第一名
     {
        if(qwPlayerID == 0)
            return false;
     }
     auto it1 = _mapRankInfo.find(eRTFormation);
     if(it1 == _mapRankInfo.end())
     {
         LOG_INF << " mapRankinfo error";
         return false;
     }
     const SetRankInfo& rsetRankInfo = it1->second;
     auto oIt = _mapRankIndex.find(eRTFormation);
     if(oIt == _mapRankIndex.end())
     {
          LOG_INF << " _mapRankIndex error";
          return false;
     }
     const MapRankIndex& rmapRankIndex = oIt->second;
     auto it = rmapRankIndex.find(qwRoleID); 
     if(it == rmapRankIndex.end())
     {
          LOG_INF << "VecItSetRank error";
          return false;
     }
     const VecItSetRank& rvecItSetRankInfo = it->second;
     if (rvecItSetRankInfo.empty())
     {
         LOG_INF << "VecItSetRank empty";
         return false;
     }
     for(auto& it4 : rvecItSetRankInfo)
     {
          UINT32 dwRank = distance(rsetRankInfo.begin(), it4) + 1;
          sPlayer.dwValue1 = dwRank;
     }

     SRankInfoPtr pBaseInfo = *(rvecItSetRankInfo[0]);
     SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfo);
     SRoleRankInfoPtr pRoleRankInfo = dynamic_pointer_cast<SRoleRankInfo>(pBaseInfo);
     sPlayer.dwValue2 = pInfo->dwBattlePoint;

     sPlayer.strName = pRoleRankInfo->strName;
     sPlayer.strName1 = pInfo->strGuildName;
     sPlayer.wID = pInfo->wID;
     UINT16 wFighterID = pRoleRankInfo->wPlayerFighterID;    
     sPlayer.eCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
     UINT8 byIndex  = wFighterID % 2;
     if(byIndex)
        sPlayer.eSex = ESEX_MALE;
     else 
        sPlayer.eSex = ESEX_FEMALE;
    return true;
}

bool CRankMgr::SaveRoleInfoForPet(UINT16 wActID)
{
    SRetain sPlayer;

    auto it1 = _mapRankInfo.find(eRTFormation);
    if(it1 == _mapRankInfo.end())
    {
        LOG_INF << " mapRankinfo error";
        return 0;
    }
    const SetRankInfo& rsetRankInfo = it1->second;

    auto oIt = _mapRankIndex.find(eRTFormation);
    if(oIt == _mapRankIndex.end())
    {
        LOG_INF << " _mapRankIndex error";
        return false;
    }
    const MapRankIndex& rmapRankIndex = oIt->second;
    for(auto &it : rmapRankIndex)
    {
        sPlayer.qwRoleID = it.first;
        sPlayer.wActID = wActID;
        const VecItSetRank& rvecItSetRankInfo = it.second;
        if (rvecItSetRankInfo.empty())
        {
            LOG_INF << "VecItSetRank empty";
            return false;
        }
        for(auto& it4 : rvecItSetRankInfo)
        {
            UINT32 dwRank = distance(rsetRankInfo.begin(), it4) + 1;
            sPlayer.wType = static_cast<UINT16>(dwRank);
        }

        SRankInfoPtr pBaseInfo = *(rvecItSetRankInfo[0]);
        SRRFormationInfoPtr pInfo = dynamic_pointer_cast<SRRFormationInfo>(pBaseInfo);
        SRoleRankInfoPtr pRoleRankInfo = dynamic_pointer_cast<SRoleRankInfo>(pBaseInfo);

        sPlayer.dwValue = pInfo->dwBattlePoint;
        sPlayer.strName = pRoleRankInfo->strName;
        sPlayer.strGuildName = pInfo->strGuildName;
        sPlayer.wID = pInfo->wID;

        UINT16 wFighterID = pRoleRankInfo->wPlayerFighterID;    
        sPlayer.byCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
            sPlayer.bySex = static_cast<UINT8>(ESEX_MALE);
        else 
            sPlayer.bySex = static_cast<UINT8>(ESEX_FEMALE);
        
        g_RetainMgr.SetRetain(sPlayer);
    }

    return true;
}
        
//全服帮派榜活动
bool CRankMgr::GetPlayerInfoForGuild(UINT16 wActID,bool bType,UINT64& qwPlayerID,SWActPlayerInfo& sPlayer,NWonderActivityProt::EWActState eType)
{
    if(eType == eWActState_End)
    {
        UINT16 wIndex = 1;
        SRetain sSaveInfo;
        if(bType)
            g_RetainMgr.GetRetainByType(wActID,wIndex,sSaveInfo);
        else
        {
            if(!qwPlayerID)
                 return false;
            UINT64 qwGuildID = 0;
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwPlayerID);
            if(!pUser)
                return false ;
            qwGuildID = pUser->GetGuildID();
            if(qwGuildID == 0)
            {
                LOG_INF << " GuildID = 0,qwRoleID="<<qwPlayerID;
                return false;
            }
            g_RetainMgr.GetRetainByRoleID(qwGuildID,wActID,sSaveInfo);
        }
        sPlayer.dwValue1 = sSaveInfo.wType;
        sPlayer.dwValue2 = sSaveInfo.dwValue;
        sPlayer.strName = sSaveInfo.strName;
        sPlayer.strName1 = sSaveInfo.strGuildName;
        sPlayer.wID = sSaveInfo.wID;
        sPlayer.eCareer = static_cast<ECareerType>(sSaveInfo.byCareer);
        sPlayer.eSex = static_cast<ESexType>(sSaveInfo.bySex);
        return true;
    }
    UINT64 qwGuildID = 0;
    if(bType)
    {
        qwGuildID = CGuildMgr::Instance().GetFirstGuildByLevel();
        if(qwGuildID == 0)
        {
            LOG_INF << "wrong GuildID(" <<qwGuildID<<").";
            return false;
        }
        CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
        if(!pGuild)
        {
            LOG_INF << " pGuild NULL.";
            return false;
        }
        //sPlayer.qwRoleID = qwGuildID;
        sPlayer.wID = 0;
        sPlayer.strName = pGuild->GetOwnerName(); 
        sPlayer.strName1 = pGuild->GetName();
        sPlayer.dwValue1 = 1;
        sPlayer.dwValue2 = pGuild->GetLevel();
        UINT16 wFighterID = pGuild->GetPlayerFighterID();    
        if(!wFighterID)
        {
            LOG_INF << "wFighterID is 0";
            return false;
        }
        sPlayer.eCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
           sPlayer.eSex = ESEX_MALE;
        else 
           sPlayer.eSex = ESEX_FEMALE;
    }
    else
    {
        if(qwPlayerID == 0)
        {
            LOG_WRN<<" qwPlayerID is 0";
            return false; 
        }
        CGuildUserPtr pGuildUser = CGuildUserMgr::Instance().GetUserByUserID(qwPlayerID);
        if(!pGuildUser)
        {
            LOG_WRN << " pGuildUser NULL.qwRoleID("<<qwPlayerID<<") no Guild";
            return false;
        }
        UINT64 qwGuildID = CGuildUserMgr::Instance().GetGuildID(qwPlayerID);
        if(!qwGuildID)
        {
            LOG_WRN << "qwGuildID is 0";
            return false;
        }
        CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
        if(!pGuild)
        {
            LOG_INF << " pGuild NULL.";
            return false;
        }
        sPlayer.wID = 0;
        sPlayer.strName = pGuild->GetOwnerName(); 
        sPlayer.strName1 = pGuild->GetName();
        sPlayer.dwValue1 = CGuildMgr::Instance().GetRankForLevel(qwGuildID) ;
        sPlayer.dwValue2 = pGuild->GetLevel();
        UINT16 wFighterID = pGuild->GetPlayerFighterID();    
        if(!wFighterID)
        {
            LOG_INF << "wFighterID is 0";
            return false;
        }
        sPlayer.eCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
           sPlayer.eSex = ESEX_MALE;
        else 
           sPlayer.eSex = ESEX_FEMALE;
    }
    return true;
}

bool CRankMgr::SaveRoleInfoForGuild(UINT16 wActID)
{ 
    
    SRetain sPlayer;
    std::set<SGuildRankByLevel> setGuildRank;
    UINT64 qwGuildID = 0;
    if(!CGuildMgr::Instance().GetGuildLevelRank(setGuildRank))
    {
        LOG_INF << " setGuildRank error.";
        return false;
    }
    UINT16 wRank =1;
    for(auto it=setGuildRank.begin(); it!=setGuildRank.end(); ++it)
    {
       qwGuildID = it->qwGuildID;
       if(qwGuildID == 0)
       {
           LOG_INF << " qwGuildID =0.";
           continue;
       }
       CGuildPtr pGuild = CGuildMgr::Instance().GetGuild(qwGuildID);
        if(!pGuild)
        {
            LOG_INF << " pGuild NULL.";
            continue;
        }
        sPlayer.wType = wRank;
        wRank ++;
        sPlayer.strName = pGuild->GetOwnerName(); 
        sPlayer.strGuildName = pGuild->GetName();
        sPlayer.wID = 0;
        sPlayer.dwValue = pGuild->GetLevel();
        UINT16 wFighterID = pGuild->GetPlayerFighterID();   
        
        LOG_INF <<"GuildName(" <<sPlayer.strGuildName<<"),wFighterID(" <<wFighterID<<").";
        if(wFighterID == 0) //wFighterID =0表示创建Guild 异常，就付给一个默认值 4
        {
            LOG_WRN<< " wFighterID is 0";
            wFighterID = 4;
        }
        sPlayer.byCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
            sPlayer.bySex = static_cast<UINT8>(ESEX_MALE);
        else 
            sPlayer.bySex = static_cast<UINT8>(ESEX_FEMALE);
        sPlayer.wActID = wActID;
        sPlayer.qwRoleID = qwGuildID;
       g_RetainMgr.SetRetain(sPlayer);
    }

    //清空发邮件临时数据
    
    _setRoleID.clear();
    return true;
}

//全服斗剑榜活动
bool CRankMgr::GetPlayerInfoForArena(UINT16 wActID,bool bType,UINT64& qwPlayerID,SWActPlayerInfo& sPlayer,NWonderActivityProt::EWActState eType)
{
    if(eType == eWActState_End)
    {
        UINT16 wIndex = 1;
        SRetain sSaveInfo;
        if(bType)
        {
            g_RetainMgr.GetRetainByType(wActID,wIndex,sSaveInfo);
            sPlayer.qwPlayerID = sSaveInfo.qwRoleID;
        }
        else
            g_RetainMgr.GetRetainByRoleID(qwPlayerID,wActID,sSaveInfo);
        sPlayer.dwValue1 = sSaveInfo.wType;
        sPlayer.dwValue2 = sSaveInfo.dwValue;
        sPlayer.strName = sSaveInfo.strName;
        sPlayer.strName1 = sSaveInfo.strGuildName;
        sPlayer.wID = sSaveInfo.wID;
        sPlayer.eCareer = static_cast<ECareerType>(sSaveInfo.byCareer);
        sPlayer.eSex = static_cast<ESexType>(sSaveInfo.bySex);
        return true;
    }
    TVecArenaRank2Client vecRankInfo;
    SArenaRank2Client stClient;
    UINT32 dwCurIndex;
    UINT32 dwMaxCount;
    UINT32 dwSelfRank;
    UINT64 qwRoleID = 0;
    if(qwPlayerID)
    {
       qwRoleID = qwPlayerID;
    }
    CArenaManager::GetRankInfo(qwRoleID, 0, 1, dwMaxCount, dwCurIndex, dwSelfRank, vecRankInfo, stClient);
    if(vecRankInfo.size() == 0)
    {
        LOG_INF << " vecRankInfo for Arena size = 0.";
        return false;
    }
    SArenaRank2Client  rBaseInfo = vecRankInfo[0];
    if(bType)
    {
         sPlayer.dwValue1= 1;
         sPlayer.dwValue2 = rBaseInfo.dwFighterPower;
         sPlayer.strName =  rBaseInfo.stFighter.strName;
         sPlayer.strName1 = "NOGUILDNAME";
         if(CArenaManager::IsRobot(rBaseInfo.qwRoleID,true))
         {
             LOG_INF<<"qwRoleID="<<rBaseInfo.qwRoleID<<" is Robot.";
             sPlayer.qwPlayerID = rBaseInfo.qwRoleID;
         }
         sPlayer.wID = 0;
         sPlayer.eCareer = rBaseInfo.stFighter.stAppear.eJob;
         sPlayer.eSex = rBaseInfo.stFighter.stAppear.eSex;
    }else //false 表示自己，true 表示第一名
     {
        if(qwPlayerID == 0)
            return false;
         sPlayer.dwValue1 = dwSelfRank;
         sPlayer.dwValue2 = stClient.dwFighterPower;
         sPlayer.strName =  stClient.stFighter.strName;
         sPlayer.strName1 = "NOGUILDNAME";
         sPlayer.wID = 0;
         sPlayer.eCareer = stClient.stFighter.stAppear.eJob;
         sPlayer.eSex = stClient.stFighter.stAppear.eSex;
     }
    
     return true;
}

bool CRankMgr::SaveRoleInfoForArena(UINT16 wActID)
{
    SRetain sPlayer;
    TVecArenaRank2Client vecRankInfo;
    SArenaRank2Client stClient;
    UINT32 dwCurIndex;
    UINT32 dwMaxCount;
    UINT32 dwSelfRank;
    UINT32 dwCount = 100;
    CArenaManager::GetRankInfo(0, 1, dwCount, dwMaxCount, dwCurIndex, dwSelfRank, vecRankInfo, stClient);
    if(vecRankInfo.empty())
    {
        LOG_INF << " vecRankInfo is empty.";
        return false;
    }
    UINT16 dwRank = 1;
    for(auto & rInfo : vecRankInfo)
    {
        sPlayer.wType = dwRank ++;
        sPlayer.dwValue = rInfo.dwFighterPower;
        sPlayer.strName =  rInfo.stFighter.strName;
        sPlayer.strGuildName = "NOGUILDNAME";
        sPlayer.wID = wActID;
        sPlayer.byCareer = static_cast<UINT8>( rInfo.stFighter.stAppear.eJob);
        sPlayer.bySex = static_cast<UINT8>(rInfo.stFighter.stAppear.eSex);
        sPlayer.qwRoleID = rInfo.qwRoleID;
        sPlayer.wActID = wActID;

        g_RetainMgr.SetRetain(sPlayer);
        //第一名玩家 颁发称号2006
        if(sPlayer.wType == 1)
        {
            UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
            g_Game2CenterCommS.SendSvr_SyncTitle(&dwGameSvrIdx, 1, sPlayer.qwRoleID,2006);
        }
    }
    return true;
}

bool CRankMgr::GetPlayerInfoForTrump(UINT16 wActID,bool bType,UINT64& qwPlayerID, SWActPlayerInfo& sPlayer,NWonderActivityProt::EWActState eType)
{
    if(eType == eWActState_End)
    {
        UINT16 wIndex = 1;
        SRetain sSaveInfo;
        if(bType)
            g_RetainMgr.GetRetainByType(wActID,wIndex,sSaveInfo);
        else
            g_RetainMgr.GetRetainByRoleID(qwPlayerID,wActID,sSaveInfo);
        sPlayer.dwValue1 = sSaveInfo.wType;
        sPlayer.dwValue2 = sSaveInfo.dwValue;
        sPlayer.strName = sSaveInfo.strName;
        sPlayer.strName1 = sSaveInfo.strGuildName;
        sPlayer.wID = sSaveInfo.wID;
        sPlayer.eCareer = static_cast<ECareerType>(sSaveInfo.byCareer);
        sPlayer.eSex = static_cast<ESexType>(sSaveInfo.bySex);
        return true;
    }

    UINT64 qwRoleID = qwPlayerID;
    if(bType)
    {
        TVecUINT64 vecRoleID;
        GetRankRoleID(eRTTrump, 1, 1, vecRoleID);
        if(vecRoleID.size() == 0)
        {
            LOG_INF << " GetRankRoleID error";
            return false;
        }
        qwRoleID = vecRoleID.at(0);
     }else //false 表示自己，true 表示第一名
     {
        if(qwPlayerID == 0)
            return false;
     }
     auto it1 = _mapRankInfo.find(eRTTrump);
     if(it1 == _mapRankInfo.end())
     {
         LOG_INF << " mapRankinfo error";
         return false;
     }
     const SetRankInfo& rsetRankInfo = it1->second;
     auto oIt = _mapRankIndex.find(eRTTrump);
     if(oIt == _mapRankIndex.end())
     {
          LOG_INF << " _mapRankIndex error";
          return false;
     }
     const MapRankIndex& rmapRankIndex = oIt->second;
     auto it = rmapRankIndex.find(qwRoleID); 
     if(it == rmapRankIndex.end())
     {
          LOG_INF << "VecItSetRank error";
          return false;
     }
     const VecItSetRank& rvecItSetRankInfo = it->second;
     if (rvecItSetRankInfo.empty())
     {
         LOG_INF << "VecItSetRank empty";
         return false;
     }
     for(auto& it4 : rvecItSetRankInfo)
     {
          UINT32 dwRank = distance(rsetRankInfo.begin(), it4) + 1;
          sPlayer.dwValue1 = dwRank;
     }

     SRankInfoPtr pBaseInfo = *(rvecItSetRankInfo[0]);
     SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfo);
     
     SRoleRankInfoPtr pRoleRankInfo = dynamic_pointer_cast<SRoleRankInfo>(pBaseInfo);
     sPlayer.dwValue2 = pInfo->dwBattlePoint;

     sPlayer.strName = pRoleRankInfo->strName;
     sPlayer.strName1 = pInfo->strGuildName;
     sPlayer.wID = pInfo->wID;

     //LOG_CRI <<"wTrumpID = " << sPlayer.wID;
     UINT16 wFighterID = pRoleRankInfo->wPlayerFighterID;    
     sPlayer.eCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
     UINT8 byIndex  = wFighterID % 2;
     if(byIndex)
        sPlayer.eSex = ESEX_MALE;
     else 
        sPlayer.eSex = ESEX_FEMALE;
 
    return true;
}

bool CRankMgr::SaveRoleInfoForTrump(UINT16 wActID)
{
    SRetain sPlayer;

    auto it1 = _mapRankInfo.find(eRTTrump);
    if(it1 == _mapRankInfo.end())
    {
        LOG_INF << " mapRankinfo error";
        return 0;
    }
    const SetRankInfo& rsetRankInfo = it1->second;
    UINT16 wRank = 1;
    for(auto &it : rsetRankInfo)
    {
        SRankInfoPtr pBaseInfo = it;
        SRRTrumpInfoPtr pInfo = dynamic_pointer_cast<SRRTrumpInfo>(pBaseInfo);
        sPlayer.qwRoleID = pInfo->qwRoleID;
        sPlayer.wActID = wActID;
        sPlayer.wType = wRank ++;
        sPlayer.dwValue = pInfo->dwBattlePoint;
        sPlayer.strName = pInfo->strName;
        sPlayer.strGuildName = pInfo->strGuildName;
        sPlayer.wID = pInfo->wID;
        UINT16 wFighterID = pInfo->wPlayerFighterID;    
        sPlayer.byCareer = static_cast<ECareerType>((wFighterID - 1) / 2  + 1);  
        UINT8 byIndex  = wFighterID % 2;
        if(byIndex)
            sPlayer.bySex = static_cast<UINT8>(ESEX_MALE);
        else 
            sPlayer.bySex = static_cast<UINT8>(ESEX_FEMALE);
        
        g_RetainMgr.SetRetain(sPlayer);
        //第一名玩家 颁发称号2005
        if(sPlayer.wType == 1)
        {
            UINT32 dwGameSvrIdx = CCenterConfig::Instance().GetSvrID();
            g_Game2CenterCommS.SendSvr_SyncTitle(&dwGameSvrIdx, 1, sPlayer.qwRoleID,2005);
        }
    }
    return true;
}

