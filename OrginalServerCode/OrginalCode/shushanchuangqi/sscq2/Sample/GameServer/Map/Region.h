#pragma once
#include "Point.h"
#include "TaskConfMgr.h"

enum ERegionType
{
	eRegionCommon,//普通区域
	eRegionJump,
	eRegionProbe,
	eRegionTaskTrigger,
	eRegionEnd
};

struct SRegion
{
	virtual bool IsInRegion(float fX, float fY) const = 0;
	virtual bool IsInRegion(const SPoint& rPoint) const = 0;
	virtual bool IntersectRegion(const SPoint& rPoint1, const SPoint& rPoint2) const;
};

struct SSquareRegion : public SRegion
{
	float fLLX, fLLY, fRUX, fRUY;

	void Init();
	void SetRegion(float fLLX, float fLLY, float fRUX, float fRUY, bool bAlighToGrid = true);
	virtual bool IsInRegion(float fX, float fY) const override;
	virtual bool IsInRegion(const SPoint& rPoint) const override;
	virtual bool IntersectRegion(const SPoint& rPoint1, const SPoint& rPoint2) const override;
	const SPoint& GetCenter() const { return oPoint; }
	const SPoint& GetRadius() const { return oRadius; }

private:
	SPoint oPoint;
	SPoint oRadius;
};

struct SRoundRegion : public SRegion
{
	float fX, fY, fRadius;

	void Init();
	void SetRegion(float fX, float fY, float fRadius, bool bAlighToGrid = true);
	void SetRegion(float fLLX, float fLLY, float fRUX, float fRUY, bool bAlighToGrid = true);
	virtual bool IsInRegion(float fX, float fY) const override;
	virtual bool IsInRegion(const SPoint& rPoint) const override;
	const SPoint& GetCenter() const { return oPoint; }
	float GetRadius() const { return fRadius; }

private:
	SPoint oPoint;
};

struct SJumpRegion : public SSquareRegion
{
	UINT16 wToMapID;
    UINT16 wID;
	SPoint oToPoint;

	SJumpRegion() : wToMapID(0), wID(0) { }
};

struct SProbeRegion : public SSquareRegion, public SProbeInfo
{
	SProbeRegion(const SProbeInfo& rProbeInfo);
};

struct SAreaRegion:public SSquareRegion
{
    UINT16 wAreaID;
    UINT16 wIndex;
    SAreaRegion():wAreaID(0),wIndex(0){ }

};
DEF_SMART_POINTER(struct,SAreaRegion);
