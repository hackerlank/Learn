#ifndef ACTIVITY_H__
#define ACTIVITY_H__
#include "stdafx.h"
#include "RoleInfoDefine.h"
#include "ActivityProt.h"
#include "ActivityManager.h"
#include "EventMgr.h"
class CPlayer;
using namespace NRoleInfoDefine;
using namespace NActivityProt;
using namespace NProtoCommon;
enum IconAppear
{
    ActivityIcon = 36,

};
class CActivityPkg:public CRegiserterEvent
{
    public:
        CActivityPkg(CPlayer &rPlayer);
        bool HasIcon();
        void Init(const TVecActivityTaskInfo &rvecInfo);
        void Update2DB(const SActivityTaskInfo & rInfo,EDataChange eUpdatwEventId);
        void SendAllInfoActivity();
        EActivityResult GetActivityAward(const SActivityAward& stActivityGet);
        EActivityResult GetActivityPool(UINT32 &dwTotalActivity);
        //void CheckActivityPoint(UINT16 wEventId); 
        virtual void OnEvent(SEventInfoPtr pEventInfo);
        void RegiserterEvent(UINT8 bySource = 0);//0,初始化，1，升级,2vip变更
        void OnLevelUp();
        void OnVipUp();
        void OpenIcon();
        void AddActivity(UINT16 wActivity);    
        void AddActivityPool(UINT16 wActivity);
    private:
        bool DoLoot(UINT32 dwLootId);
        bool  CheckActivityTask();
        UINT32 ThisDayZero();

        //分享好友状态
        void SetShareStatus(UINT32 dwActivityID,EShareStatus eStatus);
        EShareStatus GetShareStatus(UINT32 dwActivityID);

    public:
        //获取分享列表
        void OnGeShareList(TVecActivityShare& vecActivityShare);
        EActivityResult OnTakeSharePrize(UINT32 dwActivityID);

    private:
        map<UINT16,SActivityTaskInfo> _mapActivityTaskInfo;
        UINT16 _wLastLevel;
        UINT8 _byLastVIp;
};
#endif

