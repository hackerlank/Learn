#pragma once
#include "Monster.h"
#include "MonsterGroupCFG.h"
#include "TaskDropCFG.h"
#include "WorldBossCFG.h"

typedef vector<STaskDropCFG> TVecTaskDropInfo;
typedef map<UINT16, TVecTaskDropInfo> TMapTask2Drop;
struct SMonsterGroupCFGEx :public SMonsterGroupCFG
{
    SMonsterGroupCFGEx(const SMonsterGroupCFG &rOther):SMonsterGroupCFG(rOther), wPetID(0)
    {
    }
    SMonsterGroupCFGEx(): wPetID(0)
    {
    }
    struct SFighterPos
    {
        UINT16 wMonsterID;
        UINT8 byPos;
        SFighterPos():
            wMonsterID(0), byPos(0)
        {}
    };
    struct SAddSkill
    {
        UINT16 wFighterID;
        UINT32 dwSkillID;
        UINT32 dwSkillLevel;
        SAddSkill():
            wFighterID(0), dwSkillID(0), dwSkillLevel(0)
        {}
    };
    vector<UINT32>	    vecDropID;
    vector<SFighterPos> vecFighters;
    vector<SFighterPos> vecAddFighters;
    vector<SAddSkill>   vecAddSkills;
    TVecUINT16          vecMonsterID;
    UINT16 wPetID; 
};

struct SAICFGEx: public SAICFG
{
    public:
        enum EMoveType
        {
            eMoveNone,//不移动
            eMoveRand,//随机移动
            eMovePath,//按固定路线移动
        };
        SAICFGEx():SightAngle(0),SightRadius(0),_eMoveType(eMoveNone){}
        SAICFGEx(const SAICFG &rCfg):SAICFG(rCfg),SightAngle(0),SightRadius(0),_eMoveType(eMoveNone){}
public:
        
        float SightAngle;
        float SightRadius;
        EMoveType _eMoveType;
};

struct SMonsterExp
{
    UINT32 dwExp;
    UINT32 dwSkillExp;
};

struct SWorldBossCFGEx : public SWorldBossCFG
{
    void SetConfig(const SWorldBossCFG& rWorldBoss)
    {
        *(SWorldBossCFG*)this = rWorldBoss;
    }
    SPoint pos;
    std::vector<SPoint> vecBirthPlace;
};

class CMonsterMgr
{
public:
    static bool	Init();
    static bool LoadConfig(const string&);
    static void Destroy();
    static SAICFGEx* GetAIConfig(UINT16 wAIID);
    static CMonsterPtr CreateMonster(UINT16 wMonsterID,const string& strName);
    static void DestroyMonster(const CMonsterPtr& pMonster);
    static CMonsterPtr GetMonster(UINT64 qwCreatureID);
    static const SMonsterGroupCFGEx* GetMonsterGroup(UINT16 wGroupID);
    static TMapTask2Drop* GetTaskDropMap(UINT32 dwMonsterIdx);
    static void PrintMonsterLog(const char* pMsg, CMonster& rMonster);
    static void SetMonsterLog(bool bOpen){ _bPrintLog = bOpen; }

    static UINT16 GetMonsterLevel(UINT16 wGroupID);

    static SWorldBossCFGEx* GetWorldBossCfg(UINT16 wBossID);

private:
    static UINT32 SelectSlowMapIndex();
    static UINT32 SelectFastMapIndex();
    static map<UINT16, SAICFGEx> _mapID2AICfg;
    static map<UINT64, CMonsterPtr> _mapID2Monster;
    static map<UINT16, SMonsterGroupCFGEx> _mapID2MonsterGroup;
    static map<UINT16, TMapTask2Drop> _mapID2TaskDrop;
    static map<UINT16, SWorldBossCFGEx> _mapWorldBoss;
    static bool _bPrintLog;
};
