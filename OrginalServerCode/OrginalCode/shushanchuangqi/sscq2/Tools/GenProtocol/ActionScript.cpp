/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	Document.h
//	Created:	2012/08/11	10:00
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

#include <boost/algorithm/string/replace.hpp>
#include "Document.h"
#include "Directory.h"
#include "Encode.h"

using namespace std;
using namespace boost;

string HeadToLower(const string& str)
{
	string strLower = str;
	strLower[0] = tolower(strLower[0]);
	return strLower;
}

string NumberToText(INT32 dwValue)
{
	char szBuf[100];
	sprintf_s(szBuf, "%d", dwValue);
	return szBuf;
}

string GetASEnumType(INT8 byByte)
{
	if(byByte > 0)
		return "uint";
	else if(byByte < 0)
		return "int";
	return "ErrorType";
}

///////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
bool PrintImportUINT64(ostringstream& os, const vector<T>& rVec)
{
	for(size_t i = 0; i < rVec.size(); ++i)
	{
		const T& rT = rVec[i];
		if(rT.strTypeName.find("INT64") != string::npos)
		{
			os << "\timport com.hurlant.math.BigInteger;\n";
			return true;
		}
	}
	return false;
}

template<typename T>
bool PrintImportByteArray(ostringstream& os, const vector<T>& rVec)
{
	for(size_t i = 0; i < rVec.size(); ++i)
	{
		const T& rT = rVec[i];
		if(rT.bByteArray)
		{
			os << "\timport flash.utils.ByteArray;\n";
			os << "\timport net.util.BytesUtil;\n";
			return true;
		}
	}
	return false;
}

template<typename T>
bool CDocument::PrintImportRef(ostringstream& os, const vector<T>& rVec)
{
	vector<SRefType> vecRefType;
	for(size_t i = 0; i < rVec.size(); ++i)
	{
		const T& rT = rVec[i];
		auto it = _mapType2Ref.find(rT.strTypeName);
		if(it != _mapType2Ref.end())
		{
			SRefType& rRefType = it->second;
			if(rRefType.pDocument == NULL)
			{
				cerr << "Error package " << rRefType.strPackage << endl;
				return false;
			}
			if(rRefType.strTypeName.find("TVec") == 0)
			{
				string strTypeName;
				if(!rRefType.pDocument->GetStructNameByVec(rRefType.strTypeName, strTypeName))
				{
					cerr << "Error vector type " << rRefType.strTypeName << endl;
					return false;
				}
				SRefType oRefType = { NULL, rRefType.strPackage, strTypeName };
				vecRefType.push_back(oRefType);
			}
			else
			{
				SEnum* pEnum = NULL;
				SMember* pMember = rRefType.pDocument->GetEnumItem(rRefType.strTypeName, &pEnum);
				if(pMember != NULL)
				{
					SRefType oRefType = { NULL, rRefType.strPackage, pEnum->strName };
					vecRefType.push_back(oRefType);
				}
				else if(!rRefType.pDocument->IsEnumType(rRefType.strTypeName))
				{
					vecRefType.push_back(rRefType);
				}
			}
		}
	}
	for(size_t i = 0; i < vecRefType.size(); ++i)
	{
		SRefType& rRefType = vecRefType[i];
		os << "\timport " << _strASPkgBase << "." << rRefType.strPackage << "." << rRefType.strTypeName << ";\n";
	}
	if(vecRefType.empty())
		return false;
	return true;
}

bool CDocument::PrintAllImportRef(ostringstream& os)
{
	map<string, SRefType> mapRefType;
	for(auto it = _mapType2Ref.begin(); it != _mapType2Ref.end(); ++it)
	{
		SRefType& rRefType = it->second;
		if(rRefType.pDocument == NULL)
		{
			cerr << "Error package " << rRefType.strPackage << endl;
			return false;
		}
		if(rRefType.strTypeName.find("TVec") == 0)
		{
			string strTypeName;
			if(!rRefType.pDocument->GetStructNameByVec(rRefType.strTypeName, strTypeName))
			{
				cerr << "Error vector type " << rRefType.strTypeName << endl;
				return false;
			}
			SRefType oRefType = { NULL, rRefType.strPackage, strTypeName };
			mapRefType.insert(make_pair(strTypeName, oRefType));
		}
		else
		{
			SMember* pMember = rRefType.pDocument->GetEnumItem(rRefType.strTypeName);
			if(pMember == NULL && !rRefType.pDocument->IsEnumType(rRefType.strTypeName))
				mapRefType.insert(make_pair(rRefType.strTypeName, rRefType));
		}
	}
	for(auto it = mapRefType.begin(); it != mapRefType.end(); ++it)
	{
		SRefType& rRefType = it->second;
		os << "\timport " << _strASPkgBase.c_str() << "." << rRefType.strPackage.c_str() << "." << rRefType.strTypeName.c_str() << ";\n";
	}
	if(mapRefType.empty())
		return false;
	return true;
}

template<typename T>
void CDocument::PrintASTypeToXML(ostringstream& os, const string& strTypeName, const vector<T>& rVec, bool bUseName /*= false*/, bool bHasSuper /*= false*/)
{
	os << "\t\t/**\n";
	os << "\t\t * 转换为XML\n";
	if(bUseName)
	{
		os << "\t\t * @param name_ 此类型作为成员变量时的变量名\n";
		os << "\t\t */\n";
		if(bHasSuper)
			os << "\t\tpublic override function toXML(name_:String = null):XML\n";
		else
			os << "\t\tpublic function toXML(name_:String = null):XML\n";
	}
	else
	{
		os << "\t\t */\n";
		if(bHasSuper)
			os << "\t\tpublic override function toXML():XML\n";
		else
			os << "\t\tpublic function toXML():XML\n";
	}
	os << "\t\t{\n";

	string strTail;
	vector<const T*> vecCompType;
	for(size_t i = 0; i < rVec.size(); ++i)
	{
		const T& rT = rVec[i];
		if(_setPrimType.find(rT.strTypeName) != _setPrimType.end() || IsStringType(rT.strTypeName)
			|| rT.bByteArray || IsEnumType(rT.strTypeName) || IsRefEnumType(rT.strTypeName))
		{
			if(i > 0 && i % 5 == 0)
				strTail += "\n\t\t\t\t";
			strTail += " " + rT.strName + "={";
			if(rT.bByteArray)
				strTail += "BytesUtil.bytes2String(" + rT.strName + ")}";
			else
				strTail += rT.strName + "}";
		}
		else
		{
			vecCompType.push_back(&rT);
		}
	}
	strTail += "/>;\n";

	if(bUseName)
	{
		os << "\t\t\tvar topXml:XML\n";
		os << "\t\t\tif(name_ != null && name_ != \"\")\n";
		os << "\t\t\t\ttopXml = <" << strTypeName << " _name_={name_}" << strTail;
		os << "\t\t\telse\n";
		os << "\t\t\t\ttopXml = <" << strTypeName << strTail;
	}
	else
	{
		os << "\t\t\tvar topXml:XML = <" << strTypeName << strTail;
	}
	for(UINT32 i = 0; i < (UINT32)vecCompType.size(); ++i)
	{
		const T* pT = vecCompType[i];
		PrintASCompTypeToXML(os, pT->strName, pT->strTypeName, i + 1);
	}
	if(bUseName && bHasSuper)
		os << "\t\t\ttopXml.appendChild(super.toXML(name_));\n";
	os << "\t\t\treturn topXml;\n";
	os << "\t\t}\n";
}

void CDocument::PrintASCompTypeToXML(ostringstream& os, const string& strName, const string& strTypeName, UINT32 dwIndex)
{
	if(!IsVectorType(strTypeName))
	{
		os << "\t\t\tif(" << strName << " != null)\n";
		os << "\t\t\t\ttopXml.appendChild(" << strName << ".toXML(\"" << strName << "\"));\n";
		return;
	}
	auto it = _mapPrimVecType.find(strTypeName);
	if(it != _mapPrimVecType.end())
	{
		string strPrimTypeName = it->second;
		string strASType = GetASTypeName(strPrimTypeName);
		os << "\t\t\tif(" << strName << " != null)\n";
		os << "\t\t\t{\n";
		os << "\t\t\t\tvar " << strName << "Xml:XML = <Vec_" << strPrimTypeName << " _name_=\"" << strName << "\"/>;\n";
		os << "\t\t\t\tvar text" << dwIndex << ":String = \"\";\n";
		os << "\t\t\t\tfor each(var value" << dwIndex << ":" << strASType << " in " << strName << ")\n";
		os << "\t\t\t\t\ttext" << dwIndex << " += \"[\" + value" << dwIndex << " + \"]\";\n";
		os << "\t\t\t\t" << strName << "Xml.appendChild(text" << dwIndex << ");\n";
		os << "\t\t\t\ttopXml.appendChild(" << strName << "Xml);\n";
		os << "\t\t\t}\n";
		return;
	}
	SStruct* pStruct = GetStruct(strTypeName, true);
	if(pStruct == NULL)
		GetRefStruct(strTypeName, true, &pStruct);
	if(pStruct != NULL)
	{
		os << "\t\t\tif(" << strName << " != null)\n";
		os << "\t\t\t{\n";
		os << "\t\t\t\tvar " << strName << "Xml:XML = <Vec_" << pStruct->strName << " _name_=\"" << strName << "\"/>;\n";
		os << "\t\t\t\tfor each(var s" << dwIndex << ":" << pStruct->strName << " in " << strName << ")\n";
		os << "\t\t\t\t\t" << strName << "Xml.appendChild(s" << dwIndex << ".toXML());\n";
		os << "\t\t\t\ttopXml.appendChild(" << strName << "Xml);\n";
		os << "\t\t\t}\n";
		return;
	}
	cerr << "Fail to print XML for variable: " << strName << ", type: " << strTypeName << endl;
}

string CDocument::GetASTypeName(const string& strTypeName)
{
	static map<string, string> mapASType;
	if(mapASType.empty())
	{
		mapASType["INT8"] = "int";
		mapASType["INT16"] = "int";
		mapASType["INT32"] = "int";
		mapASType["INT64"] = "BigInteger";
		mapASType["UINT8"] = "uint";
		mapASType["UINT16"] = "uint";
		mapASType["UINT32"] = "uint";
		mapASType["UINT64"] = "BigInteger";
		mapASType["float"] = "Number";
		mapASType["double"] = "Number";
		mapASType["bool"] = "Boolean";
		mapASType["string"] = "String";

		mapASType["TVecINT8"] = "Vector.<int>";
		mapASType["TVecINT16"] = "Vector.<int>";
		mapASType["TVecINT32"] = "Vector.<int>";
		mapASType["TVecINT64"] = "Vector.<BigInteger>";
		mapASType["TVecUINT8"] = "Vector.<uint>";
		mapASType["TVecUINT16"] = "Vector.<uint>";
		mapASType["TVecUINT32"] = "Vector.<uint>";
		mapASType["TVecUINT64"] = "Vector.<BigInteger>";
		mapASType["TVecFloat"] = "Vector.<Number>";
		mapASType["TVecDouble"] = "Vector.<Number>";
		mapASType["TVecBool"] = "Vector.<Boolean>";
		mapASType["TVecString"] = "Vector.<String>";
	}

	auto it = mapASType.find(strTypeName);
	if(it != mapASType.end())
		return it->second;

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return GetASEnumType(pEnum->byByte);

	for(size_t i = 0, size = _vecStruct.size(); i < size; ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(strTypeName == rStruct.strName)
			return strTypeName;
		if(!rStruct.strVecName.empty() && strTypeName == rStruct.strVecName)
			return "Vector.<" + rStruct.strName + ">";
	}

	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef != _mapType2Ref.end())
	{
		SRefType& rRefType = itRef->second;
		if(rRefType.pDocument == NULL)
		{
			cerr << "Error package " << rRefType.strPackage << endl;
			return "ErrorPackage";
		}
		if(rRefType.strTypeName.find("TVec") == 0)
		{
			string strName;
			if(!rRefType.pDocument->GetStructNameByVec(rRefType.strTypeName, strName))
			{
				cerr << "Error vector type " << rRefType.strTypeName << endl;
				return "ErrorVector";
			}
			return "Vector.<" + strName + ">";
		}
		SEnum* pEnum = rRefType.pDocument->GetEnum(rRefType.strTypeName);
		if(pEnum != NULL)
			return GetASEnumType(pEnum->byByte);
		return rRefType.strTypeName;
	}
	cerr << "Unknown AS Type " << strTypeName << endl;
	return "Unknown";
}

string CDocument::GetASTypeName(const SElement& rElement)
{
	if(rElement.bByteArray)
		return "ByteArray";
	return GetASTypeName(rElement.strTypeName);
}

string CDocument::GetASComment(const string& strTypeName, const string& strComment)
{
	bool bFound = false;
	string strDesc;
	size_t pos = strTypeName.find("INT8");
	if(pos != string::npos)
	{
		bFound = true;
		strDesc = "符号8位整数)";
		goto FOUND;
	}
	pos = strTypeName.find("INT16");
	if(pos != string::npos)
	{
		bFound = true;
		strDesc = "符号16位整数)";
		goto FOUND;
	}
	pos = strTypeName.find("INT32");
	if(pos != string::npos)
	{
		bFound = true;
		strDesc = "符号32位整数)";
		goto FOUND;
	}
	pos = strTypeName.find("INT64");
	if(pos != string::npos)
	{
		bFound = true;
		strDesc = "符号64位整数)";
	}
FOUND:
	if(bFound)
	{
		if(pos == 0 || strTypeName[pos - 1] != 'U')
			return "(有" + strDesc + strComment;
		return "(无" + strDesc + strComment;
	}
	if(strTypeName == "float" || strTypeName == "TVecFloat")
		return "(Float)" + strComment;
	if(strTypeName == "double" || strTypeName == "TVecDouble")
		return "(Double)" + strComment;
	if(IsEnumType(strTypeName))
		return "(枚举类型：" + strTypeName + ")" + strComment;
	SRefType* pRefType = GetRefEnumType(strTypeName);
	if(pRefType != NULL)
		return "(枚举类型：" + pRefType->strPackage + "." + pRefType->strTypeName + ")" + strComment;
	return strComment;
}

static string GetEnumWrite(const SEnum& rEnum, const string& strName)
{
	switch(rEnum.byByte)
	{
	case -1:
	case 1:
		return ".writeByte(" + strName + ");";
	case -2:
	case 2:
		return ".writeShort(" + strName + ");";
	case -4:
		return ".writeInt(" + strName + ");";
	case 4:
		return ".writeUnsignedInt(" + strName + ");";
	default:
		cerr << "Enum:" << rEnum.strName << " Byte:" << rEnum.byByte << " is invalid!" << endl;
		return "ErrorEnumByte";
	}
}

string CDocument::GetASWriteExpr(const SElement& rElement, const string& strByteArray)
{
	static map<string, string> mapASExpr;
	char szBuf[0x100];
	if(mapASExpr.empty())
	{
		mapASExpr["INT8"] = "%s.writeByte(%s);";
		mapASExpr["INT16"] = "%s.writeShort(%s);";
		mapASExpr["INT32"] = "%s.writeInt(%s);";
		mapASExpr["INT64"] = "BytesUtil.writeInt64(%s, %s);";
		mapASExpr["UINT8"] = "%s.writeByte(%s);";
		mapASExpr["UINT16"] = "%s.writeShort(%s);";
		mapASExpr["UINT32"] = "%s.writeUnsignedInt(%s);";
		mapASExpr["UINT64"] = "BytesUtil.writeUInt64(%s, %s);";
		mapASExpr["float"] = "%s.writeFloat(%s);";
		mapASExpr["double"] = "%s.writeDouble(%s);";
		mapASExpr["bool"] = "%s.writeBoolean(%s);";
		mapASExpr["string"] = "BytesUtil.writeString(%s, %s);";

		mapASExpr["TVecINT8"] = "BytesUtil.writeVecByte(%s, %s);";
		mapASExpr["TVecINT16"] = "BytesUtil.writeVecShort(%s, %s);";
		mapASExpr["TVecINT32"] = "BytesUtil.writeVecInt(%s, %s);";
		mapASExpr["TVecINT64"] = "BytesUtil.writeVecInt64(%s, %s);";
		mapASExpr["TVecUINT8"] = "BytesUtil.writeVecUByte(%s, %s);";
		mapASExpr["TVecUINT16"] = "BytesUtil.writeVecUShort(%s, %s);";
		mapASExpr["TVecUINT32"] = "BytesUtil.writeVecUInt(%s, %s);";
		mapASExpr["TVecUINT64"] = "BytesUtil.writeVecUInt64(%s, %s);";
		mapASExpr["TVecFloat"] = "BytesUtil.writeVecFloat(%s, %s);";
		mapASExpr["TVecDouble"] = "BytesUtil.writeVecDouble(%s, %s);";
		mapASExpr["TVecBool"] = "BytesUtil.writeVecBool(%s, %s);";
		mapASExpr["TVecString"] = "BytesUtil.writeVecString(%s, %s);";
	}
	const string& strName = rElement.strName;
	const string& strTypeName = rElement.strTypeName;
	if(rElement.bByteArray)
	{
		sprintf_s(szBuf, "BytesUtil.writeBytes(%s, %s);", strByteArray.c_str(), strName.c_str());
		return szBuf;
	}
	auto it = mapASExpr.find(strTypeName);
	if(it != mapASExpr.end())
	{
		const string& strExpr = it->second;
		sprintf_s(szBuf, strExpr.c_str(), strByteArray.c_str(), strName.c_str());
		return szBuf;
	}

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return strByteArray + GetEnumWrite(*pEnum, strName);

	SStruct* pStruct = GetStruct(strTypeName);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return strName + ".toByteArray(" + strByteArray + ");";
		else
			return strName + ".superToByteArray(" + strByteArray + ");";
	}

	pStruct = GetStruct(strTypeName, true);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return pStruct->strName + ".vectorToByteArray(" + strName + ", " + strByteArray + ");";
		else
			return pStruct->strName + ".superVectorToByteArray(" + strName + ", " + strByteArray + ");";
	}

	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef != _mapType2Ref.end())
	{
		SRefType& rRefType = itRef->second;
		if(rRefType.pDocument == NULL)
		{
			cerr << "Error package: " << rRefType.strPackage << endl;
			return "ErrorPackage";
		}
		pEnum = rRefType.pDocument->GetEnum(rRefType.strTypeName);
		if(pEnum != NULL)
			return strByteArray + GetEnumWrite(*pEnum, strName);
		pStruct = rRefType.pDocument->GetStruct(rRefType.strTypeName);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return strName + ".toByteArray(" + strByteArray + ");";
			else
				return strName + ".superToByteArray(" + strByteArray + ");";
		}
		pStruct = rRefType.pDocument->GetStruct(rRefType.strTypeName, true);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return pStruct->strName + ".vectorToByteArray(" + strName + ", " + strByteArray + ");";
			else
				return pStruct->strName + ".superVectorToByteArray(" + strName + ", " + strByteArray + ");";
		}
	}
	cerr << "Invalid Write Expression For " << strTypeName << endl;
	return "Invalid Write Expression";
}

static string GetEnumRead(const SEnum& rEnum)
{
	switch(rEnum.byByte)
	{
	case -1:
		return ".readByte();";
	case -2:
		return ".readShort();";
	case -4:
		return ".readInt();";
	case 1:
		return ".readUnsignedByte();";
	case 2:
		return ".readUnsignedShort();";
	case 4:
		return ".readUnsignedInt();";
	default:
		cerr << "Enum:" << rEnum.strName << " Byte:" << rEnum.byByte << " is invalid!" << endl;
		return "ErrorEnumByte";
	}
}

string CDocument::GetASReadExpr(const SElement& rElement, const string& strByteArray)
{
	static map<string, string> mapASExpr;
	char szBuf[0x100];
	if(mapASExpr.empty())
	{
		mapASExpr["INT8"] = "var %s:int = %s.readByte();";
		mapASExpr["INT16"] = "var %s:int = %s.readShort();";
		mapASExpr["INT32"] = "var %s:int = %s.readInt();";
		mapASExpr["INT64"] = "var %s:BigInteger = BytesUtil.readInt64(%s);";
		mapASExpr["UINT8"] = "var %s:uint = %s.readUnsignedByte();";
		mapASExpr["UINT16"] = "var %s:uint = %s.readUnsignedShort();";
		mapASExpr["UINT32"] = "var %s:uint = %s.readUnsignedInt();";
		mapASExpr["UINT64"] = "var %s:BigInteger = BytesUtil.readUInt64(%s);";
		mapASExpr["float"] = "var %s:Number = %s.readFloat();";
		mapASExpr["double"] = "var %s:Number = %s.readDouble();";
		mapASExpr["bool"] = "var %s:Boolean = %s.readBoolean();";
		mapASExpr["string"] = "var %s:String = BytesUtil.readString(%s);";

		mapASExpr["TVecINT8"] = "var %s:Vector.<int> = BytesUtil.readVecByte(%s);";
		mapASExpr["TVecINT16"] = "var %s:Vector.<int> = BytesUtil.readVecShort(%s);";
		mapASExpr["TVecINT32"] = "var %s:Vector.<int> = BytesUtil.readVecInt(%s);";
		mapASExpr["TVecINT64"] = "var %s:Vector.<BigInteger> = BytesUtil.readVecInt64(%s);";
		mapASExpr["TVecUINT8"] = "var %s:Vector.<uint> = BytesUtil.readVecUByte(%s);";
		mapASExpr["TVecUINT16"] = "var %s:Vector.<uint> = BytesUtil.readVecUShort(%s);";
		mapASExpr["TVecUINT32"] = "var %s:Vector.<uint> = BytesUtil.readVecUInt(%s);";
		mapASExpr["TVecUINT64"] = "var %s:Vector.<BigInteger> = BytesUtil.readVecUInt64(%s);";
		mapASExpr["TVecFloat"] = "var %s:Vector.<Number> = BytesUtil.readVecFloat(%s);";
		mapASExpr["TVecDouble"] = "var %s:Vector.<Number> = BytesUtil.readVecDouble(%s);";
		mapASExpr["TVecBool"] = "var %s:Vector.<Boolean> = BytesUtil.readVecBool(%s);";
		mapASExpr["TVecString"] = "var %s:Vector.<String> = BytesUtil.readVecString(%s);";
	}
	const string& strName = rElement.strName;
	const string& strTypeName = rElement.strTypeName;
	if(rElement.bByteArray)
	{
		sprintf_s(szBuf, "var %s:ByteArray = BytesUtil.readBytes(%s);", strName.c_str(), strByteArray.c_str());
		return szBuf;
	}
	auto it = mapASExpr.find(strTypeName);
	if(it != mapASExpr.end())
	{
		const string& strExpr = it->second;
		sprintf_s(szBuf, strExpr.c_str(), strName.c_str(), strByteArray.c_str());
		return szBuf;
	}

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return "var " + strName + ":" + GetASEnumType(pEnum->byByte) + " = " + strByteArray + GetEnumRead(*pEnum);

	SStruct* pStruct = GetStruct(strTypeName);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return "var " + strName + ":" + strTypeName + " = " + strTypeName + ".fromByteArray(" + strByteArray + ");";
		else
			return "var " + strName + ":" + strTypeName + " = " + strTypeName + ".superFromByteArray(" + strByteArray + ");";
	}

	pStruct = GetStruct(strTypeName, true);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return "var " + strName + ":Vector.<" + pStruct->strName + "> = " + pStruct->strName + ".vectorFromByteArray(" + strByteArray + ");";
		else
			return "var " + strName + ":Vector.<" + pStruct->strName + "> = " + pStruct->strName + ".superVectorFromByteArray(" + strByteArray + ");";
	}

	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef != _mapType2Ref.end())
	{
		SRefType& rRefType = itRef->second;
		if(rRefType.pDocument == NULL)
		{
			cerr << "Error package " << rRefType.strPackage << endl;
			return "ErrorPackage";
		}
		pEnum = rRefType.pDocument->GetEnum(rRefType.strTypeName);
		if(pEnum != NULL)
			return "var " + strName + ":" + GetASEnumType(pEnum->byByte) + " = " + strByteArray + GetEnumRead(*pEnum);
		pStruct = rRefType.pDocument->GetStruct(rRefType.strTypeName);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return "var " + strName + ":" + pStruct->strName + " = " + pStruct->strName + ".fromByteArray(" + strByteArray + ");";
			else
				return "var " + strName + ":" + pStruct->strName + " = " + pStruct->strName + ".superFromByteArray(" + strByteArray + ");";
		}
		pStruct = rRefType.pDocument->GetStruct(rRefType.strTypeName, true);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return "var " + strName + ":Vector.<" + pStruct->strName + "> = " + pStruct->strName + ".vectorFromByteArray(" + strByteArray + ");";
			else
				return "var " + strName + ":Vector.<" + pStruct->strName + "> = " + pStruct->strName + ".superVectorFromByteArray(" + strByteArray + ");";
		}
	}
	cerr << "Invalid Read Expression For " << strTypeName << endl;
	return "Invalid Read Expression";
}

void CDocument::PrintASRecvFunc(ostringstream& os, SFunc& rFunc)
{
	os << "\t\t/**\n";
	os << "\t\t * " << "接收：" + rFunc.strComment << "\n";
	os << "\t\t */\n";
	os << "\t\tpublic function onRecv_" << rFunc.strName << "(\n";
	for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
	{
		SParam& rParam = rFunc.vecParam[i];
		os << "\t\t\t" << rParam.strName << ":" << GetASTypeName(rParam);
		if(i < size - 1)
			os << ",";
		os << " //" << rParam.GetASComment(*this) << "\n";
	}
	os << "\t\t):void\n";
	os << "\t\t{\n";
	os << "\t\t\tthrow new Error(\"Function onRecv_" << rFunc.strName << " should be overrided!\");\n";
	os << "\t\t}\n\n";
}

void CDocument::PrintASRetParam(ostringstream& os, SFunc& rFunc)
{
	if(!rFunc.bReturn)
		return;
	os << "\t\t\tvar sessionID_:uint = _sessionMgr.getNewSession(this, " << -rFunc.iRetID << ");\n";
	os << "\t\t\tvar origParam_:SOrigParam_" << rFunc.strName << " = new SOrigParam_" << rFunc.strName << "();\n";
	if(rFunc.bKeepParam)
	{
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			if(rParam.bKeep)
				os << "\t\t\torigParam_." << rParam.strName << " = " << rParam.strName << ";\n";
		}
		for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecLocParam[i];
			os << "\t\t\torigParam_.loc_" << rParam.strName << " = loc_" << rParam.strName << ";\n";
		}
	}
	os << "\t\t\torigParam_.callback = callback;\n";
	os << "\t\t\t_sessionMgr.storeData(sessionID_, origParam_);\n";
}

bool CDocument::GetASEnumItemName(const string& strName, string& strASName, const SEnum* pCurEnum /*= NULL*/)
{
	SEnum* pEnum = NULL;
	SMember* pMember = GetEnumItem(strName, &pEnum);
	if(pMember != NULL && pEnum != NULL)
	{
		if(pEnum == pCurEnum)
			strASName = strName;
		else
			strASName = pEnum->strName + "." + strName;
		return true;
	}
	else
	{
		SRefType* pRefType = GetRefEnumItem(strName, &pEnum, &pMember);
		if(pRefType != NULL && pEnum != NULL)
		{
			strASName = pEnum->strName + "." + pRefType->strTypeName;
			return true;
		}
	}
	return false;
}

void CDocument::PrintASEnum(const SEnum& rEnum, const string& strPkg, const string& strPkgPath)
{
	string strASFile = strPkgPath + PATHSEP + rEnum.strName + ".as";
	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的Flash客户端协议代码(枚举类型)\n"
		"//  File Name:    " + rEnum.strName + ".as\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";

    set<int> setImported;
    string strHead = strTitle + "package " + strPkg + "\n {\n";
    string strImport = "";
	bool bPrinted = false;
	if(PrintImportRef(os, rEnum.vecMember))
		bPrinted = true;
	if(bPrinted)
		os << "\n";
	os << "\t/**\n";
	os << "\t * " << rEnum.strComment << "\n";
	os << "\t */\n";
	os << "\tpublic final class " << rEnum.strName << "\n";
	os << "\t{\n";
	char szBuf[100];
	string strRefValue;
	size_t stRefIndex = 0;
	for(size_t i = 0; i < rEnum.vecMember.size(); ++i)
	{
		const SMember& rMember = rEnum.vecMember[i];
		if(rMember.strTypeName.empty())
		{
			if(strRefValue.empty())
			{
				sprintf_s(szBuf, "%d", rMember.qwValue);
				(string&)rMember.strTypeName = szBuf;
			}
			else
			{
				sprintf_s(szBuf, " + %d", i - stRefIndex);
				(string&)rMember.strTypeName = strRefValue + szBuf;
			}
		}
		else
		{
			if(GetASEnumItemName(rMember.strTypeName, strRefValue, &rEnum))
			{
				(string&)rMember.strTypeName = strRefValue;
				stRefIndex = i;
			}
			else
			{
				strRefValue.clear();
			}
		}
		os << "\t\tpublic static const " << rMember.strName << ":" << GetASEnumType(rEnum.byByte) << " = " << rMember.strTypeName;
		string strComment = rMember.GetASComment(*this);
		if(!strComment.empty())
			os << "; //" << strComment << "\n";
		else
			os << ";\n";
	}
	if(rEnum.wMaxValIndex >= 0)
	{
		const SMember& rMember = rEnum.vecMember[rEnum.wMaxValIndex];
		os << "\t\tpublic static const end:" << GetASEnumType(rEnum.byByte) << " = " << rMember.strName << ";\n";
	}
	if(!rEnum.bClassType)
	{
		os << "\n\t\t/////////////////////以下为辅助函数/////////////////////\n";
		os << "\n\t\tpublic static function getDescription(value:" << GetASEnumType(rEnum.byByte) << "):String\n";
		os << "\t\t{\n";
		os << "\t\t\tswitch(value)\n";
		os << "\t\t\t{\n";
		list<const SMember*> lstMember;
		for(size_t k = 0; k < rEnum.vecMember.size(); ++k)
		{
			const SMember& rMember = rEnum.vecMember[k];
			const SMember* pMember = NULL;
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
		for(auto it = lstMember.begin(); it != lstMember.end(); ++it)
		{
			const SMember& rMember = **it;
			os << "\t\t\t\tcase " << rMember.strName << ":\n";
			os << "\t\t\t\t\treturn ProtocolMessageProt" << _ID << "." << rMember.strName << ";\n";
            if(!rEnum.bClassType)
            {
                if (setImported.find(_ID) == setImported.end())
                {
                    char szBuf1[100];
                    sprintf_s(szBuf1, ".Message.ProtocolMessageProt%u;\n", _ID);
                    strImport += ("\timport "+_strASPkgBase + szBuf1);
                    setImported.insert(_ID);
                }
            }
		}
		os << "\t\t\t\tdefault:\n";
		os << "\t\t\t\t\treturn \"Unknown Error\";\n";
		os << "\t\t\t}\n";
		os << "\t\t}\n";
	}
	os << "\t}\n";
	os << "}\n";

	ofstream ofile(strASFile.c_str());
	string strUtf = os.str();
#ifdef _WIN32
    strUtf = GB2312ToUTF8(strUtf);
    ofile << GB2312ToUTF8(strHead);
    ofile << GB2312ToUTF8(strImport);
#else
    ofile << strHead;
    ofile << strImport;
#endif
	ofile << strUtf;
}

const char* pszHead = "public static const";

static int GetProtID(const string& strLine)
{
	if(strLine.empty())
		return 0;
	size_t prev = strLine.find(pszHead);
	if(prev != string::npos)
	{
		prev += strlen(pszHead);
		size_t next = strLine.find("_", prev);
		if(next == string::npos)
		{
			cerr << "Invalid Line: " << strLine << endl;
			return 0;
		}
		string strNum = strLine.substr(prev, next - prev);
		return atoi(strNum.c_str());
	}
	return 0;
}

bool CDocument::PrintASEnumComment()
{
	if(_vecEnum.empty())
		return true;

    string strDir = _strASDestDir + algorithm::replace_all_copy(_strASPkgBase, ".", PATHSEP) + PATHSEP + "Message";
    CreateDirectory(strDir);

	char szBuf[0x100];
	list<string> lstEnum;
    string strFile = "ProtocolMessageProt";
    sprintf_s(szBuf, "%u", _ID);
    string strProtName = strFile + szBuf;
    strFile = strDir+PATHSEP+strProtName + ".as";

	for(size_t i = 0; i < _vecEnum.size(); ++i)
	{
		SEnum& rEnum = _vecEnum[i];
		if(rEnum.bClassType)
			continue;
		for(size_t k = 0; k < rEnum.vecMember.size(); ++k)
		{
			SMember& rMember = rEnum.vecMember[k];
			sprintf_s(szBuf, "\t\t%s %s:String = \"%s\";", pszHead, rMember.strName.c_str(), rMember.strComment.c_str());
			string strText = szBuf;
			if(k == 0)
				strText += "\t\t\t//Begin of Protocol:" + _strName + " Enum:" + rEnum.strName;
#ifdef _WIN32
			lstEnum.push_back(GB2312ToUTF8(strText));
#else
			lstEnum.push_back(szBuf);
#endif
		}
	}

	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的Flash客户端枚举类型注释汇总文件\n"
		"//  File Name:    " + strFile + "\n"
		"//  Purpose:      枚举类型注释，用于批量翻译\n"
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
#ifdef _WIN32
	os << GB2312ToUTF8(strTitle);
#else
	os << strTitle;
#endif
	os << "package " << _strASPkgBase << ".Message\n";
	os << "{\n";
	os << "\tpublic final class " + strProtName + "\n";
	os << "\t{\n";
	for(auto it = lstEnum.begin(); it != lstEnum.end(); ++it)
		os << *it << "\n";
	os << "\t}\n";
	os << "}\n";

	ofstream ofile(strFile.c_str());
	if(!ofile)
	{
		cerr << "Open file fails! file name: " << strFile << endl;
		return false;
	}
	string strUtf = os.str();
	ofile << strUtf;
	return true;
}

void CDocument::PrintASStruct(const SStruct& rStruct, const string& strPkg, const string& strPkgPath)
{
	string strASFile = strPkgPath + PATHSEP + rStruct.strName + ".as";
	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的Flash客户端协议代码(结构体类型)\n"
		"//  File Name:    " + rStruct.strName + ".as\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "package " << strPkg << "\n";
	os << "{\n";
	if(rStruct.bUseINT64)
		os << "\timport com.hurlant.math.BigInteger;\n";
	vector<SMember> vecMember(rStruct.vecMember);
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		const SMember& rMember = rStruct.vecMember[i];
		if(!rMember.strDefaultValue.empty() && GetRefEnumItem(rMember.strDefaultValue) != NULL)
		{
			SMember oMember(rMember);
			oMember.strTypeName = oMember.strDefaultValue;
			vecMember.push_back(oMember);
		}
	}
	PrintImportRef(os, vecMember);
	os << "\timport flash.utils.ByteArray;\n";
	os << "\timport net.util.*;\n\n";
	os << "\t/**\n";
	os << "\t * " << rStruct.strComment << "\n";
	os << "\t */\n";
	if(!rStruct.bHasSub)
	{
		if(rStruct.strSuperName.empty())
			os << "\tpublic final class " << rStruct.strName << "\n";
		else
			os << "\tpublic final class " << rStruct.strName << " extends " << rStruct.strSuperName << "\n";
	}
	else
	{
		if(rStruct.strSuperName.empty())
			os << "\tpublic class " << rStruct.strName << "\n";
		else
			os << "\tpublic class " << rStruct.strName << " extends " << rStruct.strSuperName << "\n";
	}
	os << "\t{\n";
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		const SMember& rMember = rStruct.vecMember[i];
		os << "\t\tpublic var " << rMember.strName << ":" << GetASTypeName(rMember);
		if(!rMember.strDefaultValue.empty())
		{
			string strASName;
			if(GetASEnumItemName(rMember.strDefaultValue, strASName))
				os << " = " << strASName;
			else
				os << " = " << rMember.strDefaultValue;
		}
		os << "; //" << rMember.GetASComment(*this) << "\n";
	}
	if(!rStruct.vecMember.empty())
		os << "\n";
	if(!rStruct.bHasSub && rStruct.strSuperName.empty())
	{
		os << "\t\t/**\n";
		os << "\t\t * 辅助创建函数\n";
		os << "\t\t */\n";
		os << "\t\tpublic static function create(";
		for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
		{
			const SMember& rMember = rStruct.vecMember[i];
			if(i != 0)
			{
				os << ", ";
				if(i % 5 == 0)
					os << "\n\t\t\t";
			}
			os << rMember.strName << ":" << GetASTypeName(rMember);
		}
		os << "):" << rStruct.strName << "\n";
		os << "\t\t{\n";
		os << "\t\t\tvar s_:" << rStruct.strName << " = new " << rStruct.strName << "();\n";
		for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
		{
			const SMember& rMember = rStruct.vecMember[i];
			os << "\t\t\ts_." << rMember.strName << " = " << rMember.strName << ";\n";
		}
		os << "\t\t\treturn s_;\n";
		os << "\t\t}\n\n";
	}
	else
	{
		os << "\t\t/**\n";
		os << "\t\t * 获取继承类的类型\n";
		os << "\t\t */\n";
		if(rStruct.bHasSub && rStruct.strSuperName.empty())
		{
			os << "\t\tpublic function getClassType():uint\n";
			os << "\t\t{\n";
			os << "\t\t\treturn EType_" << GetBaseClassName(rStruct.strName) << ".eType_" << rStruct.strName << ";\n";
			os << "\t\t}\n\n";
		}
		else
		{
			os << "\t\tpublic override function getClassType():uint\n";
			os << "\t\t{\n";
			os << "\t\t\treturn EType_" << GetBaseClassName(rStruct.strSuperName) << ".eType_" << rStruct.strName << ";\n";
			os << "\t\t}\n\n";
		}
	}
	if(rStruct.strSuperName.empty())
		PrintASTypeToXML(os, rStruct.strName, rStruct.vecMember, true);
	else
		PrintASTypeToXML(os, rStruct.strName, rStruct.vecMember, true, true);
	if(!rStruct.vecMember.empty())
	{
		os << "\n\t\t/**\n";
		os << "\t\t * 拷贝到另一个对象\n";
		os << "\t\t * @param obj_ 另一个对象\n";
		os << "\t\t */\n";
		SStruct* pStruct = GetStruct(rStruct.strSuperName);
		if(pStruct != NULL && !pStruct->vecMember.empty())
			os << "\t\tpublic override function copyTo(obj_:*):void\n";
		else
			os << "\t\tpublic function copyTo(obj_:*):void\n";
		os << "\t\t{\n";
		if(pStruct != NULL && !pStruct->vecMember.empty())
			os << "\t\t\tsuper.copyTo(obj_);\n";
		for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
		{
			const SMember& rMember = rStruct.vecMember[i];
			os << "\t\t\tobj_." << rMember.strName << " = " << rMember.strName << ";\n";
		}
		os << "\t\t}\n";
	}
	os << "\n\t\t/////////////////////以下为序列化函数/////////////////////\n\n";
	os << "\t\tpublic static function fromByteArray(bytes:ByteArray):" << rStruct.strName << "\n";
	os << "\t\t{\n";
	os << "\t\t\tvar s_:" << rStruct.strName << " = new " << rStruct.strName << "();\n";
	if(!rStruct.strSuperName.empty())
	{
		os << "\t\t\tvar base_:" << rStruct.strSuperName << " = " << rStruct.strSuperName << ".fromByteArray(bytes);\n";
		SStruct* pStruct = GetStruct(rStruct.strSuperName);
		if(pStruct == NULL)
		{
			cerr << "Can't find Struct: " << rStruct.strSuperName << endl;
			return;
		}
		if(!pStruct->vecMember.empty())
			os << "\t\t\tbase_.copyTo(s_);\n";
	}
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		const SMember& rMember = rStruct.vecMember[i];
		os << "\t\t\t" << GetASReadExpr(rMember, "bytes") << "\n";
		os << "\t\t\ts_." << rMember.strName << " = " << rMember.strName << ";\n";
	}
	os << "\t\t\treturn s_;\n";
	os << "\t\t}\n\n";

	if(rStruct.bHasSub)
	{
		os << "\t\tpublic static function superFromByteArray(bytes:ByteArray):" << rStruct.strName << "\n";
		os << "\t\t{\n";
		os << "\t\t\tvar eType:uint = bytes.readUnsignedByte();\n";
		os << "\t\t\tvar s:" << rStruct.strName << ";\n";
		os << "\t\t\tswitch(eType)\n";
		os << "\t\t\t{\n";
		vector<string> vecAllName;
		vecAllName.push_back(rStruct.strName);
		vecAllName.insert(vecAllName.end(), rStruct.vecSubName.begin(), rStruct.vecSubName.end());
		for(size_t i = 0; i < vecAllName.size(); ++i)
		{
			string& strName = vecAllName[i];
			os << "\t\t\t\tcase EType_" << GetBaseClassName(rStruct.strName) << ".eType_" << strName << ":\n";
			os << "\t\t\t\t\ts = " << strName << ".fromByteArray(bytes);\n";
			os << "\t\t\t\t\tbreak;\n";
		}
		os << "\t\t\t\tdefault:\n";
		os << "\t\t\t\t\tthrow new Error(\"Unknown value for EType_" << GetBaseClassName(rStruct.strName) << ":\" + eType);\n";
		os << "\t\t\t}\n";
		os << "\t\t\treturn s;\n";
		os << "\t\t}\n\n";
	}

	os << "\t\tpublic static function vectorFromByteArray(bytes:ByteArray):Vector.<" << rStruct.strName << ">\n";
	os << "\t\t{\n";
	os << "\t\t\tvar length:uint = BytesUtil.readVectorLength(bytes);\n";
	os << "\t\t\tvar vec:Vector.<" << rStruct.strName << "> = new Vector.<" << rStruct.strName << ">();\n";
	os << "\t\t\tfor(var i:uint = 0; i < length; ++i)\n";
	os << "\t\t\t{\n";
	os << "\t\t\t\tvar s:" << rStruct.strName << " = " << rStruct.strName << ".fromByteArray(bytes);\n";
	os << "\t\t\t\tvec.push(s);\n";
	os << "\t\t\t}\n";
	os << "\t\t\treturn vec;\n";
	os << "\t\t}\n\n";

	if(rStruct.bHasSub)
	{
		os << "\t\tpublic static function superVectorFromByteArray(bytes:ByteArray):Vector.<" << rStruct.strName << ">\n";
		os << "\t\t{\n";
		os << "\t\t\tvar length:uint = BytesUtil.readVectorLength(bytes);\n";
		os << "\t\t\tvar vec:Vector.<" << rStruct.strName << "> = new Vector.<" << rStruct.strName << ">();\n";
		os << "\t\t\tfor(var i:uint = 0; i < length; ++i)\n";
		os << "\t\t\t{\n";
		os << "\t\t\t\tvar s:" << rStruct.strName << " = " << rStruct.strName << ".superFromByteArray(bytes);\n";
		os << "\t\t\t\tvec.push(s);\n";
		os << "\t\t\t}\n";
		os << "\t\t\treturn vec;\n";
		os << "\t\t}\n\n";
	}

	if(rStruct.strSuperName.empty())
	{
		os << "\t\tpublic function toByteArray(bytes:ByteArray):void\n";
		os << "\t\t{\n";
	}
	else
	{
		os << "\t\tpublic override function toByteArray(bytes:ByteArray):void\n";
		os << "\t\t{\n";
		os << "\t\t\tsuper.toByteArray(bytes);\n";
	}
	for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
	{
		const SMember& rMember = rStruct.vecMember[i];
		os << "\t\t\t" << GetASWriteExpr(rMember, "bytes") << "\n";
	}
	os << "\t\t}\n\n";

	if(rStruct.bHasSub)
	{
		if(rStruct.strSuperName.empty())
			os << "\t\tpublic function superToByteArray(bytes:ByteArray):void\n";
		else
			os << "\t\tpublic override function superToByteArray(bytes:ByteArray):void\n";
		os << "\t\t{\n";
		os << "\t\t\tbytes.writeByte(getClassType());\n";
		os << "\t\t\ttoByteArray(bytes);\n";
		os << "\t\t}\n\n";
	}

	os << "\t\tpublic static function vectorToByteArray(vec:Vector.<" << rStruct.strName << ">, bytes:ByteArray):void\n";
	os << "\t\t{\n";
	os << "\t\t\tBytesUtil.writeVectorLength(bytes, vec.length);\n";
	os << "\t\t\tfor each(var s:" << rStruct.strName << " in vec)\n";
	os << "\t\t\t\ts.toByteArray(bytes);\n";
	os << "\t\t}\n";

	if(rStruct.bHasSub)
	{
		os << "\n\t\tpublic static function superVectorToByteArray(vec:Vector.<" << rStruct.strName << ">, bytes:ByteArray):void\n";
		os << "\t\t{\n";
		os << "\t\t\tBytesUtil.writeVectorLength(bytes, vec.length);\n";
		os << "\t\t\tfor each(var s:" << rStruct.strName << " in vec)\n";
		os << "\t\t\t\ts.superToByteArray(bytes);\n";
		os << "\t\t}\n";
	}

	os << "\t}\n";
	os << "}\n";

	ofstream ofile(strASFile.c_str());
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
}

void CDocument::PrintASRetStruct(const SFunc& rFunc, const string& strPkg, const string& strPkgPath)
{
	if(!rFunc.bReturn)
		return;
	//if(rFunc.bKeepParam)
	{
		string strASFile = strPkgPath + PATHSEP"SOrigParam_" + rFunc.strName + ".as";
		ostringstream os;
		string strTitle = 
			"/************************************************************************\n"
			"//  工具自动生成的Flash客户端协议代码(结构体类型)\n"
			"//  File Name:    SOrigParam_" + rFunc.strName + ".as\n"
			"//  Purpose:      " + rFunc.strComment + "\n"
#ifdef GEN_FILE_TIME
			"//  Create Time:  " + _strGenTime + "\n"
#endif
			"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
			"*************************************************************************/\n\n";
		os << strTitle;
		os << "package " << strPkg << "\n";
		os << "{\n";
		vector<SParam> vecParam;
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			const SParam& rParam = rFunc.vecParam[i];
			if(rParam.bKeep)
				vecParam.push_back(rParam);
		}
		vector<SParam> vecLocParam = rFunc.vecLocParam;
		for(size_t i = 0, size = vecLocParam.size(); i < size; ++i)
		{
			SParam& rParam = vecLocParam[i];
			rParam.strName = "loc_" + rParam.strName;
			vecParam.push_back(rParam);
		}
		bool bPrinted = PrintImportByteArray(os, vecParam);
		bPrinted = PrintImportUINT64(os, vecParam) || bPrinted;
		bPrinted = PrintImportRef(os, vecParam) || bPrinted;
		if(bPrinted)
			os << "\n";
		os << "\t/**\n";
		os << "\t * " << rFunc.strComment + "的原来的参数组成的结构体\n";
		os << "\t */\n";
		os << "\tpublic final class SOrigParam_" << rFunc.strName << "\n";
		os << "\t{\n";
		for(size_t i = 0, size = vecParam.size(); i < size; ++i)
		{
			const SParam& rParam = vecParam[i];
			os << "\t\tpublic var " << rParam.strName << ":" << GetASTypeName(rParam) << "; //" << rParam.GetASComment(*this) << "\n";
		}
        os << "\t\tpublic var callback:Function;\n";
		os << "\n";
		PrintASTypeToXML(os, "SOrigParam_" + rFunc.strName, vecParam, true);
		os << "\t}\n";
		os << "}\n";

		ofstream ofile(strASFile.c_str());
		string strUtf = os.str();
#ifdef _WIN32
		strUtf = GB2312ToUTF8(strUtf);
#endif
		ofile << strUtf;
	}
	if(!rFunc.vecRetParam.empty())
	{
		string strASFile = strPkgPath + PATHSEP"SRetParam_" + rFunc.strName + ".as";
		ostringstream os;
		string strTitle = 
			"/************************************************************************\n"
			"//  工具自动生成的Flash客户端协议代码(结构体类型)\n"
			"//  File Name:    SRetParam_" + rFunc.strName + ".as\n"
			"//  Purpose:      " + rFunc.strComment + "\n"
#ifdef GEN_FILE_TIME
			"//  Create Time:  " + _strGenTime + "\n"
#endif
			"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
			"*************************************************************************/\n\n";
		os << strTitle;
		os << "package " << strPkg << "\n";
		os << "{\n";
		bool bPrinted =	PrintImportByteArray(os, rFunc.vecRetParam);
		bPrinted = PrintImportUINT64(os, rFunc.vecRetParam) || bPrinted;
		bPrinted = PrintImportRef(os, rFunc.vecRetParam) || bPrinted;
		if(bPrinted)
			os << "\n";
		os << "\t/**\n";
		os << "\t * " << rFunc.strComment + "的返回的参数组成的结构体\n";
		os << "\t */\n";
		os << "\tpublic final class SRetParam_" << rFunc.strName << "\n";
		os << "\t{\n";
		for(size_t i = 0, size = rFunc.vecRetParam.size(); i < size; ++i)
		{
			const SParam& rParam = rFunc.vecRetParam[i];
			os << "\t\tpublic var " << rParam.strName << ":" << GetASTypeName(rParam) << "; //" << rParam.GetASComment(*this) << "\n";
		}
		os << "\n";
		PrintASTypeToXML(os, "SRetParam_" + rFunc.strName, rFunc.vecRetParam, true);
		os << "\t}\n";
		os << "}\n";

		ofstream ofile(strASFile.c_str());
		string strUtf = os.str();
#ifdef _WIN32
		strUtf = GB2312ToUTF8(strUtf);
#endif
		ofile << strUtf;
	}
}

void CDocument::PrintASRecvEvent(SFunc& rFunc, const string& strPkg, const string& strPkgPath)
{
	string strASFile = strPkgPath + PATHSEP"REvt_" + rFunc.strName + ".as";
	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的Flash客户端协议代码(接收函数参数事件类型)\n"
		"//  File Name:    REvt_" + rFunc.strName + ".as\n"
		"//  Purpose:      协议:" + _strComment + ", 函数:" + rFunc.strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "package " << strPkg << "\n";
	os << "{\n";
	os << "\timport flash.events.Event;\n";
	PrintImportUINT64(os, rFunc.vecParam);
	PrintImportByteArray(os, rFunc.vecParam);
	PrintImportRef(os, rFunc.vecParam);
	os << "\n\t/**\n";
	os << "\t * " << "函数" + rFunc.strName + "[" + rFunc.strComment + "]的接收事件\n";
	os << "\t */\n";
	os << "\tpublic final class REvt_" << rFunc.strName << " extends Event\n";
	os << "\t{\n";
	os << "\t\tpublic static const DATA_RECEIVE:String = \"" << _strName << "_" << rFunc.strName << "\";\n";
	os << "\t\tpublic static const DATA_ERROR:String = \"" << _strName << "_" << rFunc.strName << "_Error\";\n\n";
	for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
	{
		const SParam& rParam = rFunc.vecParam[i];
		os << "\t\tpublic var " << rParam.strName << ":" << GetASTypeName(rParam) << "; //" << rParam.GetASComment(*this) << "\n";
	}
	os << "\n\t\tpublic function REvt_" << rFunc.strName << "(type:String, bubbles:Boolean = false, cancelable:Boolean = false)\n";
	os << "\t\t{\n";
	os << "\t\t\tsuper(type, bubbles, cancelable);\n";	
	os << "\t\t}\n\n";
	PrintASTypeToXML(os, "REvt_" + rFunc.strName, rFunc.vecParam);  
    if(!rFunc.strAckMsg.empty())
    {
        for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
        {
            const SParam& rParam = rFunc.vecParam[i];
            if((rParam.strName == rFunc.strAckMsg) &&(IsEnumType(rParam.strTypeName)||GetRefEnumType(rParam.strTypeName)))
            {
                os << "\t\tpublic  function getMsg():String \n";
                os << "\t\t{\n";
                os << "\t\t\t return getDescription(" << rParam.strName  <<");\n";
                os << "\t\t}\n";

                os << "\t\tpublic  function getDescription(value:uint):String \n";
                os << "\t\t{\n";
                os << "\t\t\t return " <<rParam.strTypeName<<".getDescription( value );\n";
                os << "\t\t}\n";     
                break;
            }
        }

    }
   
	os << "\t}\n";  
    os << "}\n"; 
    

    
 

	ofstream ofile(strASFile.c_str());
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
}

void CDocument::PrintASReturnEvent(SFunc& rFunc, const string& strPkg, const string& strPkgPath)
{
	string strASFile = strPkgPath + PATHSEP"TEvt_" + rFunc.strName + ".as";
	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的Flash客户端协议代码(返回函数参数事件类型)\n"
		"//  File Name:    TEvt_" + rFunc.strName + ".as\n"
		"//  Purpose:      协议:" + _strComment + ", 函数:" + rFunc.strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "package " << strPkg << "\n";
	os << "{\n";
	os << "\timport flash.events.Event;\n\n";
	os << "\t/**\n";
	os << "\t * " << "函数" + rFunc.strName + "[" + rFunc.strComment + "]的返回事件\n";
	os << "\t */\n";
	os << "\tpublic final class TEvt_" << rFunc.strName << " extends Event\n";
	os << "\t{\n";
	os << "\t\tpublic static const DATA_RETURN:String = \"" << _strName << "_" << rFunc.strName << "\";\n";
	os << "\t\tpublic static const DATA_ERROR:String = \"" << _strName << "_" << rFunc.strName << "_Error\";\n\n";
	os << "\t\tpublic var ret:int; //0为成功，1为失败，2为超时\n";
	if(rFunc.bKeepParam)
		os << "\t\tpublic var origParam:SOrigParam_" + rFunc.strName + "; //原来的参数\n";
	if(!rFunc.vecRetParam.empty())
		os << "\t\tpublic var retParam:SRetParam_" + rFunc.strName + "; //返回的参数\n";
	os << "\n\t\tpublic function TEvt_" << rFunc.strName << "(type:String, bubbles:Boolean = false, cancelable:Boolean = false)\n";
	os << "\t\t{\n";
	os << "\t\t\tsuper(type, bubbles, cancelable);\n";	
	os << "\t\t}\n\n";
	os << "\t\t/**\n";
	os << "\t\t * " << "转换为XML\n";
	os << "\t\t */\n";
	os << "\t\tpublic function toXML():String\n";
	os << "\t\t{\n";
	os << "\t\t\tvar topXml:XML = <TEvt_" << rFunc.strName << " ret={ret}/>;\n";
	if(rFunc.bKeepParam)
	{
		os << "\t\t\tif(origParam != null)\n";
		os << "\t\t\t\ttopXml.appendChild(origParam.toXML(\"origParam\"));\n";
	}
	if(!rFunc.vecRetParam.empty())
	{
		os << "\t\t\tif(retParam != null)\n";
		os << "\t\t\t\ttopXml.appendChild(retParam.toXML(\"retParam\"));\n";
	}
	os << "\t\t\treturn topXml.toXMLString();\n";
	os << "\t\t}\n";
	os << "\t}\n";
	os << "}\n";

	ofstream ofile(strASFile.c_str());
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
}

bool CDocument::GenActionScript(const char* szDestDir, const char* szPkg)
{
	if(!HasClientType(eClientAs))
		return true;
	if(szDestDir == NULL || szPkg == NULL)
		return false;
	_strASPkgBase = szPkg;
	string strPkg = szPkg;
	strPkg += "." + HeadToLower(_strName);
	string strPkgPath = szDestDir;
	strPkgPath += PATHSEP "ActionScript" PATHSEP;
	_strASDestDir = strPkgPath;
	strPkgPath += algorithm::replace_all_copy(strPkg, ".", PATHSEP);
	CreateDirectory(strPkgPath);

	//enum
	for(size_t i = 0; i < _vecEnum.size(); ++i)
	{
		SEnum& rEnum = _vecEnum[i];
		PrintASEnum(rEnum, strPkg, strPkgPath);
	}

	if(!PrintASEnumComment())
	{
		cerr << "Print ActionScript Enum Comment fails! Protocol: " << _strName << endl;
		return false;
	}

	//struct
	for(size_t i = 0; i < _vecStruct.size(); ++i)
	{
		SStruct& rStruct = *_vecStruct[i];
		if(rStruct.eGlobalType == eGlobalServer)
			continue;
		PrintASStruct(rStruct, strPkg, strPkgPath);
	}

	if(_vecFuncC2S.empty() && _vecFuncS2C.empty())
		return true;

	string strASName = _strName;
	if(_bClientRpc)
		strASName += "Base";
	string strASFile = strPkgPath + PATHSEP + strASName + ".as";
	ostringstream os;
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的Flash客户端协议代码\n"
		"//  File Name:    " + strASName + ".as\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
	os << "package " << strPkg << "\n";
	os << "{\n";
	os << "\timport flash.utils.ByteArray;\n";
	if(_bUseINT64)
		os << "\timport com.hurlant.math.BigInteger;\n";
	PrintAllImportRef(os);
	os << "\timport net.core.*;\n";
	os << "\timport net.util.*;\n\n";
	os << "\t/**\n";
	os << "\t * " << "协议：" + _strComment << "\n";
	os << "\t */\n";
	os << "\tpublic class " << strASName << " extends ProtocolBase\n";
	os << "\t{\n";
	if(_bClientRpc)
	{
		if(!_vecFuncS2C.empty())
		{
			os << "\t\t/////////////////////以下的接收函数需要重载/////////////////////\n";
			for(size_t i = 0; i < _vecFuncS2C.size(); ++i)
			{
				SFunc& rFunc = _vecFuncS2C[i];
				PrintASRecvFunc(os, rFunc);
			}
		}
		if(_bHasC2SRetFunc)
		{
			os << "\t\t/////////////////////以下的返回函数需要重载/////////////////////\n";
			for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
			{
				SFunc& rFunc = _vecFuncC2S[i];
				if(!rFunc.bReturn)
					continue;
				PrintASRetStruct(rFunc, strPkg, strPkgPath);
				os << "\t\t" << "//返回：" + rFunc.strComment << "\n";
				os << "\t\tpublic function onReturn_" << rFunc.strName << "(\n";
				os << "\t\t\tret:int";
				if(rFunc.bKeepParam || !rFunc.vecRetParam.empty())
					os << ",";
				os << " //0为成功，1为失败，2为超时\n";
				if(rFunc.bKeepParam)
				{
					os << "\t\t\torigParam:SOrigParam_" << rFunc.strName;
					if(!rFunc.vecRetParam.empty())
						os << ",";
					os << " //原来的参数\n";
				}
				if(!rFunc.vecRetParam.empty())
					os << "\t\t\tretParam:SRetParam_" << rFunc.strName << " //返回的参数\n";
				os << "\t\t):void\n";
				os << "\t\t{\n";
				os << "\t\t\tthrow new Error(\"Function onReturn_" << rFunc.strName << " should be overrided!\");\n";
				os << "\t\t}\n\n";
			}
		}
	}
	else if(_bHasC2SRetFunc)
	{
		for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
		{
			SFunc& rFunc = _vecFuncC2S[i];
			if(rFunc.bReturn)
				PrintASRetStruct(rFunc, strPkg, strPkgPath);
		}
	}
	//send
	if(!_vecFuncC2S.empty())
		os << "\t\t/////////////////////以下为发送函数/////////////////////\n";
	for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
	{
		SFunc& rFunc = _vecFuncC2S[i];
		os << "\t\t/**\n";
		os << "\t\t * " << "发送：" + rFunc.strComment << "\n";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			os << "\t\t * @param " << rParam.strName << " " << rParam.GetASComment(*this) << "\n";
		}
		if(rFunc.bReturn)
		{
			for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
			{
				SParam& rParam = rFunc.vecLocParam[i];
				os << "\t\t * @param loc_" << rParam.strName << " " << rParam.GetASComment(*this) << "\n";
			}
		}
		os << "\t\t */\n";
		os << "\t\tpublic function send_" << rFunc.strName << "(";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			if(i > 0 && i % 5 == 0)
				os << "\n\t\t\t";
			os << rParam.strName << ":" << GetASTypeName(rParam);
			if (i < size - 1 || rFunc.bReturn)
				os << ", ";
		}
		if(rFunc.bReturn)
		{
			for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
			{
				SParam& rParam = rFunc.vecLocParam[i];
				if(i > 0 && i % 5 == 0)
					os << "\n\t\t\t";
				os << "loc_" << rParam.strName << ":" << GetASTypeName(rParam);
				os << ", ";
			}
			os << "callback:Function = null";
		}

		os << "):Boolean\n";
		os << "\t\t{\n";
		PrintASRetParam(os, rFunc);
		os << "\t\t\tvar bytes_:ByteArray = BytesUtil.createByteArray();\n";
		os << "\t\t\tbytes_.writeByte(_protID);\n";
		os << "\t\t\tconst funcID_:int = " << rFunc.ID << ";\n";
		os << "\t\t\tbytes_.writeByte(funcID_);\n";
		if(rFunc.bReturn)
			os << "\t\t\tbytes_.writeUnsignedInt(sessionID_);\n";
		for(size_t k = 0, size = rFunc.vecParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecParam[k];
			os << "\t\t\t" << GetASWriteExpr(rParam, "bytes_") << "\n";
		}
		os << "\t\t\treturn serverHandler.sendPacket(bytes_);\n";
		os << "\t\t}\n\n";
	}

	//Receive
	if(!_vecFuncS2C.empty())
		os << "\t\t/////////////////////以下为接收处理函数/////////////////////\n";
	for(size_t i = 0; i < _vecFuncS2C.size(); ++i)
	{
		SFunc& rFunc = _vecFuncS2C[i];
		os << "\t\t" << "//接收处理：" + rFunc.strComment << "\n";
		os << "\t\tprivate function _doRecv_" << rFunc.strName << "(bytes:ByteArray):void\n";
		os << "\t\t{\n";
		for(size_t k = 0, size = rFunc.vecParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecParam[k];
			os << "\t\t\t" << GetASReadExpr(rParam, "bytes") << " //" << rParam.GetASComment(*this) << "\n";
		}
		if(_bClientRpc)
		{
			os << "\t\t\tonRecv_" << rFunc.strName << "(";
			for(size_t k = 0, size = rFunc.vecParam.size(); k < size; ++k)
			{
				SParam& rParam = rFunc.vecParam[k];
				os << rParam.strName;
				if(k < size - 1)
					os << ", ";
			}
			os << ");\n";
		}
		else
		{
			os << "\t\t\tvar event_:REvt_" << rFunc.strName << " = new REvt_" << rFunc.strName << "(REvt_" << rFunc.strName << ".DATA_RECEIVE);\n";
			for(size_t k = 0, size = rFunc.vecParam.size(); k < size; ++k)
			{
				SParam& rParam = rFunc.vecParam[k];
				os << "\t\t\tevent_." << rParam.strName << " = " << rParam.strName << ";\n";
			}
			os << "\t\t\tdispatchEvent(event_);\n";
			PrintASRecvEvent(rFunc, strPkg, strPkgPath);
		}
		os << "\t\t}\n\n";
	}

	//Return
	if(!_vecFuncS2C.empty() && _bHasC2SRetFunc)
		os << "\t\t/////////////////////以下为返回处理函数/////////////////////\n";
	for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
	{
		SFunc& rFunc = _vecFuncC2S[i];
		if(!rFunc.bReturn)
			continue;
		os << "\t\t" << "//返回处理：" + rFunc.strComment << "\n";
		os << "\t\tprivate function _doReturn_" << rFunc.strName << "(bytes:ByteArray):void\n";
		os << "\t\t{\n";
		os << "\t\t\tvar retParam_:SRetParam_" << rFunc.strName << " = new SRetParam_" << rFunc.strName << "();\n";
		os << "\t\t\tvar sessionID_:uint = bytes.readUnsignedInt();\n";
		os << "\t\t\tvar ret_:Boolean = bytes.readBoolean();\n";
		for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			os << "\t\t\t" << GetASReadExpr(rParam, "bytes") << " //" << rParam.GetASComment(*this) << "\n";
		}
		for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			os << "\t\t\tretParam_." << rParam.strName << " = " << rParam.strName << ";\n";
		}
		if(rFunc.bReturn || rFunc.bKeepParam)
			os << "\t\t\tvar origParam_:SOrigParam_" << rFunc.strName << " = _sessionMgr.getData(sessionID_) as SOrigParam_" << rFunc.strName << ";\n";
		os << "\t\t\tvar ret:int = 0;\n";
		if(rFunc.bKeepParam)
		{
			os << "\t\t\tif(origParam_ == null)\n";
			os << "\t\t\t\tret = 3; //确认已超时但又收到返回\n";
			os << "\t\t\telse if(!ret_)\n";
			os << "\t\t\t\tret = 1;\n";
		}
		else
		{
			os << "\t\t\tif(!ret_)\n";
			os << "\t\t\t\tret = 1;\n";
		}
		if(_bClientRpc)
		{
			os << "\t\t\tonReturn_" << rFunc.strName << "(ret";
			if(rFunc.bKeepParam)
				os << ", origParam_";
			if(!rFunc.vecRetParam.empty())
				os << ", retParam_";
			os << ");\n";
		}
		else
		{
			os << "\t\t\tvar event_:TEvt_" << rFunc.strName << " = new TEvt_" << rFunc.strName << "(TEvt_" << rFunc.strName << ".DATA_RETURN);\n";
			os << "\t\t\tevent_.ret = ret;\n";
			if(rFunc.bKeepParam)
				os << "\t\t\tevent_.origParam = origParam_;\n";
			if(!rFunc.vecRetParam.empty())
				os << "\t\t\tevent_.retParam = retParam_;\n";
			if(rFunc.bKeepParam || rFunc.bReturn)
			{
				os << "\t\t\tif (origParam_.callback != null)\n";
				os << "\t\t\t\torigParam_.callback(event_);\n";
				os << "\t\t\telse\n";
				os << "\t\t\t\tdispatchEvent(event_);\n";
			} else
				os << "\t\t\tdispatchEvent(event_);\n";
			
			PrintASReturnEvent(rFunc, strPkg, strPkgPath);
		}
		os << "\t\t\t_sessionMgr.delSession(sessionID_);\n";
		os << "\t\t}\n\n";

		os << "\t\t" << "//超时处理：" + rFunc.strComment << "\n";
		os << "\t\tprivate function _onTimeOut_" << rFunc.strName << "(sessionID:uint):void\n";
		os << "\t\t{\n";
		if(!rFunc.vecRetParam.empty())
			os << "\t\t\tvar retParam:SRetParam_" << rFunc.strName << " = new SRetParam_" << rFunc.strName << "();\n";
		if(rFunc.bKeepParam)
			os << "\t\t\tvar origParam:SOrigParam_" << rFunc.strName << " = _sessionMgr.getData(sessionID) as SOrigParam_" << rFunc.strName << ";\n";
		if(_bClientRpc)
		{
			os << "\t\t\tonReturn_" << rFunc.strName << "(2";
			if(rFunc.bKeepParam)
				os << ", origParam";
			if(!rFunc.vecRetParam.empty())
				os << ", retParam";
			os << ");\n";
		}
		else
		{
			os << "\t\t\tvar event_:TEvt_" << rFunc.strName << " = new TEvt_" << rFunc.strName << "(TEvt_" << rFunc.strName << ".DATA_RETURN);\n";
			os << "\t\t\tevent_.ret = 2;\n";
			if(rFunc.bKeepParam)
				os << "\t\t\tevent_.origParam = origParam;\n";
			if(!rFunc.vecRetParam.empty())
				os << "\t\t\tevent_.retParam = retParam;\n";
			os << "\t\t\tdispatchEvent(event_);\n";
		}
		os << "\t\t}\n\n";
	}
	os << "\t\t/////////////////////以下为单例访问接口/////////////////////\n";
	os << "\t\tprivate static var _instance:" << strASName << ";\n\n";
	os << "\t\tpublic static function get instance():" << strASName << "\n";
	os << "\t\t{\n";
	os << "\t\t\tif(_instance == null)\n";
	os << "\t\t\t\t_instance = new " << strASName << "();\n";
	os << "\t\t\treturn _instance;\n";
	os << "\t\t}\n\n";
	os << "\t\t/////////////////////以下为协议接口/////////////////////\n";
	os << "\t\tprivate var _recvFuncList:Array;\n";
	if(_bHasC2SRetFunc)
	{
		os << "\t\tprivate var _retFuncList:Array;\n";
		os << "\t\tprivate var _timeFuncList:Array;\n";
	}
	os << "\n";
	os << "\t\tpublic function " << strASName << "()\n";
	os << "\t\t{\n";
	os << "\t\t\t_protID = " << _ID << ";\n";
	os << "\t\t\t_recvFuncList = [\n";
	for(size_t i = 0; i < _vecFuncS2C.size(); ++i)
	{
		SFunc& rFunc = _vecFuncS2C[i];
		os << "\t\t\t\t_doRecv_" << rFunc.strName << (i < _vecFuncS2C.size() - 1 ? "," : "") << " //FuncID: " << (i + 1) << "\n";
	}
	os << "\t\t\t];\n";
	if(_bHasC2SRetFunc)
	{
		os << "\n\t\t\t_retFuncList = [\n";
		for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
		{
			SFunc& rFunc = _vecFuncC2S[i];
			if(rFunc.bReturn)
				os << "\t\t\t\t_doReturn_" << rFunc.strName << (i < _vecFuncC2S.size() - 1 ? "," : "") << " //FuncID: " << -rFunc.iRetID << "\n";
		}
		os << "\t\t\t];\n\n";
		os << "\t\t\t_timeFuncList = [\n";
		for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
		{
			SFunc& rFunc = _vecFuncC2S[i];
			if(rFunc.bReturn)
				os << "\t\t\t\t_onTimeOut_" << rFunc.strName << (i < _vecFuncC2S.size() - 1 ? "," : "") << " //FuncID: " << -rFunc.iRetID << "\n";
		}
		os << "\t\t\t];\n";
	}
	os << "\t\t}\n\n";
	os << "\t\tpublic override function handleMessage(bytes:ByteArray):Boolean\n";
	os << "\t\t{\n";
	if(!_vecFuncS2C.empty() || _bHasC2SRetFunc)
	{
		os << "\t\t\tvar funcID:int = bytes.readByte();\n";
		os << "\t\t\tif(funcID == 0";
		if(!_vecFuncS2C.empty())
			os << " || funcID > _recvFuncList.length";
		if(_bHasC2SRetFunc)
			os << "\n\t\t\t\t || funcID < -_retFuncList.length";
		os << ")\n";
		os << "\t\t\t\treturn false;\n";
		os << "\t\t\tvar func:Function;\n";
		os << "\t\t\tif(funcID > 0)\n";
		os << "\t\t\t\tfunc = _recvFuncList[funcID - 1];\n";
		if(_bHasC2SRetFunc)
		{
			os << "\t\t\telse\n";
			os << "\t\t\t\tfunc = _retFuncList[-funcID - 1];\n";
		}
		os << "\t\t\tif(func != null)\n";
		os << "\t\t\t{\n";
		os << "\t\t\t\tfunc(bytes);\n";
		os << "\t\t\t\treturn true;\n";
		os << "\t\t\t}\n";
		os << "\t\t\treturn false;\n";
	}
	else
	{
		os << "\t\t\treturn true;\n";
	}
	os << "\t\t}\n";
	if(_bHasC2SRetFunc)
	{
		os << "\n\t\tpublic override function onTimeOut(funcID:uint, sessionID:uint):void\n";
		os << "\t\t{\n";
		os << "\t\t\tif(funcID == 0 || funcID > _timeFuncList.length)\n";
		os << "\t\t\t\treturn;\n";
		os << "\t\t\t_timeFuncList[funcID - 1](sessionID);\n";
		os << "\t\t}\n";
	}

	os << "\t}\n";
	os << "}";

	ofstream ofile(strASFile.c_str());
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
	return true;
}
