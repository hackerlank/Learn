#ifndef TRUMPRANK_H__ 
#define TRUMPRANK_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class CTrumpRank : public CWonderActivity
{
    public:
        CTrumpRank(UINT16 wType) : CWonderActivity(wType) {}
        virtual ~CTrumpRank(){};
        void     OnRetain();
        void     OnEnd();

        //继承自父类 必须有实现
        void    TakePrize(UINT64 &qwPlayerID,UINT32 wCond)  {};
        void    GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet) {}; 
        bool    GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer);
        bool    SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID);
        void    GetStateByRoleID(UINT64 qwRoleID,UINT16 wID,TVecWonderPrize2DB& sResult) {};
        bool             CheckConds(UINT32 dwCond){return true;};
    protected:
    private:


};
#endif
