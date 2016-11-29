/********************************************************************
//	Server Utility Library Source File.
//	File name:	NameCheck.h
//	Created:	2012/03/12	14:00
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
#include <string>
#include <vector>
#include <map>
#include "Platform.h"

using namespace std;

typedef multimap<UINT8, UINT16> TMapLoc2Index;
typedef multimap<UINT16, UINT8> TMapIndex2Loc;

struct SIndexInfo
{
	TMapLoc2Index mapLoc2Index;
	TMapIndex2Loc mapIndex2Loc;
};

typedef map<wchar_t, SIndexInfo> TMapChar2Index;

class CNameChecker
{
public:
	bool LoadFile(const string& strPath);
	bool CheckName(const string& strName) const;
protected:
	vector<wstring> _vecInvalidName;
	TMapChar2Index _mapChar2Index;
};
