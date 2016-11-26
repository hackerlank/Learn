/*
		文件类型：实现文件
		文件名称：activeAccept.cpp
		文件作用：实现私聊的消息发送；
		修改人：chenzhen
		修改时间：2012.10.24
*/
#include"active_communicate.h"
#include"dailyActive.h"
#include"hero.h"

extern map<string,DailyActive*> dailyActiveConfMap;
extern map<string, Hero*> heroId_to_pHero;

void takePartActive(char *buffers)
{	
	char len_arg,my_hero_id[SHOR_MID_VALUE_LENGTH + 1] = {'\0'}; 
	char active_id[SHOR_MID_VALUE_LENGTH + 1] = {'\0'}; 
	map<string,DailyActive*>::iterator active_it;
	map<string,Hero*>::iterator msgSender_iter;
	int typeFlg,count = 6;   
	Hero* msgSender;
   
	len_arg = buffers[count++];
	memmove(my_hero_id,buffers+count,len_arg);
	
	msgSender_iter=heroId_to_pHero.find(my_hero_id);	
	if(msgSender_iter == heroId_to_pHero.end())
	{
		cout<<"msgSender is not find:"<<my_hero_id<<endl;
		return;
	}
	
	msgSender = msgSender_iter->second;
	if(NULL == msgSender)
	{
		cout<<"msgSender is NULL:"<<my_hero_id<<endl;
	    return;
	}	
	count += len_arg;
	len_arg = buffers[count++];
	memmove(active_id,buffers+count,len_arg);	
	
	active_it = dailyActiveConfMap.find(active_id);
	
	if(active_it == dailyActiveConfMap.end())
	{
		cout<<"not find the active:"<<endl;
		return;
	}
	
	active_it->second->takePart(msgSender);	
	
}




