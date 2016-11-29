/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	Convert.cpp
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

void CDocument::PrintStructArchive(ostringstream& os, SStruct& rStruct)
{
	os << "CInArchive& operator>>(CInArchive& src, " << rStruct.strName << "& s)\n";
	os << "{\n";
	if(rStruct.byDBLen > 0)
	{
		if(rStruct.byDBLen == 4)
			os << "\tUINT32 len = 0;\n";
		else
			os << "\tUINT16 len = 0;\n";
		os << "\tif(src.IsForDB())\n";
		os << "\t{\n";
		os << "\t\tCDBInArchive& iar = (CDBInArchive&)src;\n";
		os << "\t\tiar.PushEndPos(len);\n";
		os << "\t}\n";
	}
	if(!rStruct.strSuperName.empty())
		os << "\tsrc >> (" << rStruct.strSuperName << "&)s;\n";
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		SMember& rMember = rStruct.vecMember[i];
		if(rMember.bBase)
			os << "\t" << GetTypeName(rMember.strTypeName) << "_Wrapper " << rMember.strName << "_Wrapper;\n";
	}
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		SMember& rMember = rStruct.vecMember[i];
		if(rMember.bBase)
			os << "\tsrc >> " << rMember.strName << "_Wrapper;\n";
		else
			os << "\tsrc >> " << GetTypeConvert(rMember.byByte) << "s." << rMember.strName << ";\n";
	}
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		SMember& rMember = rStruct.vecMember[i];
		if(rMember.bBase)
			os << "\ts." << rMember.strName << " = " << rMember.strName << "_Wrapper.ptr;\n";
	}
	if(rStruct.byDBLen > 0)
	{
		os << "\tif(src.IsForDB())\n";
		os << "\t{\n";
		os << "\t\tCDBInArchive& iar = (CDBInArchive&)src;\n";
		os << "\t\tiar.PopEndPos();\n";
		os << "\t}\n";
	}
	os << "\treturn src;\n";
	os << "}\n\n";

	os << "COutArchive& operator<<(COutArchive& src, const " << rStruct.strName << "& s)\n";
	os << "{\n";
	if(rStruct.byDBLen > 0)
	{
		if(rStruct.byDBLen == 4)
			os << "\tUINT32 len = 0;\n";
		else
			os << "\tUINT16 len = 0;\n";
		os << "\tsize_t pos = 0, start = 0;\n";
		os << "\tif(src.IsForDB())\n";
		os << "\t{\n";
		os << "\t\tCDBOutArchive& oar = (CDBOutArchive&)src;\n";
		os << "\t\tpos = oar.PreWriteLength(len);\n";
		os << "\t\tstart = oar.GetLength();\n";
		os << "\t}\n";
	}
	if(!rStruct.strSuperName.empty())
		os << "\tsrc << (const " << rStruct.strSuperName << "&)s;\n";
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		SMember& rMember = rStruct.vecMember[i];
		if(rMember.bBase)
			os << "\t" << GetTypeName(rMember.strTypeName) << "_Wrapper " << rMember.strName << "_Wrapper(s." << rMember.strName << ");\n";
	}
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		SMember& rMember = rStruct.vecMember[i];
		if(rMember.bBase)
			os << "\tsrc << " << rMember.strName << "_Wrapper;\n";
		else
			os << "\tsrc << " << GetTypeConvert(rMember.byByte) << "s." << rMember.strName << ";\n";
	}
	if(rStruct.byDBLen > 0)
	{
		os << "\tif(src.IsForDB())\n";
		os << "\t{\n";
		os << "\t\tCDBOutArchive& oar = (CDBOutArchive&)src;\n";
		if(rStruct.byDBLen == 4)
			os << "\t\tlen = UINT32(oar.GetLength() - start);\n";
		else
			os << "\t\tlen = UINT16(oar.GetLength() - start);\n";
		os << "\t\toar.WriteLength(pos, len);\n";
		os << "\t}\n";
	}
	os << "\treturn src;\n";
	os << "}\n\n";

	if(rStruct.bHasSub)
	{
		string strBaseName = GetBaseClassName(rStruct.strName);
		os << "CInArchive& operator>>(CInArchive& src, " << rStruct.strName << "_Wrapper& rWrapper)\n";
		os << "{\n";
		os << "\tEType_" << strBaseName << " eType = eType_" << strBaseName << ";\n";
		os << "\tsrc >> (UINT8&)eType;\n";
		os << "\tswitch(eType)\n";
		os << "\t{\n";
		vector<string> vecAllName = rStruct.vecSubName;
		vecAllName.insert(vecAllName.begin(), rStruct.strName);
		for(size_t i = 0; i < vecAllName.size(); ++i)
		{
			string& strName = vecAllName[i];
			os << "\tcase eType_" << strName << ":\n";
			os << "\t\t{\n";
			os << "\t\t\trWrapper.ptr.reset(new " << strName << ");\n";
			os << "\t\t\tsrc >> (" << strName << "&)*rWrapper.ptr;\n";
			os << "\t\t}\n";
			os << "\t\tbreak;\n";
		}
		os << "\tdefault:\n";
		os << "\t\tthrow \"Unknown value for EType_" << strBaseName << "\";\n";
		os << "\t\tbreak;\n";
		os << "\t}\n";
		os << "\treturn src;\n";
		os << "}\n\n";

		os << "COutArchive& operator<<(COutArchive& src, const " << rStruct.strName << "_Wrapper& rWrapper)\n";
		os << "{\n";
		os << "\tif(rWrapper.ptr != NULL)\n";
		os << "\t{\n";
		os << "\t\tsrc << (UINT8)rWrapper.ptr->GetClassType();\n";
		os << "\t\tswitch(rWrapper.ptr->GetClassType())\n";
		os << "\t\t{\n";
		for(size_t i = 0; i < vecAllName.size(); ++i)
		{
			string& strName = vecAllName[i];
			os << "\t\tcase eType_" << strName << ":\n";
			os << "\t\t\tsrc << (" << strName << "&)*rWrapper.ptr;\n";
			os << "\t\t\tbreak;\n";
		}
		os << "\t\tdefault:\n";
		os << "\t\t\tthrow \"Unknown value for EType_" << strBaseName << "\";\n";
		os << "\t\t\tbreak;\n";
		os << "\t\t}\n";
		os << "\t}\n";
		os << "\treturn src;\n";
		os << "}\n\n";

		if(!rStruct.strVecName.empty())
		{
			os << "CInArchive& operator>>(CInArchive& src, " << rStruct.strVecName << "& vec)\n";
			os << "{\n";
			os << "\tUINT16 wSize = src.ReadContainerSize();\n";
			os << "\tvec.resize(wSize);\n";
			os << "\tfor(UINT16 i = 0; i < wSize; ++i)\n";
			os << "\t{\n";
			os << "\t\t" << rStruct.strName << "_Wrapper wrapper;\n";
			os << "\t\tsrc >> wrapper;\n";
			os << "\t\tvec[i] = wrapper.ptr;\n";
			os << "\t}\n";
			os << "\treturn src;\n";
			os << "}\n\n";

			os << "COutArchive& operator<<(COutArchive& src, const " << rStruct.strVecName << "& vec)\n";
			os << "{\n";
			os << "\tif(vec.size() > 0x7FFF)\n";
			os << "\t\tthrow \"Vector Size Too Large!\";\n";
			os << "\tUINT16 wSize = (UINT16)vec.size();\n";
			os << "\tsrc.WriteContainerSize(wSize);\n";
			os << "\tfor(UINT16 i = 0; i < wSize; ++i)\n";
			os << "\t{\n";
			os << "\t\t" << rStruct.strName << "_Wrapper wrapper;\n";
			os << "\t\twrapper.ptr = vec[i];\n";
			os << "\t\tsrc << wrapper;\n";
			os << "\t}\n";
			os << "\treturn src;\n";
			os << "}\n\n";
		}
	}
	else if((!rStruct.strSuperName.empty() || rStruct.bUsePtr) && !rStruct.strVecName.empty())
	{
		os << "CInArchive& operator>>(CInArchive& src, " << rStruct.strVecName << "& vec)\n";
		os << "{\n";
		os << "\tUINT16 wSize = src.ReadContainerSize();\n";
		os << "\tvec.resize(wSize);\n";
		os << "\tfor(UINT16 i = 0; i < wSize; ++i)\n";
		os << "\t{\n";
		os << "\t\t" << rStruct.strName << "Ptr p(new " << rStruct.strName << ");\n";
		os << "\t\tsrc >> *p;\n";
		os << "\t\tvec[i] = p;\n";
		os << "\t}\n";
		os << "\treturn src;\n";
		os << "}\n\n";

		os << "COutArchive& operator<<(COutArchive& src, const " << rStruct.strVecName << "& vec)\n";
		os << "{\n";
		os << "\tif(vec.size() > 0x7FFF)\n";
		os << "\t\tthrow \"Vector Size Too Large!\";\n";
		os << "\tUINT16 wSize = (UINT16)vec.size();\n";
		os << "\tsrc.WriteContainerSize(wSize);\n";
		os << "\tfor(UINT16 i = 0; i < wSize; ++i)\n";
		os << "\t\tsrc << *vec[i];\n";
		os << "\treturn src;\n";
		os << "}\n\n";
	}
}

void CDocument::PrintStructFromXML(ostringstream& os, SStruct& rStruct)
{
	os << "bool FromXML(TiXmlElement& rElement, " << rStruct.strName << "& s)\n";
	os << "{\n";
	os << "\tif(strcmp(rElement.Value(), \"" << rStruct.strName << "\") != 0)\n";
	os << "\t{\n";
	os << "\t\tLOG_CRI << \"rElement is not " << rStruct.strName << "!\";\n";
	os << "\t\treturn false;\n";
	os << "\t}\n";
	bool bFirstChild = true;
	if(!rStruct.strSuperName.empty())
	{
		const string& strSuperName = rStruct.strSuperName;
		if(bFirstChild)
		{
			os << "\tTiXmlElement* pElemChild = rElement.FirstChildElement();\n";
			bFirstChild = false;
		}
		else
		{
			os << "\tpElemChild = pElemChild->NextSiblingElement();\n";
		}
		os << "\tif(pElemChild == NULL)\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"pElemChild for " << strSuperName << " is empty!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		os << "\tif(!FromXML(*pElemChild, (" << strSuperName << "&)s))\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"FromXML for: " << strSuperName << " fails!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
	}
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		SMember& rMember = rStruct.vecMember[i];
		const string& strTypeName = rMember.strTypeName;
		const string& strName = rMember.strName;
		if(bFirstChild)
		{
			os << "\tTiXmlElement* pElemChild = rElement.FirstChildElement();\n";
			bFirstChild = false;
		}
		else
		{
			os << "\tpElemChild = pElemChild->NextSiblingElement();\n";
		}
		os << "\tif(pElemChild == NULL)\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"pElemChild for " << strName << " is empty!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		if(!rMember.bBase)
		{
			os << "\tif(strcmp(pElemChild->Value(), \"" << strTypeName << "\") != 0)\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"pElemChild is not " << strTypeName << "!\";\n";
			os << "\t\treturn false;\n";
			os << "\t}\n";
		}
		os << "\tif(strcmp(pElemChild->Attribute(\"name\"), \"" << strName << "\") != 0)\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"Attribute: name is not " << strName << "!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		bool bBuiltInType = false;
		bool bIsEnumType = false;
		bool bIsRefEnumType = false;
		bool bIsStringType = false;
		if(IsBuiltInType(rMember.strTypeName))
			bBuiltInType = true;
		else if(IsEnumType(rMember.strTypeName))
			bIsEnumType = true;
		else if(IsRefEnumType(rMember.strTypeName))
			bIsRefEnumType = true;
		else if(IsStringType(rMember.strTypeName))
			bIsStringType = true;
		if(bBuiltInType || bIsEnumType || bIsRefEnumType || bIsStringType)
		{
			os << "\tconst char* pszVal_" << rMember.strName << " = pElemChild->Attribute(\"value\");\n";
			os << "\tif(pszVal_" << rMember.strName << " == NULL)\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"Attribute: value doesn't exist!\";\n";
			os << "\t\treturn false;\n";
			os << "\t}\n";
			if(bBuiltInType)
			{
				os << "\tif(!String2Number(pszVal_" << rMember.strName << ", s." << rMember.strName << "))\n";
			}
			else if(bIsEnumType)
			{
				os << "\tif(!EnumStrToVal(pszVal_" << rMember.strName << ", s." << rMember.strName << "))\n";
			}
			else if(bIsRefEnumType)
			{
				SRefType* pRefType = GetRefEnumType(rMember.strTypeName);
				if(pRefType != NULL && pRefType->pDocument != NULL)
					os << "\tif(!" << pRefType->pDocument->_strNameSpace << "::EnumStrToVal(pszVal_" << rMember.strName << ", s." << rMember.strName << "))\n";
			}
			else if(bIsStringType)
			{
				os << "\ts." << rMember.strName << " = pszVal_" << rMember.strName << ";\n";
			}
			else
			{
				cerr << "Type " << rMember.strTypeName << " Error!" << endl;
			}
			if(bBuiltInType || bIsEnumType || bIsRefEnumType)
			{
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"Read attribute: value fails!\";\n";
				os << "\t\treturn false;\n";
				os << "\t}\n";
			}
		}
		else if(!IsVectorType(strTypeName))
		{
			if(rMember.bBase)
				os << "\tif(!SuperFromXML(*pElemChild, s." << strName << "))\n";
			else
				os << "\tif(!FromXML(*pElemChild, s." << strName << "))\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"FromXML for: " << strName << " fails!\";\n";
			os << "\t\treturn false;\n";
			os << "\t}\n";
		}
		else
		{
			auto it = _mapPrimVecType.find(strTypeName);
			if(it != _mapPrimVecType.end())
			{
				string strPrimTypeName = it->second;
				os << "\tconst char* pszText_" << strName << " = pElemChild->GetText();\n";
				os << "\tif(pszText_" << strName << " != NULL)\n";
				if(strTypeName == "TVecString")
					os << "\t\tSplitToText(pszText_" << strName << ", \",\", s." << strName << ");\n";
				else
					os << "\t\tSplitToNumber(pszText_" << strName << ", \",\", s." << strName << ");\n";
			}
			else
			{
				SRefType* pRefType = NULL;
				SStruct* pStruct = GetStruct(strTypeName, true);
				if(pStruct == NULL)
					pRefType = GetRefStruct(strTypeName, true, &pStruct);
				if(pStruct != NULL)
				{
					if(pRefType != NULL)
						os << "\tif(!" << pRefType->pDocument->_strNameSpace << "::VectorFromXML(*pElemChild, s." << strName << "))\n";
					else
						os << "\tif(!VectorFromXML(*pElemChild, s." << strName << "))\n";
					os << "\t{\n";
					os << "\t\tLOG_CRI << \"VectorFromXML for " << strName << " fails!\";\n";
					os << "\t\treturn false;\n";
					os << "\t}\n";
				}
				else
				{
					cerr << "Fail to parse XML for variable: " << strName << ", type: " << strTypeName << endl;
				}
			}
		}
	}
	os << "\treturn true;\n";
	os << "}\n\n";
}

void CDocument::PrintSuperFromXML(ostringstream& os, SStruct& rStruct)
{
	if(!rStruct.bHasSub)
		return;
	os << "bool SuperFromXML(TiXmlElement& rElement, " << rStruct.strName << "Ptr& p)\n";
	os << "{\n";
	os << "\tconst char* pszName = rElement.Value();\n";
	os << "\tif(pszName == NULL)\n";
	os << "\t{\n";
	os << "\t\tLOG_CRI << \"Element Name is empty!\";\n";
	os << "\t\treturn false;\n";
	os << "\t}\n";
	vector<string> vecAllName;
	vecAllName.push_back(rStruct.strName);
	vecAllName.insert(vecAllName.end(), rStruct.vecSubName.begin(), rStruct.vecSubName.end());
	for(size_t i = 0; i < vecAllName.size(); ++i)
	{
		string& strName = vecAllName[i];
		if(i == 0)
			os << "\tif(strcmp(pszName, \"" << strName << "\") == 0)\n";
		else
			os << "\telse if(strcmp(pszName, \"" << strName << "\") == 0)\n";
		os << "\t{\n";
		os << "\t\t" << strName << "Ptr pStruct(new " << strName << ");\n";
		os << "\t\tif(pStruct == NULL)\n";
		os << "\t\t{\n";
		os << "\t\t\tLOG_CRI << \"Can't allow memory for " << strName << "\";\n";
		os << "\t\t\treturn false;\n";
		os << "\t\t}\n";
		os << "\t\tif(!FromXML(rElement, *pStruct))\n";
		os << "\t\t{\n";
		os << "\t\t\tLOG_CRI << \"" << strName << " FromXML fails!\";\n";
		os << "\t\t\treturn false;\n";
		os << "\t\t}\n";
		os << "\t\tp = pStruct;\n";
		os << "\t}\n";
	}
	os << "\telse\n";
	os << "\t{\n";
	os << "\t\tLOG_CRI << \"Invalid name: \" << pszName << \"!\";\n";
	os << "\t\treturn false;\n";
	os << "\t}\n";
	os << "\treturn true;\n";
	os << "}\n\n";
}

void CDocument::PrintVectorFromXML(ostringstream& os, SStruct& rStruct)
{
	if(rStruct.strVecName.empty())
		return;
	os << "bool VectorFromXML(TiXmlElement& rElement, " << rStruct.strVecName << "& vec)\n";
	os << "{\n";
	os << "\tTiXmlElement* pElemMember = rElement.FirstChildElement();\n";
	os << "\twhile(pElemMember != NULL)\n";
	os << "\t{\n";
	if(rStruct.bHasSub)
	{
		os << "\t\t" << rStruct.strName << "Ptr p;\n";
		os << "\t\tif(!SuperFromXML(*pElemMember, p))\n";
		os << "\t\t{\n";
		os << "\t\t\tLOG_CRI << \"SuperFromXML fails!\";\n";
		os << "\t\t\treturn false;\n";
		os << "\t\t}\n";
		os << "\t\tvec.push_back(p);\n";
	}
	else if(!rStruct.strSuperName.empty() || rStruct.bUsePtr)
	{
		os << "\t\t" << rStruct.strName << "Ptr p(new " << rStruct.strName << ");\n";
		os << "\t\tif(!FromXML(*pElemMember, *p))\n";
		os << "\t\t{\n";
		os << "\t\t\tLOG_CRI << \"FromXML fails!\";\n";
		os << "\t\t\treturn false;\n";
		os << "\t\t}\n";
		os << "\t\tvec.push_back(p);\n";
	}
	else
	{
		os << "\t\t" << rStruct.strName << " s;\n";
		os << "\t\tif(!FromXML(*pElemMember, s))\n";
		os << "\t\t{\n";
		os << "\t\t\tLOG_CRI << \"FromXML fails!\";\n";
		os << "\t\t\treturn false;\n";
		os << "\t\t}\n";
		os << "\t\tvec.emplace_back(move(s));\n";
	}
	os << "\t\tpElemMember = pElemMember->NextSiblingElement();\n";
	os << "\t}\n";
	os << "\treturn true;\n";
	os << "}\n\n";
}

void CDocument::PrintStructToXML(ostringstream& os, SStruct& rStruct)
{
	os << "bool ToXML(const " << rStruct.strName << "& s, TiXmlElement& rElement)\n";
	os << "{\n";
	os << "\trElement.SetValue(\"" << rStruct.strName << "\");\n";
	os << "\trElement.SetAttribute(\"type\", ToUTF8Ptr(\"" << rStruct.strComment << "\"));\n";
	if(!rStruct.strSuperName.empty())
	{
		const string& strSuperName = rStruct.strSuperName;
		SStruct* pStruct = GetStruct(strSuperName);
		if(pStruct == NULL)
		{
			cerr << "Base Struct: " << strSuperName << "doesn't exist!" << endl;
			return;
		}
		os << "\tunique_ptr<TiXmlElement> pElem_" << strSuperName << "(new TiXmlElement(\"" << strSuperName << "\"));\n";
		os << "\tif(pElem_" << strSuperName << " == NULL)\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"Allocate memory fails!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		os << "\tif(!ToXML((const " << strSuperName << "&)s, *pElem_" << strSuperName << "))\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"" << strSuperName << " ToXML fails!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		os << "\tpElem_" << strSuperName << "->SetAttribute(\"type\", ToUTF8Ptr(\"" << pStruct->strComment << "\"));\n";
		os << "\tpElem_" << strSuperName << "->SetAttribute(\"comment\", ToUTF8Ptr(\"父类" << strSuperName << "部分\"));\n";
		os << "\tif(rElement.LinkEndChild(pElem_" << strSuperName << ".get()) != NULL)\n";
		os << "\t\tpElem_" << strSuperName << ".release();\n";
	}
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		SMember& rMember = rStruct.vecMember[i];
		const string& strName = rMember.strName;
		const string& strTypeName = rMember.strTypeName;
		const string& strComment = rMember.strComment;
		os << "\tunique_ptr<TiXmlElement> pElem_" << strName << "(new TiXmlElement(\"" << strTypeName << "\"));\n";
		os << "\tif(pElem_" << strName << " == NULL)\n";
		os << "\t{\n";
		os << "\t\tLOG_CRI << \"Allocate memory fails!\";\n";
		os << "\t\treturn false;\n";
		os << "\t}\n";
		os << "\tpElem_" << strName << "->SetAttribute(\"name\", \"" << strName << "\");\n";
		if(IsBuiltInType(rMember.strTypeName))
		{
			os << "\tpElem_" << strName << "->SetAttribute(\"value\", NumberToString(s." << rMember.strName << ").c_str());\n";
		}
		else if(IsEnumType(rMember.strTypeName))
		{
			os << "\tconst char* pszEnum_" << rMember.strName << " = EnumValToStr(s." << rMember.strName << ");\n";
			os << "\tif(pszEnum_" << rMember.strName << " == NULL)\n";
			os << "\t{\n";
			os << "\t\tLOG_CRI << \"EnumValToStr for " << rMember.strTypeName << " fails!\";\n";
			os << "\t\treturn false;\n";
			os << "\t}\n";
			os << "\tpElem_" << strName << "->SetAttribute(\"value\", pszEnum_" << rMember.strName << ");\n";
		}
		else if(IsRefEnumType(rMember.strTypeName))
		{
			SRefType* pRefType = GetRefEnumType(rMember.strTypeName);
			if(pRefType != NULL && pRefType->pDocument != NULL)
			{
				os << "\tconst char* pszEnum_" << rMember.strName << " = " << pRefType->pDocument->_strNameSpace << "::EnumValToStr(s." << rMember.strName << ");\n";
				os << "\tif(pszEnum_" << rMember.strName << " == NULL)\n";
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"EnumValToStr for " << rMember.strName << " fails!\";\n";
				os << "\t\treturn false;\n";
				os << "\t}\n";
				os << "\tpElem_" << strName << "->SetAttribute(\"value\", pszEnum_" << rMember.strName << ");\n";
			}
		}
		else if(IsStringType(rMember.strTypeName))
		{
			os << "\tpElem_" << strName << "->SetAttribute(\"value\", s." << rMember.strName << ".c_str());\n";
		}
		else if(!IsVectorType(strTypeName))
		{
			if(rMember.bBase)
			{
				os << "\tif(s." << strName << " == NULL)\n";
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"" << strName << " is NULL!\";\n";
				os << "\t\treturn false;\n";
				os << "\t}\n";
				os << "\tif(!SuperToXML(*s." << strName << ", *pElem_" << strName << "))\n";
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"" << strName << " SuperToXML fails!\";\n";
				os << "\t\treturn false;\n";
				os << "\t}\n";
			}
			else
			{
				os << "\tif(!ToXML(s." << strName << ", *pElem_" << strName << "))\n";
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"" << strName << " ToXML fails!\";\n";
				os << "\t\treturn false;\n";
				os << "\t}\n";
			}
		}
		else
		{
			auto it = _mapPrimVecType.find(strTypeName);
			if(it != _mapPrimVecType.end())
			{
				string strPrimTypeName = it->second;
				os << "\tstring strText_" << strName << ";\n";
				os << "\tfor(size_t i = 0; i < s." << strName << ".size(); ++i)\n";
				os << "\t{\n";
				os << "\t\tif(i > 0)\n";
				os << "\t\t\tstrText_" << strName << " += \", \";\n";
				if(strTypeName == "TVecString")
					os << "\t\tstrText_" << strName << " += s." << strName << "[i];\n";
				else
					os << "\t\tstrText_" << strName << " += NumberToString(s." << strName << "[i]);\n";
				os << "\t}\n";
				os << "\tunique_ptr<TiXmlText> pText_" << strName << "(new TiXmlText(strText_" << strName << ".c_str()));\n";
				os << "\tif(pText_" << strName << " == NULL)\n";
				os << "\t{\n";
				os << "\t\tLOG_CRI << \"Allocate memory fails!\";\n";
				os << "\t\treturn false;\n";
				os << "\t}\n";
				os << "\tif(pElem_" << strName << "->LinkEndChild(pText_" << strName << ".get()) != NULL)\n";
				os << "\t\tpText_" << strName << ".release();\n";
			}
			else
			{
				SRefType* pRefType = NULL;
				SStruct* pStruct = GetStruct(strTypeName, true);
				if(pStruct == NULL)
					pRefType = GetRefStruct(strTypeName, true, &pStruct);
				if(pStruct != NULL)
				{
					if(pRefType != NULL)
						os << "\tif(!" << pRefType->pDocument->_strNameSpace << "::VectorToXML(s." << strName << ", *pElem_" << strName << "))\n";
					else
						os << "\tif(!VectorToXML(s." << strName << ", *pElem_" << strName << "))\n";
					os << "\t{\n";
					os << "\t\tLOG_CRI << \"VectorToXML fails!\";\n";
					os << "\t\treturn false;\n";
					os << "\t}\n";
				}
				else
				{
					cerr << "Fail to print XML for variable: " << strName << ", type: " << strTypeName << endl;
				}
			}
		}
		os << "\tpElem_" << strName << "->SetAttribute(\"comment\", ToUTF8Ptr(\"" << strComment << "\"));\n";
		os << "\tif(rElement.LinkEndChild(pElem_" << strName << ".get()) != NULL)\n";
		os << "\t\tpElem_" << strName << ".release();\n";
	}
	os << "\treturn true;\n";
	os << "}\n\n";
}

void CDocument::PrintSuperToXML(ostringstream& os, SStruct& rStruct)
{
	if(!rStruct.bHasSub)
		return;
	os << "bool SuperToXML(const " << rStruct.strName << "& s, TiXmlElement& rElement)\n";
	os << "{\n";
	os << "\tswitch(s.GetClassType())\n";
	os << "\t{\n";
	vector<string> vecAllName;
	vecAllName.push_back(rStruct.strName);
	vecAllName.insert(vecAllName.end(), rStruct.vecSubName.begin(), rStruct.vecSubName.end());
	for(size_t i = 0; i < vecAllName.size(); ++i)
	{
		string& strName = vecAllName[i];
		os << "\tcase eType_" << strName << ":\n";
		os << "\t\treturn ToXML((" << strName << "&)s, rElement);\n";
	}
	os << "\tdefault:\n";
	os << "\t\tLOG_CRI << \"Invalid type: \" << s.GetClassType();\n";
	os << "\t\treturn false;\n";
	os << "\t}\n";
	os << "}\n\n";
}

void CDocument::PrintVectorToXML(ostringstream& os, SStruct& rStruct)
{
	if(rStruct.strVecName.empty())
		return;
	os << "bool VectorToXML(const " << rStruct.strVecName << "& vec, TiXmlElement& rElement)\n";
	os << "{\n";
	os << "\tfor(size_t i = 0; i < vec.size(); ++i)\n";
	os << "\t{\n";
	os << "\t\tunique_ptr<TiXmlElement> pElemMember(new TiXmlElement(\"" << rStruct.strName << "\"));\n";
	os << "\t\tif(pElemMember == NULL)\n";
	os << "\t\t{\n";
	os << "\t\t\tLOG_CRI << \"Allocate memory fails!\";\n";
	os << "\t\t\treturn false;\n";
	os << "\t\t}\n";
	if(rStruct.bHasSub)
		os << "\t\tif(!SuperToXML(*vec[i], *pElemMember))\n";
	else if(!rStruct.strSuperName.empty() || rStruct.bUsePtr)
		os << "\t\tif(!ToXML(*vec[i], *pElemMember))\n";
	else
		os << "\t\tif(!ToXML(vec[i], *pElemMember))\n";
	os << "\t\t{\n";
	os << "\t\t\tLOG_CRI << \"ToXML fails!\";\n";
	os << "\t\t\treturn false;\n";
	os << "\t\t}\n";
	os << "\t\tif(rElement.LinkEndChild(pElemMember.get()) != NULL)\n";
	os << "\t\t\tpElemMember.release();\n";
	os << "\t}\n";
	os << "\treturn true;\n";
	os << "}\n\n";
}
