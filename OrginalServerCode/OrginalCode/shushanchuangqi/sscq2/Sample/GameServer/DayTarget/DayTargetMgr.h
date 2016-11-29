/*
 * 七日目标活动
*/
#ifndef _DAYTARGETMGR_H
#define _DAYTARGETMGR_H
#include "SevenDaysTargetCFG.h"
#include "EventMgr.h"
#include "DayTargetS.h"
#include "ItemProt.h"
using namespace NProtoCommon;
using namespace NDayTarget;
using namespace NItemProt;
//活动基本信息
struct SDayTargetCFGEx:SSevenDaysTargetCFG
{
    TVecItemGenInfo _vecPrizeItem; //物品奖励
    TVecUINT32    _vecEventInstID;
    void CopyFrom(SSevenDaysTargetCFG& rCFG)
    {
        *((SSevenDaysTargetCFG*)this) = rCFG;
    }
};


typedef shared_ptr<SDayTargetCFGEx> SDayTargetCFGExPtr;
typedef std::vector<SDayTargetCFGExPtr> TVecDayTargetCFGExPtr;

typedef std::map<UINT16,SDayTargetCFGExPtr> TMapDayTargetCFGExPtr;

typedef std::map<UINT16,SDayTargetDBInfo> TMapDayTargetDBInfo;

class CPlayer;
class CDayTargetMgr:public CRegiserterEvent
{
 public:
     CDayTargetMgr(CPlayer& rPlayer);
     ~CDayTargetMgr(){};
     
     static bool DayTargetInit();
     
     static bool ReLoadConfig(const string&);

     SDayTargetCFGExPtr GetDayTargetCFGByID(UINT32 wTaskID);

     void LoadFromDB(const TVecDayTargetDBInfo& vecDayTargetInfo);
     void UpdateToDB(SDayTargetDBInfo& rInfo,EDataChange eDataChange = eOpUpdate);

     bool IsFinished(UINT16 wTaskID);

     UINT32 GetProcess(UINT16 wTaskID);

     void SetProcess(UINT16 wTaskID,UINT32 dwTotal,bool bInit = false);

     //任务完成
     void   OnFinish(UINT16 wTaskID);

    

     void GetTaskList(TVecDayTargetTask& vecDayTargetTask);

     void NotifiyUpdate(SDayTargetDBInfo& oInfo);

     //事件中心发过来的消息
     virtual void OnEvent(SEventInfoPtr pEventInfo);

     //领取奖励
     EDayTargetRet TakePrize(UINT16 wTaskID);

 private:
     CPlayer& _rPlayer;
     
     TMapDayTargetDBInfo _mapDayTargetInfo;

     bool _bGetData;

     //数据保存数据
     TMapDayTargetDBInfo _mapDayTargetDBInfo;

     //基础配置数据
     static TMapDayTargetCFGExPtr _mapDayTargetCFGExPtr;

     bool _bLog;
};


#endif

