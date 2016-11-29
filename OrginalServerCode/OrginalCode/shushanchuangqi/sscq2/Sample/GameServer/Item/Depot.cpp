#include "stdafx.h"
#include "Depot.h"
#include "Parameter.h"
#include "VIPMgr.h"
#include "User.h"

CDepot::CDepot(CUser& rUser) : CPack(rUser, SParamConfig::wDepotInitCount)
{
}

UINT16 CDepot::GetCapacity() const
{
    /*
    SVIPLevelCFGEx* pVIPLvlCfg = VIPMgr.GetVIPLevelCfg(GetUser().GetVIPLevel());
    if (!pVIPLvlCfg)
        return 0;
    return pVIPLvlCfg->_StoreNum;
    */
    return _wCapacity;
}
