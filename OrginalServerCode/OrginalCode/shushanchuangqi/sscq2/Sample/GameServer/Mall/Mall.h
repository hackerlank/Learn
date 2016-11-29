
#ifndef MALL_H_
#define MALL_H_

#include "Singleton.h"
#include "MallProtSvr.h" // XXX: for EMallResult

using namespace NMallProt;

class CUser;

class CMall : public Singleton<CMall>
{
    public:
        EMallResult BuyItem(CUser& rUser, EUseMoneyMark eMark, EMallType eType, UINT32 dwInstID, INT16 wCount);

        void PresentItem(CUser& rUser, EUseMoneyMark eMark, EMallType eType, UINT32 dwInstID, INT16 wCount,
                const std::string& strReceiveName, const std::string& strTitle, const std::string& strMsg, shared_func<CMallProtSvr::SMallPresentAck>& fnACK);


        /********商城限购 begin*******/
        void SendMallDiscountInfo(CUserPtr pUser);
        void SendMallDiscountInfo(const SDiscount& oDiscount);
        EMallResult BuyDiscountItem(CUserPtr pUser, UINT8 byPos, UINT16 wCount);
        //XXX 是否开启充值仙石限购
        void IsInRechargeDiscount(UINT32& dwPos1EndTime, UINT32& dwPos2EndTime, UINT32& dwPos3EndTime);
        //XXX 是否开启消费仙石限购
        void IsInConsumeDiscount(UINT32& dwPos1EndTime, UINT32& dwPos2EndTime, UINT32& dwPos3EndTime);
        void CheckMarkID(CUserPtr pUser);
        void AddDiscountFromBS(const SDiscount& oDiscount);
        void ClearMallDiscount(UINT8 byPos);
        void LoadMallDiscount();
        void UpdateDiscountToDB();
        /********商城限购 end*********/

        void OnChongZhiAward(UINT16 wGoldID, UINT32 dwCount, CUserPtr pUser);
    private:
        TVecDiscount _vecDiscountItem;          //折扣道具信息

};

#endif // MALL_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

