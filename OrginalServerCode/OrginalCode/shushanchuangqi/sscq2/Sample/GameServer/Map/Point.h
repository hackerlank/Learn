#pragma once
#include "MapProt.h"

using namespace NMapProt;

class CBaseObj;

struct SPoint
{
    float fX;
	float fY;

    SPoint(float fX_ = 0, float fY_ = 0) : fX(fX_), fY(fY_) { }
	SPoint(const SPosition& rPosition) : fX(rPosition.fX), fY(rPosition.fY) { }
	operator SPosition() const { return SPosition(fX, fY); }
	void Clear() { fX = fY = 0; }
	bool IsValid() const;
	static TVecPosition ToProtVecPoint(const vector<SPoint>& rVecPoint, size_t stStart = 0);
};

typedef vector<SPoint> TVecPoint;

bool operator==(const SPoint& rPoint1, const SPoint& rPoint2);
bool operator!=(const SPoint& rPoint1, const SPoint& rPoint2);
SPoint& operator+=(SPoint& rPoint1, const SPoint& rPoint2);
SPoint& operator-=(SPoint& rPoint1, const SPoint& rPoint2);
SPoint operator+(SPoint& rPoint1, const SPoint& rPoint2);
SPoint operator-(SPoint& rPoint1, const SPoint& rPoint2);

template<typename T>
SPoint operator*(SPoint& rPoint1, T val)
{
	return SPoint(rPoint1.fX * val, rPoint1.fY * val);
}

inline CLogObj& operator<<(CLogObj& src, const SPoint& rPoint)
{
	src << " [Point X: " << rPoint.fX << ", Y: " << rPoint.fY << "]";
	return src;
}

inline CLogObj& operator<<(CLogObj& src, const TVecPoint& vecPoint)
{
	for(size_t i = 0; i < vecPoint.size(); ++i)
		src << " [X: " << vecPoint[i].fX << ", Y: " << vecPoint[i].fY << "]";
	return src;
}

/////////////////////////////////////////////////////////////////////////////////

struct SCoord
{
	INT32 dwX;
	INT32 dwY;

	SCoord(INT32 dwX_ = 0, INT32 dwY_ = 0) : dwX(dwX_), dwY(dwY_) { }
	operator INT64() const { return ((INT64)dwX << 32) + dwY; }
};

bool operator==(const SCoord& rCoord1, const SCoord& rCoord2);
bool operator!=(const SCoord& rCoord1, const SCoord& rCoord2);
bool operator<(const SCoord& rCoord1, const SCoord& rCoord2);

bool HasBlockPoint(const SCoord& rCoord1, const SCoord& rCoord2, function<bool (INT32, INT32)> fnIsBlock, function<bool (INT32, INT32)> fnIsCorner = nullptr);
bool HasBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2, function<bool (INT32, INT32)> fnIsBlock, function<bool (INT32, INT32)> fnIsCorner = nullptr);

inline CLogObj& operator<<(CLogObj& src, const SCoord& rCoord)
{
	src << " [Coord X: " << rCoord.dwX << ", Y: " << rCoord.dwY << "]";
	return src;
}

/////////////////////////////////////////////////////////////////////////////////

float GetDistance(const SPoint& rPoint1, const SPoint& rPoint2);
float GetDistance(const CBaseObj& rObj1, const CBaseObj& rObj2);
float GetDir(const SPoint& rFrom, const SPoint& rTo);
SPoint GetMidPoint(const SPoint& rPoint1, const SPoint& rPoint2, float fLength);
SPoint GetExtPoint(const SPoint& rPoint1, const SPoint& rPoint2, float fLength);
bool LineIntersect(const SPoint& rPoint11, const SPoint& rPoint12, const SPoint& rPoint21, const SPoint& rPoint22);

inline INT32 Square(INT32 dwVal) { return dwVal * dwVal; }
inline float Square(float fVal) { return fVal * fVal; }
bool Transpose(INT32& dwX, INT32& dwZ);
bool GetCrossCoord(INT32 dwX, SCoord& rInCoord1, SCoord& rInCoord2, INT32& dwZ);
void GetIntersection(INT32 dwX, SCoord (&arCoord)[4], INT32& dwLowZ, INT32& dwUpZ);

template<typename T>
T Round(float fVal)
{
	return T(fVal + 0.5f);
}