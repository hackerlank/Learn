#pragma once
#include "stdafx.h"
#include "DungeonCFG.h"
#include "DungeonProt.h"
#include "ItemProt.h"
#define DGN_MULTI_PLAYER_JUMP 2
#define DGN_CARD_NUM 5
class CGameMap;
class CPlayer;
struct SPoint;
using namespace NDungeonProt;
using namespace NItemProt;
struct DgnOutConfig
{
    UINT16 wMapId;
    float fPosX;
    float fPosY;
    DgnOutConfig()
    {
        wMapId = 0;
        fPosX = 0;
        fPosY = 0;
    }
};
enum EOverSource
{
    eOver_SysTem,//系统
    eOver_Finish,//副本完成
    eOver_Leave,//玩家离开
    eOver_Logic,//副本失败
};
// 移到协议
/*
   enum EDgnType
   {
   eNoneDgn = 0,
   eNoviceDgn = 0,         //新手副本
   ePlayerDgn,         //单人副本
   eTeamDgn,           //组队副本
   eTowerDgn,          //试练之塔
   eWorldBossDgn,      //世界Boss副本
   eFYZJDummyDgn,      //封印之间虚拟副本，不是真正的副本
   eMineBattleDgn,     //矿战副本
   eTempleExploreDgn,  //魔宫冒险
   };
   */
struct SDgnConfig:public SDungeonCFG
{
    SDgnConfig(const SDungeonCFG& rDungeonCFG):SDungeonCFG(rDungeonCFG),wDgnID(0),eType(eNoneDgn),byMinLev(0),eSubType(eSubCommon),dwLootID(0),dwCostLootID(0)
    {
    }
    SDgnConfig():wDgnID(0),eType(eNoneDgn),byMinLev(0),eSubType(eSubCommon),dwLootID(0),dwCostLootID(0)
    {
    }
    UINT16 wDgnID;//副本Id
    EDgnType eType;//副本类型
    UINT8 byMinLev;//最小进入等级
    EDgnSubType eSubType;//副本次类型
    TVecUINT16 vecPreDgnID;
    TVecUINT16 vecRound;
    TVecUINT16 vecMap;
    TVecUINT32 vecAward;
    DgnOutConfig sOutConfig;
    TVecUINT16 vecAttackOrder;//杀怪副本，组队副本
    vector<TVecUINT16> vecProcess;
    vector<TVecUINT16> vecStar;
    UINT32 dwLootID;
    UINT32 dwCostLootID;

};
enum EDgnTimerDefine
{
    eTimerWaitPlayer = 60,//副本开启后等待玩家进入60秒
    eTimerFinish = 10*60,// 副本完成后，等待玩家领取奖励180秒,包括最后战报播放时间 
    eTimerLeave = 2*3600,
};

enum EDgnState//副本状态
{
    eDgnInit,//副本初始化
    eDgnWaitPlayer,//副本等待玩家进入
    eDgnRuning,//副本运行
    eDgnFinish,//副本目标完成，玩家领取奖励阶段
    eDgnDel_Over,//副本等待删除,因为副本已经结束
};
struct SDgnInfo
{
    SDgnInfo(const SDungeonCFG& pDungeonCFG):oDgnCfg(pDungeonCFG),_bHasOnEnterLimit(false),_bHasOnInit(false), _bHasOnTimer(false),_bHasOnEnd(false),_bHasOnFinish(false),_bLoad(false) { }

    SDgnConfig oDgnCfg;
    void Reset(){_bLoad = false;}
    SDgnInfo() : _bHasOnEnterLimit(false),_bHasOnInit(false), _bHasOnTimer(false),_bHasOnEnd(false),_bHasOnFinish(false),_bLoad(false) { }
    public:
    bool CheckScriptOnEnterLimit() const ;
    bool CheckScriptOnInit() const;
    bool CheckScriptOnTimer() const;
    bool CheckScriptOnEnd() const;
    bool CheckScriptOnFinish() const;
    void LuaInit();
    private:
    bool _bHasOnEnterLimit;
    bool _bHasOnInit;
    bool _bHasOnTimer;
    bool _bHasOnEnd;
    bool _bHasOnFinish;
    bool _bLoad;

};

class CDungeon : public enable_shared_from_this<CDungeon>
{
    friend class CDungeonMgr;
    public:
    DEF_NEW_DELETE(CDungeon);
    CDungeon(const SDgnInfo& rSDgnInfo, UINT64 qwInstID) :_rDgnInfo(rSDgnInfo), _qwInstID(qwInstID),_tCreateTime(0),_eDgnState(eDgnInit),_eOverSource(eOver_SysTem),_tStateTimer(0),_dwBattleRouds(0),_qwLastReportID(0) { }

    virtual ~CDungeon() { }
    //玩家重新进入副本
    virtual bool PlayerReEnter(CPlayer& rPlayer, SPoint& rPoint);
    //玩家进入副本
    virtual bool PlayerEnter(CPlayer& rPlayer,const SPoint* pPoint = NULL);
    //玩家离开副本
    virtual bool PlayerLeave(CPlayer& rPlayer);
    //副本异常关闭
    virtual void FailOver();//因为结束关闭，可能超时，或别的条件
    //怪物死亡
    virtual	void OnMonsterDie(CMonster& rMonster, UINT64 qwKillRoleID ,UINT64 qwBattleID);
    //玩家死亡
    virtual void OnPlayerDie(CCreature& rKiller,CPlayer& rPlayer){};
    virtual void GetLogString(string &strMsg){}
    //采集一个物品
    virtual	void OnGather(UINT16 wGatherID, CPlayer& rPlayer);

    //判断能否进入 
    virtual bool CanEnter(CPlayer& rPlayer);
    //获得副本类型
    virtual EDgnType GetDgnType() { return eNoneDgn; }
    //能否攻击
    virtual bool CanAttackMonster(UINT16 wMonsterGroup) {return true;}
    //副本清除
    virtual void ClearDungeon() { }
    //设置副本的状态
    virtual void SetDgnState(EDgnState eState);
    EDgnState GetDgnState() const { return _eDgnState; }
    //加载地图
    virtual bool LoadMap(UINT16 wMapID = 0 );
    //副本奖励
    virtual EDungeonResult  AcceptDgnAward(CPlayer& rPlayer){ return eDungeonSuccess;}
    //副本开始
    virtual bool OnBegin(){return true;}
    //副本结束
    virtual void OnEnd(){}

    //时钟函数
    virtual void OnTimer(time_t tNow);

    //-qf- 2014/05/28
    //是否可以跳转地图
    virtual bool IsCanJumpMap( CPlayer* pPlayer,CGameMapPtr& pCurMap,CGameMapPtr& pDestMap) { return true; };

    //玩家离开副本事件
    virtual void OnBeforeLeaveDgn( CPlayer* pPlayer) {};

    //进入副本
    virtual void OnEnterDgn(CPlayer* pPlayer) {};

    //进入地图之后事件（在进入副本函数之后调用）
    virtual void OnEnterMap(CPlayer* pPlayer,CGameMapPtr& pCurMap) {}

    //秒杀所有怪物
    virtual void PlayerKillAll(CPlayer& rPlayer){} 
    virtual  void FinishDgn(CPlayer& rPlayer){}

    //登陆后是否还在副本
    virtual bool IsCanRelogin() { return true; };
    
    void SetBattleRouds(UINT32 dwRounds) { _dwBattleRouds = dwRounds; };
    UINT32 GetBattleRouds() { return _dwBattleRouds; };

    void SetReportID(UINT64 qwReportID) { _qwLastReportID=qwReportID; };
    UINT64 GetReportID() { return _qwLastReportID; }

    //得到副本Id 
    UINT16 GetDgnID() const { return _rDgnInfo.oDgnCfg.wDgnID; }
    //得到副本实例ID
    UINT64 GetDgnInstID() const { return _qwInstID; }
    //得到副本配置
    const SDgnConfig& GetDgnConfig() const { return _rDgnInfo.oDgnCfg; }
    //得到加工后的配置
    const SDgnInfo& GetDgnInfo() const { return _rDgnInfo; }
    //能否摧毁
    bool CanDestroy(time_t tNow);
    //得到创建时间
    time_t GetCreateTime() const { return _tCreateTime; }
    //设置创建时间
    void SetCreateTime(time_t tCreateTime){ _tCreateTime = tCreateTime; }
    //初始化
    bool Init(UINT16 wMapId = 0);
    //获得地图
    CGameMapPtr GetMap(UINT16 wMapID);
    //得到当前地图
    CGameMapPtr GetCurMap() const { return _pCurMap.lock(); }
    //设置当前地图
    void SetCurMap(const CGameMapPtr& pMap) { _pCurMap = pMap; }
    // void OnEnter(CPlayer& rPlayer);
    // 是否无人判断
    bool IsNoPerson();
    //lua
    //设置定时器
    void SetTimer(UINT16 wTimerId,UINT32 dwTimerIntral);
    //设置参数
    void SetParam(UINT16 wParamId,UINT32 dwParamVal);
    //得到参数
    UINT32 GetParam(UINT16 wPramId);
    //中止定时器
    void EndTimer(UINT16 wTimerId);
    //刷怪物
    void CreateMonster(UINT16 wMonsterGroup,float fX,float fY);
    void CreateMonsterIfNotExist(UINT16 wMonsterGroup,float fX,float fY);
    //清理怪物
    void DestroyMonster(UINT16 wMonsterGroup);
    //刷采集物
    void CreateGather(UINT16 wGatherId,float fX, float fY);
    //清理采集物
    void DestroyGather(UINT16 wGatherId);
    //传递图
    void TransMap(UINT16 wMap,float fX = 0, float fy = 0);
    //设置阻挡
    void CreateBlockByIndex(UINT16 wIndex);
    //撤销阻挡
    void DestroyBlockByIndex(UINT16 wIndex);
    //增加区域
    void CreateAreaByIndex(UINT16 wIndex);
    //撤销区域
    void DestroyAreaByIndex(UINT16 wIndex);
    //Lua
     void AddSwitcherByIndex(UINT8 byIndex);
     void SwitcherDestroyByIndex(UINT8 byIndex);
     void AddGatherByIndex(UINT8 byIndex);
     void GatherDestroyByIndex(UINT8 byIndex);
     void AddNpcByIndex(UINT8 byIndex);
     void NpcDestroyByIndex(UINT8 byIndex);
     void DestroyNpc(UINT16 wNpcId);

    protected:
    const SDgnInfo& _rDgnInfo;
    UINT64 _qwInstID;
    time_t _tCreateTime;
    CGameMapWtr _pCurMap;
    std::map<UINT16, CGameMapPtr> _mapID2Map;
    std::set<UINT16> _setKillMonsterID;
    EDgnState _eDgnState;
    EOverSource _eOverSource;
    time_t _tStateTimer;
    map<UINT16,UINT32> mapTimer;
    map<UINT16,UINT32> mapParam;
    UINT32 _dwBattleRouds;
    UINT64 _qwLastReportID;

};


