#pragma once

#include "ace\ACE.h"

class GameService;

//向目的Service 报告状态的回调函数
typedef int (*Service_Status_Callback)(ACE_UINT32, GameService *, char *, int);

class ParentService
{
public:
	enum
	{
		SERVICE_REGISTER = 0,
		SERVICE_REGISTER_DONE,
		SERVICE_UNREGISTER
	};
	ParentService();
	~ParentService();

	void setDesServiceID(ACE_UINT32 unServiceID, Service_Status_Callback pCallback);
	void unregister();

	ACE_UINT32 m_unServiceID;
	ACE_UINT8 m_unStatus;
	Service_Status_Callback m_pCallback;
};