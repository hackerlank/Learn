#include "DBGuildMgr.h"

#include "DBConfig.h"
#include "Protocols.h"
#include "GUIDMgr.h"
#include "ProtoCommon.h"

#include "DBGuildData.h"
#include "DBGuildUserTable.h"

#include "Center2DBGuildS.h"

using namespace NGuildProt;
using namespace NProtoCommon;
using namespace NCenter2DBGuild;

CDBGuildMgr::~CDBGuildMgr()
{
    _mapGuildData.clear();
}

bool CDBGuildMgr::AddGuildData(CDBGuildDataPtr pGuildData)
{
    if (!pGuildData)
        return false;
    UINT64 qwGuildID = pGuildData->GetGuildID();

    auto it = _mapGuildDataCache.find(qwGuildID);
    if (it != _mapGuildDataCache.end())
        _mapGuildDataCache.erase(it);

    //LOG_DBG << "_mapGuildData.insert(" << qwGuildID << ".";
    if (_mapGuildData.find(qwGuildID) == _mapGuildData.end())
        _mapGuildData.insert(make_pair(qwGuildID, pGuildData));

    return true;
}

bool CDBGuildMgr::AddGuildDataCache(CDBGuildDataPtr pGuildData)
{
    if (!pGuildData)
        return false;
    UINT64 qwGuildID = pGuildData->GetGuildID();

    auto it = _mapGuildData.find(qwGuildID);
    if (it != _mapGuildData.end())
    {
        LOG_CRI << "AddGuildDataCache with _mapGuildData has data.(" << qwGuildID << ").";
        _mapGuildData[qwGuildID] = pGuildData;
        return false;
    }

    //LOG_DBG << "_mapGuildDataCache.insert(" << qwGuildID << ".";
    _mapGuildDataCache.insert(make_pair(qwGuildID, pGuildData));

    return true;
}

void CDBGuildMgr::EraseGuildDataCache(CDBGuildDataPtr pGuildData)
{
    // FIXME: 如果清除，异步回调会找不到对象崩溃
    /*
    if (!pGuildData)
        return;
    UINT64 qwGuildID = pGuildData->GetGuildID();

    auto it = _mapGuildDataCache.find(qwGuildID);
    if (it != _mapGuildDataCache.end())
        _mapGuildDataCache.erase(it);
        */
}

CDBGuildDataPtr CDBGuildMgr::GetGuildData(UINT64 qwGuildID)
{
    auto it = _mapGuildData.find(qwGuildID);
    if(it == _mapGuildData.end())
    {
        it = _mapGuildDataCache.find(qwGuildID);
        if(it == _mapGuildDataCache.end())
            return NULL;
        else
            return it->second;

    }
    else 
        return it->second;
}

void CDBGuildMgr::UserLoginGuild(UINT64 qwRoleID)
{
    if (!qwRoleID)
        return;
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select qwGuildID from tblroleguilddata where qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoSelectQuery(basesql.str(),NULL,
            [this, basesql, qwLoadTimer, qwRoleID] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable 
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << (INT32)byRet << ", count = " << dataRes.size() << ", time = " << GetTickCount() - qwLoadTimer << ".";
                UINT64 qwGuildID = 0;
                if(byRet == 0 && dataRes.size()== 1)
                {
                    mysqlpp::Row& rRow = dataRes[0];
                    GET_UBIGINT_SAME(qwGuildID);
                }
                else
                    return;
                if (qwGuildID)
                {
                    LoadGuildData(qwGuildID, 
                            [this, qwRoleID](CDBGuildDataPtr pGuildData, EGuildResult eResult)
                    {
                        if (eResult == eGuildSuccess)
                        {
                            if (pGuildData->GetGuildID())
                                SendDataToCenter(*pGuildData);
                            else
                                SendUserDataToCenter(*pGuildData, qwRoleID);
                        }
                        else
                            LOG_WRN << "LoadGuildData error, eResult = " << (UINT32)eResult << ".";
                    });
                }
                else
                {
                    LoadIdleGuildUserData(qwRoleID, 
                            [this, qwRoleID](CDBGuildDataPtr pGuildData, EGuildResult eResult)
                            {
                                if (eResult != eGuildSuccess)
                                    LOG_WRN << "LoadIdleGuildUserData error, eResult = " << (UINT32)eResult << ".";
                                else
                                {
                                    LOG_DBG << "Start SendUserDataToCenter.";
                                    SendUserDataToCenter(*pGuildData, qwRoleID);
                                }
                            }
                            );
                }

            });
}

void CDBGuildMgr::LoginGuild(UINT64 qwGuildID, UINT64 qwRoleID)
{
    LoadGuildData(qwGuildID, 
            [this, qwRoleID](CDBGuildDataPtr pGuildData, EGuildResult eResult)
        {
            if (eResult != eGuildSuccess)
            {
                LOG_WRN << "LoadGuildData error, eResult = " << (UINT32)eResult << ".";
                return;
            }
            if (pGuildData->GetGuildID())
                SendDataToCenter(*pGuildData);
            else
                SendUserDataToCenter(*pGuildData, qwRoleID);
        });
}

void CDBGuildMgr::LoadAllGuildData()
{
    UINT32 dwPageSize = 20;
    QueryData(dwPageSize,
            [dwPageSize, this](INT8 byRet,UINT32 dwTotalSize)
            {
                TVecDBGuildAllInfo vecDBGuildAllInfo;
                UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
                if(dwTotalSize % dwPageSize != 0)
                    dwTotalPage++;
                UINT32 dwTotalCount = 0;
                if(dwTotalPage == 0)//无记录
                {
                    SendDataToCenter(dwTotalPage,dwTotalSize, vecDBGuildAllInfo);
                    return ;
                }
                UINT32 dwIndex = 0;
                for(auto iter = _mapGuildData.begin() ;iter != _mapGuildData.end(); ++iter)
                {
                    ++dwTotalCount;
                    ++dwIndex;
                    SDBGuildAllInfo sInfo;
                    GetAllInfo(sInfo, *(iter->second));
                    vecDBGuildAllInfo.push_back(sInfo);
                    if(dwIndex == dwPageSize)
                    {
                        SendDataToCenter(dwTotalCount,dwTotalSize, vecDBGuildAllInfo);     
                        vecDBGuildAllInfo.clear();
                        dwIndex = 0;
                    }
                }
                if (dwIndex)
                    SendDataToCenter(dwTotalCount, dwTotalSize, vecDBGuildAllInfo);     
            });
}

void CDBGuildMgr::LoadGuildData(UINT64 qwGuildID, function<void(CDBGuildDataPtr, EGuildResult)> funcLoaded)
{
    CDBGuildDataPtr pGuildData = GetGuildData(qwGuildID);
    if(pGuildData)
        return funcLoaded(pGuildData, eGuildSuccess);

    CDBGuildDataPtr pGuildDataTmp(new CDBGuildData(qwGuildID));
    pGuildData = pGuildDataTmp;
    if (!pGuildData)
        return funcLoaded(pGuildData, eGuildFailed);
    AddGuildDataCache(pGuildData);

    if (qwGuildID)
    {
        CTableManagerBaseForGuild* pManager = pGuildData->GetDataManagerByType(eGDTBaseInfo); 
        if (!pManager)
            return funcLoaded(pGuildData, eGuildFailed);
        UINT64 qwLoadTimer = GetTickCount();
        pManager->QueryDataByGuildID(qwGuildID,[this,pGuildData,funcLoaded,qwLoadTimer](INT8 Ret,UINT32 nQuerynum){
            if ( Ret != 0)
                return funcLoaded(NULL, eGuildFailed);
            if (nQuerynum == 0) // 查不到数据
                return funcLoaded(NULL, eGuildNotExisted);
            pGuildData->SetNowUpdate(0);
            for (auto iter = pGuildData->_mapDataManager.begin(); iter!= pGuildData->_mapDataManager.end(); ++iter)
            {
                if (iter->first == eGDTBaseInfo)
                    continue;

                iter->second->QueryDataByGuildID(pGuildData->GetGuildID(),[this,qwLoadTimer,pGuildData,funcLoaded](INT8 byRet,UINT32 nQuerynum){
                    pGuildData->AddNowUpdate();
                    if (pGuildData->GetNowUpdate() == pGuildData->_mapDataManager.size() - 1)
                    {
                        this->AddGuildData(pGuildData);
                        funcLoaded(pGuildData,eGuildSuccess); 
                        LOG_INF << "Load " << pGuildData->GetGuildID() << " GuildData timer is " << (GetTickCount() - qwLoadTimer) << " miscseconds.";

                    }
                }); 
            } 
        });
    }
    else
    {
        AddGuildData(pGuildData);
        return funcLoaded(pGuildData, eGuildSuccess);
    }
}

void CDBGuildMgr::LoadIdleGuildUserData(UINT64 qwRoleID, function<void(CDBGuildDataPtr, EGuildResult)> funcLoaded)
{
    CDBGuildDataPtr pGuildData = GetGuildData(0);
    if(!pGuildData)
    {
        CDBGuildDataPtr pGuildDataTmp(new CDBGuildData(0));
        pGuildData = pGuildDataTmp;
    }
    if (!pGuildData)
        return funcLoaded(pGuildData, eGuildFailed);
    AddGuildData(pGuildData);

    CDBGuildUserTableManager* pManager = static_cast<CDBGuildUserTableManager*>(pGuildData->GetDataManagerByType(eGDTUser));
    if (!pManager)
        return funcLoaded(pGuildData, eGuildFailed);
    UINT64 qwLoadTimer = GetTickCount();
    pManager->QueryDataByRoleID(0, qwRoleID, 
            [this,pGuildData,funcLoaded,qwLoadTimer](INT8 Ret,UINT32 nQuerynum)
            {
                if ( Ret != 0)
                    return funcLoaded(NULL, eGuildFailed);
                if (nQuerynum == 0) // 查不到数据
                    return funcLoaded(NULL, eGuildNotExisted);
                return funcLoaded(pGuildData, eGuildSuccess);
            });
}

void CDBGuildMgr::GuildDataOperate(UINT64 qwGuildID, EGuildDataType eDataType, EDataChange eUpdateType, const std::string& strData)
{
    switch (eUpdateType)
    {
        case eOpAdd:
            CreateGuild(qwGuildID, eDataType, strData, 
                    [eDataType, eUpdateType, strData](CDBGuildDataPtr pGuildData, EGuildResult eResult)
                    {
                        //LOG_DBG << "CreateGuild eResult = " << (UINT32) eResult << ".";
                        if (eResult != eGuildSuccess)
                            return;
                    });
            break;
        case eOpUpdate:
        case eOpReplace:
            LoadGuildData(qwGuildID, [this, qwGuildID, eDataType, eUpdateType, strData](CDBGuildDataPtr pGuildData, EGuildResult eResult){
                if(eResult != eGuildSuccess)
                    return;

                CTableManagerBaseForGuild* pManager = pGuildData->GetDataManagerByType(eDataType);
                if (pManager == NULL)
                    return;

                string strNewData(strData);
                pManager->Update(strNewData, eUpdateType);
                if(pGuildData->HasUpdateNum())
                    this->CheckGuildState(pGuildData, true);
            });
            break;
        case eOpDel:
            LoadGuildData(qwGuildID, 
                    [this, qwGuildID, eDataType, strData](CDBGuildDataPtr pGuildData, EGuildResult eResult)
                    {
                        LOG_DBG << "eResult = " << (UINT32) eResult << " when Del GuildData. type = " << (UINT32) eDataType << ", qwGuildID = " << qwGuildID <<  " .";
                        if (eResult != eGuildSuccess)
                            return;
                        CTableManagerBaseForGuild* pManager = pGuildData->GetDataManagerByType(eDataType);
                        if (!pManager)
                        {
                            LOG_CRI << "pManager == NULL, type = " << (UINT32) eDataType << ", qwGuildID = " << qwGuildID << ".";
                            return;
                        }
                        string strNewData(strData);
                        pManager->DelData(strNewData, qwGuildID);
                        pManager->DumpToDBGuild(
                            [](UINT32 dwNum, UINT32 dwErrNum)
                            {
                                //LOG_DBG << "DumpToDBGuild " << dwNum << ", " << dwErrNum << ".";
                            });
                    });
            break;
        default:
            break;
    }
}

bool CDBGuildMgr::CheckGuildState(CDBGuildDataPtr pGuildData,bool bIsUpdate)
{
    if (bIsUpdate)
    {
        if (pGuildData->GetUpdateStatus() != DATAUPDATA_WILL)
        {
            pGuildData->SetUpdateStatus(DATAUPDATA_WILL);
            _queueUpdate.push(pGuildData);
        }
    }
    return true;
}

void CDBGuildMgr::SaveGuild(bool bIsAll)
{
    UINT32 dwTotalUpdate = 500;
    UINT32 dwCurrentNum = 0;
    while( !_queueUpdate.empty() && (bIsAll || dwCurrentNum < dwTotalUpdate))
    {
        CDBGuildDataPtr pGuildData = _queueUpdate.front();
        _queueUpdate.pop();
        dwCurrentNum += pGuildData->UpdateNum();
        pGuildData->SetNowUpdate(0);
        for (auto iter = pGuildData->_mapDataManager.begin();iter != pGuildData->_mapDataManager.end();iter++)
        {
            if(iter->second->GetUpdataNum())
            {
                iter->second->DumpToDBGuild([pGuildData,this](UINT32 Num,UINT32 nErrNum){
                    pGuildData->AddNowUpdate();
                    if ( pGuildData->GetNowUpdate() == pGuildData->_mapDataManager.size())
                    {
                        pGuildData->SetUpdateStatus(DATAUPDATE_NONE);
                        if(pGuildData->HasUpdateNum())
                            this->CheckGuildState(pGuildData, true);
                    }
                });
            }
            else
            {
                pGuildData->AddNowUpdate();
                if(pGuildData->GetNowUpdate() == pGuildData->_mapDataManager.size())
                {
                    pGuildData->SetUpdateStatus(DATAUPDATE_NONE);
                    if(pGuildData->HasUpdateNum()) 
                        this->CheckGuildState(pGuildData, true);
                }
            }
        }
    }
}

bool CDBGuildMgr::EnterGame(CDBGuildData& rGuildData)
{
    rGuildData.SetGuildState(eGuildBusy);
    return true;
}

void CDBGuildMgr::GetAllInfo(SDBGuildAllInfo &rInfo, CDBGuildData& rGuildData)
{
    for (auto iter = rGuildData._mapDataManager.begin(); iter != rGuildData._mapDataManager.end();iter++)
    {
        iter->second->GetAllInfo(rInfo);
    }
    rInfo.sBaseInfo.strName = rInfo.sBaseInfo.strName;
    rInfo.sBaseInfo.qwGuildID = rGuildData.GetGuildID();
}

// 发送所有帮派的神像供奉相关信息给Center用于发奖励
void CDBGuildMgr::SendAllGuildWorshipInfo()
{
    LOG_WRN << "Need SendAllGuildWorshipInfo.";
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select qwGuildID, byWorshipCount from tblguildstatue where byWorshipCount != 0;";
    CDBMgr::Instance().DoSelectQuery(basesql.str(),NULL,
            [this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << static_cast<INT32>(byRet) << "(" << rDataRes.size() << "),  time = " << GetTickCount() - qwLoadTimer << ".";
                if(byRet != 0)
                    return ;
                UINT32 dwCount = rDataRes.size();
                TVecGSWorshipInfo vecGSWorshipInfo;
                for(UINT32 dwIndex = 0; dwIndex < dwCount; ++dwIndex)
                {
                    const UINT32 dwPageSize = 20;
                    bool bFinal = (dwIndex + 1) >= dwCount ? true:false;
                    UINT64 qwGuildID = 0;
                    UINT8 byWorshipCount = 0;
                    mysqlpp::Row& rRow = rDataRes[dwIndex];
                    GET_UBIGINT_SAME(qwGuildID);
                    GET_UTINYINT_SAME(byWorshipCount);
                    if (vecGSWorshipInfo.size() >= dwPageSize || bFinal)

                    {
                        g_Center2DBGuildS.Send_SendAllGuildStatueWorshipCount(vecGSWorshipInfo);
                        vecGSWorshipInfo.clear();
                    }

                    if (!qwGuildID || !byWorshipCount)
                        continue;

                    SGSWorshipInfo sGSWorshipInfo;
                    sGSWorshipInfo.qwGuildID = qwGuildID;
                    sGSWorshipInfo.byWorshipCount = byWorshipCount;

                    auto it = _mapGuildData.find(qwGuildID);
                    if (it != _mapGuildData.end())
                    {
                        CDBGuildDataPtr pGuildData = it->second;
                        if (pGuildData)
                        {
                            auto it2 = pGuildData->_mapDataManager.find(eGDTUser);
                            CDBGuildUserTableManager* pManager = static_cast<CDBGuildUserTableManager*>(it2->second);
                            pManager->GetAllRoleID(sGSWorshipInfo.vecMemberID);
                            vecGSWorshipInfo.push_back(sGSWorshipInfo);
                            if (vecGSWorshipInfo.size() >= dwPageSize || bFinal)
                            {
                                g_Center2DBGuildS.Send_SendAllGuildStatueWorshipCount(vecGSWorshipInfo);
                                vecGSWorshipInfo.clear();
                            }
                            continue;
                        }
                    }
                }
            });
}

void CDBGuildMgr::DumpToDB(bool bForBit)
{
    // TODO: 关服保存
    /* 
    if(GetUpdataNum() ==0 )
    {
        return ;
    }
    UINT32 nNowQuery = 0;
    UINT32 nMaxQuery = 1000;
    UINT32 nDelNum = _vecDelArena.size();
    for (auto deliter = _vecDelArena.begin();deliter != _vecDelArena.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbltotalarena where qwRoleID="<<*deliter <<  ";";
        CDBMgr::Instance().DoArenaModifyQuery(sqlstr.str(),NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                });
    }
    _vecDelArena.clear();
    if(nDelNum >= nMaxQuery && !bForBit)
    {
        return ;
    }
    nNowQuery = nDelNum;

    for (auto iter = _mapRoleArenaData.begin();iter != _mapRoleArenaData.end();iter++)
    {
        if(nNowQuery >= nMaxQuery && !bForBit)
        {
            return ;
        }
        bool bDoCase = true;
        if (iter->second.IsNew())
        {
            string sqlstr;
            iter->second.GetInsertSqlStr(sqlstr);
            CDBMgr::Instance().DoArenaModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                    });
        }
        else if(iter->second.IsChange())
        {
            string sqlstr;
            iter->second.GetUpdateSqlStr(sqlstr);
            CDBMgr::Instance().DoArenaModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                    });

        }
        else
        {
            bDoCase = false;
        }
        if(bDoCase)
        {
            iter->second.ResetChange();
            nNowQuery++;
        }
    }   
    */

}

bool CDBGuildMgr::SendDataToCenter(CDBGuildData& rGuildData)
{
    SDBGuildAllInfo  sInfo; 
    GetAllInfo(sInfo, rGuildData);
    //LOG_DBG << "Send_GuildLoginNotify(" << rGuildData.GetGuildID() << ").";
    g_Center2DBGuildS.Send_GuildLoginNotify(rGuildData.GetGuildID(), sInfo);
    return true;
}

bool CDBGuildMgr::SendDataToCenter (UINT32 dwTotalPage, UINT32 dwTotalSize, const TVecDBGuildAllInfo& vecDBGuildAllInfo)
{
    g_Center2DBGuildS.Send_AllGuildLoginNotify(dwTotalPage, dwTotalSize, vecDBGuildAllInfo);
    return true;
}

bool CDBGuildMgr::SendUserDataToCenter(CDBGuildData& rGuildData, UINT64 qwRoleID)
{
    auto it = rGuildData._mapDataManager.find(eGDTUser);
    CDBGuildUserTableManager* pManager = static_cast<CDBGuildUserTableManager*>(it->second);
    TVecDBGuildUserInfo vecGuildUserInfo;
    SDBGuildUserInfo sGuildUserInfo;
    if (pManager->GetUserInfo(sGuildUserInfo, qwRoleID))
        vecGuildUserInfo.push_back(sGuildUserInfo);
    //LOG_DBG << "Send_GuildUserLoginNotify(" << qwRoleID << ").";
    g_Center2DBGuildS.Send_GuildUserLoginNotify(qwRoleID, vecGuildUserInfo);
    return true;
}

void CDBGuildMgr::CreateGuild(UINT64 qwGuildID, EGuildDataType eDataType, const std::string& strData, function<void(CDBGuildDataPtr, EGuildResult)> cb)
{
    //LOG_DBG << "Start CreateGuild(" << qwGuildID << "), eDataType = " << (UINT32)eDataType << ".";
    bool bNew = false;
    CDBGuildDataPtr pGuildData = GetGuildData(qwGuildID);
    if (!pGuildData)
    {
        CDBGuildDataPtr pGuildDataTmp(new CDBGuildData(qwGuildID));
        pGuildData = pGuildDataTmp;
        bNew = true;
    }
    if (!pGuildData)
        return cb(NULL, eGuildFailed);
    if (bNew)
        AddGuildDataCache(pGuildData);

    DoCreateGuild(bNew, pGuildData, eDataType, strData, cb);
}

void CDBGuildMgr::DoCreateGuild(bool bNew, CDBGuildDataPtr pGuildData, EGuildDataType eDataType, const string &strData,function<void(CDBGuildDataPtr, EGuildResult)> cb )
{
    if (!pGuildData)
        return cb(pGuildData, eGuildFailed);
    CTableManagerBaseForGuild* pManager = pGuildData->GetDataManagerByType(eDataType);
    if( NULL == pManager)
    {
        if (bNew)
            EraseGuildDataCache(pGuildData);
        return  cb(pGuildData, eGuildFailed);
    }

    string strData2 = strData;
    pManager->Update(strData2,eOpAdd);
    pManager->DumpToDBGuild([this,bNew,pGuildData,cb](UINT32 nQuerynum,UINT32 nErrNum){
        if (nQuerynum != 1 || nErrNum)
        {
            cb(NULL, eGuildFailed);
            if (bNew)
                EraseGuildDataCache(pGuildData);
            return;
        }
        if (!CDBGuildMgr::Instance().AddGuildData(pGuildData))
        {
            LOG_CRI << "AddGuildData Error.";
            if (bNew)
                EraseGuildDataCache(pGuildData);
            cb(NULL, eGuildFailed); 
            return;
        }
        cb(pGuildData,eGuildSuccess);
    });
}

//离线数据处理
void CDBGuildMgr::CleanIdleGuild()
{
    UINT32 dwCurrentSize    = _mapGuildData.size();

    UINT32 dwReuce = 0;
    if (dwCurrentSize > DEFAULT_GUILD_HIGH_MARK)
        dwReuce = dwCurrentSize -  DEFAULT_GUILD_LOW_MARK;

    while(dwReuce > 0 && !_queueOffLine.empty())
    {
        CDBGuildDataPtr pGuildData = _queueOffLine.front();
        if (pGuildData->GetUpdateStatus() != DATAUPDATA_WILL)
        {
            if( pGuildData->HasUpdateNum())
                this->CheckGuildState(pGuildData, true);
            else
            {
                if (pGuildData->GetGuildState() == eGuildIdle)
                {
                    _mapGuildData.erase(pGuildData->GetGuildID());
                    --dwReuce;
                }
            }
        }
        _queueOffLine.pop();
    }
}

void CDBGuildMgr::QueryData(UINT32 dwPageSize,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tblguilddata;";
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
                for(UINT32 dwPage = 0; dwPage < dwTotalPage; dwPage++)
                {
                    mysqlpp::SQLStream querysql(NULL);
                    querysql << "SELECT qwGuildID FROM tblguilddata LIMIT ";
                    querysql << dwPage * dwPageSize << "," << dwPageSize;
                    querysql << ";";
                    CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,
                            [this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
                        {
                            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                            UINT32 dwDataCount = rDataRes.size();
                            for (UINT32 dwIndex = 0; dwIndex < dwDataCount; ++ dwIndex)
                            {
                                mysqlpp::Row& rRow = rDataRes[dwIndex];
                                UINT64 qwGuildID = 0;
                                GET_UBIGINT_SAME(qwGuildID);
                                if (!qwGuildID)
                                    continue;
                                LoadGuildData(qwGuildID, 
                                    [this, dwCount, queryfun, qwLoadTimer, byRet](CDBGuildDataPtr pGuildData, EGuildResult eResult)
                                {
                                    if(_mapGuildData.size() == dwCount)
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

