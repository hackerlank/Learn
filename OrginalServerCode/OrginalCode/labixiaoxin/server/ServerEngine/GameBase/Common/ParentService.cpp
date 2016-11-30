#include "ParentService.h"

ParentService::ParentService()
{
	m_unServiceID = OBJ_ID_NONE;
	m_unStatus = SERVICE_REGISTER;
}

ParentService::~ParentService()
{

}

void ParentService::setDesServiceID(ACE_UINT32 unServiceID, Service_Status_Callback pCallback)
{
	m_unServiceID = unServiceID;
	m_unStatus = SERVICE_REGISTER;
	m_pCallback = pCallback;
}

void ParentService::unregister()
{
	m_unStatus = SERVICE_UNREGISTER;
}