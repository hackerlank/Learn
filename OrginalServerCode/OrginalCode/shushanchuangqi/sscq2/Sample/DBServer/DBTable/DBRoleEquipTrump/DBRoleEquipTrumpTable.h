#ifndef  DB_ROLE_EQUIP_TRUMP_TABLE_H
#define  DB_ROLE_EQUIP_TRUMP_TABLE_H
#include "DBTableBase.h"

class DBRoleEquipTrumpTable : public TableRowBase, public SEquipTrump, public CPoolObj<DBRoleEquipTrumpTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwOwnerID),
            UPCOL(qwRoleID),
            UPCOL(qwInstID),
            UPCOL(byIntensifyLvl),
            UPCOL(byIntensifyLvlMax),
            UPCOL(dwBlessing),
            UPCOL(strRandomAttr),
            UPCOL(strReplaceAttr),
            UPCOL(dwXiLianBlessing),
            UPCOL(Max)
        };

    public:
        DBRoleEquipTrumpTable(UINT64 qwRoleID);
        void InitDataByBase(const SEquipTrump& rInfo);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

    private:
        UINT64  _qwRoleID;
        bitset<UPCOL(Max)> _setChanged;
        std::string strRandomAttr;
        std::string strReplaceAttr;
};

class DBRoleEquipTrumpTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleEquipTrumpTableManager>
{ 
    public:
        DBRoleEquipTrumpTableManager(UINT64 qwRoleID,UINT8 byLine);

        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,DBRoleEquipTrumpTable> _mapRoleEquipTrumpData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelEquipTrump;
};

#endif // #ifndef  DB_ROLE_EQUIP_TRUMP_TABLE_H
