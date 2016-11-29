// Excel_To_Code.cpp : implementation file
//

#include "stdafx.h"
#include <vector>
#include "resource.h"		// main symbols
#include "ExcelToCode.h"
#include "afxdialogex.h"
#include "WriteXML.h"
#include "ExcelFormat.h"
// CExcelToCode dialog

using namespace ExcelFormat;

IMPLEMENT_DYNAMIC(CExcelToCode, CDialogEx)

CExcelToCode::CExcelToCode(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExcelToCode::IDD, pParent)
	, m_strDirPath(_T(""))
	, m_strFilePath(_T(""))
	, m_iTotalIndex(0)
{
}

CExcelToCode::~CExcelToCode()
{
}

void CExcelToCode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DIR_PATH, m_strDirPath);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
	DDX_Control(pDX, IDC_LIST_NOTICE, m_noticeList);
}


BEGIN_MESSAGE_MAP(CExcelToCode, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_DIR, &CExcelToCode::OnBnClickedButtonViewDir)
	ON_BN_CLICKED(IDC_BUTTON_VIEWFILE, &CExcelToCode::OnBnClickedButtonViewfile)
	ON_BN_CLICKED(IDOK, &CExcelToCode::OnBnClickedOk)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_VIEW_DIR2, &CExcelToCode::OnBnClickedButtonViewDir2)
	ON_BN_CLICKED(IDC_BUTTON_VIEWFILE2, &CExcelToCode::OnBnClickedButtonViewfile2)
END_MESSAGE_MAP()


// CExcelToCode message handlers

void CExcelToCode::Recurse(LPCTSTR pstr, std::vector<CString>& vecfile, std::vector<CString>& vecfilename)
{ 
    // build a string with wildcards
    CString strWildcard(pstr);
	{
		 CFileFind fir;
		 BOOL bWorking = fir.FindFile(strWildcard);
		 fir.FindNextFile();
		 if(bWorking && fir.IsDirectory())
			 strWildcard += _T("\\*.*");
		 fir.Close();
	}
	CFileFind finder;
    // start working for files
    BOOL bWorking = finder.FindFile(strWildcard);
    
    while (bWorking)
    {
        bWorking = finder.FindNextFile();
        
        // skip . and .. files; otherwise, we'd
        // recur infinitely!
        
        if (finder.IsDots()
			|| finder.IsHidden())
            continue;
        
        // if it's a directory, recursively search it
        CString str = finder.GetFilePath();
        if (finder.IsDirectory())
        {
            Recurse(str, vecfile,vecfilename);
        }
		else if(str.Right(3) == L"xls"
			|| str.Right(4) == L"xlsx")
        {
			vecfile.push_back(str);
			vecfilename.push_back(finder.GetFileTitle());
			CString strOut = GetTimeString() + L"添加【";
			strOut += str;
			strOut += L"】成功!    请点击[导出]";
			m_noticeList.InsertString(m_iTotalIndex++, strOut);
        }
    }
    
    finder.Close();
}


void CExcelToCode::ClearVec(bool bOutput/*=true*/)
{
	if(m_vecPath.size() > 0 && bOutput)
	{
		CString str = GetTimeString() + L"上次导入文件已经过期！";
		m_noticeList.InsertString(m_iTotalIndex++, str);
	}
	if(bOutput)
	{
		m_strFilePath = "";
		m_strDirPath = "";
		UpdateData(false);
	}
	m_vecPath.clear();
	m_vecfileName.clear();

}

void CExcelToCode::OnBnClickedButtonViewDir()
{
	// TODO: Add your control notification handler code here
	  BROWSEINFO   bf;
	  LPITEMIDLIST   lpitem;
	  memset(&bf,0,sizeof   BROWSEINFO);
	  bf.hwndOwner=this->m_hWnd;
	  bf.ulFlags= BIF_RETURNONLYFSDIRS;//属性你可自己选择
	  lpitem=SHBrowseForFolder(&bf);
	  if(lpitem==NULL)     //如果没有选择路径则返回
		  return;
	  ClearVec();
	  TCHAR   szDisplayName[MAX_PATH];
	  SHGetPathFromIDList(lpitem,szDisplayName);
	  std::vector<CString> vecAllFile;
	  Recurse(szDisplayName,m_vecPath,m_vecfileName);
	  m_strDirPath = szDisplayName;
	  UpdateData(false);
}

void CExcelToCode::OnBnClickedButtonViewfile()
{

	// TODO: Add your control notification handler code here
	CFileDialog cfd(true,_T(""),0,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_ALLOWMULTISELECT|OFN_ENABLESIZING,
		_T("Microsoft Excel Files(*.xls,*.xlsx)|*.xls;*.xlsx||"));
	cfd.m_ofn.lpstrTitle=L"请选择要导出的表：";
	//最多可以打开100个文件
	cfd.m_ofn.nMaxFile = 100 * MAX_PATH; 
	TCHAR* pFileName = new TCHAR[cfd.m_ofn.nMaxFile]; 
	cfd.m_ofn.lpstrFile = pFileName; 
	TCHAR szPath[MAX_PATH] = {0};
	::GetCurrentDirectory(MAX_PATH, szPath);
	cfd.GetOFN().lpstrInitialDir = szPath;
	ZeroMemory(cfd.m_ofn.lpstrFile, sizeof(TCHAR) * cfd.m_ofn.nMaxFile); 
	if(cfd.DoModal()==IDCANCEL) return;
	ClearVec();
	POSITION   pos = cfd.GetStartPosition();
	while(pos!=NULL)
	{   
		CString s;
		s=cfd.GetNextPathName(pos); 
		Recurse(s, m_vecPath, m_vecfileName);
		m_strFilePath += s;
		m_strFilePath += L";";
	} 
	delete[]pFileName;
	UpdateData(false);
}


void CExcelToCode::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	// 定义一个缓冲区来存放读取的文件名信息
	TCHAR szFileName[MAX_PATH + 1] = {0};
	// 通过设置iFiles参数为0xFFFFFFFF,可以取得当前拖动的文件数量，
	// 当设置为0xFFFFFFFF,函数间忽略后面连个参数。
	UINT nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	// 通过循环依次取得拖动文件的File Name信息，并把它添加到ListBox中
	ClearVec();
	for(UINT i=0; i<nFiles; i++)
	{
		DragQueryFile(hDropInfo, i, szFileName, MAX_PATH);
		Recurse(szFileName, m_vecPath, m_vecfileName);
	}
	// 结束此次拖拽操作，并释放分配的资源
	DragFinish(hDropInfo);
}

enum EValueType
{
	eTypeINT8,
	eTypeUINT8,
	eTypeINT16,
	eTypeUINT16,
	eTypeINT32,
	eTypeUINT32,
	eTypeINT64,
	eTypeUINT64,
	eTypeFloat,
	eTypeDouble,
	eTypeBool,
	eTypeString
};

static bool GetExcelValue(BasicExcelCell& cell, CString &sValue, LPCTSTR szType)
{
	static map<CString, EValueType> mapValidType;
	if(mapValidType.empty())
	{
		mapValidType[L"INT8"] = eTypeINT8;
		mapValidType[L"UINT8"] = eTypeUINT8;
		mapValidType[L"INT16"] = eTypeINT16;
		mapValidType[L"UINT16"] = eTypeUINT16;
		mapValidType[L"INT32"] = eTypeINT32;
		mapValidType[L"UINT32"] = eTypeUINT32;
		mapValidType[L"INT64"] = eTypeUINT64;
		mapValidType[L"UINT64"] = eTypeUINT64;
		mapValidType[L"FLOAT"] = eTypeFloat;
		mapValidType[L"DOUBLE"] = eTypeDouble;
		mapValidType[L"BOOL"] = eTypeBool;
		mapValidType[L"STRING"] = eTypeString;
	}

	CString strType = szType;
	strType.Trim(L" \n\t");
	if(strType.IsEmpty())
		return false;
	auto it = mapValidType.find(strType);
	if(it == mapValidType.end())
	{
		CString msg;
		msg.Format(L"未知类型定义: %s！", szType);
		AfxMessageBox(msg);
		return false;
	}
	EValueType eValueType = it->second;
	switch(eValueType)
	{
	case eTypeINT8:
		sValue.Format(L"%d", (INT8)cell.GetInteger());
		break;
	case eTypeUINT8:
		sValue.Format(L"%u", (UINT8)cell.GetInteger());
		break;
	case eTypeINT16:
		sValue.Format(L"%d", (INT16)cell.GetInteger());
		break;
	case eTypeUINT16:
		sValue.Format(L"%u", (UINT16)cell.GetInteger());
		break;
	case eTypeINT32:
		sValue.Format(L"%d", (INT32)cell.GetInteger());
		break;
	case eTypeUINT32:
		sValue.Format(L"%u", (UINT32)cell.GetBigInteger());
		break;
	case eTypeINT64:
		sValue.Format(L"%lld", (INT64)cell.GetBigInteger());
		break;
	case eTypeUINT64:
		sValue.Format(L"%llu", (UINT64)cell.GetBigInteger());
		break;
	case eTypeFloat:
		sValue.Format(L"%f", (float)cell.GetDouble());
		break;
	case eTypeDouble:
		sValue.Format(L"%f", cell.GetDouble());
		break;
	case eTypeBool:
		sValue.Format(L"%d", cell.GetInteger() != 0 ? 1 : 0);
		break;
	case eTypeString:
		{
			sValue = cell.GetWString();
			if(sValue.IsEmpty())
			{
				double dVal = cell.GetDouble();
				int nVal = cell.GetInteger();
				if(abs(dVal - nVal) > FLT_EPSILON)
					sValue.Format(L"%f", dVal);
				else if(nVal != 0)
					sValue.Format(L"%d", nVal);
			}
		}
		break;
	}
	return true;
}

bool CExcelToCode::ConvertExcel()
{
	wchar_t m_arrcol[26] = 
	{
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};
	BOOL Sucess = FALSE;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	CString RunDir = szFilePath;
	int nPos = RunDir.ReverseFind(L'\\');
	if(nPos != -1) RunDir = RunDir.Left(nPos+1);
	CString str_url = RunDir + L"Generated\\";
	FileExistAndCreate(str_url);
	HRESULT hRes = 0;
	for(size_t my_index=0;my_index<m_vecfileName.size();++my_index)
	{
		BasicExcel xls;
		CString csFileName = m_vecPath[my_index].GetBuffer();
		int nPos = csFileName.ReverseFind(L'\\');
		CString FileName;
		if (nPos != -1) FileName = csFileName.Right(csFileName.GetLength()-nPos-1);
		if(!xls.Load(csFileName))
		{
			CString str = GetTimeString() + L"读取【";
			str += m_vecPath[my_index].GetBuffer();
			str += L"】失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			continue;
		}
		BasicExcelWorksheet* sheet = xls.GetWorksheet(0);
		if(sheet == NULL)
		{
			CString str = GetTimeString() + L"读取【";
			str += m_vecPath[my_index].GetBuffer();
			str += L"】失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			continue;
		}
		vector<vector<CString>> vecAllInfo;
		int nMaxCol = 0;
		for(int r = 0; r < sheet->GetTotalRows(); ++r)
		{
			vector<CString> vecString;
			for(int c = 0; c < sheet->GetTotalCols(); ++c)
			{
				if(r == 0)
					++nMaxCol;
				else if(c >= nMaxCol)
					break;
				BasicExcelCell* cell = sheet->Cell(r, c);
				if(cell != NULL)
				{
					CString sValue;
					if(r < 4)
					{
						const wchar_t* pszVal = cell->GetWString();
						if(pszVal != NULL)
							sValue = pszVal;
						if(r == 0 && sValue.IsEmpty()) // 以第一列的列数为准
						{
							--nMaxCol;
							break;
						}
					}
					else
					{
						if (!GetExcelValue(*cell, sValue, vecAllInfo[1][c].GetBuffer()))
							return FALSE;
					}
					vecString.emplace_back(sValue);
				}
			}
			vecAllInfo.push_back(vecString);
		}

		size_t size = vecAllInfo.size();
		FileExistAndCreate(str_url);
		// server
		CString createFilePath = str_url + L"server";//\\table\\";
		FileExistAndCreate(createFilePath);

		createFilePath = str_url + L"server\\code\\";
		FileExistAndCreate(createFilePath); // XXX: for Parameter.h
		createFilePath = str_url + L"server\\table\\";
		FileExistAndCreate(createFilePath);
		if(!Write_to_XML(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 XML数据 失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			return false;
		}
		createFilePath = str_url + L"server\\code\\";
		if(!Write_Server_C(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 C++代码 失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			return false;
		}

		// clt
		createFilePath = str_url + L"client";
		FileExistAndCreate(createFilePath);
		createFilePath = str_url + L"client\\table\\";
		FileExistAndCreate(createFilePath);
		if(!Write_AS_Binary(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 AS数据 失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			return false;
		}
		createFilePath = str_url + L"client\\code\\";
		FileExistAndCreate(createFilePath);

		if(!Write_Client_AS(vecAllInfo,createFilePath,m_vecfileName[my_index]) ||
			!Write_Client_AS_VO(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 AS代码 失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			return false;
		}

		vecAllInfo.clear();
		CString str = GetTimeString() + L"导出【";;
		str += m_vecPath[my_index] + L"】完成!";
		m_noticeList.InsertString(m_iTotalIndex++, str);

		Sucess = TRUE;
	}

	//生成as管理类文件
	if(Sucess && !Write_Client_AS_Mgr(str_url + L"client\\code\\", m_vecfileName))
	{
		CString str = GetTimeString() + L"AS管理类代码失败!";
		m_noticeList.InsertString(m_iTotalIndex++, str);
		return false;
	}

	return true;
}

void CExcelToCode::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

//	CDialogEx::OnOK();
}

bool  CExcelToCode::FileExistAndCreate(CString strFileName)
{
	CFileFind fFind;
	if(!fFind.FindFile(strFileName))
		CreateDirectory(strFileName,NULL);
	return true;
}


void CExcelToCode::OnBnClickedButtonViewDir2()
{
	// TODO: Add your control notification handler code here
	if(m_vecPath.size() < 1)
	{
		CString str = GetTimeString() + L"没有添加文件！";
		m_noticeList.InsertString(m_iTotalIndex++, str);
	}
	else
	{
		bool bRet = ConvertExcel();
		ClearVec(false);
		LPCTSTR pMsg = bRet ? L"导出操作成功！" : L"导出操作失败！";
		CString str = GetTimeString() + pMsg;
		m_noticeList.InsertString(m_iTotalIndex++, str);
		AfxMessageBox(pMsg, MB_OK | MB_ICONINFORMATION);
	}
}


void CExcelToCode::OnBnClickedButtonViewfile2()
{
	// TODO: Add your control notification handler code here
	if(m_vecPath.size() < 1)
	{
		CString str = GetTimeString() + L"没有添加文件！";
		m_noticeList.InsertString(m_iTotalIndex++, str);
	}
	else
	{
		bool bRet = ConvertExcel();
		ClearVec(false);
		LPCTSTR pMsg = bRet ? L"导出操作成功！" : L"导出操作失败！";
		CString str = GetTimeString() + pMsg;
		m_noticeList.InsertString(m_iTotalIndex++, str);
		AfxMessageBox(pMsg, MB_OK | MB_ICONINFORMATION);
	}
}

CString CExcelToCode::GetTimeString()
{
	time_t tNow = time(NULL);
	tm tmTime;
	localtime_s(&tmTime,&tNow);
	char arBuff[100];
	sprintf_s(arBuff,"%u/%02u/%02u %02u:%02u    ",tmTime.tm_year+1900,tmTime.tm_mon+1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min);
	return CString(arBuff);
}
