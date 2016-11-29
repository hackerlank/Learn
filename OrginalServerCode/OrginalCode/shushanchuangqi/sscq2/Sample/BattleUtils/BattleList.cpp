// =====================================================================================
//
//       Filename:  BattleList.cpp
//
//    Description:  战斗队列，用于战斗场地的行动队列
//
//        Version:  1.0
//        Created:  12/27/2014 04:42:16 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================


#include "BattleList.h"

#include "Random.h"

#include "BattleFighter.h"

namespace NBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  CBattleList
//  Description:  战斗队列构造函数
// =====================================================================================
CBattleList::CBattleList ():
    _dwRounds(1), _dwTurns(0)
{
}		// -----  end of function CBattleList  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CBattleList
//  Description:  战斗队列析构函数
// =====================================================================================
CBattleList::~CBattleList ()
{
}		// -----  end of function ~CBattleList  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  DumpListInfo
//  Description:  输出当前的行动队列战斗对象（仅在Debug版本开启该调试功能时有效）
// =====================================================================================
void CBattleList::DumpListInfo() const
{
#ifdef BATTLE_LIST_DEBUG
    string strInfo;
    strInfo += "Current List:\n";
    for (auto & pFighter : _vecCurFigher)
    {
        strInfo << *pFighter;
    }
    strInfo += "\n";

    strInfo += "Next List:\n";
    for (auto & pFighter : _vecNextFighter)
    {
        strInfo << *pFighter;
    }
    BATTLE_DBG << strInfo;
#endif // #ifdef BATTLE_LIST_DEBUG
}		// -----  end of function DumpListInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsEmpty
//  Description:  行动队列是否没有任何战队对象
// =====================================================================================
bool CBattleList::IsEmpty () const
{
    return _vecCurFigher.empty() && _vecNextFighter.empty();
}		// -----  end of function IsEmpty  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRounds
//  Description:  获取回合数
// =====================================================================================
UINT32  CBattleList::GetRounds() const
{ 
    return _dwRounds; 
}		// -----  end of function GetRounds  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTurns
//  Description:  获取出手数
// =====================================================================================
UINT32  CBattleList::GetTurns() const
{ 
    return _dwTurns; 
}		// -----  end of function GetTurns  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllAliveBattleFighter
//  Description:  获取所有活着的战斗对象
// =====================================================================================
void CBattleList::GetAllAliveBattleFighter(TVecBattleFighterPtr& vecBF, UINT8 bySide)
{
    size_t szCount = _vecCurFigher.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        CBattleFighter* pFighter = _vecCurFigher[szIndex];
        if (pFighter && pFighter->GetSide() == bySide)
            vecBF.push_back(pFighter);

    }
    
    szCount = _vecNextFighter.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        CBattleFighter* pFighter = _vecNextFighter[szIndex];
        if (pFighter && pFighter->GetSide() == bySide)
            vecBF.push_back(pFighter);

    }
}		// -----  end of function GetAllAliveBattleFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllAliveBattleFighter
//  Description:  获取所有活着的战斗对象
// =====================================================================================
void CBattleList::GetAllAliveBattleFighter(TVecBattleFighterPtr& vecBF)
{
    vecBF.insert(vecBF.end(), _vecCurFigher.begin(), _vecCurFigher.end());
    vecBF.insert(vecBF.end(), _vecNextFighter.begin(), _vecNextFighter.end());
}		// -----  end of function GetAllAliveBattleFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllAliveBattleFighterWithMS
//  Description:  获取所有活着的并且有该状态触发的战斗对象
// =====================================================================================
void CBattleList::GetAllAliveBattleFighterWithMS (TVecBattleFighterPtr& vecBF, EMachineState eMachineState)
{
    size_t szCount = _vecCurFigher.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        CBattleFighter* pFighter = _vecCurFigher[szIndex];
        if (pFighter && pFighter->HasStateBuff(eMachineState))
            vecBF.push_back(pFighter);

    }
    
    szCount = _vecNextFighter.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        CBattleFighter* pFighter = _vecNextFighter[szIndex];
        if (pFighter && pFighter->HasStateBuff(eMachineState))
            vecBF.push_back(pFighter);

    }
}		// -----  end of function GetAllAliveBattleFighterWithMS  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllAliveBattleFighterWithMS
//  Description:  获取所有活着的并且有该状态触发的战斗对象
// =====================================================================================
void CBattleList::GetAllAliveBattleFighterWithMS (TVecBattleFighterPtr& vecBF, UINT8 bySide, EMachineState eMachineState)
{
    size_t szCount = _vecCurFigher.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        CBattleFighter* pFighter = _vecCurFigher[szIndex];
        if (pFighter 
                && pFighter->GetSide() == bySide 
                && pFighter->HasStateBuff(eMachineState))
            vecBF.push_back(pFighter);

    }
    
    szCount = _vecNextFighter.size();
    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
    {
        CBattleFighter* pFighter = _vecNextFighter[szIndex];
        if (pFighter 
                && pFighter->GetSide() == bySide 
                && pFighter->HasStateBuff(eMachineState))
            vecBF.push_back(pFighter);

    }
}		// -----  end of function GetAllAliveBattleFighterWithMS  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PopCurrentFighter
//  Description:  从行动队列中取下一个战斗对象
// =====================================================================================
CBattleFighter* CBattleList::PopCurrentFighter(bool& bNewRound)
{
    if (IsEmpty())
        return NULL;

    if (_vecCurFigher.empty())
        _vecCurFigher.swap(_vecNextFighter);

    CBattleFighter* pBF = *(_vecCurFigher.begin());
    _vecCurFigher.erase(_vecCurFigher.begin());

    if(_vecCurFigher.empty())   // 一轮结束
    {
        ++ _dwRounds;
        bNewRound = true;
    }
    else
        bNewRound = false;
    ++ _dwTurns;

    return pBF;
}		// -----  end of function PopCurrentFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PushFighterToNext
//  Description:  将该战斗对象放入下一回合的行动队列
// =====================================================================================
void CBattleList::PushFighterToNext(CBattleFighter* pFighter)
{
    if(!pFighter || pFighter->GetHP() == 0)
        return;
    size_t szCount = _vecNextFighter.size();
    size_t szIndex = 0;
    for(szIndex = 0; szIndex < szCount; ++ szIndex)
    {
        CBattleFighter* pFighterOrigin = _vecNextFighter[szIndex];
        if(pFighter->GetSpeed() > pFighterOrigin->GetSpeed())
            break;
        else if(pFighter->GetSpeed() == pFighterOrigin->GetSpeed()
                && pFighter->GetPos() > pFighterOrigin->GetPos())
            break;
    }
    _vecNextFighter.insert(_vecNextFighter.begin() + szIndex, pFighter);
}		// -----  end of function PushFighterToNext  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InsertFighterToCurrent
//  Description:  将该战斗对象放入本回合的行动队列
// =====================================================================================
void CBattleList::InsertFighterToCurrent(CBattleFighter* pFighter)
{
    if(!pFighter || pFighter->GetHP() == 0)
        return;

    size_t szCount = _vecCurFigher.size();
    size_t szIndex = 0;
    for(szIndex = 0; szIndex < szCount; ++ szIndex)
    {
        CBattleFighter* pFighterOrigin = _vecCurFigher[szIndex];
        if(pFighter->GetSpeed() > pFighterOrigin->GetSpeed())
            break;
        else if(pFighter->GetSpeed() == pFighterOrigin->GetSpeed()
                && pFighter->GetPos() > pFighterOrigin->GetPos())
            break;
    }
    _vecCurFigher.insert(_vecCurFigher.begin() + szIndex, pFighter);
}		// -----  end of function InsertFighterToCurrent  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemoveFighter
//  Description:  移除战斗对象
// =====================================================================================
void CBattleList::RemoveFighter(CBattleFighter* pFighter)
{
    for(size_t i = 0; i < _vecCurFigher.size();)
    {
        if(pFighter == _vecCurFigher[i])
            _vecCurFigher.erase(_vecCurFigher.begin() + i);
        else
            ++i;
    }

    for(size_t i = 0; i < _vecNextFighter.size();)
    {
        if(pFighter == _vecNextFighter[i])
            _vecNextFighter.erase(_vecNextFighter.begin() + i);
        else
            ++i;
    }
}		// -----  end of function RemoveFighter  ----- //

} // namespace NBattle

