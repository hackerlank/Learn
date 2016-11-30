#include "DoAction.h"
#include <boost/algorithm/string.hpp>
#include "../MyClient.h"

void CDoAction::OnMessage( std::string & str )
{
	std::map<std::string,int>::const_iterator c_it = CMyClient::g_tools.m_opMap.begin();
	while(c_it != CMyClient::g_tools.m_opMap.end())
	{
		if (boost::iequals(str,c_it->first))
		{
			OnDealMsg(c_it->second);
			break;
		}
		c_it++;
	}
}

bool CDoAction::OnDealMsg( int tag )
{
	Bitfield bitfield;
	ZeroVar(bitfield);
	
	memcpy(&bitfield,&tag,sizeof(Bitfield));
	if (bitfield.stop)
	{
		KillProcess(NULL,CMyClient::g_tools.m_title.c_str());
	}
	if (bitfield.start)
	{
		CreateNewProcess(CMyClient::g_tools.m_exestart.c_str());
	}
	return true;
}

int CDoAction::KillProcess(const char * pszClassName,const char * pszWindowTitle )
{
// 	HANDLE hProcessHandle; 
// 	ULONG nProcessID;
// 	HWND TheWindow;
// 	TheWindow = ::FindWindow( NULL, pszWindowTitle );
// 	::GetWindowThreadProcessId( TheWindow, &nProcessID );
// 	hProcessHandle = ::OpenProcess( PROCESS_TERMINATE, FALSE,nProcessID );
// 	return ::TerminateProcess( hProcessHandle, 4 );

	char strHead[128];
	HWND hWndPrevious = GetWindow(GetDesktopWindow(),GW_CHILD);
	//LPTSTR m_pszExeName;
	while (IsWindow(hWndPrevious)) 
	{
		ZeroVar(strHead);
		int i=GetWindowTextLength(hWndPrevious);
		GetWindowTextA(hWndPrevious,strHead,i);//获取窗口标题//这里我的窗口中只有下面几个字是不变的
		if (strstr(strHead,pszWindowTitle)){
			ULONG nProcessID;
			::GetWindowThreadProcessId( hWndPrevious, &nProcessID );
			HANDLE hProcessHandle = ::OpenProcess( PROCESS_TERMINATE, FALSE, nProcessID );
			std::cout<<strHead<<std::endl;

			hWndPrevious = GetWindow(hWndPrevious,GW_HWNDNEXT);
			::TerminateProcess( hProcessHandle, 4);//匹配，这时hWndPrevious就是所要找的窗口的句柄
		}
		else
		{
			hWndPrevious = GetWindow(hWndPrevious,GW_HWNDNEXT);
		}
	} 

	return true;
}

int CDoAction::CreateNewProcess(const char * pszExeName )
{
	PROCESS_INFORMATION piProcInfoGPS;  
	STARTUPINFO siStartupInfo;  
	SECURITY_ATTRIBUTES saProcess, saThread;  
	ZeroMemory( &siStartupInfo, sizeof(siStartupInfo) );  
	siStartupInfo.cb = sizeof(siStartupInfo);  
	saProcess.nLength = sizeof(saProcess);  
	saProcess.lpSecurityDescriptor = NULL;  
	saProcess.bInheritHandle = true;  
	saThread.nLength = sizeof(saThread);  
	saThread.lpSecurityDescriptor = NULL;  
	saThread.bInheritHandle = true;  
	return ::CreateProcess( NULL, (LPSTR)pszExeName, &saProcess,&saThread, 
		false,CREATE_DEFAULT_ERROR_MODE, NULL, NULL,&siStartupInfo,&piProcInfoGPS );  
}

