/********************************************************************
//	Server Common Library Source File.
//	File name:	ServerID.cpp
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

#include "ServerID.h"
#include "UtilFunc.h"

UINT32 GetServerID(UINT16 wGroupID, EHostType eSvrType, UINT8 bySvrIndex)
{
	UINT32 dwSvrID = 0;
	*((UINT16*)&dwSvrID + 1) = wGroupID;
	*((UINT8*)&dwSvrID + 1) = (UINT8)eSvrType;
	*(UINT8*)&dwSvrID = bySvrIndex;
	return dwSvrID;
}

UINT16 GetServerGroup(UINT32 dwSvrID)
{
	return *((UINT16*)&dwSvrID + 1);
}

EHostType GetServerType(UINT32 dwSvrID)
{
	return (EHostType)*((UINT8*)&dwSvrID + 1);
}

UINT8 GetServerIndex(UINT32 dwSvrID)
{
	return (UINT8)dwSvrID;
}

static EHostType arServerType[] = 
{
	eHostGate,
	eHostLogin,
	eHostCenter,
	eHostGame,
	eHostDB,
	eHostLog,
	eHostControl,
	eHostClient,
	eHostNone
};

static const char* arServerName[] = {
	"GateServer",
	"LoginServer",
	"CenterServer",
	"GameServer",
	"DBServer",
	"LogServer",
	"ControlClient",
	"Client",
	NULL
};

static const char* arShortName[] = {
	"GT",
	"LG",
	"CT",
	"GS",
	"DB",
	"LS",
	"CR",
	"CL",
	NULL
};

EHostType GetServerType(const char* pServerName)
{
	int index = 0;
	while(arServerName[index] != NULL)
	{
		if(strstr(pServerName, arServerName[index]) != NULL)
			break;
		++index;
	}
	return arServerType[index];
}

const char* GetServerName(EHostType eHostType)
{
	int index = 0;
	while(arServerType[index] != eHostNone)
	{
		if(eHostType == arServerType[index])
			return arServerName[index];
		++index;
	}
	return "Unknown";
}

const char* GetServerShortName(EHostType eHostType)
{
	int index = 0;
	while(arServerType[index] != eHostNone)
	{
		if(eHostType == arServerType[index])
			return arShortName[index];
		++index;
	}
	return "Unknown";
}

std::string GetServerInfo(UINT32 dwSvrID)
{
	string strInfo;
	const char* pszName = GetServerName(GetServerType(dwSvrID));
	if(pszName != NULL)
		strInfo += pszName;
	strInfo += NumberToString(GetServerIndex(dwSvrID));
	return move(strInfo);
}

std::string GetServerDesc(UINT32 dwSvrID)
{
	string strDesc = "[Group:" + NumberToString(GetServerGroup(dwSvrID)) + ", Server: " +
		GetServerName(GetServerType(dwSvrID)) + ", Index: " + NumberToString(GetServerIndex(dwSvrID)) + "]";
	return move(strDesc);
}
