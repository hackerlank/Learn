#include "GlobalDefine.h"
#include "ServerID.h"
#include "NetMgr.h"
#include "RequestHandler.h"
#include "Config.h"
#include "UtilFunc.h"

#ifdef _WIN32
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

string CRequestHandler::_strSvrDir;
string CRequestHandler::_strCltDir;
string CRequestHandler::_strServerName;
string CRequestHandler::_strPipeName;
CNamePipe CRequestHandler::_oSvrPipe;
bool CRequestHandler::_bRun;
CConfig* CRequestHandler::_pConfig;

void CRequestHandler::ProcessRequest(CConfig& rConfig)
{
	if(!Init(rConfig))
	{
		LOG_CRI << "CRequestHandler::Init fails!";
		return;
	}
	if(!CRequestHandler::Wait())
	{
		LOG_CRI << "CRequestHandler::Wait fails!";
		return;
	}
	CRequestHandler::Run();
}

void CRequestHandler::Close()
{
	_bRun = false;
	_oSvrPipe.Close();
}

bool CRequestHandler::Init(CConfig& rConfig)
{
	_pConfig = &rConfig;
	_strSvrDir = rConfig._strPipeDir + PATH_SEP "server";
	_strCltDir = rConfig._strPipeDir + PATH_SEP "client";
	_strServerName = rConfig._strSvrName;

	char buf[32];
	sprintf_s(buf, "%s%x", rConfig._strShortName.c_str(), rConfig._byIndex);
	_strPipeName = buf;
	if(!_oSvrPipe.Init(_strSvrDir, _strPipeName))
	{
		LOG_CRI << "oSvrPipe.Init fails!";
		return false;
	}
	if(!_oSvrPipe.OpenForRead())
	{
		LOG_CRI << "oSvrPipe.Init fails!";
		return false;
	}
	return true;
}

bool CRequestHandler::Wait()
{
	if(!_oSvrPipe.OpenForWait())
	{
		LOG_CRI << "oSvrPipe.OpenForWait fails!";
		return false;
	}
	return true;
}

void CRequestHandler::Run()
{
	char szBuf[100];
	_bRun = true;
	while(_bRun)
	{
		EReqType eReqType = eReqNone;
		int pid = 0;
		string strData;
		if(!_oSvrPipe.Read(eReqType, pid, strData))
		{
			LOG_CRI << "oSvrPipe.Read fails!";
			continue;
		}
		string strResp = CRequestHandler::HandleRequest(eReqType, strData);
		sprintf_s(szBuf, "%s%u", _strPipeName.c_str(), pid);
		CNamePipe oCltPipe(true);
		if(!oCltPipe.Init(_strCltDir, szBuf, false))
		{
			LOG_CRI << "oCltPipe.Init fails!";
			continue;
		}
		if(!oCltPipe.OpenForWrite())
		{
			LOG_CRI << "oCltPipe.OpenForWrite fails!";
			continue;
		}
		oCltPipe.Write(eReqInfo, strResp);
#ifdef _WIN32
		if(!_bRun)
			break;
		_oSvrPipe.Close();
		if(!_oSvrPipe.Init(_strSvrDir, _strPipeName))
		{
			LOG_CRI << "oSvrPipe.Init fails!";
			continue;
		}
		if(!_oSvrPipe.OpenForRead())
		{
			LOG_CRI << "oSvrPipe.Init fails!";
			continue;
		}
#endif
	}
	LOG_INF << LOGCTL_NO_CONSOLE << "Server: " << _strServerName << " exits normal!";
}

bool CRequestHandler::CheckGroupKey(const string& strData)
{
	UINT32 dwGroupKey = 0;
	if(strData.copy((char*)&dwGroupKey, strData.size()) != sizeof dwGroupKey)
		return false;
	if(_pConfig == NULL)
		return false;
	return _pConfig->_dwGroupKey == dwGroupKey;
}

string CRequestHandler::HandleRequest(EReqType eReqType, const string& strData)
{
	string strResp;
	switch(eReqType)
	{
	case eReqInfo:
		if(!CheckGroupKey(strData))
			return "Invalid Group Key for eReqInfo!";
		GetServerInfo(strResp);
		break;
	case eReqExit:
		if(!CheckGroupKey(strData))
			return "Invalid Group Key for eReqExit!";
		Exit(strResp);
		break;
	case eReqLoad:
		if(!CheckGroupKey(strData))
			return "Invalid Group Key for eReqLoad!";
		if(_pConfig != NULL)
			_pConfig->LoadUserData();
		break;
	case eReqStore:
		if(!CheckGroupKey(strData))
			return "Invalid Group Key for eReqStore!";
		if(_pConfig != NULL)
			_pConfig->StoreUserData();
		break;
	case eReqClose:
		if(_pConfig != NULL)
		{
			UINT32 dwRemTime = (UINT32)atoi(strData.c_str());
			_pConfig->CloseAllServer(dwRemTime);
		}
		break;
    default:
        break;
	}
	return strResp;
}

void CRequestHandler::GetServerInfo(string& strInfo)
{
	ostringstream os;
	EHostType eSvrType = CNetMgr::GetNetMgr()->GetHostType();
	os << GetServerName(eSvrType) << "\n";
	os << "Group: " << _pConfig->_wGroup << ", Index: " << (int) _pConfig->_byIndex << ", Listen Port: " << _pConfig->_wListenPort << "\n";
	os << "Connect Server:\n";
	for(auto it = _pConfig->_mapID2Conn.begin(); it != _pConfig->_mapID2Conn.end(); ++it)
	{
		UINT32 dwSvrID = it->first;
		CConfig::SConnect& rConn = it->second;
		if(rConn.eState != CConfig::eStateEstablished)
			continue;
		EHostType eHostType = GetServerType(dwSvrID);
		UINT16 wGroup = GetServerGroup(dwSvrID);
		UINT8 byIndex = GetServerIndex(dwSvrID);
		os << "\t" << GetServerName(eHostType) << ": " << rConn.strAddr << ", Group: " << wGroup << ", Index: "
			<< (int) byIndex << ", Port: " << rConn.wPort << "\n";
	}
	os << "Accept Server:\n";
	for(auto it = _pConfig->_mapID2Acc.begin(); it != _pConfig->_mapID2Acc.end(); ++it)
	{
		UINT32 dwSvrID = it->first;
		CConfig::SAccept& rAccept = it->second;
		if(rAccept.eState != CConfig::eStateEstablished)
			continue;
		EHostType eHostType = GetServerType(dwSvrID);
		UINT16 wGroup = GetServerGroup(dwSvrID);
		UINT8 byIndex = GetServerIndex(dwSvrID);
		os << "\t" << GetServerName(eHostType) << ": " << rAccept.strAddr << ", Group: " << wGroup << ", Index: "
			<< (int) byIndex << ", Port: " << rAccept.wPort << "\n";
	}
	strInfo = os.str();
	_pConfig->GetExtraInfo(strInfo);
}

void CRequestHandler::Exit(string& strResult)
{
	_bRun = false;
	strResult = "Server: " + _strServerName + " exited successfully\n";
	LOG_INF << LOGCTL_NO_CONSOLE << "Server: " << _strServerName << " exits by request!";
}
