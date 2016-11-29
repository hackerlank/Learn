#pragma once

#include "MSExcel.h"
// CExcelDlg dialog

class CExcelDlg : public CDialog
{
	DECLARE_DYNAMIC(CExcelDlg)

public:
	CExcelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExcelDlg();

// Dialog Data
	enum { IDD = IDD_EXCEL_DIALOG };
	CMenu m_mSaveMenu;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CMSExcel m_msExcel;
	DECLARE_MESSAGE_MAP()
public:
	void EnableControls(bool bEnable=true);
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton21();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedCancel();
};
