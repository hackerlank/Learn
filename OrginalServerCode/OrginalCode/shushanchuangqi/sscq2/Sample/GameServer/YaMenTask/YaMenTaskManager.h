#ifndef YAMENTASKMANAGER_H__
#define YAMENTASKMANAGER_H__
#include "stdafx.h"
#include "Daily_yamenCFG.h"
#include "Daily_yamentaskCFG.h"
#include "Daily_yamentaskColorCFG.h"

struct SDaily_yamentaskCFGEx: public SDaily_yamentaskCFG
{
    struct RateTask
    {
        UINT16 wRate;
        TVecUINT16 vecTask;
    };
    SDaily_yamentaskCFGEx(const SDaily_yamentaskCFG& rCfg):SDaily_yamentaskCFG(rCfg)
    {
    }
    vector<RateTask> vecRateTask;
    vector<RateTask> vecRateTaskCost;
};

class CPlayer;
class CYaMenTaskManager
{
    public:
        bool Init();
        bool ReLoadConfig(const string&);

        void GetTasksByLevel(CPlayer &rPlayer,UINT8 byNum,vector<UINT16>& vecTask,bool bFirst ,bool bCost);//获得衙门任务库
        const SDaily_yamenCFG * GetLevelCFGbyLevel(UINT16 wLevel);//获得衙门等级配 
        UINT16 GetReputeLvByRepute(UINT32 dwRepute);
        UINT16 GetReputeLvByTaskId(UINT32 wTaskId,UINT32 dwRepute);
        const SDaily_yamentaskColorCFG *GetConfigByTaskID(UINT16 wTaskID);
    private:
        void CheckRepeatTask(CPlayer &rPlayer,SDaily_yamentaskCFGEx &tepCfg,bool bCost);

        void ResetRateMap(SDaily_yamentaskCFGEx &tepCfg,bool bCost);
        bool LoadConfig();
        bool LoadLevel();
        bool LoadColor();
    private:
        map<UINT16,SDaily_yamenCFG> _mapYaMenLevel;//衙门等级配置
        vector<SDaily_yamentaskCFGEx> _vecCroupTask;//任务数据库
        map<UINT16,SDaily_yamentaskColorCFG> _mapColor;
};
extern CYaMenTaskManager g_CYaMenTaskManager;
#endif
