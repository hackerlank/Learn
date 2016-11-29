#ifndef HORSEACT_H__ 
#define HORSEACT_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class CHorseActMgr : public CWonderActivity
{
    public:
        CHorseActMgr() : CWonderActivity(eWActType_HORSEACT){}
        CHorseActMgr(UINT16 wType) : CWonderActivity(wType){}
        virtual ~CHorseActMgr(){};
        void     TakePrize(UINT64 &qwPlayerID,UINT32 wCond) ;
        bool     SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID){ return false; };
        void     GetStateByRoleID(UINT64 qwRoleID,UINT16 wID,TVecWonderPrize2DB& sResult) {};
        void     OnEnd();
        void     OnRetain();
        //检查是否达到条件
        bool     CheckConds(UINT32 wConds);
        void     GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet); 
        UINT32   GetCurRoleCount(UINT16 wActID,UINT32 wCond);
        UINT8    GetPrizeStateForRole(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond);
        bool     GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer) { return false; };
    protected:
    private:
        set<UINT64> _setAddItemUser;    // 零时保存用来防止重复领取奖励的缓存

};
#endif
