/********************************************************************
 //	Server Utility Library Source File.
 //	File name:	NamePipe.cpp
 //	Created:	2012/08/23	11:00
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

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include "NamePipe.h"
#include "Directory.h"

CNamePipe::CNamePipe(bool bAutoClose /*= false*/) :	_fdPipe(0), _bAutoClose(bAutoClose) { }

CNamePipe::~CNamePipe()
{
	if(_bAutoClose)
		Close();
}

bool CNamePipe::Init(const string& strDir, const string& strName, bool bMake)
{
	if(!CreateDirectory(strDir))
		return false;
	_strPath = strDir + "/" + strName;
	if(!bMake)
		return true;
	umask(0);
	if(mkfifo(_strPath.c_str(), S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
		return false;
	return true;
}

void CNamePipe::Close()
{
	if(_fdPipe > 0)
		close(_fdPipe);
	unlink(_strPath.c_str());
}

bool CNamePipe::OpenForRead(bool bNonBlock /*= false*/)
{
	int flags = O_RDONLY;
	if(bNonBlock)
		flags |= O_NONBLOCK;
	_fdPipe = open(_strPath.c_str(), flags);
	if(_fdPipe < 0)
		return false;
	return true;
}

bool CNamePipe::OpenForWrite(bool bNonBlock /*= false*/)
{
	int flags = O_WRONLY;
	if(bNonBlock)
		flags |= O_NONBLOCK;
	_fdPipe = open(_strPath.c_str(), flags);
	if(_fdPipe < 0)
		return false;
	return true;
}

bool CNamePipe::OpenForWait()
{
	_fdPipe = open(_strPath.c_str(), O_RDONLY);
	if(_fdPipe == -1)
		return false;

	int fdDummy = open(_strPath.c_str(), O_WRONLY);
	if(fdDummy == -1)
		return false;

	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return false;

	return true;
}

bool CNamePipe::Read(EReqType& eReqType, int& pid, string& strData)
{
    static string strBuff;
	eReqType = eReqNone;
	int type = 0;
	int rc = read(_fdPipe, &type, sizeof(int));
	if(rc < (int) sizeof(int))
		return false;
	eReqType = (EReqType) type;
	rc = read(_fdPipe, &pid, sizeof(int));
	if(rc < (int) sizeof(int))
		return false;
	int size = 0;
	rc = read(_fdPipe, &size, sizeof(int));
	if(rc < (int) sizeof(int))
		return false;
    strBuff.resize(size + 1);
	rc = read(_fdPipe, &(strBuff[0]), size);
	if(rc < size)
		return false;
	strData.assign(strBuff.c_str(), size);
	return true;
}

bool CNamePipe::Write(EReqType eReqType, const string& strData)
{
    static int* p = NULL;
    p = (int*)malloc (sizeof(int) * 3 + strData.size());
    if (!p)
        return false;
	int type = eReqType;
    p[0] = type;
	int pid = getpid();
    p[1] = pid;
    int size = strData.size();
    p[2] = size;
    memcpy(p + 3, strData.c_str(), strData.size());
	if(write(_fdPipe, p, sizeof(int)* 3 + strData.size()) < 0)
    {
        free(p);
        p = NULL;
		return false;
    }
    free(p);
    p = NULL;
	return true;
}
