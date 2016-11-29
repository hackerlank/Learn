#include "stdafx.h"
#include "Grid.h"

bool CGrid::AddObj(const CBaseObjPtr& rObj)
{
	if(_pObjList == NULL)
	{
		_pObjList.reset(new SObjList);
		if(_pObjList == NULL)
			return false;
	}
	if(!_pObjList->_setObj.insert(rObj).second)
	{
		LOG_CRI << "Object already exists!";
#ifdef _DEBUG
		DebugBreak();
#endif
		return false;
	}
	rObj->SetGrid(this);
	return true;
}

bool CGrid::DelObj(const CBaseObjPtr& rObj)
{
	if(_pObjList == NULL)
		return false;
	if(rObj->GetGrid() != this)
	{
		LOG_CRI << "Grid is different!";
#ifdef _DEBUG
		DebugBreak();
#endif
	}
	if(_pObjList->_setObj.erase(rObj) == 0)
	{
		LOG_CRI << "Object doesn't exist!";
#ifdef _DEBUG
		DebugBreak();
#endif
		return false;
	}
	rObj->SetGrid(NULL);
	return true;
}

bool CGrid::HasObj() const
{
	if(_pObjList == NULL)
		return false;
	return !_pObjList->_setObj.empty();
}

void CGrid::GetAllObj(set<CBaseObjPtr>& setObj) const
{
	if(_pObjList == NULL)
		return;
	for(auto& pwBaseObj : _pObjList->_setObj)
	{
		CBaseObjPtr pBaseObj = pwBaseObj.lock();
		setObj.insert(pBaseObj);
	}
}
