/********************************************************************
//	Server Network Library Source File.
//	File name:	Exception.cpp
//	Created:	2012/08/24	11:00
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ucontext.h>
#include <execinfo.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include "Linux.h"
#include "GlobalDefine.h"
#include "Exception.h"
#include "EPollMgr.h"
#include "Directory.h"
#include "CallStack.h"
#include "ServerID.h"
#include "Config.h"

#define gettid() syscall(__NR_gettid)
#define BACKSTACK_DEPTH 100

static void ExLog(const char* fmt, ...)
{
	char arBuf[0x1000];
	time_t tNow = time(NULL);
	tm tmNow;
	localtime_r(&tNow, &tmNow);
	int offset = snprintf(arBuf, sizeof arBuf, "[%02u:%02u:%02u]Crash:\n", tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec);
	if(offset < 0)
		return;
	va_list args;
	va_start(args, fmt);
	offset += vsnprintf(arBuf + offset, sizeof arBuf - offset, fmt, args);
	va_end(args);
	if(offset < 0)
		return;
	write(STDOUT_FILENO, arBuf, static_cast<UINT32>(offset) < sizeof(arBuf) ? offset : sizeof(arBuf));
}

struct sig_ucontext_t
{
	unsigned long uc_flags;
	ucontext* uc_link;
	stack_t uc_stack;
	sigcontext uc_mcontext;
	sigset_t uc_sigmask;
};

jmp_buf CException::_env;

extern "C" void sigbreak(int sig)
{
	ExLog("%s is terminated!\n", GetServerName(CEPollMgr::Instance().GetServerType()));
    CConfig::GetConfig()->Shutdown();
    LOG_CRI << __PRETTY_FUNCTION__;
    LOG_INF << __PRETTY_FUNCTION__;
    PRINT_CALL_STACK;
}

bool CException::Init()
{
#if 0
	struct sigaction oActExcept;
	oActExcept.sa_sigaction = HandleException;
	sigemptyset(&oActExcept.sa_mask);
	oActExcept.sa_flags = SA_RESTART | SA_SIGINFO;

	if(sigaction(SIGSEGV, &oActExcept, (struct sigaction*)NULL) != 0)
	{
		LOG_CRI << "error setting signal handler for " << SIGSEGV << " (" << strsignal(SIGSEGV) << ")";
		return false;
	}

	if(sigaction(SIGABRT, &oActExcept, (struct sigaction*)NULL) != 0)
	{
		LOG_CRI << "error setting signal handler for " << SIGABRT << " (" << strsignal(SIGABRT) << ")";
		return false;
	}

	signal(SIGPIPE, SIG_IGN);

	struct sigaction oActTerm;
	oActTerm.sa_sigaction = HandleTerm;
	sigemptyset(&oActTerm.sa_mask);
	oActTerm.sa_flags = SA_RESTART | SA_SIGINFO;

	if(sigaction(SIGTERM, &oActTerm, (struct sigaction*)NULL) != 0)
	{
		LOG_CRI << "error setting signal handler for " << SIGTERM << " (" << strsignal(SIGTERM) << ")";
		return false;
	}
#else
#ifndef SIGBREAK
#define SIGBREAK 21
#endif
    signal(SIGABRT, &sigbreak);
    signal(SIGINT, &sigbreak);
    signal(SIGTERM, &sigbreak);
    signal(SIGBREAK, &sigbreak);
	signal(SIGPIPE, SIG_IGN);
#endif
	return true;
}

static void DumpCoreImpl()
{
	rlimit limit;
	if(getrlimit(RLIMIT_CORE, &limit) < 0)
		ExLog("getrlimit fails! error: %d\n", errno);
	else
		ExLog("cur: %d, max: %d\n", limit.rlim_cur, limit.rlim_max);
	limit.rlim_cur = limit.rlim_max = RLIM_INFINITY;
	if(setrlimit(RLIMIT_CORE, &limit) < 0)
		ExLog("setrlimit fails! error: %d\n", errno);
}

static void DumpStack()
{
	char szBuf[0x100];
	int rc = readlink("/proc/self/exe", szBuf, sizeof szBuf);
	if(rc < 0)
	{
		strerror_r(errno, szBuf, sizeof szBuf);
		ExLog("%s\n", szBuf);
		return;
	}
	szBuf[rc] = '\0';
	int i = rc - 1;
	for(; i > 0; --i)
	{
		if(szBuf[i] == '/')
		{
			szBuf[i] = '\0';
			break;
		}
	}
	if(i == 0)
	{
		ExLog("Can't find current directory path!\n");
		return;
	}
	int offset = sprintf(szBuf + i, "/Crash");
	if(offset < 0)
	{
		ExLog("sprintf offset: %d\n", offset);
		return;
	}
	offset += (int)i;
	if(mkdir(szBuf, 0777) != 0 && errno != EEXIST)
	{
		strerror_r(errno, szBuf, sizeof szBuf);
		ExLog("%s\n", szBuf);
		return;
	}
	time_t tNow = time(NULL);
	tm oTime;
	localtime_r(&tNow, &oTime);
	sprintf(szBuf + offset, "/Stack_%u-%02u-%02u_%02u-%02u.txt", oTime.tm_year + 1900, oTime.tm_mon + 1, oTime.tm_mday, oTime.tm_hour, oTime.tm_min);
	int fd = open(szBuf, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd < 0)
	{
		strerror_r(errno, szBuf, sizeof szBuf);
		ExLog("%s\n", szBuf);
		return;
	}
	void* buffer[BACKSTACK_DEPTH];
	int size = backtrace(buffer, BACKSTACK_DEPTH);
	backtrace_symbols_fd(buffer, size, fd);
	close(fd);
}

#define MAX_DUMP_COUNT 100

void CException::HandleException(int sig, siginfo_t* pInfo, void* context)
{
	static bool bCoreDumped;
	if(bCoreDumped)
		return;
	bCoreDumped = true;

	sig_ucontext_t* pContext = (sig_ucontext_t*)context;
	void* pCallerAddress = (void*)pContext->uc_mcontext.rip;

	static void* arDumpedAddress[MAX_DUMP_COUNT];
	static UINT8 arDumpedCount[MAX_DUMP_COUNT];
	size_t index = 0;
	bool bDump = false;
	for(; index < ARRAYSIZE(arDumpedAddress) && arDumpedAddress[index] != NULL; ++index)
	{
		if(arDumpedAddress[index] == pCallerAddress)
		{
			if(arDumpedCount[index] < 3)
			{
				++arDumpedCount[index];
				bDump = true;
			}
			break;
		}
	}
	if(!bDump && index < ARRAYSIZE(arDumpedAddress) && arDumpedAddress[index] == NULL)
	{
		arDumpedAddress[index] = pCallerAddress;
		++arDumpedCount[index];
		bDump = true;
	}

	ExLog("signal %d (%s), address is %p from %p\n", sig, strsignal(sig), pInfo->si_addr, pCallerAddress);
	if(bDump)
	{
		DumpStack();
		char szBuf[0x1000];
		memset(szBuf, 0, sizeof szBuf);
		GetCallStack(pCallerAddress, szBuf, sizeof szBuf);
		ExLog("%s\n", szBuf);
	}
	if(sig == SIGSEGV)
	{
		if(bDump)
		{
			if(DumpCore() == -1)
				exit(EXIT_FAILURE);
			else
				wait(NULL);
		}
#ifdef ROBUST_USER_LOGIC
		CEPollMgr::Instance().OnExceptionCallback(NetInterface::eExceptCrash);
		bCoreDumped = false;
		siglongjmp(_env, 1);
#else
		exit(EXIT_FAILURE);
#endif
	}
	else
	{
		if(bDump)
		{
			struct sigaction act;
			act.sa_handler = SIG_IGN;
			sigemptyset(&act.sa_mask);
			sigaction(SIGABRT, &act, (struct sigaction*)NULL);
			DumpCoreImpl();
		}
		exit(EXIT_FAILURE);
	}
}

void CException::HandleTerm(int sig, siginfo_t* pInfo, void* context)
{
	//RecordExit(true);
	ExLog("%s is terminated!\n", GetServerName(CEPollMgr::Instance().GetServerType()));
    CConfig::GetConfig()->Shutdown();
}

pid_t CException::DumpCore()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		struct sigaction act;
		act.sa_handler = SIG_IGN;
		sigemptyset(&act.sa_mask);
		sigaction(SIGABRT, &act, (struct sigaction*)NULL);
		DumpCoreImpl();
		abort();
	}
	return pid;
}

void CException::RecordExit(bool bKill)
{
	char szBuf[0x100];
	int rc = readlink("/proc/self/exe", szBuf, sizeof szBuf);
	if(rc < 0)
	{
		strerror_r(errno, szBuf, sizeof szBuf);
		printf("%s\n", szBuf);
		return;
	}
	szBuf[rc] = '\0';
	int i = rc - 1;
	for(; i > 0; --i)
	{
		if(szBuf[i] == '/')
		{
			szBuf[i] = '\0';
			break;
		}
	}
	if(i == 0)
	{
		printf("Can't find current directory path!\n");
		return;
	}
	int offset = sprintf(szBuf + i, "/NetLog/ExitLog.txt");
	if(offset < 0)
	{
		printf("sprintf fails for file name! offset: %d\n", offset);
		return;
	}
	offset += i;
	int fd = open(szBuf, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd < 0)
	{
		strerror_r(errno, szBuf, sizeof szBuf);
		printf("open fails! path: %s\n", szBuf);
		return;
	}
	time_t tNow = time(NULL);
	tm oTime;
	localtime_r(&tNow, &oTime);
	const char* pszSvrName = GetServerName(CNetIFMgr::Instance().GetServerType());
	offset = sprintf(szBuf, "%s %s time: %u-%02u-%02u %02u:%02u:%02u\n", pszSvrName, bKill ? "kill" : "shutdown",
		oTime.tm_year + 1900, oTime.tm_mon + 1, oTime.tm_mday, oTime.tm_hour, oTime.tm_min, oTime.tm_sec);
	if(offset < 0)
		printf("sprintf fails for shutdown time! offset: %d\n", offset);
	else
        write(fd, szBuf, static_cast<UINT32>(offset) < sizeof(szBuf) ? offset : sizeof(szBuf));
	close(fd);
}
