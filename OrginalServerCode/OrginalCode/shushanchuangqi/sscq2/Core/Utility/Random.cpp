/********************************************************************
//	Server Utility Library Source File.
//	File name:	Random.cpp
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

#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <random>
#include "Random.h"

using namespace std;

static mt19937 rgn;

void CRandom::ResetSeed()
{
	rgn.seed((UINT32)time(NULL));
}

INT32 CRandom::RandInt()
{
	static uniform_int_distribution<INT32> ui(INT_MIN, INT_MAX);
	return ui(rgn);
}

INT32 CRandom::RandInt(INT32 dwMin, INT32 dwMax)
{
	if(dwMin >= dwMax)
		return dwMin;
	uniform_int_distribution<INT32> ui(dwMin, dwMax);
	return ui(rgn);
}

float CRandom::RandFloat(float fMin, float fMax)
{
	if(fMin >= fMax)
		return fMin;
	uniform_real_distribution<float> ur(fMin, fMax);
	return ur(rgn);
}

size_t CRandom::RandArrayIndex(size_t stSize)
{
	if(0 == stSize)
		return 0;

	uniform_int_distribution<size_t> ui(0, stSize - 1);
	return ui(rgn);
}
