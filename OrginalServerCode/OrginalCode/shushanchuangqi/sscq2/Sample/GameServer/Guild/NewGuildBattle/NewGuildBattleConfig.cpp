// =====================================================================================
//
//       Filename:  NewGuildBattleConfig.cpp
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

#include "NewGuildBattleConfig.h"

#include "tinyxml.h"
#include "DayActivityMgr.h"

namespace NNewGuildBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  ~CConfigMgr
//  Description:  析构函数
// =====================================================================================
CConfigMgr::~CConfigMgr ()
{
}		// -----  end of function ~CConfigMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Init
//  Description:  初始化
// =====================================================================================
bool CConfigMgr::Init ()
{
    _dwStartTime = 0;
    _dwCampaignTime = 0;

    _dwExpTime = 0;

    _dwCaveCoreMaxRes = 0;
    _dwResCalcTime = 5;

    _dwDebugStartTime = 5;

    string strConfigFile = Config._strConfigDir + "Conf/Misc/NewGuildBattleConfig.xml";
    if (!LoadConfig(strConfigFile))
        return false;
    return InitStartTime();
}		// -----  end of function Init  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitStartTime
//  Description:  初始化开始时间
// =====================================================================================
bool CConfigMgr::InitStartTime ()
{
    _setBeginTime.clear();
    g_DayActivityMgr.GetTypeTime(eActTypeNewGuildBattle, _setBeginTime);
    return true;
}		// -----  end of function InitStartTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetStartTime
//  Description:  获取开始时间
// =====================================================================================
UINT32 CConfigMgr::GetStartTime () const
{
    return _dwStartTime;
}		// -----  end of function GetStartTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCampaignTime
//  Description:  获取活动时间
// =====================================================================================
UINT32 CConfigMgr::GetCampaignTime () const
{
    return _dwCampaignTime;
}		// -----  end of function GetCampaignTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetExpTime
//  Description:  获取经验值结算时间
// =====================================================================================
UINT32 CConfigMgr::GetExpTime () const
{
    return _dwExpTime;
}		// -----  end of function GetExpTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCaveCoreMaxRes
//  Description:  获取洞府战资源上限
// =====================================================================================
UINT32 CConfigMgr::GetCaveCoreMaxRes () const
{
    return _dwCaveCoreMaxRes;
}		// -----  end of function GetCaveCoreMaxRes  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetResCalcTime
//  Description:  获取洞府战资源增加时间间隔
// =====================================================================================
UINT32 CConfigMgr::GetResCalcTime () const
{
    return _dwResCalcTime;
}		// -----  end of function GetCaveCoreMaxRes  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCaveCoreResSpeed
//  Description:  获取阵眼资源增长速率
// =====================================================================================
UINT8 CConfigMgr::GetCaveCoreResSpeed (ENGBCaveCore eType) const
{
    auto it = _mapCaveCoreResSpeed.find(eType);
    if (it == _mapCaveCoreResSpeed.end())
        return 0;
    else
        return it->second;

}		// -----  end of function GetCaveCoreResSpeed  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetNextBeginTime
//  Description:  获取下次开始时间
// =====================================================================================
UINT32 CConfigMgr::GetNextBeginTime (UINT32 dwTime) const
{
    UINT32 dwWeekTime = Time::TheWeek(0, dwTime);

    UINT32 dwOutTime = 0;
    for (auto & rTime : _setBeginTime)
    {
        if (rTime  + dwWeekTime > dwTime)
        {
            dwOutTime =  dwWeekTime + rTime;
            break;
        }
    }
    if (!dwOutTime && !_setBeginTime.empty())
        dwOutTime =  Time::TheWeek(1, dwOutTime) + *(_setBeginTime.begin());
    UINT32 dwSharpTime = dwOutTime - Time::TheDay(0, dwOutTime);

    UINT8 byDay = g_DayActivityMgr.GetForceOpenDay(eActTypeNewGuildBattle);
    if (byDay)
    {
        time_t tOpenDay = Time::TheDay(byDay - 1, Config._dwOpenServerTime) + dwSharpTime;
        if (dwOutTime < tOpenDay)
            dwOutTime = tOpenDay;
        if (dwTime < tOpenDay)
            dwOutTime = tOpenDay;
    }
    return dwOutTime;
}		// -----  end of function GetNextBeginTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetDebugStartTime
//  Description:  获取GM开启前准备时间
// =====================================================================================
UINT32 CConfigMgr::GetDebugStartTime () const
{
    return _dwDebugStartTime;
}		// -----  end of function GetDebugStartTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetStartTime
//  Description:  设置开始时间
// =====================================================================================
void CConfigMgr::SetStartTime (UINT32 dwTime)
{
    _dwStartTime = dwTime;
}		// -----  end of function SetStartTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetCampaignTime
//  Description:  设置活动时间
// =====================================================================================
void CConfigMgr::SetCampaignTime (UINT32 dwTime)
{
    _dwCampaignTime = dwTime;
}		// -----  end of function SetCampaignTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetResCalcTime
//  Description:  
// =====================================================================================
void CConfigMgr::SetResCalcTime (UINT32 dwTime)
{
    _dwResCalcTime = dwTime;
}		// -----  end of function SetResCalcTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetDebugStartTime
//  Description:  设置GM开启前准备时间
// =====================================================================================
void CConfigMgr::SetDebugStartTime (UINT32 dwTime)
{
    _dwDebugStartTime = dwTime;
}		// -----  end of function SetDebugStartTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadConfig
//  Description:  读取配置
// =====================================================================================
bool CConfigMgr::LoadConfig (const string& strFile)
{
    TiXmlDocument doc;
    if(!doc.LoadFile(strFile.c_str()))
    {
        LOG_CRI << "LoadFile fails! File: " << strFile;
        return false;
    }
    TiXmlElement* pElemRoot = doc.RootElement();
    if(!pElemRoot)
        return false;
    TiXmlElement* pElemDebugConfig = pElemRoot->FirstChildElement("DebugConfig");
    if (pElemDebugConfig)
    {
        const char* pstrCampaignTime    = pElemDebugConfig->Attribute("CampaignTime");
        if (pstrCampaignTime)
            _dwCampaignTime = atoi(pstrCampaignTime);
    }

    TiXmlElement* pElemExpConfig = pElemRoot->FirstChildElement("ExpConfig");
    if (!pElemExpConfig)
    {
        LOG_CRI << "ExpConfig load error.";
        return false;
    }

    const char* pstrExpTime = pElemExpConfig->Attribute("Time");
    if (!pstrExpTime)
    {
        LOG_CRI << "ExpConfig Time load error.";
        return false;
    }
    _dwExpTime = atoi(pstrExpTime);

    // <CaveConfig MaxRes="3000">
    TiXmlElement* pElemCaveConfig = pElemRoot->FirstChildElement("CaveConfig");
    if (!pElemCaveConfig)
    {
        LOG_CRI << "CaveConfig load error.";
        return false;
    }
    const char* pstrMaxRes = pElemCaveConfig->Attribute("MaxRes");
    if (!pstrMaxRes)
    {
        LOG_CRI << "CaveConfig MaxRes load error.";
        return false;
    }
    _dwCaveCoreMaxRes = atoi(pstrMaxRes);

    _mapCaveCoreResSpeed.clear();

    // <CaveCore Type="1" ResOutput="10" />
    TiXmlElement* pElemCaveCore = pElemCaveConfig->FirstChildElement("OneTrump");
    while(pElemCaveCore)
    {
        const char* pstrType    = pElemCaveCore->Attribute("Type");
        const char* pstrOutput  = pElemCaveCore->Attribute("ResOutput");
        if (!pstrType || !pstrOutput)
        {
            LOG_CRI << "CaveConfig CaveCore load error.";
            return false;
        }
        if (atoi(pstrType) >= eNGBCCMax)
        {
            LOG_CRI << "CaveConfig CaveCore type load error.";
            return false;
        }
        _mapCaveCoreResSpeed[static_cast<ENGBCaveCore>(atoi(pstrType))] = atoi(pstrOutput);
        pElemCaveCore = pElemCaveCore->NextSiblingElement();
    }
    return true;
}		// -----  end of function LoadConfig  ----- //

} // namespace NNewGuildBattle

