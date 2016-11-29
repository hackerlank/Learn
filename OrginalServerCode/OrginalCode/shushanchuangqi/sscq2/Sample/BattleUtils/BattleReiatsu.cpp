// =====================================================================================
//
//       Filename:  BattleReiatsu.cpp
//
//    Description:  战斗美女灵压
//
//        Version:  1.0
//        Created:  01/03/2015 04:05:24 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "BattleReiatsu.h"

#include "BattleDebugger.h"

#include "BattleFighter.h"

namespace NBattle
{

const UINT8 FIELD_INDEX = 0;    //  场地编号

// ===  FUNCTION  ======================================================================
//         Name:  CBattleReiatsu
//  Description:  构造函数
// =====================================================================================
CBattleReiatsu::CBattleReiatsu ()
{
    memset(_pBeauty, 0, sizeof(_pBeauty));
    memset(_byReiatsu, 0, sizeof(_byReiatsu));
}		// -----  end of function CBattleReiatsu  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CBattleReiatsu
//  Description:  析构函数
// =====================================================================================
CBattleReiatsu::~CBattleReiatsu ()
{
}		// -----  end of function ~CBattleReiatsu  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBeauty
//  Description:  获取美女
// =====================================================================================
CBattleFighter* CBattleReiatsu::GetBeauty(UINT8 bySide)
{
    if (bySide >= eBSideMax)
        return NULL;
    return _pBeauty[bySide].get();
}		// -----  end of function GetBeauty  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetReiatsu
//  Description:  获取某一方的灵压
// =====================================================================================
UINT8 CBattleReiatsu::GetReiatsu(UINT8 bySide) const
{
    return _byReiatsu[bySide];
}		// -----  end of function GetReiatsu  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetBeauty
//  Description:  设置美女
// =====================================================================================
bool CBattleReiatsu::SetBeautyObject(CBattleFighterPtr pBF)
{
    if (!pBF)
        return false;
    string strInfo;
    strInfo << *pBF;
    BATTLE_DBG << "Beauty: " << strInfo << ".";
    UINT8 bySide = pBF->GetSide();
    _pBeauty[bySide] = pBF;
    pBF->UpdateIndex();
    _byReiatsu[bySide] = pBF->GetAura();
    return true;
}		// -----  end of function SetBeauty  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearFormatin
//  Description:  清除美女
// =====================================================================================
void CBattleReiatsu::ClearFormatin (UINT8 bySide)
{
    if (bySide >= eBSideMax)
        return;
    _pBeauty[bySide] = NULL;
}		// -----  end of function ClearFormatin  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearReiatsu
//  Description:  清除灵压
// =====================================================================================
void CBattleReiatsu::ClearReiatsu (UINT8 bySide)
{
    if (bySide >= eBSideMax)
        return;
    _byReiatsu[bySide] = 0;
}		// -----  end of function ClearReiatsu  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ChangeReiatsu
//  Description:  改变某一方的灵压
// =====================================================================================
void CBattleReiatsu::ChangeReiatsu(UINT8 bySide, INT8 byReiatsu)
{
    INT32 byResult = static_cast<INT32>(byReiatsu) + _byReiatsu[bySide];
    if (byResult < 0)
        byResult = 0;
    if (static_cast<UINT32>(byResult) > MAX_REIATSU)
        byResult = MAX_REIATSU;
    _byReiatsu[bySide] = byResult;
}		// -----  end of function ChangeReiatsu  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetReiatsu
//  Description:  设置某一方的灵压
// =====================================================================================
void  CBattleReiatsu::SetReiatsu(UINT8 bySide, UINT8 byReiatsu)
{
    _byReiatsu[bySide] = byReiatsu;
#ifdef BATTLE_AURA_CHANGE    // 战斗灵气变化调试开关 
    BATTLE_DBG << "Reiatsu(" << static_cast<UINT32>(bySide) << "): " << static_cast<UINT32>(_byReiatsu[bySide]) << ".";
#endif
}		// -----  end of function SetReiatsu  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddReiatsu
//  Description:  增加某一方的灵压
// =====================================================================================
void  CBattleReiatsu::AddReiatsu(UINT8 bySide, UINT8 byReiatsu)
{
    _byReiatsu[bySide] += byReiatsu;
}		// -----  end of function AddReiatsu  ----- //

} // namespace NBattle
