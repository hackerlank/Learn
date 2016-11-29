/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Center2DBGuild.h
//  Purpose:      CenterServer到DBServer有关帮派的通信协议
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
#include "GuildProt.h"
#include "ProtoCommon.h"

namespace NCenter2DBGuild
{

/////////////////////以下为类型定义/////////////////////
//帮派神像供奉人数信息
struct SGSWorshipInfo
{
	UINT64 qwGuildID; //帮派ID
	UINT8 byWorshipCount; //供奉人数
	TVecUINT64 vecMemberID; //帮派成员ID

	SGSWorshipInfo();
	SGSWorshipInfo(UINT64 qwGuildID_, UINT8 byWorshipCount_, const TVecUINT64& vecMemberID_);
};

typedef std::vector<SGSWorshipInfo> TVecGSWorshipInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SGSWorshipInfo&);
COutArchive& operator<<(COutArchive&, const SGSWorshipInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SGSWorshipInfo&);
bool ToXML(const SGSWorshipInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGSWorshipInfo&);
bool VectorToXML(const TVecGSWorshipInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NCenter2DBGuild
