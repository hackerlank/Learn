/********************************************************************
//	Communication Protocol Generation Tool Source File.
//	File name:	Ruby.cpp
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

void CDocument::PrintRubyDefaultValue(ostringstream& os, const SElement& rElement)
{
	if(IsPrimType(rElement.strTypeName))
	{
		
		if(rElement.strTypeName == "bool")
			os << "false\n";
		else
			os << "0\n";
	}
	else if(IsStringType(rElement.strTypeName))
	{
		os << "''\n";
	}
	else if(IsVectorType(rElement.strTypeName))
	{
		os << "Array.new\n";
	}
	else
	{
		SStruct* pStruct = NULL;
		GetRefStruct(rElement.strTypeName, false, &pStruct);
		if(pStruct != NULL)
			os << pStruct->strName << ".new\n";
		else
			os << rElement.strTypeName << ".new\n";
	}
}

#define TOUPPER(a) std::transform(a.begin(), a.end(), a.begin(), ::toupper)

bool CDocument::GenRuby(const char* szDestDir)
{
	//if(!HasClientType(eClientPhp))
	//	return true;
	if(szDestDir == NULL)
		return false;
	string strDestPath = string(szDestDir) + PATHSEP"Ruby";
	CreateDirectory(strDestPath);
	string strRubyName = _strName + "Base";
	string strRubyFile = strDestPath + PATHSEP + strRubyName + ".rb";
	ostringstream os;
//	os << "<?php\n";
	string strTitle = 
		"#************************************************************************\n"
		"#  工具自动生成的Ruby客户端协议代码\n"
		"#  File Name:    " + _strFileName + ".rb\n"
		"#  Purpose:      " + _strComment + "\n"
#ifdef GEN_FILE_TIME
		"#  Create Time:  " + _strGenTime + "\n"
#endif
		"#  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.\n"
		"#*************************************************************************/\n\n";
	os << strTitle;
#ifdef RUBY_USE_NAME_SPACE
	os << "module " << _strNameSpace << ";\n\n";
#endif
	os << "require_relative '../core/ByteUtil.rb'\n";
	os << "require_relative '../core/ProtocolBase.rb'\n";
	for(auto it = _mapProt2Doc.begin(); it != _mapProt2Doc.end(); ++it)
	{
		string strFile = it->first + "Base.rb";
		os << "require_relative './" << strFile << "'\n";
	}

#ifdef PHP_USE_NAME_SPACE
	os << "\nuse ProtocolBase;\n";
	os << "use ByteUtil;\n\n";
#else
	os << "\n";
#endif

	if(!_vecEnum.empty() || !_vecStruct.empty())
		os << "#以下为类型定义\n\n";
	//enum
	for(SEnum& rEnum : _vecEnum)
	{
		os << "#" << rEnum.strComment << "\n";
		os << "class " << rEnum.strName << "\n";
		//os << "{\n";
		for(size_t i = 0; i < rEnum.vecMember.size(); ++i)
		{
			const SMember& rMember = rEnum.vecMember[i];
			string strMember = rMember.strName;
			TOUPPER(strMember);
			os << "\t" << strMember << " = ";
			if(rMember.strTypeName.empty() || atoi(rMember.strTypeName.c_str()) == 0)
				os << rMember.qwValue;
			else
				os << rMember.strTypeName;
			const string& strComment = rMember.strComment;
			if(!strComment.empty())
				os << "#" << strComment << "\n";
			else
				os << "\n";
		}
		os << "end\n\n";
	}

	//struct
	for(SStruct* pStruct : _vecStruct)
	{
		SStruct& rStruct = *pStruct;
		if(rStruct.eGlobalType == eGlobalServer)
			continue;
		os << "#" << rStruct.strComment << "\n";
		if(!rStruct.bHasSub)
		{
			if(rStruct.strSuperName.empty())
				os << "class " << rStruct.strName << "\n";
			else
				os << "class " << rStruct.strName << " < " << rStruct.strSuperName << "\n";
		}
		else
		{
			if(rStruct.strSuperName.empty())
				os << "class " << rStruct.strName << "\n";
			else
				os << "class " << rStruct.strName << " < " << rStruct.strSuperName << "\n";
		}
		//os << "end\n";
		for(SMember& rMember : rStruct.vecMember)
			os << "\tattr_accessor:" << rMember.strName << " #" << rMember.GetRubyComment(*this) << "\n";
			//os << "\t@" << rMember.strName << " #" << rMember.GetRubyComment(*this) << "\n";
		if(!rStruct.vecMember.empty())
			os << "\n";
		os << "\t#构造函数\n";
		os << "\tdef initialize\n";
		if(!rStruct.strSuperName.empty())
			os << "\t\tsuper()\n";
		for(SMember& rMember : rStruct.vecMember)
		{
			os << "\t\t@" << rMember.strName << " = ";
			PrintRubyDefaultValue(os, rMember);
		}
		os << "\tend\n\n";
		if(rStruct.bHasSub || !rStruct.strSuperName.empty())
		{
			os << "\t#获取继承类的类型\n";
			os << "\tdef getClassType\n";
			string strName = rStruct.strName;
			TOUPPER(strName);
			os << "\t\treturn EType_" << GetBaseClassName(rStruct.strName) << "::ETYPE_" << strName << "\n";
			os << "\tend\n\n";
		}
		if(!rStruct.vecMember.empty())
		{
			os << "\t#拷贝到另一个对象\n";
			os << "\tdef copyTo(obj)\n";
			SStruct* pStruct = GetStruct(rStruct.strSuperName);
			if(pStruct != NULL && !pStruct->vecMember.empty())
				os << "\t\tsuper(obj)\n";
			for(size_t i = 0; i < rStruct.vecMember.size(); ++i)
			{
				const SMember& rMember = rStruct.vecMember[i];
				os << "\t\tobj." << rMember.strName << " = @" << rMember.strName << "\n";
			}
			os << "\tend\n\n";
		}
		os << "\t#以下为序列化函数\n";
		os << "\tdef self.fromStream(data)\n";
		//os << "\t{\n";
		os << "\t\ts = " << rStruct.strName << ".new\n";
		if(!rStruct.strSuperName.empty())
		{
			os << "\t\tbase = " << rStruct.strSuperName << "::fromStream(data)\n";
			SStruct* pStruct = GetStruct(rStruct.strSuperName);
			if(pStruct == NULL)
			{
				cerr << "Can't find Struct: " << rStruct.strSuperName << endl;
				return false;
			}
			if(!pStruct->vecMember.empty())
				os << "\t\tbase.copyTo(s)\n";
		}
		for(SMember& rMember : rStruct.vecMember)
			os << "\t\t" << GetRubyReadExpr(rMember, "data") << "\n";
		os << "\t\treturn s\n";
		os << "\tend\n\n";

		if(rStruct.bHasSub)
		{
			os << "\tdef self.superFromStream(data)\n";
			//os << "\t{\n";
			os << "\t\teType = ByteUtil::readUINT8(data)\n";
			os << "\t\tcase eType\n";
			//os << "\t\t{\n";
			vector<string> vecAllName;
			vecAllName.push_back(rStruct.strName);
			vecAllName.insert(vecAllName.end(), rStruct.vecSubName.begin(), rStruct.vecSubName.end());
			for(string& strName : vecAllName)
			{
				string strName_ = strName;
				TOUPPER(strName_);
				os << "\t\t\twhen EType_" << GetBaseClassName(rStruct.strName) << "::ETYPE_" << strName_ << "\n";
				os << "\t\t\t\ts = " << strName << "::fromStream(data)\n";
				//os << "\t\t\t\tbreak;\n";
			}
			//os << "\t\t\telse\n";
			//os << "\t\t\t\tthrow new Exception('Unknown value for EType_" << GetBaseClassName(rStruct.strName) << ":'.eType);\n";
			os << "\t\tend\n";
			os << "\t\treturn s\n";
			os << "\tend\n\n";
		}

		os << "\tdef self.vectorFromStream(data)\n";
		//os << "\t{\n";
		os << "\t\tlength = ByteUtil::readVectorLength(data)\n";
		os << "\t\tarr = Array.new\n";
		//os << "\t\tfor(i = 0; i < length; ++i)\n";
		os << "\t\tlength.times do |i|\n";
		//os << "\t\t{\n";
		os << "\t\t\ts = " << rStruct.strName << "::fromStream(data)\n";
		os << "\t\t\tarr[i] = s\n";
		os << "\t\tend\n";
		os << "\t\treturn arr\n";
		os << "\tend\n\n";

		if(rStruct.bHasSub)
		{
			os << "\tdef self.superVectorFromStream(data)\n";
			//os << "\t{\n";
			os << "\t\tlength = ByteUtil::readVectorLength(data)\n";
			os << "\t\tarr = Array.new\n";
			//os << "\t\tfor(i = 0; i < length; ++i)\n";
			os << "\t\tlength.times do |i|\n";
			//os << "\t\t{\n";
			os << "\t\t\ts = " << rStruct.strName << "::superFromStream(data)\n";
			os << "\t\t\tarr[i] = s\n";
			os << "\t\tend\n";
			os << "\t\treturn arr\n";
			os << "\tend\n\n";
		}

		os << "\tdef toStream(data)\n";
		//os << "\t{\n";
		if(!rStruct.strSuperName.empty())
			os << "\t\tsuper::toStream(data)\n";
		for(SMember& rMember : rStruct.vecMember)
			os << "\t\t" << GetRubyWriteExpr(rMember, "data") << "\n";
		os << "\tend\n\n";

		if(rStruct.bHasSub)
		{
			os << "\tdef superToStream(data)\n";
			//os << "\t{\n";
			os << "\t\teType = getClassType()\n";
			os << "\t\tByteUtil::writeUINT8(data, eType)\n";
			os << "\t\ttoStream(data)\n";
			os << "\tend\n\n";
		}

		os << "\tdef self.vectorToStream(data, arr)\n";
		//os << "\t{\n";
		os << "\t\tByteUtil::writeVectorLength(data, arr.length)\n";
		//os << "\t\tforeach($arr as $s)\n";
		os << "\t\tarr.each do |s|\n";
		os << "\t\t\ts.toStream(data)\n";
		os << "\t\tend\n";
		os << "\tend\n";

		if(rStruct.bHasSub)
		{
			os << "\n\tdef self.superVectorToStream(data, arr)\n";
			//os << "\t{\n";
			os << "\t\tByteUtil::writeVectorLength(data, arr.length)\n";
//			os << "\t\tforeach($arr as $s)\n";
			os << "\t\tarr.each do |s|\n";
			os << "\t\t\ts.superToStream(data)\n";
			os << "\t\tend\n";
			os << "\tend\n";
		}
		os << "end\n\n";
	}

	if(_bHasC2SRetFunc)
	{
		for(SFunc& rFunc : _vecFuncC2S)
		{
			if(!rFunc.bReturn)
				continue;
			if(rFunc.bKeepParam)
			{
				os << "#函数[" << rFunc.strName << ":" << rFunc.strComment + "]的原来的参数组成的结构体\n";
				os << "class SOrigParam_" << rFunc.strName << "\n";
				//os << "{\n";
				for(SParam& rParam : rFunc.vecParam)
				{
					if(rParam.bKeep)
						os << "\tattr_accessor:" << rParam.strName << " #" << rParam.GetRubyComment(*this) << "\n";
				}
				for(SParam& rParam : rFunc.vecLocParam)
					os << "\tattr_accessor:loc_" << rParam.strName << " #" << rParam.GetRubyComment(*this) << "\n";
				os << "\n\t#构造函数\n";
				os << "\tdef initialize\n";
				//os << "\t{\n";
				for(SParam& rParam : rFunc.vecParam)
				{
					if(rParam.bKeep)
					{
						os << "\t\t@" << rParam.strName << " = ";
						PrintRubyDefaultValue(os, rParam);
					}
				}
				for(SParam& rParam : rFunc.vecLocParam)
				{
					os << "\t\t@" << rParam.strName << " = ";
					PrintRubyDefaultValue(os, rParam);
				}
				os << "\tend\n";
				os << "end\n\n";
			}
			if(!rFunc.vecRetParam.empty())
			{
				os << "#函数[" << rFunc.strName << ":" << rFunc.strComment + "]的返回的参数组成的结构体\n";
				os << "class SRetParam_" << rFunc.strName << "\n";
				//os << "{\n";
				for(SParam& rParam : rFunc.vecRetParam)
					os << "\tattr_accessor:" << rParam.strName << "#" << rParam.GetRubyComment(*this) << "\n";
				os << "\n\t#构造函数\n";
				os << "\tdef initialize\n";
				//os << "\t{\n";
				for(SParam& rParam : rFunc.vecRetParam)
				{
					os << "\t\t@" << rParam.strName << " = ";
					PrintRubyDefaultValue(os, rParam);
				}
				os << "\tend\n";
				os << "end\n\n";
			}
		}
	}

	//os << "////////////////////////////////////////////////////////////\n";
	os << "#协议类：" << _strComment << "\n";
	os << "class " << strRubyName << " < ProtocolBase\n";
	//os << "{\n";
	//send
	if(!_vecFuncC2S.empty())
		os << "\t#以下为发送函数\n";
		//os << "\t/////////////////////以下为发送函数/////////////////////\n";
	for(SFunc& rFunc : _vecFuncC2S)
	{
		os << "\t#" << "发送：" + rFunc.strComment << "\n";
		os << "\tdef send_" << rFunc.strName << "(\n";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			os << "\t\t" << rParam.strName;
			if(i < size - 1 || rFunc.bReturn && !rFunc.vecLocParam.empty())
				os << ", ";
			os << " #" << rParam.GetRubyComment(*this) << "\n";
		}
		if(rFunc.bReturn)
		{
			for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
			{
				SParam& rParam = rFunc.vecLocParam[i];
				os << "\t\tloc_" << rParam.strName;
				if(i < size - 1)
					os << ", ";
				os << " #" << rParam.GetRubyComment(*this) << "\n";
			}
		}
		os << "\t)\n";
		//os << "\t{\n";
		PrintRubyRetParam(os, rFunc);
		os << "\t\tdata = ''\n";
		os << "\t\tByteUtil::writeINT8(data, @protID)\n";
		os << "\t\tfuncID = " << rFunc.ID << "\n";
		os << "\t\tByteUtil::writeINT8(data, funcID)\n";
		if(rFunc.bReturn)
			os << "\t\tByteUtil::writeUINT32(data, sessionID)\n";
		for(SParam& rParam : rFunc.vecParam)
			os << "\t\t" << GetRubyWriteExpr(rParam, "data") << "\n";
		os << "\t\treturn @svrHandler.sendPacket(data)\n";
		os << "\tend\n\n";
	}
	//OnReceive
	if(!_vecFuncS2C.empty())
		os << "#以下的接收函数需要重载\n";
		//os << "\t/////////////////////以下的接收函数需要重载/////////////////////\n";
	for(SFunc& rFunc : _vecFuncS2C)
	{
		os << "\t#" << "接收：" + rFunc.strComment << "\n";
		os << "\tdef onRecv_" << rFunc.strName << "(\n";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			os << "\t\t" << rParam.strName;
			if(i < size - 1)
				os << ",";
			os << " #" << rParam.GetRubyComment(*this) << "\n";
		}
		os << "\t)\n";
		os << "\t\traise NotImplementedError\n";
		os << "\tend\n";
	}
	if(_bHasC2SRetFunc)
	{
		//os << "\t/////////////////////以下的返回函数需要重载/////////////////////\n";
		os << "#以下的返回函数需要重载\n";
		for(SFunc& rFunc : _vecFuncC2S)
		{
			if(!rFunc.bReturn)
				continue;
			os << "\t" << "#返回：" + rFunc.strComment << "\n";
			os << "\tdef onReturn_" << rFunc.strName << "(\n";
			os << "\t\tret";
			if(rFunc.bKeepParam || !rFunc.vecRetParam.empty())
				os << ",";
			os << " #0为成功，1为失败，2为超时\n";
			if(rFunc.bKeepParam)
			{
				os << "\t\torigParam";
				if(!rFunc.vecRetParam.empty())
					os << ",";
				os << " #(类类型：SOrigParam_" << rFunc.strName << ")原来的参数\n";
			}
			if(!rFunc.vecRetParam.empty())
				os << "\t\tretParam #(类类型：SRetParam_" << rFunc.strName << ")返回的参数\n";
			os << "\t)\n";
			os << "\tend\n\n";
		}
	}
	//Receive
	if(!_vecFuncS2C.empty())
		os << "#以下为接收处理函数\n";
		//os << "\t/////////////////////以下为接收处理函数/////////////////////\n";
	for(SFunc& rFunc : _vecFuncS2C)
	{
		os << "\t" << "#接收处理：" + rFunc.strComment << "\n";
		os << "\tdef _doRecv_" << rFunc.strName << "(data)\n";
		//os << "\t{\n";
		for(SParam& rParam : rFunc.vecParam)
			os << "\t\t" << GetRubyReadExpr(rParam, "data") << "\n";
		os << "\t\treturn onRecv_" << rFunc.strName << "(";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			os << "" << rParam.strName;
			if(i < size - 1)
				os << ", ";
		}
		os << ")\n";
		os << "\tend\n\n";
	}
	//Return
	if(!_vecFuncS2C.empty() && _bHasC2SRetFunc)
		os << "#以下为返回处理函数\n";
		//os << "\t/////////////////////以下为返回处理函数/////////////////////\n";
	for(SFunc& rFunc : _vecFuncC2S)
	{
		if(!rFunc.bReturn)
			continue;
		os << "\t" << "#返回处理：" + rFunc.strComment << "\n";
		os << "\tdef _doReturn_" << rFunc.strName << "(data)\n";
		//os << "\t{\n";
		os << "\t\tretParam = SRetParam_" << rFunc.strName << ".new\n";
		os << "\t\tsessionID = ByteUtil::readUINT32(data)\n";
		os << "\t\tretVal = ByteUtil::readBOOL(data)\n";
		for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			os << "\t\t" << GetRubyReadExpr(rParam, "data") << " #" << rParam.GetRubyComment(*this) << "\n";
		}
		for(size_t k = 0, size = rFunc.vecRetParam.size(); k < size; ++k)
		{
			SParam& rParam = rFunc.vecRetParam[k];
			os << "\t\tretParam." << rParam.strName << " = " << rParam.strName << "\n";
		}
		if(rFunc.bKeepParam)
			os << "\t\torigParam = @sessionMgr.getData(sessionID)\n";
		os << "\t\tret = 0\n";
		if(rFunc.bKeepParam)
		{
			os << "\t\tif origParam == nil \n";
			os << "\t\t\tret = 3 #确认已超时但又收到返回\n";
			os << "\t\telsif(!retVal)\n";
			os << "\t\t\tret = 1\n";
			os << "\t\tend\n";
		}
		else
		{
			os << "\t\tif(!retVal)\n";
			os << "\t\t\tret = 1\n";
			os << "\t\tend\n";
		}
		os << "\t\tresult = onReturn_" << rFunc.strName << "(ret";
		if(rFunc.bKeepParam)
			os << ", origParam";
		if(!rFunc.vecRetParam.empty())
			os << ", retParam";
		os << ")\n";
		os << "\t\t@sessionMgr.delSession(sessionID)\n";
		os << "\t\treturn result\n";
		os << "\tend\n\n";

		os << "\t" << "#超时处理：" + rFunc.strComment << "\n";
		os << "\tdef _onTimeOut_" << rFunc.strName << "(sessionID)\n";
		//os << "\t{\n";
		if(!rFunc.vecRetParam.empty())
			os << "\t\tretParam = SRetParam_" << rFunc.strName << ".new;\n";
		if(rFunc.bKeepParam)
			os << "\t\torigParam = @sessionMgr.getData(sessionID)\n";
		os << "\t\tonReturn_" << rFunc.strName << "(2";
		if(rFunc.bKeepParam)
			os << ", origParam";
		if(!rFunc.vecRetParam.empty())
			os << ", retParam";
		os << ")\n";
		os << "\tend\n\n";
	}
	os << "\t#以下为协议接口\n";
	os << "\t@recvFuncList\n";
	if(_bHasC2SRetFunc)
	{
		os << "\t@retFuncList\n";
		os << "\t@timeFuncList\n";
	}
	os << "\n";
	os << "\tdef initialize\n";
	//os << "\t{\n";
	os << "\t\t@protID = " << _ID << ";\n";
	os << "\t\t@recvFuncList = Array.new\n";
	for(size_t i = 0; i < _vecFuncS2C.size(); ++i)
	{
		SFunc& rFunc = _vecFuncS2C[i];
		os << "\t\t@recvFuncList[" << i << "] = '_doRecv_" << rFunc.strName << "' #FuncID: " << (i + 1) << "\n";
	}
	if(_bHasC2SRetFunc)
	{
		os << "\n";
		os << "\t\t@retFuncList = Array.new\n";
		for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
		{
			SFunc& rFunc = _vecFuncC2S[i];
			if(rFunc.bReturn)
				os << "\t\t@retFuncList[" << (-rFunc.iRetID - 1) << "] = '_doReturn_" << rFunc.strName << "' #FuncID: " << -rFunc.iRetID << "\n";
		}
		os << "\n";
		os << "\t\t@timeFuncList = Array.new\n";
		for(size_t i = 0; i < _vecFuncC2S.size(); ++i)
		{
			SFunc& rFunc = _vecFuncC2S[i];
			if(rFunc.bReturn)
				os << "\t\t@timeFuncList[" << (-rFunc.iRetID - 1) << "] = '_onTimeOut_" << rFunc.strName << "' #FuncID: " << -rFunc.iRetID << "\n";
		}
	}
	os << "\tend\n\n";
	os << "\tdef handleMessage(data)\n";
	//os << "\t{\n";
	if(!_vecFuncS2C.empty() || _bHasC2SRetFunc)
	{
		os << "\t\tfuncID = ByteUtil::readINT8(data);\n";
		os << "\t\tif funcID == 0";
		if(!_vecFuncS2C.empty())
			os << " || funcID > @recvFuncList.length";
		if(_bHasC2SRetFunc)
			os << " || funcID < -@retFuncList.length";
		os << "\n";
		os << "\t\t\treturn false\n";
		os << "\t\tend\n";
		os << "\t\tif funcID > 0 \n";
		os << "\t\t\tfunc = @recvFuncList[funcID - 1]\n";
		if(_bHasC2SRetFunc)
		{
			os << "\t\telse\n";
			os << "\t\t\tfunc = @retFuncList[-funcID - 1]\n";
			os << "\t\tend\n";
		}
		else
		{
			os << "\t\tend\n";
		}
		os << "\t\tif func\n";
		os << "\t\t\t send(func, data)\n";	
		os << "\t\tend\n";
		os << "\t\t#if func != nil\n";
		os << "\t\t\t#return call_user_func(Array.new(self, func), data)\n";
		os << "\t\t#end\n";
		//os << "\t\t\treturn call_user_func(Array.new(self, func), data)\n";
		os << "\t\treturn true\n";
	}
	else
	{
		os << "\t\treturn true;\n";
	}
	os << "\tend\n";
	if(_bHasC2SRetFunc)
	{
		os << "\n\tdef onTimeOut(funcID, sessionID)\n";
		//os << "\t{\n";
		os << "\t\tif funcID == 0 || funcID > @timeFuncList.length\n";
		os << "\t\t\treturn\n";
		os << "\t\tend\n";
		//os << "\t\t@timeFuncList[funcID - 1](sessionID)\n";
		os << "\t\tsend(@timeFuncList[funcID - 1], sessionID)\n";
		os << "\tend\n";
	}

	os << "end\n";
	os << "\n";

	ofstream ofile(strRubyFile.c_str());
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

string CDocument::GetRubyWriteExpr(const SElement& rElement, const string& strStream)
{
	static map<string, string> mapRubyExpr;
	char szBuf[0x100];
	if(mapRubyExpr.empty())
	{
		mapRubyExpr["INT8"] = "ByteUtil::writeINT8(%s, %s)";
		mapRubyExpr["INT16"] = "ByteUtil::writeINT16(%s, %s)";
		mapRubyExpr["INT32"] = "ByteUtil::writeINT32(%s, %s)";
		mapRubyExpr["INT64"] = "ByteUtil::writeINT64(%s, %s)";
		mapRubyExpr["UINT8"] = "ByteUtil::writeUINT8(%s, %s)";
		mapRubyExpr["UINT16"] = "ByteUtil::writeUINT16(%s, %s)";
		mapRubyExpr["UINT32"] = "ByteUtil::writeUINT32(%s, %s)";
		mapRubyExpr["UINT64"] = "ByteUtil::writeUINT64(%s, %s)";
		mapRubyExpr["float"] = "ByteUtil::writeFLOAT(%s, %s)";
		mapRubyExpr["double"] = "ByteUtil::writeDOUBLE(%s, %s)";
		mapRubyExpr["bool"] = "ByteUtil::writeBOOL(%s, %s)";
		mapRubyExpr["string"] = "ByteUtil::writeSTRING(%s, %s)";

		mapRubyExpr["TVecINT8"] = "ByteUtil::writeVecINT8(%s, %s)";
		mapRubyExpr["TVecINT16"] = "ByteUtil::writeVecINT16(%s, %s)";
		mapRubyExpr["TVecINT32"] = "ByteUtil::writeVecINT32(%s, %s)";
		mapRubyExpr["TVecINT64"] = "ByteUtil::writeVecINT64(%s, %s)";
		mapRubyExpr["TVecUINT8"] = "ByteUtil::writeVecUINT8(%s, %s)";
		mapRubyExpr["TVecUINT16"] = "ByteUtil::writeVecUINT16(%s, %s)";
		mapRubyExpr["TVecUINT32"] = "ByteUtil::writeVecUINT32(%s, %s)";
		mapRubyExpr["TVecUINT64"] = "ByteUtil::writeVecUINT64(%s, %s)";
		mapRubyExpr["TVecFloat"] = "ByteUtil::writeVecFLOAT(%s, %s)";
		mapRubyExpr["TVecDouble"] = "ByteUtil::writeVecDOUBLE(%s, %s)";
		mapRubyExpr["TVecBool"] = "ByteUtil::writeVecBOOL(%s, %s)";
		mapRubyExpr["TVecString"] = "ByteUtil::writeVecSTRING(%s, %s)";
	}
	const string& strName = rElement.strName;
	string strVarName;
	if(rElement.bIsMember)
		strVarName = "@" + strName;
	else
		strVarName = strName;
	const string& strTypeName = rElement.strTypeName;
	auto it = mapRubyExpr.find(strTypeName);
	if(it != mapRubyExpr.end())
	{
		const string& strExpr = it->second;
		sprintf_s(szBuf, strExpr.c_str(), strStream.c_str(), strVarName.c_str());
		return szBuf;
	}

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return "ByteUtil::" + GetEnumWrite(*pEnum, strName) + strStream + ", " + strVarName + ")";

	SStruct* pStruct = GetStruct(strTypeName);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return strVarName + ".toStream(" + strStream + ")";
		else
			return strVarName + ".superToStream(" + strStream + ")";
	}

	pStruct = GetStruct(strTypeName, true);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return pStruct->strName + "::vectorToStream(" + strStream + ", " + strVarName + ")";
		else
			return pStruct->strName + "::superVectorToStream(" + strStream + ", " + strVarName + ")";
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
			return "ByteUtil::" + GetEnumWrite(*pEnum, strName) + strStream + ", " + strVarName + ")";
		pStruct = pDocument->GetStruct(rRefType.strTypeName);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return strVarName + ".toStream(" + strStream + ")";
			else
				return strVarName + ".superToStream(" + strStream + ")";
		}
		pStruct = pDocument->GetStruct(rRefType.strTypeName, true);
		if(pStruct != NULL)
		{
			string strNameSpace;
#ifdef PHP_USE_NAME_SPACE
			strNameSpace = "\\" + pDocument->_strNameSpace + "\\";
#endif
			if(!pStruct->bHasSub)
				return strNameSpace + pStruct->strName + "::vectorToStream(" + strStream + ", " + strVarName + ")";
			else
				return strNameSpace + pStruct->strName + "::superVectorToStream(" + strStream + ", " + strVarName + ")";
		}
	}

	cerr << "Invalid Ruby Write Expression For " << strTypeName << endl;
	return "Invalid Ruby Write Expression";
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

string CDocument::GetRubyReadExpr(const SElement& rElement, const string& strStream)
{
	static map<string, string> mapRubyExpr;
	char szBuf[0x100];
	if(mapRubyExpr.empty())
	{
		mapRubyExpr["INT8"] = "%s = ByteUtil::readINT8(%s)";
		mapRubyExpr["INT16"] = "%s = ByteUtil::readINT16(%s)";
		mapRubyExpr["INT32"] = "%s = ByteUtil::readINT32(%s)";
		mapRubyExpr["INT64"] = "%s = ByteUtil::readINT64(%s)";
		mapRubyExpr["UINT8"] = "%s = ByteUtil::readUINT8(%s)";
		mapRubyExpr["UINT16"] = "%s = ByteUtil::readUINT16(%s)";
		mapRubyExpr["UINT32"] = "%s = ByteUtil::readUINT32(%s)";
		mapRubyExpr["UINT64"] = "%s = ByteUtil::readUINT64(%s)";
		mapRubyExpr["float"] = "%s = ByteUtil::readFLOAT(%s)";
		mapRubyExpr["double"] = "%s = ByteUtil::readDOUBLE(%s)";
		mapRubyExpr["bool"] = "%s = ByteUtil::readBOOL(%s)";
		mapRubyExpr["string"] = "%s = ByteUtil::readSTRING(%s)";

		mapRubyExpr["TVecINT8"] = "%s = ByteUtil::readVecINT8(%s)";
		mapRubyExpr["TVecINT16"] = "%s = ByteUtil::readVecINT16(%s)";
		mapRubyExpr["TVecINT32"] = "%s = ByteUtil::readVecINT32(%s)";
		mapRubyExpr["TVecINT64"] = "%s = ByteUtil::readVecINT64(%s)";
		mapRubyExpr["TVecUINT8"] = "%s = ByteUtil::readVecUINT8(%s)";
		mapRubyExpr["TVecUINT16"] = "%s = ByteUtil::readVecUINT16(%s)";
		mapRubyExpr["TVecUINT32"] = "%s = ByteUtil::readVecUINT32(%s)";
		mapRubyExpr["TVecUINT64"] = "%s = ByteUtil::readVecUINT64(%s)";
		mapRubyExpr["TVecFloat"] = "%s = ByteUtil::readVecFLOAT(%s)";
		mapRubyExpr["TVecDouble"] = "%s = ByteUtil::readVecDOUBLE(%s)";
		mapRubyExpr["TVecBool"] = "%s = ByteUtil::readVecBOOL(%s)";
		mapRubyExpr["TVecString"] = "%s = ByteUtil::readVecSTRING(%s)";
	}
	const string& strName = rElement.strName;
	string strVarName;
	if(rElement.bIsMember)
		strVarName = "s." + strName;
	else
		strVarName = strName;
	const string& strTypeName = rElement.strTypeName;
	auto it = mapRubyExpr.find(strTypeName);
	if(it != mapRubyExpr.end())
	{
		const string& strExpr = it->second;
		sprintf_s(szBuf, strExpr.c_str(), strVarName.c_str(), strStream.c_str());
		return szBuf;
	}

	SEnum* pEnum = GetEnum(strTypeName);
	if(pEnum != NULL)
		return strVarName + " = ByteUtil::" + GetEnumRead(*pEnum) + strStream + ")";

	SStruct* pStruct = GetStruct(strTypeName);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return strVarName + " = " + strTypeName + "::fromStream(" + strStream + ")";
		else
			return strVarName + " = " + strTypeName + "::superFromStream(" + strStream + ")";
	}

	pStruct = GetStruct(strTypeName, true);
	if(pStruct != NULL)
	{
		if(!pStruct->bHasSub)
			return strVarName + " = " + pStruct->strName + "::vectorFromStream(" + strStream + ")";
		else
			return strVarName + " = " + pStruct->strName + "::superVectorFromStream(" + strStream + ")";
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
			return strVarName + " = ByteUtil::" + GetEnumRead(*pEnum) + strStream + ")";
		string strNameSpace;
#ifdef PHP_USE_NAME_SPACE
		strNameSpace = "\\" + pDocument->_strNameSpace + "\\";
#endif
		pStruct = pDocument->GetStruct(rRefType.strTypeName);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return strVarName + " = " + strNameSpace + pStruct->strName + "::fromStream(" + strStream + ")";
			else
				return strVarName + " = " + strNameSpace + pStruct->strName + "::superFromStream(" + strStream + ")";
		}
		pStruct = pDocument->GetStruct(rRefType.strTypeName, true);
		if(pStruct != NULL)
		{
			if(!pStruct->bHasSub)
				return strVarName + " = " + strNameSpace + pStruct->strName + "::vectorFromStream(" + strStream + ")";
			else
				return strVarName + " = " + strNameSpace + pStruct->strName + "::superVectorFromStream(" + strStream + ")";
		}
	}
	cerr << "Invalid Ruby Read Expression For " << strTypeName << endl;
	return "Invalid Ruby Read Expression";
}

void CDocument::PrintRubyRetParam(ostringstream& os, SFunc& rFunc)
{
	if(!rFunc.bReturn)
		return;
	os << "\t\tsessionID = @sessionMgr.getNewSession(self, " << -rFunc.iRetID << ");\n";
	if(rFunc.bKeepParam)
	{
		os << "\t\torigParam = SOrigParam_" << rFunc.strName << ".new\n";
		for(size_t i = 0, size = rFunc.vecParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecParam[i];
			if(rParam.bKeep)
				os << "\t\torigParam." << rParam.strName << " = " << rParam.strName << "\n";
		}
		for(size_t i = 0, size = rFunc.vecLocParam.size(); i < size; ++i)
		{
			SParam& rParam = rFunc.vecLocParam[i];
			os << "\t\torigParam.loc_" << rParam.strName << " = loc_" << rParam.strName << "\n";
		}
		os << "\t\t@sessionMgr.storeData(sessionID, origParam)\n";
	}
}

bool CDocument::GetRubyItemName(const string& strName, string& strRubyName, const SEnum* pCurEnum /*= NULL*/)
{
	SEnum* pEnum = NULL;
	SMember* pMember = GetEnumItem(strName, &pEnum);
	if(pMember != NULL && pEnum != NULL)
	{
		if(pEnum == pCurEnum)
			strRubyName = strName;
		else
			strRubyName = pEnum->strName + "::" + strName;
		return true;
	}
	else
	{
		SRefType* pRefType = GetRefEnumItem(strName, &pEnum, &pMember);
		if(pRefType != NULL && pEnum != NULL)
		{
			strRubyName = pEnum->strName + "::" + pRefType->strTypeName;
			return true;
		}
	}
	return false;
}

string CDocument::GetRubyComment(const string& strTypeName, const string& strComment)
{
	static map<string, string> mapRubyCmt;
	if(mapRubyCmt.empty())
	{
		mapRubyCmt["INT8"] = "INT8";
		mapRubyCmt["INT16"] = "INT16";
		mapRubyCmt["INT32"] = "INT32";
		mapRubyCmt["INT64"] = "INT64";
		mapRubyCmt["UINT8"] = "UINT8";
		mapRubyCmt["UINT16"] = "UINT16";
		mapRubyCmt["UINT32"] = "UINT32";
		mapRubyCmt["UINT64"] = "UINT64";
		mapRubyCmt["float"] = "float";
		mapRubyCmt["double"] = "double";
		mapRubyCmt["bool"] = "bool";
		mapRubyCmt["string"] = "string";

		mapRubyCmt["TVecINT8"] = "INT8数组";
		mapRubyCmt["TVecINT16"] = "INT16数组";
		mapRubyCmt["TVecINT32"] = "INT32数组";
		mapRubyCmt["TVecINT64"] = "INT64数组";
		mapRubyCmt["TVecUINT8"] = "UINT8数组";
		mapRubyCmt["TVecUINT16"] = "UINT16数组";
		mapRubyCmt["TVecUINT32"] = "UINT32数组";
		mapRubyCmt["TVecUINT64"] = "UINT64数组";
		mapRubyCmt["TVecFloat"] = "float数组";
		mapRubyCmt["TVecDouble"] = "double数组";
		mapRubyCmt["TVecBool"] = "bool数组";
		mapRubyCmt["TVecString"] = "string数组";
	}
	auto it = mapRubyCmt.find(strTypeName);
	if(it != mapRubyCmt.end())
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
	cerr << "Invalid Ruby Type For " << strTypeName << endl;
	return strComment;
}