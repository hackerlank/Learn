#include "stdafx.h"
#include "ExpireItem.h"
#include "ItemMgr.h"

CExpireItem::CExpireItem(UINT16 wTimeID) : _pItemTimeCfg(NULL), _wTimeID(0), _dwExpireTime(0), _bExpired(false)
{
	if(wTimeID > 0)
		InitExpiration(wTimeID);
}

void CExpireItem::SetExpiration(UINT32 dwExpireTime, bool bExpired)
{
	_dwExpireTime = dwExpireTime;
	_bExpired = bExpired;
}

EExpireType CExpireItem::GetExpireType() const
{
	if(_pItemTimeCfg == NULL)
		return eExpireNone;
	if(_pItemTimeCfg->_StartType == 0)
		return eExpirePick;
	if(_pItemTimeCfg->_StartType == 1)
		return eExpireUse;
	return eExpireNone;
}

bool CExpireItem::InitExpiration(UINT16 wTimeID)
{
	_pItemTimeCfg = CItemMgr::GetItemTimeConfig(wTimeID);
	if(_pItemTimeCfg == NULL)
		return false;
	_wTimeID = _pItemTimeCfg->_ID;
	if(eExpirePick == GetExpireType())
		StartExpire();
	return true;
}

bool CExpireItem::StartExpire()
{
	if(_pItemTimeCfg == NULL || _dwExpireTime != 0)
		return false;
	if(_pItemTimeCfg->_DueType == 0)
		_dwExpireTime = (UINT32)time(NULL) + _pItemTimeCfg->_RemTime * 60;
	else
		_dwExpireTime = (UINT32)CONTAINING_RECORD(_pItemTimeCfg, SItemTimeInfo, oTimeCfg)->tExpireTime;
	return true;
}

bool CExpireItem::OnExpire()
{
	if(!HasExpiration())
		return false;
	_bExpired = true;
	return true;
}

bool CExpireItem::CanExpire(time_t tNow)
{
	if(!HasExpiration())
		return false;
	if(_bExpired)
		return false;
	return tNow >= _dwExpireTime;
}
