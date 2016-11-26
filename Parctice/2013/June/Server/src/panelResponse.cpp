/*
		文件类型：实现文件
		文件名称：panelResponse.cpp
		文件作用：面板响应函数；
		修改人：chenzhen
		修改时间：2012.10.24
*/
#include"activeAsist.h"
#include"cpyAsist.h"
#include"hero.h"

extern map<string, Hero*> heroId_to_pHero;

void panelResponse(char *buffer)
{

	char len_arg,hero_id[SHOR_MID_VALUE_LENGTH + 1] = {'\0'}; 
	map<string,Hero*>::iterator hero_it;
	int typeFlg,count = 6;   
	Hero* myHero;
	 	
	
	/*解析id*/
    len_arg = buffer[count++];
    memmove(hero_id,buffer+count,len_arg);
	count += len_arg;	
	
	/*解析类型*/
    len_arg = buffer[count++];
	
	
	if(len_arg != 4)
	{
		cout<<"the panelTypeFlg is error:"<<hero_id<<endl;
		return;
	}  
	
	hero_it = heroId_to_pHero.find(hero_id);
	if(hero_it == heroId_to_pHero.end())
	{
		cout<<"the heroId is error:"<<hero_id<<endl;
		return;
	}	
		
	myHero = hero_it->second;
	
	typeFlg = buffer[count]<<24|buffer[count+1]<<16|buffer[count+2]<<8|buffer[count+3];
	
	
	
	if(typeFlg <= 0 || typeFlg > 4)
	{
		cout<<"the type  error:"<<typeFlg<<endl;
		return;
	}
	
	/*活动面板数据请求*/
	if(typeFlg == 1)
	{
		activePanelResponse(myHero);
	}
	
	/*副本面板数据请求*/
	else if(typeFlg == 2)
	{
		cpyPanelResponse(myHero);
		
	}	
	
	/*体力值面板数据请求*/
	else if(typeFlg == 3)
	{
		fatigueResponse(myHero);		
	}	
	
	/*黑木崖副本面板数据请求*/
	else if(typeFlg == 4)
	{
		towerLayerCpyResponse(myHero);		
	}	
}




