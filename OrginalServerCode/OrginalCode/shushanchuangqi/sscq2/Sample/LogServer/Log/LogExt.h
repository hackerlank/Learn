#pragma once

#include <time.h>
#include <string>
#include <fstream>
#include <iostream>
#include "Lock.h"
#include "LogEvent.h"

using std::ios_base;
using std::string;
using std::ofstream;
using std::cout;
using std::endl;

using namespace NLogEvent;

class CLogBase
{
public:
	enum ELogControl
	{
		eLogNoNewLine,
		eLogFlush,
		eLogEndl
	};

	CLogBase();
	~CLogBase();
	void SetMultiThread(bool bSupport) { _bMultiThread = bSupport; }
	ofstream& GetStream() { return _ofs; }
 	bool OpenLog(const string& strFile);
	bool OpenLog(const string& strPath, const string& strName);

	bool GetNewFileName(string& strFileName);
	 
	bool CheckLog();

	template<typename T>
	CLogBase& operator<<(const T& val)
	{
		_ofs << val;
		if(_bOpenConsole && _bDebug)
			cout << val;
		return *this;
	}

	CLogBase& operator<<(UINT8 byVal)
	{
		_ofs << (int)byVal;
		if(_bOpenConsole && _bDebug)
			cout << (int)byVal;
		return *this;
	}

	CLogBase& operator<<(const ELogControl& eLogControl)
	{
		switch(eLogControl)
		{
		case eLogNoNewLine:
			_bNewLine = false;
			break;
		case eLogFlush:
			_ofs.flush();
			break;
		case eLogEndl:
			_ofs << endl;
			break;
		}
		return *this;
	}

private:
	ofstream _ofs;
	bool _bDir;
	bool _bMultiThread;
	CSpinLock _lock;
	tm _tmTime;
	char _szbuf[0x100];
	bool _bOpenConsole;
	bool _bDebug;
	bool _bNewLine;

	string _strPath;
	string _strCurFileName;
	string _strLogName;
};

////////////////////////////////////////////////////////////////////

class CLogMgr
{
public:
    static CLogMgr& Instance();
	bool Init();
	
	bool WriteLog(ELogType eLogType, const string& strLog);
private:
	CLogMgr();
	CLogBase* GetLog(ELogType eLogType);

	CLogBase _arLog[eLogEnd];
	string _arrName[eLogEnd];
};
