
#include "DBRoleFashionTable.h"

void CDBRoleFashionTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SFashion)
    {
        return ;
    }

    SFashionPtr pFashion = dynamic_pointer_cast<SFashion>(weakPtr.ptr);
    InitDataByFashion(pFashion);
}

bool CDBRoleFashionTable::InitDataByFashion(SFashionPtr pFashion)
{
    if(NULL == pFashion)
    {
        return false;
    }

    byLevel = pFashion->byLevel;;
    dwExp = pFashion->dwExp;
    qwInstID = pFashion->sItemInfo.qwInstID;
    bySelected = pFashion->bySelected;
    byHide = pFashion->byHide;
    return true;
}

bool CDBRoleFashionTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SFashion)
    {
        return false;
    }
    SFashionPtr pFashion = dynamic_pointer_cast<SFashion>(weakPtr.ptr);
    if(NULL == pFashion)
    {
        return false;
    }
    SFashion& newData = *pFashion;

    DIFF(byLevel);
    DIFF(dwExp);
    DIFF(bySelected);
    DIFF(byHide);

    return  !_setChanged.none();
}

bool CDBRoleFashionTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolefashion(qwInstID,qwRoleID,byLevel,dwExp,bySelected,byHide) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwInstID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byLevel;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwExp;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)bySelected;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byHide;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleFashionTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolefashion SET";

    UPDATE_UTINYINT_SAME(byLevel);
    UPDATE_UINT_SAME(dwExp);
    UPDATE_UTINYINT_SAME(bySelected);
    UPDATE_UTINYINT_SAME(byHide);

    ostr << " WHERE qwInstID =" << qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleFashionTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleFashionTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwInstID);
    //GET_UBIGINT_SAME(_qwRoleID);
    GET_UTINYINT_SAME(byLevel);
    GET_UINT_SAME(dwExp);
    GET_UTINYINT_SAME(bySelected);
    GET_UTINYINT_SAME(byHide);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleFashionTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolefashion WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
         LOG_INF<<"--------Load tblrolefashion is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i < ncount; ++i)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleFashionTable FashionTable(qwRoleID);
                FashionTable.InitDataByDBRow(rRow);
                _mapRoleFashionData[FashionTable.qwInstID]= FashionTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleFashionTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SFashion)
    {
        return ;
    }
    SFashionPtr pFashion = dynamic_pointer_cast<SFashion>(weakPtr.ptr);
    if(pFashion == NULL)
    {
        return ;
    }
    map<UINT64, CDBRoleFashionTable>::iterator iter = _mapRoleFashionData.find(pFashion->sItemInfo.qwInstID);
    if (iter == _mapRoleFashionData.end() && bIsAdd)
    {
        CDBRoleFashionTable FashionNew(_qwRoleID);
        FashionNew.Update(strData, bIsAdd);
        _mapRoleFashionData[pFashion->sItemInfo.qwInstID] = FashionNew;
    }
    else if(iter != _mapRoleFashionData.end() && !bIsAdd)
    {
        iter->second.Update(strData, bIsAdd);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleFashionTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBRoleFashionTable>::iterator iter;
    set<UINT64> setUseFashion;
    for (auto it = rData.vecRoleItemInfo.begin();it != rData.vecRoleItemInfo.end();it++)
    {
        if ((*it)->GetClassType() == eType_SFashion)
        {
            SFashionPtr pFashion = dynamic_pointer_cast<SFashion>(*it);
            if(NULL == pFashion)
            {
                continue;
            }
            iter = _mapRoleFashionData.find(pFashion->sItemInfo.qwInstID);
            if(iter != _mapRoleFashionData.end())
            {
                pFashion->byLevel = iter->second.byLevel;
                pFashion->dwExp = iter->second.dwExp;
                pFashion->bySelected = iter->second.bySelected;
                pFashion->byHide = iter->second.byHide;
                setUseFashion.insert(pFashion->sItemInfo.qwInstID);
            }
        }
    }

    if (setUseFashion.size() != _mapRoleFashionData.size())
    {
        LOG_CRI << "数据不一致，清除多余数据";
    }
    else
    {
        return ;
    }

    for (iter = _mapRoleFashionData.begin();iter != _mapRoleFashionData.end();iter++)
    {
        if(setUseFashion.find(iter->first) == setUseFashion.end())
        {
            if (iter->second.IsInDB())
            {
                _vecDelFashion.push_back(iter->first);
            }
        }
    }
}

void CDBRoleFashionTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelFashion.begin();deliter != _vecDelFashion.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolefashion WHERE qwInstID = " << *deliter << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            if (this->_nNowQuery == 0)
            {
                fun(this->_nMaxQuery,this->_nErrQuery);
            }
        });
    }
    _vecDelFashion.clear();

    for (auto iter = _mapRoleFashionData.begin();iter != _mapRoleFashionData.end();iter++)
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

UINT32 CDBRoleFashionTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleFashionData.begin();iter != _mapRoleFashionData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelFashion.size();

}

void CDBRoleFashionTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SFashion)
    {
        return ;
    }
    SFashionPtr pFashion = dynamic_pointer_cast<SFashion>(weakPtr.ptr);
    if(pFashion == NULL)
    {
        return ;
    }
    auto iter = _mapRoleFashionData.find(pFashion->sItemInfo.qwInstID);
    if (iter != _mapRoleFashionData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelFashion.push_back(pFashion->sItemInfo.qwInstID);
        }
        _mapRoleFashionData.erase(iter);
    }
}

