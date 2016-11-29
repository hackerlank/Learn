#ifndef POINTRANK_H__ 
#define POINTRANK_H__
#include "stdafx.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class CPointRank : public CWonderActivity
{
    public:
        CPointRank(UINT16 wType) : CWonderActivity(wType) { _setRank.clear(); }
        virtual ~CPointRank(){};
        void     OnEnd();
        void     OnRetain();
        void     TakePrize(UINT64 &qwPlayerID,UINT32 wCond) {};
        void     GetStateByRoleID(UINT64 qwRoleID,UINT16 wID,TVecWonderPrize2DB& sResult) {};
        bool     SendMail(UINT32& wHigh,UINT16& wLow, const TVecItemConfigPtr& vecItem, UINT16 &wMailID,UINT16 &wContentID);
        bool     GetPlayerInfo(bool bType,UINT64 &qwPlayerID,UINT16& wType,SWActPlayerInfo &sPlayer);
        void    GetRoleStateByActID(UINT64 qwRoleID,UINT16 wActID,TVecRoleStatus& vecRet) {}; 
        //检查是否达到条件
        bool     CheckConds(UINT32 wConds) { return true;};
    
    protected:
        TSetUINT32 _setRank;//临时数据

};
#endif
