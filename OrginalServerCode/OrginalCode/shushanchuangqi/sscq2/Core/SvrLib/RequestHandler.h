#pragma once
#include "NamePipe.h"

class CConfig;

class CRequestHandler
{
public:
	static void ProcessRequest(CConfig& rConfig);
	static void Close();

private:
	static bool Init(CConfig& rConfig);
	static bool Wait();
	static void Run();
	static string HandleRequest(EReqType eReqType, const string& strData);
	static void GetServerInfo(string& strInfo);
	static void Exit(string& strResult);
	static bool CheckGroupKey(const string& strData);

	static string _strSvrDir;
	static string _strCltDir;
	static string _strServerName;
	static string _strPipeName;
	static CNamePipe _oSvrPipe;
	static bool _bRun;

	static CConfig* _pConfig;
};
