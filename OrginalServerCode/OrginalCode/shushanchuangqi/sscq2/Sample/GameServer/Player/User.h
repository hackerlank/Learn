/********************************************************************
//	Game Server Source File.
//	File name:	User.h
//	Created:	2011/05/30	10:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
*********************************************************************/

#pragma once
#include "Game2DBComm.h"
#include "Game2CenterComm.h"
#include "RoleInfoDefine.h"
#include "RoleEvent.h"
#include "Pack.h"
#include "Depot.h"
#include "TaskPkg.h"
#include "Var/Var.h"
#include "GameBuffManager.h"
#include "TimePointMgr.h"
#include "RoleEnterGameProt.h"
#include "BoostObject.h"
#include "PropInfo.h"


using namespace NRoleInfoDefine;
using namespace NProtoCommon;
using namespace NGame2DBComm;
using namespace NGame2CenterComm;
using namespace NRoleEvent;
using namespace NRoleEnterGameProt;
using namespace NPropInfo;

class CPlayer;
class CUser;
class CGameVar;

enum EUserState
{
	eUserNone,
	eUserInGame,
	eUserLeaveAway,
	eUserReplace
};

enum EPendMoneyType
{
	ePendMoneyNone,
	ePendMoneyGold,
	ePendMoneyDiamondGame,
	ePendMoneyDiamondBill,
	ePendMoneyGift,
	ePendMoneyCrystal,
};

static SPlatformParam s_sPlatformParam;

enum eLockType
{
    eLock_DujieUpgrade     = 1,
};

struct COpLock
{
   COpLock(CUser &rUser):_rUser(rUser){}
   bool AddLock(eLockType eLock, UINT8 byTime = 3);
   void UnLock(eLockType eLock);
   private:
   CUser &_rUser;
   map<eLockType,UINT32> _mapLock;

};

class CUser : public enable_shared_from_this<CUser>, public CPoolObj<CUser>, public CBoostObject
{
	friend class CUserMgr;
	friend class CGame2DBCommC;
	friend class CGame2CenterCommC;
	friend class CGMCommand;
public:
	DEF_NEW_DELETE(CUser);
	CUser(UINT64 qwUsrID);
	virtual ~CUser();

    void Init();

	UINT64 GetUserID() const { return _qwUsrID; }
	EUserState GetUserState() const { return _eUserState; }
	void SetUserState(EUserState eUserState);
	time_t GetCheckTime() const { return _tLastCheckTime; }
    time_t GetOffLineTime() const ;

	const char* GetCUserName() const { return GetUserName().c_str(); }
	const std::string& GetUserName() const;
	const std::string& GetRoleName() const { return GetUserName(); }
    void SetUserName(const std::string& name);
    const std::string GetFixdUserName() const;
    const char* GetFixdCUserName() const { return GetFixdUserName().c_str(); }

	UINT32 GetDBSvrID() const;
	UINT32 GetCenterSvrID() const;
	void SetSvrGroup(UINT16 wSvrGroup);

	bool SendPkg(const string& strPkg);
    bool SendCenterSvrPkg(const string& strPkg);
	void OnRecvFail();

	bool HasChange() const;
	void SetChange(bool bChange) { _bHasChange = bChange; }
	void ClearChange();

	bool IsAllSysOpen() const { return _bAllSysOpen; }
	void SetAllSysOpen(bool bAllSysOpen, bool bNotify = true);

    CPlayerPtr GetPlayer() { return _pPlayer; }
    CPlayer * GetpPlayer() {return _pPlayer.get();}
    void SetPlayer(const CPlayerPtr& pPlayer) { _pPlayer = pPlayer; }

    virtual UINT64 GetRoleID() const ;
    virtual UINT64 GetOwnerID() const { return GetRoleID(); }

    UINT8 GetLevel() const;
    void SetLotteryID(UINT16 wLotteryID) { _wLotteryID = wLotteryID; }
    UINT16 GetLotteryID() { return _wLotteryID; }
	bool CanRemove();

	bool HasMercenary(UINT16 wMonsterID);

	void NotifyUserProp();

	void OnEnter();
	void OnReplace(); //替换帐号
	void OnLeaveAway(); //暂时离开(不清除)
	void OnLeaveOff(ESaveType eSaveType); //离开游戏(完全清除)
	void OnSwitchMap(CGameMapPtr& pMap);

    CPack& GetPack();
    CDepot& GetDepot();
    CTaskPkg& GetTaskPkg();
    CStore* GetStoreByType(EStoreType eStoreType);
    CGameVar& GetVars();

#define SET_BIT(X,Y)     (static_cast<UINT64>(X) | (static_cast<UINT64>(1)<<static_cast<UINT64>(Y)))
#define GET_BIT(X,Y)     ((static_cast<UINT64>(X) & (static_cast<UINT64>(1)<<static_cast<UINT64>(Y))) >> static_cast<UINT64>(Y))
#define CLR_BIT(X,Y)     (static_cast<UINT64>(X) & ~(static_cast<UINT64>(1)<<static_cast<UINT64>(Y)))

#define SET_BIT_2(X,Y,V) (CLR_BIT_2(static_cast<UINT64>(X), static_cast<UINT64>(Y)) | static_cast<UINT64>(V)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(2)))
#define GET_BIT_2(X,Y)   ((static_cast<UINT64>(X) >> (static_cast<UINT64>(Y)*static_cast<UINT64>(2))) & static_cast<UINT64>(0x03))
#define CLR_BIT_2(X,Y)   (static_cast<UINT64>(X) & ~(static_cast<UINT64>(0x03)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(2))))

#define CLR_BIT_8(X,Y)   (static_cast<UINT64>(X) & ~(static_cast<UINT64>(0xFF)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(8))))
#define SET_BIT_8(X,Y,V) (CLR_BIT_8(static_cast<UINT64>(X),static_cast<UINT64>(Y)) | static_cast<UINT64>(V)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(8)))
#define GET_BIT_8(X,Y)   ((static_cast<UINT64>(X) >> (static_cast<UINT64>(Y)*static_cast<UINT64>(8))) & static_cast<UINT64>(0xFF))

#define CLR_BIT_16(X,Y)   (static_cast<UINT64>(X) & ~(static_cast<UINT64>(0xFFFF)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(16))))
#define SET_BIT_16(X,Y,V) (CLR_BIT_16(static_cast<UINT64>(X),static_cast<UINT64>(Y)) | static_cast<UINT64>(V)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(16)))
#define GET_BIT_16(X,Y)   ((static_cast<UINT64>(X) >> (static_cast<UINT64>(Y)*static_cast<UINT64>(16))) & static_cast<UINT64>(0xFFFF))

#define CLR_BIT_32(X,Y)   (static_cast<UINT64>(X) & ~(static_cast<UINT64>(0xFFFFFFFF)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(32))))
#define SET_BIT_32(X,Y,V) (CLR_BIT_32(static_cast<UINT64>(X),static_cast<UINT64>(Y)) | static_cast<UINT64>(V)<<(static_cast<UINT64>(Y)*static_cast<UINT64>(32)))
#define GET_BIT_32(X,Y)   ((static_cast<UINT64>(X) >> (static_cast<UINT64>(Y)*static_cast<UINT64>(32))) & static_cast<UINT64>(0xFFFFFFFF))

#define MAX_RANDNUM 9999
#define RANDVALUE_A 50
#define RANDVALUE_B 150
#define RANDVALUE_C 450
#define TWO_NOTIFY 2
#define FIVE_NOTIFY 5
#define TEN_NOTIFY  10
#define ON_OFF      1

    bool TryUnlockTrump(const TVecUINT16& rvecActiveID, const TVecUINT32& rvecActiveValue);

    // 序列化处理
    bool StoreToStream(EStoreType eStoreType, SStoreStream& stStoreStream);
    bool RoleToStream(SRoleStream& stRoleStream);
    bool GetFighters(TVecFighterSpecInfo& vecFighters);

	bool CanSubGoldOrCoupon(UINT32 dwCount, ECoinType eCoinType = eCouponCoin);
	bool SubGoldOrCoupon(UINT32 dwCoupon, ECoinType eCoinType = eCouponCoin, UINT16 toWhere=0,bool bNotify = true);

    //统一货币扣除接口
    UINT32 GetMoney(EMoneyType eMoneyType);
	bool CanAddMoney(EMoneyType eMoneyType,UINT32 dwCount);
	bool CanSubMoney(EMoneyType eMoneyType,UINT32 dwCount);
	bool AddMoney(EMoneyType eMoneyType,UINT32 dwCount,UINT16 fromWhere, bool bNotify = true);
	bool SubMoney(EMoneyType eMoneyType,UINT32 dwCount, NLogDataDefine::ItemTo toWhere, bool bNotify = true);
    void SetMoney(EMoneyType eMoneyType,UINT32 dwCount);
    void SynToCeneterNotify(EMoneyType eMoneyType, UINT32 dwValue);
    void WriteMoneyLog(EMoneyType eMoneyType, UINT32 dwCount, UINT16 fromTo, bool bIsFreeGold = false);

    //获取非零货币列表
    void GetMoneyList(TVecMoneyCount& vecMoneyCount);

    // 两种类型货币的兑换
    EExchangeResult ExchangeMoney(EPropType eSrcProp, EPropType eDestProp, UINT32 dwCount);

    //体力增加扣除
	bool CanSubAction(UINT32 dwAction);
	bool AddAction(UINT32 dwAction,UINT16 fromwhere=0);
	bool SubAction(UINT32 dwAction,UINT16 towhere=0, bool bNotify = true);

    UINT32 GetNation() const { return _byNation; }
    void SetNation(UINT32 byNation) { _byNation = byNation; }
    UINT32 GetGMLvl() const { return _byGMLvl; }
    void SetGMLvl(UINT32 byGMLvl) { _byGMLvl = byGMLvl; }
    UINT8 CalcVIPLevel();
    UINT32 GetTotalRecharge() const;
    void SetTotalRecharge(UINT32 dwTotalRecharge);
    UINT8 GetVIPLevel();
    void SetVIPLevel(UINT8 byLevel);
    void PHPSetVIPLevel(UINT8 byLevel);
    void SendVIPInfoToClt();
    bool OpenSelfMonthCard();
    void SendMonthCardAward();
    void SendShushanFoundInfo();
    bool CanDelShushanFoundIcon();
    bool HasTempVIPPrivilege();
    bool AutoOpenDepotByVIPUp();
    bool AutoAddTitleByVIPUp();
    bool AddTotalRechargeByLua(UINT16 wGoldID, UINT32 dwRecharge);
    bool AddTotalRecharge(UINT32 dwRecharge, bool bAddGold = true);
    void CheckVIPGrowthValue();
    void GoldConvertVIPGrowth(UINT32 dwUsedGold);
    void AddVIPGrowthValue(UINT32 dwValue = 0);

    //QQ黄钻等级设置
    void SetYelloDiamondLevel(UINT8 byLevel);
    UINT8 GetYelloDiamondLevel();

    const SPlatformParam& GetCurrentPlatformParam() const;
    const TVecPlatformParam& GetPlatformParam() const;
    void UpdateYD2DB(const SPlatformParam &,EDataChange) const;
    bool SetPlatformParam(const TVecPlatformParam &);
    void SetEnterString(const TVecString& vecString);
    bool PlatformParamFromDB(const TVecPlatformParam& rvecPlatform);
    bool IsSuperPlatform() const;
    bool IsYealyPlatform() const;
    bool IsYellowDiamond() const;

    UINT32 GetLoginTime() const { return _dwLoginTime; }
    void SetLoginTime(UINT32 dwLoginTime) { _dwLoginTime = dwLoginTime; }
	UINT32 GetOfflineTime() const { return _dwOfflineTime; }
    void SetOfflineTime(UINT32 dwOfflineTime) { _dwOfflineTime = dwOfflineTime; }
	UINT32 GetLockExpireTime() const { return _dwLockExpireTime; }
    void SetLockExpireTime(UINT32 dwLockExpireTime) { _dwLockExpireTime = dwLockExpireTime; }
	UINT32 GetForbExpireTime() const { return _dwForbExpireTime; }
    void SetForbExpireTime(UINT32 dwForbExpireTime) { _dwForbExpireTime = dwForbExpireTime; }
    void SetSign(const std::string& strSign);
    void SetMood(UINT16 wMood);

	void TimerCheck(time_t tNow);

    //19点事件仅在线玩家执行
    void OnDayReset(ETimePointType eType);

	//CMapHookSys& GetMapHook(){ return _oMapHookSys; }

	//角色地图同步
	void BroadcastUserSync(const string& strMsg, bool bNotifySelf = true);

	//跨服玩法
	void OnEnterToCrossSvr(const TVecString& vecParam);
	//从跨服服务器回来
	void OnEnterFromCrossSvr(const TVecString& vecParam);
	//重新进入跨服服务器 内存中玩家要存在
	void OnReEnterCrossSvr();

    void SyncData(RoleBaseInfo& info);
    UINT64 Test64(UINT64 p);
    

    /*
    // Buff相关处理
    virtual EBuffType GetBuffType() const { return eBTUser; }
    virtual void UpdateBuff2DB(const SBuffInfo& rBuffInfo, EDataChange eDataChange);
    virtual void OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo);
    */

    //播放剧情
    void NoticeStory(UINT16 wStoryID,UINT8 byType,UINT32 dwParam);

    void Boost(UINT32 dwMode);
    void RobotBoost(UINT32 dwMode);
    void AddFashionItemForRobot();
    virtual EBoostObjectType GetType() const {return eBOTUser;}
    virtual void Super();

    void MoneySuper();
    void VIPSuper();


    //发送客户端提示消息
    void SendSysMsg(UINT32 dwMsgID); 

    CBubbleOwnerPtr GetBubbleOwner() { return _pBubbleOwner;}

    //防沉迷
    void  SetIndulge(bool bIndulge);
    void  SetIndulgeRate(UINT32 dwIndulgeRate);
    double GetIndulgeRate();
    void  UpdateIndulgeStatus();
    void  GMAddIndulgeTime(UINT32 dwTime);
    //九疑鼎相关
    void ActiveTripodFire(UINT16 wFireID);

    UINT32 ToSize();

    COpLock& GetOpLock() { return _opLock; }
    void AddIconByLua(UINT16 wIcon);
    void DelIconByLua(UINT16 wIcon);

    void FixQQAlarmSuc();
private:
    UINT32& GetMoneyVarible(EMoneyType eMoneyType);

protected:
	UINT64 _qwUsrID;
	UINT32 _dwRecvFailCount;
	UINT8 _byCampForDB;			//DB中保存的阵营ID
	EUserState _eUserState;
	time_t _tLastCheckTime;
	time_t _tLastSaveTime;		//上一次保存角色数据的时间
	UINT16 _wUsrDataVer;		//玩家数据版本
	UINT16 _wSvrGroup;			//当前所属的服务器组
	bool _bAllSysOpen;
    CPlayerPtr _pPlayer;

	UINT8 _byNation;
    UINT8 _byGMLvl;             // GM权限,参见GMSystem.h
    UINT8 _byVIPLevel;          // VIP等级
    UINT8 _byYelloDiamondLevel;  // QQ黄钻等级
	UINT32 _dwLoginTime;        // 上次登陆时间
    UINT32 _dwOfflineTime;      // 上次下线时间
    UINT32 _dwLockExpireTime;   // 被封禁结束时间
    UINT32 _dwForbExpireTime;   // 被禁言结束时间

    UINT32 _dwNoMoney;          //无效货币类型标志

    CPack _oPack;               // 包裹
    CDepot _oDepot;             // 仓库
    CTaskPkg _oTaskPkg;         //任务
    CVar _oVars;                //所有变量
    COpLock _opLock;

	bool _bHasChange;
	bool _bHasMiscChange;
    CBubbleOwnerPtr        _pBubbleOwner;   // 气泡管理

    //
    bool _bIndulge;               //是否防沉迷
    time_t _tIndulgeTime;        //计时起点
    time_t _tDiffTime;
    time_t _tAddOnLineTime;
    UINT16 _wIncome;             //防沉迷收益
    UINT32 _dwKickTime;
    //保存玩家黄钻信息
    TVecPlatformParam _vecPlatformParam;
    UINT32 _dwPlatformIndex;

    TVecString _vecEnterString;
    UINT16 _wLotteryID; //玩家抽奖ID
    
};

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

