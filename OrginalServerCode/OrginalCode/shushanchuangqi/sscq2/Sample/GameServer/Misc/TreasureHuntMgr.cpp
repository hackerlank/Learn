#include "stdafx.h"
#include "Protocols.h"
#include "TreasureHuntMgr.h"
#include "Version.h"
#include "Tokenizer.h"

UINT64 CTreasureHuntMgr::_qwVersion = VERSION_INIT;
map<UINT8, SSearchBuffCFG> CTreasureHuntMgr::_mapID2SearchBuffCFG;
map<UINT8, SSearchMapCFG> CTreasureHuntMgr::_mapID2SearchMapCFG;

bool CTreasureHuntMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/SearchBuff.xml";
    CSearchBuffLoader oSearchBuffLoader;
    if(!oSearchBuffLoader.LoadData(strPath))
    {
        LOG_CRI << "oSearchBuffLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i=0; i<oSearchBuffLoader._vecData.size(); ++i)
    {
        SSearchBuffCFG* pSearchBuffCFG = oSearchBuffLoader._vecData[i];
        if (!pSearchBuffCFG)
            continue;

        _mapID2SearchBuffCFG.insert(std::make_pair(pSearchBuffCFG->_ID, *pSearchBuffCFG));
    }

    strPath = Config._strConfigDir + "Conf/Table/SearchMap.xml";
    CSearchMapLoader oSearchMapLoader;
    if(!oSearchMapLoader.LoadData(strPath))
    {
        LOG_CRI << "oSearchMapLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i=0; i<oSearchMapLoader._vecData.size(); ++i)
    {
        SSearchMapCFG* pSearchMapCFG = oSearchMapLoader._vecData[i];
        if(!pSearchMapCFG)
            continue;

        _mapID2SearchMapCFG.insert(std::make_pair(pSearchMapCFG->_ID, *pSearchMapCFG));
    }

    return true;
}

bool CTreasureHuntMgr::LoadConfig(const string &strFile)
{
    string strPath;

    if("SearchMap.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/SearchBuff.xml";
        CSearchBuffLoader oSearchBuffLoader;
        if(!oSearchBuffLoader.LoadData(strPath))
        {
            LOG_CRI << "oSearchBuffLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i=0; i<oSearchBuffLoader._vecData.size(); ++i)
        {
            SSearchBuffCFG* pSearchBuffCFG = oSearchBuffLoader._vecData[i];
            if (!pSearchBuffCFG)
                continue;

            _mapID2SearchBuffCFG.insert(std::make_pair(pSearchBuffCFG->_BuffID, *pSearchBuffCFG));
        }
    }
    else if("SearchMap.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/SearchMap.xml";
        CSearchMapLoader oSearchMapLoader;
        if(!oSearchMapLoader.LoadData(strPath))
        {
            LOG_CRI << "oSearchMapLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i=0; i<oSearchMapLoader._vecData.size(); ++i)
        {
            SSearchMapCFG* pSearchMapCFG = oSearchMapLoader._vecData[i];
            if(!pSearchMapCFG)
                continue;

            _mapID2SearchMapCFG.insert(std::make_pair(pSearchMapCFG->_ID, *pSearchMapCFG));
        }
    }
    return true;
}

SSearchBuffCFG* CTreasureHuntMgr::GetSearchBuffCFG(UINT8 byBuffID)
{
    auto it = _mapID2SearchBuffCFG.find(byBuffID);
    if(it != _mapID2SearchBuffCFG.end())
        return &it->second;

    return NULL;
}

SSearchMapCFG* CTreasureHuntMgr::GetSearchMapCFG(UINT8 byMapID)
{
    auto it = _mapID2SearchMapCFG.find(byMapID);
    if(it != _mapID2SearchMapCFG.end())
        return &it->second;

    return NULL;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

