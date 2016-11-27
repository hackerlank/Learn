#ifndef _START_COMMAND_H
#define _START_COMMAND_H

#include "common/nullCmd.h"

#pragma pack(1)
enum ServerType
{
	UNKNOWNSERVER  = 0,       //未知服务器
	SUPERSERVER    = 1,       //管理服
	RECORDSERVER   = 2,       //档案服
	SESSIONSERVER  = 3,       //会话服务器
	SCENESERVER   = 4,       //场景服务器
	GATEWAYSERVER  = 5,       //网关服务器
	PLATESERVER    = 6,       //平台服务器
};

struct ServerTypeStruct
{
	ServerTypeStruct( const ServerType _type = UNKNOWNSERVER,const char *_name = NULL )
	{
		bzero(this,sizeof(*this));
		type = _type;
		if(_name) 
		{
			strncpy(name,_name,sizeof(name));
		}
	}
	ServerType type;
	char name[MAX_NAMESIZE];
};

static ServerTypeStruct ServerTypeString[] = 
{
	ServerTypeStruct( UNKNOWNSERVER,"未知服务器" ),
	ServerTypeStruct( SUPERSERVER,"管理服务器" ),
	ServerTypeStruct( RECORDSERVER,"档案服务器" ),
	ServerTypeStruct( SESSIONSERVER,"会话服务器" ),
	ServerTypeStruct( SCENESERVER,"场景服务器" ),
	ServerTypeStruct( GATEWAYSERVER,"网关服务器" ),
	ServerTypeStruct( PLATESERVER,"平台服务器" ),
};

inline const char* getServerTypeString( const ServerType type )
{
	size_t count = sizeof( ServerTypeString ) / sizeof( ServerTypeStruct );
	for( size_t index = 0;index < count;++index )
	{
		if( ServerTypeString[index].type == type )
		{
			return ServerTypeString[index].name;
		}
	}
	return ServerTypeString[0].name;
}
struct ServerEntry
{
	WORD serverID;
	WORD serverType;
	char name[MAX_NAMESIZE];
	char ip[MAX_IP_LENGTH];
	WORD port;
	char outNetIP[MAX_IP_LENGTH];
	WORD outNetPort;
	WORD state;
	WORD netType;
	ServerEntry()
	{
		bzero(this,sizeof(*this));
	}
	ServerEntry(const ServerEntry &serverEntry)
	{
		serverID = serverEntry.serverID;
		serverType = serverEntry.serverType;
		strncpy( name,serverEntry.name,sizeof( name ) );
		strncpy( ip,serverEntry.ip,sizeof( ip ) );
		port = serverEntry.port;
		strncpy( outNetIP,serverEntry.outNetIP,sizeof( outNetIP ) );
		outNetPort = serverEntry.outNetPort;
		state = serverEntry.state;
		netType = serverEntry.netType;
	}
	ServerEntry& operator= ( const ServerEntry &serverEntry )
	{
		serverID = serverEntry.serverID;
		serverType = serverEntry.serverType;
		strncpy( name,serverEntry.name,sizeof( name ) );
		strncpy( ip,serverEntry.ip,sizeof( ip ) );
		port = serverEntry.port;
		strncpy( outNetIP,serverEntry.outNetIP,sizeof( outNetIP ) );
		outNetPort = serverEntry.outNetPort;
		state = serverEntry.state;
		netType = serverEntry.netType;
		return *this;
	}
};

#define _USE_CMD_SERVER_NAMESPACE namespace Cmd { namespace Server{
#define _CMD_SERVER_NAMESPACE_END };};
_USE_CMD_SERVER_NAMESPACE 

const BYTE START_SERVERCMD     = 255;
const BYTE FORWARD_SERVERCMD   = 254;
struct StartServerCmd : public NullCmd
{
	StartServerCmd()
	{
		byCmd = START_SERVERCMD;
	}
};

const BYTE LOGIN_START_SERVERCMD_PARA = 1;
struct LoginStartServerCmd : public StartServerCmd
{
	WORD serverID;
	DWORD serverType;
	char ip[MAX_IP_LENGTH];
	LoginStartServerCmd()
	{
		byParam = LOGIN_START_SERVERCMD_PARA;
		serverID = 0;
		serverType = 0;
		bzero(ip,sizeof(ip));
	}
};

/// @brief 向管理服务器请求启动
const BYTE REQUEST_START_SERVERCMD_PARA = 2;
struct RequestStartServerCmd : public StartServerCmd
{
	RequestStartServerCmd()
	{
		byParam = REQUEST_START_SERVERCMD_PARA;
		serverType = 0;
		protocol = 0;
		buildTime = 0;
		svnVersion = 0;
		bzero( ip,sizeof( ip ) );
	}
	DWORD serverType;
	char ip[MAX_IP_LENGTH];
	DWORD protocol;
	DWORD buildTime;
	DWORD svnVersion;
};
const BYTE RESPONSE_START_SERVERCMD_PARA = 3;
struct ResponseStartServerCmd : public StartServerCmd
{
	WORD serverID;
	WORD port;
	char outIp[MAX_IP_LENGTH];
	WORD outPort;
	WORD netType;
	ResponseStartServerCmd()
	{
		byParam = RESPONSE_START_SERVERCMD_PARA;
		serverID = 0;
		port = 0;
		outPort = 0;
		netType = 0;
		bzero(outIp,sizeof(outIp));
	}
};

const BYTE NOTIFY_OTHER_SERVERCMD_PARA = 4;
struct NotifyOtherServer : public StartServerCmd
{
	ServerEntry entry;
	NotifyOtherServer()
	{
		byParam = NOTIFY_OTHER_SERVERCMD_PARA;
	}
};

const BYTE NOTIFY_ME_SERVERCMD_PARA = 5;
struct NotifyMeServer : public StartServerCmd
{
	WORD size;
	ServerEntry entry[0];
	NotifyMeServer()
	{
		byParam = NOTIFY_ME_SERVERCMD_PARA;
		size = 0;
	}
	DWORD allSize() const
	{
		return sizeof(*this) + size * sizeof(ServerEntry);
	}
};

const BYTE OK_START_SERVERCMD_PARA = 6;
struct OkStartServerCmd : public StartServerCmd
{
	WORD serverID;
	OkStartServerCmd()
	{
		byParam = OK_START_SERVERCMD_PARA;
		serverID = 0;
	}
};

const BYTE OK_START_RETURN_SERVERCMD_PARA = 7;
struct OkStartReturnServerCmd : public StartServerCmd
{
	OkStartReturnServerCmd()
	{
		byParam = OK_START_RETURN_SERVERCMD_PARA;
	}
};




_CMD_SERVER_NAMESPACE_END

#pragma pack()
#endif




