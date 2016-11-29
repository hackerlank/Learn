#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;
#include "MSExcel.h"
// CExcel_To_Code dialog

class CExcel_To_Code : public CDialogEx
{
	DECLARE_DYNAMIC(CExcel_To_Code)

public:
	CExcel_To_Code(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExcel_To_Code();

// Dialog Data
	enum { IDD = IDD_DIALOG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CMSExcel m_msExcel;
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
	bool op_excel();
	bool FileExistAndCreate(CString strFileName);
	CString GetTimeString();
	void ClearVec(bool bOutput=true);
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonViewDir2();
	afx_msg void OnBnClickedButtonViewfile2();
};
