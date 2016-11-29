/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	Document.cpp
//	Created:	2011/06/03	15:00
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

#ifndef INT32_MAX
#define INT8_MIN (-128)
#define INT16_MIN (-32767-1)
#define INT32_MIN (-2147483647-1)
#define INT64_MIN (-9223372036854775807LL-1)
#define INT8_MAX  __INT8_MAX__
#define INT16_MAX __INT16_MAX__
#define INT32_MAX __INT32_MAX__
#define INT64_MAX __INT64_MAX__
#define UINT8_MAX  __UINT8_MAX__
#define UINT16_MAX __UINT16_MAX__
#define UINT32_MAX __UINT32_MAX__
#define UINT64_MAX __UINT64_MAX__
#endif

#define ELEMENT_TYPEDEF		"TypeDef"
#define ELEMENT_REFER		"Refer"
#define ELEMENT_FUNCC2S		"FuncC2S"
#define ELEMENT_FUNCS2C		"FuncS2C"
#define ELEMENT_ENUM		"Enum"
#define ELEMENT_STRUCT		"Struct"
#define ELEMENT_SUBSTRUCT	"SubStruct"
#define ELEMENT_DECLSTRUCT	"DeclStruct"
#define ELEMENT_MEMBER		"Member"
#define ELEMENT_FUNC		"Func"
#define ELEMENT_PARAM		"Param"
#define ELEMENT_LOCPARAM	"LocParam"
#define ELEMENT_RETPARAM	"RetParam"
#define ELEMENT_PROTOCOL	"Protocol"

#define ATTRIBUTE_NAME		"name"
#define ATTRIBUTE_VALUE		"value"
#define ATTRIBUTE_VEC		"vec"
#define ATTRIBUTE_GLOBAL	"global"
#define ATTRIBUTE_TYPE		"type"
#define ATTRIBUTE_ID		"id"
#define ATTRIBUTE_CLIENT	"client"
#define ATTRIBUTE_BYTE		"byte"
#define ATTRIBUTE_SIGNED	"signed"
#define ATTRIBUTE_DBLEN		"dblen"
#define ATTRIBUTE_RPC		"rpc"
#define ATTRIBUTE_RET		"ret"
#define ATTRIBUTE_MULRET	"mulret"
#define ATTRIBUTE_KEEP		"keep"
#define ATTRIBUTE_OPERATOR	"operator"
#define ATTRIBUTE_TAIL		"tail"
#define ATTRIBUTE_PKG		"pkg"
#define ATTRIBUTE_DESC		"desc"
#define ATTRIBUTE_PTR		"ptr"
#define ATTRIBUTE_PROXY		"proxy"
#define ATTRIBUTE_COMMENT	"comment"
#define ATTRIBUTE_DEFAULT	"default"
#define ATTRIBUTE_ACKMSG    "ackmsg"

///////////////////////////////////////////////////////////////////////

string SElement::GetASComment(CDocument& rDocument) const
{
	return rDocument.GetASComment(strTypeName, strComment);
}

string SElement::GetPHPComment(CDocument& rDocument) const
{
	return rDocument.GetPHPComment(strTypeName, strComment);
}

string SElement::GetRubyComment(CDocument& rDocument) const
{
	return rDocument.GetRubyComment(strTypeName, strComment);
}

///////////////////////////////////////////////////////////////////////

const char* GetTypeConvert(INT8 byByte)
{
	switch(byByte)
	{
	case -1:
		return "(INT8&)";
	case -2:
		return "(INT16&)";
	case -4:
		return "(INT32&)";
	case 1:
		return "(UINT8&)";
	case 2:
		return "(UINT16&)";
	case 4:
		return "(UINT32&)";
	default:
		return "";
	}
}

bool CDocument::HasClientType(EClientType eClientType)
{
	return (_dwClientType & eClientType) != 0;
}

bool CDocument::HasOnlyClientType(EClientType eClientType)
{
	return _dwClientType == eClientType;
}

CDocument::CDocument() : _ID(0), _bHasC2SRetFunc(false), _bHasS2CRetFunc(false), _bClientRpc(false),
	_bUseVector(false),	_bUseINT64(false), _iNextRetID(-1), _eProxyType(eProxyNone), _dwClientType(0)
{
	_setPrimType.insert("INT8");
	_setPrimType.insert("INT16");
	_setPrimType.insert("INT32");
	_setPrimType.insert("INT64");
	_setPrimType.insert("UINT8");
	_setPrimType.insert("UINT16");
	_setPrimType.insert("UINT32");
	_setPrimType.insert("UINT64");
	_setPrimType.insert("float");
	_setPrimType.insert("double");
	_setPrimType.insert("bool");
	_setPrimType.insert("string");

	_mapPrimVecType.insert(make_pair("TVecINT8", "INT8"));
	_mapPrimVecType.insert(make_pair("TVecINT16", "INT16"));
	_mapPrimVecType.insert(make_pair("TVecINT32", "INT32"));
	_mapPrimVecType.insert(make_pair("TVecINT64", "INT64"));
	_mapPrimVecType.insert(make_pair("TVecUINT8", "UINT8"));
	_mapPrimVecType.insert(make_pair("TVecUINT16", "UINT16"));
	_mapPrimVecType.insert(make_pair("TVecUINT32", "UINT32"));
	_mapPrimVecType.insert(make_pair("TVecUINT64", "UINT64"));
	_mapPrimVecType.insert(make_pair("TVecFloat", "float"));
	_mapPrimVecType.insert(make_pair("TVecDouble", "double"));
	_mapPrimVecType.insert(make_pair("TVecBool", "bool"));
	_mapPrimVecType.insert(make_pair("TVecString", "string"));

	/*
	time_t tNow = time(NULL);
	tm tmTime;
	localtime_r(&tNow, &tmTime);
	char arBuf[100];
	sprintf_s(arBuf, "%u/%02u/%02u  %02u:%02u", tmTime.tm_year + 1900, tmTime.tm_mon + 1, tmTime.tm_mday, tmTime.tm_hour, tmTime.tm_min);
	_strGenTime = arBuf;
	*/
}

CDocument::~CDocument()
{
	for(auto it = _mapProt2Doc.begin(); it != _mapProt2Doc.end(); ++it)
		delete it->second;
	for(size_t i = 0; i < _vecStruct.size(); ++i)
		delete _vecStruct[i];
	for(size_t i = 0; i < _vecDeclStruct.size(); ++i)
		delete _vecDeclStruct[i];
}

string CDocument::GetStringValue(const char* pszValue)
{
#ifdef _WIN32
    wstring wstr = ToWString(pszValue, CP_UTF8);
    string str = ToString(wstr, CP_ACP);
    return str;
#else
#if 0
    size_t olen = wcslen((const wchar_t*)pszValue)+1;
    string str;
    str.resize(olen*2);
    size_t len = wcstombs(&str[0], (const wchar_t*)pszValue, str.size());
    return str;
#endif
    return string(pszValue);
#endif

}

bool CDocument::CheckType(SElement& rElement, bool bForDB /*= false*/)
{
	string& strType = rElement.strTypeName;
	if(strType == "string" || strType == "std::string")
	{
		strType = "string";
		return true;
	}

	if(HasClientType(eClientCppSvr) && rElement.IsParam())
	{
		SParam& rParam = (SParam&)rElement;
		if(rParam.bLocal && strType == "VoidPtr")
			return true;
	}

	if(strType == "ByteArray")
	{
		strType = "string";
		rElement.bByteArray = true;
		return true;
	}

	size_t pos = strType.find("::");
	if(pos != string::npos)
	{
		SRefType oRefType;
		oRefType.strPackage = strType.substr(0, pos);
		auto it = _mapProt2Doc.find(oRefType.strPackage);
		if(it == _mapProt2Doc.end())
		{
			cerr << "Unknown protocol: " << oRefType.strPackage << endl;
			return false;
		}
		oRefType.pDocument = it->second;
		oRefType.strPackage = HeadToLower(oRefType.strPackage);
		oRefType.strTypeName = strType.substr(pos + 2, strType.size() - pos - 2);
		_mapType2Ref.insert(make_pair(strType, oRefType));

		SEnum* pEnum = oRefType.pDocument->GetEnum(oRefType.strTypeName);
		if(pEnum != NULL)
			rElement.byByte = pEnum->byByte;
		if(bForDB)
		{
			SStruct* pStruct = oRefType.pDocument->GetStruct(oRefType.strTypeName);
			if(pStruct != NULL && pStruct->byDBLen == 0)
			{
				cerr << "Struct Member: " << pStruct->strName << " is not for DB!" << endl;
				return false;
			}
		}
		return true;
	}

	if(_setPrimType.find(strType) != _setPrimType.end())
	{
		if(strType.find("INT64") != string::npos)
			_bUseINT64 = true;
		return true;
	}

	if(_mapPrimVecType.find(strType) != _mapPrimVecType.end())
	{
		if(strType.find("INT64") != string::npos)
			_bUseINT64 = true;
		return true;
	}

	SEnum* pEnum = GetEnum(strType);
	if(pEnum != NULL)
	{
		rElement.byByte = pEnum->byByte;
		return true;
	}

	SStruct* pStruct = GetStruct(strType);
	if((pStruct = GetStruct(strType)) != NULL || (pStruct = GetStruct(strType, true)) != NULL
		|| (pStruct = GetDeclStruct(strType)) != NULL || (pStruct = GetDeclStruct(strType, true)) != NULL)
	{
		if(bForDB && pStruct->byDBLen == 0)
		{
			cerr << "Struct Member: " << pStruct->strName << " is not for DB!" << endl;
			return false;
		}
		return true;
	}

	return false;
}

string CDocument::GetTypeName(const string& strTypeName)
{
	if(strTypeName == "string")
		return "std::string";
	auto it = _mapType2Ref.find(strTypeName);
	if(it != _mapType2Ref.end())
		return "N" + strTypeName;
	return strTypeName;
}

static bool CheckChildElem(TiXmlElement* pElem, vector<string>& vecValidName)
{
	if(pElem == NULL)
		return true;
	TiXmlElement* pChildElem = pElem->FirstChildElement();
	bool bFind = false;
	while(pChildElem != NULL)
	{
		bFind = false;
		const char* pName = pChildElem->Value();
		for(size_t i = 0, size = vecValidName.size(); i < size; ++i)
		{
			if(vecValidName[i] == pName)
				bFind = true;
		}
		if(!bFind)
		{
			cerr << "Element \"" << pName << "\" under Element \"" << pElem->Value() << "\" is not valid!" << endl;
			return false;
		}
		pChildElem = pChildElem->NextSiblingElement();
	}
	return true;
}

static bool CheckChildElem(TiXmlElement* pElem, const char* pName1, const char* pName2 = NULL, const char* pName3 = NULL, const char* pName4 = NULL)
{
	vector<string> vecValidName;
	if(pName1 == NULL)
		return false;
	vecValidName.push_back(pName1);
	if(pName2 != NULL)
		vecValidName.push_back(pName2);
	if(pName3 != NULL)
		vecValidName.push_back(pName3);
	if(pName4 != NULL)
		vecValidName.push_back(pName4);
	if(!CheckChildElem(pElem, vecValidName))
		return false;
	return true;
}

SStruct* CDocument::GetStruct(const string& strName, bool bVec /*= false*/)
{
	for(size_t i = 0; i < _vecStruct.size(); ++i)
	{
		if(bVec && _vecStruct[i]->strVecName == strName || !bVec && _vecStruct[i]->strName == strName)
			return _vecStruct[i];
	}
	return NULL;
}

SRefType* CDocument::GetRefStruct(const string& strName, bool bVec, SStruct** ppStruct /*= NULL*/)
{
	auto itRef = _mapType2Ref.find(strName);
	if(itRef == _mapType2Ref.end())
		return NULL;
	SRefType& rRefType = itRef->second;
	if(rRefType.pDocument == NULL)
	{
		cerr << "Error package " << rRefType.strPackage << endl;
		return NULL;
	}
	SStruct* pStruct = rRefType.pDocument->GetStruct(rRefType.strTypeName, bVec);
	if(pStruct == NULL)
		return NULL;
	if(ppStruct != NULL)
		*ppStruct = pStruct;
	return &rRefType;
}

SStruct* CDocument::GetDeclStruct(const string& strName, bool bVec /*= false*/)
{
	for(size_t i = 0; i < _vecDeclStruct.size(); ++i)
	{
		if(bVec && _vecDeclStruct[i]->strVecName == strName || !bVec && _vecDeclStruct[i]->strName == strName)
			return _vecDeclStruct[i];
	}
	return NULL;
}

SEnum* CDocument::GetEnum(const string& strName)
{
	for(size_t i = 0; i < _vecEnum.size(); ++i)
	{
		if(_vecEnum[i].strName == strName)
			return &_vecEnum[i];
	}
	return NULL;
}

SMember* CDocument::GetEnumItem(const string& strName, SEnum** ppEnum /*= NULL*/)
{
	for(size_t i = 0; i < _vecEnum.size(); ++i)
	{
		SEnum& rEnum = _vecEnum[i];
		for(size_t k = 0; k < rEnum.vecMember.size(); ++k)
		{
			SMember& rMember = rEnum.vecMember[k];
			if(rMember.strName == strName)
			{
				if(ppEnum != NULL)
					*ppEnum = &rEnum;
				return &rMember;
			}
		}
	}
	return NULL;
}

SRefType* CDocument::GetRefEnumType(const string& strTypeName)
{
	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef == _mapType2Ref.end())
		return NULL;
	SRefType& rRefType = itRef->second;
	if(rRefType.pDocument == NULL)
	{
		cerr << "Error package " << rRefType.strPackage << endl;
		return NULL;
	}
	if(rRefType.pDocument->IsEnumType(rRefType.strTypeName))
		return &rRefType;
	return NULL;
}

bool CDocument::RecordRefEnumItem(const string& strName, SMember** ppMember /*= NULL*/)
{
	size_t pos = strName.find("::");
	if(pos == string::npos)
		return true;
	SRefType oRefType;
	oRefType.strPackage = strName.substr(0, pos);
	auto it = _mapProt2Doc.find(oRefType.strPackage);
	if(it == _mapProt2Doc.end())
	{
		cerr << "Unknown protocol: " << oRefType.strPackage << endl;
		return false;
	}
	oRefType.pDocument = it->second;
	oRefType.strPackage = HeadToLower(oRefType.strPackage);
	oRefType.strTypeName = strName.substr(pos + 2, strName.size() - pos - 2);
	SMember* pMember = oRefType.pDocument->GetEnumItem(oRefType.strTypeName);
	if(pMember != NULL)
		_mapType2Ref.insert(make_pair(strName, oRefType));
	if(ppMember != NULL)
		*ppMember = pMember;
	return true;
}

SRefType* CDocument::GetRefEnumItem(const string& strName, SEnum** ppEnum /*= NULL*/, SMember** ppMember /*= NULL*/)
{
	auto itRef = _mapType2Ref.find(strName);
	if(itRef == _mapType2Ref.end())
		return NULL;
	SRefType& rRefType = itRef->second;
	if(rRefType.pDocument == NULL)
	{
		cerr << "Error package " << rRefType.strPackage << endl;
		return NULL;
	}
	SMember* pMember = rRefType.pDocument->GetEnumItem(rRefType.strTypeName, ppEnum);
	if(ppMember != NULL)
		*ppMember = pMember;
	return &rRefType;
}

bool CDocument::FindElemType(const string& strVecType, string& strElemType)
{
	for(size_t i = 0; i < _vecStruct.size(); ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(rStruct.strVecName == strVecType)
		{
			strElemType = rStruct.strName;
			return true;
		}
	}
	return false;
}

bool CDocument::IsBuiltInType(const string& strTypeName)
{
	return _setPrimType.find(strTypeName) != _setPrimType.end() && !IsStringType(strTypeName);
}

bool CDocument::IsEnumType(const string& strTypeName)
{
	return GetEnum(strTypeName) != NULL;
}

bool CDocument::IsRefEnumType(const string& strTypeName)
{
	return GetRefEnumType(strTypeName) != NULL;
}

bool CDocument::IsStringType(const string& strTypeName)
{
	return strTypeName.find("string") != string::npos;
}

bool CDocument::IsPrimType(const string& strTypeName)
{
	return IsBuiltInType(strTypeName) || IsEnumType(strTypeName) || IsRefEnumType(strTypeName);
}

bool CDocument::IsVectorType(const string& strTypeName)
{
	if(_mapPrimVecType.find(strTypeName) != _mapPrimVecType.end())
		return true;
	for(size_t i = 0, size = _vecStruct.size(); i < size; ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(!rStruct.strVecName.empty() && strTypeName == rStruct.strVecName)
			return true;
	}
	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef != _mapType2Ref.end())
	{
		SRefType& rRefType = itRef->second;
		if(rRefType.strTypeName.find("TVec") == 0)
			return true;
	}
	return false;
}

bool CDocument::GetStructNameByVec(const string& strVecName, string& strName)
{
	for(size_t i = 0, size = _vecStruct.size(); i < size; ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(!rStruct.strVecName.empty() && strVecName == rStruct.strVecName)
		{
			strName = rStruct.strName;
			return true;
		}
	}
	return false;
}

string CDocument::GetBaseClassName(const string& strName)
{
	SStruct* pStruct = GetStruct(strName);
	while(pStruct != NULL)
	{
		if(pStruct->strSuperName.empty())
			return pStruct->strName;
		pStruct = GetStruct(pStruct->strSuperName);
	}
	return strName;
}

bool CDocument::ParseElemParam(TiXmlElement* pElemParam, SFunc& f, SParam& p)
{
	const char *pName = NULL, *pKeep = NULL, *pComment = NULL;
	pName = pElemParam->Attribute(ATTRIBUTE_NAME);
	if(pName == NULL)
	{
		cerr << ATTRIBUTE_NAME << " not found!" << endl;
		return false;
	}
	p.strName = pName;
	boost::trim(p.strName);
	if(p.strName.empty())
	{
		cerr << "Parameter name is empty!" << endl;
		return false;
	}
	pName = pElemParam->Attribute(ATTRIBUTE_TYPE);
	if(pName == NULL)
	{
		cerr << ATTRIBUTE_TYPE << " not found!" << endl;
		return false;
	}
	p.strTypeName = pName;
	boost::trim(p.strTypeName);
	if(p.strTypeName.empty())
	{
		cerr << "Parameter type is empty!" << endl;
		return false;
	}
	if(!CheckType(p))
	{
		cerr << "Type: " << pName << " is not valid!" << endl;
		return false;
	}
	if(IsPrimType(p.strTypeName))
	{
		p.bByRef = false;
	}
	else
	{
		p.bByRef = true;
		SStruct* pStruct = GetStruct(pName);
		if(pStruct == NULL)
			GetRefStruct(pName, false, &pStruct);
		if(pStruct != NULL)
		{
			if(pStruct->bHasSub)
			{
				p.bBase = true;
				p.bByRef = false;
			}
			p.bHasBase = pStruct->bHasBase;
		}
		pStruct = GetStruct(pName, true);
		if(pStruct == NULL)
			GetRefStruct(pName, true, &pStruct);
		if(pStruct != NULL)
		{
			if(pStruct->bHasSub)
				p.bBaseVec = true;
			p.bHasBaseVec = pStruct->bHasBase;
		}
	}
	pKeep = pElemParam->Attribute(ATTRIBUTE_KEEP);
	if(pKeep != NULL && strcasecmp(pKeep, "true") == 0)
	{
		if(!f.bReturn)
		{
			cerr << "Keeping parameter is not allowed in non-return PRC!" << endl;
			return false;
		}
		p.bKeep = true;
		f.bKeepParam = true;
	}
	pComment = pElemParam->Attribute(ATTRIBUTE_COMMENT);
	if(pComment != NULL)
	{
		p.strComment = GetStringValue(pComment);
		boost::trim(p.strComment);
	}
	return true;
}

bool CDocument::ParseElemFunc(TiXmlElement* pElemFunc, SFunc& f, bool bC2S)
{
	const char* pName = pElemFunc->Attribute(ATTRIBUTE_NAME);
	if(pName == NULL)
	{
		cerr << ATTRIBUTE_NAME << " not found!" << endl;
		return false;
	}
	f.strName = pName;
	boost::trim(f.strName);
	if(f.strName.empty())
	{
		cerr << "Function name is empty!" << endl;
		return false;
	}
	const char* pRet = pElemFunc->Attribute(ATTRIBUTE_RET);
	if(pRet != NULL && strcasecmp(pRet, "true") == 0)
	{
		if(!HasClientType(eClientCppSvr) && !bC2S)
		{
			cerr << "RPC from server to client is not allowed! Function: " << pName << endl;
			return false;
		}
		f.bReturn = true;
		if(bC2S)
			_bHasC2SRetFunc = true;
		else
			_bHasS2CRetFunc = true;
		f.iRetID = _iNextRetID--;
	}
    const char* pAckMsg = pElemFunc->Attribute(ATTRIBUTE_ACKMSG);
    if(pAckMsg != NULL && strcasecmp(pAckMsg, "") != 0)
    {
        if((HasClientType(eClientAs) && !bC2S))
        {
            f.strAckMsg.assign(pAckMsg);           
        }      
    }

	const char* pMulRet = pElemFunc->Attribute(ATTRIBUTE_MULRET);
	if(pMulRet != NULL && strcasecmp(pMulRet, "true") == 0)
	{
		if(!HasClientType(eClientCppSvr) && !bC2S)
		{
			cerr << "RPC from server to client is not allowed! Function: " << pName << endl;
			return false;
		}
		f.bReturn = true;
		f.bMultiReturn = true;
		if(bC2S)
			_bHasC2SRetFunc = true;
		else
			_bHasS2CRetFunc = true;
		f.iRetID = _iNextRetID--;
	}
	const char* pPkg = pElemFunc->Attribute(ATTRIBUTE_PKG);
	if(pPkg != NULL && strcasecmp(pPkg, "true") == 0)
	{
		if(!HasClientType(eClientCppSvr) && bC2S)
		{
			cerr << "Build Param Package on client is not allowed! Function: " << pName << endl;
			return false;
		}
		f.bPkg = true;
	}
	const char* pComment = pElemFunc->Attribute(ATTRIBUTE_COMMENT);
	if(pComment != NULL)
	{
		f.strComment = GetStringValue(pComment);
		boost::trim(f.strComment);
	}
	TiXmlElement* pElemParam = pElemFunc->FirstChildElement(ELEMENT_PARAM);
	while(pElemParam != NULL)
	{
		SParam p;
		if(!ParseElemParam(pElemParam, f, p))
		{
			cerr << "Parse parameter for function " << f.strName << " fails!" << endl;
			return false;
		}
		if(p.bKeep)
		{
			++f.dwSessDataCount;
			++f.dwCbkParamCount;
		}
		f.vecParam.push_back(p);
		pElemParam = pElemParam->NextSiblingElement(ELEMENT_PARAM);
	}
	pElemParam = pElemFunc->FirstChildElement(ELEMENT_LOCPARAM);
	while(pElemParam != NULL)
	{
		if(!f.bReturn)
		{
			cerr << "Local parameter is not allowed in non-return PRC!" << endl;
			return false;
		}
		SParam p;
		p.bLocal = true;
		if(!ParseElemParam(pElemParam, f, p))
		{
			cerr << "Parse local parameter for function " << f.strName << " fails!" << endl;
			return false;
		}
		++f.dwSessDataCount;
		++f.dwCbkParamCount;
		p.bKeep = true;
		f.bKeepParam = true;
		f.vecLocParam.push_back(p);
		pElemParam = pElemParam->NextSiblingElement(ELEMENT_LOCPARAM);
	}
	pElemParam = pElemFunc->FirstChildElement(ELEMENT_RETPARAM);
	while(pElemParam != NULL)
	{
		if(!f.bReturn)
		{
			cerr << "Returning parameter is not allowed in non-return PRC!" << endl;
			return false;
		}
		SParam p;
		if(!ParseElemParam(pElemParam, f, p))
		{
			cerr << "Parse return parameter for function " << f.strName << " fails!" << endl;
			return false;
		}
		++f.dwCbkParamCount;
		f.vecRetParam.push_back(p);
		pElemParam = pElemParam->NextSiblingElement(ELEMENT_RETPARAM);
	}
	return true;
}

bool CDocument::ParseElemStruct(TiXmlElement* pElemStruct, SStruct& s)
{
	const char* pName = pElemStruct->Attribute(ATTRIBUTE_NAME);
	if(pName == NULL)
	{
		cerr << ATTRIBUTE_NAME << " not found!" << endl;
		return false;
	}
	s.strName = pName;
	boost::trim(s.strName);
	if(s.strName.empty())
	{
		cerr << "Struct name is empty!" << endl;
		return false;
	}
	const char* pDBLen = pElemStruct->Attribute(ATTRIBUTE_DBLEN);
	if(pDBLen != NULL)
	{
		s.byDBLen = (UINT8)atoi(pDBLen);
		if(s.byDBLen != 2 && s.byDBLen != 4)
		{
			cerr << "DBLen should only be 2 or 4! Struct: " << s.strName << endl;
			return false;
		}
	}
	pName = pElemStruct->Attribute(ATTRIBUTE_VEC);
	if(pName != NULL)
	{
		s.strVecName = pName;
		boost::trim(s.strVecName);
		if(s.strVecName.find("TVec") != 0)
		{
			cerr << "Vector type name: " << s.strVecName << " should start with \"TVec\"" << endl;
			return false;
		}
		_bUseVector = true;
	}
	const char* pGlobal = pElemStruct->Attribute(ATTRIBUTE_GLOBAL);
	if(pGlobal != NULL)
	{
		if(strcasecmp(pGlobal, "client") == 0)
			s.eGlobalType = eGlobalClient;
		else if(strcasecmp(pGlobal, "server") == 0)
			s.eGlobalType = eGlobalServer;
		else if(strcasecmp(pGlobal, "both") == 0)
			s.eGlobalType = eGlobalBoth;
	}
	const char* pComment = pElemStruct->Attribute(ATTRIBUTE_COMMENT);
	if(pComment != NULL)
	{
		s.strComment = GetStringValue(pComment);
		boost::trim(s.strComment);
	}
	const char* pPtr = pElemStruct->Attribute(ATTRIBUTE_PTR);
	if(pPtr != NULL && strcasecmp(pPtr, "true") == 0)
		s.bUsePtr = true;
	TiXmlElement* pElemMember = pElemStruct->FirstChildElement(ELEMENT_MEMBER);
	while(pElemMember != NULL)
	{
		SMember m;
		pName = pElemMember->Attribute(ATTRIBUTE_NAME);
		if(pName == NULL)
		{
			cerr << ATTRIBUTE_NAME << " not found!" << endl;
			return false;
		}
		m.strName = pName;
		boost::trim(m.strName);
		if(m.strName.empty())
		{
			cerr << "Enum member name is empty!" << endl;
			return false;
		}
		const char* pType = pElemMember->Attribute(ATTRIBUTE_TYPE);
		if(pType == NULL)
		{
			cerr << ATTRIBUTE_TYPE << " not found!" << endl;
			return false;
		}
		m.strTypeName = pType;
		boost::trim(m.strTypeName);
		if(!CheckType(m, s.byDBLen > 0))
		{
			cerr << "Type: " << m.strTypeName << " is not valid!" << endl;
			return false;
		}
		if(m.strTypeName == "string")
			s.bMoveCtor = m.bMoveCtor = true;
		SStruct* pStruct = GetStruct(m.strTypeName);
		if(pStruct != NULL)
		{
			s.bMoveCtor = m.bMoveCtor = pStruct->bMoveCtor;
			m.bHasBase = pStruct->bHasBase;
			if(pStruct->bHasSub)
			{
				m.bBase = true;
				s.bHasBase = true;
			}
			goto FOUND;
		}
		pStruct = GetStruct(m.strTypeName, true);
		if(pStruct != NULL)
		{
			s.bMoveCtor = m.bMoveCtor = true;
			m.bHasBaseVec = pStruct->bHasBase;
			if(pStruct->bHasSub)
			{
				m.bBaseVec = true;
				s.bHasBase = true;
			}
			goto FOUND;
		}
		pStruct = GetDeclStruct(m.strTypeName);
		if(pStruct != NULL)
		{
			s.bMoveCtor = m.bMoveCtor = pStruct->bMoveCtor;
			if(pStruct->bHasSub)
			{
				m.bBase = true;
				s.bHasBase = true;
			}
			goto FOUND;
		}
		pStruct = GetDeclStruct(m.strTypeName, true);
		if(pStruct != NULL)
		{
			s.bMoveCtor = m.bMoveCtor = true;
			if(pStruct->bHasSub)
			{
				m.bBaseVec = true;
				s.bHasBase = true;
			}
			goto FOUND;
		}
		GetRefStruct(m.strTypeName, false, &pStruct);
		if(pStruct != NULL)
		{
			s.bMoveCtor = m.bMoveCtor = pStruct->bMoveCtor;
			m.bHasBase = pStruct->bHasBase;
			if(pStruct->bHasSub)
			{
				m.bBase = true;
				s.bHasBase = true;
			}
			goto FOUND;
		}
		GetRefStruct(m.strTypeName, true, &pStruct);
		if(pStruct != NULL)
		{
			s.bMoveCtor = m.bMoveCtor = true;
			m.bHasBaseVec = pStruct->bHasBase;
			if(pStruct->bHasSub)
			{
				m.bBaseVec = true;
				s.bHasBase = true;
			}
		}
FOUND:
		if(m.strTypeName.find("INT64") != string::npos)
			s.bUseINT64 = true;
		const char* pOperator = pElemMember->Attribute(ATTRIBUTE_OPERATOR);
		if(pOperator != NULL && strcasecmp(pOperator, "true") == 0)
			m.bOperator = true;
		const char* pDefault = pElemMember->Attribute(ATTRIBUTE_DEFAULT);
		if(pDefault != NULL)
		{
			if(!IsPrimType(m.strTypeName))
			{
				cerr << "Default value for non-primitive type:" << m.strTypeName << " is invalid!" << endl;
				return false;
			}
			if(m.strTypeName == "bool" && strcmp(pDefault, "true") != 0 && strcmp(pDefault, "false") != 0)
			{
				cerr << "Default value: " << pDefault << " for bool type is invalid! ";
				return false;
			}
			m.strDefaultValue = GetStringValue(pDefault);
			boost::trim(m.strDefaultValue);
			if(!RecordRefEnumItem(m.strDefaultValue))
				return false;
		}
		pComment = pElemMember->Attribute(ATTRIBUTE_COMMENT);
		if(pComment != NULL)
		{
			m.strComment = GetStringValue(pComment);
			boost::trim(m.strComment);
		}
		pElemMember = pElemMember->NextSiblingElement(ELEMENT_MEMBER);
		s.vecMember.push_back(m);
	}
	return true;
}

bool CDocument::ParseElemSubStruct(TiXmlElement* pElemStruct, SStruct& s, vector<SStruct*>& rVecSubStruct)
{
	//SubStruct
	vector<SStruct*> vecDesStruct;
	TiXmlElement* pElemSubStruct = pElemStruct->FirstChildElement(ELEMENT_SUBSTRUCT);
	while(pElemSubStruct != NULL)
	{
		if(!CheckChildElem(pElemSubStruct, ELEMENT_MEMBER, ELEMENT_SUBSTRUCT))
			return false;

		s.bHasSub = true;
		SStruct* pStruct = new SStruct;
		if(pStruct == NULL)
		{
			cerr << "No memory available!" << endl;
			return false;
		}
		if(!ParseElemStruct(pElemSubStruct, *pStruct))
			return false;

		_vecStruct.push_back(pStruct);
		pStruct->bSuperHasBase = s.bHasBase;
		s.vecSubName.push_back(pStruct->strName);
		pStruct->strSuperName = s.strName;
		rVecSubStruct.push_back(pStruct);

		if(!ParseElemSubStruct(pElemSubStruct, *pStruct, vecDesStruct))
			return false;

		pElemSubStruct = pElemSubStruct->NextSiblingElement(ELEMENT_SUBSTRUCT);
	}
	for(size_t i = 0; i < vecDesStruct.size(); ++i)
		s.vecSubName.push_back(vecDesStruct[i]->strName);
	rVecSubStruct.insert(rVecSubStruct.end(), vecDesStruct.begin(), vecDesStruct.end());
	return true;
}

void CDocument::GetFileTime(const char* szFileName)
{
#ifdef _WIN32
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return;
	FILETIME oLastWriteTime;
	if(!::GetFileTime(hFile, NULL, NULL, &oLastWriteTime))
		return;
	CloseHandle(hFile);
	SYSTEMTIME oSystemTime, oLocalTime;
	if(!FileTimeToSystemTime(&oLastWriteTime, &oSystemTime))
		return;
	if(!SystemTimeToTzSpecificLocalTime(NULL, &oSystemTime, &oLocalTime))
		return;
	char arBuf[100];
	sprintf_s(arBuf, "%u/%02u/%02u  %02u:%02u", oLocalTime.wYear, oLocalTime.wMonth, oLocalTime.wDay, oLocalTime.wHour, oLocalTime.wMinute);
	_strGenTime = arBuf;
#else
	struct stat oStat;
	stat(szFileName, &oStat);
	tm oTime;
	localtime_r(&oStat.st_mtime, &oTime);
	char arBuf[100];
	sprintf(arBuf, "%u/%02u/%02u  %02u:%02u", oTime.tm_year + 1900, oTime.tm_mon + 1, oTime.tm_mday, oTime.tm_hour, oTime.tm_min);
	_strGenTime = arBuf;
#endif
}

bool CDocument::ParseXML(const char* szFileName)
{
	if(szFileName == NULL)
		return false;
#ifdef GEN_FILE_TIME
	GetFileTime(szFileName);
#endif
	TiXmlDocument doc(szFileName);
	if(!doc.LoadFile(TIXML_ENCODING_UTF8))
	{
		cerr << "Load " << szFileName << " fails!" << endl;
		return false;
	}

	_strFileName = szFileName;
	string::size_type pos = _strFileName.find_last_of("\\/");
	if(pos != string::npos)
		_strFileName = _strFileName.substr(pos + 1);
	pos = _strFileName.find_last_of(".");
	if(pos != string::npos)
		_strFileName = _strFileName.substr(0, pos);

	TiXmlElement* pElemRoot = doc.RootElement();
	if(pElemRoot == NULL)
	{
		cerr << "Load Root Element Error!" << endl;
		return false;
	}

	if(!CheckChildElem(pElemRoot, ELEMENT_REFER, ELEMENT_TYPEDEF, ELEMENT_FUNCC2S, ELEMENT_FUNCS2C))
		return false;

	const char* pName = pElemRoot->Attribute(ATTRIBUTE_NAME);
	if(pName == NULL)
	{
		cerr << ATTRIBUTE_NAME << " not found!" << endl;
		return false;
	}
	_strName = pName;
	boost::trim(_strName);
	if(_strName.empty())
	{
		cerr << "Protocol name is empty!" << endl;
		return false;
	}
	_strClassName = "C" + _strName;
	_strNameSpace = "N" + _strName;

	const char* pID = pElemRoot->Attribute(ATTRIBUTE_ID);
	if(pID == NULL)
	{
		cerr << ATTRIBUTE_NAME << " not found!" << endl;
		return false;
	}
	_ID = atoi(pID);
	if(_ID == 0)
	{
		cerr << "Protocol ID is zero!" << endl;
		return false;
	}

	const char* pProxy = pElemRoot->Attribute(ATTRIBUTE_PROXY);
	if(pProxy != NULL)
	{
		if(strcasecmp(pProxy, "GameServer") == 0)
			_eProxyType = eProxyGame;
		else if(strcasecmp(pProxy, "CenterServer") == 0)
			_eProxyType = eProxyCenter;
		else if(strcasecmp(pProxy, "DBServer") == 0)
			_eProxyType = eProxyDB;
	}

	const char* pComment = pElemRoot->Attribute(ATTRIBUTE_COMMENT);
	if(pComment != NULL)
	{
		_strComment = GetStringValue(pComment);
		boost::trim(_strComment);
	}

	TiXmlElement* pElemRefer = pElemRoot->FirstChildElement(ELEMENT_REFER);
	if(pElemRefer != NULL)
	{
		if(!CheckChildElem(pElemRefer, ELEMENT_PROTOCOL))
			return false;

		//protocol
		TiXmlElement* pElemProt = pElemRefer->FirstChildElement(ELEMENT_PROTOCOL);
		while(pElemProt != NULL)
		{
			pName = pElemProt->Attribute(ATTRIBUTE_NAME);
			if(pName == NULL)
			{
				cerr << ATTRIBUTE_NAME << " not found!" << endl;
				return false;
			}
			string strName = pName;
			boost::trim(strName);
			string strPath = _strDir + strName + ".xml";
			CDocument* pDoc = new CDocument;
			if(pDoc == NULL)
			{
				cerr << "No memory available!" << endl;
				return false;
			}
			pDoc->SetDir(_strDir);
			if(!pDoc->ParseXML(strPath.c_str()))
			{
				cerr << "Parse refered XML: " << strPath << " fails!" << endl;
				return false;
			}
			_mapProt2Doc.insert(make_pair(strName, pDoc));
			pElemProt = pElemProt->NextSiblingElement(ELEMENT_PROTOCOL);
		}
	}

	TiXmlElement* pElemTypeDef = pElemRoot->FirstChildElement(ELEMENT_TYPEDEF);
	if(pElemTypeDef != NULL)
	{
		if(!CheckChildElem(pElemTypeDef, ELEMENT_ENUM, ELEMENT_STRUCT, ELEMENT_DECLSTRUCT))
			return false;

		//enum
		TiXmlElement* pElemEnum = pElemTypeDef->FirstChildElement(ELEMENT_ENUM);
		while(pElemEnum != NULL)
		{
			if(!CheckChildElem(pElemEnum, ELEMENT_MEMBER))
				return false;

			SEnum e;
			pName = pElemEnum->Attribute(ATTRIBUTE_NAME);
			if(pName == NULL)
			{
				cerr << ATTRIBUTE_NAME << " not found!" << endl;
				return false;
			}
			e.strName = pName;
			boost::trim(e.strName);
			if(e.strName.empty())
			{
				cerr << "Enum name is empty!" << endl;
				return false;
			}
			bool bSigned = false;
			const char* pSigned = pElemEnum->Attribute(ATTRIBUTE_SIGNED);
			if(pSigned != NULL && strcasecmp(pSigned, "true") == 0)
				bSigned = true;
			const char* pByte = pElemEnum->Attribute(ATTRIBUTE_BYTE);
			if(pByte != NULL)
			{
				e.byByte = (UINT8)atoi(pByte);
				if(e.byByte != 1 && e.byByte != 2 && e.byByte != 4)
				{
					cerr << "Enum bytes could only be 1 or 2 or 4!" << endl;
					return false;
				}
				if(pSigned)
					e.byByte = -e.byByte;
			}
			else if(bSigned)
			{
				e.byByte = -1;
			}
			else
			{
				e.byByte = 1;
			}
			const char* pGlobal = pElemEnum->Attribute(ATTRIBUTE_GLOBAL);
			if(pGlobal != NULL)
			{
				if(strcasecmp(pGlobal, "client") == 0)
					e.eGlobalType = eGlobalClient;
				else if(strcasecmp(pGlobal, "server") == 0)
					e.eGlobalType = eGlobalServer;
				else if(strcasecmp(pGlobal, "both") == 0)
					e.eGlobalType = eGlobalBoth;
			}
			const char* pDesc = pElemEnum->Attribute(ATTRIBUTE_DESC);
			if(pDesc != NULL)
			{
				if(strcasecmp(pDesc, "true") == 0)
					e.bDesc = true;
			}
			pComment = pElemEnum->Attribute(ATTRIBUTE_COMMENT);
			if(pComment != NULL)
			{
				e.strComment = GetStringValue(pComment);
				boost::trim(e.strComment);
			}
			INT64 qwMaxValue = INT32_MIN;
			INT64 qwValue = -1;
			TiXmlElement* pElemMember = pElemEnum->FirstChildElement(ELEMENT_MEMBER);
			while(pElemMember != NULL)
			{
				SMember m;
				pName = pElemMember->Attribute(ATTRIBUTE_NAME);
				if(pName == NULL)
				{
					cerr << ATTRIBUTE_NAME << " not found!" << endl;
					return false;
				}
				m.strName = pName;
				boost::trim(m.strName);
				if(m.strName.empty())
				{
					cerr << "Enum member name is empty!" << endl;
					return false;
				}
				pName = pElemMember->Attribute(ATTRIBUTE_VALUE);
				if(pName != NULL)
					m.strTypeName = pName;
				boost::trim(m.strTypeName);
				if(m.strTypeName.empty())
				{
					++qwValue;
				}
				else
				{
					int iRadix = 10;
					if(m.strTypeName.find("0x") == 0 || m.strTypeName.find("0X") == 0)
						iRadix = 16;
					char* pEndPtr = NULL;
					qwValue = StrToINT64(m.strTypeName.c_str(), &pEndPtr, iRadix);
					if(pEndPtr != NULL && pEndPtr <= &m.strTypeName.back())
					{
						SMember* pMember = GetEnumItem(m.strTypeName);
						if(pMember == NULL)
						{
							for(size_t i = 0; i < e.vecMember.size(); ++i)
							{
								SMember& rMember = e.vecMember[i];
								if(rMember.strName == m.strTypeName)
									pMember = &rMember;
							}
						}
						if(pMember == NULL)
						{
							if(!RecordRefEnumItem(m.strTypeName, &pMember))
								return false;
						}
						if(pMember == NULL)
						{
							cerr << "Unknown value: " << m.strTypeName << " for Enum Member: " << m.strName << endl;
							return false;
						}
						qwValue = pMember->qwValue;
					}
				}
				bool bValid = true;
				switch(e.byByte)
				{
				case -1:
					if(qwValue < INT8_MIN || qwValue > INT8_MAX)
						bValid = false;
					break;
				case -2:
					if(qwValue < INT16_MIN || qwValue > INT16_MAX)
						bValid = false;
					break;
				case -4:
					if(qwValue < INT32_MIN || qwValue > INT32_MAX)
						bValid = false;
					break;
				case 1:
					if(qwValue < 0 || qwValue > UINT8_MAX)
						bValid = false;
					break;
				case 2:
					if(qwValue < 0 || qwValue > UINT16_MAX)
						bValid = false;
					break;
				case 4:
					if(qwValue < 0 || qwValue > UINT32_MAX)
						bValid = false;
					break;
				}
				if(!bValid)
				{
					cerr << "enum value: " << qwValue << " for " << m.strName << " is invalid!" << endl;
					return false;
				}
				m.qwValue = qwValue;
				if(qwMaxValue < qwValue)
				{
					qwMaxValue = qwValue;
					e.wMaxValIndex = (INT16)e.vecMember.size();
				}
				pComment = pElemMember->Attribute(ATTRIBUTE_COMMENT);
				if(pComment != NULL)
				{
					m.strComment = GetStringValue(pComment);
					boost::trim(m.strComment);
				}
				pElemMember = pElemMember->NextSiblingElement(ELEMENT_MEMBER);
				e.vecMember.push_back(m);
			}
			pElemEnum = pElemEnum->NextSiblingElement(ELEMENT_ENUM);
			_vecEnum.push_back(e);
		}

		//struct declaration
		TiXmlElement* pElemDeclStruct = pElemTypeDef->FirstChildElement(ELEMENT_DECLSTRUCT);
		while(pElemDeclStruct != NULL)
		{
			SStruct* pStruct = new SStruct;
			if(pStruct == NULL)
			{
				cerr << "No memory available!" << endl;
				return false;
			}
			if(!ParseElemStruct(pElemDeclStruct, *pStruct))
				return false;
			pStruct->bHasSub = true;
			_vecDeclStruct.push_back(pStruct);
			pElemDeclStruct = pElemDeclStruct->NextSiblingElement(ELEMENT_DECLSTRUCT);
		}

		//struct
		TiXmlElement* pElemStruct = pElemTypeDef->FirstChildElement(ELEMENT_STRUCT);
		while(pElemStruct != NULL)
		{
			if(!CheckChildElem(pElemStruct, ELEMENT_MEMBER, ELEMENT_SUBSTRUCT))
				return false;

			SStruct* pStruct = new SStruct;
			if(pStruct == NULL)
			{
				cerr << "No memory available!" << endl;
				return false;
			}
			if(!ParseElemStruct(pElemStruct, *pStruct))
				return false;
			_vecStruct.push_back(pStruct);

			vector<SStruct*> vecSubStruct;
			if(!ParseElemSubStruct(pElemStruct, *pStruct, vecSubStruct))
				return false;

			if(!vecSubStruct.empty())
			{
				SEnum e;
				e.strName = "EType_" + pStruct->strName;
				e.strComment = "结构体：" + pStruct->strName + "的继承体系类型";
				vecSubStruct.insert(vecSubStruct.begin(), pStruct);
				INT64 qwValue = 0;
				for(size_t i = 0; i < vecSubStruct.size(); ++i)
				{
					SMember m;
					m.strName = "eType_" + vecSubStruct[i]->strName;
					m.qwValue = qwValue++;
					m.strComment = "类型：" + vecSubStruct[i]->strName;
					e.vecMember.push_back(m);
				}
				e.byByte = 1;
				e.bClassType = true;
				_vecEnum.push_back(e);
			}
			pElemStruct = pElemStruct->NextSiblingElement(ELEMENT_STRUCT);
		}

		for(size_t i = 0; i < _vecDeclStruct.size(); ++i)
		{
			SStruct* pStruct = _vecDeclStruct[i];
			SStruct* pRelStruct = GetStruct(pStruct->strName);
			if(pRelStruct == NULL)
			{
				cerr << "Can't find the definition of Struct: " << pStruct->strName << endl;
				return false;
			}
			if(!pRelStruct->bHasSub)
			{
				cerr << "Can't forward declare Struct: " << pStruct->strName << endl;
				return false;
			}
		}
	}

	int i = 1;
	_iNextRetID = -1;
	TiXmlElement* pElemFuncC2S = pElemRoot->FirstChildElement(ELEMENT_FUNCC2S);
	if(pElemFuncC2S != NULL)
	{
		if(!CheckChildElem(pElemFuncC2S, ELEMENT_FUNC))
			return false;

		const char* pClient = pElemFuncC2S->Attribute(ATTRIBUTE_CLIENT);
		if(pClient != NULL)
		{
			string strClient = ToLower(pClient);
			if(strClient.find(ToLower("CppClt")) != string::npos)
				_dwClientType |= eClientCppClt;
			if(strClient.find(ToLower("CppSvr")) != string::npos)
				_dwClientType |= eClientCppSvr;
			if(strClient.find(ToLower("ActionScript")) != string::npos)
				_dwClientType |= eClientAs;
			if(strClient.find(ToLower("PHP")) != string::npos)
				_dwClientType |= eClientPhp;
			if(_dwClientType == 0)
				cerr << "Unknown Client Type: " << pClient << endl;
			else if(HasClientType(eClientCppClt) && HasClientType(eClientCppSvr))
				cerr << "Shouldn't has both CppClt and CppSvr: " << endl;
		}

		const char* pRpc = pElemFuncC2S->Attribute(ATTRIBUTE_RPC);
		if(pRpc != NULL && strcasecmp(pRpc, "rpc") == 0)
			_bClientRpc = true;
		else
			_bClientRpc = false;

		TiXmlElement* pElemFunc = pElemFuncC2S->FirstChildElement(ELEMENT_FUNC);
		while(pElemFunc != NULL)
		{
			if(!CheckChildElem(pElemFunc, ELEMENT_PARAM, ELEMENT_LOCPARAM, ELEMENT_RETPARAM))
				return false;

			SFunc f;
			if(!ParseElemFunc(pElemFunc, f, true))
				return false;
			f.ID = i++;
			if(f.ID > 127)
			{
				cerr << "Function ID is greater than 127!" << endl;
				return false;
			}
			pElemFunc = pElemFunc->NextSiblingElement(ELEMENT_FUNC);
			_vecFuncC2S.push_back(f);
		}
	}

	i = 1;
	_iNextRetID = -1;
	TiXmlElement* pElemFuncS2C = pElemRoot->FirstChildElement(ELEMENT_FUNCS2C);
	if(pElemFuncS2C != NULL)
	{
		if(!CheckChildElem(pElemFuncS2C, ELEMENT_FUNC))
			return false;

		TiXmlElement* pElemFunc = pElemFuncS2C->FirstChildElement(ELEMENT_FUNC);
		while(pElemFunc != NULL)
		{
			if(!CheckChildElem(pElemFunc, ELEMENT_PARAM, ELEMENT_LOCPARAM, ELEMENT_RETPARAM))
				return false;

			SFunc f;
			if(!ParseElemFunc(pElemFunc, f, false))
				return false;
			f.ID = i++;
			if(f.ID > 127)
			{
				cerr << "Function ID is greater than 127!" << endl;
				return false;
			}
			pElemFunc = pElemFunc->NextSiblingElement(ELEMENT_FUNC);
			_vecFuncS2C.push_back(f);
		}
	}
	return true;
}
