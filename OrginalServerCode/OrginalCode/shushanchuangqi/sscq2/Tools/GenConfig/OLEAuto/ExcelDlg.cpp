// ExcelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OLEAuto.h"
#include "ExcelDlg.h"
#include "XLRange.h"
#include <vector>
#include "Write_XML.h"
// CExcelDlg dialog
// We may keep this in MSExcel.h
#define ID_SAVEAS_XLS		1240	// XLS
#define ID_SAVEAS_XMLS		1246	// XML SpreadSheet
#define ID_SAVEAS_XMLD		1247	// XML Data
#define ID_SAVEAS_MHT		1245	// MHTML
#define ID_SAVEAS_HTML		1244	// HTML
#define ID_SAVEAS_XLT		1217	// XLT
#define ID_SAVEAS_TXT		1220	// TXT
#define ID_SAVEAS_CSV		1206	// CSV

IMPLEMENT_DYNAMIC(CExcelDlg, CDialog)

CExcelDlg::CExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExcelDlg::IDD, pParent)
{

}

CExcelDlg::~CExcelDlg()
{
}

void CExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExcelDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CExcelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CExcelDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CExcelDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON13, &CExcelDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CExcelDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CExcelDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CExcelDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON7, &CExcelDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CExcelDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON17, &CExcelDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CExcelDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CExcelDlg::OnBnClickedButton19)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON20, &CExcelDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON12, &CExcelDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON21, &CExcelDlg::OnBnClickedButton21)
END_MESSAGE_MAP()


// CExcelDlg message handlers

void CExcelDlg::OnBnClickedButton1()
{
	if(SUCCEEDED(m_msExcel.NewExcelBook()))
		EnableControls(true);
	else
		EnableControls(false);
}


BOOL CExcelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CWnd *pWnd=FindWindow(_T("Shell_TrayWnd"),NULL);
	int x=GetSystemMetrics(SM_CXSCREEN); 
	int y=GetSystemMetrics(SM_CYSCREEN);
	if(pWnd)
	{
		CRect rect;
		pWnd->GetWindowRect(rect);
		y-=rect.Height();
	}
	CRect rect;
	GetWindowRect(rect);
	//MoveWindow(x-rect.Width(),y-rect.Height(),rect.Width(),rect.Height(),1);
	SetWindowPos(&wndTopMost,x-rect.Width(),y-rect.Height(),rect.Width(),rect.Height(),SWP_SHOWWINDOW);
	EnableControls(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CExcelDlg::OnBnClickedButton2()
{
	if(SUCCEEDED(m_msExcel.ProtectExcelSheet(1,_T("helloworld"))))
		MessageBox(_T("Protection password: helloworld"));
	else
		MessageBox(_T("Cannot protect sheet"));
}

void CExcelDlg::OnBnClickedButton3()
{
	m_msExcel.UnProtectExcelSheet(1,_T("helloworld"));
}

void CExcelDlg::OnBnClickedButton13()
{
	m_msExcel.MoveCursor(3);
}

void CExcelDlg::OnBnClickedButton14()
{
	m_msExcel.MoveCursor(4);
}

void CExcelDlg::OnBnClickedButton15()
{
	m_msExcel.MoveCursor(1);
}

void CExcelDlg::OnBnClickedButton16()
{
	m_msExcel.MoveCursor(2);
}

void CExcelDlg::OnBnClickedButton7()
{
	CXLRange range;
	int nRow=1,nCol=1;
	m_msExcel.GetActiveCell(nRow,nCol);
	CString sActiveCell;
	sActiveCell.Format(_T("%c%d"),nCol+64,nRow);
	range.SetValue(sActiveCell);
	if(range.DoModal()==IDCANCEL) return;
	CFontDialog cfd;
	if(cfd.DoModal()==IDCANCEL) return;
	m_msExcel.SetExcelFont(range.GetValue(),cfd.GetFaceName(),cfd.GetSize()/10,cfd.GetColor(),cfd.IsBold(),cfd.IsItalic());
}

void CExcelDlg::OnBnClickedButton8()
{
	CXLRange range;
	int nRow=1,nCol=1;
	m_msExcel.GetActiveCell(nRow,nCol);
	CString sActiveCell;
	sActiveCell.Format(_T("%c%d"),nCol+64,nRow);
	range.SetValue(sActiveCell);
	if(range.DoModal()==IDCANCEL) return;
	CColorDialog ccd;
	if(ccd.DoModal()==IDCANCEL) return;
	m_msExcel.SetExcelBackgroundColor(range.GetValue(),ccd.GetColor(),1); 
}

void CExcelDlg::OnBnClickedButton17()
{
	CXLRange range;
	int nRow=1,nCol=1;
	m_msExcel.GetActiveCell(nRow,nCol);
	CString sActiveCell;
	sActiveCell.Format(_T("%c%d"),nCol+64,nRow);
	range.SetValue(sActiveCell);
	if(range.DoModal()==IDCANCEL) return;
	m_msExcel.SetExcelBorder(range.GetValue(),1); 
}

void CExcelDlg::OnBnClickedButton18()
{
	CXLRange range;
	int nRow=1,nCol=1;
	m_msExcel.GetActiveCell(nRow,nCol);
	CString sActiveCell;
	sActiveCell.Format(_T("%c%d"),nCol+64,nRow);
	range.SetValue(sActiveCell);
	if(range.DoModal()==IDCANCEL) return;
	m_msExcel.MergeExcelCells(range.GetValue());
}

void CExcelDlg::OnBnClickedButton19()
{
	int nOpt=MessageBox(_T("Do you want make a demo graph? \nClick \"Yes\" for demo graph, \"No\" for manual graph."),_T("Graph Option"),MB_YESNOCANCEL);
	if(nOpt==IDCANCEL) return;
	if(nOpt==IDYES)
	{
		m_msExcel.SetExcelValue(_T("a1"),_T("Title1"),true,1); 
		m_msExcel.SetExcelValue(_T("b1"),_T("Title2"),true,1);
		m_msExcel.SetExcelValue(_T("c1"),_T("Title3"),true,1);
		m_msExcel.SetExcelValue(_T("d1"),_T("Title4"),true,1);
		m_msExcel.SetExcelValue(_T("a2"),_T("1"),true,1); 
		m_msExcel.SetExcelValue(_T("b2"),_T("2"),true,1);
		m_msExcel.SetExcelValue(_T("c2"),_T("5"),true,1);
		m_msExcel.SetExcelValue(_T("d2"),_T("7"),true,1);
		m_msExcel.SetExcelValue(_T("a3"),_T("2"),true,1); 
		m_msExcel.SetExcelValue(_T("b3"),_T("9"),true,1);
		m_msExcel.SetExcelValue(_T("c3"),_T("4"),true,1);
		m_msExcel.SetExcelValue(_T("d3"),_T("5"),true,1);
		m_msExcel.SetExcelValue(_T("a4"),_T("5"),true,1); 
		m_msExcel.SetExcelValue(_T("b4"),_T("2"),true,1);
		m_msExcel.SetExcelValue(_T("c4"),_T("7"),true,1);
		m_msExcel.SetExcelValue(_T("d4"),_T("1"),true,1);
		m_msExcel.AddExcelChart(_T("a1:d4"),_T("Demo Graph"),5,100,100,300,400,1,1);
	}
	else
	{
		CXLRange range;
		int nRow=1,nCol=1;
		m_msExcel.GetActiveCell(nRow,nCol);
		CString sActiveCell;
		sActiveCell.Format(_T("%c%d"),nCol+64,nRow);
		range.SetValue(sActiveCell);
		if(range.DoModal()==IDCANCEL) return;
		m_msExcel.AddExcelChart(range.GetValue(),_T("Sample Chart"),1,100,100,300,400,1,1);
	}
}

void CExcelDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanging(lpwndpos);
	CRect trayrect;
	CWnd *pWnd=FindWindow(_T("Shell_TrayWnd"),NULL);
	if(!pWnd) return;
	pWnd->GetWindowRect(trayrect);
	int x=GetSystemMetrics(SM_CXSCREEN);
	int y=GetSystemMetrics(SM_CYSCREEN);
	CRect rect;
	GetWindowRect(rect);

	lpwndpos->x=x-rect.Width();

	if(lpwndpos->y + rect.Height() > trayrect.top) lpwndpos->y = trayrect.top - rect.Height();
	if(lpwndpos->y < 0) lpwndpos->y=0;
}

void CExcelDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));
}

void CExcelDlg::OnBnClickedButton20()
{
	CXLRange value;
	value.SetTitle(_T("Enter cell value")); 
	if(value.DoModal()==IDCANCEL) return;
	m_msExcel.SetActiveCellText(value.GetValue());
}

void CExcelDlg::OnBnClickedButton12()
{
	CFileDialog cfd(true,_T("*.*"),0,4|2,_T("Microsoft Excel Files|*.*"));
	if(cfd.DoModal()==IDCANCEL) return;

	if(SUCCEEDED(m_msExcel.OpenExcelBook(cfd.GetPathName())))
		EnableControls(true);
	else
		EnableControls(false);
}

void CExcelDlg::OnBnClickedButton21()
{
	m_mSaveMenu.DestroyMenu();
	m_mSaveMenu.CreatePopupMenu();
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_XLS,_T("XLS"));
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_XMLS,_T("XML SpreadSheet"));
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_XMLD,_T("XML Data"));
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_MHT,_T("MHT"));
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_HTML,_T("HTML"));
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_XLT,_T("XLT"));
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_TXT,_T("TXT"));
	m_mSaveMenu.AppendMenu(MF_STRING,ID_SAVEAS_CSV,_T("CSV"));
	CWnd *btnMenu=GetDlgItem(IDC_BUTTON21);
	CRect rect; btnMenu->GetWindowRect(rect);
	m_mSaveMenu.TrackPopupMenu(TPM_LEFTBUTTON,rect.left,rect.bottom,this); 
}

void CExcelDlg::EnableControls(bool bEnable)
{
	GetDlgItem(IDC_BUTTON21)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON13)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON14)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON15)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON16)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON17)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON18)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON19)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON20)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON21)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(!bEnable);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(!bEnable);
}

BOOL CExcelDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CFileDialog cfd(false);
	switch(LOWORD(wParam))
	{
		case ID_SAVEAS_XLS	:
		case ID_SAVEAS_XMLS	:
		case ID_SAVEAS_XMLD	:
		case ID_SAVEAS_MHT	:
		case ID_SAVEAS_HTML	:
		case ID_SAVEAS_XLT	:
		case ID_SAVEAS_TXT	:
		case ID_SAVEAS_CSV	:
			if(cfd.DoModal()!=IDCANCEL)
			{
				if(LOWORD(wParam)==1240)
					m_msExcel.SaveAs(cfd.GetPathName(),-4143);
				else
					m_msExcel.SaveAs(cfd.GetPathName(),LOWORD(wParam)-1200);
			}
		break;
	}
	return CDialog::OnCommand(wParam, lParam);
}
