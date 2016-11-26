/************************************************************
	文件名：exitCpy.cpp
	文件作用：退出副本的方法
	作者：chenzhen
	创建日期：2012.06.29
************************************************************/
#include"command_other_function_all_over.h"
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"cpyAsist.h"
#include"hero.h"

extern int g_msg_len;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern Hero* pg_hero;
void exitCpy(char *buffer)
{	 	
	map<string,CpyLimit*>::iterator cpyLimt_it;
	map<string, Hero*>::iterator hero_it;
	char *hero_id; 
	
//	cout<<"exit cpy before:"<<endl;
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*解析id*/
	MSG_CHAR_END(hero_id);	
	
	hero_it = heroId_to_pHero.find(hero_id);	
	
	if(hero_it == heroId_to_pHero.end())
	{
		return;           
	} 
//	cout<<"exit cpy after:"<<endl;
	outCpy(hero_it->second);	
	
	return;
}
	
	
	