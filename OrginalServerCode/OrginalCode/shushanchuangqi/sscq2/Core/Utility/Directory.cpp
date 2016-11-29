/********************************************************************
 //	Server Utility Library Source File.
 //	File name:	Directory.cpp
 //	Created:	2012/08/21	10:00
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

#include <errno.h>
#ifdef _WIN32
#include <Windows.h>
#include <Shlwapi.h>
#include <direct.h>
#define PATH_SEP '\\'
#else
#include <sys/stat.h>
#include "Linux.h"
#define MAX_PATH 260
#define PATH_SEP '/'
#endif
#include "Directory.h"

bool GetCurDirectory(string& strCurDir, bool bAbsolute /*= true*/)
{
	char buf[MAX_PATH];
#ifdef _WIN32
	if(GetModuleFileName(NULL, buf, MAX_PATH) == 0)
		return false;
#else
	int rc = readlink("/proc/self/exe", buf, sizeof(buf));
	if(rc < 0)
		return false;
	buf[rc] = '\0';
#endif
	string strDir = buf;
	size_t pos = strDir.find_last_of(PATH_SEP);
	if(bAbsolute)
	{
		strCurDir = strDir.substr(0, pos + 1);
	}
	else
	{
		strCurDir = strDir.substr(0, pos);
		pos = strCurDir.find_last_of(PATH_SEP);
		strCurDir = strCurDir.substr(pos + 1);
	}
	return true;
}

bool GetCurFileName(string& strFileName)
{
	char buf[MAX_PATH];
#ifdef _WIN32
	if(GetModuleFileName(NULL, buf, MAX_PATH) == 0)
		return false;
#else
	int rc = readlink("/proc/self/exe", buf, sizeof(buf));
	if(rc < 0)
		return false;
	buf[rc] = '\0';
#endif
	string strFile = buf;
	size_t pos = strFile.find_last_of(PATH_SEP);
    strFileName = strFile.substr(pos);
	return true;
}
bool CreateDirectory(const string& strDir)
{
	size_t pos = 2;
	while(true)
	{
		pos = strDir.find_first_of("\\/", pos + 1);
		string strPath = strDir.substr(0, pos);
#ifdef _WIN32
		if(_mkdir(strPath.c_str()) != 0 && errno == ENOENT)
#else
		if(mkdir(strPath.c_str(), 0775) != 0 && errno != EEXIST)
#endif
			return false;
		if(pos == string::npos)
			break;
	}
	return true;
}

bool GetFileTime(const string& strFile, tm& rTime)
{
#ifdef _WIN32
	HANDLE hFile = CreateFile(strFile.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return false;
	FILETIME oLastWriteTime;
	if(!::GetFileTime(hFile, NULL, NULL, &oLastWriteTime))
		return false;
	CloseHandle(hFile);
	SYSTEMTIME oSystemTime, oLocalTime;
	if(!FileTimeToSystemTime(&oLastWriteTime, &oSystemTime))
		return false;
	if(!SystemTimeToTzSpecificLocalTime(NULL, &oSystemTime, &oLocalTime))
		return false;
	rTime.tm_year = oLocalTime.wYear - 1900;
	rTime.tm_mon = oLocalTime.wMonth - 1;
	rTime.tm_mday = oLocalTime.wDay;
	rTime.tm_hour = oLocalTime.wHour;
	rTime.tm_min = oLocalTime.wMinute;
	rTime.tm_sec = oLocalTime.wSecond;
#else
	struct stat oStat;
	if(stat(strFile.c_str(), &oStat) < 0)
		return false;
	if(localtime_r(&oStat.st_mtime, &rTime) == NULL)
		return false;
#endif
	return true;
}

bool FileExists(const string& strFile)
{
#ifdef __GENPROTOCOL
#else
#ifdef _WIN32
	if(PathFileExists(strFile.c_str()))
#else
	if(access(strFile.c_str(), F_OK) == 0)
#endif
#endif
		return true;
	return false;
}
