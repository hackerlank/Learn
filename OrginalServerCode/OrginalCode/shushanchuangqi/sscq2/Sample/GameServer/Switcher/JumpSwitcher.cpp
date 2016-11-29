#include "stdafx.h"
#include "JumpSwitcher.h"
#include "Dungeon.h"
#include "MapInfo.h"

void CJumpSwitcher::InitJumpInfo(const SDgnJumpPoint& rJumpPoint)
{
    _oJumpRegion.wToMapID = rJumpPoint.wToMapID;
    _oJumpRegion.oToPoint.fX = rJumpPoint.fToX;
     _oJumpRegion.oToPoint.fY = rJumpPoint.fToY;
     _oJumpRegion.SetRegion(rJumpPoint.fLX, rJumpPoint.fLY, rJumpPoint.fRX, rJumpPoint.fRY);
     _oJumpRegion.wID = rJumpPoint.wID;
}

void CJumpSwitcher::TimerCheck()
{
	
}

void CJumpSwitcher::Exec()
{

}
