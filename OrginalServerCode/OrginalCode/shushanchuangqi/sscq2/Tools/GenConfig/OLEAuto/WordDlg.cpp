// WordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OLEAuto.h"
#include "WordDlg.h"
#include "XLRange.h"

// CWordDlg dialog

IMPLEMENT_DYNAMIC(CWordDlg, CDialog)

CWordDlg::CWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWordDlg::IDD, pParent)
{

}

CWordDlg::~CWordDlg()
{
}

void CWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWordDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CWordDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWordDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWordDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CWordDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CWordDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CWordDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &CWordDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CWordDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CWordDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CWordDlg::OnBnClickedButton10)
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGING()
	ON_BN_CLICKED(IDC_BUTTON11, &CWordDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CWordDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON21, &CWordDlg::OnBnClickedButton21)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT1, &CWordDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON22, &CWordDlg::OnBnClickedButton22)
END_MESSAGE_MAP()

void CWordDlg::EnableControls(bool bEnable)
{
	GetDlgItem(IDC_BUTTON2)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON9)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON10)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON11)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON21)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK1)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT1)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(!bEnable);
	GetDlgItem(IDC_BUTTON22)->EnableWindow(!bEnable);
}
// CWordDlg message handlers

void CWordDlg::OnBnClickedButton1()
{
	CFileDialog cfd(true,_T("*.doc"),0,4|2,_T("Microsoft Word Files|*.doc"));
	if(cfd.DoModal()==IDCANCEL) return;

	if(SUCCEEDED(m_msWord.OpenDocument(cfd.GetPathName())))
		EnableControls(true);
	else
		EnableControls(false);
	
}

void CWordDlg::OnBnClickedButton2()
{
	m_msWord.CloseActiveDocument();
	EnableControls(false);
}

void CWordDlg::OnBnClickedButton3()
{
	m_msWord.CloseDocuments();
	EnableControls(false);
}

void CWordDlg::OnBnClickedButton4()
{
	CString sText;
	GetDlgItemText(IDC_EDIT1,sText);
	m_msWord.SetSelectionText(sText);
}

void CWordDlg::OnBnClickedButton5()
{
	bool bExtend=((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED;
	m_msWord.MoveCursor(3,bExtend);
}

void CWordDlg::OnBnClickedButton8()
{
	bool bExtend=((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED;
	m_msWord.MoveCursor(4,bExtend);
}

void CWordDlg::OnBnClickedButton6()
{
	bool bExtend=((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED;
	m_msWord.MoveCursor(1,bExtend);

}

void CWordDlg::OnBnClickedButton7()
{
	bool bExtend=((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED;
	m_msWord.MoveCursor(2,bExtend);
}

void CWordDlg::OnBnClickedButton9()
{
	m_msWord.DeleteChar(true);
}

void CWordDlg::OnBnClickedButton10()
{
	m_msWord.DeleteChar();
}

BOOL CWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//OnBnClickedButton1();

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

void CWordDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x,point.y));
}

void CWordDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
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

void CWordDlg::OnBnClickedButton11()
{
	CFileDialog cfd(true);
	if(cfd.DoModal()==IDCANCEL) return;
	m_msWord.InserPicture(cfd.GetPathName());
}

void CWordDlg::OnBnClickedButton12()
{
	CString sText;
	GetDlgItemText(IDC_EDIT1,sText);
	m_msWord.AddComment(sText);
}

void CWordDlg::OnBnClickedButton21()
{
	CFontDialog cfd;
	if(cfd.DoModal()==IDCANCEL) return;
	m_msWord.SetFont(cfd.GetFaceName(),cfd.GetSize()/10,cfd.IsBold(),cfd.IsItalic(),cfd.GetColor());
}

HBRUSH CWordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID()==IDC_SPELLINDICATOR)
	{
		if(m_bNoSpellError)
			hbr=CreateSolidBrush(RGB(0,255,0));
		else
			hbr=CreateSolidBrush(RGB(255,0,0));
	}
	else if(pWnd->GetDlgCtrlID()==IDC_GRINDICATOR)
	{
		if(m_bNoGrammerError)
			hbr=CreateSolidBrush(RGB(0,255,0));
		else
			hbr=CreateSolidBrush(RGB(255,0,0));
	}
	return hbr;
}

void CWordDlg::OnEnChangeEdit1()
{
	CString sText;
	GetDlgItemText(IDC_EDIT1,sText);
	m_msWord.CheckSpelling(sText,m_bNoSpellError);	
	m_msWord.CheckGrammer(sText,m_bNoGrammerError);	
	GetDlgItem(IDC_SPELLINDICATOR)->Invalidate();
	GetDlgItem(IDC_GRINDICATOR)->Invalidate();
}

void CWordDlg::OnBnClickedButton22()
{
	if(SUCCEEDED(m_msWord.NewDocument()))
		EnableControls(true);
	else
		EnableControls(false);
}
