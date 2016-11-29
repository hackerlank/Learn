#include "stdafx.h"
#include "tinyxml.h"
#include "MapInfo.h"
#include "MapMgr.h"
#include "NPCMgr.h"
#include "MonsterMgr.h"
#include "SwitcherMgr.h"
#include "JumpSwitcher.h"
#include "ObjCondMgr.h"
#include "GatherMgr.h"
#include "BlockerMgr.h"
#include "Blocker.h" 
#include "MapAreaManager.h"
#include "MapArea.h"
#define MAX_RAND_POINT_COUNT 500

void FromBaseCoord(INT32 dwBaseX, INT32 dwBaseY, INT32& dwX, INT32& dwY)
{
    dwX = dwBaseX / GRID_RATIO_X;
    dwY = dwBaseY / GRID_RATIO_Y;
}

void ToBaseCoord(INT32 dwX, INT32 dwY, INT32& dwBaseX, INT32& dwBaseY)
{
    dwBaseX = dwX * GRID_RATIO_X + GRID_RATIO_X / 2;
    dwBaseY = dwY * GRID_RATIO_Y + GRID_RATIO_Y / 2;
}

void IntToFloatCoord(INT32 dwX, INT32 dwY, float& fX, float& fY)
{
    fX = float(dwX);
    fY = float(dwY);
}

void FloatToIntCoord(float fX, float fY, INT32& dwX, INT32& dwY)
{
    dwX = Round<INT32>(fX);
    dwY = Round<INT32>(fY);
}

void PointToCoord(const SPoint& rPoint, SCoord& rCoord, bool bBaseGrid /*= false*/)
{
    FloatToIntCoord(rPoint.fX, rPoint.fY, rCoord.dwX, rCoord.dwY);
    if(!bBaseGrid)
        FromBaseCoord(rCoord.dwX, rCoord.dwY, rCoord.dwX, rCoord.dwY);
}

void CoordToPoint(const SCoord& rCoord, SPoint& rPoint, bool bBaseGrid /*= false*/)
{
    INT32 dwX = rCoord.dwX, dwY = rCoord.dwY;
    if(!bBaseGrid)
        ToBaseCoord(dwX, dwY, dwX, dwY);
    IntToFloatCoord(dwX, dwY, rPoint.fX, rPoint.fY);
}

/////////////////////////////////////////////////////////////////////////////////////

const UINT8 TILE_BLOCK = 1;
const UINT8 TILE_NPC_BLOCK = 2;
const UINT8 TILE_TRANSLUCENT = 4;
const UINT8 TILE_SAFE1 = 8;
const UINT8 TILE_SAFE2 = 16;
const UINT8 TILE_CORNER = 32;
const UINT8 TILE_WALL = 64;		//墙

static bool IsBlockTile(UINT8 byValue)
{
    return (byValue & TILE_BLOCK) != 0;
}

static bool IsSafeTile(UINT8 byValue)
{
    return (byValue & TILE_SAFE1) != 0 || (byValue & TILE_SAFE2) != 0;
}

static bool IsCornerTile(UINT8 byValue)
{
    return (byValue & TILE_CORNER) != 0;
}

static bool IsWallTile(UINT8 byValue)
{
    return (byValue & TILE_WALL) != 0;
}

SMapInfo::~SMapInfo()
{
    FreeBuf();
}

int SMapInfo::GetMap(int x, int y) const
{
    if(IsBlock(x, y))
        return GRID_BLOCK_NUMBER;
    return 1;
}

bool SMapInfo::LoadConfig(const string& strFile)
{
    TiXmlDocument doc;
    if(!doc.LoadFile(strFile.c_str()))
    {
        LOG_CRI << "LoadFile fails! MapFile: " << strFile;
        return false;
    }
    TiXmlElement* pElemRoot = doc.RootElement();
    if(pElemRoot == NULL)
        return false;

    const char* pLength = pElemRoot->Attribute("TileWidth");
    if(pLength == NULL)
        return false;
    wLength = (UINT16)atoi(pLength);
    const char* pHeight = pElemRoot->Attribute("TileHeight");
    if(pHeight == NULL)
        return false;
    wHeight = (UINT16)atoi(pHeight);
    FreeBuf();
    if(!AllocBuf())
        return false;

    TiXmlElement* pElemFloor = pElemRoot->FirstChildElement("Floor");
    if(pElemFloor == NULL)
        return false;
    UINT32 dwCount = wLength * wHeight;
    const char* pBlockText = pElemFloor->GetText();
    if(pBlockText == NULL)
        return false;

    const char seps[] = ",";
    char *pToken = NULL, *pNextToken = NULL;
    UINT32 dwIndex = 0;
    pToken = strtok_s((char*)pBlockText, seps, &pNextToken);
    while(pToken != NULL)
    {
        UINT8 byBlock = (UINT8)atoi(pToken);
        UINT32 dwX = dwIndex % wLength;
        UINT32 dwY = dwIndex / wLength;
        ++dwIndex;
        ppBlock[dwX][dwY] = byBlock;
        if(dwX > 0 && dwY > 0)
        {
            UINT32 dwLLX = dwX - 1;
            UINT32 dwLLY = dwY - 1;
            UINT32 dwRLX = dwX;
            UINT32 dwRLY = dwY - 1;
            UINT32 dwLUX = dwX - 1;
            UINT32 dwLUY = dwY;
            if(!IsBlockTile(ppBlock[dwLLX][dwLLY]) && !IsBlockTile(ppBlock[dwLUX][dwLUY]))
            {
                if(!IsBlockTile(ppBlock[dwRLX][dwRLY]) && IsBlockTile(ppBlock[dwX][dwY]))
                    ppBlock[dwX][dwY] |= TILE_CORNER;
                else if(IsBlockTile(ppBlock[dwRLX][dwRLY]) && !IsBlockTile(ppBlock[dwX][dwY]))
                    ppBlock[dwRLX][dwRLY] |= TILE_CORNER;
            }
            if(!IsBlockTile(ppBlock[dwRLX][dwRLY]) && !IsBlockTile(ppBlock[dwX][dwY]))
            {
                if(!IsBlockTile(ppBlock[dwLLX][dwLLY]) && IsBlockTile(ppBlock[dwLUX][dwLUY]))
                    ppBlock[dwLUX][dwLUY] |= TILE_CORNER;
                else if(IsBlockTile(ppBlock[dwLLX][dwLLY]) && !IsBlockTile(ppBlock[dwLUX][dwLUY]))
                    ppBlock[dwLLX][dwLLY] |= TILE_CORNER;
            }
        }
        pToken = strtok_s(NULL, seps, &pNextToken);
    }
    if(dwIndex != dwCount)
    {
        LOG_CRI << "Map size error! dwIndex: " << dwIndex << ", dwCount" << dwCount;
        return false;
    }
    TiXmlElement* pElemBorn = pElemRoot->FirstChildElement("Bron");
    if(pElemBorn != NULL)
    {
        const char* pToMap = pElemBorn->Attribute("ToMap");
        if(pToMap == NULL)
            return false;
        oRealivePoint.wToMapID = (UINT16)atoi(pToMap);

        const char* pToX = pElemBorn->Attribute("ToX");
        if(pToX == NULL)
            return false;
        oRealivePoint.fToX = (float)atof(pToX);

        const char* pToY = pElemBorn->Attribute("ToY");
        if(pToY == NULL)
            return false;
        oRealivePoint.fToY = (float)atof(pToY);

        const char* pX = pElemBorn->Attribute("X");
        if(pX == NULL)
            return false;
        oRealivePoint.fX = (float)atof(pX);

        const char* pY = pElemBorn->Attribute("Y");
        if(pY == NULL)
            return false;
        oRealivePoint.fY = (float)atof(pY);

        TiXmlElement* pElemPoint = pElemBorn->FirstChildElement("Point");
        for(int i = 1; pElemPoint != NULL; ++i)
        {
            const char* pX = pElemPoint->Attribute("X");
            if(pX == NULL)
                return false;

            const char* pY = pElemPoint->Attribute("Y");
            if(pY == NULL)
                return false;

            if(i == 1)
            {
                oRealivePoint.fLX = (float)atof(pX);
                oRealivePoint.fLY = (float)atof(pY);
            }
            else if(i == 2)
            {
                oRealivePoint.fRX = (float)atof(pX);
                oRealivePoint.fRY = (float)atof(pY);
            }
            else
            {
                LOG_CRI << "More than two points found!";
                return false;
            }
            pElemPoint = pElemPoint->NextSiblingElement("Point");
        }
    }

    TiXmlElement* pElemTrans = pElemRoot->FirstChildElement("Trans");
    while(pElemTrans != NULL)
    {
        SJumpPoint oJumpPoint;
        const char* pToMap = pElemTrans->Attribute("ToMap");
        if(pToMap == NULL)
            return false;
        oJumpPoint.wToMapID = (UINT16)atoi(pToMap);
        const char* pID = pElemTrans->Attribute("Id");
        if(pID == NULL)
            return false;
        oJumpPoint.wID  = (UINT16)atoi(pID);
       const char* pbyIndex = pElemTrans->Attribute("Index");
        if(pbyIndex != NULL)
           oJumpPoint.byIndex  = (UINT16)atoi(pbyIndex);

        const char* pToX = pElemTrans->Attribute("ToX");
        if(pToX == NULL)
            return false;
        oJumpPoint.fToX = (float)atof(pToX);

        const char* pToY = pElemTrans->Attribute("ToY");
        if(pToY == NULL)
            return false;
        oJumpPoint.fToY = (float)atof(pToY);

        TiXmlElement* pElemPoint = pElemTrans->FirstChildElement("Point");
        for(int i = 1; pElemPoint != NULL; ++i)
        {
            const char* pX = pElemPoint->Attribute("X");
            if(pX == NULL)
                return false;

            const char* pY = pElemPoint->Attribute("Y");
            if(pY == NULL)
                return false;

            if(i == 1)
            {
                oJumpPoint.fLX = (float)atof(pX);
                oJumpPoint.fLY = (float)atof(pY);
            }
            else if(i == 2)
            {
                oJumpPoint.fRX = (float)atof(pX);
                oJumpPoint.fRY = (float)atof(pY);
            }
            else
            {
                LOG_CRI << "More than two points found!";
                return false;
            }
            pElemPoint = pElemPoint->NextSiblingElement("Point");
        }
        if(IsDungeon())
        {
            bool bVisual = true;
            const char* pVisual = pElemTrans->Attribute("Visual");
            if(pVisual != NULL)
                bVisual = atoi(pVisual) > 0;
            vecDgnJumpPoint.push_back(SDgnJumpPoint(oJumpPoint,bVisual));

        }
        else
        {
            vecJumpPoint.push_back(oJumpPoint);
        }
        pElemTrans = pElemTrans->NextSiblingElement("Trans");
    }

    TiXmlElement* pWarTrans = pElemRoot->FirstChildElement("WarEntry");
    while(pWarTrans != NULL)
    {
        SJumpPoint oJumpPoint;
        const char* pToMap = pWarTrans->Attribute("ToMap");
        if(pToMap == NULL)
            return false;
        oJumpPoint.wToMapID = (UINT16)atoi(pToMap);

        const char* pToX = pWarTrans->Attribute("ToX");
        if(pToX == NULL)
            return false;
        oJumpPoint.fToX = (float)atof(pToX);

        const char* pToY = pWarTrans->Attribute("ToY");
        if(pToY == NULL)
            return false;
        oJumpPoint.fToY = (float)atof(pToY);

        TiXmlElement* pElemPoint = pWarTrans->FirstChildElement("Point");
        for(int i = 1; pElemPoint != NULL; ++i)
        {
            const char* pX = pElemPoint->Attribute("X");
            if(pX == NULL)
                return false;

            const char* pY = pElemPoint->Attribute("Y");
            if(pY == NULL)
                return false;

            if(i == 1)
            {
                oJumpPoint.fLX = (float)atof(pX);
                oJumpPoint.fLY = (float)atof(pY);
            }
            else if(i == 2)
            {
                oJumpPoint.fRX = (float)atof(pX);
                oJumpPoint.fRY = (float)atof(pY);
            }
            else
            {
                LOG_CRI << "More than two points found!";
                return false;
            }
            pElemPoint = pElemPoint->NextSiblingElement("Point");
        }

        vecJumpPoint.push_back(oJumpPoint);
        pWarTrans = pWarTrans->NextSiblingElement("WarEntry");
    }

    TiXmlElement* pElemDgnTrans = pElemRoot->FirstChildElement("DungeonPort");
    while(pElemDgnTrans != NULL)
    {
        SDgnJumpPoint oJumpPoint;
        const char* pID = pElemDgnTrans->Attribute("Id");
        if(pID == NULL)
            return false;
        oJumpPoint.dwJumpID = (UINT32)atoi(pID);

        const char* pType = pElemDgnTrans->Attribute("Type");
        if(pType == NULL)
            return false;
        oJumpPoint.byType = (UINT8)atoi(pType);

        const char* pCond = pElemDgnTrans->Attribute("ConditionId");
        if(pCond == NULL)
            return false;
        oJumpPoint.wConditionID = (UINT16)atoi(pCond);

        const char* pToMap = pElemDgnTrans->Attribute("ToMap");
        if(pToMap == NULL)
            return false;
        oJumpPoint.wToMapID = (UINT16)atoi(pToMap);

        const char* pToX = pElemDgnTrans->Attribute("ToX");
        if(pToX == NULL)
            return false;
        oJumpPoint.fToX = (float)atof(pToX);

        const char* pToY = pElemDgnTrans->Attribute("ToY");
        if(pToY == NULL)
            return false;
        oJumpPoint.fToY = (float)atof(pToY);

        const char* pX = pElemDgnTrans->Attribute("X");
        if(pX == NULL)
            return false;
        oJumpPoint.fX = (float)atof(pX);

        const char* pY = pElemDgnTrans->Attribute("Y");
        if(pY == NULL)
            return false;
        oJumpPoint.fY = (float)atof(pY);

        TiXmlElement* pElemPoint = pElemDgnTrans->FirstChildElement("Point");
        for(int i = 1; pElemPoint != NULL; ++i)
        {
            pX = pElemPoint->Attribute("X");
            if(pX == NULL)
                return false;

            pY = pElemPoint->Attribute("Y");
            if(pY == NULL)
                return false;

            if(i == 1)
            {
                oJumpPoint.fLX = (float)atof(pX);
                oJumpPoint.fLY = (float)atof(pY);
            }
            else if(i == 2)
            {
                oJumpPoint.fRX = (float)atof(pX);
                oJumpPoint.fRY = (float)atof(pY);
            }
            else
            {
                LOG_CRI << "More than two points found!";
                return false;
            }
            pElemPoint = pElemPoint->NextSiblingElement("Point");
        }
        vecDgnJumpPoint.push_back(oJumpPoint);
        pElemDgnTrans = pElemDgnTrans->NextSiblingElement("DungeonPort");
    }
    //////
    TiXmlElement* pElemAreaPoint = pElemRoot->FirstChildElement("Area");
    while(pElemAreaPoint != NULL)
    {
        SAreaPoint oAreaPoint;
        const char* pIndex = pElemAreaPoint->Attribute("Index");
        if(pIndex == NULL)
            return false;
        oAreaPoint.wIndex = (UINT32)atoi(pIndex);
        const char* pId = pElemAreaPoint->Attribute("Id");
        if(pId == NULL)
            return false;
        oAreaPoint.wID = (UINT32)atoi(pId);
        const char* pOpen = pElemAreaPoint->Attribute("bIsOpen");
        if(pOpen == NULL)
            return false;
        oAreaPoint.bIsOpen = atoi(pOpen) > 0;
        const char* pX = pElemAreaPoint->Attribute("X");
        if(pX == NULL)
            return false;
        oAreaPoint.fX  = (float)atof(pX);
        const char* pY = pElemAreaPoint->Attribute("Y");
        if(pY == NULL)
            return false;
        oAreaPoint.fY  = (float)atof(pY);
        TiXmlElement* pElemPoint = pElemAreaPoint->FirstChildElement("Point");
        for(int i = 1; pElemPoint != NULL; ++i)
        {
            const char* pX = pElemPoint->Attribute("X");
            if(pX == NULL)
                return false;

            const char* pY = pElemPoint->Attribute("Y");
            if(pY == NULL)
                return false;

            if(i == 1)
            {
                oAreaPoint.fLX = (float)atof(pX);
                oAreaPoint.fLY = (float)atof(pY);
            }
            else if(i == 2)
            {
                oAreaPoint.fRX = (float)atof(pX);
                oAreaPoint.fRY = (float)atof(pY);
            }
            else
            {
                LOG_CRI << "More than two points found!";
                return false;
            }
            pElemPoint = pElemPoint->NextSiblingElement("Point");
        }
        vecAreaPoint.push_back(oAreaPoint);
        pElemAreaPoint = pElemAreaPoint->NextSiblingElement("Area");
    }
    /////
    TiXmlElement* pElemMonster = pElemRoot->FirstChildElement("Monster");
    while(pElemMonster != NULL)
    {
        /*
           const char* pID = pElemMonster->Attribute("Id");
           if(pID == NULL)
           return false;
           */
        const char* pX = pElemMonster->Attribute("X");
        if(pX == NULL)
            return false;

        const char* pY = pElemMonster->Attribute("Y");
        if(pY == NULL)
            return false;

        UINT8 byDirect = 0;
        const char* pDirect = pElemMonster->Attribute("Direct");
        if(pDirect != NULL)
            byDirect = (UINT8)atoi(pDirect);

        const char* pGroup = pElemMonster->Attribute("Group");
        if(pGroup == NULL)
            return false;
        /*
           const char* pRefreshTime = pElemMonster->Attribute("RefreshTime");
           if(pRefreshTime == NULL)
           return false;
           */
        UINT16 wWalkId  = 0;
        const char* pPath= pElemMonster->Attribute("WalkId");
        if(pPath != NULL)
        {
            wWalkId = (UINT16)atoi(pPath);
        }
        UINT16 wWalkType  = 0;
        const char* pPathType= pElemMonster->Attribute("WalkType");
        if(pPathType != NULL)
        {
            wWalkType = (UINT16)atoi(pPathType);
        }
        UINT16 wDropID = 0;
        const char* pDropId = pElemMonster->Attribute("DropId");
        if(pDropId != NULL)
            wDropID = (UINT16)atoi(pDropId);
        bool bVisual = true;
        const char* pVisual = pElemMonster->Attribute("Visual");
        if(pVisual)
            bVisual = (UINT16)atoi(pVisual) > 0;
        /*
           UINT8 byIndex = 0;
           const char* pIdx = pElemMonster->Attribute("No");
           if(pIdx != NULL)
           byIndex = (UINT8)atoi(pIdx);
           */
        SMonsterPoint oMonsterPoint;
        //       oMonsterPoint.wMonsterID = (UINT16)atoi(pID);
        oMonsterPoint.fX = (float)atof(pX);
        oMonsterPoint.fY = (float)atof(pY);
        oMonsterPoint.wPath = wWalkId;
        oMonsterPoint.bVisual = bVisual;
        oMonsterPoint.bHasPath = wWalkType > 0 ;
        if(byDirect >= 8)
            return false;
        oMonsterPoint.fDir = arDirect[byDirect];
        oMonsterPoint.wGroup = (UINT16)atoi(pGroup);
        /*
           if(eMapType == eMapSingleDgn || eMapType == eMapMultipleDgn)
           oMonsterPoint.dwRefreshTime = 0;
           else
           oMonsterPoint.dwRefreshTime = (UINT32)atoi(pRefreshTime);
           */
        oMonsterPoint.wDropID = wDropID;
        //oMonsterPoint.byIndex = byIndex;
        vecMstPoint.push_back(oMonsterPoint);
        pElemMonster = pElemMonster->NextSiblingElement("Monster");
    }

    TiXmlElement* pElemNpc = pElemRoot->FirstChildElement("Npc");
    while(pElemNpc != NULL)
    {
        const char* pID = pElemNpc->Attribute("Id");
        if(pID == NULL)
            return false;

        const char* pX = pElemNpc->Attribute("X");
        if(pX == NULL)
            return false;

        const char* pY = pElemNpc->Attribute("Y");
        if(pY == NULL)
            return false;

        const char* pDirect = pElemNpc->Attribute("Direct");
        if(pDirect == NULL)
            return false;
        bool  bVisual = true;
        const char* pVisual = pElemNpc->Attribute("Visual");
        if(pVisual != NULL)
            bVisual = atoi(pVisual) > 0 ;
        SNpcPoint oNpcPoint;
        oNpcPoint.wNpcID = (UINT16)atoi(pID);
        oNpcPoint.fX = (float)atof(pX);
        oNpcPoint.fY = (float)atof(pY);
        oNpcPoint.bVisual = bVisual;
        UINT8 byDirect = (UINT8)atoi(pDirect);
        if(byDirect >= 8)
            return false;
        const char* pIndex = pElemNpc->Attribute("Index");
        if(pIndex != NULL)
            oNpcPoint.byIndex = atoi(pIndex) ;
        oNpcPoint.fDir = arDirect[byDirect];
        vecNpcPoint.push_back(oNpcPoint);
        pElemNpc = pElemNpc->NextSiblingElement("Npc");
    }

    TiXmlElement* pElemGather = pElemRoot->FirstChildElement("Gather");
    while(pElemGather != NULL)
    {
        const char* pID = pElemGather->Attribute("Id");
        if(pID == NULL)
            return false;

        const char* pX = pElemGather->Attribute("X");
        if(pX == NULL)
            return false;

        const char* pY = pElemGather->Attribute("Y");
        if(pY == NULL)
            return false;
        bool bVisual = true;
        const char* pVisual = pElemGather->Attribute("Visual");
        if(pVisual != NULL)
            bVisual = atoi(pVisual) > 0;


        SGatherPoint oGatherPoint;
        oGatherPoint.wGatherID = (UINT16)atoi(pID);
        oGatherPoint.fX = (float)atof(pX);
        oGatherPoint.fY = (float)atof(pY);
        oGatherPoint.bVisual = bVisual;
        const char* pIndex = pElemGather->Attribute("Index");
        if(pIndex != NULL)
            oGatherPoint.byIndex = atoi(pIndex);

        vecGatherPoint.push_back(oGatherPoint);
        pElemGather = pElemGather->NextSiblingElement("Gather");
    }
    //宝箱
    TiXmlElement* pElemChest = pElemRoot->FirstChildElement("MaskFlag");
    while(pElemChest != NULL)
    {
        const char* pID = pElemChest->Attribute("Uid");
        if(pID == NULL)
            return false;

        const char* pX = pElemChest->Attribute("X");
        if(pX == NULL)
            return false;

        const char* pY = pElemChest->Attribute("Y");
        if(pY == NULL)
            return false;

        SChestPoint oGatherPoint;
        oGatherPoint.dwID = (UINT32)atoi(pID);
        oGatherPoint.fX = (float)atof(pX);
        oGatherPoint.fY = (float)atof(pY);
        vecChestPoint.push_back(oGatherPoint);
        pElemChest = pElemChest->NextSiblingElement("MaskFlag");
    }

    TiXmlElement* pElemBlocker = pElemRoot->FirstChildElement("Resist");
    while(pElemBlocker != NULL)
    {
        const char* pID = pElemBlocker->Attribute("Id");
        if(pID == NULL)
            return false;
        const char* pIndexID = pElemBlocker->Attribute("Index");
        if(pIndexID == NULL)
            return false;
        const char* pOpen = pElemBlocker->Attribute("bIsOpen");
        if(pOpen == NULL)
            return false;
        const char* pX = pElemBlocker->Attribute("X");
        if(pX == NULL)
            return false;

        const char* pY = pElemBlocker->Attribute("Y");
        if(pY == NULL)
            return false;
        /*
           const char* pCondID = pElemBlocker->Attribute("ConditionId");
           if(pCondID == NULL)
           return false;
           */
        SBlockerPoint sp;
        sp.dwID = (UINT32)atoi(pID);
        sp.fX = (float)atof(pX);
        sp.fY = (float)atof(pY);
        //sp.wCondID = (UINT16)atoi(pCondID);
        sp.wIndex = (UINT16)(atoi(pIndexID));
        sp.bIsOpen = atoi(pOpen) > 0;

        TiXmlElement* pElemPoint = pElemBlocker->FirstChildElement("Point");
        while(pElemPoint != NULL)
        {
            pX = pElemPoint->Attribute("X");
            if(pX == NULL)
                return false;

            pY = pElemPoint->Attribute("Y");
            if(pY == NULL)
                return false;

            sp.vecBlockerPt.emplace_back(SPoint((float)atof(pX), (float)atof(pY)));
            pElemPoint = pElemPoint->NextSiblingElement("Point");
        }

        vecBlockerPoint.push_back(sp);
        pElemBlocker = pElemBlocker->NextSiblingElement("Resist");
    }
    TiXmlElement* pElemPath = pElemRoot->FirstChildElement("Path");
    while(pElemPath != NULL)
    {
        const char* pID = pElemPath->Attribute("Id");
        if(pID == NULL)
            return false;
        SPath sPath;
        sPath.wID = atoi(pID);
        TiXmlElement* pElemPoint = pElemPath->FirstChildElement("Point");
        while(pElemPoint != NULL)
        {
            const char*   pX = pElemPoint->Attribute("X");
            if(pX == NULL)
                return false;

            const char*     pY = pElemPoint->Attribute("Y");
            if(pY == NULL)
                return false;
            sPath.vecPoint.emplace_back(SPoint((float)atof(pX), (float)atof(pY)));

            pElemPoint = pElemPoint->NextSiblingElement("Point");
        }
        if(sPath.vecPoint.size() < 2)
        {
            LOG_CRI<<"Path Need More Points :" << sPath.wID << "map id "<< wMapID ;
        }
        if(!_mapPath.insert(make_pair(sPath.wID,sPath)).second)
        {
            LOG_CRI<<"Path define rePeat :" << sPath.wID;
        }
        pElemPath = pElemPath->NextSiblingElement("Path");
    }
    return true;
}
const SPath * SMapInfo::GetPath(UINT16 wID)
{
    auto it = _mapPath.find(wID);
    if(it == _mapPath.end())
    {
        return NULL;
    }
    return &(it->second);
}
bool SMapInfo::AllocBuf()
{
    UINT32 dwCount = wLength * wHeight;
    ppBlock = new UINT8*[wLength];
    if(ppBlock == NULL)
        return false;
    UINT8* pBlock = new UINT8[dwCount];
    if(pBlock == NULL)
    {
        delete[] ppBlock;
        return false;
    }
    memset(pBlock, 0, dwCount);
    for(UINT16 i = 0; i < wLength; ++i)
        ppBlock[i] = &pBlock[i * wHeight];
    return true;
}

void SMapInfo::FreeBuf()
{
    if(ppBlock != NULL)
        delete[] ppBlock[0];
    delete[] ppBlock;
}

#define DEFAULT_BROADCAST_RADIUS_X 25.f
#define DEFAULT_BROADCAST_RADIUS_Y 20.f

#define WORLDBOSS_BROADCAST_RADIUS_X 45.f
#define WORLDBOSS_BROADCAST_RADIUS_Y 20.f

#define MINE_BATTLE_BROADCAST_RADIUS_X 30.f
#define MINE_BATTLE_BROADCAST_RADIUS_Y 25.f

void SMapInfo::InitBroadCastRadius()
{
    switch(eMapType)
    {
        case eMapWorldBoss:
            {
                SPoint oPoint(WORLDBOSS_BROADCAST_RADIUS_X, WORLDBOSS_BROADCAST_RADIUS_Y);
                PointToCoord(oPoint, oBroadCastRadius, false);
            }
            break;
        default:
            {
                SPoint oPoint(DEFAULT_BROADCAST_RADIUS_X, DEFAULT_BROADCAST_RADIUS_Y);
                PointToCoord(oPoint, oBroadCastRadius, false);
            }
            break;
    }
}

void SMapInfo::GenRandPoint(CGameMap& rMap)
{
    if(vecRandMovePoint.empty())
    {
        CPointPicker oPicker(rMap, 0, false);
        INT32 dwLength = GetLength() / 2;
        INT32 dwHeight = GetHeight() / 2;
        SCoord oRadius;
        FromBaseCoord(dwLength, dwHeight, oRadius.dwX, oRadius.dwY);
        rMap.VisitArea(SCoord(dwLength, dwHeight), oRadius, oPicker);
        TVecPoint& rVecPoint = oPicker.GetPointList();
        random_shuffle(rVecPoint.begin(), rVecPoint.end());
        if(rVecPoint.size() < MAX_RAND_POINT_COUNT)
            vecRandMovePoint = rVecPoint;
        else
            vecRandMovePoint.assign(rVecPoint.begin(), rVecPoint.begin() + MAX_RAND_POINT_COUNT);
    }
}

UINT64 SMapInfo::CreateMonster(const CGameMapPtr& pMap,UINT16 wGroup,float fX,float fY,const SPath *pPath,float fDir /*= 0*/)
{
    SPoint oBornPoint(fX, fY);
    if(pMap->IsBlockPoint(oBornPoint))
    {
        LOG_CRI << "MonsterID: " << wGroup << ", MapID: " << wMapID << ", Born Point is blocked: " << oBornPoint;
        SPoint oMovable;
        if(pMap->GetMovablePoint(oBornPoint, oMovable))
        {
            oBornPoint = oMovable;
            LOG_INF << "MonsterID: " << wGroup << " Choose New Point: " << oBornPoint;
        }
        else
        {
            LOG_CRI << "Can't find movable point for MonsterID: " << wGroup;
            return 0;;
        }
    }

    const SMonsterGroupCFGEx* pMstGroup = CMonsterMgr::GetMonsterGroup(wGroup);
    if(NULL == pMstGroup)
    {
        LOG_CRI << "Can't find Monster Group: " << wGroup << ", MapID: " << wMapID << ", MonsterID: " << wGroup;
        return 0;
    }
    else
    {
        CMonsterPtr pMonster = CMonsterMgr::CreateMonster(pMstGroup->_MainMonster,pMstGroup->_Name);
        if(pMonster != NULL)
        {

            pMonster->SetDir(fDir);
            pMonster->SetGroupID(wGroup);	
            pMonster->SetPath(pPath);
            //pMonster->SetMapIdx(byIndex);以后做小地图可能用
            pMap->MonsterEnter(*pMonster, &oBornPoint);
            return pMonster->GetCreatureID();
        }
        else
        {
            LOG_CRI << "Map ID: " << pMap->GetMapID() << " MonsterID: " << wGroup << " is NULL!";
            return 0;
        }
    }
    return 0;
}

bool SMapInfo::CreateGather(const CGameMapPtr& pMap,UINT16 wGather,UINT8 byIndex,float fX,float fY)
{
    IGatherPtr pGather = CGatherMgr::CreateGather(wGather,byIndex);
    if(pGather != NULL)
    {
        SPoint oPoint(fX, fY);
        pGather->SetPoint(oPoint);
        pMap->GatherAppear(*pGather);
    }
    else
    {
        LOG_CRI << "Map ID: " << pMap->GetMapID() << " GatherID: " << wGather << " is NULL!";
        return false;
    }
    return true;
}

bool SMapInfo::CreateSwitcher(const CGameMapPtr& pMap,const SDgnJumpPoint& rJumpPoint )
{
    CSwitcherPtr pSwitcher;
    if(rJumpPoint.byType == 0)
    {
        CJumpSwitcherPtr pJumpSwitcher = CSwitcherMgr::CreateJumpSwitcher(rJumpPoint);
        if(pJumpSwitcher != NULL)
        {
            pJumpSwitcher->InitJumpInfo(rJumpPoint);
            pSwitcher = pJumpSwitcher;
        }
        else
        {
            LOG_CRI << "Map ID: " << pMap->GetMapID() << " Switcher ID: " << rJumpPoint.dwJumpID << " create fails!";
            return false;
        }
    }
    else if(rJumpPoint.byType == 1)
    {
        CCampSwitcherPtr pCampSwitcher = CSwitcherMgr::CreateCampSwitcher(rJumpPoint);
        if(pCampSwitcher != NULL)
        {
            SRoundRegion& rRegion = pCampSwitcher->GetRegion();
            rRegion.SetRegion(rJumpPoint.fLX, rJumpPoint.fLY, rJumpPoint.fRX, rJumpPoint.fRY);
            pSwitcher = pCampSwitcher;
        }
        else
        {
            LOG_CRI << "Map ID: " << pMap->GetMapID() << " Switcher ID: " << rJumpPoint.dwJumpID << " create fails!";
            return false;
        }
    }

    if(pSwitcher != NULL)
    {
        pSwitcher->SetMap(pMap);
        pSwitcher->SetPoint(SPoint(rJumpPoint.fX, rJumpPoint.fY));
        pMap->SwitcherAppear(*pSwitcher);
        if(rJumpPoint.wConditionID != 0)
        {
            SObjCondPtr pCondition = CObjCondMgr::GetCondition(rJumpPoint.wConditionID);
            if(NULL == pCondition)
            {
                LOG_CRI << "can't find condition " << rJumpPoint.wConditionID;
                return false;
            }
            else
                pSwitcher->AddCondition(*pCondition);
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool SMapInfo::CreateNpc(const CGameMapPtr& pMap,const SNpcPoint& rNpcPoint)
{
    CNpcPtr pNpc = CNpcMgr::CreateNpc(rNpcPoint.wNpcID,rNpcPoint.byIndex);
    if(pNpc != NULL)
    {
        pNpc->SetMap(pMap);
        pNpc->SetPoint(SPoint(rNpcPoint.fX, rNpcPoint.fY));
        pNpc->SetDir(rNpcPoint.fDir);
        pMap->NpcAppear(*pNpc);
    }
    else
    {
        LOG_CRI << "Map ID: " << pMap->GetMapID() << " NpcID: " << rNpcPoint.wNpcID << " is NULL!";
        return false;
    }
    return true;
}
bool SMapInfo::CreateArea(const CGameMapPtr& pMap,const SAreaPoint& rAreaPt)
{
    CMapAreaPtr pArea = g_AreaManager.CreateArea(rAreaPt);
    if(pArea != NULL)
    {
        pArea->SetMap(pMap);
        pArea->SetPoint(SPoint(rAreaPt.fX,rAreaPt.fY));
        pMap->AreaAppear(*pArea);
    }
    else
    {
        LOG_CRI << "Map ID: " << pMap->GetMapID() << " Area ID: " << rAreaPt.wID << " is NULL!";
        return false;
    }
    return true;
}

bool SMapInfo::CreateBlock(const CGameMapPtr& pMap,const SBlockerPoint& rBlockerPt)
{
    CBlockerPtr pBlocker = CBlockerMgr::CreateBlocker(rBlockerPt.dwID);
    if(pBlocker != NULL)
    {
        pBlocker->SetMap(pMap);
        pBlocker->AssginBlockPt(rBlockerPt.wIndex,rBlockerPt.vecBlockerPt, *this);
        pBlocker->SetPoint(SPoint(rBlockerPt.fX, rBlockerPt.fY));
        pMap->BlockerAppear(*pBlocker);
        if(rBlockerPt.wCondID != 0)
        {
            SObjCondPtr pCondition = CObjCondMgr::GetCondition(rBlockerPt.wCondID);
            if(NULL == pCondition)
                LOG_CRI << "can't find condition " << rBlockerPt.wCondID;
            else
                pBlocker->AddCondition(*pCondition);
        }
    }
    else
    {
        LOG_CRI << "Map ID: " << pMap->GetMapID() << " Block ID: " << rBlockerPt.dwID << " is NULL!";
        return false;
    }
    return true;
}
bool SMapInfo::CreateJumpPoint(const CGameMapPtr& pMap,const SJumpPoint& rJumpPoint)
{
    SJumpRegionPtr pRegion(new SJumpRegion);
    if(pRegion == NULL)
        return false;
    pRegion->SetRegion(rJumpPoint.fLX, rJumpPoint.fLY, rJumpPoint.fRX, rJumpPoint.fRY);
    pRegion->wToMapID = rJumpPoint.wToMapID;
    pRegion->oToPoint.fX = rJumpPoint.fToX;
    pRegion->oToPoint.fY = rJumpPoint.fToY;
    pRegion->wID =  rJumpPoint.wID;
    pMap->AddRegion(eRegionJump, pRegion);
    return true;
}

bool SMapInfo::InitMap(const CGameMapPtr& pMap, bool bRefresh /*= false*/)
{
    if(!bRefresh)
    {
        //怪物
        for(size_t i = 0; i < vecMstPoint.size(); ++i)
        {
            SMonsterPoint& rMstPoint = vecMstPoint[i];
            const SMonsterGroupCFGEx* pMstGroup = CMonsterMgr::GetMonsterGroup(rMstPoint.wGroup);
            if(pMstGroup == NULL || !rMstPoint.bVisual)
            {
                continue;
            }
            const SPath *pPath = NULL;
            if(rMstPoint.bHasPath)
            {
                pPath = GetPath(rMstPoint.wPath);
            }
            CreateMonster(pMap,rMstPoint.wGroup,rMstPoint.fX, rMstPoint.fY,pPath,rMstPoint.fDir);
        }

        //NPC
        for(size_t i = 0; i < vecNpcPoint.size(); ++i)
        {
            const SNpcPoint& rNpcPoint = vecNpcPoint[i];
            if(rNpcPoint.bVisual)
                CreateNpc(pMap,rNpcPoint);
        }

        //获取地图上的随机点列表，随机点为可行走的，并且没有Monster, NPC, Jump, Block
        GenRandPoint(*pMap);

        //采集物、宝箱、巢穴
        for(size_t i = 0; i < vecGatherPoint.size(); ++i)
        {
            SGatherPoint& rGatherPoint = vecGatherPoint[i];
            if(rGatherPoint.bVisual)
                CreateGather(pMap,rGatherPoint.wGatherID,rGatherPoint.byIndex,rGatherPoint.fX,rGatherPoint.fY);
        }

        //副本跳转点
        for(size_t i = 0; i < vecDgnJumpPoint.size(); ++i)
        {
            const SDgnJumpPoint& rJumpPoint = vecDgnJumpPoint[i];
            if(rJumpPoint.bVisual)
                CreateSwitcher(pMap,rJumpPoint);
        }

        for(size_t i = 0; i < vecBlockerPoint.size(); ++i)
        {
            SBlockerPoint& rBlockerPt = vecBlockerPoint[i];
            if(rBlockerPt.bIsOpen)
            {
                CreateBlock(pMap,rBlockerPt);
            }
        }
        for(size_t i = 0; i < vecAreaPoint.size(); ++i)
        {
            SAreaPoint& rAreaPt = vecAreaPoint[i];
            if(!rAreaPt.bIsOpen)
            {
                continue;
            }
            CreateArea(pMap,rAreaPt);
        }
        if(bRefresh)
            pMap->ClearRegion(eRegionJump);
        for(size_t i = 0; i < vecJumpPoint.size(); ++i)
        {
            SJumpPoint& rJumpPoint = vecJumpPoint[i];
            CreateJumpPoint(pMap,rJumpPoint);
        }
    }
    if(bRefresh)
        pMap->ClearRegion(eRegionProbe);
    TVecProbeInfo* pVecProbe = CTaskConfMgr::Instance().GetProbeTask(wMapID);
    if(NULL != pVecProbe)
    {
        for(size_t i = 0; i < pVecProbe->size(); ++i)
        {
            SProbeInfo& rProbePoint = (*pVecProbe)[i];

            SProbeRegionPtr pRegion(new SProbeRegion(rProbePoint));
            if(pRegion != NULL)
                pMap->AddRegion(eRegionProbe, pRegion);
        }
    }

    if(bRefresh)
        pMap->ClearRegion(eRegionTaskTrigger);
    TVecProbeInfo* pVecTrigger = CTaskConfMgr::Instance().GetTriggerTask(wMapID);
    if(NULL != pVecTrigger)
    {
        for(size_t i = 0; i < pVecTrigger->size(); ++i)
        {
            SProbeInfo& rProbePoint = (*pVecTrigger)[i];

            SProbeRegionPtr pRegion(new SProbeRegion(rProbePoint));
            if(pRegion != NULL)
                pMap->AddRegion(eRegionTaskTrigger, pRegion);
        }
    }
    return true;
}

bool SMapInfo::IsBlock(INT32 dwX, INT32 dwY) const
{
    if(dwX < 0 || dwX >= wLength || dwY < 0 || dwY >= wHeight)
        return true;
    if(ppBlock == NULL)
        return false;
    return IsBlockTile(ppBlock[dwX][dwY]);
}

bool SMapInfo::IsBlock(const SCoord& rCoord) const
{
    return IsBlock(rCoord.dwX, rCoord.dwY);
}

bool SMapInfo::IsBlock(const SPoint& rPoint) const
{
    SCoord oCoord;
    PointToCoord(rPoint, oCoord, true);
    return IsBlock(oCoord);
}

bool SMapInfo::IsCorner(INT32 dwX, INT32 dwY) const
{
    if(dwX < 0 || dwX >= wLength || dwY < 0 || dwY >= wHeight)
        return false;
    if(ppBlock == NULL)
        return false;
    return IsCornerTile(ppBlock[dwX][dwY]);
}

bool SMapInfo::IsWall(INT32 dwX, INT32 dwY) const
{
    if(dwX < 0 || dwX >= wLength || dwY < 0 || dwY >= wHeight)
        return false;
    if(ppBlock == NULL)
        return false;
    return IsWallTile(ppBlock[dwX][dwY]);
}

bool SMapInfo::IsSafe(INT32 dwX, INT32 dwY) const
{
    if(dwX < 0 || dwX >= wLength || dwY < 0 || dwY >= wHeight)
        return false;
    if(ppBlock == NULL)
        return false;
    return IsSafeTile(ppBlock[dwX][dwY]);
}

bool SMapInfo::HasBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2, bool bLoose /*= false*/) const
{
    SCoord oCoord1, oCoord2;
    ToIntCoord(rPoint1, oCoord1, true);
    ToIntCoord(rPoint2, oCoord2, true);
    if(bLoose)
        return ::HasBlockPoint(oCoord1, oCoord2, [this](INT32 dwX, INT32 dwY)->bool{ return IsBlock(dwX, dwY); }, [this](INT32 dwX, INT32 dwY)->bool{ return IsWall(dwX, dwY); });
    else
        return ::HasBlockPoint(oCoord1, oCoord2, [this](INT32 dwX, INT32 dwY)->bool{ return IsBlock(dwX, dwY); });
}

INT32 SMapInfo::GetLength(bool bBaseGrid /*= false*/) const
{
    if(bBaseGrid)
        return wLength;
    else
        return (wLength + GRID_RATIO_X - 1) / GRID_RATIO_X;
}

INT32 SMapInfo::GetHeight(bool bBaseGrid /*= false*/) const
{
    if(bBaseGrid)
        return wHeight;
    else
        return (wHeight + GRID_RATIO_Y - 1) / GRID_RATIO_Y;
}

bool SMapInfo::ToIntCoord(const SPoint& rPoint, SCoord& rCoord, bool bBaseGrid /*= false*/) const
{
    PointToCoord(rPoint, rCoord, bBaseGrid);
    return IsInMapArea(rCoord, bBaseGrid);
}

bool SMapInfo::ToFloatCoord(const SCoord& rCoord, SPoint& rPoint, bool bBaseGrid /*= false*/) const
{
    CoordToPoint(rCoord, rPoint, bBaseGrid);
    return IsInMapArea(rCoord, bBaseGrid);
}

bool SMapInfo::IsInMapArea(const SCoord& rCoord, bool bBaseGrid /*= false*/) const
{
    INT32 dwX = rCoord.dwX;
    INT32 dwY = rCoord.dwY;
    if(!bBaseGrid)
    {
        dwX = dwX * GRID_RATIO_X + GRID_RATIO_X / 2;
        dwY = dwY * GRID_RATIO_Y + GRID_RATIO_Y / 2;
    }
    if(dwX < 0 || dwX >= wLength)
        return false;
    if(dwY < 0 || dwY >= wHeight)
        return false;
    return true;
}

bool SMapInfo::IsInMapArea(const SPoint& rPoint) const
{
    if(!rPoint.IsValid())
        return false;
    SCoord oCoord;
    PointToCoord(rPoint, oCoord, true);
    return IsInMapArea(oCoord, true);
}

bool SMapInfo::IsNormal() const
{
    return eMapType == eMapNormal;
}

bool SMapInfo::IsDungeon() const
{
    switch(eMapType)
    {
        case eMapNone:
            //LOG_CRI << "Invalid MapType! MapID: " << wMapID;
            break;
        case eMapSingleDgn:
        case eMapMultipleDgn:
        case eMapDemonTower:
        case eMapShushanBattle:
        case eMapGuildBattle:
            return true;
        default:
            return false;
    }
    return false;
}

bool SMapInfo::IsGuildBattle() const
{
    switch(eMapType)
    {
        case eMapNone:
            LOG_CRI << "Invalid MapType! MapID: " << wMapID;
            break;
        case eMapGuildBattle:
            return true;
        default:
            return false;
    }
    return false;
}

bool SMapInfo::IsShushanBattleMap() const
{
    switch(eMapType)
    {
        case eMapNone:
            LOG_CRI << "Invalid MapType! MapID: " << wMapID;
            break;
        case eMapShushanBattle:
            return true;
        default:
            return false;
    }
    return false;
}

SPoint SMapInfo::GetRealivePoint()
{
    return move(SPoint(oRealivePoint.fX, oRealivePoint.fY));
}

UINT16 SMapInfo::GetFighterMapID() const
{
    return wFighterMapID;
}

const string& SMapInfo::GetName() const
{
    return strName;
}

bool SMapInfo::IsWorldCity() const 
{
    return false;
}
