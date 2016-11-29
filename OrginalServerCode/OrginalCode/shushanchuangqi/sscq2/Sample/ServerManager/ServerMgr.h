#pragma once
#include <string>
#include "NamePipe.h"
#include "Interface.h"

using namespace std;

#define CONFIG_FILE_NAME "ServerConfig.xml"

struct SSvrInfo
{
	EHostType eSvrType;
	UINT8 byIndex;
	UINT16 wGroup;
	string strName;
	string strPath;
	string strPipeName;

	SSvrInfo() : eSvrType(eHostNone), byIndex(0), wGroup(0) { }
};

class CServerMgr
{
public:
	static bool Init();
	static void StartServer(UINT32 dwSvrID, bool bDebug);
	static void ShowStatus(UINT32 dwSvrID);
	static void Close(UINT32 dwSvrID);
	static void Shutdown();
	static void LoadUserData();
	static void StoreUserData();
	static UINT16 GetGroup() { return _wGroup; }

private:
	static bool StartServer(SSvrInfo& rSvrInfo, bool bDebug);
	static bool SendRequest(EReqType eReqType, const string& strName, const string& strData);
	static void SendRequestAll(EReqType eReqType, const string& strData);
	static void SendRequest(UINT32 dwSvrID, EReqType eReqType, const string& strData);

	static UINT16 _wGroup;
	static UINT32 _dwGroupKey;
	static string _strCurDir;
	static string _strSvrPipeDir;
	static string _strCltPipeDir;
	static map<UINT32, SSvrInfo> _mapID2SvrInfo;
};
