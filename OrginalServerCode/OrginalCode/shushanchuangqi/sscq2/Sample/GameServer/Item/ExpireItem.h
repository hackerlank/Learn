#pragma once
#include "ItemTimeCFG.h"

enum EExpireType
{
	eExpireNone,
	eExpirePick,
	eExpireUse
};

class CUser;

class CExpireItem
{
public:
	CExpireItem(UINT16 wTimeID);
	SItemTimeCFG* GetTimeCfg() const { return _pItemTimeCfg; }
	EExpireType GetExpireType() const;
	UINT16 GetTimeID() const { return _wTimeID; }
	UINT32 GetExpireTime() const { return _dwExpireTime; }
	bool IsExpired() const { return _bExpired; }
	bool HasExpiration() const { return _wTimeID > 0 && _dwExpireTime > 0; }
	void SetExpiration(UINT32 dwExpireTime, bool bExpired);
	bool StartExpire();
	bool OnExpire();
	bool CanExpire(time_t tNow);
protected:
	bool InitExpiration(UINT16 wTimeID);

	SItemTimeCFG* _pItemTimeCfg;
	UINT16 _wTimeID;
	UINT32 _dwExpireTime;
	bool _bExpired;
};