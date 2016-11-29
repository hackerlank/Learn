// =====================================================================================
//
//       Filename:  DBRoleEquipTrumpShuffleTable.h
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

#ifndef DB_ROLE_EQUIP_TRUMP_SHUFFLE_TABLE_H
#define DB_ROLE_EQUIP_TRUMP_SHUFFLE_TABLE_H

#include "DBTableBase.h"

class DBRoleEquipTrumpShuffleTable : public TableRowBase, public SShuffleInfo, public CPoolObj<DBRoleEquipTrumpShuffleTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwInstID),
            UPCOL(dwType),
            UPCOL(dwValue),
            UPCOL(Max)
        };

    public:
        DBRoleEquipTrumpShuffleTable(UINT64 qwInstID);
        void InitDataByBase(UINT64 qwInstIDFromParam, const SShuffleInfo& rInfo);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64 _qwInstID;

    private:
        bitset<UPCOL(Max)> _setChanged;

};

class DBRoleEquipTrumpShuffleTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleEquipTrumpShuffleTableManager>
{ 
    public:
        DBRoleEquipTrumpShuffleTableManager(UINT64 qwRoleID,UINT8 byLine);

        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,DBRoleEquipTrumpShuffleTable> _mapRoleEquipTrumpData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelEquipTrump;
};

#endif // #ifndef DB_ROLE_EQUIP_TRUMP_SHUFFLE_TABLE_H

