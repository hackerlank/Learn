#include "AdminCommandMgr.h"
#include "OnlineClient.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "json\json.h"
#include "..\Base\Communication\ServiceEndPoint.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "ace\INET_Addr.h"
#include "..\GameBase\Common\GameUtils.h"

#if _MEMORY_DEBUG
#include "./debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif


AdminCommandMgr::AdminCommandMgr(ACE_UINT32 unID)
:BaseAdapter(unID)
{
	m_key = new char[MAX_SECURITY_KEY_COUNT * SECURITY_KEY_LENGTH];

	if(init_key() == -1)
	{
		free_key();
	}
}

AdminCommandMgr::~AdminCommandMgr()
{
	free_key();
}

BaseObj *AdminCommandMgr::new_child_obj(ACE_UINT32 unID)
{
	return new AdminCommandSession(unID, this);
}

void AdminCommandMgr::free_key()
{
	if(m_key != NULL)
	{
		delete m_key;
		m_key = NULL;
	}
}

int AdminCommandMgr::deal_msg(MessageInfo &msgInfo)
{
	BaseAdapter::deal_msg(msgInfo);

	/*
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_CREATE_BASE_OBJ:
			{
				MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;

				if(create_child(body->unID) == -1)
				{
					//destroy client peer
				}
			}
			break;
		}
	}
	*/

	return 0;
}

int AdminCommandMgr::init_key()
{
	if(m_key == NULL)
	{
		return -1;
	}
	FILE *fp = ACE_OS::fopen("security_key_list.bin", "rb");

	if(fp == NULL)
	{
		return -1;
	}

	int ret = 0;

	if(fread(m_key, MAX_SECURITY_KEY_COUNT * SECURITY_KEY_LENGTH, 1, fp) < 1)
	{
		ret = -1;
	}

	fclose(fp);

	return ret;
}

bool AdminCommandMgr::is_valid_key(const char *key)
{
	return true;
	printf("src key = %s\n", key);

	if(m_key == NULL)
	{
		return false;
	}

	int t = (int)GameUtils::get_utc();
	t = t / 60;
	t = t % MAX_SECURITY_KEY_COUNT;

	int pt = t - 1;
	if(pt < 0)
	{
		pt = MAX_SECURITY_KEY_COUNT - 1;
	}

	print_key(pt);
	print_key(t);

	if(is_same_key(key, t) || is_same_key(key, pt))
	{
		return true;
	}

	return false;
}

void AdminCommandMgr::print_key(int cursor)
{
	char tmp[SECURITY_KEY_LENGTH + 1];
	ACE_OS::memcpy(tmp, &m_key[cursor * SECURITY_KEY_LENGTH], SECURITY_KEY_LENGTH);
	tmp[SECURITY_KEY_LENGTH] = '\0';

	printf("cursor at %d,key = %s\n", cursor, tmp);
}

bool AdminCommandMgr::is_same_key(const char *key, int cursor)
{
	if(ACE_OS::strncmp(key, &m_key[cursor * SECURITY_KEY_LENGTH], SECURITY_KEY_LENGTH) == 0)
	{
		return true;
	}

	return false;
}