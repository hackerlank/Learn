#ifndef BASE_DEF_H
#define BASE_DEF_H

#define MAX_HOSTSIZE (32)
#define MAX_USERSIZE (32)
#define MAX_PASSWORD (32)
#define MAX_DBSIZE (32)
#define MAX_NAME_SIZE (32)

//基本类型定义
typedef unsigned char BYTE; 
typedef unsigned short WORD;
typedef signed short SWORD;
typedef unsigned int DWORD;
typedef signed int SDWORD;
typedef unsigned long QWORD;
typedef signed long SQWORD;

#ifndef _USE_CMD_NAME_SPACE
#define _USE_CMD_NAME_SPACE
#endif

#ifdef _USE_CMD_NAME_SPACE
#define _CMD_NAMESPACE_BEGIN namespace Cmd {
#define _CMD_NAMESPACE_END };
#else
#define _CMD_NAMESPACE_BEGIN
#define _CMD_NAMESPACE_END
#endif

#define MAX_NAMESIZE    16
#define MAX_IP_LENGTH   32


#endif

