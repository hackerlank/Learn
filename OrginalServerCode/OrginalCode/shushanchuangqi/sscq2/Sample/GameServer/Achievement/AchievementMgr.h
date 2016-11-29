#ifndef _ACHIEVEMENTMGR_H
#define _ACHIEVEMENTMGR_H
#include "AchievementCFG.h"
#include "AchievementLevelCFG.h"
#include "EventMgr.h"
#include "AchievementProt.h"
#include "ItemProt.h"
using namespace NProtoCommon;
using namespace NAchievementProt;
using namespace NItemProt;
//成就基本信息
struct SAchievementCFGEx:SAchievementCFG
{

    TVecUINT32 _vecEventInstID; //多个事件条件
    TVecItemGenInfo _vecPrize;  //成就完成奖励
    TVecItemGenInfo _vecSharePrize; //分享奖励
    void CopyFrom(SAchievementCFG& rAchievementCFG)
    {
        *((SAchievementCFG*)this) = rAchievementCFG;
    }
};

typedef shared_ptr<SAchievementCFGEx> SAchievementCFGExPtr;
typedef std::map<UINT32,SAchievementCFGExPtr> TMapAchievementCFGExPtr;
typedef std::vector<SAchievementCFGExPtr>   TVecAchievementCFGExPtr;

//成就等级信息
struct SAchievementLevelCFGEx:public SAchievementLevelCFG
{
    void CopyFrom(SAchievementLevelCFG& rCFG)
    {
        *((SAchievementLevelCFG*)this) = rCFG;
    }
};

typedef shared_ptr<SAchievementLevelCFGEx> SAchievementLevelCFGExPtr;
typedef std::vector<SAchievementLevelCFGExPtr> TVecAchievementLevelCFGExPtr;

typedef std::map<UINT32,SAchievementInfo> TMapAchievementInfo;

typedef std::map<UINT32,SAchievementShare> TMapAchievementShare;

class CPlayer;
class CAchievementMgr:public CRegiserterEvent
{
 public:
     CAchievementMgr(CPlayer& rPlayer);
     ~CAchievementMgr(){};
     
     static bool AchievementInit();
     
     static bool ReLoadConfig(const string&);

     static TMapAchievementCFGExPtr& GetAllAchievement();

     SAchievementCFGExPtr GetAchievementCFGByID(UINT32 wAchieveID);

     static SAchievementLevelCFGExPtr GetAchievementLevelCFGByLevel(UINT32 dwLevel);

     void TiggerEvent(const UINT32 dwEventId,const TVecINT32& _vecParam,const EEventCondition eEventCondition,const SEventCFGExPtr pEventCFGExPtr);

     void LoadFromDB(const TVecAchievementInfo& vecAchievementInfo);
     void UpdateToDB(SAchievementInfo& rInfo,EDataChange eDataChange = eOpUpdate);

     void OnFinishAchieve(const SAchievementCFGExPtr& pAchievementCFGEx);

     //第一次完成
     void OnNewFinishAchieve(const SAchievementCFGExPtr& pAchievementCFGEx);

     bool IsFinished(UINT16 wAchieveID);

     UINT32 GetProcess(UINT16 wAchieveID);

     void SetProcess(UINT16 wAchieveID,UINT32 dwTotal,bool bInit = false);
    
     //检查升级
     void OnCheckLevel();

     void RebuildAttr();

     const TVecFloat& GetAttrVec() const { return _vecAttr; };

     void GetAchieveInfo(TVecAchievementInfo& vecAchievementInfo);

     EAchievementRet OnTakePrize(UINT16 wAchievementID);

     void NotifiyUpdate(SAchievementInfo& oInfo);

     //
     void SetSharePrize(UINT16 wAchievementID);
     bool IsTakeSharePrize(UINT16 wAchievementID);
     void ClearTakeSharePrize();

     //事件中心发过来的消息
     virtual void OnEvent(SEventInfoPtr pEventInfo);

     //接收：获取成就分享信息
     void OnGeAchievementShareList(TVecAchievementShare& vecAchievementShare);

     //接收：获取成就分享奖励
     EAchievementRet OnTakeSharePrize(UINT16 wAchievementID); 

 private:
     CPlayer& _rPlayer;

     //属性
     TVecFloat  _vecAttr;
     
     //成就表
     TMapAchievementInfo _mapAchievementInfo;

     //分享表
     TMapAchievementShare _mapAchievementShare;

     bool _bGetData;

     static TMapAchievementCFGExPtr _mapAchievementCFGExPtr;
     static TVecAchievementLevelCFGExPtr _VecAchievementLevelCFGExPtr;
     //static std::vector<TVecAchievementCFGExPtr> _vecEventList;
     bool _bLog;
};


#endif

