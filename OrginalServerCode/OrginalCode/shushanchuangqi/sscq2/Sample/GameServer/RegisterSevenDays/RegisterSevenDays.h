#ifndef _REGISTERSEVENDAYS_H_
#define _REGISTERSEVENDAYS_H_
#include "RegisterSevenDaysProt.h"

using namespace NRegisterSevenDaysProt;

class CRegisterSevenDays : public CPoolObj<CRegisterSevenDays>
{

#define DAY_TIME 86400

enum
{
    THE_FIRST_DAY = 1,
    THE_SECOND_DAY,
    THE_THIRD_DAY,
    THE_FOURTH_DAY,
    THE_FIFTH_DAY,
    THE_SIXTH_DAY,
    THE_SEVENTH_DAY
};

enum
{
    NO_GETAWARD = 0,
    CAN_GETAWARD,
    ALREADY_GETAWARD
};

public:

   CRegisterSevenDays(CPlayer& rPlayer): _rPlayer(rPlayer) {}
   ~CRegisterSevenDays() {}

public:
   
   UINT32 GetRegisterCurDay();

   UINT32 GetOpenCurDay();
   
   void GetCurTargetInfo(UINT32& dwDay, UINT64& qwTargetInfo); 
   
   UINT64 GetTargetInfoByDayID(UINT32 dwDay);
    
   bool SetTargetInfoByDayID(UINT32 dwDay, UINT64 qwTargetInfo);

   bool GetAward(UINT32 dwDay, UINT8 byTargetID);
    
   EBuyStatus GetCurBuyStatus();
   
   void SetCurBuyStatus(EBuyStatus eBuyStatus);

   void GetCurBuyInfo(UINT32& dwDay, EBuyStatus& eBuyStatus);

   bool ReqBuy();
private:

   CPlayer& _rPlayer;

};

#endif // _REGISTERSEVENDAYS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */



