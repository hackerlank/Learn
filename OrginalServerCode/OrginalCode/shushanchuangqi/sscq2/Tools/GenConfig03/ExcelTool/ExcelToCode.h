#pragma once
#include "afxwin.h"
#include <vector>

using namespace std;

// CExcelToCode dialog

class CExcelToCode : public CDialogEx
{
	DECLARE_DYNAMIC(CExcelToCode)

public:
	CExcelToCode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExcelToCode();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int m_iTotalIndex;
	std::vector<CString> m_vecPath;
	std::vector<CString> m_vecfileName;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonViewDir();
	afx_msg void OnBnClickedButtonViewfile();
	afx_msg void OnBnClickedOk();
	CString m_strDirPath;
	CString m_strFilePath;
	CListBox m_noticeList;

protected:
	void Recurse(LPCTSTR pstr, std::vector<CString>& vecfile, std::vector<CString>& vecfilename);
	bool ConvertExcel();
	bool FileExistAndCreate(CString strFileName);
	CString GetTimeString();
	void ClearVec(bool bOutput=true);
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonViewDir2();
	afx_msg void OnBnClickedButtonViewfile2();
};
