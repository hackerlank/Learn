#include "Trump.h"
#include "TrumpMgr.h"
#include "User.h"
#include "Pack.h"
#include "CommonDef.h"

#include "BattlePoint.h"

CTrump::CTrump(UINT16 wItemID):
    CItem(wItemID),
    _bUsed(0), _dwExp(0), _wLevel(1), _wRank(1)
{
}

CTrump::~CTrump()
{
}

SItemPtr CTrump::ToProt() const
{
    STrump* pTrump = new STrump;
    if(pTrump == NULL)
        return NULL;
    if(!ToStream(*pTrump))
    {
        delete pTrump;
        return NULL;
    }
    return SItemPtr(pTrump);
}

bool CTrump::FromStream(const STrump& rStream)
{
    CItem::FromStream(rStream);

    _bUsed  = rStream.byUsed;
    _wLevel = rStream.wLevel;
    _wRank  = rStream.wRank;
    _dwExp  = rStream.dwExp;

    return true;
}

bool CTrump::ToStream(STrump& rStream) const
{
    CItem::ToStream(rStream);
    rStream.qwRoleID = GetRoleID();
    rStream.byActived = 1;
    rStream.byUsed = _bUsed?1:0;
    rStream.dwExp = _dwExp;
    rStream.wLevel = _wLevel;
    rStream.wRank = _wRank;
    return true;
}

void    CTrump::SetRoleID(UINT64 qwRoleID)
{
    _qwRoleID = qwRoleID;
}

UINT64  CTrump::GetRoleID() const
{
    return _qwRoleID;
}

UINT8 CTrump::GetUsed() const
{
    return _bUsed;
}

void CTrump::SetUsed(UINT8 byIndex/* = 0*/)
{
    _bUsed = byIndex;
}

UINT32 CTrump::GetExp()     const
{
    return _dwExp;
}

UINT16 CTrump::GetIntensifyLevel()   const
{
    return _wLevel;
}

UINT16 CTrump::GetRank()    const
{
    return _wRank;
}

void CTrump::GetHaloAttr(TVecFloat& rvecAttr) const
{
    CTrumpMgr::Instance().GetHaloAttr(rvecAttr, GetID(), GetIntensifyLevel(), GetRank());
}

void CTrump::GetExtraAttr(TVecFloat& rvecAttr) const
{
    CTrumpMgr::Instance().GetExtraAttr(rvecAttr, GetID(), GetIntensifyLevel(), GetRank());
}

void CTrump::GetActiveAttr(TVecFloat& rvecAttr) const
{
    CTrumpMgr::Instance().GetActiveAttr(rvecAttr, GetID(), GetIntensifyLevel(), GetRank());
}

// 返回带等级的技能ID
UINT32 CTrump::GetSkill()     const
{
    return CTrumpMgr::Instance().GetSkill(GetID(), GetLevel(), GetRank());
}

// 法宝祭炼
ETrumpResult CTrump::Upgrade(bool bOneKey, CUserPtr pUser, UINT32& dwAddExp, UINT32& dwCount)
{
    if (!pUser)
        return eTrumpFailed;
    ETrumpResult eResult = eTrumpFailed;
    STrumpUpgradeMaterial sMaterial;
    if (!CTrumpMgr::Instance().GetUpgradeMaterial(GetID(), GetIntensifyLevel(), GetRank(), sMaterial))
        return eTrumpFailed;
    CPack& rPack = pUser->GetPack();
    UINT16 wMaxCount = rPack.GetItemCount(sMaterial.wItemID);
    if (wMaxCount < sMaterial.dwItemCount)
        return eTrumpUpgradeMaterialLack;
    sMaterial.dwItemCount = wMaxCount;  //背包剩余道具数量
    dwCount = CTrumpMgr::Instance().Upgrade(pUser, GetID(), _wLevel, _wRank, _dwExp, sMaterial, bOneKey, dwAddExp);
    if (dwCount)
    {
        rPack.DelItemByItemID(sMaterial.wItemID, static_cast<UINT16>(dwCount), true, NLogDataDefine::ItemTo_TrumpUpgrade);
        eResult = eTrumpSuccess;
    }
    return eResult;
}

// 法宝升阶
ETrumpResult CTrump::Evolve(CUserPtr pUser)
{
    if (!pUser)
        return eTrumpFailed;
    ETrumpResult eResult = eTrumpFailed;
    STrumpEvolveMaterial sMaterial;
    if (!CTrumpMgr::Instance().GetEvolveMaterial(GetID(), GetIntensifyLevel(), GetRank(), sMaterial))
        return eTrumpFailed;
    CPack& rPack = pUser->GetPack();
    UINT16 wMaxCount = rPack.GetItemCount(sMaterial.wItemID);
    if (wMaxCount < sMaterial.dwItemCount)
        return eTrumpEvolveMaterialLack;
    UINT32 dwUsedCount = CTrumpMgr::Instance().Evolve(GetID(), _wLevel, _wRank, _dwExp, sMaterial);
    if (dwUsedCount)
    {
        rPack.DelItemByItemID(sMaterial.wItemID, static_cast<UINT16>(dwUsedCount), true, NLogDataDefine::ItemTo_TrumpEvolve);
        eResult = eTrumpSuccess;
    }
    return eResult;
}

UINT32 CTrump::GetBattlePoint() const
{
    UINT32 dwBattlePoint = 0;

    TVecFloat vecAttr;
    VECATTR_RESET(vecAttr);

    GetHaloAttr(vecAttr);
    GetExtraAttr(vecAttr);
    GetActiveAttr(vecAttr);

    TVecUINT32 vecSkillsID;
    vecSkillsID.push_back(GetSkill());

    dwBattlePoint += BattlePointCalucator.CalcAttrBattlePoint(vecAttr);
    dwBattlePoint += BattlePointCalucator.CalcSkillBattlePoint(vecSkillsID);

    return dwBattlePoint;
}

// 法宝变得超级牛逼
void CTrump::Super()
{
    CTrumpMgr::Instance().Super(GetID(), _wLevel, _wRank, _dwExp);
}

