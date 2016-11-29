#include "stdafx.h"
#include "CmdExcelToCode.h"

#include "WriteXML.h"
#include "ExcelFormat.h"


using namespace std;
using namespace ExcelFormat;

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

static bool GetExcelValue2(BasicExcelCell& cell, CString &sValue, LPCTSTR szType)
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


CCmdExcelToCode::CCmdExcelToCode(void)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	CString RunDir = szFilePath;
	int nPos = RunDir.ReverseFind(L'\\');
	if(nPos != -1) 
		RunDir = RunDir.Left(nPos+1);
	m_strFilePath = RunDir + L"Generated\\";
}

CCmdExcelToCode::~CCmdExcelToCode(void)
{
}

bool CCmdExcelToCode::SetDir(LPCTSTR lpFileName)
{
	ClearVec();
	Recurse(lpFileName,m_vecPath,m_vecfileName);
	m_strDirPath = lpFileName;
	return true;
}
void CCmdExcelToCode::ExportToCode()
{
	std::cerr << static_cast<UINT32>(ConvertExcel()) << std::endl;
}

void CCmdExcelToCode::ClearVec()
{
	m_strDirPath = "";
	m_vecPath.clear();
	m_vecfileName.clear();

}

bool CCmdExcelToCode::ConvertExcel()
{
	wchar_t m_arrcol[26] = 
	{
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};
	BOOL Sucess = FALSE;
	FileExistAndCreate(m_strFilePath);
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
			std::cerr << str << std::endl;
			continue;
		}
		BasicExcelWorksheet* sheet = xls.GetWorksheet(0);
		if(sheet == NULL)
		{
			CString str = GetTimeString() + L"读取【";
			str += m_vecPath[my_index].GetBuffer();
			str += L"】失败!";
			std::cerr << str << std::endl;
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
						if (!GetExcelValue2(*cell, sValue, vecAllInfo[1][c].GetBuffer()))
							return FALSE;
					}
					vecString.emplace_back(sValue);
				}
			}
			vecAllInfo.push_back(vecString);
		}

		size_t size = vecAllInfo.size();
		FileExistAndCreate(m_strFilePath);
		// server
		CString createFilePath = m_strFilePath + L"server";//\\table\\";
		FileExistAndCreate(createFilePath);

		createFilePath = m_strFilePath + L"server\\code\\";
		FileExistAndCreate(createFilePath); // XXX: for Parameter.h
		createFilePath = m_strFilePath + L"server\\table\\";
		FileExistAndCreate(createFilePath);
		if(!Write_to_XML(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 XML数据 失败!";
			std::cerr << str << std::endl;
			return false;
		}
		createFilePath = m_strFilePath + L"server\\code\\";
		if(!Write_Server_C(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 C++代码 失败!";
			std::cerr << str << std::endl;
			return false;
		}

		// clt
		createFilePath = m_strFilePath + L"client";
		FileExistAndCreate(createFilePath);
		createFilePath = m_strFilePath + L"client\\table\\";
		FileExistAndCreate(createFilePath);
		if(!Write_AS_Binary(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 AS数据 失败!";
			std::cerr << str << std::endl;
			return false;
		}
		createFilePath = m_strFilePath + L"client\\code\\";
		FileExistAndCreate(createFilePath);

		if(!Write_Client_AS(vecAllInfo,createFilePath,m_vecfileName[my_index]) ||
			!Write_Client_AS_VO(vecAllInfo,createFilePath,m_vecfileName[my_index]))
		{
			CString str = GetTimeString() + L"导出【";
			str += m_vecfileName[my_index].GetBuffer();
			str += L"】 AS代码 失败!";
			std::cerr << str << std::endl;
			return false;
		}

		vecAllInfo.clear();
		CString str = GetTimeString() + L"导出【";;
		str += m_vecPath[my_index] + L"】完成!";
		std::cerr << str << std::endl;

		Sucess = TRUE;
	}

	//生成as管理类文件
	if(Sucess && !Write_Client_AS_Mgr(m_strFilePath + L"client\\code\\", m_vecfileName))
	{
		CString str = GetTimeString() + L"AS管理类代码失败!";
		std::cerr << str << std::endl;
		return false;
	}

	return true;
}
void CCmdExcelToCode::Recurse(LPCTSTR pstr, std::vector<CString>& vecfile, std::vector<CString>& vecfilename)
{ 
	// build a string with wildcards
	CString strWildcard(pstr);
	{
		CFileFind fir;
		BOOL bWorking = fir.FindFile(strWildcard);
		if (!bWorking)
		{
			DWORD dwError = GetLastError();

			std::cout << dwError << "." << std::endl;
		}
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
			std::cerr << strOut << std::endl;
		}
	}

	finder.Close();
}

bool  CCmdExcelToCode::FileExistAndCreate(CString strFileName)
{
	CFileFind fFind;
	if(!fFind.FindFile(strFileName))
		CreateDirectory(strFileName,NULL);
	return true;
}

CString CCmdExcelToCode::GetTimeString()
{
	time_t tNow = time(NULL);
	tm tmTime;
	localtime_s(&tmTime,&tNow);
	char arBuff[100];
	sprintf_s(arBuff,"%u/%02u/%02u %02u:%02u    ",tmTime.tm_year+1900,tmTime.tm_mon+1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min);
	return CString(arBuff);
}

bool CCmdExcelToCode::SetDstDir( LPCTSTR lpFileName )
{
	m_strFilePath = lpFileName;
	return true;
}
