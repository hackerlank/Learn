/************************************************************
	文件名：chatGroup.h
	文件作用：定义ChatGroup(群聊类）的属性和成员
	作者：chenzhen
	创建日期：2013.05.10
************************************************************/

#ifndef CHAT_GROUP
#define CHAT_GROUP
#include<iostream>
#include<set>
#include<string>
using namespace std;
const int CHAT_CROUP_ID_LEN = 50;
class ChatGroup
{
	set<string> chatHeroIdSet;
	
	char groupId[CHAT_CROUP_ID_LEN + 1];
	
	size_t index;
	
	public:
	
	ChatGroup(size_t _index);
	
	ChatGroup(const char *heroId1,const char *heroId2,size_t _index);
	
	const set<string>& getChatSet(void) const;
	
	//插入返回bool值
	bool insert(const char *heroId);
	
	//插入返回bool值
	bool erase(const char *heroId);
	
	size_t size(void) const;
	
	bool empty() const;
	
	const char* getGroupId(void) const;
	
	size_t getIndex(void) const;
	
	//发送消息
	void sendMsg(const char* chatMsg) const;
	
	//判断此人是否在群中
	bool isInGroup(const char *heroId) const;
	
	//析构函数
	~ChatGroup();
	
	private:
	
	//注意，id绝对不能冲突,且防止出错，把它不许外部调用
    ChatGroup(const ChatGroup &chatGroup);
	 
	 //注意，id绝对不能冲突,且防止出错，把它不许外部调用
	ChatGroup& operator=(const ChatGroup &chatGroup);
	
	void creatGroupId();
	
	void init();
};
#endif
	