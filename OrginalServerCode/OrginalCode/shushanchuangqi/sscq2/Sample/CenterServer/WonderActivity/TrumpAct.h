#ifndef TRUMPACT_H__ 
#define TRUMPACT_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class CTrumpAct : public CWonderActivity
{
    public:
        CTrumpAct(UINT16 wType) : CWonderActivity(wType){}
        virtual ~CTrumpAct(){};
        void     TakePrize(UINT64 &qwPlayerID,UINT32 wCond) ;
        bool     SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID){ return false; };
        void     GetStateByRoleID(UINT64 qwRoleID,UINT16 wID,TVecWonderPrize2DB& sResult) {};
        void     OnEnd();
        void     OnRetain();
        void     GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet); 
        bool     GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer) { return false; };
        UINT8    GetPrizeStateForRole(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond);
    protected:
    private:
        UINT32   GetCurRoleCount(UINT16 wActID,UINT32 wCond);
        //检查是否达到条件
        bool     CheckConds(UINT32 wConds);
        set<UINT64> _setAddItemUser;    // 零时保存用来防止重复领取奖励的缓存

};
#endif
