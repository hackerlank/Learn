
#include "DBActivityCenterDBTable.h"

void CDBActivityCenterDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SActivityOpt oActivityOpt;
    ar >> oActivityOpt;
    static_cast<SActivityOpt&>(*this) = oActivityOpt;
}

void CDBActivityCenterDBTable::InitDataByBase(const SActivityOpt  &rInfo)
{
    static_cast<SActivityOpt&>(*this) = rInfo;
}

bool CDBActivityCenterDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SActivityOpt newData;
    ar >> newData;
    DIFF(dwActID       );
    DIFF(byIndex       );
    DIFF(strName       );
    DIFF(dwSync       );
    DIFF(dwAlarm       );
    DIFF(dwReady       );
    DIFF(dwBegin       );
    DIFF(dwEnd         );
    DIFF(bSync         );
    DIFF(dwOptTime     );
    return  !_setChanged.none();
}

bool CDBActivityCenterDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblactivitycenter(dwActID";
    ostr << ","<< "byIndex";
    ostr << ","<< "strName";
    ostr << ","<< "dwSync";
    ostr << ","<< "dwAlarm";
    ostr << ","<< "dwReady";
    ostr << ","<< "dwBegin";
    ostr << ","<< "dwEnd";
    ostr << ","<< "bSync";
    ostr << ","<< "dwOptTime";
    ostr <<") Values(";
    ostr <<       (mysqlpp::sql_int_unsigned)dwActID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byIndex;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)strName;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwSync;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwAlarm;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwReady;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwBegin;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwEnd;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)bSync;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwOptTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

UINT32 CDBActivityCenterDBTable::GetActID() const
{
    return dwActID;
}

UINT8 CDBActivityCenterDBTable::GetIndex() const
{
    return byIndex;
}

bool CDBActivityCenterDBTable::GetUpdateSqlStr(string& strsql)
{
    
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblactivitycenter SET";
    UPDATE_STRING_CHAR_SAME(strName);
    UPDATE_UINT_SAME(dwSync);
    UPDATE_UINT_SAME(dwAlarm);
    UPDATE_UINT_SAME(dwReady);
    UPDATE_UINT_SAME(dwBegin);
    UPDATE_UINT_SAME(dwEnd);
    UPDATE_UTINYINT_SAME(bSync);
    UPDATE_UINT_SAME(dwOptTime);
    ostr << " WHERE dwActID=" << dwActID <<" and byIndex="<<byIndex<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    
    return true;
}

void CDBActivityCenterDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBActivityCenterDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UINT_SAME(dwActID);
    GET_UTINYINT_SAME(byIndex);
    GET_STRING_CHAR_SAME(strName);
    GET_UINT_SAME(dwSync);
    GET_UINT_SAME(dwAlarm);
    GET_UINT_SAME(dwReady);
    GET_UINT_SAME(dwBegin);
    GET_UINT_SAME(dwEnd);
    GET_UTINYINT_SAME(bSync);
    GET_UINT_SAME(dwOptTime);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBActivityCenterTableManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblactivitycenter;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblrolegodmonster is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT32 dwActID = 0;
        UINT8 byIndex = 0;
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                dwActID = (mysqlpp::sql_int_unsigned)rRow[0];
                byIndex = (mysqlpp::sql_tinyint_unsigned)rRow[1];
                CDBActivityCenterDBTable oTable(dwActID,byIndex);
                oTable.InitDataByDBRow(rRow);
                SKey oKey(dwActID,byIndex);
                _mapData.insert(make_pair(oKey,oTable));
            }
        }
        if(byRet == 0)
           Config.SetPreLoad(eLoadActivity);
        //queryfun(byRet, ncount);
    });
}


void CDBActivityCenterTableManager::Update(const SActivityOpt& oActivityOpt,bool bOpt)
{
    string strData;
    COutArchive oArchive(strData);
    oArchive << oActivityOpt;
    
    UINT32 dwActID = oActivityOpt.dwActID;
    UINT8 byIndex = oActivityOpt.byIndex;
    SKey oKey(dwActID,byIndex);
    auto oIt = _mapData.find(oKey);
    if(oIt == _mapData.end())
    {
        CDBActivityCenterDBTable oTemp(dwActID,byIndex);
        oTemp.Update(strData,true);
        _mapData.insert(make_pair(oKey,oTemp));
    }else
    {
        oIt->second.Update(strData,false);
    }
}


void CDBActivityCenterTableManager::GetALLInfo(TVecActivityOpt & rData)
{
    for (auto iter = _mapData.begin();iter != _mapData.end();iter++)
    {

        SActivityOpt oActivityOpt;
        oActivityOpt.dwActID     = iter->second.GetActID();
        oActivityOpt.byIndex     = iter->second.GetIndex();
        oActivityOpt.strName     = iter->second.strName;
        oActivityOpt.dwSync     = iter->second.dwSync;
        oActivityOpt.dwAlarm     = iter->second.dwAlarm;
        oActivityOpt.dwReady     = iter->second.dwReady;
        oActivityOpt.dwBegin     = iter->second.dwBegin;
        oActivityOpt.dwEnd       = iter->second.dwEnd;
        oActivityOpt.bSync       = iter->second.bSync;
        oActivityOpt.dwOptTime   = iter->second.dwOptTime;
        rData.push_back(oActivityOpt);
    }
}

void CDBActivityCenterTableManager::DumpToDB()
{
    
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        UINT32 dwActID = deliter->dwActID;
        UINT8  byIndex = deliter->byIndex;
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblactivitycenter WHERE dwActID = "<<dwActID<<"and byIndex = "<<byIndex<<";";
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
    for (auto iter = _mapData.begin();iter != _mapData.end();iter++)
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

UINT32 CDBActivityCenterTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapData.begin();iter != _mapData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();
}


void CDBActivityCenterTableManager::DelData(const SActivityOpt& oActivityOpt)
{  
    UINT32 dwActID = oActivityOpt.dwActID;
    UINT32 byIndex = oActivityOpt.byIndex;
    SKey oKey(dwActID,byIndex);
    auto it = _mapData.find(oKey);
    if(it != _mapData.end())
    {
        if (it->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }
        _mapData.erase(it);
    }
}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

