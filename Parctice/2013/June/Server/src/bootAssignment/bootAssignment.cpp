#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "other_define_data.h"
#include "bootAssignment.h"
#include "hero.h" 

extern int	nickNameCounts;
extern int 	preNickNameCounts;
extern NickName2heroIdHash heroNameCheckHash;

NickNameCheck_T mynickName;
ev_timer *nickNameValueTimer;

void 
nickNameCheckValueBootInit()
{

	heroNameCheckHash.clear();
	nickNameCounts=0;
	char nickName2heroIdInfo[256];
	int size=0;	
	
	memset(nickName2heroIdInfo,'\0',strlen(nickName2heroIdInfo));
	FILE* fp= fopen("config/nickName2HeorId.txt", "at+");
    if(fp==NULL)
    {
       printf("in the bootAssignment.cpp --->open the  file config/nickName.txt is error!\n");
    }else {
    while(fgets(nickName2heroIdInfo,256,fp) != NULL) { 
			char *nickName=strtok(nickName2heroIdInfo,",");
			char *heroId=strtok(NULL,",");
			
			//添加到昵称同名检查容器；
			memcpy(mynickName.nickName[nickNameCounts],nickName,strlen(nickName));
			memcpy(mynickName.HeroId[nickNameCounts],heroId,strlen(heroId));
			heroNameCheckHash[mynickName.nickName[nickNameCounts]]=mynickName.HeroId[nickNameCounts];
			nickNameCounts++;
		}
	}
	preNickNameCounts = nickNameCounts;
	if(fp)
		fclose(fp);
}

void 
saveNickNameCheckValue2Mem()
{  
    FILE *fp_clear=NULL;
    fp_clear=fopen("config/nickName2HeorId.txt","w");
	if(fp_clear)
		fclose(fp_clear);
		
    fp_clear=fopen("config/nickName2HeorId.txt","a+");
	for(NickName2heroIdHash::iterator iter = heroNameCheckHash.begin();iter != heroNameCheckHash.end();iter++)
	{
		char mystr[strlen(iter->first)+strlen(iter->second)+1];
		memset(mystr,'\0',sizeof(mystr));
		sprintf(mystr,"%s,%s\n",iter->first,iter->second);
		fputs(mystr,fp_clear); 
	}
	if(fp_clear)
		fclose(fp_clear);	
}

void 
updataNickNameCheckValue()
{
	FILE *fp_updata=NULL;

    fp_updata=fopen("config/nickName2HeorId.txt","a+");
	char mystr[HERO_ID_LEN+HERO_MAME_LEN+2];	
	
	for(int row = preNickNameCounts; row < nickNameCounts; row++)
	{
		memset(mystr,'\0',sizeof(mystr));	
		sprintf(mystr,"%s,%s\n",mynickName.nickName[row],mynickName.HeroId[row]);
		fputs(mystr,fp_updata); 
	}
	preNickNameCounts=nickNameCounts;
	
	if(fp_updata)
		fclose(fp_updata);
}



void 
saveDeleteNickNameValue()			//用于保存删除的用户名；
{
	FILE *fp_updata=NULL;

    fp_updata=fopen("config/nickName2HeorId.txt","a+");
	char mystr[HERO_ID_LEN+HERO_MAME_LEN+2];	
	if(NULL != fp_updata)
	{
		// for(int row = preNickNameCounts; row < nickNameCounts; row++)
		// {
			// memset(mystr,'\0',sizeof(mystr));	
			// sprintf(mystr,"%s,%s\n",mynickName.nickName[row],mynickName.HeroId[row]);
			// fputs(mystr,fp_updata); 
		// }
		// preNickNameCounts=nickNameCounts;
	}else{
		printf("in the bootAssignment.cpp --->open the  file config/nickName2HeorId.txt is error!\n");
	}
	if(fp_updata)
		fclose(fp_updata);
}
