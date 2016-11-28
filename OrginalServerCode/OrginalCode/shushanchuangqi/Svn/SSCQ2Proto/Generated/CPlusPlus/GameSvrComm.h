/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GameSvrComm.h
//  Purpose:      GameServer之间的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif

namespace NGameSvrComm
{

/////////////////////以下为类型定义/////////////////////
//测试结构体
struct STest
{
	UINT32 dwParam; //成员1

	STest();
	STest(UINT32 dwParam_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, STest&);
COutArchive& operator<<(COutArchive&, const STest&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, STest&);
bool ToXML(const STest&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGameSvrComm
