#include "Protocol.h"

#include "ace\OS_main.h"
#include "ace\OS_Memory.h"

char public_send_buff[81920];

ACE_Message_Block *allocServiceMessage(int nAct, ACE_UINT32 unBodySize)
{
	ACE_Message_Block *msg = NULL;
	ACE_NEW_NORETURN(msg, ACE_Message_Block(sizeof(PacketHead) + sizeof(MsgInfoHead) + sizeof(MessageHead) + unBodySize));

	if(msg == NULL)
	{
		return NULL;
	}

	resetServiceMessage(*msg, nAct);

	return msg;
}

int allocMessageWithInfo(MessageInfo &info, ACE_UINT32 unBodySize, ACE_UINT32 unType, ACE_UINT32 unDesServiceID, ACE_UINT32 unDesAdapterID, 
						 ACE_UINT32 unDesObjID, ACE_UINT32 unSrcServiceID, ACE_UINT32 unSrcAdapterID, ACE_UINT32 unSrcObjID, ACE_UINT32 unMsgType)
{
	ACE_Message_Block *msg = allocServiceMessage(SERVICE_MESSAGE_ACT_WRITE, unBodySize);

	if(msg == NULL)
	{
		return -1;
	}

	parseMsg(info, msg);

	info.p_head->unType = unType;
	info.s_head->desAdr.unServiceID = unDesServiceID;
	info.s_head->desAdr.unAdapterID = unDesAdapterID;
	info.s_head->desAdr.unObjID = unDesObjID;
	info.s_head->srcAdr.unServiceID = unSrcServiceID;
	info.s_head->srcAdr.unAdapterID = unSrcAdapterID;
	info.s_head->srcAdr.unObjID = unSrcObjID;

	info.m_head->unType = unMsgType;

	info.nBodySize = unBodySize;

	return 0;
}

void resetServiceMessage(ACE_Message_Block &msg, int nAct)
{
	if(nAct == SERVICE_MESSAGE_ACT_WRITE)
	{
		msg.wr_ptr(msg.base() + msg.size());
	}
	else
	{
		msg.wr_ptr(msg.base());
	}
	
	msg.rd_ptr(msg.base());

	memset(msg.base(), 0, msg.size());
}

int parseMsg(MessageInfo &info, ACE_Message_Block *msg)
{
	if(msg == NULL)
	{
		return -1;
	}

	int len = msg->total_length();

	if(msg->length() < (sizeof(PacketHead) + sizeof(MsgInfoHead) + sizeof(MessageHead)))
	{
		return -1;
	}

	info.p_head = (PacketHead *)msg->base();
	info.i_head = (MsgInfoHead *)(msg->base() + sizeof(PacketHead));
	info.s_head = &(info.i_head->s_head);
	//info.c_head = &(info.i_head->c_head);
	info.m_head = (MessageHead *)(msg->base() + sizeof(PacketHead) + sizeof(MsgInfoHead));
	info.body = (void *)(msg->base() + sizeof(PacketHead) + sizeof(MsgInfoHead) + sizeof(MessageHead));
	info.msg = msg;
	info.nBodySize = (msg->total_length() - (sizeof(PacketHead) + sizeof(MsgInfoHead) + sizeof(MessageHead)));

	return 0;
}
