#include "Protocols.h"
#include "TripodFire.h"

CFire::CFire(UINT16 wFireID)
    : _wFireID(wFireID), _dwSucceed(0), _dwRemain(0)
{
}

CFire::~CFire()
{}

void CFire::ToProt(SFireInfo& oFireInfo)
{
    oFireInfo.wFireID   = GetID();
    oFireInfo.dwSucceed = GetSucceedCnt();
    oFireInfo.dwRemain  = GetRemainCnt();
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

