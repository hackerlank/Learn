#pragma once

#include "..\..\Base\Service\BaseService.h"
//#include "ParentService.h"
//#include "ChildService.h"

//#define MAX_REGISTER_PARENT_SERVICE 4
//#define MAX_REGISTER_CHILD_SERVICE_TYPE 8




/*
typedef struct tagRegisterServiceInfo
{
	ACE_UINT32 unDesServiceID;
	Service_Status_Callback func;
}RegisterServiceInfo;
*/

//typedef ACE_DLList<ChildService> CHILD_SERVICE_LIST;
//typedef ACE_DLList_Iterator<ChildService> CHILD_SERVICE_LIST_ITERATOR;

/*
typedef struct tagChildListInfo
{
	ACE_UINT32 unServiceType;
	ACE_UINT32 useFlag;
	CHILD_SERVICE_LIST serviceList;
}ChildListInfo;
*/

class GameService : public BaseService
{
public:
	GameService();
	virtual ~GameService();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	//virtual int setQueryObjAddr(ACE_UINT32 unAdapterID, ObjAdr &addr);

	virtual int deal_msg(MessageInfo &msgInfo);

	virtual int get_service_info_msg(char *buff, int nMaxSize);

protected:
	int add_service_info_msg(char *buff, int offset, int nMaxSize, char *str);

	int get_service_current_status();
};