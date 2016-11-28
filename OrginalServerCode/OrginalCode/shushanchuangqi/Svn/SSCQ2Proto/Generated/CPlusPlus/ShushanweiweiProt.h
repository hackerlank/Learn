/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShushanweiweiProt.h
//  Purpose:      蜀山微微协议
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

namespace NShushanweiweiProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EPkgResult
{
	ePackError, //错误
	ePackGain, //已经领取
	ePackFull, //背包已满
	ePackSuccess //成功
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPkgResult);
bool EnumStrToVal(const char*, EPkgResult&);
#endif //PROT_USE_XML

//领奖类型
enum EPkgType
{
	eWeibo = 0, //微博
	eWeixin = 1, //微信
	eMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPkgType);
bool EnumStrToVal(const char*, EPkgType&);
#endif //PROT_USE_XML

//奖励信息
struct SPrizeInfo
{
	EPkgType eType; //奖励类型
	UINT32 dwCount; //当前人数
	bool bListen; //微博是否收听
	bool bResult; //个人奖励是否领取
	UINT16 wResult; //全服奖励领取结果

	SPrizeInfo();
	SPrizeInfo(EPkgType eType_, UINT32 dwCount_, bool bListen_, bool bResult_, UINT16 wResult_);
};

typedef std::vector<SPrizeInfo> TVecPrizeInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SPrizeInfo&);
COutArchive& operator<<(COutArchive&, const SPrizeInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SPrizeInfo&);
bool ToXML(const SPrizeInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrizeInfo&);
bool VectorToXML(const TVecPrizeInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NShushanweiweiProt
