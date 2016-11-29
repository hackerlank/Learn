// ExcelTool.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ExcelTool.h"
#include "ExcelToCode.h"
#include "CmdExcelToCode.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExcelToolApp

BEGIN_MESSAGE_MAP(CExcelToolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExcelToolApp construction

CExcelToolApp::CExcelToolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CExcelToolApp object

CExcelToolApp theApp;


// CExcelToolApp initialization

BOOL CExcelToolApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	//CString s1 = AfxGetApp()->m_lpCmdLine;
	CString s1 = GetCommandLine();
	INT32 dwNum = 0;
	LPTSTR *lpszArgv = CommandLineToArgvW(GetCommandLine(), &dwNum);
	if (dwNum > 1)	/* 有参数，默认认为是目录 */
	{
		CCmdExcelToCode cCmdExcelToCode;
		if (cCmdExcelToCode.SetDir(lpszArgv[1]))
		{
			if (dwNum > 2)
				cCmdExcelToCode.SetDstDir(lpszArgv[2]);
			cCmdExcelToCode.ExportToCode();
		}
	}
	else	/* 没有参数，调用窗口函数 */
	{
		CExcelToCode dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
