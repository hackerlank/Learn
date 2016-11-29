
#include "DBRoleItemTable.h"
#include "ItemType.h"

void CDBRoleItemTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    static_cast<RoleItemInfo&>(*this) = weakPtr.ptr->sItemInfo;
}
void CDBRoleItemTable::InitDataByBase(const RoleItemInfo &rInfo)
{
    static_cast<RoleItemInfo&>(*this) = rInfo;
}

bool CDBRoleItemTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    RoleItemInfo newData = weakPtr.ptr->sItemInfo;

    DIFF(wItemID);
    DIFF(byStoreType);
    DIFF(wIndex);
    DIFF(wCount);
    DIFF(byBind);
    DIFF(byExpired);
    DIFF(dwExpireTime);
    DIFF(dwMark);

    return  !_setChanged.none();
}

bool CDBRoleItemTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleitemdata(qwInstID,qwRoleID,wItemID,byStoreType,wIndex,wCount,byBind,byExpired,dwExpireTime) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwInstID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wItemID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byStoreType;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wIndex;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wCount;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byBind;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byExpired;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwExpireTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleItemTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleitemdata SET";

    UPDATE_USMALLINT_SAME(wItemID);
    UPDATE_UTINYINT_SAME(byStoreType);
    UPDATE_USMALLINT_SAME(wIndex);
    UPDATE_USMALLINT_SAME(wCount);
    UPDATE_UTINYINT_SAME(byBind);
    UPDATE_UTINYINT_SAME(byExpired);
    UPDATE_UINT_SAME(dwExpireTime);
    UPDATE_UINT_SAME(dwMark);

    ostr << " WHERE qwInstID=" << qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleItemTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleItemTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwInstID);
    GET_USMALLINT_SAME(wItemID);
    GET_UTINYINT_SAME(byStoreType);
    GET_USMALLINT_SAME(wIndex);
    GET_USMALLINT_SAME(wCount);
    GET_UTINYINT_SAME(byBind);
    GET_UTINYINT_SAME(byExpired);
    GET_UINT_SAME(dwExpireTime);
    GET_UINT_SAME(dwMark);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleItemTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleitemdata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroleitemdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for(UINT32 i = 0; i< ncount; ++i)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleItemTable ItemTable(qwRoleID);
            ItemTable.InitDataByDBRow(rRow);
            _mapRoleItemData[ItemTable.qwInstID]= ItemTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleItemTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    UINT64 qwInstID = weakPtr.ptr->sItemInfo.qwInstID;
    map<UINT64, CDBRoleItemTable>::iterator iter = _mapRoleItemData.find(qwInstID);
    if (iter == _mapRoleItemData.end() /* && bIsAdd*/)
    {
        CDBRoleItemTable ItemNew(_qwRoleID);
        ItemNew.Update(strData, bIsAdd);
        _mapRoleItemData[qwInstID] = ItemNew;
    }
    else if(iter != _mapRoleItemData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleItemTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBRoleItemTable>::iterator iter;
    for (iter = _mapRoleItemData.begin();iter != _mapRoleItemData.end();iter++)
    {
        SItemPtr ptr;
        if (iter->second.wCount > 1) //可堆叠 // XXX: 当堆叠的数量为1时当SItem处理
        {
            ptr = SItemPtr(new SStack);
        }
        else if (CItemType::GetItemType(iter->second.wItemID) == eItemTrump) // 法宝
        {
            ptr = STrumpPtr(new STrump);
        }
        else if (CItemType::GetItemType(iter->second.wItemID) == eItemCitta) // 心法
        {
            ptr = SCittaPtr(new SCitta);
        }
        else if (CItemType::GetItemType(iter->second.wItemID) == eItemFashion) // 时装
        {
            ptr = SFashionPtr(new SFashion);
        }
        else if(CItemType::GetItemType(iter->second.wItemID) == eItemStone && iter->second.byStoreType == eStoreGemstone)
        {
            ptr = SGemstonePtr(new SGemstone);
        }
        else if (CItemType::GetItemType(iter->second.wItemID) == eItemEquipTrump) // 装备法宝
        {
            ptr = SEquipTrumpPtr(new SEquipTrump);
        }
        else
        {   
            ptr = SItemPtr(new SItem);
        }

        ptr->sItemInfo = iter->second;
        rData.vecRoleItemInfo.push_back(ptr);
    }
}

void CDBRoleItemTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelItem.begin();deliter != _vecDelItem.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleitemdata WHERE qwInstID = "<<*deliter<<";";
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
    _vecDelItem.clear();

    for (auto iter = _mapRoleItemData.begin();iter != _mapRoleItemData.end();iter++)
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

UINT32 CDBRoleItemTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleItemData.begin();iter != _mapRoleItemData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelItem.size();

}

void CDBRoleItemTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    UINT64 qwInstID = weakPtr.ptr->sItemInfo.qwInstID;
    auto iter = _mapRoleItemData.find(qwInstID);
    if (iter != _mapRoleItemData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelItem.push_back(qwInstID);

        }
        _mapRoleItemData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

