/********************************************************************
//	Server Utility Library Source File.
//	File name:	Directory.h
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

#pragma once
#include <string>
#include <time.h>

using std::string;

bool GetCurDirectory(string& strCurDir, bool bAbsolute = true);

bool GetCurFileName(string& strFile);

bool CreateDirectory(const string& strDir);

bool GetFileTime(const string& strFile, tm& rTime);

bool FileExists(const string& strFile);
