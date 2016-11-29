#include "stdafx.h"
#include "LogExt.h"

CLogBase::CLogBase() : _bDir(false), _bMultiThread(false), _bOpenConsole(false), _bDebug(false), _bNewLine(false)
{
	memset(&_tmTime, 0, sizeof _tmTime);
	memset(_szbuf, 0, sizeof _szbuf);
}

CLogBase::~CLogBase()
{
	_ofs.flush();
	_ofs.close();
	_bDir = false;
}

bool CLogBase::OpenLog(const string& strFile)
{
	_strPath = strFile;
	_ofs.open(strFile.c_str(), ios_base::app);
	if(_ofs.bad())
		return false;
	return true;
}

bool CLogBase::OpenLog(const string& strPath, const string& strName)
{
	_bDir = true;
	_strPath = strPath;
	_strLogName = strName;
	return true;
}

bool CLogBase::GetNewFileName(string& strFileName)
{
	if(!_bDir)
		return false;
	time_t tNow = time(NULL);
	tm tmNow;
	localtime_s(&tmNow, &tNow);
	if(!strFileName.empty() && tmNow.tm_year == _tmTime.tm_year && tmNow.tm_mon == _tmTime.tm_mon && tmNow.tm_mday == _tmTime.tm_mday)
		return false;
	_tmTime = tmNow;
	sprintf_s(_szbuf, "/%04u-%02u-%02u", tmNow.tm_year + 1900, tmNow.tm_mon + 1, tmNow.tm_mday);
	string strDir;
	strDir = _strPath + _szbuf;
	if(!CreateDirectory(strDir))
		return false;

	sprintf_s(_szbuf, "/%s.log", _strLogName.c_str());
	strFileName = strDir + _szbuf;
	return true;
}

bool CLogBase::CheckLog()
{
	if(_bDir && GetNewFileName(_strCurFileName))
	{
		_ofs.close();
		_ofs.clear();
		_ofs.open(_strCurFileName.c_str(), ios_base::app);
		if(_ofs.bad())
		{
			LOG_CRI << "file is bad! Path: " << _strCurFileName;
			return false;
		}
	}

	if(!_ofs.is_open())
		return false;

	time_t tNow = time(NULL);
	localtime_s(&_tmTime, &tNow);

	sprintf_s(_szbuf, "[%02u:%02u:%02u] ", _tmTime.tm_hour, _tmTime.tm_min, _tmTime.tm_sec);
	_ofs << _szbuf;

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////

CLogMgr& CLogMgr::Instance()
{
	static CLogMgr oLogMgr;
	return oLogMgr;
}

bool CLogMgr::Init()
{
	if(Config._strGameLogDir.empty())
	{
		LOG_CRI << "GameLogDir is empty!";
		return false;
	}
	for(size_t i = 0; i < ARRAYSIZE(_arLog); ++i)
	{
		if(!_arLog[i].OpenLog(Config._strGameLogDir.c_str(), _arrName[i].c_str()))
		{
			LOG_CRI << "Open GameLog fails! Path: " << Config._strGameLogDir;
			return false;
		}
	}
	return true;
}

CLogMgr::CLogMgr()
{
	_arrName[eLogSystem] = "LogSystem";
	_arrName[eLogMoney] = "LogMoney";
	_arrName[eLogItem] = "LogItem";
	_arrName[eLogLoginout] = "LogLoginout";
	_arrName[eLogMall] = "LogMall";
	_arrName[eLogLevelUp] = "LogLevelUp";
	_arrName[eLogRecruit] = "LogRecruit";
	_arrName[eLogProp] = "LogPropPoint";
	_arrName[eLogSkill] = "LogSkill";
	_arrName[eLogTask] = "LogTask";
	_arrName[eLogBattle] = "LogBattle";
	_arrName[eLogEquipReplace] = "LogEquipReplace";
	_arrName[eLogEquipOpeator] = "LogEquipOperator";
	_arrName[eLogAlchemy] = "LogAlchemy";
	_arrName[eLogDungeon] = "LogDungeon";
	_arrName[eLogActivity] = "LogActivity";
	_arrName[eLogPVPRank] = "LogPVPRank";
	_arrName[eLogBuilding] = "LogBuilding";
	_arrName[eLogGuild] = "LogGuild";
	_arrName[eLogFamily] = "LogFamily";
	_arrName[eLogVIP] = "LogVIP";
	_arrName[eLogUDPLog] = "LogUDPLog";
	_arrName[eLogMail] = "LogMail";
    _arrName[eLogActive] = "LogActive";
}

CLogBase* CLogMgr::GetLog(ELogType eLogType)
{
	if(eLogType > eLogEnd || eLogType <= eLogNone)
	{
		LOG_CRI << "Invalid LogType: " << eLogType;
		return NULL;
	}

	if(_arLog[eLogType].CheckLog())
		return &_arLog[eLogType];
	return NULL;
}

bool CLogMgr::WriteLog(ELogType eLogType, const string& strLog)
{
	if(eLogType > eLogEnd || eLogType <= eLogNone)
	{
		LOG_CRI << "Invalid LogType: " << eLogType;
		return false;
	}

	if(!_arLog[eLogType].CheckLog())
	{
		LOG_CRI << "Can't log for LogType: " << eLogType;
		return false;
	}

	_arLog[eLogType] << strLog << CLogBase::eLogEndl;
	return true;
}


