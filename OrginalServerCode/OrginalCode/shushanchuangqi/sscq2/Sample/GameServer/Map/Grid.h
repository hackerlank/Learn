/********************************************************************
//	Game Server Source File.
//	File name:	Grid.h
//	Created:	2011/05/30	10:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
*********************************************************************/

#pragma once
#include "BaseObj.h"

struct SObjList
{
	set<CBaseObjWtr, owner_less<CBaseObjWtr>> _setObj;

	DEF_NEW_DELETE(SObjList);
};

typedef shared_ptr<SObjList> SObjListPtr;

class CGrid
{
	friend class CGameMap;
public:
	template<typename T>
	void Accept(T& rT);

	bool AddObj(const CBaseObjPtr& rObj);
	bool DelObj(const CBaseObjPtr& rObj);
	bool HasObj() const;
	void GetAllObj(set<CBaseObjPtr>& setObj) const;
protected:
	DEF_NEW_DELETE(CGrid);
	SObjListPtr _pObjList;
};

template<typename T>
void CGrid::Accept(T& rT)
{
	if(_pObjList == NULL || _pObjList->_setObj.empty())
		return;
	for(auto it = _pObjList->_setObj.begin(); it != _pObjList->_setObj.end(); ++it)
	{
		const CBaseObjWtr& pwObj = *it;
		CBaseObjPtr pObj = pwObj.lock();
		if(pObj != NULL)
		{
			if(!rT.Visit(*pObj))
				break;
		}
		else
		{
#ifdef _DEBUG
			DebugBreak();
#endif
			it = _pObjList->_setObj.erase(it);
		}
	}
}
