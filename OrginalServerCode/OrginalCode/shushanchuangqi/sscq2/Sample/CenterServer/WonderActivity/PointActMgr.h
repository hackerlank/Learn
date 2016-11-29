#ifndef POINTACTMGR_H__ 
#define POINTACTMGR_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class CPointActMgr : public CWonderActivity
{
    public:
        CPointActMgr(UINT16 wType) : CWonderActivity(wType) { _setRank.clear(); }
        virtual ~CPointActMgr(){};
        void     TakePrize(UINT64 &qwPlayerID,UINT32 wCond) ;
        void     GetStateByRoleID(UINT64 qwRoleID,UINT16 wID,TVecWonderPrize2DB& sResult) {};
        void     OnRetain();
        void     OnEnd();
        bool     SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID) { return false; };
        bool     GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer) { return false; };
        //检查是否达到条件
        bool     CheckConds(UINT32 wConds);
        void     GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet); 
        UINT32   GetCurRoleCount(UINT16 wActID,UINT32 wCond);
        UINT8   GetPrizeStateForRole(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond);
    protected:
        TSetUINT32 _setRank;//临时数据

};
#endif
