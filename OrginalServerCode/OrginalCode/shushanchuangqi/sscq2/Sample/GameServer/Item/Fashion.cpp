#include "CommonDef.h"
#include "ItemMgr.h"
#include "ProtoCommon.h"
#include "Fashion.h"

using namespace NProtoCommon;

CFashion::CFashion(UINT16 wItemID)
    : CItem(wItemID), _byLevel(1), _dwExp(0), _bySelected(0), _byHide(0), _bDirty(true)
{
}

CFashion::~CFashion()
{}

void CFashion::InitItemAttr()
{
    VECATTR_RESET(_vecItemAttr);
    /*
    SItemInfo* pItemInfo = GetItemInfo();
    if (!pItemInfo)
        return;
    VECATTR_RESET(_vecItemAttr);
    SItemAttrCFGEx* pItemAttrCFG = pItemInfo->pItemAttr;
    if (pItemAttrCFG)
    {
        SItemAttrCFGEx& rItemAttrCFG = *pItemAttrCFG;
        PHYATK_ADD(_vecItemAttr, pItemAttrCFG);
        MGCATK_ADD(_vecItemAttr, pItemAttrCFG);
        PHYDEF_ADD(_vecItemAttr, pItemAttrCFG);
        MGCDEF_ADD(_vecItemAttr, pItemAttrCFG);
        PHYRDC_ADD(_vecItemAttr, pItemAttrCFG);
        MGCRDC_ADD(_vecItemAttr, pItemAttrCFG);
        MAXHP_ADD(_vecItemAttr, pItemAttrCFG);
        SPEED_ADD(_vecItemAttr, pItemAttrCFG);
        HIT_ADD(_vecItemAttr, pItemAttrCFG);
        HITRATE_ADD(_vecItemAttr, pItemAttrCFG);
        DODGE_ADD(_vecItemAttr, pItemAttrCFG);
        DODGERATE_ADD(_vecItemAttr, pItemAttrCFG);
        CRITICAL_ADD(_vecItemAttr, pItemAttrCFG);
        CRTRATE_ADD(_vecItemAttr, pItemAttrCFG);
        ANTICRITCAL_ADD(_vecItemAttr, pItemAttrCFG);
        ANTICRTRATE_ADD(_vecItemAttr, pItemAttrCFG);
        BLOCK_ADD(_vecItemAttr, pItemAttrCFG);
        BLOCKRATE_ADD(_vecItemAttr, pItemAttrCFG);
        PIERCE_ADD(_vecItemAttr, pItemAttrCFG);
        PIERCERATE_ADD(_vecItemAttr, pItemAttrCFG);
        COUNTER_ADD(_vecItemAttr, pItemAttrCFG);
        COUNTERRATE_ADD(_vecItemAttr, pItemAttrCFG);
        RESIST_ADD(_vecItemAttr, pItemAttrCFG);
        RESISTRATE_ADD(_vecItemAttr, pItemAttrCFG);
        INITAURA_ADD(_vecItemAttr, pItemAttrCFG);
        MAXAURA_ADD(_vecItemAttr, pItemAttrCFG);
        CRIEXTRAADD_ADD(_vecItemAttr, pItemAttrCFG);
        CRIEXTRARDC_ADD(_vecItemAttr, pItemAttrCFG);
        METALATK_ADD(_vecItemAttr, pItemAttrCFG);
        WOODATK_ADD(_vecItemAttr, pItemAttrCFG);
        WATERATK_ADD(_vecItemAttr, pItemAttrCFG);
        FIREATK_ADD(_vecItemAttr, pItemAttrCFG);
        EARTHATK_ADD(_vecItemAttr, pItemAttrCFG);
        METALDEF_ADD(_vecItemAttr, pItemAttrCFG);
        WOODDEF_ADD(_vecItemAttr, pItemAttrCFG);
        WATERDEF_ADD(_vecItemAttr, pItemAttrCFG);
        FIREDEF_ADD(_vecItemAttr, pItemAttrCFG);
        EARTHDEF_ADD(_vecItemAttr, pItemAttrCFG);
        PHYATK_PER_ADD(_vecItemAttr, pItemAttrCFG);
        MGCATK_PER_ADD(_vecItemAttr, pItemAttrCFG);
        PHYDEF_PER_ADD(_vecItemAttr, pItemAttrCFG);
        MGCDEF_PER_ADD(_vecItemAttr, pItemAttrCFG);
        MAXHP_PER_ADD(_vecItemAttr, pItemAttrCFG);
        SPEED_PER_ADD(_vecItemAttr, pItemAttrCFG);
        HIT_PER_ADD(_vecItemAttr, pItemAttrCFG);
        DODGE_PER_ADD(_vecItemAttr, pItemAttrCFG);
        CRITICAL_PER_ADD(_vecItemAttr, pItemAttrCFG);
        ANTICRITCAL_PER_ADD(_vecItemAttr, pItemAttrCFG);
        BLOCK_PER_ADD(_vecItemAttr, pItemAttrCFG);
        PIERCE_PER_ADD(_vecItemAttr, pItemAttrCFG);
        COUNTER_PER_ADD(_vecItemAttr, pItemAttrCFG);
        RESIST_PER_ADD(_vecItemAttr, pItemAttrCFG);
        ANTIEFFECT_ADD(_vecItemAttr, pItemAttrCFG);
        //COUTEREXTRAADD_ADD(_vecItemAttr, pItemAttrCFG);
        //COUTEREXTRARDC_ADD(_vecItemAttr, pItemAttrCFG);
    }
    */

    InitFashionLvAttr();
}

void CFashion::InitFashionLvAttr()
{
    /*
    if (GetLevel() <= 1)
        return;
    */
    SFashionAttrCFG* pFashionAttrCfg = CItemMgr::GetFashionAttrConfig(GetItemID(), GetLevel());
    if (!pFashionAttrCfg)
        return;

    PHYATK_ADD(_vecItemAttr, pFashionAttrCfg);
    MGCATK_ADD(_vecItemAttr, pFashionAttrCfg);
    PHYDEF_ADD(_vecItemAttr, pFashionAttrCfg);
    MGCDEF_ADD(_vecItemAttr, pFashionAttrCfg);
    PHYRDC_ADD(_vecItemAttr, pFashionAttrCfg);
    MGCRDC_ADD(_vecItemAttr, pFashionAttrCfg);
    MAXHP_ADD(_vecItemAttr, pFashionAttrCfg);
    SPEED_ADD(_vecItemAttr, pFashionAttrCfg);
    HIT_ADD(_vecItemAttr, pFashionAttrCfg);
    HITRATE_ADD(_vecItemAttr, pFashionAttrCfg);
    DODGE_ADD(_vecItemAttr, pFashionAttrCfg);
    DODGERATE_ADD(_vecItemAttr, pFashionAttrCfg);
    CRITICAL_ADD(_vecItemAttr, pFashionAttrCfg);
    CRTRATE_ADD(_vecItemAttr, pFashionAttrCfg);
    ANTICRITCAL_ADD(_vecItemAttr, pFashionAttrCfg);
    ANTICRTRATE_ADD(_vecItemAttr, pFashionAttrCfg);
    BLOCK_ADD(_vecItemAttr, pFashionAttrCfg);
    BLOCKRATE_ADD(_vecItemAttr, pFashionAttrCfg);
    PIERCE_ADD(_vecItemAttr, pFashionAttrCfg);
    PIERCERATE_ADD(_vecItemAttr, pFashionAttrCfg);
    COUNTER_ADD(_vecItemAttr, pFashionAttrCfg);
    COUNTERRATE_ADD(_vecItemAttr, pFashionAttrCfg);
    RESIST_ADD(_vecItemAttr, pFashionAttrCfg);
    RESISTRATE_ADD(_vecItemAttr, pFashionAttrCfg);
    INITAURA_ADD(_vecItemAttr, pFashionAttrCfg);
    MAXAURA_ADD(_vecItemAttr, pFashionAttrCfg);
    CRIEXTRAADD_ADD(_vecItemAttr, pFashionAttrCfg);
    CRIEXTRARDC_ADD(_vecItemAttr, pFashionAttrCfg);
    METALATK_ADD(_vecItemAttr, pFashionAttrCfg);
    WOODATK_ADD(_vecItemAttr, pFashionAttrCfg);
    WATERATK_ADD(_vecItemAttr, pFashionAttrCfg);
    FIREATK_ADD(_vecItemAttr, pFashionAttrCfg);
    EARTHATK_ADD(_vecItemAttr, pFashionAttrCfg);
    METALDEF_ADD(_vecItemAttr, pFashionAttrCfg);
    WOODDEF_ADD(_vecItemAttr, pFashionAttrCfg);
    WATERDEF_ADD(_vecItemAttr, pFashionAttrCfg);
    FIREDEF_ADD(_vecItemAttr, pFashionAttrCfg);
    EARTHDEF_ADD(_vecItemAttr, pFashionAttrCfg);
    PHYATK_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    MGCATK_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    PHYDEF_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    MGCDEF_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    MAXHP_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    SPEED_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    HIT_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    DODGE_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    CRITICAL_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    ANTICRITCAL_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    BLOCK_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    PIERCE_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    COUNTER_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    RESIST_PER_ADD(_vecItemAttr, pFashionAttrCfg);
    ANTIEFFECT_ADD(_vecItemAttr, pFashionAttrCfg);
    //COUTEREXTRAADD_ADD(_vecItemAttr, pFashionAttrCfg);
    //COUTEREXTRARDC_ADD(_vecItemAttr, pFashionAttrCfg);
}

void CFashion::RebuildAttr()
{
    if (!IsDirty())
        return;
    InitItemAttr();

    SetDirty(false);
}

void CFashion::AppendAttr(TVecFloat& vecAttr)
{
    if (IsDirty())
        RebuildAttr();
    vecAttr += _vecItemAttr;
}

SItemPtr CFashion::ToProt() const
{
    SFashion* pFashion = new SFashion;
    if(pFashion == NULL)
        return NULL;
    if(!ToStream(*pFashion))
    {
        delete pFashion;
        return NULL;
    }
    return SItemPtr(pFashion);
}

bool CFashion::FromStream(const SFashion& rStream)
{
    CItem::FromStream(rStream);

    _byLevel = rStream.byLevel;
    _dwExp = rStream.dwExp;
    _bySelected = rStream.bySelected;
    _byHide = rStream.byHide;
    return true;
}

bool CFashion::ToStream(SFashion& rStream) const
{
    CItem::ToStream(rStream);

    rStream.byLevel = _byLevel;
    rStream.dwExp = _dwExp;
    rStream.bySelected = _bySelected;
    rStream.byHide = _byHide;
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

