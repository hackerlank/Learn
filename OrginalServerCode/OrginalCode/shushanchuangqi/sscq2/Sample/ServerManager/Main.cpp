#include <iostream>
#include <algorithm>
#include <stdio.h>
#include "ServerMgr.h"
#include "ServerID.h"

using namespace std;

static void ShowUsage(const char *progName)
{
	fprintf(stderr, "Usage: %s [-drsx] [ServerName]\n", progName);
	fprintf(stderr, "    -d   Start server, debug version.\n");
	fprintf(stderr, "    -r   Start server, release version.\n");
	fprintf(stderr, "    -s   Show status for server.\n");
	fprintf(stderr, "    -u   Load user data.\n");
	fprintf(stderr, "    -t   Store user data.\n");
	fprintf(stderr, "    -n   Shutdown server.\n");
	fprintf(stderr, "    -x   Close server.\n");
}

static bool ParseServerID(UINT32& dwSvrID)
{
    // XXX: 目前没有记用，optarg为空
	if(optarg != NULL)
	{
		string strSvrName = optarg;
		UINT8 byIndex = 1;
		auto it = find_if(strSvrName.begin(), strSvrName.end(), [](char c){ return ::isdigit(c); });
		if(it != strSvrName.end())
		{
			string strNumber(it, strSvrName.end());
			byIndex = (UINT8)atoi(strNumber.c_str());
			if(byIndex == 0)
				return false;
			strSvrName.assign(strSvrName.begin(), it);
		}
		EHostType eSvrType = GetServerType(strSvrName.c_str());
		dwSvrID = GetServerID(CServerMgr::GetGroup(), eSvrType, byIndex);
	}
	return true;
}

int main(int argc, char* argv[])
{
	if(!CServerMgr::Init())
	{
		cerr << "CServerMgr::Init fails!" << endl;
		return -1;
	}

	if(argc < 2)
	{
		ShowUsage(argv[0]);
		return -1;
	}

	UINT32 dwSvrID = 0;
	int opt = getopt(argc, argv, "d::r::s::u::t::n::x::");
	if(opt != -1)
	{
		switch(opt)
		{
		case 'd':
			if(!ParseServerID(dwSvrID))
			{
				ShowUsage(argv[0]);
				return -1;
			}
			CServerMgr::StartServer(dwSvrID, true);
			break;
		case 'r':
			if(!ParseServerID(dwSvrID))
			{
				ShowUsage(argv[0]);
				return -1;
			}
			CServerMgr::StartServer(dwSvrID, false);
			break;
		case 's':
			if(!ParseServerID(dwSvrID))
			{
				ShowUsage(argv[0]);
				return -1;
			}
			CServerMgr::ShowStatus(dwSvrID);
			break;
		case 'u':
			CServerMgr::LoadUserData();
			break;
		case 't':
			CServerMgr::StoreUserData();
			break;
		case 'n':
			CServerMgr::Shutdown();
			break;
		case 'x':
			if(!ParseServerID(dwSvrID))
			{
				ShowUsage(argv[0]);
				return -1;
			}
			CServerMgr::Close(dwSvrID);
			break;
		default:
			ShowUsage(argv[0]);
			break;
		}
	}
	return 0;
}
