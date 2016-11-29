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

#pragma once
#include <list>
#include <functional>

using namespace std;

typedef list<std::function<void()>> TLstFunc;

class CBatchFuncMgr
{
public:
	static void AddFunction(std::function<void()> func);
	static void Execute(bool bClear = true);
	static void Clear();
private:
	static TLstFunc _lstFunc;
};
