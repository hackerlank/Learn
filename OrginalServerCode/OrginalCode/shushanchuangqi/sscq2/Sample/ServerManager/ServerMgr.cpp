#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ServerMgr.h"
#include "ServerID.h"
#include "Directory.h"
#include "UtilFunc.h"
#include "NetMgr.h"
#include "Config.h"


UINT16 CServerMgr::_wGroup;
UINT32 CServerMgr::_dwGroupKey;
string CServerMgr::_strCurDir;
string CServerMgr::_strSvrPipeDir;
string CServerMgr::_strCltPipeDir;
map<UINT32, SSvrInfo> CServerMgr::_mapID2SvrInfo;

bool CServerMgr::Init()
{
	if(!GetCurDirectory(_strCurDir))
		return false;

	class CSvrConfig : public CConfig
	{
		class CSvrNetMgr : public CNetMgr { } _oNetMgr;
	public:
		CSvrConfig() : CConfig(_oNetMgr) { }
	} oSvrConfig;
	SConfigInfo oConfigInfo;
	string strFileName = _strCurDir + "Config/" + CONFIG_FILE_NAME;
	if(!oSvrConfig.ParseConfig(strFileName, oConfigInfo))
	{
		cerr << "ParseConfig " << CONFIG_FILE_NAME << " fails!" << endl;
		return false;
	}

	for(auto it = oConfigInfo.mapSvr2Conf.begin(); it != oConfigInfo.mapSvr2Conf.end(); ++it)
	{
		EHostType eHostType = it->first;
		auto rMapIdx2Conf = it->second;
		for(auto itIdx = rMapIdx2Conf.begin(); itIdx != rMapIdx2Conf.end(); ++itIdx)
		{
			UINT8 byIndex = itIdx->first;
			//SServerConfig& rSvrConfig = itIdx->second;

			SSvrInfo oSvrInfo;
			oSvrInfo.eSvrType = eHostType;
			oSvrInfo.byIndex = byIndex;
			oSvrInfo.wGroup = oSvrConfig._wGroup;
			oSvrInfo.strName = GetServerName(eHostType);
			oSvrInfo.strPath = oSvrInfo.strName;
			if(byIndex > 1)
				oSvrInfo.strPath += NumberToString(byIndex);
			oSvrInfo.strPipeName = GetServerShortName(eHostType) + NumberToString(byIndex);
			UINT32 dwSvrID = GetServerID(oSvrInfo.wGroup, eHostType, oSvrInfo.byIndex);
			_mapID2SvrInfo.insert(make_pair(dwSvrID, oSvrInfo));
		}
	}
	_wGroup = oSvrConfig._wGroup;
	_dwGroupKey = oSvrConfig._dwGroupKey;

	_strSvrPipeDir = oSvrConfig._strPipeDir + "/server";
	_strCltPipeDir = oSvrConfig._strPipeDir + "/client";
	return true;
}

void CServerMgr::StartServer(UINT32 dwSvrID, bool bDebug)
{
	if(dwSvrID == 0)
	{
		for(auto it = _mapID2SvrInfo.begin(); it != _mapID2SvrInfo.end(); ++it)
		{
			SSvrInfo& rSvrInfo = it->second;
			StartServer(rSvrInfo, bDebug);
		}
	}
	else
	{
		auto it = _mapID2SvrInfo.find(dwSvrID);
		if(it == _mapID2SvrInfo.end())
		{
			cout << "Invalid Server! Name: " << GetServerName(GetServerType(dwSvrID)) << ", Index: " << GetServerIndex(dwSvrID) << endl;
			return;
		}
		SSvrInfo& rSvrInfo = it->second;
		StartServer(rSvrInfo, bDebug);
	}
}

bool CServerMgr::StartServer(SSvrInfo& rSvrInfo, bool bDebug)
{
	string strFilePath = "./" + rSvrInfo.strPath;
	if(bDebug)
		strFilePath += "D";
    char szGroupID[32] = {0};
    sprintf_s(szGroupID, ".%d", rSvrInfo.wGroup);
	if(rSvrInfo.byIndex > 1)
	{
		string strSvrName = GetServerName(rSvrInfo.eSvrType);
		string strBasePath = strSvrName;
		if(bDebug)
			strBasePath += "D";

        strBasePath += szGroupID;

		tm tmBaseTime;
		memset(&tmBaseTime, 0, sizeof(tm));
		if(!GetFileTime(strBasePath, tmBaseTime))
		{
			cerr << "Can't find file: " << strBasePath << endl;
			return false;
		}

		bool bDiff = true;
		tm tmFileTime;
		memset(&tmFileTime, 0, sizeof(tm));
		if(GetFileTime(strFilePath, tmFileTime)
			&& tmBaseTime.tm_year == tmFileTime.tm_year
			&& tmBaseTime.tm_mon == tmFileTime.tm_mon
			&& tmBaseTime.tm_mday == tmFileTime.tm_mday
			&& tmBaseTime.tm_hour == tmFileTime.tm_hour
			&& tmBaseTime.tm_min == tmFileTime.tm_min
			&& tmBaseTime.tm_sec == tmFileTime.tm_sec)
			bDiff = false;

		if(bDiff)
		{
            string strExecFile = strFilePath + szGroupID;
			string strCopyCmd = "cp -f " + strBasePath + " " + strExecFile;
			if(system(strCopyCmd.c_str()) < 0)
			{
				cerr << "Copy file by command: [" << strCopyCmd << "] fails!" << endl;
				return false;
			}
			cout << strCopyCmd << endl;
			char szBuf[0x100];
			sprintf_s(szBuf, "touch --date=\"%u-%02u-%02u %02u:%02u:%02u\" %s", tmBaseTime.tm_year + 1900, tmBaseTime.tm_mon + 1,
				tmBaseTime.tm_mday, tmBaseTime.tm_hour, tmBaseTime.tm_min, tmBaseTime.tm_sec, strExecFile.c_str());
			if(system(szBuf) < 0)
			{
				cerr << "Touch file by command: [" << szBuf << "] fails!" << endl;
				return false;
			}
		}
	}
    strFilePath += szGroupID;
	string strCmd = strFilePath + " &";
	if(system(strCmd.c_str()) < 0)
		cerr << "Start server by command: [" << strCmd << "] fails!" << endl;
    return true;
}

void CServerMgr::ShowStatus(UINT32 dwSvrID)
{
	string strData((char*)&_dwGroupKey, sizeof _dwGroupKey);
	if(dwSvrID == 0)
		SendRequestAll(eReqInfo, strData);
	else
		SendRequest(dwSvrID, eReqInfo, strData);
}

void CServerMgr::Close(UINT32 dwSvrID)
{
	string strData((char*)&_dwGroupKey, sizeof _dwGroupKey);
	if(dwSvrID == 0)
		SendRequestAll(eReqExit, strData);
	else
		SendRequest(dwSvrID, eReqExit, strData);
}

void CServerMgr::Shutdown()
{
	string strData;
	if(optarg != NULL)
		strData = optarg;
	UINT32 dwSvrID = GetServerID(_wGroup, eHostCenter, 1);
	SendRequest(dwSvrID, eReqClose, strData);
}

void CServerMgr::LoadUserData()
{
	string strData((char*)&_dwGroupKey, sizeof _dwGroupKey);
	UINT32 dwSvrID = GetServerID(_wGroup, eHostDB, 1);
	SendRequest(dwSvrID, eReqLoad, strData);
}

void CServerMgr::StoreUserData()
{
	string strData((char*)&_dwGroupKey, sizeof _dwGroupKey);
	UINT32 dwSvrID = GetServerID(_wGroup, eHostDB, 1);
	SendRequest(dwSvrID, eReqStore, strData);
}

bool CServerMgr::SendRequest(EReqType eReqType, const string& strName, const string& strData)
{
	char szBuf[100];
	sprintf(szBuf, "%s%u", strName.c_str(), getpid());
	CNamePipe oCltPipe(true);
	if(!oCltPipe.Init(_strCltPipeDir, szBuf))
	{
		cerr << "oCltPipe.Init fails!" << endl;
		return false;
	}

	CNamePipe oSvrPipe;
	if(!oSvrPipe.Init(_strSvrPipeDir, strName, false))
	{
		cerr << "oSvrPipe.Init fails!" << endl;
		return false;
	}

	if(!oSvrPipe.OpenForWrite(true))
	{
		cerr << "Server: " << strName << " is not running!" << endl;
		return false;
	}

	if(!oSvrPipe.Write(eReqType, strData))
	{
		cerr << "oSvrPipe.Write fails!" << endl;
		return false;
	}

	if(!oCltPipe.OpenForRead())
	{
		cerr << "oCltPipe.OpenForRead fails!" << endl;
		return false;
	}

	int pid = 0;
	string strRetData;
	if(!oCltPipe.Read(eReqType, pid, strRetData))
	{
		cerr << "oCltPipe.Read fails!" << endl;
		return false;
	}
	cout << strRetData;
	return true;
}

void CServerMgr::SendRequestAll(EReqType eReqType, const string& strData)
{
	for(auto it = _mapID2SvrInfo.begin(); it != _mapID2SvrInfo.end(); ++it)
	{
		SSvrInfo& rSvrInfo = it->second;
		cout << "=======================================================" << endl;
		SendRequest(eReqType, rSvrInfo.strPipeName, strData);
	}
}

void CServerMgr::SendRequest(UINT32 dwSvrID, EReqType eReqType, const string& strData)
{
	auto it = _mapID2SvrInfo.find(dwSvrID);
	if(it == _mapID2SvrInfo.end())
	{
		cout << "Invalid Server! Name: " << GetServerName(GetServerType(dwSvrID)) << ", Index: " << GetServerIndex(dwSvrID) << endl;
		return;
	}
	SSvrInfo& rSvrInfo = it->second;
	SendRequest(eReqType, rSvrInfo.strPipeName, strData);
}
