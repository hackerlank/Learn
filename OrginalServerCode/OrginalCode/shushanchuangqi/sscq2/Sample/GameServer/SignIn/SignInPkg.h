#ifndef SINGN_H__
#define SINGN_H__
#include "stdafx.h"
#include "SignProt.h"
class CPlayer;
using namespace NSignProt;
class CSignInPkg
{
    public:
        CSignInPkg(CPlayer& rPlayer);
        void GetSignInfo(UINT32 &dwSignData,UINT8 &byReSignTimes,UINT32 &dwAward);
        ESignResult DoSign(UINT32 &dwSignData);
        ESignResult DoReSign(UINT8 byDay,UINT32 &dwSignData,UINT8 &byReSignTimes);
        ESignResult DoGetAward(UINT8 byId,UINT32 &dwAward);
    private:
        //0~31:日期签到 32~39 已补签数 40~63 领奖状态
        void BITGetSignDays(UINT64 qwVar,UINT32 &dwSignData);
        void BITDoSetSignDay(UINT64& qwVar,UINT8 byDay);
        bool BITCheckSignDay(UINT64 qwVar,UINT8 byDay);
        void BITGetReSignTimes(UINT64 qwVar,UINT8 &byReSignTimes);
        void BITDoAddSignTimes(UINT64& qwVar);
        void BITGetGetAwards(UINT64 qwVar,UINT32 &dwAward);
        void BITAddAwards(UINT64 &qwVar,UINT8 byId);
        bool BITCheckAward(UINT64 qwVar,UINT8 byId);
        UINT8 GetSignDays(UINT64 qwVar);
        UINT8 GetDay();
        UINT64 GetBITValue(UINT64 setValue,UINT8 byStart,UINT8 byEnd);

    private:
        CPlayer &_rPlayer;

};
#endif

