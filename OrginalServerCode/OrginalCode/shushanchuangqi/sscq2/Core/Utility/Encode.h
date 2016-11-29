/********************************************************************
//	Server Utility Library Source File.
//	File name:	Encode.h
//	Created:	2012/06/18	11:00
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
#ifdef _WIN32
#include <Windows.h>
#else
#include "Linux.h"
#include <iconv.h>
#endif
#include <string>

using std::string;
using std::wstring;

string UrlEncode(const string& szToEncode);
string UrlDecode(const string& szToDecode);

#ifdef _WIN32
wstring ToWString(const string& str, UINT32 dwCodePage = CP_ACP);
string ToString(const wstring& wstr, UINT32 dwCodePage = CP_ACP);
#endif

wstring UTF8ToUTF16(const char* pStr);
wstring UTF8ToUTF16(const string& str);
string UTF16ToUTF8(const wchar_t* pWStr);
string UTF16ToUTF8(const wstring& wstr);

string GB2312ToUTF8(const char* pStr);
string GB2312ToUTF8(const string& strInput);
string UTF8ToGB2312(const char* pStr);
string UTF8ToGB2312(const string& strInput);

string GetMD5Code(const string& strInput);

bool Compress(const char* pInBuf, UINT32 dwInSize, char* pOutBuf, UINT32& dwOutSize);
bool CompressPacket(const char* pInBuf, UINT32 dwInSize, char* pOutBuf, UINT32& dwOutSize);
bool UnCompress(const char* pInBuf, UINT32 dwInSize, char* pOutBuf, UINT32& dwOutSize);

void XOR(char* pBuf, UINT32 dwSize, UINT32 dwKey);