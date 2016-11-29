#ifndef DBTRIPODHELPTABLE_H__
#define DBTRIPODHELPTABLE_H__
#include "DBTableBase.h"
#include "Tokenizer.h"
#include "TripodProt.h"
#include "ArenaGS.h"

using namespace NArenaGS;
using namespace NTripodProt;

struct STripodHelpEx : public STripodHelp
{
    string strFighterHelp;
    string strPlayerHelp;

    void Copy(const STripodHelp* pTripodHelp)
    {
        *((STripodHelp*) this) = *pTripodHelp;
        strFighterHelp = "";
        strPlayerHelp = "";

        for(auto itr = pTripodHelp->vecFighterHelp.begin(); itr != pTripodHelp->vecFighterHelp.end(); itr ++)
        {
            char strTmp[256];
            sprintf(strTmp,"%d,%d,%d,%d|", itr->wFighterID, itr->byPos, itr->byColor, itr->dwStartTime);
            strFighterHelp  = strFighterHelp + strTmp;
        }

        for(auto itr = pTripodHelp->vecPlayerHelp.begin(); itr != pTripodHelp->vecPlayerHelp.end(); itr ++)
        {
            char strTmp[256];
            sprintf(strTmp,"%ld,%d,%d,%d|", itr->qwRoleID, itr->byPos, itr->byLevel, itr->dwStartTime);
            strPlayerHelp  = strPlayerHelp + strTmp;
        }
    }

    //解析字符串
    void StrToVec()
    {
        Tokenizer tk(strFighterHelp, "|");
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT16 wFighterID = atoi(yatk[0].c_str());
            UINT8 byPos = 0;
            UINT8 byColor = 0;
            UINT32 dwTime = 0;
            if (wFighterID)
            {
                if (yatk.size() > 3)
                {
                    byPos   = atoi(yatk[1].c_str());
                    byColor = atoi(yatk[2].c_str());
                    dwTime  = atoi(yatk[3].c_str());
                }
                vecFighterHelp.push_back(SFighterHelpInfo(wFighterID, byPos, byColor, dwTime));
            }
        }
        Tokenizer tk1(strPlayerHelp, "|");
        for (size_t i = 0; i < tk1.size(); ++i)
        {
            Tokenizer yatk(tk1[i], ",");
            UINT64 qwRoleID = atol(yatk[0].c_str());
            UINT8 byPos = 0;
            UINT8 byLevel = 0;
            UINT32 dwTime = 0;
            if (qwRoleID)
            {
                if (yatk.size() > 3)
                {
                    byPos   = atoi(yatk[1].c_str());
                    byLevel = atoi(yatk[2].c_str());
                    dwTime  = atoi(yatk[3].c_str());
                }
                SPlayerHelpInfo oPlayerHelpInfo;
                oPlayerHelpInfo.qwRoleID = qwRoleID;
                oPlayerHelpInfo.byPos    = byPos;
                oPlayerHelpInfo.byLevel  = byLevel;
                oPlayerHelpInfo.dwStartTime = dwTime;
                vecPlayerHelp.push_back(oPlayerHelpInfo);
            }
        }
    }

    void CopyTo(STripodHelp& rTripodHelp)
    {
        rTripodHelp = *((STripodHelp*) this);
    }
};


class CDBTripodHelpTable : public TableRowBase, public STripodHelpEx, public CPoolObj<CDBTripodHelpTable>
{
    public:

        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(strFighterHelp),
            UPCOL(strPlayerHelp),
            UPCOL(Max)
        };

    public:
        CDBTripodHelpTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBTripodHelpTable():_qwRoleID(0){}
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

    private:
        bitset<UPCOL(Max)> _setChanged;
    public:
        UINT64 _qwRoleID;
};

typedef shared_ptr<SArenaFighter> STripodHelpPlayerPtr;
typedef function<void(INT8,STripodHelpPlayerPtr)> QueryPlayerFun;

class CDBTripodHelpTableManager : public Singleton<CDBTripodHelpTableManager>
{ 
    public:
        CDBTripodHelpTableManager(UINT8 byLine = 0): _byLine(byLine),_nNowQuery(0), _nMaxQuery(0), _nErrQuery(0), _dwQueryFighterMax(0) {}
        //void QueryData();
        void DelData(const STripodHelp& oData);
        void Update(const STripodHelp& oData);
        void GetALLInfo(TVecTripodHelp& vecTripodHelp);
        void DumpToDB();
        UINT32 GetUpdataNum();
        void GetAllTripodHelper(UINT32 dwPageSize);
        void QueryData(UINT32 dwPageSize,QueryFun fun);
        void QueryFighterData(UINT64 qwRoleId, QueryPlayerFun fun);
        void SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize);

    private:
        UINT8 _byLine;
        map<UINT64, CDBTripodHelpTable> _mapTripodHelp;
        vector<UINT64> _vecDelTripodHelp;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        UINT32 _dwQueryFighterMax;
};
extern CDBTripodHelpTableManager g_CDBTripodHelpTableManager;

#endif // DBTRIPODHELPTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

