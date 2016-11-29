// =====================================================================================
//
//       Filename:  DBRoleEquipTrumpShuffleTable.cpp
//
//    Description:  装备法宝洗炼
//
//        Version:  1.0
//        Created:  05/15/2015 02:33:08 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "DBRoleEquipTrumpShuffleTable.h"


DBRoleEquipTrumpShuffleTable::DBRoleEquipTrumpShuffleTable(UINT64 qwInstID):
    _qwInstID(qwInstID)
{
}

void DBRoleEquipTrumpShuffleTable::InitDataByBase(UINT64 qwInstID, const SShuffleInfo& rInfo)
{
    SShuffleInfo tmp;
    memcpy(&tmp, &rInfo, sizeof(rInfo));
    static_cast<SShuffleInfo&>(*this) = tmp;
    _qwInstID = qwInstID;
}

void DBRoleEquipTrumpShuffleTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_STrump)
        return ;

    SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(weakPtr.ptr);
    if(NULL == pEquipTrump)
        return ;

    //SShuffleInfo tmp;
    //memcpy(&tmp, &pEquipTrump->sEquipTrumpInfo, sizeof(pEquipTrump->sEquipTrumpInfo));

    //static_cast<SShuffleInfo&>(*this) = tmp;
    _qwInstID = pEquipTrump->sItemInfo.qwInstID;
}

bool DBRoleEquipTrumpShuffleTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SEquipTrump)
        return false;
    SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(weakPtr.ptr);
    if(!pEquipTrump)
        return false;
    //SShuffleInfo& newData = pEquipTrump->sEquipTrumpInfo;
    //newData._qwInstID = pEquipTrump->sItemInfo.qwInstID;

    /*
    DIFF2(qwOwnerID, sEquipTrumpInfo.qwOwnerID);
    DIFF2(byEnable, sEquipTrumpInfo.byEnable);
    DIFF2(byIntensifyLvl, sEquipTrumpInfo.byIntensifyLvl);
    DIFF2(byIntensifyLvlMax, sEquipTrumpInfo.byIntensifyLvlMax);
    DIFF2(dwSP1, sEquipTrumpInfo.dwSP1);
    DIFF2(dwSP2, sEquipTrumpInfo.dwSP2);
    DIFF2(dwSP3, sEquipTrumpInfo.dwSP3);
    */

    //DIFF(wEquipTrumpType);
    return  !_setChanged.none();
}

bool DBRoleEquipTrumpShuffleTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleequiptrumpshuffledata ( qwRoleID, qwOwnerID, byEnable, byIntensifyLvl, byIntensifyLvlMax, dwSP1, dwSP2, dwSP3) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwInstID;
    /*
    ostr << "," << (mysqlpp::sql_bigint_unsigned)sEquipTrumpInfo.qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)sEquipTrumpInfo.dwSP1;
    ostr << "," <<(mysqlpp::sql_int_unsigned)sEquipTrumpInfo.dwSP2;
    ostr << "," <<(mysqlpp::sql_int_unsigned)sEquipTrumpInfo.dwSP3;
    */
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleEquipTrumpShuffleTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleequiptrumpshuffledata SET";

    UPDATE_UINT_SAME(dwType);
    UPDATE_UINT_SAME(dwValue);

    ostr << " WHERE qwInstID =" << _qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleEquipTrumpShuffleTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleEquipTrumpShuffleTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwInstID, _qwInstID);
    //GET_UBIGINT(qwOwnerID, sEquipTrumpInfo.qwOwnerID);
    TableRowBase::InitDataByDBRow(rRow);
}

DBRoleEquipTrumpShuffleTableManager::DBRoleEquipTrumpShuffleTableManager(UINT64 qwRoleID, UINT8 byLine) : 
    TableManagerBaseForRole(eTypeEquipTrumpShuffleInfo, qwRoleID, byLine), 
    _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) 
{
}

void DBRoleEquipTrumpShuffleTableManager::QueryDataByRoleId(UINT64 qwRoleID, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleequiptrumpshuffledata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, 
            [this, qwRoleID, queryfun, basesql, qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
                LOG_INF<<"--------Load tblroleequiptrumpshuffledata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                if(byRet == 0)
                {
                    for(auto& rRow : dataRes)
                    {
                        DBRoleEquipTrumpShuffleTable sTable(qwRoleID);
                        sTable.InitDataByDBRow(rRow);
                        auto it = _mapRoleEquipTrumpData.find(sTable._qwInstID);
                        if (it == _mapRoleEquipTrumpData.end())
                            _mapRoleEquipTrumpData.insert(make_pair(sTable._qwInstID, sTable));
                        else
                            it->second = sTable;
                    }
                }
                queryfun(byRet, dataRes.size());
            });
}

void DBRoleEquipTrumpShuffleTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SEquipTrump)
        return ;
    SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(weakPtr.ptr);
    if(pEquipTrump == NULL)
        return ;
    auto iter = _mapRoleEquipTrumpData.find(pEquipTrump->sItemInfo.qwInstID);
    if (iter == _mapRoleEquipTrumpData.end())
    {
        DBRoleEquipTrumpShuffleTable sTable(pEquipTrump->sItemInfo.qwInstID);
        sTable.InitDataByStr(strData);
        auto it = _mapRoleEquipTrumpData.find(pEquipTrump->sItemInfo.qwInstID);
        if (it == _mapRoleEquipTrumpData.end())
            _mapRoleEquipTrumpData.insert(make_pair(pEquipTrump->sItemInfo.qwInstID, sTable));
        else
            it->second = sTable;
    }
    else if(iter != _mapRoleEquipTrumpData.end() && !bIsAdd)
        iter->second.Update(strData, false);
}

void DBRoleEquipTrumpShuffleTableManager::GetALLInfo(RoleDataInfo & rData)
{
    TSetUINT64 setUseEquipTrump;
    for (auto & pInfo : rData.vecRoleItemInfo)
    {
        if (pInfo->GetClassType() == eType_SEquipTrump)
        {
            SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(pInfo);
            if(NULL == pEquipTrump)
                continue;
            auto iter = _mapRoleEquipTrumpData.find(pEquipTrump->sItemInfo.qwInstID);
            if(iter != _mapRoleEquipTrumpData.end())
            {
                /*
                RoleEquipTrumpInfo tmp = iter->second;
                memcpy(&pEquipTrump->sEquipTrumpInfo, &tmp, sizeof(pEquipTrump->sEquipTrumpInfo));
                setUseEquipTrump.insert(pEquipTrump->sItemInfo.qwInstID);
                */
            }
        }
    }

    if (setUseEquipTrump.size() != _mapRoleEquipTrumpData.size())
        LOG_CRI << "数据不一致，清除多余数据";
    else
        return ;

    for (auto & rPair : _mapRoleEquipTrumpData)
    {
        if(setUseEquipTrump.find(rPair.first) == setUseEquipTrump.end())
        {
            if (rPair.second.IsInDB())
                _vecDelEquipTrump.push_back(rPair.first);
        }
    }
}

void DBRoleEquipTrumpShuffleTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto & rID : _vecDelEquipTrump)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblroleequiptrumpshuffledata WHERE qwInstID = " << rID << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, 
                [this, fun, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes)
                {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                    this->_nNowQuery--;
                    if (byRet)
                        this->_nErrQuery++;
                    if (this->_nNowQuery == 0)
                        fun(this->_nMaxQuery, this->_nErrQuery);
                });
    }
    _vecDelEquipTrump.clear();
    for (auto & rPair : _mapRoleEquipTrumpData)
    {
        if (rPair.second.HasOP())
        {
            rPair.second.DumpToDB(_byLine,
                    [fun, this](INT8 byRet)
                    {
                        this->_nNowQuery--;
                        if (byRet)
                            this->_nErrQuery++;
                        if (this->_nNowQuery == 0)
                            fun(_nMaxQuery, this->_nErrQuery);
                    });
        }
    }   
}

UINT32 DBRoleEquipTrumpShuffleTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto & rPair : _mapRoleEquipTrumpData)
    {
        if (rPair.second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelEquipTrump.size();

}

void DBRoleEquipTrumpShuffleTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SEquipTrump)
        return ;
    SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(weakPtr.ptr);
    if(pEquipTrump == NULL)
        return ;
    auto iter = _mapRoleEquipTrumpData.find(pEquipTrump->sItemInfo.qwInstID);
    if (iter != _mapRoleEquipTrumpData.end())
    {
        if (iter->second.IsInDB())
            _vecDelEquipTrump.push_back(pEquipTrump->sItemInfo.qwInstID);
        _mapRoleEquipTrumpData.erase(iter);
    }
}

