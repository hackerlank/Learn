/********************************************************************
//	Server Utility Library Source File.
//	File name:	BatchFunc.h
//	Created:	2012/08/21	11:00
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

#include "BatchFunc.h"

TLstFunc CBatchFuncMgr::_lstFunc;

void CBatchFuncMgr::AddFunction(function<void()> func)
{
	_lstFunc.push_back(func);
}

void CBatchFuncMgr::Execute(bool bClear /*= true*/)
{
	for(TLstFunc::iterator it = _lstFunc.begin(); it != _lstFunc.end(); ++it)
		(*it)();
	if(bClear)
		Clear();
}

void CBatchFuncMgr::Clear()
{
	_lstFunc.clear();
}
