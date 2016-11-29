#pragma once
#include "Item.h"
#include "Store.h"
#include "SysMsgDefine.h"
#include "ItemProtS.h"
#include "ChatProtS.h"
#include "User.h"
#include "ItemMgr.h"
#include "Protocols.h"
#include "Game2CenterLog.h"

using namespace NGame2CenterLog;

class CStackItem : public CItem
{
	friend class CItemMgr;
public:
	DEF_NEW_DELETE(CStackItem);
	CStackItem(UINT16 wItemID, UINT16 wCount) : CItem(wItemID), _wCurCount(wCount), _wOptCount(0) { }
	virtual ~CStackItem(){ }

	virtual UINT16 GetCount() const { return _wCurCount; }
	bool SetCount(UINT16 wCount);
	bool AddCount(UINT16 wCount);
	UINT16 GetEmptyCount();
	bool CanMerge(const CStackItem& rStackItem, bool bCheckBind = true) const;
	bool CanMerge(UINT16 wItemID, UINT8 byQuality, bool bBind, UINT32 dwTimeID) const;
	virtual UINT16 GetOptCount() const { return _wOptCount; }
	bool SetOptCount(UINT16 wOptCount);

	virtual bool OnUse(CStore& rStore, UINT16 wCount, bool bDel, UINT16 toWhere);
	//virtual bool OnUse(CRoleEquipForm& rStore, UINT16 wCount, bool bDel = true);
	virtual bool CanUse(UINT16 wCount) { return CItem::CanUse(wCount) && _wCurCount >= wCount; }
	//virtual UINT32 GetSellPrice() { return GetItemConfig()._SellPrice * _wCurCount; }
	template<typename T> 
	bool NotifyCount(T& rStore, UINT64 qwRoleID = 0);
	virtual SItemPtr ToProt() const;
	void FromStream(const SStack& rStream);
	void ToStream(SStack& rStream) const;
protected:
	template<typename T>
	bool OnUseStack(T& rStore, UINT16 wCount, bool bDel, UINT64 qwRoleID, UINT16 toWhere);

	UINT16 _wCurCount;
	UINT16 _wOptCount;
};

template<typename T>
bool CStackItem::OnUseStack(T& rStore, UINT16 wCount, bool bDel, UINT64 qwRoleID, UINT16 toWhere)
{
	if(_wCurCount < wCount)
	{
		LOG_CRI << "_wCurCount: " << _wCurCount << ", wCount: " << wCount;
		return false;
	}

	_wCurCount -= wCount;
    _wOptCount = wCount;
	if(!bDel)
	{
		if(GetExpireType() == eExpireUse)
			StartExpire();

        // XXX: need this???
#if 0
		if(_rItemCfg._CD > 0)
		{
			CUserPtr pUser = rStore.GetUserPtr();
			if(NULL != pUser)
				pUser->GetColdItem().OnUseItem(*this);
		}
#endif
	}
    // 通知弹框
	extern CChatProtS g_ChatProtS;
    string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgUseItem, BuildStrVec(GetQuality(),GetItemName(),wCount));
    rStore.GetUser().SendPkg(strPkg);
    //XXX udpLog
    TVecUserItemChange vecItemChange;
    SUserItemChange oItemChange(GetItemID(), -wCount, GetGoldPrice(), toWhere);
    vecItemChange.push_back(oItemChange);
    rStore.GetUser().SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogItemChange(rStore.GetUser().GetUserID(), eOpTypeItemChange, vecItemChange));


	if(_wCurCount == 0)
	{
		return rStore.DelItem(*this, true, true, toWhere);
	}

	NotifyCount(rStore, qwRoleID);
    {
        // XXX:
        INT16 wIndex = 0;
        if (rStore.GetItem(GetInstID(), &wIndex))
            rStore.Update2DB(wIndex, *this, eOpUpdate, toWhere);
    }

	StartExpire();
	return true;
}

template<typename T>
bool CStackItem::NotifyCount(T& rT, UINT64 qwRoleID/* = 0*/)
{
	CUserPtr pUser = rT.GetUserPtr();
	if(pUser == NULL)
		return false;
	pUser->GetTaskPkg().OnCollectItem(GetItemID());
	extern CItemProtS g_ItemProtS;
	return pUser->SendPkg(g_ItemProtS.BuildPkg_StackItemUpdate(rT.GetStoreType(), qwRoleID, GetInstID(), _wCurCount));
}
