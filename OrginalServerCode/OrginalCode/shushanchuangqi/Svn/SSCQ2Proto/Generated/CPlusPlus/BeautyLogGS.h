/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BeautyLogGS.h
//  Purpose:      美女log
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif
#include "ProtoCommon.h"

namespace NBeautyLogGS
{

/////////////////////以下为类型定义/////////////////////
//美女log
enum EBeautyLog
{
	eBeautyLog_Sucess = 0, //成功
	eBeautyLog_Error = 1 //失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBeautyLog);
bool EnumStrToVal(const char*, EBeautyLog&);
#endif //PROT_USE_XML
const char* GetDescription(EBeautyLog);

//美女log信息
struct SBeautyLog
{
	UINT64 qwUserID; //uid
	std::string strRoleName; //角色名
	UINT8 byColor; //角色颜色
	UINT16 wItemID; //物品id
	UINT32 dwCount; //物品数量

	SBeautyLog();
	SBeautyLog(UINT64 qwUserID_, const std::string& strRoleName_, UINT8 byColor_, UINT16 wItemID_, UINT32 dwCount_);
#ifdef __GNUG__
	SBeautyLog(const SBeautyLog& src) = default; //默认拷贝构造函数
	SBeautyLog& operator=(const SBeautyLog& rhs) = default; //默认赋值操作符
#endif
	SBeautyLog(SBeautyLog&& src); //转移构造函数
	SBeautyLog& operator=(SBeautyLog&& rhs); //转移赋值操作符
};

typedef std::vector<SBeautyLog> TVecBeautyLog;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SBeautyLog&);
COutArchive& operator<<(COutArchive&, const SBeautyLog&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SBeautyLog&);
bool ToXML(const SBeautyLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBeautyLog&);
bool VectorToXML(const TVecBeautyLog&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NBeautyLogGS
