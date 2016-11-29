#ifndef BATTLE_SKILL_H
#define BATTLE_SKILL_H

#include <memory>
#include "Linux.h"
#include "BattleGS.h"
#include "BattleTypeDef.h"

using namespace NBattleGS;

namespace NBattle
{

struct SSkill
{
    UINT32          _dwID;
    string          _strName;
    ESkillType      _eType;
    bool            _bCanBeCounter;
    TVecUINT32      _vecProbEffectID;
    TVecUINT32      _vecEffectID;
    UINT32          _dwSymbol;
    UINT8           _byColor;
    UINT8           _byCombineCount;
    SSkill():
        _dwID(0), _eType(eSkillNone), _bCanBeCounter(false), _dwSymbol(0), _byColor(0), _byCombineCount(0)
    {
    }
};

struct SSkillEffect
{
    UINT32           _dwID;              // 技能ID
    string           _strName;           // 技能名称
    INT32            _dwCD;              // 技能CD
    UINT16           _wRate;             // 触发概率
    EMachineState    _eState;            // 触发条件
    TVecUINT32       _vecCondValue;      // 触发参数
    UINT8            _byCondCD;          // 触发次数
    UINT16           _wCondRate;         // 触发条件生效概率
    EMachineState    _eOutState;         // 消失条件
    TVecUINT32       _vecOutCondValue;   // 消失参数
    UINT8            _byOutCD;           // 消失次数
    UINT8            _byTurnCD;          // 回合内CD（每回合最大触发次数）
    UINT8            _byLast;            // 持续时间
    EBStateBuffType  _eBuffGroup;        // Buff组ID
    UINT16           _wArea;             // 作用范围
    ESkillEffectType _eSkillEffectType;  // 触发效果类型
    EResistType      _eResistType;       // 是否能被免疫
    FLOAT            _fValue1;           // 效果值1
    FLOAT            _fValue2;           // 效果值2
    FLOAT            _fValue3;           // 效果值3
    TVecUINT32       _vecBuffID;         // 触发的BuffID

    SSkillEffect():
        _dwID(0), _dwCD(0), _wRate(0), 
        _eState(eMSNone), _byCondCD(0), _wCondRate(0), _eOutState(eMSNone), _byOutCD(0), _byTurnCD(0),
        _byLast(0), _eBuffGroup(EBFBuffTypeNone), _wArea(0), _eSkillEffectType(ENone), _eResistType(eResistTypeNone),
        _fValue1(0), _fValue2(0), _fValue3(0)
    {
    }
    UINT32 GetRate() const;
};

typedef vector  <SSkillEffect*>             TVecSkillEffectPtr;

class CBattleSkillEffect
{
    public:
        CBattleSkillEffect();
        CBattleSkillEffect(SSkillEffect* pSEf);

        UINT32              GetID() const;
        UINT32              GetOriginSkillID() const;
        SSkillEffect*       GetSkillEffect() const;
        SSkillEffect*       GetSkillEffect();
        const string&       GetName() const;

        ESkillEffectType    GetType() const;
        UINT16              GetArea() const;

        UINT32              GetRate() const;
        bool                HasNextBuffID() const;
        void                GetNextBuffID(TVecUINT32& vecBuffID) const;

        UINT8               GetLast() const;

        FLOAT               GetValue1() const;
        FLOAT               GetValue2() const;
        FLOAT               GetValue3() const;

        FLOAT               GetDefaultValue1() const;
        FLOAT               GetDefaultValue2() const;
        FLOAT               GetDefaultValue3() const;

        EResistType         GetResistType() const;

    private:
        UINT32      _dwSkillEffectID;     // 技能ID
        INT32       _dwCD;                // 冷却

        UINT32      _dwOriginSkillID;     // 初始技能ID带出来的
                                          
        FLOAT       _fValue1;             // 效果值
        FLOAT       _fValue2;             // 效果值
        FLOAT       _fValue3;             // 效果值
        SSkillEffect* _pSkillEffect;        // 技能效果

};

typedef std::vector<CBattleSkillEffect> TVecBattleSkillEffect;

class CBattleBuff
{
    public:
        CBattleBuff();
        bool Build(SSkillEffect* pSEf, CBattleFighter* pGiver, CBattleFighter* pOwner);
        bool Build(const CBattleSkillEffect& pSEf, CBattleFighter* pGiver, CBattleFighter* pOwner);
        bool Build(UINT32 dwBuffID, CBattleFighter* pGiver, CBattleFighter* pOwner);

        void                SetInstID(UINT32 dwInstID);
        UINT32              GetInstID() const;

        UINT32              GetID() const;
        UINT32              GetOriginSkillID() const;
        const string&       GetName() const;
        EBStateBuffType     GetGroupBuffType() const;
        ESkillEffectType    GetType() const;
        EMachineState       GetEffectCond() const;
        EMachineState       GetOutEffectCond() const;

        TVecUINT32&         GetEffectCondValue() const;
        TVecUINT32&         GetOutEffectCondValue() const;

        UINT8               GetEffectCondCount() const;
        UINT8               GetOutEffectCondCount() const;

        FLOAT               GetCondParam() const;
        FLOAT               GetOutCondParam() const;
        FLOAT               GetCondParam(bool bOut) const;

        UINT16              GetCondRate() const;

        SSkillEffect*     GetSkillEffect();
        SSkillEffect*     GetSkillEffect() const;

        CBattleFighter*   GetOwner() const;
        CBattleFighter*   GetGiver() const;

        void    AddLast(UINT8 byLast = 1);
        void    SetLast(UINT8 byLast);
        UINT8   GetLast() const;
        UINT8   GetDefaultLast() const;

        FLOAT   GetValue1() const;
        FLOAT   GetValue2() const;
        FLOAT   GetValue3() const;

        FLOAT   GetDefaultValue1() const;
        FLOAT   GetDefaultValue2() const;
        FLOAT   GetDefaultValue3() const;

        void    SetValue1(FLOAT fValue1);
        void    SetValue2(FLOAT fValue2);
        void    SetValue3(FLOAT fValue3);

        void    ResetValue(FLOAT fValue1, FLOAT fValue2, FLOAT fValue3);
        void    ResetValue1(FLOAT fValue);
        void    ResetValue2(FLOAT fValue);
        void    ResetValue3(FLOAT fValue);

        FLOAT   GetDefaultResetValue1() const;

        UINT32  GetRate() const;
        void    GetNextBuffID(TVecUINT32& vecBuffID) const;

        bool    CanResist() const;
        bool    CanClear(EResistType eType) const;
        bool    CanClearControl() const;
        EResistType GetResistType() const;

        bool    AddCondCount();
        bool    AddOutCondCount();

        void    SetCondParam(FLOAT fValue);
        void    SetOutCondParam(FLOAT fValue);
        void    SetCondParam(FLOAT fValue, bool bOut);

        INT32   GetCD() const;
        void    ResetCD(bool bInit = false);
        void    ResetCondCount();
        void    ResetOutCondCount();
        void    ReleaseCD();

        bool    IsTurnEnable() const;
        UINT8   GetTurnCD() const;
        void    AddTurnCD(UINT8 byCD);
        void    ResetTurnCD();
        

    private:
        UINT32            _dwInstID;
        UINT32            _dwID;                    // BuffID
        UINT32            _dwOriginSkillID;         // 初始技能ID带出来的


        UINT8             _byEffectCondCount;       // 触发计数
        FLOAT             _fCondParam;              // 触发计数相关参数
        UINT8             _byOutEffectCondCount;    // 消失计数
        FLOAT             _fOutCondParam;           // 消失计数相关参数
        UINT8             _byLast;                  // 持续回合

        SSkillEffect*     _pSkillEffect;            // 效果
        CBattleFighter*   _pOwner;                  // buf宿主
        CBattleFighter*   _pGiver;                  // buf施放者
        FLOAT             _fValue1;                 // 效果值1
        FLOAT             _fValue2;                 // 效果值2
        FLOAT             _fValue3;                 // 效果值3
        INT32             _dwCD;                    // 冷却CD
        INT32             _dwTurnCD;                // 回合内CD (每回合最大触发次数)
};

class CBattleSkillMgr : public Singleton<CBattleSkillMgr>
{
    public:
        bool ReloadCfg(const string& strPath);
        bool ReLoadBaseConfig(const string& strPath, const string &strFile);
        bool ReLoadEffectConfig(const string& strPath, const string &strFile);
        bool Init(const string& strPath);
        bool LoadSkill(const string& strPath);               // 加载配置表
        bool LoadSkillCfg(const string& strPath);            // 这张表先加载，这个是信息总表，其它表格的数据可能依赖它
        bool LoadSkillEffectCfg(const string& strPath);

        SSkill* GetSkill(UINT32 dwSkillID);
        SSkill* GetOriginSkill(UINT32 dwSkillID);
        UINT32    GetOriginSkillID(UINT32 dwSkillID);
        EBStateBuffType GetGroupBuffType(UINT32 dwBuffID);
        SSkillEffect* GetSkillEf(UINT32 dwEffectID);
        UINT32 GetSkillIDQualityLevel(UINT32 dwSkillID, UINT8 byLevel, UINT8 byColor);
        ESkillEffectType GetSkillEffectType(UINT32 dwSkillID);
        UINT8    GetCombineCount(UINT32 dwSkillID);
        
        EStateSubType GetStateBuffSubType(EBStateBuffType eBStateBuffType) const;
        EStateAddType GetStateBuffAddType(EBStateBuffType eBStateBuffType) const;

        bool AnalysisString2VectorUINT16(string strValue, string strSep, TVecUINT16& vOut);
        bool AnalysisString2VectorUINT32(string strValue, string strSep, TVecUINT32& vOut);
        bool AnalysisString2VectorFloat(string strValue, string strSep, TVecFloat& vOut);

        void GetAllSkillEffectWithType(UINT32 dwSkillID, ESkillEffectType eType, TSetUINT32& rsetExcpEffectID, TVecSkillEffectPtr& rvecSEf);

    public:
        void GetPassiveSkillEffect   (UINT32 dwSkillID, TVecBattleSkillEffect& rvecBattleSkillEffect);
        void GetSkillEffectWithProb  (UINT32 dwSkillID, UINT32 dwSymbolID, TVecBattleSkillEffect& rvecBattleSkillEffect, TVecUINT16& rvecProb);
        void InitSkillEffectWithProb (const TVecUINT32& rvecEffectID, TVecBattleSkillEffect& rvecBattleSkillEffect, TVecUINT16& rvecProb);

        bool CanBeCounter(UINT32 dwSkillID);
        ESkillType GetSkillType(UINT32 dwSkillID);
        UINT32 GetSymbolSkillID(UINT32 dwSkillID);
        const string& GetSkillName(UINT32 dwSkillID);
        void GetAllSummonFighterID(UINT32 dwSkillID, TSetUINT16& rsetFighterID);

    private:
        map<UINT32, SSkill*>          _mapSkill;
        map<UINT32, UINT32>           _mapSkillEffect2SkillID;
        map<UINT32, SSkillEffect*>    _mapSkillEffect;        // 这个map里面，记得把base和符文抽象出来的执行也加入进去
};

#define BattleSkillMgr CBattleSkillMgr::Instance()

} //namespace NBattle

#endif // #ifndef BATTLE_SKILL_H

