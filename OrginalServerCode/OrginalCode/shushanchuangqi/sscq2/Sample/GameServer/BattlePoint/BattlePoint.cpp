#include "BattlePoint.h"
#include "ProtoCommon.h"
#include "Version.h"
#include "CommonDef.h"
#include "Skill.h"
#include "Battle.h"

using namespace NProtoCommon;

UINT64 CBattlePointCalucator::_qwVersion = VERSION_INIT;

CBattlePointOwner::CBattlePointOwner():
    _dwBattlePoint(0), _bDirty(true)
{
}

CBattlePointOwner::~CBattlePointOwner()
{
}

void CBattlePointOwner::SetDirty() const
{
    _bDirty = true;
}

bool CBattlePointOwner::IsDirty() const
{
    return _bDirty;
}

UINT32 CBattlePointOwner::GetBattlePoint() const
{
    if (IsDirty())
        RebuildBattlePoint();
    return _dwBattlePoint;
}

void CBattlePointOwner::RebuildBattlePoint() const
{
    TVecFloat vecAttr;
    AppendBPAttr(vecAttr);

    TVecUINT32 vecSkills;
    GetAllSkillsID(vecSkills);

    _dwBattlePoint = 0;
    _dwBattlePoint += BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
    _dwBattlePoint += BattlePointCalucator.CalcSkillBattlePoint(vecSkills);
    _bDirty = false;
}

// 初始化战力计算相关
bool CBattlePointCalucator::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/AttrShow.xml";
    CAttrShowLoader oAttrShowLoader;
    if (!oAttrShowLoader.LoadData(strPath))
    {
        LOG_CRI << "oAttrShowLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    VECATTR_RESET(_vecAttrFactor);
    for(size_t i = 0; i < oAttrShowLoader._vecData.size(); ++i)
    {
        SAttrShowCFG* pAttrShowCFG = oAttrShowLoader._vecData[i];
        if (!pAttrShowCFG || pAttrShowCFG->_Attr_ID == 0)
            continue;

        FLOAT fFactor = FLOAT(pAttrShowCFG->_Battle_Points) / 10;
        VECATTR_SET(_vecAttrFactor, i+1, fFactor);
    }
    IBattleFighter::_funAttrBP     = &(CalcAttrBattlePoint2);
    IBattleFighter::_funSkillBP    = &(CalcSkillBattlePoint2);
    return true;
}

UINT32 CBattlePointCalucator::CalcAttrBattlePoint2(const TVecFloat& rvecAttr)
{
    FLOAT fBattlePoint = 0;
    for (size_t dwIndex = 0; dwIndex < rvecAttr.size(); ++dwIndex)
    {
        if (dwIndex >= CBattlePointCalucator::Instance()._vecAttrFactor.size())
            break;
        fBattlePoint += CBattlePointCalucator::Instance()._vecAttrFactor[dwIndex] * rvecAttr[dwIndex];
    }
    return fBattlePoint;
}

UINT32 CBattlePointCalucator::CalcSkillBattlePoint2(const TVecUINT32& vecSkillsID)
{
    FLOAT fBattlePoint = 0;
    for (size_t i = 0; i < vecSkillsID.size(); ++ i)
    {
        SSkillEfPtr pSkillEfCfg = CSkillMgr::Instance().GetSkillEf(vecSkillsID[i]);
        if (pSkillEfCfg)
        {
            SSkillPtr pSkill = CSkillMgr::Instance().GetSkill(SKILL_ID(vecSkillsID[i]));
            if (pSkill->_eType != eSkillBeauty && pSkill->_eType != eSkillCombine)
                fBattlePoint += pSkillEfCfg->_dwBattlePoint;
        }
    }
    return fBattlePoint;
}

UINT32 CBattlePointCalucator::CalcAttrBattlePoint(const TVecFloat& rvecAttr) const
{
    FLOAT fBattlePoint = 0;
    for (size_t dwIndex = 0; dwIndex < rvecAttr.size(); ++dwIndex)
    {
        if (dwIndex >= _vecAttrFactor.size())
            break;
        fBattlePoint += _vecAttrFactor[dwIndex] * rvecAttr[dwIndex];
    }
    return fBattlePoint;
}

UINT32 CBattlePointCalucator::CalcSkillBattlePoint(const TVecUINT32& vecSkillsID) const
{
    FLOAT fBattlePoint = 0;
    for (size_t i = 0; i < vecSkillsID.size(); ++ i)
    {
        SSkillEfPtr pSkillEfCfg = CSkillMgr::Instance().GetSkillEf(vecSkillsID[i]);
        if (pSkillEfCfg)
            fBattlePoint += pSkillEfCfg->_dwBattlePoint;
    }
    return fBattlePoint;
}

