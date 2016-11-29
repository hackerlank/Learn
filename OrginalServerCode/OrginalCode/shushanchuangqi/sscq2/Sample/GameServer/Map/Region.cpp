#include "stdafx.h"
#include "Region.h"

bool SRegion::IntersectRegion(const SPoint& rPoint1, const SPoint& rPoint2) const
{
	LOG_CRI << "Not implemented!";
	PRINT_CALL_STACK_DEBUG;
	return false;
}

void SSquareRegion::Init()
{
	oPoint.fX = (fLLX + fRUX) / 2;
	oPoint.fY = (fLLY + fRUY) / 2;
	oRadius.fX = abs(fRUX - fLLX) / 2;
	oRadius.fY = abs(fRUY - fLLY) / 2;
}

void SSquareRegion::SetRegion(float fLLX_, float fLLY_, float fRUX_, float fRUY_, bool bAlighToGrid /*= true*/)
{
	fLLX = fLLX_;
	fLLY = fLLY_;
	fRUX = fRUX_;
	fRUY = fRUY_;
	if(bAlighToGrid)
	{
		fLLX -= 0.5;
		fLLY -= 0.5;
		fRUX += 0.5;
		fRUY += 0.5;
	}
	Init();
}

bool SSquareRegion::IsInRegion(float fX, float fY) const
{
	return fX >= fLLX && fX <= fRUX && fY >= fLLY && fY <= fRUY;
}

bool SSquareRegion::IsInRegion(const SPoint& rPoint) const
{
	return IsInRegion(rPoint.fX, rPoint.fY);
}

bool SSquareRegion::IntersectRegion(const SPoint& rPoint1, const SPoint& rPoint2) const
{
	SPoint oLLPoint(fLLX, fLLY), oLUPoint(fLLX, fRUY), oRLPoint(fRUX, fLLY), oRUPoint(fRUX, fRUY);
	if(max(rPoint1.fX, rPoint2.fX) < min(fLLX, fRUX))
		return false;
	if(min(rPoint1.fX, rPoint2.fX) > max(fLLX, fRUX))
		return false;
	if(max(rPoint1.fY, rPoint2.fY) < min(fLLY, fRUY))
		return false;
	if(min(rPoint1.fY, rPoint2.fY) > max(fLLY, fRUY))
		return false;
	if(LineIntersect(rPoint1, rPoint2, oLLPoint, oLUPoint))
		return true;
	if(LineIntersect(rPoint1, rPoint2, oLUPoint, oRLPoint))
		return true;
	if(LineIntersect(rPoint1, rPoint2, oRLPoint, oRUPoint))
		return true;
	if(LineIntersect(rPoint1, rPoint2, oRUPoint, oLLPoint))
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////

void SRoundRegion::Init()
{
	oPoint.fX = fX;
	oPoint.fY = fY;
}

void SRoundRegion::SetRegion(float fX_, float fY_, float fRadius_, bool bAlighToGrid /*= true*/)
{
	fX = fX_;
	fY = fY_;
	fRadius = fRadius_;
	if(bAlighToGrid)
		fRadius += 1;
	Init();
}

void SRoundRegion::SetRegion(float fLLX, float fLLY, float fRUX, float fRUY, bool bAlighToGrid /*= true*/)
{
	fX = (fLLX + fRUX) / 2;
	fY = (fLLY + fRUY) / 2;
	float fRadiusX = abs(fRUX - fLLX) / 2;
	float fRadiusY = abs(fRUY - fLLY) / 2;
	fRadius = max(fRadiusX, fRadiusY);
	if(bAlighToGrid)
		fRadius += 1;
	Init();
}

bool SRoundRegion::IsInRegion(float fX_, float fY_) const
{
	return Square(fX_ - fX) + Square(fY_ - fY) <= Square(fRadius);
}

bool SRoundRegion::IsInRegion(const SPoint& rPoint) const
{
	return IsInRegion(rPoint.fX, rPoint.fY);
}

////////////////////////////////////////////////////////////////////////////

SProbeRegion::SProbeRegion(const SProbeInfo& rProbeInfo) : SProbeInfo(rProbeInfo)
{
	if(rProbeInfo.oMapArea.fX1 < rProbeInfo.oMapArea.fX2)
	{
		fLLX = rProbeInfo.oMapArea.fX1;
		fRUX = rProbeInfo.oMapArea.fX2;
	}
	else
	{
		fLLX = rProbeInfo.oMapArea.fX2;
		fRUX = rProbeInfo.oMapArea.fX1;
	}

	if(rProbeInfo.oMapArea.fZ1 < rProbeInfo.oMapArea.fZ2)
	{
		fLLY = rProbeInfo.oMapArea.fZ1;
		fRUY = rProbeInfo.oMapArea.fZ2;
	}
	else
	{
		fLLY = rProbeInfo.oMapArea.fZ2;
		fRUY = rProbeInfo.oMapArea.fZ1;
	}

	Init();
}
