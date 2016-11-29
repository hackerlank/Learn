
#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "FighterProt.h"
#include "FighterPropCFG.h"
#include "SkillSlots.h"
#include "CommonDef.h" // XXX: for VECATTR_*
#include "Version.h" // XXX: for CVersion
#include "GameBuffManager.h"
#include "BattlePoint.h"
#include "Battle.h"

using namespace NFighterProt;
using namespace NProtoCommon;

namespace NGlobalChatProt { struct SShowInfo;};
using namespace NProtoCommon;

namespace NRoleEvent { struct SFighterSpecInfo; }
using namespace NRoleEvent;

class SFighterLvAttrCFG;
class CCreature;
class CFighter : public CVersion, public enable_shared_from_this<CFighter>, 
    public CGameBuffManager, public CBattlePointOwner, public CPoolObj<CFighter>
{
public:
    CFighter(UINT16 wFighterID,EFighterType eFighterType = eFighter, CCreature* pCreature = NULL, UINT64 qwInstID = 0);
    virtual ~CFighter();

    virtual UINT16 GetID() const { return GetFighterID(); }
    SFighterPropCFG* GetFighterPropConfig() const;
    SFighterLvAttrCFG* GetFighterLvAttrConfig() const;
    UINT8 GetFighterInclination() const;
    UINT8 GetDujieTemplateID() const;

    virtual UINT64 GetRoleID() const;
    virtual UINT64 GetOwnerID() const{ return _qwInstID;};

    ESexType GetSex() const;

    UINT64 GetInstID() const { return _qwInstID; }
    void SetInstID(UINT64 qwInstID) { _qwInstID = qwInstID; }

    UINT16 GetFighterID() const { return _wFighterID; }
    void SetFighterID(UINT16 wFighterID) { _wFighterID = wFighterID; }

    bool GetRecruited() const { return _bRecruited; }
    bool IsRecruited() const { return _bRecruited; }
    void SetRecruited(bool bRecruited) { _bRecruited = bRecruited; }

    UINT8 GetStar() const { return _byStar; }
    void SetStar(UINT8 byStar) { _byStar = byStar; }
    UINT8 GetColor() const;
    void  ResetColor();
    void SetColor(UINT8 byColor, bool bInit = false);

    INT32 GetSlot() const { return _iSlot; }
    void SetSlot(INT32 iSlot) { _iSlot = iSlot; }

    INT32 GetPos() const { return _iPos; }
    void SetPos(INT32 iPos) { _iPos = iPos; }

    CUserPtr GetUser() { return _pUser.lock(); }
    const CUserPtr GetUser() const { return _pUser.lock(); }
    virtual void SetUser(const CUserPtr& pUser) ;

    EFighterType GetType() const { return _eType; }
    void SetType(EFighterType eType) { _eType = eType; }

    bool IsMainFighter() const;
    bool IsHeroFighter() const { return GetType() == eFighterHero; }
    bool IsMonsterFighter() const { return GetType() == eFighterMonster; }

    virtual UINT8 GetLevel() const;
    void SetLevel(UINT8 byLevel, bool bUpdate = true);

    virtual UINT64 GetExp() const { return _qwExp; }
    void SetExp(UINT64 qwExp) { _qwExp = qwExp; }
    bool AddExp(UINT64 qwExp, bool bNotify = true);
    bool SubExp(UINT64 qwExp, bool bNotify = true);

    //写Log日志
    void WriteDujieLog(string &sPeriodName);

    UINT32 GetHP() const;
    void SetHP(UINT32 dwHP);
    void AddHP(UINT32 dwHP);
    void SubHP(UINT32 dwHP);

    UINT32 GetHPMax() const;
    UINT32 GetHPMax2() const;
    void SetHPMax(UINT32 dwHPMax);
    void SetHPMax2(UINT32 dwHPMax);

    UINT32 GetSpiritPower() const { return _dwSpiritPower; }
    void SetSpiritPower(UINT32 dwSpiritPower) { _dwSpiritPower = dwSpiritPower; }
    void AddSpiritPower(UINT32 dwSpiritPower) { _dwSpiritPower += dwSpiritPower; }

    UINT8 GetLianPi() const             { return _byCuiTiLvl[eCuiTiLianPi]; }
    UINT8 GetTongJin() const            { return _byCuiTiLvl[eCuiTiTongJin]; }
    UINT8 GetQiangJi() const            { return _byCuiTiLvl[eCuiTiQiangJi]; }
    UINT8 GetDuanGu() const             { return _byCuiTiLvl[eCuiTiDuanGu]; }
    UINT8 GetHuoLuo() const             { return _byCuiTiLvl[eCuiTiHuoLuo]; }
    UINT8 GetXiSui() const              { return _byCuiTiLvl[eCuiTiXiSui]; }
    void SetLianPi(UINT8 byLianPi)      { _byCuiTiLvl[eCuiTiLianPi]  = byLianPi; }
    void SetTongJin(UINT8 byTongJin)    { _byCuiTiLvl[eCuiTiTongJin] = byTongJin; }
    void SetQiangJi(UINT8 byQiangJi)    { _byCuiTiLvl[eCuiTiQiangJi] = byQiangJi; }
    void SetDuanGu(UINT8 byDuanGu)      { _byCuiTiLvl[eCuiTiDuanGu]  = byDuanGu; }
    void SetHuoLuo(UINT8 byHuoLuo)      { _byCuiTiLvl[eCuiTiHuoLuo]  = byHuoLuo; }
    void SetXiSui(UINT8 byXiSui)        { _byCuiTiLvl[eCuiTiXiSui]   = byXiSui; }
    UINT8 GetCuiTiLevel(ECuiTiType eType) const
    {
        if (eType >= eCuiTiMax)
            return 0;
        return _byCuiTiLvl[eType];
    }
    void SetCuiTiLevel(ECuiTiType eType, UINT8 byLvl)
    {
        if (eType >= eCuiTiMax)
            return;
        _byCuiTiLvl[eType] = byLvl;
    }

    virtual void InitSkills(const TVecUINT32& vecSkillID) { _vecSkillID = vecSkillID; }
    const TVecUINT32& GetInitSkills() const { return _vecSkillID; }

    void InitFighterInfo();
    void InitFighterAttr();
    void InitFighterLvAttr();
    void RegenAllHP() { _dwHP = GetAttr2(EFIGHTATTR_MAXHP); }
    
    //初始化后派生类调用
    virtual void Init(){};
    
    float GetAttr(EFighterAttr eFighterAttr) const;
    float GetAttr2(EFighterAttr eFighterAttr) const;
    bool SetAttr(EFighterAttr eFighterAttr, float fValue);
    bool SetAttr2(EFighterAttr eFighterAttr, float fValue);
    virtual const TVecFloat& GetAttrVec() const final;
    const TVecFloat& GetBPAttrVec() const;
    virtual const TVecFloat& GetAttrVec2() const final;
    TVecFtAttrMod GetFtAttrMod();
    void ApplyFtAttrMod(const TVecFtAttrMod& attr);

    virtual void GetAllSkillsID(TVecUINT32& vecSkillsID) const;
    virtual void AppendBPAttr(TVecFloat& vecAttr) const;

    ECareerType GetJob() const;
    virtual const string GetName() const;

    virtual UINT32 GetNormalAttack() const;

    virtual bool ToProt(SFighterSpecInfo& sFighterInfo) const;
    virtual bool RebuildAttr() const;
    virtual void OnAttrRebuilded() const;

    virtual void SetDirty(bool bDirty, EAttrGroupType eType = eAttrGpMax, bool bFromFgtManager = false) const; // XXX: const because of RebuildAttr is const
    virtual bool IsDirty() const { return _bDirty; }

    UINT16 GetFormation() const { return _wFormationID; }
    void SetFormation(UINT16 wFormationID) { _wFormationID = wFormationID; }

    bool SwapCuiTi(CFighterPtr& pFighter);

    void Update2DB(EDataChange eDataChange = eOpUpdate);

    // BUFF相关
    virtual EBuffType GetBuffType() const { return eBTFighter; }
    virtual void UpdateBuff2DB(const SDBBuffInfo& rDBBuffInfo, EDataChange eDataChange);
    virtual void OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo);

    void SetCreatureBufferAttr(TVecFloat& _vecCreatureBufferAtt);

    // 渡劫相关
    UINT8 GetDujieLevel() const { return _byDujieLevel; }
    UINT32 GetDujieExp() const  { return _dwDujieExp; }
    void SetDujieLevel(UINT8 byLvl) { _byDujieLevel = byLvl; }
    void SetDujieExp(UINT32 dwExp)  { _dwDujieExp = dwExp; }

    CFighterManagerPtr GetFighterManager() const { return _pFighterManager.lock();}

    virtual void AppedBattleInfo(std::string& strInfo){};

protected:
    mutable SFighterPropCFG* _pFighterCfg;
    mutable SFighterLvAttrCFG* _pFighterLvAttrCfg;

public:
    void GetShowInfo(NGlobalChatProt::SShowInfo& sInfo);

    //获取散仙的信息log（心法，技能，粹体等）
    std::string  GetInfoLog() { return _strInfoLog; };

public:
    // 生成战斗模拟器需要的战斗对象
    virtual IBattleFighterPtr ToBattleFighter(UINT8 byTeamID, EBattleType eBattleType);

protected:
    //  获取所有战斗技能
    virtual bool GetAllSkills(TVecUINT32& rvecAllSklls, UINT32& dwNormalAttack) const;
    virtual SFeatureBasePtr GetAppear() const;
    virtual SFeatureBasePtr GetBattleAppear(EBattleType eBattleType) const;

protected:
    // XXX: 将身上需要存储的数据
    UINT64 _qwInstID;
    EFighterType _eType;
    CUserWtr _pUser;
    UINT16 _wFighterID;
    bool _bRecruited;

    UINT8 _byStar;      // 星级

    INT32 _iSlot;       // 在容器中的位置
    INT32 _iPos;        // 在阵型中的位置 XXX: (-1)表示不在阵型中

    UINT8 _byLevel;     // 等级
    UINT64 _qwExp;      // 经验

    UINT16 _wFormationID;

    UINT8 _byCuiTiLvl[eCuiTiMax];

    UINT32 _dwHP;           // 当前血量
    TVecUINT32 _vecSkillID; // XXX: 配置里的技能

    UINT8 _byDujieLevel;
    UINT32 _dwDujieExp;

    mutable UINT8 _byColor; // 品质

    UINT32 _dwSpiritPower; //元神力

    // XXX: 以上为将身上需要存储的数据

    TVecFloat _vecFighterAttr; // 属性列表
    mutable TVecFloat _vecBPAttr;   // 用于计算战斗力的属性之和
    mutable TVecFloat _vecFinalAttr; // 所有属性之和
    mutable TVecFloat _vecFinalAttr2; // 所有属性之和(注：加百分比之后的属性之和)
    mutable bool _bDirty;

    CFighterManagerWtr      _pFighterManager; // 将管理类
    TVecFloat               _vecCreatureBufferAttr;//外部buffer属性

    //目前仅monster有效
    CCreature* _pCreature;

    //装备属性log
    mutable std::string _strInfoLog;
};

TVecFloat& operator+=(TVecFloat& vecAttr1, const TVecFloat& vecAttr2);

#endif // FIGHTER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

