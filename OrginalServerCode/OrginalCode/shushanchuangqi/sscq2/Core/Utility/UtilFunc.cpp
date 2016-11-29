/********************************************************************
//	Server Utility Library Source File.
//	File name:	UtilFunc.cpp
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

#include <stdio.h>
#include "UtilFunc.h"

void SplitToText(const string& strText, const char* seps, vector<string>& vecText)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(seps);
	tokenizer tokens(strText, sep);
	for(tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		const string& strText = *it;
		vecText.push_back(strText);
	}
}

string ToLower(string strText)
{
	for_each(strText.begin(), strText.end(), [](char& c){ c = ::tolower(c); });
	return strText;
}

string GetBufContent(const char* pBuf, UINT32 dwLen)
{
	string strData;
	size_t stLen = dwLen * 2 + 3;
	char* pData = new char[stLen];
	memset(pData, 0, stLen);
	int offset = snprintf(pData, stLen, "[");
	for(UINT32 i = 0; i < dwLen; ++i)
		offset += snprintf(pData + offset, stLen - offset, "%02x", (UINT8)pBuf[i]);
	snprintf(pData + offset, stLen - offset, "]");
	strData.assign(pData, stLen);
	delete[] pData;
	return strData;
}

// XXX: from CGUIDMgr.cpp
#define _BIT_MASK(digit) ((1LL << (digit)) - 1)
UINT16 _GetGroupId(UINT64 qwGUID)
{
    return _BIT_MASK(12) & (qwGUID >> 52);
}

UINT8 _GetType(UINT64 qwGUID)
{
    return _BIT_MASK(4) & (qwGUID >> 42);
}

UINT8 _GetIndex(UINT64 qwGUID)
{
    return UINT8(_BIT_MASK(6) & (qwGUID >> 46));
}

UINT64 _GetCounter(UINT64 qwGUID)
{
    const UINT64 MAX_COUNTER = _BIT_MASK(42);
    return MAX_COUNTER & qwGUID;
}

string GetUserDesc(UINT64 qwUsrID)
{
	char szBuf[0x50];
	sprintf_s(szBuf, "%u-%u-%u-%lu", _GetGroupId(qwUsrID), _GetType(qwUsrID), _GetIndex(qwUsrID), _GetCounter(qwUsrID));
	return szBuf;
}

