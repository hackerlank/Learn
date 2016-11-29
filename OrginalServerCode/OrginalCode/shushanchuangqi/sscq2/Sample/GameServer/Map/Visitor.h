#pragma once
#include "Point.h"
#include "Player.h"

enum EVisitType
{
	eVisitNone,
	eVisitNotify,
	eVisitMeet,
	eVisitMiss,
	eVisitPlayer,
	eVisitRoundPlayer,
	eVisitAllMonster,
	eVisitAllNpc,
	eVisitCanFight,
};

class CVisitor
{
public:
	CVisitor(EVisitType eVisitType, const CBaseObjPtr& pObj = NULL) : _eVisitType(eVisitType), _pObj(pObj) { }
	bool Visit(CBaseObj& rObj);
	CBaseObjPtr& GetBaseObj() { return _pObj; }
private:
	EVisitType _eVisitType;
	CBaseObjPtr _pObj;
};
template<typename T>
class CCollector
{
public:
	CCollector(T& rT) : _rT(rT) { }

	bool Finish(INT32 dwX, INT32 dwZ) { return false; }

	bool Visit(CBaseObj& rObj)
	{
		if(_rT.Visit(rObj))
			_setObj.insert(rObj.shared_from_this());
		return true;
	}

	set<CBaseObjPtr>& GetObjSet() { return _setObj; }

	void GetUserList(TVecUINT64& rVecUsrID)
	{
		set<UINT64> setUsrID;
		for(auto it = _setObj.begin(); it != _setObj.end(); ++it)
		{
			CBaseObjPtr pBaseObj = *it;
			CPlayerPtr pPlayer = dynamic_pointer_cast<CPlayer>(pBaseObj);
			if(pPlayer != NULL)
			{
				UINT64 qwUsrID = pPlayer->GetUserID();
				if(setUsrID.insert(qwUsrID).second)
					rVecUsrID.push_back(qwUsrID);
			}
		}
	}

	template<typename U>
	void GetObjectList(vector<U>& rVecObject)
	{
		for(auto it = _setObj.begin(); it != _setObj.end(); ++it)
		{
			const CBaseObjPtr& pBaseObj = *it;
			typedef typename remove_reference<decltype(*rVecObject.back())>::type V;
			auto pObj = dynamic_pointer_cast<V>(pBaseObj);
			if(pObj != NULL)
				rVecObject.push_back(pObj);
		}
	}

protected:
	T& _rT;
	set<CBaseObjPtr> _setObj;
};

class CPointPicker
{
public:
	CPointPicker(CGameMap& rMap, UINT32 dwCount, bool bBaseGrid) : _rMap(rMap), _dwCount(dwCount), _bBaseGrid(bBaseGrid) { }

	bool Finish(INT32 dwX, INT32 dwZ);

	bool Visit(CBaseObj& rObj) { return false; }

	TVecPoint& GetPointList() { return _vecPoint; }
protected:
	CGameMap& _rMap;
	TVecPoint _vecPoint;
	UINT32 _dwCount;
	bool _bBaseGrid;
};
