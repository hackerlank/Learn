#ifndef DBLINGSHANSHOPBUYLOGTABLE_H
#define DBLINGSHANSHOPBUYLOGTABLE_H
#include "DBGuildTableBase.h"
class CDBLingShanShopBuyLogTable : public TableRowBase, public CPoolObj<CDBLingShanShopBuyLogTable>
{
    friend class CDBLingShanShopBuyLogTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(wMsgID),
            UPCOL(vecString),
            UPCOL(vecParam),
            UPCOL(dwTime),
            UPCOL(Max)
        };

    public:
        CDBLingShanShopBuyLogTable();
        virtual ~CDBLingShanShopBuyLogTable();


        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64          GetGuildID() const;
        UINT16          GetMsgID() const;
        const string&   GetString() const;
        const string&   GetParam() const;
        UINT32          GetTime() const;

    private:
        bool InitDataByLingShanShopBuyLog(const SGuildLogInfo& rLog);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        UINT16 _wMsgID;
        string _strString;
        string _strParam;
        UINT32 _dwTime;
};

class CDBLingShanShopBuyLogTableManager : public CTableManagerBaseForGuild, public CPoolObj<CDBLingShanShopBuyLogTableManager>
{ 
    public:
        CDBLingShanShopBuyLogTableManager(UINT64 qwGuildID);
        virtual ~CDBLingShanShopBuyLogTableManager();

        virtual void QueryDataByGuildID(UINT64 qwGuildID, QueryFun fun);
        virtual void DelData(string& strData, UINT64 qwGuildID = 0);
        virtual void Update(string& strData, EDataChange eUpdateType);
        virtual void GetAllInfo(SDBGuildAllInfo& rData);
        virtual void DumpToDBGuild(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:

        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;

        vector<CDBLingShanShopBuyLogTable> _vecLingShanShopBuyData;
        TVecUINT64  _vecDelGuildID;
};

#endif //
