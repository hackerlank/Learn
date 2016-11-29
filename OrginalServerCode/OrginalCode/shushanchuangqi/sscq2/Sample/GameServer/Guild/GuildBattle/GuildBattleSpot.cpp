// =====================================================================================
//
//       Filename:  GuildBattleSpot.cpp
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

#include "GuildBattleSpot.h"
#include "GuildBattleConfig.h"
#include "GuildBattleMgr.h"
#include "GuildBattleInfo.h"
#include "MapMgr.h"
#include "Protocols.h"
#include "Map.h"

#ifdef _DEBUG
#include "Player.h"
#endif

bool SGuildBattleSpotPlayer::GetAllInfo(SBattleUserAllInfo& rInfo) const
{
    CPlayerPtr pPlayer2 = pPlayer.lock();
    if (pPlayer2)
    {
        rInfo.qwRoleID      = pPlayer2->GetRoleID();            // 成员角色ID
        rInfo.strName       = pPlayer2->GetName();              // 名字
        rInfo.wLevel        = pPlayer2->GetLevel();             // 等级
        rInfo.eState        = eState;                           // 玩家状态
        rInfo.byHPP         = static_cast<UINT8>(static_cast<FLOAT>(pPlayer2->GetCurrHP()) / pPlayer2->GetMaxHP());//剩余HP百分
        rInfo.dwBattlePoint = pPlayer2->GetBattlePoint();       // 战斗力
        rInfo.wFighterID    = pPlayer2->GetPlayerFighterID();   // 主将ID
        for (auto& rSkill : setSkillBuff)
        {
            rInfo.vecSkillInfo.push_back(rSkill);
        }
        pPlayer2->GetPlayerAppear(rInfo.sAppear);               // 外观
#ifdef _DEBUG
        LOG_WRN << "Player Info: " << pPlayer2->GetName() << ", " << EnumValToStr(eState) << ".";
#endif
    }
    return true;
}

CGuildBattleSpot::CGuildBattleSpot (EGBSpot eType):
    _eType(eType), _eState(eGBSpotStateNone)
{
}        // -----  end of method CGuildBattleSpot::CGuildBattleSpot  ----- //

CGuildBattleSpot::~CGuildBattleSpot()
{
}

// ===  FUNCTION  ======================================================================
//         Name:  GetType
//  Description:  获取据点类型
// =====================================================================================
EGBSpot CGuildBattleSpot::GetType () const
{
    return _eType;
}		// -----  end of function GetType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitMap
//  Description:  初始化地图
// =====================================================================================
void CGuildBattleSpot::InitMap (UINT64 qwGuildIDA, UINT64 qwGuildIDB)
{
    if (_pMap)
    {
        LOG_WRN << "Spot Already Inited(" << static_cast<UINT32>(_eType) << ").";
        return;
    }
    _pMap = CMapMgr::CreateMap(CGuildBattleConfigMgr::Instance().GetMapID(_eType));

    _eState = eGBSpotStateBattle;

    // 将玩家放入观察者列表
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        for (auto it = _listPlayer[byIndex].begin(); it != _listPlayer[byIndex].end(); ++it)
        {
            CPlayerPtr pPlayer = (*it)->pPlayer.lock();
            if (pPlayer)
                AddOB(pPlayer->GetRoleID());
        }
    }
}		// -----  end of function InitMap  ----- //

bool IsNotInPrepareMap (const SGuildBattleSpotPlayerPtr& pSpotPlayer)
{
    if (pSpotPlayer && pSpotPlayer->pPlayer.lock())
    {
        CPlayerPtr pPlayer = pSpotPlayer->pPlayer.lock();
        if (pPlayer)
        {
            CGameMapPtr pMap = pPlayer->GetMap();
            if (pMap && pMap->GetMapID() == CGuildBattleConfigMgr::Instance().GetPrepareMapID())
                return false;
        }
    }
    return true;
}

// ===  FUNCTION  ======================================================================
//         Name:  InitPlayer
//  Description:  将准备地图玩家拉入战斗地图
// =====================================================================================
void CGuildBattleSpot::InitPlayer (set<EGBSkill> setSkillBuff[2])
{
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        for (auto it = _listPlayer[byIndex].begin(); it != _listPlayer[byIndex].end(); ++it)
        {
            if (IsNotInPrepareMap(*it))
            {
                CPlayerPtr pPlayer = (*it)->pPlayer.lock();
                if (pPlayer)
                {
                    RemoveOB(pPlayer->GetRoleID());
                    //CGuildBattleMgr::Instance().RemovePlayerMap(pPlayer->GetRoleID());
                }
            }
        }
    }
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        _listPlayer[byIndex].remove_if(IsNotInPrepareMap);
    }
    // 将玩家拉入地图，回血，增加帮派战技能Buff
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        UINT8 byPos = 0;
        for (auto it = _listPlayer[byIndex].begin(); it != _listPlayer[byIndex].end(); ++it)
        {
            ++byPos;
            CPlayerPtr pPlayer = (*it)->pPlayer.lock();
            if (!pPlayer)
                continue;
            pPlayer->RegenAllHP();
            /*for (auto it2 = setSkillBuff[byIndex].begin(); it2 != setSkillBuff[byIndex].end(); ++it2)
            {
                pPlayer->AddBuff(CGuildBattleConfigMgr::Instance().GetSkillBuffID(*it2));
            }*/
            CGameMapPtr pMap = pPlayer->GetMap();
            if (pMap && pMap->GetMapID() == CGuildBattleConfigMgr::Instance().GetPrepareMapID())
            {
                SPoint oPoint;
                oPoint.fX = CGuildBattleConfigMgr::Instance().GetPosX(byPos);
                oPoint.fY = CGuildBattleConfigMgr::Instance().GetPosY(byPos);
                if(!pPlayer->JumpMap(_pMap, oPoint))
                    LOG_CRI << "Error when Return to PrepareMap(" << pPlayer->GetRoleID() << ").";
                pPlayer->RegenAllHP();
            }

            for (auto it2 = (*it)->setSkillBuff.begin(); it2!=(*it)->setSkillBuff.end(); ++it2)
            {
                pPlayer->AddBuff(CGuildBattleConfigMgr::Instance().GetSkillBuffID(*it2));
            }

            /*for (auto it2 = setSkillBuff[byIndex].begin(); it2 != setSkillBuff[byIndex].end(); ++it2)
            {
                EBuffOpResult eResult = pPlayer->AddBuff(CGuildBattleConfigMgr::Instance().GetSkillBuffID(*it2));
                LOG_WRN << pPlayer->GetName() << " Add Buff: " << CGuildBattleConfigMgr::Instance().GetSkillBuffID(*it2) << ": " << static_cast<UINT32>(eResult) << ".";
            }*/
        }
    }
}		// -----  end of function InitPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayer
//  Description:  玩家加入帮派战据点
// =====================================================================================
SGuildBattleSpotPlayerPtr CGuildBattleSpot::AddPlayer ( CPlayerPtr pPlayer, EGBSide eSide, 
        EGBSignUpResult& eResult, UINT8 byIndex, UINT32 dwPreCount)
{
    if (!pPlayer)
    {
        eResult = eGBSignUpFailed;
        LOG_CRI << "eGBSignUpFailed.";
        return NULL;
    }

    SGuildBattleSpotPlayerPtr pSpotPlayer;

    for (auto it = _listPlayer[eSide].begin(); it != _listPlayer[eSide].end(); ++it)
    {
        if ((*it)->pPlayer.lock() == pPlayer) // 该玩家已经在该据点上
        {
            pSpotPlayer = *it;
            if (byIndex)
            {
                _listPlayer[eSide].erase(it);
                break;
            }
            else
            {
                eResult = eGBSignUpRepeat;
                LOG_CRI << "eGBSignUpRepeat";
                return false;
            }
        }
    }
    if (_listPlayer[eSide].size() + _listNextPlayer[eSide].size()  + dwPreCount >= CGuildBattleConfigMgr::Instance().GetUserCount())
    {
        eResult = eGBSignUpSpotFull;
        LOG_CRI << "eGBSignUpSpotFull";
        return NULL;
    }
    if (!pSpotPlayer)
        pSpotPlayer = SGuildBattleSpotPlayerPtr(new SGuildBattleSpotPlayer(pPlayer, ToThisPtr(this)));
    if (byIndex && byIndex <= _listPlayer[eSide].size())
    {
        auto it = _listPlayer[eSide].begin();
        advance(it, byIndex - 1);
        _listPlayer[eSide].insert(it, pSpotPlayer);
    }
    else
        _listPlayer[eSide].push_back(pSpotPlayer);
    eResult = eGBSignUpSuccess;
    return pSpotPlayer;
}        // -----  end of method CGuildBattleSpot::AddPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemovePlayer
//  Description:  玩家退出帮派战据点
// =====================================================================================
EGBSide CGuildBattleSpot::RemovePlayer (CPlayerPtr pPlayer, bool bCleanMark/*默认清除buff*/, SGuildBattleSpotPlayerPtr pSpotPlayer /* = NULL */)
{
    if (!pPlayer)
        return eGBSideInvalid;
    for (UINT8 bySide = eGBSideA; bySide <= eGBSideInvalid; ++bySide)
    {
        EGBSide eSide = static_cast<EGBSide>(bySide);
        for (auto it=_listPlayer[eSide].begin(); it!=_listPlayer[eSide].end(); ++it)
        {
            if ((*it)->pPlayer.lock() == pPlayer)
            {
                if (bCleanMark)
                {
                    for (auto it2=(*it)->setSkillBuff.begin(); it2!=(*it)->setSkillBuff.end(); ++it2)
                    {
                        pPlayer->RemoveBuff(CGuildBattleConfigMgr::Instance().GetSkillBuffID(*it2));
                    }
                    (*it)->setSkillBuff.clear();
                }
                else if (pSpotPlayer)
                    pSpotPlayer->setSkillBuff = (*it)->setSkillBuff;
                _listPlayer[eSide].erase(it);
                return eSide;
            }
        }
        /*set<UINT16> setBuffID;
        CGuildBattleConfigMgr::Instance().GetAllSkillBuff(setBuffID);
        for (auto it2 = setBuffID.begin(); it2 != setBuffID.end(); ++it2)
        {
            pPlayer->RemoveBuff(*it2);
        }*/
    }
    return eGBSideInvalid;
}        // -----  end of method CGuildBattleSpot::RemovePlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CatSpotInfo
//  Description:  从另一个据点获取信息加载到本据点上
// =====================================================================================
void CGuildBattleSpot::CatSpotInfo(CGuildBattleSpotPtr pSpot, EGBSide eSide, EGBSide eSide2, bool bCleanSrc, TVecUINT64& rvecRoleID)
{
    if (!pSpot || eSide >= eGBSideInvalid)
        return;
    if (eSide2 == eGBSideInvalid)
        eSide2 = eSide;

    for (auto it = pSpot->_listPlayer[eSide2].begin(); it != pSpot->_listPlayer[eSide2].end(); ++it)
    {
        (*it)->pSpot = ToThisPtr(this);
        (*it)->eState = eGBUserStateWait;
        CPlayerPtr pPlayer = (*it)->pPlayer.lock();
        if (pPlayer)
            rvecRoleID.push_back(pPlayer->GetRoleID());
    }

    _listPlayer[eSide].insert(_listPlayer[eSide].end(), 
            pSpot->_listPlayer[eSide2].begin(), pSpot->_listPlayer[eSide2].end());
    if (bCleanSrc)
        pSpot->_listPlayer[eSide2].clear();

}		// -----  end of function CatSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PushBattleInfo
//  Description:  增加一条战报
// =====================================================================================
void CGuildBattleSpot::PushBattleInfo (CGuildBattleInfoPtr pInfo)
{
    if (pInfo)
    {
        _vecInfo.push_back(pInfo);
        _vecLastInfo[pInfo->GetIndex()-1] = pInfo;
    }
}		// -----  end of function PushBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CleanMap
//  Description:  清除据点玩家到其他地图（准备地图/大地图）
// =====================================================================================
void CGuildBattleSpot::CleanMap (bool bFinal)
{
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        for (auto it = _listPlayer[byIndex].begin(); it != _listPlayer[byIndex].end(); ++it)
        {
            (*it)->byWinCount = 0;
            (*it)->eState = eGBUserStateNone;
            CPlayerPtr pPlayer = (*it)->pPlayer.lock();
            if (!pPlayer)
                continue;
            if (bFinal) // 最后一场结束了，放回原始地图
            {
                UINT16 wMapID = pPlayer->GetBaseInfo().wMapID;
                SPoint oPoint(pPlayer->GetBaseInfo().fX, pPlayer->GetBaseInfo().fY);
                if(wMapID == 0)
                {
                    LOG_CRI << "NO MAP";
                    wMapID = 1;
                }
                pPlayer->JumpMap(wMapID, oPoint);
                pPlayer->SetCurMapID(wMapID);
                pPlayer->SetPoint(oPoint);
            }
            else // 要进行下一场，放回准备地图
            {
                UINT64 qwGuildID = CGuildBattleMgr::Instance().GetGuildID(pPlayer);
                CGameMapPtr pMap = CGuildBattleMgr::Instance().GetPrepareMap(qwGuildID);
                if (pMap)
                {
                    SPoint oPoint;
                    pMap->GetRandPoint(oPoint);
                    if(!pPlayer->JumpMap(pMap, oPoint))
                        LOG_CRI << "Error when Return to PrepareMap(" << pPlayer->GetRoleID() << ").";
                }
                else
                    LOG_CRI << "GetPrepareMap return NULL.";
            }
            
            for (auto it2 = (*it)->setSkillBuff.begin(); it2!=(*it)->setSkillBuff.end(); ++it2)
            {
                pPlayer->RemoveBuff(CGuildBattleConfigMgr::Instance().GetSkillBuffID(*it2));
            }
            (*it)->setSkillBuff.clear();

            // 清除帮派战相关Buff
            /*set<UINT16> setBuffID;
            CGuildBattleConfigMgr::Instance().GetAllSkillBuff(setBuffID);
            for (auto it2 = setBuffID.begin(); it2 != setBuffID.end(); ++it2)
            {
                pPlayer->RemoveBuff(*it2);
            }*/
        }
    }
}		// -----  end of function CleanMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerNotInPrepareMap
//  Description:  获取不在准备地图的玩家
// =====================================================================================
void CGuildBattleSpot::GetPlayerNotInPrepareMap (TVecUINT64& rvecRoleID)
{
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        for (auto it = _listPlayer[byIndex].begin(); it != _listPlayer[byIndex].end(); ++it)
        {
            CPlayerPtr pPlayer = (*it)->pPlayer.lock();
            if (pPlayer)
            {
                CGameMapPtr pMap = pPlayer->GetMap();
                if (pMap && pMap->GetMapID() != CGuildBattleConfigMgr::Instance().GetPrepareMapID())
                    rvecRoleID.push_back(pPlayer->GetRoleID());
            }
        }
    }
}		// -----  end of function GetPlayerNotInPrepareMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddOB
//  Description:  增加观测者
// =====================================================================================
void CGuildBattleSpot::AddOB (UINT64 qwRoleID)
{
    //LOG_WRN << "AddOB: "" (" << qwRoleID << ").";
    _setOBID.insert(qwRoleID);
}		// -----  end of function AddOB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemoveOB
//  Description:  移除观测者
// =====================================================================================
void CGuildBattleSpot::RemoveOB (UINT64 qwRoleID)
{
    _setOBID.erase(qwRoleID);
}		// -----  end of function RemoveOB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearBattleInfo
//  Description:  清除上一场战报信息
// =====================================================================================
void CGuildBattleSpot::ClearBattleInfo ()
{
    _vecLastInfo.clear();
    _vecLastInfo.resize(3);
}		// -----  end of function ClearBattleInfo  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  PopBattlePlayerPairs
//  Description:  获取某一方可以战斗的成员
// =====================================================================================
void CGuildBattleSpot::PopBattlePlayerPairs(TVecGBPlayerPtr& rvecPlayerA, TVecGBPlayerPtr& rvecPlayerB, UINT8 byCount /* = 3 */)
{
    if (!byCount)
        return;
    if (_eState != eGBSpotStateBattle)
        return;
    UINT8 byCountA = 0;
    UINT8 byCountB = 0;
    for (auto it = _listPlayer[eGBSideA].begin(); it != _listPlayer[eGBSideA].end(); ++it)
    {
        SGuildBattleSpotPlayerPtr pSpotPlayer = *it;
        if (pSpotPlayer->eState == eGBUserStateWait)
        {
            rvecPlayerA.push_back(pSpotPlayer);
            if (++byCountA >= byCount)
                break;
        }
    }
    while(byCountA++ < byCount)
    {
        rvecPlayerA.push_back(NULL);
    }
    for (auto it = _listPlayer[eGBSideB].begin(); it != _listPlayer[eGBSideB].end(); ++it)
    {
        SGuildBattleSpotPlayerPtr pSpotPlayer = *it;
        if (pSpotPlayer->eState == eGBUserStateWait)
        {
            rvecPlayerB.push_back(pSpotPlayer);
            if (++byCountB >= byCount)
                break;
        }
    }
    while(byCountB++ < byCount)
    {
        rvecPlayerA.push_back(NULL);
    }
}		// -----  end of function PopBattlePlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerCount
//  Description:  获得某一方的参战成员数量
// =====================================================================================
UINT32 CGuildBattleSpot::GetPlayerCount (EGBSide eSide) const
{
    if (eSide >= eGBSideInvalid)
        return 0;
    return _listPlayer[eSide].size();
}		// -----  end of function GetPlayerCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotPlayer
//  Description:  获取据点对应的据点玩家
// =====================================================================================
SGuildBattleSpotPlayerPtr CGuildBattleSpot::GetSpotPlayer (UINT64 qwRoleID)
{
    for (auto it = _listPlayer[eGBSideA].begin(); it != _listPlayer[eGBSideA].end(); ++it)
    {
        CPlayerPtr pPlayer = (*it)->pPlayer.lock();
        if (pPlayer && pPlayer->GetRoleID() == qwRoleID)
            return *it;
    }
    for (auto it = _listPlayer[eGBSideB].begin(); it != _listPlayer[eGBSideB].end(); ++it)
    {
        CPlayerPtr pPlayer = (*it)->pPlayer.lock();
        if (pPlayer && pPlayer->GetRoleID() == qwRoleID)
            return *it;
    }
    return NULL;
}		// -----  end of function GetSpotPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerSide
//  Description:  获取玩家所在的方向
// =====================================================================================
EGBSide CGuildBattleSpot::GetPlayerSide (UINT64 qwRoleID) const
{
    for (auto it = _listPlayer[eGBSideA].begin(); it != _listPlayer[eGBSideA].end(); ++it)
    {
        CPlayerPtr pPlayer = (*it)->pPlayer.lock();
        if (pPlayer && pPlayer->GetRoleID() == qwRoleID)
            return eGBSideA;
    }
    for (auto it = _listPlayer[eGBSideB].begin(); it != _listPlayer[eGBSideB].end(); ++it)
    {
        CPlayerPtr pPlayer = (*it)->pPlayer.lock();
        if (pPlayer && pPlayer->GetRoleID() == qwRoleID)
            return eGBSideB;
    }
    return eGBSideInvalid;;
}		// -----  end of function GetPlayerSide  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRoleID
//  Description:  获取某方所有人员ID
// =====================================================================================
void CGuildBattleSpot::GetRoleID(EGBSide eSide, TVecUINT64& rvecRoleID) const
{
    for (auto it = _listPlayer[eSide].begin(); it != _listPlayer[eSide].end(); ++it)
    {
        CPlayerPtr pPlayer = (*it)->pPlayer.lock();
        if (pPlayer)
            rvecRoleID.push_back(pPlayer->GetRoleID());
    }
}		// -----  end of function GetRoleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取据点所有信息
// =====================================================================================
bool CGuildBattleSpot::GetAllInfo (SSpotAllInfo& rSpotInfo) const
{
    //LOG_WRN << "GetAllInfo (ALL) " << EnumValToStr(GetType()) << ".";
    rSpotInfo.eSpotType = _eType;
    //rSpotInfo.eSelfSide = eGBSideInvalid;
    rSpotInfo.eState    = _eState;
    UINT8 byIndex = 0;

    for (auto& pInfo : _listPlayer[eGBSideA])
    {
        SBattleUserAllInfoPtr pUserInfo (new SBattleUserAllInfo);
        pInfo->GetAllInfo(*pUserInfo);
        pUserInfo->byPosIndex = byIndex + 1;
        rSpotInfo.vecMemberInfoA.push_back(pUserInfo);
        ++byIndex;
    }

    byIndex = 0;
    for (auto& pInfo : _listPlayer[eGBSideB])
    {
        SBattleUserAllInfoPtr pUserInfo (new SBattleUserAllInfo);
        pInfo->GetAllInfo(*pUserInfo);
        rSpotInfo.vecMemberInfoB.push_back(pUserInfo);
        pUserInfo->byPosIndex = byIndex + 16;
        ++byIndex;
    }


    for (auto it = _vecLastInfo.begin(); it != _vecLastInfo.end(); ++it)
    {
        if (*it)
        {
            SBattleSlotInfo sInfo;
            (*it)->GetAllInfo(sInfo);
            rSpotInfo.vecBattleSlotInfo.push_back(sInfo);
        }
    }
    for (auto it = _vecInfo.begin(); it != _vecInfo.end(); ++it)
    {
        SBattleInfo sInfo;
        (*it)->GetAllInfo(sInfo);
        rSpotInfo.vecBattleInfo.push_back(sInfo);
    }
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取据点所有信息
// =====================================================================================
bool CGuildBattleSpot::GetAllInfo (SSpotBriefInfo& rSpotInfo) const
{
    rSpotInfo.eSpotType = _eType;
    //rSpotInfo.eSelfSide = eGBSideInvalid;
    rSpotInfo.eState    = _eState;
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取据点所有信息
// =====================================================================================
bool CGuildBattleSpot::GetAllInfo (SSpotReadyInfo& rSpotInfo) const
{
    rSpotInfo.eSpotType = _eType;
    //rSpotInfo.eSelfSide = eGBSideInvalid;
    rSpotInfo.byCount   = _listPlayer[eGBSideA].size();
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllBattleInfo
//  Description:  获取战斗场信息
// =====================================================================================
bool CGuildBattleSpot::GetAllBattleInfo(TVecBattleData& rvecBattleData) const
{
    for (auto it = _vecLastInfo.begin(); it != _vecLastInfo.end(); ++it)
    {
        if (!*it)
            continue;
        SBattleData sBattleInfo;
        (*it)->GetAllInfo(sBattleInfo);
        rvecBattleData.push_back(sBattleInfo);
    }
    return true;
}		// -----  end of function GetAllBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AppendOBSpot
//  Description:  
// =====================================================================================
void CGuildBattleSpot::AppendOBSpot (map<UINT64, EGBSpot>& rmapOBSpot) const
{
    for (auto it = _setOBID.begin(); it != _setOBID.end(); ++it)
    {
        rmapOBSpot[*it] = GetType();
    }
}		// -----  end of function AppendOBSpot  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllOB
//  Description:  获取所有的观看者
// =====================================================================================
TVecUINT64 CGuildBattleSpot::GetAllOB () const
{
    TVecUINT64 vecOBID;
    for (auto rID: _setOBID)
    {
        vecOBID.push_back(rID);
    }
    return vecOBID;
}		// -----  end of function GetAllOB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RefreshState
//  Description:  更新该据点状态
// =====================================================================================
void CGuildBattleSpot::RefreshState (bool bBattle)
{
    if (_eState != eGBSpotStateBattle)
        return;
    UINT32 dwLiveCount[2] = {0};
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        for (auto it = _listPlayer[byIndex].begin(); it != _listPlayer[byIndex].end(); ++it)
        {
            SGuildBattleSpotPlayerPtr pSpotPlayer = *it;
            switch(pSpotPlayer->eState)
            {
                case eGBUserStateWin: //胜利状态
                    pSpotPlayer->eState = eGBUserStateWait;
                case eGBUserStateWait: //待战状态
                case eGBUserStateBattle: //战斗状态
                    ++dwLiveCount[byIndex];
                    break;
                case eGBUserStateDead: //死亡状态
                case eGBUserStateWinTooMuch: //连胜八场，封刀
                case eGBUserStateRunAway: //逃跑状态
                default:
                    break;
            }
        }
    }
    if (dwLiveCount[eGBSideA] && dwLiveCount[eGBSideB])
        _eState = eGBSpotStateBattle;
    else if (dwLiveCount[eGBSideA] && !dwLiveCount[eGBSideB])
        _eState = eGBSpotStateWin;
    else if (!dwLiveCount[eGBSideA] && dwLiveCount[eGBSideB])
        _eState = eGBSpotStateLose;
    else
    {
        if (_listPlayer[eGBSideA].empty() && _listPlayer[eGBSideB].empty())
            _eState = eGBSpotStateNobody;
        else
            _eState = eGBSpotStateTie;
    }
    if (bBattle)
    {
        for (auto& pInfo : _vecInfo)
        {
            UINT64 qwRoleIDA = pInfo->GetRoleIDA();
            UINT64 qwRoleIDB = pInfo->GetRoleIDB();
            if (qwRoleIDA)
            {
                SGuildBattleSpotPlayerPtr pSpotPlayer = GetSpotPlayer(qwRoleIDA);
                if (pSpotPlayer)
                    pInfo->SetState(qwRoleIDA, pSpotPlayer->eState);
            }
            if (qwRoleIDB)
            {
                SGuildBattleSpotPlayerPtr pSpotPlayer = GetSpotPlayer(qwRoleIDB);
                if (pSpotPlayer)
                    pInfo->SetState(qwRoleIDB, pSpotPlayer->eState);
            }
        }
    }
}		// -----  end of function RefreshState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  End
//  Description:  结束该据点所有战斗
// =====================================================================================
void CGuildBattleSpot::End ()
{
    if (_eState == eGBSpotStateBattle) // 如果还没战斗结束，判定为平局
        _eState = eGBSpotStateTie;
    for (UINT8 bySide = eGBSideA; bySide <= eGBSideInvalid; ++bySide)
    {
        EGBSide eSide = static_cast<EGBSide>(bySide);
        for (auto it = _listPlayer[eSide].begin(); it != _listPlayer[eSide].end(); ++it)
        {
            CPlayerPtr pPlayer = (*it)->pPlayer.lock();
            if (pPlayer)
                pPlayer->RegenAllHP();
        }
    }
}		// -----  end of function End  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifySpotInfo
//  Description:  广播据点信息
//                通知不在 准备/战斗地图 Ready类型信息
//                报名/布阵阶段通知准备地图上人物详细信息
//                战斗阶段通知 Brief
// =====================================================================================
void CGuildBattleSpot::NotifySpotInfo(EGBState eState, UINT64 qwGuildID /* = 0 */) const
{
    TVecSpotInfo vecSpotInfoInner;
    TVecSpotInfo vecSpotInfoAll;

    //LOG_WRN << "Start NotifySpotInfo.";
    SSpotAllInfoPtr pSpotInfoAll (new SSpotAllInfo);
    if (GetAllInfo(*pSpotInfoAll))
        vecSpotInfoAll.push_back(pSpotInfoAll);

    TVecUINT64 vecMapRoleID;   // 在据点内的人员

    if (eState == eGBStateBattle) // 战斗阶段广播给所有观看者据点状态
    {
        SSpotBriefInfoPtr pSpotInfoBrief (new SSpotBriefInfo);
        if (GetAllInfo(*pSpotInfoBrief))
            vecSpotInfoInner.push_back(pSpotInfoBrief);
        for (auto it = _setOBID.begin(); it != _setOBID.end(); ++it)
        {
            vecMapRoleID.push_back(*it);
        }
    }
    else // 其他阶段发送给准备地图所有人布阵状态 
    {
        SSpotReadyInfoPtr pSpotInfoReady (new SSpotReadyInfo);
        if (GetAllInfo(*pSpotInfoReady))
            vecSpotInfoInner.push_back(pSpotInfoReady);
        CGuildBattleMgr::Instance().GetAllMapPlayers(qwGuildID, vecMapRoleID);
    }

    string strData;
    strData = g_GuildBattleProtS.BuildPkg_SpotInfoNotify(vecSpotInfoInner);
    g_Game2CenterCommC.Send_NotifyGuildInfo(qwGuildID, vecMapRoleID, strData);

    if (!vecMapRoleID.empty())
        g_GuildBattleProtS.SendClt_SpotInfoNotify(vecMapRoleID.data(), vecMapRoleID.size(), vecSpotInfoAll);
}		// -----  end of function NotifySpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyBattleInfo
//  Description:  通知战斗信息
// =====================================================================================
void CGuildBattleSpot::NotifyBattleInfo () const
{
    ostringstream strInfo;
#ifdef _DEBUG
    strInfo << "NotifyBattleInfo(" << EnumValToStr(GetType()) << "):\n";
#endif
    TVecUINT64 vecMapRoleID;   // 在据点内的人员
    for (auto it = _setOBID.begin(); it != _setOBID.end(); ++it)
    {
        strInfo << *it << ", ";
        vecMapRoleID.push_back(*it);
        //LOG_WRN << "ID: " << *it;
    }
    TVecBattleData vecBattleData;
    GetAllBattleInfo(vecBattleData);
    if (!vecMapRoleID.empty())
        g_GuildBattleProtS.SendClt_SpotBattleNotify(vecMapRoleID.data(), vecMapRoleID.size(), GetType(), vecBattleData);
    //LOG_WRN << strInfo.str();
}		// -----  end of function NotifyBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetScore
//  Description:  返回该据点的得分
// =====================================================================================
bool CGuildBattleSpot::GetScore (UINT32& dwScore, EGBSide& eWinnerSide) const
{
    bool bFinal = false;
    switch(_eState)
    {
        case eGBSpotStateWin: //胜利
            dwScore = CGuildBattleConfigMgr::Instance().GetMapScore(GetType());
            eWinnerSide = eGBSideA;
            bFinal = true;
            break;
        case eGBSpotStateLose: //失败
            dwScore = CGuildBattleConfigMgr::Instance().GetMapScore(GetType());
            eWinnerSide = eGBSideB;
            bFinal = true;
            break;
        case eGBSpotStateTie: //平局
            dwScore = 0;
            bFinal = true;
            break;
        case eGBSpotStateBattle: //战斗中
            dwScore = 0;
            bFinal = false;
            break;
        case eGBSpotStateNobody: //无人参战
            dwScore = 0;
            bFinal = true;
            break;
        default:
            break;
    }
    return bFinal;
}		// -----  end of function GetScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsPlayerHere
//  Description:  玩家是否在这里
// =====================================================================================
bool CGuildBattleSpot::IsPlayerHere (CPlayerPtr pPlayer) const
{
    for (UINT8 bySide = eGBSideA; bySide <= eGBSideInvalid; ++bySide)
    {
        EGBSide eSide = static_cast<EGBSide>(bySide);
        for (auto it = _listPlayer[eSide].begin(); it != _listPlayer[eSide].end(); ++it)
        {
            if ((*it)->pPlayer.lock() == pPlayer)
                return true;
        }
    }
    return false;
}		// -----  end of function IsPlayerHere  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetDumpInfo
//  Description:  获取调试输出的信息
// =====================================================================================
string CGuildBattleSpot::GetDumpInfo ( ) const
{
#ifndef _DEBUG
    return "";
#else
    ostringstream strInfo;
    for (UINT8 bySide = eGBSideA; bySide < eGBSideInvalid; ++bySide)
    {
        for (auto it = _listPlayer[bySide].begin(); it != _listPlayer[bySide].end(); ++it)
        {
            SGuildBattleSpotPlayerPtr pSpotPlayer = *it;
            CPlayerPtr pPlayer = pSpotPlayer->pPlayer.lock();
            strInfo << (pPlayer?pPlayer->GetName():"") << ": \t";
            strInfo << EnumValToStr(pSpotPlayer->eState) << ", " << static_cast<UINT8>(pSpotPlayer->byWinCount) << ".\n";
        }
    }
    return strInfo.str();
#endif
}		// -----  end of function GetDumpInfo  ----- //
