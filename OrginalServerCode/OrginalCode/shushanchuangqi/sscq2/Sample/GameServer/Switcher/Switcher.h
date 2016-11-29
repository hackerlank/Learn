#pragma once
#include "BaseObj.h"
#include "MapProt.h"
#include "ObjCond.h"
#include "Region.h"

using namespace NMapProt;

enum
{
	MAX_CUSTOM_SWITCHER_ID = 0x1fffffff,
	SWITCHER_ID_JUMP,
};

class CSwitcher : public CBaseObj
{
	friend class CSwitcherMgr;
public:
	DEF_NEW_DELETE(CSwitcher);
	CSwitcher(UINT32 dwSwitcherID,UINT8 byIndex, bool bOpen) : _dwInstID(0),_byIndex(byIndex), _bOpen(bOpen), _dwSwitcherID(dwSwitcherID){ }
	virtual ~CSwitcher() { }

	virtual EObjType GetObjType() const { return eObjSwitcher; }
	virtual ESwitcherType GetSwitcherType() const { return eSwitcherNone; }
	virtual void Exec() { }
	void CondCheck();
	virtual void TimerCheck();

	void GetSwitcherAppear(SSwitcherAppear& rSwitcherAppear);
	UINT32 GetInstID() const { return _dwInstID; }
	void SetInstID(UINT32 dwInstID) { _dwInstID = dwInstID; }
	UINT32 GetSwitcherID() const { return _dwSwitcherID; }
	bool IsOpen() const { return _bOpen; }
	void SetOpen(bool bOpen, bool bNotify = true);
	
	bool NotifySurround(const string& strPkg);
	bool NotifyOpenState();
	void AddCondition(SObjCond& rObjCond);
    UINT8 GetIndex() {return _byIndex;}
protected:
	UINT32 _dwInstID;
    UINT8 _byIndex;
	bool _bOpen;
	UINT32 _dwSwitcherID;
	std::set<SObjCondPtr> _setObjCond;
};

class CTowerJumpSwitcher : public CSwitcher
{
	friend class CSwitcherMgr;
public:
	DEF_NEW_DELETE(CTowerJumpSwitcher);
	CTowerJumpSwitcher(UINT32 dwSwitcherID, bool bOpen) : CSwitcher(dwSwitcherID,0, bOpen) { }
	virtual ~CTowerJumpSwitcher() { }

	virtual ESwitcherType GetSwitcherType() const { return eSwitcherTower; }
	virtual void Exec();
	virtual void TimerCheck();
	void PlaceTo(float fX, float fY);

protected:

	SRoundRegion _oRegion;
};

class CCampSwitcher : public CSwitcher
{
	friend class CSwitcherMgr;
public:
	DEF_NEW_DELETE(CCampSwitcher);
	CCampSwitcher(UINT32 dwSwitcherID, bool bOpen) : CSwitcher(dwSwitcherID,0, bOpen) { }
	virtual ~CCampSwitcher() { }

	virtual ESwitcherType GetSwitcherType() const { return eSwitcherCamp; }
	SRoundRegion& GetRegion() { return _oRegion; }

protected:
	SRoundRegion _oRegion;
};
