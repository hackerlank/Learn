// =====================================================================================
//
//       Filename:  BoostMgr.cpp
//
//    Description:  玩家加速功能管理
//
//        Version:  1.0
//        Created:  01/20/2015 08:27:48 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================


#include "BoostMgr.h"
#include "tinyxml.h"

static TVecUINT32 s_vecNull32;
static TVecUINT16 s_vecNull16;

// ===  FUNCTION  ======================================================================
//         Name:  GetVIPLevel
//  Description:  获取VIP等级
// =====================================================================================
UINT8 CBoostMgr::GetVIPLevel() const
{
    return _byVIPLevel;
}		// -----  end of function GetVIPLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerLevel
//  Description:  获取玩家等级
// =====================================================================================
UINT16 CBoostMgr::GetPlayerLevel () const
{
    return _wPlayerLevel;
}		// -----  end of function GetPlayerLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSkillID
//  Description:  获取对应主角职业的技能ID
// =====================================================================================
const TVecUINT32&  CBoostMgr::GetSkillID (ECareerType eCareerType) const
{
    auto it = _mapSkillIDVec.find(eCareerType);
    if (it == _mapSkillIDVec.end())
        return s_vecNull32;
    else
        return it->second;
}		// -----  end of function GetSkillID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFormationID
//  Description:  返回对应职业需要激活的阵灵ID
// =====================================================================================
const TVecUINT16& CBoostMgr::GetFormationID () const
{
    return _vecFormationID;
}		// -----  end of function GetFormationID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPetID
//  Description:  返回对应职业需要激活的法宝ID
// =====================================================================================
const TVecUINT16& CBoostMgr::GetPetID () const
{
    return _vecPetID;
}		// -----  end of function GetPetID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTrumpID
//  Description:  返回对应职业需要激活的法宝ID
// =====================================================================================
const TVecUINT16& CBoostMgr::GetTrumpID (ECareerType eCareerType) const
{
    auto it = _mapTrumpIDVec.find(eCareerType);
    if (it == _mapTrumpIDVec.end())
        return s_vecNull16;
    else
        return it->second;
}		// -----  end of function GetTrumpID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFighterID
//  Description:  返回对应职业需要激活的散仙ID
// =====================================================================================
const TVecUINT16& CBoostMgr::GetFighterID(ECareerType eCareerType) const
{
    auto it = _mapFighterIDVec.find(eCareerType);
    if (it == _mapFighterIDVec.end())
        return s_vecNull16;
    else
        return it->second;
}		// -----  end of function GetFighterID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetMoney
//  Description:  获取金钱数量
// =====================================================================================
UINT32 CBoostMgr::GetMoney (EMoneyType eType) const
{
    auto it = _mapMoneyCount.find(eType);
    if (it == _mapMoneyCount.end())
        return 0;
    else
        return it->second;
}		// -----  end of function GetMoney  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetIconAppearID
//  Description:  获取解锁图标的ID
// =====================================================================================
const TVecUINT16& CBoostMgr::GetIconAppearID () const
{
    return _vecIconAppearID;
}		// -----  end of function GetIconAppearID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Init
//  Description:  启动初始化（加载配置）
// =====================================================================================
bool CBoostMgr::Init()
{
    _byVIPLevel = 0;
    _wPlayerLevel = 0;
    _wPlayerEquip = 0;
    _wFighterCuiTiLevel = 0;
    _wFighterSkillLevel = 0;
    _wFighterXinFaLevel = 0;

    // XXX: 现在先暂时命名为GMConfig.xml吧
    string strConfigFile = Config._strConfigDir + "Conf/Misc/GMConfig.xml"; 
    if(!LoadConfig(strConfigFile))
    {
        LOG_CRI <<"Load GMConfig Error. " << strConfigFile;
        return false;
    }
    LOG_INF <<"Load GMConfig " << strConfigFile << " succeed.";
    return true;
}		// -----  end of function Init  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadConfig
//  Description:  加载配置
// =====================================================================================
bool CBoostMgr::LoadConfig(const string& strFile)
{
    bool bRet = false;
    TiXmlDocument doc;
    if(!doc.LoadFile(strFile.c_str()))
    {
        LOG_CRI << "LoadFile fails! File: " << strFile;
        return false;
    }
    TiXmlElement* pElemRoot = doc.RootElement();
    if(!pElemRoot)
        return false;

    // <Super Comment="Super指令">
    TiXmlElement* pElemSuper = pElemRoot->FirstChildElement("Super");
    if (!pElemSuper)
        return false;
    bRet = LoadSuperConfig(pElemSuper);
    if (!bRet)
        return bRet;

    /*
    // <Boost Comment="Boost指令">
    TiXmlElement* pElemBoost = pElemRoot->FirstChildElement("Boost");
    if (!pElemBoost)
        return false;
    bRet = LoadBoostConfig(pElemBoost);
    if (!bRet)
        return bRet;
    */

    return true;
}		// -----  end of function LoadConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadSuperConfig
//  Description:  读取Super指令配置
// =====================================================================================
bool CBoostMgr::LoadSuperConfig (TiXmlElement* pElemSuper)
{
    if (!pElemSuper)
        return false;

    bool bRet = false;

    // 读取帐号相关配置
    // <User Comment="帐号相关" >
    TiXmlElement* pElemUser = pElemSuper->FirstChildElement("User");
    if(!pElemUser)
        return false;
    bRet = LoadSuperUserConfig (pElemUser);
    if (!bRet)
        return bRet;

    // 读取通用玩家配置
    // <Player Comment="通用玩家(不区分职业)">
    TiXmlElement* pElemPlayer = pElemSuper->FirstChildElement("Player");
    if(!pElemPlayer)
        return false;
    bRet = LoadSuperPlayerConfig (pElemPlayer);
    if (!bRet)
        return bRet;


    // 读取职业玩家配置
    // <JobPlayer Job="1" Comment="儒">
    TiXmlElement* pElemJobPlayer = pElemSuper->FirstChildElement("JobPlayer");
    while(pElemJobPlayer)
    {
        bRet = LoadSuperJobPlayerConfig (pElemJobPlayer);
        if (!bRet)
            return bRet;
        pElemJobPlayer = pElemJobPlayer->NextSiblingElement();
    }
    bRet = true;
    return bRet;
}		// -----  end of function LoadSuperConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadSuperUserConfig
//  Description:  读取Super指令通用玩家配置
// =====================================================================================
bool CBoostMgr::LoadSuperUserConfig (TiXmlElement* pElemUser)
{
    if (!pElemUser)
        return false;

    _mapMoneyCount.clear();
    // <Money Comment="金钱" Type="1"  Count="10000000"/>
    TiXmlElement* pElemMoney = pElemUser->FirstChildElement("Money");
    while(pElemMoney)
    {
        const char* pstrType  = pElemMoney->Attribute("Type");
        const char* pstrCount = pElemMoney->Attribute("Count");
        if (pstrType && pstrCount)
        {
            UINT8 byType    = atoi(pstrType);
            UINT32 dwCount  = atoi(pstrCount);
            if (byType > EMONEY_END)
            {
                LOG_CRI << "Wrong Money type: " << pstrType << ".";
                return false;
            }
            _mapMoneyCount[static_cast<EMoneyType>(byType)] = dwCount;
        }
        pElemMoney = pElemMoney->NextSiblingElement();
    }

    _mapItemCount.clear();
    // <Item Comment="道具" >
    TiXmlElement* pElemItem = pElemUser->FirstChildElement("Item");
    if (pElemItem)
    {
        //<OneItem Comment="单独一件道具" ID="500" Count="1" />
        TiXmlElement* pElemOneItem = pElemItem->FirstChildElement("OneItem");
        while(pElemOneItem)
        {
            const char* pstrID  = pElemOneItem->Attribute("ID");
            const char* pstrCount = pElemOneItem->Attribute("Count");
            if (pstrID && pstrCount)
            {
                UINT16 wID      = atoi(pstrID);
                UINT32 dwCount  = atoi(pstrCount);
                _mapItemCount[wID] = dwCount;
            }
            pElemOneItem = pElemOneItem->NextSiblingElement();
        }
    }

    // <VIP Level="15" Comment="VIP" />
    TiXmlElement* pElemVIP = pElemUser->FirstChildElement("VIP");
    if (pElemVIP)
    {
        const char* pstrLevel  = pElemVIP->Attribute("Level");
        if (pstrLevel)
            _byVIPLevel = atoi(pstrLevel);
    }
    return true;
}		// -----  end of function LoadSuperUserConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadSuperPlayerConfig
//  Description:  读取Super指令通用玩家配置
// =====================================================================================
bool CBoostMgr::LoadSuperPlayerConfig (TiXmlElement* pElemPlayer)
{
    if (!pElemPlayer)
        return false;
    bool bRet = false;

    // <Level Comment="等级" Max="150"/>
    TiXmlElement* pElemLevel = pElemPlayer->FirstChildElement("Level");
    if (pElemLevel)
    {
        const char* pstrMax   = pElemLevel->Attribute("Max");
        if (pstrMax)
            _wPlayerLevel = atoi(pstrMax);
    }

    // <Equip Comment="装备" Level="150">
    TiXmlElement* pElemEquip = pElemPlayer->FirstChildElement("Equip");
    if (pElemEquip)
    {
        const char* pstrLevel   = pElemEquip->Attribute("Level");
        if (pstrLevel)
            _wPlayerEquip = atoi(pstrLevel);
    }

    _mapTrumpIDVec[ECAREER_ALL].clear();
    // <Trump Comment="法宝" MinID="6000" MaxID="6018" Level="9">
    TiXmlElement* pElemTrump = pElemPlayer->FirstChildElement("Trump");
    if (pElemTrump)
    {
        const char* pstrMinID   = pElemTrump->Attribute("MinID");
        const char* pstrMaxID   = pElemTrump->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _mapTrumpIDVec[ECAREER_ALL].push_back(wID);
            }
        }

        // <OneTrump Comment="单独一件法宝" ID="5080" Level="9" />
        TiXmlElement* pElemOneTrump = pElemTrump->FirstChildElement("OneTrump");
        while(pElemOneTrump)
        {
            const char* pstrID    = pElemOneTrump->Attribute("ID");
            //const char* pstrLevel = pElemOneTrump->Attribute("Level");
            //if (pstrID && pstrLevel)
            if (pstrID)
            {
                UINT16 wID      = atoi(pstrID);
                //UINT32 dwLevel  = atoi(pstrLevel);
                _mapTrumpIDVec[ECAREER_ALL].push_back(wID);
            }
            pElemOneTrump = pElemOneTrump->NextSiblingElement();
        }
    }

    // <Fighter Comment="散仙相关配置" MinID="100" MaxID="117">
    TiXmlElement* pElemFighter = pElemPlayer->FirstChildElement("Fighter");
    if (pElemFighter)
    {
        bRet = LoadSuperFighterConfig(pElemFighter);
        if (!bRet)
            return bRet;
    }
    
    _vecFormationID.clear();
    // <Formation Comment="阵型" MinID="1" MaxID="13"/>
    TiXmlElement* pElemFormation = pElemPlayer->FirstChildElement("Formation");
    if (pElemFormation)
    {
        const char* pstrMinID   = pElemFormation->Attribute("MinID");
        const char* pstrMaxID   = pElemFormation->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _vecFormationID.push_back(wID);
            }
        }
    }

    // <Pet Comment="阵灵" MinID="1" MaxID="13" Level="9" />
    _vecPetID.clear();
    TiXmlElement* pElemPet = pElemPlayer->FirstChildElement("Pet");
    if (pElemPet)
    {
        const char* pstrMinID   = pElemPet->Attribute("MinID");
        const char* pstrMaxID   = pElemPet->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _vecPetID.push_back(wID);
            }
        }
    }

    _vecIconAppearID.clear();
    // <IconAppear Comment="图标解锁" MinID="1" MaxID="42" />
    TiXmlElement* pElemIconAppear = pElemPlayer->FirstChildElement("IconAppear");
    if (pElemIconAppear)
    {
        const char* pstrMinID   = pElemIconAppear->Attribute("MinID");
        const char* pstrMaxID   = pElemIconAppear->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _vecIconAppearID.push_back(wID);
            }
        }
    }
    
    bRet = true;
    return bRet;
}		// -----  end of function LoadSuperPlayerConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadSuperJobPlayerConfig
//  Description:  读取Super指令通用玩家配置
// =====================================================================================
bool CBoostMgr::LoadSuperJobPlayerConfig (TiXmlElement* pElemJobPlayer)
{
    if (!pElemJobPlayer)
        return false;

    // <JobPlayer Job="1" Comment="儒">
    const char* pstrJob = pElemJobPlayer->Attribute("Job");
    if (!pstrJob)
        return false;
    UINT8 byJob = atoi(pstrJob);
    if(byJob >= ECAREER_MAX)
        return false;
    ECareerType eCareerType = static_cast<ECareerType>(byJob);

    _mapSkillIDVec[eCareerType].clear();
    _mapSkillLevel[eCareerType] = 0;
    // <Skill MinID="11" MaxID="19" Level="9"/>
    TiXmlElement* pElemSkill = pElemJobPlayer->FirstChildElement("Skill");
    if (pElemSkill)
    {
        const char* pstrMinID   = pElemSkill->Attribute("MinID");
        const char* pstrMaxID   = pElemSkill->Attribute("MaxID");
        const char* pstrLevel   = pElemSkill->Attribute("Level");
        if (pstrMinID && pstrMaxID && pstrLevel)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            UINT16 wLevel = atoi(pstrLevel);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _mapSkillIDVec[eCareerType].push_back(wID);
            }
            _mapSkillLevel[eCareerType] = wLevel;
        }
    }

    _mapTrumpIDVec[eCareerType].clear();
    _mapTrumpLevel[eCareerType] = 0;
    // <Trump MinID="0" MaxID="0" Level="0">
    TiXmlElement* pElemTrump = pElemJobPlayer->FirstChildElement("Trump");
    if (pElemTrump)
    {
        const char* pstrMinID   = pElemTrump->Attribute("MinID");
        const char* pstrMaxID   = pElemTrump->Attribute("MaxID");
        const char* pstrLevel   = pElemTrump->Attribute("Level");
        if (pstrMinID && pstrMaxID && pstrLevel)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            UINT16 wLevel = atoi(pstrLevel);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _mapTrumpIDVec[eCareerType].push_back(wID);
            }
            _mapTrumpLevel[eCareerType] = wLevel;
        }
        // <OneTrump Comment="单独一件法宝" ID="5000" Level="9" />
        TiXmlElement* pElemOneTrump = pElemTrump->FirstChildElement("OneTrump");
        while(pElemOneTrump)
        {
            const char* pstrID    = pElemOneTrump->Attribute("ID");
            //const char* pstrLevel = pElemOneTrump->Attribute("Level");
            //if (pstrID && pstrLevel)
            if (pstrID)
            {
                UINT16 wID      = atoi(pstrID);
                //UINT32 dwLevel  = atoi(pstrLevel);
                _mapTrumpIDVec[eCareerType].push_back(wID);
            }
            pElemOneTrump = pElemOneTrump->NextSiblingElement();
        }
    }
    return true;
}		// -----  end of function LoadSuperJobPlayerConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadSuperFighterConfig
//  Description:  读取Super指令散仙的配置
// =====================================================================================
bool CBoostMgr::LoadSuperFighterConfig (TiXmlElement* pElemFighter)
{
    if (!pElemFighter)
        return false;

    _mapFighterIDVec[ECAREER_ALL].clear();
    // <Fighter Comment="散仙相关配置" MinID="100" MaxID="117">
    const char* pstrMinID   = pElemFighter->Attribute("MinID");
    const char* pstrMaxID   = pElemFighter->Attribute("MaxID");
    if (pstrMinID && pstrMaxID)
    {
        UINT16 wMinID = atoi(pstrMinID);
        UINT16 wMaxID = atoi(pstrMaxID);
        if (wMaxID < wMinID)
            wMaxID = wMinID;
        for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
        {
            _mapFighterIDVec[ECAREER_ALL].push_back(wID);
        }
    }

    // <CuiTi Comment="淬体" Level="150"/>
    TiXmlElement* pElemCuiTi = pElemFighter->FirstChildElement("CuiTi");
    if (pElemCuiTi)
    {
        const char* pstrLevel   = pElemCuiTi->Attribute("Level");
        if (pstrLevel)
            _wFighterCuiTiLevel = atoi(pstrLevel);
    }

    // <Skill Comment="技能" Level="9" />
    TiXmlElement* pElemSkill = pElemFighter->FirstChildElement("Skill");
    if (pElemSkill)
    {
        const char* pstrLevel   = pElemSkill->Attribute("Level");
        if (pstrLevel)
            _wFighterSkillLevel = atoi(pstrLevel);
    }

    // <Xinfa Comment="心法" Level="9" />
    TiXmlElement* pElemXinFa = pElemFighter->FirstChildElement("XinFa");
    if (pElemXinFa)
    {
        const char* pstrLevel   = pElemXinFa->Attribute("Level");
        if (pstrLevel)
            _wFighterXinFaLevel = atoi(pstrLevel);
    }

    bool bRet = true;
    return bRet;
}		// -----  end of function LoadSuperFighterConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadBoostConfig
//  Description:  读取Boost指令配置
// =====================================================================================
bool CBoostMgr::LoadBoostConfig (TiXmlElement* pElemBoost)
{
    if (!pElemBoost)
        return false;

    bool bRet = false;

    // 读取帐号相关配置
    // <User Comment="帐号相关" >
    TiXmlElement* pElemUser = pElemBoost->FirstChildElement("User");
    if(!pElemUser)
        return false;
    bRet = LoadBoostUserConfig (pElemUser);
    if (!bRet)
        return bRet;

    // 读取通用玩家配置
    // <Player Comment="通用玩家(不区分职业)">
    TiXmlElement* pElemPlayer = pElemBoost->FirstChildElement("Player");
    if(!pElemPlayer)
        return false;
    bRet = LoadBoostPlayerConfig (pElemPlayer);
    if (!bRet)
        return bRet;


    // 读取职业玩家配置
    // <JobPlayer Job="1" Comment="儒">
    TiXmlElement* pElemJobPlayer = pElemBoost->FirstChildElement("JobPlayer");
    while(pElemJobPlayer)
    {
        bRet = LoadBoostJobPlayerConfig (pElemJobPlayer);
        if (!bRet)
            return bRet;
        pElemJobPlayer = pElemJobPlayer->NextSiblingElement();
    }
    bRet = true;
    return bRet;
}		// -----  end of function LoadBoostConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadBoostUserConfig
//  Description:  读取Boost指令通用玩家配置
// =====================================================================================
bool CBoostMgr::LoadBoostUserConfig (TiXmlElement* pElemUser)
{
    if (!pElemUser)
        return false;

    _mapMoneyCount.clear();
    // <Money Comment="金钱" Type="1"  Count="10000000"/>
    TiXmlElement* pElemMoney = pElemUser->FirstChildElement("Money");
    while(pElemMoney)
    {
        const char* pstrType  = pElemMoney->Attribute("Type");
        const char* pstrCount = pElemMoney->Attribute("Count");
        if (pstrType && pstrCount)
        {
            UINT8 byType    = atoi(pstrType);
            UINT32 dwCount  = atoi(pstrCount);
            if (byType > EMONEY_END)
            {
                LOG_CRI << "Wrong Money type: " << pstrType << ".";
                return false;
            }
            _mapMoneyCount[static_cast<EMoneyType>(byType)] = dwCount;
        }
        pElemMoney = pElemMoney->NextSiblingElement();
    }

    _mapItemCount.clear();
    // <Item Comment="道具" >
    TiXmlElement* pElemItem = pElemUser->FirstChildElement("Item");
    if (pElemItem)
    {
        //<OneItem Comment="单独一件道具" ID="500" Count="1" />
        TiXmlElement* pElemOneItem = pElemItem->FirstChildElement("OneItem");
        while(pElemOneItem)
        {
            const char* pstrID  = pElemOneItem->Attribute("ID");
            const char* pstrCount = pElemOneItem->Attribute("Count");
            if (pstrID && pstrCount)
            {
                UINT16 wID      = atoi(pstrID);
                UINT32 dwCount  = atoi(pstrCount);
                _mapItemCount[wID] = dwCount;
            }
            pElemOneItem = pElemOneItem->NextSiblingElement();
        }
    }

    // <VIP Level="15" Comment="VIP" />
    TiXmlElement* pElemVIP = pElemUser->FirstChildElement("VIP");
    if (pElemVIP)
    {
        const char* pstrLevel  = pElemVIP->Attribute("Level");
        if (pstrLevel)
            _byVIPLevel = atoi(pstrLevel);
    }
    return true;
}		// -----  end of function LoadBoostUserConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadBoostPlayerConfig
//  Description:  读取Boost指令通用玩家配置
// =====================================================================================
bool CBoostMgr::LoadBoostPlayerConfig (TiXmlElement* pElemPlayer)
{
    if (!pElemPlayer)
        return false;
    bool bRet = false;

    // <Level Comment="等级" Max="150"/>
    TiXmlElement* pElemLevel = pElemPlayer->FirstChildElement("Level");
    if (pElemLevel)
    {
        const char* pstrMax   = pElemLevel->Attribute("Max");
        if (pstrMax)
            _wPlayerLevel = atoi(pstrMax);
    }

    // <Equip Comment="装备" Level="150">
    TiXmlElement* pElemEquip = pElemPlayer->FirstChildElement("Equip");
    if (pElemEquip)
    {
        const char* pstrLevel   = pElemEquip->Attribute("Level");
        if (pstrLevel)
            _wPlayerEquip = atoi(pstrLevel);
    }

    _mapTrumpIDVec[ECAREER_ALL].clear();
    // <Trump Comment="法宝" MinID="6000" MaxID="6018" Level="9">
    TiXmlElement* pElemTrump = pElemPlayer->FirstChildElement("Trump");
    if (pElemTrump)
    {
        const char* pstrMinID   = pElemTrump->Attribute("MinID");
        const char* pstrMaxID   = pElemTrump->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _mapTrumpIDVec[ECAREER_ALL].push_back(wID);
            }
        }

        // <OneTrump Comment="单独一件法宝" ID="5080" Level="9" />
        TiXmlElement* pElemOneTrump = pElemTrump->FirstChildElement("OneTrump");
        while(pElemOneTrump)
        {
            const char* pstrID    = pElemOneTrump->Attribute("ID");
            //const char* pstrLevel = pElemOneTrump->Attribute("Level");
            //if (pstrID && pstrLevel)
            if (pstrID)
            {
                UINT16 wID      = atoi(pstrID);
                //UINT32 dwLevel  = atoi(pstrLevel);
                _mapTrumpIDVec[ECAREER_ALL].push_back(wID);
            }
            pElemOneTrump = pElemOneTrump->NextSiblingElement();
        }
    }

    // <Fighter Comment="散仙相关配置" MinID="100" MaxID="117">
    TiXmlElement* pElemFighter = pElemPlayer->FirstChildElement("Fighter");
    if (pElemFighter)
    {
        bRet = LoadBoostFighterConfig(pElemFighter);
        if (!bRet)
            return bRet;
    }
    
    _vecFormationID.clear();
    // <Formation Comment="阵型" MinID="1" MaxID="13"/>
    TiXmlElement* pElemFormation = pElemPlayer->FirstChildElement("Formation");
    if (pElemFormation)
    {
        const char* pstrMinID   = pElemFormation->Attribute("MinID");
        const char* pstrMaxID   = pElemFormation->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _vecFormationID.push_back(wID);
            }
        }
    }

    // <Pet Comment="阵灵" MinID="1" MaxID="13" Level="9" />
    _vecPetID.clear();
    TiXmlElement* pElemPet = pElemPlayer->FirstChildElement("Pet");
    if (pElemPet)
    {
        const char* pstrMinID   = pElemPet->Attribute("MinID");
        const char* pstrMaxID   = pElemPet->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _vecPetID.push_back(wID);
            }
        }
    }

    _vecIconAppearID.clear();
    // <IconAppear Comment="图标解锁" MinID="1" MaxID="42" />
    TiXmlElement* pElemIconAppear = pElemPlayer->FirstChildElement("IconAppear");
    if (pElemIconAppear)
    {
        const char* pstrMinID   = pElemIconAppear->Attribute("MinID");
        const char* pstrMaxID   = pElemIconAppear->Attribute("MaxID");
        if (pstrMinID && pstrMaxID)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _vecIconAppearID.push_back(wID);
            }
        }
    }
    
    bRet = true;
    return bRet;
}		// -----  end of function LoadBoostPlayerConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadBoostJobPlayerConfig
//  Description:  读取Boost指令通用玩家配置
// =====================================================================================
bool CBoostMgr::LoadBoostJobPlayerConfig (TiXmlElement* pElemJobPlayer)
{
    if (!pElemJobPlayer)
        return false;

    // <JobPlayer Job="1" Comment="儒">
    const char* pstrJob = pElemJobPlayer->Attribute("Job");
    if (!pstrJob)
        return false;
    UINT8 byJob = atoi(pstrJob);
    if(byJob >= ECAREER_MAX)
        return false;
    ECareerType eCareerType = static_cast<ECareerType>(byJob);

    _mapSkillIDVec[eCareerType].clear();
    _mapSkillLevel[eCareerType] = 0;
    // <Skill MinID="11" MaxID="19" Level="9"/>
    TiXmlElement* pElemSkill = pElemJobPlayer->FirstChildElement("Skill");
    if (pElemSkill)
    {
        const char* pstrMinID   = pElemSkill->Attribute("MinID");
        const char* pstrMaxID   = pElemSkill->Attribute("MaxID");
        const char* pstrLevel   = pElemSkill->Attribute("Level");
        if (pstrMinID && pstrMaxID && pstrLevel)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            UINT16 wLevel = atoi(pstrLevel);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _mapSkillIDVec[eCareerType].push_back(wID);
            }
            _mapSkillLevel[eCareerType] = wLevel;
        }
    }

    _mapTrumpIDVec[eCareerType].clear();
    _mapTrumpLevel[eCareerType] = 0;
    // <Trump MinID="0" MaxID="0" Level="0">
    TiXmlElement* pElemTrump = pElemJobPlayer->FirstChildElement("Trump");
    if (pElemTrump)
    {
        const char* pstrMinID   = pElemTrump->Attribute("MinID");
        const char* pstrMaxID   = pElemTrump->Attribute("MaxID");
        const char* pstrLevel   = pElemTrump->Attribute("Level");
        if (pstrMinID && pstrMaxID && pstrLevel)
        {
            UINT16 wMinID = atoi(pstrMinID);
            UINT16 wMaxID = atoi(pstrMaxID);
            UINT16 wLevel = atoi(pstrLevel);
            if (wMaxID < wMinID)
                wMaxID = wMinID;
            for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
            {
                _mapTrumpIDVec[eCareerType].push_back(wID);
            }
            _mapTrumpLevel[eCareerType] = wLevel;
        }
        // <OneTrump Comment="单独一件法宝" ID="5000" Level="9" />
        TiXmlElement* pElemOneTrump = pElemTrump->FirstChildElement("OneTrump");
        while(pElemOneTrump)
        {
            const char* pstrID    = pElemOneTrump->Attribute("ID");
            //const char* pstrLevel = pElemOneTrump->Attribute("Level");
            //if (pstrID && pstrLevel)
            if (pstrID)
            {
                UINT16 wID      = atoi(pstrID);
                //UINT32 dwLevel  = atoi(pstrLevel);
                _mapTrumpIDVec[eCareerType].push_back(wID);
            }
            pElemOneTrump = pElemOneTrump->NextSiblingElement();
        }
    }
    return true;
}		// -----  end of function LoadBoostJobPlayerConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadBoostFighterConfig
//  Description:  读取Boost指令散仙的配置
// =====================================================================================
bool CBoostMgr::LoadBoostFighterConfig (TiXmlElement* pElemFighter)
{
    if (!pElemFighter)
        return false;

    _mapFighterIDVec[ECAREER_ALL].clear();
    // <Fighter Comment="散仙相关配置" MinID="100" MaxID="117">
    const char* pstrMinID   = pElemFighter->Attribute("MinID");
    const char* pstrMaxID   = pElemFighter->Attribute("MaxID");
    if (pstrMinID && pstrMaxID)
    {
        UINT16 wMinID = atoi(pstrMinID);
        UINT16 wMaxID = atoi(pstrMaxID);
        if (wMaxID < wMinID)
            wMaxID = wMinID;
        for(UINT16 wID = wMinID; wID < wMaxID + 1; ++wID)
        {
            _mapFighterIDVec[ECAREER_ALL].push_back(wID);
        }
    }

    // <CuiTi Comment="淬体" Level="150"/>
    TiXmlElement* pElemCuiTi = pElemFighter->FirstChildElement("CuiTi");
    if (pElemCuiTi)
    {
        const char* pstrLevel   = pElemCuiTi->Attribute("Level");
        if (pstrLevel)
            _wFighterCuiTiLevel = atoi(pstrLevel);
    }

    // <Skill Comment="技能" Level="9" />
    TiXmlElement* pElemSkill = pElemFighter->FirstChildElement("Skill");
    if (pElemSkill)
    {
        const char* pstrLevel   = pElemSkill->Attribute("Level");
        if (pstrLevel)
            _wFighterSkillLevel = atoi(pstrLevel);
    }

    // <Xinfa Comment="心法" Level="9" />
    TiXmlElement* pElemXinFa = pElemFighter->FirstChildElement("XinFa");
    if (pElemXinFa)
    {
        const char* pstrLevel   = pElemXinFa->Attribute("Level");
        if (pstrLevel)
            _wFighterXinFaLevel = atoi(pstrLevel);
    }

    bool bRet = true;
    return bRet;
}		// -----  end of function LoadBoostFighterConfig  ----- //
