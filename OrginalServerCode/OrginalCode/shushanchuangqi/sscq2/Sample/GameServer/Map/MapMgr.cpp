#include "stdafx.h"
#include <boost/progress.hpp>
#include "MapMgr.h"
#include "MapCFG.h"
#include "MapInfo.h"
#include "Map.h"
#include "Tokenizer.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "Battle.h"
#include "Skill.h"

map<UINT16, SMapInfoPtr> CMapMgr::_mapID2MapInfo;
map<UINT16, vector<CGameMapPtr>> CMapMgr::_mapID2Map;

UINT32 CMapMgr::_dwCurOnlineUserCount = 0;

bool CMapMgr::Init()
{
    if(!LoadMapInfo())
    {
        LOG_CRI << "LoadMapInfo fails!";
        return false;
    }
    if(!Config._bIsCrossServer && !CreateAllMap())
    {
        LOG_CRI << "CreateAllMap fails!";
        return false;
    }
    //TestMap();
    return true;
}

bool CMapMgr::ReloadAllMap()
{
    if(!LoadMapInfo())
    {
        LOG_CRI << "LoadMapInfo fails!";
        return false;
    }
    RefreshAllMap();
    return true;
}

bool CMapMgr::Destroy()
{
    _mapID2Map.clear();
    _mapID2MapInfo.clear();
    return true;
}

bool CMapMgr::LoadMapInfo()
{
    CMapLoader oMapLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Map.xml";
    if(!oMapLoader.LoadData(strPath))
        return false;

    if(LOG_OBJ.IsConsoleOpen())
        cout << "Loading Map Config...";
    boost::progress_display show_progress((ULONG)oMapLoader._vecData.size());
    for(size_t i = 0; i < oMapLoader._vecData.size(); ++i)
    {
        SMapCFG& rMapCFG = *oMapLoader._vecData[i];
        if(rMapCFG._ConfigFile.empty())
        {
            LOG_CRI << "Map Config File is empty! MapID: " << rMapCFG._ID;
            return false;
        }

        SMapInfoPtr pMapInfo(new SMapInfo);
        if(pMapInfo == NULL)
            return false;
        pMapInfo->wMapID = rMapCFG._ID;
        pMapInfo->strName = rMapCFG._Name;
        pMapInfo->bSafe = rMapCFG._IsSafe;
        pMapInfo->byCamp = rMapCFG._Force;
        pMapInfo->wLeastlevel = rMapCFG._Leastlevel;
        pMapInfo->wDropID = rMapCFG._DropID;


        pMapInfo->wFighterMapID = rMapCFG._FightMap;
        AnalysisString2VectorUINT32(rMapCFG._SkillID, pMapInfo->vecSkillID, ";");

        if(rMapCFG._Type >= eMapTypeMax)
        {
            LOG_CRI << "Invalid Map Type: " << rMapCFG._Type;
            return false;
        }
        pMapInfo->eMapType = (EMapType)(rMapCFG._Type);
        if(eMapNormal == pMapInfo->eMapType )
        {
            if (rMapCFG._SMaxPlayer == 0 || rMapCFG._MaxPlayer <= rMapCFG._SMaxPlayer)
            {
                LOG_CRI <<"person num err  map:" << rMapCFG._ID;
                return false;
            }
            else
            {
                pMapInfo->wMaxPlayer =  rMapCFG._MaxPlayer;
                pMapInfo->wSMaxPlayer = rMapCFG._SMaxPlayer;
            }
        }

        string strConfigFile = Config._strConfigDir + "Conf/Map/" + rMapCFG._ConfigFile;
        if(pMapInfo->LoadConfig(strConfigFile))
        {
            _mapID2MapInfo.insert(make_pair(rMapCFG._ID, pMapInfo));
        }
        else
        {
            LOG_CRI << "LoadConfig fails! Path: " << strConfigFile;
            return false;
        }
        pMapInfo->InitBroadCastRadius();
        if(LOG_OBJ.IsConsoleOpen())
            ++show_progress;
    }

    return true;
}

bool CMapMgr::CreateAllMap()
{
    for(auto it = _mapID2MapInfo.begin(); it != _mapID2MapInfo.end(); ++it)
    {
        SMapInfoPtr pMapInfo = it->second;
        if(!pMapInfo->IsDungeon())
        {
            CGameMapPtr pMap = CreateMap(*pMapInfo);
            if(pMap == NULL)
                return false;
        }
    }
    return true;
}

void CMapMgr::RefreshAllMap()
{
    for(auto& p : _mapID2Map)
    {
        vector<CGameMapPtr>& pvecMap = p.second;
        for(auto it = pvecMap.begin();it != pvecMap.end();it++)
        {
            CGameMapPtr pMap = *(it);
            SMapInfo& rMapInfo = (SMapInfo&)pMap->GetMapInfo();
            rMapInfo.InitMap(pMap, true);
        }
    }
}

bool CMapMgr::IsDgnMap(UINT16 wMapID)
{
    if(wMapID == 0)
        return false;
    SMapInfoPtr pMapInfo = GetMapInfo(wMapID);
    if(pMapInfo == NULL)
    {
        LOG_CRI << "pMapInfo is NULL! MapID: " << wMapID;
        return false;
    }
    return pMapInfo->IsDungeon();
}

bool CMapMgr::IsGuildBattleMap(UINT16 wMapID)
{
    if(wMapID == 0)
        return false;
    SMapInfoPtr pMapInfo = GetMapInfo(wMapID);
    if(pMapInfo == NULL)
    {
        LOG_CRI << "pMapInfo is NULL! MapID: " << wMapID;
        return false;
    }
    return pMapInfo->IsGuildBattle();
}

CGameMapPtr CMapMgr::CreateMap(UINT16 wMapID)
{
    auto it = _mapID2MapInfo.find(wMapID);
    if(it == _mapID2MapInfo.end())
        return NULL;
    SMapInfoPtr& pMapInfo = it->second;
    return CreateMap(*pMapInfo);
}

CGameMapPtr CMapMgr::CreateMap(SMapInfo& rMapInfo)
{
    CGameMapPtr pMap(new CGameMap(rMapInfo));
    if(pMap == NULL)
        return NULL;
    if(!pMap->InitConfig())
    {
        LOG_CRI << "Map InitConfig fails! MapID: " << rMapInfo.wMapID;
        return NULL;
    }
    if(!rMapInfo.IsDungeon())
        _mapID2Map[rMapInfo.wMapID].push_back(pMap);
    return pMap;
}

void CMapMgr::DestroyMap(const CGameMapPtr& pMap)
{
    assert(pMap != NULL);
    _mapID2Map.erase(pMap->GetMapID());
}

SMapInfoPtr CMapMgr::GetMapInfo(UINT16 wMapID)
{
    auto it = _mapID2MapInfo.find(wMapID);
    if(it != _mapID2MapInfo.end())
        return it->second;
    return NULL;
}

CGameMapPtr CMapMgr::GetMap(UINT16 wMapID,UINT8 byIndex)
{
    auto it = _mapID2Map.find(wMapID);
    if(it == _mapID2Map.end())
        return NULL;
    SMapInfoPtr pInfo = GetMapInfo(wMapID);
    if(NULL == pInfo)
    {
        return NULL;
    }
    if(eMapNormal == pInfo->eMapType)
    {

        if(byIndex == 255)
        {
            for(auto iter = it->second.begin();iter != it->second.end();iter++)
            {
                if((*iter)->IsWarning())
                {
                    continue;
                }
                return (*iter);
            }
            CGameMapPtr pMap = CreateMap(wMapID);
            if(pMap != NULL)
            {
                NoticeNewMap(wMapID);
            }
            return pMap;
        }
        else
        {
            for(size_t sz = 0;sz != it->second.size();sz++)
            {
                if(byIndex == sz)
                {
                    return it->second[sz];
                }

            }

        }
    }
    else
    {
        if(it->second.empty())
        {
            return NULL;
        }
        return it->second[0];
    }
    return NULL;
}

void CMapMgr::TestMap()
{
    class CPointTester
    {
        public:
            bool Finish(INT32 dwX, INT32 dwZ)
            {
                _vecCoord.push_back(SCoord(dwX, dwZ));
                return false;
            }

            bool Visit(CBaseObj& rObj) { return false; }

            void Dump()
            {
                LOG_DBG << "Point: ";
                for(size_t i = 0; i < _vecCoord.size(); ++i)
                    LOG_ADD << "[X:" << _vecCoord[i].dwX << ",Y:" << _vecCoord[i].dwY << "]";
            }

        private:
            vector<SCoord> _vecCoord;
    };

    auto it = CUserMgr::GetBornInfo().mapCamp2Info.begin();
    if(it == CUserMgr::GetBornInfo().mapCamp2Info.end())
        return;
    SBornCampInfo& rBornCampInfo = it->second;
    UINT16 wMapID = rBornCampInfo.wMapID;
    SPoint& rPoint = rBornCampInfo.oPoint;
    CGameMapPtr pMap = GetMap(wMapID);
    if(pMap != NULL)
    {
        CPointTester oTester;
        pMap->VisitRoundArea(rPoint, 5.f, oTester);
        oTester.Dump();
    }
}

IBattleFighterPtr CMapMgr::ToBattleFighterWithFighterMapID(UINT16 wMapID)
{
    SMapInfoPtr pMapInfo = GetMapInfo(wMapID);
    if (!pMapInfo)
        return NULL;
    IBattleFighterPtr pBattleFighter = CreateBattleFighter();
    if (!pBattleFighter)
        return NULL;

    // 把Fighter转换成BattleFighter
    SBFInfo sBFInfo;

    const UINT64 MAGIC = 9527;
    sBFInfo.qwInstID    = MAGIC;
    sBFInfo.wFighterID  = pMapInfo->wMapID;              //将类型ID
    sBFInfo.strName     = pMapInfo->GetName();           //姓名
    sBFInfo.dwPos        = IBattleFighter::GetScenePos();                     //阵型中的位置

    SFieldFeaturePtr pFieldFeature (new SFieldFeature);
    if (pFieldFeature)
        pFieldFeature->wSceneID = pMapInfo->wMapID;

    sBFInfo.pFeature = dynamic_pointer_cast<SFeatureBase>(pFieldFeature);

    if (!pBattleFighter->InitFighter(sBFInfo))
        return NULL;

    TVecFloat vecFighterAttr;
    pBattleFighter->InitFighterAttr(vecFighterAttr);

    TVecUINT32 vecAllSkill;
    for (auto & rID : pMapInfo->vecSkillID)
    {
        vecAllSkill.push_back(SkillMgr.GetSkillIDQualityLevel(rID));
    }

    pBattleFighter->InitFighterSkills(vecAllSkill, 0);

    return pBattleFighter;
}

IBattleFighterPtr CMapMgr::ToBattleFighter(UINT16 wMapID) 
{
    SMapInfoPtr pMapInfo = GetMapInfo(wMapID);
    if(!pMapInfo)
        return NULL;
    if (!pMapInfo->GetFighterMapID())
        return NULL;
    pMapInfo = GetMapInfo(pMapInfo->GetFighterMapID());
    if (!pMapInfo)
        return NULL;
    IBattleFighterPtr pBattleFighter = CreateBattleFighter();
    if (!pBattleFighter)
        return NULL;

    // 把Fighter转换成BattleFighter
    SBFInfo sBFInfo;

    const UINT64 MAGIC = 9527;
    sBFInfo.qwInstID    = MAGIC;
    sBFInfo.wFighterID  = pMapInfo->wMapID;              //将类型ID
    sBFInfo.strName     = pMapInfo->GetName();           //姓名
    sBFInfo.dwPos       = IBattleFighter::GetScenePos();                     //阵型中的位置

    SFieldFeaturePtr pFieldFeature (new SFieldFeature);
    if (pFieldFeature)
        pFieldFeature->wSceneID = pMapInfo->wMapID;

    sBFInfo.pFeature = dynamic_pointer_cast<SFeatureBase>(pFieldFeature);

    if (!pBattleFighter->InitFighter(sBFInfo))
        return NULL;

    TVecFloat vecFighterAttr;
    pBattleFighter->InitFighterAttr(vecFighterAttr);

    TVecUINT32 vecAllSkill;
    for (auto & rID : pMapInfo->vecSkillID)
    {
        vecAllSkill.push_back(SkillMgr.GetSkillIDQualityLevel(rID));
    }

    pBattleFighter->InitFighterSkills(vecAllSkill, 0);

    return pBattleFighter;
}

bool CMapMgr::AnalysisString2VectorUINT32(const string& strValue, TVecUINT32& vecData, const string& strSep)
{
    vecData.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
        vecData.push_back(::atoi(tk[i].c_str()));
    return true;
}

UINT8 CMapMgr::GetMapIndex(const CGameMapPtr& pMap)
{
    auto it = _mapID2Map.find(pMap->GetMapID());
    if( it == _mapID2Map.end())
        return 255;
    for(auto iter = 0;it->second.size();iter++)
    {
        if(it->second[iter] == pMap)
        {
            return iter;
        }

    }
    return 255;
}
void CMapMgr::GetMapLoad(UINT16 wMapId,TVecMapOverLoad &rVec)
{
    auto it = _mapID2Map.find(wMapId);
    if( it == _mapID2Map.end())
        return ;
    vector<CGameMapPtr> &rMapVec = it->second;
    for(size_t sz = 0;sz != rMapVec.size();sz++)
    {
        MapOverLoad sLoad;
        sLoad.byIndex = sz;
        if(rMapVec[sz]->IsFull())
        {
            sLoad.eLoadState = eMapFull;
        }
        else if(rMapVec[sz]->IsWarning())
        {
            sLoad.eLoadState =  eMapBusy;
        }
        else
        {
            sLoad.eLoadState = eMapFree;
        }
        rVec.push_back(sLoad);
    }
}

UINT8 CMapMgr::GetMapSize(UINT16 wMapId)
{
    auto it = _mapID2Map.find(wMapId);
    if( it == _mapID2Map.end())
        return 0;
    return it->second.size();

}

void CMapMgr::NoticeNewMap(UINT16 wMapId)
{
    TVecMapOverLoad rVec;
    GetMapLoad(wMapId,rVec);
    if(rVec.empty())
    {
        return ;
    }
    string strMsg = g_MapProtS.BuildPkg_NoticeNewMap(rVec);
    NoticeMapMsg(wMapId,strMsg);
}

void CMapMgr::NoticeMapMsg(UINT16 wMapId,const string & strMsg)
{
    auto it = _mapID2Map.find(wMapId);
    if( it == _mapID2Map.end())
        return ;
    vector<CGameMapPtr> &rMapVec = it->second;
    for(size_t sz = 0;sz != rMapVec.size();sz++)
    {
        rMapVec[sz]->NotifyAllMapPlayer(strMsg);
    }
}

void CMapMgr::GetAllMapInstByMapID(UINT16 wMapID,vector<CGameMapPtr>& vecMapInst)
{
   auto it = _mapID2Map.find(wMapID);
   if(it == _mapID2Map.end())
       return;
   vecMapInst = it->second;
}
