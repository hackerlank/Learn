#include "udplog_lib.h"
#include "udplog_codeengine.h"
#include "time.h"

CCSNotifyWriteLog::CCSNotifyWriteLog()
{
	m_nUid			= 0;
	m_nTableType	= 0;
	m_szLog[0]		= '\0';
}

CCSNotifyWriteLog::~CCSNotifyWriteLog()
{
}

int32_t CCSNotifyWriteLog::Encode(uint8_t *buf, uint32_t size, uint32_t &offset)
{
	int32_t ret = S_OK;
	ret = CCodeEngine::Encode(buf, size, offset, m_nUid);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nTableType);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_szLog, sizeof(m_szLog));
	if(ret < 0)
	{
		return ret;
	}

	return S_OK;
}
int32_t CCSNotifyWriteLog::Decode(const uint8_t *buf, const uint32_t size, uint32_t &offset)
{
	int32_t ret = S_OK;
	ret = CCodeEngine::Decode(buf, size, offset, m_nUid);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nTableType);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_szLog, sizeof(m_szLog));
	if(ret < 0)
	{
		return ret;
	}
	return S_OK;
}

int32_t CCSNotifyWriteLog::Dump(char *buf, const uint32_t size, uint32_t &offset)
{
	return S_OK;
}

CCSHead::CCSHead()
{
	m_nHttpHead			= 0;
	m_nPackageLength	= 0;
	m_nUid				= 0;
	m_nFlag				= 0;
	m_nOptionLength		= 0;
	m_szOption[0]		= '\0';
	m_nHeaderLength		= 0;
	m_nMessageID		= 0x10;
	m_nMessageType		= 0x03;
	m_nVersionType		= 0x03;
	m_nVersion			= 0;
	m_nResourceID			= -1;
	m_nSendTime			= (int32_t)time(NULL);
}

CCSHead::~CCSHead()
{
}
int32_t CCSHead::Encode(uint8_t *buf, uint32_t size, uint32_t &offset)
{
	int32_t ret = S_OK;
	ret = CCodeEngine::Encode(buf, size, offset, m_nHttpHead);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nPackageLength);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nUid);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nFlag);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nOptionLength);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_szOption, m_nOptionLength, sizeof(m_szOption));
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nHeaderLength);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nMessageID);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nMessageType);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nVersionType);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nVersion);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nResourceID);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Encode(buf, size, offset, m_nSendTime);
	if(ret < 0)
	{
		return ret;
	}
  
	return S_OK;
}
int32_t CCSHead::Decode(const uint8_t *buf, const uint32_t size, uint32_t &offset)
{
	int32_t ret = S_OK;
	ret = CCodeEngine::Decode(buf, size, offset, m_nHttpHead);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nPackageLength);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nUid);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nFlag);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nOptionLength);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_szOption, m_nOptionLength, sizeof(m_szOption));
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nHeaderLength);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nMessageID);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nMessageType);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nVersionType);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nVersion);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nResourceID);
	if(ret < 0)
	{
		return ret;
	}
	ret = CCodeEngine::Decode(buf, size, offset, m_nSendTime);
	if(ret < 0)
	{
		return ret;
	}

	return S_OK;
}

int32_t CCSHead::Dump(char *buf, const uint32_t size, uint32_t &offset)
{
	return S_OK;
}
