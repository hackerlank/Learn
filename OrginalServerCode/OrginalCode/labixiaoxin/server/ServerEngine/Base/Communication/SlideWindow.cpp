#include "SlideWindow.h"
#include "..\Protocol\Protocol.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

SlideWindow::SlideWindow(ACE_UINT32 unWindowSize)
{
	m_window = NULL;
	resize(unWindowSize);
}

SlideWindow::~SlideWindow()
{
	if(m_window)
	{
		delete m_window;
	}

	m_window = NULL;
}


int SlideWindow::resize(ACE_UINT32 unWindowSize)
{
	if(m_window)
	{
		reset();
		delete m_window;
	}

	m_unWindowSize = unWindowSize;
	m_window = new ACE_Message_Block *[m_unWindowSize];

	if(m_window == NULL)
	{
		return -1;
	}

	memset(m_window, 0, sizeof(ACE_Message_Block *) * m_unWindowSize);

	m_unCursor = 0;
	m_unCurrentSN = 0;

	return 0;
}

int SlideWindow::put(ACE_UINT32 unSN, ACE_Message_Block *msg)
{
	if(m_window == NULL)
	{
		return -1;
	}

	//MessageHead *m_head = (MessageHead *)(msg->base() + sizeof(ServiceHead));
	//PacketHead *p_head = (PacketHead *)msg->base();

	if(unSN < m_unCurrentSN)
	{
		return 0;
	}

	if(unSN >= (m_unCurrentSN + m_unWindowSize))
	{
		return -1;
	}

	int idx = (m_unCursor + (unSN - m_unCurrentSN)) % m_unWindowSize;

	if(m_window[idx] != NULL)
	{
		return 0;
	}

	m_window[idx] = msg;

	return 1;
}

ACE_Message_Block *SlideWindow::get()
{
	ACE_Message_Block *ret_msg = m_window[m_unCursor];

	if(ret_msg != NULL)
	{
		m_window[m_unCursor] = NULL;

		m_unCursor = (m_unCursor + 1) % m_unWindowSize;

		m_unCurrentSN ++;
	}

	return ret_msg;
}

void SlideWindow::reset()
{
	if(m_window == NULL)
	{
		return;
	}

	for(ACE_UINT32 i = 0;i < m_unWindowSize;i ++)
	{
		if(m_window[i] != NULL)
		{
			m_window[i]->release();
		}
	}

	memset(m_window, 0, sizeof(ACE_Message_Block *) * m_unWindowSize);

	m_unCursor = 0;
	m_unCurrentSN = 0;
}

ACE_UINT32 SlideWindow::currentSN()
{
	return m_unCurrentSN;
}