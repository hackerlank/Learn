#ifndef DB_SLOTS_TABLE_H
#define DB_SLOTS_TABLE_H

#pragma once

#include "DBTableBase.h"

struct SlotsDataKey
{
    SlotsDataKey(UINT64 qwRoleID, UINT64 qwOwnerID, UINT8 byType)
        : qwRoleID(qwRoleID), qwOwnerID(qwOwnerID), byType(byType) {}

    UINT64 qwRoleID;
    UINT64 qwOwnerID;
    UINT8 byType;

    bool operator < (const SlotsDataKey& sk) const
    {
        if (qwRoleID < sk.qwRoleID)
        {
           return true;
        }
        else if (qwRoleID > sk.qwRoleID)
        {
            return false;
        }

        if(qwOwnerID < sk.qwOwnerID)
        {
             return true;
        }
        else if(qwOwnerID > sk.qwOwnerID)
        {
          return false;
        }
        return byType < sk.byType;
    }
};

class DBSlotsTable : public TableRowBase, public CPoolObj<DBSlotsTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(qwOwnerID),
            UPCOL(byStoreType),
            UPCOL(wMaxSlot),
            UPCOL(wMaxAvaliableSlot),
            UPCOL(Max)
        };

    public:
        DBSlotsTable();
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64 GetRoleID() const { return qwRoleID; }
        UINT64 GetOwnerID() const { return qwOwnerID; }
        UINT8 GetStoreType() const { return byStoreType; }
        UINT16 GetMaxSlot() const { return wMaxSlot; }
        UINT16 GetMaxAvaliableSlot() const { return wMaxAvaliableSlot; }

    private:
        bool InitDataBySlots(const SRoleSlotsInfo& rRoleSlotsInfo);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 qwRoleID;
        UINT64 qwOwnerID;
        UINT8  byStoreType;
        UINT16 wMaxSlot;
        UINT16 wMaxAvaliableSlot;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class DBSlotsTableManager : public TableManagerBaseForRole, public CPoolObj<DBSlotsTableManager>
{ 
    public:
        DBSlotsTableManager(UINT64 setqwRoleID,UINT8 byLine) 
            : TableManagerBaseForRole(eTypeSlotsInfo,setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) 
        {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SlotsDataKey,DBSlotsTable> _mapSlotsData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SlotsDataKey> _vecDelSlots;
};

#endif // #define DB_SLOTS_TABLE_H
