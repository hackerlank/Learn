#ifndef  DGNCONDMANGER_H__
#define  DGNCONDMANGER_H__
#include "DgnCond.h"
#include "DungeonAssessCFG.h"
struct DungeonAssessCFGEx: public SDungeonAssessCFG
{
    public:
        DungeonAssessCFGEx(const SDungeonAssessCFG& rFg):SDungeonAssessCFG(rFg)
    {
    }
        DungeonAssessCFGEx(){}
        EType_DgnSucCond _eType;
        TVecUINT32 _vecParam;
};

class DgnCondInstance
{
    public:
     bool InitByID(const vector<TVecUINT16> &vecID);
     bool KillMonster(UINT16 wMonster) ;
     bool GatherFinish(UINT16 wGatherId);
     bool TimerCheck(UINT32 tNow);
     bool AddTurns(UINT8 wTurns);
     bool ArriveArea(UINT16 wAreaId);
     bool FightWithMonster(UINT16 wGroupId);
     void GetStream(TVecMulCond &rvec);
     bool IsAllSuc();
     bool IsOneFail();
     UINT8 GetSucNum();
     void GetAllState(vector<EDgnCondStatus> &vecStatus);
   private:
     bool IsAllSuc(TVecDungeonCondBasePtr &rVec) const;
     bool IsOneFail(TVecDungeonCondBasePtr &rVec) const;

     vector<TVecDungeonCondBasePtr> _vecCond;

};

class CDgnCondManager
{
    public:
        bool Init();
        const DungeonAssessCFGEx * GetDgnConfig(UINT16 wID);
        DungeonCondBasePtr CreateCond(UINT16 wID);
    private:
       map<UINT16,DungeonAssessCFGEx> _mapCfg;

};
extern CDgnCondManager g_CDgnCondManager;
#endif //DGNCONDMANGER_H__
