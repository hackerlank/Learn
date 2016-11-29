// =====================================================================================
//
//       Filename:  DBRoleRankMgr.cpp
//
//    Description:  帮派战数据管理
//
//        Version:  1.0
//        Created:  09/05/2014 02:04:27 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "DBRoleRankMgr.h"

#include "Protocols.h"

#include "DBRankData.h"

using namespace NRankProt;
using namespace NProtoCommon;


CDBRoleRankMgr::~CDBRoleRankMgr()
{
    _mapRoleRankData.clear();
}

bool CDBRoleRankMgr::AddRankData(CDBRoleRankDataPtr pRankData)
{
    if (!pRankData)
        return false;
    UINT64 qwRoleID = pRankData->GetRoleID();

    auto it = _mapRoleRankDataCache.find(qwRoleID);
    if (it != _mapRoleRankDataCache.end())
        _mapRoleRankDataCache.erase(it);

    //LOG_DBG << "_mapRoleRankData.insert(" << qwRoleID << ".";
    if (_mapRoleRankData.find(qwRoleID) == _mapRoleRankData.end())
        _mapRoleRankData.insert(make_pair(qwRoleID, pRankData));

    return true;
}

bool CDBRoleRankMgr::AddRankDataCache(CDBRoleRankDataPtr pRankData)
{
    if (!pRankData)
        return false;
    UINT64 qwRoleID = pRankData->GetRoleID();

    auto it = _mapRoleRankData.find(qwRoleID);
    if (it != _mapRoleRankData.end())
    {
        LOG_CRI << "AddRankDataCache with _mapRoleRankData has data.(" << qwRoleID << ").";
        _mapRoleRankData[qwRoleID] = pRankData;
        return false;
    }

    //LOG_DBG << "_mapRoleRankDataCache.insert(" << qwRoleID << ".";
    _mapRoleRankDataCache.insert(make_pair(qwRoleID, pRankData));

    return true;
}

bool CDBRoleRankMgr::AddAdoreData(CDBRoleAdoreDataPtr pAdoreData)
{
    if (!pAdoreData)
        return false;
    UINT64 qwRoleID = pAdoreData->GetRoleID();

    auto it = _mapRoleAdoreDataCache.find(qwRoleID);
    if (it != _mapRoleAdoreDataCache.end())
        _mapRoleAdoreDataCache.erase(it);

    //LOG_DBG << "_mapRoleAdoreData.insert(" << qwRoleID << ".";
    if (_mapRoleAdoreData.find(qwRoleID) == _mapRoleAdoreData.end())
        _mapRoleAdoreData.insert(make_pair(qwRoleID, pAdoreData));

    return true;
}

bool CDBRoleRankMgr::AddAdoreDataCache(CDBRoleAdoreDataPtr pAdoreData)
{
    if (!pAdoreData)
        return false;
    UINT64 qwRoleID = pAdoreData->GetRoleID();

    auto it = _mapRoleAdoreData.find(qwRoleID);
    if (it != _mapRoleAdoreData.end())
    {
        LOG_CRI << "AddAdoreDataCache with _mapRoleAdoreData has data.(" << qwRoleID << ").";
        _mapRoleAdoreData[qwRoleID] = pAdoreData;
        return false;
    }

    //LOG_DBG << "_mapRoleAdoreDataCache.insert(" << qwRoleID << ".";
    _mapRoleAdoreDataCache.insert(make_pair(qwRoleID, pAdoreData));
    return true;
}

CDBRoleRankDataPtr CDBRoleRankMgr::GetRankData(UINT64 qwRoleID)
{
    auto it = _mapRoleRankData.find(qwRoleID);
    if(it == _mapRoleRankData.end())
    {
        it = _mapRoleRankDataCache.find(qwRoleID);
        if(it == _mapRoleRankDataCache.end())
            return NULL;
        else
            return it->second;
    }
    else 
        return it->second;
}

CDBRoleAdoreDataPtr CDBRoleRankMgr::GetAdoreData(UINT64 qwRoleID)
{
    auto it = _mapRoleAdoreData.find(qwRoleID);
    if(it == _mapRoleAdoreData.end())
    {
        it = _mapRoleAdoreDataCache.find(qwRoleID);
        if(it == _mapRoleAdoreDataCache.end())
            return NULL;
        else
            return it->second;
    }
    else 
        return it->second;
}

void CDBRoleRankMgr::LoadAllRankData()
{
    UINT32 dwPageSize = 20;
    QueryRankData(dwPageSize,
            [dwPageSize, this](INT8 byRet,UINT32 dwTotalSize)
            {
                TVecRankInfo vecAllInfo;
                UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
                if(dwTotalSize % dwPageSize != 0)
                    dwTotalPage++;
                UINT32 dwTotalCount = 0;
                if(dwTotalPage == 0)//无记录
                {
                    SendDataToCenter(dwTotalPage,dwTotalSize, vecAllInfo);
                    return ;
                }
                UINT32 dwIndex = 0;
                for(auto iter = _mapRoleRankData.begin() ;iter != _mapRoleRankData.end(); ++iter)
                {
                    ++dwTotalCount;
                    ++dwIndex;
                    TVecRankInfo vecInfo;
                    GetAllInfo(vecInfo, iter->second);
                    vecAllInfo.insert(vecAllInfo.end(), vecInfo.begin(), vecInfo.end());
                    if(dwIndex == dwPageSize)
                    {
                        SendDataToCenter(dwTotalCount,dwTotalSize, vecAllInfo);     
                        vecAllInfo.clear();
                        dwIndex = 0;
                    }
                }
                if (dwIndex)
                    SendDataToCenter(dwTotalCount, dwTotalSize, vecAllInfo);     
            });
}

void CDBRoleRankMgr::LoadRankData(UINT64 qwRoleID, function<void(CDBRoleRankDataPtr, ERankResult)> funcLoaded)
{
    if (!qwRoleID)
        return funcLoaded(NULL, eRRFailed);
    CDBRoleRankDataPtr pRankData = GetRankData(qwRoleID);
    if(pRankData)
        return funcLoaded(pRankData, eRRSuccess);
    else
    {
        CDBRoleRankDataPtr pRankDataTmp(new CDBRoleRankData(qwRoleID));
        pRankData = pRankDataTmp;
        if (!pRankData)
            return funcLoaded(pRankData, eRRFailed);
        AddRankDataCache(pRankData);
    }

    CTableManagerBaseForRoleRank* pManager = pRankData->GetDataManagerByType(eRTRoleRankBegin); 
    if (!pManager)
        return funcLoaded(pRankData, eRRFailed);
    UINT64 qwLoadTimer = GetTickCount();
    pManager->QueryDataByRoleID(qwRoleID,
            [this,pRankData,funcLoaded,qwLoadTimer, qwRoleID](INT8 byRet,UINT32 nQuerynum)
            {
                for (auto iter = pRankData->_mapDataManager.begin(); iter!= pRankData->_mapDataManager.end(); ++iter)
                {
                    ERankType eType = iter->first;
                    if (iter->first == eRTRoleRankBegin)
                        continue;

                    iter->second->QueryDataByRoleID(qwRoleID,
                            [this, qwLoadTimer, pRankData, funcLoaded, eType](INT8 byRet,UINT32 nQuerynum)
                    {
                        if (eType == eRTRoleRankEnd - 2)
                        {
                            AddRankData(pRankData);
                            funcLoaded(pRankData,eRRSuccess); 
                            LOG_INF << "Load RankData timer is " << (GetTickCount() - qwLoadTimer) << " miscseconds.";

                        }
                    }); 
            } 
    });
}

void CDBRoleRankMgr::LoadAdoreData(UINT64 qwRoleID, function<void(CDBRoleAdoreDataPtr, EAdoreResult)> funcLoaded)
{
    if (!qwRoleID)
        return funcLoaded(NULL, eARFailed);
    CDBRoleAdoreDataPtr pAdoreData = GetAdoreData(qwRoleID);
    if(pAdoreData)
        return funcLoaded(pAdoreData, eARSuccess);
    else
    {
        CDBRoleAdoreDataPtr pAdoreDataTmp(new CDBRoleAdoreData(qwRoleID));
        pAdoreData = pAdoreDataTmp;
        if (!pAdoreData)
            return funcLoaded(pAdoreData, eARFailed);
        AddAdoreDataCache(pAdoreData);
    }

    CDBRoleAdoreTableManager* pManager = pAdoreData->_pDataManager;
    if (!pManager)
        return funcLoaded(pAdoreData, eARFailed);
    UINT64 qwLoadTimer = GetTickCount();
    pManager->QueryDataByRoleID(qwRoleID,
            [this,pAdoreData,funcLoaded,qwLoadTimer, qwRoleID](INT8 byRet,UINT32 nQuerynum)
            {
                AddAdoreData(pAdoreData);
                funcLoaded(pAdoreData,eARSuccess); 
                LOG_INF << "Load AdoreData timer is " << (GetTickCount() - qwLoadTimer) << " miscseconds.";

            });
}

void CDBRoleRankMgr::RankDataOperate(UINT64 qwRoleID, ERankType eDataType, EDataChange eUpdateType, const std::string& strData)
{
    switch (eUpdateType)
    {
        case eOpAdd:
            CreateRank(qwRoleID, eDataType, strData, 
                    [eDataType, eUpdateType, strData](CDBRoleRankDataPtr pRankData, ERankResult eResult)
                    {
                        if (eResult != eRRSuccess)
                            return;
                    });
            break;
        case eOpUpdate:
        case eOpReplace:
            LoadRankData(qwRoleID,
                    [this, qwRoleID, eDataType, eUpdateType, strData](CDBRoleRankDataPtr pRankData, ERankResult eResult)
                    {
                        if(eResult != eRRSuccess)
                            return;

                        CTableManagerBaseForRoleRank* pManager = pRankData->GetDataManagerByType(eDataType);
                        if (pManager == NULL)
                            return;

                        string strNewData(strData);
                        pManager->Update(strNewData, eUpdateType);
                        CheckRankState(pRankData);
                    });
            break;
        case eOpDel:
            LoadRankData(qwRoleID,
                    [this, qwRoleID, eDataType, strData](CDBRoleRankDataPtr pRankData, ERankResult eResult)
                    {
                        //LOG_DBG << "eResult = " << (UINT32) eResult << " when Del RankData. type = " << (UINT32) eDataType << ", qwRoleID = " << qwRoleID <<  " .";
                        if (eResult != eRRSuccess)
                            return;
                        CTableManagerBaseForRoleRank* pManager = pRankData->GetDataManagerByType(eDataType);
                        if (!pManager)
                        {
                            LOG_CRI << "pManager == NULL, type = " << (UINT32) eDataType << ", qwRoleID = " << qwRoleID << ".";
                            return;
                        }
                        string strNewData(strData);
                        pManager->DelData(strNewData, qwRoleID);
                        pManager->DumpToDBRank(
                            [](UINT32 dwNum, UINT32 dwErrNum)
                            {
                                //LOG_DBG << "DumpToDBRank " << dwNum << ", " << dwErrNum << ".";
                            });
                    });
            break;
        default:
            break;
    }
}

void CDBRoleRankMgr::CheckRankState(CDBRoleRankDataPtr pRankData)
{
    if(pRankData->HasUpdateNum())
    {
        pRankData->SetUpdateStatus(DATAUPDATA_WILL);
        _queueUpdate.push(pRankData);
        //LOG_CRI << "_queueUpdate pushed.";
    }
    else
        pRankData->SetUpdateStatus(DATAUPDATE_NONE);
}

void CDBRoleRankMgr::SaveRank(bool bIsAll)
{
    UINT32 dwTotalUpdate = 500;
    UINT32 dwCurrentNum = 0;
    while( !_queueUpdate.empty() && (bIsAll || dwCurrentNum < dwTotalUpdate))
    {
        //LOG_WRN << "_queueUpdate.size() = " << _queueUpdate.size() << ".";
        CDBRoleRankDataPtr pRankData = _queueUpdate.front();
        _queueUpdate.pop();
        dwCurrentNum += pRankData->UpdateNum();
        for (auto it = pRankData->_mapDataManager.begin(); it != pRankData->_mapDataManager.end(); ++ it)
        {
            auto it2 = it;
            bool bLast = ((++it2) == pRankData->_mapDataManager.end())?true:false;
            //LOG_WRN << "bLast = " << (bLast?"true":"false") << ".";

            if(it->second->GetUpdataNum())
            {
                it->second->DumpToDBRank(
                        [pRankData,this, bLast](UINT32 dwNum,UINT32 nErrNum)
                        {
                            if (bLast)
                                CheckRankState(pRankData);
                        });
            }
            else
            {
                if (bLast)
                    CheckRankState(pRankData);
            }
        }
    }
}

void CDBRoleRankMgr::GetAllInfo(TVecRankInfo& rvecInfo, CDBRoleRankDataPtr pRankData)
{
    for (auto iter = pRankData->_mapDataManager.begin(); iter != pRankData->_mapDataManager.end(); ++iter)
    {
        iter->second->GetAllInfo(rvecInfo);
    }
}

void CDBRoleRankMgr::GetAllInfo(TVecDBAdoreInfo& rvecInfo, CDBRoleAdoreDataPtr pAdoreData)
{
    pAdoreData->_pDataManager->GetAllInfo(rvecInfo);
}

void CDBRoleRankMgr::AdoreDataOperate(UINT64 qwRoleID, EDataChange eUpdateType, const std::string& strData)
{
    switch (eUpdateType)
    {
        case eOpAdd:
            CreateAdore(qwRoleID, strData, 
                    [eUpdateType, strData](CDBRoleAdoreDataPtr pAdoreData, EAdoreResult eResult)
                    {
                        if (eResult != eARSuccess)
                            return;
                    });
            break;
        case eOpUpdate:
        case eOpReplace:
            LoadAdoreData(qwRoleID, 
                    [this, qwRoleID, eUpdateType, strData](CDBRoleAdoreDataPtr pAdoreData, EAdoreResult eResult)
                    {
                        if(eResult != eARSuccess)
                            return;

                        CDBRoleAdoreTableManager* pManager = pAdoreData->_pDataManager;
                        if (pManager == NULL)
                            return;

                        string strNewData(strData);
                        pManager->Update(strNewData, eUpdateType);
                        if(pAdoreData->HasUpdateNum())
                            CheckAdoreState(pAdoreData);
                    });
            break;
        case eOpDel:
            LoadAdoreData(qwRoleID, 
                    [this, qwRoleID, strData](CDBRoleAdoreDataPtr pAdoreData, EAdoreResult eResult)
                    {
                        LOG_DBG << "eResult = " << (UINT32) eResult << " when Del AdoreData. qwRoleID = " << qwRoleID <<  " .";
                        if (eResult != eARSuccess)
                            return;
                        CDBRoleAdoreTableManager* pManager = pAdoreData->_pDataManager;
                        if (!pManager)
                        {
                            LOG_CRI << "pManager == NULL, qwRoleID = " << qwRoleID << ".";
                            return;
                        }
                        string strNewData(strData);
                        pManager->DelData(qwRoleID);
                        pManager->DumpToDBRank(
                            [](UINT32 dwNum, UINT32 dwErrNum)
                            {
                                //LOG_DBG << "DumpToDBRank " << dwNum << ", " << dwErrNum << ".";
                            });
                    });
            break;
        default:
            break;
    }
}

void CDBRoleRankMgr::LoadAllAdoreData()
{
    UINT32 dwPageSize = 20;
    QueryAdoreData(dwPageSize,
            [dwPageSize, this](INT8 byRet,UINT32 dwTotalSize)
            {
                TVecDBAdoreInfo vecAllInfo;
                UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
                if(dwTotalSize % dwPageSize != 0)
                    dwTotalPage++;
                UINT32 dwTotalCount = 0;
                if(dwTotalPage == 0)//无记录
                {
                    SendAdoreDataToCenter(dwTotalPage,dwTotalSize, vecAllInfo);
                    return ;
                }
                UINT32 dwIndex = 0;
                for(auto iter = _mapRoleAdoreData.begin() ;iter != _mapRoleAdoreData.end(); ++iter)
                {
                    ++dwTotalCount;
                    ++dwIndex;
                    TVecDBAdoreInfo vecInfo;
                    GetAllInfo(vecInfo, iter->second);
                    vecAllInfo.insert(vecAllInfo.end(), vecInfo.begin(), vecInfo.end());
                    if(dwIndex == dwPageSize)
                    {
                        SendAdoreDataToCenter(dwTotalCount,dwPageSize, vecAllInfo);     
                        vecAllInfo.clear();
                        dwIndex = 0;
                    }
                }
                if (dwIndex)
                    SendAdoreDataToCenter(dwTotalCount, dwTotalSize, vecAllInfo);     
            });
}

void CDBRoleRankMgr::CheckAdoreState(CDBRoleAdoreDataPtr pData)
{
    if (pData->GetUpdateStatus() != DATAUPDATA_WILL)
    {
        pData->SetUpdateStatus(DATAUPDATA_WILL);
        _queueRoleAdoreUpdate.push(pData);
        //LOG_CRI << "_queueRoleAdoreUpdate pushed.";
    }
}

void CDBRoleRankMgr::SaveAdore(bool bIsAll)
{
    UINT32 dwTotalUpdate = 500;
    UINT32 dwCurrentNum = 0;
    while( !_queueRoleAdoreUpdate.empty() && (bIsAll || dwCurrentNum < dwTotalUpdate))
    {
        CDBRoleAdoreDataPtr pAdoreData = _queueRoleAdoreUpdate.front();
        dwCurrentNum += pAdoreData->UpdateNum();

        if(pAdoreData->_pDataManager->GetUpdataNum())
        {
            pAdoreData->_pDataManager->DumpToDBRank(
                    [pAdoreData,this](UINT32 dwNum,UINT32 nErrNum)
                    {
                        pAdoreData->SetUpdateStatus(DATAUPDATE_NONE);
                        if(pAdoreData->HasUpdateNum())
                            CheckAdoreState(pAdoreData);
                    });
        }
        else
        {
            pAdoreData->SetUpdateStatus(DATAUPDATE_NONE);
            if(pAdoreData->HasUpdateNum()) 
                CheckAdoreState(pAdoreData);
        }
        _queueRoleAdoreUpdate.pop();
    }
}

bool CDBRoleRankMgr::SendAdoreDataToCenter(UINT32 dwTotalPage, UINT32 dwTotalSize, TVecDBAdoreInfo& vecDBAdoreInfo)
{
    g_Center2DBCommS.Send_AdoreInitNotify(dwTotalPage, dwTotalSize, vecDBAdoreInfo);
    return true;
}

void CDBRoleRankMgr::SendDataToCenter (UINT32 dwTotalPage, UINT32 dwTotalSize, const TVecRankInfo& vecAllInfo)
{
    g_Center2DBCommS.Send_RankInitNotify(dwTotalPage, dwTotalSize, vecAllInfo);
}

void CDBRoleRankMgr::CreateRank(UINT64 qwRoleID, ERankType eDataType, const std::string& strData, function<void(CDBRoleRankDataPtr, ERankResult)> cb)
{
    bool bNew = false;
    CDBRoleRankDataPtr pRankData = GetRankData(qwRoleID);
    if (!pRankData)
    {
        CDBRoleRankDataPtr pRankDataTmp(new CDBRoleRankData(qwRoleID));
        pRankData = pRankDataTmp;
        bNew = true;
    }
    if (!pRankData)
        return cb(NULL, eRRFailed);
    if (bNew)
        AddRankDataCache(pRankData);

    DoCreateRank(pRankData, eDataType, strData, cb);
}

void CDBRoleRankMgr::DoCreateRank(CDBRoleRankDataPtr pRankData, ERankType eDataType, const string &strData,function<void(CDBRoleRankDataPtr, ERankResult)> cb )
{
    if (!pRankData)
        return cb(pRankData, eRRFailed);
    CTableManagerBaseForRoleRank* pManager = pRankData->GetDataManagerByType(eDataType);
    if( NULL == pManager)
        return  cb(pRankData, eRRFailed);

    string strData2 = strData;
    pManager->Update(strData2,eOpAdd);
    pManager->DumpToDBRank(
            [this,pRankData,cb](UINT32 nQuerynum,UINT32 nErrNum)
            {
                if (nQuerynum != 1 || nErrNum)
                {
                    cb(NULL, eRRFailed);
                    return;
                }
                if (!AddRankData(pRankData))
                {
                    LOG_CRI << "AddRankData Error.";
                    cb(NULL, eRRFailed); 
                    return;
                }
                cb(pRankData,eRRSuccess);
            });
}

void CDBRoleRankMgr::CreateAdore(UINT64 qwRoleID, const std::string& strData, function<void(CDBRoleAdoreDataPtr, EAdoreResult)> cb)
{
    bool bNew = false;
    CDBRoleAdoreDataPtr pAdoreData = GetAdoreData(qwRoleID);
    if (!pAdoreData)
    {
        CDBRoleAdoreDataPtr pAdoreDataTmp(new CDBRoleAdoreData(qwRoleID));
        pAdoreData = pAdoreDataTmp;
        bNew = true;
    }
    if (!pAdoreData)
        return cb(NULL, eARFailed);
    if (bNew)
        AddAdoreDataCache(pAdoreData);

    DoCreateAdore(pAdoreData, strData, cb);
}

void CDBRoleRankMgr::DoCreateAdore(CDBRoleAdoreDataPtr pAdoreData, const string &strData,function<void(CDBRoleAdoreDataPtr, EAdoreResult)> cb )
{
    if (!pAdoreData)
        return cb(pAdoreData, eARFailed);
    CDBRoleAdoreTableManager* pManager = pAdoreData->_pDataManager;
    if( NULL == pManager)
        return  cb(pAdoreData, eARFailed);

    string strData2 = strData;
    pManager->Update(strData2,eOpAdd);
    pManager->DumpToDBRank(
            [this,pAdoreData,cb](UINT32 nQuerynum,UINT32 nErrNum)
            {
                if (nQuerynum != 1 || nErrNum)
                {
                    cb(NULL, eARFailed);
                    return;
                }
                if (!AddAdoreData(pAdoreData))
                {
                    LOG_CRI << "AddAdoreData Error.";
                    cb(NULL, eARFailed); 
                    return;
                }
                cb(pAdoreData,eARSuccess);
            });
}

void CDBRoleRankMgr::QueryRankData(UINT32 dwPageSize,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) dwCount from ( "
         "select `qwRoleID` from `tblrolerankbattlepoint` "
         "union "
         "select `qwRoleID` from `tblrolerankformation` "
         "union "
         "select `qwRoleID` from `tblrolerankherofighter` "
         "union "
         "select `qwRoleID` from `tblroleranktrump`"
        ")as dwCount;";
    CDBMgr::Instance().DoRankSelectQuery(basesql.str(),NULL,
            [this, queryfun, basesql,dwPageSize,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet ;
                UINT32 dwCount = 0;
                if(byRet == 0 && rDataRes.size()== 1)
                {
                    mysqlpp::Row& rRow = rDataRes[0];
                    GET_UINT_SAME(dwCount);
                }
                else
                {
                    queryfun(byRet,dwCount);
                    return ;
                }
                if(dwCount == 0)
                {
                    queryfun(byRet, dwCount);
                    return ;
                }

                UINT32 dwTotalPage = (dwCount % dwPageSize != 0) ? (dwCount/dwPageSize + 1) : (dwCount / dwPageSize);
                for(UINT32 dwPage = 0; dwPage < dwTotalPage; dwPage++)
                {
                    mysqlpp::SQLStream querysql(NULL);
                    querysql << "select `qwRoleID` from ( "
                        "select `qwRoleID` from `tblrolerankbattlepoint` "
                        "union "
                        "select `qwRoleID` from `tblrolerankformation` "
                        "union "
                        "select `qwRoleID` from `tblrolerankherofighter` "
                        "union "
                        "select `qwRoleID` from `tblroleranktrump`"
                        ") as `ID` ";
                    querysql << "LIMIT ";
                    querysql << dwPage * dwPageSize << "," << dwPageSize;
                    querysql << ";";
                    CDBMgr::Instance().DoRankSelectQuery(querysql.str(),NULL,
                            [this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
                        {
                            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                            UINT32 dwDataCount = rDataRes.size();
                            for (UINT32 dwIndex = 0; dwIndex < dwDataCount; ++ dwIndex)
                            {
                                mysqlpp::Row& rRow = rDataRes[dwIndex];
                                UINT64 qwRoleID = 0;
                                GET_UBIGINT_SAME(qwRoleID);
                                if (!qwRoleID)
                                    continue;
                                LoadRankData(qwRoleID, 
                                    [this, dwCount, queryfun, qwLoadTimer, byRet](CDBRoleRankDataPtr pRankData, ERankResult eResult)
                                {
                                    if(_mapRoleRankData.size() == dwCount)
                                    {
                                        queryfun(byRet, dwCount);
                                        LOG_INF << "Load tblrank is " << GetTickCount() - qwLoadTimer << " miscseconds. Count: " << dwCount << ".";
                                    }
                                });
                            }
                        });
                }
            });
}

void CDBRoleRankMgr::QueryAdoreData(UINT32 dwPageSize,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tblroleadore;";
    CDBMgr::Instance().DoRankSelectQuery(basesql.str(),NULL,
            [this, queryfun, basesql,dwPageSize,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet ;
                UINT32 dwCount = 0;
                if(byRet == 0 && rDataRes.size()== 1)
                {
                    mysqlpp::Row& rRow = rDataRes[0];
                    GET_UINT_SAME(dwCount);
                }
                else
                {
                    queryfun(byRet,dwCount);
                    return ;
                }
                if(dwCount == 0)
                {
                    queryfun(byRet, dwCount);
                    return ;
                }

                UINT32 dwTotalPage = (dwCount % dwPageSize != 0) ? (dwCount/dwPageSize + 1) : (dwCount / dwPageSize);
                for(UINT32 dwPage = 0; dwPage < dwTotalPage; dwPage++)
                {
                    mysqlpp::SQLStream querysql(NULL);
                    querysql << "SELECT qwRoleID FROM tblroleadore LIMIT ";
                    querysql << dwPage * dwPageSize << "," << dwPageSize;
                    querysql << ";";
                    CDBMgr::Instance().DoRankSelectQuery(querysql.str(),NULL,
                            [this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
                        {
                            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                            UINT32 dwDataCount = rDataRes.size();
                            for (UINT32 dwIndex = 0; dwIndex < dwDataCount; ++ dwIndex)
                            {
                                mysqlpp::Row& rRow = rDataRes[dwIndex];
                                UINT64 qwRoleID = 0;
                                GET_UBIGINT_SAME(qwRoleID);
                                if (!qwRoleID)
                                    continue;
                                LoadAdoreData(qwRoleID, 
                                    [this, dwCount, queryfun, qwLoadTimer, byRet](CDBRoleAdoreDataPtr pAdoreData, EAdoreResult eResult)
                                {
                                    if(_mapRoleAdoreData.size() == dwCount)
                                    {
                                        queryfun(byRet, dwCount);
                                        LOG_INF << "Load tblguilddata is " << GetTickCount() - qwLoadTimer << " miscseconds. Count: " << dwCount << ".";
                                    }
                                });
                            }
                        });
                }
            });
}
