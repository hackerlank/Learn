#ifndef GROUPTASKMANAGER_H__
#define GROUPTASKMANAGER_H__
#include "stdafx.h"
#include "Daily_shimenCFG.h"
#include "Daily_shimentaskCFG.h"
#include "Daily_shimentaskColorCFG.h"
struct SDaily_shimentaskCFGEx: public SDaily_shimentaskCFG
{
    struct RateTask
    {
        UINT16 wRate;
        TVecUINT16 vecTask;
    };

    SDaily_shimentaskCFGEx(const SDaily_shimentaskCFG& rCfg):SDaily_shimentaskCFG(rCfg)
    {
    }
    vector<RateTask> vecRateTask;
    vector<RateTask> vecRateTaskCost;

};
class CPlayer;
class CGroupTaskManager
{
    public:
        bool Init();
        bool ReLoadConfig(const string&);

        void GetTasksByLevel(CPlayer &rPlayer,UINT8 byNum,vector<UINT16>& vecTask,bool bFirst,bool bCost);//获得师门任务库
        const SDaily_shimenCFG * GetLevelCFGbyLevel(UINT16 wLevel);//获得师门等级配 
        UINT16 GetReputeLvByRepute(UINT32 dwRepute);
        UINT16 GetReputeLvByTaskId(UINT32 wTaskId,UINT32 dwRepute);
        const SDaily_shimentaskColorCFG *GetConfigByTaskID(UINT16 wTaskID);
    private:
        
        map<UINT16,SDaily_shimenCFG> _mapGroupLevel;//师门等级配置
        vector<SDaily_shimentaskCFGEx> _vecCroupTask;//任务数据库
        map<UINT16,SDaily_shimentaskColorCFG> _mapColor;
    private:
        void CheckRepeatTask(CPlayer &rPlayer,SDaily_shimentaskCFGEx &tepCfg,bool bCost);
        void ResetRateMap(SDaily_shimentaskCFGEx &tepCfg, bool bCost);
        bool LoadConfig();
        bool LoadLevel();
        bool LoadColor();

};
extern CGroupTaskManager g_CGroupTaskManager;
#endif
