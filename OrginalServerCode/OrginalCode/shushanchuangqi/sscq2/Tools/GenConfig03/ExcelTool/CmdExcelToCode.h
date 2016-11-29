#pragma once
#include <vector>
class CCmdExcelToCode
{
public:
	CCmdExcelToCode(void);
	virtual ~CCmdExcelToCode(void);

	bool SetDir(LPCTSTR lpFileName);
	bool SetDstDir( LPCTSTR lpszArgv );

	void ExportToCode();

private:
	void ClearVec();
	bool ConvertExcel();
	bool FileExistAndCreate(CString strFileName);
	void Recurse(LPCTSTR pstr, std::vector<CString>& vecfile, std::vector<CString>& vecfilename);
	CString GetTimeString();
private:
	std::vector<CString> m_vecPath;
	std::vector<CString> m_vecfileName;

	CString m_strDirPath;
	CString m_strFilePath;
};

