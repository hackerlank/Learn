// =====================================================================================
//
//       Filename:  DayTeamRewardActivity.h
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

#ifndef DAY_TEAM_REWARD_ACTIVITY_H
#define DAY_TEAM_REWARD_ACTIVITY_H

#include "Singleton.h"
#include "DayActivity.h"


// =====================================================================================
//        Class:  CTeamRewardActivity
//  Description:  组队副本奖励活动
// =====================================================================================
class CTeamRewardActivity : public CDayActivity, public Singleton<CTeamRewardActivity>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CTeamRewardActivity ();                             // constructor //
        virtual ~CTeamRewardActivity();

        // ====================  ACCESSORS     ======================================= //
        UINT32 GetRewardRate() const;

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //
        virtual bool GMOpen();                                  // GM指令直接开启活动

        virtual bool OnAlarm();                                 // 程序开始准备
        virtual void OnReady();                                 // 开始通知
        virtual void OnBegin();                                 // 正式开始
        virtual void OnEnd();                                   // 活动结束
        
        virtual void OnReBegin();                               // 服务器重启,处于活动期间的处理

        virtual void ResetState();                              // 重置原始状态
        virtual void OnEvent(SActEventData& oSActEventData);    // 注册事件触发


    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        UINT32  _dwRewardRate;    // 奖励加成系数

}; // -----  end of class CTeamRewardActivity  ----- //

#endif // #ifndef DAY_TEAM_REWARD_ACTIVITY_H

