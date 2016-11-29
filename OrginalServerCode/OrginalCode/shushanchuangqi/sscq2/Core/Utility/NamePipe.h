/********************************************************************
 //	Server Utility Library Source File.
 //	File name:	NamePipe.h
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

#pragma once
#include <string.h>
#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits.hpp>

using namespace std;

enum EReqType
{
	eReqNone,
	eReqInfo,
	eReqExit,
	eReqLoad,
	eReqStore,
	eReqClose
};

class CNamePipe
{
public:
	CNamePipe(bool bAutoClose = false);
	~CNamePipe();
	bool Init(const string& strDir, const string& strName, bool bMake = true);
	void Close();
	bool OpenForRead(bool bNonBlock = false);
	bool OpenForWrite(bool bNonBlock = false);
	bool OpenForWait();

	template<typename T>
	bool Read(T& rData);

	template<typename T>
	bool Write(const T& rData);

	bool Read(EReqType& eReqType, int& pid, string& strData);
	bool Write(EReqType eReqType, const string& strData);

protected:
	int _fdPipe;
	string _strPath;
	bool _bAutoClose;
};

template<typename T>
bool CNamePipe::Read(T& rData)
{
	if(read(_fdPipe, &rData, sizeof rData) == sizeof rData)
		return true;
	return false;
}

template<typename T>
bool CNamePipe::Write(const T& rData)
{
	if(write(_fdPipe, &rData, sizeof rData) == sizeof rData)
		return true;
	return false;
}
