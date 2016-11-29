
#ifndef EXPMGR_H_
#define EXPMGR_H_

#include "ExpCFG.h"
#include "CommonDef.h" // XXX: for LEVEL_MAX

typedef shared_ptr<SExpCFG> SExpCFGPtr;
typedef std::vector<SExpCFGPtr> TVecExpCFGPtr;

class CExpMgr
{
public:
	CExpMgr();

    static bool Init();
    static bool LoadConfig(bool bReload = false);

    static UINT8 GetLevelMax() { return _byLevelMax; }
    static void SetMaxLevel(UINT8 byLevel);
	static bool TestLevelUp(UINT8& byLevel, UINT64& exp);
	static bool TestLevelDown(UINT8& byLevel, UINT64& exp);
	static void SetExp(UINT8 byLevel, UINT64 exp);
	static UINT64 GetLevelMin(UINT8 byLevel);
    static UINT8 Exp2Level(UINT64 exp);

    static SExpCFGPtr GetExpCfg(UINT8 byLevel);

    //世界boss奖励系数
    static float GetWBossFightRate(UINT8 byLevel);
    static float GetWBossPrizeRate(UINT8 byLevel);

    //获取基础打坐经验
    static UINT64 GetBaseSitExp(UINT8 byLevel);

private:
	static UINT64 _qwExps[LEVEL_MAX];
    static UINT8 _byLevelMax;
    static TVecExpCFGPtr _vecExpCFGPtr;
};

#endif // EXPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

