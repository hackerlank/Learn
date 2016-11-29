#include "stdafx.h"
#include "Protocols.h"
#include "CommonMgr.h"
#include "Version.h"
#include "Tokenizer.h"

UINT64 CCommonMgr::_qwVersion = VERSION_INIT;
std::map<UINT16, SSevDiscountCFG> CCommonMgr::_mapSevDiscountCFG;

bool CCommonMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/SevDiscount.xml";
    CSevDiscountLoader oSevDiscountLoader;
    if(!oSevDiscountLoader.LoadData(strPath))
    {
        LOG_CRI << "oSevDiscountLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i=0; i<oSevDiscountLoader._vecData.size(); ++i)
    {
        SSevDiscountCFG* pSevDiscountCFG = oSevDiscountLoader._vecData[i];
        if (!pSevDiscountCFG)
            continue;

        _mapSevDiscountCFG.insert(std::make_pair(pSevDiscountCFG->_Day, *pSevDiscountCFG));
    }

    return true;
}

bool CCommonMgr::LoadConfig(const string &strFile)
{
    string strPath;

    if("GuardEMeiCFG.xml" == strFile)
    {
        string strPath = Config._strConfigDir + "Conf/Table/SevDiscount.xml";
        CSevDiscountLoader oSevDiscountLoader;
        if(!oSevDiscountLoader.LoadData(strPath))
        {
            LOG_CRI << "oSevDiscountLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i=0; i<oSevDiscountLoader._vecData.size(); ++i)
        {
            SSevDiscountCFG* pSevDiscountCFG = oSevDiscountLoader._vecData[i];
            if (!pSevDiscountCFG)
                continue;

            _mapSevDiscountCFG.insert(std::make_pair(pSevDiscountCFG->_Day, *pSevDiscountCFG));
        }
    }
    return true;
}

SSevDiscountCFG* CCommonMgr::GetSevDiscountCFG(UINT16 wDay)
{
    auto it = _mapSevDiscountCFG.find(wDay);
    if(it != _mapSevDiscountCFG.end())
        return &it->second;

    return NULL;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

