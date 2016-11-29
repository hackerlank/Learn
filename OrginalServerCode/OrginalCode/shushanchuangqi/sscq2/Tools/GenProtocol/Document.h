/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	Document.h
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

#pragma once
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string/trim_all.hpp>
#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#include <codecvt>
#define PATHSEP "\\"
#define strcasecmp _stricmp
#define localtime_r(t, tm) localtime_s(tm, t)
#define mkdir(name, mode) _mkdir(name)
#else
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "Utility/Linux.h"
#define CP_UTF8 1
#define CP_ACP 0
#define PATHSEP "/"
#endif

/*是否生成文件的修改时间*/
//#define GEN_FILE_TIME

/*是否一直生成客户端的CPP文件*/
//#define FORCE_GEN_CPP_CLT

/*是否生成OnRecv函数的空函数体*/
//#define FORCE_GEN_RECV_IMPL

/*是否生成PHP的名称空间(PHP5.3以上才支持)*/
//#define PHP_USE_NAME_SPACE

using namespace std;

class CDocument;

struct SElement
{
	SElement() : byByte(0), bIsMember(false), bByteArray(false), bMoveCtor(false),
		bBase(false), bBaseVec(false), bHasBase(false), bHasBaseVec(false) { }
	virtual ~SElement() { }
	virtual bool IsMember() const { return false; }
	virtual bool IsParam() const { return false; }
	string GetASComment(CDocument& rDocument) const;
	string GetPHPComment(CDocument& rDocument) const;
	string GetRubyComment(CDocument& rDocument) const;
	string strName;
	string strTypeName;
	string strDefaultValue;
	string strComment;
	UINT8 byByte;
	bool bIsMember;
	bool bByteArray;
	bool bMoveCtor;
	bool bBase;
	bool bBaseVec;
	bool bHasBase;
	bool bHasBaseVec;
};

struct SMember : public SElement
{
	SMember() : qwValue(0), bOperator(false) { bIsMember = true; }
	virtual bool IsMember() const override { return true; }
	INT64 qwValue;
	bool bOperator;
};

enum EGlobalType
{
	eGlobalNone,
	eGlobalClient,
	eGlobalServer,
	eGlobalBoth
};

struct SEnum
{
	SEnum() : eGlobalType(eGlobalNone), byByte(1), wMaxValIndex(-1), bDesc(false), bClassType(false) { }
	vector<SMember> vecMember;
	string strName;
	string strComment;
	EGlobalType eGlobalType;
	INT8 byByte;
	INT16 wMaxValIndex;
	bool bDesc;
	bool bClassType;
};

struct SStruct
{
	SStruct() : eGlobalType(eGlobalNone), bUsePtr(false), bUseINT64(false), bMoveCtor(false),
		bHasSub(false), bHasBase(false), bSuperHasBase(false), byDBLen(2) { }
	vector<SMember> vecMember;
	string strName;
	string strVecName;
	string strComment;
	string strSuperName;
	vector<string> vecSubName;
	EGlobalType eGlobalType;
	bool bUsePtr;
	bool bUseINT64;
	bool bMoveCtor;
	bool bHasSub;
	bool bHasBase;
	bool bSuperHasBase;
	UINT8 byDBLen;
};

class CDocument;

struct SParam : public SElement
{
	SParam() : bByRef(false), bKeep(false), bLocal(false) { }
	virtual bool IsParam() const override { return true; }
	bool bByRef;
	bool bKeep;
	bool bLocal;
};

struct SFunc
{
	SFunc() : ID(0), iRetID(0), dwCbkParamCount(0), dwSessDataCount(0), bPkg(false), bReturn(false), bMultiReturn(false), bKeepParam(false) { }
	string strName;
	int ID;
	int iRetID;
    string strAckMsg;
	UINT32 dwCbkParamCount;
	UINT32 dwSessDataCount;
	vector<SParam> vecParam;
	vector<SParam> vecLocParam;
	vector<SParam> vecRetParam;
	string strComment;
	bool bPkg;
	bool bReturn;
	bool bMultiReturn;
	bool bKeepParam;
};

struct SRefType
{
	CDocument* pDocument;
	string strPackage;
	string strTypeName;
};

enum EProxyType
{
	eProxyNone,
	eProxyGame,
	eProxyCenter,
	eProxyDB
};

enum EClientType
{
	eClientNone,
	eClientCppClt = 1,
	eClientCppSvr = 1 << 1,
	eClientAs = 1 << 2,
	eClientPhp = 1 << 3
};

const char* GetTypeConvert(INT8 byByte);
string HeadToLower(const string& str);

class TiXmlElement;

class CDocument
{
	friend struct SParam;
public:
	CDocument();
	~CDocument();
	bool ParseXML(const char* szFileName);
	bool GenCodeFile(const char* szDestDir);
	bool GenActionScript(const char* szDestDir, const char* szPkg);
	bool GenPHP(const char* szDestDir);
	bool GenRuby(const char* szDestDir);

	string GetASComment(const string& strTypeName, const string& strComment);
	string GetPHPComment(const string& strTypeName, const string& strComment);
	string GetRubyComment(const string& strTypeName, const string& strComment);

	void SetDir(const string& strDir) { _strDir = strDir; }

protected:
	bool HasClientType(EClientType eClientType);
	bool HasOnlyClientType(EClientType eClientType);
	void GetFileTime(const char* szFileName);
	string GetStringValue(const char* pszValue);
	string GetTypeName(const string& strTypeName);
	SStruct* GetStruct(const string& strName, bool bVec = false);
	SRefType* GetRefStruct(const string& strName, bool bVec, SStruct** ppStruct = NULL);
	SStruct* GetDeclStruct(const string& strName, bool bVec = false);
	SEnum* GetEnum(const string& strName);
	SMember* GetEnumItem(const string& strName, SEnum** ppEnum = NULL);
	SRefType* GetRefEnumType(const string& strTypeName);
	bool RecordRefEnumItem(const string& strName, SMember** ppMember = NULL);
	SRefType* GetRefEnumItem(const string& strName, SEnum** ppEnum = NULL, SMember** ppMember = NULL);
	bool GetDefaultValue(const SElement& rElement, string& strValue);

	bool ParseElemParam(TiXmlElement* pElemParam, SFunc& f, SParam& p);
	bool ParseElemFunc(TiXmlElement* pElemFunc, SFunc& f, bool bC2S);
	bool ParseElemStruct(TiXmlElement* pElemStruct, SStruct& s);
	bool ParseElemSubStruct(TiXmlElement* pElemStruct, SStruct& s, vector<SStruct*>& rVecSubStruct);
	bool CheckType(SElement& rElement, bool bForDB = false);

	void PrintHeader(const string& strPath, bool bServer);
	void PrintCPP(const string& strPath, bool bServer);
	void PrintTypeHeader(const string& strPath);
	void PrintTypeCPP(const string& strPath);
	void PrintCallBackFunc(ostringstream& os, SFunc& rFunc, const char* pszIndent);
	void PrintFuncParamList(ostringstream& os, SFunc& rFunc, bool bHeader);
	void PrintFuncParam(ostringstream& os, SParam& rParam, const char* pszIndent);
	void PrintRecvFunc(ostringstream& os, SFunc& rFunc);
	void PrintRetParam(ostringstream& os, SFunc& rFunc);
	void PrintStructArchive(ostringstream& os, SStruct& rStruct);
	void PrintStructToXML(ostringstream& os, SStruct& rStruct);
	void PrintStructFromXML(ostringstream& os, SStruct& rStruct);
	void PrintSuperToXML(ostringstream& os, SStruct& rStruct);
	void PrintSuperFromXML(ostringstream& os, SStruct& rStruct);
	void PrintVectorToXML(ostringstream& os, SStruct& rStruct);
	void PrintVectorFromXML(ostringstream& os, SStruct& rStruct);
	void PrintArchive(ostringstream& os, SFunc& rFunc, bool bServer, bool bParam = false);
	UINT32 PrintDefaultValue(ostringstream& os, const vector<SElement>& vecElement);
	bool PrintProxyCode(const string& strPath);

	bool FindElemType(const string& strVecType, string& strElemType);
	bool IsBuiltInType(const string& strTypeName);
	bool IsEnumType(const string& strTypeName);
	bool IsRefEnumType(const string& strTypeName);
	bool IsStringType(const string& strTypeName);
	bool IsPrimType(const string& strTypeName);
	bool IsVectorType(const string& strTypeName);
	bool GetStructNameByVec(const string& strVecName, string& strName);
	string GetBaseClassName(const string& strName);
	string GetSessionDataType(SFunc& rFunc);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Action Script
	string GetASTypeName(const string& strTypeName);
	string GetASTypeName(const SElement& rElement);
	string GetASWriteExpr(const SElement& rElement, const string& strByteArray);
	string GetASReadExpr(const SElement& rElement, const string& strByteArray);

	bool GetASEnumItemName(const string& strName, string& strASName, const SEnum* pCurEnum = NULL);

	void PrintASRecvFunc(ostringstream& os, SFunc& rFunc);
	void PrintASRetParam(ostringstream& os, SFunc& rFunc);

	void PrintASEnum(const SEnum& rEnum, const string& strPkg, const string& strPkgPath);
	bool PrintASEnumComment();
	void PrintASStruct(const SStruct& rStruct, const string& strPkg, const string& strPkgPath);
	void PrintASRetStruct(const SFunc& rFunc, const string& strPkg, const string& strPkgPath);
	void PrintASRecvEvent(SFunc& rFunc, const string& strPkg, const string& strPkgPath);
	void PrintASReturnEvent(SFunc& rFunc, const string& strPkg, const string& strPkgPath);

	template<typename T>
	bool PrintImportRef(ostringstream& os, const vector<T>& rVec);
	bool PrintAllImportRef(ostringstream& os);

	template<typename T>
	void PrintASTypeToXML(ostringstream& os, const string& strTypeName, const vector<T>& rVec, bool bUseName = false, bool bHasSuper = false);
	void PrintASCompTypeToXML(ostringstream& os, const string& strName, const string& strTypeName, UINT32 dwIndex);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//PHP
	void PrintPHPDefaultValue(ostringstream& os, const SElement& rElement);
	void PrintPHPRetParam(ostringstream& os, SFunc& rFunc);
	string GetPHPWriteExpr(const SElement& rElement, const string& strStream);
	string GetPHPReadExpr(const SElement& rElement, const string& strStream);
	bool GetPHPEnumItemName(const string& strName, string& strPHPName, const SEnum* pCurEnum = NULL);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Ruby
	void PrintRubyDefaultValue(ostringstream& os, const SElement& rElement);
	void PrintRubyRetParam(ostringstream& os, SFunc& rFunc);
	string GetRubyWriteExpr(const SElement& rElement, const string& strStream);
	string GetRubyReadExpr(const SElement& rElement, const string& strStream);
	bool GetRubyItemName(const string& strName, string& strRubyName, const SEnum* pCurEnum = NULL);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool _bHasC2SRetFunc;
	bool _bHasS2CRetFunc;
	bool _bClientRpc;
	bool _bUseVector;
	bool _bUseINT64;
	string _strName;
	string _strClassName;
	string _strNameSpace;
	int _ID;
	string _strComment;
	vector<SEnum> _vecEnum;
	vector<SStruct*> _vecStruct;
	vector<SStruct*> _vecDeclStruct;
	vector<SFunc> _vecFuncC2S;
	vector<SFunc> _vecFuncS2C;
	set<string> _setPrimType;
	map<string, string> _mapPrimVecType;
	string _strFileName;
	string _strGenTime;
	map<string, CDocument*> _mapProt2Doc;
	string _strASPkgBase;
	string _strASDestDir;
	map<string, SRefType> _mapType2Ref;

	int _iNextRetID;
	string _strDir;
	EProxyType _eProxyType;
	UINT32 _dwClientType;
};
