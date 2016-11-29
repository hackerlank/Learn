#pragma once

struct SDgnJumpPoint;
class CSwitcher;
class CJumpSwitcher;
class CTowerJumpSwitcher;
class CCampSwitcher;

class CSwitcherMgr
{
public:
	static bool Init();
	static void Destroy();

	static UINT32 GetNewInstID();
	static CJumpSwitcherPtr CreateJumpSwitcher(const SDgnJumpPoint& rDgnJumpPoint);
	static CCampSwitcherPtr CreateCampSwitcher(const SDgnJumpPoint& rDgnJumpPoint);
	static CTowerJumpSwitcherPtr CreateTowerJumpSwitcher(UINT32 dwSwitcherID, bool bOpen);
	static void DestroySwitcher(CSwitcher& rSwitcher);
	static void TimerCheck();

private:
	static map<UINT32, CSwitcherPtr> _mapID2Switcher;
	static UINT32 _dwNextInstID;
};