/******************************************
	文件类型：头文件
	
	文件名称：bootAssignment.h
	
	文件作用：服务器开机调用初始化全局变量值
*******************************************/
#ifndef BOOT_ASSIGNMENT_H
#define BOOT_ASSIGNMENT_H


#define MAX_REGISTER_SIZE 500000

typedef struct nickNameCheck_S{
	char nickName[MAX_REGISTER_SIZE][32];
	char HeroId[MAX_REGISTER_SIZE][38];
}NickNameCheck_T;

void nickNameCheckValueBootInit();

void saveNickNameCheckValue2Mem();

void updataNickNameCheckValue();

void saveDeleteNickNameValue();

#endif

