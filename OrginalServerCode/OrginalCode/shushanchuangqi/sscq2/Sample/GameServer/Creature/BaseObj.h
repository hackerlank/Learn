
#ifndef BASEOBJ_H_
#define BASEOBJ_H_

#include "Point.h"
#include "stdafx.h"

enum EObjType
{
    eObjNone,
    eObjPlayer,
    eObjMonster,
    eObjNpc,
    eObjGather,
    eObjSwitcher,
    eObjBlocker,
    eObjArea,
};

class CGrid;

class CBaseObj : public enable_shared_from_this<CBaseObj>
{
public:
    static const char* GetObjTypeName(EObjType eObjType);

public:
    CBaseObj() : _fDir(0), _pGrid(NULL),_bDel(false) { }
    virtual ~CBaseObj(); 

    virtual EObjType GetObjType() const { return eObjNone; }
    virtual string GetDescription() const { return "ObjectNone"; }

    const string& GetName() const { return _strName; }
#ifdef _WIN32
    string GetLocaleName() const { return UTF8ToGB2312(_strName); }
#else
    const string& GetLocaleName() const { return _strName; }
#endif
    void SetName(const string& strName) { _strName = strName; }

    SPoint& GetPoint() { return _oPoint; }
    const SPoint& GetPoint() const { return _oPoint; }
    void SetPoint(const SPoint& rPoint);
    SPoint CopyPoint() { return _oPoint; }

    float GetDir() const { return _fDir; }
    virtual void SetDir(float fDir) { _fDir = fDir; }

    CGameMapPtr GetMap() const { return _pMap.lock(); }
    CGameMap * GetpMap() const { return (_pMap.lock()).get(); }
    void SetMap(const CGameMapPtr& pMap) { _pMap = pMap; }

    void SetGrid(CGrid* pGrid) { _pGrid = pGrid; }
    CGrid* GetGrid() const { return _pGrid; }
    void SetCoord(const SCoord& rCoord) { _oCoord = rCoord; }
    bool GetCoord(SCoord& rCoord) const;
    SCoord CopyCoord() const { return _oCoord; }
    bool IsOnMap() const { return _pGrid != NULL; }
    void SetDel(){_bDel = true;}
    bool IsDel() {return _bDel;}
protected:
	string _strName;
	CGameMapWtr _pMap;
	SPoint _oPoint;
	SCoord _oCoord;
	float _fDir;
	CGrid* _pGrid;
    bool _bDel;
   };

inline CLogObj& operator<<(CLogObj& src, const CBaseObj& rBaseObj)
{
	src << " [" << rBaseObj.GetDescription() << "]";
	return src;
}

#endif // BASEOBJ_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

