#include "stdafx.h"
#include "NameCheckMgr.h"
#include "Encode.h"

CNameChecker CNameCheckMgr::_oNameChecker;

bool CNameCheckMgr::Init()
{
    string strPath = Config._strConfigDir + "Conf/Misc/pingbizhiku.xml";
    if(!_oNameChecker.LoadFile(strPath))
    {
        LOG_CRI << "_oNameChecker.LoadFile fails! Path: " << strPath;
        return false;
    }
    return true;
}

ENameLenRes CNameCheckMgr::CheckNameLength(const string& strName, UINT32 dwMinLen, UINT32 dwMaxLen)
{
    assert(dwMinLen < dwMaxLen);
    UINT32 dwLength = 0;
    wstring wstrName = UTF8ToUTF16(strName);
    for(wchar_t c : wstrName)
    {
        if(isascii(c))
            dwLength += 1;
        else
            dwLength += 2;
    }
    if(dwLength < dwMinLen)
        return eNameLenTooShort;
    if(dwLength > dwMaxLen)
        return eNameLenTooLong;
    return eNameSuc;
}

ENameLenRes  CNameCheckMgr::CheckNameValid(string& strName,UINT32 dwMinLen, UINT32 dwMaxLen)
{
    trimName(strName);
    ENameLenRes eNameCheck = CheckNameLength(strName,dwMinLen,dwMaxLen);
    if(eNameCheck != eNameSuc)
    {
        return eNameCheck;
    }
    if(!_oNameChecker.CheckName(strName))
    {
        return eNameValid;
    }
    return eNameCheck;
}
int CNameCheckMgr::char_type(UINT8 p)
{
    if(p < 0x20) return -1;
    if(p >= 0xFE) return -1;
    if(p >= 0xFC) return 6;
    if(p >= 0xF8) return 5;
    if(p >= 0xF0) return 4;
    if(p >= 0xE0) return 3;
    if(p >= 0xC0) return 2;
    if(p >= 0x80) return -1;
    return 1;
}
void CNameCheckMgr::trimName(std::string& str)
{
    size_t len = str.length();
    size_t i = 0;
    while(i < len)
    {
        if(str[i] >= 0 && str[i] <= ' ')
            ++ i;
        else if(i + 2 < len && static_cast<UINT8>(str[i]) == 0xE3 && static_cast<UINT8>(str[i + 1]) == 0x80 && static_cast<UINT8>(str[i + 2]) == 0x80)
            i += 3;
        else
            break;
    }
    size_t j = len;
    while(j > 0)
    {
        if(str[j - 1] >= 0 && str[j - 1] <= ' ')
            -- j;
        else if(j > 2 && static_cast<UINT8>(str[j - 3]) == 0xE3 && static_cast<UINT8>(str[j - 2]) == 0x80 && static_cast<UINT8>(str[j - 1]) == 0x80)
            j -= 3;
        else
            break;
    }
    if(i < j)
        str = std::string(str.begin() + i, str.begin() + j);
    else
        str.clear();
    len = str.length();
    i = 0;
    while(i < len)
    {
        int cur = char_type(str[i]);
        if(cur < 0)
        {
            str.erase(str.begin() + i);
            -- len;
        }
        else
            i += static_cast<size_t>(cur);
    }
    if(i > len)
        str.clear();
}
