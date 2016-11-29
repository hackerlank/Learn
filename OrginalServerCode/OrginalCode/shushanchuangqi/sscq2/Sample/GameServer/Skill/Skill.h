#ifndef _SKILL_H_
#define _SKILL_H_

#include "stdafx.h"
#include "Singleton.h"
#include "BattleGS.h"

#ifndef SKILL_RANGE_DEFINE
#define SKILL_RANGE_DEFINE

#define SKILL_LEVEL_MAX 100
#define SKILL_QUALITY_MAX 10
#define SKILL_LEVEL(x)  (((UINT32)(x))%(SKILL_LEVEL_MAX))
#define SKILL_ID(x) (((UINT32)(x))/(SKILL_LEVEL_MAX * SKILL_QUALITY_MAX))
#define SKILL_QUALITY(x) (((UINT32)(x))%(SKILL_LEVEL_MAX * SKILL_QUALITY_MAX)/SKILL_LEVEL_MAX)
#define SKILLANDLEVEL(s,l) (((UINT32)(s))*SKILL_LEVEL_MAX * SKILL_QUALITY_MAX + ((UINT32)(l)))
#define SKILLID_QUALITY_LEVEL(s,c,l) (((UINT32)(s))*SKILL_LEVEL_MAX * SKILL_QUALITY_MAX + (UINT32)(c)*SKILL_LEVEL_MAX + (UINT32)(l))

#endif // #ifndef SKILL_RANGE_DEFINE

struct SSkillEf
{
    UINT32          _dwID;              // 技能ID
    string          _strName;           // 技能名称
    UINT16          _wCostType;         // 升级消耗类型1
    UINT32          _dwCost;            // 升级消耗1
    UINT8           _byNeedLevel;       // 升级所需要玩家等级
    INT32           _dwCD;              // 技能CD
    UINT16          _wRate;             // 触发概率
    UINT16          _wCond;             // 触发条件
    TVecUINT32      _vecCondValue;      // 触发参数
    UINT8           _byCondCD;          // 触发次数
    UINT16          _wOutCond;          // 消失条件
    TVecUINT32      _vecOutCondValue;   // 消失参数
    UINT8           _byOutCD;           // 消失次数
    UINT8           _byLast;            // 持续时间
    UINT16          _wGroupID;          // Buff组ID
    UINT16          _wArea;             // 作用范围
    UINT16          _wType;             // 触发效果类型
    FLOAT           _fValue1;           // 效果值1
    FLOAT           _fValue2;           // 效果值2
    FLOAT           _fValue3;           // 效果值3
    TVecUINT32      _vecBuffID;         // 触发的BuffID
    UINT32          _dwBattlePoint;     // 技能战斗力

    SSkillEf():
        _dwID(0), 
        _wCostType(0), _dwCost(0), _byNeedLevel(0),
        _dwCD(0), _wRate(0), 
        _wCond(0), _byCondCD(0), _wOutCond(0), _byOutCD(0), 
        _byLast(0), _wGroupID(0), _wArea(0), _wType(0),
        _fValue1(0), _fValue2(0), _fValue3(0), _dwBattlePoint(0)
    {
    }
};

enum ESkillType
{
    eSkillNone       = 0, // 无效技能
    eSkillActive     = 1, // 主动技能
    eSkillPeerless   = 2, // 无双技能
    eSkillPassive    = 3, // 被动技能
    eSkillSymbol     = 4, // 技能符文
    eSkillFormation  = 5, // 阵灵技能
    eSkillScene      = 6, // 场景技能
    eSkillTalent     = 7, // 天赋技能
    eSkillCombine    = 8, // 连携技能
    eSkillBeauty     = 9, // 美女技能
    eSkillTrump      = 10,// 法宝技能
};

struct SSkill
{
    UINT32          _dwID;
    string          _strName;
    ESkillType      _eType;
    bool            _bCanBeCounter;
    TVecUINT32      _vecProbEffectID;
    TVecUINT32      _vecEffectID;
    UINT32          _dwSymbol;
    UINT32          _dwAdv;
    UINT8           _byColor;
    SSkill():
        _dwID(0), _eType(ESkillType::eSkillNone), _bCanBeCounter(false), _dwSymbol(0), _dwAdv(0), _byColor(0)
    {
    }
};

class CSkillMgr : public Singleton<CSkillMgr>
{
    public:
        bool ReloadCfg(const string& strPath);
        bool Init(const string& strPath);
        bool LoadSkill(const string& strPath);               // 加载配置表
        bool LoadSkillCfg(const string& strPath);            // 这张表先加载，这个是信息总表，其它表格的数据可能依赖它
        bool LoadSkillEffectCfg(const string& strPath);

        bool ReLoadConfig(const string &);
        SSkillPtr GetSkill(UINT32 dwSkillID);
        SSkillEfPtr GetSkillEf(UINT32 dwEffectId);
        UINT32 GetSkillIDQualityLevel(UINT32 dwSkillID, UINT8 byLevel = 1, UINT8 byColor = 0);

        bool AnalysisString2VectorUINT16(string strValue, string strSep, TVecUINT16& vOut);
        bool AnalysisString2VectorUINT32(string strValue, string strSep, TVecUINT32& vOut);
        bool AnalysisString2VectorFloat(string strValue, string strSep, TVecFloat& vOut);

    private:
        map<UINT32, SSkillPtr>      _mapSkill;
        map<UINT32, SSkillEfPtr>    _mapSkillEf;        // 这个map里面，记得把base和符文抽象出来的执行也加入进去
};

#define SkillMgr CSkillMgr::Instance()

#endif // _SKILL_H_
