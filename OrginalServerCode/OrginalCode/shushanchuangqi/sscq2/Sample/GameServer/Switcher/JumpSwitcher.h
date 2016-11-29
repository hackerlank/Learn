#pragma once
#include "Switcher.h"
#include "Region.h"

class CDungeon;
struct SDgnJumpPoint;
class CJumpSwitcher : public CSwitcher
{
	friend class CSwitcherMgr;
public:
	DEF_NEW_DELETE(CJumpSwitcher);
	CJumpSwitcher(UINT32 dwSwitcherID,UINT8 byIndex,bool bOpen) : CSwitcher(dwSwitcherID, byIndex,bOpen){ }
	virtual ~CJumpSwitcher() { }

	virtual ESwitcherType GetSwitcherType() const { return eSwitcherJump; }
	virtual void Exec();
	virtual void TimerCheck();
	operator SJumpRegion&() { return _oJumpRegion; }
    void InitJumpInfo(const SDgnJumpPoint& rJumpPoint);

protected:
	SJumpRegion _oJumpRegion;
};
