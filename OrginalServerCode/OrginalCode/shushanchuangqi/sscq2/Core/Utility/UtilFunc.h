/********************************************************************
//	Server Utility Library Source File.
//	File name:	UtilFunc.h
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
#ifdef _WIN32
#include <Windows.h>
#else
#include "Linux.h"
#endif
#include <string>
#include <vector>
#include <type_traits>
#include <boost/tokenizer.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include "Platform.h"

using std::string;
using std::vector;
using std::is_floating_point;
using std::is_signed;
using std::is_integral;

template<typename T>
string NumberToString(T t)
{
	const char* pFormat = NULL;
	if(is_floating_point<T>::value)
	{
		pFormat = "%f";
	}
	else if(is_signed<T>::value)
	{
		if(sizeof(T) == 8)
#ifdef _WIN32
			pFormat = "%lld";
#else
			pFormat = "%ld";
#endif
		else
			pFormat = "%d";
	}
	else
	{
		if(sizeof(T) == 8)
#ifdef _WIN32
			pFormat = "%llu";
#else
			pFormat = "%lu";
#endif
		else
			pFormat = "%u";
	}
	char szBuffer[64];
	sprintf_s(szBuffer, pFormat, t);
	return szBuffer;
}

template<typename T>
bool String2Number(const string& strVal, T& rVal)
{
	if(strVal.empty())
		return false;
	char* pEnd = NULL;
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4800)
#endif
	if(is_floating_point<T>::value)
		rVal = (T)strtod(strVal.c_str(), &pEnd);
	else if(is_signed<T>::value)
		rVal = (T)StrToINT64(strVal.c_str(), &pEnd, 10);
	else
		rVal = (T)StrToUINT64(strVal.c_str(), &pEnd, 10);
#ifdef _WIN32
#pragma warning(pop)
#endif
	return pEnd > &strVal.back();
}

string ToLower(string strText);

//////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct SConverter
{
	string operator()(const T& rT)
	{
		return move(NumberToString(rT));
	}
};

template<>
struct SConverter<string>
{
	string operator()(const string& str)
	{
		return str;
	}
};

template<>
struct SConverter<char*>
{
	string operator()(const char* pStr)
	{
		return string(pStr);
	}
};

template<>
struct SConverter<const char*>
{
	string operator()(const char* pStr)
	{
		return string(pStr);
	}
};

template<typename T>
string ToString(const T& rT)
{
	static SConverter<T> sConverter;
	return sConverter(rT);
}

template <int N>
string ToString(const char (&arChar)[N])
{
	return string(arChar);
}

//////////////////////////////////////////////////////////////////////////////////////

#define PRINT_FUNC_PARAM(z, n, unused) const P##n& rP##n

#define PRINT_PUSH_BACK(z, n, unused) vecStr.emplace_back(ToString(rP##n));

#define DEF_FUNC_BUILDSTRVEC(z, n, unused) \
	template<BOOST_PP_ENUM_PARAMS(n, typename P)> \
	vector<string> BuildStrVec(BOOST_PP_ENUM(n, PRINT_FUNC_PARAM, none)) \
	{ \
		vector<string> vecStr; \
		BOOST_PP_REPEAT(n, PRINT_PUSH_BACK, none); \
		return vecStr; \
	}

BOOST_PP_REPEAT_FROM_TO(1, 15, DEF_FUNC_BUILDSTRVEC, none);

//////////////////////////////////////////////////////////////////////////////////////

void SplitToText(const string& strText, const char* seps, vector<string>& vecText);

template<typename T>
void SplitToNumber(const string& strText, const char* seps, vector<T>& rVecNum)
{
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep(seps);
	tokenizer tokens(strText, sep);
	for(tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		const string& strNum = *it;
		T num = (T)StrToUINT64(strNum.c_str(), NULL, 10);
		rVecNum.push_back(num);
	}
}

//////////////////////////////////////////////////////////////////////////////////////

string GetBufContent(const char* pBuf, UINT32 dwLen);

string GetUserDesc(UINT64 qwUsrID);

//////////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct STypeBitSize{ enum { value = sizeof(T) * 8 }; };

template <typename T1, typename T2>
void GetMarkPosVec(T1 tVal, vector<T2>& vecPos)
{
	static_assert(is_integral<T1>::value && is_integral<T2>::value, "T1 and T2 must be integral");
	for(int i = 0; i < STypeBitSize<T1>::value; ++i)
	{
		if((((T1)1 << i) & tVal) != 0)
			vecPos.push_back((T2)i);
	}
}

template <typename V, typename T>
bool ValueInVec(const V& vec, const T& value)
{
    if (vec.empty())
        return false;
    typedef typename V::const_pointer const_pointer;
    const_pointer pValue = &vec[0];
    size_t size = vec.size();
    for (size_t i = 0;i < size; ++i)
    {
        if (*pValue++ == value)
            return true;
    }
    return false;
}

