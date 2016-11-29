#pragma once
#include "AStar.h"
#include "Point.h"

#define BORN_MAP_ID 1
#define GRID_RATIO_X 3
#define GRID_RATIO_Y 3

enum EMapType
{
    eMapNone,
    eMapNormal        = 1,  //普通地图
    eMapSingleDgn     = 2,  //单人副本地图
    eMapMultipleDgn   = 3,	//多人副本地图
    eMapWorldBoss     = 4,  //世界BOSS地图
    eMapDemonTower    = 5,  //锁妖塔地图
    eMapShushanBattle = 6,  //蜀山论剑地图
    eMapGuildBattle   = 7,  //帮派战地图
    eMapLangHuanBless = 8,  //中午挂机活动地图
    eMapArenaGS       = 9,  //斗剑地图
    eMapTypeMax
};

enum EJumpPointType
{
    eJumpPointNormal = 0,
    eJumpPointNextMap = 1,
};



struct SJumpPoint
{
    UINT16 wToMapID;
    UINT16 wID;
    UINT8 byIndex;
    float fToX, fToY;
    float fLX, fLY, fRX, fRY;
    SJumpPoint() { memset(this, 0, sizeof*this); }
};

struct SAreaPoint//普通区域
{
    UINT16 wIndex;
    UINT16 wID;
    float fX;
    float fY;
    bool bIsOpen;
    float fLX, fLY, fRX, fRY;
    SAreaPoint()
    {
        wIndex = 0;
        wID = 0;
        bIsOpen = false;
        fLX = 0;
        fLY = 0;
        fRX = 0;
        fRY = 0;
        fX  = 0;
        fY  = 0;
    }
};
typedef vector<SAreaPoint> TVecAreaPoint;

struct SPath
{
    UINT16 wID;
    vector<SPoint> vecPoint;
    SPath()
    {
        wID = 0;
    }
};
typedef map<UINT16,SPath> TMapPath;

struct SRealivePoint : public SJumpPoint
{
    float fX, fY;
    SRealivePoint () { memset(this, 0, sizeof*this); }
};
struct SDgnJumpPoint : public SJumpPoint
{
    UINT32 dwJumpID;
    UINT8 byType; //0为一般跳转，1为选阵营跳转
    UINT16 wConditionID; //0为默认开启
    float fX, fY;
    bool bVisual;
    SDgnJumpPoint() { memset(this, 0, sizeof*this); }
    SDgnJumpPoint(const SJumpPoint &rPoint,bool bSetVisual):SJumpPoint(rPoint)
    {
        dwJumpID = rPoint.wID;
        byType = 0;
        wConditionID = 0;
        fX = (fLX + fRX)/2;
        fY = (fLY + fRY)/2;
        bVisual = bSetVisual;
    }
};

typedef vector<SJumpPoint> TVecJumpPoint;
typedef vector<SDgnJumpPoint> TVecDgnJumpPoint;

struct SMonsterPoint
{
    //UINT16 wMonsterID;
    float fX;
    float fY;
    float fDir;
    UINT16 wGroup;
    //UINT32 dwRefreshTime;
    UINT16 wDropID;
    //UINT8 byIndex;
    UINT16 wPath;
    bool bHasPath;
    bool bVisual;
    SMonsterPoint() { memset(this, 0, sizeof*this);}

};

typedef vector<SMonsterPoint> TVecMstPoint;

struct SNpcPoint
{
    UINT16 wNpcID;
    float fX;
    float fY;
    float fDir;
    bool  bVisual;
    UINT8 byIndex;

    SNpcPoint() { memset(this, 0, sizeof*this); }
};

typedef vector<SNpcPoint> TVecNpcPoint;

struct SGatherPoint
{
    UINT16 wGatherID;
    float fX;
    float fY;
    bool  bVisual;
    UINT8 byIndex;
    SGatherPoint() { memset(this, 0, sizeof*this); }
};

typedef vector<SGatherPoint> TVecGatherPoint;

struct SBlockerPoint
{
    UINT32 dwID;
    UINT16 wIndex;
    float fX;
    float fY;
    UINT16 wCondID;
    bool bIsOpen;
    SBlockerPoint()
    {
        dwID = 0;
        wIndex = 0;
        fX = 0;
        fY = 0;
        wCondID = 0;
        bIsOpen = false;
    }
    TVecPoint vecBlockerPt;
};

typedef vector<SBlockerPoint> TVecBlockerPoint;

//刷宝箱
struct SChestPoint
{
    UINT32 dwID;
    float fX;
    float fY;
    SChestPoint()
    {
        memset(this,0 , sizeof *this);
    }

};

typedef vector<SChestPoint> TVecChestPoint;

const float arDirect[] = { 0, PI / 4, PI / 2, PI * 3 / 4, PI, PI * 5 / 4, PI * 3 / 2, PI * 7 / 4};

///////////////////////////////////////////////////////////////////////////////////////

void FromBaseCoord(INT32 dwBaseX, INT32 dwBaseY, INT32& dwX, INT32& dwY);
void ToBaseCoord(INT32 dwX, INT32 dwY, INT32& dwBaseX, INT32& dwBaseY);

void IntToFloatCoord(INT32 dwX, INT32 dwY, float& fX, float& fY);
void FloatToIntCoord(float fX, float fY, INT32& dwX, INT32& dwY);

void PointToCoord(const SPoint& rPoint, SCoord& rCoord, bool bBaseGrid = false);
void CoordToPoint(const SCoord& rCoord, SPoint& rPoint, bool bBaseGrid = false);

class CGameMap;

struct SMapInfo : public CAStar
{
    UINT16 wMapID;
    string strName;
    EMapType eMapType;
    UINT16 wLength;
    UINT16 wHeight;
    UINT8** ppBlock;
    SCoord oBroadCastRadius;
    bool bSafe;
    UINT8 byCamp;
    UINT16 wLeastlevel;
    UINT16 wDropID;
    UINT16 wFighterMapID;
    UINT16 wMaxPlayer;//最大人数
    UINT16 wSMaxPlayer;//健康人数

    SRealivePoint oRealivePoint;
    TVecPoint vecRandMovePoint;
    TVecMstPoint vecMstPoint;
    TVecNpcPoint vecNpcPoint;
    TVecJumpPoint vecJumpPoint;
    TVecGatherPoint vecGatherPoint;
    TVecDgnJumpPoint vecDgnJumpPoint;
    TVecBlockerPoint vecBlockerPoint;
    TVecChestPoint   vecChestPoint;
    TVecAreaPoint  vecAreaPoint;
    TVecUINT32  vecSkillID;
    TMapPath _mapPath;
    DEF_NEW_DELETE(SMapInfo);
    SMapInfo() : wMapID(0), eMapType(eMapNone), wLength(0), wHeight(0), ppBlock(NULL), bSafe(false), wDropID(0), wFighterMapID(0),wMaxPlayer(0),wSMaxPlayer(0) { }
    ~SMapInfo();

    SPoint GetRealivePoint();
    virtual int GetMap(int x, int y) const;
    bool LoadConfig(const string& strFile);
    const SPath * GetPath(UINT16 wID);
    bool AllocBuf();
    void FreeBuf();
    void InitBroadCastRadius();
    const SCoord& GetBroadCastRadius() const { return oBroadCastRadius; }
    void GenRandPoint(CGameMap& rMap);
    bool InitMap(const CGameMapPtr& pMap, bool bRefresh = false);
    UINT64 CreateMonster(const CGameMapPtr& pMap,UINT16 wGroup,float fX,float fY,const SPath *pPath,float fDir = 0);
    bool CreateGather(const CGameMapPtr& pMap,UINT16 wGather,UINT8 byIndex,float fX,float fY);
    bool CreateSwitcher(const CGameMapPtr& pMap,const SDgnJumpPoint& rJumpPoint);
    bool CreateNpc(const CGameMapPtr& pMap,const SNpcPoint& rNpcPoint);
    bool CreateBlock(const CGameMapPtr& pMap,const SBlockerPoint& rBlockerPt);
    bool CreateJumpPoint(const CGameMapPtr& pMap,const SJumpPoint& rJumpPoint);
    bool CreateArea(const CGameMapPtr& pMap,const SAreaPoint& rArea); 
    
    bool IsBlock(INT32 dwX, INT32 dwY) const;
    bool IsBlock(const SCoord& rCoord) const;
    bool IsBlock(const SPoint& rPoint) const;
    bool IsCorner(INT32 dwX, INT32 dwY) const;
    bool IsWall(INT32 dwX, INT32 dwY) const;
    bool IsSafe(INT32 dwX, INT32 dwY) const;
    bool HasBlockPoint(const SPoint& rPoint1, const SPoint& rPoint2, bool bLoose = false) const;
    INT32 GetLength(bool bBaseGrid = false) const;
    INT32 GetHeight(bool bBaseGrid = false) const;
    bool ToIntCoord(const SPoint& rPoint, SCoord& rCoord, bool bBaseGrid = false) const;
    bool ToFloatCoord(const SCoord& rCoord, SPoint& rPoint, bool bBaseGrid = false) const;
    bool IsInMapArea(const SCoord& rCoord, bool bBaseGrid = false) const;
    bool IsInMapArea(const SPoint& rPoint) const;
    bool IsNormal() const;
    bool IsWorldCity() const ;
    bool IsDungeon() const;
    bool IsGuildBattle() const;
    bool IsShushanBattleMap() const;

    UINT16 GetFighterMapID() const;
    const string& GetName() const;
};
