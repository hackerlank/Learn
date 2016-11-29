// =====================================================================================
//
//       Filename:  GuildBattleConfig.h
//
//    Description:  帮派战相关配置
//
//        Version:  1.0
//        Created:  07/31/2014 01:33:32 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef GUILD_BATTLE_CONFIG_H
#define GUILD_BATTLE_CONFIG_H

#include "stdafx.h"

#include "Singleton.h"
#include "GuildBattleProt.h"

using namespace NGuildBattleProt;

// =====================================================================================
//        Class:  CGuildBattleConfigMgr
//  Description:  帮派战配置管理类
// =====================================================================================
class CGuildBattleConfigMgr : public Singleton<CGuildBattleConfigMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGuildBattleConfigMgr ();                             // constructor //

        // ====================  ACCESSORS     ======================================= //
        UINT32 GetPrepareTime()         const;
        UINT32 GetBattleTime()          const;
        UINT32 GetBattleMinTime()       const;
        UINT32 GetBattleMaxTime()       const;
        UINT32 GetBattleMaxWin()        const;
                                       
        UINT32 GetUserCount()           const;
        UINT32 GetMinUserCount()        const;

        UINT16 GetPrepareMapID()            const;
        UINT8  GetMapScore(EGBSpot eType)   const;
        UINT16 GetMapID(EGBSpot eType)      const;
        bool   IsBattleMap(UINT16 wMapID)   const;
        UINT8  GetMapMaxUser(EGBSpot eType) const;

        UINT16 GetPosX(UINT8 byID) const;
        UINT16 GetPosY(UINT8 byID) const;

        UINT16 GetSkillBuffID(UINT16 wID) const;
        UINT16 GetSkillPrice(UINT16 wID)  const;

        void   GetAllSkillBuff(set<UINT16>& rsetSkillBuffID);

        UINT32 GetDebugLastTime()        const;
        UINT32 GetDebugPrepareTime()     const;
        UINT32 GetDebugCampaignTime()     const;
        UINT32 GetDebugCampaignCount()    const;

        UINT8  GetWinnerScore()     const;
        UINT8  GetLoserScore()     const;
        UINT8  GetWinComboScore(UINT8 byWinCount) const;

        UINT32 GetExp(UINT8 byLevel) const;
        UINT32 GetExpTime() const;

        // ====================  MUTATORS      ======================================= //
        void ForceStart();

        void SetDebugPrepareTime(UINT32 dwVal);
        void SetDebugCampaignTime(UINT32 dwVal);
        void SetDebugCampaignCount(UINT32 dwVal);

        void SetMinUserCount(UINT32 dwCount);
        
        // ====================  METHODS       ======================================= //
        bool Init(); // 初始化
        bool Reload(); // 重新加载
        bool ReLoadConfig(const string&);
        // ====================  OPERATORS     ======================================= //

    protected:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //

    private:
        // ====================  METHODS       ======================================= //
        bool LoadConfig(const string& strFile);
        bool LoadSpotConfig(const string& strFile);
        bool LoadPosConfig(const string& strFile);
        bool LoadSkillConfig(const string& strFile);
        bool LoadExpConfig(const string& strFile);

        UINT32 GetTimeFromStr(const char* pstrTime);

        // ====================  DATA MEMBERS  ======================================= //

        UINT32 _dwPrepareTime;      // 战斗前准备时间
        UINT32 _dwBattleTime;       // 战斗持续时间

        UINT32 _dwBattleMinTime;    // 战斗最短时间
        UINT32 _dwBattleMaxTime;    // 战斗最长时间
        UINT32 _dwBattleMaxWin;     // 最高战斗场次数目

        UINT16 _wPrepareMapID;      // 帮派战准备地图ID

        UINT32 _dwUserCount;        // 每个据点允许的人数
        UINT32 _dwMinUserCount;     // 帮派战最少参与人数

        map<EGBSpot, UINT8>  _mapMapScore;      // 据点分数设置
        map<EGBSpot, UINT16> _mapMapID;         // 据点地图ID设置
        map<EGBSpot, UINT8>  _mapMapMaxUser;    // 据点最大玩家数设置
        map<UINT8, UINT16>    _mapPosX;
        map<UINT8, UINT16>    _mapPosY;

        map<UINT8, UINT16>    _mapSkillBuffID;  // 帮派战技能对应BuffID
        map<UINT8, UINT16>    _mapSkillPrice;   // 帮派战技能购买价格
        UINT32  _dwExtraScore;

        UINT32 _dwDebugPrepareTime;
        UINT32 _dwDebugCampaignTime;
        UINT32 _dwDebugCampaignCount;

        UINT8 _byWinnerScore;
        UINT8 _byLoserScore;

        map<UINT8, UINT8>   _mapWinComboScore;  // 帮派战连胜额外奖励

        map<UINT8, UINT32>  _mapLevel2Exp;  // 等级获得经验值
        UINT32              _dwExpTime;     // 经验值结算时间
}; // -----  end of class CGuildBattleConfigMgr  ----- //

#endif // #ifndef GUILD_BATTLE_CONFIG_H

