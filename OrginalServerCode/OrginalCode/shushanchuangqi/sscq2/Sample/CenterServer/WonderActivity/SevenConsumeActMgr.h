#ifndef SEVENCONSUMEACTMGR_H__
#define SEVENCONSUMEACTGR_H__

#include "stdafx.h"
#include "Singleton.h"
#include "SevenConsumeCFG.h"
#include "ItemProt.h"
#include "User.h"

using namespace NItemProt;

#define SEVENCONSUME_PERIOD 7

//七日消费活动
struct SSevenConsumeCFGEx : public SSevenConsumeCFG
{
    void SetConfig(const SSevenConsumeCFG& rSevenConsumeCFG)
    {
        *(SSevenConsumeCFG*)this = rSevenConsumeCFG;
    }
    TVecItemCount _vecItem;
};


class CSevenConsumeActMgr : public Singleton<CSevenConsumeActMgr>
{
    public:
        CSevenConsumeActMgr() : _byState(0) {}
        ~CSevenConsumeActMgr() {}

        bool Init();
        bool ReLoadConfig(const string &);
        SSevenConsumeCFGEx* GetSevenConsumeCfg(UINT8 byIdx);

        bool IsOpenAct(UINT32 dwCurTime = time(NULL));
        void UpdateSevenConsumeAct(CUserPtr pUser);
        void OnSevenConsumeAct(CUserPtr pUser);
        void SendAwardMail(SSevenConsumeCFGEx*, CUserPtr pUser);
        void DelIcon();
        void OpenIcon();
        void TimerCheck();
    private:
        map<UINT8, SSevenConsumeCFGEx> _mapID2SevenConsumeCFG;
        UINT8 _byState;     //0未通知 1已通知开始 2已通知结束

};

#endif
