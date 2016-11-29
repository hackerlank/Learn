#include "stdafx.h"
#include "MapArea.h"
#include "Map.h"
#include "Protocols.h"
#include "MapAreaManager.h"
CMapArea::CMapArea(UINT32 dwInstID,const SAreaPoint& rArea )
{
    _dwInstID = dwInstID;
     wAreaID = rArea.wID;
     wIndex = rArea.wIndex;
     fLLX = rArea.fLX;
     fLLY = rArea.fLY;
     fRUX = rArea.fRX;
     fRUY = rArea.fRY;
}
void CMapArea::GetAreaAppear(SAreaAppear& rAreaAppear)
{
	rAreaAppear.wAreaID = GetAreaID();
}

void CMapArea::Disappear()
{
	CGameMapPtr pMap = GetMap();
	if(pMap != NULL)
	{
		pMap->AreaDisappear(*this);
	}
	else
    {
		LOG_CRI << "_pMap is NULL! _dwInstID: " << _dwInstID;
     	g_AreaManager.Destroy(*this);
    }
}

bool CMapArea::IsSafe()
{
    const SAreaCFGEx* pCfg = g_AreaManager.GetConfigById(wAreaID);
    if(pCfg)
    {
        return pCfg->_IsSafe > 0;
    }
    return false;
}
bool CMapArea::CanDel()
{
    const SAreaCFGEx* pCfg = g_AreaManager.GetConfigById(wAreaID);
    if(pCfg)
    {
        return pCfg->_IsDel == 0;
    }
    return true;
}


