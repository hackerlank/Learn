
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Creature.h"
#include "RoleInfoDefine.h"
#include "RoleEvent.h"
#include "ActionBase.h"
#include "DungeonPkg.h"
#include "GatherProtSvr.h"
#include "ProtoCommon.h"    // XXX: For ESexType
#include "BattleGS.h"       // XXX: For SPlayerFeaturePtr
#include "GameBuffManager.h"
#include "GroupTaskPkg.h"
#include "YaMenTaskPkg.h"
#include "TimePointMgr.h"
#include "ActivityPkg.h"
#include "TitlePkg.h"
#include "EventMgr.h"
#include "GuildProt.h"
#include "WondActMgr.h"
#include "Battle.h"
#include "SignInPkg.h"
#include "LoginPkgMgr.h"
#include "Shushanweiwei.h"
#include "BoostObject.h"
#include "ShengLing.h"
#include "Fenbaoyan.h"

namespace NGame2CenterComm { struct SUserEnterInfo; }
namespace NItemProt { struct SItemGenInfo; }

using namespace NRoleEvent;
using namespace NRoleInfoDefine;
using namespace NItemProt;
using namespace NGatherProt;
using namespace NProtoCommon;
using namespace NBattleGS;
using namespace NGuildProt;
//using namespace NRoleEnterGameProt;

class CDungeon;
struct DgnOutConfig;
class CStore;

//角色状态
enum EPlayerState
{
    ePlayerNone,
    ePlayerBorn,
    ePlayerInGame,
    ePlayerJump,
    ePlayerSwitch,
    ePlayerLeave
};
enum 
{
    PLAYER_BASESPEED = 360,
};

enum PendSource
{
    PendALL,
    PendBattle,
    PendDgn,
};

union UDemonTowerPrize
{
    struct
    {
        UINT16 wTopPrizeID;
        UINT16 wLayerPrizeID;
    } oPrizeID;
    UINT32 dwPrizeID;
};

class CUser;

class CPlayer : public CCreature, public CPoolObj<CPlayer>, public CBoostObject
{
    public:
        CPlayer(UINT64 qwRoleID, const CUserPtr& pUser);
        virtual ~CPlayer();

        virtual bool Init();
        virtual EObjType GetObjType() const { return eObjPlayer; }
        virtual UINT64 GetUserID() const;
        virtual UINT64 GetCreatureID() const { return _qwRoleID; }
        virtual bool IsDead() const { return HasBuff(eDeadInDgn); }
        virtual UINT64 GetRoleID() const { return _qwRoleID; }
        virtual UINT64 GetOwnerID() const { return _qwRoleID; }
        virtual float GetSpeedForWalker() const {return float(_dwSpeed)/60; }
        EPlayerState GetPlayerState() const { return _ePlayerState; }
        void SetPlayerState(EPlayerState ePlayerState){ _ePlayerState = ePlayerState; }
        virtual void OnDie(CCreature& rKiller);

        ESexType GetSex() const { return _sBaseInfo.eSex;}

        bool IsRobot();
        CUser& GetUser();
        virtual CUserPtr GetUserPtr() const;
        CUser * GetpUser() {return _pUser.lock().get();}

        void Init888Coupon(CUser& rUser);
        virtual void OnEnterGhost() {/*TODO:*/}

        bool SendPkg(const string& strPkg);
        bool SendCenterSvrPkg(const string& strPkg);
        void GetPlayerAppear(SPlayerAppear& appear);
        SPlayerFeaturePtr GetAppearFeature();
        SPlayerFeatureWithBuffPtr GetBattleAppear(EBattleType eBattleType);
        bool IsOnActiveMap() const;

        virtual bool StopMove(const SPoint& rPoint, float fDir);

        bool CanRemove();
        void OnEnter();
        void OnLeaveAway();
        void OnLeaveOff();
        void OnReplace();

        UINT16 GetCurMapID() const { return _wMapID; }
        void SetCurMapID(UINT16 wMapID);
        bool LeaveDgn(bool bTransDB,const DgnOutConfig& rOutConfig);
        void EnterDgn(const CDungeon* pDungeon,bool bTransDB);
        CDungeonPtr GetDgn();
        CDungeon * GetpDgn() { return GetDgn().get();}
        UINT64 GetCurNpcID() const { return _qwCurNpcID; }
        void SetCurNpcID(UINT64 qwCurNpcID) { _qwCurNpcID = qwCurNpcID; }

        UINT16 GetDgnID() const { return _sBaseInfo.dwDgnTypeID; }
        UINT16 GetDgnMapID() const { return _sBaseInfo.wDgnMapId;}
        float GetDgnfX() const { return _sBaseInfo.fDgnfX;}
        float GetDgnfY() const { return _sBaseInfo.fDgnfY;}
        UINT64 GetDgnInstID() const { return _sBaseInfo.qwDgnId; }
        bool IsInDungeon();
        const std::string& GetOpenId() const { return _sBaseInfo.szOpenId; }
        const std::string& GetCreateIP() const { return _sBaseInfo.strCreateIP; }
        const std::string& GetLoginIP() const { return _sBaseInfo.strLoginIP; }

        void SetIndulgeLoginTime(UINT32 dwTime) { _sBaseInfo.dwIndulgeKickTime = dwTime; }
        UINT32 GetIndulgeLoginTime() { return _sBaseInfo.dwIndulgeKickTime; }
        UINT32 GetCreateTime() const { return _sBaseInfo.dwCreateTime; }  //创角时间

        bool JumpMap(UINT16 wMapID, const SPoint& rDestPoint,UINT16 wJumpID =0);
        bool JumpMap(CGameMapPtr& rDestMap, const SPoint& rDestPoint,UINT16 wJumpID =0);
        bool JumpMap(CGameMapPtr& rDestMap, const SPoint& rDestPoint,UINT16 wJumpID, bool bForce);
        bool JumpServer(UINT16 wMapID, const SPoint& rDestPoint);
        bool JumpToCrossServer(const TVecString& vecParam);
        bool JumpFromCrossServer(const TVecString& vecParam = TVecString());

        bool PHPSetLevel(UINT16 wLevel);

        bool LoadFromDB(const NRoleInfoDefine::RoleDataInfo& Info);
        void UpdateBaseInfo2DB();
        void UpdateBaseInfo2DB1();
        UINT8 GetColor();
        void OnColorChanged(UINT8 byOldColor);

        const RoleBaseInfo & GetBaseInfo(){ return _sBaseInfo;}
        void  SetBaseInfo(const RoleBaseInfo & _sInfo){_sBaseInfo = _sInfo;}
        RoleBaseInfo & GetModifyBaseInfo(){ return _sBaseInfo;} 

        bool AddExp(UINT64 qwExp, bool bNotify = true);
        bool SubExp(UINT64 qwExp, bool bNotify = true);

        virtual UINT8 GetLevel() const;
        virtual void SetLevel(UINT8 byLevel);

        inline UINT64 GetExp() const { return _sBaseInfo.qwExp; }

        void OnLevelChanged(UINT8 byOldLevel = 0);
        void TryUnlockRankData(UINT8 byOldLevel);

        void NotifyLevelUp();

        bool HasAcceptedMonsterTask(CMonster& rMonster);
        bool CheckFinishMonsterTask(CMonster& rMonster, UINT16 wFinishID);

        void UpdateLevelRank(bool bCached) const;
        void UpdateBattlePointRank() const;

        // XXX: 将相关
        void SetMainFighter(const CFighterPtr& pFighter);
        CFighterManagerPtr& GetFighterManager() { return _pFighterManager; }
        const CFighterManagerPtr& GetFighterManager() const { return _pFighterManager; }
        CHeroFighterPtr GetMainFighter();
        CHeroFighterPtr GetMainFighter() const;
        UINT16 GetPlayerFighterID() const;
        CFighterPtr GetFighterByInstID(UINT64 qwFighterID);
        CFighterPtr GetFighterByID(UINT16 wFighterID);
        bool HasFighter(UINT16 wFighterID);
        bool AddFighterFromDB(CFighterPtr& pFighter);
        UINT64 GetBattleFighterList(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType=EBTINVALID);
        bool RecruitFighterByForce(UINT16);

        //保存当前战斗散仙数据
        void SaveBattleFighterInfo(EBattleType eBattleType,TVecBattleFighterPtr& vecBattleFighter);

        IBattleFighterPtr GetSceneFighter();
        bool IsInTeam() {return _bInTeam;}
        void SetInTeam(bool bInTeam){_bInTeam = bInTeam;}
        UINT32 GetCurrHP();
        UINT32 GetMaxHP();
        UINT32 GetMaxHP2();
        void RegenAllHP();  //恢复满血
        bool RecoverFighters(TVecBattleFighterPtr& vecBattleFighter);     //恢复当前属性
        void AddCurrHP(UINT32 dwHP);
        void AddCurrHPPer(float fFactor);
        UINT32 GetBattlePoint() const;                //获取玩家的总战斗力

        void ClearDgnInfo();
        //void GetEnterGameDataForClient(RoleEnterGameData & info);
        void GetUserCenterInfo(NGame2CenterComm::SUserEnterInfo &info);
        void AddOwnTitle(UINT16 wTitle);//增加拥有的头衔
        void DelOwnTitle(UINT16 wTitle);//删除拥有的头衔
        void GetOwnTitle(TVecUINT16 &vecOwnTitle);//获取拥有的头衔
        void AddEquipTitle(UINT16 wTitle);//增加装备的头衔
        void DelEquipTitle(UINT16 wTitle);//删除装备的头衔
        void GetEquipTitle(TVecUINT16 &vecEquipTitle);//获取装备的头衔
        bool HasOwnTitle(UINT16 wTitle);//检测是否拥有该头衔
        bool HasEquipTitle(UINT16 wTitle);//检测是否装备该头衔

        bool CheckIconIsOpen(UINT16 wIcon);//检查功能是否打开
        void OpenIcon(UINT16 wIcon);//开启一个功能
        bool DelIcon(UINT16 wIcon);//关闭一个功能
        void GetOpenIcon(TVecUINT16 &vecIcon,bool bActivity);//获取开放的功能
        bool IconIsClose(UINT16 wIcon);//获取已经关闭的功能

        // 延迟发放的资源
        void PendDrop(TVecItemGenInfo &vecItem,TVecResource& vecSource,UINT8 bySource);
        void PendParam(UINT8 bySource,UINT32 dwValue, UINT32 dwParam);

        void CheckLastPend(UINT8 bySource = PendALL);
        void SetSign(const std::string& strSign);
        void SetMood(UINT16 wMood);
        void SetGuide(const std::string& strGuide);

        void SetYDLevel(UINT8 byLevel);

        //获得动作管理器
        CActionManager& GetActionManager(){ return _sActionManager; }
        void OnRecv_GatherReq(UINT32 dwGatherId,shared_func<CGatherProtSvr::SGatherReqAck>& fnAck);
        void OnRecv_CancelGather(shared_func<CGatherProtSvr::SCancelGatherAck>& fnAck);
        void OnRecv_GetGatherInfo(shared_func<CGatherProtSvr::SGetGatherInfoAck>& fnAck);
        void SetPackCapacity(UINT16 wCapacity);
        void SetDepotCapacity(UINT16 wCapacity);
        CDungeonPkg& GetDgnPkg(){return _DgnPkg;}

        //采集相关
        void SetGatherID(UINT32 dwGatherID);
        UINT32 GetGatherID();

        //0点在线玩家执行这事件(不在线不触发)
        void OnMidNight(ETimePointType eType);

        //0点或者是隔天登陆调用
        void OnDayPass();

        //镇妖塔相关

        //镇妖塔通关层数
        UINT32 GetTopDemonFloorID();
        void SetTopDemonFloorID(UINT32 dwDemonFloorID);

        //锁妖塔采集相关
        void  SetDemonFloorGather();
        void  OnDemonFloorGathered();
        bool  IsSpawGather();

        //镇妖塔领奖层数
        UINT32 GetPrizeDemonFloorID();
        void SetPrizeDemonFloorID(UINT32 dwDemonFloorID);

        //镇妖塔已领奖层数
        UINT32 GetLayerPrizeDemonFloorID();
        void SetLayerPrizeDemonFloorID(UINT32 dwDemonFloorID);

        void AddFashionItemForRobot();
        void Boost(UINT32 dwMode); // 新手一键加速
        void RobotBoost(UINT32 dwMode); // 机器人测试
        void Super(UINT32 dwMode); // 变成超级牛逼的号
        bool CheckStarAwardIsGet(UINT16 wStarAward);//检查星级奖励是否打开
        void AddStarAwardInfo(UINT16 wStarAward);//开启一个星级奖励
        void GetStarAwardInfo(TVecUINT16 &vecStarAward);//获取开放的星级奖励


        //--qf-- 2014/05/29
        void SetDemonTowerInstID(UINT64 qwInstID)
        {
            _qwDemonToweInstID = qwInstID;
        }
        UINT64 GetDemonTowerInstID()
        {
            return _qwDemonToweInstID;
        }
        void SetDemonTowerFloorID(UINT32 dwFloorID)
        {
            _dwCurTowerFlorrID = dwFloorID;
        }
        UINT32 GetDemonTowerFloorID()
        {
            return _dwCurTowerFlorrID;
        }

        CSoulSpaceMgrPtr GetSoulSpaceMgr()
        {
            return _pSoulSpaceMgr;
        }

        CHorseMgrPtr GetHorseMgr()
        {
            return _pHorseMgr;
        }

        CTreasureHuntPtr GetTreasureHunt()
        {
            return _pTreasureHunt;
        }

        CMoneyTreePtr GetMoneyTree()
        {
            return _pMoneyTree;
        }

        CRegisterSevenDaysPtr GetRegisterSevenDays()
        {
            return _pRegisterSevenDays;
        }

        CGuardEMeiPtr GetGuardEMei()
        {
            return _pGuardEMei;
        }

        CAchievementMgrPtr GetAchievementMgr()
        {
            return _pAchievementMgr;
        }

        CCollectionMgrPtr GetCollectionMgr()
        {
            return _pCollectionMgr;
        }

        CAttackedMgrPtr GetAttackedMgr()
        {
            return _pAttackedMgr;
        }

        CExchangeShopMgrPtr GetExchangeShopMgr()
        {
            return _pExchangeShopMgr;
        }

        CEnergyMgrPtr GetEnergyMgr()
        {
            return _pEnergyMgr;
        }

        CLevelPrizeActPtr GetLevelPrizeAct()
        {
            return _pLevelPrizeAct;
        }

        CLoginPkgMgrPtr GetLoginPkgMgr()
        {
            return _pLoginPkgMgr;
        }
        CShushanweiweiPtr GetShushanweiwei()
        {
            return _pShushanweiwei;
        }
        CShengLingPtr GetShengLing()
        {
            return _pShengLing;
        }
        CFenbaoyanMgrPtr GetFenbaoyan()
        {
            return _pFenbaoyan;
        }
        CShopItemMgrPtr GetShopItemMgr()
        {
            return _pShopItemMgr;
        }

        CDayTargetMgrPtr GetDayTargetMgr()
        {
            return _pDayTargetMgr;
        }

        CAutoStoreMgrPtr GetAutoStoreMgr()
        {
            return _pAutoStoreMgr;
        }

        CBattleArrayMgrPtr GetBattleArrayMgr()
        {
            return _pBattleArrayMgr;
        }

        CBeautyMgrPtr GetBeautyMgr()
        {
            return _pBeautyMgr;
        }
        CFightFormationMgrPtr GetFightFormationMgr()
        {
            return _pFightFormationMgr;
        }

        CFightHeroInfoMgrPtr GetFightHeroInfoMgr()
        {
            return _pFightHeroInfoMgr;
        }

        CEventMgrPtr GetEventMgr()
        {
            return _pEventMgr;
        }

        void OnEvent(const EventType eEvent, const TVecINT32& vecParam,const string& strParam = "",bool bLog = true,UINT32 dwEventTime = 0)
        {
            if (_pEventMgr)
                _pEventMgr->OnEvent(eEvent, vecParam, strParam, bLog,dwEventTime);
        }

        //重新计算行走速度
        void CalSpeed(bool bInit = false);

        //活动相关
        void AddActID(UINT16 wID);
        void DelActID(UINT16 wID);
        void RegisterAct();

        void LearnSkill(UINT32 dwSkillID);
        void FitherToMonster(UINT16 wMonsterGroup);

        // Buff相关
        virtual EBuffType GetBuffType() const { return eBTPlayer; }
        virtual void UpdateBuff2DB(const SDBBuffInfo& rDBBuffInfo, EDataChange eDataChange);
        virtual void OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo);
        EBuffOpResult AddBuffLua(UINT16 wBuffID);

        //守卫峨眉相关
        void GetGuardEMeiFighterID(TVecUINT16& vecFgtID);

        //弹窗
        void ElasticFrame(UINT16 wMsgID);
        bool UnlockPack();
        void CalcPackNextUnlockTime(CStore& rStore);
        UINT32 GetPackUnlockOfflineTime();
        bool InitAfterLoaded(bool bReEnter);
        bool RegistInit();
        UINT32 GetPackNextUnlockTime(bool bLoginSet = false);
        void GetPackUnlockAttr(TVecFloat& rvecAttr);
        void TimerCheck(UINT32 dwNow); // XXX: check one sceond

        //师门任务
        CGroupTaskPkg& GetGroupPkg(){return _GroupTaskPkg;}
        CYaMenTaskPkg& GetYaMenPkg(){return _YaMenTaskPkg;}
        CActivityPkg&  GetActivityPkg() {return _ActivityPkg;}
        CTitlePkg&  GetTitlePkg() {return _TitlePkg;}
        CSignInPkg& GetSignInPkg() {return _SignInPkg;}
        bool IsTrumpActived(UINT16 wItemID) const;
        UINT32 GetTotalActivity();
        void   SetTotalActivity(UINT32 dwTotalActivity);
        void  Relive();
        UINT64 GetSitToGatherPlayer();
        void  SetSitToGatherPlayer(UINT64 qwRoleID,bool bNotice);
        void  DoSitOnLine();
        //event
        //void TiggerEvent(const UINT32 dwEventId,const TVecINT32& _vecParam,const EEventCondition eEventCondition,const SEventCFGExPtr pEventCFGExPtr);

        void SetAchievementLevel(UINT16 wAchievementLevel);
        UINT16 GetAchievementLevel();
        void SetCollectionLevel(UINT16 wCollectLevel);
        UINT16 GetCollectionLevel();

        // Guild

        UINT16 GetGuildLevel() const;
        void   SetGuildLevel(UINT16 wLevel);

        const string& GetGuildName() const;
        void SetGuildName(const string& strGuildName);

        //帮派科技信息 GuildID,TechType,TechLvl
        void SetGuildTechInfo(const TVecGuildTechInfo& vecTech) { _vecGuildTech = vecTech; }
        const TVecGuildTechInfo& GetGuildTechInfo() const { return _vecGuildTech; }

        //buffer
        virtual void BufferRebuildAttr();

        //设置战斗类型
        void SetBattleType(EBattleType eFightType);
        EBattleType GetBattleType();

        //保存离开的正常地图坐标
        bool SaveLastNormalMap();
        //回到先前的普通地图
        bool ReturnLastNormalMap();

        UINT32 GetLastOfflineTime() { return _sBaseInfo.dwOfflineTime;  }
        void  BeginReload(){_bInLoad = true;}

        void DoOffLineEvent();//处理数据库传来的离线事件
        void DoOffLineEventNotice(const SEventOffLine &sEvent);
        static void AddOffLineEvent(const TVecUINT64& vecRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam = "");//蒋离线时间放入数据库
        static void AddOffLineEvent(UINT64 qwRoleID,const EventType eEvent, const TVecINT32& vecParam,const string& strParam = "");
        void SaveOffLineEvent(const TVecEventOffLine& vecOffEvent);

        //获取从角色创建到现在的天数，创建当天为第1天
        UINT32 GetFromCreateDays();

        //发送客户端提示消息
        void SendSysMsg(UINT32 dwMsgID);

        bool IsBattleCD();
        void SetBattleCD();
        UINT32 GetBattleCDTime();
        void CleanBattleCD();
        void DoCheckErrItem();
        NItemProt::TVecItem&  GetErrItem(){ return _vecErrItem;}
        void SaveMapPoint(UINT16 wMapId,float fx,float fy);
        //客户端发送战斗结束消息
        void OnFighterEnd();

        virtual EBoostObjectType GetType() const{ return eBOTPlayer;}

        virtual void Super(); // 变成超级牛逼的号

        //计算空间大小
        UINT32 ToSize();

        //获取礼包使用次数
        UINT32 GetItemUserCount(UINT16 wItemID);

        //设置礼包使用次数
        void   SetItemUserCount(UINT16 wItemID,UINT32 dwCount);


    private:
        void SetDgnID(UINT16 wDgnID);
        void SetDgnInstID(UINT64 dwInstID);
        void SynBaseInfo();
        //RobotBoost 
        ////////////////////////////////////
        void RobotTrumpBoost(UINT32 dwMode);
        void RobotFormationBoost(UINT32 dwMode);
        void RobotHorseBoost(UINT32 dwMode);
        void RobotFashionBoost(UINT32 dwMode);
        ////////////////////////////////////

        void LevelBoost(UINT32 dwMode);
        void LevelSuper(UINT32 dwMode);

        void TrumpBoost(UINT32 dwMode);
        void TrumpSuper(UINT32 dwMode);

        void FormationBoost(UINT32 dwMode);

        void FighterBoost(UINT32 dwMode);
        void FighterSuper(UINT32 dwMode);

        void DoLastParam(UINT8 bySource,UINT32 dwValue,UINT32 dwParam = 0);

    private:
        UINT64 _qwRoleID;

        CUserWtr _pUser;

        UINT16 _wMapID;

        UINT64 _qwCurNpcID;

        EPlayerState _ePlayerState;

        UINT32 _dwSpeed;

        RoleBaseInfo _sBaseInfo; 

        map<UINT8,TVecResource>  _mapPendRes;

        CDungeonPkg _DgnPkg;

        CActionManager _sActionManager;              //玩家持续处于作某件事情的：如扫荡。。

        CFighterManagerPtr  _pFighterManager;        //将管理器
        CHeroFighterWtr     _pMainFighter;           //主将
        CSoulSpaceMgrPtr    _pSoulSpaceMgr;          //魄空间
        CHorseMgrPtr        _pHorseMgr;              //坐骑
        CAchievementMgrPtr  _pAchievementMgr;        //成就
        CCollectionMgrPtr   _pCollectionMgr;         //收藏 
        CAttackedMgrPtr     _pAttackedMgr;           //被攻击列表
        CExchangeShopMgrPtr _pExchangeShopMgr;       //兑换商店
        CEnergyMgrPtr       _pEnergyMgr;             //体力
        CLevelPrizeActPtr   _pLevelPrizeAct;
        CLoginPkgMgrPtr     _pLoginPkgMgr;
        CShushanweiweiPtr   _pShushanweiwei;
        CShengLingPtr       _pShengLing;
        CFenbaoyanMgrPtr    _pFenbaoyan;
        CEventMgrPtr        _pEventMgr;
        CShopItemMgrPtr     _pShopItemMgr;
        CDayTargetMgrPtr    _pDayTargetMgr;
        TVecGuildTechInfo   _vecGuildTech;           //玩家帮派科技信息(CenterServer同步过来)
        CTreasureHuntPtr    _pTreasureHunt;          //寻宝
        CGuardEMeiPtr       _pGuardEMei;             //守卫峨眉
        CAutoStoreMgrPtr    _pAutoStoreMgr;
        CBattleArrayMgrPtr  _pBattleArrayMgr;
        CBeautyMgrPtr       _pBeautyMgr;
        CFightFormationMgrPtr   _pFightFormationMgr;
        CFightHeroInfoMgrPtr    _pFightHeroInfoMgr;
        CMoneyTreePtr           _pMoneyTree;             //摇钱树
        CRegisterSevenDaysPtr   _pRegisterSevenDays;     //注册七日目标

        // XXX: 不同功能的延迟发放可以用不同的变量，最好不要共用这个
        map<UINT8,TVecItemGenInfo> _mapLastLoot; //延迟发放掉落通知，物品已经以不通知的方式加入背包

        //逻辑变量，不进数据库
        //采集
        map<UINT8,TVecUINT32> _mapLastParam;
        UINT32 _dwGatherID;
        bool   _bInTeam;

        UINT64 _qwDemonToweInstID;
        UINT32 _dwCurTowerFlorrID;
        time_t _tLastMidNight;
        CGroupTaskPkg _GroupTaskPkg;
        CYaMenTaskPkg _YaMenTaskPkg;
        CActivityPkg _ActivityPkg;
        CTitlePkg _TitlePkg;
        CSignInPkg _SignInPkg;

        bool _bPackUnlockNotified;
        TVecString _StackMsg;


        //复活时间
        time_t _tReliveTime;

        UINT16  _wGuildLevel;   // 帮派等级
        string  _strGuildName;  // 帮派名称

        bool _bInLoad;

        //保存玩家活动列表
        TSetUINT16 _setActIDs;
        TVecEventOffLine _vecOffEvent;

        UINT32 _dwBattleCD;

        //临时战斗力 用于OnEvent
        UINT32 _dwTotalBattelPoint;  //总战斗力
        UINT32 _dwMainFighterBP;     //主将战斗力
        NItemProt::TVecItem _vecErrItem;

        bool _bCittaFirst;  // 第一次心法栏解锁检查
};

#endif // PLAYER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */




