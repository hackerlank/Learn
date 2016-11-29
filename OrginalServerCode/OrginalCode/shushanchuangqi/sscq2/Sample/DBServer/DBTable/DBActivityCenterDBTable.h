
#ifndef  DBACTIVITYCENTERTABLE_H__
#define  DBACTIVITYCENTERTABLE_H__
#include "DBTableBase.h"
#include "ProtoCommon.h"
#include "Singleton.h"

using namespace NProtoCommon;
struct SKey
{
    UINT32 dwActID;
    UINT8  byIndex;
    SKey(UINT32 ActID,UINT8 Index)
    {
        dwActID = ActID;
        byIndex = Index;
    }
    bool operator < (const SKey& oKey) const
    {
        if(dwActID != oKey.dwActID)
            return dwActID < oKey.dwActID;
        return byIndex < oKey.byIndex;
    }
};
class CDBActivityCenterDBTable: public TableRowBase,public SActivityOpt,public CPoolObj<CDBActivityCenterDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwActID       ),
            UPCOL(byIndex       ),
            UPCOL(strName       ),
            UPCOL(dwSync       ),
            UPCOL(dwAlarm       ),
            UPCOL(dwReady       ),
            UPCOL(dwBegin       ),
            UPCOL(dwEnd         ),
            UPCOL(bSync         ),
            UPCOL(dwOptTime     ),
            UPCOL(Max           )
        };

    public:
        CDBActivityCenterDBTable(UINT32 ID,UINT8 byInd): dwActID(ID),byIndex(byInd) { }
        void InitDataByBase(const SActivityOpt &rInfo);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
        UINT32 GetActID() const;
        UINT8  GetIndex() const;
    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT32 dwActID;
        UINT8 byIndex;
};

class CDBActivityCenterTableManager : public Singleton<CDBActivityCenterTableManager>
{ 
    public:
        CDBActivityCenterTableManager(UINT8 byLine = 0) : _byLine(byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        //void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        void QueryData();
        void DelData(const SActivityOpt& oActivityOpt);
        void Update(const SActivityOpt& oActivityOpt,bool bType);
        void GetALLInfo(TVecActivityOpt& rData);
        void DumpToDB();
        UINT32 GetUpdataNum();

    private:
        std::map<SKey,CDBActivityCenterDBTable> _mapData;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SKey> _vecDel;
};

#endif // 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

