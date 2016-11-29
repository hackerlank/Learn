/********************************************************************
//	Server Network Library Source File.
//	File name:	Buffer.h
//	Created:	2012/08/20	11:00
//	Organization:	
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:	
//	Version:	1.0
//	Histroy:
*********************************************************************/
#pragma once
#ifdef _WIN32
#include <Winsock2.h>
#include <Windows.h>
#else
#include <sys/uio.h>
#endif

//跨平台通用Buffer定义(Windows对应WSABUF, Linux对应iovec)
struct SBuffer
{
#ifdef _WIN32
	ULONG len;
	CHAR* buf;
#else
	void* buf;
	size_t len;
#endif
};

typedef decltype(((SBuffer*)nullptr)->len) TBufLen;

//循环缓冲区
class CLoopBuffer
{
public:
	CLoopBuffer();
	~CLoopBuffer();
	bool AllocBuffer(int size);
	void ReleaseBuffer();
	bool Write(const char* pData, int len);
	bool Read(char* pData, int len, bool bPeek = false);
	char* PeekWithOutLoop(int len);
	char* GetData() { return _pBuf; }
	int GetSize() const { return int(_pEnd - _pBuf); }
	bool WriteForward(int len);
	bool ReadForward(int len);
	bool GetReadVecBuf(SBuffer*& pBuf, int& count, int len);
	bool GetWriteVecBuf(SBuffer*& pBuf, int& count);
    int  GetFreeSize() ;

protected:
	char* _pBuf;
	char* _pEnd;
	char* _pRead;
	char* _pWrite;

	SBuffer _arBuf[2]; //循环缓冲区对应的Buffer数组(用于Windows的WSASend, WSARecv, 以及Linux的writev, readv)
};
