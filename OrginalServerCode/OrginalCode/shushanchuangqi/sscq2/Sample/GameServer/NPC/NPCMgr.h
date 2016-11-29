#pragma once
#include "NPC.h"
#include "Singleton.h"
#include "Version.h"

class CNpcMgr : public StaticSingleton<CNpcMgr>,public CVersion
{
public:
	static bool Init();
	static void Destroy();
	static CNpcPtr CreateNpc(UINT16 wNpcID,UINT8 byIndex );
	static void DestroyNpc(CNpc& rNpc);
	static CNpcPtr GetNpc(UINT64 qwCreatureID);
    static CNpc * GetpNpc(UINT64 qwCreatureID){return GetNpc(qwCreatureID).get();}
	static SNpcPropCFG* GetNpcCFG(UINT16 wNpcID);

    static bool ReloadConfig(bool bReload  = false );
    static UINT64 GetVersion() { return _qwVersion; }
private:
//   static bool LoadNpcScript(const string& strScript, bool bReload = false);
	static map<UINT64, CNpcPtr> _mapID2Npc;
	static map<UINT16, SNpcPropCFG> _mapID2NpcCfg;
    static UINT64 _qwVersion;
};
