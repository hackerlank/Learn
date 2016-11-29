// =====================================================================================
//
//       Filename:  GuildBattleInfo.cpp
//
//    Description:  帮派战战斗信息
//
//        Version:  1.0
//        Created:  07/24/2014 09:10:38 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "GuildBattleInfo.h"


/*
CGuildBattleInfo:: CGuildBattleInfo()
{
}		// -----  end of function CGuildBattleInfo  ----- //
*/

CGuildBattleInfo::CGuildBattleInfo (UINT64 qwBattleID,  UINT8 byIndex, 
        const SBattleUserAllInfo& sUserAllInfoA, const SBattleUserAllInfo& sUserAllInfoB,
        UINT64 qwRoleIDA, UINT64 qwRoleIDB,
        const string& strName1, const string& strName2, EGBSide eWinnerSide, const string& strReport):
    _qwBattleID(qwBattleID), _byIndex(byIndex), _eWinnerSide(eWinnerSide), _strReport(strReport)
{
    _strName[0] = strName1;
    _strName[1] = strName2;
    _qwRoleID[0] = qwRoleIDA;
    _qwRoleID[1] = qwRoleIDB;
    _qwGuiildID[0] = 0;
    _qwGuiildID[1] = 0;
    _sUserAllInfo[0] = sUserAllInfoA;
    _sUserAllInfo[1] = sUserAllInfoB;
}		// -----  end of function CGuildBattleInfo  ----- //

CGuildBattleInfo::~CGuildBattleInfo()
{
}

// ===  FUNCTION  ======================================================================
//         Name:  GetName
//  Description:  获取某一方参战者姓名
// =====================================================================================
const string& CGuildBattleInfo::GetName ( EGBSide eSide ) const
{
    return _strName[eSide];
}		// -----  end of function GetName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleID
//  Description:  获取战报ID
// =====================================================================================
UINT64 CGuildBattleInfo::GetBattleID () const
{
    return _qwBattleID;
}		// -----  end of function GetBattleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetIndex
//  Description:  获取战斗场编号
// =====================================================================================
UINT8 CGuildBattleInfo::GetIndex () const
{
    return _byIndex;
}		// -----  end of function GetIndex  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  序列化为协议
// =====================================================================================
bool CGuildBattleInfo::GetAllInfo (SBattleInfo& rInfo ) const
{
	rInfo.qwBattleID    = _qwBattleID; //战报ID
	rInfo.strNameA      = _strName[0]; //A方名字
    rInfo.qwRoleIDA     = _qwRoleID[0];
	rInfo.strNameB      = _strName[1]; //B方名字
    rInfo.qwRoleIDB     = _qwRoleID[1];
	rInfo.eWinnerSide   = _eWinnerSide; //获胜方
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  序列化为协议
// =====================================================================================
bool CGuildBattleInfo::GetAllInfo (SBattleSlotInfo& rInfo ) const
{
    rInfo.byIndex       = _byIndex;
	rInfo.qwBattleID    = _qwBattleID; //战报ID
    rInfo.sUserAllInfoA = _sUserAllInfo[0];
    rInfo.sUserAllInfoB = _sUserAllInfo[1];
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  系列化为协议 
// =====================================================================================
bool CGuildBattleInfo::GetAllInfo (SBattleData& rInfo) const
{
    rInfo.byIndex         = _byIndex;
	//rInfo.qwBattleID      = _qwBattleID; //战报ID
    rInfo.qwRoleIDA       = _qwRoleID[0];
    rInfo.qwRoleIDB       = _qwRoleID[1];
    rInfo.eWinnerSide     = _eWinnerSide;
    rInfo.strBattleReport = _strReport;
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRoleIDA
//  Description:  获取A方RoleID
// =====================================================================================
UINT64 CGuildBattleInfo::GetRoleIDA () const
{
    return _qwRoleID[0];
}		// -----  end of function GetRoleIDA  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRoleIDB
//  Description:  获取B方RoleID
// =====================================================================================
UINT64 CGuildBattleInfo::GetRoleIDB () const
{
    return _qwRoleID[1];
}		// -----  end of function GetRoleIDB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetState
//  Description:  设置对应玩家状态
// =====================================================================================
void CGuildBattleInfo::SetState (UINT64 qwRoleID, EGBUserState eState)
{
    if (_sUserAllInfo[0].qwRoleID == qwRoleID)
        _sUserAllInfo[0].eState = eState;
    if (_sUserAllInfo[1].qwRoleID == qwRoleID)
        _sUserAllInfo[1].eState = eState;

}		// -----  end of function SetState  ----- //
