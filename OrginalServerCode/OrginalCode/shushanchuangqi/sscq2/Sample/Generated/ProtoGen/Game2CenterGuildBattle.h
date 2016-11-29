/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterGuildBattle.h
//  Purpose:      帮派战相关协议
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
#include "GuildBattleProt.h"
#include "NewGuildBattleProt.h"

namespace NGame2CenterGuildBattle
{

/////////////////////以下为类型定义/////////////////////
//帮派战玩家分数信息
struct SMemberScore
{
	UINT64 qwRoleID; //成员角色ID
	UINT32 dwScore; //积分

	SMemberScore();
	SMemberScore(UINT64 qwRoleID_, UINT32 dwScore_);
};

typedef std::vector<SMemberScore> TVecMemberScore;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SMemberScore&);
COutArchive& operator<<(COutArchive&, const SMemberScore&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SMemberScore&);
bool ToXML(const SMemberScore&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMemberScore&);
bool VectorToXML(const TVecMemberScore&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGame2CenterGuildBattle
