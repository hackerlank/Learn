#ifndef  DBTOTAL_GAMEVAR_TABLE_H__
#define  DBTOTAL_GAMEVAR_TABLE_H__
#include "DBTableBase.h"
class CDBTotalGameVars : public SGameVarsDBInfo, public CPoolObj<CDBTotalGameVars>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwValue),
            UPCOL(dwExpired),
            UPCOL(Max)
        };

    public:
        CDBTotalGameVars():_bIsNew(false){}
        void InitDataByData(const SGameVarsDBInfo & rData);
        bool UpdateDataByData(const SGameVarsDBInfo & rData);
        bool GetInsertSqlStr(string& sqlstr);
        bool GetUpdateSqlStr(string& sqlstr);
        void ResetChange(void);
        void InitDataByDBRow(const mysqlpp::Row &row);
        void SetNew(bool bNew) {_bIsNew = bNew;}
        bool IsNew(){return _bIsNew;}
        bool IsChange(){ return !_setChanged.none();}
        UINT16 GetVar(){return wVar;}
    private:
        bitset<UPCOL(Max)> _setChanged;
        bool _bIsNew;

};
typedef shared_ptr<vector<SGameVarsDBInfo> > vecSGameVarsDBInfoPtr;
typedef function<void(vecSGameVarsDBInfoPtr)> QueyAllFun;
class CDBTotalGameVarsManager : public CPoolObj<CDBTotalGameVarsManager>
{ 
    public:
        CDBTotalGameVarsManager():_byLoadStatus(0){}
        void QueryData(QueryFun fun);
        void DelData(UINT16 wVar);
        void UpdateData(const SGameVarsDBInfo &stData);
        void DumpToDB();
        void LoadData(QueyAllFun fnAck);
        UINT32 GetUpdataNum();
    private:
        map<UINT16,CDBTotalGameVars> _mapGameVarsData;
        vector<UINT16> _vecDelGameVars;
        UINT8 _byLoadStatus;//0;未加载，1已加载未返回，2已加载且返回
        vector<QueyAllFun> _vecLoad;
};
extern CDBTotalGameVarsManager g_CDBTotalGameVarsManager;
#endif

