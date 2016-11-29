/********************************************************************
//	Server Utility Library Source File.
//	File name:	NameCheck.cpp
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

#include <fstream>
#include <algorithm>
#include <boost/algorithm/string/trim_all.hpp>
#include "NameCheck.h"
#include "Encode.h"
#include "UtilFunc.h"

#define BOOST_UTF8_BEGIN_NAMESPACE
#define BOOST_UTF8_END_NAMESPACE
#define BOOST_UTF8_DECL
#include <boost/detail/utf8_codecvt_facet.hpp>
#include <boost/detail/utf8_codecvt_facet.ipp>

bool CNameChecker::LoadFile(const string& strPath)
{
	locale::global(locale(""));
	ifstream ifs(strPath.c_str());
	if(!ifs)
		return false;
	locale::global(locale("C"));
	std::locale utf8_locale(std::locale(), new utf8_codecvt_facet);
	ifs.imbue(utf8_locale);
	const UINT32 dwSize = 0x10000;
	char* pBuf = new char[dwSize];
	if(pBuf == NULL)
		return false;
	while(ifs.getline(pBuf, dwSize))
	{
		vector<string> vecName;
		SplitToText(pBuf, ",", vecName);
		for(auto& strName : vecName)
		{
			if(!strName.empty())
			{
				wstring wstrName = UTF8ToUTF16(strName);
				UINT16 wIndex = (UINT16)_vecInvalidName.size();
				_vecInvalidName.push_back(wstrName);
				for(UINT8 i = 0; i < (UINT8)wstrName.size(); ++i)
				{
					SIndexInfo& rIndexInfo = _mapChar2Index[wstrName[i]];
					rIndexInfo.mapLoc2Index.insert(make_pair(i, wIndex));
					rIndexInfo.mapIndex2Loc.insert(make_pair(wIndex, i));
				}
			}
		}
	}
	delete[] pBuf;
	if(_vecInvalidName.empty())
		return false;
	return true;
}

bool CNameChecker::CheckName(const string& strName) const
{
	wstring wstrOrigName = UTF8ToUTF16(strName);
	wstring wstrName;

	//static wchar_t arFilterChar[] =	{ L' ', L'~', L'!', L'@', L'&', L'|', L'\\', L'/', L'?', L'-', L'+', L'#', L'_', L'=',
	//	L'.', L',', L';', L':', L'<', L'>', L'[', L']', L'{', L'}', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0' };
	static wchar_t arFilterChar[] =	{
        L' ', L'~', L'!', L'@',
        L'&', L'|', L'\\', L'/', L'?',
        L'-', L'+', L'#', L'=',
        L'.', L',', L';', L':',
        L'<', L'>', L'[', L']', L'{', L'}',
        L'\r', L'\n'
    };

	static bool bSort = false;
	if(!bSort)
	{
		sort(arFilterChar, arFilterChar + ARRAYSIZE(arFilterChar));
		bSort = true;
	}
	for(size_t i = 0; i < wstrOrigName.size(); ++i)
	{
		if(!binary_search(arFilterChar, arFilterChar + ARRAYSIZE(arFilterChar), wstrOrigName[i]))
			wstrName += wstrOrigName[i];
        else
            return false;
	}
	if(wstrName.empty())
		return false;
	vector<const SIndexInfo*> vecIndex;
	for(size_t i = 0; i < wstrName.size(); ++i)
	{
		TMapChar2Index::const_iterator it = _mapChar2Index.find(wstrName[i]);
		if(it != _mapChar2Index.end())
			vecIndex.push_back(&it->second);
		else
			vecIndex.push_back(NULL);
	}
	map<UINT16, UINT8> mapIndex2Loc;
	for(const SIndexInfo* pIndexInfo : vecIndex)
	{
		if(pIndexInfo != NULL)
		{
			for(auto it = mapIndex2Loc.begin(), itOld = it; it != mapIndex2Loc.end();)
			{
				itOld = it;
				UINT16 wIndex = it->first;
				UINT8& byLoc = it->second;
				++it;
				bool bFound = false;
				for(auto cit = pIndexInfo->mapIndex2Loc.lower_bound(wIndex), citUB = pIndexInfo->mapIndex2Loc.upper_bound(wIndex); cit != citUB; ++cit)
				{
					UINT8 byLoc2 = cit->second;
					if(byLoc2 == byLoc + 1)
					{
						++byLoc;
						if(byLoc + 1 >= (UINT8)_vecInvalidName[wIndex].size())
							return false;
						bFound = true;
						break;
					}
				}
				if(!bFound)
					mapIndex2Loc.erase(itOld);
			}
			for(auto cit = pIndexInfo->mapLoc2Index.lower_bound(0), citUB = pIndexInfo->mapLoc2Index.upper_bound(0); cit != citUB; ++cit)
			{
				UINT16 wIndex = cit->second;
				mapIndex2Loc[wIndex] = 0;
			}
		}
		else
		{
			mapIndex2Loc.clear();
		}
	}
	return true;
}

