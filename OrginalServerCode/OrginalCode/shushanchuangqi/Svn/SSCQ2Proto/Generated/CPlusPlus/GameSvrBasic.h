/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GameSvrBasic.h
//  Purpose:      GameServer的基本协议
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

namespace NGameSvrBasic
{

/////////////////////以下为类型定义/////////////////////
//断开原因
enum EBreakReason
{
	eBreakNone, //无
	eBreakUsrKick, //被另一处登录的帐号踢下线
	eBreakSvrKick, //被服务器踢下线
	eBreakExcept, //发生异常
	eBreakOther, //其它原因
	eBreakIndulgeKick, //防沉迷系统已启动，请休息5小时
	eBreakIndulgeTimeKick //防沉迷系统已启动，请休息完5小时后登陆
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBreakReason);
bool EnumStrToVal(const char*, EBreakReason&);
#endif //PROT_USE_XML

//GM命令
struct SGMCommand
{
	std::string strCmd; //命令
	std::string strName; //名称
	std::string strDesc; //描述

	SGMCommand();
	SGMCommand(const std::string& strCmd_, const std::string& strName_, const std::string& strDesc_);
#ifdef __GNUG__
	SGMCommand(const SGMCommand& src) = default; //默认拷贝构造函数
	SGMCommand& operator=(const SGMCommand& rhs) = default; //默认赋值操作符
#endif
	SGMCommand(SGMCommand&& src); //转移构造函数
	SGMCommand& operator=(SGMCommand&& rhs); //转移赋值操作符
};

typedef std::vector<SGMCommand> TVecGMCommand;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SGMCommand&);
COutArchive& operator<<(COutArchive&, const SGMCommand&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SGMCommand&);
bool ToXML(const SGMCommand&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGMCommand&);
bool VectorToXML(const TVecGMCommand&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGameSvrBasic
