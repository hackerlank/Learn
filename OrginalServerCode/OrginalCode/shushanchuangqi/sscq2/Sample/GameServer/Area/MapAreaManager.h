#ifndef AREAMANGER_H_H__
#define AREAMANGER_H_H__
#include "stdafx.h"
#include "Region.h"
#include "AreaCFG.h"
#include "MapArea.h"
struct SAreaCFGEx: public SAreaCFG
{
    SAreaCFGEx():_bHasLua(false),_bLoadLua(false){}
    SAreaCFGEx(const SAreaCFG &rConfig):SAreaCFG(rConfig),_bHasLua(false),_bLoadLua(false){}
    bool HasLua() const ;
    void ClearLua();
    void CheckLua();
    private:
    bool _bHasLua;
    bool _bLoadLua;
};

class CMapAreaManager
{
    public:
        CMapAreaManager():_dwNextID(0){}
        bool Init();
        void ClearAllLua();
        const SAreaCFGEx* GetConfigById(UINT16 wId);
        CMapAreaPtr CreateArea(const SAreaPoint& rArea);
        UINT32 GetNewInstID();
        void Destroy(CMapArea& pArea);
    private:
        map<UINT16,SAreaCFGEx> _mapAreaCfg;
        map<UINT32,CMapAreaPtr> _mapArea;
        UINT32 _dwNextID;
};
extern CMapAreaManager g_AreaManager;
#endif //AREAMANGER_H_H__
