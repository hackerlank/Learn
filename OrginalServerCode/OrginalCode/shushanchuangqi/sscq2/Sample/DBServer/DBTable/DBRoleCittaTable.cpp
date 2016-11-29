#include "DBRoleCittaTable.h"

DBRoleCittaTable::DBRoleCittaTable():
    _qwInstID(0), _qwRoleID(0), _qwOwnerID(0),
    _byAttrType1(0), _dwAttrValue1(0),
    _byAttrType2(0), _dwAttrValue2(0), 
    _byAttrType3(0), _dwAttrValue3(0), 
    _byAttrType4(0), _dwAttrValue4(0),
    _dwSkillID(0), _dwSignetID(0)
{
}

void DBRoleCittaTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SCitta)
        return ;

    SCittaPtr pCitta = dynamic_pointer_cast<SCitta>(weakPtr.ptr);
    if(!InitDataByCitta(pCitta))
        return ;
}

bool DBRoleCittaTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SCitta)
        return false;
    SCittaPtr pCitta = dynamic_pointer_cast<SCitta>(weakPtr.ptr);
    if(NULL == pCitta)
        return false;

    const NProtoCommon::TVecFtAttrMod& rAttrVec = pCitta->oAttrVec;
    switch(rAttrVec.size())
    {
        case 4:
            DIFFONLY2(byAttrType4, rAttrVec[3]._eAttr, _byAttrType4);
            DIFFONLY2(dwAttrValue4, static_cast<UINT32>(rAttrVec[3]._fValue), _dwAttrValue4);
        case 3:
            DIFFONLY2(byAttrType3, rAttrVec[2]._eAttr, _byAttrType3);
            DIFFONLY2(dwAttrValue3, static_cast<UINT32>(rAttrVec[2]._fValue), _dwAttrValue3);
        case 2:
            DIFFONLY2(byAttrType2, rAttrVec[1]._eAttr, _byAttrType2);
            DIFFONLY2(dwAttrValue2, static_cast<UINT32>(rAttrVec[1]._fValue), _dwAttrValue2);
        case 1:
            DIFFONLY2(byAttrType1, rAttrVec[0]._eAttr, _byAttrType1);
            DIFFONLY2(dwAttrValue1, static_cast<UINT32>(rAttrVec[0]._fValue), _dwAttrValue1);
            break;
        default:
            break;
    }
    DIFFONLY2(dwSkillID, _dwSkillID, pCitta->dwSkillID);
    DIFFONLY2(dwSignetID, _dwSkillID, pCitta->dwSignetID);
    return  !_setChanged.none();
}

bool DBRoleCittaTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolecittadata(qwInstID,qwRoleID,qwOwnerID,"\
        "byAttrType1, dwAttrValue1, byAttrType2, dwAttrValue2, byAttrType3, dwAttrValue3, byAttrType4, dwAttrValue4,"\
        "dwSkillID, dwSignetID) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwInstID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwOwnerID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byAttrType1;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwAttrValue1;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byAttrType2;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwAttrValue2;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byAttrType3;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwAttrValue3;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byAttrType4;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwAttrValue4;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwSkillID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwSignetID;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleCittaTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolecittadata SET";

    UPDATE_UBIGINT(qwOwnerID, _qwOwnerID);
    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UTINYINT(byAttrType1, _byAttrType1);
    UPDATE_UINT(dwAttrValue1, _dwAttrValue1);
    UPDATE_UTINYINT(byAttrType2, _byAttrType2);
    UPDATE_UINT(dwAttrValue2, _dwAttrValue2);
    UPDATE_UTINYINT(byAttrType3, _byAttrType3);
    UPDATE_UINT(dwAttrValue3, _dwAttrValue3);
    UPDATE_UTINYINT(byAttrType4, _byAttrType4);
    UPDATE_UINT(dwAttrValue4, _dwAttrValue4);
    UPDATE_UINT(dwSkillID, _dwSkillID);
    UPDATE_UINT(dwSignetID, _dwSignetID);

    ostr << " WHERE qwInstID =" << _qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleCittaTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleCittaTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwInstID, _qwInstID);
    GET_UBIGINT(qwOwnerID, _qwOwnerID);
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UTINYINT(byAttrType1, _byAttrType1);
    GET_UINT(dwAttrValue1, _dwAttrValue1);
    GET_UTINYINT(byAttrType2, _byAttrType2);
    GET_UINT(dwAttrValue2, _dwAttrValue2);
    GET_UTINYINT(byAttrType3, _byAttrType3);
    GET_UINT(dwAttrValue3, _dwAttrValue3);
    GET_UTINYINT(byAttrType4, _byAttrType4);
    GET_UINT(dwAttrValue4, _dwAttrValue4);
    GET_UINT(dwSkillID, _dwSkillID);
    GET_UINT(dwSignetID, _dwSignetID);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  DBRoleCittaTable::GetInstID() const
{
    return _qwInstID;
}

UINT64  DBRoleCittaTable::GetRoleID() const
{
    return _qwRoleID;
}

bool DBRoleCittaTable::InitDataByCitta(SCittaPtr pCitta)
{
    if (!pCitta)
        return false;
    const NProtoCommon::TVecFtAttrMod& rAttrVec = pCitta->oAttrVec;
    _qwInstID = (pCitta->sItemInfo).qwInstID;
    _qwOwnerID = pCitta->qwOwnerID;
    _qwRoleID = _qwOwnerID;
    switch(rAttrVec.size())
    {
        case 4:
            _byAttrType4 = rAttrVec[3]._eAttr;
            _dwAttrValue4 = static_cast<UINT32>(rAttrVec[3]._fValue);
        case 3:
            _byAttrType3 = rAttrVec[2]._eAttr;
            _dwAttrValue3 = static_cast<UINT32>(rAttrVec[2]._fValue);
        case 2:
            _byAttrType2 = rAttrVec[1]._eAttr;
            _dwAttrValue2 = static_cast<UINT32>(rAttrVec[1]._fValue);
        case 1:
            _byAttrType1 = rAttrVec[0]._eAttr;
            _dwAttrValue1 = static_cast<UINT32>(rAttrVec[0]._fValue);
            break;
        default:
            break;
    }
    _dwSkillID = pCitta->dwSkillID;
    _dwSignetID = pCitta->dwSignetID;
    return true;
}

void DBRoleCittaTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolecittadata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblbuffdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i < ncount; ++i)
            {
                mysqlpp::Row& rRow = dataRes[i];
                DBRoleCittaTable CittaTable;
                CittaTable.InitDataByDBRow(rRow);
                _mapRoleCittaData[CittaTable.GetInstID()]= CittaTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void DBRoleCittaTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SCitta)
        return ;

    SCittaPtr pCitta = dynamic_pointer_cast<SCitta>(weakPtr.ptr);
    if(pCitta == NULL)
        return ;

    map<UINT64, DBRoleCittaTable>::iterator iter = _mapRoleCittaData.find(pCitta->sItemInfo.qwInstID);
    if (iter == _mapRoleCittaData.end())
    {
        DBRoleCittaTable CittaNew;
        CittaNew.Update(strData, bIsAdd);
        _mapRoleCittaData[pCitta->sItemInfo.qwInstID] = CittaNew;
    }
    else
        iter->second.Update(strData, bIsAdd);
}

void DBRoleCittaTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,DBRoleCittaTable>::iterator iter;
    set<UINT64> setUseCitta;
    for (auto it = rData.vecRoleItemInfo.begin();it != rData.vecRoleItemInfo.end();it++)
    {
        if ((*it)->GetClassType() == eType_SCitta)
        {
            SCittaPtr pCitta = dynamic_pointer_cast<SCitta>(*it);
            if(NULL == pCitta)
                continue;
            iter = _mapRoleCittaData.find(pCitta->sItemInfo.qwInstID);
            if(iter != _mapRoleCittaData.end())
            {
                const DBRoleCittaTable& rCittaData = iter->second;
                pCitta->qwOwnerID = rCittaData._qwOwnerID;
                pCitta->oAttrVec.resize(4);
                pCitta->oAttrVec[0]._eAttr = (NProtoCommon::EFighterAttr)(rCittaData._byAttrType1);
                pCitta->oAttrVec[1]._eAttr = (NProtoCommon::EFighterAttr)(rCittaData._byAttrType2);
                pCitta->oAttrVec[2]._eAttr = (NProtoCommon::EFighterAttr)(rCittaData._byAttrType3);
                pCitta->oAttrVec[3]._eAttr = (NProtoCommon::EFighterAttr)(rCittaData._byAttrType4);
                pCitta->oAttrVec[0]._fValue = rCittaData._dwAttrValue1;
                pCitta->oAttrVec[1]._fValue = rCittaData._dwAttrValue2;
                pCitta->oAttrVec[2]._fValue = rCittaData._dwAttrValue3;
                pCitta->oAttrVec[3]._fValue = rCittaData._dwAttrValue4;
                pCitta->dwSkillID = rCittaData._dwSkillID;
                pCitta->dwSignetID = rCittaData._dwSignetID;
                setUseCitta.insert(rCittaData.GetInstID());
            }
        }
    }

    if (setUseCitta.size() != _mapRoleCittaData.size())
        LOG_CRI << "数据不一致，清除多余数据";
    else
        return ;

    for (iter = _mapRoleCittaData.begin();iter != _mapRoleCittaData.end();iter++)
    {
        if(setUseCitta.find(iter->first) == setUseCitta.end())
        {
            if (iter->second.IsInDB())
                _vecDelCitta.push_back(iter->first);
        }
    }
}

void DBRoleCittaTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelCitta.begin();deliter != _vecDelCitta.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolecittadata WHERE qwInstID = " << *deliter << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelCitta.clear();
    for (auto iter = _mapRoleCittaData.begin();iter != _mapRoleCittaData.end();iter++)
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

UINT32 DBRoleCittaTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleCittaData.begin();iter != _mapRoleCittaData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelCitta.size();

}

void DBRoleCittaTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SCitta)
        return ;

    SCittaPtr pCitta = dynamic_pointer_cast<SCitta>(weakPtr.ptr);
    if(pCitta == NULL)
    {
        return ;
    }
    auto iter = _mapRoleCittaData.find(pCitta->sItemInfo.qwInstID);
    if (iter != _mapRoleCittaData.end())
    {
        if (iter->second.IsInDB())
            _vecDelCitta.push_back(pCitta->sItemInfo.qwInstID);
        _mapRoleCittaData.erase(iter);
    }
}

