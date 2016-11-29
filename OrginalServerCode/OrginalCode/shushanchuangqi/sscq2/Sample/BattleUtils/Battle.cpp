// =====================================================================================
//
//       Filename:  Battle.cpp
//
//    Description:  战斗模块
//
//        Version:  1.0
//        Created:  08/15/2014 05:52:17 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "Battle.h"

#include "BattleTypeDef.h"
#include "BattleSimulator.h"
#include "BattleFighter.h"
#include "BattleArea.h"
#include "BattleReportMgr.h"
#include "BattleDebugger.h"
#include "BattleAction.h"

#include "tinyxml.h"

namespace NBattle
{
bool InitValue(const string& strFile);
};

IBattleSimulator::~IBattleSimulator()
{
}

IBattleFighter::~IBattleFighter()
{
}

INT32 IBattleFighter::GetScenePos()
{
    return NBattle::SCENE_POS;
}

INT32 IBattleFighter::GetFormationPos()
{
    return NBattle::PET_POS;
}

INT32 IBattleFighter::GetPetPos()
{
    return NBattle::PET_POS;
}

INT32 IBattleFighter::GetBeautyPos()
{
    return NBattle::BEAUTY_POS;
}

INT32 IBattleFighter::GetMaxPos()
{
    return NBattle::MAX_POS;
}

INT32 IBattleFighter::GetMinPos()
{
    return 0;
}

IBattleSimulatorPtr CreateBattleSimulator(UINT64 qwGUID)
{
    NBattle::CBattleSimulatorPtr pBSim(new NBattle::CBattleSimulator(qwGUID));
    return pBSim;
}

IBattleFighterPtr   CreateBattleFighter()
{
    NBattle::CBattleFighterPtr pFighter(new NBattle::CBattleFighter);
    return pFighter;
}

bool BattleInit(const string& strReportDir, const string& strPath)
{
    if (!NBattle::CBattleAreaMgr::Instance().Init(strPath))
    {
        LOG_CRI << "CBattleAreaMgr::Init fails!";
        return false;
    }
    if (!NBattle::CBattleReportMgr::Instance().Init(strReportDir))
    {
        LOG_CRI << "CBattleReportMgr::Init fails!";
        return false;
    }
    if (!NBattle::CBattleSkillMgr::Instance().Init(strPath))
    {
        LOG_CRI << "CBattleSkillMgr::Init fails!";
        return false;
    }

    string strValueFile = strPath + "Conf/Misc/BattleValueConfig.xml";
    if (!NBattle::InitValue(strValueFile))
    {
        LOG_CRI << "NBattle::InitValue fails!";
        return false;
    }

    return true;
}

void BattleConfigReload(const string& strPath)
{
    NBattle::CBattleSkillMgr::Instance().ReLoadBaseConfig(strPath, "SkillBase.xml");
    NBattle::CBattleSkillMgr::Instance().ReLoadEffectConfig(strPath, "SkillEffect.xml");

    NBattle::CBattleAreaMgr::Instance().ReloadCfg(strPath, "SkillArea.xml");
}

bool BattleSkillEffectReload(const string& strPath, const string& strName)
{
    return NBattle::CBattleSkillMgr::Instance().ReLoadEffectConfig(strPath, strName);
}

bool BattleSkillBaseReload(const string& strPath, const string& strName)
{
    return NBattle::CBattleSkillMgr::Instance().ReLoadBaseConfig(strPath, strName);
}

bool BattleAreaReload(const string& strPath, const string& strName)
{
    return NBattle::CBattleAreaMgr::Instance().ReloadCfg(strPath, strName);
}

void GetBattleReport( UINT64 qwBattleID , function<void(string*)> funcGetted)
{
    NBattle::CBattleReportMgr::Instance().GetReport(qwBattleID, funcGetted);
}

void ProcessBattleReportResult()
{
    NBattle::CBattleReportMgr::Instance().ProcessResult();
}

UINT32 BattleCheatMode(UINT32 dwCheatBit)
{
    NBattle::g_dwCheatBit = dwCheatBit;
    return NBattle::g_dwCheatBit;
}

namespace NBattle
{

bool InitValue(const string& strFile)
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
    // <Damage Comment="伤害计算">
    TiXmlElement* pElemDamage = pElemRoot->FirstChildElement("Damage");
    if(!pElemDamage)
        return false;

    // <Reduce Max="9000" Min="0" Comment="免伤率">
    TiXmlElement* pElemReduce = pElemDamage->FirstChildElement("Reduce");

    const char* pstrMaxValue    = pElemReduce->Attribute("Max");
    const char* pstrMinValue    = pElemReduce->Attribute("Min");
    if (!pstrMaxValue || !pstrMinValue)
        return false;
    g_dwReduceMax = atoi(pstrMaxValue);
    g_dwReduceMin = atoi(pstrMinValue);

    // <Value ID="1" Value="40" />
    TiXmlElement* pElemValue = pElemReduce->FirstChildElement("Value");
    while(pElemValue)
    {
        const char* pstrID    = pElemValue->Attribute("ID");
        const char* pstrValue = pElemValue->Attribute("Value");
        if (!pstrID || !pstrValue)
            return false;
        g_dwReduceValue[atoi(pstrID)] = atoi(pstrValue);

        pElemValue = pElemValue->NextSiblingElement();
    }

    // <CriticalDmg Max="30000" Min="15000" Comment="暴击伤害" />
    TiXmlElement* pElemCriticalDmg = pElemDamage->FirstChildElement("CriticalDmg");

    pstrMaxValue    = pElemCriticalDmg->Attribute("Max");
    pstrMinValue    = pElemCriticalDmg->Attribute("Min");
    if (!pstrMaxValue || !pstrMinValue)
        return false;
    g_dwCriticalDmgMax = atoi(pstrMaxValue);
    g_dwCriticalDmgMin = atoi(pstrMinValue);

    // <DamageFloat Max="10500" Min="9500" Comment="伤害浮动"/>
    TiXmlElement* pElemDamageFloat = pElemDamage->FirstChildElement("DamageFloat");

    pstrMaxValue    = pElemDamageFloat->Attribute("Max");
    pstrMinValue    = pElemDamageFloat->Attribute("Min");
    if (!pstrMaxValue || !pstrMinValue)
        return false;
    g_dwDamageFloatMax = atoi(pstrMaxValue);
    g_dwDamageFloatMin = atoi(pstrMinValue);

    // <Damage Comment="伤害计算">
    // =================================================================================

    // =================================================================================
    // <Hit Max="10000" Min="100" Comment="命中计算" >
    TiXmlElement* pElemHit = pElemRoot->FirstChildElement("Hit");
    if (!pElemHit)
        return false;

    pstrMaxValue    = pElemHit->Attribute("Max");
    pstrMinValue    = pElemHit->Attribute("Min");
    if (!pstrMaxValue || !pstrMinValue)
        return false;
    g_dwHitMax = atoi(pstrMaxValue);
    g_dwHitMin = atoi(pstrMinValue);

    // <Value ID="1" Value="40" />
    pElemValue = pElemHit->FirstChildElement("Value");
    while(pElemValue)
    {
        const char* pstrID    = pElemValue->Attribute("ID");
        const char* pstrValue = pElemValue->Attribute("Value");
        if (!pstrID || !pstrValue)
            return false;
        g_dwHitValue[atoi(pstrID)] = atoi(pstrValue);

        pElemValue = pElemValue->NextSiblingElement();
    }

    // <Hit Max="10000" Min="100" Comment="命中计算" >
    // =================================================================================
    
    // =================================================================================
    // <Critical Max="9000" Min="0" Comment="暴击概率">
    
    TiXmlElement* pElemCritical = pElemRoot->FirstChildElement("Critical");
    if (!pElemCritical)
        return false;

    pstrMaxValue    = pElemCritical->Attribute("Max");
    pstrMinValue    = pElemCritical->Attribute("Min");
    if (!pstrMaxValue || !pstrMinValue)
        return false;
    g_dwCriticalMax = atoi(pstrMaxValue);
    g_dwCriticalMin = atoi(pstrMinValue);

    // <Value ID="1" Value="40" />
    pElemValue = pElemCritical->FirstChildElement("Value");
    while(pElemValue)
    {
        const char* pstrID    = pElemValue->Attribute("ID");
        const char* pstrValue = pElemValue->Attribute("Value");
        if (!pstrID || !pstrValue)
            return false;
        g_dwCriticalValue[atoi(pstrID)] = atoi(pstrValue);

        pElemValue = pElemValue->NextSiblingElement();
    }

    // <Critical Max="9000" Min="0" Comment="暴击概率">
    // =================================================================================

    // =================================================================================
    // <Counter Max="10000" Min="100" Comment="反击计算" >
    TiXmlElement* pElemCounter = pElemRoot->FirstChildElement("Counter");
    if (!pElemCounter)
        return false;

    pstrMaxValue    = pElemCounter->Attribute("Max");
    pstrMinValue    = pElemCounter->Attribute("Min");
    if (!pstrMaxValue || !pstrMinValue)
        return false;
    g_dwCounterMax = atoi(pstrMaxValue);
    g_dwCounterMin = atoi(pstrMinValue);

    // <Value ID="1" Value="40" />
    pElemValue = pElemCounter->FirstChildElement("Value");
    while(pElemValue)
    {
        const char* pstrID    = pElemValue->Attribute("ID");
        const char* pstrValue = pElemValue->Attribute("Value");
        if (!pstrID || !pstrValue)
            return false;
        g_dwCounterValue[atoi(pstrID)] = atoi(pstrValue);

        pElemValue = pElemValue->NextSiblingElement();
    }

    // <Counter Max="10000" Min="100" Comment="反击计算" >
    // =================================================================================
    
    // =================================================================================
    // <Resist Max="10000" Min="0" Comment="抵抗计算" >
    
    TiXmlElement* pElemResist = pElemRoot->FirstChildElement("Resist");
    if (!pElemResist)
        return false;

    pstrMaxValue    = pElemResist->Attribute("Max");
    pstrMinValue    = pElemResist->Attribute("Min");
    if (!pstrMaxValue || !pstrMinValue)
        return false;
    g_dwResistMax = atoi(pstrMaxValue);
    g_dwResistMin = atoi(pstrMinValue);

    // <Resist Max="10000" Min="0" Comment="抵抗计算" >
    // =================================================================================
    return true;
}		// -----  end of function InitValue  ----- //

};

FunBFCreateFromID   IBattleFighter::_funCreateFromID    = NULL;
FunBFAttrBP         IBattleFighter::_funAttrBP          = NULL;
FunBFSkillBP        IBattleFighter::_funSkillBP         = NULL;
