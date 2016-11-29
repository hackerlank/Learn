/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ServerCommon.h
//  Purpose:      服务器通用类型定义
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

namespace NServerCommon
{

/////////////////////以下为类型定义/////////////////////
//下线的类型
enum ELeaveType
{
	eLeaveNone, //无
	eLeaveAway, //正常下线
	eLeaveReplace, //替换帐号
	eLeaveJump, //跳服
	eLeaveKick, //被踢
	eIndulgeKick, //防沉迷系统已启动，请休息5小时
	eIndulgeTimeKick, //防沉迷离线不足5小时，请休息5小时
	eLeaveExcept //异常
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELeaveType);
bool EnumStrToVal(const char*, ELeaveType&);
#endif //PROT_USE_XML
const char* GetDescription(ELeaveType);

//帐号信息请求类型
enum EUserReqType
{
	eUserReqNone, //无
	eUserReqMail, //邮件
	eUserReqShopMall, //商城
	eUserReqFriend, //好友查询
	eUserReqVIP //赠送VIP
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EUserReqType);
bool EnumStrToVal(const char*, EUserReqType&);
#endif //PROT_USE_XML

//账号ID,Name数据
struct SUsrIDNameData
{
	UINT64 qwUsrID; //账号ID
	std::string strName; //主英雄名
	UINT8 byLevel; //等级
	UINT8 byJob; //职业

	SUsrIDNameData();
	SUsrIDNameData(UINT64 qwUsrID_, const std::string& strName_, UINT8 byLevel_, UINT8 byJob_);
#ifdef __GNUG__
	SUsrIDNameData(const SUsrIDNameData& src) = default; //默认拷贝构造函数
	SUsrIDNameData& operator=(const SUsrIDNameData& rhs) = default; //默认赋值操作符
#endif
	SUsrIDNameData(SUsrIDNameData&& src); //转移构造函数
	SUsrIDNameData& operator=(SUsrIDNameData&& rhs); //转移赋值操作符
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SUsrIDNameData&);
COutArchive& operator<<(COutArchive&, const SUsrIDNameData&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SUsrIDNameData&);
bool ToXML(const SUsrIDNameData&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NServerCommon
