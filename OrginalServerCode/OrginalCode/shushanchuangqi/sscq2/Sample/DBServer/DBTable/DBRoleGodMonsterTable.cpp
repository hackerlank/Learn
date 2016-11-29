
#include "DBRoleGodMonsterTable.h"

void CDBRoleGodMonsterDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildUser2DB oGuildUser;
    ar >> oGuildUser;
    static_cast<SGuildUser2DB&>(*this) = oGuildUser;
}

void CDBRoleGodMonsterDBTable::InitDataByBase(const SGuildUser2DB  &rInfo)
{
    static_cast<SGuildUser2DB&>(*this) = rInfo;
}

bool CDBRoleGodMonsterDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildUser2DB newData;
    ar >> newData;
    DIFF( qwGuildID  );
    DIFF( dwFruit    );
    DIFF( dwScore    );
    DIFF( dwTotalScore    );
    return  !_setChanged.none();
}

bool CDBRoleGodMonsterDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolegodmonster(qwRoleID";
    ostr << ","<< "qwGuildID   ";
    ostr << ","<< "dwFruit     ";
    ostr << ","<< "dwScore     ";
    ostr << ","<< "dwTotalScore";
    ostr <<") Values(";
    ostr <<       (mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwGuildID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwFruit;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwScore;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwTotalScore;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleGodMonsterDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolegodmonster SET";
    UPDATE_UBIGINT_SAME(qwGuildID);
    UPDATE_UINT_SAME(dwFruit);
    UPDATE_UINT_SAME(dwScore);
    UPDATE_UINT_SAME(dwTotalScore);
    ostr << " WHERE qwRoleID=" << qwRoleID <<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleGodMonsterDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleGodMonsterDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
 
    GET_UBIGINT_SAME(qwRoleID);
    GET_UBIGINT_SAME(qwGuildID);
    GET_UINT_SAME(dwFruit);
    GET_UINT_SAME(dwScore);
    GET_UINT_SAME(dwTotalScore);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleGodMonsterTableManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolegodmonster;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblrolegodmonster is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                CDBRoleGodMonsterDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                _mapRoleGodMonsterDBData[qwRoleID]= oTable;
            }
        }
        if(byRet == 0)
           Config.SetPreLoad(eLoadGodMonster);
        //queryfun(byRet, ncount);
    });
}

void CDBRoleGodMonsterTableManager::Update(const SGuildUser2DB& oGuildUser, bool bIsAdd)
{
    string strData;
    COutArchive oArchive(strData);
    oArchive << oGuildUser;

    UINT64 qwRoleID = oGuildUser.qwRoleID;
    auto iter = _mapRoleGodMonsterDBData.find(qwRoleID);
    if (iter == _mapRoleGodMonsterDBData.end())
    {
        CDBRoleGodMonsterDBTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleGodMonsterDBData[qwRoleID] = oTemp;
    }
    else if(iter != _mapRoleGodMonsterDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleGodMonsterTableManager::GetALLInfo(TVecGuildUser2DB & rData)
{
    for (auto iter = _mapRoleGodMonsterDBData.begin();iter != _mapRoleGodMonsterDBData.end();iter++)
    {

        SGuildUser2DB oGuildUser;
        oGuildUser.qwRoleID     = iter->second.qwRoleID;
        oGuildUser.qwGuildID    = iter->second.qwGuildID;
        oGuildUser.dwFruit      = iter->second.dwFruit;
        oGuildUser.dwScore      = iter->second.dwScore;
        oGuildUser.dwTotalScore = iter->second.dwTotalScore;
        rData.push_back(oGuildUser);
    }
}

void CDBRoleGodMonsterTableManager::DumpToDB()
{
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolegodmonster WHERE qwRoleID = "<<*deliter<<";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            if (this->_nNowQuery == 0)
            {
                //fun(this->_nMaxQuery,this->_nErrQuery);
            }
        });
    }
    _vecDel.clear();

    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto iter = _mapRoleGodMonsterDBData.begin();iter != _mapRoleGodMonsterDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                    this->_nErrQuery++;
                }
                if (this->_nNowQuery == 0)
                {
                    //fun(_nMaxQuery,this->_nErrQuery);
                }
            });
        }
    }   


}

UINT32 CDBRoleGodMonsterTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleGodMonsterDBData.begin();iter != _mapRoleGodMonsterDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleGodMonsterTableManager::DelData(const SGuildUser2DB& oGuildUser)
{  
    UINT64 qwRoleID = oGuildUser.qwRoleID;
    auto iter = _mapRoleGodMonsterDBData.find(qwRoleID);
    if (iter != _mapRoleGodMonsterDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(qwRoleID);
        }

        _mapRoleGodMonsterDBData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

