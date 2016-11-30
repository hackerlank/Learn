#pragma once

#include "ace/Reactor.h"
#include "ace/Thread_Manager.h"

class StdinHandler : public ACE_Event_Handler
{
public:
	StdinHandler ();
	// Constructor.

	~StdinHandler (void);
	// Destructor.

	int hook_stdin();
	
	// Event demuxer hooks.
	virtual int handle_input (ACE_HANDLE);
	virtual int handle_close (ACE_HANDLE, ACE_Reactor_Mask);
};