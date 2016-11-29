#include "DBBuffTable.h"
#include "Tokenizer.h"

CDBBuffTable::CDBBuffTable():
    _qwRoleID(0), _qwOwnerID(0),
    _byBuffType(0), _wBuffID(0), _byBuffState(0), _dwBuffTime(0), _dwBuffCount(0)
{
}

void CDBBuffTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SDBBuffInfo sBuffInfo;
    ar >> sBuffInfo;

    if(!InitDataByBuff(sBuffInfo))
        return ;
}

bool CDBBuffTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SDBBuffInfo sBuffInfo;
    ar >> sBuffInfo;

    DIFFONLY2(qwRoleID, _qwRoleID, sBuffInfo.qwRoleID);
    DIFFONLY2(qwOwnerID, _qwOwnerID, sBuffInfo.qwOwnerID);
    DIFFONLY2(byBuffType, static_cast<EBuffType>(_byBuffType), sBuffInfo.eBuffType);
    DIFFONLY2(wBuffID, _wBuffID, sBuffInfo.wBuffID);
    DIFFONLY2(byBuffState, static_cast<EBuffState>(_byBuffState), sBuffInfo.eBuffState);
    DIFFONLY2(dwBuffTime, _dwBuffTime, sBuffInfo.dwBuffTime);
    DIFFONLY2(dwBuffCount, _dwBuffCount, sBuffInfo.dwBuffCount);

    ostringstream strTmp;
    for (auto it = sBuffInfo.vecBuffParam.begin(); it != sBuffInfo.vecBuffParam.end(); ++it)
    {
        strTmp << *it << "|";
    }

    DIFFONLY2(strBuffParam, strTmp.str(), _strBuffParam);

    return  !_setChanged.none();
}

bool CDBBuffTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblbuffdata(qwRoleID,qwOwnerID,"\
        "byBuffType,wBuffID,byBuffState,dwBuffTime,dwBuffCount, strBuffParam) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwOwnerID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byBuffType;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wBuffID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byBuffState;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwBuffTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwBuffCount;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strBuffParam;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBBuffTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblbuffdata SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UBIGINT(qwOwnerID, _qwOwnerID);
    UPDATE_UTINYINT(byBuffType, _byBuffType);
    UPDATE_USMALLINT(wBuffID, _wBuffID);
    UPDATE_UTINYINT(byBuffState, _byBuffState);
    UPDATE_UINT(dwBuffTime, _dwBuffTime);
    UPDATE_UINT(dwBuffCount, _dwBuffCount);
    UPDATE_STRING_CHAR(strBuffParam, _strBuffParam);

    ostr << " WHERE qwOwnerID =" << _qwOwnerID << " and wBuffID="<<_wBuffID<<" and byBuffType="<<(UINT16)_byBuffType<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBBuffTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBBuffTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UBIGINT(qwOwnerID, _qwOwnerID);
    GET_UTINYINT(byBuffType, _byBuffType);
    GET_USMALLINT(wBuffID, _wBuffID);
    GET_UTINYINT(byBuffState, _byBuffState);
    GET_UINT(dwBuffTime, _dwBuffTime);
    GET_UINT(dwBuffCount, _dwBuffCount);
    GET_STRING_CHAR(strBuffParam, _strBuffParam);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBBuffTable::GetOwnerID() const
{
    return _qwOwnerID;
}

UINT64  CDBBuffTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT8   CDBBuffTable::GetBuffType() const
{
    return _byBuffType;
}

UINT16  CDBBuffTable::GetBuffID() const
{
    return _wBuffID;
}

UINT8   CDBBuffTable::GetBuffState() const
{
    return _byBuffState;
}

UINT32  CDBBuffTable::GetBuffTime() const
{
    return _dwBuffTime;
}

const string& CDBBuffTable::GetBuffParam() const
{
    return _strBuffParam;
}

UINT32 CDBBuffTable::GetBuffCount() const
{
    return _dwBuffCount;
}

bool CDBBuffTable::InitDataByBuff(const SDBBuffInfo& rBuffInfo)
{
    _qwRoleID = rBuffInfo.qwRoleID;
    _qwOwnerID = rBuffInfo.qwOwnerID;
    _byBuffType = static_cast<UINT8>(rBuffInfo.eBuffType);
    _wBuffID = rBuffInfo.wBuffID;
    _byBuffState = static_cast<UINT8>(rBuffInfo.eBuffState);
    _dwBuffTime = rBuffInfo.dwBuffTime;
    _dwBuffCount = rBuffInfo.dwBuffCount;

    ostringstream strTmp;
    for (auto it = rBuffInfo.vecBuffParam.begin(); it != rBuffInfo.vecBuffParam.end(); ++it)
    {
        strTmp << *it << "|";
    }

    _strBuffParam = strTmp.str();
    return true;
}

void CDBBuffTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblbuffdata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblbuffdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i < ncount; ++i)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBBuffTable ssDBBuffTable;
                ssDBBuffTable.InitDataByDBRow(rRow);
                SBuffKey sBuffKey = SBuffKey(ssDBBuffTable.GetOwnerID(), ssDBBuffTable.GetBuffType(), ssDBBuffTable.GetBuffID());
                _mapBuffData[sBuffKey] = ssDBBuffTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBBuffTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SDBBuffInfo sBuffInfo;
    ar >> sBuffInfo;

    SBuffKey sBuffKey = SBuffKey(sBuffInfo.qwOwnerID, static_cast<UINT8>(sBuffInfo.eBuffType), sBuffInfo.wBuffID);
    auto iter = _mapBuffData.find(sBuffKey);
    if (iter == _mapBuffData.end() && bIsAdd)
    {
        CDBBuffTable CDBBuffTable;
        CDBBuffTable.Update(strData, bIsAdd);
        _mapBuffData[sBuffKey] = CDBBuffTable;
    }
    else if(iter != _mapBuffData.end() && !bIsAdd)
        iter->second.Update(strData, bIsAdd);
    else
         LOG_CRI << "ERR update! bIsAdd = " << (UINT32)bIsAdd << ".";
}

void CDBBuffTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto it = _mapBuffData.begin();it != _mapBuffData.end();it++)
    {
        SDBBuffInfo sBuffInfo;
        sBuffInfo.qwRoleID = (it->second).GetRoleID();
        sBuffInfo.qwOwnerID = (it->second).GetOwnerID();
        sBuffInfo.eBuffType = static_cast<EBuffType>((it->second).GetBuffType());
        sBuffInfo.wBuffID = (it->second).GetBuffID();
        sBuffInfo.eBuffState = static_cast<EBuffState>((it->second).GetBuffState());
        sBuffInfo.dwBuffTime = (it->second).GetBuffTime();
        sBuffInfo.dwBuffCount = (it->second).GetBuffCount();
        Tokenizer tk((it->second).GetBuffParam(), "|");
        for (size_t i = 0; i < tk.size(); ++i)
        {               
            sBuffInfo.vecBuffParam.push_back(atoi(tk[i].c_str()));
        }               
        rData.vecDBBuffInfo.push_back(sBuffInfo);
    }
}

void CDBBuffTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelBuff.begin();deliter != _vecDelBuff.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblbuffdata WHERE "\
            "qwOwnerID = " << (*deliter).qwOwnerID << " and "\
            "byBuffType = " << static_cast<UINT32>((*deliter).byBuffType) << " and "\
            "wBuffID = " << (*deliter).wBuffID << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelBuff.clear();

    for (auto iter = _mapBuffData.begin();iter != _mapBuffData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[fun,this](INT8 byRet) {
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            if (this->_nNowQuery == 0)
            {
                fun(_nMaxQuery,this->_nErrQuery);
                }
            });
        }
    }   

}

UINT32 CDBBuffTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapBuffData.begin();iter != _mapBuffData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelBuff.size();

}

void CDBBuffTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SDBBuffInfo sBuffInfo;
    ar >> sBuffInfo;

    SBuffKey sBuffKey = SBuffKey(sBuffInfo.qwOwnerID, static_cast<UINT8>(sBuffInfo.eBuffType), sBuffInfo.wBuffID);

    auto iter = _mapBuffData.find(sBuffKey);
    if (iter != _mapBuffData.end())
    {
        if (iter->second.IsInDB())
            _vecDelBuff.push_back(sBuffKey);
        _mapBuffData.erase(iter);
    }
}

