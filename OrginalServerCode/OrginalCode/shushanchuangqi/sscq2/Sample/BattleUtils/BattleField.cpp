#include "Random.h"

#include "BattleTypeDef.h"

#include "BattleField.h"
#include "BattleFighter.h"
#include "BattleArea.h"
#include "BattleDebugger.h"
#include "BattleSkill.h"

namespace NBattle
{

//   根据对位选择横排目标顺序表
#ifdef BIG_POS
// 曾经的5*5大场地
static const UINT8 s_bySelectTable[5][5] = 
{
    {0 , 1 , 2 , 3 , 4},
    {1 , 0 , 2 , 3 , 4},
    {2 , 1 , 3 , 0 , 4},
    {3 , 2 , 4 , 1 , 0},
    {4 , 3 , 2 , 1 , 0},
};
#else
// 现在游戏用的3*3小场地
static const UINT8 s_bySelectTable[3][3] = 
{
    {0 , 1 , 2},
    {1 , 0 , 2},
    {2 , 1 , 0},
};
#endif

// ===  FUNCTION  ======================================================================
//         Name:  CBattleField
//  Description:  构造函数
// =====================================================================================
CBattleField::CBattleField():
    _eResult(EBResultNone), _pScene(NULL)
{
    ClearSide(0);
    ClearSide(1);
}		// -----  end of function CBattleField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CBattleField
//  Description:  析构函数
// =====================================================================================
CBattleField::~CBattleField()
{
}		// -----  end of function ~CBattleField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetObject
//  Description:  设置战斗对象
// =====================================================================================
bool CBattleField::SetObject(CBattleFighterPtr pBF, EBattleFieldDest eDest)
{
    bool bRet = false;
    if(!pBF)
        return bRet;
    switch(eDest)
    {
        case eBFDNormal:
            if (pBF->GetPos() < MAX_POS)
                bRet = SetFieldObject(pBF);
            else
            {
                switch (pBF->GetPos())
                {
                    case PET_POS:
                        bRet = SetPet(pBF);
                        break;
                    case BEAUTY_POS:
                        bRet = SetBeautyObject(pBF);
                        break;
                    default:
                        break;
                }
            }
            break;
        case eBFDSummon:
            bRet = SetSummon(pBF);
            break;
        case eBFDScene:
            bRet = SetScene(pBF);
            break;
        default:
            break;
    }
    return bRet;
}		// -----  end of function SetObject  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetFieldObject
//  Description:  设置战场打架的战斗对象
// =====================================================================================
bool CBattleField::SetFieldObject (CBattleFighterPtr pBF)
{
    if (!pBF)
        return false;

    UINT8 bySide = pBF->GetSide();
    if (pBF->GetHP() > 0)
    {
        UINT8 byPos = pBF->GetPos();
        pBF->UpdateIndex();
        _pObjects[bySide][byPos] = pBF;
        ++ _byAliveCount[bySide];
        InsertFighterToCurrent(pBF.get());
        return true;
    }
    else
    {
        _setDeadFighter[bySide].insert(pBF);
        return false;
    }
}		// -----  end of function SetFieldObject  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetSummon
//  Description:  设置召唤物战斗对象
// =====================================================================================
bool CBattleField::SetSummon(CBattleFighterPtr pBF)
{
    if (!pBF)
        return false;
    if (_mapSummons.find(pBF->GetID()) != _mapSummons.end())
        return false;
    _mapSummons[pBF->GetID()] = pBF;
    return true;
}		// -----  end of function SetSummon  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetScene
//  Description:  设置场景技能的对象
// =====================================================================================
bool CBattleField::SetScene(CBattleFighterPtr pBF)
{
    if (pBF)
        pBF->UpdateIndex();
    _pScene = pBF;
    return true;
}		// -----  end of function SetScene  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetPet
//  Description:  设置阵灵战斗对象
// =====================================================================================
bool CBattleField::SetPet (CBattleFighterPtr pFighter)
{
    UINT8 bySide = pFighter->GetSide();
    if (bySide > eBSideMax)
        return false;
    _pPet[bySide] = pFighter;
    pFighter->UpdateIndex();
    pFighter->ResetPassiveSkillCD();
    return true;
}		// -----  end of function SetPet  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSummonFighter
//  Description:  获取指定ID的召唤物对象
// =====================================================================================
CBattleFighterPtr CBattleField::GetSummonFighter(UINT16 wFighterID)
{
    auto it = _mapSummons.find(wFighterID);
    if (it == _mapSummons.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetSummonFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFighterByID
//  Description:  根据ID寻找对应的战斗对象
// =====================================================================================
CBattleFighter* CBattleField::GetFighterByID (UINT8 bySide, UINT8 byTeamID, UINT16 wID)
{
    if(bySide >= eBSideMax)
        return NULL;
    for(UINT8 byIndex = 0; byIndex < MAX_POS; ++ byIndex)
    {
        CBattleFighter* pBO = GetObject(bySide, byIndex);
        if (pBO && pBO->GetTeamID() == byTeamID && pBO->GetID() == wID)
            return pBO;
    }
    return NULL;
}		// -----  end of function GetFighterByID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetObject
//  Description:  获取该位置上的战斗对象
// =====================================================================================
CBattleFighter* CBattleField::GetObject(UINT8 bySide, UINT8 byPos)
{
    if (byPos >= MAX_POS)
        return  NULL;
    return _pObjects[bySide][byPos].get();
}		// -----  end of function GetObject  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetScene
//  Description:  获取场景技能的对象
// =====================================================================================
CBattleFighter* CBattleField::GetScene()
{
    return _pScene.get();
}		// -----  end of function GetScene  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPet
//  Description:  获取阵灵战斗对象
// =====================================================================================
CBattleFighter* CBattleField::GetPet (UINT8 bySide)
{
    if(bySide >= eBSideMax)
        return NULL;
    return _pPet[bySide].get();
}		// -----  end of function GetPet  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPossibleTarget
//  Description:  根据攻击方的站位获取对面可能的目标
// =====================================================================================
CBattleFighter* CBattleField::GetPossibleTarget(CBattleFighter* pBF, function<bool (CBattleFighter* pBO)> func)
{
    if(!pBF)
        return NULL;

    UINT8 bySide = pBF->GetSide();
    UINT8 byPos = pBF->GetPos();

    UINT8 byTargetIdx = LINE_LEN - (byPos % LINE_LEN) - 1;
    UINT8 byTargetSide = 1 - bySide;

    // 先寻找统一纵列里面是否有对应目标
    for(UINT8 byRow = 0; byRow < ROW_LEN; ++ byRow)
    {
        UINT8 byTIdx = byRow * LINE_LEN + byTargetIdx;
        CBattleFighter* pFighter = _pObjects[byTargetSide][byTIdx].get();
        if(pFighter && pFighter->GetHP() > 0 && func(pFighter))
            return pFighter;
    }

    // 找不到纵列找最近的横列
    const UINT8 * szTbl = s_bySelectTable[byTargetIdx];
    for(UINT8 byIndex = 0; byIndex < ROW_LEN; ++ byIndex)
    {
        for(UINT8 j = 0; j < LINE_LEN; ++ j)
        {
            UINT8 byTIdx = szTbl[j] + byIndex * LINE_LEN;
            CBattleFighter* pFighter = _pObjects[byTargetSide][byTIdx].get();
            if(pFighter && pFighter->GetHP() > 0 && func(pFighter))
                return pFighter;
        }
    }

    return NULL;
}		// -----  end of function GetPossibleTarget  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSelfPossibleTarget
//  Description:  根据攻击方的站位获取己方可能的一个目标
// =====================================================================================
CBattleFighter* CBattleField::GetSelfPossibleTarget(CBattleFighter* pBF, function<bool (CBattleFighter* pBO)> func)
{
    if(!pBF)
        return NULL;

    UINT8 bySide = pBF->GetSide();
    UINT8 byPos = pBF->GetPos();

    UINT8 byTargetIdx = LINE_LEN - (byPos % LINE_LEN) - 1;
    UINT8 byTargetSide = bySide;

    // 先寻找统一纵列里面是否有对应目标
    for(UINT8 byRow = 0; byRow < ROW_LEN; ++ byRow)
    {
        UINT8 byTIdx = byRow * LINE_LEN + byTargetIdx;
        CBattleFighter* pFighter = _pObjects[byTargetSide][byTIdx].get();
        if(pFighter && pFighter->GetHP() > 0 && func(pFighter))
            return pFighter;
    }

    // 找不到纵列找最近的横列
    const UINT8 * szTbl = s_bySelectTable[byTargetIdx];
    for(UINT8 byIndex = 0; byIndex < ROW_LEN; ++ byIndex)
    {
        for(UINT8 j = 0; j < LINE_LEN; ++ j)
        {
            UINT8 byTIdx = szTbl[j] + byIndex * LINE_LEN;
            CBattleFighter* pFighter = _pObjects[byTargetSide][byTIdx].get();
            if(pFighter && pFighter->GetHP() > 0 && func(pFighter))
                return pFighter;
        }
    }

    return NULL;
}		// -----  end of function GetSelfPossibleTarget  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSelfPossibleTargets
//  Description:  根据攻击方的站位获取己方可能的多个目标
// =====================================================================================
bool CBattleField::GetSelfPossibleTargets(UINT8 bySide, TVecBattleFighterPtr& vecFighters, function<bool (CBattleFighter* pBO)> func)
{
    bool bRet = false;

    for(UINT8 byIndex = 0; byIndex < MAX_POS; ++ byIndex)
    {
        CBattleFighter* pBO = GetObject(bySide, byIndex);
        if(pBO && func(pBO))
        {
            vecFighters.push_back(pBO);
            bRet = true;
        }
    }
    return bRet;
}		// -----  end of function GetSelfPossibleTargets  ----- //


// ===  FUNCTION  ======================================================================
//         Name:  TrySummonAppear
//  Description:  尝试召唤出指定战斗对象
// =====================================================================================
bool CBattleField::TrySummonAppear(UINT8 bySide, UINT8 byPos, CBattleFighterPtr pFighter, UINT8 bySumonLast)
{
    if (!pFighter)
        return false;

    // 在随机空位召唤
    if (byPos == DEFAULT_POS)
    {
        TVecUINT8 vecEmptyPos;

        // 找不到空位召唤了
        if (!GetEmptyPos(bySide, vecEmptyPos) || vecEmptyPos.empty())
            return false;

        byPos = vecEmptyPos[CRandom::RandInt(0, vecEmptyPos.size() - 1)];
    }
    // 指定位置召唤
    else if (GetObject(bySide, byPos)) 
        return false; // 已经有人了

    pFighter->SetPos(byPos);
    pFighter->SetSide(bySide);
    pFighter->UpdateIndex();

    pFighter->RegenAllHP();

    pFighter->SetSummonLast(bySumonLast);

    SetObject(pFighter, eBFDNormal);

    return true;
}		// -----  end of function TrySummonAppear  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  TryRelive
//  Description:  尝试召唤出指定战斗对象
// =====================================================================================
bool CBattleField::TryRelive(CBattleFighter* pFighter, FLOAT fHPFactor)
{
    if (!pFighter)
        return false;
    UINT8 bySide = pFighter->GetSide();
    if (bySide > eBSideMax)
        return false;
    bool bFound = false;
    CBattleFighterPtr pBattleFighter;
    for (auto& pBF : _setDeadFighter[bySide])
    {
        if (pFighter == pBF.get())
        {
            bFound = true;
            pBattleFighter = pBF;
            break;
        }
    }
    if (!bFound)
        return false;
    _setDeadFighter[bySide].erase(pBattleFighter);
    UINT32 dwHP = static_cast<UINT32>(pFighter->GetMaxHP() * fHPFactor);
    if (!dwHP)
        dwHP = 1;

    pFighter->RegenHP(dwHP);

    SetObject(pBattleFighter, eBFDNormal);

    PushFighterToNext(pFighter);
    ++_byAliveCount[bySide];

    return true;
}		// -----  end of function TryRelive  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnDead
//  Description:  战场有人死亡
// =====================================================================================
bool CBattleField::OnDead(CBattleFighter* pFighter, TVecUINT8& rvecCombineIndex)
{
    if(!pFighter)
        return false;

    RemoveFighter(pFighter);
    RemoveCombineFighter(pFighter, rvecCombineIndex);

    UINT8 bySide = pFighter->GetSide();
    UINT8 byPos = pFighter->GetPos();
    pFighter->SetHP(0);
    if (_pObjects[bySide][byPos])
    {
        _setDeadFighter[bySide].insert(_pObjects[bySide][byPos]);
        _pObjects[bySide][byPos] = NULL;
        -- _byAliveCount[bySide];
    }

    if(_byAliveCount[bySide] == 0)
    {
        if (bySide == 0)
            _eResult = EBResultDefenseWin;
        else
            _eResult = EBResultAttackWin;
    }
    return true;
}		// -----  end of function OnDead  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetBattleFighterBuff
//  Description:  
// =====================================================================================
void CBattleField::ResetBattleFighterBuff ()
{
    for (UINT8 bySide = 0; bySide < eBSideMax; ++ bySide)
    {
        for (UINT8 byPos =  0; byPos < MAX_POS; ++ byPos)
        {
            if (_pObjects[bySide][byPos])
                _pObjects[bySide][byPos]->ResetBuff();
        }
    }
    for (auto& pFighter : _setDeadFighter[0])
    {
        if (pFighter)
            pFighter->ResetBuff();
    }
    for (auto& pFighter : _setDeadFighter[1])
    {
        if (pFighter)
            pFighter->ResetBuff();
    }
}		// -----  end of function ResetBattleFighterBuff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetResult
//  Description:  获得战场的胜负情况
// =====================================================================================
EBattleResult   CBattleField::GetResult() const
{ 
    if (_eResult == EBResultNone)
    {
        for (UINT8 bySide = 0; bySide < eBSideMax; ++bySide)
        {
            if(_byAliveCount[bySide] == 0)
            {
                if (bySide == 0)
                    _eResult = EBResultDefenseWin;
                else
                    _eResult = EBResultAttackWin;
                break;
            }
        }
    }
    return _eResult; 
}		// -----  end of function GetResult  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsPet
//  Description:  是否是阵灵
// =====================================================================================
bool  CBattleField::IsPet (CBattleFighter* pBF) const
{
    if (!pBF)
        return false;
    if (pBF == _pPet[0].get() || pBF == _pPet[1].get())
        return true;
    else
        return false;
}		// -----  end of function IsPet  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTargetList
//  Description:  根据范围类型获取相应的目标
// =====================================================================================
void CBattleField::GetTargetList(CBattleFighter* pBF, CBattleFighter* pBO, UINT16 wAreaID, 
        TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID)
{
    // 先特殊范围的特殊化处理
    if (GetSpecialTargetList(pBF, pBO, wAreaID, rvecAttacker, rvecPos, rAreaID))
        return;

    CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(wAreaID);
    if (!pArea)
    {
        LOG_WRN << "Invalid AreaID: " << wAreaID << ".";
        return;
    }

    switch (pArea->GetSelectType())
    {
        case eAreaSelectMirro: // 镜像或者自己
        case eAreaSelectResponse: // 反馈对象
        case eAreaSelectID: // 指定ID的散仙，只能自己对应自己
            break;
        default:
            if (rAreaID && wAreaID == rAreaID)
            {
#ifdef BATTLE_SKILL_AREA
                BATTLE_DBG << "AreaID: " << wAreaID << " == rAreaID.";
#endif
                return;
            }
    }
    rvecAttacker.clear();
    rvecPos.clear();
    rAreaID = wAreaID;
    UINT8 bySelfSide = pBF->GetSide();

#ifdef BATTLE_SKILL_AREA
    BATTLE_DBG << "AreaID: " << wAreaID << "." << "SelectType: " << static_cast<UINT32>(pArea->GetSelectType()) << "."
        " PosSize = " << pArea->GetPosFactorSize() << ", RepeactSize = " << pArea->GetRepeatFactorSize() << ".";
#endif

    TVecBattleFighterPtr vecFighters;   // 已经选择过的目标
    TVecUINT8 vecEmptyPos;              // 已经选择过的空位

    for (UINT8 byRepeatIndex = 0; byRepeatIndex < pArea->GetRepeatFactorSize(); ++byRepeatIndex)
    {
        UINT8 byTargetSide = GetTargetSide(pArea->GetSide(), bySelfSide);
        bool bNeedPos = false; // 是否需要空位目标
        UINT8 byX = 0;
        UINT8 byY = 0;
        bool bRet = GetAreaFirstTarget(pArea, bySelfSide, byTargetSide, pBF, pBO,
                byX, byY, bNeedPos, vecFighters, vecEmptyPos);

        if (!bRet) // 完全没找到目标
            break;

#ifdef BATTLE_SKILL_AREA
        BATTLE_DBG << "Target X: " << static_cast<UINT32>(byX) << ", Y: " << static_cast<UINT32>(byY) << ".";
#endif
        TVecAttacker vecAttackerTmp;
        UINT8 byMainTarget = pArea->GetMainTargetType();
        for (UINT8 byPosIndex = 0; byPosIndex < pArea->GetPosFactorSize(); ++byPosIndex)
        {
            INT16 wTargetX = byX;
            INT16 wTargetY = byY;

            const CBattleArea::SPos& rPos = pArea->GetPos(byPosIndex);
            wTargetX = wTargetX + rPos.byX;
            wTargetY = wTargetY + rPos.byY;
            if (wTargetX < 0 || wTargetX >= ROW_LEN
                    || wTargetY < 0 || wTargetY >= LINE_LEN)
                continue;

            UINT8 byPos = static_cast<UINT8>(wTargetX) + static_cast<UINT8>(wTargetY) * LINE_LEN;
            CBattleFighter* pTarget = GetObject(byTargetSide, byPos);
            if (pTarget)
            {
                SAttacker sAttacker;
                sAttacker._pBO = pTarget;
                sAttacker._fFactor = pArea->GetPosFactor(byPosIndex);
                sAttacker._byMainTarget = byMainTarget;
                if (byMainTarget == 1)
                    byMainTarget = 0;
                vecAttackerTmp.push_back(sAttacker);
#ifdef BATTLE_SKILL_AREA
                string strInfo;
                BATTLE_DBG << "Attack Target X: " << (strInfo << *pTarget) << ".";
#endif
            }
            else if (bNeedPos)
            {
                SFieldPos sPos;
                sPos.bMainTarget = byMainTarget ? true : false;
                if (byMainTarget == 1)
                    byMainTarget = 0;
                sPos.fFactor = pArea->GetPosFactor(byPosIndex);
                sPos.byPos = wTargetX + wTargetY * ROW_LEN;
                sPos.byGroupID = byTargetSide;
                rvecPos.push_back(sPos);
#ifdef BATTLE_SKILL_AREA
                BATTLE_DBG << "Pos Target X: " << static_cast<UINT32>(byX) << ", Y: " << static_cast<UINT32>(byY) << ".";
#endif
            }
        }

        // 根据范围命中人数重新调整伤害系数
        UINT8 bySize = vecAttackerTmp.size();
        for (UINT8 byPosIndex = 0; byPosIndex < vecAttackerTmp.size(); ++byPosIndex)
        {
            vecAttackerTmp[byPosIndex]._fFactor = pArea->GetPosFactor(bySize, byPosIndex);
        }
        rvecAttacker.insert(rvecAttacker.end(), vecAttackerTmp.begin(), vecAttackerTmp.end());
    }
}		// -----  end of function GetTargetList  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpecialTargetList
//  Description:  根据指定ID写死目标的选择方式（！@#￥%……&*（））
//                (#‵′)凸
// =====================================================================================
bool CBattleField::GetSpecialTargetList (CBattleFighter* pBF, CBattleFighter* pBO, UINT16 wAreaID, 
        TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID)
{
    bool bRet = false;
    switch (wAreaID)
    {
        case 119:
            {
                CBattleAreaPtr pArea = CBattleAreaMgr::Instance().GetArea(wAreaID);
                if (!pArea)
                {
                    LOG_WRN << "Invalid AreaID: " << wAreaID << ".";
                    break;
                }

                rvecAttacker.clear();
                rvecPos.clear();
                rAreaID = wAreaID;
                UINT8 bySelfSide = pBF->GetSide();

#ifdef BATTLE_SKILL_AREA
                BATTLE_DBG << "AreaID: " << wAreaID << "." << "SelectType: " << static_cast<UINT32>(pArea->GetSelectType()) << "."
                    " PosSize = " << pArea->GetPosFactorSize() << ", RepeactSize = " << pArea->GetRepeatFactorSize() << ".";
#endif

                TVecBattleFighterPtr vecFighters;   // 已经选择过的目标


                for (UINT8 byRepeatIndex = 0; byRepeatIndex < pArea->GetRepeatFactorSize(); ++byRepeatIndex)
                {
                    UINT8 byTargetSide = GetTargetSide(pArea->GetSide(), bySelfSide);

                    CBattleFighter* pTarget = GetHPPMinTarget2(byTargetSide, vecFighters);
                    if (pTarget)
                    {
                        if (vecFighters.empty()
                                || vecFighters[0] != pTarget)
                            vecFighters.push_back(pTarget);
                    }

                    UINT8 byMainTarget = pArea->GetMainTargetType();
                    if (pTarget)
                    {
                        SAttacker sAttacker;
                        sAttacker._pBO = pTarget;
                        sAttacker._fFactor = pArea->GetPosFactor(0);
                        sAttacker._byMainTarget = byMainTarget;
                        if (byMainTarget == 1)
                            byMainTarget = 0;
                        rvecAttacker.push_back(sAttacker);
#ifdef BATTLE_SKILL_AREA
                        string strInfo;
                        BATTLE_DBG << "Attack Target X: " << (strInfo << *pTarget) << ".";
#endif
                    }
                }
            }

            break;
        default:
            break;
    }

    return bRet;
}		// -----  end of function GetSpecialTargetList  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAreaFirstTarget
//  Description:  获取范围的首选目标
// =====================================================================================
bool CBattleField::GetAreaFirstTarget (CBattleAreaPtr pArea, UINT8 bySelfSide, UINT8 byTargetSide,
        CBattleFighter* pBF, CBattleFighter* pBO,
        UINT8& rX, UINT8& rY, bool& rNeedPos, TVecBattleFighterPtr& rvecFighters, TVecUINT8& rvecEmptyPos)
{
    if (!pArea)
        return false;
    if (bySelfSide >= eBSideMax)
        return false;

    CBattleFighter* pTarget = NULL;
    rNeedPos = false;
    switch(pArea->GetSelectType())
    {
        case eAreaSelectDefault:    // 默认选择方式（敌方最近目标/我方自己）
            if (byTargetSide != bySelfSide)
                pTarget = GetPossibleTarget(pBF, IsTargetCanBeAttacked);
            else
            {
                if (pBF->GetPos() < MAX_POS) // 在战斗阵型中的才选择自己
                    pTarget = pBF;
                else // 不在阵型中，随机选择一个阵型中的
                {
                    TVecBattleFighterPtr vecBattleFighterPtr;
                    pTarget = GetRandomTarget(byTargetSide, vecBattleFighterPtr);

                }
            }
            rNeedPos = false;
            break;
        case eAreaSelectDefaultPos:    // 默认选择方式（敌方最近目标/我方自己）
            if (byTargetSide != bySelfSide)
                pTarget = GetPossibleTarget(pBF, IsTargetCanBeAttacked);
            else
            {
                if (pBF->GetPos() < MAX_POS) // 在战斗阵型中的才选择自己
                    pTarget = pBF;
                else // 不在阵型中，随机选择一个阵型中的
                {
                    TVecBattleFighterPtr vecBattleFighterPtr;
                    pTarget = GetRandomTarget(byTargetSide, vecBattleFighterPtr);

                }
            }
            rNeedPos = true;
            break;
        case eAreaSelectAbsolute:   // 根据配置选择绝对坐标
            {
                const CBattleArea::SPos& rPos = pArea->GetPos(0);
                if (rPos.byX >= 0)
                    rX = rPos.byX;
                if (rPos.byY >= 0)
                    rY = rPos.byY;
                rNeedPos = true;
            }
            break;
        case eAreaSelectRandom:     // 随机选取目标方向的任意目标
            {
                TVecBattleFighterPtr vecExcpFgtOut;
                pTarget = GetRandomTarget(byTargetSide, vecExcpFgtOut);
            }
            break;
        case eAreaSelectRandomPos:  // 随机坐标
            rX = CRandom::RandInt(0, ROW_LEN - 1);
            rY = CRandom::RandInt(0, LINE_LEN - 1);
            rNeedPos = true;
            break;
        case eAreaSelectRandomEpt: // 随机选择空位
            {
                TVecUINT8 vecPos;
                if (GetEmptyPos(byTargetSide, vecPos))
                {
                    if (!vecPos.empty())
                    {
                        UINT8 byIndex = CRandom::RandInt(0, vecPos.size() - 1);
                        UINT8 byPos = vecPos[byIndex];
                        rX = byPos % LINE_LEN;
                        rY = byPos / LINE_LEN;
                        rNeedPos = true;
                    }
                }
            }
            break;
        case eAreaSelectMirro: // 镜像或者自己
            if (byTargetSide != bySelfSide)
                pTarget = GetObject(byTargetSide, pBF->GetPos());
            else
                pTarget = pBF;
            break;
        case eAreaSelectResponse: // 反馈对象
            pTarget = pBO;
            break;
        case eAreaSelectHPPMin: // 生命比率最低
            pTarget = GetHPPMinTarget(byTargetSide);
            break;
        case eAreaSelectRandomCnt: // 随机选择，优先选择目标，//然后选择空位（目标不重复）
            pTarget = GetRandomTarget(byTargetSide, rvecFighters);
            if (pTarget)
                rvecFighters.push_back(pTarget);
            /*
            else
            {
                rNeedPos = GetRandomEmptyPos(byTargetSide, rX, rY, rvecEmptyPos);
                if (rNeedPos)
                    rvecEmptyPos.push_back(rX + rY * LINE_LEN);
            }  
            */
            break;
        case eAreaSelectRandomCtrl: // 随机选择控制目标
            {
                TVecBattleFighterPtr vecTargets;
                GetSelfPossibleTargets(pBF->GetSide(), vecTargets, IsTargetControled);
                if (!vecTargets.empty())
                    pTarget = vecTargets[CRandom::RandInt(0, vecTargets.size() - 1)];
            }
            break;
        case eAreaSelectRandomHPLost: // 随机选择HP不满的
            {
                TVecBattleFighterPtr vecTargets;
                GetSelfPossibleTargets(pBF->GetSide(), vecTargets, IsTargetHPLost);
                if (!vecTargets.empty())
                    pTarget = vecTargets[CRandom::RandInt(0, vecTargets.size() - 1)];
            }
            break;
        case eAreaSelectID: // 指定ID的散仙，只能自己对应自己
            {
                TVecBattleFighterPtr vecTargets;
                GetIDTargets(byTargetSide, vecTargets, pArea->GetFighterID());
                for (auto& pFighter : vecTargets)
                {
                    if (pFighter->GetID() == pBF->GetID())
                    {
                        pTarget = pFighter;
                        break;
                    }
                }
            }
            break;
        default:
            break;
    }

    if (pTarget)
    {
        UINT8 byPos = pTarget->GetPos();
        rX = byPos % LINE_LEN;
        rY = byPos / LINE_LEN;
        return true;
    }
    else if (rNeedPos)
        return true;
    else
    {
#ifdef BATTLE_SKILL_AREA
        BATTLE_DBG << "NoTarget Select.";
#endif
        return false;
    }
}		// -----  end of function GetAreaFirstTarget  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRandomTarget
//  Description:  在某个方向随机获取一个战斗对象
// =====================================================================================
CBattleFighter* CBattleField::GetRandomTarget(UINT8 bySide, const TVecBattleFighterPtr& vecExcpFgtOut)
{
    TVecBattleFighterPtr vFgtOut;
    GetAllFighter (bySide, vFgtOut, vecExcpFgtOut);
    if (vFgtOut.empty())
        return NULL;

    UINT8 byRandom = CRandom::RandArrayIndex(vFgtOut.size());
    return vFgtOut[byRandom];
}		// -----  end of function GetRandomTarget  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetHPPMinTarge
//  Description:  在某个方向取得HP百分比最少的战斗对象
// =====================================================================================
CBattleFighter* CBattleField::GetHPPMinTarget(UINT8 bySide)
{
    TVecBattleFighterPtr vFgtOut;
    TVecBattleFighterPtr vecExcpFgtOut;
    GetAllFighter (bySide, vFgtOut, vecExcpFgtOut);
    CBattleFighter* pTarget = NULL;
    for (auto& pFighter : vFgtOut)
    {
        if (!pTarget)
        {
            if (pFighter && pFighter->GetHP() > 0)
                pTarget = pFighter;
            else
                continue;
        }
        else if (pFighter && pFighter->GetHP() > 0 
                && (pFighter->GetHPP() < pTarget->GetHPP()))
            pTarget = pFighter;
    }
    return pTarget;
}		// -----  end of function GetHPPMinTarge  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetHPPMinTarget2
//  Description:  先获取血最少的目标两次，然后获取血最少的目标一次（总共就三次）
//                这是为Area 119单独写的
// =====================================================================================
CBattleFighter* CBattleField::GetHPPMinTarget2 (UINT8 bySide, const TVecBattleFighterPtr& vecExcpFgtOut)
{
    CBattleFighter* pTarget = NULL;
    TVecBattleFighterPtr vFgtOut;
    switch(vecExcpFgtOut.size())
    {
        case 1:
            GetAllFighter (bySide, vFgtOut, vecExcpFgtOut);
            for (auto& pFighter : vFgtOut)
            {
                if (!pFighter || pFighter == vecExcpFgtOut[0])
                    continue;
                if (!IsTargetHPLost(pFighter))
                    continue;

                if (!pTarget)
                {
                    if (pFighter && pFighter->GetHP() > 0)
                        pTarget = pFighter;
                    else
                        continue;
                }
                else if (pFighter && pFighter->GetHP() > 0 
                        && (pFighter->GetHPP() < pTarget->GetHPP()))
                    pTarget = pFighter;
            }
            if (!pTarget)
                pTarget = vecExcpFgtOut[0];
            break;
        case 0:
        case 2:
            pTarget = GetHPPMinTarget(bySide);
            break;
        default:
            LOG_CRI << "???";
            break;
    }

    return pTarget;
}		// -----  end of function GetHPPMinTarget2  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetIDTargets
//  Description:  获取指定ID的战斗对象
// =====================================================================================
bool CBattleField::GetIDTargets(UINT8 bySide, TVecBattleFighterPtr& vecFighters, const TSetUINT16& rsetFighterID)
{
    if (bySide >= eBSideMax)
        return false;
    for (auto & rID : rsetFighterID)
    {
        for(UINT8 byIndex = 0; byIndex < MAX_POS; ++ byIndex)
        {
            CBattleFighter* pBO = GetObject(bySide, byIndex);
            if(pBO && pBO->GetID() == rID)
                vecFighters.push_back(pBO);
        }
    }
    return true;
}		// -----  end of function GetIDTargets  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSideAliveTargets
//  Description:  获取指定方向所有存活的对象
// =====================================================================================
bool CBattleField::GetSideAliveTargets (UINT8 bySide, TVecBattleFighterPtr& vecFighters)
{
    return GetSelfPossibleTargets(bySide, vecFighters, IsTargetAlive);
}		// -----  end of function GetSideAliveTargets  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetEmptyPos
//  Description:  在某个方向获取所有空位
// =====================================================================================
bool CBattleField::GetEmptyPos(UINT8 bySide, TVecUINT8& rvecPos)
{
    if (bySide >= eBSideMax)
        return false;
    for(UINT8 byIndex = 0; byIndex < MAX_POS; ++ byIndex)
    {
        if(!GetObject(bySide, byIndex))
            rvecPos.push_back(byIndex);
    }
    return true;
}		// -----  end of function GetEmptyPos  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRandomEmptyPos
//  Description:  在某个方向获取随机一个不在某些空位的空位
// =====================================================================================
bool CBattleField::GetRandomEmptyPos(UINT8 bySide, UINT8& byX, UINT8& byY, const TVecUINT8& rvecPos)
{
    if (bySide >= eBSideMax)
        return false;
    TSetUINT8 setPos;
    for(UINT8 byIndex = 0; byIndex < MAX_POS; ++ byIndex)
    {
        CBattleFighter* pBO = GetObject(bySide, byIndex);
        if(!pBO)
            setPos.insert(byIndex);
    }
    for (auto & rID : rvecPos)
    {
        setPos.erase(rID);
    }
    if (setPos.empty())
        return false;
    auto it = setPos.begin();
    std::advance(it, CRandom::RandInt(0, setPos.size() - 1));
    byX = (*it) % LINE_LEN;
    byY = (*it) / LINE_LEN;
    return true;
}		// -----  end of function GetRandomEmptyPos  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearSide
//  Description:  清除某个方向的所有数据
// =====================================================================================
void CBattleField::ClearSide(UINT8 bySide)
{
    for(UINT8 byIndex = 0; byIndex < MAX_POS; ++ byIndex)
        _pObjects[bySide][byIndex] = NULL;
    _pPet[bySide] = NULL;
    _byAliveCount[bySide] = 0;
    _setDeadFighter[bySide].clear();

    ClearCombine(bySide);
    ClearFormatin(bySide);
    ClearReiatsu(bySide);
}		// -----  end of function ClearSide  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllFighter
//  Description:  获取某个方向去除特定对象后的所有对象
// =====================================================================================
void CBattleField::GetAllFighter (UINT8 bySide, TVecBattleFighterPtr& vFgtOut, const TVecBattleFighterPtr& vecExcpFgtOut)
{
    if(bySide >= eBSideMax)
        return;
    for(UINT8 byIndex = 0; byIndex < MAX_POS; ++ byIndex)
    {
        CBattleFighter* pBO = GetObject(bySide, byIndex);
        if(!pBO)
            continue;
        bool bExcp = false;
        size_t szCount = vecExcpFgtOut.size();
        for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
        {
            CBattleFighter* pFighter = vecExcpFgtOut[szIndex];
            if (pFighter == pBO)
            {
                bExcp = true;
                break;
            }
        }
        if (!bExcp)
            vFgtOut.push_back(pBO);
    }
}		// -----  end of function GetAllFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTargetSide
//  Description:  根据配置的目标方向选择方式获取目标所在的方向
// =====================================================================================
UINT8 CBattleField::GetTargetSide (EAreaSide eSideType, UINT8 bySide)
{
    UINT8 byOtherSide = 1 - bySide;
    UINT8 byTargetSide = byOtherSide;
    switch(eSideType)
    {
        case eAreaSideBoth: // 双方都有可能，随机选择一方
            if (CRandom::RandInt(0,2))
                byTargetSide = byOtherSide;
            else
                byTargetSide = bySide;
            break;
        case eAreaSideSelf:
            byTargetSide = bySide;
            break;
        case eAreaSideOther:
            byTargetSide = byOtherSide;
            break;
        default:
            break;
    }
    return byTargetSide;
}		// -----  end of function GetTargetSide  ----- //

bool IsTargetAlive(CBattleFighter* pBF)
{
    if (!pBF)
        return false;
    return pBF->GetHP()?true:false;
}

bool IsTargetCanBeAttacked(CBattleFighter* pBF)
{
    if (!pBF || !pBF->GetHP())
        return false;
    return pBF->IsHide()?false:true;
}

bool IsTargetControled(CBattleFighter* pBF)
{
    if (pBF && pBF->GetHP() && pBF->IsControled())
        return true;
    return false;

}

bool IsTargetHPLost(CBattleFighter* pBF)
{
    if (pBF && pBF->GetHP() <  pBF->GetMaxHP())
        return true;
    return false;
}

} // namespace NBattle

