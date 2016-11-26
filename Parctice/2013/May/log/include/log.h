#ifndef LOG_H
#define LOG_H
#include<iostream>
#include<string.h>
#include <sys/stat.h>
#include<stdio.h>
using namespace std;
const int FIL_NAME_LEN = 100;
class Log
{
	char errorFileName[FIL_NAME_LEN + 1];
	char dirName[FIL_NAME_LEN + 1];	
	FILE *errorFile;
	
	public:
	
	Log()
	{
		memset(dirName,'\0',sizeof(dirName));
		memset(errorFileName,'\0',sizeof(errorFileName));
		getcwd(dirName,sizeof(dirName));
		if(strlen(dirName) == 0)
		{
			cout<<"Log() the temp is empty:"<<endl;
			return;
		}
		strncat(dirName,"/temp",5);
		if(access(dirName,F_OK)!=0)  
		{  
			if(mkdir(dirName,0777)==-1)  
			{   
				cout<<"Log() the mkdir  is error:"<<endl;
				return;   
			}
		}
		strncpy(errorFileName,dirName,strlen(dirName));
		strncat(errorFileName,"/error.txt",10);
		
	}
	
	void recordError(char *errorMsg)
	{
		
		errorFile = fopen(errorFileName,"a+");
		if(!errorFile)
		{
			cout<<"recordError errorFile open error:"<<errorFileName<<endl;
			return;
		}
		time_t t = time(NULL);
		char *ctme = ctime(&t);
		cout<<"ctme:"<<ctme<<endl;	
		char errMsg[1000] = {'\0'};
		strncpy(errMsg,ctme,strlen(ctme));
		strncat(errMsg,":  ",strlen(":  "));
		strncat(errMsg,errorMsg,strlen(errorMsg));
		fprintf(errorFile,"%s",errMsg);
		fprintf(errorFile,"\n");
		fclose(errorFile);
	}
	
	
	
	private:
	
	Log(const Log& log)
	{
	}
	
	
	Log& operator=(const Log& log)
	{
		return *this;
	}
	
	
	
};

#endif
	
	
