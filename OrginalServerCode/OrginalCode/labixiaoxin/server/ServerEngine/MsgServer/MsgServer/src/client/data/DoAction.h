/********************************************************************
创建时间：    2015/07/15  10:35:16 
文件名：      DoAction.h
作者：        xxj

功能:		1.具体逻辑
2.

说明:		1. 
2. 
*********************************************************************/
#ifndef _DOACTION_H_
#define _DOACTION_H_
#include <string>

#define ZeroVar(p) ZeroMemory( &p, sizeof( p ) )

typedef struct tagBitfield
{
	int stop:1;
	int start:1;
}Bitfield;

class CDoAction
{
public:
	void OnMessage(std::string & str);
	bool OnDealMsg(int tag);
private:
	int KillProcess(const char * pszClassName,const char * pszWindowTitle); 
	int CreateNewProcess(const char * pszExeName);  
};
#endif