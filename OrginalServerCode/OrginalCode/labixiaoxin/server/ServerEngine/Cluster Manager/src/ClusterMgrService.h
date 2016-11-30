#pragma once

#include "..\..\GameBase\Common\GameService.h"

class ClusterMgrService : public GameService
{
public:
	ClusterMgrService();
	~ClusterMgrService();

	virtual int service_init();
};