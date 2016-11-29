// Excel_To_Code.cpp : implementation file
//

#include "stdafx.h"
#include "OLEAuto.h"
#include "Excel_To_Code.h"
#include "afxdialogex.h"
#include "XLRange.h"
#include <vector>
#include "Write_XML.h"
// CExcel_To_Code dialog

IMPLEMENT_DYNAMIC(CExcel_To_Code, CDialogEx)

CExcel_To_Code::CExcel_To_Code(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExcel_To_Code::IDD, pParent)
	, m_strDirPath(_T(""))
	, m_strFilePath(_T(""))
	, m_iTotalIndex(0)
{
}

CExcel_To_Code::~CExcel_To_Code()
{
	m_msExcel.Quit();
}

void CExcel_To_Code::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DIR_PATH, m_strDirPath);
	DDX_Text(pDX, IDC_EDIT_FILE_PATH, m_strFilePath);
	DDX_Control(pDX, IDC_LIST_NOTICE, m_noticeList);
}


BEGIN_MESSAGE_MAP(CExcel_To_Code, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_DIR, &CExcel_To_Code::OnBnClickedButtonViewDir)
	ON_BN_CLICKED(IDC_BUTTON_VIEWFILE, &CExcel_To_Code::OnBnClickedButtonViewfile)
	ON_BN_CLICKED(IDOK, &CExcel_To_Code::OnBnClickedOk)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_VIEW_DIR2, &CExcel_To_Code::OnBnClickedButtonViewDir2)
	ON_BN_CLICKED(IDC_BUTTON_VIEWFILE2, &CExcel_To_Code::OnBnClickedButtonViewfile2)
END_MESSAGE_MAP()


// CExcel_To_Code message handlers

void CExcel_To_Code::Recurse(LPCTSTR pstr, std::vector<CString>& vecfile, std::vector<CString>& vecfilename)
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


void CExcel_To_Code::ClearVec(bool bOutput/*=true*/)
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

void CExcel_To_Code::OnBnClickedButtonViewDir()
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


void CExcel_To_Code::OnBnClickedButtonViewfile()
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


void CExcel_To_Code::OnDropFiles(HDROP hDropInfo)
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


bool CExcel_To_Code::op_excel()
{
	wchar_t m_arrcol[26] = 
	{
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	CString RunDir = szFilePath;
	int nPos = RunDir.ReverseFind(L'\\');
	if(nPos != -1) RunDir = RunDir.Left(nPos+1);
	CString str_url = RunDir;
	HRESULT hRes = 0;
	for(size_t my_index=0;my_index<m_vecfileName.size();++my_index)
	{
		if(!SUCCEEDED(m_msExcel.OpenExcelBook(m_vecPath[my_index].GetBuffer())))
		{
			CString str = GetTimeString() + L"读取【";
			str += m_vecPath[my_index].GetBuffer();
			str += L"】失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			continue;
		}
		CString col;// + m_arrcol[0];
		CString row;// = L"1";
		int i=1;
		row.Format(L"%d",i);
		CString value;
		int icolcount = 0;
		std::vector< std::vector<CString> > m_vecAllInfo;
		std::vector<CString> vecString;
		do
		{
			if(icolcount<26)
				col = m_arrcol[icolcount];
			else
			{
				col.Empty();
				col += m_arrcol[icolcount/26 - 1];
				col += m_arrcol[icolcount%26];
			}
			CString cell = col+row;
			m_msExcel.GetExcelValue(cell.GetBuffer(),value,L"STRING");
			if(!value.IsEmpty()) 
				vecString.push_back(value);
			else
				 break;
			value.Empty();
		}while(++icolcount);

		m_vecAllInfo.push_back(vecString);
		vecString.clear();
		// 刚刚确定了行号
		// 现在从第二行开始拿出来
		// 第二行是类型
		// 第三行是注释
		int iRowNum = 2;
		bool bIsEnd = false;
		do
		{
			row.Format(L"%d",iRowNum);
			iRowNum++;
			for(int i=0;i<icolcount;++i)
			{
				if(i<26)
					col = m_arrcol[i];
				else
				{
					col.Empty();
					col += m_arrcol[i/26 - 1];
					col += m_arrcol[i%26];
				}
				CString cell = col+row;
				if(iRowNum <= 5)
					hRes = m_msExcel.GetExcelValue(cell.GetBuffer(),value,L"STRING");
				else
					hRes = m_msExcel.GetExcelValue(cell.GetBuffer(),value,m_vecAllInfo[1][i].GetBuffer());
				if(hRes == E_FAIL)
				{
					CString str = GetTimeString() + L"导出【";
					str += m_vecPath[my_index].GetBuffer();
					str += L"】失败!";
					m_noticeList.InsertString(m_iTotalIndex++, str);
					return false;
				}
				if(value.IsEmpty()&&i==0
					&& iRowNum != 5)
				{
					bIsEnd = true;
					break;
				}
				vecString.push_back(value);
				value.Empty();
			}
			if(vecString.size()>0)
				m_vecAllInfo.push_back(vecString);
			vecString.clear();
		}while(!bIsEnd);

		size_t size = m_vecAllInfo.size();
		// server
		CString createFilePath = str_url + L"server";//\\table\\";
		FileExistAndCreate(createFilePath);
		createFilePath = str_url + L"server\\table\\";
		FileExistAndCreate(createFilePath);
		if(!Write_to_XML(m_vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 XML数据 失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			return false;
		}
		createFilePath = str_url + L"server\\code\\";
		FileExistAndCreate(createFilePath);
		if(!Write_Server_C(m_vecAllInfo,createFilePath,m_vecfileName[my_index]))
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
		if(!Write_AS_Binary(m_vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 AS数据 失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			return false;
		}
		createFilePath = str_url + L"client\\code\\";
		FileExistAndCreate(createFilePath);

		if(!Write_Client_AS(m_vecAllInfo,createFilePath,m_vecfileName[my_index]) ||
			!Write_Client_AS_VO(m_vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 AS代码 失败!";
			m_noticeList.InsertString(m_iTotalIndex++, str);
			return false;
		}

		m_vecAllInfo.clear();
		CString str = GetTimeString() + L"导出【";;
		str += m_vecPath[my_index] + L"】完成!";
		m_noticeList.InsertString(m_iTotalIndex++, str);
	}

	//生成as管理类文件
	if(!Write_Client_AS_Mgr(str_url + L"client\\code\\", m_vecfileName))
	{
		CString str = GetTimeString() + L"AS管理类代码失败!";
		m_noticeList.InsertString(m_iTotalIndex++, str);
		return false;
	}

	return true;
}

void CExcel_To_Code::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

//	CDialogEx::OnOK();
}
bool  CExcel_To_Code::FileExistAndCreate(CString strFileName)
{
	CFileFind fFind;
	if(!fFind.FindFile(strFileName))
		CreateDirectory(strFileName,NULL);
	return true;
}


void CExcel_To_Code::OnBnClickedButtonViewDir2()
{
	// TODO: Add your control notification handler code here
	if(m_vecPath.size() < 1)
	{
		CString str = GetTimeString() + L"没有添加文件！";
		m_noticeList.InsertString(m_iTotalIndex++, str);
	}
	else
	{
		bool bRet = op_excel();
		ClearVec(false);
		LPCTSTR pMsg = bRet ? L"导出操作成功！" : L"导出操作失败！";
		CString str = GetTimeString() + pMsg;
		m_noticeList.InsertString(m_iTotalIndex++, str);
		AfxMessageBox(pMsg, MB_OK | MB_ICONINFORMATION);
	}
}


void CExcel_To_Code::OnBnClickedButtonViewfile2()
{
	// TODO: Add your control notification handler code here
	if(m_vecPath.size() < 1)
	{
		CString str = GetTimeString() + L"没有添加文件！";
		m_noticeList.InsertString(m_iTotalIndex++, str);
	}
	else
	{
		bool bRet = op_excel();
		ClearVec(false);
		LPCTSTR pMsg = bRet ? L"导出操作成功！" : L"导出操作失败！";
		CString str = GetTimeString() + pMsg;
		m_noticeList.InsertString(m_iTotalIndex++, str);
		AfxMessageBox(pMsg, MB_OK | MB_ICONINFORMATION);
	}
}

CString CExcel_To_Code::GetTimeString()
{
	time_t tNow = time(NULL);
	tm tmTime;
	localtime_s(&tmTime,&tNow);
	char arBuff[100];
	sprintf_s(arBuff,"%u/%02u/%02u %02u:%02u    ",tmTime.tm_year+1900,tmTime.tm_mon+1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min);
	return CString(arBuff);
}