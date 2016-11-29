#pragma once
class CBlocker;
 #include "ResistCFG.h"
class CBlockerMgr
{
public:
	static bool Init();
	static void Destroy();
	static UINT32 GetNewInstID();
	static void TimerCheck();
	static CBlockerPtr CreateBlocker(UINT32 dwBlockerID);
	static void DestroyBlocker(CBlocker& rBlocker);
    static const SResistCFG* GetConfig(UINT32 dwID);
private:
	static std::map<UINT32, CBlockerPtr> _mapID2Blocker;
	static UINT32 _dwNextInstID;
    static std::map<UINT32,SResistCFG> _mapConfig;
};
