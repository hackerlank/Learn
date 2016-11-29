#include "DBRoleEquipTrumpTable.h"
#include "Tokenizer.h"

bool GetVecTVecEquipTrumpFromString(TVecShuffleInfo& vecShuffleInfo, const string strEquipTrump)
{
    Tokenizer tk(strEquipTrump, "|"); // XXX: 20,5000|40,3000|60,1500|80,500
    for (size_t i = 0; i < tk.size(); ++i)
    {
            Tokenizer yatk(tk[i], ",");

            if(yatk.size()< 2)
                continue;
            UINT32 dwAttrID = atoi(yatk[0].c_str());
            UINT32 dwValue = atoi(yatk[1].c_str());
            SShuffleInfo oShuffleInfo;
            oShuffleInfo.dwType = dwAttrID;
            oShuffleInfo.dwValue = dwValue;
            vecShuffleInfo.push_back(oShuffleInfo);
     }

    return true;
}

string PackVecTVecEquipTrump(TVecShuffleInfo& vecShuffleInfo)
{
    ostringstream os;
    for(size_t i = 0; i < vecShuffleInfo.size(); i++)
    {
        SShuffleInfo& rSShuffleInfo = vecShuffleInfo[i];
        os<<rSShuffleInfo.dwType<<",";
        os<<rSShuffleInfo.dwValue;
        if(i != vecShuffleInfo.size()-1)
        {
            os<<"|";
        }
    }

    return os.str();
}
DBRoleEquipTrumpTable::DBRoleEquipTrumpTable(UINT64 qwRoleID):
    _qwRoleID(qwRoleID)
{
}

void DBRoleEquipTrumpTable::InitDataByBase(const SEquipTrump& rInfo)
{
    static_cast<SEquipTrump&>(*this) = rInfo;

    strRandomAttr = PackVecTVecEquipTrump(this->vecShuffleInfo);
    strReplaceAttr     = PackVecTVecEquipTrump(this->vecNowReplace);


}

void DBRoleEquipTrumpTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SEquipTrump)
    {
        LOG_CRI << "Type Error: " << weakPtr.ptr->GetClassType() << ".";
        return ;
    }

    SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(weakPtr.ptr);
    if(NULL == pEquipTrump)
        return ;

    static_cast<SEquipTrump&>(*this) = *pEquipTrump;

    strRandomAttr = PackVecTVecEquipTrump(this->vecShuffleInfo);
    strReplaceAttr     = PackVecTVecEquipTrump(this->vecNowReplace);


}

bool DBRoleEquipTrumpTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_SEquipTrump)
    {
        LOG_CRI << "Type Error: " << weakPtr.ptr->GetClassType() << ".";
        return false;
    }

    SEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<SEquipTrump>(weakPtr.ptr);
    if(!pEquipTrump)
        return false;

    SEquipTrump& newData = *pEquipTrump;

    DIFF(qwOwnerID);
    DIFF(byIntensifyLvl);
    DIFF(byIntensifyLvlMax);
    DIFF(dwBlessing);

    string strShuffleInfo = PackVecTVecEquipTrump(newData.vecShuffleInfo);
    string strReplace     = PackVecTVecEquipTrump(newData.vecNowReplace);

    DIFFONLY2(strRandomAttr, strShuffleInfo, strRandomAttr);
    DIFFONLY2(strReplaceAttr, strReplace, strReplaceAttr);

    DIFF(dwXiLianBlessing);

    vecShuffleInfo = newData.vecShuffleInfo;
    vecNowReplace  = newData.vecNowReplace;

    return  !_setChanged.none();
}

bool DBRoleEquipTrumpTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleequiptrumpdata (qwInstID, qwRoleID, qwOwnerID, byIntensifyLvl, byIntensifyLvlMax,dwBlessing,dwXiLianBlessing,strRandomAttr,strReplaceAttr) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)sItemInfo.qwInstID;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwOwnerID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byIntensifyLvl;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byIntensifyLvlMax;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwBlessing;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwXiLianBlessing;
    ostr << "," <<"\'" <<strRandomAttr<<"\'";
    ostr << "," <<"\'" <<strReplaceAttr<<"\'";
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleEquipTrumpTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleequiptrumpdata SET";

    UPDATE_UBIGINT_SAME(qwOwnerID);
    UPDATE_UTINYINT_SAME(byIntensifyLvl);
    UPDATE_UTINYINT_SAME(byIntensifyLvlMax);
    UPDATE_UINT_SAME(dwBlessing);
    UPDATE_UINT_SAME(dwXiLianBlessing);
    UPDATE_STRING_CHAR(strRandomAttr,strRandomAttr);
    UPDATE_STRING_CHAR(strReplaceAttr,strReplaceAttr);

    ostr << " WHERE qwInstID =" << sItemInfo.qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleEquipTrumpTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleEquipTrumpTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwInstID, sItemInfo.qwInstID);
    GET_UBIGINT_SAME(qwOwnerID);
    GET_UTINYINT_SAME(byIntensifyLvl);
    GET_UTINYINT_SAME(byIntensifyLvlMax);
    GET_UINT_SAME(dwBlessing);
    GET_UINT_SAME(dwXiLianBlessing);
    GET_STRING_CHAR_SAME(strRandomAttr);
    GET_STRING_CHAR_SAME(strReplaceAttr);

    GetVecTVecEquipTrumpFromString(vecShuffleInfo,strRandomAttr);
    GetVecTVecEquipTrumpFromString(vecNowReplace,strReplaceAttr);

    TableRowBase::InitDataByDBRow(rRow);
}

DBRoleEquipTrumpTableManager::DBRoleEquipTrumpTableManager(UINT64 qwRoleID, UINT8 byLine) : 
    TableManagerBaseForRole(eTypeEquipTrumpInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) 
{
}

void DBRoleEquipTrumpTableManager::QueryDataByRoleId(UINT64 qwRoleID, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleequiptrumpdata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, 
            [this, qwRoleID, queryfun, basesql, qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
                LOG_INF<<"--------Load tblroleequiptrumpdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                if(byRet == 0)
                {
                    for(auto& rRow : dataRes)
                    {
                        DBRoleEquipTrumpTable sTable(qwRoleID);
                        sTable.InitDataByDBRow(rRow);
                        auto it = _mapRoleEquipTrumpData.find(sTable.sItemInfo.qwInstID);
                        if (it != _mapRoleEquipTrumpData.end())
                        {
                            LOG_CRI << "_mapRoleEquipTrumpData conflict: " << sTable.sItemInfo.qwInstID << ".";
                            continue;
                        }
                        _mapRoleEquipTrumpData.insert(make_pair(sTable.sItemInfo.qwInstID, sTable));
                    }
                }
                queryfun(byRet, dataRes.size());
            });
}

void DBRoleEquipTrumpTableManager::Update(string& strData, bool bIsAdd)
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
        DBRoleEquipTrumpTable EquipTrumpNew(_qwRoleID);
        EquipTrumpNew.Update(strData, true);
        _mapRoleEquipTrumpData.insert(make_pair(pEquipTrump->sItemInfo.qwInstID, EquipTrumpNew));
    }
    else if(iter != _mapRoleEquipTrumpData.end())
        iter->second.Update(strData, false);
}

void DBRoleEquipTrumpTableManager::GetALLInfo(RoleDataInfo & rData)
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
                SEquipTrump& rTmp = iter->second;

                pEquipTrump->qwOwnerID = rTmp.qwOwnerID;
                pEquipTrump->byIntensifyLvl = rTmp.byIntensifyLvl;
                pEquipTrump->byIntensifyLvlMax = rTmp.byIntensifyLvlMax;
                pEquipTrump->dwBlessing = rTmp.dwBlessing;
                pEquipTrump->dwXiLianBlessing = rTmp.dwXiLianBlessing;
                pEquipTrump->vecShuffleInfo = rTmp.vecShuffleInfo;
                pEquipTrump->vecNowReplace = rTmp.vecNowReplace;
                setUseEquipTrump.insert(pEquipTrump->sItemInfo.qwInstID);
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

void DBRoleEquipTrumpTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto & rID : _vecDelEquipTrump)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "DELETE FROM tblroleequiptrumpdata WHERE qwInstID = " << rID << ";";
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

UINT32 DBRoleEquipTrumpTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto & rPair : _mapRoleEquipTrumpData)
    {
        if (rPair.second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelEquipTrump.size();

}

void DBRoleEquipTrumpTableManager::DelData(string& strData)
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

