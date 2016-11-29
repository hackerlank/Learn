#include "stdafx.h"
#include "Protocols.h"
#include "GuardEMeiMgr.h"
#include "Version.h"
#include "Tokenizer.h"

UINT64 CGuardEMeiMgr::_qwVersion = VERSION_INIT;
std::map<UINT16, SGuardEMeiCFG> CGuardEMeiMgr::_mapID2GuardEMeiCFG;
std::map<UINT16, std::map<UINT16, SGuardEMeiLevelCFG>> CGuardEMeiMgr::_mapID2GuardEMeiLevelCFG;
std::map<UINT16, SEffectCFG> CGuardEMeiMgr::_mapID2EffectCFG;

bool CGuardEMeiMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/GuardEMei.xml";
    CGuardEMeiLoader oGuardEMeiLoader;
    if(!oGuardEMeiLoader.LoadData(strPath))
    {
        LOG_CRI << "oGuardEMeiLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i=0; i<oGuardEMeiLoader._vecData.size(); ++i)
    {
        SGuardEMeiCFG* pGuardEMeiCFG = oGuardEMeiLoader._vecData[i];
        if (!pGuardEMeiCFG)
            continue;

        _mapID2GuardEMeiCFG.insert(std::make_pair(pGuardEMeiCFG->_LevelId, *pGuardEMeiCFG));
    }

    strPath = Config._strConfigDir + "Conf/Table/GuardEMeiLevel.xml";
    CGuardEMeiLevelLoader oGuardEMeiLevelLoader;
    if(!oGuardEMeiLevelLoader.LoadData(strPath))
    {
        LOG_CRI << "oGuardEMeiLevelLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i=0; i<oGuardEMeiLevelLoader._vecData.size(); ++i)
    {
        SGuardEMeiLevelCFG* pGuardEMeiLevelCFG = oGuardEMeiLevelLoader._vecData[i];
        if(!pGuardEMeiLevelCFG)
            continue;
        
        std::map<UINT16, std::map<UINT16, SGuardEMeiLevelCFG>>::iterator iter = _mapID2GuardEMeiLevelCFG.find(pGuardEMeiLevelCFG->_LevelId);
        if(iter == _mapID2GuardEMeiLevelCFG.end())
        {
            std::map<UINT16, SGuardEMeiLevelCFG> _mapTemp;
            _mapTemp.insert(std::make_pair(pGuardEMeiLevelCFG->_GroupId, *pGuardEMeiLevelCFG));
            _mapID2GuardEMeiLevelCFG.insert(std::make_pair(pGuardEMeiLevelCFG->_LevelId, _mapTemp));
        }
        else
            iter->second.insert(std::make_pair(pGuardEMeiLevelCFG->_GroupId, *pGuardEMeiLevelCFG));
    }

    strPath = Config._strConfigDir + "Conf/Table/Effect.xml";
    CEffectLoader oEffectLoader;
    if(!oEffectLoader.LoadData(strPath))
    {
        LOG_CRI << "oEffectLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i=0; i<oEffectLoader._vecData.size(); ++i)
    {
        SEffectCFG* pEffectCFG = oEffectLoader._vecData[i];
        if (!pEffectCFG)
            continue;

        _mapID2EffectCFG.insert(std::make_pair(pEffectCFG->_ID, *pEffectCFG));
    }

    return true;
}

bool CGuardEMeiMgr::LoadConfig(const string &strFile)
{
    string strPath;

    if("GuardEMeiCFG.xml" == strFile)
    {
        string strPath = Config._strConfigDir + "Conf/Table/GuardEMei.xml";
        CGuardEMeiLoader oGuardEMeiLoader;
        if(!oGuardEMeiLoader.LoadData(strPath))
        {
            LOG_CRI << "oGuardEMeiLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i=0; i<oGuardEMeiLoader._vecData.size(); ++i)
        {
            SGuardEMeiCFG* pGuardEMeiCFG = oGuardEMeiLoader._vecData[i];
            if (!pGuardEMeiCFG)
                continue;

            _mapID2GuardEMeiCFG.insert(std::make_pair(pGuardEMeiCFG->_LevelId, *pGuardEMeiCFG));
        }
    }
    else if("GuardEMeiLevelCFG.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/GuardEMeiLevel.xml";
        CGuardEMeiLevelLoader oGuardEMeiLevelLoader;
        if(!oGuardEMeiLevelLoader.LoadData(strPath))
        {
            LOG_CRI << "oGuardEMeiLevelLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i=0; i<oGuardEMeiLevelLoader._vecData.size(); ++i)
        {
            SGuardEMeiLevelCFG* pGuardEMeiLevelCFG = oGuardEMeiLevelLoader._vecData[i];
            if(!pGuardEMeiLevelCFG)
                continue;
            
            std::map<UINT16, std::map<UINT16, SGuardEMeiLevelCFG>>::iterator iter = _mapID2GuardEMeiLevelCFG.find(pGuardEMeiLevelCFG->_LevelId);
            if(iter == _mapID2GuardEMeiLevelCFG.end())
            {
                std::map<UINT16, SGuardEMeiLevelCFG> _mapTemp;
                _mapTemp.insert(std::make_pair(pGuardEMeiLevelCFG->_GroupId, *pGuardEMeiLevelCFG));
                _mapID2GuardEMeiLevelCFG.insert(std::make_pair(pGuardEMeiLevelCFG->_LevelId, _mapTemp));
            }
            else
                iter->second.insert(std::make_pair(pGuardEMeiLevelCFG->_GroupId, *pGuardEMeiLevelCFG));
        }
    }
    else if("EffectCFG.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Effect.xml";
        CEffectLoader oEffectLoader;
        if(!oEffectLoader.LoadData(strPath))
        {
            LOG_CRI << "oEffectLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i=0; i<oEffectLoader._vecData.size(); ++i)
        {
            SEffectCFG* pEffectCFG = oEffectLoader._vecData[i];
            if (!pEffectCFG)
                continue;

            _mapID2EffectCFG.insert(std::make_pair(pEffectCFG->_ID, *pEffectCFG));
        }
    }
    return true;
}

SEffectCFG* CGuardEMeiMgr::GetEffectCFG(UINT16 wEffectID)
{
    auto it = _mapID2EffectCFG.find(wEffectID);
    if(it != _mapID2EffectCFG.end())
        return &it->second;

    return NULL;
}

SGuardEMeiCFG* CGuardEMeiMgr::GetGuardEMeiCFG(UINT16 wMissionID)
{
    auto it = _mapID2GuardEMeiCFG.find(wMissionID);
    if(it != _mapID2GuardEMeiCFG.end())
        return &it->second;

    return NULL;
}

SGuardEMeiLevelCFG* CGuardEMeiMgr::GetGuardEMeiLevelCFG(UINT16 wMissionID, UINT16 wProgress)
{
    std::map<UINT16, std::map<UINT16, SGuardEMeiLevelCFG>>::iterator iter = _mapID2GuardEMeiLevelCFG.find(wMissionID);
    if(iter != _mapID2GuardEMeiLevelCFG.end())
    {
        std::map<UINT16, SGuardEMeiLevelCFG>::iterator iterA = iter->second.find(wProgress);
        if(iterA != iter->second.end())
            return &(iterA->second);
    }

    return NULL;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

