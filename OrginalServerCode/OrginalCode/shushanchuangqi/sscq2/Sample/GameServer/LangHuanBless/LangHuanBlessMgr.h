
#ifndef LANGHUANBLESSMGR_H_
#define LANGHUANBLESSMGR_H_

#include "Singleton.h"
#include "Map.h"
#include <map>
#include <memory>
#include "DayActivity.h"
#include "LangHuanBlessProt.h"
#include "LanghuanfudiSkillCFG.h"
#include "LanghuanfudiAwardCFG.h"
#include "VarDefine.h"
using namespace NLangHuanBlessProt;

struct SLHBSkill
{
    ELHBSkillType eSkillType;
    UINT32 dwLastUseTime;
    UINT8 byRefreshTime;
    UINT32  dwCount;
    UINT32  dwScore;

    SLHBSkill()
    {
        eSkillType = eLHBSkillType_eNone;
        dwLastUseTime = 0;
        byRefreshTime = 0;
        dwCount = 0;
        dwScore = 0;
    }

};

typedef shared_ptr<SLHBSkill> SLHBSkillPtr;
typedef vector<SLHBSkillPtr> TVecLHBSkillPtr;
struct SLHBSkillCFGEx : public SLanghuanfudiSkillCFG
{
    UINT32 dwID;
    UINT16 dDistance;
    UINT16 dSkillCD;
    UINT32 dwMapID;
    UINT32 dwUseTimes;
    void CopyFrom(SLanghuanfudiSkillCFG &rLHBSkillCFG)
    {
        *(SLanghuanfudiSkillCFG*)this = rLHBSkillCFG;
    }
};

typedef shared_ptr<SLHBSkillCFGEx> SLHBSkillCFGExPtr;
typedef map<UINT32,SLHBSkillCFGExPtr> TMapLHBSkillPtr;

struct SLHBAwardCFGEx : public SLanghuanfudiAwardCFG
{
    UINT8 byLevel;
    UINT16 dBasicXiuwei;
    UINT16 dExp;
    UINT16 dSkillXiuwei;

    void CopyFrom(SLanghuanfudiAwardCFG &rAwardCFG)
    {
        *(SLanghuanfudiAwardCFG*)this = rAwardCFG;
    }
};

typedef shared_ptr<SLHBAwardCFGEx> SLHBAwardCFGExPtr;
typedef map<UINT8,SLHBAwardCFGExPtr> TMapID2AwardPtr;

struct SLHBPlayerInfo
{
    UINT64 qwUserID;
    UINT64 qwRoleID;
    string strName;
    UINT16 dwScore; //基础修为值大小
    UINT16 dwBasicExp; //基础经验值大小
    UINT16 dwSkillXiuwei;
    UINT32 dwTotalXiuwei;
    UINT32 dwTotalExp;
    UINT32 dwLevel; //等级
    UINT32 dwEnrollTime;
    CGameMapPtr rMapInstPtr;
    ESexType ePlayerSex;
    UINT32 dwLastLeaveActTime;
    UINT32 dwPeriodTime;
    TVecLHBSkillPtr vecLHBSkillPtr;
    SLHBPlayerInfo() 
    {
        qwUserID = 0;
        qwRoleID = 0;
        strName = "";
        ePlayerSex = ESEX_ALL;
        dwScore = 0;
        dwLevel = 0;
        dwEnrollTime = 0;
        rMapInstPtr = NULL;
        dwLastLeaveActTime = 0;
        dwPeriodTime = 0;
        dwTotalXiuwei = 0;
        dwTotalExp = 0;
        dwBasicExp = 0;
        dwSkillXiuwei = 0;


    };
    
};
typedef shared_ptr<SLHBPlayerInfo> SLHBPlayerInfoPtr;
typedef std::map<UINT64,SLHBPlayerInfoPtr> TMapLHBPlayerInfoPtr;
enum
{
    eLangHuanBlessEnrollEvent,  //活动开始报名提示
    eLangHuanBlessStartEvent, //npc攻击
    eLangHuanBlessEvent_KickPlayer,//把玩家T处地图
};

class CPlayer;

class CLangHuanBlessMgr : public Singleton<CLangHuanBlessMgr>,public CDayActivity
{
public:
    CLangHuanBlessMgr();
    ~CLangHuanBlessMgr();

    bool         Init();
    bool         ReLoadConfig(const string&);
    virtual bool GMOpen();
    virtual bool OnAlarm();
    virtual void OnReady();
    virtual void OnBegin();
    void OnReBegin();
    virtual void OnEnd();
    virtual void OnEvent(SActEventData&);

    ELHBResult   OnEnterMap(CPlayer&);
    ELHBResult   OnLeaveMap(CPlayer&);
    void         KickAllPlayer();
    void         KickPlayers();
    UINT32       GetScore(CPlayer&);
    ELHBResult   OnUseSkill(CPlayer&,UINT64,ELHBSkillType);
    ELHBResult   GetSkillInfo(CPlayer&,TVecLHBSkillInfo&);
    ELHBResult   CanEnterMap(CPlayer&) ;
    UINT32       GetSustainTime(CPlayer &);
    UINT32       GetExp(CPlayer &rPlayer);
    bool         GetTotalInfo(CPlayer&,SLHBTotalInfo&);
    bool         InitSkillInfo(TVecLHBSkillPtr&,UINT32);
    void         SendPrize();
    bool         OpenActivity(UINT32 dwBegin,UINT32 dwEnd);
    bool         CheckActTime();
    UINT16       GetMapID();
    bool         IsAllowEnter(CPlayer&);
private:
    ELHBResult   CanUseSkill(CPlayer&, ELHBSkillType,UINT16&, UINT32 &);
    ELHBResult   PlayerSit(CPlayer&, SLHBSkillCFGExPtr);
    ELHBResult   UseSkill(CPlayer&, ELHBSkillType);
    ELHBResult   PlayerTalkTaoism(CPlayer&,UINT64&,SLHBSkillCFGExPtr);
    ELHBResult   PlayerWander(CPlayer&, UINT64&,SLHBSkillCFGExPtr);
    ELHBResult   PlayerAskTaoism(CPlayer&,SLHBSkillCFGExPtr);
    bool         GetUserPtrByPlayerID(UINT64&,CUserPtr&);
    ELHBResult   AddSkillXiuwei(CPlayer &, ELHBSkillType );
    bool         CalcOffLinePlayer(CPlayer &);
    UINT32       GetXiuweiForOffLine(CPlayer& rPlayer,UINT32 dwTime);
    UINT32       GetExpForOffLine(CPlayer& rPlayer,UINT32 dwTime);
    UINT16       GetOffValue(CPlayer &rPlayer,UINT8 byIndex /* 0 修为，1 经验*/);
    bool         IsReBegin();
    //玩家总信息
    TMapLHBPlayerInfoPtr          _mapID2LHBPlayerPtr;
    TMapID2AwardPtr               _mapID2AwardPtr;
    TMapLHBSkillPtr               _mapID2LHBSkillPtr;
    deque<CGameMapPtr>            _deqMapGroup;
    UINT32                        _dwBeginSit;    
    UINT32                        _dwMapId;
    UINT32                        _dwBuffId;
    UINT32                        _dwAskTaoismValue;
    UINT32                        _dwTalkTaoismValue;
    UINT32                        _dwWanderValue;
    bool                          _bLog;
    ELHBState                     _byState;
    CGameMapPtr                   pMap;
};

#endif // WORLDBOSSMGR_H_


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

