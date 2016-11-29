#include "DBPubGuildMgr.h"

#include "DBGuildData.h"
#include "DBGuildListInfoTable.h"

#include "Center2DBGuildS.h"

CDBPubGuildMgr::~CDBPubGuildMgr()
{
    _mapPubGuildData.clear();
}

bool CDBPubGuildMgr::AddPubGuildData(CDBPubGuildDataPtr pPubGuildData)
{
    UINT64 qwGuildID = pPubGuildData->GetGuildID();

    _mapPubGuildData.insert(make_pair(qwGuildID, pPubGuildData));

    auto it = _mapPubGuildData.find(qwGuildID);
    if (it != _mapPubGuildData.end() && (!it->second))
    {
        LOG_CRI << "Guild already loaded: " << qwGuildID;
        return false;
    }
    return true;
}

CDBPubGuildDataPtr CDBPubGuildMgr::GetPubGuildData(UINT64 qwGuildID)
{
    auto it = _mapPubGuildData.find(qwGuildID);
    if(it == _mapPubGuildData.end())
        return NULL;
    return it->second;
}

void CDBPubGuildMgr::LoadPubGuildData(UINT64 qwGuildID, function<void(CDBPubGuildDataPtr, EGuildResult)> funcLoaded)
{
    CDBPubGuildDataPtr pPubGuildData = GetPubGuildData(qwGuildID);
    if(pPubGuildData)
        return funcLoaded(pPubGuildData, eGuildSuccess);

    pPubGuildData = CDBPubGuildDataPtr(new CDBPubGuildData(qwGuildID));
    if (!pPubGuildData)
        return funcLoaded(pPubGuildData, eGuildFailed);

    CTableManagerBaseForGuildPub* pManager = pPubGuildData->GetDataManagerByType(eGPDTListInfo); 
    if (!pManager)
        return funcLoaded(pPubGuildData, eGuildFailed);
    UINT64 qwLoadTimer = GetTickCount();
    pManager->QueryDataByGuildID(qwGuildID,[this,pPubGuildData,funcLoaded,qwLoadTimer](INT8 byRet,UINT32 nQuerynum){
        if ( byRet != 0)
        {
            return funcLoaded(NULL, eGuildFailed);
        }
        if (nQuerynum == 0) // 查不到数据
        {
            return funcLoaded(NULL, eGuildNotExisted);
        }
        pPubGuildData->SetNowUpdate(0);
        for (auto iter = pPubGuildData->_mapDataManager.begin(); iter!= pPubGuildData->_mapDataManager.end(); ++iter)
        {
            if (iter->first == eGPDTListInfo)
                continue;

            iter->second->QueryDataByGuildID(pPubGuildData->GetGuildID(),[this,qwLoadTimer,pPubGuildData,funcLoaded](INT8 byRet,UINT32 nQuerynum){
                pPubGuildData->AddNowUpdate();
                if (pPubGuildData->GetNowUpdate() == pPubGuildData->_mapDataManager.size() - 1)
                {
                    this->AddPubGuildData(pPubGuildData);
                    funcLoaded(pPubGuildData,eGuildSuccess); 
                    LOG_INF << "Load " << pPubGuildData->GetGuildID() << " PubGuildData timer is " << (GetTickCount() - qwLoadTimer) << " miscseconds.";

                }
            }); 
        } 
    });
}

void CDBPubGuildMgr::DeletePubGuildData(UINT64 qwGuildID,  function<void(CDBPubGuildDataPtr, EGuildResult)> funcLoaded)
{
    CDBPubGuildDataPtr pPubGuildData = GetPubGuildData(qwGuildID);
    if(pPubGuildData != NULL)
        return funcLoaded(pPubGuildData, eGuildSuccess);

    pPubGuildData = CDBPubGuildDataPtr(new CDBPubGuildData(qwGuildID));
    if (NULL == pPubGuildData)
        return funcLoaded(pPubGuildData, eGuildFailed);

    CTableManagerBaseForGuildPub* pManager = pPubGuildData->GetDataManagerByType(eGPDTListInfo); 
    if (NULL == pManager)
        return funcLoaded(pPubGuildData, eGuildFailed);
    UINT64 qwLoadTimer = GetTickCount();
    pManager->QueryDataByGuildID(qwGuildID,[this,pPubGuildData,funcLoaded,qwLoadTimer](INT8 byRet,UINT32 nQuerynum){
        if ( byRet != 0)
        {
            return funcLoaded(NULL, eGuildFailed);
        }
        if (nQuerynum == 0)
        {
            return funcLoaded(NULL, eGuildNotExisted);
        }
        pPubGuildData->SetNowUpdate(0);
        for (auto it = pPubGuildData->_mapDataManager.begin(); it!= pPubGuildData->_mapDataManager.end(); ++it)
        {
            if (it->first == eGPDTListInfo)
                continue;

            it->second->QueryDataByGuildID(pPubGuildData->GetGuildID(),[this,qwLoadTimer,pPubGuildData,funcLoaded](INT8 byRet,UINT32 nQuerynum){
                pPubGuildData->AddNowUpdate();
                if (pPubGuildData->GetNowUpdate() == pPubGuildData->_mapDataManager.size() - 1)
                {
                    this->AddPubGuildData(pPubGuildData);
                    funcLoaded(pPubGuildData,eGuildSuccess); 
                    LOG_INF << "Load " << pPubGuildData->GetGuildID() << " PubGuildData timer is " << (GetTickCount() - qwLoadTimer) << " miscseconds.";
                }
            }); 
        } 
    });
}

void CDBPubGuildMgr::DataOperate(UINT64 qwGuildID, EGuildPubDataType eDataType, EDataChange eUpdateType, const std::string& strData)
{
    switch (eUpdateType)
    {
        case eOpAdd:
            CreatePubGuild(qwGuildID, eDataType, strData, [eDataType, eUpdateType, strData](CDBPubGuildDataPtr pData, EGuildResult eResult){
                if (eResult != eGuildSuccess)
                    return;
                string strNewData(strData);
                CTableManagerBaseForGuildPub* pManager = pData->GetDataManagerByType(eDataType);
                if (pManager == NULL)
                    return;
                pManager->Update(strNewData, eUpdateType);
            });
            break;
        case eOpUpdate:
        case eOpReplace:
            LoadPubGuildData(qwGuildID, [this, qwGuildID, eDataType, eUpdateType, strData](CDBPubGuildDataPtr pData, EGuildResult eResult){
                if(eResult != eGuildSuccess)
                    return;

                CTableManagerBaseForGuildPub* pManager = pData->GetDataManagerByType(eDataType);
                if (pManager == NULL)
                    return;

                string strNewData(strData);
                pManager->Update(strNewData, eUpdateType);
                if(pData->HasUpdateNum())
                    this->CheckGuildState(pData, true);
            });
            break;
        case eOpDel:
            DeletePubGuildData(qwGuildID, 
                    [this, qwGuildID, eDataType, strData](CDBPubGuildDataPtr pData, EGuildResult eResult)
                    {
                        if (eResult != eGuildSuccess)
                            return;
                        CTableManagerBaseForGuildPub* pManager = pData->GetDataManagerByType(eDataType);
                        if (!pManager)
                            return;
                        string strNewData(strData);
                        pManager->DelData(strNewData, qwGuildID);
                        pManager->DumpToDBGuild(
                                [](UINT32 dwNum, UINT32 dwErrNum)
                                {
                                    LOG_DBG << "DumpToDBGuild " << dwNum << ", " << dwErrNum << ".";
                                });
                    });
            break;
        default:
            break;
    }
}

bool CDBPubGuildMgr::CheckGuildState(CDBPubGuildDataPtr pPubGuildData, bool bIsUpdate)
{
    if (bIsUpdate)
    {
        if (pPubGuildData->GetUpdateStatus() != DATAUPDATA_WILL)
        {
            pPubGuildData->SetUpdateStatus(DATAUPDATA_WILL);
            _queueUpdate.push(pPubGuildData);
        }
    }
    return true;
}

void CDBPubGuildMgr::SavePubGuild(bool bIsAll)
{
    UINT32 dwTotalUpdate = 500;
    UINT32 dwCurrentCount = 0;
    while( !_queueUpdate.empty() && (bIsAll || dwCurrentCount < dwTotalUpdate))
    {
        CDBPubGuildDataPtr pData = _queueUpdate.front();
        _queueUpdate.pop();
        dwCurrentCount += pData->UpdateNum();
        pData->SetNowUpdate(0);
        for (auto iter = pData->_mapDataManager.begin();iter != pData->_mapDataManager.end();iter++)
        {
            if(iter->second->GetUpdataNum())
            {
                iter->second->DumpToDBGuild(
                        [pData,this](UINT32 Num,UINT32 nErrNum)
                        {
                            pData->AddNowUpdate();
                            if ( pData->GetNowUpdate() == pData->_mapDataManager.size())
                            {
                                pData->SetUpdateStatus(DATAUPDATE_NONE);
                                if (pData->HasUpdateNum())
                                    this->CheckGuildState(pData, true);
                            }
                        });
            }
            else
            {
                pData->AddNowUpdate();
                if(pData->GetNowUpdate() == pData->_mapDataManager.size())
                {
                    pData->SetUpdateStatus(DATAUPDATE_NONE);
                    if (pData->HasUpdateNum())
                        this->CheckGuildState(pData, true);
                }
            }
        }
    }
}

//数据更新
void CDBPubGuildMgr::TimerCheck(time_t tNow)
{
    SavePubGuild(false);
}

bool CDBPubGuildMgr::AddLoadOrCreate(UINT64 qwGuildID)
{
    if (_setLoadOrCreate.find(qwGuildID) != _setLoadOrCreate.end())
        return false;
    _setLoadOrCreate.insert(qwGuildID);
    return true;
}

void CDBPubGuildMgr::RemoveLoadOrCreate(UINT64 qwGuildID)
{
    _setLoadOrCreate.erase(qwGuildID);
}

void CDBPubGuildMgr::GetAllInfo(SPubGuildAllInfo &rInfo, CDBPubGuildDataPtr pPubGuildData)
{
    for (auto iter = pPubGuildData->_mapDataManager.begin(); iter != pPubGuildData->_mapDataManager.end();iter++)
    {
        iter->second->GetAllInfo(rInfo);
    }
}

bool CDBPubGuildMgr::SendDataToCenter(UINT32 dwCurSize, UINT32 dwTotalSize, const TVecPubGuildAllInfo& vecPubGuildAllInfo)
{
    g_Center2DBGuildS.Send_GuildPubInfoNotify(dwCurSize, dwTotalSize, vecPubGuildAllInfo);
    return true;
}

void CDBPubGuildMgr::CreatePubGuild(UINT64 qwGuildID, EGuildPubDataType eDataType, const std::string& strData, function<void(CDBPubGuildDataPtr, EGuildResult)> cb)
{
    CDBPubGuildDataPtr pPubGuildData = GetPubGuildData(qwGuildID);
    if (!pPubGuildData)
        pPubGuildData = CDBPubGuildDataPtr(new CDBPubGuildData(qwGuildID));
    if (pPubGuildData == NULL)
        return cb(NULL, eGuildFailed);

    DoCreatePubGuild(pPubGuildData, eDataType, strData, cb);
}

void CDBPubGuildMgr::DoCreatePubGuild( CDBPubGuildDataPtr pPubGuildData, EGuildPubDataType eDataType, const string &strData,function<void(CDBPubGuildDataPtr, EGuildResult)> cb )
{
    if (!pPubGuildData)
        return cb(pPubGuildData, eGuildFailed);
    CTableManagerBaseForGuildPub* pManager = pPubGuildData->GetDataManagerByType(eDataType);
    if( NULL == pManager)
        return  cb(pPubGuildData, eGuildFailed);

    string strData2 = strData;
    pManager->Update(strData2,eOpAdd);
    pManager->DumpToDBGuild(
            [this,pPubGuildData,cb](UINT32 nQuerynum,UINT32 nErrNum)
            {
                if (nQuerynum != 1 || nErrNum)
                {
                    cb(NULL, eGuildFailed);
                    return;
                }
                if (!CDBPubGuildMgr::Instance().AddPubGuildData(pPubGuildData))
                {
                    cb(NULL, eGuildFailed); 
                    return;
                }
                cb(pPubGuildData,eGuildSuccess);
            });
}

void CDBPubGuildMgr::GetAllData(UINT32 dwPageSize)
{
    if (!dwPageSize)
    {
        LOG_CRI << "dwPageSize == 0.";
        return;
    }

    QueryData(dwPageSize,
            [dwPageSize,this](INT8 byRet,UINT32 dwTotalSize)
            {
                TVecPubGuildAllInfo vecPubGuildAllInfo;
                UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
                if(dwTotalSize % dwPageSize != 0)
                    dwTotalPage++;
                UINT32 dwTotalCount = 0;
                if(dwTotalPage == 0)//无记录
                {
                    SendDataToCenter(dwTotalPage,dwTotalSize, vecPubGuildAllInfo);
                    return ;
                }
                UINT32 dwIndex = 0;
                auto iter = _mapPubGuildData.begin();
                for(;iter != _mapPubGuildData.end();iter++)
                {
                    ++dwTotalCount;
                    ++dwIndex;
                    SPubGuildAllInfo sInfo;
                    GetAllInfo(sInfo, iter->second);
                    vecPubGuildAllInfo.push_back(sInfo);
                    if(dwIndex == dwPageSize)
                    {
                        SendDataToCenter(dwTotalCount,dwTotalSize, vecPubGuildAllInfo);     
                        vecPubGuildAllInfo.clear();
                        dwIndex = 0;
                    }
                }
                if (dwIndex)
                    SendDataToCenter(dwTotalCount, dwTotalSize, vecPubGuildAllInfo);     
            });
}

void CDBPubGuildMgr::QueryData(UINT32 dwPageSize,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tblguildlistinfo;";
    CDBMgr::Instance().DoSelectQuery(basesql.str(),NULL,
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
                for(UINT32 dwPage = 0; dwPage != dwTotalPage; dwPage++)
                {
                    mysqlpp::SQLStream querysql(NULL);
                    querysql << "SELECT * FROM tblguildlistinfo LIMIT ";
                    querysql << dwPage * dwPageSize << "," << dwPageSize;
                    querysql << ";";
                    CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,
                            [this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
                        {
                            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                            UINT32 dwDataCount = rDataRes.size();
                            for (UINT32 dwIndex = 0; dwIndex< dwDataCount; ++ dwIndex)
                            {
                                mysqlpp::Row& rRow = rDataRes[dwIndex];
                                UINT64 qwGuildID;
                                GET_UBIGINT_SAME(qwGuildID);
                                if (!qwGuildID)
                                    continue;
                                LoadPubGuildData(qwGuildID,
                                    [this, dwCount, queryfun, qwLoadTimer, byRet](CDBPubGuildDataPtr pGuildData, EGuildResult eResult)
                                {
                                    if(_mapPubGuildData.size() == dwCount)
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

void CDBPubGuildMgr::DumpToDB(bool bForBit)
{
    // TODO: 关服保存
}

