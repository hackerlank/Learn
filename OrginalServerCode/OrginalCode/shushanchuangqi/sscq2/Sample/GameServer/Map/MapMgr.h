#pragma once
#include "Map.h"
#include "Singleton.h"

#include "Battle.h"

class CMapMgr : public StaticSingleton<CMapMgr>
{
public:
	static bool Init();
	static bool ReloadAllMap();
	static bool Destroy();
	static bool LoadMapInfo();
	static bool IsDgnMap(UINT16 wMapID); //是否为副本
    static bool IsGuildBattleMap(UINT16 wMapID); // 是否为帮派战地图
	static CGameMapPtr CreateMap(UINT16 wMapID);
	static void DestroyMap(const CGameMapPtr& pMap);
	static SMapInfoPtr GetMapInfo(UINT16 wMapID);
	static CGameMapPtr GetMap(UINT16 wMapID,UINT8 byIndex = 255);
    static CGameMap * GetpMap(UINT16 wMapID,UINT8 byIndex = 255)
    {
        return GetMap(wMapID,byIndex).get();
    }
    static UINT8  GetMapIndex(const CGameMapPtr& pMap);

	static void SetCurOnlineUserCount(UINT32 dwCount) { _dwCurOnlineUserCount = dwCount; }
	static UINT32 GetCurOnlineUserCount() { return _dwCurOnlineUserCount; }

    static IBattleFighterPtr ToBattleFighterWithFighterMapID(UINT16 wMapID);
    static IBattleFighterPtr ToBattleFighter(UINT16 wMapID);

   static void GetMapLoad(UINT16 wMapId,TVecMapOverLoad &rVec);
   static UINT8 GetMapSize(UINT16 wMapId);
   static void NoticeMapMsg(UINT16 wMapId,const string & strMsg);
   static void GetAllMapInstByMapID(UINT16 wMapID,vector<CGameMapPtr>& vecMapInst);
private:
    static void NoticeNewMap(UINT16 wMapId);
	static bool CreateAllMap();
	static CGameMapPtr CreateMap(SMapInfo& rMapInfo);
	static void RefreshAllMap();
	static void TestMap();
    static bool AnalysisString2VectorUINT32(const string& strValue, TVecUINT32& vecData, const string& strSep);

	static map<UINT16, SMapInfoPtr> _mapID2MapInfo;
	static map<UINT16, vector<CGameMapPtr>> _mapID2Map;

	static UINT32 _dwCurOnlineUserCount;
};
