#include "configurationInfo.h"
#include "hero.h"
#include "my_memcached.h"
extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

//设置操作系统设置数据；
void setOperationDataInfo(char* buffers)
{
	char size;                         						/*保存每次数据截取的长度*/
	int offset=6;											/*保存信息读取偏移量*/                 
	int dataLen=0;
	int retType=0;
	char ret_OperDataInfo[SHORT_CUT_BAR_DATA_SIZE+20]={0};	

	
	/*获取英雄ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	
	
	offset+=size;   
	offset++;
	// size=buffers[offset++]; 						//数据长度可能大于128，不信任这个值；
	dataLen = strlen(buffers+offset);
	
	if(dataLen > OPERATION_SET_DATA_SIZE)
		dataLen = OPERATION_SET_DATA_SIZE;
		
	char operationSetData[dataLen+1];
	memmove(operationSetData,buffers+offset,dataLen);
	operationSetData[dataLen]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())					//该英雄id不存在；
	{
		retType=1;
	}else{	
		memset(iter->second->memHero->operationSetData,'\0',strlen(iter->second->memHero->operationSetData));
		memmove(iter->second->memHero->operationSetData,operationSetData,dataLen);
	}

	sprintf(ret_OperDataInfo,"21,7,%d,%s",retType,operationSetData);
	send_msg(sock_fd,ret_OperDataInfo);	
}

//获取操作系统设置数据；
void getOperationDataInfo(char* buffers)
{
	char size;                         					/*保存每次数据截取的长度*/
	int offset=6;										/*保存信息读取偏移量*/                 
	int retType=0;
	char ret_OperDataInfo[SHORT_CUT_BAR_DATA_SIZE+20]={0};	
	
	/*获取英雄ID*/
	size=buffers[offset++];
	char hero_id[size+1];
	memmove(hero_id,buffers+offset,size);
	hero_id[size]='\0';
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(hero_id);
	if(iter==heroId_to_pHero.end())						//该英雄id不存在；
	{
		retType=1;		
		return;
	}
	Hero*msgSender=iter->second;
	
	/*获取系统设置数据.*/
	char operationSetData[OPERATION_SET_DATA_SIZE+1];
	memset(operationSetData,'\0',OPERATION_SET_DATA_SIZE+1);
	if(!retType)
		if(iter->second->memHero)
			memcpy(operationSetData,iter->second->memHero->operationSetData,strlen(iter->second->memHero->operationSetData));
	operationSetData[OPERATION_SET_DATA_SIZE]='\0';	

	sprintf(ret_OperDataInfo,"21,8,%d,%s",retType,operationSetData);
	send_msg(msgSender->getFd(),ret_OperDataInfo);	
}