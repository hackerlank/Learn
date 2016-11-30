#pragma once

#include "ace\Asynch_IO.h"
#include "ace\Recursive_Thread_Mutex.h"
#include "..\..\base\Service\ServiceObj.h"
#include "..\..\Base\Communication\StreamRW.h"

//#define MAX_CLIENT_TCP_MSG 1024
#define MAX_PHP_TCP_MSG 4096

//typedef void (*Timer_Callback_Func)(void *, long);
//typedef ACE_Message_Block *(*Read_Client_Msg_Func)(char *, int size, ObjAdr &adr);
//typedef int (*Write_Client_Msg_Func)(ACE_Message_Block *msg, char *, int size);
class PhpEndPoint;

class PhpConnection : public ACE_Service_Handler
{
public:
	enum
	{
		NORMAL = 0,
		DESTROY
	};

	PhpConnection();
	virtual ~PhpConnection();

	virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

	virtual int openConnection();
	virtual void closeConnection();

	void setEndPoint(PhpEndPoint *endPoint);

	int send_msg(ACE_Message_Block *msg);

	void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);
	void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

	bool m_bReading;
	bool m_bWriting;

	ACE_UINT32 m_unPeerID;
protected:
	ACE_Asynch_Read_Stream m_rd;
	ACE_Asynch_Write_Stream m_wd;
private:
	int read_msg_body();

	bool isStringEnd(char *str, int start, int end);
	int putPhpRequest(ACE_Message_Block *msg);

	int m_nReadOffset;

	bool can_destroy();

	PhpEndPoint *m_endPoint;
};