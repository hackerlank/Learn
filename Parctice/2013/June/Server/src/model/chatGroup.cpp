/************************************************************
	文件名：ChatGroup.cpp
	文件作用：实现ChatGroup(群聊类）
	作者：chenzhen
	创建日期：2013.05.10
************************************************************/
#include"chatGroup.h"
#include"command_other_function_all_over.h"
ChatGroup::ChatGroup(size_t _index)
{	
	init();	
	index = _index;
}


//防止浪费，至少要有2个人，才允许建群聊
ChatGroup::ChatGroup(const char *heroId1,const char *heroId2,size_t _index)
{	
	init();
	chatHeroIdSet.insert(heroId1);
	chatHeroIdSet.insert(heroId2);
	index = _index;
}

//注意，id绝对不能冲突,且防止出错，把它不许外部调用,所以，不实现
ChatGroup::ChatGroup(const ChatGroup &chatGroup)
{
	
}

//注意，id绝对不能冲突,且防止出错，把它不许外部调用，不实现
ChatGroup& ChatGroup::operator=(const ChatGroup &chatGroup)
{
	return *this;
}

//插入返回bool值
bool ChatGroup::insert(const char *heroId)
{
	pair<set<string>::iterator,bool> insert_it = chatHeroIdSet.insert(heroId);
	return insert_it.second;
}

//插入返回bool值
bool ChatGroup::erase(const char *heroId)
{
	size_t result = chatHeroIdSet.erase(heroId);
	return result > 0 ? true : false;
}

size_t ChatGroup::size(void) const
{
	return chatHeroIdSet.size();
}

bool ChatGroup::empty() const
{
	return chatHeroIdSet.empty();
}


void ChatGroup::creatGroupId()
{
	char * temp = cid();
	if(!temp)
	{
		cout<<"ChatGroup::creatGroupId the temp is NULL error:"<<endl;		
		return;
	}
	strncpy(groupId,temp,strlen(temp));		
	free(temp);
	
}

void ChatGroup::init()
{
	chatHeroIdSet.clear();	
	memset(groupId,'\0',sizeof(groupId));	
	creatGroupId();
}

const char* ChatGroup::getGroupId(void) const
{
	return groupId;
}

size_t ChatGroup::getIndex(void) const
{
	return index;
}

//发送消息
void ChatGroup::sendMsg(const char* chatMsg) const
{
	if(chatHeroIdSet.empty() || !chatMsg)
	{
		cout<<"the chatGroup is empty or the chatMsg is NULL:"<<groupId<<endl;
		return;
	}
	
	for(set<string>::iterator chat_it = chatHeroIdSet.begin();chat_it != chatHeroIdSet.end();++chat_it)
	{
		Hero *chatHero = heroid_to_hero(*chat_it);
		if(chatHero)
		{
			send_msg(chatHero->getFd(),chatMsg);
		}
	}
}

//判断此人是否在群中
bool ChatGroup::isInGroup(const char *heroId) const
{
	if(chatHeroIdSet.empty())
	{
		return false;
	}
	set<string>::iterator chat_it = chatHeroIdSet.find(heroId);
	if(chat_it == chatHeroIdSet.end())
	{
		return false;
	}
	return true;
}

//析构函数
ChatGroup::~ChatGroup()
{
	chatHeroIdSet.clear();
	memset(groupId,'\0',sizeof(groupId));
}
	
	
	



	
