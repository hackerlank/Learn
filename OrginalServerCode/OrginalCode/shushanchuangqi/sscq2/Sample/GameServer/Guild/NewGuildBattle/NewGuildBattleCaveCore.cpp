// =====================================================================================
//
//       Filename:  NewGuildBattleCaveCore.cpp
//
//    Description:  新帮派战洞府阵眼
//
//        Version:  1.0
//        Created:  03/20/2015 04:21:54 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattleCaveCore.h"
#include "NewGuildBattleConfig.h"
#include "NewGuildBattlePlayer.h"

namespace NNewGuildBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  CCaveCore
//  Description:  构造函数
// =====================================================================================
CCaveCore::CCaveCore (ENGBCaveCore eType):
    _eType(eType), _byResSpeed(0)
{
    _byResSpeed = CConfigMgr::Instance().GetCaveCoreResSpeed(_eType);
}		// -----  end of function CCaveCore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CCaveCore
//  Description:  析构函数
// =====================================================================================
CCaveCore::~CCaveCore ()
{
}		// -----  end of function ~CCaveCore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetType
//  Description:  获取阵眼类型
// =====================================================================================
ENGBCaveCore CCaveCore::GetType () const
{
    return _eType;
}		// -----  end of function GetType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetName
//  Description:  获取灵山名字
// =====================================================================================
string CCaveCore::GetName () const
{
    string strName = "???";
    switch (GetType())
    {
        case eNGBCCDragon: //青龙
            strName =  "青龙";
            break;
        case eNGBCCTiger: //白虎
            strName =  "白虎";
            break;
        case eNGBCCPhenix: //朱雀
            strName =  "朱雀";
            break;
        case eNGBCCTurtle: //玄武
            strName =  "玄武";
        break;
        default:
            break;
    }
    return strName;
}		// -----  end of function GetName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetResSpeed
//  Description:  获取资源增长速率 
// =====================================================================================
UINT8 CCaveCore::GetResSpeed () const
{
    return _byResSpeed;
}		// -----  end of function GetResSpeed  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetOwner
//  Description:  获取占领者
// =====================================================================================
CPlayerPtr CCaveCore::GetOwner () const
{
    return _pOwner;
}		// -----  end of function GetOwner  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取所有信息
// =====================================================================================
bool CCaveCore::GetAllInfo (SCaveCoreInfo& rInfo) const
{
    rInfo.eType = GetType();
    if (_pOwner)
    {
        SPlayerPanelInfo sInfo;
        if (_pOwner->GetAllPanelInfo(sInfo))
            rInfo.vecPlayerInfo.push_back(sInfo);
    }
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetOwner
//  Description:  设置所有者
// =====================================================================================
void CCaveCore::SetOwner (CPlayerPtr pPlayer)
{
    _pOwner = pPlayer;
}		// -----  end of function SetOwner  ----- //

} // namespace NNewGuildBattle

