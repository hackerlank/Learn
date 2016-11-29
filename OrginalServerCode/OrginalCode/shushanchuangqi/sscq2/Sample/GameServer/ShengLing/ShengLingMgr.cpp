#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "Parameter.h"
#include "Loot.h"
#include "Player.h"
#include "Tokenizer.h"
#include "ShengLingMgr.h"

#define SETPOOLBYINDEX(Pool,num,id)  \
    for(size_t i=0; i<num; ++i) \
        Pool.push_back(id);
 
const static UINT16 POOLMAX = 10000;
///////////////////////////////
bool CShengLingMgr::Init()
{
    if(!LoadConfig())
    {
        LOG_CRI<<"ShengLing LoadConfig err.";
        return false;
    }
    if(!InitRandomPool())
    {
        LOG_CRI<<"Init RandomPool Err.";
        return false;
    }
    return true;
}

bool CShengLingMgr::LoadConfig()
{
    if(!LoadShengLingLevelConfig())
    {
        LOG_CRI<<"LoadShengLingLevelConfig err.";
        return false;
    }
    if(!LoadShengLingPropConfig())
    {
        LOG_CRI<<"LoadShengLingPropConfig err.";
        return false;
    }
    return true;
}

bool CShengLingMgr::LoadShengLingLevelConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/Rich.xml";
    CRichLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oRichLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
    {
        SRichCFG* pCFG = oLoader._vecData[i];
        if(pCFG)
        {
            ShengLingLevelPtr pLevel(new SShengLingLevel);
            pLevel->CopyFrom(*pCFG);
            pLevel->byLevel = pCFG->_ID;
            ParseString(pCFG->_NormalDropGroup,pLevel->vecCommonMonster);
            ParseString(pCFG->_EliteDropGroup,pLevel->vecEliteMonster);
            ParseString(pCFG->_BossDropGroup,pLevel->vecBossMonster);
            ParseString(pCFG->_PicDropGroup,pLevel->vecPintuPrize);
            ParseString(pCFG->_ChrushDropGroup1,pLevel->vecDropGroup1);
            ParseString(pCFG->_ChrushDropGroup2,pLevel->vecDropGroup2);
            ParseString(pCFG->_ChrushDropGroup3,pLevel->vecDropGroup3);
            ParseString(pCFG->_ChrushDropGroup4,pLevel->vecDropGroup4);
            ParseString(pCFG->_DrawDropGroup,pLevel->vecLootID);

            _mapID2LevelConfig.insert(make_pair(pLevel->byLevel,pLevel));
        }
    }
    return true;
}

bool CShengLingMgr::LoadShengLingPropConfig()
{
    string strPath = Config._strConfigDir + "Conf/Table/RichCell.xml";
    CRichCellLoader oLoader;
    if(!oLoader.LoadData(strPath))
    {
        LOG_CRI << "oRichCellLoader.LoadData fails! Path: " << strPath;
        return false;
    }

    for(size_t i  = 0; i < oLoader._vecData.size(); ++i)
    {
        SRichCellCFG* pCFG = oLoader._vecData[i];
        if(pCFG)
        {
            ShengLingGridPropPtr pGrid(new SShengLingGridProp);
            pGrid->FromCopy(*pCFG);
            _mapID2GridProp.insert(make_pair(pGrid->_ID,pGrid));
        }
    }
    return true;
}

void CShengLingMgr::ParseString(string &str,TVecUINT16 &vecID)
{
    Tokenizer tk(str,"|");
    if(tk.size() == 0)
    {
        LOG_CRI << "ShengLing Config Err.";
        return;
    }
    for(size_t i=0; i<tk.size(); ++i)
    {
        UINT16 wID = atoi(tk[i].c_str());
        vecID.push_back(wID);
    }
}

void CShengLingMgr::ParseString(string &str,TVecItemGenInfo &vecItem)
{
    Tokenizer tk(str,"|");
    if(tk.size() == 0)
    {
        LOG_CRI << "ShengLing Config Err.";
        return;
    }
    for(size_t i=0; i<tk.size(); ++i)
    {
        Tokenizer tkItem(tk[i],";");
        
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.wItemID = atoi(tkItem[0].c_str());
        oItemGenInfo.dwCount = atoi(tkItem[1].c_str());;
        oItemGenInfo.eBindType = eBindGet;
        vecItem.push_back(oItemGenInfo);
    }
}
ShengLingLevelPtr CShengLingMgr::GetLevelConfig(UINT8 byLevel)
{
    auto it = _mapID2LevelConfig.find(byLevel);
    if(it != _mapID2LevelConfig.end())
        return it->second;
    return NULL;
}

ShengLingGridPropPtr CShengLingMgr::GetGridProp(UINT8 byIndex)
{
    auto it = _mapID2GridProp.find(byIndex);
    if(it != _mapID2GridProp.end())
        return it->second;
    return NULL;
}
TVecUINT8* CShengLingMgr::GetRandVec(UINT8 byIndex,bool bAll,bool bExceptMonster)
{
    if(bExceptMonster)
    {
        auto it = _mapID2VecExceptRandomAndMonster.find(byIndex);
        if(it != _mapID2VecExceptRandomAndMonster.end())
            return &it->second;
        return NULL;
    }
    if(bAll)
    {
        auto it = _mapID2VecAll.find(byIndex);
        if(it != _mapID2VecAll.end())
            return &it->second;
    }
    else
    {
        auto it = _mapID2VecExceptRandom.find(byIndex);
        if(it != _mapID2VecExceptRandom.end());
            return &it->second;
    }
    return NULL;
}

UINT16 CShengLingMgr::GetBigChest(UINT8 byLevel)
{
    ShengLingLevelPtr pLevel = GetLevelConfig(byLevel);
    if(!pLevel)
        return 0;
    return pLevel->_SuperBoxDropGroup;
}

void CShengLingMgr::GetBossMonster(UINT8 byLevel,UINT16& wBoss1,UINT16& wBoss2)
{
    ShengLingLevelPtr pLevel = GetLevelConfig(byLevel);
    if(!pLevel || pLevel->vecBossMonster.size() == 0)
    {
        LOG_INF <<"pLevel null or vecBossMonster.size() = 0";
        return;
    }
    
    wBoss1 = CRandom::RandVecElem(pLevel->vecBossMonster);
    wBoss2 = CRandom::RandVecElem(pLevel->vecBossMonster);
}

EGridType CShengLingMgr::GetRandom(bool bAll /* = true */)
{
    EGridType arrRand[] = 
    {
        EGridType_Elite,
        EGridType_Elite,
        EGridType_Boss,
        //随机空格和精英怪 3:7
        EGridType_Mid,
        EGridType_Mid,
        EGridType_Mid,
        EGridType_Elite,
        EGridType_Elite,
        EGridType_Elite,
        EGridType_Elite,
        EGridType_Elite,
        EGridType_Elite,
        EGridType_Elite
    };
    UINT32 dwIndex;
    if(bAll)
        dwIndex = CRandom::RandInt(0,2);
    else
        dwIndex = CRandom::RandInt(3,12);
    return arrRand[dwIndex];
}

bool CShengLingMgr::GetNoteID(UINT8 byLevel,EGridType eGridType,UINT16& value)
{
    ShengLingLevelPtr pLevel = GetLevelConfig(byLevel);
    if(!pLevel)
        return false;
    switch(eGridType)
    {
        case EGridType_Small:
            value = pLevel->_SmallBoxDropGroup;
            break;
        case EGridType_Mid:
            value = pLevel->_BigBoxDropGroup;
            break;
        case EGridType_Big:
            value = pLevel->_SuperBoxDropGroup;
            break;
        case EGridType_Normal:
            value = CRandom::RandVecElem(pLevel->vecCommonMonster);
            break;
        case EGridType_Elite:
            value = CRandom::RandVecElem(pLevel->vecEliteMonster);
            break;
        case EGridType_Boss:
            value = CRandom::RandVecElem(pLevel->vecBossMonster);
            break;
        case EGridType_Zadan:
            value = CRandom::RandVecElem(pLevel->vecLootID);
            break;
        case EGridType_Empty:
        default:
            value = 0;
            break;
    }
    return true;
}

EGridType CShengLingMgr::RandomGrid(UINT8 byIndex,bool bExceptMonster,bool bAll)
{
    TVecUINT8 *pvecPool = NULL;
    pvecPool = GetRandVec(byIndex,bAll,bExceptMonster);
    if(!pvecPool || pvecPool->size() == 0)
    {
        LOG_INF <<"vecRandom size 0";
        return EGridType_None;
    }
    UINT8 byRandomID = CRandom::RandVecElem(*pvecPool);
    return static_cast<EGridType>(byRandomID);
}

bool CShengLingMgr::InitRandomPool()
{
    if(_mapID2GridProp.size() == 0)
        return false;
    for(auto it : _mapID2GridProp)
    {
        ShengLingGridPropPtr pGridProp = it.second;
        if(!pGridProp)
            return false;
        TVecUINT8 vecPool;        

        SETPOOLBYINDEX(vecPool,pGridProp->_SmallBoxWeight,(UINT8)EGridType_Small);
        SETPOOLBYINDEX(vecPool,pGridProp->_BigBoxWeight,(UINT8)EGridType_Mid);
        SETPOOLBYINDEX(vecPool,pGridProp->_ChrushWeight,(UINT8)EGridType_Motu);
        SETPOOLBYINDEX(vecPool,pGridProp->_PicWeight,(UINT8)EGridType_Pintu);
        SETPOOLBYINDEX(vecPool,pGridProp->_DrawWeight,(UINT8)EGridType_Zadan);
        SETPOOLBYINDEX(vecPool,pGridProp->_EmptyCellWeight,(UINT8)EGridType_Empty);

        if(!_mapID2VecExceptRandomAndMonster.insert(make_pair(pGridProp->_ID,vecPool)).second)
        {
            LOG_INF<<"_mapID2VecExceptRandomAndMonster insert Err.Index=" <<it.first<<".";
            return false;
        }
        //去掉空格
        for(size_t i=0; i<pGridProp->_EmptyCellWeight; ++i)
            vecPool.pop_back();
        SETPOOLBYINDEX(vecPool,pGridProp->_NormalWeight,(UINT8)EGridType_Normal);
        SETPOOLBYINDEX(vecPool,pGridProp->_EliteWeight,(UINT8)EGridType_Elite);
    
        if(!_mapID2VecExceptRandom.insert(make_pair(pGridProp->_ID,vecPool)).second)
        {
            LOG_INF<<"_mapID2VecExceptRandom insert Err.Index=" << it.first<<".";
            return false;
        }
        //再加上 
        SETPOOLBYINDEX(vecPool,pGridProp->_EmptyCellWeight,(UINT8)EGridType_Empty);
        SETPOOLBYINDEX(vecPool,pGridProp->_RandomWeight,(UINT8)EGridType_Random);

        if(!_mapID2VecAll.insert(make_pair(pGridProp->_ID,vecPool)).second)
        {
            LOG_INF<<"_mapID2VecAll insert Err.Index=" << it.first<<".";
            return false;
        }
    }
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

