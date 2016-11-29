// =====================================================================================
//
//       Filename:  NewGuildBattleConfig.h
//
//    Description:  新帮派战配置
//
//
//        Version:  1.0
//        Created:  03/19/2015 11:16:28 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_CONFIG_H
#define NEW_GUILD_BATTLE_CONFIG_H

#include "stdafx.h"

#include "Singleton.h"

#include "NewGuildBattleProt.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{

// =====================================================================================
//        Class:  CConfigMgr
//  Description:  新帮派战配置
// =====================================================================================
class CConfigMgr : public Singleton<CConfigMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        virtual ~CConfigMgr();

        // ====================  ACCESSORS     ======================================= //
        UINT32 GetStartTime() const;
        UINT32 GetCampaignTime() const;

        UINT32 GetExpTime() const;

        UINT32 GetCaveCoreMaxRes() const;
        UINT32 GetResCalcTime() const;

        UINT8  GetCaveCoreResSpeed(ENGBCaveCore eType) const;

        UINT32 GetNextBeginTime(UINT32 dwTime) const;

        UINT32 GetDebugStartTime() const;

        // ====================  MUTATORS      ======================================= //
        bool Init();

        bool InitStartTime();

        void SetStartTime(UINT32 dwTime);
        void SetCampaignTime(UINT32 dwTime);

        void SetResCalcTime(UINT32 dwTime);

        void SetDebugStartTime(UINT32 dwTime);

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //
        bool LoadConfig(const string& strFile);

        // ====================  DATA MEMBERS  ======================================= //
        
        UINT32 _dwStartTime;        // 新帮派战开始时间（不包括报名）
        UINT32 _dwCampaignTime;     // 新帮派战持续时间

        UINT32 _dwExpTime;          // 新帮派战经验值结算时间

        UINT32 _dwCaveCoreMaxRes;   // 洞府战资源上限
        UINT32 _dwResCalcTime;      // 洞府战资源增加时间间隔

        map<ENGBCaveCore, UINT8>    _mapCaveCoreResSpeed;   // 洞府战阵眼增长速率
        TSetUINT32                  _setBeginTime;          // 开始时间

        UINT32 _dwDebugStartTime;   // GM命令开启准备时间

}; // -----  end of class CConfigMgr  ----- //

} // namespace NNewGuildBattle

#endif // #ifndef NEW_GUILD_BATTLE_CONFIG_H

