// =====================================================================================
//
//       Filename:  HeroFighterTavern.cpp
//
//    Description:  散仙招募客栈
//
//        Version:  1.0
//        Created:  03/09/2015 08:47:08 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "HeroFighterTavern.h"

#include "TavernCFG.h"

#include "Tokenizer.h"

// ===  FUNCTION  ======================================================================
//         Name:  ~CTavernMgr
//  Description:  析构函数
// =====================================================================================
CTavernMgr::~CTavernMgr ()
{
}		// -----  end of function ~CTavernMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetTavernByFighterID
//  Description:  根据需要招募的散仙获取对应的酒馆
// =====================================================================================
CTavernPtr CTavernMgr::GetTavernByFighterID (UINT16 wFighterID) const
{
    for (auto& rPair : _mapTavernPtr)
    {
        if (rPair.second)
        {
            CHeroFighterInTavernPtr pHeroFighter = (rPair.second)->GetHeroFighter(wFighterID);
            if (pHeroFighter)
                return rPair.second;
        }
    }
    return NULL;
}		// -----  end of function GetTavernByFighterID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Init
//  Description:  初始化
// =====================================================================================
bool CTavernMgr::Init ()
{
    string strConfigFile = Config._strConfigDir + "Conf/Table/Tavern.xml"; 
    if(!LoadTavernConfig(strConfigFile))
    {
        LOG_CRI <<"Load Tavern Error. " << strConfigFile;
        return false;
    }
    LOG_INF <<"Load Tavern " << strConfigFile << " succeed.";
    return true;
}		// -----  end of function Init  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadTavernConfig
//  Description:  加载配置
// =====================================================================================
bool  CTavernMgr::LoadTavernConfig (const string& strPath)
{
    // 读取配置
    CTavernLoader oLoader;
    if (!oLoader.LoadData(strPath))
        return false;

    _mapTavernPtr.clear();

    for (auto & pInfo : oLoader._vecData)
    {
        CTavernPtr pTavern(new CTavern(pInfo->_TemplateId, pInfo->_Condition));
        if (!pTavern)
            return false;
        pTavern->SetName(pInfo->_Name);
        auto pairRet = _mapTavernPtr.insert(make_pair(pInfo->_TemplateId, pTavern));
        if (!pairRet.second)
        {
            LOG_CRI << "Tavern(" << pInfo->_TemplateId << ")error";
            return false;
        }

        {
            UINT16 wFighterID = pInfo->_Hero1;
            UINT16 wGetCondID = pInfo->_Hero1GetConId;

            CHeroFighterInTavernPtr pHeroFighter(new CHeroFighterInTavern(wFighterID, wGetCondID));
            if (!pTavern->PushHeroFighter(pHeroFighter))
            {
                LOG_CRI << "Tavern HeroFighterError: " << wFighterID << ".";
                return false;
            }
        }
        {
            UINT16 wFighterID = pInfo->_Hero2;
            UINT16 wGetCondID = pInfo->_Hero2GetConId;

            CHeroFighterInTavernPtr pHeroFighter(new CHeroFighterInTavern(wFighterID, wGetCondID));
            if (!pTavern->PushHeroFighter(pHeroFighter))
            {
                LOG_CRI << "Tavern HeroFighterError: " << wFighterID << ".";
                return false;
            }
        }
        {
            UINT16 wFighterID = pInfo->_Hero3;
            UINT16 wGetCondID = pInfo->_Hero3GetConId;

            CHeroFighterInTavernPtr pHeroFighter(new CHeroFighterInTavern(wFighterID, wGetCondID));
            if (!pTavern->PushHeroFighter(pHeroFighter))
            {
                LOG_CRI << "Tavern HeroFighterError: " << wFighterID << ".";
                return false;
            }
        }
        {
            UINT16 wFighterID = pInfo->_Hero4;
            UINT16 wGetCondID = pInfo->_Hero4GetConId;

            CHeroFighterInTavernPtr pHeroFighter(new CHeroFighterInTavern(wFighterID, wGetCondID));
            if (!pTavern->PushHeroFighter(pHeroFighter))
            {
                LOG_CRI << "Tavern HeroFighterError: " << wFighterID << ".";
                return false;
            }
        }
    }
    return true;
}		// -----  end of function LoadTavernConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CTavern
//  Description:  构造函数
// =====================================================================================
CTavern::CTavern (UINT16 wID, UINT16 wMinLevel):
    _wID(wID), _wMinLevel(wMinLevel)
{
}		// -----  end of function CTavern  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CTavern
//  Description:  析构函数
// =====================================================================================
CTavern::~CTavern ()
{
}		// -----  end of function ~CTavern  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetID
//  Description:  获取客栈ID
// =====================================================================================
UINT16 CTavern::GetID () const
{
    return _wID;
}		// -----  end of function GetID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetMinLevel
//  Description:  获取需要的最低等级
// =====================================================================================
UINT16 CTavern::GetMinLevel () const
{
    return _wMinLevel;
}		// -----  end of function GetMinLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetHeroFighter
//  Description:  获取客栈内某一个ID的散仙
// =====================================================================================
CHeroFighterInTavernPtr CTavern::GetHeroFighter(UINT16 wFighterID) const
{
    auto it = _mapHeroFighterPtr.find(wFighterID);
    if (it == _mapHeroFighterPtr.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetHeroFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetName
//  Description:  设置客栈名称
// =====================================================================================
void CTavern::SetName (const string& strName)
{
    _strName = strName;
}		// -----  end of function SetName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PushHeroFighter
//  Description:  增加可以招募的散仙
// =====================================================================================
bool CTavern::PushHeroFighter (CHeroFighterInTavernPtr pHeroFighter)
{
    if (!pHeroFighter)
        return false;
    auto pairRet = _mapHeroFighterPtr.insert(make_pair(pHeroFighter->GetID(), pHeroFighter));
    return pairRet.second;
}		// -----  end of function PushHeroFighter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CHeroFighterInTavern
//  Description:  构造函数
// =====================================================================================
CHeroFighterInTavern::CHeroFighterInTavern (UINT16 wID, UINT16 wGetCondID):
    _wID(wID), _wGetCondID(wGetCondID)
{
}		// -----  end of function CHeroFighterInTavern  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CHeroFighterInTavern
//  Description:  析构函数
// =====================================================================================
CHeroFighterInTavern::~CHeroFighterInTavern ()
{
}		// -----  end of function ~CHeroFighterInTavern  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetID
//  Description:  获取散仙ID
// =====================================================================================
UINT16 CHeroFighterInTavern::GetID () const
{
    return _wID;
}		// -----  end of function GetID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGetCondID
//  Description:  获取解锁条件ID
// =====================================================================================
UINT16 CHeroFighterInTavern::GetGetCondID () const
{
    return _wGetCondID;
}		// -----  end of function GetGetCondID  ----- //
