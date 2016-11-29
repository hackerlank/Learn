
#ifndef BEAUTYMGR_H_
#define BEAUTYMGR_H_
#include <algorithm>
#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "Beauty.h"
#include "BeautyS.h"
#include "Item.h"
#include "BeautyCFG.h"
#include "BeautyLevelCFG.h"
#include "BeautyLotteryCFG.h"
#include "Battle.h"
#include "BeautyRareLotteryCFG.h"
using namespace NProtoCommon;
using namespace NRoleInfoDefine;
using namespace NBeauty;
class CPlayer;

//等级id转换比例
const UINT16 PERID = 100;

enum EBeautyAttr
{
    eBeautyAttr_LoveHearts             = 1,//爱心数目
    eBeautyAttr_NextChatTime           = 2,//聊天时间
    eBeautyAttr_NextFreeGoldTime       = 3,//下次金币抽奖冷时间
    eBeautyAttr_NextFreeSilverTime     = 4,//下次银币抽奖时间
    eBeautyAttr_FightBeautyID          = 5,//出战美女id
    eBeautyAttr_FirstLotter            = 6,//第一次仙石抽奖
    eBeautyAttr_LotterItem             = 7,//稀有抽奖
    eBeautyAttr_FreeCnt                = 8,//免费抽奖次数 
};

struct SBeautyCFGEx:public SBeautyCFG
{
    void CopyFrom(SBeautyCFG& rBeautyCFG)
    {
        *((SBeautyCFG*)this)=rBeautyCFG;
    }
};

typedef std::shared_ptr<SBeautyCFGEx> SBeautyCFGExPtr;
typedef std::map<UINT16,SBeautyCFGExPtr> TMapBeautyCFGExPtr;

struct SBeautyLevelCFGEx:public SBeautyLevelCFG
{
    TVecUINT16 _vecItemType;
    void CopyFrom(SBeautyLevelCFG& rBeautyLevelCFG)
    {
        *((SBeautyLevelCFG*)this) = rBeautyLevelCFG;
    }

    UINT16 GetRandomItemType()
    {
        UINT16 dwMaxIndex =  _vecItemType.size();
        if(dwMaxIndex == 0)
        {
            return 0;
        }

        UINT16 dwSelect = rand()%dwMaxIndex;

        return _vecItemType[dwSelect];
    }

    bool IsItemType(UINT16 wItemType)
    {
        auto itr = find(_vecItemType.begin(),_vecItemType.end(),wItemType);
        return itr != _vecItemType.end();
    }

};

typedef std::shared_ptr<SBeautyLevelCFGEx> SBeautyLevelCFGExPtr;
typedef std::map<UINT32,SBeautyLevelCFGExPtr> TMapBeautyLevelCFGExPtr;

struct SBeautyLotteryCFGEx:public SBeautyLotteryCFG
{
    void CopyFrom(SBeautyLotteryCFG& rBeautyLotteryCFG)
    {
        *((SBeautyLotteryCFG*)this)=rBeautyLotteryCFG;
    }
};

typedef std::shared_ptr<SBeautyLotteryCFGEx> SBeautyLotteryCFGExPtr;
typedef std::map<UINT16,SBeautyLotteryCFGExPtr> TMapBeautyLotteryCFGExPtr;

typedef std::shared_ptr<SBeauty> SBeautyPtr;
typedef std::map<UINT16,SBeautyPtr>  TMapBeautyPtr;

//掉落库
struct SBeautyRareLotteryCFGEx:public SBeautyRareLotteryCFG
{
    SItemGenInfo oItemGenInfo;
    void CopyFrom(SBeautyRareLotteryCFG& rBeautyRareLotteryCFG)
    {
        *((SBeautyRareLotteryCFG*)this)=rBeautyRareLotteryCFG;
    }
};

typedef std::shared_ptr<SBeautyRareLotteryCFGEx> SBeautyRareLotteryCFGExPtr;
typedef std::vector<SBeautyRareLotteryCFGExPtr> TVecBeautyRareLotteryCFGExPtr;
typedef std::map<UINT16,TVecBeautyRareLotteryCFGExPtr> TDMapRareLotteryLoot;
typedef std::set<UINT16>  TSetRareItem;

struct SProbLottery
{
    UINT32 dwMinProb;
    SBeautyRareLotteryCFGExPtr pBeautyRareLotteryCFGExPtr;
    SProbLottery()
    {
        dwMinProb = 0;
    }
};

typedef std::vector<SProbLottery> TVecProbLottery;

struct SLootProb
{
    UINT32 dwTotleProb;
    TVecProbLottery vecProbLottery;
    SLootProb()
    {
        dwTotleProb = 0;
    }
};
typedef std::map<UINT16,SLootProb> TMapLootProb;

class CBeautyMgr 
{

public:
    CBeautyMgr(CPlayer& rPlayer);
    ~CBeautyMgr() {}
    static bool BeautyInit();
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(const SBeauty& rInfo, EDataChange eDataChanige = eOpUpdate);



     //接收：获取美女信息
    EBeautyRet OnGetBeatyInfo(shared_func<CBeautySvr::SGetBeatyInfoAck>& fnAck);

    //接收：结识美女
    EBeautyRet OnMeetBeauty( UINT16 wBeautyID);

    //接收：和美女聊天
    EBeautyRet OnChatBeauty( UINT16 wBeautyID);

    //接收：送美女礼品
    EBeautyRet OnSendPrizeBeauty(UINT16 wBeautyID,const NItemProt::TVecItemCount& vecItemCount);
    
    //接收：抽奖
    EBeautyRet OnLotteryBeauty(const ELotteryBeautyType eLotteryBeautyType,NItemProt::TVecItemGenInfo& vecItemGenInfo);
    
    //接收：美女出战
    EBeautyRet OnBeautyFight(UINT16 wBeautyID);
    
    void WriteBeautyLogToDB(UINT16 wBeautyID);

    //获取战斗美女
    bool GetBattleFighters(std::vector<IBattleFighterPtr>& vecBattleFighter); 
    //出战美女
    IBattleFighterPtr ToBattleFighter(const TVecFloat& allPetAttr); 

    //零点事件
    void OnMidNight();

    //亲密度改变
    void OnExpChange(SBeautyPtr pBeauty);

    SBeautyCFGExPtr GetBeautyCFG(UINT16 wBeautyID);
    SBeautyLevelCFGExPtr GetBeautyLevelCFG(UINT32 dwLevelID);
    SBeautyLevelCFGExPtr GetBeautyLevelCFG(UINT16 wBeautyID,UINT16 wLevel);
    SBeautyLotteryCFGExPtr GetBeautyLotteryCFG(UINT16 wPrizeType);
    
    SBeautyPtr GetBeauty(UINT16 wBeautyID);

    void AddLoveHearts(UINT32 dwCount);
    void SubLoveHearts(UINT32 dwCount);
    UINT32 GetLoveHearts();

    void SetNextChatTime(UINT32 dwTime);
    UINT32 GetNexChatTime();

    void SetNextFreeGoldTime(UINT32 dwTime);
    UINT32 GetNextFreeGoldTime();

    void SetNextFreeSilverTime(UINT32 dwTime);
    UINT32 GetNextFreeSilverTime();
    
    //第一次仙石抽奖
    void SetFirstGoldLotter(UINT32 dwTag);
    UINT32 GetFirstGoldLotter();

    //抽奖
    UINT32 GetRareItemID(UINT32 dwItemID);
    void   SetRareItemID(UINT32 dwItemID);

    //免费次数抽奖
    UINT32 GetFreeCnt();
    void   SetFreeCnt(UINT32 dwFreeCnt);



    //获取已经抽到的物品列表
    void GetTakedRareItem(TVecUINT16& vecItemID);

    //出战id
    void SetFightBeautyID(UINT16 wBeautyID);
    UINT16 GetFightBeautyID() const;

    void SetDirty();

    void ReBuildAttr();

    //获取美女id和等级
    void GetAppear(UINT16& wBeautyID,UINT8& byBeautyLevel)
    {
        wBeautyID = _wBeautyID;
        byBeautyLevel = _wBeautyLevel;
    }

    const TVecFloat& GetAttrVec() const { return _vecAttr; };

    void SendFirstGoldLotterPrize();

    //获取掉落
    void Loot(UINT32 dwDropID,TVecItemGenInfo& vecItems);

    //删掉掉落
    void DeleteDropItem(UINT16 wItemID);

    //删掉物品
    void RemoveDropItem(UINT16 wItemID,SLootProb& rLootProb);

    //设置掉落库
    void SetDropLoot(UINT32 dwDropID,TVecBeautyRareLotteryCFGExPtr& vecBeautyRareLotteryCFGExPtr);

    //初始化掉落库
    void InitDropLoot();

    //获取当前免费次数
    void OnGetLotteryFreeCnt();

    //登陆事件
    void OnLogin();

private:
    mutable TVecFloat _vecAttr;

    CPlayer&  _rPlayer;
    TMapBeautyPtr _mapBeautyPtr;

    //单独掉落库
    TMapLootProb _mapLootProb;

    UINT16 _wBeautyID;
    UINT16 _wBeautyLevel;

    //初始化个人掉落库
    bool   _bInitLotter;

    static TMapBeautyCFGExPtr        _mapBeautyCFGExPtr;
    static TMapBeautyLevelCFGExPtr   _mapBeautyLevelCFGExPtr;
    static TMapBeautyLotteryCFGExPtr _mapBeautyLotteryCFGExPtr;
    static TDMapRareLotteryLoot      _dmapRareLotteryLoot;
    static TSetRareItem              _setRareItem;
};

#endif // EXCHANGEMALLMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

