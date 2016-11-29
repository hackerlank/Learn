#pragma once
#include "NameCheck.h"

enum ENameLenRes
{
    eNameSuc,
	eNameLenTooShort,
	eNameLenTooLong,
    eNameValid,
};

class CNameCheckMgr
{
public:
	static bool Init();
	static ENameLenRes CheckNameLength(const string& strName, UINT32 dwMinLen, UINT32 dwMaxLen);
	static ENameLenRes CheckNameValid(string& strName,UINT32 dwMinLen, UINT32 dwMaxLen);
    static int char_type(UINT8 p);  
    static void trimName(std::string& str);

private:
	static CNameChecker _oNameChecker;
};
