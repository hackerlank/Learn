/************************************************************
	文件名：ChatGroupManager.h
	文件作用：定义ChatGroupManager(管理群聊类）的属性和成员
	作者：chenzhen
	创建日期：2013.05.10
************************************************************/

#ifndef CHAT_GROUP_MANAGER_H
#define CHAT_GROUP_MANAGER_H
#include<iostream>
#include<vector>
#include<list>
#include<map>
#include<set>
#include<string>
using namespace std;

class ChatGroup;

class ChatGroupManager
{
	vector<ChatGroup*> groupVec;
	list<int> usefulIndexlist;	
	
	//不够时动态生成
	vector<ChatGroup*> dynamicGroupVec;
	
	//正在用的动态下标
	set<int> usedDynamicIndex;
	
	//删掉后vector留下的空孔下标
	list<int> useAbledynamicIndex;
	
	map<string,int> usedGroupIdIndexMap;
	
	//包括动态的，所有群数量,统计作用，不用做别用
	size_t totalSize;
	
	static ChatGroupManager *chatGroupManager;
	
	
	public:	
	
	static void createManagerInst(size_t groupNum);
	
	static ChatGroupManager* getManagerInst();
	
	//获得gruopId对应的群句柄
	ChatGroup* getChatGroupHandle(const char* groupId);
	
	//占据一个群实例，返回实例id
	const char* campGroupHandle(const char* heroIdOwner);
	
	//回收一个群
	void recoverGroupHandle(const char* groupId);
	
	//析构函数
	~ChatGroupManager();
	
	private:
	
	//静止外部调用
	ChatGroupManager(const ChatGroupManager &groupManager);
	
	//静止外部调用
	ChatGroupManager& operator=(const ChatGroupManager &groupManager);
	
	//静止外部调用（单例模式）
	ChatGroupManager(size_t groupNum);
};
#endif
	