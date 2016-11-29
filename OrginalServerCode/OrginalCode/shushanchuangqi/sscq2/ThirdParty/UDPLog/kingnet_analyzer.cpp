
#include "kingnet_analyzer.h"
#include "udplog_config.h"
#include "udplog_lib.h"
#include <cstdio>

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

int32_t CKingnetAnalyzer::Init(const char* path/* = DEFAULT_CONFIGFILENAME*/)
{
	return _config.Init(path);
}

int32_t CUserLogger::LogMsg(const char *str1, const char *str2, const char *str3, const char *str4, const char *str5, const char *str6, const char *typeinfo/* = "login"*/, int32_t nCount/* = 1*/)
{
	if(NULL == str1 || NULL == str2 || NULL == str3 || NULL == str4 || NULL == str5 || NULL == str6 || NULL == typeinfo )
	{
		return E_FAIL;
	}
	int32_t type = _config.GetLogFileID(typeinfo);
	if(type < 0)
	{
		return E_FAIL;
	}
	m_szLogBuffer[MAX_LOG_LENGTH-1] = '\0';
	m_nTime		= (int32_t)time(NULL);

#ifndef WIN32
	snprintf(m_szLogBuffer,sizeof(m_szLogBuffer), "%s|%s|%s|%s|%s|%s|%d|%s|%d|%s",str1, str2, str3, str4, str5, str6, nCount,m_szUserIP, m_nTime, m_szUserMsg);
#else
	_snprintf(m_szLogBuffer,sizeof(m_szLogBuffer), "%s|%s|%s|%s|%s|%s|%d|%s|%d|%s",str1, str2, str3, str4, str5, str6, nCount,m_szUserIP, m_nTime,m_szUserMsg);
#endif
	
	SendUDPLog(m_nUid, type, m_szLogBuffer);

	return S_OK;
}

int32_t CUserLogger::SendUDPLog(int32_t uid, int32_t type, const char* msg)
{
	if(NULL == msg)
	{
		return E_FAIL;
	}

	int32_t ret = S_OK;
	stHost host;
	ret = _config.GetHostRandomly(host);
	if(ret < 0)
	{
		return ret;
	}
	CCSNotifyWriteLog body;
	body.m_nUid			= uid;
	body.m_nTableType	= type;

#ifndef WIN32
	strncpy(body.m_szLog, msg, MAX_LOG_LENGTH-1);
#else
	strncpy_s(body.m_szLog, sizeof(body.m_szLog), msg, strlen(msg));
#endif
	
	CCSHead head;
	head.m_nUid				= uid;
	head.m_nHeaderLength	= 30;//不包括打头的httphead

    head.m_nResourceID = _config.GetResourceID();
    
	char sendbuf[MAX_MESSAGE_LENGTH] = {0};
	
	uint32_t offset = 30 + 1;
	ret = body.Encode((uint8_t*)sendbuf, sizeof(sendbuf), offset);
	if(ret < 0)
	{
		return ret;
	}

	head.m_nPackageLength = offset - 1;
	offset = 0;

	ret = head.Encode((uint8_t*)sendbuf,sizeof(sendbuf),offset);
	if(ret < 0)
	{
		return ret;
	}

#ifndef WIN32
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));

	int32_t sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{
		return E_FAIL;
	}
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(host.nPort);
	if(inet_aton(host.szIP, &addr.sin_addr) < 0)
	{
		return E_FAIL;
	}
	if(sendto(sockfd, sendbuf, (size_t)(head.m_nPackageLength+1), 0, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
	{
		return E_FAIL;
	}
	close(sockfd);
#endif

	return S_OK;
}

