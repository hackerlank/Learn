#ifndef DRAGONBALLACTMGR_H__
#define DRAGONBALLACTGR_H__

#include "stdafx.h"
#include "Singleton.h"
#include "DragonBallCFG.h"
#include "ItemProt.h"
#include "User.h"

using namespace NItemProt;

#define DRAGONBALL_PERIOD 7

//七龙珠活动
struct SDragonBallCFGEx : public SDragonBallCFG
{
    void SetConfig(const SDragonBallCFG& rDragonBallCFG)
    {
        *(SDragonBallCFG*)this = rDragonBallCFG;
    }
    TVecItemCount _vecItem;
};


class CDragonBallActMgr : public Singleton<CDragonBallActMgr>
{
    public:
        CDragonBallActMgr() : _byState(0) {}
        ~CDragonBallActMgr() {}

        bool Init();
        bool ReLoadConfig(const string &);
        SDragonBallCFGEx* GetDragonBallCfg(UINT8 byIdx, UINT8 byDay);

        void TimeCheck(time_t tNow);
        void DelIcon();
        void OpenIcon();
        bool IsOpenAct(UINT32 dwCurTime = time(NULL));
        void UpdateDragonBallAct(CUserPtr pUser);
        UINT8 GetUserExtraCount(CUserPtr pUser);
        void OnDragonBallAct(CUserPtr pUser);
        void SendAwardMailDay(SDragonBallCFGEx*, UINT64 qWUserID);
        void SendAwardMailFinal(SDragonBallCFGEx*, UINT64 qWUserID);
    private:
        map<UINT16, map<UINT8, SDragonBallCFGEx>> _mapID2DragonBallCFG;
        UINT8 _byState;     //0未通知 1已通知开始 2已通知结束
};

#endif
