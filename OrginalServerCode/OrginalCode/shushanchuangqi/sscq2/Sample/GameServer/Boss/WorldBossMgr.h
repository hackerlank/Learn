
#ifndef WORLDBOSSMGR_H_
#define WORLDBOSSMGR_H_

#include "Singleton.h"
#include "Map.h"
#include "BossProtS.h"
#include "WorldBoss.h"
#include <map>
#include <memory>
#include "DayActivity.h"
#include "WorldBossPrizeCFG.h"

extern const UINT32 WORLDBOSS_MAX_HP;
extern const UINT32 WORLDBOSS_MIN_ATK;

enum EWorldBossPrize
{
    eWorldBossStrengthID = 10,  //激励ID
    eWorldBossAttribBeginID = 10001,//激励属性
    eWorldBossAttribEndID = 10015, //激励属性最高
    eWorldBossNpcBufferID = 3, //场景npcbufferId
    eWorldBossBlockID = 1,  //阻挡点id
    eWorldBossSilverBufferID = 10, //银币buffer
    eWorldBossGoldBufferID = 11,   //金币buffer
    eWorldBossDeadBufferID = 15, //死亡buffer
    eWorldBossID1030       = 20000, //上午boss
    eWorldBossID1545       = 20001, //下午boss
};

struct SWorldBossPrizeCFGEx:public SWorldBossPrizeCFG
{
    TVecItemGenInfo _vecItemGenInfo;
    void CopyFrom(SWorldBossPrizeCFG& rWorldBossPrizeCFG)
    {
        *((SWorldBossPrizeCFG*)this) = rWorldBossPrizeCFG;
    }
};

struct SDamageRatePrize
{
    UINT64 _qwRoleID;
    UINT32 _dwDamageRate;
    SDamageRatePrize(UINT64 qwRoleID,UINT32 dwDamageRate)
    {
        _qwRoleID = qwRoleID;
        _dwDamageRate = dwDamageRate;
    }
};
typedef std::vector<SDamageRatePrize> TVecDamageRatePrize;

typedef shared_ptr<SWorldBossPrizeCFGEx> SWorldBossPrizeCFGExPtr;

typedef std::vector<SWorldBossPrizeCFGExPtr> TVecWorldBossPrizeCFGExPtr;


struct SBossPlayerInfo:public CPoolObj<SBossPlayerInfo>
{
    UINT32 dwNo;
    UINT64 qwUserID;
    UINT64 qwRoleID;
    string strName;
    UINT16 wColor;
    UINT32 dwScore; //总伤害
    UINT32 dwLastScoreTime; //最后伤害时间
    UINT32 dwExp;  //获得的经验
    UINT32 dwReliveTime; //复活时间
    UINT32 dwLevel; //等级
    UINT32 dwSilverBufferCnt;//银币加持次数
    UINT32 dwGoldBufferCnt;  //金币加持次数
    UINT32 dwSilverBufferCdTime; //银币加持cd
    UINT32 dwAttackCnt; //立即战斗次数
    UINT32 dwMapID;//进来的地图
    SPoint oPoint; 

    SBossPlayerInfo() 
    {
        dwNo = 0;
        qwUserID = 0;
        qwRoleID = 0;
        strName = "";
        dwScore = 0;
        dwLastScoreTime = 0;
        dwExp = 0;
        dwReliveTime = 0;
        dwLevel = 0;
        dwSilverBufferCnt = 0;
        dwGoldBufferCnt = 0;
        dwSilverBufferCdTime = 0;
        dwAttackCnt = 0;
        dwMapID = 1;
        oPoint.fX= 30;
        oPoint.fY = 40;
        wColor = 0;
    }
    
};

typedef shared_ptr<SBossPlayerInfo> SBossPlayerInfoPtr;
typedef std::map<UINT64,SBossPlayerInfoPtr> TMapBossPlayerInfoPtr;
typedef std::vector<SBossPlayerInfoPtr> TVecBossPlayerInfoPtr;
enum
{
    eWorldBossEvent_10Tip,  //10分钟倒计时提示
    eWorldBossEvent_5Tip,   //5分钟
    eWorldBossEvent_3Tip,   //3分钟
    eWorldBossEvent_2Tip,   //2分钟
    eWorldBossEvent_1Tip,   //1分钟
    eWorldBossEvent_NPC_ATTACK, //npc攻击
    eWorldBossEvent_KickPlayer,//把玩家T处地图
    eWorldBossEvent_PlayerCnt, //玩家人数通知
};

class CPlayer;

class CWorldBossMgr : public Singleton<CWorldBossMgr>,public CDayActivity
{
public:
    CWorldBossMgr();
    ~CWorldBossMgr();

    bool Init();

    void TimerInit();

    virtual bool GMOpen();
    virtual bool OnAlarm();
    virtual void OnReady();
    virtual void OnBegin();
    virtual void OnEnd();
    virtual void OnEvent(SActEventData& oSActEventData);
    
    //服务器重启活动处理
    virtual void OnReBegin();

    //排行榜
    void OnGetTopList(CPlayer& rPlayer);

    //个人信息
    void OnGetSelfInfo(CPlayer& rPlayer);

    //boss信息
    void OnGetBossInfo(CPlayer& rPlayer);

    //进入地图
    bool OnEnterMap(CPlayer& rPlayer);

    //离开地图
    bool OnLeaveMap(CPlayer& rPlayer);

    //玩家死亡
    void OnPlayerDead(CPlayer& rPlayer);

    //购买复活
    bool OnRelive(CPlayer& rPlayer);

    void SetPlayerRelive(CPlayer& rPlayer);

    //购买加持
    bool BuyStrength(CPlayer& rPlayer,UINT32 dwBuyType,UINT32& dwSilverBufferCnt,UINT32& dwGoldBufferCnt,UINT32& dwSilverBufferCdTime);

    //攻击boss
    bool AttackBoss(CPlayer& rPlayer);

    //打印boss属性
    void PrintBossInfo(CPlayer& rPlayer);

    void ChangeBossFactor(UINT32 dwSec);

    //t掉所有地图玩家
    void KickAllPlayer();

    void UpdateTopList(bool bEnd = false);

    void TimerCheck(UINT32 dwNow); // XXX: 每5秒一次

    bool CanEnterBossMap() const;
    bool IsBossAlive() const;

    void BossAppear(UINT16 wBossID);
    void BossDisappear();
    void ClearMap(CCreature& rBoss);
    bool OnBossDamage(CPlayer& rPlayer, UINT32 dwScore,UINT32 dwBossCurHP);
    void OnDead(CCreature& rBoss, CCreature& rKiller);
    void Reward(CCreature& rKiller);
    void BossHPNotify(FLOAT fPercent, UINT32 dwHP, UINT32 dwDmgHP);

    bool IsLoaded() const { return _bLoaded; }
    bool LoadBoss();
    bool LoadBoss(const NGame2DBComm::TVecWBossDBInfo& vecWorldBossInfo);
    void SaveBoss(CCreature& rBoss);

     void ChangeBossHp(UINT32 dwHP);

    void OnBossHpRate(CPlayer& rPlayer,UINT32 dwbossRate);

    SWorldBossPrizeCFGExPtr GetPrize(UINT32 dwPrizeType, UINT32 dwTopIndex = 1);


    void GetCFGMailItem(SWorldBossPrizeCFGExPtr pWorldBossPrizeCFGEx,UINT32 dwPlayerLevel, TVecItemGenInfo& vecItems);

    SBossPlayerInfoPtr GetPlayerInfo(UINT64 qwUserID);

    void GMOpenBoss(UINT32 dwBossID,UINT32 dwProcessTime = 33600);

    bool OpenActivity(UINT32 dwBegin,UINT32 dwEnd);

    bool ChecRatePrize(UINT32 dwMsgRate,UINT32 dwOlddRate,UINT32 dwNewRate,CPlayer& rPlayer);

    bool CheckMsg(UINT32 dwMsgRate,UINT32 dwOlddRate,UINT32 dwNewRate,CPlayer& rPlayer);

    CGameMapPtr GetMap() { return _pMap.lock(); }
private:
    UINT32 _dwPrepareTime;
    UINT32 _dwAppearTime;
    UINT32 _dwDisapperTime;
    UINT32 _dwPrepareStep;

    //开始时间
    UINT32 _dwStartFightTime;

    //结束时间
    UINT32 _dwEndFightTime;


    int _iIdx;
    bool _bDisappered;

    UINT64 _qwMonsterID;
    CGameMapWtr _pMap;

    //玩家总信息
    TMapBossPlayerInfoPtr _mapBossPlayerInfoPtr;

    // 前10排行
    TVecBossPlayerInfoPtr _vecBossPlayerInfoPtr;

    //伤害奖励
    TVecDamageRatePrize _vecDamageRatePrize;

    bool _bDataChange;

    UINT32 _dwMaxHP;
    UINT32 _dwCurHP;
    UINT32 _dwBoosID;
    UINT32 _dwPlayerCnt;
    UINT32 _dwNotifyPlayerCnt;

    //boss基本击杀时间
    UINT32 _dwBossBasTime;

    //法宝等级
    UINT32 _dwNPCLevel;

    UINT64 _qwLastKillID;

    //随机奖励
    SWorldBossPrizeCFGExPtr _pNpcPrize;

    //击杀奖励
    SWorldBossPrizeCFGExPtr _pKillPrize;

    //白分比经验
    UINT32 _dwExp;

    //广播的百分比
    UINT32 _dwMessageHpRate;

    bool _bLoaded;
    std::map<UINT16, SWBossDBInfo> _mapBossInfo;

    TVecWorldBossPrizeCFGExPtr _vecWorldBossPrizeCFGExPtr;

    bool _bLog;

    UINT32 _dwSilverBaseSkillAttrID;
    UINT32 _dwGoldBaseSkillAttrID;
    UINT32 _dwSilverCD;
    
    UINT32 _dwMaxAttackCnt;

};

#endif // WORLDBOSSMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

