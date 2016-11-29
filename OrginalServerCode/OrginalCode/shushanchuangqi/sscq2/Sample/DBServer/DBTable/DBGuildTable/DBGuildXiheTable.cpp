#include "Protocols.h"
#include "DBGuildXiheTable.h"

#include "Center2DBGuildS.h"

CDBGuildXiheManager g_CDBGuildXiheManager;

void CDBGuildXihe::InitDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildXihe oGuildXihe;
    ar >> oGuildXihe;
    Copy(&oGuildXihe);
    static_cast<SGuildXihe&>(*this) = oGuildXihe;
}

bool CDBGuildXihe::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildXihe oGuildXihe;
    ar >> oGuildXihe;
    SGuildXiheEx newData;
    newData.Copy(&oGuildXihe);

    DIFF(qwRoleID);
    DIFF(byStage);
    DIFF(dwEndTime);
    DIFF(strXihe);
    DIFF(byRequest);

    return  !_setChanged.none();
}

bool CDBGuildXihe::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguildxihe(qwRoleID,byStage,dwEndTime,strXihe,byRequest) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byStage;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwEndTime;
    ostr << "," << "'" << (mysqlpp::sql_char)strXihe<<"'";
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRequest;
    ostr << ");";
    sqlstr = ostr.str();
    return true;
}

bool CDBGuildXihe::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildxihe SET";

    UPDATE_UBIGINT_SAME(qwRoleID);
    UPDATE_UTINYINT_SAME(byStage);
    UPDATE_UINT_SAME(dwEndTime);
    UPDATE_STRING_CHAR_SAME(strXihe);
    UPDATE_UTINYINT_SAME(byRequest);

    ostr << " WHERE qwRoleID=" << _qwRoleID << ";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildXihe::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildXihe::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UTINYINT_SAME(byStage);
    GET_UINT_SAME(dwEndTime);
    GET_STRING_CHAR_SAME(strXihe);
    GET_UTINYINT_SAME(byRequest);

    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBGuildXiheManager::QueryData(UINT32 dwPageSize, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tblguildxihe;";
    CDBMgr::Instance().DoSelectQuery(basesql.str(),NULL,[this, queryfun, basesql,dwPageSize,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {  
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            UINT32 dwCount = 0;
            if(byRet == 0 && dataRes.size()== 1)
            {
            mysqlpp::Row& rRow = dataRes[0];
            GET_UINT_SAME(dwCount);
            }
            else
            {
            queryfun(byRet,0);
            return ;
            }
            if(dwCount == 0)
            {
            queryfun(byRet,0);
            return ;
            }
            UINT32 dwTotalPage =dwCount % dwPageSize != 0 ? dwCount/dwPageSize+1 : dwCount/dwPageSize;
            for(UINT32 dwPage = 0; dwPage != dwTotalPage;dwPage++)
            {
                mysqlpp::SQLStream querysql(NULL);
                querysql << "select * from tblguildxihe";
                querysql << " WHERE qwRoleID >= (SELECT qwRoleID FROM tblguildxihe LIMIT ";
                querysql << dwPage*dwPageSize;
                querysql << " ,1) LIMIT ";
                querysql << dwPageSize;
                querysql << ";";
                CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,[this,dwCount,queryfun,querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                        UINT32 ncount = dataRes.size();
                        for(UINT32 i = 0; i< ncount; ++i)
                        {
                        mysqlpp::Row& rRow = dataRes[i];
                        UINT64 qwRoleID;
                        GET_UBIGINT_SAME(qwRoleID);
                        CDBGuildXihe XiheTable(qwRoleID);
                        XiheTable.InitDataByDBRow(rRow);
                        XiheTable.StrToVec();
                        _mapAllGuildXihe[qwRoleID]= XiheTable;
                        }
                        if(_mapAllGuildXihe.size() == dwCount)
                        {
                        queryfun(byRet, dwCount);
                        LOG_INF<<"--------Load tblguildxihe is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                        }
                });
            }
        });
}

void CDBGuildXiheManager::Update(const SGuildXihe& oGuildXihe)
{
    SGuildXiheEx newData;
    newData.Copy(&oGuildXihe);

    string strData;
    COutArchive iar(strData);
    iar << oGuildXihe;

    auto iter = _mapAllGuildXihe.find(newData.qwRoleID);
    if (iter == _mapAllGuildXihe.end())
    {
        CDBGuildXihe oTemp(newData.qwRoleID);
        oTemp.Update(strData, true);
        _mapAllGuildXihe[newData.qwRoleID] = oTemp;
    }
    else if(iter != _mapAllGuildXihe.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBGuildXiheManager::DumpToDB()
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelXihe.begin();deliter != _vecDelXihe.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblguildxihe WHERE qwRoleID = "<< *deliter <<";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
                LOG_INF<<"CDBGuildXiheManager::DumpToDB delete Error\n";
            }
            /*
            if (this->_nNowQuery == 0)
            {
                fun(this->_nMaxQuery,this->_nErrQuery);
            }
            */
        });
    }
    _vecDelXihe.clear();
    for (auto iter = _mapAllGuildXihe.begin();iter != _mapAllGuildXihe.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                    this->_nErrQuery++;
                    LOG_INF<<"CDBGuildXiheManager::DumpToDB update Error\n";
                }
                /*
                if (this->_nNowQuery == 0)
                {
                    fun(_nMaxQuery,this->_nErrQuery);
                }
                */
            });
        }
    }   
}

UINT32 CDBGuildXiheManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapAllGuildXihe.begin();iter != _mapAllGuildXihe.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelXihe.size();
}

void CDBGuildXiheManager::DelData(UINT64 qwRoleID)
{
    auto iter = _mapAllGuildXihe.find(qwRoleID);
    if (iter != _mapAllGuildXihe.end())
    {
        if(iter->second.IsInDB())
        {
            _vecDelXihe.push_back(qwRoleID);
        }
        _mapAllGuildXihe.erase(qwRoleID);
    }
}

void CDBGuildXiheManager::GetAllGuildXihe(UINT32 dwPageSize)
{
    QueryData(dwPageSize,[dwPageSize,this](INT8 byRet,UINT32 dwTotalSize)
            {
            UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
            if(dwTotalSize%dwPageSize != 0)
            {
            dwTotalPage++;
            }
            if(dwTotalPage == 0)//无记录
            {
            SendDataToCenter(dwTotalPage,dwTotalSize);
            return ;
            }
            _dwQueryFighterMax = dwTotalSize;
            for(auto iter = _mapAllGuildXihe.begin();iter != _mapAllGuildXihe.end();iter++)
            {
                _dwQueryFighterMax--;
                if(_dwQueryFighterMax ==0)
                {
                    SendDataToCenter(dwTotalPage,dwPageSize);     
                }
            }
            });
}

void CDBGuildXiheManager::SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize)
{

    UINT32 dwPageNum = 0;
    TVecGuildXihe vecSendData;
    if(dwTotalPage == 0)
    {
        g_Center2DBGuildS.Send_SendAllGuildXihe(dwPageNum,dwTotalPage,vecSendData);
        return ;
    }
    for(auto iter = _mapAllGuildXihe.begin();iter != _mapAllGuildXihe.end();iter++)
    {
        SGuildXihe rData;
        iter->second.CopyTo(rData);
        rData.qwRoleID = iter->first;
        vecSendData.push_back(rData);

        if(vecSendData.size() == dwPageSize)
        {
            dwPageNum++;
            g_Center2DBGuildS.Send_SendAllGuildXihe(dwPageNum,dwTotalPage,vecSendData);
            vecSendData.clear();
        }
    }
    if(!vecSendData.empty())
    {
        dwPageNum++;
        g_Center2DBGuildS.Send_SendAllGuildXihe(dwPageNum,dwTotalPage,vecSendData);
    }
    if(dwPageNum != dwTotalPage)
    {
        LOG_CRI <<"GetAllGuildXihe ERR";
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

