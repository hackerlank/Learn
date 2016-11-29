/********************************************************************
//	Server Utility Library Source File.
//	File name:	Log.cpp
//	Created:	2012/08/21	11:00
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

#ifdef _WIN32
#include <process.h>
#include <io.h>
#endif
#include <fcntl.h>
#include <stdio.h>
#include "Log.h"
#include "ServerID.h"

CNulLog CNulLog::_sNulLog;

CLogObj::CLogObj(CLog& rLog, ELogLevel eLevel, const char* szFunc, int line,const char* szFile) :
    _rLog(rLog), _eLevel(eLevel), _szFunc(szFunc),_szFile(szFile), _line(line), _bNewLine(true), _bConsole(true), _bFlush(false)
{
#ifdef _DEBUG
     _bConsole = true;
#else
     if(eLevel <= eLogLevelWarning)
    {
        _bConsole = true;
    }
    else
    {
        _bConsole = false;
    }
#endif
}


CLogObj::~CLogObj()
{
    SLogInfo* pLogInfo = new SLogInfo;
    pLogInfo->strText = move(_ostr.str());
    pLogInfo->eLevel = _eLevel;
    pLogInfo->szFunc = _szFunc?strdup(_szFunc):NULL;
    pLogInfo->line = _line;
    pLogInfo->tTime = time(NULL);
    pLogInfo->bNewLine = _bNewLine;
    pLogInfo->bConsole = _bConsole;
    pLogInfo->bFlush = _bFlush;
    pLogInfo->szFile = _szFile?strdup(_szFile):NULL;
    _rLog.PushLog(*pLogInfo);
}

///////////////////////////////////////////////////////////////////////////////////////////////

CLog::CLog() : _bDir(false), _bAutoFlush(false), _bOpenConsole(false),
    _eHostType(eHostNone), _byIndex(0), _bRun(false)
#ifdef _WIN32
               , _hOutputHandle(INVALID_HANDLE_VALUE)
#endif // _WIN32
{
    memset(&_tmTime, 0, sizeof _tmTime);
    memset(_szbuf, 0, sizeof _szbuf);
}

CLog::~CLog()
{
    deque<SLogInfo*> deqLogInfo;
    _queLog.PopAll(deqLogInfo);
    for(SLogInfo* pLogInfo : deqLogInfo)
        delete pLogInfo;
    Stop();
    _bDir = false;
}

void CLog::PushLog(SLogInfo& rLogInfo)
{
    if(_bRun)
        _queLog.Push(&rLogInfo);
    else
        delete &rLogInfo;
}

void CLog::PushLogL(const char* msg, int level, const char* func, int line, bool newline, bool console, bool flash)
{
    SLogInfo* pLogInfo = new SLogInfo;
    pLogInfo->strText = msg;
    pLogInfo->eLevel = (ELogLevel)level;
    pLogInfo->szFunc = func?strdup(func):NULL;
    pLogInfo->line = line;
    pLogInfo->tTime = time(NULL);
    pLogInfo->bNewLine = newline;
#ifdef _DEBUG
     pLogInfo->bConsole = true;
#else
     if(pLogInfo->eLevel <= eLogLevelWarning)
    {
        pLogInfo->bConsole = true;
    }
    else
    {
        pLogInfo->bConsole = false;
    }
#endif
    pLogInfo->bFlush = flash;

    PushLog(*pLogInfo);
}

bool CLog::OpenLog(const std::string& strFile)
{
    _strPath = strFile;
    _ofs.open(strFile, std::ios_base::app);
    if(_ofs.bad())
        return false;
    return true;
}

bool CLog::OpenLog(const std::string& strPath, const std::string& strPrefix)
{
    _bDir = true;
    _strPath = strPath;
    _strPrefix = strPrefix;
    return true;
}

bool CLog::GetNewFileName(std::string& strFileName)
{
    if(!_bDir)
        return false;
    time_t tNow = time(NULL);
    tm tmNow;
    localtime_s(&tmNow, &tNow);
    if(!strFileName.empty() && tmNow.tm_year == _tmTime.tm_year && tmNow.tm_mon == _tmTime.tm_mon
            && tmNow.tm_mday == _tmTime.tm_mday)
        return false;
    _tmTime = tmNow;
    int offset = sprintf_s(_szbuf, "/%s_%u-%02u-%02u.log", _strPrefix.c_str(), tmNow.tm_year - 100, tmNow.tm_mon + 1, tmNow.tm_mday);
    if(offset < 0)
        return false;
    strFileName = _strPath + _szbuf;
    return true;
}

void CLog::SetSvrID(UINT32 dwSvrID)
{
    _eHostType = GetServerType(dwSvrID);
    _byIndex = GetServerIndex(dwSvrID);
}

void CLog::OpenConsole()
{
#ifdef _WIN32
    SHORT ConsoleHeight = 400;
    SHORT ConsoleWidth  = 600;
    AllocConsole();
    HANDLE hStd = NULL;
    int fd = 0;
    FILE* file = NULL;

    // 重定向标准输入流句柄到新的控制台窗口
    hStd = GetStdHandle(STD_INPUT_HANDLE);
    fd = _open_osfhandle(reinterpret_cast<intptr_t>(hStd), _O_TEXT); // 文本模式
    file = _fdopen(fd, "r");
    setvbuf(file, NULL, _IONBF, 0); // 无缓冲
    *stdin = *file;

    // 重定向标准输出流句柄到新的控制台窗口
    hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size;
    size.X = ConsoleWidth;
    size.Y = ConsoleHeight;
    SetConsoleScreenBufferSize(hStd, size);
    fd = _open_osfhandle(reinterpret_cast<intptr_t>(hStd), _O_TEXT); //文本模式
    file = _fdopen(fd, "w");
    setvbuf(file, NULL, _IONBF, 0); // 无缓冲
    *stdout = *file;
    _hOutputHandle = hStd; // backup

    // 重定向标准错误流句柄到新的控制台窗口
    hStd = GetStdHandle(STD_ERROR_HANDLE);
    fd = _open_osfhandle(reinterpret_cast<intptr_t>(hStd), _O_TEXT); // 文本模式
    file = _fdopen(fd, "w");
    setvbuf(file, NULL, _IONBF, 0); // 无缓冲
    *stderr = *file;
#endif

    _bOpenConsole = true;
}

bool CLog::Start()
{
    _bRun = true;
    if(!_thread.Start(LogThread, this))
        return false;
    return true;
}

void CLog::Stop()
{
    if(_bRun)
    {
        _bRun = false;
        _thread.Join();
        _ofs.close();
    }
}

void CLog::Flush()
{
    _ofs.flush();
}

#ifdef _WIN32

static WORD sLevelColor[eLogLevelCount] = 
{ 
    FOREGROUND_INTENSITY | FOREGROUND_RED, // red
    FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN, // yellow
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, // white
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, // white
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, // white
};

void SetConsoleColor(HANDLE& hOutputHandle, ELogLevel eLevel)
{
    assert(eLevel >= eLogLevelCritical && eLevel < eLogLevelCount);

    if (hOutputHandle == INVALID_HANDLE_VALUE)
        return;

    SetConsoleTextAttribute(hOutputHandle, sLevelColor[eLevel]);
}

#endif // _WIN32

#ifdef __GNUG__

static const char* LevelColorPrefix[eLogLevelCount] =
{
    "\033[31;1m",
    "\033[36;1m",
    "\033[0m",
    "\033[0m",
    "\033[0m"
};

static const char* LevelColorSuffix = "\033[0m";

#endif // __GNUG__

const char* LevelName[eLogLevelCount] = { "CRI", "WRN", "INF", "DBG", "" };

void CLog::WriteLog(SLogInfo& rLogInfo)
{
    if(_bDir && GetNewFileName(_strCurFileName))
    {
        _ofs.close();
        _ofs.clear();
        _ofs.open(_strCurFileName.c_str(), std::ios_base::app);
        if(_ofs.bad())
            throw "Bad File!";
    }
    tm tmNow;
    localtime_s(&tmNow, &rLogInfo.tTime);

    if(rLogInfo.szFunc != NULL)
    {
        sprintf_s(_szbuf, "[%02u:%02u:%02u][%s][%s:%s:%u] ", tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec,
                LevelName[rLogInfo.eLevel],rLogInfo.szFile, rLogInfo.szFunc, rLogInfo.line);
        _ofs << _szbuf;
        free((void*)rLogInfo.szFunc); 
        free((void*)rLogInfo.szFile); 
        rLogInfo.szFunc = NULL;
    }
    /*
       else if(rLogInfo.eLevel == eLogLevelDummy)
       {
       sprintf_s(_szbuf, "[%02u:%02u:%02u][%s] ", tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec, LevelName[rLogInfo.eLevel]);
       _ofs << _szbuf;
       }
       */
    else
    {
        _szbuf[0] = '\0';
    }
    if(_bOpenConsole && rLogInfo.bConsole)
    {
#ifdef _WIN32
        SetConsoleColor(_hOutputHandle, rLogInfo.eLevel);
#endif // _WIN32

#ifdef __GNUG__
        std::cout << LevelColorPrefix[rLogInfo.eLevel];
        string str;
        GetServerStr(str);
#if 0
        switch(_eHostType)
        {
            case eHostGate:
                sprintf_s(szBuf, "[Gate%u ]", _byIndex);
                pServer = szBuf;
                break;
            case eHostLogin:
                pServer = "[Login ]";
                break;
            case eHostCenter:
                pServer = "[Center]";
                break;
            case eHostGame:
                sprintf_s(szBuf, "[Game%u ]", _byIndex);
                pServer = szBuf;
                break;
            case eHostDB:
                pServer = "[DB    ]";
                break;
            case eHostLog:
                pServer = "[Log   ]";
                break;
            default:
                break;
        }
 #endif
        if(!str.empty())
            std::cout << str;
#endif // __GNUG__
        std::cout << _szbuf;
    }
    _ofs << rLogInfo.strText;
    //test begin
    _ofs << "  from " ;
    string strSer;
    GetServerStr(strSer);
    if(!strSer.empty())
        _ofs << strSer;
    _ofs << ":Line " << _strPrefix;
    //test end

    if(_bOpenConsole && rLogInfo.bConsole)
    {
        std::cout << rLogInfo.strText;

#ifdef __GNUG__
        std::cout << LevelColorSuffix;
#endif //__GNUG__
    }

    if(rLogInfo.bNewLine)
    {
        _ofs << std::endl;
        if(_bOpenConsole && rLogInfo.bConsole)
            std::cout << std::endl;
    }
    if(_bAutoFlush || rLogInfo.bFlush)
        _ofs.flush();
}
 void CLog::GetServerStr(string & str)
{
        char szBuf[0x10];
        
        switch(_eHostType)
        {
            case eHostGate:
                sprintf_s(szBuf, "[Gate%u ]", _byIndex);
                str = string(szBuf);
                break;
            case eHostLogin:
                str = "[Login ]";
                break;
            case eHostCenter:
                str = "[Center]";
                break;
            case eHostGame:
                sprintf_s(szBuf, "[Game%u ]", _byIndex);
                str = string(szBuf);
                break;
            case eHostDB:
                str = "[DB    ]";
                break;
            case eHostLog:
                str = "[Log   ]";
                break;
            default:
                break;
        }
}

void CLog::LogThread(CLog* pThis)
{
    CLog& rLog = *pThis;
    deque<SLogInfo*> deqLogInfo;
    while(rLog._bRun || !rLog._queLog.Empty())
    {
        rLog._queLog.PopAll(deqLogInfo);
        if(deqLogInfo.empty())
        {
            Sleep(10);
            continue;
        }
        for(SLogInfo* pLogInfo : deqLogInfo)
        {
            rLog.WriteLog(*pLogInfo);
            delete pLogInfo;
        }
        deqLogInfo.clear();
    }
    rLog.Flush();
}
