#ifndef DB_BUFF_TABLE_H
#define DB_BUFF_TABLE_H
#include "DBTableBase.h"

#include "ProtoCommon.h"

using namespace NProtoCommon;

struct SBuffKey
{
    SBuffKey(UINT64 qwOwnerID, UINT8 byBuffType, UINT16 wBuffID)
        : qwOwnerID(qwOwnerID), byBuffType(byBuffType), wBuffID(wBuffID) {}

    UINT64  qwOwnerID;
    UINT8   byBuffType;
    UINT16  wBuffID;

    bool operator < (const SBuffKey& sk) const
    {
        if (qwOwnerID < sk.qwOwnerID)
        {
           return true;
        }
        else if (qwOwnerID > sk.qwOwnerID)
        {
            return false;
        }

        if(byBuffType < sk.byBuffType)
        {
             return true;
        }
        else if(byBuffType > sk.byBuffType)
        {
          return false;
        }
        return wBuffID < sk.wBuffID;

    }
};

class CDBBuffTable : public TableRowBase, public CPoolObj<CDBBuffTable>
{
    friend class CDBBuffTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(qwOwnerID),
            UPCOL(byBuffType),
            UPCOL(wBuffID),
            UPCOL(byBuffState),
            UPCOL(dwBuffTime),
            UPCOL(strBuffParam),
            UPCOL(dwBuffCount),
            UPCOL(Max)
        };

    public:
        CDBBuffTable();
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetOwnerID() const;
        UINT64  GetRoleID() const;
        UINT8   GetBuffType() const;
        UINT16  GetBuffID() const;
        UINT8   GetBuffState() const;
        UINT32  GetBuffTime() const;
        const string& GetBuffParam() const;
        UINT32  GetBuffCount() const;

    private:
        bool InitDataByBuff(const SDBBuffInfo& rBuffInfo);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwRoleID;
        UINT64 _qwOwnerID;
        UINT8  _byBuffType;
        UINT16 _wBuffID;
        UINT8  _byBuffState;
        UINT32 _dwBuffTime;
        string _strBuffParam;
        UINT32 _dwBuffCount;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class CDBBuffTableManager : public TableManagerBaseForRole, public CPoolObj<CDBBuffTableManager>
{ 
    public:
        CDBBuffTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeBuffInfo,setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SBuffKey,CDBBuffTable> _mapBuffData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SBuffKey> _vecDelBuff;
};


#endif // #ifndef DB_BUFF_TABLE_H
