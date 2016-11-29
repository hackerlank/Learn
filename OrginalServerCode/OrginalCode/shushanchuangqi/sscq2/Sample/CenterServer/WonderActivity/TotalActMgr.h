#ifndef TOTALACTMGR_H__ 
#define TOTALACTMGR_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class CTotalActMgr : public CWonderActivity
{
    public:
        CTotalActMgr(UINT16 wType,UINT8 byType) : CWonderActivity(wType)
        {
            _byType = byType;
        }
        virtual ~CTotalActMgr(){};
        bool     SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID){ return false; };
        void     TakePrize(UINT64 &qwPlayerID,UINT32 wCond) ;
        void     GetStateByRoleID(UINT64 qwRoleID,UINT16 wID,TVecWonderPrize2DB& sResult) {};
        void     OnRetain();
        void     OnEnd();
        //检查是否达到条件
        bool     CheckConds(UINT32 wConds);
        void     GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet); 
        UINT32   GetCurRoleCount(UINT16 wActID,UINT32 wCond);
        UINT8    GetPrizeStateForRole(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond);
        bool     GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer) { return false; };

    protected:
        UINT8 _byType;

};
#endif
