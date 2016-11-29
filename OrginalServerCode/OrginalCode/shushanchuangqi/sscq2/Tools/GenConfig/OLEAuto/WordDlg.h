#pragma once

#include "MSWord.h"
// CWordDlg dialog

class CWordDlg : public CDialog
{
	DECLARE_DYNAMIC(CWordDlg)

public:
	CWordDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWordDlg();
	CMSWord m_msWord;
// Dialog Data
	enum { IDD = IDD_WORD_DIALOG };
	bool m_bNoSpellError;
	bool m_bNoGrammerError;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void EnableControls(bool bEnable=true);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
public:
	afx_msg void OnBnClickedButton11();
public:
	afx_msg void OnBnClickedButton12();
public:
	afx_msg void OnBnClickedButton21();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton22();
};
