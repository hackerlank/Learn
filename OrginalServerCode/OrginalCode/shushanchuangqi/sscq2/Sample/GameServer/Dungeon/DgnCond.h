#include "DungeonProt.h"
#include "stdafx.h"
using namespace NDungeonProt;
class DungeonCondBase
{
    public:
        virtual bool KillMonster(UINT16 wMonster){return false; } ;
        virtual bool GatherFinish(UINT16 wGatherId){return false;};
        virtual bool TimerCheck(UINT32 tNow){return false;};
        virtual bool AddTurns(UINT8 wTurns){return false;}
        virtual bool ArriveArea(UINT16 wAreaId){ return false;}
        virtual bool FightWithMonster(UINT16 wGroupId){return false ;}
        virtual DgnSucCondPtr GetStream() = 0;
        EDgnCondStatus GetStatus();
        virtual ~DungeonCondBase() {};

};
DEF_SMART_POINTER(class,DungeonCondBase);
typedef vector<DungeonCondBasePtr> TVecDungeonCondBasePtr;
class DungeonCondSucMonster:public SucMonster,public DungeonCondBase
{
    public:
        DungeonCondSucMonster(UINT16 wId,UINT16 wMonster,UINT8 byNum);
        virtual bool KillMonster(UINT16 wMonster) ;
        virtual DgnSucCondPtr GetStream(); 
};
DEF_SMART_POINTER(class,DungeonCondSucMonster);
class DungeonCondSucGather:public SucGather,public DungeonCondBase
{
    public:
        DungeonCondSucGather(UINT16 wId,UINT16 wGatherId,UINT8 byNum);
        virtual bool GatherFinish(UINT16 wGatherId) ;
        virtual DgnSucCondPtr GetStream();
};
DEF_SMART_POINTER(class,DungeonCondSucGather);
class DungeonCondSucTurns:public SucTurns,public DungeonCondBase 
{
    public:
       DungeonCondSucTurns(UINT16 wId,UINT8 byTurns);
       virtual bool AddTurns(UINT8 byTurns);
       virtual DgnSucCondPtr GetStream();
};
 DEF_SMART_POINTER(class,DungeonCondSucTurns);
class DungeonCondSucInTimer: public SucInTimer,public DungeonCondBase
{
    public:
        DungeonCondSucInTimer(UINT16 wId,UINT32 dwTimer);
        virtual bool TimerCheck(UINT32 tNow);
        virtual DgnSucCondPtr GetStream();
};
DEF_SMART_POINTER(class,DungeonCondSucInTimer);
class DungeonCondSucMonsterInTimer: public SucMonsterInTimer,public DungeonCondBase
{
    public:
        DungeonCondSucMonsterInTimer(UINT16 wId,UINT16 wMonster,UINT8 byNum,UINT32 dwTimer);
        virtual bool KillMonster(UINT16 wMonster) ; 
        virtual bool TimerCheck(UINT32 tNow);
        virtual DgnSucCondPtr GetStream();
};
DEF_SMART_POINTER(class,DungeonCondSucMonsterInTimer);
class DungeonCondSucGatherInTimer: public SucGatherInTimer,public DungeonCondBase
{
    public:
        DungeonCondSucGatherInTimer(UINT16 wId,UINT16 wGatherId,UINT8 byNum,UINT32 dwTimer);
        virtual bool TimerCheck(UINT32 tNow); 
        virtual bool GatherFinish(UINT16 wGatherId) ;
        virtual DgnSucCondPtr GetStream();

};
DEF_SMART_POINTER(class,DungeonCondSucGatherInTimer);
class DungeonCondSucFightWithMonsterMinTimes: public SucFightWithMonsterMinTimes,public DungeonCondBase
{
    public:
        DungeonCondSucFightWithMonsterMinTimes(UINT16 wId,UINT16 wGroupId,UINT8 byNum);
        virtual bool FightWithMonster(UINT16 wGroupId);
        virtual DgnSucCondPtr GetStream();

};
DEF_SMART_POINTER(class,DungeonCondSucFightWithMonsterMinTimes);
class DungeonCondSucArriveArea: public SucArriveArea,public DungeonCondBase
{
    public:
        DungeonCondSucArriveArea(UINT16 wId,UINT16 wAreaId);
        virtual bool ArriveArea(UINT16 wAreaId);
        virtual DgnSucCondPtr GetStream();

};
DEF_SMART_POINTER(class,DungeonCondSucArriveArea);
