#pragma once

#include "ace\ACE.h"
#include "ace\Message_Block.h"

class SlideWindow
{
public:
	SlideWindow(ACE_UINT32 unWindowSize = 128);
	~SlideWindow();
	
	int resize(ACE_UINT32 unWindowSize);
	void reset();

	ACE_UINT32 currentSN();

	int put(ACE_UINT32 unSN, ACE_Message_Block *msg);
	ACE_Message_Block *get();

private:
	ACE_UINT32 m_unWindowSize;
	ACE_Message_Block **m_window;

	ACE_UINT32 m_unCursor;
	ACE_UINT32 m_unCurrentSN;
};