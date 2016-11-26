/*
created	 :	  2012/7/10  17:24
fileName :    log.cpp
author :      xhm
purpose :     To achieve the flie log.h
*/

#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "log.h"

#define _MAXLEN 256
#define MAX_DEBUG 2048

static FILE *error_log_fp,*debug_log_fp;//error_log_fp:error.out debug_log_fp:log.out

/*
read the config information;
*/
void 
Log::Read_log_conf()
{
;
}

/*
you can use the function to make a directory for log information;
*/
int
Log::Attempt2createdir()
{
char DirName[_MAXLEN]={0}; 
char LogFile[_MAXLEN]={0}; 
char ErrorFile[_MAXLEN]={0};
getcwd(DirName,sizeof(DirName));
strcat(DirName,"/temp");

if(access(DirName,6)!=0)  
  {  
      if(mkdir(DirName,0777)==-1)  
      {   
        perror("mkdir logdir  error\n");   
        return   -1;   
      }  
  } 
sprintf(LogFile,"%s/log.out",DirName);
sprintf(ErrorFile,"%s/error.out",DirName);

error_log_fp=fopen(ErrorFile,"a+");
if(NULL == error_log_fp)
  error_log_fp = stderr;
debug_log_fp=fopen(LogFile,"a+");
if(NULL == debug_log_fp)
  debug_log_fp = stderr;
return 1;
}

/*
fclose the fp;
*/
Log::~Log(){
if(error_log_fp!= NULL && (error_log_fp!=stderr))
  fclose(error_log_fp);
if(debug_log_fp!= NULL && (debug_log_fp!=stderr))
  fclose(debug_log_fp); 
}

/*
To achieve functional Debug;
*/
void 
Log::Debug(const char* str,const char *fmt, ...)
{
    va_list ap;
    char *pos, message[MAX_DEBUG]={0};
    int sz;
    time_t t;

    if (NULL == debug_log_fp) {
        debug_log_fp = stderr;
    }
    /* timestamp */
    t = time(NULL);
    pos = ctime(&t);
    sz = strlen(pos);
    /* chop off the \n */
    pos[sz-1]=' ';

    /* insert the header */
    snprintf(message, MAX_DEBUG, "%s [%s]:", pos,str);

    /* find the end and attach the rest of the msg */
    for (pos = message; *pos != '\0'; pos++); /*empty statement */
    sz = pos - message;
    va_start(ap,fmt);
    vsnprintf(pos, MAX_DEBUG - sz,fmt, ap);
    va_end(ap);
    fprintf(debug_log_fp,"%s", message);
    fprintf(debug_log_fp, "\n");
    fflush(debug_log_fp);
}

/*
To achieve functional Error;
*/
void 
Log::Error(const char *fmt, ...)
{
 va_list ap;
 char *pos, message[MAX_DEBUG]={0};  
 pos=message;
 if(NULL == error_log_fp)
    error_log_fp = stderr;	
  va_start(ap,fmt);
  vsnprintf(pos, MAX_DEBUG,fmt,ap);
  va_end(ap);
  fprintf(error_log_fp,"%s", message);
  fprintf(error_log_fp, "\n");
  fflush(error_log_fp);
}	
