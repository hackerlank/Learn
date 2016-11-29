/********************************************************************
//	Server Utility Library Source File.
//	File name:	Random.h
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
#include <vector>
#include <type_traits>
#include "Platform.h"
#include "CallStack.h"

using std::vector;
using std::remove_reference;

//随机数生成器
class CRandom
{
public:
	static void ResetSeed();
	static INT32 RandInt();
	static INT32 RandInt(INT32 dwMin, INT32 dwMax);
	static float RandFloat(float fMin, float fMax);
	static size_t RandArrayIndex(size_t stSize);

	template<typename T>
	static size_t RandWeightArrayIndex(T* pWeight, size_t stSize);	//权重数组随机索引

	template<typename T, size_t SIZE>
	static size_t RandWeightArrayIndex(T (&arWeight)[SIZE]);	//权重数组随机索引

	template<typename T>
	static size_t RandWeightArrayIndex(vector<T>& vecWeight);	//权重Vector随机索引

	template<typename T, typename M>
	static size_t RandWeightArrayIndex(T* pWeight, M member, size_t stSize);	//带权重Struct数组随机索引

	template<typename T, size_t SIZE, typename M>
	static size_t RandWeightArrayIndex(T (&arWeight)[SIZE], M member);	//带权重Struct数组随机索引

	template<typename T, typename M>
	static size_t RandWeightArrayIndex(vector<T>& vecWeight, M member);	//带权重Struct权重Vector随机索引

	template<typename T, typename F>
	static void RandWeightArrayIndexList(T* pWeight, size_t stSize, size_t stCount, F func);	//权重数组随机索引

	template<typename T, size_t SIZE, typename F>
	static void RandWeightArrayIndexList(T (&arWeight)[SIZE], size_t stCount, F func);	//权重数组随机索引

	template<typename T, typename F>
	static void RandWeightArrayIndexList(vector<T>& vecWeight, size_t stCount, F func);	//权重Vector随机索引

	template<typename T, typename M, typename F>
	static void RandWeightArrayIndexList(T* pWeight, M member, size_t stSize, size_t stCount, F func);	//带权重Struct数组随机多索引

	template<typename T, size_t SIZE, typename M, typename F>
	static void RandWeightArrayIndexList(T (&arWeight)[SIZE], M member, size_t stCount, F func);	//带权重Struct数组随机多索引

	template<typename T, typename M, typename F>
	static void RandWeightArrayIndexList(vector<T>& vecWeight, M member, size_t stCount, F func);	//带权重Struct权重Vector随机多索引

	template<typename T>
	static T& RandVecElem(vector<T>& vec);	//随机选择Vector的元素
};

template<typename T>
size_t CRandom::RandWeightArrayIndex(T* pWeight, size_t stSize)
{
	if(pWeight == NULL || stSize == 0)
		return 0;
	T total = 0;
	for(size_t i = 0; i < stSize; ++i)
		total += pWeight[i];
	if(total == 0)
		return 0;
	T rand = (T)RandInt(1, total);
	size_t index = 0;
	for(index = 0; index < stSize; ++index)
	{
		if(rand <= pWeight[index])
			break;
		rand -= pWeight[index];
	}
	assert(index < stSize);
	return index;
}

template<typename T, size_t SIZE>
size_t CRandom::RandWeightArrayIndex(T (&arWeight)[SIZE])
{
	return RandWeightArrayIndex((T*)arWeight, SIZE);
}

template<typename T>
size_t CRandom::RandWeightArrayIndex(vector<T>& vecWeight)
{
	return RandWeightArrayIndex(vecWeight.data(), vecWeight.size());
}

template<typename T, typename M>
size_t CRandom::RandWeightArrayIndex(T* pWeight, M member, size_t stSize)
{
	if(pWeight == NULL || stSize == 0)
		return 0;
	typedef typename remove_reference<decltype(pWeight->*member)>::type TVal;
	TVal total = 0;
	for(size_t i = 0; i < stSize; ++i)
	{
		TVal val = pWeight[i].*member;
		assert(val >= 0);
		total += val;
	}
	if(total == 0)
		return 0;
	TVal rand = (TVal)RandInt(1, total);
	size_t index = 0;
	for(index = 0; index < stSize; ++index)
	{
		if(rand <= pWeight[index].*member)
			break;
		rand -= pWeight[index].*member;
	}
	assert(index < stSize);
	return index;
}

template<typename T, size_t SIZE, typename M>
size_t CRandom::RandWeightArrayIndex(T (&arWeight)[SIZE], M member)
{
	return RandWeightArrayIndex(arWeight, member, SIZE);
}

template<typename T, typename M>
size_t CRandom::RandWeightArrayIndex(vector<T>& vecWeight, M member)
{
	return RandWeightArrayIndex(vecWeight.data(), member, vecWeight.size());
}

template<typename T, typename F>
void CRandom::RandWeightArrayIndexList(T* pWeight, size_t stSize, size_t stCount, F func)
{
	if(pWeight == NULL || stSize == 0 || stCount == 0)
		return;
	if(stSize <= stCount)
	{
		for(size_t i = 0; i < stSize; ++i)
		{
			if(pWeight[i] != 0)
				func(i);
		}
		return;
	}
	T total = 0;
	for(size_t i = 0; i < stSize; ++i)
	{
		assert(pWeight[i] >= 0);
		total += pWeight[i];
	}
	if(total == 0)
		return;
	vector<bool> vecSelect(stSize);
	size_t stCurCount = 0;
	while(stCurCount < stCount)
	{
		T rand = (T)RandInt(1, total);
		size_t index = 0;
		for(index = 0; index < stSize; ++index)
		{
			if(vecSelect[index])
				continue;
			if(rand <= pWeight[index])
				break;
			rand -= pWeight[index];
		}
		assert(index < stSize);
		vecSelect[index] = true;
		func(index);
		++stCurCount;
		total -= pWeight[index];
	}
}

template<typename T, size_t SIZE, typename F>
void CRandom::RandWeightArrayIndexList(T (&arWeight)[SIZE], size_t stCount, F func)
{
	return RandWeightArrayIndexList(arWeight, SIZE, stCount, func);
}

template<typename T, typename F>
void CRandom::RandWeightArrayIndexList(vector<T>& vecWeight, size_t stCount, F func)
{
	return RandWeightArrayIndexList(vecWeight.data(), vecWeight.size(), stCount, func);
}

template<typename T, typename M, typename F>
void CRandom::RandWeightArrayIndexList(T* pWeight, M member, size_t stSize, size_t stCount, F func)
{
	if(pWeight == NULL || stSize == 0 || stCount == 0)
		return;
	if(stSize <= stCount)
	{
		for(size_t i = 0; i < stSize; ++i)
		{
			if(pWeight[i].*member != 0)
				func(i);
		}
		return;
	}
	typedef typename remove_reference<decltype(pWeight->*member)>::type TVal;
	TVal total = 0;
	for(size_t i = 0; i < stSize; ++i)
	{
		TVal val = pWeight[i].*member;
		assert(val >= 0);
		total += val;
	}
	if(total == 0)
		return;
	vector<bool> vecSelect(stSize);
	size_t stCurCount = 0;
	while(stCurCount < stCount)
	{
		TVal rand = (TVal)RandInt(1, total);
		size_t index = 0;
		for(index = 0; index < stSize; ++index)
		{
			if(vecSelect[index])
				continue;
			if(rand <= pWeight[index].*member)
				break;
			rand -= pWeight[index].*member;
		}
		assert(index < stSize);
		vecSelect[index] = true;
		func(index);
		++stCurCount;
		total -= pWeight[index].*member;
	}
}

template<typename T, size_t SIZE, typename M, typename F>
void CRandom::RandWeightArrayIndexList(T (&arWeight)[SIZE], M member, size_t stCount, F func)
{
	RandWeightArrayIndexList(arWeight, member, SIZE, stCount, func);
}

template<typename T, typename M, typename F>
void CRandom::RandWeightArrayIndexList(vector<T>& vecWeight, M member, size_t stCount, F func)
{
	RandWeightArrayIndexList(vecWeight.data(), member, vecWeight.size(), stCount, func);
}

template<typename T>
T& CRandom::RandVecElem(vector<T>& vec)
{
	if(vec.empty())
		DebugBreak();
	return vec[RandArrayIndex(vec.size())];
}
