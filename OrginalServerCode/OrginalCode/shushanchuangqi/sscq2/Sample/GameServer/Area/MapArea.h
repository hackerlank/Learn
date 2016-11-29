#pragma once
#include "BaseObj.h"
#include "MapProt.h"
#include "Region.h"
using namespace NMapProt;
struct SAreaPoint;

class CMapArea : public CBaseObj ,public SAreaRegion,public CPoolObj<CMapArea>
{
	friend class CMapAreaMgr;
public:
	DEF_NEW_DELETE(CMapArea);
	CMapArea(UINT32 dwInstID,const SAreaPoint& rArea ); 
	virtual ~CMapArea() { }

	virtual EObjType GetObjType() const { return eObjArea; }
	virtual void Exec() { }
	void GetAreaAppear(SAreaAppear& rAreaAppear);
	UINT32 GetInstID() const { return _dwInstID; }
	void SetInstID(UINT32 dwInstID) { _dwInstID = dwInstID; }
	UINT32 GetAreaID() const { return wAreaID; }
    UINT16 GetIndex() const { return  wIndex;}
    void Disappear();
    bool IsSafe();
    bool CanDel();
protected:
	UINT32 _dwInstID;

};
