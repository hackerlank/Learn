#pragma once
#include "TaskConf.h"
#include "TaskProt.h"
#include "RoleInfoDefine.h"
#include "Version.h"
#include "TaskMgr.h"

using namespace NTaskProt;
using namespace NRoleInfoDefine; 
enum ETaskType
{
	eTaskCommon,	//普通
	eTaskChurch,	//教会
};

class CTaskMgr;

class CTaskPkg;

class CTask : public enable_shared_from_this<CTask>, public CPoolObj<CTask>
{
	friend class CTaskPkg;
public:
	DEF_NEW_DELETE(CTask);
    CTask(STaskConfig& rTaskConf, CTaskPkg& rTaskPkg, UINT64 qwVersion) :_pTaskConf(&rTaskConf),_rTaskPkg(rTaskPkg),
		_eTaskState(eTaskNone), _byAcceptTimes(1), _dwAcceptTime((UINT32)time(NULL)),_qwVersion(qwVersion)
    {
    }
    virtual ~CTask();// { }
	bool Init();
	UINT16 GetTaskID() { return GetConfig().wID; }
	ETaskState GetTaskState() const { return _eTaskState; }
	virtual ETaskType GetTaskType() const { return eTaskCommon; }
	void SetTaskState(ETaskState eTaskState) { _eTaskState = eTaskState; }
	bool IsRepeatTask() { return GetConfig().dwRepeat > 0; }
    void NotifyTaskFinish();
    void FromRoleTaskInfo(const RoleTaskInfo& rTaskInfo);
    STaskInfoPtr GetTaskInfo(UINT8 byType,UINT32 dwParam1,UINT32 dwParam2);
    void SetTaskInfo(STaskInfoPtr pInfo,UINT8 &byType,UINT32 &dwParam1,UINT32 &dwParam2);
    void ToRoleTaskInfo(RoleTaskInfo& rTaskInfo);
	virtual ETaskResult OnFinish(UINT8 byIndex,UINT8 &byAcceptTimes,bool bForce);

	bool OnAccept(bool bNotify  = true);
	void OnGiveUp();
	bool OnCollectItem(UINT16 wItemID);
	bool OnGather(UINT16 wGatherID);
	bool OnNpcTalk(UINT16 wNpcID);
	bool OnKillMonster(UINT16 wMonsterID);
	bool OnProbe(SMapArea& rMapArea);
	bool OnGrow(CPlayer& rPlayer, EProcessRoleProperty eProperty);
	bool OnAction(EProcessAction eProcessAction, UINT32 dwValue);
	bool OnBuild(UINT16 wBuildID, UINT16 wLevel);
	bool OnTechnics(UINT16 wTechnicsID, UINT16 wLevel);

	void OnReset();
	void SetFinishTask();
	bool ForceFinishProbe();
	bool CheckStateAndUpdate(bool bNotify = true);
	bool CheckFinishState();
	void OnStateUpdate(ETaskState eTaskState, bool bNotify = true);
    UINT8 CheckTaskAction(UINT16 type, string strParam);//0:表示成功，1：表示失败，2表示无法判定

	const STaskConfig& GetTaskConfig() { return GetConfig(); }
	UINT32 GetAcceptTime() { return _dwAcceptTime; }
	UINT32 GetLimitTime() { return GetConfig().dwLimitTime; }
	bool CanTalkWithNpc(UINT16 wNpcID);
	bool IsFakeMonsterTask();
    STask ToStask();
    void SynData(RoleTaskInfo& rTaskInfo);
	bool IsClrCheckTask(EProcessAction eProcessAction);
    UINT8 GetCurAcceptTimes() {return  _byAcceptTimes;}
    bool  SubAcceptTimes() { return --_byAcceptTimes ==  0 ;}
    void  AddAcceptTimes() { _byAcceptTimes++;}
protected:
	void GetTaskInfoList(TVecTaskInfo& vecTaskInfo) const;
	bool RefreshSurroundTaskMonster(bool bAccept);
	ETaskResult OnGiveAward(UINT8 byIndex,bool bForce);
	void AwardGeneral(CUser& rUser, CPlayer& rPlayer,bool bForce);
    STaskConfig& GetConfig();
    
    STaskConfig* _pTaskConf;
	CTaskPkg& _rTaskPkg;
	ETaskState _eTaskState;
    UINT8 _byAcceptTimes;
	UINT32 _dwAcceptTime;
    UINT64 _qwVersion;
	multimap<EType_STaskInfo, STaskInfoPtr> _mapType2Info;
};
