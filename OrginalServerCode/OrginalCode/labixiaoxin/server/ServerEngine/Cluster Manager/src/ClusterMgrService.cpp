#include "ClusterMgrService.h"
#include "OnlineUserMgr.h"
#include "GatewayInfoMgr.h"

ClusterMgrService::ClusterMgrService()
{

}

ClusterMgrService::~ClusterMgrService()
{

}

int ClusterMgrService::service_init()
{
	OnlineUserMgr *userMgr = new OnlineUserMgr();

	if(userMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(userMgr) == -1)
	{
		delete userMgr;
		return -1;
	}

	GatewayInfoMgr *gInfoMgr = new GatewayInfoMgr();

	if(gInfoMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(gInfoMgr) == -1)
	{
		delete gInfoMgr;
		return -1;
	}

	return 0;
}