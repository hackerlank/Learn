
#ifndef SHENGLINGMGR_H_
#define SHENGLINGMGR_H_

#include "User.h"
#include "Singleton.h"
#include "RichCFG.h"
#include "RichCellCFG.h"
#include "Singleton.h"
#include "Random.h"
#include "ShengLing.h"

struct SShengLingLevel : public SRichCFG
{
    UINT8 byLevel;
    TVecUINT16 vecCommonMonster;
    TVecUINT16 vecEliteMonster;
    TVecUINT16 vecBossMonster;
    TVecItemGenInfo vecPintuPrize;
    TVecItemGenInfo vecDropGroup1;
    TVecItemGenInfo vecDropGroup2;
    TVecItemGenInfo vecDropGroup3;
    TVecItemGenInfo vecDropGroup4;
    TVecUINT16 vecLootID;
    SShengLingLevel()
    {
        byLevel = 0;
    }

    void CopyFrom(const SRichCFG &rConfig)
    {
        *(SRichCFG*)this = rConfig;
    }
};

typedef shared_ptr<SShengLingLevel> ShengLingLevelPtr;
typedef std::map<UINT8,ShengLingLevelPtr> TMapID2LevelConfig;

struct SShengLingGridProp : public SRichCellCFG
{
    void FromCopy(const SRichCellCFG &rInfo)
    {
        *(SRichCellCFG*)this = rInfo;
    }
};

typedef shared_ptr<SShengLingGridProp> ShengLingGridPropPtr;
typedef std::map<UINT8,ShengLingGridPropPtr> TMapID2GridProp;

class CShengLingMgr : public Singleton<CShengLingMgr>
{
public:
    CShengLingMgr() { };
    virtual ~CShengLingMgr() { };
    bool Init();
    bool LoadConfig();
    bool LoadShengLingLevelConfig();
    bool LoadShengLingPropConfig();
    EGridType RandomGrid(UINT8 byIndex,bool bExceptMonster,bool bAll = true);
    EGridType GetRandom(bool bAll = true);
    ShengLingGridPropPtr GetGridProp(UINT8 byIndex);
    ShengLingLevelPtr GetLevelConfig(UINT8 byLevel);
    bool GetNoteID(UINT8 byLevel,EGridType eGridType,UINT16& value);
    bool InitRandomPool();
    UINT16 GetBigChest(UINT8 byLevel);
    void GetBossMonster(UINT8 byLevel,UINT16& wBoss1,UINT16& wBoss2);
    TVecUINT8* GetRandVec(UINT8 byIndex,bool bAll,bool bExceptMonster);
private:
    void ParseString(string &str, TVecUINT16 &container);
    void ParseString(string &str, TVecItemGenInfo &vecItem);
private:
    TMapID2LevelConfig _mapID2LevelConfig;
    TMapID2GridProp _mapID2GridProp;
    
    //随机池子,不包括boss怪物和大宝箱的随机
    std::map<UINT8,TVecUINT8> _mapID2VecAll;
    std::map<UINT8,TVecUINT8> _mapID2VecExceptRandom;
    std::map<UINT8,TVecUINT8> _mapID2VecExceptRandomAndMonster;
};

#define g_ShengLingMgr CShengLingMgr::Instance() 
#endif // CoinMGR_H_
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

