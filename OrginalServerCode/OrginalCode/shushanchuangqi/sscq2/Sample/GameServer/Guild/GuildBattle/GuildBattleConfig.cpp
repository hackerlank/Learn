// =====================================================================================
//
//       Filename:  GuildBattleConfig.cpp
//
//    Description:  帮派战相关配置
//
//        Version:  1.0
//        Created:  07/31/2014 01:33:32 PM
//       Revision:  none
//       Campiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================


#include "GuildBattleConfig.h"

#include "Tokenizer.h"
#include "GuildSpotCFG.h"
#include "GuildBattlePosCFG.h"
#include "GuildBattleSkillCFG.h"
#include "GuildWarAwardCFG.h"
#include "RTime.h"
#include "tinyxml.h"

CGuildBattleConfigMgr::CGuildBattleConfigMgr():
    _dwPrepareTime(0), _dwBattleTime(0), _dwBattleMinTime(0), _dwBattleMaxTime(0), _dwBattleMaxWin(0),
    _wPrepareMapID(0), 
    _dwUserCount(0), _dwMinUserCount(0), _dwExtraScore(0),
    _dwDebugPrepareTime(0), _dwDebugCampaignTime(0), _dwDebugCampaignCount(0),
    _byWinnerScore(0), _byLoserScore(0), _dwExpTime(0)
{
}

// ===  FUNCTION  ======================================================================
//         Name:  Init
//  Description:  启动初始化（加载配置）
// =====================================================================================
bool CGuildBattleConfigMgr::Init()
{
    string strConfigFile = Config._strConfigDir + "Conf/Misc/GuildBattleConfig.xml";
    if(!LoadConfig(strConfigFile))
    {
        LOG_CRI <<"Load GuildBattleConfig Error. " << strConfigFile;
        return false;
    }
    LOG_INF <<"Load GuildBattleConfig " << strConfigFile << " succeed.";

    strConfigFile = Config._strConfigDir + "Conf/Table/GuildSpot.xml";
    if(!LoadSpotConfig(strConfigFile))
    {
        LOG_CRI << "Load GuildSpot Error: " << strConfigFile << ".";
        return false;
    }
    LOG_INF <<"Load GuildSpot " << strConfigFile << " succeed.";

    strConfigFile = Config._strConfigDir + "Conf/Table/GuildBattlePos.xml";
    if(!LoadPosConfig(strConfigFile))
    {
        LOG_CRI <<"Load GuildBattlePos Error. " << strConfigFile;
        return false;
    }
    LOG_INF <<"Load GuildBattlePos " << strConfigFile << " succeed.";

    strConfigFile = Config._strConfigDir + "Conf/Table/GuildBattleSkill.xml";
    if(!LoadSkillConfig(strConfigFile))
    {
        LOG_CRI <<"Load GuildBattleSkill Error. " << strConfigFile;
        return false;
    }
    LOG_INF <<"Load GuildBattleSkill " << strConfigFile << " succeed.";

    strConfigFile = Config._strConfigDir + "Conf/Table/GuildWarAward.xml";
    if (!LoadExpConfig(strConfigFile))
    {
        LOG_CRI <<"Load GuildWarAward Error. " << strConfigFile;
        return false;
    }
    LOG_INF <<"Load GuildWarAward " << strConfigFile << " succeed.";
    return true;
}		// -----  end of function Init  ----- //

bool CGuildBattleConfigMgr::ReLoadConfig(const string& strFile)
{
    string strConfigFile;
    if("GuildBattleConfig.xml" == strFile)
    {
        strConfigFile = Config._strConfigDir + "Conf/Misc/GuildBattleConfig.xml";
        if(!LoadConfig(strConfigFile))
        {
            LOG_CRI <<"Load GuildBattleConfig Error. " << strConfigFile;
            return false;
        }
        LOG_INF <<"Load GuildBattleConfig " << strConfigFile << " succeed.";
    }else if("GuildSpot.xml" == strFile)
    {
        strConfigFile = Config._strConfigDir + "Conf/Table/GuildSpot.xml";
        if(!LoadSpotConfig(strConfigFile))
        {
            LOG_CRI << "Load GuildSpot Error: " << strConfigFile << ".";
            return false;
        }
        LOG_INF <<"Load GuildSpot " << strConfigFile << " succeed.";
    }else if("GuildBattlePos.xml" == strFile)
    {
        strConfigFile = Config._strConfigDir + "Conf/Table/GuildBattlePos.xml";
        if(!LoadPosConfig(strConfigFile))
        {
            LOG_CRI <<"Load GuildBattlePos Error. " << strConfigFile;
            return false;
        }
        LOG_INF <<"Load GuildBattlePos " << strConfigFile << " succeed.";
    }else if("GuildBattleSkill.xml" == strFile)
    {
        strConfigFile = Config._strConfigDir + "Conf/Table/GuildBattleSkill.xml";
        if(!LoadSkillConfig(strConfigFile))
        {
            LOG_CRI <<"Load GuildBattleSkill Error. " << strConfigFile;
            return false;
        }
        LOG_INF <<"Load GuildBattleSkill " << strConfigFile << " succeed.";
    }
    return  true;
}
// ===  FUNCTION  ======================================================================
//         Name:  Reload
//  Description:  重新加载配置
// =====================================================================================
bool CGuildBattleConfigMgr::Reload ()
{
    return Init();
}		// -----  end of function Reload  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadConfig
//  Description:  加载配置
// =====================================================================================
bool CGuildBattleConfigMgr::LoadConfig(const string& strFile)
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

    // =================================================================================
    // <DebugConfig CampaignTime="300" CampaignCount="3"/>
    TiXmlElement* pElemDebugConfig = pElemRoot->FirstChildElement("DebugConfig");
    if(pElemDebugConfig)
    {
        const char* pstrPrepareTime   = pElemDebugConfig->Attribute("PrepareTime");
        const char* pstrCampaignTime  = pElemDebugConfig->Attribute("CampaignTime");
        const char* pstrCampaignCount = pElemDebugConfig->Attribute("CampaignCount");
        if (pstrPrepareTime && pstrCampaignTime && pstrCampaignCount)
        {
            _dwDebugPrepareTime    = atoi(pstrPrepareTime);
            _dwDebugCampaignTime   = atoi(pstrCampaignTime);
            _dwDebugCampaignCount  = atoi(pstrCampaignCount);
        }
    }
    // <DebugConfig SignUpTime="300" CampaignTime="300" CampaignCount="3"/>
    // =================================================================================

    // =================================================================================
    // <BattleTime PrepareTime="300" BattleTime="420"  Comment="准备/战斗时间" />
    TiXmlElement* pElemBattleTime = pElemRoot->FirstChildElement("BattleTime");
    if(!pElemBattleTime)
        return false;

    const char* pstrPrepareTime  = pElemBattleTime->Attribute("PrepareTime");
    const char* pstrBattleTime   = pElemBattleTime->Attribute("BattleTime");
    if (!pstrPrepareTime || !pstrBattleTime)
        return false;
    _dwPrepareTime   = atoi(pstrPrepareTime);
    _dwBattleTime    = atoi(pstrBattleTime);
    // <BattleTime PrepareTime="300" BattleTime="420"  Comment="准备/战斗时间" />
    // =================================================================================

    // =================================================================================
    // <FieldConfig MinUserCount="5" UserCount="15" ExtraScore="20" PrepareMap="2003" Comment="场地设置（人数/分数）">
    TiXmlElement* pElemFieldConfig = pElemRoot->FirstChildElement("FieldConfig");
    if(!pElemFieldConfig)
        return false;
    const char* pstrUserCount = pElemFieldConfig->Attribute("UserCount");
    if (!pstrUserCount)
        return false;
    _dwUserCount = atoi(pstrUserCount);
    const char* pstrExtraScore = pElemFieldConfig->Attribute("ExtraScore");
    if (!pstrExtraScore)
        return false;
    _dwExtraScore = atoi(pstrExtraScore);
    const char* pstrMinUserCount = pElemFieldConfig->Attribute("MinUserCount");
    if (!pstrMinUserCount)
        return false;
    _dwMinUserCount = atoi(pstrMinUserCount);
    const char* pstrPrepareMap = pElemFieldConfig->Attribute("PrepareMap");
    if (!pstrPrepareMap)
        return false;
    _wPrepareMapID = atoi(pstrPrepareMap);
    // <FieldConfig MinUserCount="5" UserCount="15" ExtraScore="20" PrepareMap="2003" Comment="场地设置（人数/分数）">
    // =================================================================================

    // =================================================================================
    // <ExpConfig Time="15" />
    TiXmlElement* pElemExpConfig = pElemRoot->FirstChildElement("ExpConfig");
    if(!pElemExpConfig)
        return false;
    const char* pExpTime = pElemExpConfig->Attribute("Time");
    if (!pExpTime)
        return false;
    _dwExpTime = atoi(pExpTime);

    // <ExpConfig Time="15" />
    // =================================================================================

    /* 
     * 这里的配置用不到了
    // =================================================================================
	// <Field MapID="1" Name="玉柱峰" Score="3"/>
    _mapMapScore.clear();
    TiXmlElement* pElemField = pElemFieldConfig->FirstChildElement("Field");
    while(pElemField)
    {
        const char* pstrMapID = pElemField->Attribute("MapID");
        const char* pstrScore = pElemField->Attribute("Score");
        if (!pstrMapID || !pstrScore)
            return false;
        UINT8 byMapID = atoi(pstrMapID);
        UINT8 byScore = atoi(pstrScore);
        if (byMapID >= eGBSpotMax)
            return false;
        _mapMapScore.insert(make_pair(static_cast<EGBSpot>(byMapID), byScore));
        pElemField = pElemField->NextSiblingElement();
    }
	// <Field MapID="1" Name="玉柱峰" Score="3"/>
    // =================================================================================
    */

    // =================================================================================
    // <BattleConfig MinTime="5" MaxTime="30" MaxWin="5" Comment="战斗最短/最长时间"> 
    TiXmlElement* pElemBattleConfig = pElemRoot->FirstChildElement("BattleConfig");
    if(!pElemBattleConfig)
        return false;
    const char* pstrMinTime = pElemBattleConfig->Attribute("MinTime");
    if (!pstrMinTime)
        return false;
    _dwBattleMinTime = atoi(pstrMinTime);
    const char* pstrMaxTime = pElemBattleConfig->Attribute("MaxTime");
    if (!pstrMaxTime)
        return false;
    _dwBattleMaxTime = atoi(pstrMaxTime);

    const char* pstrMaxWin = pElemBattleConfig->Attribute("MaxWin");
    if (!pstrMaxWin)
        return false;
    _dwBattleMaxWin  = atoi(pstrMaxWin);
    // <BattleConfig MinTime="5" MaxTime="30" MaxWin="5" Comment="战斗最短/最长时间"> 
    // =================================================================================

    // =================================================================================
    //   <ScoreConfig WinnerScore="200" LoserScore="50">
    TiXmlElement* pElemScoreConfig = pElemRoot->FirstChildElement("ScoreConfig");
    if(!pElemScoreConfig)
        return false;
    const char* pstrWinnerScore = pElemScoreConfig->Attribute("WinnerScore");
    if (!pstrWinnerScore)
        return false;
    _byWinnerScore = atoi(pstrWinnerScore);
    const char* pstrLoserScore = pElemScoreConfig->Attribute("LoserScore");
    if (!pstrLoserScore)
        return false;
    _byLoserScore = atoi(pstrLoserScore);

    // =================================================================================
    //      <WinnerScore Count="1" Score="10"/>
    TiXmlElement* pElemWinnerScore = pElemScoreConfig->FirstChildElement("WinnerScore");
    while(pElemWinnerScore)
    {
        const char* pstrCount = pElemWinnerScore->Attribute("Count");
        const char* pstrScore = pElemWinnerScore->Attribute("Score");
        if (!pstrCount || !pstrScore)
            return false;
        UINT8 byCount = atoi(pstrCount);
        UINT8 byScore = atoi(pstrScore);
        _mapWinComboScore.insert(make_pair(byCount, byScore));
        pElemWinnerScore = pElemWinnerScore->NextSiblingElement();
    }
    //      <WinnerScore Count="1" Score="10"/>
    // =================================================================================

    //   <ScoreConfig WinnerScore="200" LoserScore="50">
    // =================================================================================

    return true;
}		// -----  end of function LoadConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadSpotConfig
//  Description:  加载据点相关配置
// =====================================================================================
bool CGuildBattleConfigMgr::LoadSpotConfig (const string& strFile)
{
    CGuildSpotLoader cLoader;
    if (!cLoader.LoadData(strFile))
    {
        LOG_CRI << "CGuildSpotLoader LoadData fails! Path: " << strFile;
        return false;
    }
    _mapMapScore.clear();
    _mapMapID.clear();
    _mapMapMaxUser.clear();
    for (auto it = cLoader._vecData.begin(); it != cLoader._vecData.end(); ++it)
    {
        SGuildSpotCFG* pCFG = *it;
        EGBSpot eType = static_cast<EGBSpot>(pCFG->_Id);
        _mapMapScore[eType] = pCFG->_Score;
        _mapMapID[eType] = pCFG->_MapId;
        _mapMapMaxUser[eType] = pCFG->_MaxNum;
    }
    return true;
}		// -----  end of function LoadSpotConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPosConfig
//  Description:  获取坐标配置
// =====================================================================================
bool CGuildBattleConfigMgr::LoadPosConfig (const string& strFile)
{
    CGuildBattlePosLoader cLoader;
    if (!cLoader.LoadData(strFile))
    {
        LOG_CRI << "CGuildBattlePosLoader LoadData fails! Path: " << strFile;
        return false;
    }
    _mapPosX.clear();
    _mapPosY.clear();
    for (auto it = cLoader._vecData.begin(); it != cLoader._vecData.end(); ++it)
    {
        SGuildBattlePosCFG* pCFG = *it;
        _mapPosX[pCFG->_Id] = pCFG->_PosX;
        _mapPosY[pCFG->_Id] = pCFG->_PosY;
    }
    return true;
}		// -----  end of function GetPosConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSkillConfig
//  Description:  获取帮派战技能配置
// =====================================================================================
bool CGuildBattleConfigMgr::LoadSkillConfig (const string& strFile)
{
    CGuildBattleSkillLoader cLoader;
    if (!cLoader.LoadData(strFile))
    {
        LOG_CRI << "CGuildBattleSkillLoader LoadData fails! Path: " << strFile;
        return false;
    }
    _mapSkillBuffID.clear();
    _mapSkillPrice.clear();
    for (auto it = cLoader._vecData.begin(); it != cLoader._vecData.end(); ++it)
    {
        SGuildBattleSkillCFG* pCFG = *it;
        _mapSkillBuffID[pCFG->_ID] = pCFG->_BuffID;
        _mapSkillPrice[pCFG->_ID] = pCFG->_Price;
    }
    return true;
}		// -----  end of function GetSkillConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadExpConfig
//  Description:  加载经验值配置
// =====================================================================================
bool CGuildBattleConfigMgr::LoadExpConfig (const string& strFile)
{
    CGuildWarAwardLoader cLoader;
    if (!cLoader.LoadData(strFile))
    {
        LOG_CRI << "CGuildWarAwardLoader LoadData fails! Path: " << strFile;
        return false;
    }
    _mapLevel2Exp.clear();
    for (auto it = cLoader._vecData.begin(); it != cLoader._vecData.end(); ++it)
    {
        SGuildWarAwardCFG* pCFG = *it;
        _mapLevel2Exp[pCFG->_Level] = pCFG->_ExpAward;
    }
    return true;
}		// -----  end of function LoadExpConfig  ----- //

UINT32 CGuildBattleConfigMgr::GetPrepareTime() const
{
    return _dwPrepareTime;
}

UINT32 CGuildBattleConfigMgr::GetBattleTime()  const
{
    return _dwBattleTime;
}

UINT32 CGuildBattleConfigMgr::GetBattleMinTime() const
{
    return _dwBattleMinTime;
}

UINT32 CGuildBattleConfigMgr::GetBattleMaxTime() const
{
    return _dwBattleMaxTime;
}

UINT32 CGuildBattleConfigMgr::GetBattleMaxWin() const
{
    return _dwBattleMaxWin;
}

UINT32 CGuildBattleConfigMgr::GetUserCount()   const
{
    return _dwUserCount;
}

UINT32 CGuildBattleConfigMgr::GetMinUserCount() const
{
    return _dwMinUserCount;
}

UINT16 CGuildBattleConfigMgr::GetPrepareMapID() const
{
    return _wPrepareMapID;
}

UINT8 CGuildBattleConfigMgr::GetMapScore(EGBSpot eType) const
{
    auto it = _mapMapScore.find(eType);
    if (it == _mapMapScore.end())
        return 0;
    return it->second;
}

UINT16 CGuildBattleConfigMgr::GetMapID(EGBSpot eType) const
{
    auto it = _mapMapID.find(eType);
    if (it == _mapMapID.end())
        return 0;
    return it->second;
}

bool CGuildBattleConfigMgr::IsBattleMap(UINT16 wMapID) const
{
    for (auto it = _mapMapID.begin(); it != _mapMapID.end(); ++it)
    {
        if (it->second == wMapID)
            return true;
    }
    return false;
}

UINT8 CGuildBattleConfigMgr::GetMapMaxUser(EGBSpot eType) const
{
    auto it = _mapMapMaxUser.find(eType);
    if (it == _mapMapMaxUser.end())
        return 0;
    return it->second;
}

UINT16 CGuildBattleConfigMgr::GetPosX(UINT8 byID) const
{
    auto it = _mapPosX.find(byID);
    if (it == _mapPosX.end())
        return 0;
    else
        return it->second;
}

UINT16 CGuildBattleConfigMgr::GetPosY(UINT8 byID) const
{
    auto it = _mapPosY.find(byID);
    if (it == _mapPosY.end())
        return 0;
    else
        return it->second;
}

UINT16 CGuildBattleConfigMgr::GetSkillBuffID(UINT16 wID) const
{
    auto it = _mapSkillBuffID.find(wID);
    if (it == _mapSkillBuffID.end())
        return 0;
    else
        return it->second;
}

UINT16 CGuildBattleConfigMgr::GetSkillPrice(UINT16 wID) const
{
    auto it = _mapSkillPrice.find(wID);
    if (it == _mapSkillPrice.end())
        return 0;
    else
        return it->second;
}

void CGuildBattleConfigMgr::GetAllSkillBuff(set<UINT16>& rsetSkillBuffID)
{
    for (auto it = _mapSkillBuffID.begin(); it != _mapSkillBuffID.end(); ++it)
    {
        rsetSkillBuffID.insert(it->second);
    }
}

UINT32 CGuildBattleConfigMgr::GetDebugLastTime() const
{
    return (_dwDebugPrepareTime + _dwDebugCampaignTime) * _dwDebugCampaignCount;
}

UINT32 CGuildBattleConfigMgr::GetDebugPrepareTime() const
{
    return _dwDebugPrepareTime;
}

UINT32 CGuildBattleConfigMgr::GetDebugCampaignTime()     const
{
    return _dwDebugCampaignTime;
}

UINT32 CGuildBattleConfigMgr::GetDebugCampaignCount()    const
{
    return _dwDebugCampaignCount;
}

UINT8 CGuildBattleConfigMgr::GetWinnerScore()     const
{
    return _byWinnerScore;
}

UINT8 CGuildBattleConfigMgr::GetLoserScore()     const
{
    return _byLoserScore;
}

UINT8 CGuildBattleConfigMgr::GetWinComboScore(UINT8 byWinCount) const
{
    auto it = _mapWinComboScore.find(byWinCount);
    if (it == _mapWinComboScore.end())
        return 0;
    else
        return it->second;
}

UINT32 CGuildBattleConfigMgr::GetExp(UINT8 byLevel) const
{
    auto it = _mapLevel2Exp.find(byLevel);
    if (it == _mapLevel2Exp.end())
        return 0;
    else
        return it->second;
}

UINT32 CGuildBattleConfigMgr::GetExpTime() const
{
    return _dwExpTime;
}

UINT32 CGuildBattleConfigMgr::GetTimeFromStr(const char* pstrTime)
{
    UINT32 dwTime = 0;
    Tokenizer tk(pstrTime, ":");
    if (tk.size() < 3)
        return dwTime;
    dwTime += atoi(tk[0].c_str()) * 3600;
    dwTime += atoi(tk[1].c_str()) * 60;
    dwTime += atoi(tk[2].c_str());
    return dwTime;
}

void CGuildBattleConfigMgr::SetDebugPrepareTime(UINT32 dwVal)
{
    _dwDebugPrepareTime = dwVal;
}

void CGuildBattleConfigMgr::SetDebugCampaignTime(UINT32 dwVal)
{
    _dwDebugCampaignTime = dwVal;
}

void CGuildBattleConfigMgr::SetDebugCampaignCount(UINT32 dwVal)
{
    _dwDebugCampaignCount = dwVal;
}

void CGuildBattleConfigMgr::SetMinUserCount(UINT32 dwCount)
{
    _dwMinUserCount = dwCount;
    if (_dwUserCount < _dwMinUserCount)
        _dwUserCount = _dwMinUserCount + 1;
}

void CGuildBattleConfigMgr::ForceStart()
{
    if (!_dwDebugPrepareTime)
        _dwDebugPrepareTime = 60;
    if (!_dwDebugCampaignTime)
        _dwDebugCampaignTime = 300;
    if (!_dwDebugCampaignCount)
        _dwDebugCampaignCount = 3;

    _dwBattleTime       = _dwDebugCampaignTime;
    _dwPrepareTime      = _dwDebugPrepareTime;
}

