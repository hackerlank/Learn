// =====================================================================================
//
//       Filename:  NewGuildBattlePuppet.cpp
//
//    Description:  新帮派战战争傀儡
//
//        Version:  1.0
//        Created:  03/20/2015 10:14:39 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattlePuppet.h"

#include "Parameter.h"

namespace NNewGuildBattle
{
// ===  FUNCTION  ======================================================================
//         Name:  CPuppet
//  Description:  构造函数
// =====================================================================================
CPuppet::CPuppet ():
    _dwNextAttackTime(0), _dwAttack(SParamConfig::wLingMountainRobotDamage)
{
}		// -----  end of function CPuppet  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CPuppet
//  Description:  析构函数
// =====================================================================================
CPuppet::~CPuppet ()
{
}		// -----  end of function ~CPuppet  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetNextAttackTime
//  Description:  获取下次攻击时间
// =====================================================================================
UINT32 CPuppet::GetNextAttackTime () const
{
    return _dwNextAttackTime;
}		// -----  end of function GetNextAttackTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAttack
//  Description:  获取傀儡攻击力
// =====================================================================================
UINT32 CPuppet::GetAttack () const
{
    return _dwAttack;
}		// -----  end of function GetAttack  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetNextAttackTime
//  Description:  设置下一次攻击时间
// =====================================================================================
void CPuppet::SetNextAttackTime (UINT32 dwTime)
{
    _dwNextAttackTime = dwTime;
}		// -----  end of function SetNextAttackTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CalcNextAttackTime
//  Description:  计算下一次攻击时间
// =====================================================================================
void CPuppet::CalcNextAttackTime ()
{
    if (_dwNextAttackTime)
        _dwNextAttackTime += SParamConfig::wLingMountainRobotCooldown;
}		// -----  end of function CalcNextAttackTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Stop
//  Description:  停止动作
// =====================================================================================
void CPuppet::Stop ()
{
    _dwNextAttackTime = 0;
}		// -----  end of function Stop  ----- //
} // namespace NNewGuildBattle

