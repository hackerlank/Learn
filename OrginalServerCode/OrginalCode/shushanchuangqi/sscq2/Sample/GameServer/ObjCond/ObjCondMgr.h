#pragma once
#include "ObjCond.h"
#include "BarrierCFG.h"

enum
{
	 MAX_CUSTOM_COND_ID = 0x7fff,
    //	 COND_ID_ALL_MONSTER_KILLED,
};

class CObjCondMgr
{
public:
	static bool Init();
	static void Destroy();
	static SObjCondPtr GetCondition(UINT16 wCondID);

private:
	static std::map<UINT16, SObjCondPtr> _mapCondition;
};
