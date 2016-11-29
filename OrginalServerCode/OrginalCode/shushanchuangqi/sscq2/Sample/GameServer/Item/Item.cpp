#include "stdafx.h"
#include "Item.h"
#include "Protocols.h"
#include "ItemMgr.h"
#include "GameScript.h"
#include "Store.h"
#include "User.h"
#include "Player.h"
#include "SysMsgDefine.h" // for Msg
#include "Parameter.h" // for SParamConfig
#include "Citta.h"
#include "Trump.h"
#include "EquipTrump.h"
#include "Gemstone.h"

CItem::CItem(UINT16 wItemID) : 
    CExpireItem(CItemMgr::GetItemConfig(wItemID)->oItemCfg._ItemTimeID), 
    _wItemID(wItemID), _qwInstID(0), _eBindType(eBindNone), _bBind(false), _byStoreType(eStoreNone), _wIndex(-1)
{
    _pItemInfo = CItemMgr::GetItemConfig(_wItemID);
}

float CItem::GetGoldPrice()
{
    return CItemMgr::GetGoldPrice(GetItemID());
}

CItem::~CItem()
{
    //LOG_CRI << "Delete Item";
}
const SItemCFG& CItem::GetItemConfig() const
{ 
    if (CItemMgr::GetVersion() != GetVersion())
        _pItemInfo = CItemMgr::GetItemConfig(_wItemID);
    return _pItemInfo->oItemCfg;
}

void CItem::SetItemID(UINT16 wItemID)
{
    if (_wItemID && _wItemID != wItemID)
        _pItemInfo = CItemMgr::GetItemConfig(wItemID);
    _wItemID = wItemID;
}

EItemType CItem::GetItemType() const
{
    return CItemType::GetItemType(GetItemConfig()._ID);
}

EItemType CItem::GetItemType(UINT16 wItemID)
{
    return CItemType::GetItemType(wItemID);
}

EItemType CItem::GetItemType(const SItemCFG& rItemCfg)
{
    return CItemType::GetItemType(rItemCfg._ID);
}

EItemSubType CItem::GetItemSubType() const
{
    return GetItemSubType(GetItemConfig());
}

EItemSubType CItem::GetItemSubType(const SItemCFG& rItemCfg)
{
    return (EItemSubType)rItemCfg._Type;
}

EItemSubType CItem::GetItemSubType(UINT16 wItemID)
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return eItemSubNone;
    return GetItemSubType(pItemInfo->oItemCfg);
}

void CItem::SetBindType(EStoreType eStoreType, EBindType eBindType, const CUserPtr& pUser /*= NULL*/)
{
    switch(eBindType)
    {
        case eBindNone:
            if(_bBind)
                _bBind = false;
            break;
        default:
            break;
    }
    _eBindType = eBindType;
    if(!_bBind)
        _bBind = _eBindType == eBindGet;
    if(pUser != NULL)
    {
        pUser->SendPkg(g_ItemProtS.BuildPkg_ItemBindChangeNtf(eStoreType, _qwInstID, _eBindType, _bBind));
    }
}

void CItem::SetBind(bool bBind)
{
    if(bBind && _eBindType == eBindNone)
    {
        _eBindType = eBindGet;
    }
    _bBind = bBind;
}

bool CItem::IsStackItem(UINT16 wItemID)
{
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if(pItemInfo == NULL)
        return false;
    return IsStackItem(pItemInfo->oItemCfg);
}

bool CItem::OnUse(CStore& rStore, UINT16 wCount, bool bDel, UINT16 towhere)
{
    if(!bDel)
    {
        if(GetExpireType() == eExpireUse)
            StartExpire();
    }
    return rStore.DelItem(*this,wCount, true,true, towhere);
}

#if 0
bool CItem::OnUse(CRoleEquipForm& rStore, UINT16 wCount, bool bDel/* = true*/)
{
    if(!bDel)
    {
        if(GetExpireType() == eExpireUse)
            StartExpire();

        if(GetItemConfig()._CD > 0)
        {
            CUserPtr pUser = rStore.GetUserPtr();
            if(NULL != pUser)
                pUser->GetColdItem().OnUseItem(*this);
        }
    }

    return rStore.DelItem(*this);//道具用完
}
#endif

bool CItem::CanUse(UINT16 wCount)
{
    // TODO:
    return true;
}

void CItem::OnAddToStore(CStore& rStore, bool bNotify /*= true*/)
{
    if(_eBindType == eBindGet)
        SetBind(true);
}

void CItem::TimerCheck(time_t tNow, CStore& rStore)
{
    if(CanExpire(tNow) && CExpireItem::OnExpire())
    {
        if(_pItemTimeCfg != NULL)//直接删除
        {
            //系统消息
            char szBuffer[64];
            sprintf_s(szBuffer, "[msgitem,%u,%u,%u]", GetItemConfig()._ID, GetQuality(), GetCount());
            if(_pItemTimeCfg->_Disposal == 0)
            {
                // TODO:
                rStore.DelItemByInstID(_qwInstID, true, true, NLogDataDefine::ItemTo_UserDeptORPack);	
                rStore.SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgItemTimeOutDel, BuildStrVec(szBuffer)));
            }
            else
                rStore.SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgItemTimeOut, BuildStrVec(szBuffer)));
        }
    }
}

SItemPtr CItem::ToProt() const
{
    SItem* pItem = new SItem;
    if(pItem != NULL)
        ToStream(*pItem);
    return SItemPtr(pItem);
}

void CItem::FromStream(const SItem& rStream)
{
    _qwInstID = rStream.sItemInfo.qwInstID;
    _byStoreType = rStream.sItemInfo.byStoreType;
    _wIndex = rStream.sItemInfo.wIndex;
    _bBind = rStream.sItemInfo.byBind;
    _dwExpireTime = rStream.sItemInfo.dwExpireTime;
    _bExpired = rStream.sItemInfo.byExpired;
}
void CItem::ToStream(SItem& rStream) const
{
    rStream.sItemInfo.qwInstID = _qwInstID;
    rStream.sItemInfo.wItemID = GetItemID();
    rStream.sItemInfo.byStoreType = _byStoreType;
    rStream.sItemInfo.wIndex = _wIndex;
    rStream.sItemInfo.wCount = GetCount();
    rStream.sItemInfo.byBind = _bBind;
    rStream.sItemInfo.byExpired = _bExpired;
    rStream.sItemInfo.dwExpireTime = _dwExpireTime;
}

UINT16 CItem::GetTypeOrder(const SItemCFG& rItemCfg)
{
    switch(rItemCfg._Type)
    {
        //1. 技能书
        case eItemSkillBook:
            return __COUNTER__;
            //2. 宝石
        case eItemStone:
            return __COUNTER__;
            //3.其他
        case eItemOther:
            return __COUNTER__;
            //5. 材料
        case eItemStuff:
            return __COUNTER__;
            //6. 任务
        case eItemTask:
            return __COUNTER__;
    }
    return __COUNTER__;
}

bool operator<(CItem& left, CItem& right)
{
    //道具大类
    UINT16 wLeftOrder = CItem::GetTypeOrder(left.GetItemCfg());
    UINT16 wRightOrder = CItem::GetTypeOrder(right.GetItemCfg());
    if(wLeftOrder < wRightOrder)
        return true;
    if(wLeftOrder > wRightOrder)
        return false;

    //道具小类
    UINT16 wLeftSubType = CItem::GetItemSubType(left.GetItemCfg());
    UINT16 wRightSubType = CItem::GetItemSubType(right.GetItemCfg());
    if(wLeftSubType < wRightSubType)
        return true;
    if(wLeftSubType > wRightSubType)
        return false;

    //道具等级
    UINT8 byLeftGrade = left.GetItemCfg()._Level;
    UINT8 byRightGrade = right.GetItemCfg()._Level;
    if(byLeftGrade > byRightGrade)
        return true;
    if(byLeftGrade < byRightGrade)
        return false;
    UINT8 byLeftLevelValue = left.GetItemCfg()._LevelValue;
    UINT8 byRightLevelValue = right.GetItemCfg()._LevelValue;
    if(byLeftLevelValue > byRightLevelValue)
        return true;
    if(byLeftLevelValue < byRightLevelValue)
        return false;

    //品质排序
    UINT16 wLeftQuality = left.GetItemCfg()._Quality;
    UINT16 wRightQuality = right.GetItemCfg()._Quality;
    if(wLeftQuality > wRightQuality)
        return true;
    if(wLeftQuality < wRightQuality)
        return false;

    //ID号排序
    UINT32 dwLeftItemIdx = left.GetItemCfg()._ID;
    UINT32 dwRightItemIdx = right.GetItemCfg()._ID;
    if(dwLeftItemIdx < dwRightItemIdx)
        return true;
    if(dwLeftItemIdx > dwRightItemIdx)
        return false;

    //绑定排序
    UINT8 byLeftBind = left.IsBind() ? 0 : 1;
    UINT8 byRightBind = right.IsBind() ? 0 : 1;
    if(byLeftBind < byRightBind)
        return true;
    if(byLeftBind > byRightBind)
        return false;

    //堆叠排序
    if(left.IsStackItem() && right.IsStackItem())
    {
        return left.GetCount() > right.GetCount();
    }

    //堆叠排序
    if(left.IsStackItem() && right.IsStackItem())
    {
        return left.GetOptCount() > right.GetOptCount();
    }

    //倒计时间
    UINT32 dwLeftExpireTime = 0;
    UINT32 dwRightExpireTime = 0;
    if(left.HasExpiration())
        dwLeftExpireTime = left.GetExpireTime();
    else
        dwLeftExpireTime = (UINT32)-1;
    if(right.HasExpiration())
        dwRightExpireTime = right.GetExpireTime();
    else
        dwRightExpireTime = (UINT32)-1;
    if(dwLeftExpireTime > dwRightExpireTime)
        return true;
    if(dwLeftExpireTime < dwRightExpireTime)
        return false;

    return false;
}

void CItem::ItemChangeNotify(CUser& rUser, CItem& rItem, EStoreType eStoreType, UINT16 wIndex, UINT64 qwOwnerID/* = 0*/)
{
    rUser.SendPkg(g_ItemProtS.BuildPkg_ItemChangeNotify(eStoreType, qwOwnerID, rItem.ToProt()));
}

void CItem::Update2DB(CItem& rItem, UINT64 qwUserID, UINT64 qwOwnerID, EStoreType eStoreType, UINT16 wIndex, EDataChange eDataChange)
{
    // XXX: 物品属性有变化时需要在这里增加代码
    SItemPtr ptr;
    EDataType eDataType = eTypeItemInfo;
    switch (rItem.GetItemType())
    {
        case eItemCitta:
            {
                ptr.reset(new SCitta);
                CCitta& rCitta = static_cast<CCitta&>(rItem);
                if (!rCitta.GetOwnerID())
                    rCitta.SetOwnerID(qwOwnerID);
                SCittaPtr sptr = dynamic_pointer_cast<SCitta>(ptr);
                //rCitta.ToStream(*sptr);
                rCitta.ToDBStream(*sptr);
                eDataType = eTypeCittaInfo;
            }
            break;
        case eItemTrump:
            {
                ptr.reset(new STrump);
                CTrump& rTrump = static_cast<CTrump&>(rItem);
                STrumpPtr sptr = dynamic_pointer_cast<STrump>(ptr);
                rTrump.ToStream(*sptr);
                eDataType = eTypeTrumpInfo;
            }
            break;
        case eItemFashion:
            {
                ptr.reset(new SFashion);
                CFashion& rFashion = static_cast<CFashion&>(rItem);
                SFashionPtr eptr = dynamic_pointer_cast<SFashion>(ptr);
                rFashion.ToStream(*eptr);
                eDataType = eTypeFashionInfo;
            }
            break;
        case eItemEquipTrump:
            {
                ptr.reset(new SEquipTrump);
                CEquipTrump& rEquipTrump = static_cast<CEquipTrump&>(rItem);
                SEquipTrumpPtr sptr = dynamic_pointer_cast<SEquipTrump>(ptr);
                rEquipTrump.ToStream(*sptr);
                eDataType = eTypeEquipTrumpInfo;
            }
            break;
        case eItemStone:
        default:
            {
                ptr.reset(new SItem);
                rItem.ToStream(*ptr);
            }
            break;
    }

    ptr->sItemInfo.qwInstID = rItem.GetInstID();
    // 位置可能发生变化
    ptr->sItemInfo.byStoreType = eStoreType;
    ptr->sItemInfo.wIndex = wIndex;
    rItem.SetStoreType(eStoreType);
    rItem.SetIndex(wIndex);
    string strData;
    COutArchive iar(strData);
    SItem_Wrapper wrapper(ptr);
    iar << wrapper;
    g_Game2DBCommC.Send_RoleDataUpdate(qwUserID, eDataType, eDataChange, strData);
}

void CItem::GetShowMsg(CItem& rItem, NGlobalChatProt::SShowInfo& stShow)
{
    SItemPtr ptr;
    switch (rItem.GetItemType())
    {
        case eItemCitta:
            ptr.reset(new SCitta);
            break;
        case eItemTrump:
            ptr.reset(new STrump);
            break;
        case eItemFashion:
            ptr.reset(new SFashion);
            break;
        default:
            ptr.reset(new SItem);
            break;
    }

    ptr->sItemInfo.qwInstID = rItem.GetInstID();
    switch (rItem.GetItemType())
    {
        case eItemCitta:
            {
                CCitta& rCitta = static_cast<CCitta&>(rItem);
                SCittaPtr sptr = dynamic_pointer_cast<SCitta>(ptr);
                rCitta.ToStream(*sptr);
            }
            break;
        case eItemTrump:
            {
                CTrump& rTrump = static_cast<CTrump&>(rItem);
                STrumpPtr sptr = dynamic_pointer_cast<STrump>(ptr);
                rTrump.ToStream(*sptr);
            }
            break;
        case eItemFashion:
            {
                CFashion& rFashion = static_cast<CFashion&>(rItem);
                SFashionPtr eptr = dynamic_pointer_cast<SFashion>(ptr);
                rFashion.ToStream(*eptr);
            }
            break;

        default:
            rItem.ToStream(*ptr);
            break;
    }

    // 位置可能发生变化

    COutArchive iar(stShow.strShowInfo);
    iar << UINT8(NGlobalChatProt::eShowItem); 
    SItem_Wrapper wrapper(ptr);
    iar << wrapper;
}


UINT32 CItem::ToSize()
{
    UINT32 dwSize = sizeof(*this) + sizeof(*_pItemInfo);
    return dwSize;
}
