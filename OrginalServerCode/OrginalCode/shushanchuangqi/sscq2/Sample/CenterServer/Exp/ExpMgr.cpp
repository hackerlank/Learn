
#include "stdafx.h"
#include "ExpMgr.h"

TVecExpCFGPtr CExpMgr::_vecExpCFGPtr;

CExpMgr::CExpMgr()
{
}

bool CExpMgr::Init()
{
    return LoadConfig();
}

bool CExpMgr::LoadConfig(bool bReload)
{
    string strPath = Config._strConfigDir + "Conf/Table/Exp.xml";
    CExpLoader oExpLoader;
    if(!oExpLoader.LoadData(strPath))
    {
        LOG_CRI << "oExpLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oExpLoader._vecData.size(); ++i)
    {
        SExpCFG* pExpCFG = oExpLoader._vecData[i];
        if(pExpCFG->_Level == 0)
            continue;
        SExpCFGPtr pExpCFGPtr(new SExpCFG);
        *pExpCFGPtr=*pExpCFG;
        _vecExpCFGPtr.push_back(pExpCFGPtr);
    }
    return true;
}

bool CExpMgr::ReLoadConfig(const string &strFile)
{
    string strPath;
    if("Exp.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Exp.xml";
        CExpLoader oExpLoader;
        if(!oExpLoader.LoadData(strPath))
        {
            LOG_CRI << "oExpLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oExpLoader._vecData.size(); ++i)
        {
            SExpCFG* pExpCFG = oExpLoader._vecData[i];
            if(pExpCFG->_Level == 0)
                continue;
            SExpCFGPtr pExpCFGPtr(new SExpCFG);
            *pExpCFGPtr=*pExpCFG;
            _vecExpCFGPtr.push_back(pExpCFGPtr);
        }
    }
    return true;
}

SExpCFGPtr CExpMgr::GetExpCfg(UINT8 byLevel)
{
    if(byLevel >= _vecExpCFGPtr.size())
    {
        return NULL;
    }
    return _vecExpCFGPtr[byLevel];
}

float CExpMgr::GetStoveAwardRate(UINT8 byLevel)
{
    float fRate = 0.0f;
    SExpCFGPtr pExpCfg = GetExpCfg(byLevel - 1);
    if (pExpCfg)
        fRate = float(pExpCfg->_StoveC) / 10000;
    return fRate;
}

float CExpMgr::GetStoveHelpRate(UINT8 byLevel)
{
    float fRate = 0.0f;
    SExpCFGPtr pExpCfg = GetExpCfg(byLevel - 1);
    if (pExpCfg)
        fRate = float(pExpCfg->_StoveHelperAddition) / 10000;
    return fRate;
}

