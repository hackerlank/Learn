/********************************************************************
    创建时间：    2015/08/06  10:22:21 
    文件名：      DefineBase.h
    作者：        xxj
    
    功能:		1.用于基础数据定义
				2.
                
    说明:		1. 
                2. 
*********************************************************************/
#ifndef _DEFINEBASE_H_
#define _DEFINEBASE_H_


typedef unsigned int MY_UINT32;

//#define ZeroVar(p) ZeroMemory( &p, sizeof( p ) )


#define MAX_TIME_OUT_DIDA 30	//最大超时时间（秒） 间隔时间
#define MAX_TIME_OUT_LOGIN 20	//最大超时时间（秒） 登录阶段
#define MAX_IO_THREAD 0		//最大网络io处理数
#define MAX_SEND_COUNT 10 //最大发送包数量
#endif

