#pragma once
//#include "StartaskCFG.h"
#include "Task.h"
class CScript;
class CNpc;
#include  "ItemProt.h"
using namespace NItemProt;
struct STaskScript 
{
	bool _bHasCanAcceptTask;
	bool _bHasAcceptTask;
	bool _bHasCanFinishTask;
	bool _bHasFinishTask;
	bool _bHasGiveUpTask;
    bool _bHasDoCaseForDgn;

	STaskScript() : _bHasCanAcceptTask(false), _bHasAcceptTask(false),
		_bHasCanFinishTask(false), _bHasFinishTask(false), _bHasGiveUpTask(false),_bHasDoCaseForDgn(false) { }
};

class CTaskMgr
{
public:
	static bool Init();
//static bool LoadTaskScript();
    static bool LoadConfig(bool bReload = false);
	static STaskScript* GetTaskScript(UINT16 wTaskID);
    static bool ReloadConfig(const string&, bool bReload = true );
	static bool GetNpcAcceptTaskMsg(CNpc& rNpc, CUser& rUser, string& strMsg);
	static bool GetNpcTalkTaskMsg(CNpc& rNpc, CUser& rUser, string& strMsg);
    static bool FinishTaskTalk(CNpc& rNpc, CUser& rUser, UINT16 wTask);  
    static STaskConfig*  GetTaskConfig(UINT16 wTaskID);
    static void ClearTaskScript();
//	static SStartaskCFG* GetTaskStarCfg(UINT8 byStar);
//	static UINT8 RandomTaskStar(bool bFree = true);
	static bool IsDummyMonster(UINT16 wMonsterID);
    static UINT64 GetVersion() { return _qwVersion; } // XXX: 如果配置被重新加载这可以通过这个version来确认是否要更新
    //获取一个环任务
    static bool GetCircleTask(CUser& rUser,UINT16& wTaskId,UINT8 &byStar);
    //获取单个环任务奖励
    static bool GetCircleTaskAward(CUser& rUser,UINT8 byStar,UINT8 byNum,TVecItemGenInfo &rvec);
    //获取完成所有环任务奖励
    static bool GetCircleFinishAward(CUser& rUser,TVecItemGenInfo &rvec);
private:
    static UINT8 GetCircleIdByLevel(UINT8 byLevel);
private:

	static map<UINT16, STaskScript> _mapID2TaskScript;
//	static UINT32 _dwStarWeight;
	static UINT32 _dwStarGoldWeight;
    static UINT64 _qwVersion;
    //circle Task
    static map<UINT8,TVecUINT16> _mapCircleStar;
    static map<UINT8,TVecUINT16> _mapCircleTask;
    static map<UINT8,TVecItemGenInfo> _mapCircleTaskAward;
    static map<UINT8,TVecItemGenInfo> _mapCircleFinishAward;
    static map<UINT8,UINT8> _mapCircleLevelID;
    static map<UINT8,UINT16> _mapCircleAddNum;
    
//	static map<UINT8, SStartaskCFG> _mapStarTaskCfg;
};
