#include "StdinHandler.h"
#include "ace/OS_main.h"
#include "ace/OS_NS_unistd.h"
#include "..\Protocol\Protocol.h"
#include "..\Protocol\ServiceProtocol.h"
#include "..\Service\ServiceObj.h"
#include "..\Service\BaseService.h"

StdinHandler::StdinHandler()
{
	
}
// Constructor.

StdinHandler::~StdinHandler (void)
{
	
}

int StdinHandler::hook_stdin()
{
	return ACE_Event_Handler::register_stdin_handler(this, ACE_Reactor::instance (), ACE_Thread_Manager::instance());
}

// Destructor.

// Event demuxer hooks.
int StdinHandler::handle_input (ACE_HANDLE h)
{
	char buf[BUFSIZ];
	if(h == ACE_STDIN)
	{
		ssize_t result = ACE_OS::read (h, buf, BUFSIZ - 1);

		if (result > 0)
		{
			buf[result] = '\0';

			if(result >= 2)
			{
				if(buf[result - 2] == '\r')
				{
					buf[result - 2] = '\0';
				}
				else if(buf[result - 1] == '\n')
				{
					buf[result - 1] = '\0';
				}
			}
			else if(result == 1)
			{
				if(buf[result - 1] == '\n')
				{
					buf[result - 1] = '\0';
				}
			}
			//send message
			MessageInfo msg;
			

			if(allocMessageWithInfo(msg, sizeof(MsgConsoleCmd), SERVICE_MESSAGE_TYPE_CTRL, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, MSG_SERVICE_CONSOLE_CMD) == 0)
			{
				MsgConsoleCmd *pcmd = (MsgConsoleCmd *)msg.body;
				ACE_OS::strncpy(pcmd->cmd, buf, MAX_CONSOLE_CMD_LENGTH);
				BaseService::instance()->put(msg.msg);
			}
		}
		else if (result == -1)
		{
			//ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "can't read from STDIN"), -1);
			return -1;
		}
		else // result == 0
		{
			//ACE_Reactor::end_event_loop ();
			//return -1;
			return -1;
		}
	}

	return 0;
}

int StdinHandler::handle_close (ACE_HANDLE h, ACE_Reactor_Mask)
{
	if(h == ACE_STDIN)
	{
		ACE_DEBUG ((LM_DEBUG,
			"STDIN_Events handle removed from reactor.\n"));
		if (ACE_Reactor::instance()->remove_handler(this, ACE_Event_Handler::READ_MASK) == -1)
		{
			ACE_ERROR_RETURN ((LM_ERROR, "%p\n", "remove_handler"), -1);
		}
	}

	return 0;
}