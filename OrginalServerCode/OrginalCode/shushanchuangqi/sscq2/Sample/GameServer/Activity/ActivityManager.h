#ifndef ACTIVITYMANAGER_H__
#define ACTIVITYMANAGER_H__
#include "stdafx.h"
#include "ActivityProt.h"
#include "ItemProt.h"
using namespace NItemProt;

const UINT8 byVIPBit =16;
struct ActivityAward
{
    UINT64 qwKey;
    UINT16 wActivity;
    UINT8  byVIPLevel;
    UINT32 dwLootId;   // 宝箱ID
    ActivityAward()
    {
        qwKey = 0;
        wActivity = 0;
        byVIPLevel = 0;
        dwLootId = 0;
    }
};
/*
enum UINT16
{
    EPOINTTYPE_NONE,//无
    EPOINTTYPE_STRONG_EQUIP,//强化装备
    EPOINTTYPE_PASS_DGN,//通关任意一个副本
    EPOINTTYPE_HARDENE_BODY,//任意散仙淬体一次
    EPOINTTYPE_SKILL_LEVELUP,//任意散仙技能升级一次
    EPOINTTYPE_TRUMP_LEVELUP,//任意散仙法宝升级一次
    EPOINTTYPE_BLOOD_WAKEUP,//任意散仙血脉觉醒一次
    EPOINTTYPE_GIFT_LEVELUP,//任意散仙天赋技能升级一次
    EPOINTTYPE_HERO_TRANS,//散仙转移一次
    EPOINTTYPE_MAX,//最大值
};
*/
struct SActivityPointCFGEx
{

    UINT16 wEventId;
    UINT16 wMinLevel;
    TVecUINT8  vecMaxTimes;
    UINT16 wActivity;
    TVecItemGenInfo _vecSharePrize; //分享奖励
    UINT8 GetMaxTimesByVip(UINT8 byVipLevel) const;
    UINT8 _Share;
    SActivityPointCFGEx()
    {
        wEventId = 0;
        wMinLevel = 0;
        wActivity = 0;
        _Share = 0;
    }
};

class CActivityManager
{
    public:
        bool MakeAwardKey(const NActivityProt::SActivityAward &rAward,UINT64 &qwKey);
        bool Init();
        bool ReLoadConfig(const string&);
        const ActivityAward* GetAward(UINT64 qwKey);
        void GetActivityAward(NActivityProt::TVecActivityAward &vecAward,UINT64 qwData);        
        const SActivityPointCFGEx * GetActivityPoint(UINT16 wEventId);
        UINT32 GetLootIdByVip(UINT16 wVipLevel);
        void GetRandomActivityPoint(UINT8 byNum,vector<UINT16>&rvec);
        void GetAllActivityPoint(vector<UINT16>&rvec);
        
    private:
        map<UINT64,ActivityAward> _mapActivityAward;
        map<UINT16,SActivityPointCFGEx> _mapActivityPoint;
        map<UINT16,UINT32> _mapVipActivityPool;
};
extern CActivityManager g_CActivityManager;

#endif
