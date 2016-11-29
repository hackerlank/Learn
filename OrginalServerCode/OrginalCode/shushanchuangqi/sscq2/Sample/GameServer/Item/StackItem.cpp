#include "stdafx.h"
#include "StackItem.h"
#include "Protocols.h"
#include "Player.h"

bool CStackItem::SetCount(UINT16 wCount)
{
	if(wCount > GetMaxNum())
		return false;
	_wCurCount = wCount;
	return true;
}

bool CStackItem::AddCount(UINT16 wCount)
{
	UINT16 wTotalCount = wCount + _wCurCount;
	if(wTotalCount > GetMaxNum())
		return false;
	_wCurCount = wTotalCount;
	return true;
}

UINT16 CStackItem::GetEmptyCount()
{
	if(_wCurCount > GetMaxNum())
	{
		LOG_CRI << "Stack Item Count Error! _wCurCount: " << _wCurCount << ", ItemID: " << GetItemID();
		return 0;
	}
	return GetMaxNum() - _wCurCount;
}

bool CStackItem::CanMerge(const CStackItem& rStackItem, bool bCheckBind /*= true*/) const
{
	if(HasExpiration() || rStackItem.HasExpiration())
	{
		if(IsExpired() != rStackItem.IsExpired() || GetExpireTime() != rStackItem.GetExpireTime())
			return false;
	}
	if(GetCount() >= GetMaxNum() || rStackItem.GetCount() >= rStackItem.GetMaxNum())
		return false;
	if(GetItemID() != rStackItem.GetItemID())
		return false;
	if(GetQuality() != rStackItem.GetQuality())
		return false;
	if(bCheckBind && IsBind() != rStackItem.IsBind())
		return false;
	return true;
}

bool CStackItem::CanMerge(UINT16 wItemID, UINT8 byQuality, bool bBind, UINT32 dwTimeID) const
{
	if(HasExpiration())
		return false;
	if(GetItemID() != wItemID)
		return false;
	if(IsBind() != bBind)
		return false;
	if(GetQuality() != byQuality)
		return false;
	return true;
}

bool CStackItem::SetOptCount(UINT16 wOptCount)
{
	if(wOptCount > GetMaxNum())
		return false;
	_wOptCount = wOptCount;
	return true;
}

bool CStackItem::OnUse(CStore& rStore, UINT16 wCount, bool bDel, UINT16 towhere)
{
	return OnUseStack(rStore, wCount, bDel, 0, towhere);
}

// TODO:
#if 0
bool CStackItem::OnUse(CRoleEquipForm& rStore, UINT16 wCount, bool bDel/* = true*/)
{
	CCreature& rCreature = rStore.GetCreature();
	CPlayerPtr pPlayer = ToPtr<CPlayer>(rCreature);
	if(NULL != pPlayer)
		return OnUseStack(rStore, wCount, bDel, pPlayer->GetRoleID());
	else
		return OnUseStack(rStore, wCount, bDel);
}
#endif

SItemPtr CStackItem::ToProt() const
{
	SStack* pStack = new SStack;
	if(pStack != NULL)
		ToStream(*pStack);
	return SItemPtr(pStack);
}

void CStackItem::FromStream(const SStack& rStream)
{
	CItem::FromStream(rStream);
	_wCurCount = rStream.sItemInfo.wCount;
}

void CStackItem::ToStream(SStack& rStream) const
{
	CItem::ToStream(rStream);
	rStream.sItemInfo.wCount = _wCurCount;
}

