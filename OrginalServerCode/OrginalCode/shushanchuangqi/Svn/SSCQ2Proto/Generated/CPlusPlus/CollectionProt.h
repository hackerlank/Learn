/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    CollectionProt.h
//  Purpose:      收藏协议
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

namespace NCollectionProt
{

/////////////////////以下为类型定义/////////////////////
//EDataType:eTypeCollectionInfo
struct SCollectionInfo
{
	UINT64 qwRoleID; //角色ID
	UINT16 wCollectionID; //收藏ID
	UINT32 dwCount; //0是否完成
	UINT32 dwProcess; //当前进度(持续型事件记录数据)
	UINT32 dwFinishTime; //完成时间

	SCollectionInfo();
	SCollectionInfo(UINT64 qwRoleID_, UINT16 wCollectionID_, UINT32 dwCount_, UINT32 dwProcess_, UINT32 dwFinishTime_);
};

typedef std::vector<SCollectionInfo> TVecCollectionInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SCollectionInfo&);
COutArchive& operator<<(COutArchive&, const SCollectionInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SCollectionInfo&);
bool ToXML(const SCollectionInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCollectionInfo&);
bool VectorToXML(const TVecCollectionInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NCollectionProt
