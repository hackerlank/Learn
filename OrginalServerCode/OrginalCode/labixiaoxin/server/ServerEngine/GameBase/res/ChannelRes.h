#ifndef __CHANNELRES_H_
#define __CHANNELRES_H_
#include "BaseRes.h"

class ChannelRes
{
public:
	char m_strName[MAX_ITEM_NAME + 1];
	ACE_UINT32 m_channelID;
public:
	ChannelRes();
};

#endif