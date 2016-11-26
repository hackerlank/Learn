#include "configurationInfo.h"
#include "hero.h"
#include "my_memcached.h"
extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

//设置系统设置数据；
void setSystemDataInfo(char* buffers)
{
	char size;                         					/*保存每次数据截取的长度*/
	int offset=6;										/*保存信息读取偏移量*/                 
	int dataLen=0;
	int retType=0;
	char ret_systemSetData[SYSTEM_SET_DATA_SIZE+20]={0};	
	
	/*获取英雄ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	offset+=size;   
	
	
	offset++;
	// size=buffers[offset++]; 						//数据长度可能大于128，不信任这个值；
	dataLen = strlen(buffers+offset);
	
	if(dataLen > SYSTEM_SET_DATA_SIZE)
		dataLen = SYSTEM_SET_DATA_SIZE;
		
	char systemSetData[dataLen+1];
	memmove(systemSetData,buffers+offset,dataLen);
	systemSetData[dataLen]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())		//该英雄id不存在；
	{
		retType=1;
	}else{	
		/*获取系统设置数据.*/
		memset(iter->second->memHero->systemSetData,'\0',strlen(iter->second->memHero->systemSetData));
		memmove(iter->second->memHero->systemSetData,systemSetData,dataLen);
	}

	sprintf(ret_systemSetData,"21,5,%d,%s",retType,systemSetData);
	send_msg(sock_fd, ret_systemSetData);     
} 

//获取系统设置数据；
void getSystemDataInfo(char* buffers)
{
	char size;                         					/*保存每次数据截取的长度*/
	int offset=6;										/*保存信息读取偏移量*/                 
	int retType=0;
	char ret_systemGetData[SYSTEM_SET_DATA_SIZE+20]={0};	
	
	/*获取英雄ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())		//该英雄id不存在；
	{
		retType=1;		
		return;
	}
	Hero*msgSender=iter->second;
	
	/*获取系统设置数据.*/
	char systemSetData[SYSTEM_SET_DATA_SIZE+1];
	memset(systemSetData,'\0',SYSTEM_SET_DATA_SIZE+1);
	if(!retType)
		if(iter->second->memHero)
			memcpy(systemSetData,iter->second->memHero->systemSetData,strlen(iter->second->memHero->systemSetData));
	systemSetData[SYSTEM_SET_DATA_SIZE]='\0';	

	sprintf(ret_systemGetData,"21,6,%d,%s",retType,systemSetData);	
	send_msg(msgSender->getFd(),ret_systemGetData);	
}