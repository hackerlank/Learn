/********************************************************************
//	Server Utility Library Source File.
//	File name:	Encode.cpp
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

#include <iostream>
#include "Encode.h"
#include "CallStack.h"
#include "openssl/md5.h"
#include "zlib.h"

using std::cerr;
using std::endl;

string UrlEncode(const string& szToEncode)
{
	string src = szToEncode;
	char hex[] = "0123456789ABCDEF";
	string dst;

	for(size_t i = 0; i < src.size(); ++i)
	{
		unsigned char cc = src[i];
		if(isascii(cc))
		{
			if(cc == ' ')
				dst += "%20";
			else
				dst += cc;
		}
		else
		{
			unsigned char c = static_cast<unsigned char>(src[i]);
			dst += '%';
			dst += hex[c / 16];
			dst += hex[c % 16];
		}
	}
	return dst;
}

string UrlDecode(const string& szToDecode)
{
	string result;
	int hex = 0;
	for(size_t i = 0; i < szToDecode.length(); ++i)
	{
		switch(szToDecode[i])
		{
		case '+':
			result += ' ';
			break;
		case '%':
			if(isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))
			{
				string strHex = szToDecode.substr(i + 1, 2);
				hex = strtol(strHex.c_str(), 0, 16);
				//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]
				//可以不经过编码直接用于URL
				if (!((hex >= 48 && hex <= 57) ||	//0-9
					(hex >=97 && hex <= 122) ||	//a-z
					(hex >=65 && hex <= 90) ||	//A-Z
					//一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]
					hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
					|| hex == 0x2a || hex == 0x2b|| hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
					|| hex == 0x3A || hex == 0x3B|| hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
					))
				{
					result += char(hex);
					i += 2;
				}
				else
				{
					result += '%';
				}
			}
			else
			{
				result += '%';
			}
			break;
		default:
			result += szToDecode[i];
			break;
		}
	}
	return result;
}

#ifdef _WIN32
wstring ToWString(const string& str, UINT32 dwCodePage /*= CP_ACP*/)
{
	int iLen = MultiByteToWideChar(dwCodePage, 0, str.c_str(), -1, NULL, 0);
	wstring wstr;
	wchar_t* pText = new wchar_t[iLen];
	if(pText == NULL)
		return wstr;
	if(MultiByteToWideChar(dwCodePage, 0, str.c_str(), -1, pText, iLen) > 0)
		wstr = pText;
	delete[] pText;
	return wstr;
}

string ToString(const wstring& wstr, UINT32 dwCodePage /*= CP_ACP*/)
{
	int iLen = WideCharToMultiByte(dwCodePage, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	string str;
	char* pText = new char[iLen];
	if(pText == NULL)
		return str;
	if(WideCharToMultiByte(dwCodePage, 0, wstr.c_str(), -1, pText, iLen, NULL, NULL) > 0)
		str = pText;
	delete[] pText;
	return str;
}
#endif

wstring UTF8ToUTF16(const char* pStr)
{
	wstring wstr;
	unsigned int codepoint = 0;
	int following = 0;
	for(; *pStr != 0; ++pStr)
	{
		unsigned char ch = *pStr;
		if(ch <= 0x7f)
		{
			codepoint = ch;
			following = 0;
		}
		else if(ch <= 0xbf)
		{
			if(following > 0)
			{
				codepoint = (codepoint << 6) | (ch & 0x3f);
				--following;
			}
		}
		else if(ch <= 0xdf)
		{
			codepoint = ch & 0x1f;
			following = 1;
		}
		else if(ch <= 0xef)
		{
			codepoint = ch & 0x0f;
			following = 2;
		}
		else
		{
			codepoint = ch & 0x07;
			following = 3;
		}
		if(following == 0)
		{
			if(codepoint > 0xffff)
			{
				wstr.append(1, static_cast<wchar_t>(0xd800 + (codepoint >> 10)));
				wstr.append(1, static_cast<wchar_t>(0xdc00 + (codepoint & 0x03ff)));
			}
			else
				wstr.append(1, static_cast<wchar_t>(codepoint));
			codepoint = 0;
		}
	}
	return wstr;
}

wstring UTF8ToUTF16(const string& str)
{
	return UTF8ToUTF16(str.c_str());
}

string UTF16ToUTF8(const wchar_t* pWStr)
{
	string str;
	unsigned int codepoint = 0;
	for(; *pWStr != 0; ++pWStr)
	{
		if(*pWStr >= 0xd800 && *pWStr <= 0xdbff)
		{
			codepoint = ((*pWStr - 0xd800) << 10) + 0x10000;
		}
		else
		{
			if(*pWStr >= 0xdc00 && *pWStr <= 0xdfff)
				codepoint |= *pWStr - 0xdc00;
			else
				codepoint = *pWStr;

			if(codepoint <= 0x7f)
				str.append(1, static_cast<char>(codepoint));
			else if(codepoint <= 0x7ff)
			{
				str.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
				str.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
			}
			else if(codepoint <= 0xffff)
			{
				str.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
				str.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
				str.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
			}
			else
			{
				str.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
				str.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
				str.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
				str.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
			}
			codepoint = 0;
		}
	}
	return str;
}

string UTF16ToUTF8(const wstring& wstr)
{
	return UTF16ToUTF8(wstr.c_str());
}

#ifdef __GNUG__
class CConverter
{
public:
	CConverter(const char* pFromCharSet, const char* pToCharSet)
	{
		_cd = iconv_open(pToCharSet, pFromCharSet);
	}

	~CConverter()
	{
		iconv_close(_cd);
	}

	bool CodeConvert(char* pInBuf, size_t stInLen, char* pOutBuf, size_t stOutLen)
	{
		if(_cd == 0)
			return false;
		if(pInBuf == NULL || pOutBuf == NULL)
			return false;
		if(iconv(_cd, &pInBuf, &stInLen, &pOutBuf, &stOutLen) == static_cast<size_t>(-1))
		{
#ifdef _DEBUG
			string GetStringErr();
			cerr << "iconv fails, error: " << GetStringErr() << endl;
			PrintCallStack();
#endif
			return false;
		}
		return true;
	}
private:
	iconv_t _cd;
};
#endif

string GB2312ToUTF8(const char* pStr)
{
#ifdef _WIN32
	int len = MultiByteToWideChar(CP_ACP, 0, pStr, -1, NULL, 0);
	string strText;
	wchar_t* pWStr = new wchar_t[len];
	if(pWStr != NULL)
	{
		MultiByteToWideChar(CP_ACP, 0, pStr, -1, pWStr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, pWStr, -1, NULL, 0, NULL, NULL);
		char* pText = new char[len];
		if(pText != NULL)
		{
			WideCharToMultiByte(CP_UTF8, 0, pWStr, -1, pText, len, NULL, NULL);
			strText = pText;
		}
		delete[] pText;
	}
	delete[] pWStr;
	return strText;
#else
	string strText;
	size_t stInLen = strlen(pStr);
	size_t stOutLen = stInLen * 2;
	char* pBuf = new char[stOutLen + 1];
	if(pBuf == NULL)
		return strText;
	static CConverter oConverter("gb2312", "utf-8");
	if(oConverter.CodeConvert((char*)pStr, stInLen, pBuf, stOutLen))
		strText = pBuf;
	delete[] pBuf;
	return strText;
#endif
}

string GB2312ToUTF8(const string& strInput)
{
	return GB2312ToUTF8(strInput.c_str());
}

string UTF8ToGB2312(const char* pStr)
{
#ifdef _WIN32
	int len = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0);
	string strText;
	wchar_t* pWStr = new wchar_t[len];
	if(pWStr != NULL)
	{
		MultiByteToWideChar(CP_UTF8, 0, pStr, -1, pWStr, len);
		len = WideCharToMultiByte(CP_ACP, 0, pWStr, -1, NULL, 0, NULL, NULL);
		char* pText = new char[len];
		if(pText != NULL)
		{
			WideCharToMultiByte(CP_ACP, 0, pWStr, -1, pText, len, NULL, NULL);
			strText = pText;
		}
		delete[] pText;
	}
	delete[] pWStr;
	return strText;
#else
	string strText;
	size_t stInLen = strlen(pStr);
	size_t stOutLen = stInLen * 2;
	char* pBuf = new char[stOutLen + 1];
	if(pBuf == NULL)
		return strText;
	static CConverter oConverter("utf-8", "gb2312");
	if(oConverter.CodeConvert((char*)pStr, stInLen, pBuf, stOutLen))
		strText = pBuf;
	delete[] pBuf;
	return strText;
#endif
}

string UTF8ToGB2312(const string& strInput)
{
	return UTF8ToGB2312(strInput.c_str());
}

string GetMD5Code(const string& strInput)
{
	unsigned char md[16];
	memset(md, 0, sizeof md);
	MD5((const unsigned char*)strInput.c_str(), strInput.size(), md);
	char szTmp[3];
	string strMd5;
	for(size_t i = 0; i < ARRAYSIZE(md); ++i)
	{
		sprintf_s(szTmp, "%2.2X", md[i]);
		strMd5 += szTmp;
	}
	return strMd5;
}

bool Compress(const char* pInBuf, UINT32 dwInSize, char* pOutBuf, UINT32& dwOutSize)
{
	Bytef* dest = (Bytef*)pOutBuf;
	uLongf destLen = dwOutSize;
	Bytef* source = (Bytef*)pInBuf;
	uLongf sourceLen = dwInSize;
	int ret = compress(dest, &destLen, source, sourceLen);
	if(ret == Z_OK)
	{
		dwOutSize = destLen;
		return true;
	}
	return false;
}

#define COMPRESS_PACKET_MIN_LEN 70

bool CompressPacket(const char* pInBuf, UINT32 dwInSize, char* pOutBuf, UINT32& dwOutSize)
{
	if(pInBuf == NULL || dwInSize < 1 || pOutBuf == NULL)
		return false;
	UINT32 dwNewLen = 0;
	if(dwInSize > COMPRESS_PACKET_MIN_LEN)
	{
		dwNewLen = dwOutSize - 1;
		if(!Compress(pInBuf, dwInSize, pOutBuf + 1, dwNewLen))
			return false;
		*(char*)pOutBuf = 1;
		++dwNewLen;
	}
	else
	{
		*(char*)pOutBuf = 0;
		memcpy_s(pOutBuf + 1, dwOutSize - 1, pInBuf, dwInSize);
		dwNewLen = dwInSize + 1;
	}
	if(dwOutSize < dwNewLen)
		return false;
	dwOutSize = dwNewLen;
	return true;
}

bool UnCompress(const char* pInBuf, UINT32 dwInSize, char* pOutBuf, UINT32& dwOutSize)
{
	Bytef* dest = (Bytef*)pOutBuf;
	uLongf destLen = dwOutSize;
	Bytef* source = (Bytef*)pInBuf;
	uLongf sourceLen = dwInSize;
	int ret = uncompress(dest, &destLen, source, sourceLen);
	if(ret == Z_OK)
	{
		dwOutSize = destLen;
		return true;
	}
	return false;
}

void XOR(char* pBuf, UINT32 dwSize, UINT32 dwKey)
{
    return ;
	UINT32 i = 0;
	for(; i + 4 <= dwSize; i += 4)
		*(UINT32*)(pBuf + i) ^= dwKey;
	for(; i < dwSize; ++i)
	{
		UINT32 dwRem = i % 4;
		switch(dwRem)
		{
		case 0:
			pBuf[i] ^= char(dwKey & 0xFF);
			break;
		case 1:
			pBuf[i] ^= char(dwKey >> 8 & 0xFF);
			break;
		case 2:
			pBuf[i] ^= char(dwKey >> 16 & 0xFF);
			break;
		case 3:
			pBuf[i] ^= char(dwKey >> 24 & 0xFF);
			break;
		}
	}
}
