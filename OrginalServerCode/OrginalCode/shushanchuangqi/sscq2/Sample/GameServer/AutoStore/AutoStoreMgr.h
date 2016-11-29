
#ifndef AUTOSTOREMGR_H_
#define AUTOSTOREMGR_H_
#include "RoleInfoDefine.h"
#include "CommonDef.h"
using namespace NProtoCommon;
using namespace NRoleInfoDefine;
class CPlayer;


enum EAutoStore
{
    //不要修改下面的索引定义,会影响数据库数据
    eAutoStore_Invalid,
    eAutoStore_BattleArray              = 1, //破阵攻击次数
    eAutoStore_BattleArray_BuyAtkCnt    = 2, //破阵购买次数
    eAutoStore_Action_TakeFlag          = 3, //体力领取时间
    eAutoStore_Beauty                   = 4, //爱心数目
    eAutoStore_BattleArray_MinTurns     = 5, //破阵战斗最小回合数
    eAutoStore_ZhanQi                   = 6, //秘境寻宝
    eAutoStore_Achievement_ShareFriend  = 7, //成就分享
    eAutoStore_Beauty_RareItem          = 8, //获得的稀有物品
    eAutoStore_Activity_ShareFriend     = 9, //活跃度分享
    eAutoStore_DemonTower_LayerPrize    = 10, //锁妖塔每层奖励 
    eAutoStore_ItemUse                  = 11, //物品使用(礼包掉落保护)
    eAutoStore_FeedBack_TakPrize        = 20, //消费回馈领奖次数     class 活动id
    eAutoStore_FeedBack_BuyCnt          = 21, //消费回馈购买次数     class 回馈类型
    eAutoStore_FeedBack_MaxTakePrize    = 22, //消费回馈最大领奖次数 class 活动id
    eAutoStore_FeedBack_InitData        = 23, //消费回馈初始化数据   class 回馈类型
};

struct SAutoStoreKey
{
    SAutoStoreKey(UINT16 wType,UINT32 dwClassID)
        :wType(wType),dwClassID(dwClassID) {}
    UINT16  wType;
    UINT32  dwClassID;

    bool operator < (const SAutoStoreKey& sk) const
    {
        if (wType !=  sk.wType)
            return wType < sk.wType;
        return dwClassID < sk.dwClassID;
    }
};

typedef std::map<SAutoStoreKey,SAutoStoreDBInfo> TMapAutoStoreDBInfo;

class CAutoStoreMgr 
{

public:
    CAutoStoreMgr(CPlayer& rPlayer);
    ~CAutoStoreMgr() {}
    static bool AutoStoreInit();
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(const SAutoStoreDBInfo& rInfo, EDataChange eDataChanige = eOpUpdate);
    
    //增加值(注意初始值默认为0)
    void AddValue(EAutoStore eType,UINT32  dwClassID,UINT32  dwAddvalue);

    //设置值
    void SetValue(EAutoStore eType,UINT32  dwClassID,UINT32  dwvalue);

    //如果未找到默认返回值0
    UINT32 GetValue(EAutoStore eType,UINT32  dwClassID);

    //删掉值
    void Remove(EAutoStore eType,UINT32  dwClassID);

    //清理某类数据
    void ClearValue(EAutoStore eType);

    //获取某个类型的全部值
    void GetListByType(EAutoStore eType,TVecAutoStoreDBInfo& vecAutoStoreDBInfo);

    //零点事件
    void OnMidNight();

    //19点事件
    void On19Event();

private:
    CPlayer&  _rPlayer;
    TMapAutoStoreDBInfo _mapAutoStoreDBInfo;
};

#endif // EXCHANGEMALLMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

