#include "MapAreaManager.h"
#include "MapInfo.h"
CMapAreaManager g_AreaManager; 
bool SAreaCFGEx::HasLua() const 
{
    return _bHasLua;
}

void  SAreaCFGEx::ClearLua()
{
    _bLoadLua = false;
}

void SAreaCFGEx::CheckLua()
{
    if(!_bLoadLua)
    {
        _bHasLua = Config.GetScript().HasInAreaFunction(_areaId);
        _bLoadLua = true;
    }
}

bool CMapAreaManager::Init()
{
    string strPath = Config._strConfigDir + "Conf/Table/Area.xml";
    CAreaLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(auto it = oLoader._vecData.begin() ;it != oLoader._vecData.end();it++)
    {
        SAreaCFGEx rCfg(*(*it));
        _mapAreaCfg[rCfg._areaId] =  rCfg;
    }
    return true;
}

void CMapAreaManager::ClearAllLua()
{
    for(auto it = _mapAreaCfg.begin();it != _mapAreaCfg.end(); it++)
    {
        it->second.ClearLua();
    }
}

const SAreaCFGEx* CMapAreaManager::GetConfigById(UINT16 wId)
{
    auto it = _mapAreaCfg.find(wId);
    if(it == _mapAreaCfg.end())
    {
        return NULL;
    }
    it->second.CheckLua();
    return &(it->second);
}


UINT32 CMapAreaManager::GetNewInstID()
{
    return ++_dwNextID;
}

CMapAreaPtr  CMapAreaManager::CreateArea(const SAreaPoint& rArea)
{
    const SAreaCFGEx* pCfg = GetConfigById(rArea.wID);
    if(pCfg == NULL)
    {
        return NULL;
    }
    CMapAreaPtr pArea(new CMapArea(GetNewInstID(),rArea));
    if(pArea != NULL)
    {
        _mapArea[pArea->GetInstID()] = pArea;
    }
    return pArea;
}


void CMapAreaManager::Destroy(CMapArea& rArea)
{
    _mapArea.erase(rArea.GetInstID());
}
