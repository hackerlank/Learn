/********************************************************************
//	Server Utility Library Source File.
//	File name:	Log.h
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

#pragma once
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ObjPool.h"
#include "Platform.h"
#include "Lock.h"
#include "LockFree.h"
#include "Interface.h"
#include "ObjPool.h"
#include "Thread.h"

enum ELogLevel
{
	eLogLevelCritical = 0,
	eLogLevelWarning,
	eLogLevelInfo,
	eLogLevelDebug,
	eLogLevelDummy,
	eLogLevelCount
};

struct SLogInfo
{
	std::string strText;
	ELogLevel eLevel;
	const char* szFunc;
	int line;
    const char* szFile;
	time_t tTime;
	bool bNewLine;
	bool bConsole;
	bool bFlush;

	SLogInfo() : eLevel(eLogLevelDummy), szFunc(NULL), line(0), szFile(NULL), tTime(0),
		bNewLine(false), bConsole(false), bFlush(false){ }

	DEF_NEW_DELETE_MT_WRAP(SLogInfo)
};

class CLog;

//一条日志
class CLogObj
{
	friend class CLog;
public:
	enum ELogControl
	{
		eLogNone,
		eLogNoNewLine,
		eLogNoConsole,
		eLogFlush
	};

	CLogObj(CLog& rLog, ELogLevel eLevel = eLogLevelDummy, 
            const char* szFunc = NULL, int line = 0, const char* szFile = NULL);
	~CLogObj();

	template<typename T>
	CLogObj& operator<<(const T& val)
	{
		_ostr << val;
		return *this;
	}

	CLogObj& operator<<(INT8 byVal)
	{
		_ostr << (int)byVal;
		return *this;
	}

	CLogObj& operator<<(UINT8 byVal)
	{
		_ostr << (int)byVal;
		return *this;
	}

	CLogObj& operator<<(const ELogControl& eLogControl)
	{
		switch(eLogControl)
		{
		case eLogNoNewLine:
			_bNewLine = false;
			break;
		case eLogNoConsole:
			_bConsole = false;
			break;
		case eLogFlush:
			_bFlush = true;
			break;
		default:
			break;
		}
		return *this;
	}

protected:
	CLog& _rLog;
	ELogLevel _eLevel;
	const char* _szFunc;
    const char* _szFile;
	int _line;
	bool _bNewLine;
	bool _bConsole;
	bool _bFlush;
	std::ostringstream _ostr;
};

//多线程日志
class CLog
{
	friend class CLogObj;
public:
	CLog();
	~CLog();
	void SetAutoFlush(bool bSupport) { _bAutoFlush = bSupport; }
	std::ofstream& GetStream() { return _ofs; }
	void PushLog(SLogInfo& rLogInfo);
    void PushLogL(const char* msg, int level, const char* func, 
            int line, bool newline = false, bool console = false, bool flash = false);
	bool OpenLog(const std::string& strFile);
	bool OpenLog(const std::string& strPath, const std::string& strPrefix);
	bool GetNewFileName(std::string& strFileName);
	void SetSvrID(UINT32 dwSvrID);
	bool IsConsoleOpen() const { return _bOpenConsole; }
	void OpenConsole();

	bool Start();
	void Stop();
	void Flush();
    void GetServerStr(string & str);

private:
	void WriteLog(SLogInfo& rLogInfo);
	static void LogThread(CLog* pThis);

	std::ofstream _ofs;
	bool _bDir;
	bool _bAutoFlush;
	tm _tmTime;
	char _szbuf[0x100];
	bool _bOpenConsole;
	EHostType _eHostType;
	UINT8 _byIndex;

	std::string _strPath;
	std::string _strCurFileName;
	std::string _strPrefix;

	bool _bRun;
	CLockFreeQueue<SLogInfo*> _queLog;
	CThread _thread;

#ifdef _WIN32
	HANDLE _hOutputHandle;
#endif // _WIN32
};

class CNulLog
{
public:
	template<typename T>
	CNulLog& operator<<(const T& val)
	{
		return *this;
	}
	static CNulLog _sNulLog;
};


