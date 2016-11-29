#include "stdafx.h"
#include <boost/math/special_functions/fpclassify.hpp>
#include "BaseObj.h"
#include "MapInfo.h"

bool SPoint::IsValid() const
{
	return boost::math::isfinite(fX) && boost::math::isfinite(fY);
}

TVecPosition SPoint::ToProtVecPoint(const vector<SPoint>& rVecPoint, size_t stStart /*= 0*/)
{
	TVecPosition vecPosition;
	for(size_t i = stStart; i < rVecPoint.size(); ++i)
		vecPosition.push_back(rVecPoint[i]);
	return vecPosition;
}

bool operator==(const SPoint& rPoint1, const SPoint& rPoint2)
{
	return fabsf(rPoint1.fX - rPoint2.fX) < FLT_EPSILON && fabsf(rPoint1.fY - rPoint2.fY) < FLT_EPSILON;
}

bool operator!=(const SPoint& rPoint1, const SPoint& rPoint2)
{
	return !operator==(rPoint1, rPoint2);
}

SPoint& operator+=(SPoint& rPoint1, const SPoint& rPoint2)
{
	rPoint1.fX += rPoint2.fX;
	rPoint1.fY += rPoint2.fY;
	return rPoint1;
}

SPoint& operator-=(SPoint& rPoint1, const SPoint& rPoint2)
{
	rPoint1.fX -= rPoint2.fX;
	rPoint1.fY -= rPoint2.fY;
	return rPoint1;
}

SPoint operator+(SPoint& rPoint1, const SPoint& rPoint2)
{
	return SPoint(rPoint1.fX + rPoint2.fX, rPoint1.fY + rPoint2.fY);
}

SPoint operator-(SPoint& rPoint1, const SPoint& rPoint2)
{
	return SPoint(rPoint1.fX - rPoint2.fX, rPoint1.fY - rPoint2.fY);
}

/////////////////////////////////////////////////////////////////////////////////

bool operator==(const SCoord& rCoord1, const SCoord& rCoord2)
{
	return rCoord1.dwX == rCoord2.dwX && rCoord1.dwY == rCoord2.dwY;
}

bool operator!=(const SCoord& rCoord1, const SCoord& rCoord2)
{
	return !operator==(rCoord1, rCoord2);
}

bool operator<(const SCoord& rCoord1, const SCoord& rCoord2)
{
	return rCoord1.dwX < rCoord2.dwX || rCoord1.dwY < rCoord2.dwY;
}

bool HasBlockPoint(const SCoord& oCoord1, const SCoord& oCoord2, function<bool (INT32, INT32)> fnIsBlock, function<bool (INT32, INT32)> fnIsCorner /*= nullptr*/)
{
	if(fnIsBlock == nullptr)
		return false;

	if(oCoord1 == oCoord2)
	{
		if(!fnIsBlock(oCoord1.dwX, oCoord1.dwY))
			return false;
		if(fnIsCorner != nullptr && fnIsCorner(oCoord1.dwX, oCoord1.dwY))
			return false;
        LOG_CRI <<"b 1";
		return true;
	}

	INT32 dwDeltaX = oCoord2.dwX - oCoord1.dwX, dwDeltaY = oCoord2.dwY - oCoord1.dwY;

	INT32 dwStep = 0;
	if(abs(dwDeltaX) > abs(dwDeltaY))
		dwStep = abs(dwDeltaX);
	else
		dwStep = abs(dwDeltaY);

	if(dwStep == 0)
		return false;

	float fIncX = dwDeltaX / (float)dwStep;
	float fIncY = dwDeltaY / (float)dwStep;

	float fX = (float)oCoord1.dwX, fY = (float)oCoord1.dwY;
	INT32 dwPreX = 0, dwPreY = 0, dwCurX = 0, dwCurY = 0;
	for(INT32 k = 0; k <= dwStep; k++)
	{
		dwPreX = dwCurX;
		dwPreY = dwCurY;
		dwCurX = Round<INT32>(fX);
		dwCurY = Round<INT32>(fY);
		if(fnIsBlock(dwCurX, dwCurY))
		{
			if(fnIsCorner == nullptr || !fnIsCorner(dwCurX, dwCurY))
            {
                //LOG_CRI <<"b 2";
                //LOG_CRI <<"dwCurX:" <<dwCurX<<"dwCurY:"<<dwCurY;
				return true;
            }
		}
		if(k > 0 && abs((dwCurX - dwPreX) * (dwCurY - dwPreY)) == 1)
		{
			if(fnIsBlock(dwPreX, dwCurY) && fnIsBlock(dwCurX, dwPreY))
            {
                //LOG_CRI <<"b 3";
                //LOG_CRI <<"dwCurX:" <<dwCurX<<"dwCurY:"<<dwCurY;
				return true;
            }
		}
		fX += fIncX;
		fY += fIncY;
	}
	return false;
}

bool HasBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2, function<bool (INT32, INT32)> fnIsBlock, function<bool (INT32, INT32)> fnIsCorner /*= nullptr*/)
{
	SCoord oCoord1, oCoord2;
	PointToCoord(rPoint1, oCoord1, true);
	PointToCoord(rPoint2, oCoord2, true);

	if(fnIsBlock == nullptr)
		return false;

	if(oCoord1 == oCoord2)
	{
		if(!fnIsBlock(oCoord1.dwX, oCoord1.dwY))
			return false;
		if(fnIsCorner != nullptr && fnIsCorner(oCoord1.dwX, oCoord1.dwY))
			return false;
		return true;
	}

	INT32 dwDeltaX = oCoord2.dwX - oCoord1.dwX, dwDeltaY = oCoord2.dwY - oCoord1.dwY;

	INT32 dwStep = 0;
	if(abs(dwDeltaX) > abs(dwDeltaY))
		dwStep = abs(dwDeltaX);
	else
		dwStep = abs(dwDeltaY);

	if(dwStep == 0)
		return false;

	float fIncX = (rPoint2.fX - rPoint1.fX) / dwStep;
	float fIncY = (rPoint2.fY - rPoint1.fY) / dwStep;

	float fX = rPoint1.fX, fY = rPoint1.fY;
	INT32 dwPreX = 0, dwPreY = 0, dwCurX = 0, dwCurY = 0;
	for(INT32 k = 0; k <= dwStep; k++)
	{
		dwPreX = dwCurX;
		dwPreY = dwCurY;
		dwCurX = Round<INT32>(fX);
		dwCurY = Round<INT32>(fY);
		if(fnIsBlock(dwCurX, dwCurY))
		{
			if(fnIsCorner == nullptr || !fnIsCorner(dwCurX, dwCurY))
				return true;
		}
		if(k > 0 && abs((dwCurX - dwPreX) * (dwCurY - dwPreY)) == 1)
		{
			if(fnIsBlock(dwPreX, dwCurY) && fnIsBlock(dwCurX, dwPreY))
				return true;
		}
		fX += fIncX;
		fY += fIncY;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////

float GetDistance(const SPoint& rPoint1, const SPoint& rPoint2)
{
	float fDeltaX = rPoint2.fX - rPoint1.fX;
	float fDeltaY = rPoint2.fY - rPoint1.fY;
	return sqrtf(fDeltaX * fDeltaX + fDeltaY * fDeltaY);
}

float GetDistance(const CBaseObj& rObj1, const CBaseObj& rObj2)
{
	if(rObj1.GetMap() != rObj2.GetMap())
		return FLT_MAX;
	return GetDistance(rObj1.GetPoint(), rObj2.GetPoint());
}

float GetDir(const SPoint& rFrom, const SPoint& rTo)
{
	return atan2f(rTo.fY - rFrom.fY, rTo.fX - rFrom.fX);
}

SPoint GetMidPoint(const SPoint& rPoint1, const SPoint& rPoint2, float fLength)
{
	if(fLength < FLT_EPSILON)
		return rPoint1;
	SPoint oMidPoint;
	float fDistance = GetDistance(rPoint1, rPoint2);
	if(fDistance < FLT_EPSILON)
		return rPoint1;
	float fPercent = fLength / fDistance;
	if(!boost::math::isfinite(fPercent))
		return rPoint1;
	float fDeltaX = rPoint2.fX - rPoint1.fX;
	float fDelatY = rPoint2.fY - rPoint1.fY;
	oMidPoint.fX = rPoint1.fX + fDeltaX * fPercent;
	oMidPoint.fY = rPoint1.fY + fDelatY * fPercent;
	return oMidPoint;
}

SPoint GetExtPoint(const SPoint& rPoint1, const SPoint& rPoint2, float fLength)
{
	if(fLength < FLT_EPSILON)
		return rPoint2;
	SPoint oExtPoint;
	float fDistance = GetDistance(rPoint1, rPoint2);
	if(fDistance < FLT_EPSILON)
		return rPoint2;
	float fPercent = fLength / fDistance;
	if(!boost::math::isfinite(fPercent))
		return rPoint2;
	float fDeltaX = rPoint2.fX - rPoint1.fX;
	float fDelatY = rPoint2.fY - rPoint1.fY;
	oExtPoint.fX = rPoint2.fX + fDeltaX * fPercent;
	oExtPoint.fY = rPoint2.fY + fDelatY * fPercent;
	return oExtPoint;
}

bool LineIntersect(const SPoint& rPoint11, const SPoint& rPoint12, const SPoint& rPoint21, const SPoint& rPoint22)
{
	return max(rPoint11.fX, rPoint12.fX) >= min(rPoint21.fX, rPoint22.fX)
		&& max(rPoint21.fX, rPoint22.fX) >= min(rPoint11.fX, rPoint12.fX)
		&& max(rPoint11.fY, rPoint12.fY) >= min(rPoint21.fY, rPoint22.fY)
		&& max(rPoint21.fY, rPoint22.fY) >= min(rPoint11.fY, rPoint12.fY);
}

bool Transpose(INT32& dwX, INT32& dwZ)
{
	INT32 dwTemp = dwX;
	if((dwX >= 0 && dwZ >= 0) || (dwX <= 0 && dwZ <= 0))
	{
		dwX = dwZ; dwZ = dwTemp;
	}
	else
	{
		dwX = -dwZ; dwZ = -dwTemp;
		if(dwX > 0 && dwZ < 0)
		{
			++dwX;
			return true;
		}
	}
	return false;
}

bool GetCrossCoord(INT32 dwX, SCoord& rInCoord1, SCoord& rInCoord2, INT32& dwZ)
{
	if(rInCoord1.dwX == rInCoord2.dwX)
		return false;
	INT32 dwDivisor = rInCoord2.dwX - rInCoord1.dwX;
	dwZ = (rInCoord2.dwY - rInCoord1.dwY) * (dwX - rInCoord1.dwX) / dwDivisor + rInCoord1.dwY;
	return true;
}

void GetIntersection(INT32 dwX, SCoord (&arCoord)[4], INT32& dwLowZ, INT32& dwUpZ)
{
	vector<INT32> vec;
	INT32 dwZ1 = 0, dwZ2 = 0;
	if(GetCrossCoord(dwX, arCoord[0], arCoord[1], dwZ1) && GetCrossCoord(dwX, arCoord[2], arCoord[3], dwZ2))
	{
		vec.push_back(dwZ1);
		vec.push_back(dwZ2);
	}
	if(GetCrossCoord(dwX, arCoord[1], arCoord[2], dwZ1) && GetCrossCoord(dwX, arCoord[3], arCoord[0], dwZ2))
	{
		vec.push_back(dwZ1);
		vec.push_back(dwZ2);
	}
	sort(vec.begin(), vec.end());
	if(vec.size() == 4)
	{
		dwLowZ = vec[1];
		dwUpZ = vec[2];
	}
	else if(vec.size() == 2)
	{
		dwLowZ = vec[0];
		dwUpZ = vec[1];
	}
	else
	{
		dwLowZ = dwUpZ = 0;
		LOG_CRI << "Error: " << vec.size();
	}
}
