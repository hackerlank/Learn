// =====================================================================================
//
//       Filename:  DayShipRewardActivity.cpp
//
//    Description:  每日组队奖励活动
//
//        Version:  1.0
//        Created:  01/07/2015 02:22:44 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "DayShipRewardActivity.h"

#include "SysMsgDefine.h"
#include "Protocols.h"
#include "RTime.h"
#include "GameNetMgr.h"

// ===  FUNCTION  ======================================================================
//         Name:  CShipRewardActivity
//  Description:  构造函数
// =====================================================================================
CShipRewardActivity::CShipRewardActivity ():
    CDayActivity(eActTypeShipReward), _dwRewardRate(0)
{
}		// -----  end of function CShipRewardActivity  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CShipRewardActivity
//  Description:  析构函数
// =====================================================================================
CShipRewardActivity::~CShipRewardActivity ()
{
}		// -----  end of function ~CShipRewardActivity  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GMOpen
//  Description:  GM命令打开该活动
// =====================================================================================
bool CShipRewardActivity::GMOpen ()
{
    if(GetStatus() == eDayActivityStatusReady 
            || GetStatus() == eDayActivityStatusProcess)
        return false;

    time_t tNow = Time::Now();
    _dwAlarmTime = tNow;
    _dwReadyTime = tNow;

    //test
    _dwBeginTime = tNow + 30;
    _dwEndTime   = tNow + 600;

    CDayActivity::SetStatus(eDayActivityStatusAlarm);

    return true;
}		// -----  end of function GMOpen  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnAlarm
//  Description:  程序开始准备
// =====================================================================================
bool CShipRewardActivity::OnAlarm ()
{
    CDayActivity::OnAlarm();
    return true;
}		// -----  end of function OnAlarm  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnReady
//  Description:  开始通知
// =====================================================================================
void CShipRewardActivity::OnReady()
{
    string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eShipAlarmPre);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
    CDayActivity::OnReady();
}		// -----  end of function OnReady  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnBegin
//  Description:  正式开始
// =====================================================================================
void CShipRewardActivity::OnBegin ()
{
    string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eShipAlarmStart);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
    CDayActivity::OnBegin();
    SDayActExPtr pCFG = GetCFG();
    if (pCFG)
        _dwRewardRate = pCFG->_dwParam;
    else
    {
        LOG_CRI << "No Rate when ShipRewardActivity.";
        _dwRewardRate = 10000;
    }
    TVecUINT32 vecParam;
    vecParam.push_back(_dwRewardRate);
    g_Game2CenterCommC.Send_SyncGameActiveParam(eShip,vecParam);
}		// -----  end of function OnBegin  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnEnd
//  Description:  活动结束
// =====================================================================================
void CShipRewardActivity::OnEnd ()
{
    _dwRewardRate = 10000;
    TVecUINT32 vecParam;
    vecParam.push_back(_dwRewardRate);
    g_Game2CenterCommC.Send_SyncGameActiveParam(eShip,vecParam);
    CDayActivity::OnEnd();
}		// -----  end of function OnEnd  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnReBegin
//  Description:  服务器重启,处于活动期间的处理
// =====================================================================================
void CShipRewardActivity::OnReBegin ()
{
    CDayActivity::OnReBegin();
    OnAlarm();
    time_t tNow = Time::Now();
    if (tNow <= _dwAlarmTime)
        ;
    else if (tNow <= _dwReadyTime)
        ;
    else if (tNow <= _dwBeginTime)
        OnReady();
    else if (tNow <= _dwEndTime)
        OnBegin();
}		// -----  end of function OnReBegin  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetState
//  Description:  重置原始状态
// =====================================================================================
void CShipRewardActivity::ResetState ()
{
    CDayActivity::ResetState();
}		// -----  end of function ResetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnEvent
//  Description:  注册事件触发
// =====================================================================================
void CShipRewardActivity::OnEvent (SActEventData& oSActEventData)
{
}		// -----  end of function OnEvent  ----- //
