// OLEAutoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OLEAuto.h"
#include "OLEAutoDlg.h"
#include "SDictionary.h"
#include "WordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// COLEAutoDlg dialog




COLEAutoDlg::COLEAutoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COLEAutoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COLEAutoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COLEAutoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &COLEAutoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON11, &COLEAutoDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &COLEAutoDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON2, &COLEAutoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// COLEAutoDlg message handlers

BOOL COLEAutoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COLEAutoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COLEAutoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COLEAutoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COLEAutoDlg::OnBnClickedButton1()
{
	ShowWindow(SW_HIDE);
	CWordDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}
HRESULT OLEMethodEx(int nType, VARIANT *pvResult, IDispatch *pDisp,LPOLESTR ptName, int cArgs...)
{
	if(!pDisp) return E_FAIL;

	va_list marker;
	va_start(marker, cArgs);

	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	char szName[200];


	// Convert down to ANSI
	WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);

	// Get DISPID for name passed...
	HRESULT hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
	if(FAILED(hr)) {
		return hr;
	}
	// Allocate memory for arguments...
	VARIANT *pArgs = new VARIANT[cArgs+1];
	// Extract arguments...
	for(int i=0; i<cArgs; i++) {
		pArgs[i] = va_arg(marker, VARIANT);
	}

	// Build DISPPARAMS
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;

	// Handle special-case for property-puts!
	if(nType & DISPATCH_PROPERTYPUT) {
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}

	// Make the call!
	hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, nType, &dp, pvResult, NULL, NULL);
	if(FAILED(hr)) {
		return hr;
	}
	// End variable-argument section...
	va_end(marker);

	delete [] pArgs;
	return hr;
}


void COLEAutoDlg::OnBnClickedButton11()
{
	CoInitialize(NULL);
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"InternetExplorer.Application.1", &clsid);
	IDispatch *pInternetExplorer=NULL;
	if(SUCCEEDED(hr))
	{
		hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void **)&pInternetExplorer);
		if(FAILED(hr)) pInternetExplorer=NULL;
	}
	{
		VARIANT x;
		x.vt = VT_I4;
		x.lVal = 1;
		hr=OLEMethodEx(DISPATCH_PROPERTYPUT, NULL, pInternetExplorer, L"Visible", 1, x);
	}
	
	if(FAILED(hr)) MessageBox(_T("Failed"));
	else
	{
		COleVariant vFname(_T("http://www.narenn.com"));
		VARIANT fname=vFname.Detach();
		{
			VARIANT result;
			VariantInit(&result);
			hr=OLEMethodEx(DISPATCH_METHOD, &result, pInternetExplorer, L"Navigate", 1,fname);
		}
		MessageBox(_T("Click OK to close IE?"));

		{
			VARIANT result;
			VariantInit(&result);
			hr=OLEMethodEx(DISPATCH_METHOD, &result, pInternetExplorer, L"Quit", 0);
		}	 
	}
	if(pInternetExplorer) pInternetExplorer->Release();
	CoUninitialize();
}
//{38BE3000-DBF4-11D0-860E-00A024CFEF6D}


void COLEAutoDlg::OnBnClickedButton12()
{
	CSDictionary dict;
	if(SUCCEEDED(dict.Initialize()))
	{
		dict.Add(_T("a"),_T("a1"));
		dict.Add(_T("b"),_T("b1"));
		dict.Add(_T("c"),_T("c1"));
		if(dict.Exists(_T("b")))
			MessageBox(dict.GetItem(_T("b")));
		else
			MessageBox(_T("not exitst"));
	}
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	return TRUE;  
}

#include "ExcelDlg.h"

void COLEAutoDlg::OnBnClickedButton2()
{
	ShowWindow(SW_HIDE);
	CExcelDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}
