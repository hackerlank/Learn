
#ifndef SHUSHANBALLTEMGR_H_
#define SHUSHANBALLTEMGR_H_

#include "Singleton.h"
#include "ProtoCommon.h" // fox TVecFtAttrMod
#include "ShushanBattleSkillCFG.h"
#include "ShushanBattleTaskCFG.h"
#include "ShushanBattleAwardCFG.h"
#include "ShuShanLunJianExpCFG.h"
#include "ShushanBattleProt.h"
#include "Player.h"
#include "DayActivity.h"

using namespace NShushanBattleProt;

/**
 *@brief 蜀山论剑技能属性
 */
struct SBattleSkillCFGEx : public SShushanBattleSkillCFG
{
    void SetConfig(const SShushanBattleSkillCFG& rBattleSkillCFG)
    {
        *(SShushanBattleSkillCFG*)this = rBattleSkillCFG;
    }
    TVecFloat _vecAddAttr;
};

/**
 *@brief 蜀山论剑奖励
 */
struct SBattleAwardCFGEx : public SShushanBattleAwardCFG
{
    void SetConfig(const SShushanBattleAwardCFG& rBattleAwardCFG)
    {
        *(SShushanBattleAwardCFG*)this = rBattleAwardCFG;
    }
    TVecItemGenInfo _vecItemGenInfo;
};

struct SBattleExpCFGEx : public SShuShanLunJianExpCFG
{
    void SetConfig(const SShuShanLunJianExpCFG& rBattleExpCFG)
    {
        *(SShuShanLunJianExpCFG*)this = rBattleExpCFG;
    }

};

enum
{
    eShushanBattleEvent_10Tip,          //10分钟倒计时提示
    eShushanBattleEvent_5Tip,           //5分钟倒计时提示
    eShushanBattleEvent_NPC_ATTACK,     //论剑活动开始
    eShushanBattleEvent_KickPlayer,     //论剑活动结束,把玩家T出地图
};

class CShushanBattleMgr : public Singleton<CShushanBattleMgr>, public CDayActivity
{
public:
    CShushanBattleMgr();
    ~CShushanBattleMgr();
    virtual bool GMOpen();
    virtual bool OnAlarm();
    virtual void OnReady();
    virtual void OnBegin();
    virtual void OnEnd();
    virtual void OnEvent(SActEventData&);

    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新
    static bool Init();
    static bool LoadConfig(bool bReload = false);
    static bool ReLoadConfig(const string&);
    static SBattleSkillCFGEx* GetBattleSkillCfg(UINT8 bySkillID);
    static void GetBattleTaskCfg(TVecTaskData&);
    static SBattleAwardCFGEx* GetBattleAwardCfg(UINT8 byLevel);
    SBattleExpCFGEx* GetBattleExpCfg(UINT8 byLevel);
    UINT8 CalcHonorLevel(UINT16 wHonor);

    void Prepare(UINT32);
    void Start(UINT32);
	void CalcNext(UINT32);
    void BroadcastTV(UINT32);
	bool TimerCheck(UINT32);    //5秒一次
	void End(UINT32);
    void SendBattleStatusInLogin(CPlayerPtr);
    inline bool IsRunning()        { return time(NULL) >= _dwPrepareTime && time(NULL) < _dwEndedTime; }
	inline UINT32 GetPrepareTime() { return _dwPrepareTime; }
	inline UINT32 GetStartTime()   { return _dwStartTime; }
	inline UINT32 GetEndedTime()     { return _dwEndedTime; }
    inline void SetGMCheck(bool b) { _bGMCheck = b; }

private:
    static UINT64 _qwVersion;
    UINT8 _byPrepareStep;
	UINT32 _dwPrepareTime, _dwStartTime, _dwEndedTime;
    bool _bGMCheck;  //for GM open ShushanBattle

private:
    static std::map<UINT8, SBattleSkillCFGEx> _mapID2BattleSkillCFG;
    static std::vector<TVecTaskData> _vecBattleTaskCFG[3];  // 蜀山论剑普通/中等/困难任务
    static std::map<UINT8, SBattleAwardCFGEx> _mapID2BattleAwardCFG;
    static std::map<UINT8, SBattleExpCFGEx> _mapID2BattleExpCFG;
};

#define ShushanBattleMgr CShushanBattleMgr::Instance()

#endif // SHUSHANBALLTEMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

