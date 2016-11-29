
#ifndef FEEDBACK_H_
#define FEEDBACK_H_

#include "Singleton.h"
#include "MiscProt.h"
#include "User.h"
#include "VarDefine.h"
#include "FeedbackCFG.h"
#include "FeedbackBagCFG.h"
#include "ItemProt.h"
#include "FeedBackProt.h"

using namespace NItemProt;
using namespace NFeedBackProt;

struct SFeedbackCFGEx:public SFeedbackCFG
{
    TVecItemGenInfo _vecPrize;
    TVecItemGenInfo _vecRandomPrize;
    UINT32 _dwBeginTime;
    UINT32 _dwEndTime;
    void CopyFrom(SFeedbackCFG& rFeedbackCFG)
    {
        *((SFeedbackCFG*)this)=rFeedbackCFG;
    }
};

typedef std::shared_ptr<SFeedbackCFGEx> SFeedbackCFGExPtr;
typedef std::map<UINT16,SFeedbackCFGExPtr> TMapFeedbackCFGExPtr;
typedef std::vector<SFeedbackCFGExPtr>     TVecFeedbackCFGExPtr;

struct SFeedbackBagCFGEx:public SFeedbackBagCFG
{

    TVecItemGenInfo _vecItem;
    UINT32 _dwBeginTime;
    UINT32 _dwEndTime;
    void CopyFrom(SFeedbackBagCFG& rFeedbackBagCFG)
    {
        *((SFeedbackBagCFG*)this)=rFeedbackBagCFG;
    }
};

typedef std::shared_ptr<SFeedbackBagCFGEx> SFeedbackBagCFGExPtr;
typedef std::map<UINT16,SFeedbackBagCFGExPtr> TMapFeedbackBagCFGExPtr;
typedef std::vector<SFeedbackBagCFGExPtr>     TVecFeedbackBagCFGExPtr;

class CFeedBackMgr
{
public:
    CFeedBackMgr();
    ~CFeedBackMgr() {}

    bool FeedBackMgrInit();

    //初始化数据
    void InitData();

    void CloseIcon();

    void TimerCheck();

    void OnMidNight();


    void OnPlayerMidNight(CPlayer& rPlayer);

    void InitPlayerData(CPlayer& rPlayer,UINT32 dwActiveType);

    void CheckUpdateTime(bool bNotify);

    //玩家登陆
    void OnLogin(CPlayer& rPlayer);

    //强化
    void OnEquipTrumpChange(CPlayer& rPlayer,UINT8 byQuality,UINT8 byMinLevel);

    //合成
    void OnStoneChange(CPlayer& rPlayer,UINT8 byMinLevel,UINT32 dwCount);

public:

    //接收：获取回馈列表
    EFeedBackRet OnGetFeedBackList(CPlayer& rPlayer,TVecFeedBackInfo& vecFeedBackInfo,TVecSBuyDiscountInfo& vecSBuyDiscountInfo);

    //接收：购买折扣物品
    EFeedBackRet OnBuyDisCountItem(CPlayer& rPlayer,UINT32 dwBuyID,UINT32 dwCount);

    //接收：领取奖励
    EFeedBackRet OnTakeFeedBackPrize(CPlayer& rPlayer,UINT32 dwActID);

private:
    //消费活动
    TMapFeedbackCFGExPtr _mapActiveFeedbackCFGExPtr;

    //购买折扣活动
    TMapFeedbackBagCFGExPtr _mapActiveFeedbackBagCFGExPtr;

   private:
    TMapFeedbackCFGExPtr _mapFeedbackCFGExPtr;
    TMapFeedbackBagCFGExPtr _mapFeedbackBagCFGExPtr;
};

#endif 
extern CFeedBackMgr g_FeedBackMgr;
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

