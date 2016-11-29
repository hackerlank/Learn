/********************************************************************
//	Server Common Library Source File.
//	File name:	ServerID.h
//	Created:	2012/08/21	10:00
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
#pragma once
#include <string>
#include "Interface.h"

//获取服务器ID，组成部分：[16位的组(区)编号, 8位的主机类型, 8位的在同类服务器中的编号]
UINT32 GetServerID(UINT16 wGroupID, EHostType eSvrType, UINT8 bySvrIndex);

//获取服务器组编号
UINT16 GetServerGroup(UINT32 dwSvrID);

//获取服务器的主机类型
EHostType GetServerType(UINT32 dwSvrID);

//获取服务器编号
UINT8 GetServerIndex(UINT32 dwSvrID);

//根据服务器名获得主机类型
EHostType GetServerType(const char* pServerName);

//根据主机类型获得服务器名
const char* GetServerName(EHostType eHostType);

//根据主机类型获得服务器的缩写名
const char* GetServerShortName(EHostType eHostType);

//获得服务器ID中包含的信息字符串
std::string GetServerInfo(UINT32 dwSvrID);

//获得服务器的信息
std::string GetServerDesc(UINT32 dwSvrID);
