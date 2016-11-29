// =====================================================================================
//
//       Filename:  DrawMgr.cpp
//
//    Description:  求签总管理类
//
//        Version:  1.0
//        Created:  03/10/2015 05:39:33 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "DrawMgr.h"

#include "DrawCFG.h"

// ===  FUNCTION  ======================================================================
//         Name:  ~CDrawMgr
//  Description:  析构函数
// =====================================================================================
CDrawMgr::~CDrawMgr ()
{
}		// -----  end of function ~CDrawMgr  ----- //


// ===  FUNCTION  ======================================================================
//         Name:  GetDrawData
//  Description:  获取对应等级的求签配置
// =====================================================================================
CDrawDataPtr CDrawMgr::GetDrawData (EDrawType eType, UINT16 wLevel) const
{
    auto it = _mapTypeDrawDataPtr.find(eType);
    if (it == _mapTypeDrawDataPtr.end())
        return NULL;

    CDrawDataPtr pDate;
    for (auto& rPair : it->second)
    {
        if (rPair.first <= wLevel)
        {
            pDate = rPair.second;
        }
    }
    return pDate;
}		// -----  end of function GetDrawData  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Init
//  Description:  初始化
// =====================================================================================
bool CDrawMgr::Init ()
{
    string strConfigFile = Config._strConfigDir + "Conf/Table/Draw.xml"; 
    if(!LoadConfig(strConfigFile))
    {
        LOG_CRI <<"Load Dwar Error. " << strConfigFile;
        return false;
    }
    LOG_INF <<"Load Draw " << strConfigFile << " succeed.";
    return true;
}		// -----  end of function Init  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadConfig
//  Description:  读取配置 
// =====================================================================================
bool CDrawMgr::LoadConfig (const string& strPath)
{
    CDrawLoader oLoader;
    if (!oLoader.LoadData(strPath))
        return false;

    _mapTypeDrawDataPtr.clear();

    for (auto & pInfo : oLoader._vecData)
    {
        UINT16 wLevel = pInfo->_PlayerLevel;

        if (pInfo->_Type >= eDrawTypeMax)
        {
            LOG_CRI << "Draw Type error: " << pInfo->_Type << ".";
            return false;
        }
        EDrawType eType = static_cast<EDrawType>(pInfo->_Type);

        if (pInfo->_BasicType >= eDrawRewardTypeMax || pInfo->_UnexpectedType >= eDrawRewardTypeMax)
        {
            LOG_CRI << "Draw Reward Type error: " << pInfo->_BasicType << ", " << pInfo->_UnexpectedType << ".";
            return false;
        }

        EDrawRewardType eBaseRewardType = static_cast<EDrawRewardType>(pInfo->_BasicType);
        EDrawRewardType eUnexpectedRewardType = static_cast<EDrawRewardType>(pInfo->_UnexpectedType);

        CDrawDataPtr pData(new CDrawData(wLevel, eType));
        if (!pData)
            return false;
        pData->SetBaseProb(pInfo->_BasicPercent);
        pData->InitBaseCount(eBaseRewardType, pInfo->_BasicValue1, pInfo->_BasicValue2, pInfo->_DrawSilverPrice);
        pData->InitUnexpectedCount(eUnexpectedRewardType, pInfo->_UnexpectedValue1, pInfo->_UnexpectedValue2, pInfo->_DrawSilverPrice, pInfo->_DrawGoldPrice);
        auto pairRet = _mapTypeDrawDataPtr[eType].insert(make_pair(wLevel, pData));
        if (!pairRet.second)
        {
            LOG_CRI << "Draw Data error: " << wLevel << ".";
            return false;
        }
    }
    return true;
}		// -----  end of function LoadConfig  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CDrawData
//  Description:  求签配置数据
// =====================================================================================
CDrawData::CDrawData (UINT16 wLevel, EDrawType eType):
    _wLevel(wLevel), _eType(eType), 
    _wBaseProb(0), _dwSilver(0), _dwGold(0), 
    _eBaseRewardType(eDrawRewardTypeNone), _wBaseMinCount(0), _wBaseMaxCount(0),
    _eUnexpectedRewardType(eDrawRewardTypeNone), _wUnexpectedMinCount(0), _wUnexpectedMaxCount(0)
{
}		// -----  end of function CDrawData  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CDrawData
//  Description:  析构函数
// =====================================================================================
CDrawData::~CDrawData ()
{
}		// -----  end of function ~CDrawData  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetLevel
//  Description:  获取最低等级 
// =====================================================================================
UINT16 CDrawData::GetLevel () const
{
    return _wLevel;
}		// -----  end of function GetLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetType
//  Description:  获取求签类型
// =====================================================================================
EDrawType CDrawData::GetType () const
{
    return _eType;
}		// -----  end of function GetType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSilver
//  Description:  获取硬币数量
// =====================================================================================
UINT32 CDrawData::GetSilver () const
{
    return _dwSilver;
}		// -----  end of function GetSilver  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGold
//  Description:  获取显示数量
// =====================================================================================
UINT32 CDrawData::GetGold () const
{
    return _dwGold;
}		// -----  end of function GetGold  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBaseProb
//  Description:  获取概率
// =====================================================================================
UINT16 CDrawData::GetBaseProb () const
{
    return _wBaseProb;
}		// -----  end of function GetBaseProb  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBaseRewardType
//  Description:  获取普通奖励类型
// =====================================================================================
EDrawRewardType CDrawData::GetBaseRewardType () const
{
    return _eBaseRewardType;
}		// -----  end of function GetBaseRewardType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBaseMinCount
//  Description:  获取普通奖励数量下限
// =====================================================================================
UINT16 CDrawData::GetBaseMinCount () const
{
    return _wBaseMinCount;
}		// -----  end of function GetBaseMinCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBaseMaxCount
//  Description:  获取普通奖励数量上限
// =====================================================================================
UINT16 CDrawData::GetBaseMaxCount () const
{
    return _wBaseMaxCount;
}		// -----  end of function GetBaseMaxCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetUnexpectedRewardType
//  Description:  获取惊喜奖励类型
// =====================================================================================
EDrawRewardType CDrawData::GetUnexpectedRewardType () const
{
    return _eUnexpectedRewardType;
}		// -----  end of function GetUnexpectedRewardType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetUnexpectedMinCount
//  Description:  获取惊喜奖励数量下限
// =====================================================================================
UINT16 CDrawData::GetUnexpectedMinCount () const
{
    return _wUnexpectedMinCount;
}		// -----  end of function GetUnexpectedMinCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetUnexpectedMaxCount
//  Description:  获取惊喜奖励数量上限
// =====================================================================================
UINT16 CDrawData::GetUnexpectedMaxCount () const
{
    return _wUnexpectedMaxCount;
}		// -----  end of function GetUnexpectedMaxCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetBaseProb
//  Description:  设置基础类型概率
// =====================================================================================
bool CDrawData::SetBaseProb (UINT16 wBaseProb)
{
    _wBaseProb = wBaseProb;
    return true;
}		// -----  end of function SetBaseProb  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitBaseCount
//  Description:  初始化普通求签概率
// =====================================================================================
bool  CDrawData::InitBaseCount (EDrawRewardType eType, UINT16 wMinCount, UINT16 wMaxCount,
        UINT32 dwSilver)
{
    _eBaseRewardType = eType;
    _wBaseMinCount = wMinCount;
    _wBaseMaxCount = wMaxCount;

    _dwSilver = dwSilver;
    return true;
}		// -----  end of function InitBaseCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitUnexpectedCount
//  Description:  初始化惊喜求签概率
// =====================================================================================
bool  CDrawData::InitUnexpectedCount (EDrawRewardType eType, UINT16 wMinCount, UINT16 wMaxCount,
        UINT32 dwSilver, UINT32 dwGold)
{
    _eUnexpectedRewardType = eType;
    _wUnexpectedMinCount = wMinCount;
    _wUnexpectedMaxCount = wMaxCount;

    _dwSilver = dwSilver;
    _dwGold = dwGold;

    return true;
}		// -----  end of function InitUnexpectedProb  ----- //

