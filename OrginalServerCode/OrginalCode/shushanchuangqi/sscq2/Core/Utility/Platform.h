#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <assert.h>
#else
#include <Linux.h>
#include <LinuxTime.h>
#endif
#include <stdio.h>

#ifdef _WIN32
#define StrToINT64 _strtoi64
#define StrToUINT64 _strtoui64
#define strcasecmp _stricmp
#pragma warning(disable:4996)
#define snprintf _snprintf
#else
#define StrToINT64 strtoll
#define StrToUINT64 strtoull
#endif

#define __BEGIN extern "C" {
#define __END }

// hardware macros
#if defined(__i386__) || defined(i386) || \
    defined(_X86_) || \
    defined(_M_IX86) || \
    defined(_WIN32)
#   define CPU_X86 1
#endif

#if defined(__x86_64__) || \
    defined(__amd64__) || defined(__amd64) || \
    defined(_WIN64)
#   define CPU_X64 1
#endif

#define SMP 1

#define _OS_FREE_BSD      0x0001
#define _OS_LINUX         0x0005
#define _OS_MAC_OS_X      0x0006
#define _OS_NET_BSD       0x0007
#define _OS_OPEN_BSD      0x0008
#define _OS_CYGWIN        0x000d
#define _OS_UNKNOWN_UNIX  0x00ff
#define _OS_WINDOWS_NT    0x1001

#if defined(__FreeBSD__)
#   define _OS_FAMILY_UNIX 1
#   define _OS_FAMILY_BSD 1
#   define _OS _OS_FREE_BSD
#   define UNIXLIKE 1
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
#   define _OS_FAMILY_UNIX 1
#   define _OS _OS_LINUX
#   define UNIXLIKE 1
#elif defined(__APPLE__) || defined(__TOS_MACOS__)
#   define _OS_FAMILY_UNIX 1
#   define _OS_FAMILY_BSD 1
#   define _OS _OS_MAC_OS_X
#   define UNIXLIKE 1
#elif defined(__NetBSD__)
#   define _OS_FAMILY_UNIX 1
#   define _OS_FAMILY_BSD 1
#   define _OS _OS_NET_BSD
#   define UNIXLIKE 1
#elif defined(__OpenBSD__)
#   define _OS_FAMILY_UNIX 1
#   define _OS_FAMILY_BSD 1
#   define _OS _OS_OPEN_BSD
#   define UNIXLIKE 1
#elif defined(unix) || defined(__unix) || defined(__unix__)
#   define _OS_FAMILY_UNIX 1
#   define _OS _OS_UNKNOWN_UNIX
#   define UNIXLIKE 1
#elif defined(_WIN32) || defined(_WIN64)
#   define _OS_FAMILY_WINDOWS 1
#   define _OS _OS_WINDOWS_NT
#   define WINDOWS 1
#elif defined(__CYGWIN__)
#   define _OS_FAMILY_UNIX 1
#   define _OS _OS_CYGWIN
#   define UNIXLIKE 1
#endif
//
// Hardware Architecture and Byte Order
//
#define _ARCH_ALPHA   0x01
#define _ARCH_IA32    0x02
#define _ARCH_IA64    0x03
#define _ARCH_MIPS    0x04
#define _ARCH_HPPA    0x05
#define _ARCH_PPC     0x06
#define _ARCH_POWER   0x07
#define _ARCH_SPARC   0x08
#define _ARCH_AMD64   0x09
#define _ARCH_ARM     0x0a
#define _ARCH_M68K    0x0b
#define _ARCH_S390    0x0c
#define _ARCH_SH      0x0d


#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
	#define _ARCH _ARCH_ALPHA
	#define _ARCH_LITTLE_ENDIAN 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
	#define _ARCH _ARCH_IA32
	#define _ARCH_LITTLE_ENDIAN 1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define _ARCH _ARCH_IA64
	#if defined(hpux) || defined(_hpux)
		#define _ARCH_BIG_ENDIAN 1
	#else
		#define _ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__x86_64__) || defined(_M_X64)
	#define _ARCH _ARCH_AMD64
	#define _ARCH_LITTLE_ENDIAN 1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
	#define _ARCH _ARCH_MIPS
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__hppa) || defined(__hppa__)
	#define _ARCH _ARCH_HPPA
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || \
      defined(__powerpc__) || defined(__ppc__) || defined(__ppc) || defined(_ARCH_PPC) || defined(_M_PPC)
	#define _ARCH _ARCH_PPC
	#define _ARCH_BIG_ENDIAN 1
#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || \
      defined(_ARCH_PWR4) || defined(__THW_RS6000)
	#define _ARCH _ARCH_POWER
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
	#define _ARCH _ARCH_SPARC
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
	#define _ARCH _ARCH_ARM
	#if defined(__ARMEB__)
		#define _ARCH_BIG_ENDIAN 1
	#else
		#define _ARCH_LITTLE_ENDIAN 1
	#endif
#elif defined(__m68k__)
	#define _ARCH _ARCH_M68K
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__s390__)
	#define _ARCH _ARCH_S390
	#define _ARCH_BIG_ENDIAN 1
#elif defined(__sh__) || defined(__sh)
	#define _ARCH _ARCH_SH
	#if defined(__LITTLE_ENDIAN__)
		#define _ARCH_LITTLE_ENDIAN 1
	#else
		#define _ARCH_BIG_ENDIAN 1
	#endif
#endif

// compiler macros
#if defined(__GNUC__) || defined(__CYGWIN__)
#define __COMPILER_GCC 1
#define __COMPILER_CXX 1
#endif

#if defined(_MSC_VER)
#define COMPILER_MSVC 1
#if _MSC_VER < 1400
#define __COMPILER_MSVC7_OR_LOWER 1
#elif _MSC_VER < 1600
#define __COMPILER_MSVC9_OR_LOWER 1
#endif
#endif

#define COMPILER(x) defined (__COMPILER_##x)

#if COMPILER(GCC) || COMPILER(CXX)
#include <stddef.h>
#endif

#if (defined(__GNUC__) && (\
            defined(__GXX_EXPERIMENTAL_CXX0X__) ||\
            (__GNUC__ >= 4 && __GNUC_MINOR__ >= 3)))
#define CXX0X 1
#endif

#if defined(__GNUC__)
#include <limits.h>
#endif

#if COMPILER(GCC)
#define ALIGN_OF(type) __alignof__(type)
#define ALIGNMENT(type, varname, alignment) \
    type varname __attribute__((__aligned__(alignment)))
#elif COMPILER(MSVC)
#define ALIGN_OF(type) __alignof(type)
#define ALIGNMENT(type, varname, alignment) \
    __declspec(align(alignment)) type varname
#else
#error need alignment
#endif

// constants
#if defined(DEFAULT_TRUNK_SIZE) && DEFAULT_TRUNK_SIZE
#define TRUNK_SIZE DEFAULT_TRUNK_SIZE
#else
#define TRUNK_SIZE (64*1024)
#endif

#define RECV_BUF_SIZE (4096)
#define SEND_BUF_SIZE TRUNK_SIZE

// utilies
#undef MAX
#define MAX(x, y) ((x)>(y)?(x):(y))

#undef MIN
#define MIN(x, y) ((x)<(y)?(x):(y))

#undef UNUSE
#define UNUSE(x) ((void)(x))

#define CLRERR() (errno=0)

// memory
#ifdef UNIXLIKE
#   include <string.h>
#   define MEMZRO(d,s) memset((d), 0x00, (s))
#   define MEMSET memset
#   define MEMCPY memcpy
#   define MEMMOVE memmove
#elif defined(WINDOWS)
#   include <Windows.h>
#   define MEMZRO(d,s) ZeroMemory((d), (s))
#   define MEMSET memset
#   define MEMCPY memcpy
#   define MEMMOVE memmove
#else
#   error "system error"
#endif

// string format
#if defined(UNIXLIKE)
#define SNPRINTF    snprintf
#define VSNPRINTF   vsnprintf
#endif
#if defined(WINDOWS)
#define SNPRINTF    _snprintf
#define VSNPRINTF   _vsnprintf
#include <io.h>
#endif

#if COMPILER(GCC) || COMPILER(CXX)
#   define ATTR_NORETURN __attribute__((noreturn))
#   define ATTR_PRINTF(F,V) __attribute__ ((format (printf, F, V)))
#   define CONSTRUCTOR __attribute__((constructor))
#   define DESTRUCTOR __attribute__((destructor))
#else
#   define ATTR_NORETURN
#   define ATTR_PRINTF(F,V)
#   define CONSTRUCTOR
#   define DESTRUCTOR
#endif

#if !defined(_NDEBUG) && defined(__GNUC__)
#   define DEBUG_OUT(...) fprintf(stderr, __VA_ARGS__)
#else
#   define DEBUG_OUT(...)
#endif
#define EMPTY() fprintf(stderr, "Need implementation: %s\n", __PRETTY_FUNCTION__)

#ifndef TEMP_FAILURE_RETRY
#   if defined(__GNUC__)
#       define TEMP_FAILURE_RETRY(expr)                 \
    (                                                   \
        __extension__                                   \
        ({                                              \
            CLRERR();                                   \
            long int __result = 0;                      \
            do __result = (long int)(expr);             \
            while(__result == -1L && errno == EINTR);   \
            __result;                                   \
        })                                              \
    )
#   else
#       define TEMP_FAILURE_RETRY(expr) (expr)
#   endif
#endif

#if defined(__x86_64__)     \
    || defined(__amd64__)   \
    || defined(__amd64)     \
    || defined(_WIN64)
#   define CPU_64BIT 1
#endif

#ifdef CPU_64BIT
#   define I64_FMT "l"
#else
#   define I64_FMT "ll"
#endif

#define SZT "lu"

typedef UINT16 strlen_t;

