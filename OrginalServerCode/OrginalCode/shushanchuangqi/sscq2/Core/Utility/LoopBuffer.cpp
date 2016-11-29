/********************************************************************
//	Server Network Library Source File.
//	File name:	Buffer.cpp
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

#include <memory.h>
#include "LoopBuffer.h"
#include "Platform.h"

CLoopBuffer::CLoopBuffer() : _pBuf(NULL), _pEnd(NULL), _pRead(NULL), _pWrite(NULL)
{
	memset(_arBuf, 0, sizeof _arBuf);
}

CLoopBuffer::~CLoopBuffer()
{
	ReleaseBuffer();
}

bool CLoopBuffer::AllocBuffer(int size)
{
#ifdef _WIN32
	_pBuf = (char*)VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE);
	static_assert(sizeof(SBuffer) == sizeof(WSABUF), "SBuffer and WSABUF should have same size!");
#else
	_pBuf = (char*)malloc(size);
	static_assert(sizeof(SBuffer) == sizeof(iovec), "SBuffer and iovec should have same size!");
#endif
	if(_pBuf == NULL)
		return false;
	_pEnd = _pBuf + size;
	_pRead = _pBuf;
	_pWrite = _pBuf;
	return true;
}

void CLoopBuffer::ReleaseBuffer()
{
#ifdef _WIN32
	VirtualFree(_pBuf, 0, MEM_RELEASE);
#else
	free(_pBuf);
#endif
	_pBuf = _pEnd = _pRead = _pWrite = NULL;
}

bool CLoopBuffer::Write(const char* pData, int len)
{
	if(pData == NULL || len == 0)
		return true;

	char* pRead = _pRead;
	if(_pWrite < pRead)
	{
		if(_pWrite + len >= pRead)
			return false;
		memcpy(_pWrite, pData, len);
		_pWrite += len;
	}
	else if(_pWrite + len <= _pEnd)
	{
		memcpy(_pWrite, pData, len);
		_pWrite += len;
	}
	else if(_pBuf + len - (_pEnd - _pWrite) >= pRead)
	{
		return false;
	}
	else
	{
		size_t len1 = _pEnd - _pWrite;
		memcpy(_pWrite, pData, len1);
		size_t len2 = len - len1;
		memcpy(_pBuf, pData + len1, len2);
		_pWrite = _pBuf + len2;
	}
	return true;
}

bool CLoopBuffer::Read(char* pData, int len, bool bPeek)
{
	if(pData == NULL || len == 0)
		return true;

	char* pWrite = _pWrite;
	if(_pRead <= pWrite)
	{
		if(_pRead + len > pWrite)
			return false;
		memcpy(pData, _pRead, len);
		if(!bPeek)
			_pRead += len;
	}
	else if(_pRead + len <= _pEnd)
	{
		memcpy(pData, _pRead, len);
		if(!bPeek)
			_pRead += len;
	}
	else if(_pBuf + len - (_pEnd - _pRead) > pWrite)
	{
		return false;
	}
	else
	{
		int len1 = int(_pEnd - _pRead);
		memcpy(pData, _pRead, len1);
		int len2 = len - len1;
		memcpy(pData + len1, _pBuf, len2);
		if(!bPeek)
			_pRead = _pBuf + len2;
	}
	return true;
}

char* CLoopBuffer::PeekWithOutLoop(int len)
{
	char* pWrite = _pWrite;
	if(_pRead <= pWrite)
	{
		if(_pRead + len > pWrite)
			return NULL;
	}
	else if(_pRead + len > _pEnd)
	{
		return NULL;
	}
	return _pRead;
}

bool CLoopBuffer::WriteForward(int len)
{
	char* pRead = _pRead;
	if(_pWrite < pRead)
	{
		if(_pWrite + len >= pRead)
			return false;
		_pWrite += len;
	}
	else if(_pWrite + len <= _pEnd )
		_pWrite += len;
	else if(_pBuf + len - (_pEnd - _pWrite) >= pRead)
		return false;
	else
		_pWrite =  _pWrite - (_pEnd - _pBuf) + len;
	return true;
}

bool CLoopBuffer::ReadForward(int len)
{
	char* pWrite = _pWrite;
	if(_pRead <= pWrite)
	{
		if(_pRead + len > pWrite)
			return false;
		_pRead += len;
	}
	else if(_pRead + len <= _pEnd)
		_pRead += len;
	else if(_pBuf + len - (_pEnd - _pRead) > pWrite)
		return false;
	else
		_pRead = _pBuf + (_pRead+ len - _pEnd);
	return true;
}

bool CLoopBuffer::GetReadVecBuf(SBuffer*& pBuf, int& count, int len)
{
	char* pWrite = _pWrite;
	pBuf = _arBuf;
	count = 0;
	if(_pRead < pWrite)
	{
		if(pWrite - _pRead < len)
		{
			memset(_arBuf, 0, sizeof _arBuf);
			return false;
		}
		_arBuf[0].buf = _pRead;
		_arBuf[0].len = len;
		_arBuf[1].buf = NULL;
		_arBuf[1].len = 0;
		count = 1;
		return true;
	}
	if(_pRead > pWrite)
	{
		if(_pEnd - _pRead + pWrite - _pBuf < len)
		{
			memset(_arBuf, 0, sizeof _arBuf);
			return false;
		}
		_arBuf[0].buf = _pRead;
		if(_pEnd - _pRead >= len)
		{
			_arBuf[0].len = len;
			_arBuf[1].buf = NULL;
			_arBuf[1].len = 0;
			count = 1;
		}
		else
		{
			_arBuf[0].len = TBufLen(_pEnd - _pRead);
			_arBuf[1].buf = _pBuf;
			_arBuf[1].len = len - _arBuf[0].len;
			count = 2;
		}
		return true;
	}
	memset(_arBuf, 0, sizeof _arBuf);
	return false;
}

bool CLoopBuffer::GetWriteVecBuf(SBuffer*& pBuf, int& count)
{
	char* pRead = _pRead;
	pBuf = _arBuf;
	count = 0;
	if(_pWrite < pRead)
	{
		if(pRead - _pWrite == 1)
		{
			memset(_arBuf, 0, sizeof _arBuf);
			return false;
		}
		_arBuf[0].buf = _pWrite;
		_arBuf[0].len = TBufLen(pRead - _pWrite);
		_arBuf[1].buf = NULL;
		_arBuf[1].len = 0;
		count = 1;
	}
	else
	{
		_arBuf[0].buf = _pWrite;
		_arBuf[0].len = TBufLen(_pEnd - _pWrite);
		if(pRead == _pBuf)
		{
			_arBuf[1].buf = NULL;
			_arBuf[1].len = 0;
			count = 1;
		}
		else
		{
			_arBuf[1].buf = _pBuf;
			_arBuf[1].len = TBufLen(pRead - _pBuf);
			count = 2;
		}
	}
	return true;
}

int  CLoopBuffer::GetFreeSize()
{
    char* pRead = _pRead;
	if(_pWrite < pRead)
	{
		return pRead - _pWrite;
	}
    return _pEnd - _pWrite + _pRead - _pBuf > 0 ? _pEnd - _pWrite + _pRead - _pBuf : 0;
}
