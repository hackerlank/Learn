/********************************************************************
//	TaskLoad Library Source File.
//	File name:	TaskConfMgr.h
//	Created:	2011/09/12	15:00
//	Organization:	
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:	
//	Version:	1.0
//	Histroy:
*********************************************************************/

#pragma once
#include <set>
#include <sstream>
#include "TaskConf.h"

using namespace std;

struct SNpcTask
{
	vector<UINT16> vecAcceptTask;
	vector<UINT16> vecFinishTask;
	map<UINT16, SNpcTalk> mapTask2Talk;
};

struct SProbeInfo
{
	UINT16 wTaskID;
	SMapArea oMapArea;

	SProbeInfo() { memset(this, 0, sizeof*this); }
};

typedef vector<SProbeInfo> TVecProbeInfo;

typedef std::vector<UINT16> TTaskList;
typedef std::map<UINT16, STaskConfig> TMapTaskConfig;

class CTaskConfMgr
{
public:

	static CTaskConfMgr& Instance()
	{
		static CTaskConfMgr mgr;
		return mgr;
	}

	/**
	*	从目录中加载名字为Task*.xml的文件
	*
	*/
	bool LoadTaskDirectory(const string& strPath);
   
    // 从指定的目录中加载指定的文件
    // 该目录中必须存在该文件
    bool LoadTaskFile(const string&, const string&);

	TMapTaskConfig& GetTaskConfig();
	STaskConfig* GetTaskConfig(UINT16 wTaskID);

	//得到某个Monster对应的所有杀怪任务列表
	TTaskList* GetMonsterTask(UINT16 wMonsterID);
	//得到某个道具对应的所有收集任务列表
	TTaskList* GetCollectTask(UINT16 wItemID);
	//得到某个Monster对应的所有收集道具任务列表
	TTaskList* GetCollectKillTask(UINT16 wMonsterID);
	//怪物是否有任务
	bool HasTask(UINT16 wMonsterID);

	//得到某个人物属性对应的成长任务列表
	TTaskList* GetRoleProperty(EProcessRoleProperty type);

	/*
	TTaskList* GetUseItemTask(UINT32 wItemID);
	TTaskList* GetUseSkillTask(UINT32 dwSkillID);
	*/

	//得到某个item对应的采集任务列表
	TTaskList* GetGatherTask(UINT16 wItemID);

	//得到某个活动对应的行为任务列表
	TTaskList* GetBehaviorTask(EProcessAction type);

	//得到某个建筑对应的建设任务列表
	TTaskList* GetBuildingTask(UINT32 id);
	//得到某项科技对应的建设任务列表
	TTaskList* GetTechnicTask(UINT32 id);

	//得到与某个Npc相关的任务列表
	SNpcTask* GetNpcTask(UINT16 wNpcID);

	//得到与某个地图相关的探索任务信息
	TVecProbeInfo* GetProbeTask(UINT16 wMapID);

	//系统触发任务
	//等级
	void AddLevelTask(UINT16 wLevel, UINT16 wTaskID);
	TTaskList* GetLevelTask(UINT16 wLevel);
	//声望
	TTaskList* GetReputeTask(UINT16 wCamp);
	//前置
	TTaskList* GetTaskPreTask(UINT16 wTaskID);
	//出生
	TTaskList* GetBeginTask();
	//区域
	TVecProbeInfo* GetTriggerTask(UINT16 wMapID);
    //每日任务
    const TTaskList& GetEveryDayTask();

	//悬赏任务
	//void AddChurchTask(UINT16 wLevel, UINT16 wTaskID);

	//TTaskList* GetChurchTask(UINT16 wLevel);

	ostringstream& GetLogStream() { return _osLog; }

private:
	bool LoadTask(UINT16 wTaskID, const string& strXmlPath);

private:
	TMapTaskConfig _mapID2TaskConf;

	//任务内容分类
	map<UINT16, TTaskList> _mapMst2TaskList;		//杀怪
	map<EProcessRoleProperty, TTaskList> _mapGrow2TaskList;	//成长
	map<UINT16, TTaskList> _mapItem2ColTaskList;	//收集
	map<UINT16, TTaskList> _mapMst2ColTaskList;		//杀怪收集
	
	//map<UINT32, TTaskList> _mapItem2UseTaskList;
	//map<UINT32, vector<UINT16>> _mapSkill2UseTaskList;

	map<UINT16, TTaskList> _mapGather2TaskList;			//采集
	map<UINT16, TVecProbeInfo> _mapMap2ProbeList;		//探索
	map<EProcessAction, TTaskList> _mapAction2TaskList;	//行为
	map<UINT32, TTaskList> _mapBuilding2TaskList;	//建设_建筑
	map<UINT32, TTaskList> _mapTechnic2TaskList;	//建筑_科技
	map<UINT16, SNpcTask> _mapNpc2Task;				//与NPC相关的

	//系统触发任务
	TTaskList _vecBegin2TaskList;	//出生触发任务
	map<UINT16, TVecProbeInfo> _mapMap2TriggerList;//触发器任务
	map<UINT16, TTaskList> _mapLevel2TaskList;	//等级触发任务
	map<UINT16, TTaskList> _mapRepute2TaskList;	//声望触发任务
	map<UINT16, TTaskList> _mapTaskPre2TaskList;//前置触发任务

	//教会任务
    //map<UINT16, TTaskList> _mapChurch2TaskList; //教会悬赏任务
   TTaskList _vecEveryDayTask; 

	ostringstream _osLog;
};
