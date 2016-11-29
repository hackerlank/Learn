#ifndef  DB_GUILDXIHE_H__
#define  DB_GUILDXIHE_H__
#include "DBTableBase.h"
#include "GuildProt.h"
#include "Tokenizer.h"

using namespace NGuildProt;

struct SGuildXiheEx : public SGuildXihe
{
    string strXihe;

    void Copy(const SGuildXihe* pXihe)
    {
        *((SGuildXihe*) this) = *pXihe;
        strXihe = "";

        for(auto itr = pXihe->vecTruckInfo.begin(); itr != pXihe->vecTruckInfo.end(); itr ++)
        {
            char strTmp[256];
            sprintf(strTmp,"%d,%d,%d,%s,%d|", itr->byTruckID, itr->byStatus, itr->byPos, itr->strName.c_str(),itr->byColor);
            strXihe = strXihe + strTmp;
        }
    }

    //解析字符串
    void StrToVec()
    {
        Tokenizer tk(strXihe, "|");
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT8 byTruckID = atoi(yatk[0].c_str());
            UINT8 byStatus = 0;
            UINT8 byPos = 0;
            UINT8 byColor = 0;
            string strName;
            if (byTruckID)
            {
                if (yatk.size() > 3)
                {
                    byStatus = atoi(yatk[1].c_str());
                    byPos    = atoi(yatk[2].c_str());
                    strName  = yatk[3].c_str();
                    byColor  = atoi(yatk[4].c_str());
                }
                vecTruckInfo.push_back(STruckInfo(byTruckID, byStatus, byPos, strName,byColor));
            }
        }
    }

    void CopyTo(SGuildXihe& rXihe)
    {
        rXihe = *((SGuildXihe*) this);
    }
};

class CDBGuildXihe: public TableRowBase, public SGuildXiheEx, public CPoolObj<CDBGuildXihe>
{
    public:

        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(byStage),
            UPCOL(dwEndTime),
            UPCOL(strXihe),
            UPCOL(byRequest),
            UPCOL(Max)
        };

    public:
        CDBGuildXihe(UINT64 qwRoleID):_qwRoleID(qwRoleID) {}
        CDBGuildXihe():_qwRoleID(0){}
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

class CDBGuildXiheManager : public Singleton<CDBGuildXiheManager>
{ 
    public:
        CDBGuildXiheManager(UINT8 byLine = 0): _byLine(byLine),_nNowQuery(0), _nMaxQuery(0), _nErrQuery(0), _dwQueryFighterMax(0) {}
        void QueryData(UINT32 dwPageSize, QueryFun queryfun);
        void Update(const SGuildXihe& oGuildXihe);
        void GetALLInfo(TVecGuildXihe& VecGuildXihe);
        void DumpToDB();
        UINT32 GetUpdataNum();

        void DelData(UINT64 qwRoleID);
        void SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize);
        void GetAllGuildXihe(UINT32 dwPageSize);
    private:
        map<UINT64, CDBGuildXihe> _mapAllGuildXihe;
        vector<UINT64> _vecDelXihe;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        UINT32 _dwQueryFighterMax;
};

extern CDBGuildXiheManager g_CDBGuildXiheManager;

#endif

