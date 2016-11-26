/************************************************************
	文件名：asistFun.h
	文件作用：辅助函数申明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#ifndef ASIST_FUN_H
#define ASIST_FUN_H

#include"numStr.h"

/*字符串为空错误*/
const int ERROR_EMPTY = 1;

/*字符串含有非数字字符错误*/
const int ERROR_DIGST = 2;

/*字符串含有非数字字符错误*/
const int ERROR_OTHRE = 3;



/*重载乘号*/
const NumStr operator* (const NumStr& numStrF,const NumStr& numStrS);

/*计算阶层函数*/
void loopFor(NumStr& numStr);

/*重载大于等于号*/
bool operator >= (const NumStr &numStrL,const NumStr &numStrR);

/*重载小于号*/
bool operator < (const NumStr &numStrL,const NumStr &numStrR);

/*错误处理函数*/
void errorDealFun(int errorType);

#endif
	
