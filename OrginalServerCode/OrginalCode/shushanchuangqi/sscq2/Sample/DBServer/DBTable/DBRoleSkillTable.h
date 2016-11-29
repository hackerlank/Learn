
#ifndef DBROLESKILLTABLE_H_
#define DBROLESKILLTABLE_H_

#include "DBTableBase.h"

class CDBRoleSkillTable : public TableRowBase, public SSkillDBInfo, public CPoolObj<CDBRoleSkillTable>
{
    public:
        enum EUpdateColumn
        {
            //UPCOL(qwOwnerID),
            UPCOL(dwUpSkill1),
            UPCOL(dwUpSkill2),
            UPCOL(dwUpSkill3),
            UPCOL(dwUpSkill4),
            UPCOL(dwUpSkill5),
            UPCOL(dwUpSkill6),
            UPCOL(dwSkill1),
            UPCOL(dwSkill2),
            UPCOL(dwSkill3),
            UPCOL(dwSkill4),
            UPCOL(dwSkill5),
            UPCOL(dwSkill6),
            UPCOL(dwSkill7),
            UPCOL(dwSkill8),
            UPCOL(dwSkill9),
            UPCOL(dwRune1),
            UPCOL(dwRune2),
            UPCOL(dwRune3),
            UPCOL(dwRune4),
            UPCOL(dwRune5),
            UPCOL(dwRune6),
            UPCOL(dwRune7),
            UPCOL(dwRune8),
            UPCOL(dwRune9),
            UPCOL(dwSkillAdv1),
            UPCOL(dwSkillAdv2),
            UPCOL(dwSkillAdv3),
            UPCOL(dwSkillAdv4),
            UPCOL(dwSkillAdv5),
            UPCOL(dwSkillAdv6),
            UPCOL(dwSkillAdv7),
            UPCOL(dwSkillAdv8),
            UPCOL(dwSkillAdv9),
            UPCOL(Max)
        };

    public:
        CDBRoleSkillTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBRoleSkillTable() : _qwRoleID(0){}

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class CDBRoleSkillTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleSkillTableManager>
{ 
    public:
        CDBRoleSkillTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeSkillInfo, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64, CDBRoleSkillTable> _mapSkillData; // OwnerID to SkillTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelSkill;
};

#endif // DBROLESKILLTABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

