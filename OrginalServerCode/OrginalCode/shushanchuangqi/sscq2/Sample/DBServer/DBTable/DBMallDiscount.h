#ifndef  DB_MALLDISCOUNT_H__
#define  DB_MALLDISCOUNT_H__
#include "DBTableBase.h"
#include "MallProt.h"
#include "Tokenizer.h"

using namespace NMallProt;

struct SMallDiscountEx:public SDiscount
{
    string strDisItem;
    void Copy(const SDiscount* pDiscount)
    {
        *((SDiscount*) this) = *pDiscount;
        strDisItem = "";
        for(auto itr = pDiscount->vecDisItems.begin(); itr != pDiscount->vecDisItems.end(); itr++)
        {
            char strTmp[256];
            sprintf(strTmp,"%d,%d,%d|",itr->wItemID, itr->wOriginalPrice, itr->wDiscountPrice);
            strDisItem = strDisItem + strTmp;
        }
    }

    void UnPack(string& strData,TVecDiscountItem& vecDisItem)
    {
        Tokenizer tk(strData, "|");
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT16 wItemID = atoi(yatk[0].c_str());
            UINT16 wOriginalPrice = 0;
            UINT16 wDiscountPrice = 0;
            if (wItemID)
            {
                if (yatk.size() > 2)
                {
                    wOriginalPrice = atoi(yatk[1].c_str());
                    wDiscountPrice = atoi(yatk[2].c_str());
                }
                vecDisItem.push_back(SDiscountItem(wItemID,wOriginalPrice,wDiscountPrice));
            }
        }
    }
    
    //解析字符串
    void StrToVec()
    {
       UnPack(strDisItem, vecDisItems);
    }

    void CopyTo(SDiscount& rDiscount)
    {
        rDiscount = *((SDiscount*) this);

    }
};


class CDBMallDiscount :public TableRowBase, public SMallDiscountEx, public CPoolObj<CDBMallDiscount>
{
    public:

        enum EUpdateColumn
        {
            UPCOL(byPos),
            UPCOL(qwMarkID),
            UPCOL(strDisItem),
            UPCOL(byLimitType),
            UPCOL(dwLimitValue),
            UPCOL(wLimitCount),
            UPCOL(dwBeginTime),
            UPCOL(dwEndTime),
            UPCOL(Max)
        };

    public:
        CDBMallDiscount(UINT8 byPos):_byPos(byPos) {}
        CDBMallDiscount():_byPos(0){}
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
private:
        bitset<UPCOL(Max)> _setChanged;
public:
        UINT8 _byPos;

};

class CDBMallDiscountManager : public Singleton<CDBMallDiscountManager>
{ 
    public:
        CDBMallDiscountManager(UINT8 byLine = 0): _byLine(byLine),_nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        void QueryData();
        void DelAllData();
        void Update(const TVecDiscount& vecDisItems);
        void GetALLInfo(TVecDiscount& VecDiscount);
        void DumpToDB();
        UINT32 GetUpdataNum();

    private:
        map<UINT8, CDBMallDiscount> _mapMallDiscount;
        vector<UINT8> _vecDeleteDiscount;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
};

extern CDBMallDiscountManager g_CDBMallDiscountManager;

#endif

