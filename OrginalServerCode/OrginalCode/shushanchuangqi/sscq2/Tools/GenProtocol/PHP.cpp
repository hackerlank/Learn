/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	PHP.cpp
//	Created:	2013/08/23	10:00
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
#include "Directory.h"
#include "Encode.h"

void CDocument::PrintPHPDefaultValue(ostringstream& os, const SElement& rElement)
{
	if(IsPrimType(rElement.strTypeName))
	{
		if(rElement.strTypeName.find("INT64") != string::npos)
			os << "new Math_BigInteger;\n";
		else if(rElement.strTypeName == "bool")
			os << "false;\n";
		else
			os << "0;\n";
	}
	else if(IsStringType(rElement.strTypeName))
	{
		os << "'';\n";
	}
	else if(IsVectorType(rElement.strTypeName))
	{
		os << "array();\n";
	}
	else
	{
		SStruct* pStruct = NULL;
		GetRefStruct(rElement.strTypeName, false, &pStruct);
		if(pStruct != NULL)
			os << "new " << pStruct->strName << ";\n";
		else
			os << "new " << rElement.strTypeName << ";\n";
	}
}

bool CDocument::GenPHP(const char* szDestDir)
{
	if(!HasClientType(eClientPhp))
		return true;
	if(szDestDir == NULL)
		return false;
	string strDestPath = string(szDestDir) + PATHSEP"PHP";
	CreateDirectory(strDestPath);
	string strPHPName = _strName + "Base";
	string strPHPFile = strDestPath + PATHSEP + strPHPName + ".php";
	ostringstream os;
	os << "<?php\n";
	string strTitle = 
		"/************************************************************************\n"
		"//  工具自动生成的PHP客户端协议代码\n"
		"//  File Name:    " + _strFileName + ".php\n"
		"//  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"//  Create Time:  " + _strGenTime + "\n"
#endif
		"//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"*************************************************************************/\n\n";
	os << strTitle;
#ifdef PHP_USE_NAME_SPACE
	os << "namespace " << _strNameSpace << ";\n\n";
#endif
	os << "require_once('ByteUtil.php');\n";
	os << "require_once('ProtocolBase.php');\n";
	for(auto it = _mapProt2Doc.begin(); it != _mapProt2Doc.end(); ++it)
	{
		string strFile = it->first + "Base.php";
		os << "require_once('" << strFile << "');\n";
	}

#ifdef PHP_USE_NAME_SPACE
	os << "\nuse ProtocolBase;\n";
	os << "use ByteUtil;\n";
	os << "use Math_BigInteger;\n\n";
#else
	os << "\n";
#endif

	if(!_vecEnum.empty() || !_vecStruct.empty())
		os << "/////////////////////以下为类型定义/////////////////////\n";
	//enum
	for(SEnum& rEnum : _vecEnum)
	{
		os << "//" << rEnum.strComment << "\n";
		os << "class " << rEnum.strName << "\n";
		os << "{\n";
		for(size_t i = 0; i < rEnum.vecMember.size(); ++i)
		{
			const SMember& rMember = rEnum.vecMember[i];
			os << "\tconst " << rMember.strName << " = ";
			if(rMember.strTypeName.empty() || atoi(rMember.strTypeName.c_str()) == 0)
				os << rMember.qwValue;
			else
				os << rMember.strTypeName;
			const string& strComment = rMember.strComment;
			if(!strComment.empty())
				os << "; //" << strComment << "\n";
			else
				os << ";\n";
		}
		os << "}\n\n";
	}

	//struct
	for(SStruct* pStruct : _vecStruct)
	{
		SStruct& rStruct = *pStruct;
		if(rStruct.eGlobalType == eGlobalServer)
			continue;
		os << "//" << rStruct.strComment << "\n";
		if(!rStruct.bHasSub)
		{
			if(rStruct.strSuperName.empty())
				os << "final class " << rStruct.strName << "\n";
			else
				os << "final class " << rStruct.strName << " extends " << rStruct.strSuperName << "\n";
		}
		else
		{
			if(rStruct.strSuperName.empty())
				os << "class " << rStruct.strName << "\n";
			else
				os << "class " << rStruct.strName << " extends " << rStruct.strSuperName << "\n";
		}
		os << "{\n";
		for(SMember& rMember : rStruct.vecMember)
			os << "\tpublic $" << rMember.strName << "; //" << rMember.GetPHPComment(*this) << "\n";
		if(!rStruct.vecMember.empty())
			os << "\n";
		os << "\t//构造函数\n";
		os << "\tfunction __construct()\n";
		os << "\t{\n";
		if(!rStruct.strSuperName.empty())
			os << "\t\tparent::__construct();\n";
		for(SMember& rMember : rStruct.vecMember)
		{
			os << "\t\t$this->" << rMember.strName << " = ";
			PrintPHPDefaultValue(os, rMember);
		}
		os << "\t}\n\n";
		if(rStruct.bHasSub || !rStruct.strSuperName.empty())
		{
			os << "\t//获取继承类的类型\n";
			os << "\tfunction getClassType()\n";
			os << "\t{\n";
			os << "\t\treturn EType_" << GetBaseClassName(rStruct.strName) << "::eType_" << rStruct.strName << ";\n";
			os << "\t}\n\n";
		}
		if(!rStruct.vecMember.empty())
		{
			os << "\t//拷贝到另一个对象\n";
			os << "\tfunction copyTo($obj)\n";
			os << "\t{\n";
			SStruct* pStruct = GetStruct(rStruct.strSuperName);
			if(pStruct != NULL && !pStruct->vecMember.empty())
				os << "\t\tparent::copyTo($obj);\n";
			for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
			{
				const SMember& rMember = rStruct.vecMember[i];
				os << "\t\t$obj->" << rMember.strName << " = $this->" << rMember.strName << ";\n";
			}
			os << "\t}\n\n";
		}
		os << "\t/////////////////////以下为序列化函数/////////////////////\n\n";
		os << "\tstatic function fromStream(&$data)\n";
		os << "\t{\n";
		os << "\t\t$s = new " << rStruct.strName << ";\n";
		if(!rStruct.strSuperName.empty())
		{
			os << "\t\t$base = " << rStruct.strSuperName << "::fromStream($data);\n";
			SStruct* pStruct = GetStruct(rStruct.strSuperName);
			if(pStruct == NULL)
			{
				cerr << "Can't find Struct: " << rStruct.strSuperName << endl;
				return false;
			}
			if(!pStruct->vecMember.empty())
				os << "\t\t$base->copyTo($s);\n";
		}
		for(SMember& rMember : rStruct.vecMember)
			os << "\t\t" << GetPHPReadExpr(rMember, "$data") << "\n";
		os << "\t\treturn $s;\n";
		os << "\t}\n\n";

		if(rStruct.bHasSub)
		{
			os << "\tstatic function superFromStream(&$data)\n";
			os << "\t{\n";
			os << "\t\t$eType = ByteUtil::readUINT8($data);\n";
			os << "\t\tswitch($eType)\n";
			os << "\t\t{\n";
			vector<string> vecAllName;
			vecAllName.push_back(rStruct.strName);
			vecAllName.insert(vecAllName.end(), rStruct.vecSubName.begin(), rStruct.vecSubName.end());
			for(string& strName : vecAllName)
			{
				os << "\t\t\tcase EType_" << GetBaseClassName(rStruct.strName) << "::eType_" << strName << ":\n";
				os << "\t\t\t\t$s = " << strName << "::fromStream($data);\n";
				os << "\t\t\t\tbreak;\n";
			}
			os << "\t\t\tdefault:\n";
			os << "\t\t\t\tthrow new Exception('Unknown value for EType_" << GetBaseClassName(rStruct.strName) << ":'.eType);\n";
			os << "\t\t}\n";
			os << "\t\treturn $s;\n";
			os << "\t}\n\n";
		}

		os << "\tstatic function vectorFromStream(&$data)\n";
		os << "\t{\n";
		os << "\t\t$length = ByteUtil::readVectorLength($data);\n";
		os << "\t\t$arr = array();\n";
		os << "\t\tfor($i = 0; $i < $length; ++$i)\n";
		os << "\t\t{\n";
		os << "\t\t\t$s = " << rStruct.strName << "::fromStream($data);\n";
		os << "\t\t\t$arr[$i] = $s;\n";
		os << "\t\t}\n";
		os << "\t\treturn $arr;\n";
		os << "\t}\n\n";

		if(rStruct.bHasSub)
		{
			os << "\tstatic function superVectorFromStream(&$data)\n";
			os << "\t{\n";
			os << "\t\t$length = ByteUtil::readVectorLength($data);\n";
			os << "\t\t$arr = array();\n";
			os << "\t\tfor($i = 0; $i < $length; ++$i)\n";
			os << "\t\t{\n";
			os << "\t\t\t$s = " << rStruct.strName << "::superFromStream($data);\n";
			os << "\t\t\t$arr[$i] = $s;\n";
			os << "\t\t}\n";
			os << "\t\treturn $arr;\n";
			os << "\t}\n\n";
		}

		os << "\tfunction toStream(&$data)\n";
		os << "\t{\n";
		if(!rStruct.strSuperName.empty())
			os << "\t\tparent::toStream($data);\n";
		for(SMember& rMember : rStruct.vecMember)
			os << "\t\t" << GetPHPWriteExpr(rMember, "$data") << "\n";
		os << "\t}\n\n";

		if(rStruct.bHasSub)
		{
			os << "\tpublic function superToStream(&$data)\n";
			os << "\t{\n";
			os << "\t\t$eType = $this->getClassType();\n";
			os << "\t\tByteUtil::writeUINT8($data, $eType);\n";
			os << "\t\t$this->toStream($data);\n";
			os << "\t}\n\n";
		}

		os << "\tstatic function vectorToStream(&$data, $arr)\n";
		os << "\t{\n";
		os << "\t\tByteUtil::writeVectorLength($data, count($arr));\n";
		os << "\t\tforeach($arr as $s)\n";
		os << "\t\t\t$s->toStream($data);\n";
		os << "\t}\n";

		if(rStruct.bHasSub)
		{
			os << "\n\tstatic function superVectorToStream(&$data, $arr)\n";
			os << "\t{\n";
			os << "\t\tByteUtil::writeVectorLength($data, count($arr));\n";
			os << "\t\tforeach($arr as $s)\n";
			os << "\t\t\t$s->superToStream($data);\n";
			os << "\t}\n";
		}
		os << "}\n\n";
	}

	if(_bHasC2SRetFunc)
	{
		for(SFunc& rFunc : _vecFuncC2S)
		{
			if(!rFunc.bReturn)
				continue;
			if(rFunc.bKeepParam)
			{
				os << "//函数[" << rFunc.strName << ":" << rFunc.strComment + "]的原来的参数组成的结构体\n";
				os << "class SOrigParam_" << rFunc.strName << "\n";
				os << "{\n";
				for(SParam& rParam : rFunc.vecParam)
				{
					if(rParam.bKeep)
						os << "\tpublic $" << rParam.strName << "; //" << rParam.GetPHPComment(*this) << "\n";
				}
				for(SParam& rParam : rFunc.vecLocParam)
					os << "\tpublic $loc_" << rParam.strName << "; //" << rParam.GetPHPComment(*this) << "\n";
				os << "\n\t//构造函数\n";
				os << "\tfunction __construct()\n";
				os << "\t{\n";
				for(SParam& rParam : rFunc.vecParam)
				{
					if(rParam.bKeep)
					{
						os << "\t\t$this->" << rParam.strName << " = ";
						PrintPHPDefaultValue(os, rParam);
					}
				}
				for(SParam& rParam : rFunc.vecLocParam)
				{
					os << "\t\t$this->" << rParam.strName << " = ";
					PrintPHPDefaultValue(os, rParam);
				}
				os << "\t}\n";
				os << "};\n\n";
			}
			if(!rFunc.vecRetParam.empty())
			{
				os << "//函数[" << rFunc.strName << ":" << rFunc.strComment + "]的返回的参数组成的结构体\n";
				os << "class SRetParam_" << rFunc.strName << "\n";
				os << "{\n";
				for(SParam& rParam : rFunc.vecRetParam)
					os << "\tpublic $" << rParam.strName << "; //" << rParam.GetPHPComment(*this) << "\n";
				os << "\n\t//构造函数\n";
				os << "\tfunction __construct()\n";
				os << "\t{\n";
				for(SParam& rParam : rFunc.vecRetParam)
				{
					os << "\t\t$this->" << rParam.strName << " = ";
					PrintPHPDefaultValue(os, rParam);
				}
				os << "\t}\n";
				os << "};\n\n";
			}
		}
	}

	os << "////////////////////////////////////////////////////////////\n";
	os << "//协议类：" << _strComment << "\n";
	os << "abstract class " << strPHPName << " extends ProtocolBase\n";
	os << "{\n";
	//send
	if(!_vecFuncC2S.empty())
		os << "\t/////////////////////以下为发送函数/////////////////////\n";
	for(SFunc& rFunc : _vecFuncC2S)
	{
		os << "\t//" << "发送：" + rFunc.strComment << "\n";
		os << "\tfunction send_" << rFunc.strName << "(\n";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			os << "\t\t$" << rParam.strName;
			if(i < size - 1 || rFunc.bReturn && !rFunc.vecLocParam.empty())
				os << ", ";
			os << " //" << rParam.GetPHPComment(*this) << "\n";
		}
		if(rFunc.bReturn)
		{
			for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
			{
				SParam& rParam = rFunc.vecLocParam[i];
				os << "\t\t$loc_" << rParam.strName;
				if(i < size - 1)
					os << ", ";
				os << " //" << rParam.GetPHPComment(*this) << "\n";
			}
		}
		os << "\t)\n";
		os << "\t{\n";
		PrintPHPRetParam(os, rFunc);
		os << "\t\t$data = '';\n";
		os << "\t\tByteUtil::writeINT8($data, $this->_protID);\n";
		os << "\t\t$funcID = " << rFunc.ID << ";\n";
		os << "\t\tByteUtil::writeINT8($data, $funcID);\n";
		if(rFunc.bReturn)
			os << "\t\tByteUtil::writeUINT32($data, $sessionID);\n";
		for(SParam& rParam : rFunc.vecParam)
			os << "\t\t" << GetPHPWriteExpr(rParam, "$data") << "\n";
		os << "\t\treturn $this->_svrHandler->sendPacket($data);\n";
		os << "\t}\n\n";
	}
	//OnReceive
	if(!_vecFuncS2C.empty())
		os << "\t/////////////////////以下的接收函数需要重载/////////////////////\n";
	for(SFunc& rFunc : _vecFuncS2C)
	{
		os << "\t//" << "接收：" + rFunc.strComment << "\n";
		os << "\tabstract function onRecv_" << rFunc.strName << "(\n";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			os << "\t\t$" << rParam.strName;
			if(i < size - 1)
				os << ",";
			os << " //" << rParam.GetPHPComment(*this) << "\n";
		}
		os << "\t);\n\n";
	}
	if(_bHasC2SRetFunc)
	{
		os << "\t/////////////////////以下的返回函数需要重载/////////////////////\n";
		for(SFunc& rFunc : _vecFuncC2S)
		{
			if(!rFunc.bReturn)
				continue;
			os << "\t" << "//返回：" + rFunc.strComment << "\n";
			os << "\tabstract function onReturn_" << rFunc.strName << "(\n";
			os << "\t\t$ret";
			if(rFunc.bKeepParam || !rFunc.vecRetParam.empty())
				os << ",";
			os << " //0为成功，1为失败，2为超时\n";
			if(rFunc.bKeepParam)
			{
				os << "\t\t$origParam";
				if(!rFunc.vecRetParam.empty())
					os << ",";
				os << " //(类类型：SOrigParam_" << rFunc.strName << ")原来的参数\n";
			}
			if(!rFunc.vecRetParam.empty())
				os << "\t\t$retParam //(类类型：SRetParam_" << rFunc.strName << ")返回的参数\n";
			os << "\t);\n\n";
		}
	}
	//Receive
	if(!_vecFuncS2C.empty())
		os << "\t/////////////////////以下为接收处理函数/////////////////////\n";
	for(SFunc& rFunc : _vecFuncS2C)
	{
		os << "\t" << "//接收处理：" + rFunc.strComment << "\n";
		os << "\tprivate function _doRecv_" << rFunc.strName << "($data)\n";
		os << "\t{\n";
		for(SParam& rParam : rFunc.vecParam)
			os << "\t\t" << GetPHPReadExpr(rParam, "$data") << "\n";
		os << "\t\treturn $this->onRecv_" << rFunc.strName << "(";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			os << "$" << rParam.strName;
			if(i < size - 1)
				os << ", ";
		}
		os << ");\n";
		os << "\t}\n\n";
	}
	//Return
	if(!_vecFuncS2C.empty() && _bHasC2SRetFunc)
		os << "\t/////////////////////以下为返回处理函数/////////////////////\n";
	for(SFunc& rFunc : _vecFuncC2S)
	{
		if(!rFunc.bReturn)
			continue;
		os << "\t" << "//返回处理：" + rFunc.strComment << "\n";
		os << "\tprivate function _doReturn_" << rFunc.strName << "($data)\n";
		os << "\t{\n";
		os << "\t\t$retParam = new SRetParam_" << rFunc.strName << ";\n";
		os << "\t\t$sessionID = ByteUtil::readUINT32($data);\n";
		os << "\t\t$retVal = ByteUtil::readBool($data);\n";
		for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			os << "\t\t" << GetPHPReadExpr(rParam, "$data") << " //" << rParam.GetASComment(*this) << "\n";
		}
		for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			os << "\t\t$retParam->" << rParam.strName << " = $" << rParam.strName << ";\n";
		}
		if(rFunc.bKeepParam)
			os << "\t\t$origParam = $this->_sessionMgr->getData($sessionID);\n";
		os << "\t\t$ret = 0;\n";
		if(rFunc.bKeepParam)
		{
			os << "\t\tif($origParam == null)\n";
			os << "\t\t\t$ret = 3; //确认已超时但又收到返回\n";
			os << "\t\telse if(!$retVal)\n";
			os << "\t\t\t$ret = 1;\n";
		}
		else
		{
			os << "\t\tif(!$retVal)\n";
			os << "\t\t\t$ret = 1;\n";
		}
		os << "\t\t$result = $this->onReturn_" << rFunc.strName << "($ret";
		if(rFunc.bKeepParam)
			os << ", $origParam";
		if(!rFunc.vecRetParam.empty())
			os << ", $retParam";
		os << ");\n";
		os << "\t\t$this->_sessionMgr->delSession($sessionID);\n";
		os << "\t\treturn $result;\n";
		os << "\t}\n\n";

		os << "\t" << "//超时处理：" + rFunc.strComment << "\n";
		os << "\tprivate function _onTimeOut_" << rFunc.strName << "($sessionID)\n";
		os << "\t{\n";
		if(!rFunc.vecRetParam.empty())
			os << "\t\t$retParam = new SRetParam_" << rFunc.strName << ";\n";
		if(rFunc.bKeepParam)
			os << "\t\t$origParam = $this->_sessionMgr->getData(sessionID);\n";
		os << "\t\t$this->onReturn_" << rFunc.strName << "(2";
		if(rFunc.bKeepParam)
			os << ", $origParam";
		if(!rFunc.vecRetParam.empty())
			os << ", $retParam";
		os << ");\n";
		os << "\t}\n\n";
	}
	os << "\t/////////////////////以下为协议接口/////////////////////\n";
	os << "\tprivate $_recvFuncList;\n";
	if(_bHasC2SRetFunc)
	{
		os << "\tprivate $_retFuncList;\n";
		os << "\tprivate $_timeFuncList;\n";
	}
	os << "\n";
	os << "\tfunction __construct()\n";
	os << "\t{\n";
	os << "\t\t$this->_protID = " << _ID << ";\n";
	for(size_t i = 0; i < _vecFuncS2C.size(); ++i)
	{
		SFunc& rFunc = _vecFuncS2C[i];
		os << "\t\t$this->_recvFuncList[" << i << "] = '_doRecv_" << rFunc.strName << "'; //FuncID: " << (i + 1) << "\n";
	}
	if(_bHasC2SRetFunc)
	{
		os << "\n";
		for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
		{
			SFunc& rFunc = _vecFuncC2S[i];
			if(rFunc.bReturn)
				os << "\t\t$this->_retFuncList[" << (-rFunc.iRetID - 1) << "] = '_doReturn_" << rFunc.strName << "'; //FuncID: " << -rFunc.iRetID << "\n";
		}
		os << "\n";
		for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
		{
			SFunc& rFunc = _vecFuncC2S[i];
			if(rFunc.bReturn)
				os << "\t\t$this->_timeFuncList[" << (-rFunc.iRetID - 1) << "] = '_onTimeOut_" << rFunc.strName << "'; //FuncID: " << -rFunc.iRetID << "\n";
		}
	}
	os << "\t}\n\n";
	os << "\tfunction handleMessage($data)\n";
	os << "\t{\n";
	if(!_vecFuncS2C.empty() || _bHasC2SRetFunc)
	{
		os << "\t\t$funcID = ByteUtil::readINT8($data);\n";
		os << "\t\tif($funcID == 0";
		if(!_vecFuncS2C.empty())
			os << " || $funcID > count($this->_recvFuncList)";
		if(_bHasC2SRetFunc)
			os << "\n\t\t\t || $funcID < -count($this->_retFuncList)";
		os << ")\n";
		os << "\t\t\treturn false;\n";
		os << "\t\tif($funcID > 0)\n";
		os << "\t\t\t$func = $this->_recvFuncList[$funcID - 1];\n";
		if(_bHasC2SRetFunc)
		{
			os << "\t\telse\n";
			os << "\t\t\t$func = $this->_retFuncList[-$funcID - 1];\n";
		}
		os << "\t\tif($func != null)\n";
		os << "\t\t\treturn call_user_func(array($this, $func), $data);\n";
		os << "\t\treturn false;\n";
	}
	else
	{
		os << "\t\t\treturn true;\n";
	}
	os << "\t}\n";
	if(_bHasC2SRetFunc)
	{
		os << "\n\tfunction onTimeOut($funcID, $sessionID)\n";
		os << "\t{\n";
		os << "\t\tif($funcID == 0 || $funcID > count($this->_timeFuncList))\n";
		os << "\t\t\treturn;\n";
		os << "\t\t$this->_timeFuncList[$funcID - 1]($sessionID);\n";
		os << "\t}\n";
	}

	os << "}\n";
	os << "\n?>";

	ofstream ofile(strPHPFile.c_str());
	string strUtf = os.str();
#ifdef _WIN32
	strUtf = GB2312ToUTF8(strUtf);
#endif
	ofile << strUtf;
	return true;
}

static string GetEnumWrite(const SEnum& rEnum, const string& strName)
{
	switch(rEnum.byByte)
	{
	case -1:
		return "writeINT8(";
	case 1:
		return "writeUINT8(";
	case -2:
		return "writeINT16(";
	case 2:
		return "writeUINT16(";
	case -4:
		return "writeINT32(";
	case 4:
		return "writeUINT32(";
	default:
		cerr << "Enum:" << rEnum.strName << " Byte:" << rEnum.byByte << " is invalid!" << endl;
		return "ErrorEnumByte";
	}
}

string CDocument::GetPHPWriteExpr(const SElement& rElement, const string& strStream)
{
	static map<string, string> mapPHPExpr;
	char szBuf[0x100];
	if(mapPHPExpr.empty())
	{
		mapPHPExpr["INT8"] = "ByteUtil::writeINT8(%s, %s);";
		mapPHPExpr["INT16"] = "ByteUtil::writeINT16(%s, %s);";
		mapPHPExpr["INT32"] = "ByteUtil::writeINT32(%s, %s);";
		mapPHPExpr["INT64"] = "ByteUtil::writeINT64(%s, %s);";
		mapPHPExpr["UINT8"] = "ByteUtil::writeUINT8(%s, %s);";
		mapPHPExpr["UINT16"] = "ByteUtil::writeUINT16(%s, %s);";
		mapPHPExpr["UINT32"] = "ByteUtil::writeUINT32(%s, %s);";
		mapPHPExpr["UINT64"] = "ByteUtil::writeUINT64(%s, %s);";
		mapPHPExpr["float"] = "ByteUtil::writeFloat(%s, %s);";
		mapPHPExpr["double"] = "ByteUtil::writeDouble(%s, %s);";
		mapPHPExpr["bool"] = "ByteUtil::writeBool(%s, %s);";
		mapPHPExpr["string"] = "ByteUtil::writeString(%s, %s);";

		mapPHPExpr["TVecINT8"] = "ByteUtil::writeVecINT8(%s, %s);";
		mapPHPExpr["TVecINT16"] = "ByteUtil::writeVecINT16(%s, %s);";
		mapPHPExpr["TVecINT32"] = "ByteUtil::writeVecINT32(%s, %s);";
		mapPHPExpr["TVecINT64"] = "ByteUtil::writeVecINT64(%s, %s);";
		mapPHPExpr["TVecUINT8"] = "ByteUtil::writeVecUINT8(%s, %s);";
		mapPHPExpr["TVecUINT16"] = "ByteUtil::writeVecUINT16(%s, %s);";
		mapPHPExpr["TVecUINT32"] = "ByteUtil::writeVecUINT32(%s, %s);";
		mapPHPExpr["TVecUINT64"] = "ByteUtil::writeVecUINT64(%s, %s);";
		mapPHPExpr["TVecFloat"] = "ByteUtil::writeVecFloat(%s, %s);";
		mapPHPExpr["TVecDouble"] = "ByteUtil::writeVecDouble(%s, %s);";
		mapPHPExpr["TVecBool"] = "ByteUtil::writeVecBool(%s, %s);";
		mapPHPExpr["TVecString"] = "ByteUtil::writeVecString(%s, %s);";
	}
	const string& strName = rElement.strName;
	string strVarName;
	if(rElement.bIsMember)
		strVarName = "$this->" + strName;
	else
		strVarName = "$" + strName;
	const string& strTypeName = rElement.strTypeName;
	auto it = mapPHPExpr.find(strTypeName);
	if(it != mapPHPExpr.end())
	{
		const string& strExpr = it->second;
		sprintf_s(szBuf, strExpr.c_str(), strStream.c_str(), strVarName.c_str());
		return szBuf;
	}

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return "ByteUtil::" + GetEnumWrite(*pEnum, strName) + strStream + ", " + strVarName + ");";

	SStruct* pStruct = GetStruct(strTypeName);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return strVarName + "->toStream(" + strStream + ");";
		else
			return strVarName + "->superToStream(" + strStream + ");";
	}

	pStruct = GetStruct(strTypeName, true);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return pStruct->strName + "::vectorToStream(" + strStream + ", " + strVarName + ");";
		else
			return pStruct->strName + "::superVectorToStream(" + strStream + ", " + strVarName + ");";
	}

	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef != _mapType2Ref.end())
	{
		SRefType& rRefType = itRef->second;
		if(rRefType.pDocument == NULL)
		{
			cerr << "Error protocol: " << rRefType.strPackage << endl;
			return "ErrorPackage";
		}
		CDocument* pDocument = rRefType.pDocument;
		pEnum = pDocument->GetEnum(rRefType.strTypeName);
		if(pEnum != NULL)
			return "ByteUtil::" + GetEnumWrite(*pEnum, strName) + strStream + ", " + strVarName + ");";
		pStruct = pDocument->GetStruct(rRefType.strTypeName);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return strVarName + "->toStream(" + strStream + ");";
			else
				return strVarName + "->superToStream(" + strStream + ");";
		}
		pStruct = pDocument->GetStruct(rRefType.strTypeName, true);
		if(pStruct != NULL)
		{
			string strNameSpace;
#ifdef PHP_USE_NAME_SPACE
			strNameSpace = "\\" + pDocument->_strNameSpace + "\\";
#endif
			if(!pStruct->bHasSub)
				return strNameSpace + pStruct->strName + "::vectorToStream(" + strStream + ", " + strVarName + ");";
			else
				return strNameSpace + pStruct->strName + "::superVectorToStream(" + strStream + ", " + strVarName + ");";
		}
	}

	cerr << "Invalid PHP Write Expression For " << strTypeName << endl;
	return "Invalid PHP Write Expression";
}

static string GetEnumRead(const SEnum& rEnum)
{
	switch(rEnum.byByte)
	{
	case -1:
		return "readINT8(";
	case -2:
		return "readINT16(";
	case -4:
		return "readINT32(";
	case 1:
		return "readUINT8(";
	case 2:
		return "readUINT16(";
	case 4:
		return "readUINT32(";
	default:
		cerr << "Enum:" << rEnum.strName << " Byte:" << rEnum.byByte << " is invalid!" << endl;
		return "ErrorEnumByte";
	}
}

string CDocument::GetPHPReadExpr(const SElement& rElement, const string& strStream)
{
	static map<string, string> mapPHPExpr;
	char szBuf[0x100];
	if(mapPHPExpr.empty())
	{
		mapPHPExpr["INT8"] = "%s = ByteUtil::readINT8(%s);";
		mapPHPExpr["INT16"] = "%s = ByteUtil::readINT16(%s);";
		mapPHPExpr["INT32"] = "%s = ByteUtil::readINT32(%s);";
		mapPHPExpr["INT64"] = "%s = ByteUtil::readINT64(%s);";
		mapPHPExpr["UINT8"] = "%s = ByteUtil::readUINT8(%s);";
		mapPHPExpr["UINT16"] = "%s = ByteUtil::readUINT16(%s);";
		mapPHPExpr["UINT32"] = "%s = ByteUtil::readUINT32(%s);";
		mapPHPExpr["UINT64"] = "%s = ByteUtil::readUINT64(%s);";
		mapPHPExpr["float"] = "%s = ByteUtil::readFloat(%s);";
		mapPHPExpr["double"] = "%s = ByteUtil::readDouble(%s);";
		mapPHPExpr["bool"] = "%s = ByteUtil::readBool(%s);";
		mapPHPExpr["string"] = "%s = ByteUtil::readString(%s);";

		mapPHPExpr["TVecINT8"] = "%s = ByteUtil::readVecINT8(%s);";
		mapPHPExpr["TVecINT16"] = "%s = ByteUtil::readVecINT16(%s);";
		mapPHPExpr["TVecINT32"] = "%s = ByteUtil::readVecINT32(%s);";
		mapPHPExpr["TVecINT64"] = "%s = ByteUtil::readVecINT64(%s);";
		mapPHPExpr["TVecUINT8"] = "%s = ByteUtil::readVecUINT8(%s);";
		mapPHPExpr["TVecUINT16"] = "%s = ByteUtil::readVecUINT16(%s);";
		mapPHPExpr["TVecUINT32"] = "%s = ByteUtil::readVecUINT32(%s);";
		mapPHPExpr["TVecUINT64"] = "%s = ByteUtil::readVecUINT64(%s);";
		mapPHPExpr["TVecFloat"] = "%s = ByteUtil::readVecFloat(%s);";
		mapPHPExpr["TVecDouble"] = "%s = ByteUtil::readVecDouble(%s);";
		mapPHPExpr["TVecBool"] = "%s = ByteUtil::readVecBool(%s);";
		mapPHPExpr["TVecString"] = "%s = ByteUtil::readVecString(%s);";
	}
	const string& strName = rElement.strName;
	string strVarName;
	if(rElement.bIsMember)
		strVarName = "$s->" + strName;
	else
		strVarName = "$" + strName;
	const string& strTypeName = rElement.strTypeName;
	auto it = mapPHPExpr.find(strTypeName);
	if(it != mapPHPExpr.end())
	{
		const string& strExpr = it->second;
		sprintf_s(szBuf, strExpr.c_str(), strVarName.c_str(), strStream.c_str());
		return szBuf;
	}

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return strVarName + " = ByteUtil::" + GetEnumRead(*pEnum) + strStream + ");";

	SStruct* pStruct = GetStruct(strTypeName);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return strVarName + " = " + strTypeName + "::fromStream(" + strStream + ");";
		else
			return strVarName + " = " + strTypeName + "::superFromStream(" + strStream + ");";
	}

	pStruct = GetStruct(strTypeName, true);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return strVarName + " = " + pStruct->strName + "::vectorFromStream(" + strStream + ");";
		else
			return strVarName + " = " + pStruct->strName + "::superVectorFromStream(" + strStream + ");";
	}

	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef != _mapType2Ref.end())
	{
		SRefType& rRefType = itRef->second;
		if(rRefType.pDocument == NULL)
		{
			cerr << "Error protocol: " << rRefType.strPackage << endl;
			return "ErrorPackage";
		}
		CDocument* pDocument = rRefType.pDocument;
		pEnum = pDocument->GetEnum(rRefType.strTypeName);
		if(pEnum != NULL)
			return strVarName + " = ByteUtil::" + GetEnumRead(*pEnum) + strStream + ");";
		string strNameSpace;
#ifdef PHP_USE_NAME_SPACE
		strNameSpace = "\\" + pDocument->_strNameSpace + "\\";
#endif
		pStruct = pDocument->GetStruct(rRefType.strTypeName);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return strVarName + " = " + strNameSpace + pStruct->strName + "::fromStream(" + strStream + ");";
			else
				return strVarName + " = " + strNameSpace + pStruct->strName + "::superFromStream(" + strStream + ");";
		}
		pStruct = pDocument->GetStruct(rRefType.strTypeName, true);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return strVarName + " = " + strNameSpace + pStruct->strName + "::vectorFromStream(" + strStream + ");";
			else
				return strVarName + " = " + strNameSpace + pStruct->strName + "::superVectorFromStream(" + strStream + ");";
		}
	}
	cerr << "Invalid PHP Read Expression For " << strTypeName << endl;
	return "Invalid PHP Read Expression";
}

void CDocument::PrintPHPRetParam(ostringstream& os, SFunc& rFunc)
{
	if(!rFunc.bReturn)
		return;
	os << "\t\t$sessionID = $this->_sessionMgr->getNewSession($this, " << -rFunc.iRetID << ");\n";
	if(rFunc.bKeepParam)
	{
		os << "\t\t$origParam = new SOrigParam_" << rFunc.strName << ";\n";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			if(rParam.bKeep)
				os << "\t\t$origParam->" << rParam.strName << " = $" << rParam.strName << ";\n";
		}
		for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecLocParam[i];
			os << "\t\t$origParam->loc_" << rParam.strName << " = $loc_" << rParam.strName << ";\n";
		}
		os << "\t\t$this->_sessionMgr->storeData($sessionID, $origParam);\n";
	}
}

bool CDocument::GetPHPEnumItemName(const string& strName, string& strPHPName, const SEnum* pCurEnum /*= NULL*/)
{
	SEnum* pEnum = NULL;
	SMember* pMember = GetEnumItem(strName, &pEnum);
	if(pMember != NULL && pEnum != NULL)
	{
		if(pEnum == pCurEnum)
			strPHPName = strName;
		else
			strPHPName = pEnum->strName + "::" + strName;
		return true;
	}
	else
	{
		SRefType* pRefType = GetRefEnumItem(strName, &pEnum, &pMember);
		if(pRefType != NULL && pEnum != NULL)
		{
			strPHPName = pEnum->strName + "::" + pRefType->strTypeName;
			return true;
		}
	}
	return false;
}

string CDocument::GetPHPComment(const string& strTypeName, const string& strComment)
{
	static map<string, string> mapPHPCmt;
	if(mapPHPCmt.empty())
	{
		mapPHPCmt["INT8"] = "INT8";
		mapPHPCmt["INT16"] = "INT16";
		mapPHPCmt["INT32"] = "INT32";
		mapPHPCmt["INT64"] = "INT64";
		mapPHPCmt["UINT8"] = "UINT8";
		mapPHPCmt["UINT16"] = "UINT16";
		mapPHPCmt["UINT32"] = "UINT32";
		mapPHPCmt["UINT64"] = "UINT64";
		mapPHPCmt["float"] = "float";
		mapPHPCmt["double"] = "double";
		mapPHPCmt["bool"] = "bool";
		mapPHPCmt["string"] = "string";

		mapPHPCmt["TVecINT8"] = "INT8数组";
		mapPHPCmt["TVecINT16"] = "INT16数组";
		mapPHPCmt["TVecINT32"] = "INT32数组";
		mapPHPCmt["TVecINT64"] = "INT64数组";
		mapPHPCmt["TVecUINT8"] = "UINT8数组";
		mapPHPCmt["TVecUINT16"] = "UINT16数组";
		mapPHPCmt["TVecUINT32"] = "UINT32数组";
		mapPHPCmt["TVecUINT64"] = "UINT64数组";
		mapPHPCmt["TVecFloat"] = "float数组";
		mapPHPCmt["TVecDouble"] = "double数组";
		mapPHPCmt["TVecBool"] = "bool数组";
		mapPHPCmt["TVecString"] = "string数组";
	}
	auto it = mapPHPCmt.find(strTypeName);
	if(it != mapPHPCmt.end())
	{
		const string& strCmt = it->second;
		return "(" + strCmt + ")" + strComment;
	}

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return "(枚举类型：" + strTypeName + ")" + strComment;

	SStruct* pStruct = GetStruct(strTypeName);
	if(pStruct != NULL)
		return "(类类型：" + strTypeName + ")" + strComment;

	pStruct = GetStruct(strTypeName, true);
	if(pStruct != NULL)
		return "(" + pStruct->strName + "的数组)" + strComment;

	auto itRef = _mapType2Ref.find(strTypeName);
	if(itRef != _mapType2Ref.end())
	{
		SRefType& rRefType = itRef->second;
		if(rRefType.pDocument == NULL)
		{
			cerr << "Error protocol: " << rRefType.strPackage << endl;
			return "ErrorPackage";
		}
		pEnum = rRefType.pDocument->GetEnum(rRefType.strTypeName);
		if(pEnum != NULL)
			return "(枚类型：" + strTypeName + ")" + strComment;
		pStruct = rRefType.pDocument->GetStruct(rRefType.strTypeName);
		if(pStruct != NULL)
			return "(类类型：" + strTypeName + ")" + strComment;
		pStruct = rRefType.pDocument->GetStruct(rRefType.strTypeName, true);
		if(pStruct != NULL)
			return "(" + pStruct->strName + "的数组)" + strComment;
	}
	cerr << "Invalid PHP Type For " << strTypeName << endl;
	return strComment;
}
