// =====================================================================================
//
//       Filename:  DBGuildNewBattleHistoryTable.cpp
//
//    Description:  新帮派战历史占领帮派数数据
//
//        Version:  1.0
//        Created:  03/20/2015 04:42:40 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "DBGuildNewBattleHistoryTable.h"

CDBGuildNewBattleHistoryTable::CDBGuildNewBattleHistoryTable():
    _byMountainType(0), _qwGuildID(0), _dwTime(0)
{
}

CDBGuildNewBattleHistoryTable::~CDBGuildNewBattleHistoryTable()
{
}

void CDBGuildNewBattleHistoryTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SDBGuildNewBattleHistoryInfo sInfo;
    ar >> sInfo;

    _byMountainType     = sInfo.byMountainType;
    _qwGuildID          = sInfo.qwGuildID;
    _strGuildName       = sInfo.strGuildName;
    _strGuildOwnerName  = sInfo.strGuildOwnerName;
    _dwTime             = sInfo.dwTime;
}

bool CDBGuildNewBattleHistoryTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblnewguildbattlehistory(byMountainType, qwGuildID, strGuildName, strGuildOwnerName, dwTime) Values(";
    ostr << (mysqlpp::sql_tinyint_unsigned)_byMountainType;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strGuildName;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strGuildOwnerName;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

void CDBGuildNewBattleHistoryTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UTINYINT(byMountainType, _byMountainType);
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_STRING_CHAR(strGuildName, _strGuildName);
    GET_STRING_CHAR(strGuildOwnerName, _strGuildOwnerName);
    GET_UINT(dwTime, _dwTime);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT8 CDBGuildNewBattleHistoryTable::GetMountainType() const
{
    return _byMountainType;
}

UINT64  CDBGuildNewBattleHistoryTable::GetGuildID() const
{
    return _qwGuildID;
}

const string& CDBGuildNewBattleHistoryTable::GetGuildName() const
{
    return _strGuildName;
}

const string& CDBGuildNewBattleHistoryTable::GetGuildOwnerName() const
{
    return _strGuildOwnerName;
}

UINT32  CDBGuildNewBattleHistoryTable::GetTime() const
{
    return _dwTime;
}

CDBGuildNewBattleHistoryTableManager::CDBGuildNewBattleHistoryTableManager()
{
}

CDBGuildNewBattleHistoryTableManager::~CDBGuildNewBattleHistoryTableManager()
{
}

void CDBGuildNewBattleHistoryTableManager::GetAllInfo(TVecDBGuildNewBattleHistoryInfo& vecInfo, 
        UINT32 dwIndex, UINT32 dwCount, UINT32& dwCurIndex, UINT32& dwMaxCount)
{
    dwMaxCount = _vecData.size();
    if (dwIndex >= dwMaxCount)
    {
        dwCurIndex = dwMaxCount;
        return;
    }
    else
        dwCurIndex = dwIndex;

    UINT32 dwTmpCount = 0;
    while(dwIndex < _vecData.size())
    {
        SDBGuildNewBattleHistoryInfo sInfo;
        sInfo.byMountainType    = _vecData[dwIndex].GetMountainType(); //灵山类型
        sInfo.qwGuildID         = _vecData[dwIndex].GetGuildID(); //当前占领帮派ID
        sInfo.strGuildName      = _vecData[dwIndex].GetGuildName(); //当前占领帮派名称
        sInfo.strGuildOwnerName = _vecData[dwIndex].GetGuildOwnerName(); //当前占领帮派帮主名称
        sInfo.dwTime            = _vecData[dwIndex].GetTime(); //占领时间
        vecInfo.push_back(sInfo);
        ++dwIndex;
        if (++ dwTmpCount >= dwCount)
            break;
    }
}

void CDBGuildNewBattleHistoryTableManager::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    CDBGuildNewBattleHistoryTable cData;
    cData.InitDataByDBRow(rRow);
    _vecData.push_back(cData);
}

void CDBGuildNewBattleHistoryTableManager::QueryAllData(QueryFun queryfun)
{
    UINT32 dwPageSize = 20;
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tblnewguildbattlehistory;";
    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(),NULL,
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
                if(!dwCount)
                {
                    queryfun(byRet, dwCount);
                    return ;
                }

                UINT32 dwTotalPage = (dwCount % dwPageSize != 0) ? (dwCount/dwPageSize + 1) : (dwCount / dwPageSize);
                for(UINT32 dwPage = 0; dwPage < dwTotalPage; dwPage++)
                {
                    mysqlpp::SQLStream querysql(NULL);
                    querysql << "SELECT * FROM tblnewguildbattlehistory LIMIT ";
                    querysql << dwPage * dwPageSize << "," << dwPageSize;
                    querysql << ";";
                    CDBMgr::Instance().DoGuildSelectQuery(querysql.str(),NULL,
                            [this, dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
                        {
                            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                            UINT32 dwDataCount = rDataRes.size();
                            for (UINT32 dwIndex = 0; dwIndex < dwDataCount; ++ dwIndex)
                            {
                                mysqlpp::Row& rRow = rDataRes[dwIndex];
                                InitDataByDBRow(rRow);
                                if(_vecData.size() == dwCount)
                                {
                                    queryfun(byRet, dwCount);
                                    LOG_INF << "Load tblnewguildbattlehistory is " << GetTickCount() - qwLoadTimer << " miscseconds. Count: " << dwCount << ".";
                                }
                            }
                        });
                }
            });
}

void CDBGuildNewBattleHistoryTableManager::InsertNewData(string& strData)
{
    CInArchive ar(strData);
    TVecDBGuildNewBattleHistoryInfo vecInfo;
    ar >> vecInfo;
    for (auto& rInfo : vecInfo)
    {
        string strData2;
        COutArchive ar2(strData2);
        ar2 << rInfo;

        CDBGuildNewBattleHistoryTable cTable;
        cTable.InitDataByStr(strData2);
        string strSql;
        cTable.GetInsertSqlStr(strSql);
        _vecData.push_back(cTable);
        CDBMgr::Instance().DoGuildModifyQuery(strSql,NULL, 
                [this,strSql](UINT8 byRet, mysqlpp::SimpleResult& simRes)
                {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << strSql << "result:" << byRet;
                });
    }
}

