/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	CodeGen.cpp
//	Created:	2013/06/05	15:00
//	Organization:	
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:	
//	Version:	1.0
//	Histroy:
*********************************************************************/

#include "Document.h"
#include "tinyxml.h"
#include "Encode.h"
#include "UtilFunc.h"

static UINT8 BOM[] = { 0xEF, 0xBB, 0xBF };

bool CDocument::GenCodeFile(const char* szDestDir)
{
	if(szDestDir == NULL)
		return false;
	string strDir = szDestDir;
	strDir += PATHSEP;
	string strCPPDir = strDir + PATHSEP"CPlusPlus";
	if(mkdir(strCPPDir.c_str(), 0755) != 0 && errno == ENOENT)
	{
		cerr << strDir << " not exist!" << endl;
		return false;
	}
	_strNameSpace = "N" + _strName;
	string strTypeHeader = strCPPDir + PATHSEP + _strName + ".h";
	PrintTypeHeader(strTypeHeader);
	string strTypeCPP = strCPPDir + PATHSEP + _strName + ".cpp";
	PrintTypeCPP(strTypeCPP);

	_strClassName = "C" + _strName + "Svr";
	string strServerHeader = strCPPDir + PATHSEP + _strName + "Svr.h";
	PrintHeader(strServerHeader, true);
	string strServerCPP = strCPPDir + PATHSEP + _strName + "Svr.cpp";
	PrintCPP(strServerCPP, true);

#ifndef FORCE_GEN_CPP_CLT
	if(HasClientType(eClientCppClt) || HasClientType(eClientCppSvr))
#endif
	{
		_strClassName = "C" + _strName + "Clt";
		string strClientHeader = strCPPDir + PATHSEP + _strName + "Clt.h";
		PrintHeader(strClientHeader, false);
		string strClientCPP = strCPPDir + PATHSEP + _strName + "Clt.cpp";
		PrintCPP(strClientCPP, false);
	}

	string strProxyFile = strCPPDir + PATHSEP + "ProtProxy.h";
	if(!PrintProxyCode(strProxyFile))
		cerr << "PrintProxyCode fails! File: " << strProxyFile << endl;
	return true;
}

void CDocument::PrintTypeHeader(const string& strPath)
{
	if(_vecEnum.empty() && _vecStruct.empty())
		return;
	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的协议类型定义代码(UTF-8 With BOM)\n"
		"//  File Name:    " + _strFileName + ".h\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "#pragma once\n";
	if(_bUseVector)
		os << "#include <vector>\n";
	os << "#include <string>\n";
	os << "#include <memory>\n";
	os << "#include \"Archive.h\"\n";
	os << "#ifdef PROT_USE_XML\n";
	os << "#include \"tinyxml.h\"\n";
	os << "#endif\n";
	for(auto it = _mapProt2Doc.begin(); it != _mapProt2Doc.end(); ++it)
	{
		string strHeader = it->first + ".h";
		os << "#include \"" << strHeader << "\"\n";
	}

	os << "\nnamespace " << _strNameSpace << "\n";
	os << "{\n\n";

	if(!_vecEnum.empty() || !_vecStruct.empty())
		os << "/////////////////////以下为类型定义/////////////////////\n";
	//enum
	for(size_t i = 0, size = _vecEnum.size(); i < size; ++i)
	{
		SEnum& rEnum = _vecEnum[i];
		os << "//" << rEnum.strComment << "\n";
		os << "enum " << rEnum.strName << "\n";
		os << "{\n";
		for(size_t k = 0; k < rEnum.vecMember.size(); ++k)
		{
			SMember& rMember = rEnum.vecMember[k];
			os << "\t" << rMember.strName;
			if(!rMember.strTypeName.empty())
			{
				SRefType* pRefType = GetRefEnumItem(rMember.strTypeName);
				if(pRefType != NULL)
					os << " = N" << rMember.strTypeName;
				else
					os << " = " << rMember.strTypeName;
			}
			if(k < rEnum.vecMember.size() - 1)
				os << ",";
			if(!rMember.strComment.empty())
				os << " //" << rMember.strComment;
			os << "\n";
		}
		os << "};\n\n";
		if(rEnum.bClassType)
			continue;
		os << "#ifdef PROT_USE_XML\n";
		os << "const char* EnumValToStr(" << rEnum.strName << ");\n";
		os << "bool EnumStrToVal(const char*, " << rEnum.strName << "&);\n";
		os << "#endif //PROT_USE_XML\n";
		if(rEnum.bDesc)
			os << "const char* GetDescription(" << rEnum.strName << ");\n";
		os << "\n";
	}

	//struct declaration
	for(size_t i = 0, size = _vecDeclStruct.size(); i < size; ++i)
	{
		SStruct& rStruct = *_vecDeclStruct[i];
		os << "//" << rStruct.strComment << "\n";
		os << "struct " << rStruct.strName << ";\n";
		os << "typedef std::shared_ptr<" << rStruct.strName << "> " << rStruct.strName << "Ptr;\n";
		if(!rStruct.strVecName.empty())
			os << "typedef std::vector<" << rStruct.strName << "Ptr> " << rStruct.strVecName << ";\n";
		os << "\n";
	}

	//struct
	for(size_t i = 0, size = _vecStruct.size(); i < size; ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(rStruct.eGlobalType == eGlobalClient)
			continue;
		os << "//" << rStruct.strComment << "\n";
		if(rStruct.strSuperName.empty())
			os << "struct " << rStruct.strName << "\n";
		else
			os << "struct " << rStruct.strName << " : public " << rStruct.strSuperName << "\n";
		os << "{\n";
		bool bHasBase = false;
		for(size_t k = 0; k < rStruct.vecMember.size(); ++k)
		{
			SMember& rMember = rStruct.vecMember[k];
			if(rMember.bBase)
			{
				os << "\t" << GetTypeName(rMember.strTypeName) << "Ptr " << rMember.strName << "; //" << rMember.strComment << "\n";
				bHasBase = true;
			}
			else
			{ 
				if(rMember.bBaseVec)
					bHasBase = true;
				os << "\t" << GetTypeName(rMember.strTypeName) << " " << rMember.strName << "; //" << rMember.strComment << "\n";
			}
		}
		for(size_t k = 0; k < rStruct.vecMember.size(); ++k)
		{
			SMember& rMember = rStruct.vecMember[k];
			string strElemType;
			if(rMember.bOperator && FindElemType(rMember.strTypeName, strElemType))
			{
				os << "\n\t" << strElemType << "& operator[](size_t index);\n";
				os << "\tconst " << strElemType << "& operator[](size_t index) const;\n";
				os << "\tbool Empty() const;\n";
				os << "\tsize_t Size() const;\n";
			}
		}
		if(!rStruct.vecMember.empty())
			os << "\n";
		os << "\t" << rStruct.strName << "();\n";
		if(!rStruct.bHasBase && rStruct.vecMember.size() <= 10 && rStruct.strSuperName.empty() && !rStruct.bHasSub)
		{
			os << "\t" << rStruct.strName << "(";
			for(size_t k = 0; k < rStruct.vecMember.size(); ++k)
			{
				SMember& rMember = rStruct.vecMember[k];
				if(k != 0)
				{
					os << ", ";
					if(k % 5 == 0)
						os << "\n\t\t";
				}
				if(IsPrimType(rMember.strTypeName))
					os << GetTypeName(rMember.strTypeName) << " " << rMember.strName << "_";
				else
					os << "const " << GetTypeName(rMember.strTypeName) << "& " << rMember.strName << "_";
			}
			os << ");\n";
		}
		if(rStruct.bHasSub)
			os << "\tvirtual ~" << rStruct.strName << "() { }\n";
		if(rStruct.bMoveCtor)
		{
			os << "#ifdef __GNUG__\n";
			os << "\t" << rStruct.strName << "(const " << rStruct.strName << "& src) = default; //默认拷贝构造函数\n";
			os << "\t" << rStruct.strName << "& operator=(const " << rStruct.strName << "& rhs) = default; //默认赋值操作符\n";
			os << "#endif\n";
			os << "\t" << rStruct.strName << "(" << rStruct.strName << "&& src); //转移构造函数\n";
			os << "\t" << rStruct.strName << "& operator=(" << rStruct.strName << "&& rhs); //转移赋值操作符\n";
		}
		if(rStruct.bHasSub || !rStruct.strSuperName.empty())
		{
			os << "\tDEF_NEW_DELETE(" << rStruct.strName << "); //使用对象池\n";
			os << "\tvirtual EType_" << GetBaseClassName(rStruct.strName) << " GetClassType() const { return eType_" << rStruct.strName << "; }\n";
		}
		else if(rStruct.bUsePtr)
		{
			os << "\tDEF_NEW_DELETE(" << rStruct.strName << "); //使用对象池\n";
		}
		os << "};\n\n";
		if(rStruct.bHasSub)
		{
			os << "typedef std::shared_ptr<" << rStruct.strName << "> " << rStruct.strName << "Ptr;\n";
			os << "typedef std::weak_ptr<" << rStruct.strName << "> " << rStruct.strName << "Wtr;\n";
			if(rStruct.strVecName.empty())
				os << "\n";
			else
				os << "typedef std::vector<" << rStruct.strName << "Ptr> " << rStruct.strVecName << ";\n\n";
			os << "//父类：" << rStruct.strName << "的辅助结构体\n";
			os << "struct " << rStruct.strName << "_Wrapper\n";
			os << "{\n";
			os << "\t" << rStruct.strName << "Ptr ptr;\n";
			os << "\t" << rStruct.strName << "_Wrapper(const " << rStruct.strName << "Ptr& ptr_ = NULL) : ptr(ptr_) { }\n";
			os << "};\n\n";
		}
		else if(!rStruct.strSuperName.empty() || rStruct.bUsePtr)
		{
			os << "typedef std::shared_ptr<" << rStruct.strName << "> " << rStruct.strName << "Ptr;\n";
			os << "typedef std::weak_ptr<" << rStruct.strName << "> " << rStruct.strName << "Wtr;\n";
			if(rStruct.strVecName.empty())
				os << "\n";
			else
				os << "typedef std::vector<" << rStruct.strName << "Ptr> " << rStruct.strVecName << ";\n\n";
		}
		else if(!rStruct.strVecName.empty())
		{
			os << "typedef std::vector<" << rStruct.strName << "> " << rStruct.strVecName << ";\n\n";
		}
	}

	if(!_vecStruct.empty())
		os << "/////////////////////以下为序列化函数/////////////////////";
	for(size_t i = 0; i < _vecStruct.size(); ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(rStruct.eGlobalType == eGlobalClient)
			continue;
		os << "\nCInArchive& operator>>(CInArchive&, " << rStruct.strName << "&);\n";
		os << "COutArchive& operator<<(COutArchive&, const " << rStruct.strName << "&);\n";
		if(rStruct.bHasSub)
		{
			os << "CInArchive& operator>>(CInArchive&, " << rStruct.strName << "_Wrapper&);\n";
			os << "COutArchive& operator<<(COutArchive&, const " << rStruct.strName << "_Wrapper&);\n";
		}
		if(!rStruct.strVecName.empty() && (rStruct.bHasSub || rStruct.bUsePtr || !rStruct.strSuperName.empty()))
		{
			os << "CInArchive& operator>>(CInArchive&, " << rStruct.strVecName << "&);\n";
			os << "COutArchive& operator<<(COutArchive&, const " << rStruct.strVecName << "&);\n";
		}
	}

	if(!_vecStruct.empty())
	{
		os << "\n#ifdef PROT_USE_XML\n";
		os << "/////////////////////以下为XML转换函数/////////////////////";
		for(size_t i = 0; i < _vecStruct.size(); ++i)
		{
			SStruct& rStruct = *_vecStruct[i];
			if(rStruct.eGlobalType == eGlobalClient)
				continue;
			os << "\nbool FromXML(TiXmlElement&, " << rStruct.strName << "&);\n";
			os << "bool ToXML(const " << rStruct.strName << "&, TiXmlElement&);\n";
			if(rStruct.bHasSub)
			{
				os << "bool SuperFromXML(TiXmlElement&, " << rStruct.strName << "Ptr&);\n";
				os << "bool SuperToXML(const " << rStruct.strName << "&, TiXmlElement&);\n";
			}
			if(!rStruct.strVecName.empty())
			{
				os << "bool VectorFromXML(TiXmlElement&, " << rStruct.strVecName << "&);\n";
				os << "bool VectorToXML(const " << rStruct.strVecName << "&, TiXmlElement&);\n";
			}
		}
		os << "#endif //PROT_USE_XML\n";
	}

	os << "\n} //namespace " << _strNameSpace << "\n";

	ofstream ofile(strPath.c_str());
	ofile << BOM;
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
}

void CDocument::PrintTypeCPP(const string& strPath)
{
	if(_vecEnum.empty() && _vecStruct.empty())
		return;
	ostringstream os;
	string strTitle =
		"/************************************************************************\n"
		"//  工具自动生成的协议类型定义代码(UTF-8 With BOM)\n"
		"//  File Name:    " + _strFileName + ".cpp\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "#include \"UtilFunc.h\"\n";
	os << "#include \"" << _strName << ".h\"\n";
	os << "#include \"SessionMgr.h\"\n\n";
	os << "#ifdef _WIN32\n";
	os << "#pragma warning(disable:4700)\n";
	os << "#endif\n\n";
	os << "namespace " << _strNameSpace << "\n";
	os << "{\n\n";

	for(size_t i = 0, size = _vecEnum.size(); i < size; ++i)
	{
		SEnum& rEnum = _vecEnum[i];
		if(rEnum.bClassType)
			continue;
		list<SMember*> lstMember;
		for(size_t k = 0; k < rEnum.vecMember.size(); ++k)
		{
			SMember& rMember = rEnum.vecMember[k];
			SMember* pMember = NULL;
			auto it = lstMember.begin();
			while(it != lstMember.end())
			{
				if((*it)->qwValue == rMember.qwValue)
				{
					pMember = *it;
					break;
				}
				++it;
			}
			if(pMember != NULL)
			{
				if(pMember->strComment.empty())
					*it = &rMember;
			}
			else
			{
				lstMember.push_back(&rMember);
			}
		}
		os << "#ifdef PROT_USE_XML\n\n";
		os << "const char* EnumValToStr(" << rEnum.strName << " e)\n";
		os << "{\n";
		os << "\tswitch(e)\n";
		os << "\t{\n";
		for(auto it = lstMember.begin(); it != lstMember.end(); ++it)
		{
			SMember& rMember = **it;
			os << "\tcase " << rMember.strName << ":\n\t\treturn \"" << rMember.strName << "\";\n";
		}
		os << "\tdefault:\n\t\treturn NULL;\n";
		os << "\t}\n";
		os << "}\n\n";
		os << "bool EnumStrToVal(const char* pszEnumStr, " << rEnum.strName << "& e)\n";
		os << "{\n";
		os << "\tif(pszEnumStr == NULL)\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"pszEnumStr is NULL!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		os << "\tstatic map<string, " << rEnum.strName << "> mapStr2Val;\n";
		os << "\tif(mapStr2Val.empty())\n";
		os << "\t{\n";
		for(auto it = lstMember.begin(); it != lstMember.end(); ++it)
		{
			SMember& rMember = **it;
			os << "\t\tmapStr2Val.insert(make_pair(\"" << rMember.strName << "\", " << rMember.strName << "));\n";
		}
		os << "\t}\n";
		os << "\tauto it = mapStr2Val.find(pszEnumStr);\n";
		os << "\tif(it == mapStr2Val.end())\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"Unrecognized enum string: \" << pszEnumStr;\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		os << "\te = it->second;\n";
		os << "\treturn true;\n";
		os << "}\n\n";
		os << "#endif //PROT_USE_XML\n\n";
		if(rEnum.bDesc)
		{
			os << "const char* GetDescription(" << rEnum.strName << " e)\n";
			os << "{\n";
			os << "\tswitch(e)\n";
			os << "\t{\n";
			for(auto it = lstMember.begin(); it != lstMember.end(); ++it)
			{
				SMember& rMember = **it;
				os << "\tcase " << rMember.strName << ":\n\t\treturn \"" << rMember.strComment << "\";\n";
			}
			os << "\tdefault:\n\t\treturn \"未知错误\";\n";
			os << "\t}\n";
			os << "}\n\n";
		}
	}

	for(size_t i = 0, size = _vecStruct.size(); i < size; ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(rStruct.eGlobalType == eGlobalClient)
			continue;
		vector<SElement> vecElem;
		for(SMember& rMember : rStruct.vecMember)
			vecElem.push_back(rMember);
		os << rStruct.strName << "::" << rStruct.strName << "()";
        ostringstream os2;
		UINT32 dwCount = PrintDefaultValue(os2, vecElem);
        if (dwCount > 0)
            os << " : " << os2.str();
        else
            os << os2.str();
		os << " { }\n\n";
		if(!rStruct.bHasBase && !rStruct.bHasSub && rStruct.strSuperName.empty() && rStruct.vecMember.size() <= 10)
		{		
			os << rStruct.strName << "::" << rStruct.strName << "(";
			for(size_t k = 0; k < rStruct.vecMember.size(); ++k)
			{
				SMember& rMember = rStruct.vecMember[k];
				if(k != 0)
				{
					os << ", ";
					if(k % 5 == 0)
						os << "\n\t\t\t";
				}
				if(IsPrimType(rMember.strTypeName))
					os << GetTypeName(rMember.strTypeName) << " " << rMember.strName << "_";
				else
					os << "const " << GetTypeName(rMember.strTypeName) << "& " << rMember.strName << "_";
			}
			os << ")";
			for(size_t k = 0; k < rStruct.vecMember.size(); ++k)
			{
				SMember& rMember = rStruct.vecMember[k];
				if(k == 0)
				{
					if(rStruct.vecMember.size() >= 5)
						os << "\n\t\t\t: ";
					else
						os << " : ";
				}
				else
				{
					os << ", ";
					if(k % 5 == 0)
						os << "\n\t\t\t";
				}
				os << rMember.strName << "(" << rMember.strName << "_)";
			}
			os << " { }\n\n";
		}
		if(rStruct.bMoveCtor)
		{
			os << rStruct.strName << "::" << rStruct.strName << "(" << rStruct.strName << "&& src)";
			bool bFirstMember = true;
			if(!rStruct.strSuperName.empty())
			{
				os << " : " << rStruct.strSuperName << "(src)";
				bFirstMember = false;
			}
			vector<SMember*> vecMember;
			for(size_t k = 0; k < rStruct.vecMember.size(); ++k)
			{
				SMember& rMember = rStruct.vecMember[k];
				if(rMember.bBase)
				{
					vecMember.push_back(&rMember);
					continue;
				}
				if(bFirstMember)
				{
					os << " : ";
					bFirstMember = false;
				}
				else
				{
					os << ", ";
				}
				if(k > 0 && k % 5 == 0)
					os << "\n\t\t\t";
				if(rMember.bBaseVec || rMember.bMoveCtor)
					os << rMember.strName << "(move(src." << rMember.strName << "))";
				else
					os << rMember.strName << "(src." << rMember.strName << ")";
			}
			if(!vecMember.empty())
			{
				os << "\n{\n";
				for(size_t k = 0 ; k < vecMember.size(); ++k)
				{
					SMember& rMember = *vecMember[k];
					os << "\t" << rMember.strName << ".swap(src." << rMember.strName << ");\n";
				}
				os << "}\n\n";
			}
			else
			{
				os << " { }\n\n";
			}

			os << rStruct.strName << "& " <<  rStruct.strName << "::operator=(" << rStruct.strName << "&& rhs)\n";
			os << "{\n";
			os << "\tif(this != &rhs)\n";
			os << "\t{\n";
			os << "\t\tthis->~" << rStruct.strName << "();\n";
			os << "\t\tnew (this) " << rStruct.strName << "(rhs);\n";
			os << "\t}\n";
			os << "\treturn *this;\n";
			os << "}\n\n";
		}
		PrintStructArchive(os, rStruct);
		for(size_t k = 0; k < rStruct.vecMember.size(); ++k)
		{
			SMember& rMember = rStruct.vecMember[k];
			string strElemType;
			if(rMember.bOperator && FindElemType(rMember.strTypeName, strElemType))
			{
				os << strElemType << "& " << rStruct.strName << "::operator[](size_t index)\n";
				os << "{\n";
				os << "\treturn const_cast<" << strElemType << "&>(static_cast<const " << rStruct.strName << "&>(*this)[index]);\n";
				os << "}\n\n";
				os << "const " << strElemType << "& " << rStruct.strName << "::operator[](size_t index) const\n";
				os << "{\n";
				os << "\tif(index >= " << rMember.strName << ".size())\n";
				os << "\t{\n";
				os << "\t\tstatic " << strElemType << " s;\n";
				os << "\t\treturn s;\n";
				os << "\t}\n";
				os << "\treturn " << rMember.strName << "[index];\n";
				os << "}\n\n";
				os << "bool " << rStruct.strName << "::Empty() const { return " << rMember.strName << ".empty(); }\n\n";
				os << "size_t " << rStruct.strName << "::Size() const { return " << rMember.strName << ".size(); }\n\n";
			}
		}
		os << "#ifdef PROT_USE_XML\n\n";
		PrintStructFromXML(os, rStruct);
		PrintStructToXML(os, rStruct);
		PrintSuperFromXML(os, rStruct);
		PrintSuperToXML(os, rStruct);
		PrintVectorFromXML(os, rStruct);
		PrintVectorToXML(os, rStruct);
		os << "#endif\n\n";
	}
	os << "} //namespace " << _strNameSpace << "\n";
	ofstream ofile(strPath.c_str());
	ofile << BOM;
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
}

void CDocument::PrintFuncParamList(ostringstream& os, SFunc& rFunc, bool bHeader)
{
	for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecParam[i];
		if(bHeader)
			os << "\t";
		PrintFuncParam(os, rParam, "\t");
		if(i < size - 1 || rFunc.bReturn)
			os << ",";
		os << " //" << rParam.strComment << "\n";
	}
	if(!rFunc.bReturn)
		return;
	for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecLocParam[i];
		if(bHeader)
			os << "\t";
		if(rParam.bByRef)
			os << "\tconst " << GetTypeName(rParam.strTypeName) << "& loc_" << rParam.strName;
		else if(rParam.bBase)
			os << "\tconst " << GetTypeName(rParam.strTypeName) << "Ptr& loc_" << rParam.strName;
		else
			os << "\t" << GetTypeName(rParam.strTypeName) << " loc_" << rParam.strName;
		if(i < size - 1 || rFunc.bReturn)
			os << ",";
		os << " //" << rParam.strComment << "\n";
	}
	if(bHeader)
	{
		PrintCallBackFunc(os, rFunc, "\t\t");
		os << " = NULL";
	}
	else
	{
		PrintCallBackFunc(os, rFunc, "\t");
	}
	os << " //返回时的回调函数\n";
}

void CDocument::PrintFuncParam(ostringstream& os, SParam& rParam, const char* pszIndent)
{
	if(pszIndent != NULL)
		os << pszIndent;
	if(rParam.bByRef)
		os << "const " << GetTypeName(rParam.strTypeName) << "& " << rParam.strName;
	else if(rParam.bBase)
		os << "const " << GetTypeName(rParam.strTypeName) << "Ptr& " << rParam.strName;
	else
		os << GetTypeName(rParam.strTypeName) << " " << rParam.strName;
}

void CDocument::PrintRecvFunc(ostringstream& os, SFunc& rFunc)
{
	bool bRetParam = rFunc.bReturn;
	if(bRetParam)
	{
		os << "\tstruct S" << rFunc.strName << "Ack";
		if(HasClientType(eClientCppSvr) || HasOnlyClientType(eClientPhp))
			os << " : public CServerFuncAck\n";
		else 
			os << " : public CClientFuncAck\n";
		os << "\t{\n";
		for(size_t i = 0, size = rFunc.vecRetParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecRetParam[i];
			if(rParam.bBase)
				os << "\t\t" << GetTypeName(rParam.strTypeName) << "Ptr " << rParam.strName << "; //" << rParam.strComment << "\n";
			else
				os << "\t\t" << GetTypeName(rParam.strTypeName) << " " << rParam.strName << "; //" << rParam.strComment << "\n";
		}
		if(!rFunc.vecRetParam.empty())
			os << "\n";
		os << "\t\tS" << rFunc.strName << "Ack(IProtocol& rProtocol, ";
		if(HasClientType(eClientCppSvr) || HasOnlyClientType(eClientPhp))
			os << "UINT32 dwSvrID";
		else
			os << "UINT64 qwUsrID";
		os << ", UINT32 dwSessionID);\n";
		if(rFunc.bMultiReturn)
			os << "\t\t~S" << rFunc.strName << "Ack();\n";
		os << "\tprivate:\n";
		os << "\t\tvirtual void SendReturn(bool bRet) override;\n";
		if(rFunc.bMultiReturn)
			os << "\t\tbool _bFinish;\n";
		os << "\t};\n";
	}
	os << "\t//接收：" + rFunc.strComment << "\n";
	if(rFunc.bReturn)
		os << "\tvirtual bool OnRecv_" << rFunc.strName << "(\n";
	else
		os << "\tvirtual void OnRecv_" << rFunc.strName << "(\n";
	for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecParam[i];
		PrintFuncParam(os, rParam, "\t\t");
		if(i < size - 1 || bRetParam)
			os << ",";
		os << " //" << rParam.strComment << "\n";
	}
	if(bRetParam)
		os << "\t\tshared_func<S" << rFunc.strName << "Ack>& fnAck //返回回调函数\n";
#ifdef FORCE_GEN_RECV_IMPL
	os << "\t) { }\n\n";
#else
	os << "\t) = 0;\n\n";
#endif
}

void CDocument::PrintHeader(const string& strPath, bool bServer)
{
	bool bRetFunc = !bServer && _bHasC2SRetFunc || bServer && _bHasS2CRetFunc;
	vector<SFunc>* pVecFuncSend = bServer ? &_vecFuncS2C : &_vecFuncC2S;
	vector<SFunc>* pVecFuncRecv = bServer ? &_vecFuncC2S : &_vecFuncS2C;
	if(pVecFuncSend->empty() && pVecFuncRecv->empty())
		return;
	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的" + string(bServer ? "服务器" : "客户端") + "协议代码(UTF-8 With BOM)\n"
		"//  File Name:    " + _strFileName + ".h\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "#pragma once\n";
	if(_vecEnum.empty() && _vecStruct.empty())
	{
		if(_bUseVector)
			os << "#include <vector>\n";
		os << "#include <string>\n";
		os << "#include <memory>\n";
		//os << "#include \"ServerDefine.h\"\n";
		os << "#include \"Archive.h\"\n";
		os << "#ifdef PROT_USE_XML\n";
		os << "#include \"tinyxml.h\"\n";
		os << "#endif\n";
		for(auto it = _mapProt2Doc.begin(); it != _mapProt2Doc.end(); ++it)
		{
			string strHeader = it->first + ".h";
			os << "#include \"" << strHeader << "\"\n";
		}
	}
	else
	{
		os << "#include \"" << _strName << ".h\"\n";
	}
	os << "\nnamespace " << _strNameSpace << "\n";
	os << "{\n\n";
	os << "//协议类：" << _strComment << "\n";
	os << "class " << _strClassName << " : public IProtocol\n";
	os << "{\n";
	os << "public:\n";

	if(!pVecFuncSend->empty())
		os << "\t/////////////////////以下为发送函数/////////////////////\n";
	for(size_t i = 0, size = pVecFuncSend->size(); i < size; ++i)
	{
		SFunc& rFunc = (*pVecFuncSend)[i];
		os << "\t" << "//发送：" + rFunc.strComment << "\n";
		os << "\tbool Send_" << rFunc.strName << "( //发送给当前协议处理的" + string(bServer && !HasClientType(eClientCppSvr) ? "客户端" : "服务器") << "\n";
		PrintFuncParamList(os, rFunc, true);
		os << "\t);\n";

		if(bServer && (HasClientType(eClientCppClt) || HasClientType(eClientAs)))
		{
			os << "\tbool SendClt_" << rFunc.strName << "(const UINT64* pUsrID, UINT16 wCnt";
			if(!rFunc.vecParam.empty() || rFunc.bReturn && !rFunc.vecLocParam.empty())
				os << ",";
			os << " //发送给多个客户端\n";
			PrintFuncParamList(os, rFunc, true);
			os << "\t);\n";
		}
		else if(bServer && HasClientType(eClientPhp) || HasClientType(eClientCppSvr))
		{
			os << "\tbool SendSvr_" << rFunc.strName << "(const UINT32* pSvrID, UINT8 byCnt";
			if(!rFunc.vecParam.empty() || rFunc.bReturn)
				os << ",";
			os << " //发送给多个服务器\n";
			PrintFuncParamList(os, rFunc, true);
			os << "\t);\n";
		}
		if(!rFunc.bReturn)
		{
			os << "\tstd::string& BuildPkg_" << rFunc.strName << "( //只组包不发送\n";
			PrintFuncParamList(os, rFunc, true);
			os << "\t);\n";
			if(rFunc.bPkg)
			{
				os << "\tstd::string& BuildParamPkg_" << rFunc.strName << "( //只对参数组包\n";
				PrintFuncParamList(os, rFunc, true);
				os << "\t);\n";
				os << "\tstd::string& BuildFullPkg_" << rFunc.strName << "( //从参数包构造完整的协议函数包\n";
				os << "\t\tconst string& strParamPkg //参数包\n";
				os << "\t);\n";
			}
		}
		os << "\n";
	}
	if(!pVecFuncRecv->empty())
		os << "\t/////////////////////以下的接收函数需要重载/////////////////////\n";
	for(size_t i = 0, size = pVecFuncRecv->size(); i < size; ++i)
	{
		SFunc& rFunc = (*pVecFuncRecv)[i];
		PrintRecvFunc(os, rFunc);
	}
	os << "\t/////////////////////以下为协议接口函数/////////////////////\n";
	os << "\tvirtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;\n\n";
	if(bRetFunc)
		os << "\tvirtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;\n\n";
	else
		os << "\tvirtual void OnTimeOut(UINT8, UINT32) override { }\n\n";
	os << "\tvirtual UINT8 GetProtID() const override { return " << _ID << "; }\n\n";
	os << "\tvirtual bool IsForClient() const override { return " << ((HasClientType(eClientCppClt) || HasClientType(eClientAs)) ? "true" : "false") << "; }\n\n";
	os << "\tstd::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }\n\n";
	os << "protected:\n";
	if(!pVecFuncRecv->empty())
		os << "\t/////////////////////协议处理函数/////////////////////\n";
	for(size_t i = 0, size = pVecFuncRecv->size(); i < size; ++i)
	{
		SFunc& rFunc = (*pVecFuncRecv)[i];
		os << "\tbool _DoRecv_" << rFunc.strName << "(const char* pBuf, UINT32 dwLen);\n";
	}
	if(bRetFunc)
	{
		os << "\n\t/////////////////////协议返回函数/////////////////////\n";
		for(size_t i = 0, size = pVecFuncSend->size(); i < size; ++i)
		{
			SFunc& rFunc = (*pVecFuncSend)[i];
			if(!rFunc.bReturn)
				continue;
			os << "\tbool _DoReturn_" << rFunc.strName << "(const char* pBuf, UINT32 dwLen);\n";
			os << "\tvoid _OnTimeOut_" << rFunc.strName << "(UINT32 dwSessionID);\n";
		}
	}
	os << "\nprivate:\n";
	os << "\ttypedef bool (" << _strClassName << "::*THandleFunc)(const char* pBuf, UINT32 dwLen);\n";
	if(bRetFunc)
		os << "\tstatic THandleFunc _ReturnFuncs[];\n";
	os << "\tstatic THandleFunc _HandleFuncs[];\n";
	if(bRetFunc)
	{
		os << "\n\ttypedef void (" << _strClassName << "::*TTimeOutFunc)(UINT32 dwSessionID);\n";
		os << "\tstatic TTimeOutFunc _TimeoutFuncs[];\n";
	}
	os << "\tstd::string _strPkg;\n";
	os << "\nprotected:\n";
	os << "\tCInArchive _oInArchive;\n";
	os << "};\n\n";	
	os << "} //namespace " << _strNameSpace << "\n";

	ofstream ofile(strPath.c_str());
	ofile << BOM;
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
}

void CDocument::PrintCallBackFunc(ostringstream& os, SFunc& rFunc, const char* pszIndent)
{
	os << pszIndent << "boost::function<void (UINT8 byRet_";
	if(rFunc.dwCbkParamCount > 0)
		os << ",";
	os << " //0为成功，1为失败，2为超时\n";
	if(rFunc.bKeepParam)
	{
		UINT32 dwKeepCount = 0;
		for(UINT32 i = 0, size = (UINT32)rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			if(!rParam.bKeep)
				continue;
			++dwKeepCount;
			os << "\t";
			PrintFuncParam(os, rParam, pszIndent);
			if(dwKeepCount < rFunc.dwCbkParamCount)
				os << ",";
			os << " //(本地保存的函数参数)" << rParam.strComment << "\n";
		}
	}
	for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecLocParam[i];
		os << pszIndent;
		if(rParam.bByRef)
			os << "\tconst " << GetTypeName(rParam.strTypeName) << "& loc_" << rParam.strName;
		else if(rParam.bBase)
			os << "\tconst " << GetTypeName(rParam.strTypeName) << "Ptr& loc_" << rParam.strName;
		else
			os << "\t" << GetTypeName(rParam.strTypeName) << " loc_" << rParam.strName;
		if(i < size - 1 || !rFunc.vecRetParam.empty())
			os << ",";
		os << " //(本地保存的变量)" << rParam.strComment << "\n";
	}
	for(size_t i = 0, size = rFunc.vecRetParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecRetParam[i];
		os << "\t";
		PrintFuncParam(os, rParam, pszIndent);
		if(i < size - 1)
			os << ",";
		os << " //(返回值)" << rParam.strComment << "\n";
	}
	os << pszIndent << ")> fnOnReturn_";
}

string CDocument::GetSessionDataType(SFunc& rFunc)
{
	string strType = "typedef std::tuple<decltype(fnOnReturn_)";
	if(rFunc.bKeepParam)
	{
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			if(!rParam.bKeep)
				continue;
			strType += ", " + GetTypeName(rParam.strTypeName);
		}
	}
	for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecLocParam[i];
		strType += ", " + GetTypeName(rParam.strTypeName);
	}
	strType += "> TSessData;";
	return strType;
}

void CDocument::PrintRetParam(ostringstream& os, SFunc& rFunc)
{
	if(!rFunc.bReturn)
		return;
	os << "\tif(_pSessionMgr == NULL)\n";
    os << "\t{\n";
    os << "\t\tLOG_CRI << \"_pSessionMgr == NULL\";";
	os << "\t\treturn false;\n";
    os << "\t}\n";
	os << "\tUINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, " << -rFunc.iRetID << ");\n";
	os << "\t" << GetSessionDataType(rFunc) << "\n";
	os << "\tstd::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_";
	for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecParam[i];
		if(rParam.bKeep)
			os << ", " << rParam.strName;
	}
	for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecLocParam[i];
		os << ", loc_" << rParam.strName;
	}
	os << "));\n";	
	os << "\t_pSessionMgr->StoreData(dwSessionID_, pSessData_);\n";
}

void CDocument::PrintArchive(ostringstream& os, SFunc& rFunc, bool bServer, bool bParam /*= false*/)
{
	if(!bParam)
	{
		os << "\tUINT8 byProtID_ = GetProtID();\n";
		os << "\tconst UINT8 byFuncID_ = " << rFunc.ID << ";\n";
	}
	for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecParam[i];
		if(rParam.bBase)
			os << "\t" << GetTypeName(rParam.strTypeName) << "_Wrapper " << rParam.strName << "_Wrapper(" << rParam.strName << ");\n";
	}
	if(bServer || HasClientType(eClientCppSvr))
	{
		os << "\ttry\n";
		os << "\t{\n\t";
	}
	os << "\tar";
	if(!bParam)
		os << " << byProtID_ << byFuncID_";
	if(rFunc.bReturn)
		os << " << dwSessionID_";
	for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecParam[i];
		if(rParam.bBase)
			os << " << " << rParam.strName << "_Wrapper";
		else
			os << " << " << GetTypeConvert(rParam.byByte) << rParam.strName;
	}
	os << ";\n";
}

bool CDocument::GetDefaultValue(const SElement& rElement, string& strValue)
{
	if(!IsPrimType(rElement.strTypeName))
		return false;
	if(IsEnumType(rElement.strTypeName) || IsRefEnumType(rElement.strTypeName))
	{
		if(rElement.strDefaultValue.empty())
		{
			strValue = "(" + GetTypeName(rElement.strTypeName) + ")0";
		}
		else
		{
			if(IsRefEnumType(rElement.strTypeName))
				strValue = "N" + rElement.strDefaultValue;
			else
				strValue = rElement.strDefaultValue;
		}
	}
	else if(rElement.strTypeName == "bool")
	{
		if(rElement.strDefaultValue.empty())
			strValue = "false";
		else
			strValue = rElement.strDefaultValue;
	}
	else
	{
		if(rElement.strDefaultValue.empty())
			strValue = "0";
		else
			strValue = rElement.strDefaultValue;
	}
	return true;
}

UINT32 CDocument::PrintDefaultValue(ostringstream& os, const vector<SElement>& vecElement)
{
	UINT32 dwPrimTypeCount = 0;
	for(const SElement& rElement : vecElement)
	{
		if(IsPrimType(rElement.strTypeName))
			++dwPrimTypeCount;
	}
	if(dwPrimTypeCount > 0)
	{
		dwPrimTypeCount = 0;
		for(const SElement& rElement : vecElement)
		{
			string strDefaultValue;
			if(GetDefaultValue(rElement, strDefaultValue))
			{
				if(dwPrimTypeCount > 0)
				{
					os << ", ";
					if(dwPrimTypeCount % 5 == 0)
						os << "\n\t\t\t";
				}
				os << rElement.strName << "(" << strDefaultValue << ")";
				++dwPrimTypeCount;
			}
		}
	}
	return dwPrimTypeCount;
}

void CDocument::PrintCPP(const string& strPath, bool bServer)
{
	bool bRetFunc = !bServer && _bHasC2SRetFunc || bServer && _bHasS2CRetFunc;
	vector<SFunc>* pVecFuncSend = bServer ? &_vecFuncS2C : &_vecFuncC2S;
	vector<SFunc>* pVecFuncRecv = bServer ? &_vecFuncC2S : &_vecFuncS2C;
	if(pVecFuncSend->empty() && pVecFuncRecv->empty())
		return;
	ostringstream os;
	string strTitle =
		"/************************************************************************\n"
		"//  工具自动生成的" + string(bServer ? "服务器" : "客户端") + "协议代码(UTF-8 With BOM)\n"
		"//  File Name:    " + _strFileName + ".cpp\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "#include \"UtilFunc.h\"\n";
	os << "#include \"" << _strName;
	if(bServer)
		os << "Svr";
	else
		os << "Clt";
	os << ".h\"\n";
	os << "#include \"SessionMgr.h\"\n\n";
	os << "#ifdef _WIN32\n";
	os << "#pragma warning(disable:4700)\n";
	os << "#endif\n\n";

	os << "namespace " << _strNameSpace << "\n";
	os << "{\n\n";
	if(bRetFunc)
	{
		os << _strClassName << "::THandleFunc " << _strClassName << "::_ReturnFuncs[] =\n";
		os << "{\n";
		for(size_t i = 0, size = pVecFuncSend->size(); i < size; ++i)
		{
			SFunc& rFunc = (*pVecFuncSend)[i];
			if(rFunc.bReturn)
				os << "\t&" << _strClassName << "::_DoReturn_" << rFunc.strName << ", //FuncID: " << rFunc.iRetID << "\n";
		}
		os << "};\n\n";
	}
	os << _strClassName << "::THandleFunc " << _strClassName << "::_HandleFuncs[] =\n";
	os << "{\n";
	for(size_t i = 0, size = pVecFuncRecv->size(); i < size; ++i)
	{
		SFunc& rFunc = (*pVecFuncRecv)[i];
		os << "\t&" << _strClassName << "::_DoRecv_" << rFunc.strName << ", //FuncID: " << (i + 1) << "\n";
	}
	if(pVecFuncRecv->empty())
		os << "\tNULL" << "\n";
	os << "};\n\n";
	if(bRetFunc)
	{
		os << _strClassName << "::TTimeOutFunc " << _strClassName << "::_TimeoutFuncs[] =\n";
		os << "{\n";
		for(size_t i = 0, size = pVecFuncSend->size(); i < size; ++i)
		{
			SFunc& rFunc = (*pVecFuncSend)[i];
			if(rFunc.bReturn)
				os << "\t&" << _strClassName << "::_OnTimeOut_" << rFunc.strName << ", //FuncID: " << -rFunc.iRetID << "\n";
		}
		os << "};\n\n";
	}

	os << "bool " << _strClassName << "::HandleMessage(const char* pBuf, UINT32 dwLen)\n";
	os << "{\n";
	if(!pVecFuncRecv->empty() || bRetFunc)
	{
		os << "\tif(pBuf == NULL || dwLen == 0)\n";
		os << "\t\treturn false;\n";
		os << "\tINT8 byFuncID = pBuf[0];\n";
		os << "\tif(byFuncID == 0";
		if(!pVecFuncRecv->empty())
			os << " || byFuncID > (INT8)ARRAYSIZE(_HandleFuncs)";
		if(bRetFunc)
			os << "\n\t\t || byFuncID < -(INT8)ARRAYSIZE(_ReturnFuncs)";
		os << ")\n";
		if(bServer || HasClientType(eClientCppSvr))
		{
			os << "\t{\n";
			os << "#ifdef _DEBUG\n";
			os << "\t\tLOG_CRI << \"byFuncID is invalid: \" << byFuncID;\n";
			os << "#endif\n";
			os << "\t\treturn false;\n";
			os << "\t}\n";
		}
		else
		{
			os << "\t\treturn false;\n";
		}
		os << "\tpBuf += sizeof(INT8);\n";
		os << "\tdwLen -= sizeof(INT8);\n";
		os << "\tif(byFuncID > 0)\n";
		os << "\t{\n";
		os << "\t\t--byFuncID;\n";
		os << "\t\tif(_HandleFuncs[static_cast<UINT8>(byFuncID)] != NULL)\n";
		os << "\t\t\treturn (this->*_HandleFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);\n";
		os << "\t}\n";
		if(bRetFunc)
		{
			os << "\telse\n";
			os << "\t{\n";
			os << "\t\tbyFuncID = -1 - byFuncID;\n";
			os << "\t\tif(_ReturnFuncs[static_cast<UINT8>(byFuncID)] != NULL)\n";
			os << "\t\t\treturn (this->*_ReturnFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);\n";
			os << "\t}\n";
		}
		os << "\treturn true;\n";
	}
	else
	{
		os << "\treturn true;\n";
	}
	os << "}\n\n";

	if(bRetFunc)
	{
		os << "void " << _strClassName << "::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)\n";
		os << "{\n";
		os << "\tif(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))\n";
		os << "\t\treturn;\n";
		os << "\t(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);\n";
		os << "}\n\n";
	}

	//Send
	for(size_t i = 0, size = pVecFuncSend->size(); i < size; ++i)
	{
		SFunc& rFunc = (*pVecFuncSend)[i];
		os << "//发送：" + rFunc.strComment << "\n";
		os << "bool " << _strClassName << "::Send_" << rFunc.strName << "(\n";
		PrintFuncParamList(os, rFunc, false);
		os << ")\n";
		os << "{\n";

		PrintRetParam(os, rFunc);
		os << "\tCOutArchive ar;\n";
		PrintArchive(os, rFunc, bServer);
		if(bServer || HasClientType(eClientCppSvr))
		{
			os << "\t}\n";
			os << "\tcatch(const char* szExcept)\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"Send exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
			os << "\t\treturn false;\n";
			os << "\t}\n";
		}
		os << "\tUINT32 dwLen_ = 0;\n";
		os << "\tchar* pBuf_ = ar.GetBuf(dwLen_);\n";
		os << "\tif(_pConnHandler != NULL)\n";
		os << "\t\treturn _pConnHandler->Send(pBuf_, dwLen_);\n";
		os << "\treturn false;\n";
		os << "}\n\n";

		if(bServer && (HasClientType(eClientCppClt) || HasClientType(eClientAs)))
		{
			os << "bool " << _strClassName << "::SendClt_" << rFunc.strName << "(const UINT64* pUsrID_, UINT16 wCnt_";
			if(!rFunc.vecParam.empty() || rFunc.bReturn && !rFunc.vecLocParam.empty())
				os << ",";
			os << "\n";
			PrintFuncParamList(os, rFunc, false);
			os << ")\n";
			os << "{\n";
			PrintRetParam(os, rFunc);
			os << "\tCOutArchive ar;\n";
			PrintArchive(os, rFunc, bServer);
			os << "\t}\n";
			os << "\tcatch(const char* szExcept)\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"SendClt exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
			os << "\t\treturn false;\n";
			os << "\t}\n";
			os << "\tUINT32 dwLen_ = 0;\n";
			os << "\tchar* pBuf_ = ar.GetBuf(dwLen_);\n";
			os << "\tif(_pConnHandler != NULL)\n";
			os << "\t\treturn _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);\n";
			os << "\treturn false;\n";
			os << "}\n\n";
		}
		else if(bServer && HasClientType(eClientPhp) || HasClientType(eClientCppSvr))
		{
			os << "bool " << _strClassName << "::SendSvr_" << rFunc.strName << "(const UINT32* pSvrID_, UINT8 byCnt_";
			if(!rFunc.vecParam.empty() || rFunc.bReturn)
				os << ",";
			os << "\n";
			PrintFuncParamList(os, rFunc, false);
			os << ")\n";
			os << "{\n";
			PrintRetParam(os, rFunc);
			os << "\tCOutArchive ar;\n";
			PrintArchive(os, rFunc, bServer);
			if(bServer || HasClientType(eClientCppSvr))
			{
				os << "\t}\n";
				os << "\tcatch(const char* szExcept)\n";
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"SendSvr exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
				os << "\t\treturn false;\n";
				os << "\t}\n";
			}
			os << "\tUINT32 dwLen_ = 0;\n";
			os << "\tchar* pBuf_ = ar.GetBuf(dwLen_);\n";
			os << "\tif(_pConnHandler != NULL)\n";
			os << "\t\treturn _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);\n";
			os << "\treturn false;\n";
			os << "}\n\n";
		}

		if(rFunc.bReturn)
			continue;

		os << "std::string& " << _strClassName << "::BuildPkg_" << rFunc.strName << "(\n";
		PrintFuncParamList(os, rFunc, false);
		os << ")\n";
		os << "{\n";
		os << "\tCOutArchive ar(_strPkg);\n";
		PrintArchive(os, rFunc, bServer);
		if(bServer || HasClientType(eClientCppSvr))
		{
			os << "\t}\n";
			os << "\tcatch(const char* szExcept)\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"BuildPkg exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
			os << "\t\t_strPkg.clear();\n";
			os << "\t}\n";
		}
		os << "\treturn _strPkg;\n";
		os << "}\n\n";

		if(!rFunc.bPkg)
			continue;

		os << "std::string& " << _strClassName << "::BuildParamPkg_" << rFunc.strName << "(\n";
		PrintFuncParamList(os, rFunc, false);
		os << ")\n";
		os << "{\n";
		os << "\tCOutArchive ar(_strPkg);\n";
		PrintArchive(os, rFunc, bServer, true);
		if(bServer || HasClientType(eClientCppSvr))
		{
			os << "\t}\n";
			os << "\tcatch(const char* szExcept)\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"BuildPkg exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
			os << "\t\t_strPkg.clear();\n";
			os << "\t}\n";
		}
		os << "\treturn _strPkg;\n";
		os << "}\n\n";

		os << "std::string& " << _strClassName << "::BuildFullPkg_" << rFunc.strName << "(const string& strParamPkg)\n";
		os << "{\n";
		os << "\tCOutArchive ar(_strPkg);\n";
		os << "\tUINT8 byProtID_ = GetProtID();\n";
		os << "\tconst UINT8 byFuncID_ = " << rFunc.ID << ";\n";
		os << "\tar << byProtID_ << byFuncID_;\n";
		os << "\t_strPkg += strParamPkg;\n";
		os << "\treturn _strPkg;\n";
		os << "}\n\n";
	}

	//Receive
	for(size_t i = 0, size = pVecFuncRecv->size(); i < size; ++i)
	{
		SFunc& rFunc = (*pVecFuncRecv)[i];
		bool bRetParam = rFunc.bReturn;
		if(bRetParam)
		{
			vector<SElement> vecElem;
			for(SParam& rParam : rFunc.vecRetParam)
				vecElem.push_back(rParam);
			os << _strClassName << "::S" << rFunc.strName << "Ack::S" << rFunc.strName << "Ack(IProtocol& rProtocol, ";
			if(HasClientType(eClientCppSvr) || HasOnlyClientType(eClientPhp))
				os << "UINT32 dwSvrID";
			else
				os << "UINT64 qwUsrID";
			os << ", UINT32 dwSessionID)";

            os << " : \n\t\t\t";
			if(HasClientType(eClientCppSvr) || HasOnlyClientType(eClientPhp))
				os << "CServerFuncAck(rProtocol, dwSvrID, dwSessionID)";
			else
				os << "CClientFuncAck(rProtocol, qwUsrID, dwSessionID)";
			if(rFunc.bMultiReturn)
				os << ", _bFinish(false)";

            ostringstream os2;
			UINT32 dwCount = PrintDefaultValue(os2, vecElem);
            if (dwCount > 0)
                os <<  ", \n\t\t\t" << os2.str();

			if(rFunc.bMultiReturn)
				os << " { _bMulRet = true; }\n\n";
			else
				os << " { }\n\n";
			if(rFunc.bMultiReturn)
			{
				os << _strClassName << "::S" << rFunc.strName << "Ack::~S" << rFunc.strName << "Ack()\n";
				os << "{\n";
				for(size_t k = 0; k < rFunc.vecRetParam.size(); ++k)
				{
					SParam& rParam = rFunc.vecRetParam[k];
					if(IsPrimType(rParam.strTypeName))
					{
						string strDefaultValue;
						if(GetDefaultValue(rParam, strDefaultValue))
							os << "\t" << rParam.strName << " = " << strDefaultValue << ";\n";
					}
					else if(IsStringType(rParam.strTypeName) || IsVectorType(rParam.strTypeName))
					{
						os << "\t" << rParam.strName << ".clear();\n";
					}
				}
				os << "\t_bFinish = true;\n";
				os << "\tSendReturn(true);\n";
				os << "}\n\n";
			}
			os << "void " << _strClassName << "::S" << rFunc.strName << "Ack::SendReturn(bool bRet_)\n";
			os << "{\n";
			os << "\tUINT8 byProtID_ = _rProtocol.GetProtID();\n";
			os << "\tconst INT8 byFuncID_ = " << rFunc.iRetID << ";\n";
			for(size_t k = 0; k < rFunc.vecRetParam.size(); ++k)
			{
				SParam& rParam = rFunc.vecRetParam[k];
				if(rParam.bBase)
				{
					os << "\t" << GetTypeName(rParam.strTypeName) << "_Wrapper " << rParam.strName << "_RetWrapper;\n";
					os << "\t" << rParam.strName << "_RetWrapper.ptr = " << rParam.strName << ";\n";
				}
			}
			os << "\tCOutArchive arOut;\n";
			if(bServer || HasClientType(eClientCppSvr))
			{
				os << "\ttry\n";
				os << "\t{\n\t";
			}
			os << "\tarOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_";
			if(rFunc.bMultiReturn)
				os << " << _bFinish";
			for(size_t k = 0; k < rFunc.vecRetParam.size(); ++k)
			{
				SParam& rParam = rFunc.vecRetParam[k];
				if(rParam.bBase)
					os << " << " << rParam.strName << "_RetWrapper";
				else
					os << " << " << GetTypeConvert(rParam.byByte) << rParam.strName;
			}
			os << ";\n";
			if(bServer || HasClientType(eClientCppSvr))
			{
				os << "\t}\n";
				os << "\tcatch(const char* szExcept)\n";
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"Return exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
				os << "\t\treturn;\n";
				os << "\t}\n";
			}
			os << "\tUINT32 dwLen_ = 0;\n";
			os << "\tconst char* pBuf_ = arOut.GetBuf(dwLen_);\n";
			os << "\tIConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();\n";
			os << "\tif(pConHandler != NULL)\n";
			if(HasClientType(eClientCppSvr) || HasOnlyClientType(eClientPhp))
				os << "\t\tpConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);\n";
			else
				os << "\t\tpConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);\n";
			os << "\t_bReturned = true;\n";
			os << "}\n\n";
		}
		os << "bool " << _strClassName << "::_DoRecv_" << rFunc.strName << "(const char* pBuf_, UINT32 dwLen_)\n";
		os << "{\n";
		if(rFunc.bReturn)
			os << "\tUINT32 dwSessionID_ = 0;\n";
		vector<string> vecBase;
		vector<string> vecBaseVec;
		for(size_t k = 0; k < rFunc.vecParam.size(); ++k)
		{
			SParam& rParam = rFunc.vecParam[k];
			if(rParam.bBase)
			{
				os << "\t" << GetTypeName(rParam.strTypeName) << "_Wrapper " << rParam.strName << ";\n";
				vecBase.push_back(rParam.strName);
			}
			else
			{
				os << "\t" << GetTypeName(rParam.strTypeName) << " " << rParam.strName;
				string strDefaultValue;
				if(GetDefaultValue(rParam, strDefaultValue))
					os << " = " << strDefaultValue;
				os << ";\n";
				if(rParam.bBaseVec)
					vecBaseVec.push_back(rParam.strName);
			}
		}
		if(rFunc.bReturn || !rFunc.vecParam.empty())
		{
			os << "\tnew (&_oInArchive) CInArchive(pBuf_, dwLen_);\n";
			if(bServer || HasClientType(eClientCppSvr))
			{
				os << "\ttry\n";
				os << "\t{\n\t";
			}
			os << "\t_oInArchive";
			if(rFunc.bReturn)
				os << " >> dwSessionID_";
			for(size_t k = 0; k < rFunc.vecParam.size(); ++k)
			{
				SParam& rParam = rFunc.vecParam[k];
				os << " >> " << GetTypeConvert(rParam.byByte) << rParam.strName;
			}
			os << ";\n";
			if(bServer || HasClientType(eClientCppSvr))
			{
				os << "\t}\n";
				os << "\tcatch(const char* szExcept)\n";
				os << "\t{\n";
				if(HasOnlyClientType(eClientPhp) || HasClientType(eClientCppSvr))
				{
					os << "\t\tLOG_CRI << \"DoRecv exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
				}
				else
				{
					os << "#ifdef _DEBUG\n";
					os << "\t\tLOG_CRI << \"DoRecv exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
					os << "#else\n";
					os << "\t\tUNUSED(szExcept);\n";
					os << "#endif\n";
				}
				os << "\t\treturn false;\n";
				os << "\t}\n";
			}
		}
		if(rFunc.bReturn)
		{
			if(HasClientType(eClientCppSvr) || HasOnlyClientType(eClientPhp))
				os << "\tshared_func<S" << rFunc.strName << "Ack> fnAck_(new S" << rFunc.strName << "Ack(*this, GetCurSvrID(), dwSessionID_));\n";
			else
				os << "\tshared_func<S" << rFunc.strName << "Ack> fnAck_(new S" << rFunc.strName << "Ack(*this, GetCurUsrID(), dwSessionID_));\n";
			os << "\tbool bRet_ = OnRecv_" << rFunc.strName << "(";
			bool bHasPrev = false;
			for(size_t k = 0; k < rFunc.vecParam.size(); ++k)
			{
				SParam& rParam = rFunc.vecParam[k];
				if(bHasPrev)
					os << ", ";
				else
					bHasPrev = true;
				if(rParam.bBase)
					os << rParam.strName << ".ptr";
				else
					os << rParam.strName;
			}
			if(bHasPrev)
				os << ", ";
			os << "fnAck_);\n";
			os << "\tif(fnAck_.unique() && !fnAck_->HasReturned())\n";
			os << "\t\tfnAck_(bRet_);\n";
			os << "\treturn true;\n";
		}
		else
		{
			os << "\tOnRecv_" << rFunc.strName << "(";
			for(size_t k = 0; k < rFunc.vecParam.size(); ++k)
			{
				SParam& rParam = rFunc.vecParam[k];
				if(rParam.bBase)
					os << rParam.strName << ".ptr";
				else
					os << rParam.strName;
				if(k < rFunc.vecParam.size() - 1)
					os << ", ";
			}
			os << ");\n";
			os << "\treturn true;\n";
		}
		os << "}\n\n";
	}

	//Return
	for(size_t i = 0, size = pVecFuncSend->size(); i < size; ++i)
	{
		SFunc& rFunc = (*pVecFuncSend)[i];
		if(!rFunc.bReturn)
			continue;
		os << "bool " << _strClassName << "::_DoReturn_" << rFunc.strName << "(const char* pBuf_, UINT32 dwLen_)\n";
		os << "{\n";
		os << "\tUINT32 dwSessionID_ = 0;\n";
		os << "\tbool bRet_ = false;\n";
		if(rFunc.bMultiReturn)
			os << "\tbool bFinish_ = false;\n";
		for(SParam& rParam : rFunc.vecRetParam)
		{
			if(rParam.bBase)
			{
				os << "\t" << GetTypeName(rParam.strTypeName) << "_Wrapper " << rParam.strName;
			}
			else
			{
				os << "\t" << GetTypeName(rParam.strTypeName) << " " << rParam.strName;
				string strDefaultValue;
				if(GetDefaultValue(rParam, strDefaultValue))
					os << " = " << strDefaultValue;
			}
			os << ";\n";
		}
		os << "\tnew (&_oInArchive) CInArchive(pBuf_, dwLen_);\n";
		if(bServer || HasClientType(eClientCppSvr))
		{
			os << "\ttry\n";
			os << "\t{\n\t";
		}
		os << "\t_oInArchive >> dwSessionID_ >> bRet_";
		if(rFunc.bMultiReturn)
			os << " >> bFinish_";
		for(size_t k = 0; k < rFunc.vecRetParam.size(); ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			os << " >> " << GetTypeConvert(rParam.byByte) << rParam.strName;
		}
		os << ";\n";
		if(bServer || HasClientType(eClientCppSvr))
		{
			os << "\t}\n";
			os << "\tcatch(const char* szExcept)\n";
			os << "\t{\n";
			if(HasOnlyClientType(eClientPhp) || HasClientType(eClientCppSvr))
			{
				os << "\t\tLOG_CRI << \"DoReturn exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
			}
			else
			{
				os << "#ifdef _DEBUG\n";
				os << "\t\tLOG_CRI << \"DoReturn exception: \" << szExcept << \", Protocol: " << _ID << ", Function: " << rFunc.ID << "\";\n";
				os << "#else\n";
				os << "\t\tUNUSED(szExcept);\n";
				os << "#endif\n";
			}
			os << "\t\treturn false;\n";
			os << "\t}\n";
		}
		os << "\tUINT8 byRet_ = 0;\n";
		os << "\tif(!bRet_)\n";
		os << "\t\tbyRet_ = 1;\n";
		PrintCallBackFunc(os, rFunc, "\t");
		os << ";\n\t" << GetSessionDataType(rFunc) << "\n";
		os << "\tstd::shared_ptr<TSessData> pSessData_;\n";
		os << "\tif(_pSessionMgr != NULL)\n";
		os << "\t\tpSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));\n";
		os << "\tif(pSessData_ == NULL)\n";
		os << "\t\treturn false;\n";
		os << "\tfnOnReturn_ = std::get<0>(*pSessData_);\n";
		if(rFunc.bMultiReturn)
		{
			os << "\tif(!bFinish_)\n";
			os << "\t{\n";
			os << "\t\tif(fnOnReturn_ != NULL)\n";
			os << "\t\t\tfnOnReturn_(byRet_";
			for(UINT32 k = 0; k < rFunc.dwSessDataCount; ++k)
				os << ", std::get<" << (k + 1) << ">(*pSessData_)";
			for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
			{
				SParam& rParam = rFunc.vecRetParam[k];
				if(rParam.bBase)
					os << ", " << rParam.strName << ".ptr";
				else
					os << ", " << rParam.strName;
			}
			os << ");\n";
			os << "\t}\n";
			os << "\telse\n";
			os << "\t{\n";
			os << "\t\tif(_pSessionMgr != NULL)\n";
			os << "\t\t\t_pSessionMgr->DelSession(dwSessionID_);\n";
			os << "\t}\n";
		}
		else
		{
			os << "\tif(fnOnReturn_ != NULL)\n";
			os << "\t\tfnOnReturn_(byRet_";
			for(UINT32 k = 0; k < rFunc.dwSessDataCount; ++k)
				os << ", std::get<" << (k + 1) << ">(*pSessData_)";
			for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
			{
				SParam& rParam = rFunc.vecRetParam[k];
				if(rParam.bBase)
					os << ", " << rParam.strName << ".ptr";
				else
					os << ", " << rParam.strName;
			}
			os << ");\n";
			os << "\tif(_pSessionMgr != NULL)\n";
			os << "\t\t_pSessionMgr->DelSession(dwSessionID_);\n";
		}
		os << "\treturn true;\n";
		os << "}\n\n";

		os << "void " << _strClassName << "::_OnTimeOut_" << rFunc.strName << "(UINT32 dwSessionID)\n";
		os << "{\n";
		for(SParam& rParam : rFunc.vecRetParam)
		{
			if(rParam.bBase)
			{
				os << "\t" << GetTypeName(rParam.strTypeName) << "_Wrapper " << rParam.strName;
			}
			else
			{
				os << "\t" << GetTypeName(rParam.strTypeName) << " " << rParam.strName;
				string strDefaultValue;
				if(GetDefaultValue(rParam, strDefaultValue))
					os << " = " << strDefaultValue;
			}
			os << ";\n";
		}
		PrintCallBackFunc(os, rFunc, "\t");
		os << ";\n\t" << GetSessionDataType(rFunc) << "\n";
		os << "\tstd::shared_ptr<TSessData> pSessData_;\n";
		os << "\tif(_pSessionMgr != NULL)\n";
		os << "\t\tpSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));\n";
		os << "\tif(pSessData_ == NULL)\n";
		os << "\t\treturn;\n";
		os << "\tfnOnReturn_ = std::get<0>(*pSessData_);\n";
		os << "\tif(fnOnReturn_ != NULL)\n";
		os << "\t\tfnOnReturn_(2";
		for(UINT32 k = 0; k < rFunc.dwSessDataCount; ++k)
			os << ", std::get<" << (k + 1) << ">(*pSessData_)";
		for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			if(rParam.bBase)
				os << ", " << rParam.strName << ".ptr";
			else
				os << ", " << rParam.strName;
		}
		os << ");\n";
		os << "}\n\n";
	}
	os << "} //namespace " << _strNameSpace << "\n";
	ofstream ofile(strPath.c_str());
	ofile << BOM;
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
}

static int GetProtID(const string& strLine)
{
	auto itBegin = find_if(strLine.begin(), strLine.end(), [](UINT8 c)->bool{ return isdigit(c) != 0; });
	auto itEnd = find_if(itBegin, strLine.end(), [](UINT8 c)->bool{ return !isdigit(c); });
	string strNum(itBegin, itEnd);
	if(strNum.empty())
		return 0;
	return atoi(strNum.c_str());
}

bool CDocument::PrintProxyCode(const string& strPath)
{
	if(_eProxyType == eProxyNone)
		return true;
	ifstream ifile(strPath.c_str());
	char szBuf[0x100];
	list<string> lstGame, lstCenter, lstDB;
	EProxyType eProxyType = eProxyNone;
	while(ifile.getline(szBuf, sizeof szBuf))
	{
		string strLine = szBuf;
		if(strLine.find("arProtGameServer") != string::npos)
		{
			eProxyType = eProxyGame;
		}
		else if(strLine.find("arProtCenterServer") != string::npos)
		{
			eProxyType = eProxyCenter;
		}
		else if(strLine.find("arProtDBServer") != string::npos)
		{
			eProxyType = eProxyDB;
		}
		else if(strLine.find("}") == string::npos && !boost::trim_copy(strLine).empty())
		{
			int iProtID = GetProtID(strLine);
			if(iProtID != 0 && iProtID != _ID)
			{
				switch(eProxyType)
				{
				case eProxyGame:
					lstGame.push_back(strLine);
					break;
				case eProxyCenter:
					lstCenter.push_back(strLine);
					break;
				case eProxyDB:
					lstDB.push_back(strLine);
					break;
				}
			}
		}
	}
	ifile.close();

	ostringstream os;
	list<string>* pLstProxy = NULL;
	switch(_eProxyType)
	{
	case eProxyGame:
		pLstProxy = &lstGame;
		break;
	case eProxyCenter:
		pLstProxy = &lstCenter;
		break;
	case eProxyDB:
		pLstProxy = &lstDB;
		break;
	default:
		return false;
	}
	string strLine = "\t" + NumberToString(_ID) + ", //" + _strName;
	pLstProxy->emplace_back(move(strLine));
	
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的协议转发类型代码文件\n"
		"//  File Name:    ProtocolProxy.h\n"
		"//  Purpose:      定义协议转发类型，网关服务器用\n"
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "#pragma once\n\n";
	auto func = [&os](list<string>& lstLine, const char* pszName, const char* pszComment, const char* pszTail) {
		lstLine.sort([](const string& left, const string& right)->bool{ return GetProtID(left) < GetProtID(right); });
		if(!lstLine.empty())
			os << "const UINT8 " << pszName << "[] = { //" << pszComment << "\n";
		for(auto& strLine : lstLine)
			os << strLine << "\n";
		if(!lstLine.empty())
			os << "};" << pszTail;
	};
	func(lstGame, "arProtGameServer", "转发到GameServer的协议", "\n\n");
	func(lstCenter, "arProtCenterServer", "转发到CenterServer的协议", "\n\n");
	func(lstDB, "arProtDBServer", "转发到DBServer的协议", "\n");

	ofstream ofile(strPath.c_str());
	if(!ofile)
	{
		cerr << "Open file fails! file name: " << strPath << endl;
		return false;
	}
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << BOM << strUtf;
	return true;
}
