/************************************************************
	文件名：TeamManager.h
	文件作用：定义TeamManager(管理组队类）的属性和成员
	作者：chenzhen
	创建日期：2013.05.10
************************************************************/

#ifndef TEAM_MANGER_H
#define TEAM_MANGER_H
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<string>
using namespace std;

class Team;

class TeamManager
{
	vector<Team*> teamVec;
	list<int> usefulIndexlist;	
	
	//不够时动态生成
	vector<Team*> dynamicTeamVec;
	
	//正在用的动态下标
	set<int> usedDynamicIndex;
	
	//删掉后vector留下的空孔下标
	list<int> useAbledynamicIndex;
	
	map<string,int> usedTeamIdIndexMap;
	
	//包括动态的，所有群数量,统计作用，不用做别用
	size_t totalSize;
	
	static TeamManager *teamManager;
	
	
	public:	
	
	static void createManagerInst(size_t groupNum);
	
	static TeamManager* getManagerInst();
	
	//获得gruopId对应的群句柄
	Team* getTeamHandle(const char* teamId);
	
	//占据一个群实例，返回实例id
	const char* captureTeamHandle(const char *teamLeader);
	
	//回收一个群
	void recoverTeamHandle(const char* teamId);
	
	//析构函数
	~TeamManager();
	
	void addAgreeNum();
	
	void initAgreeNum();
	
	size_t size() const;
	
	private:
	
	//静止外部调用
	TeamManager(const TeamManager &teamManagers);
	
	//静止外部调用
	TeamManager& operator=(const TeamManager &teamManagers);
	
	//静止外部调用（单例模式）
	TeamManager(size_t teamNum);
};
#endif
	