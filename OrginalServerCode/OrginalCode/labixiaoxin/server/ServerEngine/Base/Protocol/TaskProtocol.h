#pragma once

#include "Protocol.h"

#define TASK_PROTOCOL_GROUP 0x1000

#define MSG_TASK_TIMER							MAKE_MSG_TYPE(TASK_PROTOCOL_GROUP, 0x0001)
#define MSG_TASK_REMOTE_CALL					MAKE_MSG_TYPE(TASK_PROTOCOL_GROUP, 0x0002)
#define MSG_TASK_REMOTE_NORMAL					MAKE_MSG_TYPE(TASK_PROTOCOL_GROUP, 0x0003)
#define MSG_TASK_REMOTE_CANCEL					MAKE_MSG_TYPE(TASK_PROTOCOL_GROUP, 0x0004)
#define MSG_TASK_REMOTE_CALL_EXCEPTION			MAKE_MSG_TYPE(TASK_PROTOCOL_GROUP, 0x0005)


#define MAX_TASK_NAME_LEN 64

/*
typedef struct tagTaskMsg
{
	ACE_UINT32 unTaskNo;;
	char pContent[1];
}TaskMsg;
*/

typedef struct tagTaskCallInfo
{
	char strName[MAX_TASK_NAME_LEN];
	ACE_UINT32 unArgLen;
	char arg[1];
}TaskCallInfo;
