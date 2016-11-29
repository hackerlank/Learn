
#include "DBRoleGemstone.h"
void CDBRoleGemstoneTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SGemstone)
    {
        return ;
    }
    SGemstonePtr pGemstone = dynamic_pointer_cast<SGemstone>(weakPtr.ptr);
    InitDataByGemstone(pGemstone);
}

bool CDBRoleGemstoneTable::InitDataByGemstone(SGemstonePtr pGemstone)
{
    if(NULL == pGemstone)
    {
        return false;
    }
    qwInstID = pGemstone->sItemInfo.qwInstID;
    qwOwnerID = pGemstone->qwOwnerID;
    return true;
}

bool CDBRoleGemstoneTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SGemstone)
    {
        return false;
    }
    SGemstonePtr pGemstone = dynamic_pointer_cast<SGemstone>(weakPtr.ptr);
    if(NULL == pGemstone)
    {
        return false;
    }
    SGemstone& newData = *pGemstone;

    DIFF(qwOwnerID);

    return  !_setChanged.none();
}

bool CDBRoleGemstoneTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolegemstone(qwInstID,qwRoleID,qwOwnerID) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwInstID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwOwnerID;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleGemstoneTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolegemstone SET";

    UPDATE_UBIGINT_SAME(qwOwnerID);

    ostr << " WHERE qwInstID =" << qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleGemstoneTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleGemstoneTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwInstID);
    //GET_UBIGINT_SAME(_qwRoleID);
    GET_UBIGINT_SAME(qwOwnerID);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleGemstoneTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolegemstone WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
         LOG_INF<<"--------Load tblrolegemstone is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i < ncount; ++i)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleGemstoneTable GemstoneTable(qwRoleID);
                GemstoneTable.InitDataByDBRow(rRow);
                _mapRoleGemstoneData[GemstoneTable.qwInstID]= GemstoneTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleGemstoneTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SGemstone)
    {
        return ;
    }
    SGemstonePtr pGemstone = dynamic_pointer_cast<SGemstone>(weakPtr.ptr);
    if(pGemstone == NULL)
    {
        return ;
    }
    map<UINT64, CDBRoleGemstoneTable>::iterator iter = _mapRoleGemstoneData.find(pGemstone->sItemInfo.qwInstID);
    if (iter == _mapRoleGemstoneData.end() && bIsAdd)
    {
        CDBRoleGemstoneTable GemstoneNew(_qwRoleID);
        GemstoneNew.Update(strData, bIsAdd);
        _mapRoleGemstoneData[pGemstone->sItemInfo.qwInstID] = GemstoneNew;
    }
    else if(iter != _mapRoleGemstoneData.end() && !bIsAdd)
    {
        iter->second.Update(strData, bIsAdd);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleGemstoneTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBRoleGemstoneTable>::iterator iter;
    set<UINT64> setUseGemstone;
    for (auto it = rData.vecRoleItemInfo.begin();it != rData.vecRoleItemInfo.end();it++)
    {
        if ((*it)->GetClassType() == eType_SGemstone)
        {
            SGemstonePtr pGemstone = dynamic_pointer_cast<SGemstone>(*it);
            if(NULL == pGemstone)
            {
                continue;
            }
            iter = _mapRoleGemstoneData.find(pGemstone->sItemInfo.qwInstID);
            if(iter != _mapRoleGemstoneData.end())
            {
                pGemstone->qwOwnerID = iter->second.qwOwnerID;
                setUseGemstone.insert(pGemstone->sItemInfo.qwInstID);
            }
        }
    }

    if (setUseGemstone.size() != _mapRoleGemstoneData.size())
    {
        LOG_CRI << "数据不一致，清除多余数据";
    }
    else
    {
        return ;
    }

    for (iter = _mapRoleGemstoneData.begin();iter != _mapRoleGemstoneData.end();iter++)
    {
        if(setUseGemstone.find(iter->first) == setUseGemstone.end())
        {
            if (iter->second.IsInDB())
            {
                _vecDelGemstone.push_back(iter->first);
            }
        }
    }
}

void CDBRoleGemstoneTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelGemstone.begin();deliter != _vecDelGemstone.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolegemstone WHERE qwInstID = " << *deliter << ";";
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
    _vecDelGemstone.clear();

    for (auto iter = _mapRoleGemstoneData.begin();iter != _mapRoleGemstoneData.end();iter++)
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

UINT32 CDBRoleGemstoneTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleGemstoneData.begin();iter != _mapRoleGemstoneData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelGemstone.size();

}

void CDBRoleGemstoneTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SGemstone)
    {
        return ;
    }
    SGemstonePtr pGemstone = dynamic_pointer_cast<SGemstone>(weakPtr.ptr);
    if(pGemstone == NULL)
    {
        return ;
    }
    auto iter = _mapRoleGemstoneData.find(pGemstone->sItemInfo.qwInstID);
    if (iter != _mapRoleGemstoneData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelGemstone.push_back(pGemstone->sItemInfo.qwInstID);
        }
        _mapRoleGemstoneData.erase(iter);
    }
}

