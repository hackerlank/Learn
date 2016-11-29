#include "stdafx.h"
#include "WriteXML.h"

UINT8 BOM[] = { 0xEF, 0xBB, 0xBF };

class CLocaleSetter
{
public:
	CLocaleSetter() { locale::global(locale("")); }
	~CLocaleSetter() { locale::global(locale("C")); }
};

std::string U_To_UTF8(CString& data)
{
	int len = WideCharToMultiByte(CP_UTF8,0,data.GetBuffer(),-1,NULL,0,NULL,NULL);
	char* pTest = new char[len];
	WideCharToMultiByte(CP_UTF8,0,data.GetBuffer(),-1,pTest,len,NULL,NULL);
	std::string strTemp = pTest;
	delete[]pTest;
	return strTemp;
}

std::string U_To_Ansi(CString& data)
{
	int len = WideCharToMultiByte(CP_ACP,0,data.GetBuffer(),-1,NULL,0,NULL,NULL);
	char* pTest = new char[len];
	WideCharToMultiByte(CP_ACP,0,data.GetBuffer(),-1,pTest,len,NULL,NULL);
	std::string strTemp = pTest;
	delete[]pTest;
	return strTemp;
}

CString GetTableData(const CString& strData)
{
	CString strTmpData = strData;
	strTmpData.Trim(L" \n\t");
	return strTmpData;
}

string GetTableStrData(const CString& strData)
{
	CString strTmpData = strData;
	strTmpData.Trim(L" \n\t");
	return U_To_UTF8(strTmpData);
}

static ofstream* pdofs = NULL;
static ofstream* GetEFile(CString path, CString name)
{
	if (!pdofs)
	{
		CString n = path + L"..\\code\\" + name + L".inc";
		std::string strPDFileName = U_To_Ansi(n);
		pdofs = new ofstream(strPDFileName);
		if (!pdofs)
		{
			AfxMessageBox(L"文件路径错误：" + n);
			return NULL;
		}
		return pdofs;
	}
	return pdofs;
}

static void ResetEFile()
{
	if (pdofs)
	{
		delete pdofs;
		pdofs = NULL;
	}
}

bool Write_to_XML(std::vector< std::vector<CString> >& tableData,CString allPath,CString fileName)
{
	CLocaleSetter oLocaleSetter;
	CString cstrFileName = allPath+fileName+L".xml";
	std::string strFileName = U_To_Ansi(cstrFileName);
	ofstream ofs(strFileName);
	std::string title = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
	ofs << title;
	ofs << "<Table>\n";
	for(size_t i=4;i<tableData.size();++i)
	{
		ofs << "\t<Row ";
		for(size_t y=0;y<tableData[0].size();++y)
		{
			std::string strTemp = GetTableStrData(tableData[i][y]);
			std::string strcol = GetTableStrData(tableData[0][y]);
			std::string str = GetTableStrData(tableData[3][y]);
			if(str == ""
				|| _stricmp(str.c_str(), "Server") == 0 || 
				0 == _stricmp(str.c_str(), "noIndexed") || 
				0 == _stricmp(str.c_str(), "indexed"))
			{
				ofs << strcol << "=\"" << strTemp << "\" ";
			}
			else if (0 == stricmp(str.c_str(), "cname"))
			{
				ofstream* pdofs = GetEFile(allPath, fileName);
				if (pdofs)
				{
					std::string CType = GetTableStrData(tableData[i][y-1]);
					std::string ID = GetTableStrData(tableData[i][0]);
					std::string CM = GetTableStrData(tableData[i][y+1]);
					*pdofs << "DEF_" << CType << "(" << strTemp << ", " << ID << ") // " << CM << "\n";
				}
			}
			else if(_stricmp(str.c_str(), "Client") != 0 &&
				_stricmp(str.c_str(), "Skip") != 0 &&
				_stricmp(str.c_str(), "ctype") != 0 &&
				_stricmp(str.c_str(), "ccomment") != 0)
			{
				AfxMessageBox(L"Client/Server标记错误！");
				return false;
			}
		}
		ofs << "/>\n";
	}
	ofs << "</Table>\n" ;

	ResetEFile();
	return true;
}

string GetServerType(const string& strType)
{
	if(strType == "STRING")
		return "string";
	if(strType == "FLOAT")
		return "float";
	if(strType == "DOUBLE")
		return "double";
	if(strType == "BOOL")
		return "bool";
	return strType;
}

bool Write_Server_C(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName)
{
	CLocaleSetter oLocaleSetter;
	if(tableData.size()<=3) return false;
	std::string allPath = U_To_Ansi(cstrAllPath);
	std::string fileName = U_To_Ansi(csrtfileName);
	std::string className;
	std::string strBaseName;
	char ch = (char)toupper(fileName[0]);
	strBaseName +=ch;
	strBaseName += fileName.substr(1,fileName.size()-1);
	className = "C" + strBaseName + "Loader";
	strBaseName += "CFG";
	std::string structName = "S" + strBaseName;

	std::string strFileName = allPath+strBaseName+".h";
	time_t tNow = time(NULL);
	tm tmTime;
	localtime_s(&tmTime,&tNow);
	char arBuff[100];
	sprintf_s(arBuff,"%u/%02u/%02u %02u:%02u",tmTime.tm_year+1900,tmTime.tm_mon+1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min);
	CString strTitle;
	std::string vecParam = "_vecData";
	{
		ofstream ofs(strFileName);
		if(!ofs)
		{
			AfxMessageBox(L"文件路径错误：" + csrtfileName);
			return false;
		}
		ofs << BOM;
		// 标题

#if 0
		ofs << "// ******************************************************************************************************/\n";
		ofs << "// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<Ansi>\n";
		ofs << "// 文件名：\t"<< strFileName << "\n";
		ofs << "// 创建时间：\t" << arBuff << "\n";
		ofs << "// 创建人：\thulq@kingnet.com\n";
		ofs << "// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.\n";
		ofs << "// ******************************************************************************************************/\n\n\n";

		CString strUp;
		strUp = className.c_str();
		strUp.MakeUpper();
		ofs << "#ifndef _" << U_To_Ansi(strUp) << "_H\n";
		ofs << "#define _" << U_To_Ansi(strUp) << "_H\n";
		ofs << "\n";
		ofs << "#include <vector>" << "\n";
		ofs << "#include \"mydefine.h\"" << "\n";
		ofs << "class " << className << "\n";
		ofs << "{\n";
		ofs << "public:\n";
		ofs << "\t// table struct\n";
		ofs << "\tstruct " << structName << "\n";
		ofs << "\t{\n";
		for(int i=0;i<tableData[0].size();++i)
		{
			ofs << "\t\t/**\n";
			ofs << "\t\t" << U_To_Ansi(tableData[2][i]) << "\n";
			ofs << "\t\t**/\n";
			ofs << "\t\t" << U_To_Ansi(tableData[1][i]) << "\t" << "m_" << U_To_Ansi(tableData[0][i]) << ";\n";
		}
		ofs << "\t}// " << structName << " define end\n";
		ofs << "\tstd::vector< " << structName << "* >\t" << vecParam << "\n";
		ofs << "\t~" << className << "();\n";
		ofs << "\tbool LoadTableData(const std::string strPath);\n";
		ofs << "\tvoid ClearTableData();\n";
		ofs << "}\n";
		ofs << "#endif";
		ofs << "\n\n";
#else
		strTitle += L"// ******************************************************************************************************/\n";
		strTitle += L"// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>\n";
		strTitle += L"// 文件名：     "; strTitle += structName.c_str();strTitle += L".h"; strTitle+=L"\n";
		//strTitle += L"// 创建时间：   ";strTitle += arBuff;strTitle += L"\n";
		//strTitle += L"// 创建人：     hulq@kingnet.com\n";
		strTitle += L"// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.\n";
		strTitle += L"// ******************************************************************************************************/\n\n\n";
		ofs << U_To_UTF8(strTitle);
		// 正文
		CString strUp;
		strUp = className.c_str();
		strUp.MakeUpper();
		ofs << "#ifndef _" << U_To_UTF8(strUp) << "_H\n";
		ofs << "#define _" << U_To_UTF8(strUp) << "_H\n\n";
		ofs << "#include <string>\n";
		ofs << "#include <vector>\n";
		ofs << "#include \"Platform.h\"\n\n";
		ofs << "using namespace std;\n\n";
		ofs << "//struct definition for the excel table\n";
		ofs << "struct " << structName << "\n";
		ofs << "{\n";
		for(int i=0;i<(int)tableData[0].size();++i)
		{
			std::string str = GetTableStrData(tableData[3][i]);
			if(str == ""
				|| _stricmp(str.c_str(), "Server") == 0 || 
				0 == _stricmp(str.c_str(), "noIndexed") ||
				0 == _stricmp(str.c_str(), "indexed"))
			{
				if(i > 0)
					ofs << "\n";
				ofs << "\t/**\n";
				ofs << "\t" << GetTableStrData(tableData[2][i]) << "\n";
				ofs << "\t**/\n";
				ofs << "\t" << GetServerType(GetTableStrData(tableData[1][i])) << "\t" << "_" << GetTableStrData(tableData[0][i]) << ";\n";
			}
			else if (0 == stricmp(str.c_str(), "cname"))
			{
				CString a = tableData[0][i-1].GetBuffer();
				CString b = tableData[0][i].GetBuffer();
				// XXX: Do nothing
			}
			else if(_stricmp(str.c_str(), "Client") != 0 &&
				_stricmp(str.c_str(), "Skip") != 0 &&
				_stricmp(str.c_str(), "ctype") != 0 &&
				_stricmp(str.c_str(), "ccomment") != 0)
			{
				AfxMessageBox(L"Client/Server标记错误！");
				return false;
			}
		}
		ofs << "}; // " << structName << " define end\n\n";
		ofs << "//data loader for the excel table\n";
		ofs << "class " << className << "\n";
		ofs << "{\n";
		ofs << "public:\n";
		ofs << "\tstd::vector<" << structName << "*> " << vecParam << ";\n\n";
		ofs << "\t~" << className << "();\n";
		ofs << "\tbool LoadData(const std::string& strPath);\n";
		ofs << "\tvoid ClearData();\n";
		ofs << "};\n";
		ofs << "#endif";
		ofs << "\n\n";
#endif
	}
	// .h写入OK
	// .cpp文件写入开始
	{
		strFileName = allPath+strBaseName+".cpp";
		ofstream ofs(strFileName);
		if(!ofs)
		{
			AfxMessageBox(L"文件路径错误：" + csrtfileName);
			return false;
		}
		ofs << BOM;
#if 0
		ofs << "// ******************************************************************************************************/\n";
		ofs << "// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<Ansi>\n";
		ofs << "// 文件名：\t"<< strFileName << "\n";
		ofs << "// 创建时间：\t" << arBuff << "\n";
		ofs << "// 创建人：\thulq@kingnet.com\n";
		ofs << "// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.\n";
		ofs << "// ******************************************************************************************************/\n\n\n";
#else
		strTitle.Empty();
		strTitle += L"// ******************************************************************************************************/\n";
		strTitle += L"// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>\n";
		strTitle += L"// 文件名：     "; strTitle += structName.c_str();strTitle += L".cpp"; strTitle+=L"\n";
		//strTitle += L"// 创建时间：   ";strTitle += arBuff;strTitle += L"\n";
		//strTitle += L"// 创建人：     hulq@kingnet.com\n";
		strTitle += L"// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.\n";
		strTitle += L"// ******************************************************************************************************/\n\n\n";
		ofs << U_To_UTF8(strTitle);
#endif
		ofs << "#include \"" << strBaseName << ".h\"" << "\n";
		ofs << "#include \"tinyxml.h\"\n\n";
		ofs << className << "::" << "~" << className << "()" << "\n";
		ofs << "{\n";
		ofs << "\tClearData();\n";
		ofs << "}\n\n";

		ofs << "void " << className << "::" << "ClearData()" << "\n";
		ofs << "{\n";
		ofs << "\tfor(size_t i=0; i<" << vecParam << ".size();" << "++i)" << "\n";
		ofs << "\t{\n";
		ofs << "\t\t" << structName << " *p = " << vecParam << "[i];" << "\n";
		ofs << "\t\tdelete p;\n";
		ofs << "\t}\n";
		ofs << "\t" << vecParam << ".clear();\n";
		ofs << "}\n\n";

		ofs << "bool " << className << "::" << "LoadData(const std::string& strPath)" << "\n";
		ofs << "{\n";
		ofs << "\tClearData();\n";
		ofs << "\tTiXmlDocument doc;\n";
		ofs << "\tif(!doc.LoadFile(strPath.c_str(), TIXML_ENCODING_UTF8))\n";
		ofs << "\t{\n";
		ofs << "\t\tdoc.Clear();\n";
		ofs << "\t\treturn false;\n";
		ofs << "\t}\n";

		ofs << "\tTiXmlElement* pElemRoot = doc.RootElement();\n";
		ofs << "\tif(pElemRoot == NULL)\n";
		ofs << "\t{\n";
		ofs << "\t\tdoc.Clear();\n";
		ofs << "\t\treturn false;\n";
		ofs << "\t}\n";

		/*
		ofs << "\tTiXmlElement* pDataRoot = pElemRoot->FirstChildElement(\"Table\");\n";
		ofs << "\tif(pDataRoot == NULL)\n";
		ofs << "\t{\n";
		ofs << "\t\tdoc.Clear();\n";
		ofs << "\t\treturn false;\n";
		ofs << "\t}\n";
		*/

		ofs << "\tTiXmlElement* pDataElem = pElemRoot->FirstChildElement(\"Row\");\n";
		ofs << "\twhile(pDataElem != NULL)\n";
		ofs << "\t{\n";
		ofs << "\t\t" << structName << "* pData = new " << structName << ";\n";

		for(size_t i=0;i<tableData[0].size();++i)
		{
			std::string str = GetTableStrData(tableData[3][i]);
			if(str == ""
				|| _stricmp(str.c_str(), "Server") == 0 || 
				0 == _stricmp(str.c_str(), "noIndexed") ||
				0 == _stricmp(str.c_str(), "indexed"))
			{
				std::string sparam = "pstr_" + GetTableStrData(tableData[0][i]);
				std::string structParam = "_" + GetTableStrData(tableData[0][i]);
				ofs << "\t\tconst char* " << sparam << " = pDataElem->Attribute(\"" << GetTableStrData(tableData[0][i]) << "\");\n";
				CString str_comp = GetTableData(tableData[1][i]);
				if(str_comp == L"STRING")
				{
					ofs << "\t\tif(" << sparam << " != NULL)\n";
					ofs << "\t\t\tpData->" << structParam << " = " << sparam << ";\n";
					ofs << "\t\telse\n";
					ofs << "\t\t\tpData->" << structParam << " = " << "\"\";\n"; 
				}
				else if(str_comp == L"INT32"
					|| str_comp == L"UINT32"
					|| str_comp == L"INT16"
					|| str_comp == L"UINT16"
					|| str_comp == L"INT8"
					|| str_comp == L"UINT8")
				{
					ofs << "\t\tif(" << sparam << " != NULL)\n";
					ofs << "\t\t\tpData->" << structParam << " = " <<"(" << U_To_UTF8(str_comp) << ")"<< "atoi(" << sparam << ");\n";
					ofs << "\t\telse\n";
					ofs << "\t\t\tpData->" << structParam << " = " << "0;\n"; 
				}
                else if(str_comp == L"INT64" || str_comp == L"UINT64")
                {
                    ofs << "\t\tif(" << sparam << " != NULL)\n";
                    ofs << "\t\t\tpData->" << structParam << " = " <<"(" << U_To_UTF8(str_comp) << ")"<< "atoll(" << sparam << ");\n";
                    ofs << "\t\telse\n";
                    ofs << "\t\t\tpData->" << structParam << " = " << "0;\n"; 
                    
                }
				else if(str_comp == L"BOOL")
				{
					ofs << "\t\tif(" << sparam << " != NULL)\n";
					ofs << "\t\t\tpData->" << structParam << " = " << "(int)"<< "atoi(" << sparam << ")>0?true:false;\n";
					ofs << "\t\telse\n";
					ofs << "\t\t\tpData->" << structParam << " = " << "false;\n"; 
				}
				else if(str_comp == L"DOUBLE"
					|| str_comp == L"FLOAT")
				{
					ofs << "\t\tif(" << sparam << " != NULL)\n";
					ofs << "\t\t\tpData->" << structParam << " = " << "(" << U_To_UTF8(str_comp) << ")"<< "atof(" << sparam << ");\n";
					ofs << "\t\telse\n";
					ofs << "\t\t\tpData->" << structParam << " = " << "0.0f;\n"; 
				}
				else
				{
					AfxMessageBox(L"定义类型有错误！");
					return false;
				}
			}
			else if (0 == stricmp(str.c_str(), "cname"))
			{
				printf("%s", tableData[0][i].GetBuffer());
			}
			else if(_stricmp(str.c_str(), "Client") != 0 && _stricmp(str.c_str(), "Skip") != 0 &&
				_stricmp(str.c_str(), "cname") != 0 && _stricmp(str.c_str(), "ctype") != 0 && _stricmp(str.c_str(), "ccomment") != 0)
			{
				AfxMessageBox(L"Client/Server标记错误！");
				return false;
			}
		}
		ofs << "\t\t" << vecParam << ".push_back(pData);\n";
		ofs << "\t\tpDataElem = pDataElem->NextSiblingElement();\n";
		ofs << "\t}\n";
		ofs << "\tdoc.Clear();\n";
		ofs << "\treturn true;\n";
		ofs << "}\n";
		ofs << "\n\n";
	}
	return true;
}

bool Write_AS_Binary(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName)
{
	CLocaleSetter oLocaleSetter;
	CString cstrFileName = cstrAllPath+csrtfileName+L".dat";
	std::string allPath = U_To_Ansi(cstrAllPath);
	std::string fileName = U_To_Ansi(csrtfileName);
	std::string strFileName = U_To_Ansi(cstrFileName);
	ofstream ofs(strFileName,ios::binary);
	if(!ofs)
	{
		AfxMessageBox(L"文件路径错误：" + csrtfileName);
		return false;
	}
	for(size_t i=4;i<tableData.size();++i)
	{
		for(size_t col = 0;col<tableData[0].size();++col)
		{
			CString str_comp = GetTableData(tableData[1][col]);
			std::string str = GetTableStrData(tableData[3][col]);
			if(str == ""
				|| _stricmp(str.c_str(), "Client") == 0 || 
				0 == _stricmp(str.c_str(), "noIndexed") ||
				0 == _stricmp(str.c_str(), "indexed"))
			{
				if(str_comp == L"STRING")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					short size = (short)strData.size();
					ofs.write((char*)&size,2);
					ofs.write(strData.c_str(),size);
				}
				else if(str_comp == L"UINT32")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					UINT32 value = (UINT32)atoi(strData.c_str());	
					ofs.write((char*)&value,4);
				}
				else if (str_comp == L"UINT64")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					INT64 value = (INT64)_atoi64(strData.c_str());	
					ofs.write((char*)&value,8);
				}
				else if(str_comp == L"INT32")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					INT32 value = (INT32)atoi(strData.c_str());	
					ofs.write((char*)&value,4);
				}
				else if (str_comp == L"INT64")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					UINT64 value = (UINT64)_atoi64(strData.c_str());	
					ofs.write((char*)&value,8);
				}
				else if(str_comp == L"INT16"
					|| str_comp == L"UINT16")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					int value = (int)atoi(strData.c_str());
					ofs.write((char*)&value,2);
				}
				else if(str_comp == L"INT8"
					|| str_comp == L"UINT8"
					|| str_comp == L"BOOL")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					int value = (int)atoi(strData.c_str());	
					ofs.write((char*)&value,1);
				}
				else if(str_comp == L"DOUBLE"
					|| str_comp == L"FLOAT")
				{
					std::string strData = GetTableStrData(tableData[i][col]);
					float value = (float)atof(strData.c_str());	
					ofs.write((char*)&value,4);
				}
				else
				{
					AfxMessageBox(L"定义类型有错误！");
					return false;
				}
			}
			else if(_stricmp(str.c_str(), "Server") != 0 && _stricmp(str.c_str(), "Skip") != 0 &&
				_stricmp(str.c_str(), "cname") != 0 && _stricmp(str.c_str(), "ctype") != 0 && _stricmp(str.c_str(), "ccomment") != 0)
			{
				AfxMessageBox(L"Client/Server标记错误！");
				return false;
			}
		}
	}
	return true;
}

bool Write_Client_AS_VO(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName)
{
	CLocaleSetter oLocaleSetter;
	std::string allPath = U_To_Ansi(cstrAllPath);
	std::string fileName = U_To_Ansi(csrtfileName);
	if(tableData.size()<=3) return false;
	std::string className;
	char ch = (char)toupper(fileName[0]);
	className +=ch;
	className+=fileName.substr(1,fileName.size()-1);
	className += "CfgVo";
	std::string structName = className; //.substr(1,className.size()-1);

	std::string strFileName = allPath+structName+".as";
	time_t tNow = time(NULL);
	tm tmTime;
	localtime_s(&tmTime,&tNow);
	char arBuff[100];
	sprintf_s(arBuff,"%u/%02u/%02u %02u:%02u",tmTime.tm_year+1900,tmTime.tm_mon+1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min);
	CString strTitle;

	{
		ofstream ofs(strFileName);
		if(!ofs)
		{
			AfxMessageBox(L"文件路径错误：" + csrtfileName);
			return false;
		}
		// 标题

		strTitle += L"// ******************************************************************************************************/\n";
		strTitle += L"// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！\n";
		strTitle += L"// 文件名：     "; strTitle += structName.c_str();strTitle += L".as"; strTitle+=L"\n";
		//strTitle += L"// 创建时间：   ";strTitle += arBuff;strTitle += L"\n";
		//strTitle += L"// 创建人：     hulq@kingnet.com\n";
		strTitle += L"// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.\n";
		strTitle += L"// ******************************************************************************************************/\n\n\n";
		ofs << U_To_UTF8(strTitle);

		// 正文
		ofs << "package com.xkgame.persist.parseCfg\n";
		ofs << "{\n";
		bool bUInt64 = false;
		for(int i=0;i<(int)tableData[0].size();++i)
		{
			CString str_comp = GetTableData(tableData[1][i]);
			if (str_comp == L"UINT64" || str_comp == L"INT64")
			{
				bUInt64 = true;
				break;
			}
		}
		if (bUInt64)
			ofs << "\timport com.hurlant.math.BigInteger;\n";
		ofs << "\tpublic final class " << className << "\n";
		ofs << "\t{\n";
		for(int i=0;i<(int)tableData[0].size();++i)
		{
			std::string str = GetTableStrData(tableData[3][i]);
			if(str == ""
				|| _stricmp(str.c_str(), "Client") == 0 || 
				0 == _stricmp(str.c_str(), "noIndexed") ||
				0 == _stricmp(str.c_str(), "indexed"))
			{
				CString str_comp = GetTableData(tableData[1][i]);
				std::string data_type = "";
				if(str_comp == L"STRING")
				{
					data_type = "String";
				}
				else if(str_comp == L"UINT32")
				{
					data_type = "uint";
				}
				else if(str_comp == L"UINT64")
				{
					data_type = "uint64";
				}
				else if(str_comp == L"INT32")
				{
					data_type = "int";
				}
				else if(str_comp == L"INT64")
				{
					data_type = "int64";
				}
				else if(str_comp == L"INT16"
					|| str_comp == L"UINT16"
					)
				{
					data_type = "int";
				}
				else if(str_comp == L"INT8"
					|| str_comp == L"UINT8"
					)
				{
					data_type = "int";
				}
				else if(str_comp == L"BOOL")
				{
					data_type = "Boolean";
				}
				else if(str_comp == L"DOUBLE"
					|| str_comp == L"FLOAT")
				{
					data_type = "Number";
				}
				else
				{
					AfxMessageBox(L"定义类型有错误！");
					return false;
				}
				if(i > 0)
					ofs << "\n";
				ofs << "\t\t/**\n";
				ofs << "\t\t" << GetTableStrData(tableData[2][i]) << "\n";
				ofs << "\t\t**/\n";

				if (data_type == "uint64" || data_type == "int64")
					ofs << "\t\tpublic var " << GetTableStrData(tableData[0][i]) << ": BigInteger;\n";
				else
					ofs << "\t\tpublic var " << GetTableStrData(tableData[0][i]) << ":" << data_type << ";\n";
			}
			else if(_stricmp(str.c_str(), "Server") != 0 && _stricmp(str.c_str(), "Skip") != 0 &&
				_stricmp(str.c_str(), "cname") != 0 && _stricmp(str.c_str(), "ctype") != 0 && _stricmp(str.c_str(), "ccomment") != 0)
			{
				AfxMessageBox(L"Client/Server标记错误！");
				return false;
			}
		}	
		ofs << "\t}\n";
		ofs << "}\n";
	}

	return true;
}

bool Write_Client_AS(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName)
{
	CLocaleSetter oLocaleSetter;
	std::string allPath = U_To_Ansi(cstrAllPath);
	std::string fileName = U_To_Ansi(csrtfileName);
	if(tableData.size()<=3) return false;
	std::string className;
	char ch = (char)toupper(fileName[0]);
	className +=ch;
	className+=fileName.substr(1,fileName.size()-1);
	string voClassName = className + "CfgVo";	//数据类名称
	className += "CFG";
	std::string structName = className; //.substr(1,className.size()-1);

	std::string strFileName = allPath+structName+".as";
	time_t tNow = time(NULL);
	tm tmTime;
	localtime_s(&tmTime,&tNow);
	char arBuff[100];
	sprintf_s(arBuff,"%u/%02u/%02u %02u:%02u",tmTime.tm_year+1900,tmTime.tm_mon+1,tmTime.tm_mday,tmTime.tm_hour,tmTime.tm_min);
	CString strTitle;
	std::string vecParam = "items";

	//根据第四行第一列的值进行判断是否需要已第一列的值进行索引
	if(tableData.size() < 4 || tableData[3].size() <= 0)
	{
		return false;
	}
	bool bIndex = true;
	if(0 == tableData[3][0].CompareNoCase(L"noIndexed"))
	{
		bIndex = false;
	}
	

	{
		ofstream ofs(strFileName);
		if(!ofs)
		{
			AfxMessageBox(L"文件路径错误：" + csrtfileName);
			return false;
		}
		// 标题

		strTitle += L"// ******************************************************************************************************/\n";
		strTitle += L"// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！\n";
		strTitle += L"// 文件名：     "; strTitle += structName.c_str();strTitle += L".as"; strTitle+=L"\n";
		//strTitle += L"// 创建时间：   ";strTitle += arBuff;strTitle += L"\n";
		//strTitle += L"// 创建人：     hulq@kingnet.com\n";
		strTitle += L"// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.\n";
		strTitle += L"// ******************************************************************************************************/\n\n\n";
		ofs << U_To_UTF8(strTitle);
		// 正文
		ofs << "package com.xkgame.persist.parseCfg\n";
		ofs << "{\n";
		ofs << "\timport flash.utils.ByteArray;\n";
		if(bIndex)
		{
			ofs << "\timport flash.utils.Dictionary;\n";
		}
		ofs << "\timport flash.utils.Endian;\n";

		bool bUInt64 = false;
		for(int i=0;i<(int)tableData[0].size();++i)
		{
			CString str_comp = GetTableData(tableData[1][i]);
			if (str_comp == L"UINT64" || str_comp == L"INT64")
			{
				bUInt64 = true;
				break;
			}
		}
		if (bUInt64)
			ofs << "\timport net.util.BytesUtil;\n";

		ofs << "\n";
		ofs << "\tpublic final class " << className << "\n";
		ofs << "\t{\n";
	
		ofs << "\n\t\tpublic var " << vecParam;
		if(bIndex)
		{
			ofs << ": Dictionary;\n\n";
		}
		else
		{
			ofs << ": Vector.<" << voClassName << ">;\n\n";
		}

		ofs << "\t\tprivate static var _instance: " << className << " = new " << className << ";\n\n";
		ofs << "\t\tpublic static function get instance(): " << className << "\n";;
		ofs << "\t\t{\n";
		ofs << "\t\t\treturn _instance;\n";
		ofs << "\t\t}\n\n";

		ofs << "\t\tpublic function " << className << "()\n";
		ofs << "\t\t{\n";
		ofs << "\t\t\tif(_instance != null)\n";
		ofs << "\t\t\t{\n";
		ofs << "\t\t\t\treturn;\n";
		ofs << "\t\t\t}\n";
		ofs << "\t\t}\n\n";

		ofs << "\t\tpublic function LoadData(bytes:ByteArray):void\n";
		ofs << "\t\t{\n";
		ofs << "\t\t\tbytes.endian = Endian.LITTLE_ENDIAN;\n";
		ofs << "\t\t\t" << vecParam << " = new ";
		if(bIndex)
		{
			ofs << "Dictionary;\n";
		}
		else
		{
			ofs << "Vector.<" << voClassName << ">();\n";
		}

		std::vector<std::string> vecIndexs;
		ofs << "\t\t\twhile(bytes.bytesAvailable > 0)\n";
		ofs << "\t\t\t{\n";
		ofs << "\t\t\t\tvar obj:" << voClassName << " = new " << voClassName << "();\n";
		ofs << "\t\t\t\tvar size:int = 0;\n";
		for(size_t col = 0;col<tableData[0].size();++col)
		{
			std::string str = GetTableStrData(tableData[3][col]);
			bool bIndexed = (0 == _stricmp(str.c_str(), "indexed"));
			if(str == ""
				|| str == "Client" || 
				0 == _stricmp(str.c_str(), "noindexed") ||
				bIndexed)
			{
				if (bIndexed)
					vecIndexs.push_back(GetTableStrData(tableData[0][col]));

				CString str_comp = GetTableData(tableData[1][col]);
				if(str_comp == L"STRING")
				{
					ofs << "\t\t\t\tsize = bytes.readShort();\n";
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readUTFBytes(size);\n";
				}
				else if(str_comp == L"UINT32")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readUnsignedInt();\n";
				}
				else if(str_comp == L"UINT64")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "BytesUtil.readUInt64(bytes);\n";
				}
				else if(str_comp == L"INT32")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readInt();\n";
				}
				else if (str_comp == L"INT64")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "BytesUtil.readInt64(bytes);\n";
				}
				else if(str_comp == L"INT16")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readShort();\n";
				}
				else if(str_comp == L"UINT16")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readUnsignedShort();\n";
				}
				else if(str_comp == L"INT8")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readByte();\n";
				}
				else if(str_comp == L"UINT8")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readUnsignedByte();\n";
				}
				else if(str_comp == L"BOOL")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readBoolean();\n";
				}
				else if(str_comp == L"DOUBLE"
					|| str_comp == L"FLOAT")
				{
					ofs << "\t\t\t\tobj." << GetTableStrData(tableData[0][col]) << " = " << "bytes.readFloat();\n";
				}
				else
				{
					AfxMessageBox(L"定义类型有错误！");
					return false;
				}
			}
			else if(_stricmp(str.c_str(), "Server") != 0 && _stricmp(str.c_str(), "Skip") != 0 &&
				_stricmp(str.c_str(), "cname") != 0 && _stricmp(str.c_str(), "ctype") != 0 && _stricmp(str.c_str(), "ccomment") != 0)
			{
				AfxMessageBox(L"Client/Server标记错误！");
				return false;
			}
		}
		ofs << "\t\t\t\t" << vecParam;
		if(bIndex)
		{
			size_t size = vecIndexs.size();
			if (size)
			{
				ofs << "[";
				for (size_t i = 0; i < size; ++i)
				{
					ofs << "obj." << vecIndexs[i];
					if (i < size - 1)
						ofs << "+\"_\"+";
				}
				ofs << "] = obj;\n"; 
			}
			else
				ofs << "[obj." << GetTableStrData(tableData[0][0]) << "] = obj;\n"; 
		}
		else
		{
			ofs << ".push(obj);\n";
		}
		ofs << "\t\t\t}\n";
		ofs << "\t\t}\n";
		ofs << "\n";

		size_t size = vecIndexs.size();
		if (size)
		{
			ofs << "\t\tpublic function getItem(";

			for (size_t i = 0; i < size; ++i)
			{
				ofs << vecIndexs[i] << ":uint";
				if (i < size - 1)
					ofs << ",";
			}
			ofs << "):" << voClassName << "\n\t\t{\n";
			ofs << "\t\t\treturn items[";
			for (size_t i = 0; i < size; ++i)
			{
				ofs << vecIndexs[i];
				if (i < size - 1)
					ofs << "+\"_\"+";
			}
			ofs << "];\n"; 
			ofs << "\t\t}\n"; 
		}
		ofs << "\t}\n";
		ofs << "}\n";
	}
	return true;
}

bool Write_Client_AS_Mgr(CString &path, std::vector<CString> &fileNames)
{
	const std::string className = "cfgMgr";
	std::string allPath = U_To_Ansi(path);
	std::string fileName = allPath + "\\" + className + ".as";

	ofstream ofs(fileName);
	if(!ofs)
	{
		AfxMessageBox(L"文件路径错误：" + CString(fileName.c_str()));
		return false;
	}
	ofs << BOM;
	// 标题

	CString strTitle("");
	strTitle += L"// ******************************************************************************************************/\n";
	strTitle += L"// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！\n";
	strTitle += L"// 文件名：     "; strTitle += className.c_str();strTitle += L".as"; strTitle+=L"\n";
	strTitle += L"// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.\n";
	strTitle += L"// ******************************************************************************************************/\n\n\n";
	ofs << U_To_UTF8(strTitle);

	ofs << "package com.xkgame.persist.parseCfg\n";
	ofs << "{\n";
	ofs << "\tpublic class " << className << "\n";
	ofs << "\t{\n";
	ofs << "\t\tpublic static const infos: Object = {";

	size_t size = fileNames.size();
	for(size_t i = 0; i < size; ++i)
	{
		std::string name = U_To_Ansi(fileNames[i]);
		ofs << "\"" << name << ".dat\": " << name << "CFG";
		if(i < size - 1)
			ofs << ", \n\t\t\t\t";
	}

	ofs << "};\n";
	ofs << "\t}\n";
	ofs << "}\n";
	return true;
}