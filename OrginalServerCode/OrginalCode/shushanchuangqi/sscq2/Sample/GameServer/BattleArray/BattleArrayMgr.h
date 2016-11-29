#ifndef BATTLEARRAYMGR_H_
#define BATTLEARRAYMGR_H_

#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "BattleArray.h"
#include "BattleArrayCFG.h"
#include "BattleArrayLevelCFG.h"
#include "BattleArrayPriceCFG.h" 
#include "ItemProt.h"
#include "BattleArraySvr.h"

using namespace NProtoCommon;
using namespace NRoleInfoDefine;
using namespace NItemProt;
using namespace NBattleArray;
enum EBattleArrayLevelType
{
    eBattleArrayLevelType_invalid, //无效
    eBattleArrayLevelType_eye = 1,     //阵眼
    eBattleArrayLevelType_positon, //阵位
    eBattleArrayLevelType_End,
};


enum EBattleArraySave
{
    //上线后下面的序号不能改变
    //wType = eAutoStore_BattleArray_BuyAtkCnt
    eBattleArraySave_TotleCnt = 0, //购买总次数
    eBattleArraySave_BuyCnt   = 1, //当天购买次数
    eBattleArraySave_FailCd   = 2, //战败cd
    eBattleArraySave_FirstAttack = 3, //首次p破阵眼
    eBattleArraySave_End      =100, //100以上是阵图id
};
struct SBattleArrayCFGEx:public SBattleArrayCFG
{
    TVecItemGenInfo vecPassPrize;
    void CopyFrom(SBattleArrayCFG& rBattleArrayCFG)
    {
        *((SBattleArrayCFG*)this)=rBattleArrayCFG;
    }
};

struct SBattleArrayLevelCFGEx: public SBattleArrayLevelCFG
{
    TVecUINT16 vecStar;
    void CopyFrom(SBattleArrayLevelCFG& rBattleArrayLevelCFG)
    {
        *((SBattleArrayLevelCFG*)this)= rBattleArrayLevelCFG;
    }
};

typedef std::shared_ptr<SBattleArrayCFGEx> SBattleArrayCFGExPtr;
typedef std::map<UINT16,SBattleArrayCFGExPtr> TMapBattleArrayCFGExPtr;
typedef std::shared_ptr<SBattleArrayLevelCFGEx> SBattleArrayLevelCFGExPtr;
typedef std::map<UINT32,SBattleArrayLevelCFGExPtr> TMapBattleArrayLevelCFGExPtr;

typedef std::vector<SBattleArrayPriceCFG>   TVecBattleArrayPriceCFG;

class CPlayer;
typedef std::shared_ptr<SBattleArrayDBInfo> SBattleArrayDBInfoPtr;
typedef std::map<UINT16,SBattleArrayDBInfoPtr> TMapBattleArrayDBInfoPtr;
class CBattleArrayMgr:public CPoolObj<CBattleArrayMgr>  
{

public:
    CBattleArrayMgr(CPlayer& rPlayer);
    ~CBattleArrayMgr() {}
    static bool BattleArrayInit();
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(const SBattleArrayDBInfo& rInfo, EDataChange eDataChanige = eOpUpdate);

    //获取阵配置
    SBattleArrayCFGExPtr GetBattleArrayCFG(UINT16 wBattleArrayID);

    //获取阵图配置
    SBattleArrayLevelCFGExPtr GetBattleArrayLevelCFG(UINT32 dwBattleArrayLevelID);

    void OnGetBattleArray(shared_func<CBattleArraySvr::SGetBattleArrayAck>& fnAck);

    EBattleArrayRet OnAttackBattleArray(UINT32 dwBattleArrayLevelID);

    EBattleArrayRet OnSweepBattleArray(UINT32 dwBattleArrayLevelID);

    EBattleArrayRet OnBattleArrayTakePrize(UINT16 wBattleArrayID);

    bool IsFinish(UINT16 wBattleArrayID);

    SBattleArrayDBInfoPtr GetBattleArray(UINT16 wBattleArrayID);

    //获取攻击阵图次数
    UINT32 GetAttackCnt(UINT32 dwBattleArrayLevelID);

    //增加攻击阵图次数
    void   AddAttackCnt(UINT32 dwBattleArrayLevelID,UINT32 dwAdd = 1);

    //设置攻击阵图次数
    void   SetAttackCnt(UINT32 dwBattleArrayLevelID,UINT32 dwValue);
    
    //设置攻击阵图最小轮数
    void   SetMinTurns(UINT32 dwBattleArrayLevelID,UINT32 dwMinTurns,SBattleArrayLevelCFGExPtr pBattleArrayLevelCFGEx);

    //获取攻击阵图次数最小轮数
    UINT32 GetMinTurns(UINT32 dwBattleArrayLevelID);


    //获取总次数
    UINT32 GetTotleAtkCnt();

    //设置总次数
    void   SetTotleAtkCnt(UINT32 dwCount);

    //获取购买次数
    UINT32 GetTotleBuyCnt();

    //设置购买次数
    void   SetTotleBuyCnt(UINT32 dwCount);

    //获取当天购买次数
    UINT32 GetDayTotleBuyCnt();

    //设置当天购买次数
    void  SetDayTotleBuyCnt(UINT32 dwCount);


    //最大攻击次数
    UINT32 GetMaxTotleAtkCnt();

    //最大可购买次数
    UINT32 GetMaxBuyCnt();

    //
    UINT32 GetFailCD();
    void   SetFailCD(UINT32 dwFailCD);

    //第一次破阵眼
    bool   IsFirstAttack();
    void   SetFirstAttack();

    //查询价格
    EBattleArrayRet OnGetBuyAtkCountPrice(UINT32 dwCount,shared_func<CBattleArraySvr::SGetBuyAtkCountPriceAck>& fnAck);

    //购买攻击次数
    EBattleArrayRet OnBuyAtkCount(UINT32 dwCount,shared_func<CBattleArraySvr::SBuyAtkCountAck>& fnAck);

    //客户端发送战斗结束消息
    void OnFighterEnd();

    //零点消息
    void OnMidNight();


public:
    static TVecBattleArrayPriceCFG _vecBattleArrayPriceCFG;
private:
    CPlayer&  _rPlayer;
    TMapBattleArrayDBInfoPtr _mapBattleArrayPtr;
    
    //消息提示保存
    TVecItemGenInfo _oPendVecItemGenInfo;

    //cd
    UINT32 _dwAttackCd;

    //价格信息
    //static TVecBattleArrayPriceCFG _vecBattleArrayPriceCFG;

    static TMapBattleArrayCFGExPtr _mapBattleArrayCFGExPtr;
    static TMapBattleArrayLevelCFGExPtr _mapBattleArrayLevelCFGExPtr;
};

#endif // EXCHANGEMALLMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

