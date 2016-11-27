#ifndef _NULLCMD_H
#define _NULLCMD_H
#include "baseDef.h"

#pragma pack(1)
_CMD_NAMESPACE_BEGIN
const BYTE CMD_NULL = 0;
const BYTE PARA_NULL = 0;

struct NullCmd
{
	BYTE	byCmd;
	BYTE	byParam;
	NullCmd(const BYTE cmd = CMD_NULL,const BYTE para = PARA_NULL):byCmd(cmd),byParam(para)
	{
	}
};

const BYTE SERVER_PARA_NULL = 1;
struct ServerNullCmd : public NullCmd
{
	ServerNullCmd()
	{
		byCmd = CMD_NULL;
		byParam = SERVER_PARA_NULL;
	}
};
const BYTE CLIENT_PARA_NULL = 2;
struct ClientNullCmd : public NullCmd
{
	ClientNullCmd()
	{
		byCmd = CMD_NULL;
		byParam = CLIENT_PARA_NULL;
	}
};

const BYTE ZIP_CMD_PARA_NULL = 3;
struct ZipCmdPackNullCmd : public NullCmd
{
	ZipCmdPackNullCmd()
	{
		byCmd = CMD_NULL;
		byParam = ZIP_CMD_PARA_NULL;
		size = 0;
	}
	inline DWORD allSize()
	{
		return sizeof(*this) + size;
	}
	inline DWORD dataSize()
	{
		return size;
	}
	DWORD size;
	char data[0];
};

struct NullUserCmd : public NullCmd
{
	DWORD timeStamp;
};
struct DataSendCmd : public NullCmd
{
	DataSendCmd()
	{
		dwSize = 0;
	}
	DWORD datasize()
	{
		return dwSize;
	}
	DWORD allsize()
	{
		return sizeof(*this) + dwSize;
	}
	DWORD dwSize;
	BYTE data[0];
};

_CMD_NAMESPACE_END
#pragma pack()
#endif
