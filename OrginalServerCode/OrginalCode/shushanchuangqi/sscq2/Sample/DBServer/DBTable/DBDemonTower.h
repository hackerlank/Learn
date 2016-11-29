#ifndef  DB_DEMONTOWER_PLAYER_H__
#define  DB_DEMONTOWER_PLAYER_H__
#include "DBTableBase.h"
#include "DemonTowerGS.h"
#include "Tokenizer.h"
using namespace NDemonTowerGS;

struct SDemonTowerPlayerEx:public SDemonTowerPlayer
{
    string sFailSoulPrize;
    string sDaySoulPrize;
    string sGatherSoulPrize;
    void Copy(const SDemonTowerPlayer* pDemonTowerPlayer)
    {
        *((SDemonTowerPlayer*) this) = *pDemonTowerPlayer;
        this->strRoleName = pDemonTowerPlayer->strRoleName;
        sFailSoulPrize = "";
        sDaySoulPrize = "";
        for(auto itr = pDemonTowerPlayer->vecFailSoulPrize.begin(); itr != pDemonTowerPlayer->vecFailSoulPrize.end(); itr++)
        {
            char strTmp[256];
            sprintf(strTmp,"%d,%d|",itr->dwMoneyType,itr->dwMoneyValue);
            sFailSoulPrize = sFailSoulPrize + strTmp;
        }

        for(auto itr = pDemonTowerPlayer->vecDaySoulPrize.begin(); itr != pDemonTowerPlayer->vecDaySoulPrize.end(); itr ++)
        {
            char strTmp[256];
            sprintf(strTmp,"%d,%d|",itr->dwMoneyType,itr->dwMoneyValue);
            sDaySoulPrize  = sDaySoulPrize + strTmp;
        }
        
        for(auto itr = pDemonTowerPlayer->vecGatherSoulPrize.begin(); itr != pDemonTowerPlayer->vecGatherSoulPrize.end(); itr ++)
        {
            char strTmp[256];
            sprintf(strTmp,"%d,%d|",itr->dwMoneyType,itr->dwMoneyValue);
            sGatherSoulPrize  = sGatherSoulPrize + strTmp;
        }
    }

    void UnPack(string& strData,TVecMoneyInfo& vecMoneyInfo)
    {
        Tokenizer tk(strData, "|");
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT32 dwType = atoi(yatk[0].c_str());
            UINT32 dwValue = 0;
            if (dwType)
            {
                if (yatk.size() > 1)
                    dwValue = atoi(yatk[1].c_str());
                vecMoneyInfo.push_back(MoneyInfo(dwType,dwValue));
            }
        }
    }

    
    //解析字符串
    void StrToVec()
    {
       UnPack(sFailSoulPrize,vecFailSoulPrize);
       UnPack(sDaySoulPrize,vecDaySoulPrize);
       UnPack(sGatherSoulPrize,vecGatherSoulPrize);
    }

    void CopyTo(SDemonTowerPlayer& rDemonTowerPlayer)
    {
        rDemonTowerPlayer = *((SDemonTowerPlayer*) this);

    }
};


class CDBDemonTowerPlayer :public TableRowBase, public SDemonTowerPlayerEx, public CPoolObj<CDBDemonTowerPlayer>
{
    public:

        enum EUpdateColumn
        {
            UPCOL(qwUserID),
            UPCOL(qwRoleID),
            UPCOL(strRoleName),
            UPCOL(bySex),
            UPCOL(byLevel),
            UPCOL(dwFloorID),
            UPCOL(dwGuardFloorID),
            UPCOL(dwGuardPos),
            UPCOL(dwGuardStartTime),
            UPCOL(dwGuardEndTime),
            UPCOL(dwGuardNextPrizeTime),
            UPCOL(dwGuardNextReduceRateTime),
            UPCOL(dwGuardGatherSpeed),
            UPCOL(dwGuardGatherSpeedEndTimer), 
            UPCOL(dwGuardReduceRate),
            UPCOL(dwGuardNextAttackTime),
            UPCOL(dwPower),
            UPCOL(sFailSoulPrize),
            UPCOL(sDaySoulPrize),
            UPCOL(sGatherSoulPrize),
            UPCOL(byColor),
            UPCOL(Max)
        };

    public:
        CDBDemonTowerPlayer(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        CDBDemonTowerPlayer():_qwRoleID(0){}
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

class CDBDemonTowerPlayerManager : public Singleton<CDBDemonTowerPlayerManager>
{ 
    public:
        CDBDemonTowerPlayerManager(UINT8 byLine = 0): _byLine(byLine),_nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        void QueryData();
        void DelData(const SDemonTowerPlayer& oData);
        void Update(const SDemonTowerPlayer& oData);
        void GetALLInfo(TVecDemonTowerPlayer& VecDemonTowerPlayer);
        void DumpToDB();
        UINT32 GetUpdataNum();

    private:
        map<UINT32,CDBDemonTowerPlayer> _mapDemonTowerPlayer;
        vector<UINT64> _vecDeleteDemonTowerPlayer;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
};
#endif

