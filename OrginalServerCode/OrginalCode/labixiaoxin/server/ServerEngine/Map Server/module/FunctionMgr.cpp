#include "FunctionMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\Map.h"

FunctionMgr::FunctionMgr()
{
	
}

FunctionMgr::~FunctionMgr()
{

}

void FunctionMgr::init(ACE_UINT32 *list)
{
	ACE_OS::memcpy(m_functionList, list, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);

	int i;

	m_unLockedCount = 0;

	for(i = 0;i < MAX_FUNCTION_COUNT;i ++)
	{
		if(m_functionList[i] == 0)
		{
			break;
		}
	}

	m_unLockedCount = i;
}

void FunctionMgr::update(ACE_UINT32 unCurrentTime)
{
}

void FunctionMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgFunctionListResponse response;
	response.nResult = 0;
	response.unSN = unSN;
	response.unCount = m_unLockedCount;
	ACE_OS::memcpy(response.list, m_functionList, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_FUNCTION_LIST_RESPONSE, (char *)&response, sizeof(MsgFunctionListResponse), targetAdr);
}

void FunctionMgr::update_2_db()
{
	MsgDBUpdateFunctionListRequest db_request;
	ACE_OS::memcpy(db_request.list, m_functionList, sizeof(ACE_UINT32) * MAX_FUNCTION_COUNT);

	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_FUNCTION_LIST, (char *)&db_request, sizeof(MsgDBUpdateFunctionListRequest));
}

void FunctionMgr::unlock(ACE_UINT32 unID)
{
	int i;

	int idx = -1;

	for(i = 0;i < m_unLockedCount;i ++)
	{
		if(m_functionList[i] == unID)
		{
			idx = i;
			break;
		}
	}

	if(idx == -1)
	{
		return;
	}

	if(idx != (m_unLockedCount - 1))
	{
		m_functionList[idx] = m_functionList[m_unLockedCount - 1];
		//m_functionList[m_unLockedCount - 1] = 0;
	}

	m_functionList[m_unLockedCount - 1] = 0;

	m_unLockedCount --;

	update_2_db();
}

bool FunctionMgr::is_locked(ACE_UINT32 unID)
{
	for(int i = 0;i < m_unLockedCount;i ++)
	{
		if(m_functionList[i] == unID)
		{
			return true;
		}
	}

	return false;
}