// =====================================================================================
//
//       Filename:  DBFighterPassiveSkillTable.h
//
//    Description:  散仙被动技能表
//
//        Version:  1.0
//        Created:  05/12/2015 01:49:33 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef DB_FIGHTERR_PASSIVE_SKILL_TABLE_H
#define DB_FIGHTERR_PASSIVE_SKILL_TABLE_H

#include "DBTableBase.h"

struct SPassiveSkillKey
{
    SPassiveSkillKey(UINT64 qwOwnerID, UINT32 dwSkillID) : 
        qwOwnerID(qwOwnerID), dwSkillID(dwSkillID)
    {
    }

    UINT64  qwOwnerID;
    UINT32  dwSkillID;

    bool operator < (const SPassiveSkillKey& sk) const
    {
        if (qwOwnerID != sk.qwOwnerID)
            return qwOwnerID < sk.qwOwnerID;
        return dwSkillID < sk.dwSkillID;
    }
};

class CDBFighterPassiveSkillTable : public TableRowBase, public SPassiveSkillDBInfo, public CPoolObj<CDBFighterPassiveSkillTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwOwnerID),
            UPCOL(qwRoleID),
            UPCOL(dwSkillID),
            UPCOL(dwSkillQuality),
            UPCOL(dwSkillLevel),
            UPCOL(Max)
        };

    public:
        CDBFighterPassiveSkillTable(){}

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

    private:
        bitset<UPCOL(Max)> _setChanged;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class CDBFighterPassiveSkillTableManager : public TableManagerBaseForRole, public CPoolObj<CDBFighterPassiveSkillTableManager>
{ 
    public:
        CDBFighterPassiveSkillTableManager(UINT64 qwRoleID,UINT8 byLine);
        virtual ~CDBFighterPassiveSkillTableManager();
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SPassiveSkillKey, CDBFighterPassiveSkillTable> _mapPassiveSkillData; // OwnerID to SkillTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SPassiveSkillKey> _vecDelPassiveSkill;
};

#endif // #ifndef DB_FIGHTERR_PASSIVE_SKILL_TABLE_H

