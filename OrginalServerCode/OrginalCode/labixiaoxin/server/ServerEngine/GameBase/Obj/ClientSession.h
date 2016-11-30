#pragma once

#include "..\..\Base\Service\BaseObj.h"

class ClientSession : public BaseObj
{
public:
	ClientSession(ACE_UINT32 unID, ACE_UINT32 unSessionID, BaseAdapter *parent, ObjAdr entityAdr);
	virtual ~ClientSession();

	void setSessionID(ACE_UINT32 unSessionID);
	void setEntityAdr(ObjAdr entityAdr);

	virtual int dealMsg(MessageInfo &msgInfo);

	virtual void run();

private:
	void closeClientConnection(ACE_UINT32 unSessionID, ACE_UINT32 unID);
	void closeClientConnection(ACE_UINT64 verifyID);

	int m_unLostConnectionCounter;

	ObjAdr m_entityAdr;
	
	ACE_UINT32 m_unSessionID;
	ACE_UINT64 m_verifyID;
};