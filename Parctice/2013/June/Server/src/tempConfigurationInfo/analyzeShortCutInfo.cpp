#include "configurationInfo.h"
#include "hero.h"
#include "my_memcached.h"
extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

//设置角色对应快捷操作数据；
void setShortCutInfo(char* buffers)
{
	char size;                         					/*保存每次数据截取的长度*/
	int offset=6;										/*保存信息读取偏移量*/                 
	int dataLen;
	int retType=0;
	char ret_shortCutData[SHORT_CUT_BAR_DATA_SIZE+20]={0};	
	
	/*获取英雄ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	offset+=size;   
	offset++;
	// size=buffers[offset++]; 						//数据长度可能大于128，不信任这个值；
	dataLen = strlen(buffers+offset);
	
	if(dataLen > SHORT_CUT_BAR_DATA_SIZE)
		dataLen = SHORT_CUT_BAR_DATA_SIZE;
		
	char shortCutData[dataLen+1];
	memmove(shortCutData,buffers+offset,dataLen);
	shortCutData[dataLen]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())		//该英雄id不存在；
	{
		retType=1;
	}else{	
		/*获取快捷栏数据.*/
		memset(iter->second->memHero->shortCutData,'\0',strlen(iter->second->memHero->shortCutData));
		memmove(iter->second->memHero->shortCutData,shortCutData,dataLen);
	}
	
	sprintf(ret_shortCutData,"21,2,%d,%s",retType,shortCutData);
	send_msg(sock_fd,ret_shortCutData);	
}

//获取角色对应快捷操作数据；
void getShortCutInfo(char* buffers)
{
	char size;                         					/*保存每次数据截取的长度*/
	int offset=6;										/*保存信息读取偏移量*/                 
	int retType=0;
	char ret_shortCutData[SHORT_CUT_BAR_DATA_SIZE+20]={0};		
	
	
	/*获取英雄ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())		//该英雄id不存在；
	{
		retType=1;
	}
	
	/*获取快捷操作数据.*/
	char shortCutData[SHORT_CUT_BAR_DATA_SIZE+1];
	memset(shortCutData,'\0',SHORT_CUT_BAR_DATA_SIZE+1);
	if(!retType)
		if(iter->second->memHero)
			memcpy(shortCutData,iter->second->memHero->shortCutData,strlen(iter->second->memHero->shortCutData));
	shortCutData[SHORT_CUT_BAR_DATA_SIZE]='\0';	
	
	sprintf(ret_shortCutData,"21,3,%d,%s",retType,shortCutData);
	send_msg(sock_fd,ret_shortCutData);	
}