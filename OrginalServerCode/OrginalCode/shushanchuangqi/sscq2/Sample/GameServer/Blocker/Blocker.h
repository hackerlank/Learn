#pragma once
#include "BaseObj.h"
#include "ObjCond.h"

class CBlocker : public CBaseObj, public CPoolObj<CBlocker>
{
	friend class CBlockerMgr;
public:
	DEF_NEW_DELETE(CBlocker);
	CBlocker(UINT32 dwBlockerID) : _dwBlockerID(dwBlockerID), _dwInstID(0),_wIndex(0) { }
	virtual ~CBlocker() { }

	virtual EObjType GetObjType() const { return eObjBlocker; }
	UINT32 GetInstID() const { return _dwInstID; }
	void SetInstID(UINT32 dwInstID) { _dwInstID = dwInstID; }
	UINT32 GetBlockerID() { return _dwBlockerID; }
	void AssginBlockPt(UINT16 wIndex,const TVecPoint& rVecPoint, SMapInfo& rMapInfo);
	void AddCondition(SObjCond& rObjCond);
	void GetBlockerAppear(SBlockerAppear& rBlockerAppear);
	bool IsDisappeared();
	void Disappear();
    UINT16 GetIndex() {return _wIndex; }	
protected:

	UINT32 _dwBlockerID;
	UINT32 _dwInstID;
    UINT16 _wIndex;
	std::set<SObjCondPtr> _setObjCond;
	TVecPoint _vecBlockPt;
	std::vector<SCoord> _vecBlockCoord;
};
